
package com.gensym.jgi.download;

import com.gensym.util.*;

import java.util.StringTokenizer;
import java.util.Enumeration;


/**
 * This class holds the raw description of a G2 method
 *
 *@author M.D.Gribble
 *@version 1.0 15/OCT/1997
 */
public class MethodInfo implements com.gensym.util.symbol.G2TypeSymbols {
  Symbol   G2MethodName;
  String   javaMethodName;
  Symbol   G2OriginalMethodName;
  boolean  isStatic;
  Sequence G2ArgumentTypes, G2ResultTypes;
  Sequence argumentNames;
  String   methodSource = "";     // Complete method
  String   G2MethodSource;
  String   methodSourceBody; // -interface
  Symbol   absoluteG2ClassReference;
  boolean  active = true;
  Symbol   superG2ClassThatDefinesReturnTypeForSignature;
  Symbol   definingG2Class;
  boolean  isAddListenerMethod;
  boolean  isRemoveListenerMethod;
  String   listenerClassName;
  Symbol   G2ListenerClassName;
  StubClassLoader stubClassLoader;

  private static String _addJavaListenerMethodName = 
                 "G2JavaStubController.getG2JavaStubController().addJavaListenerToG2EventSource";
  private static String _removeJavaListenerMethodName = 
                 "G2JavaStubController.getG2JavaStubController().removeJavaListenerFromG2EventSource";

  private boolean debug = false;

  protected MethodInfo (Symbol G2MethodName, 
	    boolean isStatic, 
	    Sequence G2ArgumentTypes, 
	    Sequence G2ResultTypes,
	    String   G2MethodSource,
	    Symbol   definingG2Class,
	    Symbol   absoluteG2ClassReference,
	    StubClassLoader stubClassLoader)
  {
    int num_arguments = 0;
    if (G2ArgumentTypes != null)
      num_arguments = G2ArgumentTypes.size();

    this.G2MethodName    = G2MethodName;
    this.javaMethodName  = G2ClassTranslator.createJavaNameFromG2Name(G2MethodName);
    this.G2OriginalMethodName = G2MethodName;
    this.isStatic      = isStatic;
    this.G2ArgumentTypes = G2ArgumentTypes;
    this.argumentNames = new Sequence();
    this.G2ResultTypes   = G2ResultTypes;
    this.G2MethodSource  = G2MethodSource;
    this.definingG2Class = definingG2Class;
    this.absoluteG2ClassReference = absoluteG2ClassReference;
    this.stubClassLoader = stubClassLoader;

    // Extract method parameters, as they are not send to us
    // If there is no methodSource, then we will generate them here
    // otherwise extract them from the source
    if ("".equals(methodSource))
      {
	// Make our own parameters	
	if (!isStatic)
	  argumentNames.addElement("this");  // first argument will always be this

	for (int i = 1; i < num_arguments; i++)
	  argumentNames.addElement("arg" + i);

      }
    else
      {
	setArgumentNames(methodSource);

	// Get method body source
	int start_pos = methodSource.indexOf("{");
	int end_pos = methodSource.lastIndexOf("}");

	if (start_pos != -1 && end_pos != -1 && end_pos > start_pos+1) 
	  this.methodSourceBody = methodSource.substring(start_pos+1, end_pos);
	
      }

    // Check if we are a add/remove Listener interface of the form
    // void addXXXListener(XXXListener listener) or void removeXXXListener(XXXListener listener)
    if (num_arguments == 2 && // g2 methods always have this as first param
	G2ResultTypes.isEmpty() && 
	javaMethodName.endsWith("Listener")) {
      
      // Make sure the first argument class name matches the
      // methodName
      G2ListenerClassName = getMethodG2Type(G2ArgumentTypes.elementAt(1));
      boolean isRootG2ListenerClass = 
	StubClassLoader.isG2ClassG2EventListenerClass(G2ListenerClassName);
      String G2ListenerFromMethodName = G2MethodName.toString();
      G2ListenerFromMethodName = G2ListenerFromMethodName.substring(G2ListenerFromMethodName.indexOf("-") + 1);

      isAddListenerMethod = (javaMethodName.startsWith("add", 0));
      if (isAddListenerMethod) {
	listenerClassName = javaMethodName.substring(3);
	// an adder if first param is the listener class and the class is not the root G2 listener class
	isAddListenerMethod = (G2ListenerClassName.toString().equals(G2ListenerFromMethodName) &&
			       !isRootG2ListenerClass);
      }
      isRemoveListenerMethod = (javaMethodName.startsWith("remove", 0));
      if (isRemoveListenerMethod) {
	listenerClassName = javaMethodName.substring(6);
	// an remover if first param is the listener class and the class is not the root G2 listener class
	isRemoveListenerMethod = ( G2ListenerClassName.toString().equals(G2ListenerFromMethodName) &&
				  !isRootG2ListenerClass);
      }

    }

    //System.out.println("G2MethodName: " + G2MethodName);
    //System.out.println("isStatic:" + isStatic);
    //System.out.println("G2argumentTupes" + G2ArgumentTypes);
    //System.out.println("G2ResultTypes" + G2ResultTypes);
    //System.out.println("methodSource" + methodSource);
  }

