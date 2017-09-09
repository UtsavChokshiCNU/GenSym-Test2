package com.gensym.gda.dialogs.preferences;

import javax.swing.JScrollPane;

	public class gdiTabularViewTemplate extends PreferencesDialog {
	
	public gdiTabularViewTemplate() {}

	public gdiTabularViewTemplate(java.awt.Frame frame) {
		super(frame);		
		getContentPane().remove(scrollPane);
		scrollPane = new JScrollPane(new gdiTabularViewTemplatePanel(this));
		getContentPane().add(scrollPane);
		pack();
		setLocationRelativeTo(frame);
	}

}