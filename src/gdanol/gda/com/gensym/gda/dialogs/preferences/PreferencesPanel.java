	
package com.gensym.gda.dialogs.preferences;


import com.gensym.message.Resource;
import com.gensym.gda.dialogs.gdaPanel;
import com.gensym.util.Symbol;

/**
The parent of all gdaPanels in the com.gensym.gda.dialogs.preferences package.
*/
public class PreferencesPanel extends gdaPanel {


	public PreferencesPanel(PreferencesDialog d) {
    	super(d);
    	i18n=Resource.getBundle("com.gensym.gda.dialogs.preferences.Messages");
    	attributeEditorFillConstraint=java.awt.GridBagConstraints.HORIZONTAL;
	}
		
	public Symbol getSettingClass() {return settingClass;}
	public void setSettingClass(Symbol settingclass) {settingClass=settingclass;}
	
	/**
	The name of the gfr-module-setting subclass which is editing by this panel.
	*/
	protected Symbol settingClass;
}