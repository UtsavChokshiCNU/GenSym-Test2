package com.gensym.cbu.mpe;

public class DFAState
{
  DFATransition[] transitions;
  String[] starts;
  String[] ends;
  boolean isStop;  // for limited lookahead
  int tokenIndex = -1; // -1 means not a terminal State
  

  DFAState(DFATransition[] transitions, int tokenIndex)
  {
    this.transitions = transitions;
    this.tokenIndex = tokenIndex;
  }

  public DFAState()
  {

  }

  public DFATransition[] getTransitions()
  {
    return transitions;
  }

  public void setTransitions(DFATransition[] transitions)
  {
    this.transitions = transitions;
  }
  
  public String[] getStarts()
  {
    return starts;
  }

  public void setStart(String[] starts)
  {
    this.starts = starts;
  }

  public String[] getEnds()
  {
    return ends;
  }

  public void setEnd(String[] ends)
  {
    this.ends = ends;
  }

  public boolean isStop()
  {
    return isStop;
  }

  public void setStop(boolean isStop)
  {
    this.isStop = isStop;
  }

  public int getTokenIndex()
  {
    return tokenIndex;
  }
  
  public void setTokenIndex(int tokenIndex)
  {
    this.tokenIndex = tokenIndex;
  }
}


