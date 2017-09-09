package com.gensym.editor.icon.simulation;

import com.gensym.editor.icon.core.Parameter;
import java.util.Vector;

public abstract class SimulationExpression
implements TimeListener
{
  protected Vector listeners = new Vector();  
  protected int currentTime = 0;  

  public abstract String[] getVariableKeys();
  
  public int getTime() {
    return currentTime;
  }

  public void addVariableListener(Parameter parameter, String key) {
    listeners.addElement(parameter);
  }
  
  public void removeVariableListener(Parameter parameter, String key) {
    listeners.removeElement(parameter);
  }
  
  public Parameter[] getParameters() {
    synchronized(listeners) {
      Parameter[] params = new Parameter[listeners.size()];
      listeners.copyInto(params);
      return params;
    }
  }
}
  
