
package com.gensym.clscupgr.gold;

import java.beans.*;
import java.awt.Dialog;
import java.awt.Cursor;
import java.awt.event.*;

import sunw.hotjava.bean.HotJavaBrowserBean;
import sunw.hotjava.bean.HotJavaDocumentStack;
import sunw.hotjava.bean.HotJavaSystemState;
import sunw.hotjava.doc.ElementInfo;

public class HotJavaHTMLDisplayer extends HotJavaBrowserBean implements ContentDisplayer {

  HotJavaDocumentStack stackBean;
  HotJavaSystemState stateBean;

  public HotJavaHTMLDisplayer () {
    stackBean = new HotJavaDocumentStack ();
    stateBean = new HotJavaSystemState ();
    stackBean.addBrowserHistoryListener (this);
    addBrowserHistoryListener (stackBean);
    addPropertyChangeListener (new PropertyChangeListener () {
      @Override
      public void propertyChange (PropertyChangeEvent pEvt) {
	System.out.println ("PC = " + pEvt.getPropertyName () + " = " + pEvt.getNewValue ());
	if (pEvt.getNewValue() instanceof ElementInfo) {
	  ElementInfo io = (ElementInfo)pEvt.getNewValue ();
	  if (io.hrefURL != null)
	    setCursor (Cursor.getPredefinedCursor (Cursor.HAND_CURSOR));
	  else
	    setCursor (Cursor.getDefaultCursor ());
	  System.out.println ("  " + io.imageURL + ", " + io.hrefURL + ", " + io.event);
	}
	if (pEvt.getPropertyName().equals ("documentTitle")) {
	  System.out.println ("isTitle");
	  ((Dialog)getParent ()).setTitle ((String)pEvt.getNewValue ());
	} else
	  System.out.println ("notTitle");
      }
    });
    addVetoableChangeListener (new VetoableChangeListener () {
      @Override
      public void vetoableChange (PropertyChangeEvent pEvt) {
	System.out.println ("VC = " + pEvt.getPropertyName () + " = " + pEvt.getNewValue ());
      }
    });
    addMouseMotionListener (new MouseMotionListener () {
      @Override
      public void mouseMoved (MouseEvent mEvt) {
	System.out.println ("IE = " + getIndicatedElement ());
      }
      @Override
      public void mouseDragged (MouseEvent mEvt) {
	//
      }
    });
  }

  @Override
  public void displayDocument (String urlLocation) {
    setDocumentString (urlLocation);
  }

  @Override
  public boolean isNextDocumentAvailable () {
    return stackBean.isNextAvailable ();
  }
  
  @Override
  public boolean isPreviousDocumentAvailable () {
    return stackBean.isPreviousAvailable ();
  }

  @Override
  public void nextDocument () {
    stackBean.nextDocument ();
  }

  @Override
  public void previousDocument () {
    stackBean.previousDocument ();
  }

  public void skipToDocument (int delta) {

  }

}