  /**
   * Get a sequence representing the signature of a Java Interface
   */
  public static Sequence getMethodSignatureAsSequence(String signature)
  {
    Sequence sigSeq = new Sequence(5);

    int start_pos = signature.indexOf("(");

    if (start_pos < 1)
      return sigSeq;

    StringTokenizer tknzr = new StringTokenizer (signature.substring(0, start_pos)," \t\n\r,");
    String token = "";
    String lastToken = "";
    while (tknzr.hasMoreTokens ()) {
      lastToken = token;
      token = tknzr.nextToken ();
    }

    sigSeq.addElement(lastToken);  // This should be the return type
    sigSeq.addElement(token);      // The method name

    int end_pos = signature.indexOf(")");
    String params_sec = "";

    if (start_pos != -1 && end_pos != -1 && end_pos > start_pos+1) 
      {
	params_sec = signature.substring(start_pos+1,end_pos);

	// Extract from source
	StringTokenizer st = new StringTokenizer(params_sec," \t\n\r,");
	    
	while (st.hasMoreTokens()) {
	  token = st.nextToken(); // Type
	      
	  //System.out.println("Got param type..." + token);
	  sigSeq.addElement(token);

	  if (token.equals(")"))  // last parameter
	    break;
	  token = st.nextToken(); // param_name or ","

	}
      }     

    return sigSeq;

  }
    


  /**
   * Read the argument names for this method from the Java interface text given
   */
  void setArgumentNames(String signature)
  {
    	// Get Parameter names from declarations of exported code
	int start_pos = signature.indexOf("(");
	int end_pos = signature.indexOf(")");
	String params_sec = "";
	
	// First name will always be this for instance methods
	if (!isStatic)
	  argumentNames.addElement("this");

	if (start_pos != -1 && end_pos != -1 && end_pos > start_pos+1) 
	  {
	    params_sec = signature.substring(start_pos+1,end_pos);

	    String token;
	    // Extract from source
	    StringTokenizer st = new StringTokenizer(params_sec," \t\n\r,");

	    while (st.hasMoreTokens()) {
	      token = st.nextToken(); // Type

	      if (token.equals(")"))  // last parameter
		break;
	      token = st.nextToken(); // param_name or ","

	      //System.out.println("Got param name..." + token);

	      argumentNames.addElement(token);
	    }
	  }
  }

  /**
   * Get Java method name from MethodInfo
   */
  public String getJavaMethodName()
  {
    return javaMethodName;
  }

  /**
   * Create a Java method comment for this G2 stub
   */
  String generateInterfaceComment()
  {
    StringBuffer op = new StringBuffer(201);
    int numResultTypes = G2ResultTypes.size();

    op.append("/**\n");
    op.append(" * Auto Generated method for G2 Method\n");
    op.append(" * " +  definingG2Class.toString() + "::" + G2OriginalMethodName.toString() + "\n");
    if (numResultTypes > 0)
      op.append(" * @return the return from calling " + G2OriginalMethodName.toString() + "\n");
    op.append(" * @exception G2AccessException if there are any communication problems");
    op.append("\n * (");

    int i = 0;
    Enumeration names = argumentNames.elements();
    for (Enumeration args = G2ArgumentTypes.elements(); 
	 args.hasMoreElements(); 
	 i++) {

      if (i > 0) {
	op.append(",");
      }

      Object argType = args.nextElement();
      String argName = (String)names.nextElement();

      op.append(argName + ":" + getMethodG2TypeWithClass(argType));
    }
    
    op.append(") = ("); 

    String resultType;

    // If G2 expects to send back more than one return, it will be received in 
    // a Sequence
    
    if (numResultTypes == 0)
      resultType = "void";
    else if (numResultTypes == 1) {
	op.append(getMethodG2TypeWithClass(G2ResultTypes.elementAt(0)));
      }
    else // multiple arguments returned in Sequence
      {
	i = 0;
	for (Enumeration resTypes = G2ResultTypes.elements(); 
	     resTypes.hasMoreElements(); 
	     i++) {
	    if (i > 0) {
	      op.append(",");
	    }
	    op.append(getMethodG2TypeWithClass(resTypes.nextElement())); 
	}
      }

    op.append(")\n */");

    return op.toString();
  }

