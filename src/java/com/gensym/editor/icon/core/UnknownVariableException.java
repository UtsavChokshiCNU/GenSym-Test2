package com.gensym.editor.icon.core;

public class UnknownVariableException extends BadExpressionException {
  public UnknownVariableException(String msg) {
    super(msg);
  }

  public UnknownVariableException(Exception nestedException) {
    super(nestedException.getMessage());
  }  
}
