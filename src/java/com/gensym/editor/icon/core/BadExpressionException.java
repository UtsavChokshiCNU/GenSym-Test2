package com.gensym.editor.icon.core;

public class BadExpressionException extends Exception {
  public BadExpressionException(String msg) {
    super(msg);
  }

  public BadExpressionException(Exception nestedException) {
    super(nestedException.getMessage());
  }  
}
