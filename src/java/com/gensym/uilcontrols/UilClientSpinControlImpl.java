package com.gensym.uilcontrols;

import com.gensym.widgets.Spin;
import com.gensym.util.Symbol;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.modules.uillib.UilSpinControlEntryBox;

class UilClientSpinControlImpl extends UilClientEditBoxImpl implements UilClientSpinControl{

  static final long serialVersionUID = -8637474011363075884L;

  private double uilSpinControlLowValue;
  private double uilSpinControlHiValue;
  private double uilSpinControlIncrement;
  private boolean uilSpinControlPermitWrapping;

  private UILSpinControl spin;

  UilClientSpinControlImpl(UilSpinControlEntryBox uilSpinControl, UILSpinControl component, Class staticClass)
       throws G2AccessException{
    super(uilSpinControl, component.getEditBox(), staticClass);
    this.spin = component;
    setUilSpinControlLowValue(((Number)uilSpinControl.getUilSpinControlLowValue()).doubleValue());
    setUilSpinControlHiValue(((Number)uilSpinControl.getUilSpinControlHiValue()).doubleValue());
    setUilSpinControlIncrement(((Number)uilSpinControl.getUilSpinControlIncrement()).doubleValue());
    setUilSpinControlPermitWrapping(((Boolean)uilSpinControl.getUilSpinControlPermitWrapping()).booleanValue());
    fieldType.setFormatType("Quantity");
  }

  @Override
  public double getUilSpinControlLowValue(){
    return uilSpinControlLowValue;
  }

  @Override
  public double getUilSpinControlHiValue(){
    return uilSpinControlHiValue;
  }

  @Override
  public double getUilSpinControlIncrement(){
    return uilSpinControlIncrement;
  }

  @Override
  public boolean getUilSpinControlPermitWrapping(){
    return uilSpinControlPermitWrapping;
  }

  @Override
  public void setUilSpinControlLowValue(double lowValue){
    uilSpinControlLowValue = lowValue;
    fieldType.setMinimumValue(uilSpinControlLowValue);
    spin.setMinValue(getUilSpinControlLowValue());
  }

  @Override
  public void setUilSpinControlHiValue(double highValue){
    uilSpinControlHiValue = highValue;
    fieldType.setMaximumValue(uilSpinControlHiValue);
    spin.setMaxValue(getUilSpinControlHiValue());
  }

  @Override
  public void setUilSpinControlIncrement(double increment){
    uilSpinControlIncrement = increment;
    spin.setIncrement(getUilSpinControlIncrement());
  }

  @Override
  public void setUilSpinControlPermitWrapping(boolean permitWrapping){
    uilSpinControlPermitWrapping = permitWrapping;
    spin.setWrap(getUilSpinControlPermitWrapping());
  }

  @Override
  public void uilEnableGrobj(){
    super.uilEnableGrobj();
    spin.setEnabled(true);
  }

  @Override
  public void uilDisableGrobj(){
    super.uilDisableGrobj();
    spin.setEnabled(false);
  }
}


    
    
