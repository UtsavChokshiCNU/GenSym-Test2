package com.gensym.gcg;

import com.gensym.message.Trace;

import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.NtwIllegalArgumentException;
import com.gensym.util.DefinitionListener;
import com.gensym.util.DefinitionEvent;
import com.gensym.util.ClassManager;

import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2AccessException;

import com.gensym.classes.Item;
import com.gensym.classes.Definition;
import com.gensym.classes.G2Definition;

import com.gensym.types.G2Type;

import java.awt.Component;
import java.util.Hashtable;
import java.util.Vector;
import java.util.Enumeration;
import java.io.*;

public class AttributeDialogInfo
{
  Symbol attributeName;        // may have class-name:: before attr-name
  Symbol simpleAttributeName;  // always just the attr-name
  Symbol definingClass;
  Symbol editorGrammar;

  boolean isSystemDefined = false;
  boolean isSuperseded = false;
  boolean isVirtual = false;
  boolean isTextReadable = false;
  boolean isTextWritable = false;
  boolean isValueReadable = false;
  boolean isValueWritable = false;
 

  G2Type type = null;

  Component editor = null;
  boolean hasEditor = false;
  byte[] serializedEditor;
  Structure denotation;

  String key; // "<ClassName>::<AttributeName>"

  private static boolean trace = false;

  static Hashtable attributesForModeTable = new Hashtable();
  static Hashtable infoTable = new Hashtable();
  static Hashtable classTable = new Hashtable();
  private static Vector patterns = null;
  private static boolean noPatternsAvailable = false;

  private static final Symbol attributeName_ = Symbol.intern("ATTRIBUTE-NAME");
  private static final Symbol definingClass_ = Symbol.intern("DEFINING-CLASS");
  private static final Symbol editorGrammar_ = Symbol.intern("EDITOR-GRAMMAR");
  private static final Symbol virtual_ = Symbol.intern("VIRTUAL");
  private static final Symbol superseded_ = Symbol.intern("SUPERSEDED");
  private static final Symbol systemDefined_ = Symbol.intern("IS-SYSTEM-DEFINED");
  private static final Symbol valueReadable_ = Symbol.intern("VALUE-READABLE");
  private static final Symbol valueWritable_ = Symbol.intern("VALUE-WRITABLE");
  private static final Symbol textReadable_ = Symbol.intern("TEXT-READABLE");
  private static final Symbol textWritable_ = Symbol.intern("TEXT-WRITABLE");

  private static final Symbol type_ = Symbol.intern("TYPE");
  private static final Symbol name_ = Symbol.intern("NAME");
  private static final Symbol attribute_ = Symbol.intern("ATTRIBUTE");
  private static final Symbol classQualifier_ = Symbol.intern("CLASS-QUALIFIER");
  private static final Symbol extentColorOrMetacolor_
     = Symbol.intern("EXTANT-COLOR-OR-METACOLOR");

  // hax
  private static final Symbol text_ = Symbol.intern("TEXT");
  private static final Symbol expressionToDisplay_ 
    = Symbol.intern("EXPRESSION-TO-DISPLAY");

  private static final String keySeparator = "<>";


  private static String[] complexGrammarNames
  = { "DATA-SERIES-DESCRIPTIONS",
      "COMMAND",
      "GENERIC-FILE-PATHNAME",
      "FILE-COMMAND",
      "INIT-FILE-COMMAND",
      "QUERY-COMMAND",
      "GESTURE-DEFINITION",
      "PLOT-EXPRESSION",
      "RESOURCE-DEFINITION",
      "SIMPLE-FORMATTED-TEXT",
      "STATEMENT",
      "DISPLAY-EXPRESSION",
      "EMBEDDED-RULE",
      "EXPRESSION",
      "FOREIGN-FUNCTION-DECLARATION",
      "FUNCTION-DEFINITION",
      "GENERIC-FORMULA",
      "GENERIC-SIMULATION-FORMULA",
      "GFI-OUTPUT-VALUES",
      "INSTANCE-FORMULA",
      "ITEM-DESIGNATIONS-FOR-MODEL",
      "LANGUAGE-TRANSLATION",
      "LIST-OF-GRAPH-EXPRESSIONS",
      "LOGICAL-INSTANCE-FORMULA",
      "PROCEDURE-DEFINITION",
      "REMOTE-PROCEDURE-DECLARATION",
      "RULE",
      "SPECIFIC-SIMULATION-FORMULA",
      "TEXT-CONVERSION-STYLE-NAME",
      "UNITS-DECLARATION",
      "USER-MENU-CHOICE-EXPRESSION",
      "CONSTANT-VARIABLE-DESIGNATION?",
      "FRAME-CHANGE-LOG"};

