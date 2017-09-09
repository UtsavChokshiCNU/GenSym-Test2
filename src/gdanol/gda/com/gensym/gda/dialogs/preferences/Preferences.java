package com.gensym.gda.dialogs.preferences;

import java.util.Hashtable;
import java.util.Enumeration;

import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JPanel;
import javax.swing.BoxLayout;

import com.gensym.controls.SymbolVector;
import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.message.Resource;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.dlgevent.ObjectChangeEvent;


/**
Dialog for GDA Preferences.
Each PreferencesPanel has the property settingClass. 
*/
public class Preferences extends PreferencesDialog {
	
	public Preferences() {}

	/**
	*/
	public Preferences(java.awt.Frame frame) {
		super(frame);		
    	i18n=Resource.getBundle("com.gensym.gda.dialogs.preferences.Messages");		
		JTabbedPane tabbedPane = new JTabbedPane();
		scrollPane.setViewportView(tabbedPane);

		panels=new Hashtable();

		PreferencesDialog dialog;
		PreferencesPanel panel;
		
		panels.put(panel=new gdiBlockColorDlgPanel(dialog=new PreferencesDialog(frame)), dialog);
		tabbedPane.addTab(localize("Blocks&PathsColors"), createUnstretchedPanel(panel));
		
		panels.put(panel=new gdiNetworkColorDlgPanel(dialog=new PreferencesDialog(frame)), dialog);
		tabbedPane.addTab(localize("NetworkColors"), createUnstretchedPanel(panel));		
		
		panels.put(panel=new gdiAlarmColorDlgPanel(dialog=new PreferencesDialog(frame)), dialog);
		tabbedPane.addTab(localize("AlarmColors"), createUnstretchedPanel(panel));		

		panels.put(panel=new gdiStartupSettingsPanel(dialog=new PreferencesDialog(frame)), dialog);
		tabbedPane.addTab(localize("StartupSettings"), createUnstretchedPanel(panel));		

		panels.put(panel=new gdiEnvironmentSettingsPanel(dialog=new PreferencesDialog(frame)), dialog);
		tabbedPane.addTab(localize("EnvironmentSettings"), createUnstretchedPanel(panel));		

		panels.put(panel=new gdiGDASettingsPanel(dialog=new PreferencesDialog(frame)), dialog);
		tabbedPane.addTab(localize("RemoteProcessSettings"), createUnstretchedPanel(panel));		

		
		queuesPanel = new JPanel();
		queuesPanel.setLayout(new BoxLayout(queuesPanel, BoxLayout.Y_AXIS));

		panels.put(panel=new gdaQueueSettingPanel(dialog=new PreferencesDialog(frame)), dialog);
		panel.setSettingClass(GDA_ALARM_QUEUE_SETTING_);
//		tabbedPane.addTab(localize("AlarmQueueSettings"), createUnstretchedPanel(panel));		
		addQueuePanel(panel, localize("AlarmQueueSettings"));

		panels.put(panel=new gdiErrorQueueSettingPanel(dialog=new PreferencesDialog(frame)), dialog);
		panel.setSettingClass(GQM_ERROR_QUEUE_SETTING_);
//		tabbedPane.addTab(localize("ErrorQueueSettings"), panel);		
		addQueuePanel(panel, localize("ErrorQueueSettings"));

		panels.put(panel=new gdiQueueSettingPanel(dialog=new PreferencesDialog(frame)), dialog);
		panel.setSettingClass(GDA_EXPLANATION_QUEUE_SETTING_);
//		tabbedPane.addTab(localize("ExplanationQueueSettings"), panel);		
		addQueuePanel(panel, localize("ExplanationQueueSettings"));

		panels.put(panel=new gdiQueueSettingPanel(dialog=new PreferencesDialog(frame)), dialog);
		panel.setSettingClass(GQM_QUEUE_SETTING_);
//		tabbedPane.addTab(localize("MessageQueueSettings"), panel);		
		addQueuePanel(panel, localize("MessageQueueSettings"));
		
		tabbedPane.addTab(localize("QueuesSettings"), queuesPanel);
		

		panels.put(panel=new gqmGeneralSettingsDlgPanel(dialog=new PreferencesDialog(frame)), dialog);
		tabbedPane.addTab(localize("GeneralSettings"), createUnstretchedPanel(panel));		
		
		pack();
		setLocationRelativeTo(frame);
	}

	
	/**
	Sets the properties of the dialog and the attribute editor values.
    @param additionalData should contain the next attributes:<br>
    ITEM - the sequence of the items (instances of gfr-module-setting class) 
    edited by the dialog;<br>
    TITLE - the title of the dialog;<br>
    IS-MODAL - (optional, by default - false) the modality of the dialog ;<br>
    ATTRIBUTES - the sequence of attibute values (sequence of structures) 
    for edited items passed in the ITEM attribute.	
    SETTING-CLASSES - the sequence of setting class names passed in the ITEM attribute.
    Each PreferencesPanel knows item of which class it should edit. 
	*/
	public void setAdditionalData(Structure additionaldata) {
		settingClasses=(Sequence) additionaldata.getAttributeValue(SETTING_CLASSES_, null);
		super.setAdditionalData(additionaldata);
		pack();
	}
	
	
	/**
	Update controls with values of item attributes in sequence <i>avalues</i>.
	@param avalues sequence of sequences of structures with attributes described in
	superior method.<br>
	Each panel knows item of which class it should edit. It difines the index of this class
	in the {@link #settingClasses} parameter and sets attribute values from sequence at this 
	index in <code>avalues</code>.
	*/
	public void setAttributeValues(Sequence avalues) {
		PreferencesPanel panel;
		int index;
		Sequence settings = (Sequence) editedItem;
		PreferencesDialog dialog;
		for (Enumeration enum=panels.keys();enum.hasMoreElements();) {
			panel=(PreferencesPanel) enum.nextElement();
			index=settingClasses.indexOf(panel.getSettingClass());
			if (index!=-1) {
				dialog = (PreferencesDialog)panels.get(panel);
				dialog.setEditedItem(settings.get(index));
				dialog.setConnection(connection);
				dialog.setAttributeValues((Sequence)avalues.get(index));
			}
		}
	}
	
