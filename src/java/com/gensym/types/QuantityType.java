package com.gensym.types;

import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;

public class QuantityType extends ValueType
{
 /*
  * Allow deserialization
  */
 static final long serialVersionUID = 5889072800362166884L;

  public QuantityType()
  {
    
  }

  @Override
  public boolean includes(Object o)
  {
    if (o instanceof Integer ||
	o instanceof Double)
      return true;
    else
      return false;
  }

  @Override
  public void pprint(java.io.PrintWriter out, int indent)
  {
    if (getClass() == QuantityType.class)
      out.print("Quantity");
    else
      out.print("No Specific ValueType Pprinter for "+this);
  }
}
