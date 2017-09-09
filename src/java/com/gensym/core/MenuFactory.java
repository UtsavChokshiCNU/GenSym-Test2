package com.gensym.core;

import javax.swing.JMenuBar;
import javax.swing.JMenu;

public interface MenuFactory {
  public JMenuBar getMenuBar(Object focalObject);
  public JMenu getMenu(Object focalObject);
}
