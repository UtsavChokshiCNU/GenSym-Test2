/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ItemPoxyCustomizer.java
 *
 */

package com.gensym.controls;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.beans.Customizer;
import java.util.Vector;
import java.awt.*;
import java.awt.event.*;
import com.gensym.beansruntime.StringVectorEditor;
import com.gensym.beansruntime.StringVector;

/** This class is a customizer for ItemProxy
 */

public class ItemProxyCustomizer extends Panel implements Customizer,
             TextListener, ItemListener, MouseListener, PropertyChangeListener,
             WindowListener
{
  private ItemProxy itemProxy;
  private Vector    propListeners = new Vector();
  private TextField nameField     = new TextField();
  private Canvas    attrCanvas    = new Canvas();
  private Choice    uploadChoice  = new Choice();
  private Label     nameLabel     = new Label("name   ");
  private Label     attrLabel     = new Label("attributes   ");
  private Label     uploadLabel   = new Label("autoUpload   ");
  private SymbolVectorEditor sve  = new SymbolVectorEditor();
  private boolean   launch        = false;

  /** Constructor for this bean
  */
  public ItemProxyCustomizer()
  {
      setLayout (new GridLayout(3, 2));

      nameLabel.setAlignment(Label.RIGHT);
      attrLabel.setAlignment(Label.RIGHT);
      uploadLabel.setAlignment(Label.RIGHT);

      add(nameLabel);
      add(nameField);
      add(attrLabel);
      add(attrCanvas);
      add(uploadLabel);
      add(uploadChoice);

      uploadChoice.addItem("True");
      uploadChoice.addItem("False");
  }

  @Override
  public Dimension getPreferredSize()
  {
      return new Dimension(200, 100);
  }

  @Override
  public Insets getInsets()
  {
     return new Insets (10, 10, 10, 10);
  }

  /** Sets the object for this customizer to edit
  */
  @Override
  public void setObject(Object object)
  {
      itemProxy = (ItemProxy)object;
      nameField.setText(itemProxy.getName());
      uploadChoice.select((new Boolean(itemProxy.getAutoUpload())).toString());

      nameField.addTextListener(this);
      uploadChoice.addItemListener(this);
      attrCanvas.addMouseListener(this);
  }

  /** Adds a listener for Property Change events to this bean
   */
  @Override
  public void addPropertyChangeListener(PropertyChangeListener listener)
  {
      propListeners.addElement(listener);
  }
  
  /** Removes a listener for Property Change events from this bean
   */
  @Override
  public void removePropertyChangeListener(PropertyChangeListener listener)
  {
      propListeners.removeElement(listener);
  }

  /** Sends PropertyChangeEvents to all the ActionListeners
   * for this bean
   */
  public void firePropertyChange()
  {
      int size = propListeners.size();

      PropertyChangeEvent event = new PropertyChangeEvent(this, "", null, null); 

      for (int i=0; i < size; i++)
      {
          ((PropertyChangeListener)(propListeners.elementAt(i))).propertyChange(event);
      }
  }

  /** Sets the name field to a new value
  */
  @Override
  public void textValueChanged(TextEvent event)
  {
      itemProxy.setName((nameField.getText()));
      firePropertyChange();

  }

  /** Sets the autoUpload field to a new value
  */
  @Override
  public void itemStateChanged(ItemEvent event)
  {
      Boolean state = new Boolean((uploadChoice.getSelectedItem()));
      itemProxy.setAutoUpload(state.booleanValue());
      firePropertyChange();
  }

  @Override
  public void mouseClicked (MouseEvent event)
  { 
      if (!launch)
      {
         sve.setValue(itemProxy.getAttributes());
         sve.addPropertyChangeListener(this);
         Frame frame = new Frame("Attributes");
         frame.setLocation(getLocation().x, getLocation().y);
         frame.setBackground(Color.lightGray);
         frame.addWindowListener(this);
         frame.add(sve);
         frame.pack();
         launch = true;
         frame.show();
      }
  }

  @Override
  public void mousePressed (MouseEvent event)
  {
  }

  @Override
  public void mouseReleased (MouseEvent event)
  {
  }

  @Override
  public void mouseEntered (MouseEvent event)
  {
  }

  @Override
  public void mouseExited (MouseEvent event)
  {
  }

  @Override
  public void propertyChange (PropertyChangeEvent event)
  {
      itemProxy.setAttributes((SymbolVector)(sve.getValue()));
      firePropertyChange();
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
      launch = false;
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
