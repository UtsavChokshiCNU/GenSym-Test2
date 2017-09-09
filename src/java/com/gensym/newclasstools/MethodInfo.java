package com.gensym.newclasstools;
import java.io.*;
import java.util.Vector;


public class MethodInfo extends Info implements RuntimeConstants
{
  //************** Properties ***********

  private Type returnType;

  public Type getReturnType() {
    return returnType;
  }

  public void setReturnType(Type returnType) throws ClassException {
    this.returnType = returnType;
    // ?? Need to recompile here
  }

  private Type[] argumentTypes;
  
  public Type[] getParameterTypes() {
    Type[] result = new Type[argumentTypes.length];
    for (int i = 0; i < argumentTypes.length; i++) {
      result[i] = argumentTypes[i];
    }
    return result;
  }

  public void setArgumentTypes(Type[] argumentTypes) throws ClassException {
    this.argumentTypes = (argumentTypes == null) ? new Type[0] : argumentTypes;
  }


  String getDescriptor()
  {
    return returnType.descriptor(argumentTypes);  
  }

  private Access access;
  public Access getAccess() 
  {
    return access;
  }

  public int getModifiers() {
    return access.getModifiers();
  }

  public void setAccess(Access access) 
  {
    access = this.access;
  }

  Vector attributes;  // package public only until parsing of attributes is moved
  // into this class
  public Attribute[] getAttributes()
  {
    if (attributes == null)
      return new Attribute[] { };
    Attribute[] attributeArray = new Attribute[attributes.size()];
    attributes.copyInto(attributeArray);
    return attributeArray;       
  }

  private Block contents;

  Block getContents() {
    return contents;
  }

  public void setBlock(Block block) throws ClassException {
    this.contents = block;
  }

  private String[] argumentNamesIfAny;

  public String[] getParameterNames() {
    return argumentNamesIfAny;
  }

  private ExceptionsAttribute exceptions;

  public ExceptionsAttribute getExceptionsAttribute() {
    return exceptions;
  }

  // filled in during emit. Not valid at any other time.
  private static Type classType = null;

  private static final boolean trace = false;  

  //*************** Constructors **************

  /** 
   * Specify a MethodInfo from its component parts. <p>
  *
  * Example: creating method that simply returns its argument
  * that throws java.lang.Exception<p>
  *
  * <code>
  * <pre>
  * try {
  *   MethodInfo methodInfo = new MethodInfo(new Access(Access.PUBLIC),
  *                                          new MethodRef("Lcom/gensym/tests/Bar;","foo","(I)I"),
  *                                          new String[] { "baz" }, 
  *                                          new Block(new Return(new Variable(("baz","I"))),
  *                                          new ClassRef[] { new ClassRef("java/lang/Exception")});
  * }
  * catch (ClassException e) 
  * {
  *  System.out.println("MethodInfo create failed: " + e)
  * }
  * </pre>
  * </code>
  * @see ClassInfo#add(com.gensym.newclasstools.MethodInfo)
  *
  * @param access         The access restrictions of the desired method
  * @param methodRef      A method reference
  * @param block          Definition of the contents of the desired method
  * @param argumentNames  An array of the names of arguments to the desired method
  * @param exceptions     An array of the types that represent the 
  *                       exceptions that can be returned by the desired method     
  * @exception ClassException 
  *      Cannot create a methodInfo from these arguments.
  */
  
  public MethodInfo(Access accessFlags,
		    String name,
		    Type returnType,
		    Type[] argumentTypes,
		    Block block,
		    String[] argumentNames,
		    Type[] exceptions) throws ClassException
  {
    super(name);
    initA(accessFlags, returnType, argumentTypes);
    argumentNamesIfAny = argumentNames;
    if (name.equals("<clinit>") && exceptions != null && exceptions.length > 0)
      throw new ClassException("Static initialization methods cannot throw exceptions");
    attributes = new Vector(2);
    this.contents = block;
    if (exceptions != null && exceptions.length > 0) {
      this.exceptions = initC(exceptions);
    } else {
      this.exceptions = null;
    }
  }
 
  /** 
   * Specify a MethodInfo  from its component parts. <p>
   * 
   * Example: creating an empty method, with no args, and no return value<p>
   * <code>
   * <pre>
   * try {
   *  MethodInfo methodInfo = new MethodInfo(new Access(Access.PUBLIC),
   *                                         null, 
   *                                         new MethodRef("Lcom/gensym/tests/Bar;","foo","()V"),
   *                                         new Block().add(new Return()));
   * }
   * catch (ClassException e) 
   * {
   *  System.out.println("MethodInfo create failed: " + e)
   * }
   * </pre>
   * </code>
   * @see ClassInfo#add(com.gensym.newclasstools.MethodInfo)
   * @param access         The access restrictions of the desired method
   * @param methodRef      A method reference
   * @param argumentNames  An array of the names of arguments to the desired method
   * @param block          Definition of the contents of the desired method,      
   *  @exception ClassException 
   *      Cannot create a MethodInfo from these arguments.
   * 
   */
  public MethodInfo(Access flags,
		    String name,
		    Type returnType,
		    Type[] argumentTypes,
		    String [] argumentNames,
		    Block block) throws ClassException
  {
    this(flags, name, returnType, argumentTypes, block, argumentNames, null);
  }

