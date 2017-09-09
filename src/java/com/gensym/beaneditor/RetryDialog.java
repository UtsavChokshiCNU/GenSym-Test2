package com.gensym.beaneditor;

import java.awt.Panel;
import java.awt.Label;
import java.awt.Frame;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeEvent;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;

public class RetryDialog extends StandardDialog{
  RetryPanel retryPanel;

  public RetryDialog(Frame frame, String  title, boolean isModal, String  message, String currentFileName,
		     StandardDialogClient client){
    super(frame, title, isModal, new String[]{"Retry", "Ignore"}, 
          new int[]{OK, CANCEL}, new RetryPanel(message, currentFileName), client); 
  }

  @Override
  protected int getButtonAlignment () {
    return CENTER;
  }

  String getFileName(){
    return ((RetryPanel)getDialogComponent()).getFileName();
  }

}

class RetryPanel extends Panel {
  String fileName;
  FileNameEditor fileNameEditor;
  
  RetryPanel(String message, String currentFileName){
    setLayout(new GridLayout(2, 1));
    Panel messagePanel = new Panel();
    messagePanel.setLayout(new FlowLayout(FlowLayout.LEFT));
    fileName = currentFileName;
    messagePanel.add(new Label(message));
    add(messagePanel);
    fileNameEditor = new FileNameEditor();
    fileNameEditor.setValue(currentFileName);
    add(fileNameEditor);
  }
  
  String getFileName(){
    return (String)fileNameEditor.getValue();
  }
  
}


