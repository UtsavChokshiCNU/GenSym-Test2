/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 CenteredWarningialog.java
 *
 */

package com.gensym.ntw.util;

import java.awt.Window;
import java.awt.Frame;
import com.gensym.dlg.WarningDialog;
import com.gensym.dlg.StandardDialogClient;

class CenteredWarningDialog extends WarningDialog{

  private Window centerWindow;

  CenteredWarningDialog(KbMessageTableView msgTableView, Window centerWindow, String title, boolean modal,
		 String message, StandardDialogClient client){
    super(msgTableView.getParentFrame(centerWindow), title, modal, message, client);
    this. centerWindow = centerWindow;
  }

  @Override
  public void setVisible(boolean visible){
    if (visible)
      WindowUtil.centerFrame (centerWindow, this);
    show();
  }
}
