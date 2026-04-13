package sugarlyzer.tester.sugarc

import com.microsoft.z3.{BoolExpr, Context, Status}
import io.circe.Encoder

case class PresenceCondition(ctx: Context, expr: BoolExpr) {

  def &&(other: PresenceCondition): PresenceCondition = {
    val otherExpr =
      if (other.ctx eq ctx) other.expr else other.expr.translate(ctx)
    PresenceCondition(ctx, ctx.mkAnd(expr, otherExpr))
  }

  def ||(other: PresenceCondition): PresenceCondition = {
    val otherExpr =
      if (other.ctx eq ctx) other.expr else other.expr.translate(ctx)
    PresenceCondition(ctx, ctx.mkOr(expr, otherExpr))
  }

  def simplify: PresenceCondition = {
    PresenceCondition(ctx, expr.simplify().asInstanceOf[BoolExpr])
  }

  def isSatisfiable: Boolean = {
    val solver = ctx.mkSolver()
    solver.add(expr)
    solver.check() == Status.SATISFIABLE
  }

  def getModel: String = {
    val solver = ctx.mkSolver()
    solver.add(expr)
    if (solver.check() == Status.SATISFIABLE) {
      solver.getModel.toString
    } else {
      "Unsatisfiable"
    }
  }
}

object PresenceCondition {
  given Encoder[PresenceCondition] {
    def apply(pc: PresenceCondition): io.circe.Json = {
      /* For simplicity, we just encode the string representation of the
       * expression. */
      /* In a real implementation, you might want to serialize the expression in
       * a more structured way. */
      io.circe.Json.fromString(pc.expr.toString)
    }
  }

  def vacuouslyTrue(ctx: Context): PresenceCondition =
    PresenceCondition(ctx, ctx.mkTrue())

  def fromTuples(tups: Iterable[(String, String)]): PresenceCondition = {
    /* Transform the list of tuples, which is of the form [("MACRO_NAME", TRUE)]
     * into a conjunction of expressions */
    val ctx = new Context()
    val exprs = tups.map { case (mac, value) =>
      val const = ctx.mkConst(mac, ctx.mkBoolSort())
      val boolValue = value.toLowerCase match {
        case "true"  => ctx.mkTrue()
        case "false" => ctx.mkFalse()
        case _ => throw new IllegalArgumentException(s"Invalid value: $value")
      }
      ctx.mkEq(const, boolValue)
    }
    PresenceCondition(ctx, ctx.mkAnd(exprs.toSeq*))
  }
}
