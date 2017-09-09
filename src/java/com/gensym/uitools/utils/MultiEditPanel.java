package com.gensym.uitools.utils;

import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.JLabel;
import javax.swing.JButton;
import java.awt.Insets;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;

import java.awt.event.FocusEvent;
import java.awt.event.KeyListener;
import java.awt.AWTEvent;

/**
 * A panel for laying out rows of labeled textfields and optional edit buttons.
 * <p>
 * Sample Code: (creates a panel for getting a class name and an item name.
 * the class name row has a 'browser' button that could be used to launch a 
 * class browser that would set the class name textfield's value upon exit).
 * <p>
 * <code>
 *
 * <li>private static String[] mainPanelLabels = {"Class Name", "Item Name"};
 * <li>private static String[] mainPanelInitialValues = {"OBJECT",""};
 * <li>JButton classBrowserButton = new JButton("browse...");
 * <li>private JButton[] buttons = {classBrowserButton, null};
 * <li>MultiEditPanel mep = new MultiEditPanel(mainPanelLabels, mainPanelInitialValues, buttons);<li>
 *<p>
 * <li>classBrowserTextField = mep.getTextField(0);
 * <li>classBrowserButton.addActionListener(this);
 *<p>
 * </code>
 * <p>
 * All arrays passed in should be of the same length.
 */
public class MultiEditPanel extends JPanel {

  JTextField[] textControls;
  private static final Insets stdInsets = new Insets (0, 10, 0, 10);
  private static final Insets menuInsets = new Insets (0, 5, 0, 10);
  int numEdits;

  void setColumns (int numCols) {
    for (int i=0; i<textControls.length; i++)
      textControls[i].setColumns (numCols);
  }

  /**
   * @param fieldIndex The index of the desired textField 
   * @param value The new String to be set into the indicated JTextField
   */
  public void setTextFieldValue(int fieldIndex, String value)
  {
    JTextField control = textControls[fieldIndex];
    control.setText(value);
  }

  /**
   * @return A String array containing the values of each text field.
   */
  public String[] getResults () {
    JTextField[] controls = textControls;
    String[] results = new String[numEdits];
    for (int i=0; i<numEdits; i++)
      results[i] = controls[i].getText ();
    return results;
  }
  
  private void createMultiEditPanel (String[] labels,
				     String[] initialValues,
				     int textFieldColumns,
				     JButton[] buttons){

    Insets firstLabelInsets = new Insets (10, 0, 5, 0);
    Insets labelInsets = new Insets (5, 0, 5, 0);
    Insets firstTextInsets = new Insets (10, 10, 5, 0);
    Insets textInsets = new Insets (5, 10, 5, 0);

    numEdits = labels.length;
    GridBagLayout gbl = new GridBagLayout ();
    GridBagConstraints gbc = new GridBagConstraints ();
    gbc.insets = new Insets (5, 0, 5, 0);
    gbc.anchor = GridBagConstraints.CENTER;
    gbc.weighty = 0.5;
    textControls = new JTextField[numEdits];

    setLayout (gbl);
    for (int i=0; i<numEdits; i++) {
      JButton button = buttons[i];
      
      if (i == 0)
	gbc.insets = firstLabelInsets;
      else
	gbc.insets = labelInsets;
      JLabel l = new JLabel (labels[i], JLabel.RIGHT);
      if (i == 0)
	gbc.insets = firstTextInsets;
      else
	gbc.insets = textInsets;
      JTextField t = new AutoSelectingTextField (initialValues[i], textFieldColumns);
      t.setMargin(menuInsets);

      int numChars = initialValues[i].length ();
      textControls[i] = t;

      if (button == null) {
	// add Label
	gbc.gridwidth = 2;
	gbc.weightx = 0.0;
	gbc.fill = GridBagConstraints.NONE;
	gbc.anchor = GridBagConstraints.EAST;
	gbl.setConstraints (l, gbc);
	add (l);
	
	// add TextField
	gbc.weightx = 1.0;
	gbc.gridwidth = GridBagConstraints.REMAINDER;
	gbc.fill = GridBagConstraints.HORIZONTAL;
	gbc.anchor = GridBagConstraints.WEST;
	gbl.setConstraints (t, gbc);
	add (t);
      } else {
	// add Label
	gbc.gridwidth = 3;
	gbc.weightx = 0.0;
	gbc.fill = GridBagConstraints.NONE;
	gbc.anchor = GridBagConstraints.EAST;
	gbl.setConstraints (l, gbc);
	add (l);
	
	// add TextField
	gbc.weightx = 1.0;
	gbc.gridwidth = GridBagConstraints.RELATIVE;
	gbc.fill = GridBagConstraints.HORIZONTAL;
	gbc.anchor = GridBagConstraints.WEST;
	gbl.setConstraints (t, gbc);
	add (t);

	// add Button
	gbc.gridwidth = GridBagConstraints.REMAINDER;
	gbc.weightx = 0.0;
	gbc.anchor = GridBagConstraints.EAST;
	gbc.fill = GridBagConstraints.NONE;
	gbl.setConstraints (button, gbc);
	add(button);
      }
    }
  }

