package sugarlyzer.tester.sugarc

import com.microsoft.z3.{BoolExpr, Context}

/** Parses C preprocessor presence condition expressions into Z3 BoolExprs.
  *
  * Handles the grammar produced by SugarC's desugaring, e.g.:
  *   !(defined HELLO_WORLD) && (defined GOODBYE_WORLD)
  *   (defined A) || ((defined B) && (defined C))
  *
  * Grammar:
  *   expr     ::= or_expr
  *   or_expr  ::= and_expr ('||' and_expr)*
  *   and_expr ::= not_expr ('&&' not_expr)*
  *   not_expr ::= '!' not_expr | atom
  *   atom     ::= '(' expr ')'
  *              | '(' 'defined' IDENT ')'
  *              | 'defined' IDENT
  *              | IDENT
  */
object PresenceConditionParser {

  def parse(ctx: Context, condition: String): BoolExpr = {
    val tokens = tokenize(condition)
    val parser = new Parser(ctx, tokens)
    val result = parser.parseExpr()
    if (parser.hasRemaining) {
      throw new IllegalArgumentException(
        s"Unexpected trailing tokens in: $condition"
      )
    }
    result
  }

  private sealed trait Token
  private case object TokNot                extends Token
  private case object TokAnd                extends Token
  private case object TokOr                 extends Token
  private case object TokLParen             extends Token
  private case object TokRParen             extends Token
  private case object TokDefined            extends Token
  private case class TokIdent(name: String) extends Token
  private case object TokCmpOp              extends Token

  private def tokenize(s: String): Array[Token] = {
    val buf = collection.mutable.ArrayBuffer.empty[Token]
    var i   = 0
    while (i < s.length) {
      s(i) match {
        case ' ' | '\t' | '\n' | '\r' =>
          i += 1
        case '!' =>
          buf += TokNot; i += 1
        case '(' =>
          buf += TokLParen; i += 1
        case ')' =>
          buf += TokRParen; i += 1
        case '&' if i + 1 < s.length && s(i + 1) == '&' =>
          buf += TokAnd; i += 2
        case '|' if i + 1 < s.length && s(i + 1) == '|' =>
          buf += TokOr; i += 2
        case '=' if i + 1 < s.length && s(i + 1) == '=' =>
          buf += TokCmpOp; i += 2
        case '<' if i + 1 < s.length && s(i + 1) == '=' =>
          buf += TokCmpOp; i += 2
        case '>' if i + 1 < s.length && s(i + 1) == '=' =>
          buf += TokCmpOp; i += 2
        case c if c.isLetterOrDigit || c == '_' =>
          val start = i
          while (i < s.length && (s(i).isLetterOrDigit || s(i) == '_')) {
            i += 1
          }
          val word = s.substring(start, i)
          if (word == "defined") buf += TokDefined
          else buf += TokIdent(word)
        case c =>
          throw new IllegalArgumentException(
            s"Unexpected character '$c' at position $i in: $s"
          )
      }
    }
    buf.toArray
  }

  private class Parser(ctx: Context, tokens: Array[Token]) {
    private var pos = 0

    def hasRemaining: Boolean = pos < tokens.length

    private def peek: Option[Token] =
      if (pos < tokens.length) Some(tokens(pos)) else None

    private def expect(tok: Token): Unit = {
      peek match {
        case Some(t) if t == tok => pos += 1
        case got =>
          throw new IllegalArgumentException(
            s"Expected $tok but got $got at position $pos"
          )
      }
    }

    def parseExpr(): BoolExpr = parseOr()

    private def parseOr(): BoolExpr = {
      var left = parseAnd()
      while (peek.contains(TokOr)) {
        pos += 1
        val right = parseAnd()
        left = ctx.mkOr(left, right)
      }
      left
    }

    private def parseAnd(): BoolExpr = {
      var left = parseNot()
      while (peek.contains(TokAnd)) {
        pos += 1
        val right = parseNot()
        left = ctx.mkAnd(left, right)
      }
      left
    }

    private def parseNot(): BoolExpr = {
      if (peek.contains(TokNot)) {
        pos += 1
        ctx.mkNot(parseNot())
      } else {
        parseAtom()
      }
    }

    private def parseAtom(): BoolExpr = {
      peek match {
        case Some(TokLParen) =>
          pos += 1
          // Distinguish `(defined IDENT)` from a grouped sub-expression
          if (peek.contains(TokDefined)) {
            pos += 1
            val name = parseIdent()
            expect(TokRParen)
            ctx.mkBoolConst(name)
          } else {
            // Peek ahead: if it's `(IDENT cmp_op NUMBER)`, consume and return the ident
            val savedPos = pos
            peek match {
              case Some(TokIdent(name)) if pos + 2 < tokens.length &&
                  tokens(pos + 1) == TokCmpOp &&
                  tokens(pos + 2).isInstanceOf[TokIdent] &&
                  tokens(pos + 2).asInstanceOf[TokIdent].name.forall(_.isDigit) =>
                pos += 3
                expect(TokRParen)
                ctx.mkBoolConst(name)
              case _ =>
                pos = savedPos
                val expr = parseExpr()
                expect(TokRParen)
                expr
            }
          }
        case Some(TokDefined) =>
          pos += 1
          val name = parseIdent()
          ctx.mkBoolConst(name)
        case Some(TokIdent(name)) =>
          pos += 1
          ctx.mkBoolConst(name)
        case got =>
          throw new IllegalArgumentException(
            s"Expected '(', 'defined', or identifier but got $got at position $pos"
          )
      }
    }

    private def parseIdent(): String = {
      peek match {
        case Some(TokIdent(name)) =>
          pos += 1
          name
        case got =>
          throw new IllegalArgumentException(
            s"Expected identifier but got $got at position $pos"
          )
      }
    }
  }
}
