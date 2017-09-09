package com.gensym.jgi.download.local;

import com.gensym.classtools.*;
import java.util.*;
import java.io.FileInputStream;
import java.io.File;
import java.io.OutputStream;
import com.gensym.util.*;
import com.gensym.message.Trace;
import com.gensym.jgi.download.ClassFileGenerationException;

/** This Class is used by the stub generator (StubGenerationContext or ClassGenerationContext) 
 *  to assemble a class file for interfaces and stubs using classtools.
 */
public class ClassFileGenerator implements RuntimeConstants {

  private static Hashtable typeToDescriptorTable = new Hashtable(20);
  String className;
  boolean debug = true;

  static { 
    typeToDescriptorTable.put("void", "V");
    typeToDescriptorTable.put("int", "I");
    typeToDescriptorTable.put("double", "D");
    typeToDescriptorTable.put("float", "F");
    typeToDescriptorTable.put("boolean","Z");
    typeToDescriptorTable.put("byte", "B");
    typeToDescriptorTable.put("char", "C");
    typeToDescriptorTable.put("short","S");
    typeToDescriptorTable.put("long", "J");
    typeToDescriptorTable.put("int[]", "[I");
    typeToDescriptorTable.put("double[]", "[D");
    typeToDescriptorTable.put("float[]", "[F");
    typeToDescriptorTable.put("boolean[]","[Z");
    typeToDescriptorTable.put("byte[]", "[B");
    typeToDescriptorTable.put("char[]", "[C");
    typeToDescriptorTable.put("short[]","[S");
    typeToDescriptorTable.put("long[]", "[J");
  }

  private ClassInfo ci;
  private OutputStream outputStream;
  
  /** Constructs an instance of a ClassFileGenerator.
   *  @param classAccess access modifiers for the class to create the class file for
   *  @param className the (fully qualified) name of the class to create the class file for
   *  @param superClassName the (fully qualified) name of the direct super-class of the class 
   *  to create the class file for
   *  @param createZeroArgConstructor whether to create a default (no arguments) constructor for the class
  **/
  public ClassFileGenerator(InterfaceOrClassAccess classAccess,
			    String className,
			    String superClassName,
			    boolean createZeroArgConstructor,
			    OutputStream out) throws ClassException 
  {
    if (superClassName == null) { // implicitly java.lang.Object
      ci = new ClassInfo(classAccess, className.replace('.', '/'), createZeroArgConstructor);
    }
    else {
      ci = new ClassInfo(classAccess, className.replace('.', '/'), superClassName, createZeroArgConstructor);
    }
    this.className = className;
    outputStream = out;
    System.out.println("CFG: " + className);
  }

  /** Returns the fully qualified name of the class whose class file is being generated.
  **/
  public String getClassName() {
    return ci.getClassName();
  }

  /** Returns the descriptor of the class whose class file is being generated.
  **/
  public String getClassDescriptor() {
    return getVMDescriptorForJavaType(ci.getClassName());
  }

  /** Returns the fully qualified name of the super class of the class whose class file is being generated.
  **/
  public String getSuperClassName() {
    return ci.getSuperClassName();
  }

  /** Returns the descriptor of the super class of the class whose class file is being generated.
  **/
  public String getSuperClassDescriptor() {
    return getVMDescriptorForJavaType(ci.getSuperClassName());
  }

  /** Implements the given interface.
   *  @param interfaceName the name of the interface to implemented
   */
  public void implementInterface(InterfaceInfo interfaceInfo) {
    try {
      ci.add(interfaceInfo);
    } 
    catch (ClassException e) {
      {e.printStackTrace(System.err);}
      throw new ClassFileGenerationException(e, "CFG: Implementing interface " + interfaceInfo + "in class " + className + ":");
    }
  }

  /** Implements the given interface.
   *  @param interfaceName the name of the interface to implemented
   */
  public void implementInterface(String interfaceName) {
    try {
      ci.add(new InterfaceInfo(interfaceName));
    } 
    catch (ClassException e) {
      {e.printStackTrace(System.err);}
      throw new ClassFileGenerationException(e, "CFG: Implementing interface " + interfaceName + "in class " + className + ":");
    }
  }

