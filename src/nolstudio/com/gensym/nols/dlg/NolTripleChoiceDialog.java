package com.gensym.nols.dlg;

import java.awt.*;
import java.awt.event.*;
import java.util.*;

import javax.swing.*;
import javax.swing.border.*;

import com.gensym.nols.main.NolMainFrame;

public class NolTripleChoiceDialog extends JDialog {
    protected static final String OK_BUTTON_LABEL = "OkButtonLabel";
    protected static final String CANCEL_BUTTON_LABEL = "CancelButtonLabel";

	private JFrame parent;
	protected JTextArea infoText;

	private JComboBox choice1;
	private JComboBox choice2;
	private DefaultListModel choice3ListModel;
	protected NolList choice3List;
	private JButton okButton, cancelButton;
	private boolean isOk;
	private boolean isMultiSelection;
	
	private String choice1String;
	private String choice2String;
	private String choice3String;

	private Vector choice1Vector;
	private Vector choice2Vector;
	private Vector choice3Vector;

	private Vector selectedItems;

	private MainAction mainListener;
	private JPanel choicePane;
	private JLabel choice1Label;
	private JLabel choice2Label;
	private JLabel choice3Label;

	private boolean nofire = false;

	public NolTripleChoiceDialog(JFrame dw, String title, 
		String choice1String, String choice2String, 
		String choice3String,Vector choice1Vector, 
		Vector choice2Vector,Vector choice3Vector, boolean isMultiSelection) {

		super(dw, title, true);
        parent = dw;
		mainListener = new MainAction();

		this.choice1Vector = choice1Vector;
		this.choice2Vector = choice2Vector;
		this.choice3Vector = choice3Vector;
		this.choice1String = choice1String;
		this.choice2String = choice2String;
		this.choice3String = choice3String;
		this.isMultiSelection = isMultiSelection;
		isOk = false;
		initializeLayout();
	}
	
	public void setContent(String title, 
		String choice1String, String choice2String, 
		String choice3String,Vector choice1Vector, 
		Vector choice2Vector,Vector choice3Vector, boolean isMultiSelection) {

		setTitle(title);

		this.choice1Vector = choice1Vector;
		this.choice2Vector = choice2Vector;
		this.choice3Vector = choice3Vector;
		this.choice1String = choice1String;
		this.choice2String = choice2String;
		this.choice3String = choice3String;
		this.isMultiSelection = isMultiSelection;
		isOk = false;

		if(this.isMultiSelection)
			choice3List.setSelectionMode(ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);
		else
			choice3List.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
	
		choice1Label.setText(choice1String);
		choice2Label.setText(choice2String);
		choice3Label.setText(choice3String);
		refreshDialog(0,0, 0);
		pack();
	}


