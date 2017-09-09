package com.gensym.nols.dlg;

import java.awt.*;
import java.awt.event.*;
import java.net.URL;

import javax.swing.*;
import javax.swing.border.*;

public class NolURLImportDialog extends JDialog {
	private JButton yesButton, noButton, cancelButton;
	private JTextField urlInput;
	private boolean isOk;
	private ButtonAction buttonListener;
	
	public NolURLImportDialog(JFrame dw, String title, String[] buttonStrings, 
		String labelText, String iconLocation) {
		super(dw, title, true);
		isOk = false;
        //Create middle section.
        JPanel workSpace = new JPanel(new BorderLayout());
		JLabel label = new JLabel(labelText);
        label.setVerticalAlignment(label.CENTER);
		URL url = this.getClass().getResource(iconLocation);
		ImageIcon butIcon = new ImageIcon(url);
        label.setIcon(butIcon);
        label.setVerticalTextPosition(label.CENTER);
        label.setHorizontalTextPosition(label.RIGHT);
        workSpace.add("West",label);
		urlInput = new JTextField();
        workSpace.add("Center",urlInput);
		JPanel controlPane = new JPanel();
        controlPane.setLayout(new FlowLayout(FlowLayout.CENTER));
		buttonListener = new ButtonAction();

		workSpace.setBorder(new EmptyBorder(10,10,10,10));
		
		yesButton = new JButton(buttonStrings[0]);
		cancelButton = new JButton(buttonStrings[1]);
		yesButton.addActionListener(buttonListener);
		cancelButton.addActionListener(buttonListener);
		controlPane.add(yesButton);
		controlPane.add(cancelButton);

		getContentPane().setLayout(new BorderLayout());
		getContentPane().add("Center", workSpace);
		getContentPane().add("South", controlPane);

        //Initialize this dialog to its preferred size.
        pack();
	}

	public boolean getResult(){
		return this.isOk;
	}

	public void focusYes(){
		yesButton.requestFocus();
	}

	public String getURL(){
		return urlInput.getText();
	}
    
	class ButtonAction extends AbstractAction {

		ButtonAction() {
			super("title");
		}

        @Override
		public void actionPerformed(ActionEvent event) {
			if (event.getSource().equals(yesButton)) {
				isOk = true;
			}else if(event.getSource().equals(noButton) || event.getSource().equals(cancelButton)){
				isOk = false;
			}
			NolURLImportDialog.this.setVisible(false);
		}
    }
}

