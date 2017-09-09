package com.gensym.demos.dialogapplet;

import java.beans.*;
import com.gensym.util.ModifiableBeanInfo;

public class ControlChartBeanInfo extends ModifiableBeanInfo
{

  @Override
  public Class getBeanClass()
  {
    return ControlChart.class;
  }

  @Override
  protected void modifyEventSetDescriptor(EventSetDescriptor eventSetDescriptor)
  {
    String eventName = eventSetDescriptor.getName();
    if (eventName.equals("alarm") ||
	eventName.equals("action"))
      eventSetDescriptor.setExpert(false);
    else
      eventSetDescriptor.setExpert(true);
  }


  @Override
  protected PropertyDescriptor modifyPropertyDescriptor(PropertyDescriptor propertyDescriptor)
  {
    String propertyName = propertyDescriptor.getName();
    if (propertyName.equals("font") ||
	propertyName.equals("foreground") ||
	propertyName.equals("background") ||
	propertyName.equals("timespan") ||
	propertyName.equals("upperLimit") ||
	propertyName.equals("lowerLimit")||
	propertyName.equals("attributeName"))
      propertyDescriptor.setExpert(false);
    else
      propertyDescriptor.setExpert(true);
    return propertyDescriptor;
  }

  @Override
  protected void modifyMethodDescriptor(MethodDescriptor methodDescriptor)
  {
    String methodName = methodDescriptor.getName();
    //System.out.println("calling modMethDesc on "+methodName+
    //	       " for "+getBeanClass().getName());
    if (methodName.equals("newSample") ||
	methodName.equals("objectUpdated"))
      methodDescriptor.setExpert(false);
    else
      methodDescriptor.setExpert(true);
  }
}
