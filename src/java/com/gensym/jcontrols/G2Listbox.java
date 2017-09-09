/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2Listbox.java
 *
 */

// rpenny: review use of sending out objectUpdate events
// and objectChange: keep them for now

package com.gensym.jcontrols;

import javax.swing.JList;
import javax.swing.ListSelectionModel;
import javax.swing.DefaultListModel;
import javax.swing.event.ListSelectionListener;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListDataListener;
import javax.swing.event.ListDataEvent;
import java.awt.*;
import java.awt.event.*;
import java.beans.*;
import java.io.IOException;
import java.util.Vector;
import com.gensym.widgets.ScrollList;
import com.gensym.util.Deserializer;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.UnexpectedException;
import com.gensym.types.G2SyntaxException;
import com.gensym.beansruntime.StringVector;
import com.gensym.beansruntime.Enum;
import com.gensym.dlgevent.ObjectUpdateListener;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.dlgevent.ObjectChangeListener;
import com.gensym.dlgevent.ObjectChangeEvent;
import com.gensym.controls.Formatter;
import com.gensym.controls.FieldType;
import com.gensym.widgets.ScrollList;
import com.gensym.types.G2TokenizerException;
import com.gensym.types.G2ParserException;
import com.gensym.controls.AttributeEditor;

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