  public String getJavaReturnType() {
    int numResultTypes = G2ResultTypes.size();
    if (numResultTypes == 0)
      return "void";
    else if (numResultTypes == 1) {
      if (debug){
    	  System.out.println("MI::resultTypes = " + G2ResultTypes.elementAt(0));
      }
      return getMethodG2Type(G2ResultTypes.elementAt(0)).toString();
    }
    else // multiple arguments returned in Sequence
      return "com.gensym.util.Sequence";
  }

  /**
   * Return a method interface from the information defined in this MethodInfo
   *
   * @param generateExternalAddRemoveListenerInterface Define the first param of a Add/Remove Listener method
   *        to be an ExternalG2EventListener Class Name 
   * @param externalListenerInterface The Method in intended for an external G2 Listener interface
   *        and any G2 Events Class param types should be convered to External G2 Event Object classes
   */
  public String generateMethodInterface(ClassGenerationContext cc,
				 boolean generateExternalAddRemoveListenerInterface, 
				 boolean externalListenerInterface) {
    
    int i = 0;
    boolean ignoreFirst = false;
    String javaListenerClassName = null;

    StringBuffer argStrBuf = new StringBuffer(100);

    // Static references need a context
    if (isStatic) { 
	argStrBuf.append("G2Access context, int timeout"); 
	i = 2;
      }
    else
      // Ignore the first argument type as in G2 the first arg of a method is self
      ignoreFirst = true;

    Enumeration names = argumentNames.elements();
    for (Enumeration args = G2ArgumentTypes.elements(); 
	 args.hasMoreElements(); 
	 i++) {
	if (ignoreFirst) {
	    args.nextElement();
	    names.nextElement();
	    ignoreFirst = false;
	    i--;
	    continue;
	  }
	if (i > 0) {
	  argStrBuf.append(",");
	}
	Object argType = args.nextElement();
	String argName = (String)names.nextElement();
	String argJavaType = getMethodType(cc, argType);

	// If generateExternalAddRemoveListenerInterface is turned on then the first argument is an
	// external listener
	if (i == 0 && generateExternalAddRemoveListenerInterface) {
	  argJavaType = StubClassLoader.getExternalG2ListenerClassName(argJavaType);
	  javaListenerClassName = argJavaType;
        }

	if (externalListenerInterface) {
	  if (stubClassLoader.isG2EventClass(getMethodG2Type(argType))) {
	    argJavaType = getFullQExternalG2EventClassName(argJavaType);
	  }
	}

	argStrBuf.append(argJavaType + " " + argName );
      }
    

    String resultType;

    // If G2 expects to send back more than one return, it will be received in 
    // a Sequence
    int numResultTypes = G2ResultTypes.size();
    if (numResultTypes == 0)
      resultType = "void";
    else if (numResultTypes == 1) {
	resultType = MethodInfo.getMethodType(cc, G2ResultTypes.elementAt(0));

      }
    else { // multiple arguments returned in Sequence
	resultType = cc.getJavaTypeNameForG2Type (SEQUENCE_);
      }
      

    // Method Name for add/remove interfaces must match the listener class
    String mName = G2ClassTranslator.createJavaNameFromG2Name(G2MethodName);
    mName = cc.ensureLegalMethodName(mName);
    if (generateExternalAddRemoveListenerInterface && javaListenerClassName != null) {
      if (isAddListenerMethod)
	mName = "add"+ javaListenerClassName;
      else if (isRemoveListenerMethod)
	mName = "remove" + javaListenerClassName;
    }

    // Now the interface
    String intfStr = "public " + 
                    (isStatic ? "static " : " ") +
                    resultType + " " +
                    mName + 
                    "(" + argStrBuf.toString() + ") throws G2AccessException";

    return intfStr;

  }

  /**
   * Return a symbol declaration Name for an RPC call for this g2 Method stub
   */
  public String generateRPCDeclarationName()
  {
    // If the method needs a abolsute class reference we must append class::

      Symbol newG2MethodName = G2MethodName;
      if (absoluteG2ClassReference != null)
	newG2MethodName = Symbol.intern(G2OriginalMethodName +
					"$"+
					absoluteG2ClassReference); 

      return "MethodName_" + ClassGenerationContext.createJavaSymbolVariableName ( newG2MethodName);
  }




