package com.gensym.newclasstools;

import java.util.Vector;

/** 
  * The class <code>NewArray</code> can be used to create a new array of
  * a particular array class.
  */
public class NewArray extends Expression {
  int rank;
  int dimensionsSpecified;
  private boolean includesAssignment = false;
  private Type arrayType;
  private Type elementType;
  private static Type intType = Type.INT_TYPE;

  /**
   * Construct a node that represents the creation of a one dimensional array
   * and immediately initialize the created array to the values specified in 
   * initialValues. 
   * <p>
   * The arrayElementType should be the type of the element, not the
   * type of the array.
   * <p>
   * Note that this is an incompatible change from the old classtools.
   */  
  public NewArray(Type arrayElementType, Expression[] initialValues) throws ClassException {	
    this.elementType = arrayElementType;
    rank = 1;
    dimensionsSpecified =1;
    arrayType = Type.makeType(elementType, 1);
    addJavaNode(new Value(initialValues.length));
    for (int i = 0 ; i < initialValues.length ; i ++) { 
      addJavaNode(new Value(i));
      addJavaNode(initialValues[i]);
    }
    includesAssignment = true;
  }


  /**
   * Construct a node that represents the creation of a (possibly
   * multidimensional) array and immediately initialize the created array
   * to the values specified in 
   * initialValues. 
   * <p>
   * If a 1-dimensional array is desired, initialValues should be an array of
   * Expression. If a 2-dimensional array is desired, initialValues should be
   * an array of array of Expression, and so forth. The arrays that are the
   * elements of the initialValues need not be the same length, so this can
   * be used to create and initialize nonrectangluar arrays.
   * <p>
   * This is not yet implemented, and pretty low down on the priority list.
   * Let me know if you actually need this---Andy
   * 
   */  
  public NewArray(Type arrayElementType, Object[] initialValues) throws ClassException {	
    throw new ClassException("Multidimensional newarray with initializers not yet implemented");
  }

  /** 
   * Construct a node that represents the creation of an uninitialized 
   * (or partially initialized, in the case of multidimensional arrays)
   * array specified element type, whose length is determined
   * at runtime. For Example:
   *
   * <pre><code>NewArray(Type.INT_TYPE, 1, new Expression[]{Variable("x", Type.INT_TYPE)}); </code></pre> 
   *
   * In this example the NewArray instance defined a one dimensional array of
   * length determined by the value of local variable x, corresponding to the
   * java expression
   *
   * <pre> <code>new int[x];</code></pre>
   *
   * the length of arrayDimensions must be at least 1, and must be
   * less than or equal to the specified arrayRank. Specifying
   * an arrayDimensions expression of length less than the specified arrayRank
   * corresponds to a java expression where the spines of the new array are
   * not fully initialized. For example,
   *
   * <pre><code>NewArray(Type.INT_TYPE, 2, new Expression[]{Variable("x", Type.INT_TYPE)}); </code></pre> 
   *
   * corresponds to the java code
   *
   * <pre> <code>new int[x][];</code></pre>,
   *
   * while
   *
   * <pre><code>NewArray(Type.INT_TYPE, 2, new Expression[]{Variable("x", Type.INT_TYPE), new Variable("y", Type.INT_TYPE)}); </code></pre> 
   *
   * corresponds to the java code
   *
   * <pre> <code>new int[x][y];</code></pre>,
   *
   * <p>
   * The arrayElementType should be the type of the element, not the
   * type of the array.
   * <p>
   * Note that this is an incompatible change from the old classtools.
   */
  public NewArray(Type arrayElementType, int arrayRank,
		  Expression[] arrayDimensions) throws ClassException {	
		    
    this.rank = arrayRank;
    dimensionsSpecified = arrayDimensions.length;
    elementType = arrayElementType;
    arrayType = Type.makeType(elementType, rank);
    int dimensionExpressionCount = arrayDimensions.length;
    if (dimensionExpressionCount == 0)
      throw new ClassException("At least one dimension must be specified in a NewArray");
    if (dimensionExpressionCount > rank)
      throw new ClassException("NewArray: " + dimensionExpressionCount + " dimensions given for an array of rank only " + rank);
    for (int i = 0; i < dimensionExpressionCount; i++) {
      if (!arrayDimensions[i].getExpressionType().isIntegralType())
	throw new ClassException("Dimension " + i + " of array in NewArray, " + arrayDimensions[i] + " was not of integral type.");
      addJavaNode(new Cast(intType, arrayDimensions[i]));
    }
    includesAssignment = false;
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
    for (int i = 0; i < dimensionsSpecified; i++) {
      ((Expression)children.elementAt(i)).emit(state, true, continuation);
    }
    if (rank > 1) {
      if (includesAssignment)
	throw new ClassException("Multidimensional arrays with initializers not yet supported");
      ins = Instruction.makeInstruction(opc_multianewarray,
					new ClassConstant(arrayType),
					dimensionsSpecified);
    } else {
      if (elementType.isReferenceType())
	ins = Instruction.makeInstruction(opc_anewarray, new ClassConstant(elementType));
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
    }
  instructions.addElement(ins);
  state.popStack(dimensionsSpecified - 1);
  if (includesAssignment) {
    for (int i = dimensionsSpecified; i < children.size(); i+=2) {
      instructions.addElement(Instruction.makeInstruction(opc_dup));
      state.pushStack();
      ((Expression) children.elementAt(i)).emit(state, true, continuation);
      if (! (i < children.size()))
	throw new ClassException("Unbalanced NewArray node");
      ((Expression) children.elementAt(i+1)).emit(state,leaveOnStack,continuation);
      Instruction.emitArrayStoreInstruction(state,elementType);
    }
  }
  state.maybePopStack(leaveOnStack, getExpressionType());
  }

  /**
   * Return the type of this Expression
   */
  @Override
  public Type getExpressionType() {
    return arrayType;
  }

  // Actually, I suppose new int[0] is a constant expression, but we'll
  // ignore this case for simplicity.
  @Override
  public boolean isConstantExpression() {
    return false;
  }
}
