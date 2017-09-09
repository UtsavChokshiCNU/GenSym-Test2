package com.gensym.classtools;

import java.util.Vector;

/** For advanced users of classtools who require explicit
* control over monitor locks.  This node adds the expression
* on the stack and then executes an opc_monitorexit instruction.
* The expression argument must be a class type.
*/
public class EnterMonitor extends Statement {
 
  public EnterMonitor (Expression exp) 
      throws ClassException
  {
    // Check that the expression is a class type.

    if(! exp.getExpressionType().isClassType())
      throw new ClassException("EnterMonitor requires class type");

    addJavaNode(exp);
  }

  @Override
  void emit(EmitState state, boolean leaveOnStack, 
        Statement continuation) 
        throws ClassException 
  {
    Expression exp = (Expression) children.elementAt(0);
    exp.emit(state, true, continuation);
    Instruction ins = Instruction.makeInstruction(opc_monitorenter);
    state.instructions.addElement(ins);
    state.popStack();
  }
}
