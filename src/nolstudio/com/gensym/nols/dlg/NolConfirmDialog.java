package com.gensym.nols.dlg;

import java.awt.*;
import java.awt.event.*;
import java.net.URL;

import javax.swing.*;
import javax.swing.border.*;

public class NolConfirmDialog extends JDialog {
	private JFrame parent;
	private JPanel controlPane;
	private JButton button1, button2, button3;
	private int result;
	private int numberOfButtons;
	private String iconLocation;
	private JTextArea labelArea;
	private JLabel label;
	private ButtonAction buttonListener;
	private Font labelFont = new Font("Dialog", Font.BOLD, 14);

	public NolConfirmDialog(JFrame dw, String title, String[] buttonStrings, String labelText, String iconLocation) {
		super(dw, title, true);
        parent = dw;	 
		result = -1;
        //Create middle section.
        JPanel workSpace = new JPanel(new BorderLayout());
 		workSpace.setBorder(new EmptyBorder(10,10,10,10));
//		System.out.println("NolConfirmDialog iconLocation = "+iconLocation);
		this.iconLocation = iconLocation;
		URL url = this.getClass().getResource(iconLocation);
		ImageIcon butIcon = new ImageIcon(url);
		label = new JLabel(butIcon);
        workSpace.add("West",label);

        JPanel labelPane = new JPanel(new GridLayout());
 		labelPane.setBorder(new EmptyBorder(10,10,0,0));
		
		labelArea = new JTextArea(labelText);
		labelArea.setFont(labelFont);
		labelArea.setLineWrap(true);
		labelArea.setWrapStyleWord(true);
		labelArea.setEditable(false);
		labelArea.setBackground(labelPane.getBackground());
		labelPane.add(labelArea);
        workSpace.add("Center",labelPane);
		controlPane = new JPanel();
        controlPane.setLayout(new FlowLayout(FlowLayout.CENTER));
		buttonListener = new ButtonAction();
		numberOfButtons = -1;
		getContentPane().setLayout(new BorderLayout());
		getContentPane().add("Center", workSpace);
		getContentPane().add("South", controlPane);
		setBounds(200,200,200,150);	 // initialize size
		setContent(title, buttonStrings, labelText, iconLocation);
	}

	/** Set the content of the dialog.*/
 	public void setContent(String title, String[] buttonStrings, String labelText, String iconLocation) {
		result = -1;
		setTitle(title);
		if(!this.iconLocation.equals(iconLocation)){
			this.iconLocation = iconLocation;
			URL url = this.getClass().getResource(iconLocation);
			ImageIcon butIcon = new ImageIcon(url);
			label.setIcon(butIcon);
		}

//		if(numberOfButtons != buttonStrings.length) {
			controlPane.removeAll();
			numberOfButtons = buttonStrings.length;
			if(numberOfButtons >= 1) {
				button1 = new JButton(buttonStrings[0]);
				button1.addActionListener(buttonListener);
				controlPane.add(button1);
			}
			if(numberOfButtons >= 2) {
				button2 = new JButton(buttonStrings[1]);
				button2.addActionListener(buttonListener);
				controlPane.add(button2);
			}
			if(numberOfButtons >= 3) {
				button3 = new JButton(buttonStrings[2]);
				button3.addActionListener(buttonListener);
				controlPane.add(button3);
			}
//		}
		// size it properly
		int maxWidth = 450;
		int length = labelText.length()*12+70;
		int extraLines = length/maxWidth;
		int height = 120+extraLines*20;
		setBounds(200,200,Math.min(length, maxWidth), height);
		// set the label text
		labelArea.setText(labelText);
		repaint(0l);
		validate();
		//pack();
	}

	public int getResult(){
		return result;
	}

	public void setFocus(int i){
		if(i>numberOfButtons){
			return;
		}
		if(i==1){
			button1.requestFocus();
		} else if(i==2){
			button2.requestFocus();
		}else if(i==3){
			button3.requestFocus();
		}
	}

	class ButtonAction extends AbstractAction {
		ButtonAction() {super("title");}

        @Override
		public void actionPerformed(ActionEvent event) {
			if(event.getSource().equals(button1)) 
				result = 1;
			else if(event.getSource().equals(button2)) 
				result = 2;
			else if(event.getSource().equals(button3)) 
				result = 3;
			NolConfirmDialog.this.setVisible(false);
		}
    }
}

