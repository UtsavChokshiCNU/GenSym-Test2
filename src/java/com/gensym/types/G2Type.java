package com.gensym.types;

import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;

import java.io.EOFException;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.Writer;
import java.io.Reader;

import java.util.Enumeration;

/** 
 * G2Type is the root class for a set of java classes that can 
 * describe any G2 Type Specification. 
 */

public abstract class G2Type implements java.io.Serializable
{

  static final long serialVersionUID = -5829675715641199030L;

  private static final Symbol typeOrOperator_ 
    = Symbol.intern("TYPE-OR-OPERATOR");
  private static final Symbol operands_ = Symbol.intern("OPERANDS");
  private static final Symbol structure_ = Symbol.intern("STRUCTURE");
  private static final Symbol slots_ = Symbol.intern("SLOTS");
  private static final Symbol requiredSlots_ 
    = Symbol.intern("REQUIRED-SLOTS");
  private static final Symbol type_ 
    = Symbol.intern("TYPE");
  private static final Symbol attributeName_ 
    = Symbol.intern("ATTRIBUTE-NAME");
  private static final Symbol sequence_ = Symbol.intern("SEQUENCE");
  private static final Symbol elementType_ 
    = Symbol.intern("ELEMENT-TYPE");
  private static final Symbol minimumElements_ 
    = Symbol.intern("MINIMUM-ELEMENTS");
  private static final Symbol maximumElements_ 
    = Symbol.intern("MAXIMUM-ELEMENTS");

  private static final Symbol member_ = Symbol.intern("MEMBER");
  private static final Symbol possibleValues_ 
    = Symbol.intern("POSSIBLE-VALUES");

  private static final Symbol class_ = Symbol.intern("CLASS");
  private static final Symbol className_ 
    = Symbol.intern("CLASS-NAME");


  private static final Symbol and_ = Symbol.intern("AND");
  private static final Symbol or_ = Symbol.intern("OR");
  private static final Symbol not_ = Symbol.intern("NOT");

  private static final Symbol none_ = Symbol.intern("NONE");
  private static final Symbol value_ = Symbol.intern("VALUE");
  private static final Symbol itemOrValue_ = Symbol.intern("ITEM-OR-VALUE");

  private static final Symbol float_ = Symbol.intern("FLOAT");
  private static final Symbol integer_ = Symbol.intern("INTEGER");
  private static final Symbol long_ = Symbol.intern("LONG");
  private static final Symbol QUANTITY_ = Symbol.intern ("QUANTITY");
  private static final Symbol symbol_ = Symbol.intern("SYMBOL");
  private static final Symbol text_ = Symbol.intern("TEXT");
  private static final Symbol truthValue_ = Symbol.intern("TRUTH-VALUE");
  private static final Symbol noItem_ = Symbol.intern("NO-ITEM");

