package com.gensym.uitools.attrdisplays.layoutmodel;


import java.util.Vector;
import javax.swing.DefaultListModel;

/**
 * AttributeDisplayLayoutEditor is a template for editing the layout of 
 * attribute displays. For G2, this includes which attributes, show with 
 * name or not, and text color. In other applications, this may also 
 * control indentation, text and background color per line. 
 *
 * The editor has two groups of AttributeDisplayLayouts; <i>current</i> 
 * is the group most of the editor methods manipulate.  <i>Initial</i>
 * is held from the instantiation of the editor and is kept for refresh/revert
 * purposes.
 */
public abstract class AttributeDisplayLayoutEditor {

  protected Vector currentAttributeDisplayLayouts;
  protected Vector currentTableModels;
  protected Vector currentListModels;
  protected AttributeDisplayLayout[] initialAttributeDisplayLayouts;
  protected Vector collectionListeners = new Vector();
  protected Object[] choices;
  
  public AttributeDisplayLayoutEditor (Object[] choices) {
    this(null, choices);
  }

  /**
    @param initialAttributeDisplayLayouts a vector of AttributeDisplayLayouts
    */
  public AttributeDisplayLayoutEditor 
  (Vector initialAttributeDisplayLayouts, Object[] choices) {
    this.choices = choices;
    if (initialAttributeDisplayLayouts != null) {
      int length = initialAttributeDisplayLayouts.size();
      if (-1< length) {
	currentAttributeDisplayLayouts = initialAttributeDisplayLayouts;
	for(int i=0; i<length;i++) {
	  AttributeDisplayLayout adl = (AttributeDisplayLayout)initialAttributeDisplayLayouts.elementAt(i);
	  this.initialAttributeDisplayLayouts[i] = adl;
	  addModelVectors(adl);
	}
      }
    } else {
      this.initialAttributeDisplayLayouts = new AttributeDisplayLayout[0];
      currentAttributeDisplayLayouts = new Vector();
      currentTableModels = new Vector();
      currentListModels = new Vector();
    }
  }

  private void addModelVectors(AttributeDisplayLayout adl) {
    LayoutTableModel tableModel = createLayoutTableModel(adl);
    currentTableModels.addElement(tableModel);
    currentListModels.addElement(createListModel(tableModel));
  }

  private void insertInModelVectors(AttributeDisplayLayout adl, int index) {
    LayoutTableModel tableModel = createLayoutTableModel(adl);
    currentTableModels.insertElementAt(tableModel, index);
    currentListModels.insertElementAt(createListModel(tableModel), index);
  }
    
  public AttributeDisplayLayout createAttributeDisplayLayout() {
    return new AttributeDisplayLayoutImpl();
  }
  
  public abstract LayoutTableModel createLayoutTableModel(AttributeDisplayLayout adl);
  public abstract DefaultListModel createListModel(LayoutTableModel model);

  /**
   * @param layoutToAdd - an AttributeDisplayLayout to add to the end
   * of current group
   */
  public void addAttributeDisplay(AttributeDisplayLayout layoutToAdd){
    AttributeDisplayLayout layout;
    if (layoutToAdd == null)
      layout = createAttributeDisplayLayout();
    else layout = layoutToAdd;
    currentAttributeDisplayLayouts.addElement(layout);
    addModelVectors(layout);
  }

  public void setChoices(Object[] choices) {
    this.choices = choices;
  }

  /**
   * Returns the attribute display layout at the specified index.
   */
  public AttributeDisplayLayout getAttributeDisplayLayoutAt(int index){
    return (AttributeDisplayLayout)currentAttributeDisplayLayouts.
      elementAt(index);
  }

  public LayoutTableModel getTableModelAt(int index) {
    return (LayoutTableModel)currentTableModels.elementAt(index);
  }

  public DefaultListModel getListModelAt(int index) {
    return (DefaultListModel)currentListModels.elementAt(index);
  }

