package com.gensym.newclasstools;

import java.util.Vector;

public class Continue extends Statement {
		
  public Continue () {
  }

  @Override
  void emit(EmitState state, boolean leaveOnStack, 
	    Statement continuation) 
            throws ClassException
  {
    //System.out.println("Emitting Continue");
    generateLineNumberInfo(state);
    if (state.isContinuableContext())
      state.emitJumpToContinue();
    else throw new ClassException("Continue statement found outside of continuable context");
  }
}
