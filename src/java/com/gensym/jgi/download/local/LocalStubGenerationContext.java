
package com.gensym.jgi.download.local;

import java.io.*;
import java.util.Locale;
import java.util.Enumeration;
import java.util.Vector;
import java.util.Hashtable;
import com.gensym.types.G2Type;
import com.gensym.g2script.Compiler;
import com.gensym.g2script.ClassInfoFactory;
import com.gensym.util.*;
import com.gensym.jgi.download.*;

import com.gensym.message.Trace;
import com.gensym.message.Resource;
import com.gensym.message.MessageKey;
import com.gensym.classtools.*;

public class LocalStubGenerationContext extends LocalClassGenerationContext 
implements com.gensym.util.symbol.G2TypeSymbols, com.gensym.util.ClassConstants {

  // Tracing stuff
  static private MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.jgi.download.stubs",
			   LocalStubGenerationContext.class);
  static private Resource i18nTrace =
  Trace.getBundle("com.gensym.jgi.download.Messages", Locale.getDefault());
  private static final int DEF_TRACE_LEVEL = 5;
  protected String javaClassInterfaceName;
  private static final int DEF_WARN_LEVEL  = 2;

  private boolean debug = false;
  private Vector compilerErrorReports = new Vector();

  private static final String INIT_METHOD = "initializeFields";
  private static final String GET_IMPLEMENTED_INTERFACE_METHOD = "getImplementedInterface";
  private static final String REGISTER_CLASS_METHODS_METHOD = "registerClassMethods";
  private static final String CONVERT_G2_ATTRIBUTE_FOR_LOCAL_METHOD = "_convertG2AttributeForLocal";
  private static final String CONVERT_G2_ATTRIBUTE_FOR_LOCAL_DESCR = 
                                 "(Lcom/gensym/util/Structure;Lcom/gensym/util/Symbol;)Ljava/lang/Object;";
  private static final String CONVERT_LOCAL_ATTRIBUTE_FOR_G2_METHOD = "_convertLocalAttributeForG2";
  private static final String CONVERT_LOCAL_ATTRIBUTE_FOR_G2_DESCR =
                           "(Lcom/gensym/util/Structure;Lcom/gensym/util/Symbol;Ljava/lang/Object;)V";
  private static final String UPDATE_LOCAL_ATTRIBUTES_FROM_G2_METHOD = "_updateLocalAttributesFromG2";
  private static final String UPDATE_LOCAL_ATTRIBUTES_FROM_G2_DESCR = "(Lcom/gensym/util/Structure;)V";
  private static final String UPDATE_G2_ATTRIBUTES_FROM_LOCAL_METHOD = "_updateG2AttributesFromLocal";
  private static final String UPDATE_G2_ATTRIBUTES_FROM_LOCAL_DESCR = UPDATE_LOCAL_ATTRIBUTES_FROM_G2_DESCR;

  private Vector fieldInits = new Vector();

  private static final String
      PROXY_ACCESS_CLASS_NAME = "com/gensym/fida/ObjectProxy",
      PROXY_ACCESS_CLASS_DESC = "L" + PROXY_ACCESS_CLASS_NAME + ";",
      PROXY_VARIABLE_NAME  = "remoteProxy";


  //Fields
  private String[] symVarNames;
  private Compiler compiler;
  private ClassInfoFactory factory;
  private boolean useRuntimeManager = true;
  protected boolean insertRemoteProxyCode = true;
  protected boolean addSlotFields = true;

  LocalStubGenerationContext (OutputStream out,
			      boolean isInterface,
			      String packageName,
			      String className,
			      String version,
			      String stubExtension,
			      LocalClassNameMapper nameMapper,
			      Compiler compiler,
			      ClassInfoFactory factory) {
    super (out, isInterface, packageName, className, nameMapper);
    javaClassInterfaceName = javaClassName;
    javaClassName += stubExtension+version;
    this.compiler = compiler;
    this.factory = factory;
  }

 /** Generates the '.class' file for the required class.
  **/
  void generateLocalClassImpl (String[] imports, 
			       String superClass,
			       Symbol[] classesToCollect,
		      String[] interfaces, 
		      Symbol[] classInheritancePath,
		      AttrInfo attributes,
		      AttrInfo inheritedAttributeInitializations,
		      com.gensym.jgi.download.MethodInfo[] m) 
       throws G2ClassCompilerException {

    cacheInheritedAttributeInitializations(inheritedAttributeInitializations);

    generateClass(imports,
		  superClass,
		  classesToCollect,
		  interfaces,
		  classInheritancePath,
		  attributes,
		  m);
      
    checkForCompilerErrors();
  }

  void generateClass(String[] imports, 
		       String superClass,
		       Symbol[] classesToCollect,
		       String[] interfaces, 
		       Symbol[] classInheritancePath,
		       AttrInfo attributes,
		       com.gensym.jgi.download.MethodInfo[] m) {
    
    super.generateClass(imports,
		  superClass,
		  interfaces,
		  classInheritancePath,
		  attributes,
		  m,
		  null);
  }

  @Override
  protected void endClass () {
    if (debug) 
      System.out.println("LSGC:  Generating field inits."); // DEBUG
    try {
      // create the INIT_METHOD method
      Block methodBody = new Block();
      if (addSlotFields) {
	for (Enumeration e = fieldInits.elements(); e.hasMoreElements();) {
	  FieldInitialisation f = (FieldInitialisation) e.nextElement();
	  if (debug)
	    System.out.println("Field: " + f.fieldName + " type " + 
			       f.fieldType + "init " + f.initialValue); // DEBUG
	  FieldRef field = new FieldRef(cfg.getClassName(),
					f.fieldName,
					cfg.getVMDescriptorForJavaType(f.fieldType));
	  Expression assignValue = new OperatorCall("=", new Expression[] {field, f.initialValue});
	  methodBody.add(assignValue);
	}
      }
      methodBody.add(new Return());
      cfg.addMethod(INIT_METHOD,
		    "()V",
		    new String[] {},
		    PRIVATE_ACCESS,
		    methodBody,
		    new ClassRef[] {});

      //Create getImplementedInterface method
      Block getMethodBody = new Block();
      MethodRef forNameMethod = new MethodRef("java.lang.Class",
					      "forName",
					      "(Ljava/lang/String;)Ljava/lang/Class;");
      MethodCall invokeForName = new MethodCall(forNameMethod, 
						new Expression[] {new Value(packageName + 
									    "." + javaClassInterfaceName)},
						MethodCall.MTH_CALL_STATIC);
      getMethodBody.add(new Return(invokeForName));
      cfg.addMethod(GET_IMPLEMENTED_INTERFACE_METHOD,
		    "()Ljava/lang/Class;",
		    new String[] {},
		    PUBLIC_ACCESS,
		    getMethodBody,
		    new ClassRef[] {});
		    
      
      //Create registerClassMethods
      // public void registerClassMethods() {
      //   super.registerClassMethods();
      //   G2__BaseImpl.registerClassMethodSignatures(getClass(),
      //                                              ...methodNames,
      //                                              ...methodSignatures);
      // }
      Block registerMethodBody = new Block();
      MethodRef superMethod = new MethodRef(cfg.getSuperClassName(),
					   REGISTER_CLASS_METHODS_METHOD ,
					    "()V");
      MethodCall invokeSuperMethod = new MethodCall(superMethod,
						    new Expression[] {},
						    MethodCall.MTH_CALL_SPECIAL);
      registerMethodBody.add(invokeSuperMethod);
      MethodRef registerSigsMethod = new MethodRef(G2__BASEIMPL_CLASS_NAME,
						    "registerClassMethodSignatures",
			    "(Ljava/lang/String;[Ljava/lang/String;[Ljava/lang/Object;)V");

      Expression[] methodNames = new Expression[methodNamesForIndex.size()];
      methodNamesForIndex.copyInto(methodNames);

      MethodRef getClassMethod = new MethodRef("java.lang.Object",
					 "getClass",
					 "()Ljava/lang/Class;");

      VariableDeclaration sigsArray = 
	new VariableDeclaration("signatures", 
				"[Ljava/lang/Object;",
				new NewArray("[Ljava/lang/Object;",
					     new int[] {methodNames.length}));
      registerMethodBody.add(sigsArray);
      Expression sigsArrayRef = new Variable("signatures", "[Ljava/lang/Object;");

      for (int i=0; i<methodNames.length; i++)
	{
	  Expression[] methodSignatures = (Expression[])methodArgSignaturesForIndex.elementAt(i);
	  if (methodSignatures.length > 0) {
	    Expression assignValue = 
	      new OperatorCall("=", 
			       new Expression[] {new ArrayRef(sigsArrayRef, new Value(i)),
						   new NewArray("[Ljava/lang/String;", 
								methodSignatures)});
	    registerMethodBody.add(assignValue);
	  }
	}
      MethodCall invokeRegisterSigsMethod = 
	new MethodCall(registerSigsMethod,
		       new Expression[] { new Value(cfg.getClassName()),
	                                  new NewArray("[Ljava/lang/String;", methodNames),
	                                  sigsArrayRef },
		       MethodCall.MTH_CALL_VIRTUAL);
      registerMethodBody.add(invokeRegisterSigsMethod);
      registerMethodBody.add(new Return());
      cfg.addMethod(REGISTER_CLASS_METHODS_METHOD,
		    "()V",
		    new String[] {},
		    PUBLIC_ACCESS,
		    registerMethodBody,
		    new ClassRef[] {});
							   

    } catch (ClassException ce) {
      ce.printStackTrace(System.err);
      throw new ClassFileGenerationException(ce, "");
    }
  }

  protected void generateHeader (String[] imports,
		       String superClass,
		       String[] interfaces) {
    super.generateHeader (imports, superClass, interfaces, (InterfaceInfo[])null);
    cfg.implementInterface("java.io.Serializable"); // all local classes must be serializable
  }

  @Override
  protected void generateFields (AttrInfo attributes,
		       Symbol[] classInheritancePath) {
 
    // Need to add: static final long serialVersionUID = 0xD0EFACED;
    cfg.addField("serialVersionUID",
		 "J", // long
		 STATIC_FINAL_ACCESS,
		 new Value(0xD0EFACED),
		 true); // static field

    Symbol[] attrTypes = attributes.attrTypes, attrNames = attributes.attrNames,
      origNames = attributes.origNames, defClasses = attributes.defClasses;
    boolean[] staticQ = attributes.staticP;
    boolean[] systemDefined = attributes.systemDefined;
    symVarNames = createJavaSymbolVariableNames(systemDefined, attrNames, staticQ);
  }

  class AttrClassPair {
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
      if (mostSpecificClassDefiningDuplicateAttribute (attrName, isStatic, duplicates) == null) {
      	for (int j = i + 1; j < origNames.length; j++)
      	  if (attrName.equals (origNames[j]) && (isStatic == staticQ[j])) {
      	    duplAttrInfo = new AttrClassPair (attrName, defClasses[i], isStatic);
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
    if (classOfDuplAttr == null || definingClass.equals (classOfDuplAttr))
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

    /* Constructor looks like this:
      public <javaClassName>() {
        super();
	initializeFields();
      }
    */
    // So, let's generate some byte-code to do this:
    if (!useJavaC) {
      try {
        Block methodBody = new Block();
	// MethodReference to super() method
	MethodRef superRef = new MethodRef(cfg.getSuperClassName(), "<init>", "()V");
	// MethodCall for super() method
        MethodCall invokeSuper = new MethodCall(superRef, MethodCall.MTH_CALL_SPECIAL);
        // add super() invocation to method body
	methodBody.add(invokeSuper);
	// MethodReference to initializeFields() method
	MethodRef initRef = new MethodRef(cfg.getClassName(), INIT_METHOD, "()V");
	// MethodCall for super() method
        MethodCall invokeInit = new MethodCall(initRef, MethodCall.MTH_CALL_VIRTUAL);
        // add initialzeFields() invocation to method body
	methodBody.add(invokeInit);
        
	// add constructor to classFileGenerator
        methodBody.add(new Return());
	cfg.addMethod("<init>", 
		      "()V", 
		      null, 
		      PUBLIC_ACCESS, 
		      methodBody, 
		      null);

	/* And code for this
	   public <javaClassName>(ObjectProxy proxy) {
	     super();
	     initiaizeFields();
	     this.proxy = proxy;
	   }
        */  
	Block methodBody2 = new Block();
        // add super() invocation to method body
	methodBody2.add(invokeSuper);
	// MethodReference to initializeFields() method
	methodBody2.add(invokeInit);

	FieldRef field = new FieldRef(G2__BASEIMPL_CLASS_NAME,
				      PROXY_VARIABLE_NAME,
				      PROXY_ACCESS_CLASS_DESC);

	Expression assignValue = new OperatorCall("=", 
						  new Expression[] {field,
								      new Variable("proxyInputName", 
										   PROXY_ACCESS_CLASS_DESC )});
	methodBody2.add(assignValue);

	// add constructor to classFileGenerator
        methodBody2.add(new Return());

	cfg.addMethod("<init>", 
		      "(" + PROXY_ACCESS_CLASS_DESC + ")V", 
		      new String[] {"proxyInputName"}, 
		      PUBLIC_ACCESS, 
		      methodBody2, 
		      null);


  
      }
      catch (ClassException e) {
	System.err.println("Could not instantiate MethodRef.  Byte-code for zero arg constructor in " + javaClassName + " not generated");
	e.printStackTrace(System.err);
	{toggleJavaC();} // abandon all hope of generating byte code}
	throw new ClassFileGenerationException(e, "");
      }
    }
  }

  private String[] createJavaSymbolVariableNames (boolean[] systemDefined, Symbol[] attrNames, boolean[] staticQ) {
    int numAttributes = attrNames.length;
    String[] symVarNames = new String[numAttributes];
    for (int i=0; i<numAttributes; i++) {
      if (systemDefined[i]) {
        symVarNames[i] = "com.gensym.util.symbol.SystemAttributeSymbols." + createJavaSymbolVariableName (attrNames[i]);
      } else {
        symVarNames[i] = createJavaSymbolVariableName (attrNames[i]);
        if (staticQ[i])
	  symVarNames[i] += "FOR_CLASS_";
      }
    }
    return symVarNames;
  }

  @Override
  void generatePropertyAccessors (String[] jSlotTypes,
				  String[] jSlotNames,
				  Symbol[] slotNames,
				  int[] generationFlags,
				  G2Type[] typeSpecifications,
				  Symbol[] definingClasses,
				  Object[] initialValues,
				  boolean[] systemDefined) {
  try {

    Block updateLocalAttributesFromG2Body = new Block();
    Block updateG2AttributesFromLocalBody = new Block();
    Variable attsVar = new Variable("atts", "Lcom/gensym/util/Structure;"); 
    MethodRef superUpdateLocalAttributeFromG2 = 
      new MethodRef(cfg.getSuperClassName(),
		    UPDATE_LOCAL_ATTRIBUTES_FROM_G2_METHOD,
		    UPDATE_LOCAL_ATTRIBUTES_FROM_G2_DESCR);

    updateLocalAttributesFromG2Body.add(new MethodCall(superUpdateLocalAttributeFromG2,
						      new Expression[] {attsVar},
						      MethodCall.MTH_CALL_SPECIAL));

    MethodRef superUpdateG2AttributeFromLocal = 
      new MethodRef(cfg.getSuperClassName(),
		    UPDATE_G2_ATTRIBUTES_FROM_LOCAL_METHOD,
		    UPDATE_G2_ATTRIBUTES_FROM_LOCAL_DESCR);

    
    updateG2AttributesFromLocalBody.add(new MethodCall(superUpdateG2AttributeFromLocal,
						      new Expression[] {attsVar},
						      MethodCall.MTH_CALL_SPECIAL));

    MethodRef convertG2AttributeForLocalRef = 
      new MethodRef(G2__BASEIMPL_CLASS_NAME,
		    CONVERT_G2_ATTRIBUTE_FOR_LOCAL_METHOD,
		    CONVERT_G2_ATTRIBUTE_FOR_LOCAL_DESCR);

    MethodRef convertLocalAttributeForG2Ref = 
      new MethodRef(G2__BASEIMPL_CLASS_NAME,
		    CONVERT_LOCAL_ATTRIBUTE_FOR_G2_METHOD,
		    CONVERT_LOCAL_ATTRIBUTE_FOR_G2_DESCR);

    //System.out.println("Generating property accessors...");
    for(int i = 0; i < jSlotNames.length; i++) {
      //if (systemDefined[i])
      //break;
      Symbol currentSlot_= slotNames[i];
      String currentSlot = jSlotNames[i];
      String currentType = jSlotTypes[i];
      String currentDescriptor = cfg.getVMDescriptorForJavaType(currentType);
      boolean staticField = ((generationFlags[i] & PROPERTY_STATIC) != 0);
      if (staticField) break;
      String fieldName   = G2ClassTranslator.initCap(makeFieldNameForSlot (currentSlot, staticField));
      String slotVarName = ensureLegalJavaVariableName (currentSlot);
      boolean getterExists = (generationFlags[i] & PROPERTY_GETTER) != 0;
      boolean setterExists = (generationFlags[i] & PROPERTY_SETTER) != 0;
      if (fieldName.equals ("Text")) {
	getterExists = setterExists = true;
	currentType  = "java.lang.String";
      }

      if (addSlotFields) {
	// insert field declaration.
	cfg.addField(slotVarName,
		     currentDescriptor,
		     PUBLIC_ACCESS,
		     null, // init vals set up in endClass();
		     staticField);

	if (!isSystemClass) {
	  FieldRef fieldRef = new FieldRef(cfg.getClassName(),
					   slotVarName,
					   currentDescriptor,
					   false);

	  MethodCall internSymbol = 
	    new MethodCall(new MethodRef(com.gensym.jgi.download.ClassConstants.SYMBOL_CLASS_NAME, 
					 "intern", 
					 "(" + STRING_DESC + ")" + 
					 com.gensym.jgi.download.ClassConstants.SYMBOL_CLASS_DESC),
			   new Expression[] {new Value(currentSlot_.toString())}, 
			   MTH_CALL_STATIC);
	  Expression[] assargs = 
	    new Expression[] {fieldRef,
				ClassFileGenerator.doCast(currentType,
							  new MethodCall(convertG2AttributeForLocalRef, 
									 new Expression[] {attsVar,
											   internSymbol},
									 MTH_CALL_VIRTUAL))};
	  // Adding <field> = <cast>_convertLocalAttributeForG2Ref(atts, g2attName) 
	  updateLocalAttributesFromG2Body.add(new OperatorCall("=", assargs));

	  Expression wrappedFieldRef = ClassFileGenerator.wrapPrimitiveIfNecessary(currentType,
										   fieldRef);
	  
	  // Adding _convertG2AttributeForLocal(atts, g2attName, <cast><field>)
	  updateG2AttributesFromLocalBody.add(new MethodCall(convertLocalAttributeForG2Ref,
							    new Expression[] {attsVar,
										internSymbol,
										wrappedFieldRef},
							    MTH_CALL_VIRTUAL));
	}
									 
      }

      //System.out.println(currentSlot + " " + initialValues[i] + " " + currentType );
      if (initialValues[i] != null)
	cacheInitialisation(currentSlot, byteCodeForInitialValue(initialValues[i], currentType, staticField), currentType);
      
      if (setterExists) {
	String setterName = "set" + fieldName;
	String setterInterface = ("public void " + setterName + "(" + currentType + " " + slotVarName + ") {");
	Sequence intfSig = com.gensym.jgi.download.MethodInfo.getMethodSignatureAsSequence(setterInterface);
	if (!methodAlreadyDefined(intfSig)) {
	  recordOpInterfaceSignature(setterInterface);
	  Block setterBody = generateSetBody (output, 
					      currentType, 
					      slotVarName, 
					      symVarNames[i],
					      currentSlot_,
					      staticField, 
					      getJavaTypeNameForG2Type(definingClasses[i]),
					      initialValues[i],
					      setterName);
	  Access access;
	  //if (staticField) access =  new Access(ACC_PUBLIC | ACC_STATIC);
	  access = PUBLIC_ACCESS;
	  String descriptor = "(" + cfg.getVMDescriptorForJavaType(currentType)  + ")V";
	  // now add setter method to class
	  cfg.addMethod(setterName, 
			descriptor, 
			new String[] {slotVarName}, 
			access, 
			setterBody, 
			new ClassRef[] {});
 	}
      }

      if (getterExists) {
	String getterName = "get" + fieldName;
	String getterInterface = ("public " + currentType + " " + getterName + "() {");
	Sequence intfSig = com.gensym.jgi.download.MethodInfo.getMethodSignatureAsSequence(getterInterface);
	if (!methodAlreadyDefined(intfSig)) {
	  recordOpInterfaceSignature(getterInterface);
 	  Block getterBody = generateGetBody (output, 
					      currentType, 
					      slotVarName, 
					      symVarNames[i], 
					      currentSlot_, 
					      staticField,
					      getJavaTypeNameForG2Type(definingClasses[i]),
					      initialValues[i],
					      getterName);
	  Access access;
	  //if (staticField) access =  new Access(ACC_PUBLIC | ACC_STATIC);
	  access = PUBLIC_ACCESS;
	  String descriptor = "()" + cfg.getVMDescriptorForJavaType(currentType);
	  // now add getter method to class
	  cfg.addMethod(getterName, 
			descriptor, 
			new String[] {}, 
			access, 
			getterBody, 
			new ClassRef[] {});
	}
      }
    }

    updateLocalAttributesFromG2Body.add(new Return());    

    cfg.addMethod(UPDATE_LOCAL_ATTRIBUTES_FROM_G2_METHOD,
		  UPDATE_LOCAL_ATTRIBUTES_FROM_G2_DESCR,
		  new String[] {"atts"},
		  new Access(ACC_PROTECTED),
		  updateLocalAttributesFromG2Body,
		  new ClassRef[] {});

    updateG2AttributesFromLocalBody.add(new Return());
    
    cfg.addMethod(UPDATE_G2_ATTRIBUTES_FROM_LOCAL_METHOD,
		  UPDATE_G2_ATTRIBUTES_FROM_LOCAL_DESCR,
		  new String[] {"atts"},
		  new Access(ACC_PROTECTED),
		  updateG2AttributesFromLocalBody,
		  new ClassRef[] {});

    } catch (ClassException e) {
      throw new ClassFileGenerationException(e, e.toString());
    }
  }

  private void cacheInheritedAttributeInitializations(AttrInfo inheritedAttributeInitializations) {
    if (inheritedAttributeInitializations == null) return;
    for (int i = 0; i<inheritedAttributeInitializations.attrTypes.length; i++) {
      Symbol attrType = inheritedAttributeInitializations.attrTypes[i];
      if (attrType != null && inheritedAttributeInitializations.attrNames[i] != null) {
	String jSlotName = getJavaPropertyNameForG2Slot (inheritedAttributeInitializations.attrNames[i]);
	String jSlotType = getJavaTypeNameForG2Type(attrType);
	cacheInitialisation(jSlotName, 
			    byteCodeForInitialValue(inheritedAttributeInitializations. initialValues[i], 
						    jSlotType, 
						    false), 
			    jSlotType);
      }
    }
  }

  void cacheInitialisation(String fieldName, Expression initVal, String type) {
    //System.out.println("Caching init for " + fieldName + "(" + type + ")=" + initVal);
    fieldInits.addElement(new FieldInitialisation(fieldName, initVal, type));
  }

  class FieldInitialisation extends Object {
    String fieldName;
    Expression initialValue;
    String fieldType;
    
    FieldInitialisation(String name, Expression value, String type) {
      fieldName = name;
      initialValue = value;
      fieldType = type;
    }
  }

  @Override
  Expression byteCodeForInitialValue(Object initVal, String type, boolean isStatic) {
    if (debug) System.out.println("Initial Value for " + type + " = " + initVal);
    // MACH 20/08/98 00:20 BUG!  Doesn't deal with type conversions.
    try {
      if (initVal instanceof Structure) { // can only be initialising a structure.
	// BUG:  Does not deal with initialisation
	return new New("com.gensym.util.Structure");
      }
      if (initVal instanceof Sequence) { // can only be initialising a sequence.
	// BUG:  Does not deal with initialisation
	return new New("com.gensym.util.Sequence");
      }
      if (initVal instanceof Symbol) { // can only be initialising a symbol
	Expression[] args = new Expression[] {new Value(((Symbol) initVal).toString())};
	String descriptor = "(Ljava/lang/String;)Lcom/gensym/util/Symbol;";
	MethodRef internRef = new MethodRef("com.gensym.util.Symbol", "intern", descriptor);
	return new MethodCall(internRef, args, MTH_CALL_STATIC);
      }
      if (initVal instanceof Boolean) { // can only be initialising a truth-value
	//System.out.println("LSGC:>>>init Val is Boolean, initialising " + type);
	return new Value(((Boolean) initVal).booleanValue());
      }
      if (initVal instanceof Integer) { // could be initialising any of : integer, float, quantity, item-or-value, or value
	//System.out.println("Integral type being assigned to " + type);
	if (type.equals("int")) // int being assigned to int - no problem
	  return new Value(((Integer) initVal).intValue());
	if (type.equals("double")) // int being assigned to double
	  return new Value(((Integer) initVal).doubleValue());
	if (type.equals(NUMBER_CLASS_NAME)) {// int being assigned to Number
	  MethodRef methodRef = new MethodRef("java.lang.Integer","<init>","(I)V");
	  Expression[] args = new Expression[] {new Value(((Integer) initVal).intValue())};
	  MethodCall methodCall = new MethodCall(methodRef, args, MTH_CALL_SPECIAL);
	  return new New(methodCall);
	}
	if (type.equals("java.lang.Object")) { // int being assigned to Object
	  MethodRef methodRef = new MethodRef("java.lang.Integer","<init>","(I)V");
	  Expression[] args = new Expression[] {new Value(((Integer) initVal).intValue())};
	  MethodCall methodCall = new MethodCall(methodRef, args, MTH_CALL_SPECIAL);
	  return new New(methodCall);
	}
      }
      if (initVal instanceof String) // can only be a text (= String)
	return new Value((String) initVal);
      if (initVal instanceof Double) { // could be initialising any of : float, quantity, item-or-value, or value
	//System.out.println("Double type being assigned to " + type);
	if (type.equals("double")) // Double being assigned to double - extract value
	  return new Value(((Double) initVal).doubleValue());
	if (type.equals(NUMBER_CLASS_NAME)) { // Double being assigned to Number
	  MethodRef methodRef = new MethodRef("java.lang.Double","<init>","(D)V");
	  Expression[] args = new Expression[] {new Value(((Double) initVal).doubleValue())};
	  MethodCall methodCall = new MethodCall(methodRef, args, MTH_CALL_SPECIAL);
	  return new New(methodCall);
	}
	if (type.equals("java.lang.Object")) { // double being assigned to Object
	  MethodRef methodRef = new MethodRef("java.lang.Double","<init>","(D)V");
	  Expression[] args = new Expression[] {new Value(((Double) initVal).doubleValue())};
	  MethodCall methodCall = new MethodCall(methodRef, args, MTH_CALL_SPECIAL);
	  return new New(methodCall);
	}
      }
      /*      if (initVal instanceof boolean) {
	System.out.println("boolean initVal");
      }
      else if (initVal instanceof int) {
	System.out.println("int initVal");
      }
      else if (initVal instanceof double) {
	System.out.println("double initVal");
      }*/
      // WHAT DO I DO WHEN THE INITVAL IS A PRIMITIVE (boolean), BUT THE FIELD IS AN OBJECT (ITEM-OR-VALUE)?
      // SEE THE X FIELD IN THE QUANTITY-FUNCTION-CLASS.
      // the theory is that if it wasn't one of the above, then it must be a user class
      return new New(factory.getImplementationClassName(type)); // can't instantiate the interface, so use Impl
    }
    catch (ClassException ce) {
      ce.printStackTrace(System.err);
      throw new ClassFileGenerationException(ce, "");
    }
    
  }


  private static final String instVarSetter = "setAttributeValue",
			      classVarSetter = "setStaticAttributeValue";

  Block generateSetBody(PrintWriter output,
			String currentType,
			String slotVarName, // the name of the argument holding the new value
			String symVarName, // the name of the attribute to set
			Symbol g2SlotName,
			boolean staticField,
			String definingClass,
			Object initialValue,
			String setterName) {
    String setterFn = (staticField ? classVarSetter : instVarSetter);
    String extraArgs = (staticField ? ", classPropertyKeys, classPropertyValues" : "");
    extraArgs = "";
    if (!useJavaC) { // do some dbcg
      /* Add byte-code to implement the following:
	 public [static] set<FieldName>(<currentType> <slotVarName>) {
	   [setAttributeValue | setStaticAttributeValue](<symVarName>, new <Wrapper>(<symVarName>));
	 }
       */
      try {
	Block body = new Block();
	String paramDescr = cfg.getVMDescriptorForJavaType(currentType);
	String setterDescr = "(" + paramDescr + ")V";
	Expression[] setterArgs = new Expression[] {new Variable(slotVarName, 
								 paramDescr) };
	
	if (useRuntimeManager) {
	  insertRuntimeManagerCode(body,
				setterName,
				setterDescr,
				setterArgs);
	}

	if (insertRemoteProxyCode) {
	  Sequence javaArgTypes = new Sequence();
	  javaArgTypes.addElement(currentType);
	  insertRemoteProxyCode(body,
				setterName,
				javaArgTypes,
				null,
				setterArgs);
	}

	FieldRef attribute = new FieldRef(cfg.getClassName(),
					  slotVarName,
					  cfg.getVMDescriptorForJavaType(currentType),
					  false);
	Variable value = new Variable(slotVarName, cfg.getVMDescriptorForJavaType(currentType));
	Expression[] args = new Expression[] {attribute, value};
	
	OperatorCall assignment = new OperatorCall("=", args);
	body.add(assignment);

	// MDG-Add for propertyChangeSupport 11/sep/98
	// firePropertyChange(String slotValue, Object oldValue, Object newValue)
	body.add(new VariableDeclaration("oldValue",
					 cfg.getVMDescriptorForJavaType(currentType)));
	MethodRef firePropertyChangeMethodRef = 
	  new MethodRef(G2__BASEIMPL_CLASS_NAME,
			"firePropertyChange",
			"(Ljava/lang/String;Ljava/lang/Object;Ljava/lang/Object;)V");

	Expression  oldValue = 
	  new Variable("oldValue", cfg.getVMDescriptorForJavaType(currentType));
	Expression[] oldArgs = new Expression[] {oldValue, attribute};
	OperatorCall oldValueAssignment = new OperatorCall("=", oldArgs);
	body.add(oldValueAssignment);
	Expression[] fireMethodArgs = 
	  new Expression[] {new Value((String) slotVarName),
			    byteCodeToMakeObject("oldValue", currentType), 
			    byteCodeToMakeObject(slotVarName, currentType)};

	MethodCall fireMethodCall = new MethodCall(firePropertyChangeMethodRef,
						      fireMethodArgs,
						      MTH_CALL_VIRTUAL);
	body.add(fireMethodCall);
	body.add(new Return());
	return body;
      }
      catch (ClassException ce) {
	ce.printStackTrace(System.err);
	throw new ClassFileGenerationException(ce, "Generating set body for " + slotVarName);
      }
    }
    return null;
  }

  // This should go somewhere generic
  static String codeToMakeObject (String varName, String type) {
    String wrapperType = ClassFileGenerator.getWrapperClass(type);
    if (wrapperType.equals("")) return varName;
    return "new " + wrapperType + "(" + varName + ")";
  }

  static Expression byteCodeToMakeObject(String varName, String type) {
    try {
      String typeDesc = ClassFileGenerator.getVMDescriptorForJavaType(type);
      String wrapperClass = ClassFileGenerator.getWrapperClass(type);
      if (wrapperClass.equals("")) {
	return new Variable(varName, typeDesc);
      }
      else {
	MethodRef constructorRef = new MethodRef(ClassFileGenerator.getWrapperClass(type),
						 "<init>",
						 "(" + typeDesc + ")V");
	Expression[] args = new Expression[] {new Variable(varName, typeDesc)};
	MethodCall constructorCall = new MethodCall(constructorRef, args, MTH_CALL_SPECIAL);
	return new New(constructorCall);
      }
    } 
    catch (ClassException ce) {
      ce.printStackTrace(System.err);
      throw new ClassFileGenerationException(ce, "");
    }
   
  }

  private static final String instVarGetter = "getAttributeValue",
			      classVarGetter = "getStaticAttributeValue",
                              textVarGetter = "getAttributeTextValue";

  Block generateGetBody (PrintWriter output,
			 String currentType,
			 String slotVarName,
			 String symVarName,
			 Symbol g2SlotName,
			 boolean staticField,
			 String definingClassName,
			 Object initialValue,
			 String getterName) {

    Block body = new Block();
    
    String getterDescr = "()" + cfg.getVMDescriptorForJavaType(currentType);
    Expression[] getterArgs = new Expression[] { };

    if (useRuntimeManager) {
	insertRuntimeManagerCode(body,
			      getterName,
			      getterDescr,
			      getterArgs);
    }

    
    if (insertRemoteProxyCode) {
	  insertRemoteProxyCode(body,
				getterName,
				new Sequence(),
				currentType,
				getterArgs);
    }

    
    String getterFn = (staticField ? classVarGetter : instVarGetter);
    String extraArgs = (staticField ? ", classPropertyKeys, classPropertyValues" : "");
    extraArgs = "";
    // moved here because this method needs to know which type of return statement is being created
    String wrapperClass = ClassFileGenerator.getWrapperClass(currentType);
    boolean returnWrapper = true; // tells the byte-code generation code what type of return statement to generate
    if (wrapperClass.equals("")) { //codeToGetPrimitiveValueOrCastReturnObject ("retnValue", currentType)
      returnWrapper = false; // use currentType for cast, not wrapper class
    }
    
    if (useJavaC) 
      return null; // no byte-code generation required
    else {
      try {
	// What is being generated above will look something like this:
	// java.lang.Object retnValue = getAttributeValue(<symVarName>);
	// EITHER return (<type>) symVarName;
	// OR     return ((<wrapperType>) symVarName).typeValue();

	FieldRef fieldRef = new FieldRef(packageName + "." + javaClassName, //definingClassName,
					 stripPackage(slotVarName),
					 ClassFileGenerator.getVMDescriptorForJavaType(currentType),
					 false);
        Return returnStatement = new Return(fieldRef);
        body.add(returnStatement);
	return body; // another corpse for the collection
      }
      catch (ClassException e) {
	e.printStackTrace(System.err);
	{toggleJavaC();} // abandon all hope of generating byte code}
	throw new ClassFileGenerationException(e, "While generating get body for " + g2SlotName);
      }
    }
  }

  static String codeToGetPrimitiveValueOrCastReturnObject (String varName, String type) {
    String wrapperClass = ClassFileGenerator.getWrapperClass(type);
    if (wrapperClass.equals("")) return "(" + type + ")" + varName;
    return "((" + wrapperClass + ")" + varName + ")." + ClassFileGenerator.getAccessorMethod(type) + "()";
  }

  static Expression byteCodeToGetPrimitiveValueOrCastReturnObject(String varName, String type, boolean isStatic) {
    String wrapperClass = ClassFileGenerator.getWrapperClass(type);
    String typeDesc = ClassFileGenerator.getVMDescriptorForJavaType(type);
    try {
      if (wrapperClass.equals("")) {
	// return (<type>) <varName>;
	return new Cast(type, new Variable(varName, typeDesc));
      }
      else {
	// return ((<wrapperClass) varName).<accessorMethod>()
	Expression wrapperCast = new Cast(wrapperClass, new Variable(varName, typeDesc));
	MethodRef accessorRef = new MethodRef(wrapperClass, ClassFileGenerator.getAccessorMethod(type), "()" + typeDesc);
	return new MethodCall(wrapperCast, 
			      accessorRef, 
			      new Expression[] {}, 
			      (isStatic ? MTH_CALL_STATIC : MTH_CALL_VIRTUAL));
      }
    }
    catch (ClassException ce) {
      ce.printStackTrace(System.err);
      throw new ClassFileGenerationException(ce, "");
    }
   
  }

  static final int SIG_POS = 0;
  static final int INT_POS = 1;
  static final int IMP_POS = 2;

  /**
   * Generate the method code for each method read from G2 for this class and
   * its inherited classes.
   * We also include any overide methods from the classes hierarchy.
   * If any override methods match up with G2 generated methods, then
   * the method source for the override is used.
   */
  @Override
  void generateMethods (com.gensym.jgi.download.MethodInfo methodInfoArray[], 
			ClassInfo ovrClassInfo,
			boolean onlyEventMethods) {

    if (debug)
      System.out.println("SGC: Methods."); // DEBUG

    if (methodInfoArray == null) methodInfoArray = new com.gensym.jgi.download.MethodInfo[0];
			
    // Symbol Declarations for methodNames

    Hashtable decTable = new Hashtable(201);
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "genStubMethod", new Integer (methodInfoArray.length));

    //    boolean titleSent = false;
    for (int i = 0; i<methodInfoArray.length; i++) {

      com.gensym.jgi.download.MethodInfo mi = methodInfoArray[i];
      if (mi.isActive()) {
      	String decName = (mi.generateRPCDeclarationName()).intern();
      	// Check to ensure that the symbol is not already defined
      	if (decTable.get(decName) == null) {
      	  decTable.put(decName, this); 
      	  // insert a dummy, we just want to remember that we have got this symbol
      	}
      }
    }
    
    // Output any overrides for this class - any required DBCG will be performed in endClass()
    Sequence opSignatures = new Sequence(50);
    Sequence ovrInterfaceSig;
    String ovrInterface;

    boolean conflict = false;
    // Now output any overrides for any superior class
    // But as the implementation is flat, mangle the name if there is a match
    Sequence inhOpSignatures = new Sequence(50);

    // Concat all override signatures together
    opSignatures.concatenate(inhOpSignatures);

    Sequence hcInfoSeq = new Sequence(50);

    // No exported methods for Proxy classes
    if (isG2ProxyObjectClass) return;
    
    Sequence hcInfoSeqCopy = (Sequence)hcInfoSeq.clone();   // we will be removing items, inside an Enumeration

    // Make a list of Item methods names
    Sequence itemMethods = getItemMethods();

    // Output generated G2 method stubs
    for (int i =0; i<methodInfoArray.length; i++) {

      com.gensym.jgi.download.MethodInfo mi = methodInfoArray[i];

      if (debug)
	System.out.println("Implementing method " + mi.getJavaMethodName()); // DEBUG
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
    
      Object[] info = (Object[])e.nextElement();
      Sequence eSigSeq = (Sequence)info[SIG_POS];

      // Check that we have not already sent this interface out
      
      for (Enumeration opsige = opSignatures.elements(); opsige.hasMoreElements();) {
      	if (eSigSeq.equals(opsige.nextElement())) {
      	  conflict = true;
      	  break;
      	}
      }
    }
  }

  /**
   *  Produce a local implementation for a G2 method stub 
   *  @param cfg the class file generator to use when producing byte-code 
   *  (null if no byte-code being generated).
   */
  boolean generateLocalMethodImplementation(com.gensym.jgi.download.MethodInfo mi,
					    boolean opAddRemoveInterface) {

    boolean dbcg = (cfg != null); // directly generate byte-code if cfg is not null
    if (debug)
      System.out.println("Generating local method impl for " + mi.getJavaMethodName()); // DEBUG

    // block to hold method body (call to compiled method)
    Block methodBody = new Block();

    String overrideArgNameAt1Pos = null;

    // Enter the rest of the parameters in the arguments array
    // converting primitive types to objects where necessary
    String argName;
    Sequence G2ArgumentTypes = mi.getArgumentTypes();
    if (debug) System.out.println("arg types = " + G2ArgumentTypes);
    Enumeration argTypes = G2ArgumentTypes.elements();
    argTypes.nextElement(); // HACK - get rid of self
    Sequence argumentNames = mi.getArgumentNames();
    Expression[] methodArguments = new Expression[argumentNames.size() - 1]; // DBCG

    if (debug) {
      String[] nams = mi.getArgumentNamesAsStrings();
      for (int i = 0; i < nams.length; i++)
	System.out.println("Arg " + i + " = " + nams[i]);
    }

    int argumentCount = 0;
    int localRef = 1; // the local var to refer to
    Enumeration names = argumentNames.elements();
    names.nextElement(); // HACK - get rid of self
    Sequence javaArgTypes = new Sequence();
    while (names.hasMoreElements()) {

      argName = (String) names.nextElement();
      Object argType = argTypes.nextElement();
      String argJavaType = getMethodType(argType);
      javaArgTypes.addElement(argJavaType);
      if (debug) {
	System.out.println("Arg Name: " + argName + "; type = " + argJavaType);
      }
      if (dbcg) { // DBCG
        try {
          String wrapperClass = ClassFileGenerator.getWrapperClass(argJavaType);
 	  if (debug) {
	    System.out.println("argumentCount = " + argumentCount + "; type = " + argJavaType);
	    //System.out.println("Wrapper = " + wrapperClass);
	  }
          //if (wrapperClass.equals("")) {
	  //if (debug) System.out.println("No wrapper - instantiating Variable");
	    // if there's no wrapper, assume this is a variable
	  methodArguments[argumentCount++] = 
	    new Variable(localRef++, 
			 ClassFileGenerator.getVMDescriptorForJavaType(argJavaType));
	  if (argJavaType.equals("double") || argJavaType.equals("long"))
	    localRef++;
        }
        catch (ClassException ce) {
          ce.printStackTrace(System.err);
          dbcg = !dbcg; // failed to generate byte-code - give up
	  throw new ClassFileGenerationException(ce, "");
        }
      } // GCBD
    }

    if (debug) System.out.println("Invoking method with " + methodArguments.length + " argument(s)");

    Block bcBody = null;
    if (dbcg) { // add runtimeManager code to method and pass methodBody to cfg
          bcBody = new Block();

	  insertRuntimeManagerCode(bcBody,
				mi.getJavaMethodName(),
				buildMethodDescriptor(mi.getArgumentTypes(), 
						      mi.getResultTypes()),
				methodArguments);

	  String javaReturnType = null;
	  Sequence G2ReturnTypes = mi.getResultTypes();
	  switch (G2ReturnTypes.size()) {
	  case 0: // void return type
	    // this is a void return type
	    break;
	  case 1: // single return type
	    javaReturnType = getMethodType(G2ReturnTypes.elementAt(0)); 
	    // get the java type defintion of the return type
	    break;
	  default: // multiple return types - enclose within a Sequence object
	    javaReturnType = "com.gensym.util.Sequence";
	    break;
	  }
	 
	  insertRemoteProxyCode(bcBody,
				mi.getJavaMethodName(),
				javaArgTypes,
				javaReturnType,
				methodArguments);

	  try {
	    cfg.compileMethodCall(mi.getG2MethodSource(),
				  bcBody,
				  compiler);
	  } catch (com.gensym.g2script.CompilerException e) {
	    compilerErrorReports.addElement(new CompilerErrorReport(mi, e.getMessage()));
	  } catch (ClassException e) {
	    compilerErrorReports.addElement(new CompilerErrorReport(mi, e.toString()));
	  }
    }
    return dbcg;
  }

  class CompilerErrorReport {

    String error;
    com.gensym.jgi.download.MethodInfo mi;

    CompilerErrorReport(com.gensym.jgi.download.MethodInfo mi, String error) {
      this.error = error;
      this.mi = mi;
    }
  }

  private void checkForCompilerErrors() throws G2ClassCompilerException {
    if (compilerErrorReports.size() == 0) return;

    String errString = "The G2Script Compiler reported the following " +
                       "during the compilation of methods found in " + className + "\n";
   
    for (int i=0; i<compilerErrorReports.size(); i++) {
      CompilerErrorReport report = (CompilerErrorReport)compilerErrorReports.elementAt(i);
      errString = errString + (i+1) + ". In " + report.mi.getG2MethodName() + report.mi.getArgumentTypes() +
	          ":\n" + report.error + "\n";
    }

    throw new G2ClassCompilerException(errString);
  }
    

  private void outputMethodInfoImplementation(com.gensym.jgi.download.MethodInfo mi,
					      Sequence itemMethods,
					      Sequence opSignatures, 
					      Sequence hcInfoSeq,
					      Sequence hcInfoSeqCopy,
					      boolean generateExternalAddRemoveListenerInterface) {
    boolean conflict;

    if (mi.isActive()) {
      String intf = mi.generateMethodInterface((ClassGenerationContext) this, 
					       generateExternalAddRemoveListenerInterface, 
					       false);
      Sequence mInterfaceSig = com.gensym.jgi.download.MethodInfo.getMethodSignatureAsSequence(intf);

      conflict = false;

      // Check that this interface method does not conflict with any Item methods
      // as we don't allow G2 methods to override any methods defined by Item
      // (This check is minimal name and number, should also be type)
      for (Enumeration e = itemMethods.elements(); e.hasMoreElements();) {
	java.lang.reflect.Method method = (java.lang.reflect.Method)e.nextElement();
	if (method.getName().equals(mi.getJavaMethodName()) &&
	    method.getParameterTypes().length == mInterfaceSig.size()) {
	  conflict = true;
	  break;
	}
      if (!conflict)
      	// Check that we have not already sent this interface out
      	for (Enumeration opsige = opSignatures.elements(); opsige.hasMoreElements();) {
      	  if (mInterfaceSig.equals(opsige.nextElement())) {
      	    conflict = true;
      	    break;
      	  }
      	}
      }
      if (!conflict) {
      	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "genMeth", mi.getG2MethodName().toString());
      	// Header
      	// Interface
      	// Implementation
      	// First check that there is no exported code that we should as
      	// replacement code
      	boolean gotImplementation = false;
      	// zip through
      	for (Enumeration e = hcInfoSeqCopy.elements(); e.hasMoreElements();) {
      	  Object[] info = (Object[])e.nextElement();
      	  Sequence exSig = (Sequence)info[SIG_POS];
      	  if (mInterfaceSig.equals(exSig)) {
      	    // use exported implementation, rather than default
      	    useJavaC = generateLocalMethodImplementation(mi,
							 generateExternalAddRemoveListenerInterface);
      	    gotImplementation = true;
      	    // Don't export this as an override
      	    hcInfoSeq.removeElement(info);
      	    break;
      	  }
      	}

      	if (!gotImplementation) {
      	  useJavaC = generateLocalMethodImplementation(mi,
						       generateExternalAddRemoveListenerInterface);
      	}
      }
    }
  }

  int methodIndex = 0;
  Vector methodArgSignaturesForIndex = new Vector();
  Vector methodNamesForIndex = new Vector();

  protected int getMethodIndex() {
    return methodIndex;
  }

  protected void recordIndexedMethod(Expression[] methodArgClasses,
				     String methodName)
  {
    methodArgSignaturesForIndex.addElement(methodArgClasses);
    methodNamesForIndex.addElement(new Value(methodName));
    methodIndex++;
  }

  /**
  **/
  void insertRemoteProxyCode(Block methodBody,
			     String methodName,
			     Sequence javaArgTypes,
			     String javaReturnType,
			     Expression[] methodArguments) 
  {
    //if (insertRemoteProxyCode == false) return;
    //System.out.println("In insertRemoteProxyCode" + methodName + " " + javaArgTypes + " " + methodArguments.length);
    try {
      int numParams = javaArgTypes.size();
      Expression[] methodParams = new Expression[numParams];
      Expression[] methodArgClasses = new Expression[numParams];
      int localRef = 1;
      for (int i=0; i<numParams; i++) {
	String paramType = (String)javaArgTypes.elementAt(i); 
	String paramDescriptor = ClassFileGenerator.getVMDescriptorForJavaType(paramType);
	methodParams[i] = ClassFileGenerator.wrapPrimitiveIfNecessary(paramType,
								      methodArguments[i]);
	if (paramType.equals("double") || paramType.equals("long"))
	    localRef++;
	// We clarify if the argument is actually a primitive, as we wrap primitives
	methodArgClasses[i] = new Value(paramType);
	//System.out.println(paramType + " " + paramType);
      }
      
      MethodRef smr = new MethodRef(G2__BASEIMPL_CLASS_NAME,
				    "invokeMyRemoteMethod",
				    "(Ljava/lang/String;I[Ljava/lang/Object;)Ljava/lang/Object;");
      
      Expression[] smrParams = 
	new Expression[] { new Value(cfg.getClassName().replace('/','.')),
	                     new Value(methodIndex),
			     new NewArray("[Ljava/lang/Object;", methodParams) };

      // Remember the signature for later
      recordIndexedMethod(methodArgClasses, 
			  methodName);

      //Expression[] smrParams = 
      //new Expression[] { new Value(methodName),
      //		     new NewArray("[Ljava/lang/Object;", methodParams),
      //		     new NewArray("[Ljava/lang/String;", methodArgClasses) };
      
      FieldRef proxyRef = new FieldRef(G2__BASEIMPL_CLASS_NAME,
				       PROXY_VARIABLE_NAME,
				       PROXY_ACCESS_CLASS_DESC);

      // Note creating the dummy ref as ClassTools does not like OperatorCall with 
      // new Value(null) 21/Jan/99
      VariableDeclaration dummy = new VariableDeclaration("dummy", 
      						  "Ljava/lang/Object;",
						   new Value(null));
      methodBody.add(dummy);
      Expression dummyRef = new Variable("dummy", "Ljava/lang/Object;");
      Expression condition = new OperatorCall("!=", 
					      new Expression[] {proxyRef, dummyRef});      

      
      Block thenBlock = new Block(); // the then block will call proxy.callMethod(...)

      if (javaReturnType == null) {
	thenBlock.add(new MethodCall(smr,
				     smrParams,
				     MTH_CALL_VIRTUAL));
	thenBlock.add(new Return()); //return void
      } else {
	thenBlock.add(new Return(ClassFileGenerator.doCast(javaReturnType, 
							   new MethodCall(smr,
									  smrParams,
									  MTH_CALL_VIRTUAL))));
      } 
      
      // add the if statement to the method body
      methodBody.add(new If(condition, thenBlock));	
    } catch (ClassException e) {
      e.printStackTrace();
      throw new ClassFileGenerationException(e, "While inserting proxy access section");
    }
  }

  /**
   * This method is responsible for adding code to a method body to check
   * if there has been a new version of self, if so call the new versions
   * version of the method instead.
   *  Code for RIM support looks like this:
		<class> newSelf = _getCurrentSelf();
		if (this != newSelf)
		return (<class>)newSelf.<methodName>(<params>);
   **/
  void insertRuntimeManagerCode(Block methodBody, 
			String methodName, 
			String methodDescr, 
			Expression[] methodArguments) {

    try {
      if (!useRuntimeManager) return;
      String returnType =  G2__BASE_CLASS_DESC;
      String fullyQualifiedInterfaceName = packageName + '.' + javaClassInterfaceName;
      MethodRef mRef = new MethodRef(G2__BASEIMPL_CLASS_NAME, 
				     "_getCurrentSelf", 
				     "()" + returnType);
      Expression initVal = new Cast(cfg.getVMDescriptorForJavaType(fullyQualifiedInterfaceName),
				    new MethodCall(mRef, 
						   new Expression[] {}, 
						   MTH_CALL_VIRTUAL));
      VariableDeclaration newSelfDecl = new VariableDeclaration("newSelf", 
								returnType, 
								initVal);
      methodBody.add(newSelfDecl);
      Expression newSelfRef = new Variable("newSelf", returnType); 
      Expression thisRef = new Variable("this", cfg.getClassDescriptor());
      Expression condition = new OperatorCall("!=", 
					      new Expression[] {thisRef, newSelfRef});
      
      Block thenBlock = new Block(); // the then block will call newSelf.methodName(...)
      
      InterfaceMethodRef newSelfMethodRef = new InterfaceMethodRef(fullyQualifiedInterfaceName,
								   methodName,
								   methodDescr);
      MethodCall newSelfMethodCall = new MethodCall(newSelfRef,
						    newSelfMethodRef,
						    methodArguments,
						    MTH_CALL_INTERFACE);
      thenBlock.add(new Return(newSelfMethodCall));
      
      // add the if statement to the method body
      methodBody.add(new If(condition, thenBlock));	    
    } catch (ClassException e) {
      throw new ClassFileGenerationException(e, "While inserting getCurrentSelf section");
    }
  }


  String getPackageName() {
    return packageName;
  }

}


