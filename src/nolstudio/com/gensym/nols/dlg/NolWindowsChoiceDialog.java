package com.gensym.nols.dlg;

import java.awt.*;
import java.awt.event.*;
import java.util.*;

import javax.swing.*;
import javax.swing.border.*;

import com.gensym.nols.main.*;
 
public class NolWindowsChoiceDialog extends JDialog {
    protected static final String CANCEL_BUTTON_LABEL = "CancelButtonLabel";
    protected static final String CLOSE_LABEL = "CloseLabel";
    protected static final String ACTIVATE_LABEL = "WindowsChoiceDialog_activateLabel";
    protected static final String SELECT_WINDOWS_LABEL = "WindowsChoiceDialog_selectWindowsLabel";
	protected static final String TITLE_LABEL = "WindowsChoiceDialog_windowsTitleLabel";

	private JFrame parent;
	protected JTextArea infoText;

	private DefaultListModel choiceListModel;
	protected JList choiceList;
	private JButton okButton, cancelButton, closeButton;
	private int returnFlag;
	private boolean isMultiSelection;

	private Vector choiceVector;

	private Vector selectedItems;
	private MainAction mainListener;
	private JPanel choicePane;
	private JLabel choiceLabel;
	private boolean nofire = false;
	private boolean choiceStatusFire = false;

	public NolWindowsChoiceDialog(JFrame parent, Vector choiceVector, boolean isMultiSelection) {

		super(parent, ((NolMainFrame)parent).getNolResourceString(TITLE_LABEL), true);
        this.parent = parent;
		mainListener = new MainAction();

		this.choiceVector = choiceVector;
		this.isMultiSelection = isMultiSelection;
		returnFlag = -1;
		initializeLayout();
		refreshDialog();
	}
	
	public void setContent(Vector choiceVector, boolean isMultiSelection) {

		this.choiceVector = choiceVector;
		this.isMultiSelection = isMultiSelection;
		returnFlag = -1;

		if(this.isMultiSelection)
			choiceList.setSelectionMode(ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);
		else
			choiceList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		refreshDialog();
		pack();
	}


	private void initializeLayout(){ 
		// create and add the label for variables
		choiceListModel = new DefaultListModel();
 		choiceList = new JList(choiceListModel);
		choiceList.setBackground(Color.white);
		choiceList.addMouseListener((MouseListener)mainListener);
		JScrollPane listScrollPane = new JScrollPane(choiceList);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		
		// Create the choice combo boxes to be placed at the top of the dialog
		choicePane = new JPanel(new GridLayout(1,1,5,5));
		// create and add the label for variable 
		choiceLabel = new JLabel(((NolMainFrame)parent).getNolResourceString(SELECT_WINDOWS_LABEL) + ":");
 		choicePane.add(choiceLabel);

		// now put it all together
		JPanel cenPane = new JPanel(new BorderLayout());
 		cenPane.setBorder(new EmptyBorder(10, 10, 10, 10));
		cenPane.add("North", choicePane);
		cenPane.add("Center", listScrollPane);
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
		okButton = new JButton(((NolMainFrame)parent).getNolResourceString(ACTIVATE_LABEL));
		cancelButton = new JButton(((NolMainFrame)parent).getNolResourceString(CANCEL_BUTTON_LABEL));
		closeButton = new JButton(((NolMainFrame)parent).getNolResourceString(CLOSE_LABEL));
		okButton.addActionListener(mainListener);
		cancelButton.addActionListener(mainListener);
		closeButton.addActionListener(mainListener);
		pane0.add(okButton);
		pane0.add(cancelButton);
		pane0.add(closeButton);
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
		for(int z = 0; z < choiceVector.size(); z++) {
			choiceListModel.addElement(choiceVector.elementAt(z));
		}
		if(!choiceVector.isEmpty())
			choiceList.setSelectedIndex(0);
		nofire = false;
	}

	public int getResult(){
		return returnFlag;
	}

	public Vector getSelectedItems() {
		return selectedItems;
	}

	public Object getSelectedItem() {
		if(selectedItems.isEmpty()) 
			return null;
		return selectedItems.elementAt(0);
	}

	public int getSelectedIndex() {
		return choiceList.getSelectedIndex();
	}

	private int okFired() {
		if(isMultiSelection){
			int[] selectedIndeces = choiceList.getSelectedIndices();
			int numberOfSelectedItems = selectedIndeces.length;
			selectedItems = new Vector(numberOfSelectedItems);
			if(numberOfSelectedItems == 0) {
				return -1;
			}
			for(int z = 0; z < numberOfSelectedItems; z++) {
				selectedItems.addElement(choiceVector.elementAt(selectedIndeces[z]));
			}
		}else{
			int selectedIndex = choiceList.getSelectedIndex();
			if(selectedIndex<0) {
				return -1;
			}
			selectedItems = new Vector(1);
 			selectedItems.addElement(choiceVector.elementAt(selectedIndex));
		}
		return 1;
	}


    class MainAction extends AbstractAction implements MouseListener{
		MainAction() {	super("title");}
        @Override
		public void actionPerformed(ActionEvent event) {
			if(nofire) {
				return;
			}
			if (event.getSource().equals(okButton)) {
				returnFlag = okFired();
				NolWindowsChoiceDialog.this.setVisible(false);
			} else if(event.getSource().equals(closeButton)){
				okFired();
				returnFlag = 2;
				NolWindowsChoiceDialog.this.setVisible(false);
			} else if(event.getSource().equals(cancelButton)){
				returnFlag = -1;
				NolWindowsChoiceDialog.this.setVisible(false);
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
			returnFlag = okFired();
			NolWindowsChoiceDialog.this.setVisible(false);
		}
    }
}

