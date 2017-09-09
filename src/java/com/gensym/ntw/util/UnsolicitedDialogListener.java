package com.gensym.ntw.util;

/**
 * Interface for listening to unsolicited dialog mechanism
 */
public interface UnsolicitedDialogListener extends java.util.EventListener {
  
  public void enterDialog(UnsolicitedDialogEvent evt);
  
  public void exitDialog(UnsolicitedDialogEvent evt);

  public void updateDialog(UnsolicitedDialogEvent evt);

}
