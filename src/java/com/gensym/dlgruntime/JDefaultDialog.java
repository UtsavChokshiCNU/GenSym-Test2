/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	Native Dialog Launcher - Ndm.java
 *
 *     
 *   Modifications:
 *
 */


package com.gensym.dlgruntime;

import java.awt.Frame;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.JDialog;
import com.gensym.controls.DialogCommand;

class JDefaultDialog extends JDialog {
  JDefaultDialog (Frame f, final DialogCommand cmdBean) {
    super (f);
    addWindowListener (new WindowAdapter () {
      @Override
      public void windowClosing(WindowEvent e) {
	//System.out.println ("Dialog WindowAdapter informing cmdBean of closing!");
	cmdBean.close ();
	}
    });
  }
  JDefaultDialog (Frame f) {
    super(f);
  }
}
  