  /** Get a VM descriptor for a given Java type.
   *  @param type the java type to get the descriptor for
   *  @return the VM descriptor for the given java type
  **/
  public static String getVMDescriptorForJavaType(String type) {
    String descriptor = (String) typeToDescriptorTable.get(type);
    if (descriptor == null) {
      // must be a class (non-primitive)
      // replace all . with / and add L ;
      descriptor = "L" + type.replace('.','/'); 
      if ((descriptor.indexOf(';') == -1)) // class descriptors are terminated with a ";"
        descriptor += ";"; // hack - trying to get rid of spurious ';' on end of class descriptors
    }
    return descriptor;
  }

  /** Adds a method with the given details to the class.
   *  @param methodName the name of the method we are adding (must include full package spec)
   *  @param descriptor VM descriptor for method
   *  @param parameterNames Variable names of parameters (null for none)
   *  @param access VM access definition for method
   *  @param exceptions the exceptions (potentially) thrown by the method (null for none)
  **/
  public void addMethod(String methodName,
		 String descriptor,
		 String[] parameterNames,
		 Access access,
		 ClassRef[] exceptions) {
    try {
      addClassMethod(methodName,
		     descriptor,
		     parameterNames,
		     access,
		     exceptions);
    }
    catch (ClassException e) { 
      {e.printStackTrace(System.err);}
      throw new ClassFileGenerationException(e, "CFG: Adding method declaration to class " + className + ":");
    }
  }


  public void addMethodIgnoreMergeProblems(String methodName,
		 String descriptor,
		 String[] parameterNames,
		 Access access,
		 ClassRef[] exceptions) {
    try {
      addClassMethod(methodName,
		     descriptor,
		     parameterNames,
		     access,
		     exceptions);
    }
    catch (ClassMergeException e) { 
      // ClassMergeException may be generated when a method of the same descriptor has already
      // been added, we can silently ignore these
      Trace.exception(e);
    } 
    catch (ClassException e) {
      {e.printStackTrace(System.err);}
      throw new ClassFileGenerationException(e, "CFG: Adding method declaration to class " + className + ":");
    }
  }


  private void addClassMethod(String methodName,
		 String descriptor,
		 String[] parameterNames,
		 Access access,
		 ClassRef[] exceptions) throws ClassException {
      // lose any package '.' chars (the VM expects the package spec with '/' chars)
      methodName = methodName.replace('.', '/');
      // a reference to the method we wish to add (so we can create a MethodInfo object)
      MethodRef mrc = new MethodRef(ci.getClassName(), methodName, descriptor);
      // the method info object to encapsulate the method we are about to add
      com.gensym.classtools.MethodInfo mi = new com.gensym.classtools.MethodInfo(access, mrc, parameterNames, exceptions);
      // add the method to the class
      ci.add(mi);
  }

  /** Adds a method with the given details to the class.
   *  @param methodName the name of the method we are adding (must include full package spec)
   *  @param descriptor VM descriptor for method
   *  @param parameterNames Variable names of parameters (null for none)
   *  @param access VM access definition for method
   *  @param block a Block encapsulating the body of the method
   *  @param exceptions the exceptions (potentially) thrown by the method (null for none)
  **/
  public void addMethod(String methodName,
		 String descriptor,
		 String[] parameterNames,
		 Access access,
		 Block block,
		 ClassRef[] exceptions) {
    try {
      // lose any package '.' chars (the VM expects the package spec with '/' chars)
      methodName = methodName.replace('.', '/');
      // a reference to the method we wish to add (so we can create a MethodInfo object)
      MethodRef mrc = new MethodRef(ci.getClassName(), methodName, descriptor);
      // the method info object to encapsulate the method we are about to add
      com.gensym.classtools.MethodInfo mi = new com.gensym.classtools.MethodInfo(access, 
										 mrc, 
										 block, 
										 parameterNames, 
										 exceptions);
      // add the method to the class
      ci.add(mi);
    } catch (ClassException e) { 
      {e.printStackTrace(System.err);}
      throw new ClassFileGenerationException(e, "CFG: Adding method implementation to class " + className + ":");
    }
  }

