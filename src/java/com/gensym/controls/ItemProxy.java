/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ItemPoxy.java
 *
 */

package com.gensym.controls;

import java.awt.Component;

import com.gensym.util.*;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.message.*;
import com.gensym.classes.Item;
import com.gensym.classes.ImplAccess;
import com.gensym.classes.VariableOrParameter;
import com.gensym.beansruntime.StringVector;
import com.gensym.dlgevent.ObjectUpdateListener;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.dlgevent.ObjectChangeEvent;
import com.gensym.dlgevent.ItemDeletionListener;
import com.gensym.dlgevent.ItemDeletionEvent;
import java.util.Vector;
import com.gensym.dlgruntime.DialogManager;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.TwAccess;

/**
 * An invisible bean which represents an item in G2. It usually
 * serves the role of being a port from a dialog into G2.  This proxy
 * is not class specific.  It contains a set (a Vector) of attributes
 * that will be uploaded or downloaded to G2 as directed by method
 * calls or subscription to state changes in the G2 server.  The item
 * proxy generates ObjectUpdateEvents for downstream editing controls
 * and receives ObjectChangeEvents (user edit's) for uploading back
 * to G2.  Uploading and downloading can be invoked by API, or happen
 * as a result of event handling or state changes.
 * <p>
 * Item proxies do not access items from g2 directly but can receive
 * them from ItemRetrievers, by dialog launchers, and through a method
 * call.
 * @see com.gensym.controls.ItemRetriever
 * @see com.gensym.dlgruntime.DialogLauncher
 * @see com.gensym.controls.ItemProxy#setProxy
 */

public class ItemProxy extends AttributeHolder implements ItemRetrievalListener, ObjectUpdateListener {
  /*
   * Allow deserialization
   */
  static final long serialVersionUID = 1791218745849269810L;

  private static final Object ATTRIBUTE_NOT_PRESENT = new Object();

  private String           name = "";
  private String           subObjectAttributeName = "";
  private Symbol           subObjectAttribute;
  private StringVector     attributeNames = new StringVector ();
  private SymbolVector     attributeSymbols = null;
  private Symbol[]         attributes;
  private transient volatile Item   item = null;
  private boolean          autoUpload = true;
  private volatile boolean autoDownload = true;
  private volatile ItemListener     itmListener;
  private transient VariableValueListener vorpListener;
  private transient Vector batchedChanges;

  /**
   * Constructor for this bean
   */
  public ItemProxy () {
    attributeNames.addElement("NAMES");
    cacheAttributeSymbols();
    structure = new Structure();
  }

  /**
   * Sets the name of this ItemProxy.  This name is
   *  is used by DialogLauncher's to distinguish multiple proxies
   *  on a dialog.
   *  @see com.gensym.dlgruntime.DialogLauncher
   */
  public void setName(String name)
  {
    this.name = name;
  }
  
  /**
   * Gets the name of this ItemProxy.
   */
  public String getName() {
    return name;
  }
  
  /**
   * Sets the item that this proxy represents.  It is legal to pass in null, which
   * will clear the proxy.
   */
  public void setProxy (Item item) {// throws G2AccessException

    if (this.item != null && this.item.equals (item))
      return;

    structure = new Structure();
    try {
      if (autoDownload) {
	if (this.item != null)
	  this.item.removeItemListener (itmListener);
	if (vorpListener != null)
	  ((VariableOrParameter)this.item).removeVariableValueListener (vorpListener);
	itmListener = null;
	vorpListener = null;
	if (item != null) {
	  item.addItemListener (itmListener = new ItemProxyAdapter ());
	  if (item instanceof VariableOrParameter) {
	    VariableOrParameter vorp = (VariableOrParameter)item;
	    for (int i=0; i<attributes.length; i++)
	      if (attributes[i].equals (SystemAttributeSymbols.VALUE_STRUCTURE_))
		vorp.addVariableValueListener (vorpListener = new VariableAdapter ());
	  }
	}
      }
    } catch (G2AccessException gae) {
      Trace.exception (gae);
    }
    setupInvalidationListening(item);
    this.item = item;
  }

  /**
   * Provides access to the Item inside this ItemProxy.
   * @returns The item that is encapsulated in this ItemProxy.
   */
  public Item getProxy() {
    return item;
  }

  class ItemProxyAdapter implements ItemListener {
    @Override
    public void receivedInitialValues (ItemEvent e) {}

    @Override
    public void itemModified (ItemEvent e) {
      try {
	//System.out.println ("MODIFICATION : " + e);
	Sequence denotation = e.getDenotation ();
	Structure dentnStruct = (Structure) denotation.elementAt (0);
	Symbol attrName = (Symbol) dentnStruct.getAttributeValue
	  (Denotation.NAME_, null);
	fireAttributeUpdate (attrName);
      } catch (Exception ex) {
	Trace.exception (ex);
      }
    }

