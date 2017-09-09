package com.gensym.gda.dialogs.preferences;

import java.awt.BorderLayout;
import javax.swing.border.TitledBorder;

import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.gda.controls.*;
import com.gensym.dlgevent.*;
import com.gensym.classes.SymbolArray;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;

public class gdiNetworkColorDlgPanel extends PreferencesPanel {
	
	public gdiNetworkColorDlgPanel(PreferencesDialog dialog) {
		super(dialog);
		
		settingClass=Symbol.intern("GDA-NETWORK-COLOR-SETTINGS");
		for (int i=0;i<9;i++) {
			colorEditor = new ThreeColorEditor();
			setEditorAttributes(colorEditor, i+"-");
			placeAttributeEditor(colorEditor, labels[i], NETWORK_BACKGROUND_COLOR_, i);
		}

	}

	
	protected void setEditorAttributes(ThreeColorEditor editor, String attribute) {
		editor.setBackgroundAttribute(Symbol.intern(attribute + NETWORK_BACKGROUND_COLOR));
		editor.setBorderAttribute(Symbol.intern(attribute + NETWORK_BORDER_COLOR));
		editor.setTextAttribute(Symbol.intern(attribute + NETWORK_TEXT_COLOR));		
	}
	
	protected ThreeColorEditor colorEditor;
	
	protected final static String NETWORK_BACKGROUND_COLOR = "NETWORK-BACKGROUND-COLOR";
	protected final static String NETWORK_BORDER_COLOR = "NETWORK-BORDER-COLOR";
	protected final static String NETWORK_TEXT_COLOR = "NETWORK-TEXT-COLOR";
	
	protected final static Symbol NETWORK_BACKGROUND_COLOR_ = 
		Symbol.intern(NETWORK_BACKGROUND_COLOR);

	protected final String[] labels = new String[] {
		localize("RunningLabel"),
		localize("PausedLabel"),
		localize("ResetLabel"),
		localize("TimedOutLabel"),
		localize("ConnectedLabel"),
		localize("NotConnectedLabel"),
		localize("AttemptingLabel"),
		localize("FailedLabel"),
		localize("ErrorLabel")
	};
	

}