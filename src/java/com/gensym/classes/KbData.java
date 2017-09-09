
package com.gensym.classes;

import com.gensym.ntw.util.KbModuleListener;
import com.gensym.ntw.util.KbMessageListener;
import java.util.Hashtable;

/**
 * Need not be Serializable
 */
class KbData {

  volatile boolean currentlySubscribed;
  
  volatile KbModuleListener listener;

  volatile Hashtable moduleTable;

  volatile Module topLevelModule;

  KbData () {
    moduleTable = new Hashtable (29);
  }

  volatile KbMessageListener msgListener;

  void pprint (java.io.PrintWriter out) {
    java.util.Enumeration e = moduleTable.keys ();
    while (e.hasMoreElements ()) {
      java.lang.Object moduleKey = e.nextElement ();
      ModuleImpl m = (ModuleImpl) moduleTable.get (moduleKey);
      m.pprint (out);
    }
  }
}
