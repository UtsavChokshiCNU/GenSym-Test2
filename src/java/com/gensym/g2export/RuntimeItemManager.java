package com.gensym.g2export;

import java.util.Hashtable;
import java.util.Enumeration;
import com.gensym.message.Trace;

/**
 * This class is a temporary attempt at providing local exported g2 classes
 * with the ability to detect changes in their classes
 */
public class RuntimeItemManager {

  private static RuntimeItemManager runtimeItemManager = null;

  // In 1.2 these can be weak reference Hashtables
  private Hashtable itemLookup = new Hashtable(11);
  private Hashtable itemClassChangeTable = new Hashtable(11);

  private RuntimeItemManager() {
  }

  public static RuntimeItemManager getRuntimeItemManager() {
    if (runtimeItemManager == null)
      runtimeItemManager = new RuntimeItemManager();
    return runtimeItemManager;
  }

  public synchronized void registerItem(G2__Base item) {
    itemLookup.put(item, item);
  }

  public synchronized void registerItem(G2__Base item, G2__Base newItem) {
    itemLookup.put(item, newItem);
  }

  public G2__Base getCurrentItem(G2__Base item) {
    Class itemClassChange = (Class)itemClassChangeTable.get(item);
    if (itemClassChange != null) {
      G2__Base currentItem = (G2__Base)itemLookup.get(item);
      // Create a new version of this item
      // extra work to be done here, copy internal state etc...
      // cheat for now dumb new instance....
      G2__Base newself = null;
      try {
	newself = (G2__Base)itemClassChange.newInstance();
	itemClassChangeTable.remove(item);
	registerItem(item, newself);
	return newself;
      } catch (Exception e) {
	Trace.exception(e);
	e.printStackTrace();
      }
      return item;
    } else {
      G2__Base ret = (G2__Base)itemLookup.get(item);
      return ret;
    }
  }

  public void implementationChanged(Class interfaceClass, Class newImplementationClass) {
    if (!interfaceClass.isInterface()) return;
    // Look through all items registered
    for (Enumeration e = itemLookup.keys(); e.hasMoreElements();) {
      G2__Base item = (G2__Base)e.nextElement();
      if (interfaceClass.isInstance(item)) {
	itemClassChangeTable.put(item, newImplementationClass);
      }
    }
  }
    
}
