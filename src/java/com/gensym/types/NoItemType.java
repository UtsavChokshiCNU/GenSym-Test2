package com.gensym.types;

public class NoItemType extends SimpleType
{
 /*
  * Allow deserialization
  */
 static final long serialVersionUID = -7820068576135029533L;

  public NoItemType()
  {

  }

  @Override
  public boolean includes(Object o)
  {
    if (o == null)
      return true;
    else
      return false;
  }

  @Override
  public void pprint(java.io.PrintWriter out, int indent)
  {
    out.print("NoItem");
  }
}
