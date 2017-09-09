package com.gensym.controls;

import java.beans.*;
import java.awt.Image;
import java.awt.Toolkit;

public class G2TextFieldBeanInfo extends AWTDerivedBeanInfo {
  private Image icon32x32 = Toolkit.getDefaultToolkit().getImage(this.getClass().getResource ("g2textfield.gif"));

  @Override
  public Image getIcon(int iconKind) {
    if (iconKind == ICON_COLOR_32x32) return icon32x32;
    return null;
  }

  @Override
  public Class getBeanClass()
  {
    return G2TextField.class;
  }

 
}
