package com.gensym.editor.icon.simulation;

import com.gensym.editor.icon.core.Parameter;
import java.util.Vector;

public abstract class MathSimulationExpression extends SimulationExpression {
  private int amplitude;
  private int period;
  private int xAxisOrigin;

  public MathSimulationExpression(int amplitude,
				  int period,
				  int xAxisOrigin)
  {
    this.period = period;
    this.amplitude = amplitude;
    this.xAxisOrigin = xAxisOrigin;
  }

  protected abstract double computeY(double x);
  
  @Override
  public void setTime(int t) {
    currentTime = t;
    double xIncrement = 2*Math.PI/period;
    double currentX = currentTime*xIncrement;
    Integer value = new Integer((int)(amplitude*computeY(currentX)) + xAxisOrigin);
    Parameter[] ls = null;
    synchronized(listeners) {
      ls = new Parameter[listeners.size()];
      listeners.copyInto(ls);
    }
    for (int i=0;i<ls.length;i++) {
      Parameter param = ls[i];
      param.setDefaultValue(value);
    }
  }
  
}

