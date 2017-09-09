package com.gensym.types;

public class IntersectionType extends CompoundType
{
 /*
   * Allow deserialization
   */
 static final long serialVersionUID = -7634428766215558989L;

  private G2Type[] conjuncts;
  
  public IntersectionType(G2Type[] conjuncts)
  {
    this.conjuncts = conjuncts;
  }

  @Override
  public boolean includes(Object o)
  {
    for (int i = 0; i<conjuncts.length ; i++)
      if (! (conjuncts[i]).includes(o))
	return false;
    return true;
  }

  @Override
  public void pprint(java.io.PrintWriter out, int indent)
  {
    out.print("(AND ");
    int newIndent = indent + 5;
    for (int i = 0; i<conjuncts.length ; i++)
      {
	if (i > 0)
	  G2Type.pprintIndent(out,newIndent);
	conjuncts[i].pprint(out,newIndent);
      }
    out.print(")");
  }
}
