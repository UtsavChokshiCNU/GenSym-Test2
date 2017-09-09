package com.gensym.newclasstools;
import java.io.*;
import java.util.Vector;


public class ConstructorInfo implements RuntimeConstants
{
  //************** Properties ***********

  // If this is read from a class file, all we have is the MethodInfo object.
  private MethodInfo method;

  // If it is constructed, we have all of these:
  private Access access;
  private Type[] argumentTypes;
  private Block block;
  private String[] argumentNames;
  private Type[] exceptions;
  // one of CONSTRUCTOR_CALLS_THIS, CONSTRUCTOR_CALLS_SUPER, DEFAULT_CONSTRUCTOR_CALL
  private int constructorInvocationType;
  private Expression[] constructorInvocationArgs;

  
  public ConstructorInfo(Access access, Type[] argumentTypes,
			 Block block, String[] argumentNames,
			 Type[] exceptions, int constructorInvocationType,
			 Expression[] constructorInvocationArgs) {
    this.access = access;
    this.argumentTypes = (argumentTypes == null) ? new Type[0] : argumentTypes;
    this.block = block;
    this.argumentNames = (argumentNames == null) ? new String[0]: argumentNames;
    this.exceptions = exceptions;
    this.constructorInvocationType = constructorInvocationType;
    this.constructorInvocationArgs = (constructorInvocationArgs == null) ?
      new Expression[0] : constructorInvocationArgs;
  }

  // For default constructor case
  public ConstructorInfo(Access access, Type[] argumentTypes,
			 Block block, String[] argumentNames,
			 Type[] exceptions) {
    this(access, argumentTypes, block, argumentNames,
	 exceptions, DEFAULT_CONSTRUCTOR_CALL, new Expression[]{});
  }

  // For constructing when reading a class file.
  ConstructorInfo(MethodInfo method) {
    this.method = method;
  }

  // Need a bunch of accessors here.
  public MethodInfo getMethod() {
    return method;
  }

  public void setMethod(MethodInfo method) {
    this.method = method;
  }

  public void setAccess(Access access) {
    this.access = access;
  }

  public int getModifiers() {
    return access.getModifiers();
  }

  public Type[] getArgumentTypes() {
    return argumentTypes;
  }

  public void getArgumentTypes(Type[] argumentTypes) {
    this.argumentTypes = argumentTypes;
  }

  
  public String getDescriptor() {
    return Type.VOID_TYPE.descriptor(argumentTypes);
  }

  public Block getBlock() {
    return block;
  }

  public void setBlock(Block block) {
    this.block = block;
  }

  public String[] getArgumentNames() {
    return argumentNames;
  }

  public void setArgumentNames(String[] argumentNames) {
    this.argumentNames = argumentNames;
  }

  public Type[] getExceptionTypes() {
    return exceptions;
  }

  public void getExceptionTypes(Type[] exceptionTypes) {
    this.exceptions = exceptionTypes;
  }
  
  MethodInfo computeConstructorMethod(ClassInfo containingClass) throws ClassException {
    // System.out.println("computeConstructorMethod called on " + this);
    Block methodBlock = new Block();
    if (constructorInvocationType == DEFAULT_CONSTRUCTOR_CALL) {
      methodBlock.add(new MethodCall("<init>", containingClass.getSuperType(),
				     null, Type.VOID_TYPE, null, null,
				     MTH_CALL_SPECIAL));
    } else if (constructorInvocationType == CONSTRUCTOR_CALLS_SUPER) {
      methodBlock.add(new MethodCall("<init>", containingClass.getSuperType(),
				     argumentTypes, Type.VOID_TYPE, null,
				     constructorInvocationArgs,
				     MTH_CALL_SPECIAL));
    } else if (constructorInvocationType == CONSTRUCTOR_CALLS_THIS) {
      methodBlock.add(new MethodCall("<init>", containingClass.getClassType(),
				     argumentTypes, Type.VOID_TYPE, null,
				     constructorInvocationArgs,
				     MTH_CALL_SPECIAL));
    } else throw new ClassException("Bad ConstructorInfo type " +
				    constructorInvocationType);
    Vector initializers = containingClass.getInitializers();
    for (int i = 0; i < initializers.size(); i++) {
      Object initializer = initializers.elementAt(i);
      if (initializer instanceof FieldInfo) {
	methodBlock.add(((FieldInfo)initializer).getFieldInitializer(containingClass));
      } else if (initializer instanceof Block) {
	methodBlock.add((Block)initializer);
      } else throw new ClassException("bad initializer " + initializer);
    }
    methodBlock.add(block);
    method = new MethodInfo(access, "<init>", Type.VOID_TYPE, argumentTypes,
			    methodBlock, argumentNames, exceptions);
    return method;
  }

  public static void toStdout(Vector infos, ClassInfo containingClass) {
    System.out.println("Constructors");
    System.out.println("------------");
    if (infos != null) 
      for (int i = 0; i < infos.size(); i++)  {
	if (infos.elementAt(i) != null) 
	  ((ConstructorInfo) infos.elementAt(i)).toStdout("", containingClass);
      }
  }

  public void toStdout(String prefix, ClassInfo containingClass) {
    try {
      if (method == null) {
	computeConstructorMethod(containingClass);
      }
      method.toStdout(prefix);
    } catch (ClassException c) {
      System.out.println(prefix + "<Constructor with bad constructor method>");
    }
  }

  @Override
  public String toString() {
    return       "<ConstructorInfo, descriptor=" + getDescriptor() +
      ", access=" + access.toString() +">";
  }

}
    
    
