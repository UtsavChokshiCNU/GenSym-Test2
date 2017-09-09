package com.gensym.types;

import com.gensym.classes.Item;

public class ItemOrValueType extends SimpleType
{
  /*
   * Allow deserialization
   */
  static final long serialVersionUID = -1546804891302229227L;

  private static ValueType valueType = new ValueType();

  public ItemOrValueType()
  {

  }

  @Override
  public boolean includes(Object o)
  {
    if (o instanceof Item ||
	valueType.includes(o))
      return true;
    else
      return false;
  }

  @Override
  public void pprint(java.io.PrintWriter out, int indent)
  {
    out.print("ItemOrValue");
  }
}
