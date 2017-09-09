/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 StandardGridBagPanel.java
 *
 */
package com.gensym.uiutil;

import java.awt.Component;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Panel;

public class StandardGridBagPanel extends Panel {

  protected GridBagLayout gridBagLayout = new GridBagLayout();

  public StandardGridBagPanel () {
    new Panel();
  }

  public void addComponent(Component component, GridBagConstraints gridC) {
    gridBagLayout.setConstraints(component, gridC);
    add(component);
  }
}
