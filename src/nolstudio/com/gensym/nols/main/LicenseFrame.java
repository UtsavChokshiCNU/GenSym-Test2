package com.gensym.nols.main;


import java.awt.*;
import java.awt.event.*;

import javax.swing.*;
import javax.swing.border.*;


/**
 * a class to display license messages to the user
 *
 * @version	4,9, 1999
 * @author gchen
**/
public class LicenseFrame extends JDialog {

	private JTextPane Textpane;
	private JPanel controlPane;
	private JTextArea licenseText;
	private JButton acceptButton;
	private JButton concelButton;
	private ButtonAction buttonListener;
	private boolean confirmed;

	// Set up constants for width and height of frame
	static final int WIDTH = 450;
	static final int HEIGHT = 250;

	// Add a constructor for our frame.
	public LicenseFrame(Frame frame, String title) {
		// Set the title of the frame
		super(frame,title,true);

/*		URL url = this.getClass().getResource("framelogo.gif");
		ImageIcon gensymLogo = new ImageIcon(url);
		setIconImage(gensymLogo.getImage());
  */
		buttonListener = new ButtonAction();
		confirmed = false;
        getContentPane().add("Center", getConsolePanel());
        getContentPane().add("South", getControlPanel());

	}

	private JPanel getConsolePanel(){
		JPanel pane = new JPanel(new GridLayout());
		pane.setBorder(new EmptyBorder(10,10,10,10));

		licenseText = new JTextArea();
		licenseText.setEditable(false);
		licenseText.setLineWrap(true);
		licenseText.setWrapStyleWord(true);
		JScrollPane scrollPane = new JScrollPane(licenseText) {
				@Override
				public Dimension getPreferredSize() { return new Dimension(300,200); }
		};
		scrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		pane.add(scrollPane);
		return pane;
	}

	private JPanel getControlPanel(){
		JPanel controlPanel = new JPanel();
		acceptButton = new JButton("Accept");
		acceptButton.addActionListener(buttonListener);
		controlPanel.add(acceptButton);
		concelButton = new JButton("Do Not Accept");
		concelButton.addActionListener(buttonListener);
		controlPanel.add(concelButton);
		return controlPanel;
	}

	public void setMessage(String s) {
		licenseText.setText(s);
	}

	public boolean getConfirmed(){
		return confirmed;
	}

	class ButtonAction extends AbstractAction {
		ButtonAction() {super("title");	}
        @Override
		public void actionPerformed(ActionEvent event) {
			if(event.getSource().equals(acceptButton)){
				confirmed = true;
				setVisible(false);
			}else if(event.getSource().equals(concelButton)){
				confirmed = false;
				setVisible(false);
			}
		}
    }

}