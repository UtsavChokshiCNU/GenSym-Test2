package com.gensym.gda.dialogs.preferences;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JButton;
import javax.swing.JPanel;


import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdaQueueSettingPanel extends gdiQueueSettingPanel {
	
	public gdaQueueSettingPanel(PreferencesDialog dialog) {
		super(dialog);

		gdaAlarmLogFormatter = new TextFieldEditor();
		placeAttributeEditor(gdaAlarmLogFormatter, GDA_ALARM_LOG_FORMATTER_,
			symbolFieldType, 1);
			
		gdaHistoryLimit=new SpinEditor(Integer.MIN_VALUE, Integer.MAX_VALUE, 1);
		placeAttributeEditor(gdaHistoryLimit, GDA_HISTORY_LIMIT_,
			integerFieldType, 2);
			
		gdaReuseEntry=new CheckBoxEditor();
		placeAttributeEditor(gdaReuseEntry, GDA_REUSE_ENTRY_, 3);
	}
	
	protected TextFieldEditor gdaAlarmLogFormatter;
	protected SpinEditor gdaHistoryLimit;
	protected CheckBoxEditor gdaReuseEntry;
	
	protected final static Symbol GDA_ALARM_LOG_FORMATTER_ = Symbol.intern("GDA-ALARM-LOG-FORMATTER");	
	protected final static Symbol GDA_HISTORY_LIMIT_ = Symbol.intern("GDA-HISTORY-LIMIT");	
	protected final static Symbol GDA_REUSE_ENTRY_ = Symbol.intern("GDA-REUSE-ENTRY");	

}