package com.gensym.beaneditor;

import java.beans.PropertyEditorManager;

public class FileName{
  private String fileName;

  static 
  {
    Class editor = com.gensym.beaneditor.FileNameEditor.class;
    PropertyEditorManager.registerEditor
      (com.gensym.beaneditor.FileName.class, editor);
  }

  public FileName(String fileName){
    this.fileName = fileName;
  }

  public String getFileName(){
    return fileName;
  }
  
}
