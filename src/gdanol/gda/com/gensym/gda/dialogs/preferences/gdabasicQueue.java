package com.gensym.gda.dialogs.preferences;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;
import javax.swing.JScrollPane;

	public class gdabasicQueue extends PreferencesDialog {
	
	public gdabasicQueue() {}

	public gdabasicQueue(java.awt.Frame frame) {
		super(frame);		
		scrollPane.setViewportView(dpanel=new gdabasicQueuePanel(this));

//		getContentPane().remove(scrollPane);
//		scrollPane = new JScrollPane(dpanel=new gdabasicQueuePanel(this));
//		getContentPane().add(scrollPane);
	}
}