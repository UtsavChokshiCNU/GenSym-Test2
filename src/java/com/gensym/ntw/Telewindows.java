
package com.gensym.ntw;

import java.awt.*;
import java.util.*;
import com.gensym.irm.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.message.*;
import com.gensym.jgi.*;
import com.gensym.core.CmdLineArgHandler;
import com.gensym.core.GensymApplication;
import com.gensym.dlg.*;
import com.gensym.ntw.util.*;
import com.gensym.ntw.rmi.TwRMIClientImpl;

/**
 * This is the top level class to run NTW.
 * Loading this:
 * 1) Creates a frame.
 * 2) If appropriate command line arguments are provided or after using the
 *    connect menu choice, a connection is initiated to G2.
 * 3) The callback when the context is initialized sets up the CDM, IRM etc.
 * 4) Blah, Blah, Yadda, Yadda, Yadda.
 *
 */
public class Telewindows extends GensymApplication implements NtwNotificationHandler {

  /** To allow a developer to customize the UI in a consistent way, this
   * field should be used to determine the locale for resource lookup. This is
   * needed because in an applet situation, Locale.setDefault is restricted by
   * the AppletSecurityManager as described in the Internationalization
   * specification, intl/html/intlspec.doc2.html.
   */
  // maybe should allow for keeping track of multiple locals
  private static Locale currentLocale; // = Locale.getDefault();
  private static Resource i18nTrimmings, i18nMessages;
  private static Telewindows twApplcn;
  private static boolean debugInterface = false;
  public static boolean traceOn = false;
  private static final MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.ntw", Telewindows.class);
  private static TraceOut traceListener = new TraceOut();

  private NtwFrame frame;
  static NtwFrame staticFrame;
  private static final int MAX_CONTEXTS = 20;
  //  private static int openContextSerialID = 0;
  private TwAccess[] openContexts = new TwAccess[MAX_CONTEXTS];
  private static String[] cmdLineArgs;
  private TwAccess currentContext;
  static int nextCxnxSerialIndex = 0;

  private static final Rectangle stdBounds = new Rectangle (0, 0, 900, 700);

