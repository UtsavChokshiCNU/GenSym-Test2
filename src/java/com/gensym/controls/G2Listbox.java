/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2Listbox.java
 *
 */

package com.gensym.controls;

import java.awt.*;
import java.awt.event.*;
import java.beans.*;
import java.io.IOException;
import java.util.Vector;
import com.gensym.util.Deserializer;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.UnexpectedException;
import com.gensym.types.G2SyntaxException;
import com.gensym.types.SymbolType;
import com.gensym.beansruntime.StringVector;
import com.gensym.beansruntime.Enum;
import com.gensym.dlgevent.ObjectUpdateListener;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.dlgevent.ObjectChangeListener;
import com.gensym.dlgevent.ObjectChangeEvent;


/** The G2Listbox is a component that can be used as either a collection list or
 * a selection list.  The behaviour is determined by the listType property.
 * A collection list allows the editing of sets of
 * items represented as java.util.Vector's.  This includes instances
 * of com.gensym.util.Sequence which is a subclass of Vector.  The G2Listbox
 * is used for editing, growing and shrinking the set of objects. 
 * The vector of objects is translated
 * into a set of strings/list-items through the fieldType property. 
 * A selection list allows the editing of a single attribute whose value may be one of
 * a finite list of choices.
 * <p>
 * A G2Listbox configured as a collection list can both send and receive ObjectUpdateEvents 
 * and ObjectChangeEvents.  A G2Listbox configured as a selection list receives ObjectUpdateEvents
 * and sends ObjectChangeEvents.
 * @see java.awt.List
 * @see com.gensym.controls.ObjectUpdateEvent
 * @see com.gensym.controls.ObjectChangeEvent
 * @see com.gensym.controls.FieldType
 */

