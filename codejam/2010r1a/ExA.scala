import scala.io.Source


object ExA {
  def main(args: Array[String]): Unit = {
    val lines = Source.fromFile(args(0)).getLines
    val N:Int = lines.next().toInt
    for(i <- 1 to N) {
      val l = lines.next()
      l.split(" ").map(_.toInt) match {
        case Array(n, k) => {
          val r = solve(n, k, lines.slice(0, n).toArray);
          println(f"Case #$i%d: $r%s")
        }
      }
    }
  }

  def solve(n: Int, k: Int, lines: Array[String]): String = {
    val lr = leftright(lines)
    val l = lr._1;
    val r = lr._2;
    //  println(lines.mkString);
    //  println(p.mkString("\n"));
    //  println(l.mkString("\n"));
    //  println(r.mkString("\n"));
     val x = (is_winning(k, l, 'R'), is_winning(k, l, 'B'))
     x match {
       case (true, true) => "Both"
       case (true, false) => "Red"
       case (false, true) => "Blue"
       case (false, false) => "Neither"
     }
  }

  def leftright(lines: Array[String]): Tuple2[Array[String], Array[String]] = {
     val p:Array[Tuple2[String, String]] = lines.map(_.partition(_=='.'))
     val l:Array[String] = p.map(x=>x._1 + x._2)
     val r:Array[String] = p.map(x=>x._2 + x._1)
     return (l,r)
  }

   def is_winning(k: Int, lines: Array[String], c: Char): Boolean = {
      checkwin(k, lines.map(_.map(_==c).toArray))
   }

   def checkwin(k: Int, map: Array[Array[Boolean]]): Boolean = {
     (map.count(has_k(k, _)) +
      map.transpose.count(has_k(k, _)) +
      diag(map).count(has_k(k, _))
    ) > 0
   }

   def diag(m: Array[Array[Int]]): Array[Array[Int]] = {
      diagx(m.length, 2).map(d=>{
        d.map(i=>m(i._1)(i._2)) toArray
      }) toArray
   }

   def diag(m: Array[Array[Boolean]]): Array[Array[Boolean]] = {
      diagx(m.length, 2).map(d=>{
        d.map(i=>m(i._1)(i._2)) toArray
      }) toArray
   }

   def diagi(n: Int, m: Int): List[List[(Int, Int)]] = {
     (for(i <- (1-n) until n) yield {
       //val a = 0 max i
       //val b = n min (n-i)
       //println("diag range:", a, b, i)
       (0 until n)
       .map(x=>(x, x+i)) 
       .filter(x=>(x._1 >= 0 && x._1 < n &&
                   x._2 >= 0 && x._2 < n))
       .toList
     }) filter(_.length >= m) toList
   }

   def diagx(n: Int, m: Int): List[List[(Int, Int)]] = {
       diagi(n, m) :::
        (diagi(n, m) map {
          x => x map (r => (r._1, n-r._2-1))
        })
   }

   def has_k(k: Int, vals: Array[Boolean]): Boolean = {
     vals.scanLeft(0)((a,b) => if(b) a+1 else 0).max >= k
   }
}

import collection.mutable.Stack
import org.scalatest._

class ATest extends FlatSpec with Matchers {

  "has_k()" should "give give correct results" in {
    val a1:Boolean = ExA.has_k(2, Array(false, false, true, true, false))
    val a2:Boolean = ExA.has_k(2, Array(false, true, false, true, false, true))
    val a3:Boolean = ExA.has_k(2, Array(true, true, true, true, true))
    a1 should be (true);
    a2 should be (false);
    a3 should be (true);
  }

  "checkwin()" should "find a winner" in {
    ExA.checkwin(2, Array(
      Array(false, false, true),
      Array(false, false, true),
      Array(false, false, false)
    )) should be (true)

    ExA.checkwin(2, Array(
      Array(true, true),
      Array(false, false)
    )) should be (true)

    ExA.checkwin(2, Array(
      Array(true, false),
      Array(false, false)
    )) should be (false)
  }

