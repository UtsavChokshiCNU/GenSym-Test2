
package com.gensym.gda.dialogs.blocks;

import javax.swing.JTabbedPane;
import com.gensym.util.Symbol;
import com.gensym.message.Resource;


/**the parent of GDA Configuration Dialogs.
*/
public class BlocksDialog extends com.gensym.gda.dialogs.gdaDialog {

	public BlocksDialog() {}

	public BlocksDialog(java.awt.Frame frame) {
		super(frame);
		i18n = Resource.getBundle("com.gensym.gda.dialogs.blocks.Messages");
		
		centerPane=dpanel=new BlocksPanel(this);
		scrollPane.setViewportView(dpanel);
	}

	/** Creates the JTabbedPane with two panels: Configuration 
		and Descriptions. Configuration contains the dialog panel, 
		and Descriptions contains the descriptions panel.
	*/
	protected void createDescriptionsTab() {
		JTabbedPane tabbedPane = new JTabbedPane();
		tabbedPane.addTab(localize(configuration), dpanel);
		tabbedPane.addTab(localize(descriptions), new DescriptionsPanel(this));
		scrollPane.setViewportView(tabbedPane);

/*		JTabbedPane tabbedPane = new JTabbedPane();
		getContentPane().remove(scrollPane);
		tabbedPane.addTab(localize(configuration), scrollPane);
		tabbedPane.addTab(localize(descriptions), new JScrollPane(new DescriptionsPanel(this)));
		getContentPane().add(tabbedPane, BorderLayout.CENTER);
*/		
	}
	
	protected static final String configuration = "Configuration";
	protected static final String descriptions = "Descriptions";
	protected BlocksPanel dpanel;
}