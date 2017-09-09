package com.gensym.cbu.mpe;

public class DFATransition implements TestTypes
{
  int testType;
  CharacterTester test;
  int nextStateIndex;
  char arg;

  DFATransition(int testType, char arg, int nextStateIndex)
  {
    this.testType = testType;
    this.arg = arg;
    this.nextStateIndex = nextStateIndex;
  }

  public DFATransition()
  {
  }

  public int getTestType()
  {
    return testType;
  }

  public void setTestType(int testType)
  {
    this.testType = testType;
  }

  public int getNextStateIndex()
  {
    return nextStateIndex;
  }

  public void setNextStateIndex(int nextStateIndex)
  {
    this.nextStateIndex = nextStateIndex;
  }

  public char getArg()
  {
    return arg;
  }

  public void setArg(char arg)
  {
    this.arg = arg;
  }
}
