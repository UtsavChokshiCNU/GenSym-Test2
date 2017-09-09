package com.gensym.types;

import com.gensym.classes.Item;

import com.gensym.util.Symbol;

public class ClassType extends ItemOrValueType
{
  /*
   * Allow deserialization
   */
  static final long serialVersionUID = 331250019423487124L;

  private Symbol className;

  public ClassType(Symbol className)
  {
    this.className = className;
  }

  @Override
  public boolean includes(Object o)
  {
      // Not Yet Implemented.
      return false;
  }

  @Override
  public void pprint (java.io.PrintWriter out, int indent)
  {
    out.print("(Class "+className+")");
  }
}
