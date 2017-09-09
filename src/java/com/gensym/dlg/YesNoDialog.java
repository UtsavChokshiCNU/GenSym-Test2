
package com.gensym.dlg;

import java.awt.*;
import java.awt.event.*;

public class YesNoDialog extends QuestionDialog{

  private int selectedButtonCode;
  
  public YesNoDialog(Frame   frame,
		     String  title,
		     boolean isModal,
		     String  message,
		     StandardDialogClient client) {
    super(frame, title, isModal, new String[]{YES_LABEL, NO_LABEL}, new int[]{YES, NO},
          message, img, client);
  }

  @Override
  protected void dispatchCallback (int code) {
    selectedButtonCode = code;
    super.dispatchCallback(code);
  }

  public boolean selectedYes(){
    return selectedButtonCode == YES;
  }
}
