package com.gensym.classtools;

import java.util.Vector;

public class Do extends Statement implements MacroNode {
	    
  public Do (Statement work,Expression condition) throws ClassException {
    Type tpe = condition.getExpressionType();
    if (! tpe.isBooleanType())
      throw new ClassException("Condition in while statement must be boolean, received" +
			       tpe);
    addJavaNode(work);
    addJavaNode(condition);
  }

  //****************************** Macro Expansion *********************
  // In the case that the expression is the constant false, then expand
  // to be just the Statement

  @Override

  public boolean expansionRequired() {
    Expression exp = (Expression) children.elementAt(1);
    try {
      if (exp instanceof Value && (! ((Value) exp).getBooleanValue()))
	return true;
      else return false;
    }
    catch (ClassException e) { 
      return false;
    }
  }
			
  @Override
			
  public void expandInto(JavaNode j) throws ClassException {				
    j.addJavaNode((JavaNode) children.elementAt(0));
  }

  @Override
void emit(EmitState state, boolean leaveOnStack, Statement continuation)
      throws ClassException {
  generateLineNumberInfo(state);
  Statement st =  (Statement) children.elementAt(0);
  Expression exp =  (Expression) children.elementAt(1);
  boolean loopCondition = true;
			
  Instruction ins;

  // Check if the condition is the constant true or not
  if (exp instanceof Value && (((Value) exp).getBooleanValue()))
    loopCondition = false;
			
  Vector instructions = state.instructions;

  // Create jump tag instructions
  Instruction jump1 = state.getJumpTargetInstruction();
  Instruction jump2 = state.getJumpTargetInstruction();
  Instruction jump3 = null;

  if (continuation != null)
    jump3 = state.getJumpTargetInstruction();
							
  // Emit jump tag instruction #1
  instructions.addElement(jump1);
			
  // Emit Statement
  ContinuableAndBreakableContext saved =
    state.getContinuableAndBreakableContext();
  state.setContinuableAndBreakableContext(jump2,jump3);
  st.emit(state,false,this);
  state.restoreContinuableAndBreakableContext(saved);

  // Emit jump tag instruction #2
  instructions.addElement(jump2);

  // Emit conditional
  exp.emit(state,true,continuation);

  if (loopCondition) {
    // With jump to tag #1				
    if (! (exp instanceof OperatorCall))  {
      ins = Instruction.makeInstruction(opc_ifne,0);
      ins.jumpTagIfAny = jump1.jumpTagIfAny;
      instructions.addElement(ins);					
    }
    else {
      ins = (Instruction) instructions.lastElement();
      ins.jumpTagIfAny = jump3.jumpTagIfAny;
    }
  }
  if (!loopCondition || (exp instanceof OperatorCall)) {
    ins = Instruction.makeInstruction(opc_goto,0);
    ins.jumpTagIfAny = jump1.jumpTagIfAny; 
    instructions.addElement(ins);
  }

  // Emit jump tag instruction #3
  instructions.addElement(jump3);

  state.doContinuation(continuation);
  }
}
