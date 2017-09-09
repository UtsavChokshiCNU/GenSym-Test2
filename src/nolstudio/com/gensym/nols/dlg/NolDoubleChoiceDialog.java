package com.gensym.nols.dlg;

import java.awt.*;
import java.awt.event.*;
import java.util.*;

import javax.swing.*;
import javax.swing.border.*;

import com.gensym.nols.main.NolMainFrame;

public class NolDoubleChoiceDialog extends JDialog {
    protected static final String OK_BUTTON_LABEL = "OkButtonLabel";
    protected static final String CANCEL_BUTTON_LABEL = "CancelButtonLabel";

	private JFrame parent;
	protected JTextArea infoText;

	private JComboBox choice1;
	private DefaultListModel choice2ListModel;
	protected NolList choice2List;
	private JButton okButton, cancelButton;
	private boolean isOk;
	private boolean isMultiSelection;
	
	private String choice1String;
	private String choice2String;

	private Vector choice1Vector;
	private Vector choice2Vector;

	private Vector selectedItems;

	private MainAction mainListener;
	private JPanel choicePane;
	private JLabel choice1Label;
	private JLabel choice2Label;

	private boolean nofire = false;
	private boolean choiceStatusFire = false;

	public NolDoubleChoiceDialog(JFrame dw, String title, String choice1String, 
		String choice2String,Vector choice1Vector, Vector choice2Vector, boolean isMultiSelection) {

		super(dw, title, true);
        parent = dw;
		mainListener = new MainAction();

		this.choice1Vector = choice1Vector;
		this.choice2Vector = choice2Vector;
		this.choice1String = choice1String;
		this.choice2String = choice2String;
		this.isMultiSelection = isMultiSelection;
		isOk = false;
		initializeLayout();
	}
	
	public void setContent(String title, String choice1String, 
		String choice2String,Vector choice1Vector, Vector choice2Vector, 
		boolean isMultiSelection) {
		setTitle(title);

		this.choice1Vector = choice1Vector;
		this.choice2Vector = choice2Vector;
		this.choice1String = choice1String;
		this.choice2String = choice2String;
		this.isMultiSelection = isMultiSelection;
		isOk = false;

		if(this.isMultiSelection)
			choice2List.setSelectionMode(ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);
		else
			choice2List.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
	
		choice1Label.setText(choice1String);
		choice2Label.setText(choice2String);
		refreshDialog(0, true);
		pack();
	}


	private void initializeLayout(){ 
		// create and add the label for variables
		choice2ListModel = new DefaultListModel();
 		choice2List = new NolList(choice2ListModel);
		choice2List.setBackground(Color.white);
		choice2List.addMouseListener((MouseListener)mainListener);
		JScrollPane listScrollPane = new JScrollPane(choice2List);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		
		// Create the choice combo boxes to be placed at the top of the dialog
		choicePane = new JPanel(new GridLayout(3,1,5,5));
		// create and add the label for data source
		choice1Label = new JLabel();
		choicePane.add(choice1Label);
		// create and add the choice combo box for data source
		choice1 = new JComboBox();
		choicePane.add(choice1);
		choice1.addActionListener(mainListener);
		// create and add the label for data series
		choice2Label = new JLabel();
		choicePane.add(choice2Label);

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
		cancelButton = new JButton(((NolMainFrame)parent).getNolResourceString(CANCEL_BUTTON_LABEL));
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

	public void refreshDialog(int choice1Index, boolean first) {
//		System.out.println("refreshDialog");

		nofire  = true;
	 	int numDataSource = choice1Vector.size();
		if(first) {
			// clean up content from maybe last time...
			choice2ListModel.removeAllElements();
			choice1.removeAllItems();
			// fill the data source choice with all possible sources
			for(int i = 0; i < numDataSource; i++) {
				choice1.addItem(choice1Vector.elementAt(i).toString());
			}
			Vector choice2ContentSource = (Vector) choice2Vector.elementAt(0);
			choice2List.addElements(choice2ContentSource);
			if(!choice2ContentSource.isEmpty()) {
				choice2List.setSelectedIndex(0);
			}
		}else {		
			choice2ListModel.removeAllElements();
			Vector choice2ContentSource = (Vector) choice2Vector.elementAt(choice1Index);
			choice2List.addElements(choice2ContentSource);
			if(!choice2ContentSource.isEmpty()) {
				choice2List.setSelectedIndex(0);
			}
		}
		nofire = false;
	}

	public boolean getResult(){
		return isOk;
	}

	public Vector getSelectedItems() {
		return selectedItems;
	}

	public Object getSelectedItem() {
		return selectedItems.elementAt(0);
	}

	public Object getChoice1SelectedItem(){
		return choice1.getSelectedItem();
	}

	private boolean okFired() {
		if(isMultiSelection){
			int[] selectedIndeces = choice2List.getSelectedIndices();
			int numberOfSelectedItems = selectedIndeces.length;
			if(numberOfSelectedItems == 0){
				return false;
			}
			selectedItems = new Vector(numberOfSelectedItems);

			Vector choice2ContentSource = (Vector) choice2Vector.elementAt(choice1.getSelectedIndex());
			for(int z = 0; z < selectedIndeces.length; z++) {
				Object obj = choice2ContentSource.elementAt(selectedIndeces[z]);		
				selectedItems.addElement(obj);
			}
		}else{
			int selectedIndex = choice2List.getSelectedIndex();
			if(selectedIndex<0){
				return false;
			}
			selectedItems = new Vector(1);
			Vector choice2ContentSource = (Vector) choice2Vector.elementAt(choice1.getSelectedIndex());
 			selectedItems.addElement(choice2ContentSource.elementAt(selectedIndex));
		}
		return true;
	}


    class MainAction extends AbstractAction implements MouseListener{
		MainAction() {super("title");}
        @Override
		public void actionPerformed(ActionEvent event) {
			if(nofire){
				return;
			}
			if (event.getSource().equals(okButton)) {
				isOk = okFired();
//				System.out.println("isok="+isOk);
//				System.out.println("selectedItems="+selectedItems.elementAt(0));
				NolDoubleChoiceDialog.this.setVisible(false);
			} else if(event.getSource().equals(choice1)){
				if(choiceStatusFire){
					return;
				}
				int index = choice1.getSelectedIndex();
				refreshDialog(index, false);
			} else if(event.getSource().equals(cancelButton)){
				isOk = false;
				NolDoubleChoiceDialog.this.setVisible(false);
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
			NolDoubleChoiceDialog.this.setVisible(false);
		}
    }
}

