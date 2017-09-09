package com.gensym.classtools;

import java.util.Vector;

class SubRoutineJump extends Statement {
    
    SubRoutineJump(Label label) throws ClassException {
        addJavaNode(label);
    }

    @Override
    void emit(EmitState state, boolean leaveOnStack,
              Statement continuation) 
      throws ClassException {
        Label label = (Label) children.elementAt(0);
        Instruction ins = Instruction.makeInstruction(opc_jsr,0);
        ins.labelNameIfAny = label.getLabel();
        state.instructions.addElement(ins);
    }
}
