/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ClassChooserDialog.java
 *
 *
 */
package com.gensym.ntw.util;

import java.awt.Frame;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.message.Resource;
import com.gensym.ntw.TwAccess;
import com.gensym.util.Symbol;

public class ClassChooserDialog extends StandardDialog{

  private static final Resource i18n = Resource.getBundle("com.gensym.ntw.util.Messages");

  public ClassChooserDialog(Frame frame, boolean modal, TwAccess connection, Symbol[] selectedClasses,
			    StandardDialogClient client) {
    super(frame, i18n.getString("ClassChooserTitle"), modal, 
	  new String[]{OK_LABEL, CANCEL_LABEL}, new int[]{OK, CANCEL},
          new ClassChooserPanel(connection, selectedClasses), client);
    setDefaultButton(OK);
    setCancelButton(CANCEL);
  }

  public Symbol[] getSelection(){
    return ((ClassChooserPanel)getDialogComponent()).getSelection();
  }

  @Override
  protected int getButtonAlignment(){
    return CENTER;
  }
}