  "checkwin()" should "should true in diagonals" in {
    ExA.checkwin(2, Array(
      Array(false, true, false),
      Array(false, false, true),
      Array(false, false, false)
    )) should be (true)

    ExA.checkwin(2, Array(
      Array(false, false, false),
      Array(false, false, true),
      Array(false, true, false)
    )) should be (true)

    ExA.checkwin(2, Array(
      Array(false, true, false),
      Array(true, false, false),
      Array(false, true, false)
    )) should be (true)

    ExA.checkwin(2, Array(
      Array(false, true, false),
      Array(true, false, false),
      Array(false, false, false)
    )) should be (true)

    ExA.checkwin(2, Array(
      Array(false, false, false),
      Array(false, true, false),
      Array(false, false, true)
    )) should be (true)

    ExA.checkwin(2, Array(
      Array(false, false, false),
      Array(false, true, false),
      Array(true, false, false)
    )) should be (true)

    ExA.checkwin(2, Array(
      Array(true, false, false),
      Array(false, true, false),
      Array(false, false, false)
    )) should be (true)
  }

  "checkwin()" should "should false in" in {
    ExA.checkwin(2, Array(
      Array(true, false, true),
      Array(false, false, false),
      Array(true, false, true)
    )) should be (false)
  }

  "diagi(3,2)" should "be good" in {
    ExA.diagi(3, 2) should be (List(
      List((1,0), (2,1)),
      List((0,0), (1,1), (2,2)),
      List((0,1), (1,2))
    ))
  }

  "diagi(4,3)" should "be good" in {
    ExA.diagi(4, 3) should be (List(
      List((1,0), (2,1), (3,2)),
      List((0,0), (1,1), (2,2), (3,3)),
      List((0,1), (1,2), (2,3))
    ))
  }

  "diagx(2,2)" should "be good" in {
    ExA.diagx(2, 2) should be (List(
      List((0,0), (1,1)),
      List((0,1), (1,0))
    ))
  }

  "diagx(3,2)" should "be good" in {
    ExA.diagx(3, 2) should be (List(
      List((1,0), (2,1)),
      List((0,0), (1,1), (2,2)),
      List((1,2), (2,1)),
      List((0,2), (1,1), (2,0))
    ))
  }

  "diag()" should "be good" in {
    ExA.diag(
      Array(
        Array(1, 2),
        Array(3, 4)
      )
    ) should be (
      Array(
        Array(1, 4),
        Array(2, 3)
    ))

    // ExA.diag(Array(Array(1, 2, 3),
    //            Array(4, 5, 6),
    //            Array(7, 8, 9))) should be (Array(
    //              Array(1, 5, 9),
    //              //Array(3, 5, 7),
    //              Array(2, 6),
    //              //Array(2, 4),
    //              Array(4, 8)
    //              //Array(6, 8)
    //            ))
  }

  "A Stack" should "pop values in last-in-first-out order" in {
    val stack = new Stack[Int]
    stack.push(1)
    stack.push(2)
    stack.pop() should be (2)
    stack.pop() should be (1)
  }

  it should "throw NoSuchElementException if an empty stack is popped" in {
    val emptyStack = new Stack[Int]
    a [NoSuchElementException] should be thrownBy {
      emptyStack.pop()
    }
  }

  it should "rotate left right" in {
    ExA.leftright(Array("...", ".R.", ".B."
    ))._1 mkString(";") should be ("...;..R;..B")

    ExA.leftright(Array("...", ".R.", ".B."
    ))._2 mkString(";") should be ("...;R..;B..")

    ExA.leftright(Array("R..", "BR.", "BBR")
    )._2 mkString(";") should be ("R..;BR.;BBR")

    ExA.leftright(Array("R..", "BR.", "BBR")
    )._1 mkString(";") should be ("..R;.BR;BBR")
  }

  it should "should solve" in {
    ExA.solve(3, 2, Array("...", "RR.", "B..")) should be ("Red")
    ExA.solve(3, 2, Array("...", "RR.", "B..")) should be ("Red")
    ExA.solve(3, 2, Array("R..", "BR.", "B..")) should be ("Both")
    ExA.solve(3, 3, Array(".R.", "BR.", "BBR")) should be ("Red")
    ExA.solve(3, 2, Array("BRB", "BBR", "BBB")) should be ("Both")
    ExA.solve(3, 2, Array("BRB", "BBR", "BBB")) should be ("Both")
    ExA.solve(3, 2, Array("...", ".B.", ".R.")) should be ("Neither")
  }
}
