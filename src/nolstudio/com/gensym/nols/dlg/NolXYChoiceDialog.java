package com.gensym.nols.dlg;

import java.awt.*;
import java.awt.event.*;
import java.util.*;

import javax.swing.*;
import javax.swing.border.*;

import com.gensym.nols.main.NolMainFrame;

public class NolXYChoiceDialog extends JDialog {
    protected static final String OK_BUTTON_LABEL = "OkButtonLabel";
    protected static final String CANCEL_BUTTON_LABEL = "CancelButtonLabel";

	private JFrame frame;
	protected JTextArea infoText;

	private JComboBox XChoice1;
	private JComboBox XChoice2;
	private JComboBox YChoice1;
	private JComboBox YChoice2;
	private DefaultListModel XChoice3ListModel;
	private DefaultListModel YChoice3ListModel;
	protected NolList XChoice3List;  // MK 2/6/99 changed to faster list type NolList
	protected NolList YChoice3List;
	private JButton okButton, cancelButton;
	private boolean isOk;
	private boolean isMultiSelection;
	
	private String XChoice1String;
	private String XChoice2String;
	private String XChoice3String;

	private Vector XChoice1Vector;
	private Vector XChoice2Vector;
	private Vector XChoice3Vector;

	private Vector YChoice1Vector;
	private Vector YChoice2Vector;
	private Vector YChoice3Vector;

	private Vector selectedItemsX;
	private Vector selectedItemsY;

	private MainAction mainListener;
	private JLabel XChoice1Label;
	private JLabel XChoice2Label;
	private JLabel XChoice3Label;
	private JLabel YChoice1Label;
	private JLabel YChoice2Label;
	private JLabel YChoice3Label;

	private boolean nofire = false;

	public NolXYChoiceDialog(JFrame dw, String title, 
		String XChoice1String, String XChoice2String, String XChoice3String,
		Vector XChoice1Vector, Vector XChoice2Vector,Vector XChoice3Vector, 
		Vector YChoice1Vector, Vector YChoice2Vector,Vector YChoice3Vector, 
		boolean isMultiSelection) {

		super(dw, title, true);
        frame = dw;
		mainListener = new MainAction();

		this.XChoice1Vector = XChoice1Vector;
		this.XChoice2Vector = XChoice2Vector;
		this.XChoice3Vector = XChoice3Vector;
		this.YChoice1Vector = YChoice1Vector;
		this.YChoice2Vector = YChoice2Vector;
		this.YChoice3Vector = YChoice3Vector;

		this.XChoice1String = XChoice1String;
		this.XChoice2String = XChoice2String;
		this.XChoice3String = XChoice3String;
		this.isMultiSelection = isMultiSelection;
		isOk = false;
		initializeLayout();
	}
	
	public void setContent(String title, 
		String XChoice1String, String XChoice2String, String XChoice3String,
		Vector XChoice1Vector, Vector XChoice2Vector,Vector XChoice3Vector, 
		Vector YChoice1Vector, Vector YChoice2Vector,Vector YChoice3Vector, 
		boolean isMultiSelection) {


		setTitle(title);

		this.XChoice1Vector = XChoice1Vector;
		this.XChoice2Vector = XChoice2Vector;
		this.XChoice3Vector = XChoice3Vector;
		this.YChoice1Vector = YChoice1Vector;
		this.YChoice2Vector = YChoice2Vector;
		this.YChoice3Vector = YChoice3Vector;

		this.XChoice1String = XChoice1String;
		this.XChoice2String = XChoice2String;
		this.XChoice3String = XChoice3String;
		
		this.isMultiSelection = isMultiSelection;
		isOk = false;

		if(this.isMultiSelection){
			XChoice3List.setSelectionMode(ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);
			YChoice3List.setSelectionMode(ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);
		}else{
			XChoice3List.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
			YChoice3List.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		}

		XChoice1Label.setText(XChoice1String);
		XChoice2Label.setText(XChoice2String);
		XChoice3Label.setText(XChoice3String);
		
		YChoice1Label.setText(XChoice1String);
		YChoice2Label.setText(XChoice2String);
		YChoice3Label.setText(XChoice3String);
		refreshDialogX(0, 0, 0);
		refreshDialogY(0, 0, 0);
		pack();
	}


