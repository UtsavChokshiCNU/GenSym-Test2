package com.gensym.demos;

import java.awt.Frame;
import com.gensym.dlg.WarningDialog;
import com.gensym.dlg.StandardDialogClient;

public class ErrorDialog extends com.gensym.dlg.WarningDialog {

  public ErrorDialog (Exception e, Frame frame, StandardDialogClient client, String title,
		      String msg){
    super (frame, title, true, msg, client);
    System.err.println(e);
    setVisible (true);
  }

}
