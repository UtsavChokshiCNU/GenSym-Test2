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
import com.gensym.jgi.G2ConnectionAdapter;
import com.gensym.jgi.G2ConnectionEvent;

import com.gensym.classes.Item;
import com.gensym.classes.Definition;
import com.gensym.classes.G2Definition;

import com.gensym.types.G2Type;

import java.awt.Component;
import java.util.Hashtable;
import java.util.Vector;
import java.util.Enumeration;
import java.io.*;

public class AttributeInfo{

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

  private boolean initialized = false;
  boolean hasEditor = false;
  private EditorBuilder editorBuilder = null;
  TypePattern thePattern = null;
  Structure theBindings = null;
  Structure denotation;

  String key; // "<ClassName>::<AttributeName>"

  private static boolean trace = false;

  static Hashtable connectionTable = new Hashtable(); //connection --> ConnectionTableEntry

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


  private AttributeInfo(){
  }

  private static AttributeInfo makeAttributeInfo(Structure description){
    AttributeInfo info = new AttributeInfo();

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


    info.key = info.definingClass+keySeparator+info.attributeName;

    String symbolName = info.attributeName.toString();
    int index = symbolName.indexOf("::");

    if (index != -1)
      {
	String classNameString = symbolName.substring(0,index);
	String attributeNameString = symbolName.substring(index+2);
	info.simpleAttributeName = Symbol.intern(attributeNameString);
	info.denotation = makeDenotation(info.simpleAttributeName,
					 Symbol.intern(classNameString));
      } 
    else
      {
	info.simpleAttributeName = info.attributeName;
	info.denotation = makeDenotation(info.attributeName,null);
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

    return info;
  }

  private static Structure makeDenotation (Symbol attributeName, Symbol className){
    Symbol[] keys = new Symbol[] { type_, name_ };
    Object[] values = new Object[] { attribute_, attributeName };
    
    Structure denotation = null;

    try {
      denotation = new Structure(keys, values);
    } catch (NtwIllegalArgumentException e) // this is completely inane
      {
	e.printStackTrace();
      }

    if (className != null)
      denotation.setAttributeValue(classQualifier_, className);
    return denotation;
  }

  /**
   * @undocumented
   * We probably shouldn't have this public but should call it inside each getter.
   */
  public void initializeEditorInformation() {
    if (initialized)
      return;
    synchronized (AttributeInfo.class) {
      initialized = true;
      if (noPatternsAvailable)
        return; // do nothing
      else if (patterns == null)
        try {
          patterns = TypePattern.readPatternFile(getClass()
              .getResourceAsStream("DefaultPatterns.lisp"));
        } catch (IOException e) {
          e.printStackTrace();
          noPatternsAvailable = true;
          return;
        }
      // should protect against complex text fields (formulas & expressions)
      // here, but need way of doing this through introspection
      
      boolean attributeNameCheck = (simpleAttributeName.equals(text_) 
    		  					|| simpleAttributeName.equals(expressionToDisplay_)) && isSystemDefined;
      boolean grammerCheck = editorGrammar == null || !isComplexGrammar(editorGrammar);
      
      if (isValueWritable && (type != null) && !attributeNameCheck && grammerCheck ) {
        int i, size = patterns.size();
        if (editorGrammar != null && editorGrammar.equals(extentColorOrMetacolor_)) {
          editorBuilder = new ColorEditorBuilder();
          hasEditor = true;
        } else
          for (i = 0; i < size; i++) {
            TypePattern pattern = (TypePattern) patterns.elementAt(i);
            Structure bindings = pattern.match(type);
            if (bindings != null) {
              thePattern = pattern;
              theBindings = bindings;
              hasEditor = true;
              break;
            }
          }
      }
    }
  }

  class ColorEditorBuilder extends EditorBuilder{
    @Override
    public Component buildEditor(){
      return new G2ColorField(com.gensym.editor.color.G2ColorsCanvas.INCLUDE_FOREGROUND + com.gensym.editor.color.G2ColorsCanvas.INCLUDE_TRANSPARENT);
    }
  }

  Component makeEditor(){
    if (editorBuilder != null)
      return editorBuilder.buildEditor();
    if (thePattern != null)
      return thePattern.invokeEditorBuilder(theBindings);
    else 
      return null;
  }

  /**
   *  Returns a list of AttributeInfos for the specified attributes of item
   */
  public static final AttributeInfo[] getAttributeInfos(TwAccess connection, Item item, Symbol[] attributes) throws G2AccessException{
    //if descriptions for this class have not yet been requested, get & cache descriptions for ALL attributes
    //need to get ALL descriptions because of bugs in getAttributeDescription with list of attributes
    if (getClassTableEntry(connection, item) == null){
      Sequence attributeDescriptions = connection.getAttributeDescriptions(item.getG2ClassName(), new Sequence(0));
      for (int i=0; i<attributeDescriptions.size(); i++)
	getOrCreateAttributeInfo(connection, item, (Structure)attributeDescriptions.elementAt(i));
    }

    AttributeInfo[] infos = new AttributeInfo[attributes.length];
    for (int i=0; i<infos.length; i++)
      infos[i] = getAttributeInfo(connection, item, attributes[i]);
    return infos;
  }

  private static AttributeInfo getOrCreateAttributeInfo(TwAccess connection, Item item, Structure description) throws G2AccessException{
    AttributeInfo info = 
      getAttributeInfo(connection, item, (Symbol)description.getAttributeValue(attributeName_, null));
    if (info == null || !info.definingClass.equals(description.getAttributeValue(definingClass_, null))){
      info = makeAttributeInfo(description);
      getInfoTable(connection).put(info.key, info);
    }
    return info;
  }

  private static AttributeInfo getAttributeInfo(TwAccess connection, Item item, Symbol attribute) throws G2AccessException{
    Hashtable infoTable = getInfoTable(connection);
    Symbol className = item.getG2ClassName();
    ClazzTableEntry classEntry = getOrCreateClassTableEntry(connection, item);
    return getAttributeInfo(infoTable, className, attribute, classEntry.inheritancePath);
  }

  private static ClazzTableEntry getOrCreateClassTableEntry(TwAccess connection, Item item) throws G2AccessException{
    ClazzTableEntry classEntry = getClassTableEntry(connection, item);
    if (classEntry == null){
      Sequence inheritancePathSeq =
	item.getDefinition ().getSystemClassInheritancePath ();
      Symbol[] inheritancePath = new Symbol[inheritancePathSeq.size ()];
      inheritancePathSeq.copyInto (inheritancePath);
      Symbol className = item.getG2ClassName();
      classEntry = new ClazzTableEntry(connection, className, inheritancePath);
      Hashtable classTable = getClassTable(connection);
      classTable.put(className, classEntry);
    }
    return classEntry;
  }

  private static ClazzTableEntry getClassTableEntry(TwAccess connection, Item item) throws G2AccessException{
    Symbol className = item.getG2ClassName();
    Hashtable classTable = getClassTable(connection);
    return (ClazzTableEntry)classTable.get(className);
  }
  
  private static AttributeInfo getAttributeInfo(Hashtable infoTable, Symbol className, Symbol attributeName, Symbol[] inheritancePath) throws G2AccessException  {
    String symbolName = attributeName.toString();
    int index = symbolName.indexOf("::");

    if (index != -1)
      return (AttributeInfo)infoTable.get(symbolName.substring(0, index)+keySeparator+attributeName);
    else{
      for (int i = 0 ; i<inheritancePath.length ; i++){
	String key = inheritancePath[i]+keySeparator+attributeName;
	AttributeInfo info = (AttributeInfo)infoTable.get(key);
	if (info != null)
	  return info;
      }
    }
    return null;
  }

  /**
   *  Returns a list of all attribute names for the item visible in the 
   *  connection's user mode
   */
  public static final Symbol[] getAttributesForMode(Item item, Symbol userMode) throws G2AccessException{
    Sequence visibleAttributes = item.getVisibleAttributes(userMode);
    int size = visibleAttributes.size();
    Symbol[] attributes = new Symbol[size];
    for (int i=0; i<size; i++)
      attributes[i] = (Symbol)visibleAttributes.elementAt(i);
    return attributes;
  }


  /**
   *  Returns a list of all attribute names for the item regardless of the 
   *  connection's user mode
   */
  private static final Symbol ADMINISTRATOR_ = Symbol.intern("ADMINISTRATOR");

  public static final Symbol[] getAttributes(TwAccess connection, Item item) throws G2AccessException{
    return getAttributesForMode(item, ADMINISTRATOR_);
  }

  /**
   *  Returns a list of all the non-virtual readable attribute names for the item visible in the 
   *  connection's user mode
   */
  public static final Symbol[] getTableAttributesForMode(TwAccess connection, Item item, Symbol userMode) throws G2AccessException{
    Symbol[] attributes = getAttributesForMode(item, userMode);
    AttributeInfo[] infos = getAttributeInfos(connection, item, attributes);
    Vector attributeList = new Vector();
    for (int i=0; i<infos.length; i++){
      if (!infos[i].isVirtual && infos[i].isTextReadable && !infos[i].isSuperseded)
	attributeList.addElement(attributes[i]);
    }
    Symbol[] tableAttributes = new Symbol[attributeList.size()];
    attributeList.copyInto(tableAttributes);
    return tableAttributes;
  }

  /**
   *  Returns a list of all the non-virtual readable attribute names for the item regardless of the 
   *  connection's user mode
   */
  public static final Symbol[] getTableAttributes(TwAccess connection, Item item) throws G2AccessException{
    return getTableAttributesForMode(connection, item, ADMINISTRATOR_);
  }

  private static Hashtable getInfoTable(TwAccess connection){
    return getConnectionTableEntry(connection).infoTable;
  }

  private static Hashtable getClassTable(TwAccess connection){
    return getConnectionTableEntry(connection).classTable;
  }

  private static ConnectionTableEntry getConnectionTableEntry(TwAccess connection){
    ConnectionTableEntry cxnEntry = (ConnectionTableEntry)connectionTable.get(connection);
    if (cxnEntry == null){
      cxnEntry = new ConnectionTableEntry();
      connectionTable.put(connection, cxnEntry);
      connection.addG2ConnectionListener(new ConnectionClosedAdapter());
    }
    return cxnEntry;
  }

  public Structure getDenotation() {
    return denotation;
  }

  public boolean hasEditor() {
    return hasEditor;
  }
  
  public Symbol getAttributeName(){
    return attributeName;
  }

  public Symbol getSimpleAttributeName(){
    return simpleAttributeName;
  }

  public Symbol getDefiningClass(){
    return definingClass;
  }

  public boolean isSystemDefined(){
    return isSystemDefined;
  }

  public boolean isSuperseded(){
    return isSuperseded;
  }

  public boolean isVirtual(){
    return isVirtual;
  }

  public boolean isTextReadable(){
    return isTextReadable;
  }

  public boolean isTextWritable(){
    return isTextWritable;
  }

  public boolean isValueReadable(){
    return isValueReadable;
  }

  public boolean isValueWritable(){
    return isValueWritable;
  }

  public G2Type getType(){
    return type;
  }


  static void clearAllDialogInfoCaches(TwAccess connection){
    Hashtable classTable = getClassTable(connection);
    Enumeration classes = classTable.elements();
    try 
      {
	while (classes.hasMoreElements())
	  {
	    ClazzTableEntry entry = (ClazzTableEntry)classes.nextElement();
	    if (entry.definition instanceof Definition)
	      ((Definition)entry.definition).removeDefinitionListener(entry);
	  }
      } catch (G2AccessException g2ae)
	{
	  // do nothing
	  Trace.exception (g2ae);
	}
    classTable.clear();
    getInfoTable(connection).clear();
  }

  @Override
  public String toString(){
	  
	String systemDefined = isSystemDefined? "T" : "F";
	String virtual = isVirtual? "T" : "F";
	String superseded = isSuperseded? "T" : "F";
	String textReadable = isTextReadable? "T" : "F";
	String textWritable = isTextWritable? "T" : "F";
	String valueReadable = isValueReadable? "T" : "F";
	String valueWritable = isValueWritable? "T" : "F";
    
	return 
      getClass().getName()+
      "[attribute: "+attributeName+
      " definingClass: "+definingClass+
      " systemDefined: "+ systemDefined +
      " virtual: "+ virtual +
      " superseded: "+ superseded +
      " txtReadable: "+ textReadable +
      " txtWritable: "+ textWritable +
      " valueReadable: "+ valueReadable +
      " valueWritable: "+ valueWritable +
      " type: "+type+
      " denotation:"+denotation+"]";
  }

}

class ConnectionTableEntry{
  Hashtable infoTable = new Hashtable(); //infoTable : "<definingClassname><><attribute>" --> info
  Hashtable classTable = new Hashtable();//classTable : classname -->  classTableEntry
}                           

class ConnectionClosedAdapter extends G2ConnectionAdapter{
  @Override
  public void g2ConnectionClosed(G2ConnectionEvent event){
    TwAccess connection = (TwAccess)event.getSource();
    connection.removeG2ConnectionListener(this);
    AttributeInfo.clearAllDialogInfoCaches(connection);
  }
}

class ClazzTableEntry implements DefinitionListener{
  TwAccess connection;
  G2Definition definition;
  boolean isSystemDefined;
  Symbol[] inheritancePath;
  
