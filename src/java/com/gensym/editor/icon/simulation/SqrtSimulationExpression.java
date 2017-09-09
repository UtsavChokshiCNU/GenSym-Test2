package com.gensym.editor.icon.simulation;

public class SqrtSimulationExpression extends MathSimulationExpression {
  public static final String SQRT = "sqrt(t)";

  public SqrtSimulationExpression(int amplitude,
				  int period,
				  int xAxisOrigin) {
    super(amplitude, period, xAxisOrigin);
  }
  
  @Override
  public String[] getVariableKeys() {
    return new String[] {SQRT};
  }
  
  @Override
  protected double computeY(double x) {
    return Math.sqrt(x);
  }
  
}
