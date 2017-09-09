package com.gensym.types;

public class BooleanTruthValueType extends TruthValueType
{

  /*
   * Allow deserialization
   */
  static final long serialVersionUID = -510879560946404587L;

  public BooleanTruthValueType ()
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
    out.print("BooleanTruthValue");
  }
}