  ClazzTableEntry(TwAccess connection, Symbol className,
		  Symbol[] inheritancePath){
    this.connection = connection;
    this.inheritancePath = inheritancePath;
    try {
      ClassManager classManager = connection.getClassManager();
      definition = classManager.getDefinition(className);
      if (definition instanceof Definition)
	((Definition)definition).addDefinitionListener(this);
      else
	isSystemDefined = true;
    }
    catch (G2AccessException g2ae){
      // do nothing
      Trace.exception (g2ae);
    }
  }
  
  @Override
  public void staticAttributeChanged (DefinitionEvent e){
    AttributeInfo.clearAllDialogInfoCaches(connection);
  }
  
  @Override
  public void classNameChanged (DefinitionEvent e){
    AttributeInfo.clearAllDialogInfoCaches(connection);
  }
  
  @Override
  public void directSuperiorClassesChanged (DefinitionEvent e){
    AttributeInfo.clearAllDialogInfoCaches(connection);
  }
  
  @Override
  public void deleted (DefinitionEvent e){
    AttributeInfo.clearAllDialogInfoCaches(connection);
  }
  
  @Override
  public void classInheritancePathChanged (DefinitionEvent e){
    AttributeInfo.clearAllDialogInfoCaches(connection);
  }
  
  @Override
  public void classSpecificAttributesChanged (DefinitionEvent e){
    AttributeInfo.clearAllDialogInfoCaches(connection);
  }
}

