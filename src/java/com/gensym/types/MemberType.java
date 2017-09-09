package com.gensym.types;

public class MemberType extends ValueType
{
  /*
   * Allow deserialization
   */
  static final long serialVersionUID = 69689157885028904L;

  private Object[] members;
  
  public MemberType (Object[] members)
  {
    this.members = members;
  }

  @Override
  public boolean includes(Object o)
  {
    for (int i = 0; i< members.length ; i++)
      if (members[i].equals(o))
	return true;

    return false;
  }

  public Object[] getMembers()
  {
    return members;
  }

  @Override
  public void pprint(java.io.PrintWriter out, int indent)
  {
    out.print("(MEMBER ");
    int newIndent = indent + 8;
    int room = G2Type.pprintWidth - newIndent;
    for (int i = 0; i<members.length ; i++)
      {
	
	String memberText = members[i].toString();
	int length = memberText.length();
	if (room > length)
	  {
	    room -= (length + 1);
	    out.print(memberText+
		      ((i+1 == members.length) ? "" : " "));
	  }
	else
	  {
	    G2Type.pprintIndent(out,newIndent);
	    out.print(memberText+
		      ((i+1 == members.length) ? "" : " "));
	    room = G2Type.pprintWidth - (newIndent + length);
	  }
      }
    out.print(")");
  }

  @Override
  public String toString()
  {
    StringBuffer buffer = new StringBuffer("<G2 Member Type, with ");
    for (int i = 0; i<members.length ; i++)
      if (i==0)
	buffer.append(members[i].toString());
      else
	buffer.append(", "+members[i]);
    buffer.append(">");
    return buffer.toString();
  }

}