  /** 
   * Specfy a MethodInfo without providing any implementation.<br>
   * Note - this can be used for specifying abstract methods.<br>
   *  @see ClassInfo#add(com.gensym.newclasstools.MethodInfo)
   *
   * @param access         The access restrictions of the desired method
   * @param methodRef      A method reference
   * @param argumentNames  An array of the names of arguments to the desired method
   * @param exceptions     An array of the class references that represent the 
   *                       exceptions that can be returned by the desired method     
   *  @exception ClassException 
   *      Cannot create a MethodInfo from these arguments.
   */
  public MethodInfo(Access flags,
		    String name,
		    Type returnType,
		    Type[] argumentTypes,
		    String[] argumentNames,
		    Type[] exceptions) throws ClassException
  {
    this(flags, name, returnType, argumentTypes, null, argumentNames, exceptions);
  }

  /** 
   * Specify a MethodInfo without providing any implementation.<br>  
   * Note - this can be used for specifying unimplemented abstract methods.<br>
   * @see ClassInfo#add(com.gensym.newclasstools.MethodInfo)
   * @param access         The access restrictions of the desired method
   * @param methodRef      A method reference
   * @exception ClassException 
   *      Cannot create a methodInfo from these arguments.
   */
  public MethodInfo(Access flags,
		    String name,
		    Type returnType,
		    Type[] argumentTypes) throws ClassException
  {
    this(flags, name, returnType, argumentTypes, null, null, null);
  }

  
  /** 
   * Create a MethodInfo from some of its constituent parts.
   * Note that MethodInfo must also keep a track of the method and
   * name_and_type constants required when the method is normalized
   *
   * @exception ClassException 
   *      Cannot create a methodInfo from these arguments.
   */ 
  MethodInfo(Access flags, UTF8Constant nameConstant,
	     UTF8Constant descriptorConstant)
      throws ClassException
  {	  
    this(flags, nameConstant.getString(),
	 Type.parseReturnType(descriptorConstant.getString()),
	 Type.makeTypeArray(Type.parseArgumentTypes(descriptorConstant.getString())),
	 null,
	 null,
	 null);
  }
 
  private void initA(Access accessFlags, Type returnType, Type[] argumentTypes)
       throws ClassException
  {
    access = accessFlags;
    this.returnType = returnType;
    this.argumentTypes = (argumentTypes == null) ? new Type[0] : argumentTypes;
  }

  public CodeAttribute getCodeAttribute()
  {
    for (int i = 0; i < attributes.size(); i++)
      {
	Attribute attr = (Attribute) attributes.elementAt(i);
	if (attr instanceof CodeAttribute)
	  return (CodeAttribute) attr;
      }
    return null;
  }

	 
  private ExceptionsAttribute initC(Type[] exceptions)
      throws ClassException
  {
    ClassConstant[] excepts =  new ClassConstant[exceptions.length];
    // Add exceptions into the same constant Pool
    for(int i = 0 ; i < exceptions.length; i++) {
      excepts[i] = new ClassConstant(exceptions[i]);
    }
    return new ExceptionsAttribute(excepts);
  }
 
  //************************* Output ********************************
  
  @Override
  void emit(DataOutputStream out, ConstantPool cp)
      throws IOException, ClassException
  {
    EmitState state = new EmitState(cp,
				    argumentNamesIfAny,
				    argumentTypes,
				    returnType,
				    classType,
				    true);
    if (trace)
      System.out.println("Emitting method " + this);
    contents.emit(state,false,null);
    CodeAttribute codeAttr =
      new CodeAttribute(cp, state.instructions, 
			state.exceptionTable,
			state.maxStackSize,
			state.varID + (access.isStatic() ? 0 : 1));

    // Here is where we tell the codeattribute to turn its instructions
    // into a byte vector. Maybe this should happen in the CodeAttribute
    // constructor itself.
    Vector lineNumberTable = state.lineNumberTable;
    if ((lineNumberTable != null) && (lineNumberTable.size() > 0)) {
      codeAttr.add(new LineNumberTableAttribute(lineNumberTable));
    }
    access.emit(out);
    super.emit(out, cp);
    if (trace)
      System.out.println("Descriptor emitted " + getDescriptor());
    out.writeShort(cp.getIndex(new UTF8Constant(getDescriptor())));
    attributes.addElement(codeAttr);
    if (exceptions != null && exceptions.length > 0)
      attributes.addElement(exceptions);
    Attribute.emit(attributes, out, cp);
  }


  @Override
  public void toStdout(String prefix) {
    super.toStdout(prefix);
    Info.toStdout(attributes, prefix + "     ");
    System.out.println("");
  }

  @Override
  public String toString() {
    return       "<MethodInfo, name=" + getName() +
      ", descriptor=" + getDescriptor() +
      ", access=" + access.toString() +">";
  }

  synchronized static void emit(Vector methods,DataOutputStream out, Type theClassType, ConstantPool cp)
      throws IOException, ClassException
  {
    if (trace)
      System.out.println("Emitting a Vector of " + methods.size() + " MethodInfo object");
    classType = theClassType;
    Info.emit(methods,out, cp);
  }

  public static void toStdout(Vector methods) {
    System.out.println("Methods");
    System.out.println("-------");
    Info.toStdout(methods,"");
  }


}
