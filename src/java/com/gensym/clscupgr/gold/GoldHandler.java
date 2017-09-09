
package com.gensym.clscupgr.gold;

import java.lang.reflect.Method;
//import java.lang.reflect.NoSuchMethodException;
import com.gensym.core.GensymApplication;
import com.gensym.message.Trace;
import com.gensym.util.Symbol;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.TwAccess;
import com.gensym.clscupgr.ModuleHandler;

import com.gensym.mdi.MDIApplication;

public class GoldHandler implements ModuleHandler {

  private WindowContentDisplayer contentDisplayer;

  private static final Symbol _GOLD_LAUNCH_OR_REPOINT_T2_BROWSER_ = Symbol.intern ("_GOLD-LAUNCH-OR-REPOINT-T2-BROWSER");

  public GoldHandler () {
  }

  @Override
  public void moduleLoaded (TwAccess cxn,  Symbol moduleName_) {
    try {
      Method method =
	getClass().getMethod("displayURL", new Class[] { String.class });
      cxn.registerJavaMethod(this, method,
			     _GOLD_LAUNCH_OR_REPOINT_T2_BROWSER_,true);
      System.out.println ("Registered " + method +  " for " + _GOLD_LAUNCH_OR_REPOINT_T2_BROWSER_);
      /*      if (false)
	contentDisplayer = new DocumentContentDisplayer (cxn);
      else*/
	contentDisplayer = new WindowContentDisplayer (cxn);
    } catch (NoSuchMethodException nsme) {
      Trace.exception (nsme);
    }
  }

  @Override
  public void moduleUnloaded (TwAccess cxn, Symbol moduleName_) {
    // unregisterJavaMethod
  }

  public void registerContentDisplayer (WindowContentDisplayer newDisplayer) {
    if (newDisplayer == null) {
      throw new IllegalArgumentException ("ContentDisplayer cannot be null");
    }
    contentDisplayer = newDisplayer;
  }

  public void displayURL (String url) {
    System.out.println ("GoldInitializer.displayURL (" + url + ")");
    try {
      contentDisplayer.display (url);
    } catch (Throwable e) {
      Trace.exception (e);
    }
  }

}
