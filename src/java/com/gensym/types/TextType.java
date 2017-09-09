package com.gensym.types;

public class TextType extends ValueType
{
  /*
   * Allow deserialization
   */
  static final long serialVersionUID = 7887497959111132333L;

  public TextType ()
  {}

  @Override
  public boolean includes(Object o)
  {
    if (o instanceof String)
      return true;
    else
      return false;
  }

  @Override
  public void pprint(java.io.PrintWriter out, int indent)
  {
    out.print("Text");
  }
}
