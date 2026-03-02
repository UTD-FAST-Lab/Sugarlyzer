package sugarlyzer.tester.sugarc

import com.microsoft.z3.{BoolExpr, Context, Status}

case class PresenceCondition(ctx: Context, expr: BoolExpr) {

  def &&(other: PresenceCondition): PresenceCondition = {
    val otherExpr =
      if (other.ctx eq ctx) other.expr else other.expr.translate(ctx)
    PresenceCondition(ctx, ctx.mkAnd(expr, otherExpr))
  }

  def isSatisfiable: Boolean = {
    val solver = ctx.mkSolver()
    solver.add(expr)
    solver.check() == Status.SATISFIABLE
  }
}

object PresenceCondition {
  def vacuouslyTrue(ctx: Context): PresenceCondition =
    PresenceCondition(ctx, ctx.mkTrue())
}
