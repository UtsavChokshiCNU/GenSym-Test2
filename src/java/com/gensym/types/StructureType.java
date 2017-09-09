package com.gensym.types;

import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.util.Cons;

import java.util.Enumeration;

public class StructureType extends ValueType
{
  /*
   * Allow deserialization
   */
  static final long serialVersionUID = 6187434306235703142L;

  private Symbol[] attributeNames = null;
  private G2Type[] attributeTypes = null;
  private Cons requiredAttributesSpec;

  private static final Symbol and_ = Symbol.intern("AND");
  private static final Symbol or_ = Symbol.intern("OR");
  private static final Symbol not_ = Symbol.intern("NOT");

  public StructureType()
  {}

  public StructureType(Symbol[] names, G2Type[] types, 
		       Cons requiredAttributesSpec)
  {
    if ((names != null && types == null) ||
	(names == null && types != null))
      throw new RuntimeException("names and types must be specified");
    else if (names != null && (names.length != types.length))
      throw new RuntimeException("names and types must be of same length");

    this.attributeNames = names;
    this.attributeTypes = types;
    this.requiredAttributesSpec = requiredAttributesSpec;
  }

  @Override
  public boolean includes(Object o)
  {

    if (o instanceof Structure)
      {
	if (attributeNames == null)
	  return true;
	

	Structure s = (Structure)o;
	Enumeration nameEnumeration = s.getAttributeNames();
	Enumeration valueEnumeration = s.getAttributeValues();
	
	while (nameEnumeration.hasMoreElements())
	  { 
	    Object value = valueEnumeration.nextElement();
	    Object name = nameEnumeration.nextElement();
	    
	    G2Type type = getTypeByName((Symbol)name);
	    if (type == null ||
		!type.includes(value))
	      return false;
	  }
	if (requiredAttributesSpec == null)
	  return true;
	else
	  return evaluateRequiredAttributes(requiredAttributesSpec,s);
      }
    else
      return false;
  }

  private boolean evaluateRequiredAttributes(Object spec, Structure s)
  {
    if (spec instanceof Cons)
      {
	Symbol operator = (Symbol) ((Cons)spec).car;
	Cons operands = (Cons) ((Cons)spec).cdr;

	if (operator.equals(and_))
	  {
	    while (operands != null)
	      if (evaluateRequiredAttributes(operands.car,s))
		operands = (Cons)operands.cdr;
	      else
		return false;
	    return true;
	  }
	else if (operator.equals(or_))
	  {
	    while (operands != null)
	      if (evaluateRequiredAttributes(operands.car,s))
		return true;
	      else
		operands = (Cons)operands.cdr;
	    return false;
	  }
	else if (operator.equals(not_))
	  return !(evaluateRequiredAttributes(operands.car,s));
	else 
	  throw new RuntimeException("bad requiredAttributeSpec");
      }
    else if (spec instanceof Symbol)
      {
	Symbol attributeName = (Symbol)spec;
	
	if (s.getAttributeValue(attributeName,null) != null)
	  return true;
	else
	  return false;
      }
    else
      throw new RuntimeException("bad requiredAttributeSpec");
  }

  private G2Type getTypeByName(Symbol name)
  {
    for (int i = 0; i<attributeNames.length; i++)
      if (attributeNames[i].equals(name))
	return attributeTypes[i];
    return null;
  }

  @Override
  public void pprint(java.io.PrintWriter out, int indent)
  {
    out.print("(Structure");
    if (attributeNames != null)
      {
	out.print(" ");
	int newIndent = indent + G2Type.pprintIndentIncrement;
	for (int i = 0; i<attributeNames.length ; i++)
	  {
	    Symbol name = attributeNames[i];
	    String symbolName = name.toString();
	    int nameLength = symbolName.length();
	    G2Type type = attributeTypes[i];
	    
	    if (type instanceof StructureType ||
		type instanceof SequenceType  ||
		type instanceof CompoundType ||
		type instanceof MemberType)
	      {
		G2Type.pprintIndent(out,newIndent);
		out.print(name);
		G2Type.pprintIndent(out,newIndent+G2Type.pprintIndentIncrement);
		type.pprint(out,newIndent+G2Type.pprintIndentIncrement);
	      }
	    else
	      {
		G2Type.pprintIndent(out,newIndent);
		out.print(name+" ");
		type.pprint(out,newIndent+nameLength+1);
	      }
	  }
      }
    out.print(")");
  }
}
