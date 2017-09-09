/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2ObjectCreator.java
 *
 */

package com.gensym.ntw.util;

import java.awt.Image;
import java.util.Vector;
import java.util.Enumeration;
import java.util.Hashtable;
import java.lang.reflect.Array;
import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.DefinitionListener;
import com.gensym.util.DefinitionEvent;
import com.gensym.util.UnexpectedException;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.classes.Definition;
import com.gensym.classes.Item;
import com.gensym.classes.Entity;
import com.gensym.classes.G2Definition;
import com.gensym.ui.ObjectCreator;
import com.gensym.ui.StructuredObjectCreator;
import com.gensym.ui.ObjectCreatorListener;
import com.gensym.ui.StructuredObjectCreatorListener;
import com.gensym.ui.ObjectCreatorEvent;

/** 
 *  An implementation of the ObjectCreator interface for creating G2 items off
 *  of palettes.  A G2ObjectCreator can create items from definitions in a
 *  single G2.
 *
 *  All items except CONNECTIONS and KB-WORKSPACES may be created with
 *  a G2ObjectCreator.
 * 
 *  For entities, the icon is obtained from the definition in G2.  For text-boxes,
 *  a standard "text" image is used as the icon. If the icon in G2 changes,
 *  the G2ObjectCreator will notify listeners.
 *
 *  The description of all items is the name of the G2 class.  
 *
 *  Deleted definitons or definitions whose name change are made unavailable and
 *  notification of the change in availability is dispatched to all listeners.
 *  
 */
public class G2ObjectCreator implements StructuredObjectCreator{

  private static final Symbol NAME_ = Symbol.intern("NAME");
  private static final Resource i18n = Resource.getBundle("com/gensym/ntw/util/Errors");
  private static final Class thisClass = com.gensym.ntw.util.G2ObjectCreator.class;

  private TwAccess context;
  private Vector orderedKeys;
  private Object[] structure;
  private Hashtable itemTable; //maps key -> info
  private Hashtable defTable; //maps def -> key
  private DefinitionListener classChangeAdapter;
  private Vector listeners;

  private G2ObjectCreator(TwAccess connection) {
    context = connection;
    orderedKeys = new Vector();
    itemTable = new Hashtable();
    defTable = new Hashtable();
    classChangeAdapter = new ClassChangeAdapter();
    listeners = new Vector();    
  }
  
  /** 
   * Creates a G2ObjectCreator for the specified connection and G2 class names 
   */
  public G2ObjectCreator(TwAccess connection, Object[] classNames) throws G2AccessException{
    this(connection);
    setStructuredKeys(classNames);
  }

  /** 
   * Creates a G2ObjectCreator for the specified connection and G2 items
   */  
  public G2ObjectCreator(TwAccess connection, Item[] items) throws G2AccessException{
    this(connection);
    setStructuredKeys(items);
  }  

  private final void doSetStructuredKeys(Object[] classNamesOrItems)
       throws G2AccessException
  {
    Hashtable newItemTable = new Hashtable();
    Hashtable newDefTable = new Hashtable();
    structure = new Object[classNamesOrItems.length];
    orderedKeys.removeAllElements();
    setupTables(classNamesOrItems, newItemTable, newDefTable);
    resetTables();
    itemTable = newItemTable;
    defTable = newDefTable;
    notifyStructureChanged();    
  }

  public void setStructuredKeys(Item[] items) throws G2AccessException{
    doSetStructuredKeys(items);
  }
  
  public void setStructuredKeys(Object[] classNames) throws G2AccessException{
    doSetStructuredKeys(classNames);
  }

  private void setupTables(Object[] classNamesOrItems, Hashtable newItemTable, Hashtable newDefTable) throws G2AccessException{
    for (int i=0; i<classNamesOrItems.length; i++){
      Object element = classNamesOrItems[i];
      Class elementClass = element.getClass();
      if (elementClass.isArray()){
	boolean isSymbolArray =
	  elementClass.getComponentType().equals(com.gensym.util.Symbol.class);
	boolean isItemArray =
	  !isSymbolArray &&
	  elementClass.getComponentType().equals(com.gensym.classes.Item.class);
	if (isSymbolArray||isItemArray) {
	  int len = Array.getLength(element);
	  String[] group = new String[len];
	  structure[i] = group;
	  for (int j=0; j<len; j++){
	    Object elt = Array.get(element, j);
	    Symbol className=null;
	    Item item = null;
	    if (isSymbolArray)
	      className = (Symbol)elt;
	    else {
	      item = (Item)elt;
	      className = item.getG2ClassName();
	    }
	    String key = getKeyForClass(className);
	    addPaletteItem(className, item, key, newItemTable, newDefTable);
	    group[j] = key;
	  }
	} else
	  setupTables((Object[])element, newItemTable, newDefTable);
      } else if (element instanceof Symbol ||
		 element instanceof Item){
	Symbol className = null;
	Item item = null;
	if (element instanceof Symbol)
	  className = (Symbol)element;
	else {
	  item = (Item)element;	  
	  className = item.getG2ClassName();
	}
	String key = getKeyForClass(className);
	//THIS NEEDS TO BE UPDATED IN CASE THERE IS MORE THAN ONE INSTANCE
	//OF THE SAME CLASS ON A GIVEN PALETTE(<class-name>(#1),...)	
	if (orderedKeys.contains(key))
	  throw new IllegalArgumentException(i18n.format("duplicateKeys", key));
	addPaletteItem(className, item, key, newItemTable, newDefTable);
	structure[i] = key;
      }	else
	throw new IllegalArgumentException(i18n.format("illegalClassNames", element.toString()));
    }
  }  

