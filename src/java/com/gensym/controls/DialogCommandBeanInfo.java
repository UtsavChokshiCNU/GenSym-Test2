package com.gensym.controls;

import java.beans.*;
import java.awt.Image;
import java.awt.Toolkit;
import com.gensym.util.ModifiableBeanInfo;

public class DialogCommandBeanInfo extends ModifiableBeanInfo{
  private Image icon32x32 = Toolkit.getDefaultToolkit().getImage(this.getClass().getResource ("dialog_command.gif"));


  @Override
  public Class getBeanClass()
  {
    return DialogCommand.class;
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
    if (methodName.equals("apply") ||
	methodName.equals("close") ||
	methodName.equals("ok"))
      methodDescriptor.setExpert(false);
    else
      methodDescriptor.setExpert(true);
  }
}
