package com.gensym.gda.dialogs.preferences;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiQueue extends PreferencesDialog {
	
	public gdiQueue() {}

	public gdiQueue(java.awt.Frame frame) {
		super(frame);
		scrollPane.setViewportView(dpanel=new gdiQueuePanel(this));
	}
}