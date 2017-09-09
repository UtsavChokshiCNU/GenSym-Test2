package com.gensym.uilcontrols;

import com.gensym.util.Symbol;

public interface UilClientSpinControl extends UilClientEditBox{

  public double getUilSpinControlLowValue();
  public double getUilSpinControlHiValue();
  public double getUilSpinControlIncrement();
  public boolean getUilSpinControlPermitWrapping();

  public void setUilSpinControlLowValue(double lowValue);
  public void setUilSpinControlHiValue(double highValue);
  public void setUilSpinControlIncrement(double increment);
  public void setUilSpinControlPermitWrapping(boolean permitWrapping);
}
