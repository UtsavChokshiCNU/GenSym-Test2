package com.gensym.controls;

import java.beans.*;
import java.awt.Image;
import java.awt.Toolkit;

public class TwConnectorBeanInfo extends AWTDerivedBeanInfo{
  private Image icon32x32 = Toolkit.getDefaultToolkit().getImage(this.getClass().getResource ("connector.gif"));

  @Override
  public Class getBeanClass()
  {
    return TwConnector.class;
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
    if (methodName.equals("closeConnection") ||
	methodName.equals("createConnection"))
      methodDescriptor.setExpert(false);
    else
      methodDescriptor.setExpert(true);
  }

  @Override
  protected PropertyDescriptor modifyPropertyDescriptor(PropertyDescriptor propertyDescriptor)
  {
    String propertyName = propertyDescriptor.getName();
    if (propertyName.equals("host") ||
	propertyName.equals("port"))
      propertyDescriptor.setExpert(false);
    else
      propertyDescriptor.setExpert(true);
    return propertyDescriptor;
  }

  @Override
  protected void modifyEventSetDescriptor(EventSetDescriptor eventSetDescriptor)
  {
    String eventName = eventSetDescriptor.getName();
    if (eventName.equals("twConnection") ||
	eventName.equals("workspaceShowing"))
      eventSetDescriptor.setExpert(false);
    else
      eventSetDescriptor.setExpert(true);
  }

}
