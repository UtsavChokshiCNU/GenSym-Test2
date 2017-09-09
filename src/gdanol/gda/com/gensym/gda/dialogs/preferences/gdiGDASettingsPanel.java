package com.gensym.gda.dialogs.preferences;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiGDASettingsPanel extends PreferencesPanel {
	
	public gdiGDASettingsPanel(PreferencesDialog dialog) {
		super(dialog);

		settingClass=GDA_REMOTE_PROC_SETTINGS_;

		remoteProcessQueryTimeoutPeriod=new IntervalEditor();
		placeAttributeEditor(remoteProcessQueryTimeoutPeriod, 
			REMOTE_PROCESS_QUERY_TIMEOUT_PERIOD_, 0);
		
		remoteProcessRetryPeriod=new IntervalEditor();
		placeAttributeEditor(remoteProcessRetryPeriod, 
			REMOTE_PROCESS_RETRY_PERIOD_, 1);

	}

	
	protected IntervalEditor remoteProcessQueryTimeoutPeriod;
	protected IntervalEditor remoteProcessRetryPeriod;

	protected final static Symbol REMOTE_PROCESS_QUERY_TIMEOUT_PERIOD_ = 
		Symbol.intern("REMOTE-PROCESS-QUERY-TIMEOUT-PERIOD");	
	protected final static Symbol REMOTE_PROCESS_RETRY_PERIOD_ =
		Symbol.intern("REMOTE-PROCESS-RETRY-PERIOD");	
	protected final static Symbol GDA_REMOTE_PROC_SETTINGS_ = Symbol.intern("GDA-REMOTE-PROC-SETTINGS");	
}