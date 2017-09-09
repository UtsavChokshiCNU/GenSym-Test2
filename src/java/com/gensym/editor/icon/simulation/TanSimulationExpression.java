package com.gensym.editor.icon.simulation;

public class TanSimulationExpression extends MathSimulationExpression {
  public static final String TAN = "tan(t)";

  public TanSimulationExpression(int amplitude,
				 int period,
				 int xAxisOrigin) {
    super(amplitude, period, xAxisOrigin);
  }
  
  @Override
  public String[] getVariableKeys() {
    return new String[] {TAN};
  }
  
  @Override
  protected double computeY(double x) {
    return Math.tan(x);
  }
  
}
