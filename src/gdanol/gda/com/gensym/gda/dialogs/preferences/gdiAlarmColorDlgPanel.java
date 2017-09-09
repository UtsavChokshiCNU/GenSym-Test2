package com.gensym.gda.dialogs.preferences;

import javax.swing.BoxLayout;
import javax.swing.JPanel;
import javax.swing.border.TitledBorder;

import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.gda.controls.*;
import com.gensym.dlgevent.*;
import com.gensym.classes.SymbolArray;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;

public class gdiAlarmColorDlgPanel extends PreferencesPanel {
	
	public gdiAlarmColorDlgPanel(PreferencesDialog dialog) {
		super(dialog);
		
		settingClass=Symbol.intern("GDA-ALARM-COLOR-SETTING");
		
		JPanel panel = new JPanel();
		panel.setLayout(new BoxLayout(panel, BoxLayout.X_AXIS));
		panel.setBorder(new TitledBorder(localize("SeverityPanelTitle")));
		addPanel(panel, null, 0);
		PreferencesPanel gdapanel = new PreferencesPanel(dialog);
		panel.add(gdapanel);
		gdapanel.setMinimumPanelWidth(0);
		for (int i=1;i<16;i++) {
			severity = new ThreeColorEditor();
			setEditorAttributes(severity, i+"-");
			gdapanel.placeAttributeEditor(severity, ""+i, SEVERITY_BACKGROUND_COLOR_, i);
			if (i==5 || i==10) {
				panel.add(gdapanel=new PreferencesPanel(dialog));
				gdapanel.setMinimumPanelWidth(0);
			}
		}
		
		noAlarm = new ThreeColorEditor();
		setEditorAttributes(noAlarm, "0-");
		placeAttributeEditor(noAlarm, localize("NoAlarmLabel"), SEVERITY_BACKGROUND_COLOR_, 1);
	
		inhibitedAlarms = new ColorEditor();
		placeAttributeEditor(inhibitedAlarms, localize("InhibitedAlarmsLabel"), GDA_INHIBITED_ALARM_COLOR_, 2);
		
		unAcknowledged = new ThreeColorEditor();
		unAcknowledged.setBackgroundAttribute(Symbol.intern(unack+ACKNOWLEDGEMENT_BACKGROUND_COLOR));
		unAcknowledged.setBorderAttribute(Symbol.intern(unack+ACKNOWLEDGEMENT_BORDER_COLOR));
		unAcknowledged.setTextAttribute(Symbol.intern(unack + ACKNOWLEDGEMENT_TEXT_COLOR));		
		placeAttributeEditor(unAcknowledged, localize("UnacknowledgedLabel"), SEVERITY_BACKGROUND_COLOR_, 3);

		acknowledged = new ThreeColorEditor();
		acknowledged.setBackgroundAttribute(Symbol.intern(ack+ACKNOWLEDGEMENT_BACKGROUND_COLOR));
		acknowledged.setBorderAttribute(Symbol.intern(ack+ACKNOWLEDGEMENT_BORDER_COLOR));
		acknowledged.setTextAttribute(Symbol.intern(ack + ACKNOWLEDGEMENT_TEXT_COLOR));		
		placeAttributeEditor(acknowledged, localize("AcknowledgedLabel"), SEVERITY_BACKGROUND_COLOR_, 4);

	}

	
	protected void setEditorAttributes(ThreeColorEditor editor, String attribute) {
		editor.setBackgroundAttribute(Symbol.intern(attribute + SEVERITY_BACKGROUND_COLOR));
		editor.setBorderAttribute(Symbol.intern(attribute + SEVERITY_BORDER_COLOR));
		editor.setTextAttribute(Symbol.intern(attribute + SEVERITY_TEXT_COLOR));		
	}
	
	protected ThreeColorEditor severity;
	protected ThreeColorEditor noAlarm;
	protected ColorEditor inhibitedAlarms;
	protected ThreeColorEditor unAcknowledged;
	protected ThreeColorEditor acknowledged;

	
	protected final static String SEVERITY_BACKGROUND_COLOR = "SEVERITY-BACKGROUND-COLOR";
	protected final static String SEVERITY_BORDER_COLOR = "SEVERITY-BORDER-COLOR";
	protected final static String SEVERITY_TEXT_COLOR = "SEVERITY-TEXT-COLOR";
	
	protected final static String ACKNOWLEDGEMENT_BACKGROUND_COLOR = "ACKNOWLEDGEMENT-BACKGROUND-COLOR";
	protected final static String ACKNOWLEDGEMENT_BORDER_COLOR = "ACKNOWLEDGEMENT-BORDER-COLOR";
	protected final static String ACKNOWLEDGEMENT_TEXT_COLOR = "ACKNOWLEDGEMENT-TEXT-COLOR";
	
	protected final static String unack="0-";
	protected final static String ack = "1-";

	protected final static Symbol SEVERITY_BACKGROUND_COLOR_ = 
		Symbol.intern(SEVERITY_BACKGROUND_COLOR);	
	protected final static Symbol GDA_INHIBITED_ALARM_COLOR_ = 
		Symbol.intern("GDA-INHIBITED-ALARM-COLOR");	

}