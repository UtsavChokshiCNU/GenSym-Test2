package com.gensym.wksp;

import java.beans.*;
import com.gensym.util.ModifiableBeanInfo;
import java.awt.Image;
import java.awt.Toolkit;

public class ScalableWorkspaceViewBeanInfo extends WorkspaceViewBeanInfo {
  private Image icon32x32 = Toolkit.getDefaultToolkit().getImage(this.getClass().getResource ("scalable-workspaceview.gif"));

  @Override
  public Image getIcon(int iconKind) {
    if (iconKind == ICON_COLOR_32x32) return icon32x32;
    return null;
  }

  @Override
  protected Class getBeanClass(){
    return ScalableWorkspaceView.class;
  }

  @Override
  protected PropertyDescriptor modifyPropertyDescriptor(PropertyDescriptor propertyDescriptor){
    String propertyName = propertyDescriptor.getName();
    if (propertyName.equals("scaledToFit")||
	 propertyName.equals("scaleX") ||
	 propertyName.equals("scaleY"))
      propertyDescriptor.setExpert(false);
    else
      return super.modifyPropertyDescriptor(propertyDescriptor);
    return propertyDescriptor;
  }

  @Override
  protected void modifyMethodDescriptor(MethodDescriptor methodDescriptor){
    String methodName = methodDescriptor.getName();
    if (methodName.equals("setScale"))
      methodDescriptor.setExpert(false);
    else
      super.modifyMethodDescriptor(methodDescriptor);
  }

  @Override
  protected void modifyEventSetDescriptor(EventSetDescriptor eventSetDescriptor){
    String eventName = eventSetDescriptor.getName();
    if (eventName.equals("transformation"))
      eventSetDescriptor.setExpert(false);
    else
      super.modifyEventSetDescriptor(eventSetDescriptor);
  }

}
