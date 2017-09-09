package com.gensym.nols.dlg;
import java.awt.*;
import java.awt.event.*;
import java.util.*;

import javax.swing.*;

import com.gensym.nols.main.*;

public class NolTableDialog  extends JDialog{
	private JFrame parent;
    private JButton okButton;
    private JButton cancelButton;
	private boolean isOk;
	private Vector contents;
	private Vector inputs;
	private Vector inputFields;
	private ControlAction actionListener;

    private static final String OK_BUTTON_LABEL = "OkButtonLabel";
    private static final String CANCEL_BUTTON_LABEL = "CancelButtonLabel";

	public NolTableDialog (JFrame dw, String title, String labelText,
		Vector contents) {
		super(dw, title, true);
		parent = dw;
		this.contents = contents;
		this.inputs = new Vector(contents.size());
		this.inputFields = new Vector(contents.size());
		JPanel workSpace = new JPanel();
		setContentPane(workSpace);    
		workSpace.setLayout(new BorderLayout());
		actionListener = new ControlAction();

		workSpace.add("North",getLabelPanel(labelText));
		workSpace.add("Center",getTabelPanel());
		workSpace.add("South",getControlPanel());
	}

	public NolTableDialog (JFrame dw, String title, String labelText,
		Vector contents, Vector defaultInputs) {
		this(dw, title, labelText,contents);
		this.inputs.removeAllElements();
		int n = defaultInputs.size();
		for(int i=0;i<n;i++)
			inputs.addElement(defaultInputs.elementAt(i));
		refreshInputFields();
	}
	public boolean getResult(){
		return this.isOk;
	}

	public Vector getInputs(){
		return this.inputs;
	}

	private void refreshInputFields(){ 
		int n = inputs.size();
		for(int i=0;i<n;i++){
			String content = inputs.elementAt(i).toString();
			((JTextField)inputFields.elementAt(i)).setText(content);
		}
	}

	private JPanel getLabelPanel(String labelText){
		JPanel labelPane = new JPanel();
//		labelPane.setBackground(Color.darkGray);
//		JLabel label1 = new JLabel(labelText);
//		label1.setForeground(Color.white);
//		labelPane.add(label1);
		labelPane.add(new JLabel(labelText));
		return labelPane;
	}

	private JPanel getTabelPanel(){

		JPanel tablePane = new JPanel();
		int cl = contents.size();
		tablePane.setLayout(new GridLayout(cl,2));
		for(int i=0;i<cl;i++){
			JPanel attriPane = new JPanel();
//			attriPane.setBorder(BorderFactory.createLineBorder(Color.black));
			attriPane.setBorder(BorderFactory.createBevelBorder(1));
			attriPane.setBackground(Color.white);
			attriPane.add(new JLabel(contents.elementAt(i).toString()));
			tablePane.add(attriPane);
			JTextField inputField = new JTextField();
			tablePane.add(inputField);
			inputFields.addElement(inputField);
		}
		return tablePane;
	}

	private JPanel getControlPanel(){
		JPanel control = new JPanel();
		control.setBackground(getContentPane().getBackground());
		control.setLayout(new FlowLayout(FlowLayout.CENTER));
		okButton = new JButton(((NolMainFrame)parent).getNolResourceString(OK_BUTTON_LABEL));
		cancelButton = new JButton(((NolMainFrame)parent).getNolResourceString(CANCEL_BUTTON_LABEL));
		okButton.addActionListener(actionListener);
		cancelButton.addActionListener(actionListener);
		control.add(okButton);
		control.add(cancelButton);
		return control;
	}
    /**
     * Export action implementation
     */
    class ControlAction extends AbstractAction {

		ControlAction() {
			super("controlAction");
		}

        @Override
		public void actionPerformed(ActionEvent e) {
			if(e.getSource().equals(okButton)){
				int ic = inputFields.size();
				inputs.removeAllElements();
				for(int i=0;i<ic;i++)
					inputs.addElement(((JTextField)inputFields.elementAt(i)).getText());
				isOk = true;
				NolTableDialog.this.setVisible(false);
				NolTableDialog.this.dispose();
			}else if(e.getSource().equals(cancelButton)){	
				isOk = false;
				NolTableDialog.this.setVisible(false);
				NolTableDialog.this.dispose();
			}
		}
    }

}

