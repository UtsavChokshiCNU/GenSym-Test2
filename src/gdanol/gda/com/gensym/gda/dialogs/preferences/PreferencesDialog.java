	
package com.gensym.gda.dialogs.preferences;

import com.gensym.message.Resource;
import com.gensym.gda.dialogs.gdaDialog;

public class PreferencesDialog extends gdaDialog {


/**the parent of Preferences dialogs.
*/
	public PreferencesDialog() {}
	
	public PreferencesDialog(java.awt.Frame frame) {
		super(frame);
		i18n=Resource.getBundle("com.gensym.gda.dialogs.preferences.Messages");
	}
		
	protected PreferencesPanel dpanel;
}