
package com.gensym.jgi.download.local;

import java.io.*;
import java.util.Locale;
import java.util.Enumeration;
import java.util.Vector;
import java.util.Hashtable;
import com.gensym.types.G2Type;
import com.gensym.g2script.ClassInfoFactory;
import com.gensym.util.*;
import com.gensym.jgi.download.*;

import com.gensym.message.Trace;
import com.gensym.message.Resource;
import com.gensym.message.MessageKey;
import com.gensym.classtools.*;

public class LocalProxyStubGenerationContext extends LocalStubGenerationContext {

  private static String G2ITEMREF_FIELDNAME = "g2itemref";
  private static String G2CONTEXTREF_FIELDNAME = "context";
  private static String G2__PROXYBASE_IMPL_CLASSNAME = "com.gensym.g2export.G2__ProxyBaseImpl";

  private static MethodRef setterRef = null;
  private static MethodRef getterRef = null;
  private static MethodRef callG2ProxyRef = null;


  private String[] symVarNames;
  private String fullyQualifiedInterfaceName;
  private boolean debug = false;

  LocalProxyStubGenerationContext (OutputStream out,
				   boolean isInterface,
				   String packageName,
				   String className,
				   String version,
				   String stubExtension,
				   LocalClassNameMapper nameMapper,
				   com.gensym.g2script.Compiler compiler,
				   ClassInfoFactory factory) {

    super (out, isInterface,
	   packageName, className, 
	   version, stubExtension, 
	   nameMapper, compiler, factory);
    System.out.println("LocalProxyStubGenerationContext::<init>");
    fullyQualifiedInterfaceName = packageName + '.' + javaClassInterfaceName;
    addSlotFields = false; // get all data from G2 or proxy
    try {
      if (setterRef == null) {
	setterRef = 
	  new MethodRef(G2__PROXYBASE_IMPL_CLASSNAME,
			"_setPropertyValue",
			"(" + com.gensym.jgi.download.ClassConstants.SYMBOL_CLASS_DESC + 
			"Ljava/lang/String;I" + OBJECT_DESC + ")V");
      }
      if (getterRef == null) {
	getterRef =  new MethodRef(G2__PROXYBASE_IMPL_CLASSNAME,
				   "_getPropertyValue",
				   "(" + com.gensym.jgi.download.ClassConstants.SYMBOL_CLASS_DESC + 
				   "Ljava/lang/String;I)" + OBJECT_DESC);
      }
      if (callG2ProxyRef == null) {
	callG2ProxyRef = new MethodRef(G2__PROXYBASE_IMPL_CLASSNAME,
				       "_callG2ProxyMethod",
				       "(" + 
				       com.gensym.jgi.download.ClassConstants.SYMBOL_CLASS_DESC + 
				       "Ljava/lang/String;I" + 
				       com.gensym.jgi.download.ClassConstants.OBJECT_ARRAY_DESC +
				       ")" + OBJECT_DESC);
      } 
    } catch (ClassException e) {
      throw new ClassFileGenerationException(e, e.toString());
    }
  }

  @Override
  protected void generateHeader (String[] imports,
				 String superClass,
				 String[] interfaces,
				 InterfaceInfo[] interfaceInfos) {
    super.generateHeader (imports, superClass, interfaces, interfaceInfos);
    cfg.implementInterface("com.gensym.g2export.G2ProxyAccess");
  }

  @Override
  protected void generateConstructors () {
    super.generateConstructors();
    try {
      // add constructor to set itemRef
      /* Constructor looks like this:
	 <className>(<interfaceName> item) {
	   <className>(); // call default constructor
	   g2itemRef = item;
	   context = ((ImplAccess) item).getContext();
	 }
       */
      Block body = new Block();
      MethodRef mRef = new MethodRef(cfg.getSuperClassName(), 
				     "<init>", 
				     "(Lcom/gensym/classes/G2__Base;)V");

      Variable itemParamRef = new Variable("item", 
					   cfg.getVMDescriptorForJavaType(fullyQualifiedInterfaceName));
      MethodCall superConstructorCall = new MethodCall(mRef, 
						       new Expression[] {itemParamRef}, 
						       MTH_CALL_SPECIAL);

      body.add(superConstructorCall); // call the default constructor for this class

      body.add(new Return());

      cfg.addMethod("<init>",
		    //"(" + cfg.getVMDescriptorForJavaType(fullyQualifiedInterfaceName) + ")V",
		    "(Lcom/gensym/classes/G2__Base;)V",
		    new String[] {"item"},
		    new Access(ACC_PUBLIC),
		    body,
		    new ClassRef[] {});
    }
    catch (ClassException ce) {
      ce.printStackTrace(System.err);
    }
  }