public class G2Listbox extends List
     implements ItemListener, ObjectChangeListener, ObjectUpdateListener, AttributeEditor
{
  /*
   * Allow deserialization
   */
  static final long serialVersionUID = -4020304664824355938L;

  public final static int COLLECTION = 0;
  public final static int SELECTION = 1;

  private Vector vector;
  private PropertyChangeSupport changes = 
            new PropertyChangeSupport(this);
  private Object previousSelection = null;
  private Integer lookupDefault = new Integer(123456);
  private int prefSizeCount = 0;
  private Formatter formatter = new Formatter();
  private Vector changeListeners = null;
  private Vector updateListeners = null;
  private FieldType fieldType = new FieldType();
  private String attributeName = "";
  private Symbol attributeSymbol = null;
  private Enum listType;
  private StringVector choices = new StringVector();
  private String defaultContents = "";
  private Symbol initializationAttribute = null;
  private String lastSelectionFromObjectUpdated = null;
  /** Contructor for this bean
  */ 
  public G2Listbox()
  {
    vector = new Vector();
    addItemListener(this);
    listType = new Enum(new String[]{"Collection", "Selection"},
                        new int[]{COLLECTION, SELECTION}, COLLECTION);
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
  
  /** The listType property determines how the G2Listbox responds to ObjectUpdateEvents and when it
   * sends ObjectChangeEvents.
   */
  public void setListType(Enum listType)
  {
    this.listType = listType;
  }

  public Enum getListType()
  {
    return listType;
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

  public StringVector getChoices()
  {
    return choices;
  }

  /** Sets the list of possible values for this bean.  The choices property is only applicable for
   * selection lists.
   * @param newChoices, a vector of Strings.
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

  /** Initializes the choices of this G2Listbox with the contents of an attribute of a G2 item.
   * @see com.gensym.controls.G2Listbox#getInitializationAttribute
   */
  public void initializeChoices(ObjectUpdateEvent e){
    Symbol attribute = initializationAttribute;
    if (attribute == null)
      attribute = attributeSymbol;
    Object updateValue = e.getUpdatedObject();
    if ((updateValue instanceof Structure) && (attribute != null)){
      Object values = ((Structure)updateValue).getAttributeValue(attribute, lookupDefault);
      if ((values != lookupDefault) && (values instanceof Vector)){
	removeAll();
	for (int i=0; i<((Vector)values).size(); i++){
	  try{
	    addItem(fieldType.objectToString(((Vector)values).elementAt(i)));
	  }
	  catch(IOException ex){
	    throw new UnexpectedException(ex);
	  }
	}
	if (lastSelectionFromObjectUpdated != null){
	  int index = choices.indexOf(lastSelectionFromObjectUpdated);
	  if (index >=0)
	    select(index);
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

  /* Get's the current object in the vector being edited, rather than
   * its string representation in the list. Returns null for a selection list.
   */
  public Object getCurrentSelection()
  {
    if (listType.value == COLLECTION){
      int count = getItemCount();

      if (count > 0)
 	return vector.elementAt(getSelectedIndex());
      else 
	return null;
    }
    return null;
  }
  
  /** Gets the preferred size for this bean.
  */
  @Override
  public Dimension getPreferredSize()
  {
    if (prefSizeCount++ > 2)
      return getSize();
    else
      return new Dimension(100, 100);
  }
  
  
  /**  The objectUpdated method implements the ObjectUpdateListener interface.
   *  When this method is called for a collection list, the contents of the Vector being edit are changed.
   *  If the new vector has any elements, downstream editing components will be issued
   *  ObjectUpdateEvents.  When this method is called for a selection list, the selected item is updated.
   */
  @Override
  public void objectUpdated(ObjectUpdateEvent e)
  {
    String attrName =  e.getAttributeName();
    Object updateValue = e.getUpdatedObject();
   
    Object newValue;

    if (listType.value == SELECTION){
      newValue = e.getUpdatedValue(attributeSymbol, defaultContents);
      try {
	lastSelectionFromObjectUpdated = fieldType.objectToString(newValue);
	int index = choices.indexOf(lastSelectionFromObjectUpdated);
	if (index >=0)
	  select(index);
      } catch (IOException ioException)
	{
	  throw new UnexpectedException(ioException);
	}
    }
    else{
      if (attributeName.equals(""))
	newValue = updateValue;
      else if ((updateValue instanceof Structure) &&
	       (attributeSymbol != null))
	{
	  newValue = ((Structure)updateValue).getAttributeValue
	    (attributeSymbol,lookupDefault);
	  
	  if (newValue == lookupDefault)
	    newValue = null;
	}
      else
	newValue = null;
      
      removeAll();
      if (newValue instanceof Vector)
	{
	  vector = (Vector) ((Vector)newValue).clone();
	  int size = vector.size();
	  if (size == 0)
	    updateCurrentSelection(null);
	  else
	    {
	      for (int i = 0; i<size ; i++)
	        {
		  add(formatter.format(vector.elementAt(i)));
	        }

	      select(0);
	      updateCurrentSelection(vector.elementAt(0));
	     }
	}
      else
       updateCurrentSelection(null);
    }
  }
 
  /** Sets the currently selected item
  */
  private void setCurrentSelection(Object object)
  {
    Object oldSelection =  getCurrentSelection();
    int count = getItemCount();
    if (count > 0)
      {
        int index = getSelectedIndex();
        vector.setElementAt(object,index);
	remove(index);
	add(formatter.format(object),index);
	select(index);
      }
    firePropertyChange(object);
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

  /** Gets the formatter for this bean.  The formatter is a helper
   * class that assists making labels for the list.
   * @undocumented
   * @see com.gensym.controls.Formatter
   */
  public Formatter getFormatter()
  {
    return formatter;
  }

  /** Sets the formatter for this bean.  The formatter is a helper
   * class that assists making labels for the list. 
   * @undocumented
   * @see com.gensym.controls.Formatter
   */
  public void setFormatter(Formatter newFormatter)
  { 
    formatter = newFormatter;
    int index = getSelectedIndex();

    int count = getItemCount();
    if (count > 0)
    {
        for (int i = 0; i<count ; i++)
        {
	        Object element = vector.elementAt(i);
           replaceItem(formatter.format(element),i);
	     }
	     select(index);
    }
  }
  
  /** This method implements the ObjectChangeListener.  When it is called for a collection list,
   * the contents of the current selection (if any) will be modified.  This
   * will also propagate ObjeteChangeEvents to upstream components.  This method does nothing for
   * a selection list.
   */
  @Override
  public void objectChanged(ObjectChangeEvent e)
  {
    if (listType.value == COLLECTION){    
      setCurrentSelection(e.getChangedObject());
      fireObjectChange();
    }
  }

  /** Adds an additional object to the collection list.
  */
  public void extend()
  {
    Object oldSelection = getCurrentSelection();
    int count = getItemCount();
    Object defaultValue = fieldType.newInstance();
    add(formatter.format(defaultValue));
    select(count);
    updateCurrentSelection(defaultValue);
  }

  /**  Fires PropertyChange and ObjectUpdate events based on a new
  * value
  */
  private void updateCurrentSelection(Object newValue)
  {
    firePropertyChange(newValue);
    fireObjectUpdate(newValue);
  }

  /**  Fires a PropertyChangeEvent based on a new
  * value
  */
  private void firePropertyChange(Object newValue)
  {
    changes.firePropertyChange("currentSelection",
			       previousSelection,newValue);
    previousSelection = newValue;
  }

  /** listener method -- do not call
   * @undocumented.
   */
  @Override
  public void itemStateChanged(ItemEvent event)
  {
    if (listType.value == COLLECTION){
      Object object_target = event.getSource();
      updateCurrentSelection(getCurrentSelection());
    }
    else{
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
    }   
  }  

  /** Adds a listener to this bean for PropertyChangeEvents.
  */
  @Override
  public void addPropertyChangeListener(PropertyChangeListener l) 
  {
    changes.addPropertyChangeListener(l);
  }
  
  /** Removes a listener from this bean for PropertyChangeEvents.
  */
  @Override
  public void removePropertyChangeListener(PropertyChangeListener l) 
  {
    changes.removePropertyChangeListener(l);
  }
  
  /** Adds a listener to this bean for ObjectChangeEvents.
  */
  public synchronized void addObjectUpdateListener (ObjectUpdateListener
						      listener)
  {
    if (updateListeners == null) {
      updateListeners = new java.util.Vector();
    }
    updateListeners.addElement(listener);
  }
  
  /** Removes a listener from this bean for ObjectChangeEvents.
  */
  public synchronized void removeObjectUpdateListener(ObjectUpdateListener
							listener) 
  {
    if (updateListeners == null)
    {
      return;
    }
    updateListeners.removeElement(listener);
  }

  /**  Invokes the ObjectUpdated method on each of this beans ObjectUpdate
  * listeners
  */
  private void fireObjectUpdate(Object newSelection)
  {
    java.util.Vector targets;
    synchronized (this)
    {
      if (updateListeners == null)
      {
	       return;
      }
      targets = (java.util.Vector) updateListeners.clone();
    }
    
    ObjectUpdateEvent evt;
    evt = new ObjectUpdateEvent(this, newSelection ); 

    for (int i = 0; i < targets.size(); i++)
    {
      ObjectUpdateListener target = (ObjectUpdateListener)targets.elementAt(i);
      target.objectUpdated(evt);
    }
  }

 /** Subscribe to ObjectChangeEvents from a given StructureMUX
   */
  @Override
  public synchronized void addObjectChangeListener (ObjectChangeListener
						      listener)
  {
    if (changeListeners == null) {
      changeListeners = new java.util.Vector();
    }
    changeListeners.addElement(listener);
  }
  
  /** Cancel subscription to ObjectChangeEvents from a given StructureMUX.
   *
   */
  @Override
  public synchronized void removeObjectChangeListener(ObjectChangeListener
							listener) 
  {
    if (changeListeners == null) {
      return;
    }
    changeListeners.removeElement(listener);
  }

  void fireObjectChange()
  {
    java.util.Vector targets;
    synchronized (this) {
      if (changeListeners == null) {
	return;
      }
      targets = (java.util.Vector) changeListeners.clone();
    }
    
    ObjectChangeEvent evt;
    evt = new ObjectChangeEvent(this, vector.clone(), attributeName); /* clone changes */

    for (int i = 0; i < targets.size(); i++) {
      ObjectChangeListener target = (ObjectChangeListener)targets.elementAt(i);
      target.objectChanged(evt);
    }
  }

  private void fireObjectChange(Object newValue){
    java.util.Vector targets;
    synchronized (this) {
      if (changeListeners == null) {
	return;
      }
      targets = (java.util.Vector) changeListeners.clone();
    }
    
    ObjectChangeEvent evt;
    evt = new ObjectChangeEvent(this, newValue, attributeName); /* clone changes */

    for (int i = 0; i < targets.size(); i++) {
      ObjectChangeListener target = (ObjectChangeListener)targets.elementAt(i);
      target.objectChanged(evt);
    }
  }
  
  @Override
  public void add(String item){
    addItem(item, -1);
  }

  @Override
  public void addItem(String item){
    addItem(item, -1);
  }
  
  @Override
  public synchronized void add(String item, int index){
    addItem(item, index);
  }

  @Override
  public synchronized void addItem(String item, int index){
    if (fieldType.getType() instanceof SymbolType)
      item = item.toUpperCase();
    if (listType.value == SELECTION){
      if ((index < 0) || (index >= choices.size()))
	choices.addElement(item);
      else if (choices.size() > index)
	choices.insertElementAt(item, index);
    }
    super.addItem(item, index);
  }

  @Override
  public synchronized void replaceItem(String newValue, int index){
    if ((listType.value == SELECTION) && (choices.size() >= index))
      choices.setElementAt(newValue, index);
    super.replaceItem(newValue, index);
  }

  @Override
  public synchronized void removeAll(){
    if (listType.value == SELECTION)
      choices.removeAllElements();
    super.removeAll();
  }
   
  @Override
  public synchronized void remove(String item){
    if (listType.value == SELECTION)
      choices.removeElement(item);
    super.remove(item);
  }

  @Override
  public synchronized void remove(int position){
    if ((listType.value == SELECTION) && (choices.size() > position))
      choices.removeElementAt(position);
    super.remove(position);
  }

  private void readObject(java.io.ObjectInputStream stream) throws
                   java.lang.ClassNotFoundException, java.io.IOException,
                   java.io.NotActiveException
  {
    stream.defaultReadObject();
    if (listType == null)
     listType = new Enum(new String[]{"Collection", "Selection"},
                         new int[]{COLLECTION, SELECTION}, COLLECTION);
    if (choices == null)
      choices = new StringVector();
    if (defaultContents == null)
      defaultContents = "";
  } 

}