  private static Symbol[] complexGrammarSymbols;

  static {
    int i, len = complexGrammarNames.length;
    complexGrammarSymbols = new Symbol[len];
    for (i=0; i<len ; i++)
      complexGrammarSymbols[i] = Symbol.intern(complexGrammarNames[i]);
  }

  private static boolean isComplexGrammar(Symbol grammar)
  {
    boolean res = false;
    int i, len = complexGrammarSymbols.length;
    for (i=0; i<len ; i++)
      {
// 	System.out.println("is "+complexGrammarSymbols[i]+
// 			   " equal to "+grammar);
	if (complexGrammarSymbols[i].equals(grammar))
	  {
	    res = true;
	    break;
	  }
      }
    //System.out.println("grammar "+grammar+" complex? "+res);
    return res;
  }
    
  public static String[] getCachedVisibleAttributes(TwAccess connection,
						    Item item,
						    Symbol userMode)
  {
    Symbol className = null;
    try {
      className = item.getG2ClassName();
    } catch (G2AccessException e)
      { e.printStackTrace(); } // this can't happen - stub HAVE class-names

    String key = className+"<in>"+userMode;
    Object entry = attributesForModeTable.get(key);
    
    if (entry != null)
      return (String[]) entry;
    else
      try 
      {
	Sequence visibleAttributes
	  = item.getVisibleAttributes(userMode);
	if (trace)
	  System.out.println ("Visible attributes for " + item + " in mode " + userMode + " = " +
			      visibleAttributes);

	Symbol[] inheritancePath;
	ClassTableEntry classTableEntry 
	  = (ClassTableEntry)classTable.get(className);
	
	int i, size = visibleAttributes.size();

	// ensure all classes associated with item are cached.
	if (classTableEntry == null)
	  {
	    Sequence inheritancePathSeq =
	      item.getDefinition ().getSystemClassInheritancePath ();
	    inheritancePath = new Symbol[inheritancePathSeq.size ()];
	    inheritancePathSeq.copyInto (inheritancePath);
	    // this will get any super-classes of className implicitly
	    storeNewAttributeDialogInfo(connection,className, null);
	    classTable.put(className,
			   new ClassTableEntry(connection,className,
					       inheritancePath));
	  }
	else
	  inheritancePath = classTableEntry.inheritancePath;
	  
	Symbol[] definingClasses = new Symbol[size];
	String[] keyArray = new String[size];
	for (i=0; i<size ; i++)
	  {
	    Symbol attributeName = (Symbol) visibleAttributes.elementAt(i);
	    Symbol definingClass = getDefiningClass(className,attributeName, inheritancePath);
	    Symbol simpleAttributeName 
	      = getSimpleAttributeName(className,attributeName);
	    keyArray[i] = definingClass+keySeparator+simpleAttributeName;
	    if (trace)
	      System.out.println ("AttrName = " + attributeName +
				  ", Defining Class = " + definingClass +
				  ", Simple AttrName = " + simpleAttributeName);
	    
	  }
	
	attributesForModeTable.put(key,keyArray);
	return keyArray;
      } catch (G2AccessException e)
	{
	  e.printStackTrace();
	  return null;
	}
  }

  public static void clearVisibleAttributesCache()
  {
    attributesForModeTable.clear();
  }

