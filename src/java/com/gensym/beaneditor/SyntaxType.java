package com.gensym.beaneditor;

import java.beans.PropertyEditorManager;

class SyntaxType  implements java.io.Serializable{
  static final SyntaxType JAVA = new SyntaxType(HookupFactory.JAVA);
  static final SyntaxType G2SCRIPT = new SyntaxType(HookupFactory.G2SCRIPT);

  private static final Class thisClass = com.gensym.beaneditor.SyntaxType.class;
  private static final Class editor = com.gensym.beaneditor.SyntaxTypeEditor.class;

  static{
    PropertyEditorManager.registerEditor(thisClass, editor);
  }

  private int type =  HookupFactory.JAVA;
  
  SyntaxType(){}

  SyntaxType(int type){
    this.type = type;
  }
  
  int getType(){
    return type;
  }

  void setType(int type){
    this.type = type;
  }
}
