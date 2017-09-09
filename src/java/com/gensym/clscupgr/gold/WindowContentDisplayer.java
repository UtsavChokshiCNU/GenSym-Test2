
package com.gensym.clscupgr.gold;

import java.lang.reflect.Method;

import java.awt.Component;
import java.awt.BorderLayout;
import java.awt.Dialog;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import com.gensym.core.UiApplication;
import com.gensym.core.DebugUtil;
import com.gensym.dlg.ErrorDialog;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.util.WindowUtil;

public class WindowContentDisplayer {

  private Dialog displayWindow;
  private /*Component*/ContentDisplayer htmlDisplayComponent;

  WindowContentDisplayer (TwAccess connection) {
    //cxn = connection;
  }

  public void display (String urlLocation) {
    try {
      if (displayWindow == null) {
	displayWindow = new Dialog (UiApplication.getCurrentFrame ());
	displayWindow.setLayout (new BorderLayout ());
	String registeredDisplayClass = 
	  System.getProperty ("com.gensym.clscupgr.gold.HTMLDisplayComponentClass",
			      "com.gensym.clscupgr.gold.HotJavaHTMLDisplayer");
	Class displayerClass = Class.forName (registeredDisplayClass);
	//htmlDisplayComponent = (Component) displayerClass.newInstance ();
	htmlDisplayComponent = (ContentDisplayer) displayerClass.newInstance ();
	displayWindow.add ((Component)htmlDisplayComponent, BorderLayout.CENTER);
	WindowUtil.centerFrame (UiApplication.getCurrentFrame(), displayWindow);
	displayWindow.setBounds (100, 100, 700, 500);
	displayWindow.setVisible (true);
	displayWindow.addWindowListener (new WindowAdapter () {
	  @Override
	  public void windowClosing (WindowEvent wEvt) {
	    displayWindow.setVisible (false);
	    displayWindow.dispose ();
	    displayWindow = null;
	  }
	});
      }
      System.out.println ("Displaying URL in " + htmlDisplayComponent);
      /*
      Method displayMethod = Class.forName ("sunw.hotjava.bean.HotJavaBrowserBean").getMethod
	  ("setDocumentString", new Class[] {String.class});
      displayMethod.invoke (htmlDisplayComponent, new Object[] {urlLocation});
      */
      htmlDisplayComponent.displayDocument (urlLocation);
      System.out.println ("Finished Displaying!");
    } catch (Exception e) {
      com.gensym.message.Trace.exception (e);
      //System.out.println ("Backtrace = \n" + DebugUtil.getStackTrace ());
      new ErrorDialog (null, "Error displaying Help", false,
		       DebugUtil.getStackTrace (),
		       null).setVisible (true);
    }
  }

}
