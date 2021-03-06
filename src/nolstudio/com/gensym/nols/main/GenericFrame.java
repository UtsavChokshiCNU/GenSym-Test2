package com.gensym.nols.main;


import java.awt.*;
import java.awt.event.*;
import java.net.*;

import javax.swing.*;
import javax.swing.border.*;


/**
 * a class to display error manager messages to the user
 *
 * @version	1.0 December 14, 1998
 * @author brian o bush, gearhead
**/
public class GenericFrame extends JFrame {

	private JTextPane Textpane;
	private JPanel controlPane;
	private JTextArea errText;
	private JButton confirmButton;
	private ButtonAction buttonListener;
	private boolean confirmed;

	// Set up constants for width and height of frame
	static final int WIDTH = 450;
	static final int HEIGHT = 250;

	// Add a constructor for our frame.
	public GenericFrame(String title) {
		// Set the title of the frame
		super(title);

		URL url = this.getClass().getResource("framelogo.gif");
		ImageIcon gensymLogo = new ImageIcon(url);
		setIconImage(gensymLogo.getImage());

		Container c = getContentPane();
        c.add("Center", getConsolePanel());

		controlPane = new JPanel();
		confirmButton = new JButton("OK");
		confirmButton.setActionCommand("OK");
		buttonListener = new ButtonAction();
		confirmButton.addActionListener(buttonListener);
		controlPane.add(confirmButton,BorderLayout.CENTER);
		c.add("South", controlPane);

		confirmed = false;
	}

	private JScrollPane getTextArea(){
		errText = new JTextArea();
		errText.setEditable(false);
		errText.setLineWrap(true);
		errText.setWrapStyleWord(true);
		JScrollPane errScrollPane = new JScrollPane(errText) {
				@Override
				public Dimension getPreferredSize() { return new Dimension(300,200); }
			};
		errScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		return errScrollPane;
	}

	private JPanel getConsolePanel(){
		JPanel pane = new JPanel(new GridLayout());
		pane.add(getTextArea());
		pane.setBorder(new EmptyBorder(10,10,10,10));
		return pane;
	}

	public void setMessage(String s) {
		errText.append(s);
	}

	public void clearMessage() {
		errText.setText("");
	}

	class ButtonAction extends AbstractAction {

		ButtonAction() {
			super("title");
		}

        @Override
		public void actionPerformed(ActionEvent event) {
			if(event.getSource().equals(confirmButton)){
				confirmed = true;
				dispose();
			}
		}
    }

}