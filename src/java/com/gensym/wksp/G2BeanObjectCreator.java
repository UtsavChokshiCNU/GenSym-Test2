
package com.gensym.wksp;

import java.awt.Image;
import java.beans.*;
import java.util.Vector;
import com.gensym.message.*;
import com.gensym.ui.*;
import com.gensym.util.*;
import com.gensym.jgi.*;
import com.gensym.ntw.*;
import com.gensym.ntw.util.*;
import com.gensym.classes.Item;
import com.gensym.classes.modules.t2beans.*;

public class G2BeanObjectCreator extends G2ObjectCreator implements StructuredObjectCreator {

  TwConnection cxn;
  Sequence beanClasses;
  Vector listeners = new Vector ();
  T2beansRegistry beansRegistry;

  private static final Symbol T2BEANS_REGISTRY_ = Symbol.intern ("T2BEANS-REGISTRY");
  private static final Symbol BEANS_REGISTRY_ = Symbol.intern ("BEANS-REGISTRY");
  private static final Symbol JAVA_CLASS_NAME_ = Symbol.intern ("JAVA-CLASS-NAME");
  private static final Symbol G2_CLASS_NAME_ = Symbol.intern ("G2-CLASS-NAME");
  private static final Symbol T2BEANS_GET_IMPORTED_BEAN_CLASS_NAMES_ = Symbol.intern ("T2BEANS-GET-IMPORTED-BEAN-CLASS-NAMES");

  public G2BeanObjectCreator (TwConnection connection) throws G2AccessException {
    super (connection, new Symbol[] {});
    cxn = connection;
    beansRegistry = (T2beansRegistry) connection.getUniqueNamedItem (T2BEANS_REGISTRY_, BEANS_REGISTRY_);
    beansRegistry.addG2_RegistryListener (new RegistryAdapter ());
    new BeanClassUpdater (this).start ();
    if (beanClasses == null) {
      synchronized (this) {
	try {
	  wait (10000);
	} catch (InterruptedException ie) {
	  Trace.exception (ie);
	}
      }
    }
  }


  void updateBeanClasses () {
    try {
      beanClasses =
	(Sequence) cxn.callRPC (T2BEANS_GET_IMPORTED_BEAN_CLASS_NAMES_, new Object[] {});
      System.out.println ("BeanClasses = " + beanClasses);
      notifyListeners ();
    } catch (G2AccessException g2ae) {
      Trace.exception (g2ae);
    }
  }

  private void notifyListeners () {
    if (listeners.size () == 0)
      return;
    ObjectCreatorEvent evt = new ObjectCreatorEvent (this, null);
    for (int i=0; i<listeners.size (); i++) {
      ObjectCreatorListener l = (ObjectCreatorListener) listeners.elementAt (i);
      if (l instanceof StructuredObjectCreatorListener)
	((StructuredObjectCreatorListener)l).structureChanged (evt);
    }
  }

  private java.lang.Object getClassDataFromEvent (G2_RegistryEvent evt) {
    try {
      return evt.getClassData ();
    } catch (G2AccessException g2ae) {
      throw new CorruptionException (g2ae);
    }
  }

  
  class RegistryAdapter implements G2_RegistryListener {
    @Override
    public void handleRegistryInitialValues (G2_RegistryEvent evt) {
      beanClasses = (Sequence) getClassDataFromEvent (evt);
      System.out.println (" > > 1 < < " + beanClasses);
      Object creator = G2BeanObjectCreator.this;
      notifyListeners ();
      synchronized (creator) {
	creator.notify ();
      }
    }
    @Override
    public void beanAdded (G2_RegistryEvent evt) {
      Structure classData = (Structure) getClassDataFromEvent (evt);
      beanClasses.addElement (classData);
      System.out.println (" > > 2 < < " + beanClasses);
      notifyListeners ();
    }
    @Override
    public void beanRemoved (G2_RegistryEvent evt) {
      Structure classData = (Structure) getClassDataFromEvent (evt);
      String deletedClassName = (String) classData.getAttributeValue (JAVA_CLASS_NAME_, null);
      for (int i=0; i<beanClasses.size (); i++) {
	if (deletedClassName.equals (((Structure) (beanClasses.elementAt (i))).getAttributeValue (JAVA_CLASS_NAME_, null))) {
	  beanClasses.removeElementAt (i);
	  break;
	}
      System.out.println (" > > 3 < < " + beanClasses);
      notifyListeners ();
      }
    }
  }

  @Override
  public String[] getKeys () {
    if (beanClasses == null) {
      System.err.println ("\n\n BEAN CLASSES = null!! \n\n");
      updateBeanClasses ();
    }
    String[] keys = new String[beanClasses.size ()];
    for (int i=0; i<beanClasses.size (); i++)
      keys[i] = (String) ((Structure) beanClasses.elementAt (i)).getAttributeValue (JAVA_CLASS_NAME_, null);
    return keys;
  }

  @Override
  public java.lang.Object[] getStructuredKeys () {
    return getKeys ();
  }

  @Override
  public boolean isAvailable (String key) {
    return true; // running
  }

  @Override
  public String getDescription (String key, int type) {
    int indexOfSep = key.lastIndexOf ('.');
    return indexOfSep >= 0 ? key.substring (indexOfSep + 1) : key;
  }

  @Override
  public java.lang.Object createObject (String key) {
    Symbol g2ClassName_ = null;
    for (int i=0; i<beanClasses.size(); i++) {
      if (key.equals (((Structure) beanClasses.elementAt (i)).getAttributeValue (JAVA_CLASS_NAME_, null))) {
	g2ClassName_ = (Symbol)
	  ((Structure) beanClasses.elementAt (i)).getAttributeValue (G2_CLASS_NAME_, null);
	break;
      }
    }
    try {
      Item itm = cxn.createItem (g2ClassName_);
      return itm;
    } catch (G2AccessException g2ae) {
      Trace.exception (g2ae);
      return null;
    }
  }

  @Override
  public Image getIcon (String key, int type) {
    try {
      BeanInfo beanInfo = Introspector.getBeanInfo (Class.forName (key));
      return beanInfo.getIcon ((type == SMALL_ICON) ?
			       BeanInfo.ICON_COLOR_16x16 :
			       BeanInfo.ICON_COLOR_32x32);
    } catch (Exception e) {
      Trace.exception (e);
      return null;
    }
  }

  @Override
  public void addObjectCreatorListener (ObjectCreatorListener ocl) {
    listeners.addElement (ocl);
  }

  @Override
  public void removeObjectCreatorListener (ObjectCreatorListener ocl) {
    listeners.removeElement (ocl);
  }

  @Override
  public void addStructuredObjectCreatorListener (StructuredObjectCreatorListener ocl) {
    listeners.addElement (ocl);
  }

  @Override
  public void removeStructuredObjectCreatorListener (StructuredObjectCreatorListener ocl) {
    listeners.removeElement (ocl);
  }

}

class BeanClassUpdater extends Thread {

  private G2BeanObjectCreator creator;

  BeanClassUpdater (G2BeanObjectCreator creator) {
    super ("Bean-Classes-Updater-Thread");
    this.creator = creator;
  }

  @Override
  public void run () {
    for (;;) {
      try {
	if (1 == 1) break;
	creator.updateBeanClasses ();
	Thread.sleep (20000);
      } catch (InterruptedException ie) {}
    }
  }
}
