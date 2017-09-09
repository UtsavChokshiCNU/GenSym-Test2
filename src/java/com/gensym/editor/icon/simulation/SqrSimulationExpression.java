package com.gensym.editor.icon.simulation;

public class SqrSimulationExpression extends MathSimulationExpression {
  public static final String SQR = "sqr(t)";

  public SqrSimulationExpression(int amplitude,
				 int period,
				 int xAxisOrigin) {
    super(amplitude, period, xAxisOrigin);
  }
  
  @Override
  public String[] getVariableKeys() {
    return new String[] {SQR};
  }
  
  @Override
  protected double computeY(double x) {
    return Math.pow(x,2);
  }
  
}
