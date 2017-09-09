/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	Layout Dialog - LayoutDialog.java
 *
 *
 *   Modifications:
 *
 */

package com.gensym.beaneditor;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import com.gensym.dlgruntime.PageGroup;

/** This class creates a dialog which gathers data used to define a
* new PageGroup
*/
class GroupDialog extends Dialog implements ActionListener, WindowListener
{
  private PageGroup group         = null;
  private Frame     frame         = null;
  private Panel     panel         = new Panel();
  private List      list          = new List();
  private TextField nameField     = new TextField();  
  private TextField resourceField = new TextField();
  private TextField heightField   = new TextField(8);  
  private TextField widthField    = new TextField(8);
  private Button    addButton     = new Button("Add"); 
  private Button    removeButton  = new Button("Remove");
  private Button    saveButton    = new Button("Save");
  private Button    exitButton    = new Button("Exit");

  /** Contructor for this class
   */
  public GroupDialog(Frame frame, PageGroup group, int x, int y)
  {	        
    super(frame, "Page Group", true);

    this.group = group;
    this.frame = frame;

    GridBagLayout layout = new GridBagLayout();
    setLayout(layout);

    GridBagConstraints constraints = new GridBagConstraints();
    constraints.fill = GridBagConstraints.NONE;
    constraints.insets = new Insets (0, 5, 0, 5);
    constraints.gridwidth = GridBagConstraints.REMAINDER;

    Label widthLabel  = new Label("Width:");
    Label heightLabel = new Label("Height:");

    widthLabel.setAlignment(Label.LEFT);
    heightLabel.setAlignment(Label.LEFT);

    panel.add(widthLabel);    
    panel.add(widthField);
    panel.add(heightLabel);
    panel.add(heightField);

    constraints.anchor = GridBagConstraints.WEST;
    layout.setConstraints(panel, constraints);
    add(panel);

    constraints.weightx = 1;

    Label resourceLabel = new Label("Pages:");
    resourceLabel.setAlignment(Label.LEFT);
    // This label will fill the remainder of the row
    constraints.gridwidth = GridBagConstraints.REMAINDER;
    constraints.anchor    = GridBagConstraints.CENTER;
    constraints.fill      = GridBagConstraints.HORIZONTAL;
    layout.setConstraints(resourceLabel, constraints);
    add(resourceLabel);

    // Setup the list 
    list.setMultipleMode(true);
    constraints.weighty = 1;
    constraints.fill = GridBagConstraints.BOTH;
    constraints.gridheight = 4;
    constraints.gridwidth = GridBagConstraints.RELATIVE;
    layout.setConstraints(list, constraints);
    add(list);

    // Setup the text fields and labels
    constraints.fill = GridBagConstraints.HORIZONTAL;
    constraints.gridheight = 1;
    constraints.weighty = 0;
    constraints.gridwidth = GridBagConstraints.REMAINDER;

    Label nameFieldLabel = new Label("Tab Name:");
    layout.setConstraints(nameFieldLabel, constraints);
    add(nameFieldLabel);

    layout.setConstraints(nameField, constraints);
    add(nameField);

    Label resourceFieldLabel = new Label("Resource:");
    layout.setConstraints(resourceFieldLabel, constraints);
    add(resourceFieldLabel);

    constraints.anchor = GridBagConstraints.NORTH;
    layout.setConstraints(resourceField, constraints);
    add(resourceField);

    // Add the buttons
    constraints.insets = new Insets (5, 5, 5, 5);

    constraints.gridwidth = 1;
    layout.setConstraints(addButton, constraints);
    add(addButton);

    constraints.gridwidth = 1;
    layout.setConstraints(removeButton, constraints);
    add(removeButton);

    constraints.gridwidth = GridBagConstraints.RELATIVE;
    layout.setConstraints(saveButton, constraints);
    add(saveButton);

    constraints.gridwidth = GridBagConstraints.REMAINDER;
    layout.setConstraints(exitButton, constraints);
    add(exitButton);
            
    exitButton.addActionListener(this);
    addButton.addActionListener(this);
    removeButton.addActionListener(this);
    saveButton.addActionListener(this);
          
    pack();
    setLocation(x - getSize().width/2, y - getSize().height/2);

    addWindowListener(this);

    // Check to see if the URL is null
    if (group.getLocation() == null)
      {
	URLDialog urld = new URLDialog(frame, x, y);
	group.setLocation(urld.getURL());
      }

    widthField.setText("" + group.getWidth());
    heightField.setText("" + group.getHeight());

    String[] tabNames = group.getTabNames(); 
    String[] pages    = group.getPages();

    for(int i=0; i < tabNames.length; i++)
      {
	list.add(tabNames[i] + "  " + pages[i]);
      }
         
    // Show the dialog

    if (group.getLocation() != null)
      setVisible(true);
    else
      dispose();
  }

  // Action event

  @Override
  public void actionPerformed (ActionEvent e)
  { 
    Object source = e.getSource();

    if (source.equals(addButton))
      {
	if ((!(nameField.getText()).equals("")) ||
	    (!(resourceField.getText()).equals("")) )
	  {
	    list.add(nameField.getText() + "  " + resourceField.getText());
	    nameField.setText("");
	    resourceField.setText("");
	  }
      }
    else if (source.equals(removeButton))
      {
	int[] items = list.getSelectedIndexes();

	while (items.length > 0)
	  {
	    list.delItem(items[0]);
	    items = list.getSelectedIndexes();
	  }

      }
    else if (source.equals(saveButton))
      {
	FileDialog fd = new FileDialog(frame, "Save", FileDialog.SAVE);

	fd.setDirectory (System.getProperty("user.dir"));        
	fd.setFile ("temp.grp");
	fd.show();

	String  fname     = fd.getFile();
	String  dname     = fd.getDirectory();

	if (fname != null && dname != null)
	  {
	    File file = new File(dname, fname);

	    group.setWidth((new Integer(widthField.getText())).intValue());
	    group.setHeight((new Integer(heightField.getText())).intValue());

	    String[] strings = list.getItems();

	    for (int i=0; i < strings.length; i++)
	      {
		int end = strings[i].indexOf(32);  // find the first space

		String tabName  = strings[i].substring(0, end - 1);
		String resource = strings[i].substring(end + 2);

		group.addPage (tabName, resource);             
	      }

	    try
	      {    
		FileOutputStream   fos = new FileOutputStream(file);
		ObjectOutputStream oos = new ObjectOutputStream(fos);

		oos.writeObject(group);            

		oos.close();
		fos.close();
	      }
	    catch (Exception ex)
	      {
	      } 
	  }
      } 
    else
      dispose();
  }
   
  // Window events

  @Override
  public void windowOpened(WindowEvent e)
  {
  }

  @Override
  public void windowClosing(WindowEvent e)
  {
    e.getWindow().dispose();
  }

  @Override
  public void windowClosed(WindowEvent e)
  {
  }

  @Override
  public void windowIconified(WindowEvent e)
  {
  }

  @Override
  public void windowDeiconified(WindowEvent e)
  {
  }

  @Override
  public void windowActivated(WindowEvent e)
  {
  }

  @Override
  public void windowDeactivated(WindowEvent e)
  {
  }


}

