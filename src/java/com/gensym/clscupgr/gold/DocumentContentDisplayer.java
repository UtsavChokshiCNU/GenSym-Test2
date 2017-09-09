
package com.gensym.clscupgr.gold;

import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.Component;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Label;
import java.lang.reflect.Method;

import com.gensym.core.DebugUtil;
import com.gensym.core.UiApplication;
import com.gensym.message.Trace;
import com.gensym.dlg.ErrorDialog;
import com.gensym.mdi.MDIFrame;
import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2ConnectionAdapter;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.shell.util.TW2Document;

public class DocumentContentDisplayer implements ContentDisplayer {

  private HTMLDisplayDocument htmlDisplayDocument;
  private TwAccess cxn;

  public DocumentContentDisplayer (TwAccess connection) {
    cxn = connection;
    cxn.addG2ConnectionListener (new G2ConnectionAdapter () {
      @Override
      public void g2ConnectionClosed (G2ConnectionEvent evt) {
	cxn.removeG2ConnectionListener (this);
	cxn = null;
      }
    });
  }

  public void display (String urlLocation) {
    if (htmlDisplayDocument == null) {
      htmlDisplayDocument = new HTMLDisplayDocument (cxn);
      ((MDIFrame)UiApplication.getCurrentFrame()).getManager().addDocument (htmlDisplayDocument,
									    htmlDisplayDocument.getPreferredSize());
    }
    System.out.println ("Displaying in HTML Doc = " + htmlDisplayDocument);
    htmlDisplayDocument.display (urlLocation);
  }

  class HTMLDisplayDocument extends TW2Document {
    Component htmlDisplayComponent;
    HTMLDisplayDocument (TwAccess cxn) {
      super (cxn);
      try {
	getContentPane().setLayout (new BorderLayout ());
	String registeredDisplayClass = 
	  System.getProperty ("com.gensym.clscupgr.gold.HTMLDisplayComponentClass",
			      "sunw.hotjava.bean.HotJavaBrowserBean");
	Class displayerClass = Class.forName (registeredDisplayClass);
	htmlDisplayComponent = (Component) displayerClass.newInstance ();
      } catch (ClassNotFoundException cnfe) {
	Trace.exception (cnfe);
      } catch (IllegalAccessException iae) {
	Trace.exception (iae);
      } catch (InstantiationException ie) {
	Trace.exception (ie);
      }
      if (htmlDisplayComponent == null) {
	htmlDisplayComponent = new Container () {
	  @Override
	  public Dimension getPreferredSize () {
	    return new Dimension (400, 200);
	  }
	};
	((Container)htmlDisplayComponent).setLayout (new FlowLayout ());
	((Container)htmlDisplayComponent).add (new Label ("HTML Bean not found"));
      }
      getContentPane().add (htmlDisplayComponent, BorderLayout.CENTER);
    }

    void display (String urlLocation) {
      try {
	Method displayMethod = Class.forName ("sunw.hotjava.bean.HotJavaBrowserBean").getMethod
	  ("setDocumentString", new Class[] {String.class});
	displayMethod.invoke (htmlDisplayComponent, new Object[] {urlLocation});
      } catch (Exception e) {
	new ErrorDialog (null, "Error displaying Help", false,
			 DebugUtil.getStackTrace (),
			 null).setVisible (true);
      }
    }

    @Override
    public void setClosed(boolean closed) throws java.beans.PropertyVetoException {
      super.setClosed (closed);
      if (closed)
	htmlDisplayDocument = null;
    }
  }

  @Override
  public void displayDocument (String urlLocation) {
  }

  @Override
  public boolean isNextDocumentAvailable () {
    return false;
  }
  
  @Override
  public boolean isPreviousDocumentAvailable () {
    return false;
  }

  @Override
  public void nextDocument () {
  }

  @Override
  public void previousDocument () {
  }

}
