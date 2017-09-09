package com.gensym.types;

import com.gensym.util.Symbol;

public class SymbolType extends ValueType
{
  /*
   * Allow deserialization
   */
  static final long serialVersionUID = -6975632304939031779L;

  public SymbolType ()
  {}

  @Override
  public boolean includes(Object o)
  {
    if (o instanceof Symbol)
      return true;
    else
      return false;
  }

  @Override
  public void pprint(java.io.PrintWriter out, int indent)
  {
    out.print("Symbol");
  }
}
