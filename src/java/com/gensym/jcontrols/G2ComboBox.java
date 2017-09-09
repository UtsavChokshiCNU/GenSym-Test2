/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2ComboBox.java
 *
 */

package com.gensym.jcontrols;

import javax.swing.JComboBox;
import javax.swing.ComboBoxModel;
import java.awt.*;
import java.beans.Beans;
import java.awt.event.*;
import java.util.Vector;
import com.gensym.message.Trace;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.util.UnexpectedException;
import com.gensym.types.G2SyntaxException;
import com.gensym.beansruntime.StringVector;
import com.gensym.dlg.WarningDialog;
import com.gensym.dlgevent.ObjectUpdateListener;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.dlgevent.ObjectChangeListener;
import com.gensym.dlgevent.ObjectChangeEvent;
import com.gensym.controls.AttributeEditor;
import com.gensym.controls.FieldType;

import java.io.IOException;

/** The G2ComboBox allows an end user to choose one of an
 * enumerated set of elements.  It is also sometimes called a
 * drop-down list, or in AWT a "choice".  The set of choices are
 * represented by a set of string (actually a Vector).  These strings
 * are parsed into corresponding Objects in a manner governed by
 * the fieldType property.  This allows the G2ComboBox to
 * be any homogenous finite enumeration of Integers, Symbols, Strings,
 * etc.
 *
 * @see com.gensym.types.G2Type
 * @see com.gensym.controls.FieldType.
 */
