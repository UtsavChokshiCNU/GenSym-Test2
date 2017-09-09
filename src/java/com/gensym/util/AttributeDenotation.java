
package com.gensym.util;

/**
 *  A class representing denotations referencing attributes of items.
 *  In o
 */
public class AttributeDenotation extends Sequence 
                                 implements Denotation, 
                                            com.gensym.util.symbol.G2TypeSymbols
{
  static final long serialVersionUID = 4371325311900549307L;
  private static final Structure typeRef;
  public static final AttributeDenotation WILDCARD_DENOTATION;

  static {
    typeRef = new Structure ();
    typeRef.setAttributeValue (TYPE_, ATTRIBUTE_);
    WILDCARD_DENOTATION = new AttributeDenotation (Symbol.intern ("*"));
  }

  public AttributeDenotation () {
    super (1);
    elementCount = 1;
    elementData[0] = typeRef.clone ();
  }

  public AttributeDenotation (Symbol attrName) {
    this ();
    ((Structure)elementData[0]).setAttributeValue (NAME_, attrName);
  }

  /**
   * @undocumented
   */
  public AttributeDenotation (Symbol attrName, Symbol classQualifier) {
    this(attrName);
    if (classQualifier != null)
      ((Structure)elementData[0]).setAttributeValue (CLASS_QUALIFIER_,
						     classQualifier);
  }

  public Symbol getAttributeName () {
    Symbol attrName = (Symbol)((Structure)elementData[0]).getAttributeValue (NAME_, null);
    return attrName;
  }

  public void setAttributeName (Symbol attrName) {
    ((Structure)elementData[0]).setAttributeValue (NAME_, attrName);
  }

  public static boolean isAttributeDenotation (Sequence seq) {
    if (seq.size () != 1)
      return false;
    Object x = seq.elementAt (0);
    if (!(x instanceof Structure))
      return false;
    Structure structInDentn = (Structure) x;
    if (!(ATTRIBUTE_.equals (structInDentn.getAttributeValue (TYPE_, null))))
      return false;
    x = structInDentn.getAttributeValue (NAME_, null);
    return (x != null && x instanceof Symbol);
  }

  public static Symbol getAttributeName (Sequence denotation) {
    if (denotation.size () == 0)
      throw new RuntimeException ("Sequence is not a legal denotation - " + denotation);
    Structure attrDesignation = (Structure)denotation.elementAt (0);
    Symbol attrName = (Symbol)attrDesignation.getAttributeValue (NAME_, null);
    return attrName;
  }

  public static final Symbol CLASS_QUALIFIER_ = Symbol.intern ("CLASS-QUALIFIER");

  /**
   * @undocumented
   */
  public void setClassQualifier(Symbol className) {
    ((Structure)elementData[0]).setAttributeValue (CLASS_QUALIFIER_, className);
  }

  /**
   * Separator for class-qualified attributes
   * @undocumented
   */
  public static final String CLASS_QUALIFICATION_SEPARATOR = "::";

  /**
   * Tool to deal with the separator for class-qualified attributes
   * @undocumented
   */
  public static Symbol getSimpleAttributeName(Symbol attributeName) {
    String symbolName = attributeName.toString();
    int index = symbolName.indexOf(CLASS_QUALIFICATION_SEPARATOR);
    
    if (index != -1)
      return Symbol.intern(symbolName.substring(index+2));
    else 
      return attributeName;
  }
    
  /**
   * Tool to deal with the separator for class-qualified attributes
   * @undocumented
   */
  public static Symbol getAttributeClassQualifier(Symbol attributeName) {
    String symbolName = attributeName.toString();
    int index = symbolName.indexOf(CLASS_QUALIFICATION_SEPARATOR);
    
    if (index != -1)
      return Symbol.intern(symbolName.substring(0, index));
    else
      return null;
  }

  /**
   * Tool to deal with the separator for class-qualified attributes
   * @undocumented
   */
  public static Symbol makeClassQualifiedAttributeName(Symbol className,
						       Symbol attributeName) {
    return Symbol.intern(className + CLASS_QUALIFICATION_SEPARATOR +
			 attributeName);
  }

  /**
   * Not currently used.
   * currently dextructive to match denormalizeDenotation
   * @undocumented
   */
  public static void normalizeDenotation(Denotation denotationIn) {
    if (!(denotationIn instanceof AttributeDenotation))
      return; // denotationIn;

    AttributeDenotation denotation = (AttributeDenotation) denotationIn;
    Structure struct = (Structure)denotation.elementAt(0);

    Symbol attrName = (Symbol)struct.getAttributeValue(NAME_, null);
    Symbol classQualifier =
      attrName == null ? null : getAttributeClassQualifier(attrName);
    if (classQualifier != null) {
      // currently destructive to match denormalizeDenotation
      //denotation = (AttributeDenotation)denotation.clone();
      struct = (Structure)denotation.elementAt(0);
      struct.setAttributeValue(NAME_, getSimpleAttributeName(attrName));
      struct.setAttributeValue(CLASS_QUALIFIER_, classQualifier);
    }

    //return denotation;
  }

  private static final Symbol VIRTUAL_ATTRIBUTE_ = Symbol.intern ("VIRTUAL-ATTRIBUTE");

  /**
   * Change the attribute name to include the class qualifier if appropriate.
   * Destructive.
   * In the future, this should maybe check if denotation is actually
   * a valide denotation.
   * @undocumented
   */
  public static void denormalizeDenotation(Sequence denotation) {
    Object obj = denotation.elementAt(0);
    if (!(obj instanceof Structure))
      return;

    Structure struct = (Structure)obj;

    Symbol classQualifier =
      (Symbol)struct.getAttributeValue(CLASS_QUALIFIER_, null);
    if  (classQualifier != null) {
      Symbol newAttr =
	makeClassQualifiedAttributeName(classQualifier,
					(Symbol)struct.getAttributeValue(NAME_, null));
      struct.setAttributeValue(NAME_, newAttr);
    }

    
  }
				 
}
