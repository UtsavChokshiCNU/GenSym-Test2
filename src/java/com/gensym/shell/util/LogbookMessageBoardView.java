package com.gensym.shell.util;

import com.gensym.classes.SystemTable;
import com.gensym.jgi.G2AccessException;

public interface LogbookMessageBoardView {
  public String getKey();
  public void disposeView() throws G2AccessException;
  public SystemTable getParameters();
  public void handleShow();
}
