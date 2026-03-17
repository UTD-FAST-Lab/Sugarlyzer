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
}
