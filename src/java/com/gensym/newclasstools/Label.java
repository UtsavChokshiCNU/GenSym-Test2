package com.gensym.newclasstools;

import java.util.Vector;

class Label extends Statement {
	String label;

      private static long uniqueCount = 0;
      
      Label(String label) {
          this.label = label;
      }

	static Label generateUniqueLabel() {
	    return new Label(gensym());	
	}

      String getLabel() {
          return label;
      }

	static String gensym() {
        return "<_" + 
	    	Long.toHexString(uniqueCount++) +
	  // Ack! Phhtht!
	    	Long.toHexString(System.currentTimeMillis()) +
	  	">";
	}
      
      @Override
      public String toString() {
        return "<Label: " + label +">";
      }

      @Override
      void emit(EmitState state, boolean leaveOnStack, Statement continuation) 
        throws ClassException {
            Instruction ins = state.getJumpTargetInstruction();
            ins.labelNameIfAny = label;
            state.instructions.addElement(ins);
      }
}
