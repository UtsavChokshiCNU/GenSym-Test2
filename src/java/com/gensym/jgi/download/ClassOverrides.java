
package com.gensym.jgi.download;

import java.lang.reflect.*;
import java.util.*;

import com.gensym.util.*;
import com.gensym.message.Trace;

class ClassOverrides implements Cloneable, com.gensym.util.symbol.OverrideSymbols {
  Structure overrides;
  private Structure classInfo;
  private Sequence properties, methods, events, fields, imports;

  ClassOverrides (Structure overrides) throws MalformedOverridesException {
    this.overrides = overrides;
    classInfo  = (Structure) overrides.getAttributeValue (CLASS_INFO_, null);
    properties = (Sequence) overrides.getAttributeValue (PROPERTIES_, null);
    methods    = (Sequence) overrides.getAttributeValue (METHODS_, null);
    events     = (Sequence) overrides.getAttributeValue (EVENTS_, null);
    fields     = (Sequence) overrides.getAttributeValue (FIELDS_, null);
    imports    = (Sequence) overrides.getAttributeValue (IMPORTS_, null);
  }


  ClassOverrides () {

    //classInfo  =  new Structure ();
    properties =  new Sequence ();
    methods    =  new Sequence ();
    events     =  new Sequence ();
    fields     =  new Sequence ();
    imports    =  new Sequence ();
    
    Structure s = new Structure ();
    s.setAttributeValue (CLASS_INFO_, classInfo);
    s.setAttributeValue (PROPERTIES_,  properties);
    s.setAttributeValue (METHODS_, methods);
    s.setAttributeValue (EVENTS_,  events);
    s.setAttributeValue (FIELDS_,  fields);
    s.setAttributeValue (IMPORTS_, imports);

    this.overrides = s;
  }

  Sequence getImplementedInterfaces () {
    if (classInfo == null)
      return new Sequence ();
    else
      return (Sequence)classInfo.getAttributeValue (INTERFACES_, null);
  }


  String getGetterComments (Symbol propName) {
    return getAttributeFromStructureWithMatchingSlotInSequence (GETTER_COMMENTS_,
								PROPERTY_NAME_,
								propName,
								properties);
  }

  String getGetterInterface (Symbol propName) {
    return getAttributeFromStructureWithMatchingSlotInSequence (GETTER_INTERFACE_,
								PROPERTY_NAME_,
								propName,
								properties);
  }

  String getGetterImplementation (Symbol propName) {
    return getAttributeFromStructureWithMatchingSlotInSequence (GETTER_IMPLEMENTATION_,
								PROPERTY_NAME_,
								propName,
								properties);
  }

  String getSetterComments (Symbol propName) {
    return getAttributeFromStructureWithMatchingSlotInSequence (SETTER_COMMENTS_,
								PROPERTY_NAME_,
								propName,
								properties);
  }

  String getSetterInterface (Symbol propName) {
    return getAttributeFromStructureWithMatchingSlotInSequence (SETTER_INTERFACE_,
								PROPERTY_NAME_,
								propName,
								properties);
  }

  String getSetterImplementation (Symbol propName) {
    return getAttributeFromStructureWithMatchingSlotInSequence (SETTER_IMPLEMENTATION_,
								PROPERTY_NAME_,
								propName,
								properties);
  }

  String getMethodComments (Symbol methodName) {
    return getAttributeFromStructureWithMatchingSlotInSequence (COMMENTS_,
								METHOD_NAME_,
								methodName,
								methods);
  }

  String getMethodInterface (Symbol methodName) {
    return getAttributeFromStructureWithMatchingSlotInSequence (INTERFACE_,
								METHOD_NAME_,
								methodName,
								methods);
  }

  String getMethodImplementation (Symbol methodName) {
    return getAttributeFromStructureWithMatchingSlotInSequence (IMPLEMENTATION_,
								METHOD_NAME_,
								methodName,
								methods);
  }

  String getAddListenerComments (Symbol eventName) {
    return getAttributeFromStructureWithMatchingSlotInSequence (ADD_LISTENER_COMMENTS_,
								EVENT_NAME_,
								eventName,
								events);
  }

  String getAddListenerInterface (Symbol eventName) {
    return getAttributeFromStructureWithMatchingSlotInSequence (ADD_LISTENER_INTERFACE_,
								EVENT_NAME_,
								eventName,
								events);
  }

  String getAddListenerImplementation (Symbol eventName) {
    return getAttributeFromStructureWithMatchingSlotInSequence (ADD_LISTENER_IMPLEMENTATION_,
								EVENT_NAME_,
								eventName,
								events);
  }


  String getRemoveListenerComments (Symbol eventName) {
    return getAttributeFromStructureWithMatchingSlotInSequence (REMOVE_LISTENER_COMMENTS_,
								EVENT_NAME_,
								eventName,
								events);
  }
  String getRemoveListenerInterface (Symbol eventName) {
    return getAttributeFromStructureWithMatchingSlotInSequence (REMOVE_LISTENER_INTERFACE_,
								EVENT_NAME_,
								eventName,
								events);
  }

