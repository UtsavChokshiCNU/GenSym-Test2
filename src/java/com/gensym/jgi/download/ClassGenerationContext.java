
package com.gensym.jgi.download;

import java.io.*;
import java.nio.charset.Charset;
import java.util.Locale;
import java.util.Enumeration;
import java.util.Hashtable;
import com.gensym.types.G2Type;
import com.gensym.util.*;

import com.gensym.message.Trace;
import com.gensym.message.Resource;
import com.gensym.message.MessageKey;

public class ClassGenerationContext implements com.gensym.util.symbol.G2TypeSymbols, ExtendedTypeSymbols {


  // Tracing stuff
  private static MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.jgi.download.stubs",
			   ClassGenerationContext.class);
  private static Resource i18nTrace =
  Trace.getBundle("com.gensym.jgi.download.Messages", Locale.getDefault());
  private static final int DEF_TRACE_LEVEL = 5;
  

  //Fields
  protected OutputStream stream;
  protected PrintWriter output;
  protected boolean isInterface;
  protected String packageName, className, javaClassName;
  protected Symbol g2ClassName;
  protected boolean isG2EventObjectClass = false;
  protected boolean isG2ProxyObjectClass = false;
  protected boolean isSystemClass;
  Symbol realG2ClassForG2ProxyClass = null;
  protected ClassNameMapper nameMapper;

  // History of methods signatures exported
  protected Sequence opSignatures = new Sequence(101); 

  protected static final int PROPERTY_GETTER = 1, PROPERTY_SETTER = 2, PROPERTY_STATIC = 4;
  protected static final Symbol HAND_CODED_METHODS_  = Symbol.intern ("HAND-CODED-METHODS");

  protected ClassGenerationContext (OutputStream out,
				    boolean isInterface,
				    String packageName,
				    String className,
				    ClassNameMapper nameMapper) {
    this(out, isInterface, packageName, className,
	 G2ClassTranslator.createJavaClassNameFromG2ClassName (Symbol.intern(className)),
	 nameMapper);
  }

  protected ClassGenerationContext (OutputStream out,
				    boolean isInterface,
				    String packageName,
				    String className,
				    String javaClassName,
				    ClassNameMapper nameMapper) {

    stream = out;
    this.isInterface = isInterface;
    this.packageName = packageName;
    this.className = className; // remove this ASAP
    this.nameMapper = nameMapper;
    g2ClassName = Symbol.intern (className);
    this.javaClassName = javaClassName;
    isSystemClass = com.gensym.classes.SystemPredicate.isSystemClass (g2ClassName);
    output = new PrintWriter (new OutputStreamWriter(stream, Charset.defaultCharset()), true);
  }

  void generateClass (final String[] imports, final String superClass,
		  final Symbol[] classesToCollect,
		  final String[] interfaces, final Symbol[] classInheritancePath,
		  final AttrInfo attributes,
		  final MethodInfo[] m,
		  final Hashtable overridesInhTable) {
      generateClass(imports, superClass, classesToCollect, interfaces, classInheritancePath, attributes, m, overridesInhTable, new java.util.Date());
  }

  void generateClass (final String[] imports, final String superClass,
		  final Symbol[] classesToCollect,
		  final String[] interfaces, final Symbol[] classInheritancePath,
		  final AttrInfo attributes,
		  final MethodInfo[] m,
		  final Hashtable overridesInhTable,
		  final java.util.Date date) {

    Symbol[] attrTypes  = attributes.attrTypes,
             attrNames  = attributes.attrNames,
             origNames  = attributes.origNames,
             defClasses = attributes.defClasses;
    boolean[] readable = attributes.readable,
              writable = attributes.writable,
              isStatic = attributes.staticP;
    G2Type[] typeDescrpns = attributes.typeSpecifications;


    if (isInterface) {
      if (StubClassLoader.isG2ClassG2EventClass(g2ClassName))
	isG2EventObjectClass = true;
    } else {
      // Implementations are flat, need to check if we inherit from the G2
      // Event base class
      if (StubClassLoader.isG2EventClass(g2ClassName, classInheritancePath))
	isG2EventObjectClass = true;    
    }
    
    isG2ProxyObjectClass = (
	(realG2ClassForG2ProxyClass = 
	   StubClassLoader.getRealG2ClassForG2ProxyClass(g2ClassName, classInheritancePath)
	  ) != null); 

    //System.out.println ("For G2 Class <" + g2ClassName + ">, class inheritancePath = " + classInheritancePath);
    ClassOverrides overrides = collectInheritedOverrides(overridesInhTable, classesToCollect);
    //System.out.println ("Overrides = " + overrides);
    String[] allImports = collectAllImports (imports, overrides);
    //System.out.println ("Collected imports = " + imports.length);
    generateHeader (allImports, superClass, interfaces, overrides, date);
    increaseIndent (2);
    generateFields (attributes, classInheritancePath, overrides);
    generateConstructors ();
    generatePropertyAccessors (attrTypes, attrNames, readable, writable, isStatic, overrides, typeDescrpns);
    generateEventMethods (overrides);
    //System.out.println ("About to call generateMethods");
    generateMethods (m, overridesInhTable, false); // all methods
    decreaseIndent (2);
    endClass ();
  }

  void generateG2EventListenerExternalInterface (final String[] imports, 
		  final String superClass, 
		  final String[] interfaces, 
		  final Symbol[] classInheritancePath,
		  final MethodInfo[] m,
		  final Hashtable overridesInhTable) {
      generateG2EventListenerExternalInterface(imports, superClass, interfaces, classInheritancePath, m, overridesInhTable, new java.util.Date());
  }

  void generateG2EventListenerExternalInterface (final String[] imports, 
		  final String superClass, 
		  final String[] interfaces, 
		  final Symbol[] classInheritancePath,
		  final MethodInfo[] m,
		  final Hashtable overridesInhTable,
		  final java.util.Date date) {

    //System.out.println ("For G2 Class <" + g2ClassName + ">, class inheritancePath = " + classInheritancePath);
    ClassOverrides overrides = collectInheritedOverrides(overridesInhTable, classInheritancePath);
    //System.out.println ("Overrides = " + overrides);
    String[] allImports = collectAllImports (imports, overrides);
    //System.out.println ("Collected imports = " + imports.length);
    generateHeader (allImports, superClass, interfaces, overrides, date);
    increaseIndent (2);
    //System.out.println ("About to call generateMethods");
    generateMethods (m, overridesInhTable, true); // Output methods for external EventListener class only
    decreaseIndent (2);
    endClass ();
  }



  private ClassOverrides collectInheritedOverrides (Hashtable overridesTable, Symbol[] classesToCollect) {

    ClassOverrides ov =  new ClassOverrides();

    for (int i=0; i<classesToCollect.length; i++) {
      Symbol classToCollect = classesToCollect[i];
      ClassOverrides ovInherited = (ClassOverrides) overridesTable.get (classToCollect);
      if (ovInherited != null)
	ov.concatenate (ovInherited);
    }
    return ov;
  }

  protected void endClass () {
    iprintln ("}");
  }

  protected void generateFields (AttrInfo attributes,
		       Symbol[] classInheritancePath,
		       ClassOverrides overrides) {
    String sym = createJavaSymbolVariableName (Symbol.intern (className));
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "genField");
    if (!isSystemClass)
      iprintln ("public static final Symbol " + sym + " = Symbol.intern (\"" +
		className + "\");");
    else
      iprintln ("public static final Symbol " + sym + " = com.gensym.util.symbol.G2ClassSymbols." +
		sym + ";");
    iprintln ("static final Symbol g2ClassName = " + sym + ";");
    iprint ("static final Symbol[] classInheritancePath = new Symbol[] {");
    for (int i=0; i<classInheritancePath.length; i++) {
      print (createJavaSymbolVariableName (classInheritancePath[i]));
      if (i != (classInheritancePath.length - 1))
	print (", ");
    }
    println ("};");
    println ();

    if (isG2ProxyObjectClass) {
      iprintln ("static final Symbol realG2ClassName " +" = Symbol.intern (\""
		+ realG2ClassForG2ProxyClass + "\");"); 
    } else {
      Symbol[] attrNames = attributes.attrNames;
      boolean[] staticP = attributes.staticP;
      for (int i=0; i<attrNames.length; i++) {
	if (staticP[i]) {
	  Symbol attrName = attrNames[i];
	  iprintln ("static final Symbol " + createJavaSymbolVariableName (attrName) +
		    " = Symbol.intern (\"" + attrName + "\");");
	}
      }
      println ();
      iprint ("static final Symbol[] staticAttributes = new Symbol[] {");
      for (int i=0; i<attrNames.length; i++) {
	if (staticP[i]) {
	  print (createJavaSymbolVariableName (attrNames[i]));
	  if (i != (attrNames.length - 1))
	    print (", ");
	}
      }
      println ("};");
    }
    println ();
  }

  protected void generateHeader (final String[] imports,
		  final String superClass,
		  final String[] interfaces,
		  final ClassOverrides overrides,
		  final java.util.Date date) {
    iprintln("/*");
    iprintln(" *  Copyright (c) " +"1998 " + G2ClassTranslator.companyName + ".");
    iprintln(" *  All Rights Reserved.");
    iprintln(" *");
    iprintln(" *      " + javaClassName + ".java");
		iprintln(" *");
		iprintln(" *   Description: Generated Interface file. Do not edit!");
		iprintln(" *");
		iprintln(" *        Author: Gensym Corp.");
		iprintln(" *");
		iprintln(" *       Version: " + nameMapper.getVersionForClass(null));
		iprintln(" *");
		iprintln(" *          Date: " + date);
		iprintln(" *");
		iprintln(" */\n\n");
      
    iprintln("package " + packageName +";\n");
      
    for (int i = 0; i < imports.length; i++) {
      if(imports[i] != null && !(imports[i]).equals(""))
	iprintln("import " + imports[i] + ";");
      else
	println();
    }
      
    println();
    String[] interfaceNames = interfaces;  
    iprint("public ");
    print (isInterface ? "interface " : "class ");
    print (javaClassName);
    if (!isInterface &&
	!"java.lang.Object".equals(superClass))
      print (" extends " + superClass);

    Sequence addnlInterfaces = overrides.getImplementedInterfaces ();
    int intfCount = addnlInterfaces.size ();
    if (isInterface && intfCount > 0) {
      String[] fullInterfaces;
      if (interfaceNames != null) {
	int origIntfCount = interfaceNames.length;
	fullInterfaces = new String[intfCount + origIntfCount];
	addnlInterfaces.copyInto (fullInterfaces);
	System.arraycopy (interfaceNames, 0, fullInterfaces, intfCount, origIntfCount);
      } else {
	fullInterfaces = new String[intfCount];
	addnlInterfaces.copyInto (fullInterfaces);
      }
      interfaceNames = fullInterfaces;
    }
      
    if (interfaceNames != null) {
      if ((interfaceNames != null) && (interfaceNames.length > 0))
	print (isInterface ? " extends " : " implements ");
      for (int i=0; i<interfaceNames.length; i++) {
	print (qualifyConditionally (interfaceNames[i]));
	if (i < interfaceNames.length - 1)
	  print (", ");
      }
    }

    // if this is the interface for the base class of G2 event class, 
    // it must implement The G2 Event Tag interface
    if (StubClassLoader.isG2ClassG2EventClass(g2ClassName) && isInterface) {
      if (interfaceNames != null && interfaceNames.length > 0)
	print(",");
      print(StubClassLoader.g2EventTagInterfaceName);
    } else if (isG2ProxyObjectClass) {
      // if this class inherits from the base class of G2 Proxy class,
      // it must implement the G2ProxyObject interface
      if (interfaceNames != null && interfaceNames.length > 0)
	print (",");
      print(StubClassLoader.g2ProxyTagInterfaceName);
    }

    println (" {");

    println();

  }

  protected void generateConstructors () {    
      
    println();
  }
    
  void generatePropertyAccessors (Symbol[] slotTypes, Symbol[] slotNames, boolean[] readable, boolean[] writable, boolean[] isStatic, ClassOverrides overrides, G2Type[] typeSpecifications) {
 
    if (isG2ProxyObjectClass){
    	return; // not needed in proxy class
    }

    String[] jSlotNames = new String[slotNames.length];
    String[] jSlotTypes = new String[slotNames.length];
    int[] generationFlags = new int[slotNames.length];
    for(int i = 0; i < slotNames.length; i++) {
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "genProp", i, slotNames[i], slotTypes[i]);
      jSlotNames[i] = getJavaPropertyNameForG2Slot (slotNames[i]);
      jSlotTypes[i] = getJavaTypeNameForG2Type(slotTypes[i]);
      //System.out.println ("Type of " + jSlotNames[i] + " = " + jSlotTypes[i] + " (ORIG: " + slotTypes[i] + ")");
      if (slotNames[i].equals (Symbol.intern ("TEXT"))) {
	//System.out.println (">>>> TEXT attribute : type = " + slotTypes[i]);
      }
      generationFlags[i] = (readable[i] ? PROPERTY_GETTER : 0) |
	(writable[i] ? PROPERTY_SETTER : 0) |
	(isStatic[i] ? PROPERTY_STATIC : 0);      
    }
       
    if (overrides != null)
      writeOverridenPropertyAccessors (overrides);

    if (!isInterface)
      generatePropertyAccessors (jSlotTypes, jSlotNames, slotNames, generationFlags, typeSpecifications);
    else
      generatePropertyAccessDeclarations (jSlotTypes, jSlotNames, slotNames, generationFlags, typeSpecifications);

  }

  void generatePropertyAccessors (String[] jSlotTypes,
				  String[] jSlotNames,
				  Symbol[] slotNames,
				  int[] generationFlags,
				  G2Type[] typeSpecifications) {
    throw new InternalError ("Should never call ClassGenerationContext::generatePropertyAccessors");
  }

  void generatePropertyAccessDeclarations (String[] types, String[] names, Symbol[] g2Names,
					   int[] generationFlags, G2Type[] typeSpecifications) {
    for(int i = 0; i < names.length; i++) {
      Symbol currentSlot_ = g2Names[i];
      String currentSlot = names[i];
      String currentType = types[i];
      boolean staticQ    = (generationFlags[i] & PROPERTY_STATIC) != 0;
      String fieldName   = G2ClassTranslator.initCap(makeFieldNameForSlot(currentSlot, staticQ));
      String slotVarName = ensureLegalJavaVariableName (currentSlot);
      boolean getterExists = (generationFlags[i] & PROPERTY_GETTER) != 0;
      boolean setterExists = (generationFlags[i] & PROPERTY_SETTER) != 0;
      G2Type type = typeSpecifications[i];
      if (fieldName.equals ("Text")) {
	getterExists = setterExists = true;
	currentType  = "java.lang.String";
      }
      if (getterExists) {
	String getterInterface = ("public " + currentType + " get" +
		   fieldName + "() throws G2AccessException;\n");
	Sequence intfSig = MethodInfo.getMethodSignatureAsSequence(getterInterface);
	if (!methodAlreadyDefined(intfSig)) {
	  iprintln ("/**");
	  iprintln (" * Generated Property Getter for attribute -- " + currentSlot_);
	  iprint   (" * @return the value of the " + currentSlot_ + " attribute of this ");
	  println  (staticQ ? "class" : "item");
	  iprintln (" * @exception G2AccessException if there are any communication problems");
	  iprintln (" *");
	  if (type != null) {
	    iprintln (" * Type Specification for " + currentSlot_ + " is : ");
	    iprint   (" * ");
	    type.pprint (output, 2); //Need to write HTML!
	    println ("");
	  } else
	    iprintln (" * Attribute " + currentSlot_ + " has no type");
	  iprintln (" *");
	  iprintln (" */");
	  iprintln(getterInterface);
	  recordOpInterfaceSignature(intfSig);
	}
      }

      if (setterExists) {
	 String setterInterface = ("public void set" + fieldName +
				    "(" + currentType + " " + slotVarName + ") throws G2AccessException;\n");
	Sequence intfSig = MethodInfo.getMethodSignatureAsSequence(setterInterface);
	if (!methodAlreadyDefined(intfSig)) {
	  iprintln ("/**");
	  iprintln (" * Generated Property Setter for attribute -- " + currentSlot_);
	  iprintln (" * @param " + slotVarName + " new value to conclude for " + currentSlot_);
	  iprintln (" * @exception G2AccessException if there are any communication problems");
	  iprintln (" *              or the value does not match with the type specification");
	  iprintln (" */");
	 
	  iprintln(setterInterface);
	  recordOpInterfaceSignature(intfSig);
	}
      }
    }
  }

  private static final String[] java_modifiers = {"public",
						  "private",
						  "protected",
						  "static",
						  "final",
						  "synchronized",
						  "volatile",
						  "transient",
						  "native",
						  "interface",
						  "abstract"
                                                  };

  private static String[] java_reserved_words = {
    "abstract", "boolean", "case", "catch", "char", "class", "const", "continue", "default", "do",
    "break", "byte", "double" , "else", "extents", "final", "finally", "float", "for" , "goto", 
    "if", "implemenents", "import", "instanceof", "int", "interface", "long", "native", 
    "new", "package", "private", "protected", "public", "return", "short", "static", 
    "super", "switch", "synchronized", "this", "throw", "throws", "transient", "try", 
    "void", "volatile", "while" };


  protected String ensureLegalJavaVariableName (String origName) {
    for (int i=0; i<java_reserved_words.length; i++)
      if (origName.equals (java_reserved_words[i]))
	return origName + "$";
    return origName;
  }

  protected String ensureLegalMethodName (String origName) {
    for (int i=0; i<java_reserved_words.length; i++)
      if (origName.equals (java_reserved_words[i]))
	return "_" + origName;
    return origName;
  }

  protected String makeFieldNameForSlot (final String slotName, final boolean staticQ) {
    if (staticQ){
      return slotName + "ForClass";
    }
    return slotName;
  }

  void writeOverridenPropertyAccessors (ClassOverrides overrides) {
    Enumeration e = overrides.getProperties ();
    while (e.hasMoreElements ()) {
      Symbol propName = (Symbol) e.nextElement ();
      String getterText = overrides.getGetterInterface (propName);
      String setterText = overrides.getSetterInterface (propName);
      boolean outputGetter = // Can do this better, vkp
	getterText != null && getterText.indexOf ("public") >= 0;
      boolean outputSetter =
	setterText != null && setterText.indexOf ("public") >= 0;
      if (outputGetter || outputSetter)
	iprintln ("/* Overriden Property - " + propName + " */");
      if (outputGetter) {
	String comments = overrides.getGetterComments (propName);
	if (comments == null)
	  comments = "/**  Property Getter for " + propName + " */";
	iprintln (comments);
	iprint   (getterText);
	recordOpInterfaceSignature(getterText);
	println (";");
      }
      if (outputSetter) {
	String comments = overrides.getSetterComments (propName);
	if (comments == null)
	  comments = "/**  Property Setter for " + propName + " */";
	iprintln (comments);
	iprint   (setterText);
	recordOpInterfaceSignature(setterText);
	println (";");
      }
      println ();
    }
  }


  /**
   * Generate the method interface for each exported G2 method stub and any overrides
   * for this class.
   * Rules of engagement:
   * If an override exists of the same signature as a G2 method stub, then G2 method stub
   * is not used...as the override can define additional throw clauses
   */
  void generateMethods (MethodInfo[] methodInfoArray, 
			Hashtable overridesTable, 
			boolean generateMethodsForExternalEventListenerClass) {

    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "enterGenMethod");

    // If this is an event interface, it must implement G2 Tag interface
    if (isG2EventObjectClass) {
      iprintln("/* " + StubClassLoader.g2EventTagInterfaceName + " support */");
      iprintln("public Class " + StubClassLoader.getExternalEventClassMethodName + "();");
      println();
    }

    if (!generateMethodsForExternalEventListenerClass) { // We ignore overrides in this case

      // Only interested in overrides for this class
      ClassOverrides overrides = (ClassOverrides)overridesTable.get(g2ClassName);

      if (overrides != null) {
	Enumeration e = overrides.getMethods (java.lang.reflect.Modifier.PUBLIC);
	while (e.hasMoreElements ()) {
	  Symbol methodName = (Symbol) e.nextElement ();
	  Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "genMeth", methodName);
	String ovrInterface = overrides.getMethodInterface (methodName);

	// Remember which interface we have written here
	Sequence ovrInterfaceSig = MethodInfo.getMethodSignatureAsSequence(ovrInterface);
	opSignatures.addElement(ovrInterfaceSig);

	iprintln ("/* Overriden method - " + methodName + " */");
	String methodComments = overrides.getMethodComments (methodName);
	if (methodComments != null)
	  iprintln (methodComments);
	iprint (ovrInterface);
	println (";");
	println ();
	}
      }

      // We dont include methods exported for Proxy classes
      if (isG2ProxyObjectClass) {
    	  return;
      }

      // Also interested in overrides HAND_CODED_METHODS exported from G2
      overrides = (ClassOverrides)overridesTable.get(HAND_CODED_METHODS_);

      if (overrides != null) {
	Enumeration e = overrides.getMethods (java.lang.reflect.Modifier.PUBLIC);
	while (e.hasMoreElements ()) {
	  Symbol methodName = (Symbol) e.nextElement ();
	  Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "genMeth", methodName);
	  String ovrInterface = overrides.getMethodInterface (methodName);

	  // Remember which interface we have written here
	  Sequence ovrInterfaceSig = MethodInfo.getMethodSignatureAsSequence(ovrInterface);
	  opSignatures.addElement(ovrInterfaceSig);

	  iprintln ("/* Exported Override method - " + methodName + " */");
	  iprint (ovrInterface);     
	  println (";");
	  println ();
	}
      }
    }

    // Make a list of Item methods names
    Sequence itemMethods = getItemMethodNames();
    
    if (methodInfoArray != null)
    for (int i =0; i<methodInfoArray.length; i++) {

      MethodInfo methodInfo = methodInfoArray[i];
      outputMethodInfoInterface(methodInfo, 
				itemMethods, 
				opSignatures, 
				false, 
				generateMethodsForExternalEventListenerClass );

      // If this method is a add/remove listener interface, we need to
      // add a secondary version that allows external listeners to add/remove themselves
      if (methodInfo.isAddListenerMethod() || methodInfo.isRemoveListenerMethod())
	outputMethodInfoInterface(methodInfo, 
				  itemMethods, 
				  opSignatures, 
				  true, // Switch on External interface add/remove
				  false);
    }
  }
    
  /**
   * @param generateExternalAddRemoveListenerInterface Define the first param of a Add/Remove Listener method
   *        to be an ExternalG2EventListener Class Name 
   * @param externalListenerInterface The Method in intended for an external G2 Listener interface
   *        and any G2 Events Class param types should be convered to External G2 Event Object classes
   */
  private void outputMethodInfoInterface(MethodInfo methodInfo,
					 Sequence itemMethods,
					 Sequence opSignatures, 
					 boolean generateExternalAddRemoveListenerInterface,
					 boolean externalListenerInterface) {

    boolean conflict = false;

    if (methodInfo.isActive()) {

      // No statics in an interface !
      if (!methodInfo.isStatic()) {
	String intf = methodInfo.generateMethodInterface(this,
							 generateExternalAddRemoveListenerInterface,
							 externalListenerInterface);

	// Check that this interface method does not conflict with any Item methods
	// as we dont allow G2 methods to override any methods defined by Item
	if (itemMethods.contains(methodInfo.getJavaMethodName()))
	  conflict = true;
	else {
	  // Check that we have not already sent this interface out
	  Sequence mInterfaceSig =  MethodInfo.getMethodSignatureAsSequence(intf);
	  for (Enumeration opsige = opSignatures.elements(); opsige.hasMoreElements();) {
	    if (mInterfaceSig.equals(opsige.nextElement())) {
	      conflict = true;
	      break;
	    }
	  }
	}

	if (!conflict) {
	  iprintMultiLineString(methodInfo.generateInterfaceComment());
	  iprint(intf);
	  println(";");
	  iprintln("");
	}
      }
    }
  }


  void generateEventMethods (ClassOverrides overrides) {
    Enumeration e = overrides.getEvents ();
    while (e.hasMoreElements ()) {
      Symbol eventName = (Symbol) e.nextElement ();
      String addIntf = overrides.getAddListenerInterface (eventName);
      String removeIntf = overrides.getRemoveListenerInterface (eventName);
      iprintln ("/* Overriden  - " + eventName + " Event Listeners Management */");
      if (addIntf != null && addIntf.indexOf ("public") >= 0) { // Can do this better
	iprintln ("/* Adder */");
	iprintln (overrides.getAddListenerComments (eventName));
	iprint   (addIntf);
	println (";");
	recordOpInterfaceSignature(addIntf);
      }
      if (removeIntf != null && removeIntf.indexOf ("public") >= 0) {
	iprintln ("/* Remover */");
	iprintln (overrides.getRemoveListenerComments (eventName));
	iprint   (removeIntf);
	println (";");
	recordOpInterfaceSignature(removeIntf);
      }
      println ();
    }
  }

  /**
   * Return a list of methods names defined in the base class and above.
   */
  protected Sequence getItemMethodNames() {
    //should really be doing a more sophisticated check that
    // ensures that no G2 method hides a method written in
    // Java (i.e., inherited from G2__BaseImpl or from
    // a special impl. Should worry about protected methods too,
    // not just public.
    java.lang.reflect.Method[] methods =
      StubClassLoader.BASE_JAVA_CLASS.getMethods();
    Sequence names = new Sequence(50);
    for (int i=0; i<methods.length; i++)
      names.addElement(methods[i].getName());
    return names;
  }

  /**
   * Record a method signature that has been output
   */
  protected final void recordOpInterfaceSignature(String intrface) {
    opSignatures.addElement(MethodInfo.getMethodSignatureAsSequence(intrface));
  }

  protected final void recordOpInterfaceSignature(Sequence intrface) {
    opSignatures.addElement(intrface);
  }

  protected boolean methodAlreadyDefined(Sequence mInterfaceSig) {
    for (Enumeration opsige = opSignatures.elements(); opsige.hasMoreElements();) {
      if (mInterfaceSig.equals(opsige.nextElement())) {
	return true;
      }
    }
    return false;
  }
    

  protected static final Symbol[] knownG2Types = new Symbol[] {ITEM_OR_VALUE_,
								 VALUE_,
								 SEQUENCE_,
								 STRUCTURE_,
								 TRUTH_VALUE_,
								 QUANTITY_,
								 INTEGER_,
								 FLOAT_,
								 TEXT_,
								 SYMBOL_,
								 TRUTH_VALUE_OR_NULL_,
								 INTEGER_OR_NULL_,
								 FLOAT_OR_NULL_};
  protected static final Class[] mappedJavaTypes  = new Class[] {java.lang.Object.class,
								   java.lang.Object.class,
								   com.gensym.util.Sequence.class,
								   com.gensym.util.Structure.class,
								   Boolean.TYPE,
								   java.lang.Number.class,
								   Integer.TYPE,
								   Double.TYPE,
								   java.lang.String.class,
								   com.gensym.util.Symbol.class,
								   Boolean.class,
								   Integer.class,
								   Double.class};
  
  protected String getJavaTypeNameForG2Type (Symbol g2TypeName_) {
    // Check against known mappings. This needs to be stored in a standard place
    for (int i=0; i<knownG2Types.length; i++)
      if (g2TypeName_.equals (knownG2Types[i]))
	return (mappedJavaTypes[i]).getName ();

    // Must be a class?
    // How to check whether user or system defined class?
    // BUG ?
    /* This will return a simple Java Type (not package qualified).
     * It works in both cases. If the class is a system-defined class
     * it will exist in the same package; if not, the system package
     * is always imported, so we are all set!
     */
    //return G2ClassTranslator.createJavaClassNameFromG2ClassName (g2TypeName_);

    /* Now that we are importing classes from multiple packages,
     * this is no longer enough. We need more specific package info
     */

    /*
     * The nameMapper may not know about our class, as we are generating if here
     */
    if (g2TypeName_.equals(g2ClassName))
      return packageName + "." + G2ClassTranslator.createJavaClassNameFromG2ClassName (Symbol.intern(className));

    return nameMapper.javaClassNameFromG2ClassName (g2TypeName_);
  }

  /**
   * Whether or not there is a definition corresponding to this type
   */
  static boolean typeHasClass (Symbol g2TypeName) {
    for (int i=0; i<knownG2Types.length; i++)
      if (g2TypeName.equals (knownG2Types[i]))
	return false;
    return true;
  }
      
  /**
   * Converts any '-' and '/'s in the symbol to '_' and adds a '_' at the end
   * Returns a syntactically valid and convention conformant variable name
   * for the symbol.
   */
  protected static String createJavaSymbolVariableName (Symbol g2AttrName) {
    String g2AttrNameStr = g2AttrName.getPrintValue ().toUpperCase ();
    StringBuffer javaSymVarName = new StringBuffer (g2AttrNameStr);
    String notallowedchars = "!@#%^&*()[].,<>+|=`~\"'\\-/";
    for (int i=0; i<g2AttrNameStr.length (); i++) {
      char c = g2AttrNameStr.charAt(i);
      if (notallowedchars.indexOf(c) > -1)
	javaSymVarName.setCharAt(i, '_');
      else if (c == '?')
	javaSymVarName.setCharAt(i, 'Q');
    }
    javaSymVarName.append ('_');
    if (javaSymVarName.length() > 0 && Character.isDigit(javaSymVarName.charAt(0)))
     javaSymVarName.insert(0, 'N');
    return javaSymVarName.toString ();
  }

  /**
   * Uses the standard slot name mangler but makes an exception for
   * the "Class" attribute since getClass is a non-overridable
   * method in Java
   */
  protected String getJavaPropertyNameForG2Slot (Symbol g2SlotName) {
    return (g2SlotName.equals (CLASS_) ? "G2ClassName" :
	    G2ClassTranslator.slotNameFromG2Slot(g2SlotName.getPrintValue ()));
  }

  private String[] collectAllImports (String[] imports, ClassOverrides overrides) {
    if (overrides == null)
      return imports;
    int newImportsCount = overrides.getImportsCount ();
    if (newImportsCount == 0)
      return imports;
    String[] fullImports = new String[imports.length + newImportsCount];
    System.arraycopy (imports, 0, fullImports, 0, imports.length);
    int i=imports.length;
    Enumeration e = overrides.getImports ();
    while (e.hasMoreElements ()) {
      Symbol importName = (Symbol) e.nextElement ();
      fullImports[i++] = overrides.getImportTypeOrPackage (importName);
    }
    //System.out.println ("Total # of imports = " + imports.length + " + " + newImportsCount);
    return fullImports;
  }

  /**
   * Hack to get around the shadowing of Object
   */
  protected String qualifyConditionally (String interfaceName) {
    return interfaceName;
  }


  private int indent = 0;
  private volatile String indentString = "";
  private String SPACES = "                ";

  protected void increaseIndent (int delta) {
    indent += delta;
    indentString = SPACES.substring (0, indent);
  }

  protected void decreaseIndent (int delta) {
    indent -= delta;
    if (indent < 0)
      indent = 0;
    indentString = SPACES.substring (0, indent);
  }

  void print (String x) {
    output.print (x);
  }

  void println (String x) {
    output.println (x);
  }

  void println () {
    output.println ();
  }

  void iprint (String x) {
    output.print (indentString);
    output.print (x);
  }

  void iprintln (String x) {
    iprint (x);
    output.println ();
  }


  void iprintMultiLineString (String x) {
    BufferedReader br = new BufferedReader (new StringReader (x));
    String line;
    try {
      while ((line = br.readLine ()) != null)
	iprintln (line);
    } catch (IOException ioe) {
      // Should never happen
      System.err.println (ioe);
    }
  }

}
