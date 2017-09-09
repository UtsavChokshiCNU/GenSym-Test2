package com.gensym.gda.dialogs.preferences;


import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiStartupSettingsPanel extends PreferencesPanel {
	
	public gdiStartupSettingsPanel(PreferencesDialog dialog) {
		super(dialog);

		settingClass=Symbol.intern("GDL-STARTUP-SETTINGS");

    	attributeEditorFillConstraint=java.awt.GridBagConstraints.BOTH;		

    	animateAtStartup = CheckBoxEditor.createYesNoCheckBox();
		placeAttributeEditor(animateAtStartup, ANIMATE_AT_STARTUP_, 0);
		
		enableDataInputAtStartup=CheckBoxEditor.createYesNoCheckBox();
		placeAttributeEditor(enableDataInputAtStartup, ACTIVATE_DATA_INSERTION_AT_STARTUP_, 1);
		
		postGlobalInitializer = new TextOrNoneEditor();
		placeAttributeEditor(postGlobalInitializer, POST_GLOBAL_INITIALIZER_, symbolFieldType, 2);
		
		postGlobalResetter = new TextOrNoneEditor();
		placeAttributeEditor(postGlobalResetter, POST_GLOBAL_RESETTER_, symbolFieldType, 3);
		
	}

	
	protected CheckBoxEditor animateAtStartup;
	protected CheckBoxEditor enableDataInputAtStartup;
	protected TextOrNoneEditor postGlobalInitializer;
	protected TextOrNoneEditor postGlobalResetter;
	
	protected final static Symbol ANIMATE_AT_STARTUP_ = Symbol.intern("ANIMATE-AT-STARTUP");	
	protected final static Symbol ACTIVATE_DATA_INSERTION_AT_STARTUP_ = Symbol.intern("ACTIVATE-DATA-INSERTION-AT-STARTUP");	
	protected final static Symbol POST_GLOBAL_INITIALIZER_ = Symbol.intern("POST-GLOBAL-INITIALIZER");	
	protected final static Symbol POST_GLOBAL_RESETTER_ = Symbol.intern("POST-GLOBAL-RESETTER");	

}