package sugarlyzer.tester.sugarc

import com.microsoft.z3.{BoolExpr, Context, Status}
import io.circe.Encoder
import com.typesafe.scalalogging.Logger
import scala.util.Using

case class PresenceCondition(
    configs: Set[Map[String, String]],
    simplifiedCache: Option[String] = None
) {

  def &&(other: PresenceCondition): PresenceCondition = {
    val newConfigs = for {
      c1     <- this.configs
      c2     <- other.configs
      merged <- mergeConfigs(c1, c2)
    } yield merged
    PresenceCondition(newConfigs)
  }

  def ||(other: PresenceCondition): PresenceCondition = {
    PresenceCondition(this.configs ++ other.configs)
  }

  def simplify: PresenceCondition = {
    val simplifiedStr = Using.resource(new Context()) { ctx =>
      toZ3(ctx).simplify().toString
    }
    this.copy(simplifiedCache = Some(simplifiedStr))
  }

  def isSatisfiable: Boolean = configs.nonEmpty

  def getModel: String = {
    if (configs.isEmpty) return "Unsatisfiable"
    Using.resource(new Context()) { ctx =>
      val solver = ctx.mkSolver()
      solver.add(toZ3(ctx))
      if (solver.check() == Status.SATISFIABLE) solver.getModel.toString
      else "Unsatisfiable"
    }
  }

  def numConsts: Int = {
    if (configs.isEmpty) return 0
    Using.resource(new Context()) { ctx =>
      val solver = ctx.mkSolver()
      solver.add(toZ3(ctx))
      if (solver.check() == Status.SATISFIABLE)
        solver.getModel.getConstDecls.length
      else 0
    }
  }

  private def mergeConfigs(
      c1: Map[String, String],
      c2: Map[String, String]
  ): Option[Map[String, String]] = {
    val keys = c1.keySet ++ c2.keySet
    keys.foldLeft(Option(Map.empty[String, String])) { (accOpt, k) =>
      accOpt.flatMap { acc =>
        (c1.get(k), c2.get(k)) match {
          case (Some(v1), Some(v2)) if v1.toLowerCase != v2.toLowerCase => None
          case (Some(v1), _) => Some(acc + (k -> v1))
          case (_, Some(v2)) => Some(acc + (k -> v2))
          case _             => Some(acc)
        }
      }
    }
  }

  private def toZ3(ctx: Context): BoolExpr = {
    if (configs.isEmpty) return ctx.mkFalse()
    val orClauses = configs.map { config =>
      if (config.isEmpty) ctx.mkTrue()
      else {
        val andClauses = config.map { case (mac, value) =>
          value.toLowerCase match {
            case "true" | "y" =>
              ctx.mkEq(ctx.mkConst(mac, ctx.mkBoolSort()), ctx.mkTrue())
            case "false" | "n" =>
              ctx.mkEq(ctx.mkConst(mac, ctx.mkBoolSort()), ctx.mkFalse())
            case i if i.toIntOption.isDefined =>
              ctx.mkEq(ctx.mkConst(mac, ctx.mkIntSort()), ctx.mkInt(i.toInt))
            case s =>
              ctx.mkEq(ctx.mkConst(mac, ctx.mkStringSort()), ctx.mkString(s))
          }
        }
        if (andClauses.size == 1) andClauses.head
        else ctx.mkAnd(andClauses.toSeq*)
      }
    }
    if (orClauses.size == 1) orClauses.head else ctx.mkOr(orClauses.toSeq*)
  }
}

object PresenceCondition {
  val logger = Logger[PresenceCondition]

  given Encoder[PresenceCondition] = Encoder.instance { pc =>
    io.circe.Json.fromString(pc.simplifiedCache.getOrElse {
      Using.resource(new Context()) { ctx => pc.toZ3(ctx).toString }
    })
  }

  def vacuouslyTrue(ctx: Context = null): PresenceCondition =
    PresenceCondition(Set(Map.empty))

  def fromTuples(tups: Iterable[(String, String)]): PresenceCondition = {
    PresenceCondition(Set(tups.toMap))
  }
}
