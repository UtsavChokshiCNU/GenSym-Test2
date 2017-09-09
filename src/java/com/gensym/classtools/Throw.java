package com.gensym.classtools;

import java.util.Vector;

public class Throw extends Statement {
  private static Type throwableType  
              = new Type(T_CLASS,
                          null,
                          "Ljava/lang/Throwable;",
                          0);
	    	
  public Throw (Expression exception) throws ClassException
  {
    addJavaNode(exception);
  }
 
  @Override
  void emit(EmitState state, boolean leaveOnStack,
            Statement continuation) 
    throws ClassException
 {
    super.emit(state, leaveOnStack, continuation);
    ((Expression) children.elementAt(0)).emit(state, true, continuation);
    Vector instructions = state.instructions;  
    instructions.addElement(Instruction.makeInstruction(opc_athrow));
 }


}
