package com.gensym.types;

public class TruthValueType extends ValueType
{
  /*
   * Allow deserialization
   */
  static final long serialVersionUID = 192900322352011465L;

  public TruthValueType ()
  {}

  @Override
  public boolean includes(Object o)
  {
    if (o instanceof Boolean)
      return true;
    else
      return false;
  }

  @Override
  public void pprint(java.io.PrintWriter out , int indent)
  {
    out.print("TruthValue");
  }
}
