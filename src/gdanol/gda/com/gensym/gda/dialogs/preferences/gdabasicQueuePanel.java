package com.gensym.gda.dialogs.preferences;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JButton;
import javax.swing.JPanel;


import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.gda.controls.*;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.dlgevent.ObjectUpdateEvent;


public class gdabasicQueuePanel extends PreferencesPanel implements ActionListener {
	
	public gdabasicQueuePanel(PreferencesDialog dialog) {
		super(dialog);

		gqmEntryClass=new ComboBoxEditor();
		placeAttributeEditor(gqmEntryClass, GQM_ENTRY_CLASS_, symbolFieldType, 0);
		
		gqmEntryLimit=new SpinEditor(Integer.MIN_VALUE, Integer.MAX_VALUE, 1);
		placeAttributeEditor(gqmEntryLimit, GQM_ENTRY_LIMIT_, integerFieldType, 2);
		
		gqsViewTemplateOrAccessTable=new ComboBoxEditor();
		placeAttributeEditor(gqsViewTemplateOrAccessTable,
			GQS_VIEW_TEMPLATE_OR_ACCESS_TABLE_, symbolFieldType, 4);

		managerPanel = new NoBoundsPreferencesPanel(dialog);
		gqsLoggingManager = new LoggingManagerEditor();
		managerPanel.placeAttributeEditor(gqsLoggingManager, "",
			GQS_LOGGING_MANAGER_, symbolFieldType, 0);
		configureManager=new JButton(localize("ConfigureLoggingManagerButtonLabel"));
		configureManager.addActionListener(this);
		managerPanel.addButton(configureManager,3);
		addPanel(managerPanel, localize(GQS_LOGGING_MANAGER_.toString().toLowerCase()),5);

		gqmDefaultPriority=new SpinEditor(Integer.MIN_VALUE, Integer.MAX_VALUE, 1);
		placeAttributeEditor(gqmDefaultPriority, GQM_DEFAULT_PRIORITY_, 
			integerFieldType, 6);
		

		gqmUpdateLatency=new SpinEditor();
		gqmUpdateLatency.setMinValue(1);
		placeAttributeEditor(gqmUpdateLatency, GQS_UPDATE_LATENCY_, 7);
		
		gqmDisplayMessages=new CheckBoxEditor();
		placeAttributeEditor(gqmDisplayMessages, GQM_DISPLAY_MESSAGES_, integerFieldType, 8);

		gqmBeepForNewEntry=new CheckBoxEditor();
		placeAttributeEditor(gqmBeepForNewEntry, GQM_BEEP_FOR_NEW_ENTRY_, integerFieldType, 9);

		gqmConfirmDeletions=new CheckBoxEditor();
		placeAttributeEditor(gqmConfirmDeletions, GQM_CONFIRM_DELETIONS_, integerFieldType, 10);
}

	public void actionPerformed(ActionEvent e) {
		if (e.getSource()==configureManager) {
			try {
				dialog.getConnection().callRPC(GDL_LAUNCH_LOGGING_MANAGER_DIALOG_,
					new Object[]{selectedLoggingManager, dialog.getConnection().retrieveSession()});
			} catch (G2AccessException error) {Trace.exception(error);}
		}
	}

	class LoggingManagerEditor extends ComboBoxEditor {
		public void objectUpdated(ObjectUpdateEvent event) {
			super.objectUpdated(event);
			Structure values = (Structure) event.getUpdatedObject();
			selectedLoggingManager = (Symbol)values.getAttributeValue(getAttribute(), null);			
		}
		
		public void fireObjectChange(Object object) {
			selectedLoggingManager=(Symbol) object;
			super.fireObjectChange(object);
		}
	}
		

	protected Symbol selectedLoggingManager;
	protected NoBoundsPreferencesPanel managerPanel;

	protected ComboBoxEditor gqmEntryClass;
	protected SpinEditor gqmEntryLimit;
	protected SpinEditor gqmEntryLifetime;
	protected ComboBoxEditor gqsViewTemplateOrAccessTable;
	protected LoggingManagerEditor gqsLoggingManager;
	protected SpinEditor gqmUpdateLatency;
	protected CheckBoxEditor gqmDisplayMessages;
	protected CheckBoxEditor gqmBeepForNewEntry;
	protected CheckBoxEditor gqmConfirmDeletions;
	protected JButton configureManager;
	protected SpinEditor gqmDefaultPriority;
	
	protected final static Symbol GQM_ENTRY_CLASS_ = Symbol.intern("GQM-ENTRY-CLASS");	
	protected final static Symbol GQM_ENTRY_LIMIT_ = Symbol.intern("GQM-ENTRY-LIMIT");	
	protected final static Symbol GQS_VIEW_TEMPLATE_OR_ACCESS_TABLE_ = 
		Symbol.intern("GQS-VIEW-TEMPLATE-OR-ACCESS-TABLE");
	protected final static Symbol GQS_LOGGING_MANAGER_ = Symbol.intern("GQS-LOGGING-MANAGER");	
	protected final static Symbol GQS_UPDATE_LATENCY_ = Symbol.intern("GQS-UPDATE-LATENCY");
	protected final static Symbol GQM_DISPLAY_MESSAGES_ = Symbol.intern("GQM-DISPLAY-MESSAGES");	
	protected final static Symbol GQM_BEEP_FOR_NEW_ENTRY_ = Symbol.intern("GQM-BEEP-FOR-NEW-ENTRY");
	protected final static Symbol GQM_CONFIRM_DELETIONS_ = Symbol.intern("GQM-CONFIRM-DELETIONS");
	protected final static Symbol GQM_DEFAULT_PRIORITY_ = Symbol.intern("GQM-DEFAULT-PRIORITY");

	protected final static Symbol GDL_LAUNCH_LOGGING_MANAGER_DIALOG_ = 
		Symbol.intern("GDL-LAUNCH-LOGGING-MANAGER-DIALOG");
	
	
}