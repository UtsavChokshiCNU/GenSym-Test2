package com.gensym.newclasstools;

import java.util.Vector;

public class While extends Statement implements MacroNode {

		public While (Expression condition, Statement work) throws ClassException {
			Type tpe = condition.getExpressionType();
			if (! tpe.isBooleanType())
				throw new ClassException("Condition in while statement must be boolean, received" +
										tpe);
			addJavaNode(condition);
			addJavaNode(work);
		} 


		//****************************** Macro Expansion *********************
		// In the case that the expression is the constant false, then expand
		// to nothing

		@Override
		public boolean expansionRequired() {
				Expression exp = (Expression) children.elementAt(0);
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
		}


		//****************************** Emitting ************************


  @Override
  void emit(EmitState state, boolean leaveOnStack, 
            Statement continuation) 
      throws ClassException {			
    generateLineNumberInfo(state);
    Expression exp =  (Expression) children.elementAt(0);
    Statement st =  (Statement) children.elementAt(1);
    boolean loopCondition = true;
    
    // Check if the condition is the constant true or not
    if (exp instanceof Value && (((Value) exp).getBooleanValue()))
      loopCondition = false;
    
    Vector instructions = state.instructions;
    
    // Create jump target instructions
    Instruction jump1 = state.getJumpTargetInstruction();
    Instruction jump2 = state.getJumpTargetInstruction();
    Instruction ins; 

    
    // Emit jump target instruction #1
    instructions.addElement(jump1);
     
    // Emit conditional
    if (loopCondition) {
      exp.emit(state,true,continuation);
      // With jump to target #1	
      if (! (exp instanceof OperatorCall))  {
	ins = Instruction.makeInstruction(opc_ifeq,0);
	ins.jumpDestination = jump2;
	instructions.addElement(ins);		
      }
      else {
	ins = (Instruction) instructions.lastElement();
	ins.jumpDestination = jump2;
      }
    }
   
    // Emit Statement
    ContinuableAndBreakableContext saved =
      state.getContinuableAndBreakableContext();
    state.setContinuableAndBreakableContext(jump1,jump2);
    st.emit(state,false,this);
    state.restoreContinuableAndBreakableContext(saved);
    
    // Emit Goto with branch to target #1
    ins = Instruction.makeInstruction(opc_goto,0);
    ins.jumpDestination = jump1;
    instructions.addElement(ins);
    
    // Emit jump target #2
    instructions.addElement(jump2);

    state.doContinuation(continuation);
  }
}
