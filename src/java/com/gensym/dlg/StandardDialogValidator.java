package com.gensym.dlg;

import java.util.EventListener;

/**
 * An interface for notifications of command events generated
 * by the buttons on a StandardDialog.  Implementations of this interface are
 * responsible for validating the contents of the StandardDialog passed to them
 * for the command code.  If any validator returns false, the StandardDialogClient
 * will not be informed of the event, and the dialog will not be dismissed.
 *
 * @author Nathan Brown
 */
public interface StandardDialogValidator
{
  /**
   * The method that is called when a command button on a
   * StandardDialog is activated by the user
   * @param d the StandardDialog that is the source of the event
   * @param cmdCode the command code for the button
   * @see CommandConstants
   */
  public boolean isDialogValid(StandardDialog dlg, int cmdCode);
}