package com.gensym.editor.icon.simulation;

public class SecSimulationExpression extends MathSimulationExpression {
  public static final String SEC = "sec(t)";

  public SecSimulationExpression(int amplitude,
				 int period,
				 int xAxisOrigin) {
    super(amplitude, period, xAxisOrigin);
  }
  
  @Override
  public String[] getVariableKeys() {
    return new String[] {SEC};
  }
  
  @Override
  protected double computeY(double x) {
    return 1/Math.cos(x);
  }
  
}
