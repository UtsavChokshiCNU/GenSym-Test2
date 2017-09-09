  
package com.gensym.jgi.download;

import java.io.*;
import java.util.Locale;
import java.util.Enumeration;
import java.util.Vector;
import java.util.Hashtable;
import com.gensym.types.G2Type;

import com.gensym.util.*;
import com.gensym.message.Trace;
import com.gensym.message.Resource;
import com.gensym.message.MessageKey;
import com.gensym.classes.G2_ExternalEventObjectRoot;

class EventClassGenerationContext extends StubGenerationContext {

  // Tracing stuff
  private static MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.jgi.download.stubs",
			   EventClassGenerationContext.class);
  private static Resource i18nTrace =
  Trace.getBundle("com.gensym.jgi.download.Messages", Locale.getDefault());
  private static final int DEF_TRACE_LEVEL = 5;
  private String javaClassInterfaceName;
  private static final int DEF_WARN_LEVEL  = 2;
  private Sequence superiorMethodNames;

  //Fields
  private String originalG2JavaStubClassName;
  

  EventClassGenerationContext (OutputStream out,
			       String packageName,
			       String className,
			       String originalG2ClassName,
			       ClassNameMapper nameMapper) {

    super (out, false, packageName, className, nameMapper);
    originalG2JavaStubClassName = 
      G2ClassTranslator.createJavaClassNameFromG2ClassName (Symbol.intern(originalG2ClassName));
    javaClassName = G2ClassTranslator.createJavaClassNameFromG2ClassName(Symbol.intern(className));
  }


  void generateClass (String[] imports, 
			     String superClass, 
			     String[] interfaces, 
			     Symbol[] classInheritancePath,
			     AttrInfo attributes,
			     MethodInfo[] m,
			     Hashtable overridesInhTable) {
      generateClass(imports, superClass, interfaces, classInheritancePath, attributes, m, overridesInhTable, new java.util.Date());
  }

  void generateClass (String[] imports, 
			     String superClass, 
			     String[] interfaces, 
			     Symbol[] classInheritancePath,
			     AttrInfo attributes,
			     MethodInfo[] m,
			     Hashtable overridesInhTable,
			     java.util.Date date) {

    Symbol[] attrTypes  = attributes.attrTypes,
             attrNames  = attributes.attrNames,
             origNames  = attributes.origNames,
             defClasses = attributes.defClasses;
    boolean[] readable = attributes.readable,
              writable = attributes.writable,
              isStatic = attributes.staticP;
    G2Type[] types     = attributes.typeSpecifications;

    //System.out.println ("For G2 Class <" + g2ClassName + ">, class inheritancePath = " + classInheritancePath);
    ClassOverrides overrides = new ClassOverrides();
    //System.out.println ("Collected imports = " + imports.length);
    generateHeader (imports, superClass, interfaces, overrides, date);
    increaseIndent (2);
    // Add hand crafted access method
    println();
    generateFields(attributes, classInheritancePath, overrides);
    println();
    generateConstructors ();
    println();
    // We only allow getters to output for Event Classes
    boolean [] writable_not = new boolean[writable.length];
    superiorMethodNames = getSuperiorMethodNames(superClass);
    generatePropertyAccessors (attrTypes, attrNames, readable, writable_not, isStatic, overrides, types);
    decreaseIndent (2);
    endClass ();
  }

  @Override
  protected void generateFields (AttrInfo attributes,
		       Symbol[] classInheritancePath,
		       ClassOverrides overrides) {
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "genField");
    iprintln("");
    iprintln("private static Sequence userAttributeList;");
    iprintln("");
    super.generateFields(attributes, classInheritancePath, overrides);
  }


  @Override
  protected void generateConstructors () {
    iprintln ("/* Generated constructor */");
    println();
    iprintln("public " + javaClassName 
         + "(java.lang.Object source, Item g2EventObject) {");
    increaseIndent (2);
    iprintln("super(source, g2EventObject);");
    decreaseIndent (2);
    iprintln("};");
  }

  @Override
  void generatePropertyAccessors (String[] jSlotTypes,
				  String[] jSlotNames,
				  Symbol[] slotNames,
				  int[] generationFlags,
				  G2Type[] types){ 

    // Setters are ignored and static fields ignored

    StringBuffer getAttributeListMethodText = new StringBuffer(100);
    for(int i = 0; i < jSlotNames.length; i++) {
      Symbol currentSlot_ = slotNames[i];
      String fieldSym = createJavaSymbolVariableName(currentSlot_);
      String currentSlot = jSlotNames[i];
      String currentType = jSlotTypes[i];
      boolean staticField = ((generationFlags[i] & PROPERTY_STATIC) != 0);
      String fieldName   = G2ClassTranslator.initCap(makeFieldNameForSlot(currentSlot, staticField));
      String slotVarName = ensureLegalJavaVariableName (currentSlot);
      boolean getterExists = (generationFlags[i] & PROPERTY_GETTER) != 0;
      if (fieldName.equals ("Text")) {
	getterExists = true;
	currentType  = "java.lang.String";
      }

      if (getterExists && !staticField) {
	String getterName =  "get" + fieldName;

	if (!superiorMethodNames.contains(getterName)) {  
	  iprintln ("/**");
	  iprintln (" * Generated Property Getter for attribute -- " + currentSlot_);
	  iprint   (" * @return the value of the " + currentSlot_ + " attribute of this ");
	  println  (staticField ? "class" : "item");
	  iprintln (" * @exception G2AccessException if there are any communication problems");
	  iprintln (" */");
	  String getterInterface = ("public " + currentType + " " + getterName +
				    "() throws G2AccessException {");
	  iprintln(getterInterface);
	  increaseIndent (2);
	  //iprintln("return (" + currentType + ")getAttributeValue(" + fieldSym + ");");
	  iprintln ("java.lang.Object retnValue = getAttributeValue (" + fieldSym + ");");
 	  iprintln ("return " + StubGenerationContext.codeToGetPrimitiveValueOrCastReturnObject ("retnValue", currentType) + ";");
	  getAttributeListMethodText.append("userAttributeList.addElement(" + fieldSym + ");\n");
	  //generateGetBody (output, currentType, fieldName);
	  decreaseIndent (2);
	  iprintln ("}");
	  println();
	}
      }
    }

    iprintln("");
    iprintln("/**");
    iprintln("* Return the attributes that this External event will \"preload\" from");
    iprintln("* G2 at creation.");
    iprintln("*/");
    iprintln("public static Sequence " + G2_ExternalEventObjectRoot.GET_ATTRIBUTELIST_METHODNAME_ + "() {\n");
    increaseIndent(2);
    iprintln("if (userAttributeList == null) {");
    increaseIndent(2);
    iprintln("userAttributeList = new Sequence(5);");
    iprintln("userAttributeList.addElement(SOURCE_);"); //inherited
    iprintMultiLineString(getAttributeListMethodText.toString());
    decreaseIndent(2);
    iprintln("}");
    iprintln("return userAttributeList;");
    decreaseIndent(2);
    iprintln("}");
    iprintln("");
  }


  void generateGetBody (PrintWriter output,
			       String currentType,
			       String fieldName) {

    //String getterFn = "((" + originalG2JavaStubClassName + ")" + "g2EventObject).get" + fieldName;

    //iprintln ("return " + getterFn);
  }

  /**
   * Return a list of methods names defined in superClassName and above.
   */
  protected Sequence getSuperiorMethodNames(String superClassName) {
    try {
      Class superClass = Class.forName(superClassName);
      java.lang.reflect.Method[] methods = superClass.getMethods();
      Sequence names = new Sequence(20);
      for (int i=0; i<methods.length; i++)
	names.addElement(methods[i].getName());
      return names;
    } catch (Exception e) {
      Trace.exception(e);
      return new Sequence();
    }
  }

}
