package com.gensym.nols.dlg;

import java.awt.*;
import java.awt.event.*;
import java.util.*;

import javax.swing.text.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;

import com.gensym.nols.main.NolMainFrame;

public class NolJoinedLabel extends JDialog{
    protected static final String OkButtonLabel = "OkButtonLabel";
    protected static final String CancelButtonLabel = "CancelButtonLabel";
    protected static final String JOINED_LABEL_TITLE = "JoinedLabel_title";
    protected static final String LABEL_CONJUNCTION = "JoinedLabel_conjunction";
    protected static final String ADD_LABEL = "AddLabel";
    protected static final String DELETE_LABEL = "DeleteLabel";

	private JFrame parent;
	private JList singleLabelList;
	private DefaultListModel singleLabelListModel;
	private ControlAction actionListener;
	private boolean isOk;
	private JTextField joinedLabel;
	private JButton okButton;
	private Vector labels;
	private boolean noFire;
	private Vector jLabel;

    private static final Dimension hpad10 = new Dimension(10,1);
    private static final Dimension hpad20 = new Dimension(20,1);
    private static final Dimension vpad5 = new Dimension(1,5);
    private static final Dimension vpad20 = new Dimension(1,15);

	public NolJoinedLabel (JFrame dw, String title, Vector labels) {

		super(dw, title, true);
		parent = dw;
		this.labels = labels;
		jLabel = new Vector();

		JPanel workSpace = new JPanel();
		setContentPane(workSpace);    
		workSpace.setLayout(new BorderLayout());

		actionListener = new ControlAction();
		noFire = false;

		workSpace.add("Center",getLabelPane());
 		workSpace.add("East",getControlPanel());
		refreshList();
	}

	public boolean getResult(){
		return this.isOk;
	}

	public Vector getJoindLabel(){
		return jLabel;
	}

	private JPanel getLabelPane(){

		JPanel labelPane = new JPanel(new BorderLayout());
		JPanel pane = new JPanel(new GridLayout());
		joinedLabel = new JTextField();
		pane.add(joinedLabel);
		pane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
				((NolMainFrame)parent).getNolResourceString(JOINED_LABEL_TITLE) + ":", TitledBorder.LEFT , TitledBorder.TOP));
		labelPane.add("North",pane);

		labelPane.add("Center",getLabelListPane());
		return labelPane;
	}

	private JPanel getLabelListPane(){
		JPanel labelListPane = new JPanel(new BorderLayout());

		JPanel pane = new JPanel(new GridLayout());
		pane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
				((NolMainFrame)parent).getNolResourceString(JOINED_LABEL_TITLE) + ":", TitledBorder.LEFT , TitledBorder.TOP));
		singleLabelList = new JList(getSingleLabelListModel());
		singleLabelList.setBackground(Color.white);
		JScrollPane listScrollPane = new JScrollPane(singleLabelList);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		pane.add(listScrollPane);

		JPanel control = new JPanel();
		control.setBackground(getContentPane().getBackground());
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
		control.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
				"", TitledBorder.LEFT , TitledBorder.TOP));
		JPanel pane0 = new JPanel(new GridLayout(2,1,5,5));
		JButton addButton = new JButton(((NolMainFrame)parent).getNolResourceString(ADD_LABEL));
		addButton.setActionCommand("Add");
		JButton deleteButton = new JButton(((NolMainFrame)parent).getNolResourceString(DELETE_LABEL));
  		deleteButton.setActionCommand("Delete");
		pane0.add(addButton);
  		pane0.add(deleteButton);
		addButton.addActionListener(actionListener);
		deleteButton.addActionListener(actionListener);

		control.add(Box.createRigidArea(vpad20));
		control.add(pane0);
		control.add(Box.createRigidArea(new Dimension(1,100)));
		control.add(Box.createVerticalGlue());

		labelListPane.add("Center",pane);
		labelListPane.add("East",control);

		return labelListPane; 
	}

	private JPanel getControlPanel(){
		JPanel control = new JPanel();
		control.setBackground(getContentPane().getBackground());
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
		control.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
				"", TitledBorder.LEFT , TitledBorder.TOP));
		JPanel pane0 = new JPanel(new GridLayout(2,1,5,5));
		okButton = new JButton(((NolMainFrame)parent).getNolResourceString(OkButtonLabel));
		okButton.setActionCommand("OK");
		okButton.setEnabled(false);
		JButton cancelButton = new JButton(((NolMainFrame)parent).getNolResourceString(CancelButtonLabel));
		cancelButton.setActionCommand("Cancel");
  		pane0.add(okButton);
  		pane0.add(cancelButton);
		okButton.addActionListener(actionListener);
		cancelButton.addActionListener(actionListener);

		control.add(Box.createRigidArea(vpad20));
		control.add(pane0);
		control.add(Box.createRigidArea(new Dimension(1,150)));
		control.add(Box.createVerticalGlue());
		return control;
	}

	private DefaultListModel getSingleLabelListModel() {
		if (singleLabelListModel == null) {
			singleLabelListModel = new DefaultListModel();
		}	
		return singleLabelListModel;
	}	

 	private void refreshList() {
		getSingleLabelListModel().removeAllElements();
		int c = labels.size();
		for(int i=0;i<c;i++)
			getSingleLabelListModel().addElement(labels.elementAt(i));
	}

	private void refreshJoinedLabel(){
		int c = jLabel.size();
		if(c>0){
			String n = "";
			for(int i=0;i<c-1;i++)
				n = n+jLabel.elementAt(i).toString() + " " + ((NolMainFrame)parent).getNolResourceString(LABEL_CONJUNCTION) + " ";	
			n = n+jLabel.elementAt(c-1).toString();
			joinedLabel.setText(n);
		}else{
			joinedLabel.setText("");
		}
		if(c<2){
			okButton.setEnabled(false);
		}else{
			okButton.setEnabled(true);
		}
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
				NolJoinedLabel.this.dispose();
			}else if(command.equals("Cancel")){
				isOk = false;
				NolJoinedLabel.this.dispose();
			}else if(command.equals("Add")){
				Object lab = singleLabelList.getSelectedValue();	
				if(!jLabel.contains(lab)){
					jLabel.addElement(lab);
					refreshJoinedLabel();
				}
			}else if(command.equals("Delete")){
				int c = jLabel.size();
				if(c>0){
					jLabel.removeElementAt(c-1);
					refreshJoinedLabel();
				}
			}
		}
    }

}