	private void initializeLayout(){ 
		// create and add the label for variables
		XChoice3ListModel = new DefaultListModel();
 		XChoice3List = new NolList(XChoice3ListModel);
		XChoice3List.setBackground(Color.white);
		XChoice3List.addMouseListener((MouseListener)mainListener);
		JScrollPane listScrollPaneX = new JScrollPane(XChoice3List);
		listScrollPaneX.setBorder(BorderFactory.createLoweredBevelBorder());
		
		YChoice3ListModel = new DefaultListModel();
 		YChoice3List = new NolList(YChoice3ListModel);
		YChoice3List.setBackground(Color.white);
		YChoice3List.addMouseListener((MouseListener)mainListener);
		JScrollPane listScrollPaneY = new JScrollPane(YChoice3List);
		listScrollPaneY.setBorder(BorderFactory.createLoweredBevelBorder());
		
		// Create the choice combo boxes to be placed at the top of the dialog
		JPanel choicePaneX = new JPanel(new GridLayout(5,1,5,5));
		// create and add the label for data source
		XChoice1Label = new JLabel();
		choicePaneX.add(XChoice1Label);
		// create and add the choice combo box for data source
		XChoice1 = new JComboBox();
		XChoice1.addActionListener(mainListener);
		choicePaneX.add(XChoice1);

		XChoice2Label = new JLabel();
		choicePaneX.add(XChoice2Label);
		// create and add the choice combo box for data source
		XChoice2 = new JComboBox();
		choicePaneX.add(XChoice2);
		XChoice2.addActionListener(mainListener);
		// create and add the label for data series
		XChoice3Label = new JLabel();
		choicePaneX.add(XChoice3Label);

		// Create the choice combo boxes to be placed at the top of the dialog
		JPanel choicePaneY = new JPanel(new GridLayout(5,1,5,5));
		// create and add the label for data source
		YChoice1Label = new JLabel();
		choicePaneY.add(YChoice1Label);
		// create and add the choice combo box for data source
		YChoice1 = new JComboBox();
		YChoice1.addActionListener(mainListener);
		choicePaneY.add(YChoice1);

		YChoice2Label = new JLabel();
		choicePaneY.add(YChoice2Label);
		// create and add the choice combo box for data source
		YChoice2 = new JComboBox();
		choicePaneY.add(YChoice2);
		YChoice2.addActionListener(mainListener);
		// create and add the label for data series
		YChoice3Label = new JLabel();
		choicePaneY.add(YChoice3Label);

		// now put it all together
		JPanel cenPane = new JPanel(new GridLayout(1,2,10,10));
 		cenPane.setBorder(new EmptyBorder(10, 10, 10, 10));
		
		JPanel cenPaneX = new JPanel(new BorderLayout());
		cenPaneX.add("North", choicePaneX);
		cenPaneX.add("Center", listScrollPaneX);

		JPanel cenPaneY = new JPanel(new BorderLayout());
		cenPaneY.add("North", choicePaneY);
		cenPaneY.add("Center", listScrollPaneY);
		
		cenPane.add(cenPaneX);
		cenPane.add(cenPaneY);
		getContentPane().setLayout(new BorderLayout());
		getContentPane().add("Center", cenPane);
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

	public void refreshDialogX(int XChoice1Index, int XChoice2Index, int flag) {
//		System.out.println("refreshDialog");
//		System.out.println("XChoice1Index"+XChoice1Index);
//		System.out.println("XChoice2Index"+XChoice2Index);
//		System.out.println("flag"+flag);
		nofire  = true;
	 	int count1 = XChoice1Vector.size();
		if(flag == 0) {
			XChoice1.removeAllItems();
			XChoice2.removeAllItems();
			XChoice3ListModel.removeAllElements();
			// fill the data source choice with all possible sources
			for(int i = 0; i < count1; i++) {
				XChoice1.addItem(XChoice1Vector.elementAt(i).toString());
			}
			Vector XChoice2Content = (Vector) XChoice2Vector.elementAt(0);
			for(int z = 0; z < XChoice2Content.size(); z++) {
				XChoice2.addItem(XChoice2Content.elementAt(z).toString());
			}
			Vector XChoice3Content1 = (Vector) XChoice3Vector.elementAt(0);
			Vector XChoice3Content2 = (Vector) XChoice3Content1.elementAt(0);
			XChoice3List.addElements(XChoice3Content2);  // changed to faster method on NolList - MK 2/9/99
			if(!XChoice3Content2.isEmpty()) 
				XChoice3List.setSelectedIndex(0);
		}else if(flag == 1){
			XChoice3ListModel.removeAllElements();
			XChoice2.removeAllItems();
			Vector XChoice2Content = (Vector) XChoice2Vector.elementAt(XChoice1Index);
			for(int z = 0; z < XChoice2Content.size(); z++) {
				XChoice2.addItem(XChoice2Content.elementAt(z).toString());
			}
			Vector XChoice3Content1 = (Vector) XChoice3Vector.elementAt(XChoice1Index);
			Vector XChoice3Content2 = (Vector) XChoice3Content1.elementAt(XChoice2Index);
			XChoice3List.addElements(XChoice3Content2);
			if(!XChoice3Content2.isEmpty()) 
				XChoice3List.setSelectedIndex(0);
		}else if(flag == 2){		
			XChoice3ListModel.removeAllElements();
			Vector XChoice3Content1 = (Vector) XChoice3Vector.elementAt(XChoice1Index);
			Vector XChoice3Content2 = (Vector) XChoice3Content1.elementAt(XChoice2Index);
			XChoice3List.addElements(XChoice3Content2);
			if(!XChoice3Content2.isEmpty()) 
				XChoice3List.setSelectedIndex(0);
		}

		nofire = false;
	}

	public void refreshDialogY(int YChoice1Index, int YChoice2Index, int flag) {
//		System.out.println("refreshDialogY");

		nofire  = true;
	 	int count1 = YChoice1Vector.size();
		if(flag == 0) {
			// clean up content from maybe last time...
			YChoice3ListModel.removeAllElements();
			YChoice1.removeAllItems();
			YChoice2.removeAllItems();
			// fill the data source choice with all possible sources
			for(int i = 0; i < count1; i++) {
				YChoice1.addItem(YChoice1Vector.elementAt(i).toString());
			}
			Vector YChoice2Content = (Vector) YChoice2Vector.elementAt(0);
			for(int z = 0; z < YChoice2Content.size(); z++) {
				YChoice2.addItem(YChoice2Content.elementAt(z).toString());
			}
			Vector YChoice3Content1 = (Vector) YChoice3Vector.elementAt(0);
			Vector YChoice3Content2 = (Vector) YChoice3Content1.elementAt(0);
			YChoice3List.addElements(YChoice3Content2);
		}else if(flag == 1){		
			YChoice2.removeAllItems();
			YChoice3ListModel.removeAllElements();
			Vector YChoice2Content = (Vector) YChoice2Vector.elementAt(YChoice1Index);
			for(int z = 0; z < YChoice2Content.size(); z++) {
				YChoice2.addItem(YChoice2Content.elementAt(z).toString());
			}
			Vector YChoice3Content1 = (Vector) YChoice3Vector.elementAt(YChoice1Index);
			Vector YChoice3Content2 = (Vector) YChoice3Content1.elementAt(YChoice2Index);
			YChoice3List.addElements(YChoice3Content2);
		}else if(flag == 2){		
			YChoice3ListModel.removeAllElements();
			Vector YChoice3Content1 = (Vector) YChoice3Vector.elementAt(YChoice1Index);
			Vector YChoice3Content2 = (Vector) YChoice3Content1.elementAt(YChoice2Index);
			YChoice3List.addElements(YChoice3Content2);
		}
		nofire = false;
	}

	public boolean getResult(){
		return isOk;
	}

	public Object getXSelectedItem() {
		return selectedItemsX.elementAt(0);
	}

	public Object getYSelectedItem() {
		return selectedItemsY.elementAt(0);
	}

	public Object getXChoice1SelectedItem(){
		return XChoice1.getSelectedItem();
	}

	public Object getXChoice2SelectedItem(){
		return XChoice2.getSelectedItem();
	}

	public Object getYChoice1SelectedItem(){
		return YChoice1.getSelectedItem();
	}

	public Object getYChoice2SelectedItem(){
		return YChoice2.getSelectedItem();
	}

	private boolean okFired() {
		if(isMultiSelection){
			int[] selectedIndecesX = XChoice3List.getSelectedIndices();
			int numberOfSelectedItemsX = selectedIndecesX.length;
			if(numberOfSelectedItemsX == 0) {
				return false;
			}
			selectedItemsX = new Vector(numberOfSelectedItemsX);

			Vector XChoice3Content1 = (Vector) XChoice3Vector.elementAt(XChoice1.getSelectedIndex());
			Vector XChoice3Content2 = (Vector) XChoice3Content1.elementAt(XChoice2.getSelectedIndex());
			for(int z = 0; z < numberOfSelectedItemsX; z++) {
				Object obj = XChoice3Content2.elementAt(selectedIndecesX[z]);		
				selectedItemsX.addElement(obj);
			}

			int[] selectedIndecesY = YChoice3List.getSelectedIndices();
			int numberOfSelectedItemsY = selectedIndecesY.length;
			if(numberOfSelectedItemsY == 0) {
				return false;
			}
			selectedItemsY = new Vector(numberOfSelectedItemsY);

			Vector YChoice3Content1 = (Vector) YChoice3Vector.elementAt(YChoice1.getSelectedIndex());
			Vector YChoice3Content2 = (Vector) YChoice3Content1.elementAt(YChoice2.getSelectedIndex());
			for(int z = 0; z < numberOfSelectedItemsY; z++) {
				Object obj = YChoice3Content2.elementAt(selectedIndecesY[z]);		
				selectedItemsY.addElement(obj);
			}

		}else{
			int selectedIndex = XChoice3List.getSelectedIndex();
			if(selectedIndex<0) {
				return false;
			}

			selectedItemsX = new Vector(1);
			Vector XChoice3Content1 = (Vector) XChoice3Vector.elementAt(XChoice1.getSelectedIndex());
			Vector XChoice3Content2 = (Vector) XChoice3Content1.elementAt(XChoice2.getSelectedIndex());
			Object obj = XChoice3Content2.elementAt(selectedIndex);		
			selectedItemsX.addElement(obj);

		
			selectedIndex = YChoice3List.getSelectedIndex();
			if(selectedIndex<0) {
				return false;
			}

			selectedItemsY = new Vector(1);
			Vector YChoice3Content1 = (Vector) YChoice3Vector.elementAt(YChoice1.getSelectedIndex());
			Vector YChoice3Content2 = (Vector) YChoice3Content1.elementAt(YChoice2.getSelectedIndex());
			obj = YChoice3Content2.elementAt(selectedIndex);		
			selectedItemsY.addElement(obj);
		
		}
		return true;
	}


    class MainAction extends AbstractAction implements MouseListener {
		MainAction() {super("title");}
        @Override
		public void actionPerformed(ActionEvent event) {
			if(nofire) {
				return;
			}
			if (event.getSource().equals(okButton)) {
				isOk = okFired();
				NolXYChoiceDialog.this.setVisible(false);
			} else if(event.getSource().equals(XChoice1)){
				int index = XChoice1.getSelectedIndex();
				refreshDialogX(index,0, 1);
			} else if(event.getSource().equals(XChoice2)){
				int index1 = XChoice1.getSelectedIndex();
				int index2 = XChoice2.getSelectedIndex();
				refreshDialogX(index1,index2, 2);
			} else if(event.getSource().equals(YChoice1)){
				int index = YChoice1.getSelectedIndex();
				refreshDialogY(index,0, 1);
			} else if(event.getSource().equals(YChoice2)){
				int index1 = YChoice1.getSelectedIndex();
				int index2 = YChoice2.getSelectedIndex();
				refreshDialogY(index1,index2, 2);
			} else if(event.getSource().equals(cancelButton)){
				isOk = false;
				NolXYChoiceDialog.this.setVisible(false);
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
			NolXYChoiceDialog.this.setVisible(false);
		}
    }

	private Object getPrototypeObject(Vector vars) {
		int maxLength = 0;
		int index = -1;
		for(int z = 0; z < vars.size(); z++) {
			if(vars.elementAt(z).toString().length() > maxLength) {
				maxLength = vars.elementAt(z).toString().length();
				index = z;
			}
		}
		return vars.elementAt(index);
	}

}

