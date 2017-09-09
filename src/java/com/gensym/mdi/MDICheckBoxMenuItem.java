/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 MDICheckboxMenuItem.java
 *
 */
package com.gensym.mdi;

import javax.swing.JCheckBoxMenuItem;

/** This class should be used in the MDI package only.
 *  It is the check-box menu item used in the window menu. */
class MDICheckBoxMenuItem extends JCheckBoxMenuItem{
  MDIDocument child;

  MDICheckBoxMenuItem(MDIDocument child, String label){
    super(label);
    this.child = child;
  }

  MDIDocument getMDIDocument(){
    return child;
  }
}
