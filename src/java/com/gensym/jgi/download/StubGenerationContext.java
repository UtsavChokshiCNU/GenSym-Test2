
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

class StubGenerationContext extends ClassGenerationContext implements com.gensym.util.symbol.G2TypeSymbols {

  // Tracing stuff
  private static MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.jgi.download.stubs",
			   StubGenerationContext.class);
  private static Resource i18nTrace =
  Trace.getBundle("com.gensym.jgi.download.Messages", Locale.getDefault());
  private static final int DEF_TRACE_LEVEL = 5;
  private String javaClassInterfaceName;
  private static final int DEF_WARN_LEVEL  = 2;

  //Fields
  private String[] symVarNames;

  StubGenerationContext (OutputStream out,
			 boolean isInterface,
			 String packageName,
			 String className,
			 ClassNameMapper nameMapper) {
    super (out, isInterface, packageName, className, nameMapper);
    javaClassInterfaceName = javaClassName;
    javaClassName += "Impl";
  }

  StubGenerationContext (OutputStream out,
			 boolean isInterface,
			 String packageName,
			 String className,
			 String javaClassName,
			 ClassNameMapper nameMapper) {
    super (out, isInterface, packageName, className,
	   javaClassName, nameMapper);
  }


  @Override
  protected void generateHeader (String[] imports,
			      String superClass,
			      String[] interfaces,
			      ClassOverrides overrides,
			      java.util.Date date) {
    super.generateHeader (imports, superClass, interfaces, overrides, date);
  }

  @Override
  protected void generateFields (AttrInfo attributes,
		       Symbol[] classInheritancePath,
		       ClassOverrides overrides) {

    if (isG2ProxyObjectClass){
    	return; // not output for proxy classes
    }

    println ();
    // NOTE: this is for performance reasons in three-tier: we do not
    // support persistence of these generated classes.
    iprintln ("static final long serialVersionUID = 2L;");
    Symbol[] attrTypes = attributes.attrTypes, attrNames = attributes.attrNames,
      origNames = attributes.origNames, defClasses = attributes.defClasses;
    boolean[] staticQ = attributes.staticP;
    boolean[] systemDefined = attributes.systemDefined;
    // Symbol Declarations
    String symFieldModifiersAndType = "private static final Symbol ";
    symVarNames = createJavaSymbolVariableNames (systemDefined, attrNames, staticQ);
    Vector duplicates = determineDuplicateAttributeNames (origNames, defClasses, classInheritancePath, staticQ);
    Symbol origName;
    String internThis;
    for (int i=0; i<symVarNames.length; i++) {
      if (!systemDefined[i]) {
	String g2AttributeName =
	  getG2NameForAttribute (origNames[i], staticQ[i], defClasses[i], duplicates);
      /*
      System.out.println ("DUP: G2 name for attribute " + origNames[i] +
			  " defined at " + defClasses[i] +
			  "in class " + g2ClassName +
			  " = " + g2AttributeName);
			  */
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "genStubField", i, attrTypes[i], attrNames[i]);
	iprintln (symFieldModifiersAndType + symVarNames[i] + " = " +
		  javaCodeForInterningSymbol (systemDefined[i], attrNames[i], g2AttributeName) + ";");
      }
    }
    println ();
    generateOverridenFields (overrides);
  }

    static class AttrClassPair {
    Symbol attributeName;
    Symbol definingClass;
    boolean isStatic;

    AttrClassPair (Symbol attributeName, Symbol definingClass, boolean isStatic) {
      this.attributeName = attributeName;
      this.definingClass = definingClass;
      this.isStatic      = isStatic;
    }
  }

  private Vector determineDuplicateAttributeNames (Symbol[] origNames,
						   Symbol[] defClasses,
						   Symbol[] classInheritancePath,
						   boolean[] staticQ) {
    Vector duplicates = new Vector ();
    for (int i=0; i<origNames.length; i++) {
      Symbol attrName = origNames[i];
      boolean isStatic = staticQ[i];
      AttrClassPair duplAttrInfo = null;
      //System.out.println ("DUP?: Checking " + origNames[i] + " at class " + defClasses[i]);
      if (mostSpecificClassDefiningDuplicateAttribute (attrName, isStatic, duplicates) == null) {
	//System.out.println ("DUP?: Really Checking " + origNames[i] + " at class " + defClasses[i]);
	for (int j=i+1; j<origNames.length; j++)
	  if (attrName.equals (origNames[j]) && (isStatic == staticQ[j])) {
	    duplAttrInfo = new AttrClassPair (attrName, defClasses[i], isStatic);
	    //System.out.println ("DUP: While generating stub for " + g2ClassName + ", found duplicate attribute name = " + attrName + " at class " + defClasses[j]);
	  }
	if (duplAttrInfo != null)
	  duplicates.addElement (duplAttrInfo);
      }
    }
    return duplicates;
  }

  private Symbol mostSpecificClassDefiningDuplicateAttribute (Symbol attrName,
							      boolean isStatic,
							      Vector duplicates) {
    Enumeration e = duplicates.elements ();
    while (e.hasMoreElements ()) {
      AttrClassPair duplAttrInfo = (AttrClassPair)e.nextElement ();
      if (duplAttrInfo.attributeName.equals (attrName) && (duplAttrInfo.isStatic == isStatic))
	return duplAttrInfo.definingClass;
    }
    return null;
  }

  private String getG2NameForAttribute (Symbol origName, boolean isStatic, Symbol definingClass, Vector duplicateNames) {
    Symbol classOfDuplAttr = mostSpecificClassDefiningDuplicateAttribute (origName, isStatic, duplicateNames);
    /*
    System.out.println ("getG2NameForAttribute (" + origName + ", " + definingClass + ")" +
			" duplClass = " + classOfDuplAttr);
			*/
    if (classOfDuplAttr == null ||
	definingClass.equals (classOfDuplAttr))
      return origName.getPrintValue ();
    else
      return definingClass.getPrintValue () + "::" + origName.getPrintValue ();
  }

  private String javaCodeForInterningSymbol (boolean isSystemDefined, Symbol attrName, String sym) {
    if (isSystemDefined)
      return "SystemAttributeSymbols." + createJavaSymbolVariableName (attrName);
    else
      return "Symbol.intern (\"" + sym + "\")";
  }

  @Override
  protected void generateConstructors () {
    iprintln ("/* Generated constructors */");
    println();

    iprintln ("public " + javaClassName + "() {");
    increaseIndent(2);
    iprintln("super();");
    decreaseIndent(2);
    iprintln("}");
    println();

    /*
    iprintln ("public " + javaClassName + "(Structure attributes) {");
    increaseIndent(2);
    iprintln("super(attributes);"); 
    iprintln("// Add the classname, so its all setup to send back to G2");
    iprintln("try { ");
    increaseIndent(2);
    iprintln("setAttributeValue(CLASS_," + javaClassInterfaceName + ".g2ClassName);");
    decreaseIndent(2);
    iprintln("}");
    iprintln("catch (G2AccessException e) {}");
    decreaseIndent(2);
    iprintln("}");
    println();
    */

    iprintln ("public " + javaClassName + "(G2Access context, int handle, Structure attributes) {");
    increaseIndent (2);
    iprintln ("super (context, handle, attributes);");
    decreaseIndent (2);
    iprintln ("}");
    println ();
    println ();

    iprintln ("public " + javaClassName + "(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {");
    increaseIndent (2);
    iprintln ("super (context, handle, handleVersion, wrap, attributes);");
    decreaseIndent (2);
    iprintln ("}");
    println ();
    println ();
  }

  private String[] createJavaSymbolVariableNames (boolean[] systemDefined, Symbol[] attrNames, boolean[] staticQ) {
    int numAttributes = attrNames.length;
    String[] javaSymbolVarNames = new String[numAttributes];
    for (int i=0; i<numAttributes; i++) {
      if (systemDefined[i]) {
	javaSymbolVarNames[i] = "SystemAttributeSymbols." + createJavaSymbolVariableName (attrNames[i]);
      } else {
      javaSymbolVarNames[i] = createJavaSymbolVariableName (attrNames[i]);
      if (staticQ[i])
	javaSymbolVarNames[i] += "FOR_CLASS_";
      }
    }
    return javaSymbolVarNames;
  }

  @Override
  void generatePropertyAccessors (String[] jSlotTypes,
				  String[] jSlotNames,
				  Symbol[] slotNames,
				  int[] generationFlags,
				  G2Type[] typeSpecifications){ 
    for(int i = 0; i < jSlotNames.length; i++) {
      Symbol currentSlot_= slotNames[i];
      String currentSlot = jSlotNames[i];
      String currentType = jSlotTypes[i];
      boolean staticField = ((generationFlags[i] & PROPERTY_STATIC) != 0);
      String fieldName   = G2ClassTranslator.initCap(makeFieldNameForSlot (currentSlot, staticField));
      String slotVarName = ensureLegalJavaVariableName (currentSlot);
      boolean getterExists = (generationFlags[i] & PROPERTY_GETTER) != 0;
      boolean setterExists = (generationFlags[i] & PROPERTY_SETTER) != 0;
      if (fieldName.equals ("Text")) {
	getterExists = setterExists = true;
	currentType  = "java.lang.String";
      }
      if (setterExists) {
	String setterInterface = ("public void set" + fieldName +
			"(" + currentType + " " + slotVarName + ") throws G2AccessException {");
	Sequence intfSig = MethodInfo.getMethodSignatureAsSequence(setterInterface);
	if (!methodAlreadyDefined(intfSig)) {
	  iprintln ("/**");
	  iprintln (" * Generated Property Setter for attribute -- " + currentSlot_);
	  iprintln (" * @param " + slotVarName + " new value to conclude for " + currentSlot_);
	  iprintln (" * @exception G2AccessException if there are any communication problems");
	  iprintln (" *              or the value does not match with the type specification");
	  iprintln (" */");

	  iprintln(setterInterface);
	  recordOpInterfaceSignature(setterInterface);
	  increaseIndent (2);
	  generateSetBody (output, currentType, slotVarName, symVarNames[i], staticField);
	  decreaseIndent (2);
	  iprintln ("}");
	  println();
	}
      }

      if (getterExists) {
	String getterInterface = ("public " + currentType + " get" +
		  fieldName + "() throws G2AccessException {");
	Sequence intfSig = MethodInfo.getMethodSignatureAsSequence(getterInterface);
	if (!methodAlreadyDefined(intfSig)) {
	  iprintln ("/**");
	  iprintln (" * Generated Property Getter for attribute -- " + currentSlot_);
	  iprint   (" * @return the value of the " + currentSlot_ + " attribute of this ");
	  println  (staticField ? "class" : "item");
	  iprintln (" * @exception G2AccessException if there are any communication problems");
	  iprintln (" */");
	  iprintln(getterInterface);
	  recordOpInterfaceSignature(getterInterface);
	  increaseIndent (2);
	  generateGetBody (output, currentType, slotVarName, symVarNames[i], staticField);
	  decreaseIndent (2);
	  iprintln ("}");
	  println();
	}
      }
    }
  }

  @Override
  void writeOverridenPropertyAccessors (ClassOverrides overrides) {
    Enumeration e = overrides.getProperties ();
    while (e.hasMoreElements ()) {
      Symbol propName = (Symbol) e.nextElement ();
      String getterSign = overrides.getGetterInterface (propName);
      String setterSign = overrides.getSetterInterface (propName);
      String getterText = overrides.getGetterImplementation (propName);
      String setterText = overrides.getSetterImplementation (propName);
      iprintln ("/* Overriden Property - " + propName + " */");
      if (getterSign != null) {
	String comments = overrides.getGetterComments (propName);
	if (comments == null)
	  comments = "/**  Property Getter for " + propName + " */";
	iprintln (comments);
	iprint (getterSign);
	println (" {");
	increaseIndent (2);
	iprintMultiLineString (getterText);
	decreaseIndent (2);
	iprintln ("}");
	recordOpInterfaceSignature(getterSign);
      }
      println ();
      if (setterSign != null) {
	String comments = overrides.getSetterComments (propName);
	if (comments == null)
	  comments = "/**  Property Setter for " + propName + " */";
	iprintln (comments);
	iprint (setterSign);
	iprintln (" {");
	increaseIndent (2);
	iprintMultiLineString (setterText);
	decreaseIndent (2);
	iprintln ("}");
	recordOpInterfaceSignature(setterSign);
      }
      println ();
    }
  }

  private static final String instVarSetter = "setAttributeValue",
			      classVarSetter = "setStaticAttributeValue";

  void generateSetBody (PrintWriter output,
			       String currentType,
			       String slotVarName,
			       String symVarName,
			       boolean staticField) {
    String setterFn = (staticField ? classVarSetter : instVarSetter);
    String extraArgs = (staticField ? ", classPropertyKeys, classPropertyValues" : "");
    extraArgs = "";
    iprintln (setterFn + " (" + symVarName + ", " + 
	      codeToMakeObject (slotVarName, currentType) + extraArgs + ");");
  }

  // This should go somewhere generic
  static String codeToMakeObject (String varName, String type) {
    if (type.equals ("int"))
      return "new Integer (" + varName + ")";
    else if (type.equals ("double"))
      return "new Double (" + varName + ")";
    if (type.equals ("boolean"))
      return "new Boolean (" + varName + ")";
    else
      return varName;
  }

  private static final String instVarGetter = "getAttributeValue",
			      classVarGetter = "getStaticAttributeValue",
                              textVarGetter = "getAttributeTextValue";

  void generateGetBody (PrintWriter output,
			String currentType,
			String slotVarName,
			String symVarName,
			boolean staticField) {
    String getterFn = (staticField ? classVarGetter : instVarGetter);
    String extraArgs = (staticField ? ", classPropertyKeys, classPropertyValues" : "");
    extraArgs = "";
    iprintln ("java.lang.Object retnValue = " + getterFn + " (" + symVarName + extraArgs + ");");
    iprintln ("return " + codeToGetPrimitiveValueOrCastReturnObject ("retnValue", currentType) + ";");
  }

  static String codeToGetPrimitiveValueOrCastReturnObject (String varName, String type) {
    if (type.equals ("int"))
      return "((Integer)" + varName + ").intValue ()";
    else if (type.equals ("double"))
      return "((Double)" + varName + ").doubleValue ()";
    else if (type.equals ("boolean"))
      return "((Boolean)" + varName + ").booleanValue ()";
    else
      return "(" + type + ")" + varName;
  }

  static final int SIG_POS = 0;
  static final int INT_POS = 1;
  static final int IMP_POS = 2;

  /**
   * Generate the method code for each method read from G2 for this class and
   * its inherited classes.
   * We also include any overide methods from the classes hierarchy.
   * If any override methods match up with G2 generated methods, then
   * the method source for the ovveride is used.
   */
  @Override
  void generateMethods (final MethodInfo methodInfoArray[],
			final Hashtable overridesTable, 
			final boolean onlyEventMethods) {


    // If this is an event class, it will implement G2 Event Tag interface
    if (isG2EventObjectClass) {
      iprintln("/* " + StubClassLoader.g2EventTagInterfaceName + " support */");
      iprintln("public Class " + StubClassLoader.getExternalEventClassMethodName + "() {");
      increaseIndent(2);
      iprintln("return " + 
	       packageName + "." + 
	       StubClassLoader.getExternalG2EventClassName(javaClassInterfaceName) +
	       ".class;");
      decreaseIndent(2);
      iprintln("}");
      println();
    }
    
    MethodInfo[] methodInfos = methodInfoArray; 
    if (methodInfos == null) {
    	methodInfos = new MethodInfo[0];
    }
			
    // Symbol Declarations for methodNames

    Hashtable decTable = new Hashtable(201);
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "genStubMethod", methodInfos.length);
    //iprintln ("/* Overridden methods in Stub! */\n");

    boolean titleSent = false;
    for (int i = 0; i<methodInfos.length; i++) {

      MethodInfo mi = methodInfos[i];
      if (mi.isActive()) {

	if (!titleSent) { 
		iprintln("// Method Name Constants");	
		titleSent = true; 
	}
	String decName = (mi.generateRPCDeclarationName()).intern();
	// Check to ensure that the symbol is not already defined
	if (decTable.get(decName) == null) {
	  iprintln(mi.generateRPCDeclarartion());
	  decTable.put(decName, this); 
	  // insert a dummy, we just want to remember that we have got this symbol
	}
      }
      
    }
    
    iprintln(MethodInfo.generateImplementationDeclarations());
    iprintln("");

    // Output any overrides for this class
    ClassOverrides overrides = (ClassOverrides)overridesTable.get(g2ClassName);
    Sequence ovrInterfaceSig;
    String ovrInterface;

    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "genOvrdMeth", overrides);
    if (overrides != null) {
      Enumeration e = overrides.getMethods ();
      while (e.hasMoreElements ()) {
	Symbol methodName = (Symbol) e.nextElement ();
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "genMeth", methodName);
		ovrInterface = overrides.getMethodInterface (methodName);

	// Remember which interface we have written here
	ovrInterfaceSig = MethodInfo.getMethodSignatureAsSequence(ovrInterface);
	opSignatures.addElement(ovrInterfaceSig);

	iprintln ("/* Overriden method - " + methodName + " */");
	iprintln (ovrInterface);
	println (" {");
	increaseIndent (2);
	iprintMultiLineString (overrides.getMethodImplementation (methodName));
	decreaseIndent (2);
	iprintln ("}");
	println ();
      }
    }

    boolean conflict = false;
    // Now output any overrides for any superior class
    // But as the implementation is flat, mangle the name of there is a match
    Sequence inhOpSignatures = new Sequence(50);

    for (Enumeration ovrClassEnum = overridesTable.keys(); ovrClassEnum.hasMoreElements();) {
      Symbol inhClass = (Symbol)ovrClassEnum.nextElement();
      overrides = (ClassOverrides)overridesTable.get(inhClass);

      // Ignore current class and hand coded methods from G2 (see later)
      if (!HAND_CODED_METHODS_.equals(inhClass) &&  !inhClass.equals(g2ClassName) && overrides != null) {
	Enumeration e = overrides.getMethods ();
	while (e.hasMoreElements ()) {
	  Symbol methodName = (Symbol) e.nextElement ();
	  Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "genMeth", methodName);
	  ovrInterface = overrides.getMethodInterface (methodName);
	  conflict = false;

	  // Check that we have not already sent this interface out
	  ovrInterfaceSig = MethodInfo.getMethodSignatureAsSequence(ovrInterface);
	  for (Enumeration opsige = opSignatures.elements(); opsige.hasMoreElements();) {
	    if (ovrInterfaceSig.equals(opsige.nextElement())) {
	      Trace.send (DEF_WARN_LEVEL, traceKey, i18nTrace, "ovrConflict", ovrInterfaceSig);
	      //System.out.println ("not writing method " + methodName + " with class1 = " + g2ClassName + " class2 = " + inhClass);
	      conflict = true;
	      break;
	    }
	  }


	  // This bit TBD....
	  if (conflict) 
	    { //mangle name...TBD
	    }

	  // Remember which interface we have written here

	  // inhOpSignatures.addElement(ovrInterfaceSig);
	  if (!conflict) {
	    iprintln ("/* Overriden method - " + methodName + " */");
	    iprintln (ovrInterface);
	    println (" {");
	    increaseIndent (2);
	    iprintMultiLineString (overrides.getMethodImplementation (methodName));
	    decreaseIndent (2);
	    iprintln ("}");
	    println ();
	    opSignatures.addElement (ovrInterfaceSig);
	  }
	}
      }
    }

    // Concat all override signatures together
    opSignatures.concatenate(inhOpSignatures);


    // Get all the handcoded methods, for later use
    overrides = (ClassOverrides)overridesTable.get(HAND_CODED_METHODS_);
    
    Sequence hcInfoSeq = new Sequence(50);


    if (overrides != null) {
      Enumeration e = overrides.getMethods ();
      while (e.hasMoreElements ()) {

	Symbol methodName = (Symbol) e.nextElement ();
	ovrInterface = overrides.getMethodInterface (methodName);
	ovrInterfaceSig = MethodInfo.getMethodSignatureAsSequence(ovrInterface);

	Object[] info = new Object[] {ovrInterfaceSig, 
				    ovrInterface,
				    overrides.getMethodImplementation (methodName)};
	hcInfoSeq.addElement(info);

      }
    }

    // No exported methods for Proxy classes
    if (isG2ProxyObjectClass){
    	return;
    }
    
    Sequence hcInfoSeqCopy = (Sequence)hcInfoSeq.clone();   // we will be removing items, inside an Enumeration

    // Make a list of Item methods names
    Sequence itemMethods = getItemMethodNames();

    // Output generated G2 method stubs
    iprintln("");
    for (int i =0; i<methodInfos.length; i++) {

      if (i == 0){
    	  iprintln("//Generated Methods \n");
      }

      MethodInfo mi = methodInfos[i];
        outputMethodInfoImplementation(mi,
				       itemMethods,
				       opSignatures,
				       hcInfoSeq,
				       hcInfoSeqCopy,
				       false);

	// If this method is a add/remove listener interface, we need to
	// add a secondary version that allows external listeners to add/remove themselves
	if (mi.isAddListenerMethod() || mi.isRemoveListenerMethod())
	  outputMethodInfoImplementation(mi,
					 itemMethods,
					 opSignatures,
					 hcInfoSeq,
					 hcInfoSeqCopy, 
					 true);
    }
    


    
    // Finally Output any Exported code that has not been inserted into a stub
    // as long as it does conflict with an override

    int i = 0;

    Enumeration e = hcInfoSeq.elements();
    while (e.hasMoreElements ()) {

	
      if (i == 0)
	iprintln("// G2 Exported Overrides");

      Object[] info = (Object[])e.nextElement();
      Sequence eSigSeq = (Sequence)info[SIG_POS];

      // Check that we have not already sent this interface out
      
      for (Enumeration opsige = opSignatures.elements(); opsige.hasMoreElements();) {
	if (eSigSeq.equals(opsige.nextElement())) {
	  conflict = true;
	  break;
	}
      }
      if (!conflict) {
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "genMeth", eSigSeq.toString());
	iprintln((String)info[INT_POS]);
	iprintln("{");
	increaseIndent(2);
	iprintMultiLineString((String)info[IMP_POS]);
	decreaseIndent(2);
	iprintln("}");
	iprintln("");
	i++;
      }

    }

  }
    

  private void outputMethodInfoImplementation(MethodInfo mi,
					 Sequence itemMethods,
					 Sequence opSignatures, 
					 Sequence hcInfoSeq,
					 Sequence hcInfoSeqCopy,
					 boolean generateExternalAddRemoveListenerInterface) {
    boolean conflict;

    if (mi.isActive()) {
	
      String intf = mi.generateMethodInterface(this, generateExternalAddRemoveListenerInterface, false);
      Sequence mInterfaceSig = MethodInfo.getMethodSignatureAsSequence(intf);

      conflict = false;

      // Check that this interface method does not conflict with any Item methods
      // as we dont allow G2 methods to override any methods defined by Item
      if (itemMethods.contains(mi.getJavaMethodName()))
	conflict = true;
      else {
	// Check that we have not already sent this interface out
	for (Enumeration opsige = opSignatures.elements(); opsige.hasMoreElements();) {
	  if (mInterfaceSig.equals(opsige.nextElement())) {
	    conflict = true;
	    break;
	  }
	}
      }
      if (!conflict) {
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "genMeth", mi.G2MethodName.toString());
	// Header
	iprintMultiLineString(mi.generateInterfaceComment());
	// Interface
	iprintln(intf);
	// Implementation
	// First check that there is no exported code that we should as
	// replacement code
	boolean gotImplementation = false;
	for (Enumeration e = hcInfoSeqCopy.elements(); e.hasMoreElements();) {
	  Object[] info = (Object[])e.nextElement();
	  Sequence exSig = (Sequence)info[SIG_POS];
	  if (mInterfaceSig.equals(exSig)) {
	    // use exported implementation, rather than default
	    mi.generateMethodImplementation(this, 
					    (String)info[IMP_POS], 
					    generateExternalAddRemoveListenerInterface);
	    gotImplementation = true;
	    // Dont export this as an override
	    hcInfoSeq.removeElement(info);
	    break;
	  }
	}

	if (!gotImplementation) {
		mi.generateMethodImplementation(this, 
								"", 
								generateExternalAddRemoveListenerInterface);
	}
	iprintln("");
      }
	
    }
  }

  @Override
  void generateEventMethods (ClassOverrides overrides) {
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "genEvtMeth", overrides);
    Enumeration e = overrides.getEvents ();
    while (e.hasMoreElements ()) {
      Symbol eventName = (Symbol) e.nextElement ();
      String addIntf = overrides.getAddListenerInterface (eventName);
      String addImpl = overrides.getAddListenerImplementation (eventName);
      String removeIntf = overrides.getRemoveListenerInterface (eventName);
      String removeImpl = overrides.getRemoveListenerImplementation (eventName);
      iprintln ("/* Overriden  - " + eventName + " Event Listener - Adder1 */");
      if (addIntf != null) {
	iprint (addIntf);
	recordOpInterfaceSignature(addIntf);
	println (" {");
	increaseIndent (2);
	iprintMultiLineString (addImpl);
	decreaseIndent (2);
	iprintln ("}");
      }
      println ();
      iprintln ("/* Overriden  - " + eventName + " Event Listener - Remover1 */");
      if (removeIntf != null) {
	iprint (removeIntf);
	recordOpInterfaceSignature(removeIntf);
	iprintln (" {");
	increaseIndent (2);
	iprintMultiLineString (removeImpl);
	decreaseIndent (2);
	iprintln ("}");
      }
      println ();
    }
  }


  void generateOverridenFields (ClassOverrides overrides) {
    Enumeration e = overrides.getFields ();
    while (e.hasMoreElements ()) {
      Symbol fieldName = (Symbol) e.nextElement ();
      iprintln ("/* Overriden Field */");
      iprint (overrides.getFieldDeclaration (fieldName));
      String initValue = overrides.getFieldInitialValue (fieldName);
      if (initValue != null && !initValue.equals (""))
	print (" = " + initValue);
      println (";");
    }
  }

  String getPackageName() {
    return packageName;
  }

}

    
