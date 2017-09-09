package com.gensym.beaneditor;

import java.awt.Frame;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.CommandConstants;

public class RetryHandler implements StandardDialogClient{
  private Frame frame;
  private boolean retry = false;
  private String fileName;
  
  RetryHandler(Frame frame, String fileName){
    this.frame = frame;
    this.fileName = fileName;
  }

  boolean retry(){
    RetryDialog retryDialog = new RetryDialog(frame, "Jar Not Found", true, "Enter a new jar name:", fileName, this);
    retryDialog.setVisible(true);
    return retry;
  }

  String getFileName(){
    return fileName;
  }

  @Override
  public void dialogDismissed(StandardDialog d, int cmdCode){
    if (cmdCode == CommandConstants.OK){
      retry = true;
      fileName = ((RetryDialog)d).getFileName();
    }
  }
}
