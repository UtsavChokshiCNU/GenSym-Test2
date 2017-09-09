package com.gensym.nols.dlg;

import java.awt.*;
import java.awt.event.*;

import javax.swing.*;
import javax.swing.border.*;

import com.gensym.nols.main.NolMainFrame;

public class NolTextInput extends JDialog {
	protected static final String OK_BUTTON_LABEL = "OkButtonLabel";
    protected static final String CANCEL_BUTTON_LABEL = "CancelButtonLabel";

	private JFrame parent;
	private JTextField inputField;
	private boolean isOk;
	private ControlAction actionListener;

	public NolTextInput (JFrame dw, String title, String labelText) {

		super(dw, title, true);
 		parent = dw;
       //Create middle section.
        JPanel workSpace = new JPanel(new BorderLayout());
		JLabel label = new JLabel(labelText);
        label.setVerticalAlignment(label.CENTER);
        label.setVerticalTextPosition(label.CENTER);
        label.setHorizontalTextPosition(label.RIGHT);
        workSpace.add("West",label);
		inputField = new JTextField();
        workSpace.add("Center",inputField);
		JPanel controlPane = new JPanel();
        controlPane.setLayout(new FlowLayout(FlowLayout.CENTER));
		actionListener = new ControlAction();

		workSpace.setBorder(new EmptyBorder(10,10,10,10));
		
		JButton but = new JButton(((NolMainFrame)parent).getNolResourceString(OK_BUTTON_LABEL));
		but.setActionCommand("OK");
		but.addActionListener(actionListener);
		controlPane.add(but);
		but = new JButton(((NolMainFrame)parent).getNolResourceString(CANCEL_BUTTON_LABEL));
		but.setActionCommand("Cancel");
		but.addActionListener(actionListener);
		controlPane.add(but);

		getContentPane().setLayout(new BorderLayout());
		getContentPane().add("Center", workSpace);
		getContentPane().add("South", controlPane);

        //Initialize this dialog to its preferred size.
        pack();

	}

	public boolean getResult(){
		return isOk;
	}

	public String getText(){
		return inputField.getText();
	}

	public void setText(String str){
		inputField.setText(str);
	}

	public void setFocus(){
		inputField.requestFocus();
	}

    /**
     * Control action implementation
     */
    class ControlAction extends AbstractAction {

		ControlAction() {
			super("controlAction");
		}

        @Override
		public void actionPerformed(ActionEvent e) {
				
			String command = e.getActionCommand();
			if(command.equals("OK")){
				isOk = true;
				NolTextInput.this.dispose();
			}else if(command.equals("Cancel")){
				isOk = false;
				NolTextInput.this.dispose();
			}else if(e.getSource().equals(inputField)){
				String n = inputField.getText();
				if(n.equals("")) {
					return;
				}
				isOk = true;
				NolTextInput.this.dispose();
			}
		}
    }

}

