package com.gensym.classtools;

class Label extends Statement {
	String labelValue;

      private static long uniqueCount = 0;
      
      Label(String label) {
          this.labelValue = label;
      }

	static Label generateUniqueLabel() {
	    return new Label(gensym());	
	}

      String getLabel() {
          return labelValue;
      }

	static String gensym() {
        return "<_" + 
	    	Long.toHexString(uniqueCount++) +
	    	Long.toHexString(System.currentTimeMillis()) +
	  	">";
	}
      
      @Override
      public String toString() {
        return "<Label: " + labelValue +">";
      }

      @Override
	  void emit(EmitState state, boolean leaveOnStack, Statement continuation) 
        throws ClassException {
            Instruction ins = state.getJumpTargetInstruction();
            ins.labelNameIfAny = labelValue;
            state.instructions.addElement(ins);
      }
}