  /**
   * @param labels A String array containing the labels for each row
   * @param intialValues A String array containing the initialValues for the 
   * text field that gets created for each row
   * @param textFieldColumns the number of columns for the JTextFields
   * @param buttons An array of buttons for each row.  Not all indexes need
   * have a JButton, but the array should be of the correct length.  The 
   * buttons can be used to launch some kind of browser from which a user could
   * choose a value, such as a class browser tree view for when the given
   * text field is asking for the name of a class.
   */
  public MultiEditPanel (String[] labels,
			 String[] initialValues,
			 int textFieldColumns,
			 JButton[] buttons) {
    createMultiEditPanel(labels, initialValues, textFieldColumns, buttons);
  }

  /**
   * @param labels A String array containing the labels for each row
   * @param intialValues A String array containing the initialValues for the 
   * text field that gets created for each row
   * @param buttons An array of buttons for each row.  Not all indexes need
   * have a JButton, but the array should be of the correct length.  The 
   * buttons can be used to launch some kind of browser from which a user could
   * choose a value, such as a class browser tree view for when the given
   * text field is asking for the name of a class.
   */  
  public MultiEditPanel (String[] labels,
			 String[] initialValues,
			 JButton[] buttons) {
    this(labels, initialValues, 14, buttons);
  }

  /**
   * @return The JTextField that was created at the given index.
   */
  public JTextField getTextField(int index)
  {
    return textControls[index];
  }


  /**
   * @param labels A String array containing the labels for each row
   * @param intialValues A String array containing the initialValues for the 
   * text field that gets created for each row
   * @param textFieldColumns the number of columns for the JTextFields
   */  
  public MultiEditPanel (String[] labels, String[] initialValues, int textFieldColumns) {
    this(labels, initialValues, textFieldColumns, new JButton[labels.length]);
  }

  /**
   * @param labels A String array containing the labels for each row
   * @param intialValues A String array containing the initialValues for the 
   * text field that gets created for each row
   */    
  public MultiEditPanel (String[] labels, String[] initialValues) {
    this(labels, initialValues, 14);
  }

  @Override
  public Insets getInsets () {
    return stdInsets;
  }

  void hookupKeyListener (KeyListener kl) {
    for (int i=0; i<textControls.length; i++)
      textControls[i].addKeyListener (kl);
  }

}

class AutoSelectingTextField extends JTextField {
  AutoSelectingTextField (String initialText, int numColumns) {
    super (initialText, numColumns);
    enableEvents (AWTEvent.FOCUS_EVENT_MASK);
  }
  @Override
  protected void processFocusEvent (FocusEvent e) {
    super.processFocusEvent(e);
    if (!e.isTemporary ()) {
      if (e.getID() == FocusEvent.FOCUS_GAINED) {
	String currentText = getText ();
	select (0, currentText.length ());
      } else
	select (0, 0);
    }
  }

}