  private static Symbol getDefiningClass(Symbol className, Symbol attributeName, Symbol[] inheritancePath)
       throws G2AccessException
  {
    String symbolName = attributeName.toString();
    int index = symbolName.indexOf("::");
    
    if (index != -1)
      return Symbol.intern(symbolName.substring(0,index));
    else
    {
      for (int i = 0 ; i<inheritancePath.length ; i++)
	{
	  String key = inheritancePath[i]+keySeparator+attributeName;
	  if (infoTable.get(key) != null)
	    {
	      if (trace)
		System.out.println("class "+className+" attr "+attributeName+" def class "+
				   inheritancePath[i]);
	      return inheritancePath[i];
	    }
	}
      if (trace)
	System.out.println("class "+className+" attr "+attributeName+" no def class");
      return null;
    }
  }

  private static Symbol getSimpleAttributeName
                          (Symbol className, Symbol attributeName)
       throws G2AccessException
  {
    String symbolName = attributeName.toString();
    int index = symbolName.indexOf("::");
    
    if (index != -1)
      return Symbol.intern(symbolName.substring(index+2));
    else 
      return attributeName;
  }


  public static AttributeDialogInfo getAttributeDialogInfo(TwAccess connection,
							   String classAndNameKey)
  {
    //boolean trace = true;
    if (trace)
      System.out.println ("getAttributeDialogInfo (" + connection + ", " + classAndNameKey + ") called");
    Object entry = infoTable.get(classAndNameKey);
    
    AttributeDialogInfo result;
    if (entry != null)
      result = (AttributeDialogInfo)entry;
    else
      {
	int index = classAndNameKey.indexOf(keySeparator);
	Symbol className 
	  = Symbol.intern(classAndNameKey.substring(0,index));
	Symbol attributeName 
	  = Symbol.intern(classAndNameKey.substring(index+keySeparator.length()));
	
	result = storeNewAttributeDialogInfo(connection,className,attributeName);
      }
    if (trace)
      System.out.println("  returns "+result);
    return result;
  }

  /* the attributeName argument can be null to indicate that
     no return value is desired */
  
  private static AttributeDialogInfo storeNewAttributeDialogInfo(TwAccess connection,
								 Symbol className,
								 Symbol attributeName)
  {
    AttributeDialogInfo info = null;
    Sequence attributeDescriptions = null;

    try {
      attributeDescriptions 
	= connection.getAttributeDescriptions(className,new Sequence(0));
      if (trace)
	System.out.println ("getAttributeDescriptions (" + className + ") = " + attributeDescriptions);
    } catch (G2AccessException e)
      {
	System.out.println("unexpected undefined class "+className + " while calling getAttributeDescriptions (" + className + ")");
	e.printStackTrace();
      }
    int i,size = attributeDescriptions.size();
    
    for (i=0 ; i<size ; i++)
      {
	AttributeDialogInfo attributeInfo 
	  = makeAttributeDialogInfo((Structure) attributeDescriptions.elementAt(i));
	infoTable.put(attributeInfo.key,attributeInfo);
	if (attributeName != null &&
	    attributeInfo.attributeName.equals(attributeName))
	  info = attributeInfo;
      }
    return info;
  }



