package com.gensym.demos.jlp;

import java.lang.Math;

public class OutboardEngine {

  public OutboardEngine()
  {
  }

  public int increment(int i , int f)
  {   return i + f;
  }

  public double primaryCalculation(double v1)
  { double v2 = 20;
     System.out.println("outboard engine primary calculation of "+v1 + " + " + v2);
      return v1 + v2;
  }

}
