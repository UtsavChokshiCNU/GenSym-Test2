package com.gensym.classtools;

class ContinuableAndBreakableContext {

  boolean breakableContext;
  boolean continuableContext;
  int breakTarget;
  int continueTarget;

  ContinuableAndBreakableContext(boolean breakableContext,
				 boolean continuableContext,
				 int breakTarget,
				 int continueTarget)
  {
    this.breakableContext = breakableContext;
    this.continuableContext = continuableContext;
    this.breakTarget = breakTarget;
    this.continueTarget = continueTarget;
  }
}

