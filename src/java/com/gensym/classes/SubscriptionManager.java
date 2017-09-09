package com.gensym.classes;

import java.util.Hashtable;
import java.util.Vector;
import java.util.Enumeration;

import com.gensym.util.Symbol;
import com.gensym.util.EventMulticaster;
import com.gensym.util.ItemListener;

/**
 * SubscriptionManager is a class to maintain and manager item subscription process.
 * The class can store subscribed attributes with their itemlistener, and also keep
 * corresponding subscription handles for unsubscribing later.
 * @author fy 03/10/00
 */

public class SubscriptionManager {
  private static final Symbol WILDCARD_ = Symbol.intern("*");

  // store itemlistener with attribute name as a key for dispatching itemevent to get itemlistener
  private Hashtable  attributeHashtable = new Hashtable();
  private ItemListener allListeners;

  // store attribute names for additemlistener
  private Vector addedSubscriptions;
  private Vector removedSubscriptions;

  // for unsubscribing in two-tier and three-tier
  private Vector attributeNames;
  private Vector subscriptionHandles;

  //WILDCARD flag
  private boolean hasWILDCARD = false;
  int removedWILDCARD = 0;


  public SubscriptionManager() {
  }

  // add subscribing attributes with thier listeners into
  public void addEntry(ItemListener itemListener, Symbol[] attributeNames) {
    allListeners = EventMulticaster.add(allListeners, itemListener);
    Vector newAddedItems = new Vector();
    boolean isWILDCARD = false;
    boolean isNew = false;

    if (attributeHashtable.isEmpty()) {
    	isNew = true;
    }
    synchronized (attributeHashtable) {
      ItemListener aListener;
      for (int i=0; i < attributeNames.length; i++) {
        if (attributeNames[i].equals(WILDCARD_)) {
        	isWILDCARD = true;
        }
        aListener = (ItemListener) attributeHashtable.get(attributeNames[i]);
        if (aListener == null && !(attributeNames[i].equals(WILDCARD_)))
           newAddedItems.add(attributeNames[i]);

        attributeHashtable.put(attributeNames[i], EventMulticaster.add(aListener, itemListener));
      }
    }

    if (!hasWILDCARD && isWILDCARD) {   //there is no WILDCARD in hashtable and the coming new one is
      //add wildcard into addedSubscriptions vector
      Vector aVec = new Vector(1);
      aVec.add(WILDCARD_);
      addedSubscriptions = aVec;

      //add existing keys into removedSubscriptions vector
      if (isNew)
        removedSubscriptions = null;
      else {
        Vector rVec = new Vector();
        for (Enumeration e = attributeHashtable.keys() ; e.hasMoreElements() ;) {
            rVec.add(e.nextElement());
        }
	rVec.remove(WILDCARD_);
        removedSubscriptions = rVec;
      }

    } else if (!hasWILDCARD && !isWILDCARD) {   //no WILDCARD at all
      if (!newAddedItems.isEmpty())
          addedSubscriptions = newAddedItems;
      else
          addedSubscriptions = null;

      removedSubscriptions = null;

    } else {   //there is WILDCARD in the hashtable
     addedSubscriptions = null;
     removedSubscriptions = null;

    }

    hasWILDCARD = attributeHashtable.containsKey(WILDCARD_);
  }

  // remove entry from the hashtable
  public void removeEntry(ItemListener itemListener, Symbol[] attributeNames) {
    allListeners = EventMulticaster.remove(allListeners, itemListener);
    Vector newRemovedItems = new Vector();
    boolean isWILDCARD = false;

    synchronized (attributeHashtable) {
      ItemListener currentListener;
      ItemListener newListener;
      for (int i=0; i < attributeNames.length; i++) {
        if (attributeNames[i].equals(WILDCARD_)) {
          isWILDCARD = true;
          removedWILDCARD ++;
        }
        currentListener = (ItemListener) attributeHashtable.get(attributeNames[i]);
        if (currentListener == null){
        	continue;
        }
        if ((newListener = EventMulticaster.remove(currentListener, itemListener)) == null){
          attributeHashtable.remove(attributeNames[i]);
          newRemovedItems.add(attributeNames[i]);
        } else {
          attributeHashtable.put(attributeNames[i], newListener);
        }
      }
    }

    if (hasWILDCARD && !attributeHashtable.containsKey(WILDCARD_)) {
      //had a wildcard but no longer have any
      Vector rVec = new Vector(1);
      rVec.add(WILDCARD_);
      removedSubscriptions = rVec;

      //add existing keys into addedSubscriptions vector
      if (!attributeHashtable.isEmpty()) {
        Vector aVec = new Vector();
        for (Enumeration e = attributeHashtable.keys() ; e.hasMoreElements() ;) {
          Symbol sym = (Symbol) e.nextElement();
          if (!sym.equals(WILDCARD_))
            aVec.add(sym);
        }
        addedSubscriptions = aVec;
      } else {
        addedSubscriptions = null;
      }

    } else if (!hasWILDCARD && !isWILDCARD) { //no WILDCARD
      if (!newRemovedItems.isEmpty())
          removedSubscriptions =  newRemovedItems;
      else
          removedSubscriptions = null;
      addedSubscriptions = null;

    } else {    //there is WILDCARD but removing item is not WILDCARD OR no WILDCARD but removing item is WILDCARD
      removedSubscriptions = null;
      addedSubscriptions = null;

    }
    hasWILDCARD = attributeHashtable.containsKey(WILDCARD_);

  }