  /**
   * @param key The key, for which to find the corresponding G2 Item.
   * @return The Item corresponding to this key, or null.
   * @throws IllegalArgumentException if the key does not exist.
   */
  protected Item getPaletteItem(String key) {
    ItemInfo info = (ItemInfo)itemTable.get(key);
    if (info != null)
      return info.itemForOverrides;
    else
      throw new IllegalArgumentException(i18n.format("nonExistentKey", key));
  }
  
  private void addPaletteItem(Symbol className,
			      Item itemForOverrides,
			      String key,
			      Hashtable newItemTable,
			      Hashtable newDefTable) throws G2AccessException{
    ItemInfo info = getOrCreateItemInfo(className, itemForOverrides);
    newItemTable.put(key, info);
    newDefTable.put(info.def, key);
    orderedKeys.addElement(key);
    if (info.def instanceof Definition)
      ((Definition)info.def).addDefinitionListener(classChangeAdapter);
  }

  private String getKeyForClass(Symbol className){
    return className.getPrintValue();
  }

  private ItemInfo getOrCreateItemInfo(Symbol className,
				       Item itemForOverrides) throws G2AccessException{
    String key = getKeyForClass(className);
    ItemInfo info = (ItemInfo)itemTable.get(key);
    if (info == null){
      G2Definition def = context.getClassManager().getDefinition(className);
      if (G2ClassHelper.isInstanceAllowedOnWorkspace(def))
	return new ItemInfo(className, def.getInstantiate(), null, null, def,
			    itemForOverrides);
      else
	throw new IllegalArgumentException(i18n.format("illegalClass", className));
    }
    else
      return info;
  }
    
  private void resetTables() throws G2AccessException{
    itemTable.clear();
    Enumeration defs = defTable.keys();
    while (defs.hasMoreElements()){
      G2Definition def = (G2Definition)defs.nextElement();
      if (def instanceof Definition)
	((Definition)def).removeDefinitionListener(classChangeAdapter);
      defTable.remove(def);
    }
  }

  @Override
  public String[] getKeys(){
    String[] group = new String[orderedKeys.size()];
    orderedKeys.copyInto(group);
    return group;
  }

  @Override
  public Object[] getStructuredKeys(){
    int len = structure.length;
    Object[] structuredKeys = new Object[len];
    for (int i=0; i<len; i++)
      structuredKeys[i] = structure[i];
    return structuredKeys; 
  }

  @Override
  public boolean isAvailable(String key){
    checkKey(key);
    ItemInfo info = (ItemInfo)itemTable.get(key);
    return info.available;
  }

  /** Returns the class name for both the SHORT_DESCRIPTION and LONG_DESCRIPTION. */
  @Override
  public String getDescription (String key, int type){
    checkKey(key);
    return key;
  }

  /** 
   * Returns an image of the specified size.  The icon-description of the G2 class 
   * indicated by the key used used to create the image. 
   */
  @Override
  public Image getIcon(String key, int size){
    checkKey(key);
    ItemInfo info = (ItemInfo)itemTable.get(key);
    Item item = info.itemForOverrides;
    Structure regionOverrides = null;    
    Structure variableOverrides = null;
    if (item instanceof Entity) {
      Entity entity = (Entity)item;
      try {
	regionOverrides = entity.getItemColorPattern ();
	variableOverrides = entity.getIconVariables ();
      } catch (G2AccessException g2ae) {
	Trace.exception(g2ae);
      }
    }
    try{
      if (size == SMALL_ICON){
	if (info.icon16x16 == null)
	  info.icon16x16 = G2ClassHelper.getIconForClass(context,
							 info.def,
							 info.className,
							 regionOverrides,	 
							 variableOverrides,
							 SMALL_ICON);
	return info.icon16x16;
      }
      else{
	if (info.icon32x32 == null)
	  info.icon32x32 = G2ClassHelper.getIconForClass(context,
							 info.def,
							 info.className,
							 regionOverrides, 
							 variableOverrides,
							 LARGE_ICON);
	return info.icon32x32;
      }
    }
    catch(G2AccessException ex){
      Trace.exception(ex);
      //do nothing and return null icon?
    }
    return null;
  }

  /** 
   *  Returns the stub created for the key. A
   *  com.gensym.util.UnexpectedException is
   *  thrown if a G2AccessException occurs attempting to create the item.
   */
  @Override
  public Object createObject(String key){
    checkKey(key);
    try{
      ItemInfo info = (ItemInfo)itemTable.get(key);
      return context.createItem(info.className);
    }
    catch(G2AccessException ex){
      throw new UnexpectedException(ex);
    }
  }