  public void addMethodIgnoreMergeProblems(String methodName,
		 String descriptor,
		 String[] parameterNames,
		 Access access,
		 Block block,
		 ClassRef[] exceptions) {
    try {
      // lose any package '.' chars (the VM expects the package spec with '/' chars)
      methodName = methodName.replace('.', '/');
      // a reference to the method we wish to add (so we can create a MethodInfo object)
      MethodRef mrc = new MethodRef(ci.getClassName(), methodName, descriptor);
      // the method info object to encapsulate the method we are about to add
      com.gensym.classtools.MethodInfo mi = new com.gensym.classtools.MethodInfo(access, 
										 mrc, 
										 block, 
										 parameterNames, 
										 exceptions);
      // add the method to the class
      ci.add(mi);
    }
    catch (ClassMergeException e) { 
      // ClassMergeException may be generated when a method of the same descriptor has already
      // been added, we can silently ignore these
      Trace.exception(e);
    } 
    catch (ClassException e) {
      {e.printStackTrace(System.err);}
      throw new ClassFileGenerationException(e, "CFG: Adding method declaration to class " + className + ":");
    }
  }

  /** Adds a new field (attribute) to the class.
   *	@param fieldName the name of the field to be added (must include full package spec)
   *	@param descriptor VM descriptor for field
   *	@param access VM access definition for field
   *	@param initialValue expression giving initial value of field
   *	@param isStatic whether this is a static reference or not 
  **/
  public void addField(String fieldName,
		String descriptor,
		Access access,
		Expression initialValue,
		boolean isStatic) {
    try {
      // lose any package '.' chars (the VM expects the package spec with '/' chars)
      fieldName = fieldName.replace('.', '/');
      // a reference to the field we wish to add (so we can create a FieldInfo object)
      FieldRef fieldRef = new FieldRef(ci.getClassName(),
				       fieldName,
				       descriptor,
				       isStatic);
      FieldInfo fieldInfo;
      if (initialValue != null) {
	// the field info object to encapsulate the field we are about to add
	fieldInfo = new FieldInfo(access,
				  fieldRef,
				  initialValue);
      }
      else {
	fieldInfo = new FieldInfo(access, fieldRef);
      }
      // add the field to the class
      ci.add(fieldInfo);
    } catch (ClassException e) { 
      {e.printStackTrace(System.err);}
      throw new ClassFileGenerationException(e, "CFG: Adding field declaration to class " + className + ":");
    }
  }
  
  /** Merges all overrides for the classes passed to it.  
   *  @param ovrClassNames sequence containing the names of all classes whose overrides need to be merged
  **/
  public byte[] mergeOverrides(Sequence ovrClassNames) throws ClassNotFoundException {
    for (int i = 0; i < ovrClassNames.size(); i++) { // merge all required classes
      // the filename of the override file is the class name + "SpecialImpl.class"
      String fullClassName = (String) ovrClassNames.elementAt(i);
      String userRepository = System.getProperty ("com.gensym.class.user.repository");
      char sepChar = System.getProperty ("file.separator").toCharArray()[0];
      String filename = userRepository + sepChar + fullClassName.replace('.', sepChar) + "SpecialImpl.class";
      System.out.println("-> Merging class: " + filename);
      try {
	FileInputStream fileStream = new FileInputStream(filename);
	ClassInfo mergeClassInfo = new ClassInfo(fileStream);
	fileStream.close();
	try {
	  ci.merge(mergeClassInfo);
	}
	catch (ClassMergeException cme) {
	  System.err.println("WARNING: " + cme.getMessage());
	}
      }
      catch (Exception e) {
        System.err.println("CFG: Merging overrides from " + filename + " into class " + className + ":");
	e.printStackTrace(System.err);
	throw new ClassNotFoundException(e.toString());
      }
    }
    return ci.getBytes();
  }


  /**
   * Merges another class file into the current classInfo
   */
  public void mergeClass(FileInputStream fileStream) {
  
    try {  	
      ClassInfo mergeClassInfo = new ClassInfo(fileStream);
      MethodInfo[] methods = mergeClassInfo.getMethods();
      System.out.println("Attempting to merge methods : ");
      for (int i = 0; i<methods.length; i++) {
	System.out.println(methods[i]);
      }
      ci.merge(mergeClassInfo);
    } catch (ClassException e) {
      {e.printStackTrace();}
      throw new ClassFileGenerationException(e, "Problem Merging from " + fileStream + " into  " + ci.getClassName());
    }
  }
  
