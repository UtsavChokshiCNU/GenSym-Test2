package com.gensym.editor.icon.simulation;

import com.gensym.editor.icon.core.Parameter;
import java.util.Vector;

public class TimeSimulationExpression extends SimulationExpression {
  public static final String TIME = "t";

  @Override
  public String[] getVariableKeys() {
    return new String[] {TIME};
  }

  @Override
  public void setTime(int t) {
    currentTime = t;
    Integer val = new Integer(currentTime);
    Parameter[] ls = null;
    synchronized(listeners) {
      ls = new Parameter[listeners.size()];
      listeners.copyInto(ls);
    }
    for (int i=0;i<ls.length;i++) 
      ls[i].setDefaultValue(val);
  }

}