	/**
	Calls applyDialog for each PreferencesPanel.
	*/
	public boolean applyDialog() {
		
		for (Enumeration enum=panels.elements();enum.hasMoreElements();) {
			if (!((PreferencesDialog) enum.nextElement()).applyDialog())
				return false;
		}

		return true;
	}
	
	protected void addQueuePanel(JPanel panel, String title) {
		panel.setBorder(new javax.swing.border.TitledBorder(title));
		queuesPanel.add(panel);
	}

	protected JPanel createUnstretchedPanel(JPanel gdapanel) {

		JPanel panel = new JPanel(new java.awt.BorderLayout());
		panel.add(gdapanel, java.awt.BorderLayout.NORTH);
		return panel;
	}
	
    protected final static Symbol GDL_CONFIGURE_PREFERENCES_ = 
    	Symbol.intern("GDL-CONFIGURE-PREFERENCES");
    protected final static Symbol SETTING_CLASSES_ = Symbol.intern("SETTING-CLASSES");
	protected final static Symbol GDA_ALARM_QUEUE_SETTING_ = 
    	Symbol.intern("GDA-ALARM-QUEUE-SETTING");
	protected final static Symbol GQM_ERROR_QUEUE_SETTING_ = 
    	Symbol.intern("GQM-ERROR-QUEUE-SETTING");
	protected final static Symbol GQM_QUEUE_SETTING_ = 
    	Symbol.intern("GQM-QUEUE-SETTING");
	protected final static Symbol GDA_EXPLANATION_QUEUE_SETTING_ = 
    	Symbol.intern("GDA-EXPLANATION-QUEUE-SETTING");

    protected Sequence settingClasses;
	protected Hashtable panels; // key - PreferencesPanel,
								// value - PreferencesDialog which stores the panel 
								// AttributeEditor values.
	protected JPanel queuesPanel;
}