  static int pprintWidth = 100;
  static int pprintIndentIncrement = 2;

  
  /** 
   * This method makes a nested G2Type from a com.gensym.util.Structure
   * that describes the attribute as received from the method getAttributeDescriptions
   * from com.gensym.jgi.G2Access
   */
  public static G2Type makeG2TypeFromDescription(Structure description)
  {
    int i, size;
    Sequence operands = 
      (Sequence) description.getAttributeValue(operands_,null);
    Object operator
      = description.getAttributeValue(typeOrOperator_,null);
    if (operator.equals(sequence_))
      {
	Object elementDescription
	  = description.getAttributeValue(elementType_,null);
	Integer minimumElements
	  = (Integer) description.getAttributeValue(minimumElements_,null);
        Integer maximumElements
	  = (Integer) description.getAttributeValue(maximumElements_,null);
	if (elementDescription != null)
	  {
	    G2Type elementType 
	      = makeG2TypeFromDescription((Structure)elementDescription);
	    if (minimumElements != null &&
		maximumElements != null)
	      return new SequenceType(elementType,
				      minimumElements.intValue(),
				      maximumElements.intValue());
	    else if (minimumElements != null)
	      return new SequenceType(elementType,
				      minimumElements.intValue());
	    else
	      return new SequenceType(elementType);
	  }
	else
	  return new SequenceType();
      }
    else if (operator.equals(structure_))
      {
	Object slotsSpec = description.getAttributeValue(slots_,null);
	if (slotsSpec != null)
	  {
	    Sequence slots = (Sequence) slotsSpec;
	    size = slots.size();
	    Symbol[] slotNames = new Symbol[size];
	    G2Type[] slotTypes = new G2Type[size];
	    for (i = 0; i<size ; i++)
	      {
		Structure pair = (Structure) slots.elementAt(i);
		Structure typeDescription
		  = (Structure) pair.getAttributeValue(type_,null);
		Symbol name 
		  = (Symbol) pair.getAttributeValue(attributeName_,null);
		
		slotNames[i] = name;
		slotTypes[i] = makeG2TypeFromDescription(typeDescription);
	      }
	    return new StructureType(slotNames,slotTypes,null);
	  }
	else
	  return new StructureType();
      }
    else if (operator.equals(integer_))
      {
	return new IntegerType();
      }
    else if (operator.equals(long_))
      {
	return new LongType();
      }
    else if (operator.equals(float_))
      {
	return new FloatType();
      }
    else if (operator.equals(symbol_))
      {
	return new SymbolType();
      }
    else if (operator.equals(text_))
      {
	return new TextType();
      }
    else if (operator.equals(truthValue_))
      {
	return new BooleanTruthValueType();
      }
    else if (operator.equals(value_))
      {
	return new ValueType();
      }
    else if (operator.equals(QUANTITY_))
      {
	return new QuantityType();
      }
    else if (operator.equals(itemOrValue_))
      {
	return new ItemOrValueType();
      }
    else if (operator.equals(none_))
      {
	return new NoItemType();
      }
    else if (operator.equals(and_) ||
	     operator.equals(or_))
      {
	size = operands.size();
	G2Type[] elements = new G2Type[size];
	for (i = 0; i< size ; i++)
	  {
	    Object operand = operands.elementAt(i);
	    if (operand instanceof Structure)
	      elements[i] 
		= makeG2TypeFromDescription((Structure)operand);
	    else
	      throw new RuntimeException("(con/dis)-juncts must be types");
	  }
	if (operator.equals(and_))
	  return new IntersectionType(elements);
	else 
	  return new UnionType(elements);
      }
    else if (operator.equals(member_))
      {
	Sequence values 
	  = (Sequence) description.getAttributeValue(possibleValues_,null);
	
	if (values != null)
	  {
	    size = values.size();
	    Object[] members = new Object[size];
	    values.copyInto(members);
	    return new MemberType(members);
	  }
	else
	  return new MemberType(new Object[0]);
      }
    else if (operator.equals(class_))
      return new ClassType((Symbol)
			   description.getAttributeValue(className_,null));
    else
      throw new RuntimeException("unknown operator"+operator);
  }


  /**
   *  pprint invokes the pretty printer for G2Types.  It's output is akin to
   *  LISP pretty-printers.
   */
  public void pprint(PrintWriter out, int indent)
  {
    out.print("NO SPECIFIC PPRINT FOR "+this);
  }

  protected static void pprintIndent(PrintWriter out, int n)
  {
    out.println("");
    for (int i = 0; i<n ; i++){
    	out.print(" ");
    }
  }

  /**
   * This method tests to see whether a given object is a member of 
   * a G2 type.
   */
  public boolean includes(Object o)
  {
    return false;
  }

  /** 
   * This method sets width and indentation parameters of the G2Type 
   * pretty printer.  The pretty printer attempts to use no more than 
   * width columns and indents the number of columns specified after 
   * inserting newlines.
   */
  public static void setPprintParameters(int width, int indentIncrement)
  {
    pprintWidth  = width;
    pprintIndentIncrement = indentIncrement;
  }

  public Object parse(Reader reader)
       throws IOException, EOFException
  {
    throw new RuntimeException("No parser for this type");
  }


}
