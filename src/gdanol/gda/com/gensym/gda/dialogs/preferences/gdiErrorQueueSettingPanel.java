package com.gensym.gda.dialogs.preferences;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JButton;
import javax.swing.JPanel;


import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.gda.util.SwingWorker;
import com.gensym.dlgevent.ObjectUpdateEvent;

public class gdiErrorQueueSettingPanel extends gdiQueueSettingPanel {
	
	public gdiErrorQueueSettingPanel(PreferencesDialog dialog) {
		super(dialog);
		
		showTracebacks=new CheckBoxEditor();
		placeAttributeEditor(showTracebacks, GQM_SHOW_TRACEBACKS_, 1);

	}

	
	protected CheckBoxEditor showTracebacks;
	
	protected final static Symbol GQM_SHOW_TRACEBACKS_ = Symbol.intern("GQM-SHOW-TRACEBACKS");	
}