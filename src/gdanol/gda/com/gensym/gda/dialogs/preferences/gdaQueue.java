package com.gensym.gda.dialogs.preferences;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdaQueue extends PreferencesDialog{
	
	public gdaQueue() {}

	public gdaQueue(java.awt.Frame frame) {
		super(frame);		
		scrollPane.setViewportView(dpanel=new gdaQueuePanel(this));
	}
}