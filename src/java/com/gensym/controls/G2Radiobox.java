/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2Radiobox.java
 *
 */


package com.gensym.controls;

import java.awt.*;
import java.awt.event.*;
import java.util.Vector;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.beansruntime.StringVector;
import com.gensym.dlgevent.ObjectUpdateListener;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.dlgevent.ObjectChangeListener;
import com.gensym.dlgevent.ObjectChangeEvent;
import com.gensym.types.G2SyntaxException;
import com.gensym.util.UnexpectedException;
import java.io.IOException;

/** The G2Radiobox allows an end user to choose one of an
 * finite set of choices. The set of choices are
 * represented by a Vector of Strings.  These strings
 * are parsed into corresponding Objects in a manner governed by
 * the fieldType property.  This allows the G2RadioBox to
 * be any homogenous finite enumeration of Integers, Symbols, Strings,
 * etc.
 *
 * @see com.gensym.types.G2Type
 * @see com.gensym.controls.FieldType.
 */

public class G2Radiobox extends Panel
           implements ItemListener, ObjectUpdateListener
{
  /*
   * Allow deserialization
   */
  static final long serialVersionUID = -815752020522368726L;

  private java.util.Vector listeners    = null;
  private String        attributeName   = "";
  private Symbol        attributeSymbol = null;
  private String        defaultContents = new String("");
  private Integer       lookupDefault   = new Integer(123456);
  private CheckboxGroup cbg             = new CheckboxGroup();
  private int           rows            = 3;
  private int           columns         = 1;
  private Vector        checkboxes      = new Vector();
  private StringVector  members         = null;
  private StringVector  labels          = null;
  private FieldType fieldType = new FieldType("Symbol");
    /* warning: volatile fields */
  private volatile boolean inhibitChangePropagation = false;
  private volatile boolean inhibitUpdatePropagation = false;
  private int     updateCount        = 0;
  private Insets insets;
  /** Contructor for this bean
  */ 
  public G2Radiobox()
  {  
     setLayout (new GridLayout (rows, columns));
     StringVector defaultMembers = new StringVector();
     defaultMembers.addElement("CHOICE0");
     defaultMembers.addElement("CHOICE1");
     defaultMembers.addElement("CHOICE2");
     setMembers(defaultMembers);
     StringVector defaultLabels = new StringVector();
     defaultLabels.addElement("Choice 0");
     defaultLabels.addElement("Choice 1");
     defaultLabels.addElement("Choice 2");
     setLabels(defaultLabels);
  }

  public StringVector getLabels(){
    return labels;
  }

  public void setLabels(StringVector newLabels){
    labels = newLabels;
    adjustMembers();
  }

  /** Gets the members (names of the choices) of this radio box
  */
  public StringVector getMembers()
  {  
    return members;
  }

  /** Sets the members (names of the choices) of this radio box
  */
  public void setMembers(StringVector newMembers)
  {
    members = newMembers;
    adjustMembers();
  }

  /** Rebuilds the radiobox based on new members
  */
  private void adjustMembers ()
  {
      int length = members.size();
      removeAll();
      checkboxes.removeAllElements();

      for (int i = 0; i < length; i++)
      {
	Checkbox cb0;
	if ((labels == null) || (i > labels.size() - 1))
          cb0 = new Checkbox((String)members.elementAt(i), false, cbg);
	else
	  cb0 = new Checkbox((String)labels.elementAt(i), false, cbg);
	cb0.addItemListener (this);
	add (cb0);
	checkboxes.addElement(cb0);
      }
      validate();
  }

  /** Gets the name of the G2 Item attribute which this bean is
   * storing as a Symbol.
   * @see com.gensym.util.Symbol
   */ 
 public Symbol getAttribute()
  {
    return attributeSymbol;
  }

  /** Sets the name of the G2 Item attribute which this bean is
   * storing from a Symbol.
   * @see com.gensym.util.Symbol
   */
  public void setAttribute(Symbol symbol)
  {
    attributeSymbol = symbol;
    attributeName = symbol.toString();
  }

  /** Gets the default contents of this bean
  */
  public String getDefaultContents()
  {
     return defaultContents;
  }

  /** Sets the default contents of this bean
  */
  public void setDefaultContents (String item)
  {
     defaultContents = item;
  }

  /** Gets the number of rows by which the radio buttons
  * are aligned
  */
  public int getRows()
  {
     return rows;
  }

  /** Sets the number of rows by which the radio buttons
  * are aligned
  */
  public void setRows (int newRows)
  {
     rows = newRows;
     setLayout (new GridLayout (rows, columns));
     validate();
  }

  /** Gets the number of columns by which the radio buttons
  * are aligned
  */
  public int getColumns()
  {
     return columns;
  }

  /** Sets the number of columns by which the radio buttons
  * are aligned
  */
  public void setColumns (int newColumns)
  {
     columns = newColumns;
     setLayout (new GridLayout (rows, columns));
     validate();
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

  /** This method responds to an ItemEvent (from this bean) by firing an ObjectChange event
  * to this bean's listeners
  */
  @Override
  public void itemStateChanged(ItemEvent event)
  {
    Object source = event.getSource();
    
    try {
      Checkbox cb = (Checkbox)source;
      int index = -1;
      for (int i=0; i<checkboxes.size(); i++){
	if (cb.equals(checkboxes.elementAt(i))){
	  index = i;
	  break;
	}
      }
      String member;
      if (index >= 0) member = (String)members.elementAt(index);
      else member = defaultContents;
      Object object = fieldType.stringToObject(member);
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
  } 


  /**  This method responds to objectUpdateEvents by setting the current
  * radio button of the bean and updating the G2 item attribute it is storing
  */
  @Override
  public synchronized void objectUpdated(ObjectUpdateEvent e)
  {
    Object fieldValue = e.getUpdatedValue(attributeSymbol, defaultContents);
    setState (fieldValue.toString());
  }

  public Object getState(){
    try{
      Checkbox cb = cbg.getSelectedCheckbox();
      if (cb == null) return null;
      int index = checkboxes.indexOf(cb);
      return fieldType.stringToObject((String)members.elementAt(index));
    }
    catch (G2SyntaxException syntaxException){
      throw new UnexpectedException(syntaxException);
    }
    catch (IOException ioException){
      throw new UnexpectedException(ioException);
    }
  }

  /** Sets the selected radio button based on a string value
  */
  public void setState (String value)
  {
    int index = -1;
     for (int i = 0; i < members.size(); i++)
     {
       String val = (String)members.elementAt(i);
       if (fieldType.getTypeName().equals("Symbol"))
	 val = val.toUpperCase();
       if (value.equals (val)){
	 index = i;
	 break;
       }
     }
     if (index >= 0){
       Checkbox  cb = (Checkbox)checkboxes.elementAt(index);
       cb.setState (true);
     }
     //what if there is no match?
  }
  
  /** Adds a listener to this bean for ObjectChangeEvents
  */
  public synchronized void addObjectChangeListener (ObjectChangeListener
						      listener)
  {
    if (listeners == null) {
      listeners = new java.util.Vector();
    }
    listeners.addElement(listener);
  }
  
  /** Removes a listener from this bean for ObjectChangeEvents
  */
  public synchronized void removeObjectChangeListener(ObjectChangeListener
							listener) 
  {
    if (listeners == null) {
      return;
    }
    listeners.removeElement(listener);
  }

 
  /**  Invokes the ObjectChanged method on each of this beans ObjectChange
  * listeners
  */ 
  public void fireObjectChange(Object newObject)
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
  public void setEnabled(boolean enabled){
    super.setEnabled(enabled);
    if (checkboxes == null) return;
    for (int i= 0; i<checkboxes.size(); i++){
      Checkbox cb = (Checkbox)checkboxes.elementAt(i);
      cb.setEnabled(enabled);
    }
  }

  @Override
  public Insets getInsets(){
    if (insets == null)
      return super.getInsets();
    else return insets;
  }

  public void setInsets(Insets insets){
    this.insets = insets;
  }

}