  @Override
  protected void generateFields (AttrInfo attributes,
				 Symbol[] classInheritancePath) {
    // for field generation, see generatePropertyAccessors()
    super.generateFields(attributes, classInheritancePath);
  }

  private static final String instVarSetter = "setAttributeValue",
			      classVarSetter = "setStaticAttributeValue";


  @Override
  Block generateSetBody(PrintWriter output,
			String currentType,
			String slotVarName, // the name of the argument holding the new value
			String symVarName, // the name of the attribute to set
			Symbol g2SlotName,
			boolean staticField,
			String definingClass,
			Object initialValue,
			String setterName) {
    //System.out.println("LocalProxyStubGenerator::generateSetBody" + setterName);
    String setterFn = (staticField ? classVarSetter : instVarSetter);
    String extraArgs = (staticField ? ", classPropertyKeys, classPropertyValues" : "");
    extraArgs = "";
    if (!useJavaC) { // do some dbcg
      /* Add byte-code to implement the following:
	 public set<fieldName>(<currentType> ) {
	   _setPropertyValue(Symbol <symVarName>, 
                             String classKey, 
                             int remoteCallIndex,
			     new <Wrapper>(<slotVarName>));
	 }
       */
      try {
	Block body = new Block();
	// BLOCK CHANGE HERE - DO NOT SET FIELD VALUE, CALL G2
	Expression argVar = new Variable(slotVarName, cfg.getVMDescriptorForJavaType(currentType));
	Expression argRef = ClassFileGenerator.wrapPrimitiveIfNecessary(currentType,
									argVar);

	if (debug) System.out.println("desc = " + "(" + STRING_DESC + ")" + 
				      com.gensym.jgi.download.ClassConstants.SYMBOL_CLASS_DESC);

	MethodCall internSymbol = 
	  new MethodCall(new MethodRef(com.gensym.jgi.download.ClassConstants.SYMBOL_CLASS_NAME, 
				       "intern", 
				       "(" + STRING_DESC + ")" + 
				       com.gensym.jgi.download.ClassConstants.SYMBOL_CLASS_DESC),
			 new Expression[] {new Value(g2SlotName.toString())}, 
			 MTH_CALL_STATIC);

	body.add(new MethodCall(setterRef, 
				new Expression[] {internSymbol,
						  new Value(cfg.getClassName().replace('/','.')),
						  new Value(getMethodIndex()),
						  argRef}, 
				MTH_CALL_VIRTUAL));
	recordIndexedMethod(new Expression[] {new Value(currentType)},
                            setterName);

	body.add(new Return());
	//System.out.println("LocalProxyStubGenerator::generateSetBody Exit" + setterName);
	return body;
      }
      catch (ClassException ce) {
	ce.printStackTrace(System.err);
	throw new ClassFileGenerationException(ce, "");
      }
    }
    System.out.println("LocalProxyStubGenerator::generateSetBody Exit" + setterName);
    return null;
  }

  private static final String instVarGetter = "getAttributeValue",
			      classVarGetter = "getStaticAttributeValue",
                              textVarGetter = "getAttributeTextValue";

