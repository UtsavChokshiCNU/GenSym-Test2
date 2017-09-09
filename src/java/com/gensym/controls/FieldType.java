package com.gensym.controls;

import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import java.beans.*;
import java.io.StringWriter;
import java.io.StringReader;
import java.io.IOException;
import java.io.EOFException;
import com.gensym.types.*;

/* FieldType should support a means of producing a specific default value
   for new instance.  This would require extensions to FieldTypeEditor that
   are not very interesting. */

/** FieldType is a class that is used by most G2-aware components in 
 * com.gensym.controls that mediates the translation of Strings
 * into other data types, particularly the data types that one
 * can find in the attributes/properties of JavaLink stubs for G2 items.
 * These types include:
 * <menu>
 *  <li> Text
 *  <li> Symbol
 *  <li> Integer
 *  <li> Float
 *  <li> Quantity
 *  <li> Sequence
 *  <li> Structure
 *  <li> BooleanTruthValue
 *  <li> Value
 * </menu>
 * Fuzzy truth values are not yet supported.
 *
 * @see com.gensym.types.G2Type
 * @see com.gensym.util.Structure
 * @see com.gensym.util.Sequence
 * @see com.gensym.util.Symbol
 */
public class FieldType extends Object implements java.io.Serializable
{
  /*
   * Allow deserialization
   */
  static final long serialVersionUID = 7313784269125224548L;

  private String typeName = "Text";
  private G2Type type = new TextType();
  
  /** No-argument constructur.  The default type is "Text".
   */
  public FieldType ()
  {
    Class editor = com.gensym.controls.FieldTypeEditor.class;
    PropertyEditorManager.registerEditor
      (com.gensym.controls.FieldType.class,editor);
  }

  /** Make a FieldType by name.  See above for list of possibilities.
   *  If the property name is not exact the type be the default.
   */
  public FieldType(String typeName)
  {
    this.typeName = typeName;
    if (typeName.equals("Text"))
      type = new TextType();
    else if (typeName.equals("Symbol"))
      type = new SymbolType();
    else if (typeName.equals("Integer"))
      type = new IntegerType();
    else if (typeName.equals("Float"))
      type = new FloatType();
    else if (typeName.equals("Quantity"))
      type = new QuantityType();
    else if (typeName.equals("BooleanTruthValue"))
      type = new BooleanTruthValueType();
    else if (typeName.equals("Sequence"))
      type = new SequenceType();
    else if (typeName.equals("Structure"))
      type = new StructureType();
    else if (typeName.equals("Value"))
      type = new ValueType();
  }

  /** Make a FieldType from an instance of G2Type specification.
   */
  public FieldType(G2Type type)
  {
    this.type = type;
    String className =  type.getClass().getName();
    typeName = className.substring(className.lastIndexOf('.')+1,
				   className.length() - 4);
  }
  
  private void readObject(java.io.ObjectInputStream s)
       throws java.lang.ClassNotFoundException,
	 java.io.IOException
  {
    s.defaultReadObject();
  }

  /** Get the type as its String name. */
  public String getTypeName ()
  { 
    return typeName; 
  }

  /** Get the type as a G2Type. */
  public G2Type getType ()
  {
    return type;
  }

  public boolean isNumeric()
  {
    return (type instanceof QuantityType);
  }

  public boolean isText()
  {
    return (type instanceof TextType);
  }

  /** This method creates a human readable string for an object
   *  of some G2Type.
   */
  public String objectToString(Object object)
       throws IOException
  {
    StringWriter writer = new StringWriter();
    ValueType.writeParseably(object,writer);
    writer.close();
    return writer.toString();
  }

  /** The method creates a human-readable string into an Object of
   * some G2Type.
   */
  public Object stringToObject(String string)
       throws G2TokenizerException, G2ParserException, EOFException, IOException
  {
    StringReader reader = new StringReader(string);
    Object value = ValueType.parseValue(reader);
    if (G2Token.hasMoreTokens(reader))
      throw new G2ParserException("Extraneous Input");
    else if (type.includes(value))
      return value;
    else
      throw new G2ParserException("Incompatible Type");
  }
  
  /** The newInstance method make a default value for the type
   *
   */
  public Object newInstance()
  {
    System.out.println("in fieldtype newInstance() typeName="+typeName);
    if (typeName.equals("String"))
      return "<default>";
    else if (typeName.equals("Integer") ||
	     typeName.equals("Quantity"))
      return 0;
    else if (typeName.equals("Float"))
      return 0.0;
    else if (typeName.equals("BooleanTruthValue"))
      return Boolean.FALSE;
    else if (typeName.equals("Symbol"))
      return Symbol.intern("G2");
    else if (typeName.equals("Sequence"))
      return new Sequence();
    else if (typeName.equals("Structure"))
      return new Structure();
    return null;
  }
}
