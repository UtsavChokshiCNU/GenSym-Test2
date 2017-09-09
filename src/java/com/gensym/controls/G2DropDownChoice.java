/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2DropDownChoice.java
 *
 */

package com.gensym.controls;

import java.awt.*;
import java.awt.event.*;
import java.util.Vector;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.util.UnexpectedException;
import com.gensym.types.G2SyntaxException;
import com.gensym.types.SymbolType;
import com.gensym.beansruntime.StringVector;
import com.gensym.dlgevent.ObjectUpdateListener;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.dlgevent.ObjectChangeListener;
import com.gensym.dlgevent.ObjectChangeEvent;

import java.io.IOException;

/** The G2DropDownChoice allows an end user to choose one of an
 * enumerated set of elements.  It is also sometimes called a
 * drop-down list, or in AWT a "choice".  The set of choices are
 * represented by a set of string (actually a Vector).  These strings
 * are parsed into corresponding Objects in a manner governed by
 * the fieldType property.  This allows the G2DropDownChoice to
 * be any homogenous finite enumeration of Integers, Symbols, Strings,
 * etc.
 *
 * @see com.gensym.types.G2Type
 * @see com.gensym.controls.FieldType.
 */
public class G2DropDownChoice extends Choice implements ItemListener, ObjectUpdateListener,
  AttributeEditor, MouseListener
{
  /*
   * Allow deserialization 
   */
  static final long serialVersionUID = -3550767925418401095L;
  
  private java.util.Vector listeners = null;
  private String attributeName = "";
  private Symbol attributeSymbol = null;
  private String defaultContents = "";
  private FieldType fieldType = new FieldType();
  private StringVector choices = new StringVector();
  private boolean nextChangeIsProbablyFromUI = false;
  private Symbol initializationAttribute = null;

  /** Contructor for this bean
  */ 
  public G2DropDownChoice()
  {
    StringVector newChoices = new StringVector ();
    newChoices.addElement ("\"Choice 0\"");
    setChoices (newChoices);
    addItemListener(this);
    addMouseListener(this);
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

  /** Sets the name of the G2 Item attribute which this bean is
   * storing from a Symbol.
   * @see com.gensym.util.Symbol
   */
  @Override
  public void setAttribute(Symbol symbol)
  {
    attributeSymbol = symbol;
    attributeName = symbol.toString();
  }

  /** Gets a Vector of strings, that contains the current 
   * choices presented by this G2DropDownChoice 
   */
  public StringVector getChoices()
  {
    return choices;
  }

  /** Sets the list of possible values for this bean.
   * @param newChoices, a vector of Stings.
   */
  public void setChoices(StringVector newChoices)
  {
    int size = newChoices.size();
    removeAll();
    for (int i = 0; i<size ; i++)
      addItem((String)newChoices.elementAt(i));
  }

  /**
   * @deprecated
   * @undocumented
   */
  public void initalizeChoices(ObjectUpdateEvent e){
    initializeChoices(e);
  }

  /** Initializes the choices of this G2DropDownChoice with the contents of an attribute of a G2 item.
   * @see com.gensym.controls.G2DropDownChoice#getInitializationAttribute
   */
  public void initializeChoices(ObjectUpdateEvent e){
    String selection = getSelectedItem();
    Symbol attribute = initializationAttribute;
    if (attribute == null)
      attribute = attributeSymbol;
    Object updateValue = e.getUpdatedObject();
    if ((updateValue instanceof Structure) && (attribute != null)){
      Object values = ((Structure)updateValue).getAttributeValue(attribute, null);
      if ((values != null) && (values instanceof Vector)){
	removeAll();
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
	  select(index);	
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
    if (fieldType.getType() instanceof SymbolType){
      StringVector newChoices = new StringVector();
      for (int i=0; i<choices.size(); i++)
	newChoices.addElement(choices.elementAt(i));
      setChoices(newChoices);//force upper case
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
        if (nextChangeIsProbablyFromUI)
	  {
	    try {
	      Object object = fieldType.stringToObject(getSelectedItem());
	      if (object != null)
		fireObjectChange(object);
	    } catch (G2SyntaxException syntaxException)
	      {
		System.out.println("UnexpectedException");
		syntaxException.printStackTrace();
	      }
	    catch (IOException ioException)
	      {
		System.out.println("UnexpectedException");
		ioException.printStackTrace();
	      }
	    nextChangeIsProbablyFromUI = false;
          }
      }
  } 


  /** listener method - do not call.
   * @undocumented.
   */
  @Override
  public void mouseEntered(MouseEvent e)
  {
  }
  
  /** listener method - do not call.
   * @undocumented.
   */
  @Override
  public void mouseExited(MouseEvent e)
  {
  }
  
  /** listener method - do not call.
   * @undocumented.
   */
  @Override
  public void mousePressed(MouseEvent e)
  {
    nextChangeIsProbablyFromUI = true;
  }

  /** listener method - do not call.
   * @undocumented.
   */
  @Override
  public void mouseClicked(MouseEvent e)
  {
  }

  /** listener method - do not call.
   * @undocumented.
   */
  @Override
  public void mouseReleased(MouseEvent e)
  {
    // Exception ex = new Exception();
    // ex.printStackTrace();
    nextChangeIsProbablyFromUI = true;
  }


  /** This method implements the ObjectUpdateListener interface.
   * When this method is called the choice in the G2DropDownChoice is changed 
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
      select(fieldType.objectToString(fieldValue));
    } catch (IOException ioException)
      {
	throw new UnexpectedException(ioException);
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

  @Override
  public synchronized void add(String item){
    addItem(item);
  }

  @Override
  public synchronized void addItem(String item){
    if (fieldType.getType() instanceof SymbolType)
      item = item.toUpperCase();
    choices.addElement(item);
    super.addItem(item);
  }

  @Override
  public synchronized void insert(String item, int index){
    if (choices.size() >= index)
      choices.insertElementAt(item, index);
    else
      choices.addElement(item);
    super.insert(item, index);
  }

  @Override
  public synchronized void remove(String item){
    choices.removeElement(item);
    super.remove(item);
  }

  @Override
  public synchronized void remove(int position){
    if (choices.size() > position)
      choices.removeElementAt(position);
    super.remove(position);
  }

  @Override
  public synchronized void removeAll(){
    choices.removeAllElements();
    super.removeAll();
  }


}
