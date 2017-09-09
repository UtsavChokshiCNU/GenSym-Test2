package com.gensym.types;

public class UnionType extends CompoundType
{
  /*
   * Allow deserialization
   */
  static final long serialVersionUID = -5180684842645201478L;

  private G2Type[] disjuncts;
  
  public UnionType(G2Type[] disjuncts)
  {
    this.disjuncts = disjuncts;
  }

  public G2Type[] getDisjuncts()
  {
    return disjuncts;
  }

  @Override
  public boolean includes(Object o)
  {
    for (int i = 0; i<disjuncts.length ; i++)
      if ((disjuncts[i]).includes(o))
	return true;
    return false;
  }

  @Override
  public void pprint(java.io.PrintWriter out, int indent)
  {
    out.print("(OR ");
    int newIndent = indent + 4;
    for (int i = 0; i<disjuncts.length ; i++)
      {
	if (i > 0)
	  G2Type.pprintIndent(out,newIndent);
	disjuncts[i].pprint(out,newIndent);
      }
    out.print(")");
  }

  @Override
  public String toString()
  {
    StringBuffer buffer = new StringBuffer("<G2 Union Type of ");
    for (int i = 0; i<disjuncts.length ; i++)
      if (i==0)
	buffer.append(disjuncts[i].toString());
      else
	buffer.append("or "+disjuncts[i]);
    buffer.append(">");
    return buffer.toString();
  }
}