	private void initializeLayout(){ 
		// create and add the label for variables
		choice3ListModel = new DefaultListModel();
 		choice3List = new NolList(choice3ListModel);
		choice3List.setBackground(Color.white);
		choice3List.addMouseListener((MouseListener)mainListener);
		JScrollPane listScrollPane = new JScrollPane(choice3List);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		
		// Create the choice combo boxes to be placed at the top of the dialog
		choicePane = new JPanel(new GridLayout(5,1,5,5));
		// create and add the label for data source
		choice1Label = new JLabel();
		choicePane.add(choice1Label);
		// create and add the choice combo box for data source
		choice1 = new JComboBox();	
		choice1.addActionListener(mainListener);
		choicePane.add(choice1);

		choice2Label = new JLabel();
		choicePane.add(choice2Label);
		// create and add the choice combo box for data source
		choice2 = new JComboBox();
		choice2.addActionListener(mainListener);
		choicePane.add(choice2);
		choice2.addActionListener(mainListener);
		// create and add the label for data series
		choice3Label = new JLabel();
		choicePane.add(choice3Label);

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

	public void refreshDialog(int choice1Index, int choice2Index, int flag) {
//		System.out.println("refreshDialog");

		nofire  = true;
	 	int count1 = choice1Vector.size();
		if(flag == 0) {
			// clean up content from maybe last time...
			choice3ListModel.removeAllElements();
			choice1.removeAllItems();
			choice2.removeAllItems();
			// fill the data source choice with all possible sources
			for(int i = 0; i < count1; i++) {
				choice1.addItem(choice1Vector.elementAt(i).toString());
			}
			Vector choice2Content = (Vector) choice2Vector.elementAt(0);
			for(int z = 0; z < choice2Content.size(); z++) {
				choice2.addItem(choice2Content.elementAt(z).toString());
			}
			Vector choice3Content1 = (Vector) choice3Vector.elementAt(0);
			Vector choice3Content2 = (Vector) choice3Content1.elementAt(0);
			choice3List.addElements(choice3Content2);
			if(!choice3Content2.isEmpty()) 
				choice3List.setSelectedIndex(0);
		}else if(flag == 1){		
			choice2.removeAllItems();
			choice3ListModel.removeAllElements();
			Vector choice2Content = (Vector) choice2Vector.elementAt(choice1Index);
			for(int z = 0; z < choice2Content.size(); z++) {
				choice2.addItem(choice2Content.elementAt(z).toString());
			}
			Vector choice3Content1 = (Vector) choice3Vector.elementAt(choice1Index);
			Vector choice3Content2 = (Vector) choice3Content1.elementAt(choice2Index);
			choice3List.addElements(choice3Content2);
			if(!choice3Content2.isEmpty()) 
				choice3List.setSelectedIndex(0);
		}else if(flag == 2){		
			choice3ListModel.removeAllElements();
			Vector choice3Content1 = (Vector) choice3Vector.elementAt(choice1Index);
			Vector choice3Content2 = (Vector) choice3Content1.elementAt(choice2Index);
			choice3List.addElements(choice3Content2);
			if(!choice3Content2.isEmpty()) 
				choice3List.setSelectedIndex(0);
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

	public Object getChoice2SelectedItem(){
		return choice2.getSelectedItem();
	}

	private boolean okFired() {
		if(isMultiSelection){
			int[] selectedIndeces = choice3List.getSelectedIndices();
			int numberOfSelectedItems = selectedIndeces.length;
			if(numberOfSelectedItems == 0) {
				return false;
			}
			selectedItems = new Vector(numberOfSelectedItems);

			Vector choice3Content1 = (Vector) choice3Vector.elementAt(choice1.getSelectedIndex());
			Vector choice3Content2 = (Vector) choice3Content1.elementAt(choice2.getSelectedIndex());
			for(int z = 0; z < numberOfSelectedItems; z++) {
				Object obj = choice3Content2.elementAt(selectedIndeces[z]);		
				selectedItems.addElement(obj);
			}
		}else{
			int selectedIndex = choice3List.getSelectedIndex();
			if(selectedIndex<0) {
				return false;
			}

			selectedItems = new Vector(1);
			Vector choice3Content1 = (Vector) choice3Vector.elementAt(choice1.getSelectedIndex());
			Vector choice3Content2 = (Vector) choice3Content1.elementAt(choice2.getSelectedIndex());
			Object obj = choice3Content2.elementAt(selectedIndex);		
			selectedItems.addElement(obj);
		}
		return true;
	}


    class MainAction extends AbstractAction implements MouseListener{
		MainAction() {super("title");}
        @Override
		public void actionPerformed(ActionEvent event) {
			if(nofire) {
				return;
			}
			if (event.getSource().equals(okButton)) {
				isOk = okFired();
				NolTripleChoiceDialog.this.setVisible(false);
			} else if(event.getSource().equals(choice1)){
				int index = choice1.getSelectedIndex();
				refreshDialog(index,0, 1);
			} else if(event.getSource().equals(choice2)){
				int index1 = choice1.getSelectedIndex();
				int index2 = choice2.getSelectedIndex();
				refreshDialog(index1,index2, 2);
			} else if(event.getSource().equals(cancelButton)){
				isOk = false;
				NolTripleChoiceDialog.this.setVisible(false);
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
			NolTripleChoiceDialog.this.setVisible(false);
		}
    }
}

