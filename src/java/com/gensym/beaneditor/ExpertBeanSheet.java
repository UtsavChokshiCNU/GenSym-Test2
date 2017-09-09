package com.gensym.beaneditor;

import java.awt.Frame;
import java.beans.PropertyDescriptor;
import com.gensym.beansruntime.BeanSheet;

public class ExpertBeanSheet extends BeanSheet{

  public ExpertBeanSheet(Object newBean, Frame newFrame, int x, int y){
    super(newBean, newFrame, x, y);
  }

  @Override
  protected boolean isPropertyDisplayable(PropertyDescriptor prop){
    Preferences preferences = Preferences.currentPreferences;
    return (!preferences.isExpertMode() ? !prop.isExpert() : true);
  }
}


