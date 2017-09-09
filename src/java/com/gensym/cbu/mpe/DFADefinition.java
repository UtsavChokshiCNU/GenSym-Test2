package com.gensym.cbu.mpe;

public class DFADefinition
{
  DFAState[] states;
  int initialStateIndex;
  DFAToken[] tokens;
  
  DFADefinition(DFAState[] states, DFAToken[] tokens, int initialStateIndex)
  {
    this.states = states;
    this.tokens = tokens;
    this.initialStateIndex = initialStateIndex;
  }

  public DFADefinition()
  {

  }

  public DFAState[] getStates()
  {
    return states;
  }

  public void setStates(DFAState[] states)
  {
    this.states = states;
  }
  
  public int getInitialStateIndex()
  {
    return initialStateIndex;
  }

  public void setInitialStateIndex(int initialStateIndex)
  {
    this.initialStateIndex = initialStateIndex;
  }

  public DFAToken[] getTokens()
  {
    return tokens;
  }

  public void setTokens(DFAToken[] tokens)
  {
    this.tokens = tokens;
  }
}
