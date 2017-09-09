package com.gensym.jcontrols;

import java.beans.SimpleBeanInfo;
import java.beans.PropertyDescriptor;
import java.beans.MethodDescriptor;
import java.awt.Image;
import java.awt.Toolkit;
import com.gensym.controls.AWTDerivedBeanInfo;

public class G2ComboBoxBeanInfo extends AWTDerivedBeanInfo{
  private Image icon32x32 = Toolkit.getDefaultToolkit().getImage(this.getClass().getResource ("g2combobox.gif"));

  @Override
  public Image getIcon(int iconKind) {
    if (iconKind == ICON_COLOR_32x32) return icon32x32;
    return null;
  }

  @Override
  public Class getBeanClass()
  {
    return G2ComboBox.class;
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
    if (methodName.equals("initalizeChoices"))
      methodDescriptor.setExpert(false);
    else super.modifyMethodDescriptor(methodDescriptor);
  }

}
