package com.gensym.newclasstools;


public class LongBranchException extends Exception 
{

  Instruction destination;
  Instruction branchInstruction;
  public LongBranchException(Instruction branchInstruction, Instruction destination) {
    super();
    this.branchInstruction = branchInstruction;
    this.destination = destination;
  }
}