  /**
   * Sets the attribute display layout at index to layoutToSet.
   */
  public void setAttributeDisplayLayoutAt(int index, AttributeDisplayLayout layoutToSet) {
    LayoutTableModel tableModel = createLayoutTableModel(layoutToSet);
    currentAttributeDisplayLayouts.setElementAt(layoutToSet, index);
    currentTableModels.setElementAt(tableModel, index);
    currentListModels.setElementAt(createListModel(tableModel), index);
    fireCollectionChangeEvent();
  }

  /**
   * @return an array of AttributeDisplayLayouts, the information on the 
   * attribute display layouts up-to-date with the changes the editor has
   * made this session.
   */
  public AttributeDisplayLayout[] getCurrentAttributeDisplayLayouts() {
    int length = currentAttributeDisplayLayouts.size();
    AttributeDisplayLayout[] returnArray = new AttributeDisplayLayout[length];
    for (int i=0; i<length;i++)
      returnArray[i] = 
	(AttributeDisplayLayout)currentAttributeDisplayLayouts.elementAt(i);
    return returnArray;
  }

  /**
   * @return an array containing the initial information about the 
   * attribute display layouts, used to reset the editor.
   */
  public AttributeDisplayLayout[] getInitialAttributeDisplayLayouts() {
    return initialAttributeDisplayLayouts;
  }

  /**
   * Inserts an attribute display layout at the specified index.
   */
  public void insertAttributeDisplayAt(int index, 
				       AttributeDisplayLayout displayToInsert)
  {
    AttributeDisplayLayout layout;

    if (displayToInsert == null)
      layout = createAttributeDisplayLayout();
    else layout = displayToInsert;
    currentAttributeDisplayLayouts.insertElementAt(layout, index);
    insertInModelVectors(layout, index);
    fireCollectionChangeEvent();

  }

  /**
   * @param displayToRemove - an AttributeDisplayLayout. If there a Layout 
   * in this set of attribute displays that matches, it will be removed.
   * @return boolean indicates true if layout was removed, false if it did
   * not exist or was not removed for some other reason.
   */
  public void removeAttributeDisplay(AttributeDisplayLayout displayToRemove)
 {
    int index = currentAttributeDisplayLayouts.indexOf(displayToRemove);
    removeAttributeDisplayAt(index);
 }

  /**
   * removes AttributeDisplay at the specified index.
   */
  public void removeAttributeDisplayAt(int index) {
    currentAttributeDisplayLayouts.removeElementAt(index);
    currentTableModels.removeElementAt(index);
    currentListModels.removeElementAt(index);
    fireCollectionChangeEvent();
  }

  /**
   * @param displaysToSet - an array of AttributeDisplayLayouts, containing 
   * the information about the attribute displays the item has before the 
   * editor makes changes.
   */
  public void setInitialAttributeDisplayLayouts
  (AttributeDisplayLayout[] displaysToSet) {
    AttributeDisplayLayout adl;
    if (displaysToSet == null) displaysToSet = new AttributeDisplayLayout[0];
    initialAttributeDisplayLayouts = displaysToSet;
    currentAttributeDisplayLayouts.clear();
    currentTableModels.clear();
    currentListModels.clear();
    for (int i=0; i<initialAttributeDisplayLayouts.length; i++) {
      adl = initialAttributeDisplayLayouts[i];
      currentAttributeDisplayLayouts.add(adl);
      addModelVectors(adl);
    }
  }

  public void clearCurrentAttributeDisplays() {
    currentAttributeDisplayLayouts.clear();
    currentTableModels.clear();
    currentListModels.clear();
  }

  /**
   * @undocumented
   */
  public void addCollectionListener(CollectionListener collectionListener) {
    collectionListeners.addElement(collectionListener); 
  }

  /**
   * @undocumented
   */
  public void removeCollectionListener(CollectionListener collectionListener) {
    collectionListeners.removeElement(collectionListener); 
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

  public abstract Object createLayoutStructure(Object key) ;  

}