  /**
   * Return a string containing the predeclared RPC Name symbol
   */
  String generateRPCDeclarartion()
  {
    String symFieldModifiersAndType = "private static final Symbol ";

    // If the method needs a abolsute class reference we must append class::
    String classRef = (absoluteG2ClassReference == null ? 
		       "" : absoluteG2ClassReference.toString() + "::");

    return symFieldModifiersAndType + generateRPCDeclarationName() + " = " +
	    "Symbol.intern (\"" + classRef + G2OriginalMethodName.toString() + "\");";
  }
  

  /**
   * Insert Any Declarations need for the generated implementations to work
   */
  static String generateImplementationDeclarations() {
    // Insert any other variables we might need
    return ("private static String NoBodyExceptionString = \"This method has no implementation for local access\";");
  }

  /**
   * Return an implementation for a G2 method stub
   */
  void generateMethodImplementation(StubGenerationContext sc, 
				    String overrideMethodBody, 
				    boolean opAddRemoveInterface) {


    sc.println("{");
    // Add code for "BY-HANDLE" access to this method
    sc.increaseIndent(2);
	
    if (isStatic)
      sc.iprintln("if (context == null) {");
    else
      sc.iprintln("if (isByHandle()) {");

    sc.increaseIndent(2);

    String overrideArgNameAt1Pos = null;

    // Add "By-handle" code for add/remove listener interfaces      
    if (opAddRemoveInterface) {
      String firstarg = (String)argumentNames.elementAt(1);

      // If opAddRemoveListener is turned on then the first argument is an
      // external listener
      String argJavaType = getMethodType(sc, G2ArgumentTypes.elementAt(1));
      Symbol argG2Type = getMethodG2Type(G2ArgumentTypes.elementAt(1));

      if (isAddListenerMethod) 
	sc.iprintln(_addJavaListenerMethodName + "(this,");
      else
	sc.iprintln(_removeJavaListenerMethodName + "(this,");

      sc.increaseIndent(10);
      sc.iprintln(generateRPCDeclarationName().toString() + ",");
      sc.iprintln("\"" + sc.getPackageName() + "." + listenerClassName + "\",");
      sc.iprintln("Symbol.intern(\"" + argG2Type + "\"),");
      sc.iprintln(firstarg + ");");
      sc.decreaseIndent(10);
    } else {

      sc.iprintln("java.lang.Object result;");
      sc.iprint("java.lang.Object[] args = new java.lang.Object[] {");

      int j = 0;

      // Enter the rest of the parameters in the arguments array
      // converting primitive types to objects where necessary
      String arg_name;
      Enumeration args = G2ArgumentTypes.elements(); 
      j = 0;
      for (Enumeration e = argumentNames.elements(); e.hasMoreElements(); j++) {
	arg_name = (String)e.nextElement();
	if (j == 1 && overrideArgNameAt1Pos != null)
	  arg_name = overrideArgNameAt1Pos;
	if (j > 0)
	  sc.print(",");
	sc.print(sc.codeToMakeObject(arg_name, getMethodType(sc, args.nextElement()) ));
      }
      sc.println("};");

      if (isStatic)
	sc.iprint("result = (java.lang.Object)context.callRPC");
      else
	sc.iprint("result = (java.lang.Object)callRPC");

      sc.print("(" +  generateRPCDeclarationName().toString() + ", args");

      if (isStatic)
	sc.print(", timeout");

      sc.println(");");

      // Any return types
      int numResultTypes = G2ResultTypes.size();
      String resultType = "";
      if (numResultTypes > 0) {
	if (numResultTypes == 1)
	  {
	    resultType = getMethodType(sc, G2ResultTypes.elementAt(0));
	  }
	else // multiple arguments returned in Sequence
	  resultType = sc.getJavaTypeNameForG2Type (SEQUENCE_);
	
	sc.iprintln("return " + 
		    StubGenerationContext.codeToGetPrimitiveValueOrCastReturnObject("result", resultType) + ";");
      }
	  
    }
    sc.decreaseIndent(2);
    sc.iprintln("}");

    // Try to write any exported body, when there is no handle, local execution
    sc.iprintln("else {");
    sc.increaseIndent(2);

    // Attempt to write method body
    boolean opCopyCode = false;
      
    if (overrideMethodBody != null && !overrideMethodBody.equals("")) {
      sc.iprintMultiLineString(overrideMethodBody);
      opCopyCode = true;
    }
    else if (methodSourceBody != null){
      sc.iprintln(methodSourceBody);
      opCopyCode = true;
    } 

    if (!opCopyCode) {
      sc.iprintln("// No MethodBody for by-copy exported");
      sc.iprintln("throw new RuntimeException(NoBodyExceptionString);");
    }
	
    sc.decreaseIndent(2);
    sc.iprintln("}");
    sc.decreaseIndent(2);
    sc.iprintln("}");
	
  }

