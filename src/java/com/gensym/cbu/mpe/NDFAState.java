package com.gensym.cbu.mpe;

import java.beans.*;

public class NDFAState implements java.io.Serializable
{
  private PropertyChangeSupport support;
  String terminalStateName = "";
  boolean isStart;
  String bindingStart = "";
  String bindingEnd = "";
  TransitionSpecification[] transitions;
  boolean visited;

  public NDFAState()
  {
    support = new PropertyChangeSupport(this);
  }

  NDFAState(NDFAState state)
  {
    terminalStateName = state.terminalStateName;
    isStart = state.isStart;
    if (state.transitions != null)
      {
	transitions = new TransitionSpecification[state.transitions.length];
	for (int i=0; i<transitions.length; i++)
	  transitions[i] = state.transitions[i];
      }
    bindingStart = state.bindingStart;
    bindingEnd = state.bindingEnd;
  }

  NDFAState(String terminalStateName, boolean isStart, 
	    TransitionSpecification transition)
  {
    this.terminalStateName = terminalStateName;
    this.isStart = isStart;
    transitions = new TransitionSpecification[] { transition };
  }

  public PropertyChangeSupport getSupport()
  {
    return support;
  }

  public void setSupport(PropertyChangeSupport support)
  {
    this.support = support;
  }

  public void addPropertyChangeListener(PropertyChangeListener listener)
  {
    //    Thread.dumpStack();
    support.addPropertyChangeListener(listener);
  }

  public void removePropertyChangeListener(PropertyChangeListener listener)
  {
    support.removePropertyChangeListener(listener);
  }

  public String getTerminalStateName()
  {
    return terminalStateName;
  }

  public void setTerminalStateName(String name)
  {
    String oldName = terminalStateName;
    terminalStateName = name;
    if (support != null)
      support.firePropertyChange("terminalStateName", oldName, name);
  }

  public String getBindingStart()
  {
    return bindingStart;
  }

  public void setBindingStart(String bindingStart)
  {
    this.bindingStart = bindingStart;
  }

  public String getBindingEnd()
  {
    return bindingEnd;
  }

  public void setBindingEnd(String bindingEnd)
  {
    this.bindingEnd = bindingEnd;
  }

  public boolean isStart()
  {
    return isStart;
  }

  public void setStart(boolean isStart)
  {
    this.isStart = isStart;
  }
  
  @Override
  public String toString()
  {
    String bindingText = "";
    if (bindingExists(bindingStart) && bindingExists(bindingEnd))
      bindingText = " bindStart="+bindingStart+" bindingEnd="+bindingEnd;
    else if (bindingExists(bindingStart))
      bindingText = " bindStart="+bindingStart;
    else if (bindingExists(bindingEnd))
      bindingText = " bindEnd="+bindingEnd;
    return "<NDFAState "+hashCode()+", start="+isStart+bindingText+">";    
  }

  private boolean bindingExists(String s)
  {
    return s != null && !s.equals("");
  }
}
