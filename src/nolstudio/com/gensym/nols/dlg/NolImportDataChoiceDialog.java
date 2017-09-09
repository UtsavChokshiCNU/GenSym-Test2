package com.gensym.nols.dlg;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.*;

import javax.swing.text.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;

import com.gensym.nols.main.*;

public class NolImportDataChoiceDialog extends JDialog {
    private static final String OK_BUTTON_LABEL = "OkButtonLabel";
    private static final String CANCEL_BUTTON_LABEL = "CancelButtonLabel";

	private JFrame parent;
	protected JTextArea infoText;

	private DefaultListModel choiceListModel;
	protected NolList choiceList;
	private JButton okButton, cancelButton;
	private boolean isOk;
	private boolean isMultiSelection;

	private String choiceString;
	private Vector choiceVector;

	private Vector selectedItems;
	private MainAction mainListener;
	private JPanel choicePane;
	private JLabel choiceLabel;
	private boolean nofire = false;
	private boolean choiceStatusFire = false;

	public NolImportDataChoiceDialog(JFrame dw, String title, String choiceString, 
			Vector choiceVector, boolean isMultiSelection) {

		super(dw, title, true);
        parent = dw;
		mainListener = new MainAction();

		this.choiceString = choiceString;
		this.choiceVector = choiceVector;
		this.isMultiSelection = isMultiSelection;
		isOk = false;
		initializeLayout();
		refreshDialog();
	}
	
	public void setContent(String title, String choiceString, 
			Vector choiceVector, boolean isMultiSelection) {
		setTitle(title);
		this.choiceVector = choiceVector;
		this.choiceString = choiceString;
		this.isMultiSelection = isMultiSelection;
		isOk = false;

		if(isMultiSelection) choiceList.setSelectionMode(ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);
		else choiceList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		// update labels
		choiceLabel.setText(choiceString);
		refreshDialog();
		pack();
	}


	private void initializeLayout(){ 
		// create and add the label for variables
		choiceListModel = new DefaultListModel();
 		choiceList = new NolList(choiceListModel);
		choiceList.setBackground(Color.white);
		choiceList.addMouseListener((MouseListener)mainListener);
		JScrollPane listScrollPane = new JScrollPane(choiceList);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		
		// Create the choice combo boxes to be placed at the top of the dialog
		choicePane = new JPanel(new GridLayout(1,1,5,5));
		// create and add the label for variable
		choiceLabel = new JLabel();
 		choicePane.add(choiceLabel);

		// now put it all together
		JPanel cenPane = new JPanel(new BorderLayout());
 		cenPane.setBorder(new EmptyBorder(10, 10, 10, 10));
		cenPane.add("North", choicePane);
		cenPane.add("Center", listScrollPane);
		cenPane.add("South", getInfoPane());
		getContentPane().setLayout(new BorderLayout());
		getContentPane().add("Center", cenPane);
		getContentPane().add("East", getControlPane());
        // Initialize this dialog to its preferred size.
        pack();
	}

	private JPanel getInfoPane(){
		JPanel infoPane = new JPanel();
		infoPane.setLayout(new GridLayout());
		infoText = new JTextArea();
		infoText.setBackground(infoPane.getBackground());
		infoPane.add(infoText);
		return infoPane;
	}

	private JPanel getControlPane(){
		JPanel control = new JPanel();
		control.setBackground(getContentPane().getBackground());
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
		control.setBorder(new EmptyBorder(10, 10, 10, 10));

		JPanel pane0 = new JPanel(new GridLayout(5,1,5,5));
		okButton = new JButton(((NolMainFrame)parent).getNolResourceString(OK_BUTTON_LABEL));
		okButton.setActionCommand("OK");
		cancelButton = new JButton(((NolMainFrame)parent).getNolResourceString(CANCEL_BUTTON_LABEL));
		cancelButton.setActionCommand("Cancel");
		okButton.addActionListener(mainListener);
		cancelButton.addActionListener(mainListener);
		pane0.add(okButton);
		pane0.add(cancelButton);
		control.add(Box.createRigidArea(NolMainFrame.vpad15));
		control.add(pane0);
		control.add(Box.createRigidArea(NolMainFrame.vpad500));
		control.add(Box.createVerticalGlue());
		return control;
	}

	public void refreshDialog() {
		nofire  = true;
		// clean up content from maybe last time...
		choiceListModel.removeAllElements();
		// now fill the variable dialog with variables
		choiceList.addObjects(choiceVector);
		if(choiceVector.size()>0) choiceList.setSelectedIndex(0);
		nofire = false;
	}

	public boolean getResult(){
		return isOk;
	}

	public Vector getSelectedItems() {
		return selectedItems;
	}

	public Object getSelectedItem() {
		if(selectedItems.size() == 0) return null;
		return selectedItems.elementAt(0);
	}

	public int getSelectedIndex() {
		return choiceList.getSelectedIndex();
	}

	private boolean okFired() {
		if(isMultiSelection){
			int[] selectedIndeces = choiceList.getSelectedIndices();
			int numberOfSelectedItems = selectedIndeces.length;
			selectedItems = new Vector(numberOfSelectedItems);
			if(numberOfSelectedItems == 0) return false;
			for(int z = 0; z < numberOfSelectedItems; z++) {
				selectedItems.addElement(choiceVector.elementAt(selectedIndeces[z]));
			}
		}else{
			int selectedIndex = choiceList.getSelectedIndex();
			if(selectedIndex<0) return false;
			selectedItems = new Vector(1);
 			selectedItems.addElement(choiceVector.elementAt(selectedIndex));
		}
		return true;
	}


    class MainAction extends AbstractAction implements MouseListener{
		MainAction() {	super("title");}
        @Override
		public void actionPerformed(ActionEvent event) {
			if(nofire) return;
			if (event.getSource() == okButton) {
				isOk = okFired();
				NolImportDataChoiceDialog.this.setVisible(false);
			} else if(event.getSource() == cancelButton){
				isOk = false;
				NolImportDataChoiceDialog.this.setVisible(false);
			}
		}
		@Override
		public void mousePressed(MouseEvent m) {}
		@Override
		public void mouseEntered(MouseEvent m) {}
		@Override
		public void mouseExited(MouseEvent m) {}
		@Override
		public void mouseReleased(MouseEvent m) {}
		public void mouseDragged(MouseEvent m) {}
		public void mouseMoved(MouseEvent m) {}
		@Override
		public void mouseClicked(MouseEvent m) {
			int clickCount =  m.getClickCount();
			if(clickCount != 2) return;
			isOk = okFired();
			NolImportDataChoiceDialog.this.setVisible(false);
		}
    }
}

