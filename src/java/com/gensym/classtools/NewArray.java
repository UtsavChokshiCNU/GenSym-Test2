package com.gensym.classtools;

import java.util.Vector;

/** 
  * The class <code>NewArray</code> can be used to create a new array of
  * a particular array class.  In the VM spec the class of an array consists
  * of a primitive type or a class type preceded by the number of "[" equal to
  * the number of dimensions in the array.  For example:
  * <ul>
  * <li> [I  - this is the class name of a one dimensional integer array
  * <li> [Ljava/lang/Object -  this is the class name of a one dimensional
  * array of Objects
  * </ul> 
  */
public class NewArray extends Expression {
  int dimensions;
  private boolean includesAssignment = false;
  private Type arrayType;
  private Type elementType;
  private static Type intType = new Type(T_INT);

  /** 
   * Construct a node that represents the creation of an uninitialized array
   * of specified array class and dimensions.  For example:
   * <pre><code>NewArray("[[Ljava/lang/Object",new int[] {2, 2}); </code></pre> 
   * In this example the NewArray instance defined a two dimensional array of
   * dimensions 2 X 2.
   * <p>
   * If the dimensions specified in the arrayClassName are not the same as
   * the number of elements in the dimensions array then a ClassException 
   * will be thrown by this constructor.
   * <p>
   * If the arrayClassName is not a valid class name, or does not specify an 
   * array class then a ClassException will be thrown by this constructor. 
   */
  public NewArray(String arrayClassName, int[] dimensions) throws ClassException {	
    this.dimensions = dimensions.length;
    arrayType = Type.parseType(arrayClassName);
    if (! arrayType.isArrayType()) 
      throw new ClassException("Attempt to create a NewArray node for a non-array class: " +
			       arrayClassName);
    // Restriction needs to be relaxed to allow implicit dimension specification
    if (! (arrayType.getArrayDimensions() == dimensions.length))
      throw new ClassException("Attempt to create a NewArray node with mispecified dimensions: " +
			       arrayClassName);
    elementType = arrayType.getArrayBaseElementType();
    if (elementType.isReferenceType()) {
      addJavaNode(getElementClassRef(arrayClassName));
    }
    for (int i = 0; i < dimensions.length; i++)
      addJavaNode(new Value(dimensions[i]));
  }	

  /**
   * Construct a node that represents the creation of a one dimensional array
   * and immediately initialize the created array to the values specified in 
   * initialValues. 
   * <p>
   * If the arrayClassName specified is not a one-dimensional array
   * class name then this constructor will throw a ClassException.
   */  
  public NewArray(String arrayClassName, Expression[] initialValues) throws ClassException {	
    arrayType = Type.parseType(arrayClassName);
    // Need to find some way of specifying and checking initializations that involve
    // multiple dimensions.
    if (! (arrayType.getArrayDimensions() == 1))
      throw new ClassException("Cannot initialize multiple dimension array" + arrayClassName);
    dimensions = 1;
            
    elementType = arrayType.getArrayBaseElementType();
    if (elementType.isReferenceType()) {
      addJavaNode(getElementClassRef(arrayClassName));
    }
    addJavaNode(new Value(initialValues.length));
    for (int i = 0 ; i < initialValues.length ; i ++) { 
      addJavaNode(new Value(i));
      addJavaNode(initialValues[i]);
    }
    includesAssignment = true;
  }


