	
package com.gensym.gda.dialogs.preferences;


/**
*/
public class NoBoundsPreferencesPanel extends PreferencesPanel {


	public NoBoundsPreferencesPanel(PreferencesDialog d) {
    	super(d);
    	minimumPanelWidth=0;
    	setBorder(null);
	}
		
	protected void setDefaultConstraints() {
		super.setDefaultConstraints();
	 	gridBagConstraints.insets = noInsets;
	}

	public void addButton(javax.swing.JButton button, int gridx) {
		gridBagConstraints.gridx= gridx;
		gridBagConstraints.fill=gridBagConstraints.NONE;
		gridBagConstraints.weightx=0;
		gridBagConstraints.weighty=0;
		gridBagConstraints.insets=buttonInsets;
		gridBagLayout.setConstraints(button, gridBagConstraints);
		add(button);
	}
	
	protected final static java.awt.Insets buttonInsets=new java.awt.Insets(0,10,0,0);
}