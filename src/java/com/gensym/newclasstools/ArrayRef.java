package com.gensym.newclasstools;

import java.util.Vector;

public class ArrayRef extends Atom {

  public ArrayRef(Expression array, Expression index) throws ClassException {			
    Type tpe = index.getExpressionType();
    if (! tpe.isIntegerType())
      throw new ClassException("Invalid index for array reference");  
    tpe = array.getExpressionType();
    if (! tpe.isArrayType())
      throw new ClassException("Attempt to make array reference on type: " + tpe);
    expressionType = tpe.getArrayElementType(); 	
    addJavaNode(array);
    addJavaNode(index);				
  }

  @Override
  void emit(EmitState state, boolean leaveOnStack, Statement continuation)
    throws ClassException {
    generateLineNumberInfo(state);				
    Vector instructions = state.instructions;
    ((Expression) children.elementAt(0)).emit(state,true, continuation);
    ((Expression) children.elementAt(1)).emit(state,true, continuation);
    Instruction.emitArrayLoadInstruction(state,expressionType);
  }

  @Override
  public String toString() {
    return "<ArrayRef, type = " + expressionType + ">";
  }
}