  String getRemoveListenerImplementation (Symbol eventName) {
    return getAttributeFromStructureWithMatchingSlotInSequence (REMOVE_LISTENER_IMPLEMENTATION_,
								EVENT_NAME_,
								eventName,
								events);
  }

  String getFieldComments (Symbol fieldName) {
    return getAttributeFromStructureWithMatchingSlotInSequence (COMMENTS_,
								FIELD_NAME_,
								fieldName,
								fields);
  }

  String getFieldDeclaration (Symbol fieldName) {
    return getAttributeFromStructureWithMatchingSlotInSequence (DECLARATION_,
								FIELD_NAME_,
								fieldName,
								fields);
  }

  String getFieldInitialValue (Symbol fieldName) {
    return getAttributeFromStructureWithMatchingSlotInSequence (INITIAL_VALUE_,
								FIELD_NAME_,
								fieldName,
								fields);
  }

  String getImportTypeOrPackage (Symbol importName) {
    return getAttributeFromStructureWithMatchingSlotInSequence (TYPE_OR_PACKAGE_,
								IMPORT_NAME_,
								importName,
								imports);
  }

  private String getAttributeFromStructureWithMatchingSlotInSequence (Symbol attrName,
								      Symbol slotName,
								      Symbol slotValue,
								      Sequence seq) {
    Structure matchingStructure = getMatchingStructure (seq, slotName, slotValue);
    if (matchingStructure == null)
      return null;
    else
      return (String) matchingStructure.getAttributeValue (attrName, null);
  }
  
  private Structure getMatchingStructure (Sequence seq, Symbol slotName, Symbol slotValue) {
    Enumeration e = seq.elements ();
    while (e.hasMoreElements ()) {
      Structure s = (Structure) e.nextElement ();
      Symbol ssv  = (Symbol) s.getAttributeValue (slotName, null);
      if (slotValue.equals (ssv))
	return s;
    }
    return null;
  }

  void cacheMethods (Class clazz) {
    
  }

  Method getGetter (Symbol propName) {
    return null;
  }

  Method getSetter (Symbol propName) {
    return null;
  }

  Method getMethod (String methodName, Class[] params) {
    return null;
  }

  private String getMethodNameFromSignature (String signature) {
    StringTokenizer tknzr = new StringTokenizer (signature);
    while (tknzr.hasMoreTokens ()) {
      String token = tknzr.nextToken ();
      if (!isModifier (token)) {
	if (tknzr.hasMoreTokens ())
	  return tknzr.nextToken ();
	else
	  break;
      } else if (token.equals ("("))
	break;
    }
    throw new RuntimeException ("Could not parse method name from signature : " + signature);
  }

  private boolean isModifier (String possibleModifier) {
    for (int i=0; i<modifiers.length; i++)
      if (modifiers[i].equals (possibleModifier))
	return true;
    return false;
  }

  private int getModifierIndex (final int modKey) {
      int modifierKey = modKey;
	  if (modifierKey == 0){
		  throw new RuntimeException ("Invalid modifier " + modifierKey);
	  }
	  int modIndex = 0;
	  while (modifierKey != 1) {
		  modifierKey /= 2;
		  modIndex++;  
	  }
	  return modIndex;
  }

  public static void main (String[] args) throws MalformedOverridesException {
    int x;
    ClassOverrides c = new ClassOverrides (new Structure ());
    x = c.getModifierIndex (Modifier.PUBLIC);
    x = c.getModifierIndex (Modifier.PRIVATE);
    x = c.getModifierIndex (Modifier.PROTECTED);
    x = c.getModifierIndex (Modifier.ABSTRACT);
    x = c.getModifierIndex (Modifier.STATIC);
    x = c.getModifierIndex (Modifier.FINAL);
    x = c.getModifierIndex (Modifier.TRANSIENT);
    x = c.getModifierIndex (Modifier.VOLATILE);
    x = c.getModifierIndex (Modifier.NATIVE);
    x = c.getModifierIndex (Modifier.SYNCHRONIZED);
    x = c.getModifierIndex (Modifier.INTERFACE);
  }

  Enumeration getProperties () {
    return new OverrideEnumerator (properties, PROPERTY_NAME_);
  }

  Enumeration getMethods () {
    return getMethods (0);
  }

  Enumeration getMethods (int modifier) {
    return new OverrideMethodsEnumerator (methods, METHOD_NAME_, modifier);
  }

  Enumeration getEvents () {
    return new OverrideEnumerator (events, EVENT_NAME_);
  }

  Enumeration getFields () {
    return new OverrideEnumerator (fields, FIELD_NAME_);
  }

  Enumeration getImports () {
    return new OverrideEnumerator (imports, IMPORT_NAME_);
  }

  int getImportsCount () {
    return imports.size ();
  }
  

