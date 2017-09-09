package com.gensym.classtools;

import java.util.Vector;

public class Break extends Statement {

  public Break () {
  }

  @Override
  void emit(EmitState state, boolean leaveOnStack, Statement continuation)
    throws ClassException {
    generateLineNumberInfo(state);
    if (state.isBreakableContext())
      state.emitJumpToBreak(continuation);
    else throw new ClassException("Break statement found outside of breakable context");
  }
}
