
package com.gensym.demos.docs.custompopups;

import java.awt.Frame;
import com.gensym.dlg.*;

/**
 * A subclass of InputDialog that changes the button
 * labels appropriately
 */

class ConnectionInputDialog extends InputDialog {

  ConnectionInputDialog (Frame parent, String title, boolean isModal,
			 String[] labels, String[] initialValues,
			 StandardDialogClient client) {
    super (parent, title, isModal, labels, initialValues,
	   new String[] {"Connect", "Cancel"}, new int[] {CommandConstants.OK, CommandConstants.CANCEL},
	   client);
  }

}