  /** Adds an ObjectCreatorListener. */
  @Override
  public void addObjectCreatorListener(ObjectCreatorListener listener){
    listeners.addElement(listener);
  }

  /** Removes a ObjectCreatorListener. */
  @Override
  public void removeObjectCreatorListener(ObjectCreatorListener listener){
    listeners.removeElement(listener);
  }

  /** Adds an StructuredObjectCreatorListener. */
  @Override
  public void addStructuredObjectCreatorListener(StructuredObjectCreatorListener listener){
    listeners.addElement(listener);
  }

  /** Removes a StructuredObjectCreatorListener. */
  @Override
  public void removeStructuredObjectCreatorListener(StructuredObjectCreatorListener listener){
    listeners.removeElement(listener);
  }

  private void checkKey (String key) {
    if (orderedKeys.indexOf (key) >= 0)
      return;
    throw new IllegalArgumentException (i18n.format("unknownKey", key));
  }

  /** Return the connection associated with the ObjectCreator. */
  public TwAccess getConnection(){
    return context;
  }

  protected void setAvailable(String key, boolean available){
    ItemInfo info = (ItemInfo)itemTable.get(key);
    info.available = available;
    notifyAvailabilityChanged(key);
  }

  private void notifyIconChanged(String key){
    ObjectCreatorEvent e = new ObjectCreatorEvent(this, key);
    Vector l;
    synchronized(this) {l = (Vector)listeners.clone();}
    Enumeration dispatchList = l.elements();
    while (dispatchList.hasMoreElements()){
      ObjectCreatorListener listener = ((ObjectCreatorListener)dispatchList.nextElement());
      listener.iconChanged(e);
    }
  }

  private void notifyAvailabilityChanged(String key){
    ObjectCreatorEvent e = new ObjectCreatorEvent(this, key);
    Vector l;
    synchronized(this) {l = (Vector)listeners.clone();}
    Enumeration dispatchList = l.elements();
    while (dispatchList.hasMoreElements()){
      ObjectCreatorListener listener = ((ObjectCreatorListener)dispatchList.nextElement());
      listener.availabilityChanged(e);
    }
  }

  private void notifyStructureChanged(){
    ObjectCreatorEvent e = new ObjectCreatorEvent(this, null);
    Vector l;
    synchronized(this) {l = (Vector)listeners.clone();}
    Enumeration dispatchList = l.elements();
    while (dispatchList.hasMoreElements()){
      Object element = dispatchList.nextElement();
      if (element instanceof StructuredObjectCreatorListener)
	((StructuredObjectCreatorListener)element).structureChanged(e);
    }
  }

  class ItemInfo {
    Symbol className;
    boolean available;
    Image icon16x16;
    Image icon32x32;
    G2Definition def;
    Item itemForOverrides;//ok to be null

    ItemInfo(Symbol className, boolean available, Image icon16x16, Image icon32x32,
	     G2Definition def,
	     Item itemForOverrides){
      this.className = className;
      this.available = available;
      this.icon16x16 = icon16x16;
      this.icon32x32 = icon32x32;
      this.def = def;
      this.itemForOverrides = itemForOverrides;
    }
  }

  class ClassChangeAdapter implements DefinitionListener{

    @Override
    public void staticAttributeChanged (DefinitionEvent e){
      Symbol attrName = e.getAttributeName ();
      if (SystemAttributeSymbols.ICON_DESCRIPTION_.equals(attrName))
	updateIcon(e);
      else if (SystemAttributeSymbols.INSTANTIATE_.equals(attrName)){
	try{
	  Definition def = e.getDefinitionOriginatingChange();
	  setAvailability(e, def.getInstantiate());
	}
	catch(G2AccessException ex){
	  Trace.exception(ex);
	}
      }
    }
    

    @Override
    public void directSuperiorClassesChanged (DefinitionEvent e) {
      updateIcon(e);
    }

    @Override
    public void classNameChanged (DefinitionEvent e){
      setAvailability(e, false);
    }

    @Override
    public void classInheritancePathChanged (DefinitionEvent e){
      updateIcon (e);
    }

    @Override
    public void deleted (DefinitionEvent e){
      setAvailability(e, false);
    }

    @Override
    public void classSpecificAttributesChanged (DefinitionEvent e) {
      // ?
    }

    private void updateIcon(DefinitionEvent e){
      Definition def = e.getDefinitionOriginatingChange();
      String key = (String)defTable.get(def);
      if (key != null){
	ItemInfo info = (ItemInfo)itemTable.get(key);
	if (info != null){
	  info.icon16x16 = null;
	  info.icon32x32 = null;
	  notifyIconChanged(key);
	}
      }
    }

    private void setAvailability(DefinitionEvent e, boolean available){
      Definition def = e.getDefinitionOriginatingChange();
      String key = (String)defTable.get(def);
      if (key != null)
	setAvailable(key, available);
    }
  }
    
}








