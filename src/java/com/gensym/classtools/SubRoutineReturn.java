package com.gensym.classtools;

import java.util.Vector;

class SubRoutineReturn extends Statement {
	
    SubRoutineReturn(Variable addressOfSubRoutine) 
      throws ClassException
    {
     if (!(addressOfSubRoutine.getExpressionType().isReferenceType()))
       throw new ClassException(
       "Local variable for sub routine return must be a refernce type");
     addJavaNode(addressOfSubRoutine);
    }
    
    @Override
    void emit(EmitState state, boolean leaveOnStack, 
              Statement continuation) 
      throws ClassException {
        Variable var = (Variable) children.elementAt(0);
        var.generateVariableIds(state);
        Instruction ins = Instruction.makeInstruction(opc_ret,var.argumentNumber);
        state.instructions.addElement(ins);
    }
}
