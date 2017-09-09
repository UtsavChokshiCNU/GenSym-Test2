package com.gensym.controls;

import java.beans.SimpleBeanInfo;
import java.awt.Image;
import java.awt.Toolkit;

public class ScriptUtilitiesBeanInfo extends SimpleBeanInfo{
  private Image icon32x32 = Toolkit.getDefaultToolkit().getImage(this.getClass().getResource ("script_utilities.gif"));

  @Override
  public Image getIcon(int iconKind) {
    if (iconKind == ICON_COLOR_32x32) return icon32x32;
    return null;
  }

}
