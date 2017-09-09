package com.gensym.controls;

import java.beans.*;
import com.gensym.util.ModifiableBeanInfo;

public abstract class AWTDerivedBeanInfo extends ModifiableBeanInfo{

  @Override
  protected void modifyEventSetDescriptor(EventSetDescriptor eventSetDescriptor)
  {
    String eventName = eventSetDescriptor.getName();
    if (eventName.equals("objectChange") ||
	eventName.equals("objectUpdate") ||
	eventName.equals("action"))
      eventSetDescriptor.setExpert(false);
    else
      eventSetDescriptor.setExpert(true);
  }


  @Override
  protected PropertyDescriptor modifyPropertyDescriptor(PropertyDescriptor propertyDescriptor)
  {
    String propertyName = propertyDescriptor.getName();
    if (propertyName.equals("foreground") ||
	propertyName.equals("background") ||
	propertyName.equals("warnOnBadSyntax") ||
	propertyName.equals("fieldType") ||
	propertyName.equals("visible") ||
	propertyName.equals("emptyFieldImpliesNull") ||
	propertyName.equals("font") ||
	propertyName.equals("defaultContents") ||
	propertyName.equals("attributeName") ||
	propertyName.equals("attribute") ||
	propertyName.equals("editable") ||
	propertyName.equals("text") ||
	propertyName.equals("propagateEveryCharacterTyped") ||
	propertyName.equals("showQuotesForTextType") ||
	propertyName.equals("label") ||
	propertyName.equals("lowerLimit") ||
	propertyName.equals("lowerLimitMode") ||
	propertyName.equals("upperLimit") ||
	propertyName.equals("upperLimitMode"))
      propertyDescriptor.setExpert(false);
    else
      propertyDescriptor.setExpert(true);
    return propertyDescriptor;
  }

  @Override
  protected void modifyMethodDescriptor(MethodDescriptor methodDescriptor)
  {
    String methodName = methodDescriptor.getName();
    if (methodName.equals("hide") ||
	methodName.equals("show") ||
	methodName.equals("setEditable") ||
	methodName.equals("objectUpdated") ||
	methodName.equals("objectChanged") ||
	methodName.equals("actionPerformed"))
      methodDescriptor.setExpert(false);
    else
      methodDescriptor.setExpert(true);
  }
}