  private static AttributeDialogInfo makeAttributeDialogInfo(Structure description)
  {
    AttributeDialogInfo info = new AttributeDialogInfo();

    info.attributeName 
      = (Symbol) description.getAttributeValue(attributeName_ ,null);
    info.definingClass
      = (Symbol) description.getAttributeValue(definingClass_ ,null);
    info.editorGrammar 
      = (Symbol) description.getAttributeValue(editorGrammar_ ,null);

    info.isValueReadable
      = ((Boolean) description.getAttributeValue(valueReadable_ ,null)).booleanValue();
    info.isValueWritable
      = ((Boolean) description.getAttributeValue(valueWritable_ ,null)).booleanValue();
    info.isTextReadable
      = ((Boolean) description.getAttributeValue(textReadable_ ,null)).booleanValue();
    info.isTextWritable
      = ((Boolean) description.getAttributeValue(textWritable_ ,null)).booleanValue();
    Object thing =  description.getAttributeValue(virtual_ ,null);
    if (thing == null && trace)
      System.out.println("struct is "+description);
    info.isVirtual
      = ((Boolean) description.getAttributeValue(virtual_ ,null)).booleanValue();
    info.isSystemDefined
      = ((Boolean) description.getAttributeValue(systemDefined_ ,null)).booleanValue();

    Boolean superseded
      = (Boolean) description.getAttributeValue(superseded_ ,null);
    if (superseded != null)
      info.isSuperseded = superseded.booleanValue();

    String symbolName = info.attributeName.toString();
    int index = symbolName.indexOf("::");

    if (index != -1)
      {
	String classNameString = symbolName.substring(0,index);
	String attributeNameString = symbolName.substring(index+2);
	info.simpleAttributeName = Symbol.intern(attributeNameString);
	info.denotation = makeDenotation(info.simpleAttributeName,
					 Symbol.intern(classNameString));
	info.key = classNameString+keySeparator+attributeNameString;
      } 
    else
      {
	info.simpleAttributeName = info.attributeName;
	info.denotation = makeDenotation(info.attributeName,null);
	info.key = info.definingClass+keySeparator+symbolName;
      }

    if (trace)
      System.out.println("made info aname="+info.attributeName+
			 " simpleName=" + info.simpleAttributeName+
			 " index=" + index+
			 " definClass="+info.definingClass+
			 " key= "+info.key+
			 " value readable "+info.isValueReadable);
    Structure typeDescription 
      = (Structure) description.getAttributeValue(type_,null);
    try {
      if (typeDescription != null)
	info.type = G2Type.makeG2TypeFromDescription(typeDescription);
    } catch (Exception e)
      {
	System.out.println("FAILED TO MAKE G2TYPE from type description "+
			   typeDescription);
	e.printStackTrace();
      }

    info.makeEditorIfPossible();

    return info;
  }

  private static Structure makeDenotation (Symbol attributeName, Symbol className)
  {
    Symbol[] keys = new Symbol[] { type_, name_ };
    Object[] values = new Object[] { attribute_, attributeName };
    
    Structure denotation = null;

    try {
      denotation = new Structure(keys,values);
    } catch (NtwIllegalArgumentException e) // this is completely inane
      {
	e.printStackTrace();
      }

    if (className != null)
      denotation.setAttributeValue(classQualifier_, className);

    return denotation;
  }

  private void makeEditorIfPossible()
  {
    if (noPatternsAvailable)
      return; // do nothing
    else if (patterns == null)
      try 
      {
	patterns 
	  = TypePattern.readPatternFile(getClass().getResourceAsStream("DefaultPatterns.lisp"));
      } catch (IOException e)
	{
	  e.printStackTrace();
	  noPatternsAvailable = true;
	  return;
	}

      // should protect against complex text fields (formulas & expressions) 
      // here, but need way of doing this through introspection
    if (isValueWritable && (type != null) &&
	!((simpleAttributeName.equals(text_) ||
	   simpleAttributeName.equals(expressionToDisplay_)) &&
	  isSystemDefined) &&
	 ((editorGrammar == null) ||
	  !isComplexGrammar(editorGrammar)))
      {
	int i, size = patterns.size();
	if (editorGrammar != null && 
		editorGrammar.equals(extentColorOrMetacolor_))
	  {
	    editor = new G2ColorField(com.gensym.editor.color.G2ColorsCanvas.INCLUDE_FOREGROUND + com.gensym.editor.color.G2ColorsCanvas.INCLUDE_TRANSPARENT, simpleAttributeName.toString());
	  }
	else
	  for (i=0; i<size ; i++)
	    {
	      TypePattern pattern = (TypePattern) patterns.elementAt(i);
	      Structure bindings = pattern.match(type);
	      if (bindings != null)
		editor = pattern.invokeEditorBuilder(bindings);
	    }
	if (trace)
	  System.out.println("Fresh (unserialized) editor is "+editor);
      }
    
    if (editor != null)
      try 
      {
	ByteArrayOutputStream baos = new ByteArrayOutputStream();
	ObjectOutputStream oos = new ObjectOutputStream(baos);
	oos.writeObject(editor);
	oos.close();
	serializedEditor = baos.toByteArray();
	hasEditor = true;
      } catch (IOException e)
	{
	  com.gensym.message.Trace.exception (e);
	  System.out.println("failure to serialize Editor");
	  e.printStackTrace();
	  editor = null;
	  hasEditor = false;
	}
  }