  private Cursor THE_WAIT_CURSOR    = Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR);
  private Cursor THE_DEFAULT_CURSOR = Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR);

  private Telewindows (String[] args, String title, Rectangle bounds) {
    super (args);
    currentLocale = Locale.getDefault ();
    twApplcn = this;
    frame = new NtwFrame (title);
    staticFrame = frame;
    frame.application = this;
    if (bounds != null)
      frame.setBounds (bounds);
    frame.show ();

    NtwNotification.registerListener ((NtwNotificationHandler)this,
				      (NtwNotificationFilter)null);
    //JGInterface.setG2StubFactory (new com.gensym.util.DefaultStubFactory ());
    //System.setSecurityManager (new com.gensym.util.GensymSecurityManager ());
  }

  public static void main (String[] args) {
    try{
    cmdLineArgs = args;
    CmdLineArgHandler cmdLine = new CmdLineArgHandler (args);
    String title = cmdLine.getOptionValue ("-title");
    String url  = cmdLine.getOptionValue ("-url");
    String host  = cmdLine.getOptionValue ("-host");
    String port  = cmdLine.getOptionValue ("-port");
    String geom  = cmdLine.getOptionValue ("-geometry");
    boolean debugOption = cmdLine.getSwitchValue ("-debug");
    boolean devOption   = cmdLine.getSwitchValue ("-development");

    debugInterface = debugOption;

    Telewindows t = new Telewindows (args,
				     "NTW",
				     geom  == null ? null : parseBounds (geom));
    i18nTrimmings =
      Resource.getBundle("com.gensym.resources.WindowTrimmings",
			 currentLocale);
    i18nMessages = Resource.getBundle("com.gensym.resources.Messages",
				      currentLocale);
    t.frame.setTitle (title == null ? i18nTrimmings.getString("NTW") : title);
    com.gensym.dlgruntime.DialogManager.registerFrame (t.frame);
    com.gensym.dlgruntime.DefaultDialogLauncher.registerFrame (t.frame);

    if (debugOption) {
      TraceOut.setDebug(true);
      Resource.setResourceDebug(true);
    }

    if (devOption)
      Trace.setExceptionTraceOn (true);

    t.frame.toolBar.liveXns.addItemListener (new TwItemListener (t));
    if ((host != null) && (port != null))
      t.attemptConnection (url, host, port);
    // new Thread (new SubscriberTest (t.getInterface ())).start();
    } catch (Throwable t) {
      System.err.println (t);
      t.printStackTrace ();
      if (t instanceof ExceptionInInitializerError) {
	ExceptionInInitializerError e = (ExceptionInInitializerError)t;
	t = e.getException ();
	System.err.println (t);
	t.printStackTrace ();
      }
      System.exit (1);
    }
  }

  
  /**
   * Use this as the locale rather than Locale.getDefault() in order to make
   * applets localised against the locale of the browser if necessary. By default
   * Locale.getDefault() is used for any of language, country, and variant that
   * are not specified in the command-line.
   */
  public static Locale getCurrentLocale() {
    return currentLocale;
  }

  TwAccess attemptConnection (String url, String host, String port) {
    TwAccess newTwAccess = null;
    Trace.send(2, traceKey, i18nMessages, "AttemptingConnection",
	       url, host, port);

    try {
      if (url == null) {
	  TwGateway.initialize(cmdLineArgs);
      }
      newTwAccess = TwGateway.openConnection(url, host, port);
      newTwAccess.login();
      com.gensym.classes.Kb kb = newTwAccess.getKb ();
      kb.addKbModuleListener (new KbModuleListener () {
	@Override
	public void receivedInitialModules (KbEvent evt) {
	  System.out.println (">> Received " + evt);}

	@Override
	public void moduleCreated (KbEvent evt) {
	  System.out.println (">> Received " + evt);}

	@Override
	public void moduleDeleted (KbEvent evt) {
	  System.out.println (">> Received " + evt);}

	@Override
	public void moduleNameChanged (KbEvent evt) {
	  System.out.println (">> Received " + evt);}

	@Override
	public void moduleDependencyChanged (KbEvent evt) {
	  System.out.println (">> Received " + evt);}

	@Override
	public void kbCleared (KbEvent evt) {
	  System.out.println (">> Received " + evt);}

	@Override
	public void topLevelWorkspaceAdded (KbEvent evt){
	  System.out.println (">> Received " + evt);}

	public void topLevelWorkspaceRemoved (KbEvent evt){
	  System.out.println (">> Received " + evt);}

	@Override
	public void topLevelWorkspaceDeleted(KbEvent evt) {
		// TODO Auto-generated method stub
		
	}
      });
    } catch (Exception ex) {
      ex.printStackTrace();
      ex.fillInStackTrace();
      throw new RuntimeException(ex.getMessage());
    }
      int nextIndex;
      if (newTwAccess != null) {
	synchronized (this) {
	  nextIndex = nextCxnxSerialIndex++;
	  openContexts[nextIndex] = newTwAccess;
	}
	if (nextIndex == 0)
	  frame.toolBar.liveXns.remove (0);
	frame.toolBar.liveXns.addItem (newTwAccess.toShortString ());
	frame.toolBar.liveXns.select (nextIndex);
	frame.toolBar.invalidate ();
      }
      currentContext = newTwAccess;
      if (currentContext != null) {
      //      currentContext.setV5Mode(true);

      String message = i18nMessages.format("Notify_Connected_Host_Port",
					   host, port);
      
      NtwNotification note =
	new NtwNotification(NtwNotification.UPDATE, this, message);
      note.send();
    }
      //System.out.println ("Got Connection: " + newTwAccess);
      //System.out.println ("is of class " + newTwAccess.getClass());
    return newTwAccess;
  }

  /**
   * The application needs to know how to route notification
   * messages. It needs access to the UI if the message is
   * to be conveyed to the user.
   */
  @Override
  public void handleNtwNotification (NtwNotification notfn) {
    Trace.send (2, traceKey, i18nMessages,
		"TelewindowsHandlingNotification", notfn);
    if (notfn.notfnCode == NtwNotification.TIMEOUT)
      //MessageDialog.getMessageDialog (frame, (DialogClient)dummyClient, "Connection Failed", notfn.details).show ();
      frame.updateStatusBar (notfn.details, 20);
    else if (notfn.notfnCode == NtwNotification.UPDATE)
      frame.updateStatusBar (notfn.details, 10);
    else if (notfn.notfnCode == NtwNotification.STATUSCHANGE) {
      if (notfn.data == NtwNotification.ACTIVITY_START)
	notifyActivityBegin ();
      else if (notfn.data == NtwNotification.ACTIVITY_STOP)
	notifyActivityEnd ();
    } else if (notfn.notfnCode == NtwNotification.EXCEPTION)
      new MessageDialog (null,
			 "ERROR",
			false,
			notfn.details,
			(StandardDialogClient)null).setVisible (true);
    else
      System.out.println ("Unhandled Notification: " + notfn.details);
  }
    
  NtwFrame getFrame () {
    return frame;
  }

  TwAccess getCurrentContext () {
    return currentContext;
  }

  void setCurrentContext (TwAccess desiredContext) {
    System.out.println ("Current Context changed to " + desiredContext);
    currentContext = desiredContext;
  }

  void setCurrentContext (String contextString) {
    for (int i=0; i<MAX_CONTEXTS; i++) {
      TwAccess t = openContexts[i];
      if (t != null && t.toShortString ().equals (contextString)) {
	setCurrentContext (t);
	return;
      }
    }
  }

  protected static Rectangle parseBounds (String optn) {
    int x, y, width, height;
    if (optn == null || optn.equals (""))
      return stdBounds;
    int xIndex  = optn.indexOf ('x');
    int ppIndex = optn.indexOf ('+');
    int pmIndex = optn.indexOf ('-');
    int pIndex  = (ppIndex*pmIndex >= 0 ?
		   Math.min (ppIndex, pmIndex) : Math.max (ppIndex, pmIndex));
    
    if (xIndex < 0) {
      if (pIndex > 0)
	width = Integer.parseInt (optn.substring (0, pIndex));
      else
	width = stdBounds.width;
      height = stdBounds.height;
    } else {
      if (xIndex != 0)
	width = Integer.parseInt (optn.substring (0, xIndex));
      else
	width = stdBounds.width;
      if (pIndex < 0)
	height= Integer.parseInt (optn.substring (xIndex + 1));
      else
	height = Integer.parseInt (optn.substring (xIndex + 1, pIndex));
    }
    
    if (pIndex < 0) {
      x = 0; y = 0;
    } else {
      boolean pxNegOffset = (pIndex == pmIndex);
      boolean pyNegOffset;
      int pyIndex= optn.indexOf ('+', pIndex + 2);
      if (pyIndex < 0) {
	pyIndex = optn.indexOf ('-', pIndex + 2);
	pyNegOffset = (pyIndex > 0);
      } else
	pyNegOffset = false;
      pIndex++;
      if (pyIndex < 0) {
	x = Integer.parseInt (optn.substring (pIndex));
	y = 0;
      } else {
	x = Integer.parseInt (optn.substring (pIndex, pyIndex));
	pyIndex++;
	y = Integer.parseInt (optn.substring (pyIndex));
      }
      if (pxNegOffset || pyNegOffset) {
	Dimension screenSize = java.awt.Toolkit.getDefaultToolkit().getScreenSize();
	if (pxNegOffset) x = -x + screenSize.width - width;
	if (pyNegOffset) y = -y + screenSize.height - height;
      }
    }
    return new Rectangle (x, y, width, height);
  }

  private com.gensym.util.ActivityDisplay busyNotfn;
  private int numActivities = 0;

  public static void registerActivityDisplay (ActivityDisplay d) {
    twApplcn.busyNotfn = d;
  }

  private void notifyActivityBegin () {
    Trace.send (5, traceKey, i18nMessages, ">>> Activity Starting");
    if (busyNotfn == null)
      return;
    if (numActivities++ == 0) {
      busyNotfn.setBusy ();
      frame.setCursor (THE_WAIT_CURSOR);
    }
  }

  private void notifyActivityEnd () {
    Trace.send (5, traceKey, i18nMessages,"<<< Activity Ending");
    if (busyNotfn == null)
      return;
    if (--numActivities == 0) {
      busyNotfn.setIdle ();
      frame.setCursor (THE_DEFAULT_CURSOR);
    }
  }
}

class TwItemListener implements java.awt.event.ItemListener {

  private Telewindows application;

  TwItemListener (Telewindows appln) {
    application = appln;
  }

  @Override
  public void itemStateChanged (java.awt.event.ItemEvent ie) {
    System.out.println ("TwItemListener says: " + ie);
    System.out.println ("Item is a " + ie.getItem ().getClass ());
    application.setCurrentContext ((String) ie.getItem ());
  }
}

