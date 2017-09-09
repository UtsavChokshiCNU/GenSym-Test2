package com.gensym.gda.dialogs.preferences;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiQueuePanel extends gdabasicQueuePanel {
	
	public gdiQueuePanel(PreferencesDialog dialog) {
		super(dialog);
		gqmEntryLifetime = new SpinEditor();
		gqmEntryLifetime.setMinValue(0);
		placeAttributeEditor(gqmEntryLifetime, GQM_ENTRY_LIFETIME_, 3);			
	}

	protected SpinEditor gqmEntryLifetime;
	
	protected final static Symbol GQM_ENTRY_LIFETIME_
		= Symbol.intern("GQM-ENTRY-LIFETIME");		

	
	
}