  Component makeEditor()
  {
    if (hasEditor)
      try
      {
	ByteArrayInputStream bais = new ByteArrayInputStream(serializedEditor);
	ObjectInputStream ois = new EditorObjectInputStream(bais);
	Component editor = (Component) ois.readObject();
	ois.close();
	return editor;
      } catch (Exception e)
	{
	  System.out.println("Failed to de-serialize editor");
	  e.printStackTrace();
	  return null;
	}
    else
      return null;
  }

  @Override
  public String toString()
  {
    return 
      "<AttrDialogInfo "+attributeName+
      " sys: "+(isSystemDefined? "T" : "F")+
      " vrt: "+(isVirtual? "T" : "F")+
      " tr: "+(isTextReadable? "T" : "F")+
      " tw: "+(isTextWritable? "T" : "F")+
      " vr: "+(isValueReadable? "T" : "F")+
      " vw: "+(isValueWritable? "T" : "F")+
      " ed: "+(hasEditor? "T" : "F")+
      " gm: "+editorGrammar+
      " tp: "+type+">";
  }
}

class ClassTableEntry implements DefinitionListener
{
  G2Definition definition;
  boolean isSystemDefined = false;
  Symbol[] inheritancePath;
  
  ClassTableEntry(TwAccess connection, Symbol className,
		  Symbol[] inheritancePath)
  {
    this.inheritancePath = inheritancePath;
    try {
      ClassManager classManager = connection.getClassManager();
      definition = classManager.getDefinition(className);
      if (definition instanceof Definition)
	((Definition)definition).addDefinitionListener(this);
      else
	isSystemDefined = true;
    }
    catch (G2AccessException g2ae)
      {  // do nothing
	Trace.exception (g2ae);
      }
    AttributeDialogInfo.classTable.put(className,this);
  }

  private void clearAllDialogInfoCaches()
  {
    Enumeration classes = AttributeDialogInfo.classTable.elements();
    try 
      {
	while (classes.hasMoreElements())
	  {
	    ClassTableEntry entry = (ClassTableEntry)classes.nextElement();
	    if (entry.definition instanceof Definition)
	      ((Definition)entry.definition).removeDefinitionListener(entry);
	  }
      } catch (G2AccessException g2ae)
	{
	  // do nothing
	  Trace.exception (g2ae);
	}
    AttributeDialogInfo.infoTable.clear();
    AttributeDialogInfo.classTable.clear();
    AttributeDialogInfo.attributesForModeTable.clear();
  }

  @Override
  public void staticAttributeChanged (DefinitionEvent e)
  {
    clearAllDialogInfoCaches();
  }

  @Override
  public void classNameChanged (DefinitionEvent e)
  {
    clearAllDialogInfoCaches();
  }
  
  @Override
  public void directSuperiorClassesChanged (DefinitionEvent e)
  {
    clearAllDialogInfoCaches();
  }

  @Override
  public void deleted (DefinitionEvent e)
  {
    clearAllDialogInfoCaches();
  }

  @Override
  public void classInheritancePathChanged (DefinitionEvent e)
  {
    clearAllDialogInfoCaches();
  }

  @Override
  public void classSpecificAttributesChanged (DefinitionEvent e)
  {
    clearAllDialogInfoCaches();
  }

  @Override
  public String toString () {
    return super.toString() + " : system-class=" + isSystemDefined + ",Inh.Path=" +
      com.gensym.core.DebugUtil.printArray (inheritancePath) + ",defn=" + definition;
  }

}

class EditorObjectInputStream extends ObjectInputStream {

  EditorObjectInputStream (InputStream is) throws IOException, StreamCorruptedException {
    super (is);
  }

  @Override
  protected Class resolveClass (ObjectStreamClass v) 
       throws ClassNotFoundException {
    String className = v.getName ();
    ClassLoader cl = getClass().getClassLoader();
    return cl == null ? 
      Class.forName (className) :
      cl.loadClass (className);
  }
}
