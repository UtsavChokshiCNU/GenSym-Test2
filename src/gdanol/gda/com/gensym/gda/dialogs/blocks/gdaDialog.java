
package com.gensym.gda.dialogs.blocks;

import java.awt.BorderLayout;
import java.util.MissingResourceException;

import javax.swing.JTabbedPane;
import javax.swing.JScrollPane;

import com.gensym.util.Symbol;
import com.gensym.message.Resource;
import com.gensym.gda.dialogs.ConfigureDialog;


/**the parent of all GDA Configuration Dialogs.
*/
public class gdaDialog extends ConfigureDialog{

	public gdaDialog() {}

	public gdaDialog(java.awt.Frame frame) {
		super(frame);
		dpanel=new gdaPanel(this);
		centerPane=dpanel;
		scrollPane = new JScrollPane(dpanel);
		getContentPane().add(scrollPane, BorderLayout.CENTER);
	
	}

	/** Creates the JTabbedPane with two panels: Configuration 
		and Descriptions. Configuration contains the dialog panel, 
		and Descriptions contains the descriptions panel.
	*/
	protected void createDescriptionsTab() {
		JTabbedPane tabbedPane = new JTabbedPane();
		getContentPane().remove(scrollPane);
		tabbedPane.addTab(localize(configuration), scrollPane);
		tabbedPane.addTab(localize(descriptions), new JScrollPane(new DescriptionsPanel(this)));
		getContentPane().add(tabbedPane, BorderLayout.CENTER);
	}
	
	/**Localizes lowercased Symbol from com.gensym.gda.dialogs.blocks.Messages
		resource file. If the key not found returns lowercased symbol string.
	*/
	protected String localize(Symbol attribute) {
		if (attribute==null) return "";
		try {
			return i18n.getString(attribute.toString().toLowerCase());
		} catch (MissingResourceException e) {
			return attribute.toString().toLowerCase();
		}
	}
	
	/**Localizes text from com.gensym.gda.dialogs.blocks.Messages
		resource file. If the value for the key is not found then itreturns key itself.
	*/
	protected String localize(String text) {
		try {
			return i18n.getString(text);
		} catch (MissingResourceException e) {
			return text;
		}
	}
	
	protected Resource i18n = Resource.getBundle("com.gensym.gda.dialogs.blocks.Messages");
	protected static final String configuration = "Configuration";
	protected static final String descriptions = "Descriptions";
	protected JScrollPane scrollPane;
	protected gdaPanel dpanel;
}