  /** 
   * Construct a node that represents the creation of an uninitialized 
   * 1-dimensional of specified array class, whose length is determined
   * at runtime. For Example:
   *
   * <pre><code>NewArray("[Ljava/lang/Object",new Variable("x", "I")); </code></pre> 
   *
   * In this example the NewArray instance defined a one dimensional array of
   * length determined by the value of local variable x.
   *
   * Ultimately, this will allow multidimensional arrays, and will take
   * an array of Expression arguments, but this conflicts with the current
   * interface for creating an initialized 1-d array.
   */
  public NewArray(String arrayClassName, Expression arrayLength) throws ClassException {	
    this.dimensions = 1;
    arrayType = Type.parseType(arrayClassName);
    if (! arrayType.isArrayType()) 
      throw new ClassException("Attempt to create a NewArray node for a non-array class: " +
			       arrayClassName);
    // Restriction needs to be relaxed to allow implicit dimension specification
    elementType = arrayType.getArrayElementType();
    if (elementType.isReferenceType()) {
      addJavaNode(getElementClassRef(arrayClassName));
    }
    if (!arrayLength.getExpressionType().isIntegralType())
      throw new ClassException("Size of array in NewArray, " + arrayLength + " was not of integral type.");
    addJavaNode(new Cast(intType, arrayLength));
    includesAssignment = false;
  }	



  private ClassRef getElementClassRef(String arrayClassName) throws ClassException {
    int len = arrayClassName.length();
  
    String innerClassName 
      = (len > 1 && arrayClassName.charAt(1) == SIGC_CLASS) ?
      arrayClassName.substring(2,len-1) :
      arrayClassName.substring(1);
    return new ClassRef(innerClassName);
  }

  @Override
  void emit(EmitState state, boolean leaveOnStack, 
	    Statement continuation) 
      throws ClassException
  {
    super.emit(state,leaveOnStack,continuation);
    Vector instructions = state.instructions;
    int stackRef = state.stackSize;
    Instruction ins;
    int ref = 0;
    if (dimensions == 1) {
      if (elementType.isReferenceType()) {
	ClassRef classRef = (ClassRef) children.elementAt(ref++);	
	classRef.generateConstants(state.pool);
	int index = classRef.getWhere();
	ins = Instruction.makeInstruction(opc_anewarray,index);
      }
      else if (elementType.isBooleanType())
	ins = Instruction.makeInstruction(opc_newarray,4);
      else if (elementType.isCharType())
	ins = Instruction.makeInstruction(opc_newarray,5);
      else if (elementType.isFloatType())
	ins = Instruction.makeInstruction(opc_newarray,6);
      else if (elementType.isDoubleType())
	ins = Instruction.makeInstruction(opc_newarray,7);
      else if (elementType.isByteType())
	ins = Instruction.makeInstruction(opc_newarray,8);
      else if (elementType.isShortType())
	ins = Instruction.makeInstruction(opc_newarray,9);
      else if (elementType.isLongType())
	ins = Instruction.makeInstruction(opc_newarray,11);
      else ins = Instruction.makeInstruction(opc_newarray,10);
			
      ((Expression) children.elementAt(ref++)).emit(state,leaveOnStack,continuation);
	
      if (includesAssignment) {
	instructions.addElement(ins);
	int i = 0;
	while (ref < children.size()) {
	  instructions.addElement(Instruction.makeInstruction(opc_dup));
	  state.pushStack();
	  ((Expression) children.elementAt(ref++)).emit(state,leaveOnStack,continuation);
	  if (! (ref < children.size()))
	    throw new ClassException("Unbalanced NewArray node");
	  ((Expression) children.elementAt(ref++)).emit(state,leaveOnStack,continuation);
	  Instruction.emitArrayStoreInstruction(state,elementType);
	}
      }	
      else {
	instructions.addElement(ins);
      }
    }
    else {
      if (includesAssignment) {
	//instructions.addElement(Instruction.makeInstruction(opc_multianewarray,index));
	//state.pushStack();
	// Multidimensional initialization code here.
      }
      else {
	//	Value nextElement;
	//	for (ref++; ref < children.size(); ref++)
	//		((Value) children.elementAt(ref)).emit(state,leaveOnStack);
      }
      //ins = Instruction.makeInstruction(opc_multianewarray,index);
      //instructions.addElement(ins);
    } 
  }

  /**
   * Return the type of this Expression
   */
  @Override
  public Type getExpressionType() {
    return arrayType;
  }

}
