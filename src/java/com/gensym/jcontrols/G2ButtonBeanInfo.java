package com.gensym.jcontrols;

import java.beans.SimpleBeanInfo;
import java.awt.Image;
import java.awt.Toolkit;
import com.gensym.controls.AWTDerivedBeanInfo;

public class G2ButtonBeanInfo extends AWTDerivedBeanInfo{
  private Image icon32x32 = Toolkit.getDefaultToolkit().getImage(this.getClass().getResource ("g2button.gif"));

  @Override
  public Image getIcon(int iconKind) {
    if (iconKind == ICON_COLOR_32x32) return icon32x32;
    return null;
  }

  @Override
  public Class getBeanClass()
  {
    return G2Button.class;
  }
}
