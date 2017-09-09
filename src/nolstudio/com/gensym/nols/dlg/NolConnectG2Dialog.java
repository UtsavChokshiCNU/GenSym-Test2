package com.gensym.nols.dlg;

import java.awt.*;
import java.awt.event.*;

import javax.swing.*;
import javax.swing.border.*;

import com.gensym.nols.main.*;

public class NolConnectG2Dialog extends NolDialog{
	private NolMainFrame frame;

	private boolean isOK;
	private JButton cancelButton;
	private JButton okButton;
	private JButton testButton;
	private JButton helpButton;
	private ControlAction actionListener;
	
	private JTextField listenerportField;		
	private JTextField interfacenameField;		
	private JTextField interfaceclassField;		
	private JTextField g2hostField;		
	private JTextField g2portField;		

	private String listenerport;		
	private String interfacename;		
	private String interfaceclass;		
	private String g2host;		
	private String g2port;	
	private String[] connectInfo;
 
	private static final String CANCEL_BUTTON_LABEL = "CancelButtonLabel";
    private static final String OK_BUTTON_LABEL = "OkButtonLabel";
	

    private static final String LISTENERPORT = "ConnectG2Dialog_listenerport";
    private static final String INTERFACENAME = "ConnectG2Dialog_interfacename";
    private static final String INTERFACECLASS = "ConnectG2Dialog_interfaceclass";
    private static final String G2HOST = "ConnectG2Dialog_g2host";
    private static final String G2PORT = "ConnectG2Dialog_g2port";
    private static final String CONNECTINFO = "ConnectG2Dialog_connectioninfo";
	
	public NolConnectG2Dialog(JFrame dw, String title) {

		super(dw, title, true);
        frame = (NolMainFrame)dw;	 
		actionListener = new ControlAction();	
		initDataDisplay();
		initLayout();
        setBounds(150,150,350,240);
	}

	private void initLayout(){

		cancelButton = new JButton(frame.getNolResourceString(CANCEL_BUTTON_LABEL));
		okButton = new JButton(frame.getNolResourceString(OK_BUTTON_LABEL));
		cancelButton.addActionListener(actionListener);
		okButton.addActionListener(actionListener);

		JPanel controlPane = new JPanel(new GridLayout(1,2,5,5));
		controlPane.add(cancelButton);
		controlPane.add(okButton);

		JPanel southPane = new JPanel(new BorderLayout());
		southPane.setBorder(new EmptyBorder(10,10,10,10));
		southPane.add("East",controlPane);

														 
		getContentPane().setLayout(new BorderLayout());


		JPanel cenPane = new JPanel(new GridLayout(5,2,5,5));
		cenPane.setBorder(BorderFactory.
			  createTitledBorder(frame.getNolResourceString(CONNECTINFO)+":"));

		cenPane.add(new JLabel(frame.getNolResourceString(G2HOST)+":"));
		g2hostField = new JTextField(g2host);
		cenPane.add(g2hostField);

		cenPane.add(new JLabel(frame.getNolResourceString(G2PORT)+":"));
		g2portField = new JTextField(g2port);
		cenPane.add(g2portField);

		cenPane.add(new JLabel(frame.getNolResourceString(LISTENERPORT)+":"));
		listenerportField = new JTextField(listenerport);
		cenPane.add(listenerportField);

		cenPane.add(new JLabel(frame.getNolResourceString(INTERFACECLASS)+":"));
		interfaceclassField = new JTextField(interfaceclass );
		cenPane.add(interfaceclassField);

		cenPane.add(new JLabel(frame.getNolResourceString(INTERFACENAME)+":"));
		interfacenameField = new JTextField(interfacename);
		cenPane.add(interfacenameField);
		

		getContentPane().add("South",southPane);
		getContentPane().add("Center",cenPane);
		
	}

	private void initDataDisplay(){
		g2host = "localhost";
		g2port = "1111";
		listenerport = "22044";
		interfacename = "NOLS-INTERFACE-0";
		interfaceclass = "NOLS-STUDIO-GATEWAY";
		connectInfo = new String[10];
		connectInfo[0] = "-g2host";
		connectInfo[1] = g2host;
		connectInfo[2] = "-g2port";
		connectInfo[3] = g2port;
		connectInfo[4] = "-listenerport";
		connectInfo[5] = listenerport;
		connectInfo[6] = "-interfaceclass";
		connectInfo[7] = interfaceclass;
		connectInfo[8] = "-interfacename";
		connectInfo[9] = interfacename;
	}

	public String[] getArgs(){
		connectInfo[1] = g2hostField.getText();
		connectInfo[3] = g2portField.getText();
		connectInfo[5] = listenerportField.getText();
		connectInfo[7] = interfaceclassField.getText();
		connectInfo[9] = interfacenameField.getText();
		return connectInfo;
	}

	public boolean getOkStatus(){
		return isOK;
	}
		
	class ControlAction extends AbstractAction {
		ControlAction() { super("controlAction");}

        @Override
		public void actionPerformed(ActionEvent e) {
			if(e.getSource().equals(cancelButton)) {
				isOK = false;
				setVisible(false);
			}else if(e.getSource().equals(okButton)) {
				isOK = true;
				setVisible(false);
			}
		}
	}
}

