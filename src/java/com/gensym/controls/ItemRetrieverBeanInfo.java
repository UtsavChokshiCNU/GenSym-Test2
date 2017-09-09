package com.gensym.controls;

import java.beans.*;
import java.awt.Image;
import java.awt.Toolkit;
import com.gensym.util.ModifiableBeanInfo;

public class ItemRetrieverBeanInfo extends ModifiableBeanInfo{
  private Image icon32x32 = Toolkit.getDefaultToolkit().getImage(this.getClass().getResource ("item_retriever.gif"));

  @Override
  public Class getBeanClass()
  {
    return ItemRetriever.class;
  }

  @Override
  public Image getIcon(int iconKind) {
    if (iconKind == ICON_COLOR_32x32) return icon32x32;
    return null;
  }


  @Override
  protected void modifyMethodDescriptor(MethodDescriptor methodDescriptor)
  {
    String methodName = methodDescriptor.getName();
    if (methodName.equals("retrieveItem") ||
	methodName.equals("retrieveItemForVB"))

      methodDescriptor.setExpert(false);
    else
      methodDescriptor.setExpert(true);
  }


  @Override
  protected PropertyDescriptor modifyPropertyDescriptor(PropertyDescriptor propertyDescriptor)
  {
    String propertyName = propertyDescriptor.getName();
    if (propertyName.equals("host") ||
	propertyName.equals("port") ||
	propertyName.equals("itemClassName") ||
	propertyName.equals("itemName"))
      propertyDescriptor.setExpert(false);
    else
      propertyDescriptor.setExpert(true);
    return propertyDescriptor;
  }
}
