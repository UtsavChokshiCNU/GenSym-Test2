package com.gensym.demos.chart;

import java.beans.*;
import java.awt.Toolkit;
import java.awt.Image;
import com.gensym.util.ModifiableBeanInfo;

public class ControlChartBeanInfo extends ModifiableBeanInfo
{

  @Override
  public Class getBeanClass()
  {
    return ControlChart.class;
  }
  
  private Image icon32x32 = Toolkit.getDefaultToolkit().getImage(this.getClass().getResource ("chart32x32.gif"));
  
  @Override
  public Image getIcon(int iconKind){
    if (iconKind == ICON_COLOR_32x32) return icon32x32;
    return null;
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
