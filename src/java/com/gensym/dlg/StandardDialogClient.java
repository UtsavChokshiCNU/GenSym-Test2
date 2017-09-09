

package com.gensym.dlg;

import java.awt.*;

/**
 * An interface for notifications of command events generated
 * by the buttons on a StandardDialog. An instance of an
 * implementation of this interface is passed to the constructor
 * of a StandardDialog, which then map action events on all
 * buttons generated for the dialog to calls to the dialogDismissed
 * method of the StandardDialogClient. The listener can implement
 * application specific logic in the callback to respond to the
 * event.
 * 
 * @author vkp
 * @version 1.1 4/29/98 Added Javadoc
 */
public interface StandardDialogClient {

  /**
   * The method that is called when a command button on a
   * StandardDialog is activated by the user
   * @param d the StandardDialog that is the source of the event
   * @param cmdCode the command code for the button
   * @see CommandConstants
   */
  void dialogDismissed (StandardDialog d, int cmdCode);

}
