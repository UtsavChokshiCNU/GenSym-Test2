package com.gensym.beaneditor;

import java.beans.PropertyEditorManager;
import com.gensym.beansruntime.StringVector;

public class FileNameVector extends StringVector {

  static 
  {
    Class editor = com.gensym.beaneditor.FileNameVectorEditor.class;
    //System.out.println("registering editor class "+editor);
    PropertyEditorManager.registerEditor
      (com.gensym.beaneditor.FileNameVector.class, editor);
  }
}
