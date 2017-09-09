
package com.gensym.controls;

import java.beans.*;
import java.awt.Image;
import java.awt.Toolkit;
import com.gensym.util.ModifiableBeanInfo;

public class ItemProxyBeanInfo extends ModifiableBeanInfo
{
  private final static Class beanClass = ItemProxy.class;
  private final static Class customizerClass = ItemProxyCustomizer.class;   
  private Image icon32x32 = Toolkit.getDefaultToolkit().getImage(this.getClass().getResource ("item_proxy.gif"));

  @Override
  public BeanDescriptor getBeanDescriptor()
  {
    return new BeanDescriptor(beanClass, customizerClass);
  }


  @Override
  public Class getBeanClass()
  {
    return beanClass;
  }

  @Override
  public Image getIcon(int iconKind){
    if (iconKind == ICON_COLOR_32x32) return icon32x32;
    return null;
  }

  @Override
  protected void modifyMethodDescriptor(MethodDescriptor methodDescriptor)
  {
    String methodName = methodDescriptor.getName();
    if (methodName.equals("download") ||
	methodName.equals("upload") ||
	methodName.equals("editItem") ||
	methodName.equals("objectChanged") ||
	methodName.equals("objectUpdated") ||
	methodName.equals("itemRetrieved") ||
	methodName.equals("itemRetrievalFailed"))
      methodDescriptor.setExpert(false);
    else
      methodDescriptor.setExpert(true);
  }

  @Override
  protected void modifyEventSetDescriptor(EventSetDescriptor eventSetDescriptor) {
    String eventSetName = eventSetDescriptor.getName();
    if (eventSetName.equals("objectDeletion"))
      eventSetDescriptor.setExpert(true);
  }
    
}

