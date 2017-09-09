/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2ModuleDialog.java
 *
 *  Description:
 *
 *
 *	 Author:
 *		Todd O'Brien		Feb/98
 *
 *     
 *   Modifications:
 *
 */

package com.gensym.g2studio.dialogs;

import java.awt.Frame;
import java.awt.Insets;
import com.gensym.classes.Module;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;

/**
 */
public class G2EditModuleDialog extends StandardDialog {

  /**
   */
  public G2EditModuleDialog (Frame parentFrame, String title, 
			     boolean isModal,
                             Module module, 
			     StandardDialogClient client) {  
    super (parentFrame, title, isModal,
	   new String[] {OK_LABEL, CANCEL_LABEL},
	   new int[] {OK, CANCEL},
	   new G2EditModulePanel(module), client);
    pack();
  }

  @Override
  public Insets getInsets() {
    Insets insets = super.getInsets();
    return new Insets(insets.top + 10, 10, 10, 10);
  }
}