    @Override
    public void itemDeleted (ItemEvent e) {}
  }

  class VariableAdapter implements VariableValueListener {
    @Override
    public void receivedInitialValue(VariableValueEvent event) {}
    @Override
    public void valueChanged(VariableValueEvent event) {
      try {
	java.lang.Object newValue = event.getNewValue ();
	fireAttributeUpdate (SystemAttributeSymbols.VALUE_STRUCTURE_);
      } catch (Exception ex) {
	Trace.exception (ex);
      }
    }
  }

  /**
   * Gets the attributes which will be stored by this Proxy.
   */
  public SymbolVector getAttributes()
  {
    if (attributeSymbols == null)
      {
        int i,len = attributeNames.size();
	attributeSymbols = new SymbolVector();
	for (i=0; i<len ; i++)
	  attributeSymbols
	    .addElement(Symbol.intern((String)attributeNames.elementAt(i)));
      }
    return attributeSymbols;
  }

  /**
   * Sets the attributes which will be stored by this Proxy.
   */
  public void setAttributes(SymbolVector attributeSymbols)
  {
    this.attributeSymbols = attributeSymbols;
    int i,len = attributeSymbols.size();
    attributeNames = new StringVector();
    for (i=0; i<len ; i++)
      attributeNames.addElement(attributeSymbols.elementAt(i).toString());
    cacheAttributeSymbols();
  }

  public void addAttribute(Symbol attribute){
    if (attributeSymbols == null)
      attributeSymbols = new SymbolVector();
    attributeSymbols.addElement(attribute);
    if (attributeNames == null)
      attributeNames = new StringVector();
    attributeNames.addElement(attribute.toString());
    cacheAttributeSymbols();
  }

  public Symbol getSubObjectAttribute(){
    return subObjectAttribute;
  }

  public void setSubObjectAttribute(Symbol name){
    subObjectAttribute = name;
    subObjectAttributeName = name.toString();
  }

  /**
   * The autoUpload property determines whether received ObjectChangeEvent's
   * are propagated immediately to G2, or allowed to buffer until a call
   * to upload
   */
  public boolean getAutoUpload()
  {
    return autoUpload;
  }

  /**
   * The autoUpload property determines whether received ObjectChangeEvent's
   * are propagated immediately to G2, or allowed to buffer until a call
   * to upload
   */
  public void setAutoUpload (boolean autoUpload)
  {
    this.autoUpload = autoUpload;
  }

  /**
   * Indicates if this ItemProxy receives updates to
   * the embedded Item automatically from G2.
   * @boolean true if the Proxy is notified of changes to the Item, false otherwise
   */
  public boolean getAutoDownload () {
    return autoDownload;
  }

  /**
   * Sets the variable that indicates if this ItemProxy
   * should receive updates from G2 whenever the embedded
   * Item is modified.
   * @param autoDownloadState a boolean indicating if this ItemProxy should
   *    be kept in sync with changes to the embedded Item in G2.
   * @see getAutoDownload
   */
  public void setAutoDownload (boolean autoDownloadState) throws G2AccessException {
    if (autoDownloadState == autoDownload)
      return;

    if (item != null) {
      if (autoDownloadState)
	item.addItemListener (itmListener = new ItemProxyAdapter ());
      else {
	item.removeItemListener (itmListener);
	itmListener = null;
      }
    }
    autoDownload = autoDownloadState;
  }

  /**
   * Builds up the attributes from the attribute names
   */
  private void cacheAttributeSymbols()
  {
    int size = attributeNames.size();
    attributes = new Symbol[size];

    for (int i = 0; i<size ; i++)
      attributes[i] = Symbol.intern(((String)attributeNames.elementAt(i)).toUpperCase());
  }

  /**
   * Gets the values for the listed attributes of the item in the G2 server
   * which this proxy refers to, stores these values, then fires an
   * ObjectUpdate event to the listeners for this event
   */
  public void download() throws G2AccessException, NoSuchAttributeException {

    synchronized (this) {
    
      // Clear out the locally stored attributes
      if (item == null)
	throw new IllegalStateException ("No item set in proxy");
     
      structure = new Structure();
    
      int length = attributes.length;
      // Get the values for the attributes we are interested in         
      for (int i = 0; i < length ; i++)
	structure.setAttributeValue(attributes[i], item.getPropertyValue (attributes[i]));
    }
    // Send an event to anyone who is listening
    fireObjectUpdate();
    // System.out.println("leaving download lock");
  }

