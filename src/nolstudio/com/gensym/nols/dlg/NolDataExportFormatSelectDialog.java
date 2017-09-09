package com.gensym.nols.dlg;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.URL;
import java.util.*;

import javax.swing.text.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;
import com.gensym.nols.main.NolMainFrame;

public class NolDataExportFormatSelectDialog extends JDialog {
	private NolMainFrame frame;
	private int result;
	private int selection;
	private JButton button1;
	private ButtonAction buttonListener;

	public NolDataExportFormatSelectDialog(JFrame dw, String title) {
		super(dw, title, true);
        frame = (NolMainFrame)dw;	 
		result = -1;
		selection = 0;
        //Create middle section.
        JPanel workSpace = new JPanel(new BorderLayout());
 		workSpace.setBorder(new EmptyBorder(10,10,10,10));
		URL url = this.getClass().getResource("question.gif");
		ImageIcon butIcon = new ImageIcon(url);
		JLabel label = new JLabel(butIcon);
        workSpace.add("West",label);
		buttonListener = new ButtonAction();
        JPanel selectPane = new JPanel(new GridLayout(2,1,5,5));
 		selectPane.setBorder(new EmptyBorder(10,10,0,0));
		ButtonGroup group = new ButtonGroup();
		JRadioButton dataCheck = new JRadioButton(frame.getNolResourceString("DataSeries_ExportDataFormat"),true);
		dataCheck.setActionCommand("Data Format");
		dataCheck.addActionListener(buttonListener);
		group.add(dataCheck);
		selectPane.add(dataCheck);
		JRadioButton g2Check = new JRadioButton(frame.getNolResourceString("DataSeries_ExportG2Format"),true);
		g2Check.setActionCommand("G2 Format");
		g2Check.addActionListener(buttonListener);
		group.add(g2Check);
		selectPane.add(g2Check);
		workSpace.add("Center",selectPane);
		JPanel controlPane = new JPanel();
        controlPane.setLayout(new FlowLayout(FlowLayout.CENTER));
		button1 = new JButton(frame.getNolResourceString("OkButtonLabel"));
		button1.setActionCommand("OK");
		button1.addActionListener(buttonListener);
		controlPane.add(button1);
		JButton button = new JButton(frame.getNolResourceString("CancelButtonLabel"));
		button.setActionCommand("Cancel");
		button.addActionListener(buttonListener);
		controlPane.add(button);
		getContentPane().setLayout(new BorderLayout());
		getContentPane().add("Center", workSpace);
		getContentPane().add("South", controlPane);
	}

	public void setFocus(){
		button1.requestFocus();
	}
	public int getResult(){
		return result;
	}
	public int getSelection(){
		return selection;
	}
	
	class ButtonAction extends AbstractAction {
		ButtonAction() {super("title");}
        @Override
		public void actionPerformed(ActionEvent event) {
			String command = event.getActionCommand ();
			if(command.equals("OK")){
				result = 1;
				NolDataExportFormatSelectDialog.this.setVisible(false);
			}else if(command.equals("Cancel")){
				result = -1;
				NolDataExportFormatSelectDialog.this.setVisible(false);
			}else if(command.equals("Data Format")) {
				selection = 0;
			}else if(command.equals("G2 Format")){
				selection = 1;
			}
		}
    }
}