  /** Creates (and returns) the byte code for the class and writes the class file to disk.
  **/
  public byte[] writeClass() throws java.io.IOException {
    String userRepository = System.getProperty ("com.gensym.class.user.repository");
    char sepChar = System.getProperty ("file.separator").toCharArray()[0];
    String filename = userRepository + sepChar + this.className.replace('.', sepChar) + ".class";

//  long ct = System.currentTimeMillis();
    System.out.println("-> Generating class file...");
    ci.emit(); // build bytes array from info objects
//    long emitCT = System.currentTimeMillis();
    System.out.println("-> Writing class to disk: " + filename);
    //ci.toFile(filename, false); // write bytes class file (don't re-emit bytes, we've just done it)
    byte[] bytes = ci.getBytes();
    outputStream.write(bytes);
//  long nowCT = System.currentTimeMillis();
//  System.out.println("Emit time: " + (emitCT - ct) + " milliseconds");
//  System.out.println("Total time: " + (nowCT - ct) + " milliseconds");
    System.out.println("-> Done.");
    return bytes;
  }

  /** Creates (and returns) the byte code for the class without writing the class file to disk.
  **/
  public byte[] createClass() {
//    long ct = System.currentTimeMillis();
    System.out.println("CFG: Generating class file...");
    ci.emit(); // build bytes array from info objects
//    long emitCT = System.currentTimeMillis();
//    System.out.println("Emit time: " + (emitCT - ct) + " milliseconds");
    System.out.println("-> Done.");
    return ci.getBytes();
  }

  /** Accepts a primitive java type as a parameter and returns the wrapper to be used for it.
   *  @param javaType a primitive java type in string form (e.g.  "int", "char" etc.)
   *  @return the fully qualified name of the wrapper class for the primitive type
  **/
  public static String getWrapperClass(String javaType) {
    if (javaType.equals("boolean")) return "java.lang.Boolean";
    if (javaType.equals("char")) return "java.lang.Character";
    if (javaType.equals("byte")) return "java.lang.Byte";
    if (javaType.equals("short")) return "java.lang.Short";
    if (javaType.equals("int")) return "java.lang.Integer";
    if (javaType.equals("long")) return "java.lang.Long";
    if (javaType.equals("float")) return "java.lang.Float";
    if (javaType.equals("double")) return "java.lang.Double";
    return "";
  }

  /** Accepts a primitive java type as a parameter and returns the accessor method
   *  to be used for accessing a value of that type from the appropriate wrapper class.
   *  @param javaType a primitive java type in string form (e.g.  "int", "char" etc.)
   *  @return the name of the method to be used to access the appropriate primitive type from the wrapper class. 
  **/
  public static String getAccessorMethod(String javaType) {
    if (javaType.equals("boolean")) return "booleanValue";
    if (javaType.equals("char")) return "charValue";
    if (javaType.equals("byte")) return "byteValue";
    if (javaType.equals("short")) return "shortValue";
    if (javaType.equals("int")) return "intValue";
    if (javaType.equals("long")) return "longValue";
    if (javaType.equals("float")) return "floatValue";
    if (javaType.equals("double")) return "doubleValue";
    return "";
  }

  /**  Tests whether the class being generated defines a field with the given name
   *   @param fieldName the name of the field to test for
   *   @return true if this class defines a field with the given name, false otherwise
  **/
  public boolean isFieldDefined(String fieldName) {
    FieldInfo[] fields = ci.getFields();
    for (int i = 0; i < fields.length; i++)
      if (fieldName.equals(fields[i].getName())) return true;
    return false;
  }

  /** Invokes the G2Script compiler, adds the compiled method to the shadow class,
   *  and returns a call to the generated method.
   *  @param sourceCode the G2 source code for the method
   *  @return a call to the newly compiled method
  **/
  public void compileMethodCall(String sourceCode, 
				Block methodBody,
				com.gensym.g2script.Compiler compiler) 
       throws com.gensym.g2script.CompilerException,
	      ClassException
  {
   
      com.gensym.classtools.MethodInfo method = compiler.compileMethod(sourceCode, ci, methodBody);
      ci.add(method);
    
    return;
  }