  /**
   * Do not call.
   * @undocumented
   *  <i> This method is under design review and may be withdrawn.</i>
   */
  public void fireAttributeUpdate(Symbol attributeName)
throws G2AccessException, NoSuchAttributeException 
  { 
    java.util.Vector targets;
    synchronized (this) {
      // Clear out the locally stored attributes
      if (item == null)
	throw new IllegalStateException ("No item set in proxy");
      
      structure.setAttributeValue(attributeName,
				  item.getPropertyValue (attributeName));
      
      if (updateListeners == null) {
	return;
      }
      targets = (java.util.Vector) updateListeners.clone();
    }
    
    ObjectUpdateEvent e;
    e = new ObjectUpdateEvent(this, structure, attributeName.toString());

    //System.out.println ("Firing : " + e);
    for (int i = 0; i < targets.size(); i++) {
      ObjectUpdateListener target = (ObjectUpdateListener)targets.elementAt(i);
      if (target instanceof AttributeEditor)
	{
	  AttributeEditor editor = (AttributeEditor)target;
	  //if (editor.getAttributeSymbol().equals(attributeName))
	  //  System.out.println("found editor for "+attributeName+"; it's "+editor);
	  if (editor.getAttribute().equals(attributeName))
	    editor.objectUpdated(e);
	} else
	  ((ObjectUpdateListener)target).objectUpdated (e);
    }
  }


  /**
   * Concludes the values of the attributes which the proxy is storing
   * back into the item in the G2 server.
   */
  public void upload () throws G2AccessException {
    
    if (item == null)
      throw new IllegalStateException ("No item set in proxy");
    
    if (batchedChanges == null || batchedChanges.isEmpty())
      return;
    
    // Set the values for the attributes we are interested in 
    int numDirtyAttributes = batchedChanges.size ();

    for (int i = 0; i < numDirtyAttributes; i++) {
      Symbol attrName = (Symbol)batchedChanges.elementAt (i);
      item.setPropertyValue (attrName,
			     structure.getAttributeValue (attrName, null));
    }
    batchedChanges.removeAllElements (); 
    // System.out.println("leaving upload lock");

  }


  /**
   * This method is called in response to an ObjectChangeEvent.  The values
   * of any attributes which have changed are stored in the item proxy, and the
   * upload method is called (if autoUpload is set to true)
   */
  @Override
  public void objectChanged (ObjectChangeEvent e) {
    if (item == null)
      throw new IllegalStateException ("No item set in proxy");
    String attrName =  e.getAttributeName();
    //System.out.println("recv object changed event in IP attr="+attrName+
    //		       " and value "+e.getChangedObject());
    if (attrName != null) {
      Symbol nameSymbol = Symbol.intern(attrName.toUpperCase());
      structure.setAttributeValue(nameSymbol, e.getChangedObject());
      try {
	if (autoUpload)
	  item.setPropertyValue (nameSymbol,e.getChangedObject());
	else {
	  if (batchedChanges == null)
	    batchedChanges = new Vector (5);
	  if (!batchedChanges.contains(nameSymbol))
	    batchedChanges.addElement (nameSymbol);
	}
      } catch (G2AccessException gae) {
	Trace.exception (gae);
      }
      fireObjectChange();
    }
  }

  /**
   * The itemRetrieved method implements one of the methods
   * of the ItemRetrievalListener.  This method should be called
   * in response to ItemRetrievalEvents to set the proxy
   * after an item is fetch from G2. It also automatically
   * downloads the desired attributes of the Item.
   * @see com.gensym.controls.ItemRetriever
   * @see com.gensym.controls.ItemProxy#setProxy
   */
  @Override
  public void itemRetrieved(ItemRetrievalEvent event) {
    setProxy(event.getRetrievedItem());
    try {
      download ();
    } catch (Exception e) {
      Trace.exception (e);
      new com.gensym.dlg.ErrorDialog (null, "Error Retrieving Attributes", true,
				      e.toString (), null).setVisible (true);
    }
  }
  
  /**
   * The itemRetrieved method implements one of the methods
   * of the ItemRetrievalListener. It will clear (set to null)
   * the item held in this item proxy.
   */
  @Override
  public void itemRetrievalFailed(ItemRetrievalEvent event) {
    setProxy(null);
  }

  @Override
  public void objectUpdated(ObjectUpdateEvent e){
    Object updateObject = e.getUpdatedObject();
    if (updateObject instanceof Structure){
      Structure attr = (Structure)updateObject;
      Object value = attr.getAttributeValue(subObjectAttribute, null);
      if (value != null){
	if (value instanceof Item){
	  setProxy((Item)value);
	  try {
	    download();
	  } catch (Exception ex) {
	    Trace.exception (ex);
	    new com.gensym.dlg.ErrorDialog (null, "Error Retrieving Attributes", 
					    true, ex.toString (), 
					    null).setVisible (true);
	  }
	}
      }
    }
  }

  private synchronized void addPropertyName(String propertyName) {
    if (!attributeNames.contains(propertyName)) {
      attributeNames.addElement(propertyName);
      cacheAttributeSymbols();
    }
  }