  /**
   * Get the G2 type as a string from type, which may be a Symbol or a Structure
   * If the G2 type is a CLASS, "CLASS" will be appended
   */
  private static final String getMethodG2TypeWithClass(Object type)
  {
    
    if (type instanceof com.gensym.util.Structure)
      {
	try {
	  return "CLASS " + ((Symbol)((Structure)type).getAttributeValue(CLASS_)).toString();
	} catch (NoSuchAttributeException e) {
	  throw new RuntimeException("Expected to find CLASS attribute in method result types");
	}
      } 
    else
      return ((Symbol)type).toString();
  }


  /**
   * Get the G2 type as a string from type, which may be a Symbol or a Structure
   */
  private static final Symbol getMethodG2Type(Object type)
  {
    
    if (type instanceof com.gensym.util.Structure)
      {
	try {
	  return ((Symbol)((Structure)type).getAttributeValue(CLASS_));
	} catch (NoSuchAttributeException e) {
	  throw new RuntimeException("Expected to find CLASS attribute in method result types");
	}
      } 
    else
      return ((Symbol)type);
  }
    
  /**
   * Method types may be the G2 Types as a symbol, or a Structure containing the CLass name
   */
  static final String getMethodType(ClassGenerationContext classGenerationContext, Object type)
  {
    //    Thread.dumpStack(); // DEBUG
    if (type instanceof com.gensym.util.Structure)
      {
	try {
	  return  classGenerationContext.getJavaTypeNameForG2Type((Symbol)((Structure)type).getAttributeValue(CLASS_));
	} catch (NoSuchAttributeException e) {
	  throw new RuntimeException("Expected to find CLASS attribute in method result types");
	}
      } 
    else
      return classGenerationContext.getJavaTypeNameForG2Type ((Symbol)type);
  }


  public boolean isStatic() {
    return isStatic;
  }

  public boolean isAddListenerMethod() {
    return isAddListenerMethod;
  }

  public boolean isRemoveListenerMethod() {
    return isRemoveListenerMethod;
  }

  public boolean isActive() {
    return active;
  }

  public void setActive(boolean status) {
       active = status;
  }

  public Symbol getDefiningG2Class() {
    return definingG2Class;
  }

  public Symbol getAbsoluteG2ClassReference() {
    return absoluteG2ClassReference;
  }

  public String getG2MethodSource() {
    return G2MethodSource;
  }

  public Sequence getArgumentTypes() {
    return G2ArgumentTypes;
  }

  public Sequence getResultTypes() {
    return G2ResultTypes;
  }

  public Sequence getArgumentNames() {
    return argumentNames;
  }

  public String[] getArgumentNamesAsStrings() {
    String[] paramNames;
    if (!isStatic) {
      paramNames = new String[argumentNames.size() - 1];
      for (int i = 1; i < argumentNames.size(); i++) // first arg is the class itself - not required
        paramNames[i-1] = (String) argumentNames.elementAt(i);
    }
    else {
      paramNames = new String[argumentNames.size() + 2];
      paramNames[0] = "context"; // static methods require a G2 context param
      paramNames[1] = "timeout"; // and a timeout param
      for (int i = 0; i < argumentNames.size(); i++) // include all params
        paramNames[i+2] = (String)argumentNames.elementAt(i);
    }
    return paramNames;
  }

  public String[] getAllArgumentNamesAsStrings() {
    String[] argNames = new String[argumentNames.size()];
    for (int i = 0; i < argumentNames.size(); i++)
      argNames[i] = (String) argumentNames.elementAt(i);
    return argNames;
  }

  /**
   * Get G2 method name from MethodInfo
   */
  public Symbol getG2MethodName()
  {
    return G2MethodName;
  }

  /**
   * Return the External name of an G2 Listener Interface class
   */
  static String getFullQExternalG2EventClassName(String className) {
    // check for package
    int dotPos = className.lastIndexOf(".");
    if (dotPos > 1) {
      return className.substring(0, dotPos) + ".G2_" + className.substring(dotPos + 1);
    }
    return "G2_" + className;
  }

    public void setDebug(boolean on) {
        debug = on;
    }
}