  boolean propertyExists (Symbol propName) {
    Structure s = getMatchingStructure (properties, PROPERTY_NAME_, propName);
    return (s == null ? false : true);
  }

  boolean methodExists (Symbol methodName) {
    Structure s = getMatchingStructure (methods, METHOD_NAME_, methodName);
    return (s == null ? false : true);
  }

  boolean eventExists (Symbol eventName) {
    Structure s = getMatchingStructure (events, EVENT_NAME_, eventName);
    return (s == null ? false : true);
  }

  boolean importExists (Symbol importName) {
    Structure s = getMatchingStructure (imports, IMPORT_NAME_, importName);
    return (s == null ? false : true);
  }

  class OverrideEnumerator implements Enumeration {
    Enumeration seqEnum;
    Symbol attrName;

    OverrideEnumerator (Sequence s, Symbol attrName) {
      seqEnum = s.elements ();
      this.attrName = attrName;
    }

    @Override
    public boolean hasMoreElements () {
      return seqEnum.hasMoreElements ();
    }

    @Override
    public Object nextElement () {
      Structure s = (Structure) seqEnum.nextElement ();
      return s.getAttributeValue (attrName, null);
    }
  }

  class OverrideMethodsEnumerator extends OverrideEnumerator {
    String modifierToken;
    Symbol nextElement;

    OverrideMethodsEnumerator (Sequence s, Symbol attrName, int modifier) {
      super (s, attrName);
      if (modifier != 0) {
	int modIndex = getModifierIndex (modifier);
	modifierToken = modifiers[modIndex];
      }
    }

    @Override
    public boolean hasMoreElements () {
      while (nextElement == null) {
	if (!super.hasMoreElements ())
	  break;
	Symbol methodName = (Symbol) super.nextElement ();
	if (modifierToken == null) {
	  nextElement = methodName;
	  break;
	}
	String signature = getMethodInterface (methodName);
	if (signature.indexOf (modifierToken) >=0) {
	  nextElement = methodName;
	  break;
	}
      }
      return (nextElement != null);
    }

    @Override
    public Object nextElement () {
      Object retn = nextElement;
      nextElement = null;
      return retn;
    }

  }

  @Override
  public Object clone () {
    try {
      ClassOverrides co = (ClassOverrides) super.clone ();
      co.properties     = (Sequence) properties.clone ();
      co.methods        = (Sequence) methods.clone ();
      //co.events         = (Sequence) events.clone ();
      return co;
    } catch (CloneNotSupportedException e) { 
      // this shouldn't happen, since we are Cloneable
      throw new InternalError();
    }
  }

  /* Must discard duplicates */
  public synchronized void concatenate (ClassOverrides co) {
    //System.out.println (this + ".ClassOverrides::concatenate (" + co + ")");
    if (classInfo == null)
      classInfo = (Structure) co.classInfo.clone ();
    //System.out.println ("Other implemented interfaces = " + co.getImplementedInterfaces ().expand ());
    //System.out.println ("This  implemented interfaces = " + getImplementedInterfaces ().expand ());
    int numOrigElements = properties.size ();
    properties.concatenate (co.properties);
    removeDuplicates (properties, PROPERTY_NAME_, numOrigElements);
    numOrigElements = methods.size ();
    methods.concatenate (co.methods);
    removeDuplicates (methods, METHOD_NAME_, numOrigElements);
    numOrigElements = events.size ();
    events.concatenate (co.events);
    removeDuplicates (events, EVENT_NAME_, numOrigElements);
    numOrigElements = fields.size ();
    fields.concatenate (co.fields);
    removeDuplicates (fields, FIELD_NAME_, numOrigElements);
    imports.concatenate (co.imports);
    // Don't care about duplicates
  }

  /*
   * For each structure in the original sequence, get slot value and
   * verify that no other structure exists in the sequence
   */
  private void removeDuplicates (Sequence s, Symbol slotName, int numOrigElements) {
    try {
      for (int i=0; i<numOrigElements; i++) {
	java.lang.Object slotValue = ((Structure)s.elementAt (i)).getAttributeValue (slotName);	// non-null!
	//System.out.println ("Looking for duplicate class-override (" + slotName + " = " + slotValue + ")");
	for (int j=numOrigElements; j<s.size (); j++) {
	  if (slotValue.equals (((Structure)s.elementAt (j)).getAttributeValue (slotName))) {
	    s.removeElementAt (j);
	    //System.out.println ("Removing duplicate class-override (" + slotName + " = " + slotValue + ")");
	    break;		// Only one duplicate expected
	  }
	}	
      }
    } catch (NoSuchAttributeException nsae) {
      Trace.exception (nsae, null);
    }
  }

  private static final String[] modifiers = {"public",
					     "private",
					     "protected",
					     "static",
					     "final",
					     "synchronized",
					     "volatile",
					     "transient",
					     "native",
					     "interface",
					     "abstract"};
}
