package com.gensym.uitools.attrdisplays.layoutui;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.util.Enumeration;
import java.util.Vector;
import javax.accessibility.AccessibleState;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.DefaultListModel;
import javax.swing.ImageIcon;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.uitools.attrdisplays.layoutmodel.CollectionEvent;
import com.gensym.uitools.attrdisplays.layoutmodel.CollectionListener;
import com.gensym.uitools.attrdisplays.layoutmodel.LayoutStructure;
import com.gensym.uitools.attrdisplays.layoutmodel.VectorsNotSameLengthException;
import com.gensym.uitools.attrdisplays.layoutmodel.LayoutTableModel;
import com.gensym.uitools.attrdisplays.layoutmodel.AttributeDisplayLayout;
import com.gensym.uitools.attrdisplays.layoutmodel.AttributeDisplayLayoutEditor;



class AttributeDisplayLayoutPanel extends JPanel implements ActionListener {

  protected JButton addButton;
  protected JButton removeButton;
  protected JList choicesAvailable;
  protected ListTable attrsChosen;
  private GridBagLayout panelLayout;
  private static Resource dlgLabels = Trace.getBundle("com.gensym.uitools.attrdisplays.DialogLabels");
  private String label;
  protected Vector collectionListeners = new Vector();
  private LayoutStructure globalLayout;
  private Object[] selectedValues;
  private AttributeDisplayLayoutEditor editor;

  AttributeDisplayLayoutPanel (DefaultListModel listModel, LayoutTableModel tableModel,
			       String label, LayoutStructure globalLayout,
			       AttributeDisplayLayoutEditor editor)
  {
    this.editor = editor;
    choicesAvailable = new JList(listModel);
    attrsChosen = new ListTable(tableModel);
    this.label = label;
    this.globalLayout = globalLayout;
    panelLayout = new GridBagLayout();
    setLayout(panelLayout);
    addButton = new JButton (new ImageIcon (getClass().getResource ("rightarrow66.gif")));
    addButton.setToolTipText("Add selected attribute to this display");
    removeButton = new JButton (new ImageIcon (getClass().getResource ("leftarrow66.gif")));
    removeButton.setToolTipText("Remove selected attribute from this display");
    addButton.addActionListener(this);
    removeButton.addActionListener(this);
    initialize();
  } 

  String getLabel() {
    if (label != null)
      return label;
    else
      return "";
  }

  private static JPanel createAddRemoveButtonsPanel(JButton addButton,
						    JButton removeButton) {
    JPanel buttonPanel = new JPanel();
    GridBagLayout gbl = new GridBagLayout();
    buttonPanel.setLayout(gbl);
    GridBagConstraints gbc = new GridBagConstraints();
    gbc.insets = new Insets (0, 0, 5, 5);
    gbc.gridy = GridBagConstraints.RELATIVE;
    gbc.weightx = 1.0;
    gbc.weighty = 0.5;
    gbc.gridwidth = GridBagConstraints.REMAINDER;
    gbc.fill = GridBagConstraints.HORIZONTAL;
    gbc.anchor = GridBagConstraints.WEST;
    gbl.setConstraints(addButton, gbc);
    buttonPanel.add(addButton);
    gbl.setConstraints(removeButton, gbc);
    buttonPanel.add(removeButton);
    return buttonPanel;
  }

  private static final int defaultListWidth = 150,defaultListHeight = 150;

  private static JPanel createChoicesPanel(JList choicesAvailable) {
    JPanel choicesPanel = new JPanel();
    choicesPanel.setMinimumSize
      (new Dimension(defaultListWidth,defaultListHeight));
    choicesPanel.setPreferredSize
      (new Dimension(defaultListWidth,defaultListHeight));    
    choicesPanel.setLayout(new BorderLayout());
    JLabel forChoicesList = new JLabel(dlgLabels.getString("unselectedAttrs"));
    JScrollPane scrollPane = new JScrollPane(choicesAvailable);
    choicesPanel.add(scrollPane, "Center");
    choicesPanel.add(forChoicesList, "North");
    return choicesPanel;
  }  

