package com.gensym.nols.dlg;

import java.awt.*;
import java.awt.event.*;
import java.util.*;

import javax.swing.*;
import javax.swing.border.*;

import com.gensym.nols.main.*;
 
public class NolXYSingleChoiceDialog extends JDialog {
    protected static final String OK_BUTTON_LABEL = "OkButtonLabel";
    protected static final String CANCEL_BUTTON_LABEL = "CancelButtonLabel";

	protected JTextArea infoText;

	private DefaultListModel choice1ListModel;
	private DefaultListModel choice2ListModel;
	protected NolList choice1List;
	protected NolList choice2List;
	private JButton okButton, cancelButton;
	private boolean isOk;
	private boolean isMultiSelection;

	private String choiceString;
	private Vector choice1Vector;
	private Vector choice2Vector;

	private Vector selectedItemsX;
	private Vector selectedItemsY;
	private MainAction mainListener;
	private JLabel choice1Label;
	private JLabel choice2Label;
	private boolean nofire = false;
	private boolean choiceStatusFire = false;
	private JFrame frame;

	public NolXYSingleChoiceDialog(JFrame dw, String title, String choiceString, 
			Vector choice1Vector, Vector choice2Vector, boolean isMultiSelection) 
	{

		super(dw, title, true);
        frame = dw;
		mainListener = new MainAction();

		this.choiceString = choiceString;
		this.choice1Vector = choice1Vector;
		this.choice2Vector = choice2Vector;
		this.isMultiSelection = isMultiSelection;
		isOk = false;
		initializeLayout();
		refreshDialog();
	}
	
	public void setContent(String title, String choiceString, 
			Vector choice1Vector, Vector choice2Vector, boolean isMultiSelection) {

		setTitle(title);

		this.choiceString = choiceString;
		this.choice1Vector = choice1Vector;
		this.choice2Vector = choice2Vector;
		this.isMultiSelection = isMultiSelection;
		isOk = false;

		if(this.isMultiSelection){
			choice1List.setSelectionMode(ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);
			choice2List.setSelectionMode(ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);
		}else	 {
			choice1List.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
			choice2List.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		}
		// update lables
		choice1Label.setText(choiceString);
		choice2Label.setText(choiceString);
		refreshDialog();

		pack();
	}


	private void initializeLayout(){ 
		// create and add the label for variables
		choice1ListModel = new DefaultListModel();
 		choice1List = new NolList(choice1ListModel);
		choice1List.setBackground(Color.white);
		choice1List.addMouseListener((MouseListener)mainListener);
		JScrollPane listScrollPane = new JScrollPane(choice1List);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		
		// create and add the label for variable
		choice1Label = new JLabel();
		JPanel cenPane1 = new JPanel(new BorderLayout());
		cenPane1.add("North", choice1Label);
		cenPane1.add("Center", listScrollPane);
 
		choice2ListModel = new DefaultListModel();
 		choice2List = new NolList(choice2ListModel);
		choice2List.setBackground(Color.white);
		choice2List.addMouseListener((MouseListener)mainListener);
		listScrollPane = new JScrollPane(choice2List);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		
		// create and add the label for variable
		choice2Label = new JLabel();

		JPanel cenPane2 = new JPanel(new BorderLayout());
		cenPane2.add("North", choice2Label);
		cenPane2.add("Center", listScrollPane);


		// now put it all together
		JPanel cenPane3 = new JPanel(new GridLayout(1,2,10,10));
		cenPane3.add(cenPane1);
		cenPane3.add(cenPane2);

 		cenPane3.setBorder(new EmptyBorder(10, 10, 10, 10));
		getContentPane().setLayout(new BorderLayout());
		getContentPane().add("Center", cenPane3);
		getContentPane().add("East", getControlPane());

        // Initialize this dialog to its preferred size.
        pack();
	}

	private JPanel getControlPane(){
		JPanel control = new JPanel();
		control.setBackground(getContentPane().getBackground());
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
		control.setBorder(new EmptyBorder(10, 10, 10, 10));

		JPanel pane0 = new JPanel(new GridLayout(5,1,5,5));
		okButton = new JButton(((NolMainFrame)frame).getNolResourceString(OK_BUTTON_LABEL));
		cancelButton = new JButton(((NolMainFrame)frame).getNolResourceString(CANCEL_BUTTON_LABEL));	
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
		choice1ListModel.removeAllElements();
		choice2ListModel.removeAllElements();
		// now fill the variable dialog with variables
		choice1List.addElements(choice1Vector);
		if(!choice1Vector.isEmpty()) 
			choice1List.setSelectedIndex(0);
		choice2List.addElements(choice2Vector);
		if(!choice2Vector.isEmpty()) 
			choice2List.setSelectedIndex(0);
		nofire = false;
	}

	public boolean getResult(){
		return isOk;
	}

	public Vector getSelectedItemsX() {
		return selectedItemsX;
	}

	public Object getSelectedItemX() {
		if(selectedItemsX.isEmpty()) 
			return null;
		return selectedItemsX.elementAt(0);
	}

	public Vector getSelectedItemsY() {
		return selectedItemsY;
	}

	public Object getSelectedItemY() {
		if(selectedItemsY.isEmpty()) 
			return null;
		return selectedItemsY.elementAt(0);
	}

	private boolean okFired() {
		if(isMultiSelection){
			int[] selectedIndeces = choice1List.getSelectedIndices();
			int numberOfSelectedItems = selectedIndeces.length;
			selectedItemsX = new Vector(numberOfSelectedItems);
			if(numberOfSelectedItems == 0) {
				return false;
			}
			for(int z = 0; z < numberOfSelectedItems; z++) {
				selectedItemsX.addElement(choice1Vector.elementAt(selectedIndeces[z]));
			}

			selectedIndeces = choice2List.getSelectedIndices();
			numberOfSelectedItems = selectedIndeces.length;
			selectedItemsY = new Vector(numberOfSelectedItems);
			if(numberOfSelectedItems == 0) {
				return false;
			}
			for(int z = 0; z < numberOfSelectedItems; z++) {
				selectedItemsY.addElement(choice2Vector.elementAt(selectedIndeces[z]));
			}
		}else{
			int selectedIndex = choice1List.getSelectedIndex();
			if(selectedIndex<0) {
				return false;
			}
			selectedItemsX = new Vector(1);
 			selectedItemsX.addElement(choice1Vector.elementAt(selectedIndex));

			selectedIndex = choice2List.getSelectedIndex();
			if(selectedIndex<0) {
				return false;
			}
			selectedItemsY = new Vector(1);
 			selectedItemsY.addElement(choice2Vector.elementAt(selectedIndex));
		}
		return true;
	}


    class MainAction extends AbstractAction implements MouseListener{
		MainAction() {	super("title");}
        @Override
		public void actionPerformed(ActionEvent event) {
			if(nofire) {
				return;
			}
			if (event.getSource().equals(okButton)) {
				isOk = okFired();
				NolXYSingleChoiceDialog.this.setVisible(false);
			} else if(event.getSource().equals(cancelButton)){
				isOk = false;
				NolXYSingleChoiceDialog.this.setVisible(false);
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
			if(clickCount != 2) {
				return;
			}
			isOk = okFired();
			NolXYSingleChoiceDialog.this.setVisible(false);
		}
    }
}

