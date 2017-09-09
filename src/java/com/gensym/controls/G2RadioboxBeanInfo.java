package com.gensym.controls;

import java.beans.SimpleBeanInfo;
import java.beans.PropertyDescriptor;
import java.awt.Image;
import java.awt.Toolkit;

public class G2RadioboxBeanInfo extends AWTDerivedBeanInfo{
  private Image icon32x32 = Toolkit.getDefaultToolkit().getImage(this.getClass().getResource ("g2radiobutton.gif"));

  @Override
  public Image getIcon(int iconKind) {
    if (iconKind == ICON_COLOR_32x32) return icon32x32;
    return null;
  }

  @Override
  public Class getBeanClass()
  {
    return G2Radiobox.class;
  }


  @Override
  protected PropertyDescriptor modifyPropertyDescriptor(PropertyDescriptor propertyDescriptor)
  {
    String propertyName = propertyDescriptor.getName();
    if (propertyName.equals("members"))
      propertyDescriptor.setExpert(false);
    return propertyDescriptor;
  }
}