  private static final int defaultTableWidth = 200;
  private static JPanel createSelectedAttributesPanel(ListTable attrsChosen) {
    JPanel chosenPanel = new JPanel();

    chosenPanel.setMinimumSize
      (new Dimension(defaultTableWidth,defaultListHeight));
    chosenPanel.setPreferredSize
      (new Dimension(defaultTableWidth,defaultListHeight));    
    JLabel forChosenList = new JLabel(dlgLabels.getString("selectedAttrs"));
    JScrollPane scrollPane = new JScrollPane(attrsChosen);
    chosenPanel.setLayout(new BorderLayout());
    chosenPanel.add(forChosenList, "North");    
    chosenPanel.add(scrollPane, "Center");
    return chosenPanel;
  }    

  private void initialize() {

    JPanel choicesPanel = createChoicesPanel(choicesAvailable);
    JPanel buttonPanel = createAddRemoveButtonsPanel(addButton, removeButton);
    JPanel chosenPanel = createSelectedAttributesPanel(attrsChosen);

    GridBagConstraints gbc = new GridBagConstraints();
    gbc.gridheight = GridBagConstraints.REMAINDER;
    gbc.gridwidth = 3;
    gbc.insets = new Insets(0, 0, 5, 5);
    gbc.fill = GridBagConstraints.BOTH;
    gbc.anchor = GridBagConstraints.WEST;
    panelLayout.setConstraints(choicesPanel, gbc);
    add(choicesPanel);
    
    gbc.fill = GridBagConstraints.NONE;
    gbc.anchor = GridBagConstraints.CENTER;
    panelLayout.setConstraints(buttonPanel, gbc);
    add(buttonPanel);

    gbc.fill = GridBagConstraints.BOTH;
    gbc.anchor = GridBagConstraints.EAST;    
    panelLayout.setConstraints(chosenPanel, gbc);
    add(chosenPanel);
  }

  /**
   * handles ActionEvents from checkboxes and add/remove buttons.
   */
  @Override
  public void actionPerformed(ActionEvent ae) {
    Object source = ae.getSource();
    Object [] tempSelection;
    if (source.equals(addButton)) {
      tempSelection = choicesAvailable.getSelectedValues();
      if (tempSelection.length > 0) {
	selectedValues = tempSelection;
	fireCollectionChangeEvent();
      }
    } else if (source.equals(removeButton)) {
      tempSelection = attrsChosen.getSelectedRowValues();
      if (tempSelection.length > 0){
	selectedValues = tempSelection;
	fireCollectionChangeEvent();
      }
    }

  }

  void resetLists(DefaultListModel model, LayoutTableModel tableModel) {
    choicesAvailable.setModel(model);
    attrsChosen.setModel(tableModel);
    selectedValues = null;
  }

  /**
   * @undocumented
   */
  void addCollectionListener(CollectionListener collectionListener) {
    collectionListeners.addElement(collectionListener); 
  }

  /**
   * @undocumented
   */
  void removeCollectionListener(CollectionListener collectionListener) {
    collectionListeners.removeElement(collectionListener); 
  }

  AttributeDisplayLayout getResults(AttributeDisplayLayout adl) {
    Vector attributes = ((LayoutTableModel)attrsChosen.getModel()).getLayouts();
    if (selectedValues != null || selectedValues.length != 0 ) {
      if (selectedValues[0] instanceof LayoutStructure) {//remove
	for (int i = 0; i<selectedValues.length; i++) 
	  attributes.removeElement(selectedValues[i]);
      } else { //add
	for (int i = 0; i<selectedValues.length; i++) {
	  Object attributeKey = selectedValues[i];
	  Object newLayoutStructure = editor.createLayoutStructure(attributeKey);
	  attributes.addElement(newLayoutStructure);
	}
      }
    }
    adl.setRows(attributes);
    adl.setGlobalLayout(globalLayout);
    return adl;
  }
  /**
   * @undocumented
   */
  protected void fireCollectionChangeEvent() {
    int listenerCount;
    Vector listeners = null;
    synchronized (collectionListeners) {
      listenerCount = collectionListeners.size();
      if (listenerCount != 0)
	listeners = (Vector)collectionListeners.clone();
    }
    if (listenerCount != 0) {
      CollectionEvent collectionEvent = new CollectionEvent(this);
      for (int i = 0; i<listenerCount; i++)
	((CollectionListener)listeners.elementAt(i)).
	  collectionChanged(collectionEvent);
    }
  }

}