  public static Expression wrapPrimitiveIfNecessary(String type, Expression expr) throws ClassException {
    Expression objWrapped = expr;
    Expression[] wrapperArgs = new Expression[] {expr};
    if (type.equals(Integer.TYPE.getName())) {
      // create new Number for int
      MethodRef consRef = new MethodRef("java.lang.Integer", "<init>", "(I)V");
      objWrapped = new New(new MethodCall(consRef,
				  wrapperArgs,
				  MTH_CALL_SPECIAL));
    } else if (type.equals(Double.TYPE.getName())) {
      // create new Number for double
      MethodRef consRef = new MethodRef("java.lang.Double", "<init>", "(D)V");
      objWrapped = new New(new MethodCall(consRef,
				  wrapperArgs,
				  MTH_CALL_SPECIAL));
    } else if (type.equals(Float.TYPE.getName())) {
      // create new Number for float
      MethodRef consRef = new MethodRef("java.lang.Float", "<init>", "(F)V");
      objWrapped = new New(new MethodCall(consRef,
				  wrapperArgs,
				  MTH_CALL_SPECIAL));
    } else if (type.equals(Boolean.TYPE.getName())) {
      // create new Boolean for boolean
      MethodRef consRef = new MethodRef("java.lang.Boolean", "<init>", "(Z)V");
      objWrapped = new New(new MethodCall(consRef,
				  wrapperArgs,
				  MTH_CALL_SPECIAL));
    }
    return objWrapped;
  }

  public static Expression doCast(String type, Expression instance) throws ClassException{
    Expression objCast = instance;
    if (type.equals(Integer.TYPE.getName())) {
	  objCast = new MethodCall(new Cast("Ljava/lang/Number;", instance),
				   new MethodRef("java.lang.Number",
						 "intValue",
						 "()I"
						 ),
				   new Expression[] {},
				   MTH_CALL_VIRTUAL
				   );
    }
    else if (type.equals(Double.TYPE.getName())) {
      objCast = new MethodCall(new Cast("Ljava/lang/Number;", instance),
			       new MethodRef("java.lang.Number",
					     "doubleValue",
					     "()D"
					     ),
			       new Expression[] {},
			       MTH_CALL_VIRTUAL
			       );
    }
    else if (type.equals(Float.TYPE.getName())) {
      objCast = new MethodCall(new Cast("Ljava/lang/Number;", instance),
			       new MethodRef("java.lang.Number",
					     "floatValue",
					     "()F"
					     ),
			       new Expression[] {},
			       MTH_CALL_VIRTUAL
			       );
    }
    else if (type.equals( Boolean.TYPE.getName())) {
      objCast = new MethodCall(new Cast("Ljava/lang/Boolean;", instance),
			       new MethodRef("java.lang.Boolean",
					     "booleanValue",
					     "()Z"
					     ),
			       new Expression[] {},
			       MTH_CALL_VIRTUAL
			       );
    } else {
      objCast = new Cast(getVMDescriptorForJavaType(type), instance);
    }
    return objCast;
  }

  /** Returns an array containing the names of the interfaces implemented by this class
   *  @return an array containing the names of the interfaces implemented by this class
  **/
  public String[] getInterfaceNames() {
    InterfaceInfo[] interfaces = ci.getInterfaces();
    String[] interfaceNames = new String[interfaces.length];
    for (int i = 0; i < interfaces.length; i++)
      interfaceNames[i] = interfaces[i].getName();
    return interfaceNames;
  }

  /**  If the current class being generated is a stub, this method returns the fully qualified name of the 
   *   interface that has already been generated for the stub (all it really does is remove the "Impl" part 
   *   of the fully qualified class name).
   *   @return the fully qualified name of the interface class that matches the stub being generated.
   *   If the class being generated is not a stub, this method returns an empty string.
  **/
  public String getFullyQualifiedInterfaceName() {
    if (className.indexOf("Impl") > -1) {
      return className.substring(0, className.indexOf("Impl"));
    }
    else return ""; // not a stub - no matching interface class
  }

}