public class G2Listbox extends ScrollList
implements ObjectChangeListener, ObjectUpdateListener, ListSelectionListener,
  ListDataListener, AttributeEditor
{
  /*
   * Allow deserialization
   */
  static final long serialVersionUID = -4020304664824355938L;

  public final static int COLLECTION = 0;
  public final static int SELECTION = 1;

  //private Vector vector;
  private PropertyChangeSupport changes; //= new PropertyChangeSupport(this);
  private Object previousSelection = null;
  private static final Object lookupDefault = new Object();
  private int prefSizeCount = 0;
  //private Formatter formatter = new Formatter();
  private Vector changeListeners = null;
  private Vector updateListeners = null;
  //private FieldType fieldType = new FieldType();
  private String attributeName = "";
  private Symbol attributeSymbol = null;
  private Enum listType;
  private StringVector choices = new StringVector();
  private String defaultContents = "";
  private Symbol initializationAttribute = null;
  private Object lastSelectionFromObjectUpdated = null;
  /** Contructor for this bean
  */ 
  public G2Listbox()
  {
    //vector = new Vector();
    //addItemListener(this);
    addListSelectionListener(this);
    getModel().addListDataListener(this);
    listType = new Enum(new String[]{"Collection", "Selection"},
                        new int[]{COLLECTION, SELECTION}, COLLECTION);
    setCellRenderer(new G2CellRenderer(this));
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
    DefaultListModel model = (DefaultListModel)getModel();
    int size = model.getSize();
    FieldType fieldType = ((G2CellRenderer)getCellRenderer()).getFieldType();
    StringVector choices = new StringVector();
    for (int i = 0; i < size; i++) {
      try {
	choices.addElement(fieldType.objectToString(model.elementAt(i)));
      } catch (IOException ioe) {
	choices.addElement("IO Error on " + model.elementAt(i));
      }
    }
    return choices;
  }

  /** Sets the list of possible values for this bean.  The choices property is only applicable for
   * selection lists.
   * @param newChoices, a vector of Strings.
   */
  public void setChoices(StringVector newChoices)
  {
    // fix this: shouldn't we limit this to SELECTION programmatically?
    int size = newChoices.size();
    removeAll();
    FieldType fieldType = ((G2CellRenderer)getCellRenderer()).getFieldType();
    for (int i = 0; i<size ; i++) {
      try {
	addItem(fieldType.stringToObject((String)newChoices.elementAt(i)));
      } catch (IOException ioe) {
	addItem(ioe);
      } catch (G2ParserException g2pe) {
	addItem(g2pe);
      } catch (G2TokenizerException g2te) {
	addItem(g2te);
      }
    }
  }


  /** Initializes the choices of this G2Listbox with the contents of an attribute of a G2 item.
   * @see com.gensym.controls.G2Listbox#getInitializationAttribute
   */
  public void initializeChoices(ObjectUpdateEvent e){
    // fix this: only for SELECTION
    Symbol attribute = initializationAttribute;
    if (attribute == null)
      attribute = attributeSymbol;
    Object updateValue = e.getUpdatedObject();
    if ((updateValue instanceof Structure) && (attribute != null)){
      Object values = ((Structure)updateValue).getAttributeValue(attribute, lookupDefault);
      if ((values != lookupDefault) && (values instanceof Vector)){
	removeAll();
	for (int i=0; i<((Vector)values).size(); i++){
	  addItem(((Vector)values).elementAt(i));
	}
	if (lastSelectionFromObjectUpdated != null){
	  int index = ((DefaultListModel)getModel()).indexOf(lastSelectionFromObjectUpdated);
	  if (index >=0)
	    setSelectedIndex(index);
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
      int count = getModel().getSize();

      if (count > 0)
 	return ((DefaultListModel)getModel()).elementAt(getSelectedIndex());
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

  private boolean inObjectUpdated = false; // fix this: not thread safe
  
  /**  The objectUpdated method implements the ObjectUpdateListener interface.
   *  When this method is called for a collection list, the contents of the Vector being edit are changed.
   *  If the new vector has any elements, downstream editing components will be issued
   *  ObjectUpdateEvents.  When this method is called for a selection list, the selected item is updated.
   */
  @Override
  public void objectUpdated(ObjectUpdateEvent e)
  {
    inObjectUpdated = true;
    String attrName =  e.getAttributeName();
    Object updateValue = e.getUpdatedObject();
   
    Object newValue;

    if (listType.value == SELECTION){
      newValue = e.getUpdatedValue(attributeSymbol, defaultContents);
      lastSelectionFromObjectUpdated = newValue;
      int index = ((DefaultListModel)getModel()).indexOf(lastSelectionFromObjectUpdated);
      if (index >=0)
	setSelectedIndex(index);
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
	  Vector vector = (Vector)newValue;
	  int size = vector.size();
	  if (size == 0)
	    updateCurrentSelection(null);
	  else
	    {
	      for (int i = 0; i<size ; i++)
	        {
		  add(vector.elementAt(i));
	        }

	      setSelectedIndex(0);
	      updateCurrentSelection(vector.elementAt(0));
	     }
	}
      else
       updateCurrentSelection(null);
    }
    inObjectUpdated = false;
  }
 
  /** Sets the currently selected item
   * returns true if a change was made
  */
  private boolean setCurrentSelection(Object object)
  {
    Object oldSelection =  getCurrentSelection();
    if (oldSelection != null && oldSelection.equals(object))
      return false;
    int count = getModel().getSize();
    if (count > 0) {
        int index = getSelectedIndex();
        replaceItem(object,index);
    }
    //setSelectedValue(object, false);
    firePropertyChange(object);
    return true;
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
    return ((G2CellRenderer)getCellRenderer()).getFieldType();
  }

  /** The fieldType property controls the transformation of strings
   * into other data types that this field may represent.  All G2 data
   * types (as presented by JavaLink) are supported.
   * @see com.gensym.types.G2Type
   * @see com.gensym.util.Structure
   * @see com.gensym.util.Sequence
   * @see com.gensym.util.Symbol
   */
  public void setFieldType(FieldType fieldType)
  {
    ((G2CellRenderer)getCellRenderer()).setFieldType(fieldType);
  }

  /** Gets the formatter for this bean.  The formatter is a helper
   * class that assists making labels for the list.  
   * @see com.gensym.controls.Formatter
   */
  public Formatter getFormatter()
  {
    return ((G2CellRenderer)getCellRenderer()).getFormatter();
  }

  /** Sets the formatter for this bean.  The formatter is a helper
   * class that assists making labels for the list. 
   * @see com.gensym.controls.Formatter
   */
  public void setFormatter(Formatter newFormatter)
  {
    ((G2CellRenderer)getCellRenderer()).setFormatter(newFormatter);
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
      if (setCurrentSelection(e.getChangedObject()))
	fireObjectChange();
    }
  }

  @Override
  public void contentsChanged(ListDataEvent e) {
    if (listType.value == COLLECTION && !inObjectUpdated){
      fireObjectChange();
    }
  }

  @Override
  public void intervalAdded(ListDataEvent e) {
    if (listType.value == COLLECTION && !inObjectUpdated){
      fireObjectChange();
    }
  }

  @Override
  public void intervalRemoved(ListDataEvent e) {
    if (listType.value == COLLECTION && !inObjectUpdated){
      fireObjectChange();
    }
  }

  /** Adds an additional object to the collection list.
  */
  public void extend()
  {
    Object oldSelection = getCurrentSelection();
    int count = getModel().getSize();
    Object defaultValue = ((G2CellRenderer)getCellRenderer()).getFieldType().newInstance();
    add(defaultValue );
    setSelectedIndex(count);
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
    ensureChangeSupport().firePropertyChange("currentSelection",
			       previousSelection,newValue);
    previousSelection = newValue;
  }

  /** ListSelectionListener method -- do not call
   * @undocumented.
   */
  @Override
  public void valueChanged(ListSelectionEvent event) {
    // fix this: don't understand this first clause.
    if (listType.value == COLLECTION){
      Object object_target = event.getSource();
      updateCurrentSelection(getCurrentSelection());
    } else{
      Object object = getSelectedValue();
      if (object != null)
	fireObjectChange(object);
    }
  }

  /**
   * This was necessary, since a PropertyChangeEvent is fired
   * by the superclass, before field initialization is complete
   * on this class.
   */
  private synchronized PropertyChangeSupport ensureChangeSupport() {
    if (changes == null)
      changes = new PropertyChangeSupport(this);
      
    return changes;
  }

  /** Adds a listener to this bean for PropertyChangeEvents.
  */
  @Override
  public void addPropertyChangeListener(PropertyChangeListener l) 
  {
    ensureChangeSupport().addPropertyChangeListener(l);
  }
  
  /** Removes a listener from this bean for PropertyChangeEvents.
  */
  @Override
  public void removePropertyChangeListener(PropertyChangeListener l) 
  {
    ensureChangeSupport().removePropertyChangeListener(l);
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
    DefaultListModel model = (DefaultListModel)getModel();
    Sequence things;
    synchronized(model) {
      int size = model.getSize();
      things = new Sequence(size);
      for (int i = 0; i < size; i++) {
	things.addElement(model.elementAt(i));
      }
    }

    evt = new ObjectChangeEvent(this, things, attributeName); /* clone changes */

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
  
  public void add(Object item){
    addItem(item, -1);
  }

  public void addItem(Object item){
    addItem(item, -1);
  }
  
  public void add(Object item, int index){
    addItem(item, index);
  }

  public synchronized void addItem(Object item, int index){
    DefaultListModel model = (DefaultListModel)getModel();
    int size = model.getSize();
    if (//(listType.value == SELECTION) &&
	((index < 0) || (index >= size)))
      model.addElement(item);
    else
      model.insertElementAt(item, index);
  }

  public void replaceItem(Object newValue, int index){
    ((DefaultListModel)getModel()).setElementAt(newValue, index);
  }

  @Override
  public void removeAll(){
    ((DefaultListModel)getModel()).removeAllElements();
  }
   
  public void remove(Object item){
    ((DefaultListModel)getModel()).removeElement(item);
  }

  @Override
  public void remove(int position){
    ((DefaultListModel)getModel()).removeElementAt(position);
  }

  private void readObject(java.io.ObjectInputStream stream) throws
                   java.lang.ClassNotFoundException, java.io.IOException,
                   java.io.NotActiveException
  {
    stream.defaultReadObject();
    if (listType == null)
     listType = new Enum(new String[]{"Collection", "Selection"},
                         new int[]{COLLECTION, SELECTION}, COLLECTION);
    addListSelectionListener(this);
    getModel().addListDataListener(this);
    if (defaultContents == null)
      defaultContents = "";
  }
}