public class G2ComboBox extends JComboBox implements ItemListener, ObjectUpdateListener,
  AttributeEditor /*, ListDataListener */
{
  /*
   * Allow deserialization 
   */
  static final long serialVersionUID = 2L;
  
  private java.util.Vector listeners = null;
  private String attributeName = "";
  private Symbol attributeSymbol = null;
  private String defaultContents = "";
  private FieldType fieldType = new FieldType();
  private StringVector choices = new StringVector();
  private boolean sendNextChangeToG2 = true;
  private Symbol initializationAttribute = null;
  private boolean warnOnBadSyntax = true;

  private ComboBoxModel model;

  /** Contructor for this bean
  */ 
  public G2ComboBox()
  {
    StringVector newChoices = new StringVector ();
    model = (ComboBoxModel)getModel();
    newChoices.addElement ("\"Choice 0\"");
    setChoices (newChoices);
    //addListDataListener(this);
    addItemListener(this);
  }

   /** Gets the name of the G2 Item attribute which this bean is
   * storing as a Symbol.
   * @see com.gensym.util.Symbol
   */
  @Override
  public Symbol getAttribute()
  {
    return attributeSymbol;
  }

  @Override
  public void setAttribute(Symbol symbol)
  {
    attributeSymbol = symbol;
    attributeName = symbol.toString();
  }

  /** Sets the name of the G2 Item attribute which this bean is
   * storing from a Symbol.
   * @see com.gensym.util.Symbol
   */
  public StringVector getChoices()
  {
    return choices;
  }

  /** Sets the list of possible values for this bean.
   * @param newChoices, a vector of Strings.
   */
  public void setChoices(StringVector newChoices)
  {
    try {
      sendNextChangeToG2 = false;
      int size = newChoices.size();
      removeAllItems();
      for (int i = 0; i<size ; i++)
	addItem((String)newChoices.elementAt(i));
    } finally {
      sendNextChangeToG2 = true;
    }
  }

  /** Initializes the choices of this G2ComboBox with the contents of an attribute of a G2 item.
   * @see com.gensym.controls.G2ComboBox#getInitializationAttribute
   */
  public void initalizeChoices(ObjectUpdateEvent e){
    // fix this: ensure this is always true
    String selection = (String)getSelectedItem();
    Symbol attribute = initializationAttribute;
    if (attribute == null)
      attribute = attributeSymbol;
    Object updateValue = e.getUpdatedObject();
    if ((updateValue instanceof Structure) && (attribute != null)){
      Object values = ((Structure)updateValue).getAttributeValue(attribute, null);
      if ((values != null) && (values instanceof Vector)){
	try {
	  sendNextChangeToG2 = false;
	  removeAllItems();
	  for (int i=0; i<((Vector)values).size(); i++){
	    try{
	      addItem(fieldType.objectToString(((Vector)values).elementAt(i)));
	    }
	    catch(IOException ex){
	      throw new UnexpectedException(ex);
	    }
	  }
	  int index = choices.indexOf(selection);
	  if (index >=0)
	    setSelectedIndex(index);
	} finally {
	  sendNextChangeToG2 = true;
	}
      }
    }
  }

  /** The initializationAttribute property specifies the name of the attribute from which this 
   *  control will be initialized.
   */
  public void setInitializationAttribute(Symbol attribute){
    initializationAttribute = attribute;
  }


  /** The initializationAttribute property specifies the name of the attribute from which this 
   *  control will be initialized.
   */
  public Symbol getInitializationAttribute(){
    return initializationAttribute;
  }

 /** The defaultContents property contains a string which will be
   * used as input if none is received through an ObjectUpdateEvent or 
   * typed in.
   */
  public String getDefaultContents()
  {
    return defaultContents;
  }

 /** The defaultContents property contains a string which will be
   * used as input if none is received through an ObjectUpdateEvent or 
   * typed in.
   */
  public void setDefaultContents (String string)
  {
    defaultContents = string;
  }

  /** The fieldType property controls the transformation of strings
   * into other data types that this field may represent.  All G2 data
   * types (as presented by JavaLink) are supported.
   * @see com.gensym.types.G2Type
   * @see com.gensym.util.Structure
   * @see com.gensym.util.Sequence
   * @see com.gensym.util.Symbol
   */
  public FieldType getFieldType()
  {
    return fieldType;
  }

  /** The fieldType property controls the transformation of strings
   * into other data types that this field may represent.  All G2 data
   * types (as presented by JavaLink) are supported.
   * @see com.gensym.types.G2Type
   * @see com.gensym.util.Structure
   * @see com.gensym.util.Sequence
   * @see com.gensym.util.Symbol
   */
  public void setFieldType(FieldType type)
  {
    fieldType = type;
  }

  /** The warnOnBadSyntax property controls whether a modal dialog.
   *  will be shown for type-in that does not match the specified
   *  fieldType property.
   */
  public boolean getWarnOnBadSyntax()
  {
    return warnOnBadSyntax;
  }

  /** The warnOnBadSyntax property controls whether a modal dialog.
   *  will be shown for type-in that does not match the specified
   *  fieldType property.
   */
  public void setWarnOnBadSyntax(boolean warn)
  {
    warnOnBadSyntax = warn;
  }

  private void warningDialog(String message)
  {
    if (!Beans.isDesignTime())
      {
	WarningDialog dialog 
	  = new WarningDialog(null,"",true,message,null);
	dialog.setVisible (true);
      }
  }

  /** listener method - do not call.
   * @undocumented.
   */
  @Override
  public void itemStateChanged(ItemEvent event)
  {
    Object source = event.getSource();
    
    if (source == this)
      {
        if (sendNextChangeToG2)
	  {
	    try {
	      Object selectedItem = getSelectedItem();
	      if (selectedItem != null && (event.getStateChange() == ItemEvent.SELECTED)) {
		Object object = fieldType.stringToObject((String)selectedItem);
		fireObjectChange(object);
	      }
	    } catch (G2SyntaxException syntaxException)
	      {
		Trace.exception(syntaxException);
		if (warnOnBadSyntax)
		  warningDialog(syntaxException.getMessage());
		syntaxException.printStackTrace();
	      }
	    catch (IOException ioException)
	      {
		throw new UnexpectedException(ioException);
	      }
          }
      }
  } 

  /** This method implements the ObjectUpdateListener interface.
   * When this method is called the choice in the G2ComboBox is changed 
   * The fieldType property governs the translation of the changed datum
   * into a string which is used to select a new choice.
   * @see com.gensym.controls.G2TextField#setFieldType
   * @see java.awt.Choice#select
   */ 
  @Override
  public void objectUpdated(ObjectUpdateEvent e)
  {
    Object fieldValue = e.getUpdatedValue(attributeSymbol,defaultContents);

    try {
      sendNextChangeToG2 = false;
      setSelectedItem(fieldType.objectToString(fieldValue));
    } catch (IOException ioException) {
      throw new UnexpectedException(ioException);
    } finally {
      sendNextChangeToG2 = true;
    }
  } 

  /** Adds a listener to this bean for ObjectChangeEvents.
  */
  @Override
  public synchronized void addObjectChangeListener (ObjectChangeListener
						      listener)
  {
    if (listeners == null)
    {
      listeners = new java.util.Vector();
    }
    listeners.addElement(listener);
  }
  
  /** Removes a listener from this bean for ObjectChangeEvents.
  */
  @Override
  public synchronized void removeObjectChangeListener(ObjectChangeListener
							listener) 
  {
    if (listeners == null)
    {
      return;
    }
    listeners.removeElement(listener);
  }

  /**  Invokes the ObjectChanged method on each of this beans ObjectChange
  * listeners
  */ 
  private void fireObjectChange(Object newObject)
  {
    java.util.Vector targets;
    synchronized (this)
    {
      if (listeners == null) 
      {
	return;
      }
      targets = (java.util.Vector) listeners.clone();
    }
    
    ObjectChangeEvent evt;
    if (attributeName.equals(""))
       evt = new ObjectChangeEvent(this, newObject);
    else
       evt = new ObjectChangeEvent(this, newObject, attributeName);

    for (int i = 0; i < targets.size(); i++)
    {
      ObjectChangeListener target = (ObjectChangeListener)targets.elementAt(i);
      target.objectChanged(evt);
    }
  }

  public synchronized void add(String item){
    addItem(item);
  }

  public synchronized void addItem(String item){
    choices.addElement(item);
    super.addItem(item);
  }

  public synchronized void insert(String item, int index){
    if (choices.size() >= index)
      choices.insertElementAt(item, index);
    else
      choices.addElement(item);
    super.insertItemAt(item, index);
  }

  public synchronized void removeItem(String item){
    choices.removeElement(item);
    super.removeItem(item);
  }

  @Override
  public synchronized void removeItemAt(int position){
    if (choices.size() > position)
      choices.removeElementAt(position);
    super.removeItemAt(position);
  }

//   public synchronized void removeAll(){
//     removeAllItems();
//   }

  @Override
  public synchronized void removeAllItems(){
    choices.removeAllElements();
    if (model.getSize() > 0)
      super.removeAllItems();
  }


}
