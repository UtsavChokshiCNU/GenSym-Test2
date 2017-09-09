package com.gensym.classtools;
import java.io.*;
import java.util.Vector;


public class MethodInfo extends Info implements RuntimeConstants
{
  //************** Properties ***********
  private String declaringClassName;
  public String getClassName() {
    return declaringClassName;
  }
  public void setClassName(String declaringClassName)
      throws ClassException
  {
    if (this.declaringClassName == null)
      this.declaringClassName = declaringClassName;
    if (! declaringClassName.equals(this.declaringClassName))
      changeDeclaringClass(declaringClassName);
  }

  private String descriptor;
  public String getDescriptor()
  {
    return descriptor;  
  }

  private Access access;
  public Access getAccess() 
  {
    return access;
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
  public Block getContents() {
    return contents;
  }

  private int descriptorIndex;
  public int getTypeIndex()
  {
    return descriptorIndex;
  }
  
  private MethodRefConstant method_constant;  
  private String[] argumentNamesIfAny;

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
  * @see ClassInfo#add(com.gensym.classtools.MethodInfo)
  *
  * @param access         The access restrictions of the desired method
  * @param methodRef      A method reference
  * @param block          Definition of the contents of the desired method
  * @param argumentNames  An array of the names of arguments to the desired method
  * @param exceptions     An array of the class references that represent the 
  *                       exceptions that can be returned by the desired method     
  * @exception ClassException 
  *      Cannot create a methodInfo from these arguments.
  */
  
  public MethodInfo(Access flags,
		    MethodRef methodRef,
		    Block block,
		    String[] argumentNames,
		    ClassRef[] exceptions) throws ClassException
  {
    initA(flags,methodRef);
    argumentNamesIfAny = argumentNames;
    if (name.equals("<clinit>"))
      throw new ClassException("Static initialization methods cannot throw exceptions");
    else  {
      attributes = new Vector(2);
      attributes.addElement(initB(block,methodRef));
      if (exceptions != null && exceptions.length > 0)
	attributes.addElement(initC(exceptions));
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
   * @see ClassInfo#add(com.gensym.classtools.MethodInfo)
   * @param access         The access restrictions of the desired method
   * @param methodRef      A method reference
   * @param argumentNames  An array of the names of arguments to the desired method
   * @param block          Definition of the contents of the desired method,      
   *  @exception ClassException 
   *      Cannot create a MethodInfo from these arguments.
   * 
   */
  public MethodInfo(Access flags,
		    MethodRef methodRef,
		    String [] argumentNames,
		    Block block) throws ClassException
  {
    initA(flags,methodRef);
    argumentNamesIfAny = argumentNames;
    if (name.equals("<clinit>"))
      block.generateConstants(normalizedConstants);	  
    else  {
      attributes = new Vector(1);
      attributes.addElement(initB(block,methodRef)); 
    }
  }

  /** 
   * Specfy a MethodInfo without providing any implementation.<br>
   * Note - this can be used for specifying abstract methods.<br>
   *  @see ClassInfo#add(com.gensym.classtools.MethodInfo)
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
		    MethodRef methodRef,
		    String[] argumentNames,
		    ClassRef[] exceptions) throws ClassException
  {
    initA(flags,methodRef);
    argumentNamesIfAny = argumentNames;
    attributes = new Vector(1);
    if (exceptions != null && exceptions.length > 0)
      attributes.addElement(initC(exceptions));	
  }

  /** 
   * Specify a MethodInfo without providing any implementation.<br>  
   * Note - this can be used for specifying unimplemented abstract methods.<br>
   * @see ClassInfo#add(com.gensym.classtools.MethodInfo)
   * @param access         The access restrictions of the desired method
   * @param methodRef      A method reference
   * @exception ClassException 
   *      Cannot create a methodInfo from these arguments.
   */
  public MethodInfo(Access flags,
		    MethodRef methodRef) throws ClassException
  {
    initA(flags,methodRef);
  }

  
  /** 
   * Create a MethodInfo from some of its constituent parts.
   * Note that MethodInfo must also keep a track of the method and
   * name_and_type constants required when the method is normalized
   *
   * @exception ClassException 
   *      Cannot create a methodInfo from these arguments.
   */ 
  MethodInfo(int accessFlags, ConstantPool constantPool,
	     int nameindex, int descriptorindex)
      throws ClassException
  {	  
    super(nameindex,constantPool);
    access = new Access(accessFlags);
    
    Constant nameConstant = constantPool.getPool(nameindex);

    //nameIndex = nameindex;
    descriptorIndex = descriptorindex;
    
    //name = nameConstant.getUTF8String();

    if (trace) {
      System.out.println("Name index just read:" +nameIndex);
      System.out.println("Descriptor index just read:" +descriptorIndex);
    }
    Constant descriptorConstant = constantPool.getPool(descriptorIndex);
    descriptor = descriptorConstant.getUTF8String();

    // Keep a pointer locally to the constantPool to which
    // this method refers.
    localConstants = constantPool;

    if (trace)
      System.out.println("  just made method name="+name+" desc="+descriptor);
  }
 
  MethodInfo(Access flags,
	     MethodRef methodRef,
	     Block block,
	     boolean bufferedClinit) throws ClassException
  {
    initA(flags,methodRef);
    if (name.equals("<clinit>") && bufferedClinit == true)
      block.generateConstants(normalizedConstants);	  	  
    else  {
      attributes = new Vector(1);
      attributes.addElement(initB(block,methodRef)); 
    }
  }

  private void  initA(Access flags, MethodRef methodRef) throws ClassException
  {
    access = flags;
    methodRef.generateConstants(normalizedConstants = new ConstantPool());
    method_constant = (MethodRefConstant) methodRef.constant;
    descriptor = methodRef.getDescriptor();
    declaringClassName = methodRef.getClassName();
    name = methodRef.getMethodName();	  
    normalized = true;
  }

  private CodeAttribute initB(Block block, MethodRef methodRef) throws ClassException
  {
    Type tpe = methodRef.getExpressionType(); 

    EmitState state = new EmitState(normalizedConstants,
				    argumentNamesIfAny,
				    tpe.getArgumentTypes(),
				    tpe,
				    Type.parseType(Type.classDescriptor(declaringClassName)),
				    true);
    block.emit(state,false,null);
    state.resolveAllLabels();
    CodeAttribute codeAttr =
      new CodeAttribute(normalizedConstants, state.instructions, 
			state.exceptionTable,
			state.maxStackSize,                       
			state.varID + (access.isStatic() ? 0 : 1));
    
    
    Vector lineNumberTable = state.lineNumberTable;
    if ((lineNumberTable != null) && (!lineNumberTable.isEmpty())) {
      codeAttr.add(new LineNumberTableAttribute(lineNumberTable));
    }

    return codeAttr;
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

	 
  private ExceptionsAttribute initC(ClassRef[] exceptions)
      throws ClassException
  {
    ClassConstant[] excepts =  new ClassConstant[exceptions.length];
    // Add exceptions into the same constant Pool
    for(int i = 0 ; i < exceptions.length; i++) {
      exceptions[i].generateConstants(normalizedConstants);
      excepts[i] = exceptions[i].constant;
    }
    return new ExceptionsAttribute(normalizedConstants,excepts);
  }
 
  //************************* Output ********************************
  
  @Override
  void emit(DataOutputStream out)
      throws IOException
  {
    access.emit(out);
	  
    if (method_constant != null) {
      method_constant.emitAsMethodInfo(out);
    }
    else {
      super.emit(out);
      if (trace)
	System.out.println("Descriptor Index emitted " + descriptorIndex);
      out.writeShort(descriptorIndex);
    }

    Attribute.emit(attributes,out);
  }


  @Override
  public void toStdout(String prefix) {
    super.toStdout(prefix);
    Info.toStdout(attributes, prefix + "     ");
    System.out.println("");
  }

  @Override
  public String toString() {
    return       "<MethodInfo, name=" +  name +
      ", declaring class=" + declaringClassName +
      ", descriptor=" + descriptor +
      ", access=" + access.toString() +">";
  }

  static void emit(Vector methods,DataOutputStream out)
      throws IOException
  {
    Info.emit(methods,out);
  }

  public static void toStdout(Vector methods) {
    System.out.println("Methods");
    System.out.println("-------");
    Info.toStdout(methods,"");
  }


  //************************* Operations ********************************
	

  /** 
   * The changeDeclaringClass() method changes all references to the 
  * current parent class of this method to a new parent class.  This method
  * requires for this MethodInfo to be normalized first or it will throw
  * a ClassException
  */
  private void changeDeclaringClass(String newClassName)
      throws ClassException
  {
    String currentClassName;

    if (! normalized)
      throw new ClassException("Attempt to change declaring class of localized MethodInfo");
		
    currentClassName = declaringClassName;
       
    Constant[] pool = normalizedConstants.getPool();
    Constant element;
    int type;
    for (int i = 0; i < pool.length; i++)
      {
	element =pool[i];

	if (element == null)
	  continue;

	type = element.getType();
      
	if (type == CONSTANT_UTF8)
	  {
	    if (currentClassName.equals(element.getUTF8String()))
	      {
		// Change the utfConstant that this class is refering to
		// the new class. Note that this changes all references
		// to that class name, including regular string references.  
		element.setUTF8String(newClassName);
	      }
	  }			
      }	
  }   
  
  /** 
   * The normalize() method changes all references to constants 
   * to references to constants in the
   * normalizedConstantpool. The normalizeConstantpool will have all the
   * constants necessary for this method.
   * 
   * @exception ClassException
   *     Failure in normalization of this MethodInfo
   */
  void normalize()
      throws ClassException
  {
    // Because normalize(3) will fill at the current index and then increment
    int index = 1;

    // The normalizedConstants must be smaller than the local ones,
    // so allocate  the maximum amount of space that could be needed
    normalizedConstants = new ConstantPool(localConstants.getLength());


    if (trace)
      System.out.println("Normalizing I thought: " + 
			 localConstants.getPool(nameIndex) +
			 localConstants.getPool(descriptorIndex));


    if (hasMethodRefConstant())
      {
	index = normalizedConstants.add(method_constant,true);
	method_constant = (MethodRefConstant) normalizedConstants.getPool(index);

      }
    else {
		
      // Normalize the name index by calling the super method
      index = normalize(localConstants, normalizedConstants, index);

      // Normalize the descriptor index
      normalizedConstants.add(localConstants.getPool(descriptorIndex),false);

      descriptorIndex = index;
      index++;
    }

    // Iterate over each attribute, calling normalize(ConstantPool,
    // ConstantPool,index)
    // each attribute will then complete building up the normalizedConstants
    // array

    for (int i =0; i < attributes.size(); i++) {
      if (trace) {
	System.out.println("Starting normalizing: " + 
			   ((Attribute) attributes.elementAt(i)).name);
	System.out.flush();
      }
      index = ((Attribute) attributes.elementAt(i)).normalize(localConstants,
							      normalizedConstants,index);
    }

    // Set state of methodInfo
    normalized = true;
  }

  /** 
   * localize() method changes all references to constants in the
   * normalizedconstnatpool to references into the argument of this method
   * The attribute localconstants will also be set to this argument.
   * Localizing currently assumes that all the work of adding new constants
   * into the constantPool has been completed, and will therefore throw
   * a classMerge exception if the constant required is missing.
   * 
   * @exception ClassException
   *     Failure in localization of this MethodInfo
   */
  @Override
  void localize(ConstantPool constantPool) 
      throws ClassException
  {   
    if (hasMethodRefConstant()) {
      int localindex = constantPool.member(method_constant);
      if(localindex == -1) 
        throw new ClassMergeException();
      method_constant = (MethodRefConstant) constantPool.getPool(localindex);
    }
    else {
 
      super.localize(constantPool, normalizedConstants);

      // Localize the descriptor index
      Constant descriptorc = normalizedConstants.getPool(descriptorIndex);
	  
      int localindex = constantPool.member(descriptorc);
      if(localindex == -1) 
	throw new ClassMergeException();
      descriptorIndex = localindex;
      descriptor = constantPool.getPool(descriptorIndex).getUTF8String();
    }

    // Iterate over each attribute calling localize(ConstantPool, ConstantPool)
	  
    if (attributes != null)
      for (int i =0; i < attributes.size(); i++) {
	if (trace)
	  System.out.println("Starting localizing: " + 
			     ((Attribute) attributes.elementAt(i)).name);
	System.out.flush();
	((Attribute) attributes.elementAt(i)).localize(constantPool,
						       normalizedConstants);
      }

    // Set state of methodInfo
    normalized = false;
    localConstants = constantPool;
  }

  //********************* Predicates ***************************************

  boolean hasMethodRefConstant() {
    if (method_constant != null)
      return true;
    else return false;
  }

}