  // check if the attribute is cachable and exists in the hashtable
  public final boolean isSubscribed(Symbol attrName, G2__BaseImpl item) {
    if (hasWILDCARD)
      return (item.attributeSendsUpdates(attrName) &&
	      attributeHashtable.containsKey(WILDCARD_));
    else
      return (attributeHashtable.containsKey(attrName));
  }

  public boolean isSubscribed() {
    return  (!attributeHashtable.isEmpty());
  }

  // add attribute/handle data into for unsubscribing
  public void setAttributeHandleData(Symbol attrName, int sHandle) {
    if (attributeNames == null)
      attributeNames = new Vector();
    if (subscriptionHandles == null)
      subscriptionHandles = new Vector();

    attributeNames.add(attrName);
    subscriptionHandles.add(sHandle);

  }

  public void removeAttributeHandleData(Symbol attrName, int sHandle) {
    if ((attributeNames == null) || (subscriptionHandles == null)) {
    	return;
    }

    for (int i=0; i < subscriptionHandles.size(); i++) {
        if (sHandle == ((Integer) subscriptionHandles.get(i)).intValue()) {
          attributeNames.remove(i);
          subscriptionHandles.remove(i);
          break;
        }
    }

    if ((attributeNames.isEmpty()) || (subscriptionHandles.isEmpty())) {
      attributeNames = null;
      subscriptionHandles = null;
    }
  }

  public Symbol getAttributeNameByHandle(int handle) {
    Symbol attrName = null;
    if (attributeNames == null){
    	return null;
    }
    for(int i=0; i < subscriptionHandles.size(); i++) {
      if (handle == ((Integer) subscriptionHandles.get(i)).intValue()) {
        attrName = (Symbol) attributeNames.get (i);
        break;
      }
    }

    return attrName;
  }

  public int getHandleByAttributeName (Symbol attrName) {
    int handle = 0;
    if (subscriptionHandles == null){
    	return 0;
    }
    for(int i=0; i < attributeNames.size(); i++) {
      if (attrName.equals((Symbol) attributeNames.get(i))) {
        handle = ((Integer) subscriptionHandles.get(i)).intValue();
        break;
      }
    }

    return handle;
  }

  public boolean isSuchKeyInAttributeHashtable(Symbol attrName) {
    return attributeHashtable.containsKey(attrName);
  }


    ItemListener getAllListeners () {
	return allListeners;
    }

  /** check if there is a WILDCARD in hashtable. if yes, get an eventmulticaster itemlistener
   * otherwise get a simple itemListener. if there is a WILDCARD in the hastabel, the returning
   * itemlisteners must include the WILDCARD itemlisteners no matter what attrName is.
   * @author fy  03/05/00
   */
  public ItemListener getItemListeners(Symbol attrName) {
    if (attrName.equals(WILDCARD_)){
    	return allListeners;
    }
    ItemListener itemListener = (ItemListener) attributeHashtable.get(attrName);

    if (hasWILDCARD)
      if (itemListener != null)
        itemListener = EventMulticaster.add(itemListener, (ItemListener) attributeHashtable.get(WILDCARD_));
      else
        itemListener = (ItemListener) attributeHashtable.get(WILDCARD_);

    return  itemListener;
  }


  public Vector getAddedSubscriptions() {
    return addedSubscriptions;
  }

  public Vector getRemovedSubscriptions () {
    return removedSubscriptions;
  }

  public boolean hasWILDCARD() {
    return hasWILDCARD;
  }
}
