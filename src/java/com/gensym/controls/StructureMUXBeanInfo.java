package com.gensym.controls;

import java.beans.*;
import java.awt.Image;
import java.awt.Toolkit;
import com.gensym.util.ModifiableBeanInfo;

public class StructureMUXBeanInfo extends ModifiableBeanInfo{
  private Image icon32x32 = Toolkit.getDefaultToolkit().getImage(this.getClass().getResource ("structure_mux.gif"));


  @Override
  public Class getBeanClass()
  {
    return StructureMUX.class;
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
    if (methodName.equals("objectUpdated") ||
	methodName.equals("objectChanged"))
      methodDescriptor.setExpert(false);
    else
      methodDescriptor.setExpert(true);
  }
}