  @Override
  Block generateGetBody (PrintWriter output,
			 String currentType,
			 String slotVarName,
			 String symVarName,
			 Symbol g2SlotName,
			 boolean staticField,
			 String definingClassName,
			 Object initialValue,
			 String getterName) {

    //System.out.println("LocalProxyStubGenerator::generateGetBody " + getterName);
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
	Block body = new Block();
	// BLOCK CHANGE HERE - DON'T GET FIELD, CALL G2 AND GET IT TO GET FIELD
	MethodCall internSymbol = 
	  new MethodCall(new MethodRef(com.gensym.jgi.download.ClassConstants.SYMBOL_CLASS_NAME,
				       "intern",
				       "(" + STRING_DESC + ")" + 
				       com.gensym.jgi.download.ClassConstants.SYMBOL_CLASS_DESC),
			 new Expression[] {new Value(g2SlotName.toString())},
			 MTH_CALL_STATIC
			 );

	MethodCall getPropertyCall = 
	  new MethodCall(getterRef, 
			 new Expression[] {internSymbol,
					     new Value(cfg.getClassName().replace('/','.')),
					     new Value(getMethodIndex())}, 
			 MTH_CALL_VIRTUAL);

	recordIndexedMethod(new Expression[0],
			    getterName);

 	// now cast the returned object to whatever type we require
	Expression objCast = ClassFileGenerator.doCast(currentType, getPropertyCall);
        body.add(new Return(objCast));
	return body; 
      }
      catch (ClassException e) {
	e.printStackTrace(System.err);
	toggleJavaC(); // abandon all hope of generating byte code
	return null;
      }
    }
  }

  /**
   *  Produce a local implementation for a G2 method stub 
   *  @param cfg the class file generator to use when producing byte-code 
   *  (null if no byte-code being generated).
   */
  @Override
  boolean generateLocalMethodImplementation(com.gensym.jgi.download.MethodInfo mi,
					    boolean opAddRemoveInterface) {
    if (debug) System.out.println("LPSGC::generateLocalMethodImplementation");

    boolean dbcg = (cfg != null); // directly generate byte-code if cfg is not null

    // block to hold method body
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
    Expression[] methodArguments = new Expression[argumentNames.size()-1]; 
    Expression[] methodArgTypes = new Expression[argumentNames.size()-1];
    if (debug) {
      String[] nams = mi.getArgumentNamesAsStrings();
      for (int i = 0; i < nams.length; i++)
	System.out.println("Arg " + i + " = " + nams[i]);
    }

    int argumentCount = 0;
    int localRef = 1; // the local var to refer to
    Enumeration names = argumentNames.elements();
    names.nextElement(); // HACK - get rid of self

    while (names.hasMoreElements()) {

      argName = (String) names.nextElement();
      Object argType = argTypes.nextElement();
      String argJavaType = getMethodType(argType);
      methodArgTypes[argumentCount] = new Value(argJavaType);

      String argVMDesc = cfg.getVMDescriptorForJavaType(argJavaType);
      if (debug) {
	System.out.println("Arg Name: " + argName + "; type = " + argJavaType + "; " + argVMDesc);
      }
      if (dbcg) { // DBCG
        try { 
          String wrapperClass = ClassFileGenerator.getWrapperClass(argJavaType);
 	  if (debug) {
	    System.out.println("argumentCount = " + argumentCount + "; type = " + argJavaType);
	    //System.out.println("Wrapper = " + wrapperClass);
	  }
	  Expression argExpr = new Variable(localRef++, argVMDesc);
	  methodArguments[argumentCount] = 
	    ClassFileGenerator.wrapPrimitiveIfNecessary(argJavaType,
							argExpr);
	  argumentCount++;
	  if (argJavaType.equals("double") || argJavaType.equals("long"))
	    localRef++;
        }
        catch (ClassException ce) {
          ce.printStackTrace(System.err);
          dbcg = !dbcg; // failed to generate byte-code - give up
        }
      } // GCBD
    }

    try {
      String returnType = mi.getJavaReturnType();
      if (debug) System.out.println("returnType = " + returnType);
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

      Expression[] callArgs = new Expression[4];

      MethodRef internRef = new MethodRef("com.gensym.util.Symbol",
					  "intern",
					  "(" + STRING_DESC  + ")" + 
					  com.gensym.jgi.download.ClassConstants.SYMBOL_CLASS_DESC);
      MethodCall internSymbol = new MethodCall(internRef,
					       new Expression[] {new Value(mi.getG2MethodName().toString())},
					       MTH_CALL_STATIC);
      callArgs[0] = internSymbol;
      callArgs[1] = new Value(cfg.getClassName().replace('/','.'));
      callArgs[2] = new Value(getMethodIndex());
      callArgs[3] = new NewArray(com.gensym.jgi.download.ClassConstants.OBJECT_ARRAY_DESC, 
				 methodArguments);
      Expression initVal = new MethodCall(callG2ProxyRef, 
					  callArgs, 
					  MTH_CALL_VIRTUAL);
      recordIndexedMethod(methodArgTypes,
			  mi.getJavaMethodName());

      VariableDeclaration objectDecl = new VariableDeclaration("returnedObject",
							       OBJECT_DESC,
							       initVal);
      methodBody.add(objectDecl); // Object returnedObject = controller.callG2ProxyFromJava(...)

      Variable objectRef = new Variable("returnedObject", OBJECT_DESC);
      //FieldRef objectRef = new FieldRef(cfg.geClassName(),
      //				"returnedObject",
      //				OBJECT_DESC);
      //      methodBody.add(new OperatorCall("=", new Expression[] {objectRef, initVal}));


      if (returnType.equals("void"))
	methodBody.add(new Return());
      else
	methodBody.add(new Return(ClassFileGenerator.doCast(javaReturnType, objectRef)));

      cfg.addMethodIgnoreMergeProblems(mi.getJavaMethodName(),
		    buildMethodDescriptor(mi.getArgumentTypes(), mi.getResultTypes()),
		    mi.getArgumentNamesAsStrings(),
		    new Access(ACC_PUBLIC),
		    methodBody,
		    new ClassRef[] {});
    }
    catch (ClassException e) {
      e.printStackTrace(System.err);
    }
    return dbcg;
  }


}

    




