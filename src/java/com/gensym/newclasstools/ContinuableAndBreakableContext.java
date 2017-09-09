package com.gensym.newclasstools;

class ContinuableAndBreakableContext {

  boolean breakableContext;
  boolean continuableContext;
  Instruction breakTarget;
  Instruction continueTarget;

  ContinuableAndBreakableContext(boolean breakableContext,
				 boolean continuableContext,
				 Instruction breakTarget,
				 Instruction continueTarget)
  {
    this.breakableContext = breakableContext;
    this.continuableContext = continuableContext;
    this.breakTarget = breakTarget;
    this.continueTarget = continueTarget;
  }
}

