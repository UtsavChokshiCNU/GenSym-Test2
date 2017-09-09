package com.gensym.controls;

import java.beans.SimpleBeanInfo;
import java.beans.PropertyDescriptor;
import java.beans.MethodDescriptor;
import java.awt.Image;
import java.awt.Toolkit;

public class G2DropDownChoiceBeanInfo extends AWTDerivedBeanInfo{
  private Image icon32x32 = Toolkit.getDefaultToolkit().getImage(this.getClass().getResource ("g2dropdown.gif"));

  @Override
  public Image getIcon(int iconKind) {
    if (iconKind == ICON_COLOR_32x32) return icon32x32;
    return null;
  }

  @Override
  public Class getBeanClass()
  {
    return G2DropDownChoice.class;
  }

  @Override
  protected PropertyDescriptor modifyPropertyDescriptor(PropertyDescriptor propertyDescriptor)
  {
    String propertyName = propertyDescriptor.getName();
    if (propertyName.equals("choices") ||
	propertyName.equals("initializationAttribute"))
      propertyDescriptor.setExpert(false);
    return propertyDescriptor;
  }

  @Override
  protected void modifyMethodDescriptor(MethodDescriptor methodDescriptor)
  {
    String methodName = methodDescriptor.getName();
    if (methodName.equals("initializeChoices"))
      methodDescriptor.setExpert(false);
    else super.modifyMethodDescriptor(methodDescriptor);
  }

}
