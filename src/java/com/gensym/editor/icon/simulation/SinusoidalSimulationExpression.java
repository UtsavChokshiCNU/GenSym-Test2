package com.gensym.editor.icon.simulation;

import com.gensym.editor.icon.core.Parameter;
import java.util.Vector;

public class SinusoidalSimulationExpression extends SimulationExpression {
  private int amplitude;
  private int period;
  private int xAxisOrigin;
  public static final String SIN = "sin(t)";
  public static final String COS = "cos(t)";

  @Override
  public String[] getVariableKeys() {
    return new String[] {SIN, COS};
  }
  
  public SinusoidalSimulationExpression(int amplitude,
					int period,
					int xAxisOrigin)
  {
    this.period = period;
    this.amplitude = amplitude;
    this.xAxisOrigin = xAxisOrigin;
  }
  
  @Override
  public void setTime(int t) {
    currentTime = t;
    double xIncrement = 2*Math.PI/period;
    double currentX = currentTime*xIncrement;
    Integer sinValue = new Integer(((int)(amplitude*Math.sin(currentX))) + xAxisOrigin);
    Integer cosValue = new Integer(((int)(amplitude*Math.cos(currentX))) + xAxisOrigin);
    Parameter[] ls = null;
    synchronized(listeners) {
      ls = new Parameter[listeners.size()];
      listeners.copyInto(ls);
    }
    for (int i=0;i<ls.length;i++) {
      Parameter param = ls[i];
      String key = param.getSimulationPreferenceKey();
      if (COS.equals(key))
	param.setDefaultValue(cosValue);
      else if (SIN.equals(key))
	param.setDefaultValue(sinValue);
    }
  }
  
}

