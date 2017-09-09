/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 DialogCommand.java
 *
 */

package com.gensym.controls;

import java.util.Vector;
import com.gensym.dlgruntime.DialogStateEvent;
import com.gensym.dlgruntime.DialogStateListener;
import com.gensym.dlgruntime.DialogCommandEvent;
import com.gensym.dlgruntime.DialogCommandListener;
import java.util.Locale;
import com.gensym.message.Trace;
import com.gensym.message.Resource;
import com.gensym.message.MessageKey;


 /**
  * An invisible bean which is responsible for notifying it's
  * listeners when it's close(), apply () or ok() methods have
  * bean invoked. This allows interested objects to take
  * appropriate actions with the knowledge of these events.
  * It also has the option of making sure that the ItemProxy
  * beans on the Dialog handle these changes correctly.
  * @see com.gensym.dlgruntime.DialogCommandListener
  */

public class DialogCommand implements java.io.Serializable {
  /*
   * Standard Tracing Requirements
   */
  private static MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.controls.DialogCommand",
			   DialogCommand.class);
  private static Resource i18nTrace =
  Trace.getBundle("com.gensym.controls.TraceMessages", Locale.getDefault());
  private static final int DEF_TRACE_LEVEL = 5;
  private static final int DEF_WARN_LEVEL  = 2;
  private static final int BASIC_TRACE_LEVEL = 3;
  private static final long classLoadTimeout = 0; // forever
  private boolean handleProxies = true;

  /*
   * Allow deserialization in the face of changes to this class.
   */
  static final long serialVersionUID = -8467662549514031680L;
  
  private Vector dialogListeners = new Vector();
  private Vector dialogCommandListeners = new Vector();
  private ItemProxy[] proxies;
  
  /**
   * Constructor for this bean
   */
   public DialogCommand() {
   }

  /**
   * Indicates if the DialogCommand will handle the
   * flushing and shutdown of all ItemProxy beans
   * on this dialog automatically. If this property
   * is set to true, the DialogCommand will upload
   * the changes in the ItemProxy on FLUSH and
   * clear the stubs from the Proxy on SHUTDOWN.
   * @see com.gensym.controls.ItemProxy#upload
   * @see com.gensym.controls.ItemProxy#setProxy
   * @see com.gensym.dlgruntime.DialogCommandListener#dialogFlushed
   * @see com.gensym.dlgruntime.DialogCommandListener#dialogShutdown
   */
  public boolean getHandleProxiesAutomatically () {
    return handleProxies;
  }

  /**
   * Sets the mode to handle ItemProxy beans on the
   * dialog on state changes.
   * @see #getHandleProxiesAutomatically
   */
  public void setHandleProxiesAutomatically (boolean handleProxies) {
    this.handleProxies = handleProxies;
  }

  /**
   * Called on dialog launch.
   * @see com.gensym.dlgruntime.DialogLauncher#launch
   */
  public void open () {
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "beanopening", this);
    fireDialogCommandEvent (new DialogCommandEvent (this, DialogCommandEvent.LAUNCH));
    fireDialogStateEvent (new DialogStateEvent (this, DialogStateEvent.LAUNCH));
  }

  /**
   * Take actions appropriate to closing a dialog
   * It then fires a SHUTDOWN DialogCommandEvent to notify
   * all listeners and handles ItemProxy cleanups
   * if necessary.
   * @see #setProxies
   * @see #getHandleProxiesAutomatically
   */
   public void close() {
     Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "beanclosing", this);
     fireDialogCommandEvent (new DialogCommandEvent (this, DialogCommandEvent.SHUTDOWN));
     fireDialogStateEvent (new DialogStateEvent (this, DialogStateEvent.SHUTDOWN));
     unhookProxies ();
   }

  /**
   * Apply changes and let the dialog stay up.
   * The DialogCommand fires a FLUSH event and
   * handles ItemProxy uploads if necessary.
   * @see #setProxies
   * @see #getHandleProxiesAutomatically
   */
  public void apply () {
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "beanapplying", this);
    fireDialogCommandEvent (new DialogCommandEvent (this, DialogCommandEvent.FLUSH));
    fireDialogStateEvent (new DialogStateEvent (this, DialogStateEvent.FLUSH));
    uploadProxies ();
  }

  /**
   * Apply changes and close this dialog.
   * The DialogCommand fires a FLUSH DialogCommandEvent
   * to all listeners to commit their data, and
   * a subsequent SHUTDOWN DialogStateEvent to
   * indicate that the launch was complete
   * @see #setProxies
   * @see #getHandleProxiesAutomatically
   */
   public void ok() {
     Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "beanokaying", this);
     fireDialogCommandEvent (new DialogCommandEvent (this, DialogCommandEvent.FLUSH));
     fireDialogStateEvent (new DialogStateEvent (this, DialogStateEvent.FLUSH));
     uploadProxies ();
     fireDialogCommandEvent (new DialogCommandEvent (this, DialogCommandEvent.SHUTDOWN));
     fireDialogStateEvent (new DialogStateEvent (this, DialogStateEvent.SHUTDOWN));
     unhookProxies ();
   }

  /**
   * Set the proxies to unhook. This method should typically be
   * called by the DialogLauncher that is managing the launch
   * of the dialog to allow the DialogCommand bean to handle
   * the ItemProxy synchronization and cleanups.
   * @param proxies An array of ItemProxy objects that need to be
   *    have their Item stubs set to null when the ok or close
   *    methods of this Bean is invoked.
   * @see #ok
   * @see #close
   * @see #apply
   * @see com.gensym.dlgruntime.DialogLauncher
   */
  public void setProxies (ItemProxy[] proxies) {
    //System.out.println ("DC: setProxies with " + proxies.length + " proxies");
    //System.out.println (com.gensym.core.DebugUtil.getStackTrace ());
    this.proxies = proxies;
  }

  /**
   * Adds a listener for DialogState events to this bean
   */
  //public void addDialogStateListener (DialogStateListener listener) {
  //dialogListeners.addElement(listener);
  //}

  /**
   * Removes a listener for DialogState events from this bean
   */
   public void removeDialogStateListener (DialogStateListener listener) {
     dialogListeners.removeElement(listener);
   }


  /**
   * Adds a listener for DialogState events to this bean
   */
  public void addDialogCommandListener (DialogCommandListener listener) {
    dialogCommandListeners.addElement(listener);
  }

  /**
   * Removes a listener for DialogState events from this bean
   */
   public void removeDialogCommandListener (DialogCommandListener listener) {
     dialogCommandListeners.removeElement(listener);
   }

  /**
   * Sends DialogStateEvents to all the DialogStateListeners
   * for this bean
   */
   void fireDialogStateEvent (DialogStateEvent event) {
       int size = dialogListeners.size();
       int evtID = event.getID ();
       //System.out.println (this + " : Sending " + event + " to " + dialogListeners);
       for (int i=0; i < size; i++) {
	 switch (evtID)
	   {
	   case DialogStateEvent.SHUTDOWN:
	     ((DialogStateListener)(dialogListeners.elementAt(i))).dialogLaunchComplete (event);
	     break;
	   case DialogStateEvent.FLUSH:
	     ((DialogStateListener)(dialogListeners.elementAt(i))).dialogFlushed (event);
	     break;
	   default:
	   }
       }
   }


  /**
   * Sends DialogCommandEvents to all the DialogCommandListeners
   * for this bean
   */
   void fireDialogCommandEvent (DialogCommandEvent event) {
     Vector listeners;
     synchronized(this){
       listeners = (Vector)dialogCommandListeners.clone();
     }
       int size = listeners.size();
       int evtID = event.getID ();
       //System.out.println (this + " : Sending " + event + " to " + dialogListeners);
       for (int i=0; i < size; i++) {
	 switch (evtID)
	   {
	   case DialogCommandEvent.SHUTDOWN:
	     ((DialogCommandListener)(listeners.elementAt(i))).dialogShutdown (event);
	     break;
	   case DialogCommandEvent.FLUSH:
	     ((DialogCommandListener)(listeners.elementAt(i))).dialogChangesFlushed (event);
	     break;
	     case DialogCommandEvent.LAUNCH:
	       ((DialogCommandListener)(listeners.elementAt(i))).dialogLaunched (event);
	     break;
	     default:
	   }
       }
   }

   
  private void uploadProxies () {
    if (!handleProxies)
      return;
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "beanuploading");
    //System.out.println ("DC.uploadProxies (" + proxies + ")");
    if (proxies == null)
      return;
    //System.out.println ("DC.uploadProxies # = " + proxies.length);
    for (int i=0; i<proxies.length; i++) {
      ItemProxy proxy = proxies[i];
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "proxyUploadState", proxy, new Boolean (proxy.getAutoUpload ()));
      if (!proxy.getAutoUpload ()) {
	try {
	  Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "beanProxyUpload", proxy);
	  proxy.upload ();
	} catch (com.gensym.jgi.G2AccessException g2ae) {
	  com.gensym.message.Trace.exception (g2ae);
	}
      }
    }
    //System.out.println ("Returning from uploadProxies");
  }

  private void unhookProxies () {
    if (!handleProxies)
      return;
    if (proxies == null)
      return;
    for (int i=0; i<proxies.length; i++)
      proxies[i].setProxy (null);
  }

  private void readObject(java.io.ObjectInputStream stream) throws
                   java.lang.ClassNotFoundException, java.io.IOException,
                   java.io.NotActiveException
  {
    stream.defaultReadObject();
    if (dialogCommandListeners == null)
      dialogCommandListeners = new Vector();
  } 


}


