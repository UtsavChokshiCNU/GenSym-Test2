package com.gensym.types;

import com.gensym.util.Sequence;

public class SequenceType extends ValueType
{
  /*
   * Allow deserialization
   */
  static final long serialVersionUID = 2698647210698352460L;

  private G2Type elementType = null;
  private boolean hasMaximum = false;
  private boolean hasMinimum = false;
  private int minimum = 0;
  private int maximum = 1;

  public SequenceType()
  {}

  public SequenceType(G2Type elementType)
  {
    this.elementType = elementType;
  }

  public SequenceType(G2Type elementType, int minimum)
  {
    this.elementType = elementType;
    this.hasMinimum = true;
    this.minimum = minimum;
  }

  public SequenceType(G2Type elementType, int minimum, int maximum)
  {
    this.elementType = elementType;
    this.hasMinimum = true;
    this.minimum = minimum;
    this.hasMaximum = true;
    this.maximum = maximum;
  }

  public G2Type getElementType()
  {
    return elementType;
  }
  
  @Override
  public boolean includes(Object o)
  {

    if (o instanceof Sequence)
      {
	if (elementType == null)
	  return true;

	Sequence s = (Sequence)o;
	int i, size = s.size(); 
	
	if (hasMinimum && size < minimum)
	  return false;
	if (hasMaximum && size >= maximum)
	  return false;
	
	for (i=0 ; i<size ; i++)
	  if (!elementType.includes(s.elementAt(i)))
	    return false;

	return true;
      }
    else
      return false;
  }

  @Override
  public void pprint(java.io.PrintWriter out, int indent)
  {
    if (elementType == null)
      out.print("(Sequence)");
    else
      {
	out.print("(Sequence ");
	if (elementType instanceof StructureType ||
	    elementType instanceof SequenceType  ||
	    elementType instanceof CompoundType ||
	    elementType instanceof MemberType)
	  {
	    int newIndent = indent + G2Type.pprintIndentIncrement;
	    G2Type.pprintIndent(out,newIndent);
	    elementType.pprint(out,newIndent);
	    if (hasMinimum)
	      {
		G2Type.pprintIndent(out,newIndent);
		out.print(minimum);
	      }
	    if (hasMaximum)
	      {
		G2Type.pprintIndent(out,newIndent);
		out.print(maximum);
	      }
	    out.print(")");
	  }
	else
	  {
	    elementType.pprint(out,indent+10);
	    if (hasMinimum)
	      out.print(" "+minimum);
	    if (hasMaximum)
	      out.print(" "+maximum);
	  }
	out.print(")");
      }
  }
}