  /**
   * uses the objectChanged() mechanism to indicate a change to the
   * value of a property.
   * <p>
   * Automatically adds <code>propertyName</code> to the
   * <code>attributeNames</code> if not already present.
   * @see #objectChanged
   * @undocumented
   */
  public void setPropertyValue(String propertyName, Object newValue)
  throws G2AccessException {
    addPropertyName(propertyName);
    objectChanged(new ObjectChangeEvent(this, newValue, propertyName));
  }


  /**
   * Returns a view of the value of the property. The relationship
   * between that view and the value of the property in G2
   * has the following behaviour in relation to the autoUpload and
   * autoDownload properties:
   * <p>
   * If autoDownload is <code>false</code>, then a local copy of
   * the property is returned if it exists (even if this copy
   * has been changed by
   * a call to setPropertyValue or objectChanged, and the new value
   * has not been uploaded to G2).
   * <p>
   * Automatically adds <code>propertyName</code> to the
   * <code>attributeNames</code> if not already present.
   * @undocumented
   */
  public Object getPropertyValue(String propertyName) 
  throws G2AccessException, NoSuchAttributeException {
    addPropertyName(propertyName);
    Symbol propertySymbol = Symbol.intern(propertyName);
    Object attrValue =
      structure.getAttributeValue(propertySymbol, ATTRIBUTE_NOT_PRESENT);

    if (ATTRIBUTE_NOT_PRESENT.equals(attrValue)) {
      Object value = item.getPropertyValue(propertySymbol);
      structure.setAttributeValue(propertySymbol, value);
      return value;
    }
    else
      return attrValue;
  }

  /**
   * @deprecated As of Telewindows2 Toolkit 1.1 rev 0. Use editItem(Component)
   * instead.
   */
  public void editItem()
  {
    editItem(null);
  }

  /** 
   *  editItem() will launch a dialog for editing the item held by this ItemProxy.
   *  If the proxy is not set nothing happens.  The dialog that it will launch is
   *  whatever dialog is stored for the current class and mode in the DialogManager
   *  of the current TwAccess object.
   * @since Telewindows2 Toolkit 1.1 rev 0
   */
  public void editItem(Component requestingComponent) {
    if (item != null)
      {
	try {
	  G2Access context = ((ImplAccess)item).getContext ();
	  if (context instanceof TwAccess)
	    {
	      DialogManager dialogManager = ((TwAccess)context).getDialogManager();
	      dialogManager.editItem(requestingComponent,
				     item, 
				     ((TwAccess)context).getUserMode(),
				     java.util.Locale.getDefault());
	    }
	} catch (Exception e)
	  {
	    Trace.exception(e);
	  }
      }
  }

  /**
   * @undocumented Needed for method dispatch in VB to work around
   * Plug-in bug of not delivering exceptions
   */
  public Object getThis () {
    return this;
  }

  private transient StubInvalidationListener invalidationAdapter;

  /**
   * must be called before the internal proxy member is changed.
   */
  private void setupInvalidationListening(Item newItem) {
    if (item != null && invalidationAdapter != null)
      ((ImplAccess)item).removeStubInvalidationListener(invalidationAdapter);
    if(newItem == null)
      return;

    if (invalidationAdapter == null) {
      invalidationAdapter =
	new StubInvalidationListener() {
	@Override
	public void stubIsInvalid(StubInvalidationEvent event){
	  Vector notificationList;
	  synchronized (deletionListeners) {
	    if (deletionListeners.isEmpty())
	      return;
	    notificationList = (Vector)deletionListeners.clone();
	  }
	  
	  int size = notificationList.size();
	  Item invalidatedStub = (Item)event.getSource();
	  ItemDeletionEvent e = new ItemDeletionEvent(this, invalidatedStub);
	  for (int i = 0; i < size; i++) {
	    ((ItemDeletionListener)notificationList.elementAt(i)).itemDeleted(e);
	  }
	}
      };
    }
     
    ((ImplAccess)newItem).addStubInvalidationListener(invalidationAdapter);
  }

  private Vector deletionListeners = new Vector();

  /**
   * @undocumented Needed for VB to know if an item has been deleted.
   * NOTE: ALL invalidation events are translated into ItemDeletionEvents.
   * In Telewindows2Toolkit (particularly under VB) these should
   * be equivalent.
   */
  public void addItemDeletionListener(ItemDeletionListener l) {
    synchronized (deletionListeners) {
      deletionListeners.addElement(l);
    }
  }

  /**
   * @undocumented Needed for VB
   */
  public void removeItemDeletionListener(ItemDeletionListener l) {
    if (deletionListeners == null)
      return;

    synchronized (deletionListeners) {
      deletionListeners.removeElement(l);
    }
  }
}
