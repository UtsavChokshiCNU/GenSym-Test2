
package com.gensym.jgi.download.local;

import java.io.*;
import java.util.Locale;
import java.util.Enumeration;
import java.util.Hashtable;
import com.gensym.types.G2Type;

import com.gensym.jgi.download.*;
import com.gensym.message.Trace;
import com.gensym.message.Resource;
import com.gensym.message.MessageKey;
import com.gensym.classtools.*; // for byte-code generation
import com.gensym.g2script.Compiler;
import com.gensym.util.*;
import com.gensym.g2export.LocalClassFriendAccess;

class LocalClassGenerationContext extends ClassGenerationContext 
implements com.gensym.util.symbol.G2TypeSymbols, com.gensym.jgi.download.ClassConstants, RuntimeConstants {

  final static String CLASS_PACKAGE = "com.gensym.classes.modules."; // where the byHandle() classes are kept
  final static String LOCAL_PACKAGE = "com.gensym.local."; // where the local implementations of the package are kept 

  ClassFileGenerator cfg; // generates byte code
  boolean useJavaC = false;
  private LocalClassNameMapper localNameMapper;

  LocalClassGenerationContext (OutputStream out,
			       boolean isInterface,
			       String packageName,
			       String className,
			       LocalClassNameMapper nameMapper) {
    super(out, isInterface, packageName, className, nameMapper);
    localNameMapper = nameMapper;
  }


  @Override
  protected String getJavaTypeNameForG2Type (Symbol g2TypeName_)
  {
    return getJavaTypeNameForG2Type(g2TypeName_, false);
  }

  protected String getJavaTypeNameForG2Type (Symbol g2TypeName_, boolean checkForSubstituteTypes) {
    // Check against known mappings. This needs to be stored in a standard place
    for (int i=0; i<knownG2Types.length; i++)
      if (g2TypeName_.equals (knownG2Types[i]))
	return (mappedJavaTypes[i]).getName ();

    if (checkForSubstituteTypes) {
      String subs = localNameMapper.substituteJavaClassNameFromG2ClassName (g2TypeName_);
      if (subs != null) return subs;
    }

    /*
     * The nameMapper may not know about our class, as we are generating if here
     */
    if (g2TypeName_.equals(g2ClassName))
      return packageName + "." + G2ClassTranslator.createJavaClassNameFromG2ClassName (Symbol.intern(className));

    // Qualified G2 Class names are assumed to refer to Java Class names...leave alone
    String g2TypeName = g2TypeName_.toString();
    if (g2TypeName.indexOf('.') > -1) {
      String unqClassName = g2TypeName.substring(g2TypeName.lastIndexOf(".") + 1);
      String packageName = g2TypeName.substring(0, g2TypeName.lastIndexOf("."));
      return packageName.toLowerCase() + "." + 
	G2ClassTranslator.createJavaClassNameFromG2ClassName (Symbol.intern(unqClassName));
    }

    return nameMapper.javaClassNameFromG2ClassName (g2TypeName_);
  }


  /** Generates the '.class' file for the required class.
  **/
  void generateClass (String[] imports, 
		      String superClass,
		      String[] interfaces, 
		      Symbol[] classInheritancePath,
		      AttrInfo attributes,
		      com.gensym.jgi.download.MethodInfo[] m,
		      ClassInfo ovrClassInfo) {

    Symbol[] attrTypes  = attributes.attrTypes,
      attrNames  = attributes.attrNames,
      origNames  = attributes.origNames,
      defClasses = attributes.defClasses;
    boolean[] readable = attributes.readable,
      writable = attributes.writable,
      isStatic = attributes.staticP,
      systemDefined = attributes.systemDefined;
    G2Type[] typeDescrpns = attributes.typeSpecifications;
    Object[] initVals = attributes.initialValues;
    String fullyQualifiedClassName = qualifyConditionally(packageName + "." + javaClassName);

    //if (isSystemClass) useJavaC = true; // DON'T generate byte-code for system classes
    // Byte-code is only generated for user classes.

    if (!useJavaC) { // use classtools to generate the byte-code directly
      try { // instantiate a ClassFileGenerator to use in generating byte-code
        InterfaceOrClassAccess access;
        if (isInterface) 
	  access = new InterfaceAccess(Access.ACC_PUBLIC | Access.ACC_INTERFACE);
        else 
	  access = new ClassAccess(Access.ACC_PUBLIC);
        // don't generate constructors - interfaces don't need them and stubs create their own
       	cfg = new ClassFileGenerator(access,
       	                             fullyQualifiedClassName,
       	                             (isInterface ? null : superClass), // super class
       	                             false, //  no zero arg constructor
				     stream);
      }
      catch (ClassException e) {
      	System.err.println("Cannot instantiate class file generator - byte code generation aborted.  " + e);
	toggleJavaC();
      }
    }

    InterfaceInfo[] interfaceInfos = null;
    if (isInterface)
      interfaceInfos = (ovrClassInfo == null ? null : ovrClassInfo.getInterfaces());
    generateHeader (imports, superClass, interfaces, interfaceInfos);
    increaseIndent (2);
    generateFields (attributes, classInheritancePath);
    generateConstructors ();
    generatePropertyAccessors (attrTypes, attrNames, readable, writable, isStatic, defClasses, initVals, typeDescrpns, systemDefined);
    generateMethods (m, ovrClassInfo, false); // all methods
    decreaseIndent (2);
    endClass ();
  }

  /** Returns a byte array containing the byte-code that implements this class.
  **/
  public byte[] getByteCodeForClass() {
    byte[] bytes = cfg.createClass();
    return bytes;
  }

  /** Merge a class into this stub
   */
  public void mergeClass(FileInputStream fileStream)  {
    cfg.mergeClass(fileStream);
  }

  /** Returns a byte array containing the byte-code that implements this class.
  **/
  public byte[] writeClass() throws java.io.IOException {
    byte[] bytes = null;
    bytes = cfg.writeClass();
    return bytes;
  }

  @Override
  protected void endClass () {
    //    iprintln ("}");
  }

  private String[] createJavaSymbolVariableNames (boolean[] systemDefined, Symbol[] attrNames, boolean[] staticQ) {
    int numAttributes = attrNames.length;
    String[] symVarNames = new String[numAttributes];
    for (int i=0; i<numAttributes; i++) {
      if (systemDefined[i]) {
	symVarNames[i] = "SystemAttributeSymbols." + createJavaSymbolVariableName (attrNames[i]);
      } else {
      symVarNames[i] = createJavaSymbolVariableName (attrNames[i]);
      if (staticQ[i])
	symVarNames[i] += "FOR_CLASS_";
      }
    }
    return symVarNames;
  }

  // Fields are generated in generatePropertyAccessors()
  protected void generateFields (AttrInfo attributes,
		       Symbol[] classInheritancePath) {

    // Add private info about G2 inhertiance
    // if this is a system class, we already have the symbols loaded
    //   then add
    //      public static final Symbol NAME_ = com.gensym.util.symbol.G2ClassSymbols.NAME_
    //   else
    //      public static final Symbol NAME_ = Symbol.intern("NAME");

    String sym = createJavaSymbolVariableName (Symbol.intern (className));
    try {
      Expression cs = null;
      if (isSystemClass) {
	cs =  new FieldRef(G2CLASSSYMBOLS_CLASS_NAME,
			  sym,
			  SYMBOL_CLASS_DESC,
			  true);

	cfg.addField(sym,
		     SYMBOL_CLASS_DESC,
		     PUBLIC_STATIC_FINAL_ACCESS,
		     cs,
		     true); // static field	

      } else {
	MethodRef mrc = new MethodRef(SYMBOL_CLASS_NAME,
				      "intern",
				      "(Ljava/lang/String;)"+SYMBOL_CLASS_DESC);
	MethodCall mc =  new MethodCall(mrc,
					new Expression[] { new Value(className)},
					MTH_CALL_STATIC);
	
	FieldRef fr =  new FieldRef(cfg.getClassName(),
				    sym,
				    SYMBOL_CLASS_DESC,true);
	cfg.addField(sym,
		     SYMBOL_CLASS_DESC,
		     PUBLIC_STATIC_FINAL_ACCESS,
		     mc,
		     true); // static field	
	
	cs = fr;
      }
      
      cfg.addField("g2ClassName",
      	   SYMBOL_CLASS_DESC,
      	   PUBLIC_STATIC_FINAL_ACCESS,
      	   cs,
      	   true); // static field


      //iprint ("static final Symbol[] classInheritancePath = new Symbol[] {");
      Expression[] symbolArrayContents = new Expression[classInheritancePath.length];
      for (int i=0; i<classInheritancePath.length; i++) {
	String symbolLocation = getJavaTypeNameForG2Type(classInheritancePath[i]);
	// Cant refer to Symbol fields that dont exits in external Java classes
	// or G2__Base
	if (LocalStubClassLoader.BASE_JAVA_INTERFACE_NAME.endsWith(symbolLocation) ||
	    classInheritancePath[i].toString().indexOf(".") > 0) {
	  MethodRef mrc = new MethodRef(SYMBOL_CLASS_NAME,
				      "intern",
				      "(Ljava/lang/String;)"+SYMBOL_CLASS_DESC);
	  MethodCall mc =  new MethodCall(mrc,
					new Expression[] { 
	                                new Value(classInheritancePath[i].toString())},
					MTH_CALL_STATIC);
	  symbolArrayContents[i] = mc;
	} else
	  symbolArrayContents[i] = new FieldRef(getJavaTypeNameForG2Type(classInheritancePath[i]),
						createJavaSymbolVariableName (classInheritancePath[i]),
						SYMBOL_CLASS_DESC ,true);
	//System.out.println(getJavaTypeNameForG2Type(classInheritancePath[i]));
      }

      NewArray na 
	= new NewArray(SYMBOL_ARRAY_CLASS_DESC,symbolArrayContents);

      cfg.addField(LocalClassFriendAccess.CLASS_INH_FIELD_NAME,
      	   SYMBOL_ARRAY_CLASS_DESC,
      	   PUBLIC_STATIC_FINAL_ACCESS,
      	   na,
      	   true); // static field


      //MethodRef forNameMethod = new MethodRef("java.lang.Class",
      //				      "forName",
      //				      "(Ljava/lang/String;)Ljava/lang/Class;");
      //
      //MethodCall invokeForName = new MethodCall(forNameMethod, 
      //					new Expression[] {new Value(cfg.getClassName())},
      //					MethodCall.MTH_CALL_STATIC);


      MethodRef recordClassMethod = new MethodRef("com.gensym.g2export.G2ClassManager",
						  "recordG2ClassNameForClass",
						  "(Lcom/gensym/util/Symbol;Ljava/lang/String;)Z");

      MethodCall recordClassCall = 
	new MethodCall(recordClassMethod,
		       new Expression[] { cs, 
					  new Value(packageName + "." + javaClassName) },
		       MethodCall.MTH_CALL_STATIC);
      
      cfg.addField("recordedClass",
		   "Z",
		   PUBLIC_STATIC_FINAL_ACCESS,
		   recordClassCall,
		   true);

    } catch (ClassException e) {
      throw new StubCreationException("Class Generation failure during field generation, exception was " + e.toString());
    }

  }

  protected void generateHeader (String[] imports,
				 String superClass,
				 String[] interfaces,
				 InterfaceInfo[] interfaceInfos) {
    if (interfaces != null) {
      for (int i = 0; i < interfaces.length; i++) {
      	if (!useJavaC) {
	  // DBCG
	  //	  System.out.println("Implementing interface " + qualifyConditionally(interfaces[i])); // DEBUG
	  cfg.implementInterface(qualifyConditionally (interfaces[i]));
	  // GCBD
        }
      }
    }
    if (interfaceInfos != null)
      for (int i = 0; i < interfaceInfos.length; i++) 
	cfg.implementInterface(interfaceInfos[i]);
    
  }

  @Override
  protected void generateConstructors () {
    if (!isInterface) {
      // This creates a single constructor which invokes super().  There is no bcg to do here, 
      // because the ClassInfo constructor (in the cfg) does this for us
    }
  }
    
  void generatePropertyAccessors (Symbol[] slotTypes,
				  Symbol[] slotNames,
				  boolean[] readable,
				  boolean[] writable,
				  boolean[] isStatic,
				  Symbol[] definingClasses,
				  Object[] initialValues,
				  G2Type[] typeSpecifications,
				  boolean[] systemDefined) {
    //    if (isG2ProxyObjectClass) return; // not needed in proxy class

    String[] jSlotNames = new String[slotNames.length];
    String[] jSlotTypes = new String[slotNames.length];
    int[] generationFlags = new int[slotNames.length];
    for(int i = 0; i < slotNames.length; i++) {
      jSlotNames[i] = getJavaPropertyNameForG2Slot (slotNames[i]);
      jSlotTypes[i] = getJavaTypeNameForG2Type(slotTypes[i]);
      // indicate whether this property is readble and/or writable and/or static
      generationFlags[i] = (readable[i] ? PROPERTY_GETTER : 0) |
      	(writable[i] ? PROPERTY_SETTER : 0) |
      	(isStatic[i] ? PROPERTY_STATIC : 0);
    }
       
    if (!isInterface)
      generatePropertyAccessors (jSlotTypes, jSlotNames, slotNames, generationFlags, typeSpecifications, definingClasses, initialValues, systemDefined);
    else
      generatePropertyAccessDeclarations (jSlotTypes, jSlotNames, slotNames, generationFlags, typeSpecifications, systemDefined, initialValues);
  }

  void generatePropertyAccessors (String[] jSlotTypes,
				  String[] jSlotNames,
				  Symbol[] slotNames,
				  int[] generationFlags,
				  G2Type[] typeSpecifications,
				  Symbol[] definingClasses,
				  Object[] initVals,
				  boolean[] systemDefined) {
    //    G2ClassTranslator.generatePropertyAccessors (output, jSlotTypes, jSlotNames, className);
    throw new InternalError ("Should never call ClassGenerationContext::generatePropertyAccessors");
  }

  Expression byteCodeForInitialValue(Object initVal, String type, boolean isStatic) {
    String wrapperClass = ClassFileGenerator.getWrapperClass(type);
    String typeDesc = ClassFileGenerator.getVMDescriptorForJavaType(type);
    try {
      Value value = null;
      if (initVal instanceof Boolean) value = new Value(((Boolean) initVal).booleanValue());
      if (initVal instanceof Integer) value = new Value(((Integer) initVal).intValue());
      if (initVal instanceof String) value = new Value((String) initVal);
      if (initVal instanceof Double) value = new Value(((Double) initVal).doubleValue());
      if (value == null) value = new Value(initVal);
      if (wrapperClass.equals("")) {
	// return (<type>) <varName>;
	return new Cast(typeDesc, value);
      }
      else {
	String wrapperDesc = ClassFileGenerator.getVMDescriptorForJavaType(wrapperClass);
	// return ((<wrapperClass) varName).<accessorMethod>()
	Expression wrapperCast = new Cast(wrapperDesc, value);
	MethodRef accessorRef = new MethodRef(wrapperClass, 
					      ClassFileGenerator.getAccessorMethod(type), 
					      "()" + typeDesc);
	return new MethodCall(wrapperCast, 
			      accessorRef, 
			      new Expression[] {}, 
			      (isStatic ? MTH_CALL_STATIC : MTH_CALL_VIRTUAL));
      }
    }
    catch (ClassException ce) {
      ce.printStackTrace(System.err);
    }
    return null;
  }


  void generatePropertyAccessDeclarations (String[] types, String[] names, Symbol[] g2Names,
					   int[] generationFlags, G2Type[] typeSpecifications,
					   boolean[] systemDefined, Object[] initVals) {
    for(int i = 0; i < names.length; i++) { 
      //if (systemDefined[i])
      //break;
      Symbol currentSlot_ = g2Names[i];
      String currentSlot = names[i];
      String currentType = types[i];
      Object initialValue = initVals[i];
      boolean staticQ    = (generationFlags[i] & PROPERTY_STATIC) != 0;
      if (staticQ) break;
      String fieldName   = G2ClassTranslator.initCap(makeFieldNameForSlot(currentSlot, staticQ));
      String slotVarName = ensureLegalJavaVariableName (currentSlot);
      boolean getterExists = (generationFlags[i] & PROPERTY_GETTER) != 0; // readable property - generate getter
      boolean setterExists = (generationFlags[i] & PROPERTY_SETTER) != 0; // writable property - generate setter
      G2Type type = typeSpecifications[i];

      /*      if (fieldName.equals ("Text")) { // always generate getter & setter for "Text" property
	getterExists = setterExists = true;
	currentType  = "java.lang.String";
      }*/
      if (getterExists) {
      	String getterMethodName = "get" + fieldName;
	String getterInterface = ("public " + currentType + " " + getterMethodName + "();\n");
	Sequence intfSig = com.gensym.jgi.download.MethodInfo.getMethodSignatureAsSequence(getterInterface);
	if (!methodAlreadyDefined(intfSig)) {
	  if (!useJavaC) {
	    // DBCG
	    //  method descriptor for get<slotName>() method is <()<javaType>;>
	    String getterMethodDescriptor = "()" + cfg.getVMDescriptorForJavaType(currentType);
	    cfg.addMethod(getterMethodName, 
			  getterMethodDescriptor, 
			  null, 
			  PUBLIC_ABSTRACT_ACCESS, 
			  new ClassRef[] {}); // no args, no exceptions
	    // GCBD
	  }
	  recordOpInterfaceSignature(intfSig);
	}
      }

      if (setterExists) {
      	String setterMethodName = "set" + fieldName;
	String setterInterface = ("public void " + setterMethodName + "(" + currentType + " " + slotVarName + ");\n");
	Sequence intfSig = com.gensym.jgi.download.MethodInfo.getMethodSignatureAsSequence(setterInterface);
	if (!methodAlreadyDefined(intfSig)) {
	  if (!useJavaC) {
	    // DBCG
	    //  method descriptor for set<slotName>(<javaType>) method is <(<javaType>;)>
	    String setterMethodDescriptor = "(" + cfg.getVMDescriptorForJavaType(currentType) + ")V";
	    cfg.addMethod(setterMethodName, 
			  setterMethodDescriptor, 
			  new String[] {slotVarName}, 
			  PUBLIC_ABSTRACT_ACCESS, 
			  new ClassRef[] {}); // arg is slotVarName, no exceptions
	    // GCBD
	  }
	  recordOpInterfaceSignature(intfSig);
	}
      }
    }
  }

  /**
   * Generate the method interface for each exported G2 method stub and any overrides
   * for this class.
   * Rules of engagement:
   * If an override exists of the same signature as a G2 method stub, then G2 method stub
   * is not used...as the override can define additional throw clauses
   */
  void generateMethods (com.gensym.jgi.download.MethodInfo[] methodInfoArray,
			ClassInfo ovrClassInfo,
			boolean generateMethodsForExternalEventListenerClass) {

    // Make a list of Item methods names
    Sequence itemMethods = getItemMethods();
    
    if (methodInfoArray != null)
      for (int i =0; i<methodInfoArray.length; i++) {
        com.gensym.jgi.download.MethodInfo methodInfo = methodInfoArray[i];
        outputMethodInfoInterface(methodInfo, 
				  itemMethods, 
				  opSignatures, 
				  false, 
				  generateMethodsForExternalEventListenerClass);
	
        // If this method is a add/remove listener interface, we need to
        // add a secondary version that allows external listeners to add/remove themselves
        if (methodInfo.isAddListenerMethod() || methodInfo.isRemoveListenerMethod())
	  outputMethodInfoInterface(methodInfo, 
				    itemMethods, 
				    opSignatures, 
				    true, // Switch on External interface add/remove
				    false);
      }

    
    if (ovrClassInfo != null) {
      com.gensym.classtools.MethodInfo[] ovrmethods = ovrClassInfo.getMethods();
      Access methodAccess = PUBLIC_ABSTRACT_ACCESS;
      for (int i=0; i<ovrmethods.length; i++) {
	com.gensym.classtools.MethodInfo ovrmethod = ovrmethods[i];
	Access access = ovrmethod.getAccess();
	if (!ovrmethod.getName().equals("<init>")  && access.isPublic() && !access.isStatic()) { 
	  //System.out.println("Adding Override method " + ovrmethod);
	  cfg.addMethodIgnoreMergeProblems(ovrmethod.getName(),
			ovrmethod.getDescriptor(),
			null,
			methodAccess ,
			null);
	}
      }
    }
  }
  
  /**
   * @param generateExternalAddRemoveListenerInterface Define the first param of a Add/Remove Listener method
   *        to be an ExternalG2EventListener Class Name 
   * @param externalListenerInterface The Method in intended for an external G2 Listener interface
   *        and any G2 Events Class param types should be convered to External G2 Event Object classes
   */
  private void outputMethodInfoInterface(com.gensym.jgi.download.MethodInfo methodInfo,
					 Sequence itemMethods,
					 Sequence opSignatures, 
					 boolean generateExternalAddRemoveListenerInterface,
					 boolean externalListenerInterface) {
    boolean conflict = false;

    if (methodInfo.isActive()) {

      // No statics in an interface !
      	if (!conflict) {
      	  if (!useJavaC) { // DBCG for item method
      	    Sequence g2ReturnType = methodInfo.getResultTypes();
       	    Sequence g2ParameterTypes = methodInfo.getArgumentTypes();
            String[] paramNames = methodInfo.getArgumentNamesAsStrings();
	    ClassRef[] exceptions = new ClassRef[] {};
	    String javaMethodName = G2ClassTranslator.createJavaNameFromG2Name(methodInfo.getG2MethodName());
	    if (javaMethodName.indexOf('$') == -1)
	      cfg.addMethod(javaMethodName,
			    buildMethodDescriptor(g2ParameterTypes, g2ReturnType),
			    paramNames,
			    PUBLIC_ABSTRACT_ACCESS,
			    exceptions);
      	  } // GCBD
      	}
    }
  }

  protected void toggleJavaC() {
    useJavaC = !useJavaC;
  }

  /** @return true if this class has not been generated; false if the class has been generated
  **/
  public boolean isUseJavaC() {
    return useJavaC;
  }

  /**
   * Return a list of final methods that we cannot override
   */
  protected Sequence getItemMethods() {
    java.lang.reflect.Method[] methods =
      LocalStubClassLoader.BASE_JAVA_CLASS.getMethods();
    Sequence finalMethods = new Sequence();
    for (int i = 0; i< methods.length; i++)
      if (java.lang.reflect.Modifier.isFinal(methods[i].getModifiers()))
	finalMethods.addElement(methods[i]);
    return finalMethods;
  }

  /** Builds a method descriptor using the given return type(s) and parameter list.
   *  @param g2ParameterTypes the types of the g2 parameters of the method
   *  @param g2ResultTypes the g2 return types - will be enclosed within a Sequence if multiple return types are required
   *  @return a String representing the method descriptor
  **/
  public String buildMethodDescriptor(Sequence g2ParameterTypes, Sequence g2ReturnTypes)
  {
    String descriptor = "("; // start parameter list (within parentheses)
    for (int i = 1; i < g2ParameterTypes.size(); i++) {
      String paramJavaType = getMethodType(g2ParameterTypes.elementAt(i)); // get the java type definition of this param
      descriptor += ClassFileGenerator.getVMDescriptorForJavaType(paramJavaType); 
      // add VM type of this param to the descriptor
    }
    descriptor += ")"; // end parameter list
    switch (g2ReturnTypes.size()) {
      case 0: // void return type
        descriptor += "V"; // this is a void return type
        break;
      case 1: // single return type
        String returnJavaType = getMethodType(g2ReturnTypes.elementAt(0)); // get the java type defintion of the return type
        descriptor += ClassFileGenerator.getVMDescriptorForJavaType(returnJavaType); 
	// add VM type definition of return type to descriptor
        break;
      default: // multiple return types - enclose within a Sequence object
        descriptor += ClassFileGenerator.getVMDescriptorForJavaType("com.gensym.util.Sequence");
        break;
    }
    return descriptor;
  }

  /**
   * Method types may be the G2 Types as a symbol, or a Structure containing the CLass name
   */
  final String getMethodType(Object type)
  {
    Symbol g2ClassName = null;
    if (type instanceof com.gensym.util.Structure) {
      try {
	g2ClassName = (Symbol)((Structure)type).getAttributeValue(CLASS_);
      } catch (NoSuchAttributeException e) {
	throw new RuntimeException("Expected to find CLASS attribute in method result types");
      }
    } 
    else {
      g2ClassName = (Symbol)type;
    }

    String methodType = getJavaTypeNameForG2Type(g2ClassName, true);
    return methodType;
  }

  /** Removes any package prefix from the given name.
   *  @param fullName the fully qualified name of a field or class
   *  @return the name of the field or class without the package prefix
  **/
  public String stripPackage(String fullName) {
    return fullName.substring(fullName.lastIndexOf('.') + 1, fullName.length());
  } 

  /** 
  **/
  public String getPackagePrefix(String fullName) {
    return fullName.substring(0, fullName.lastIndexOf('.'));
  }
}













