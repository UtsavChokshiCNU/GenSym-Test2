
package com.gensym.demos.wkspapplet;

import java.awt.*;
import java.util.*;
import java.applet.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.controls.ItemRetriever;
import com.gensym.jgi.*;
import com.gensym.ntw.*;
import com.gensym.wksp.*;
import com.gensym.draw.*;
import com.gensym.classes.KbWorkspace;

/** A demonstration applet showing how to include a G2 workspace as part
 * of an applet.
 *
 */
public class WkspApplet extends Applet implements
NtwNotificationHandler, java.awt.event.ActionListener {

  static {
    // temp hack: netscape has problems with resources
    Resource.setResourceDebug(true);
  }

  // For translation of user-visible messages
  protected static Resource i18n =
  Resource.getBundle("com.gensym.demos.wkspapplet.Messages");

  //
  // Tracing tools
  //

  // for translation of tracing messages
  protected static Resource i18nTrace =
  Resource.getBundle("com.gensym.demos.wkspapplet.TraceMessages");
  protected static MessageKey traceKey = 
  Trace.registerMessageKey("com.gensym.ntw", WkspApplet.class);
  // only one of these is needed for an application, though one can
  // use more than one of these.
  private static TraceOut traceListener = new TraceOut();
  private static boolean trace = true;

  private WorkspaceView view;

  public WkspApplet () {
    // Some parts of Sequioa generate user notification messages,
    // so it is a good idea to listen for them.
    NtwNotification.registerListener ((NtwNotificationHandler)this,
				      (NtwNotificationFilter)null);
  }

  @Override
  public String getAppletInfo() {
    return
      "Gensym JavaTeleWindows\n" +
      "Version 1.0 Alpha Rev 0\n" +
      "Copyright (C) 1986-2017 Gensym Corporation.\n" +
      //"Machine ID: " + machineID + "\n" +
      "All Rights Reserved.\n" +
      "Authors: Joe E. Devlin, Christine Hostage, Sidra Michon,\n" +
      "                Paul B. Konigsberg, Todd Obrien, Robert Penny, \n" +
      "                Vikram Pillai, Wallid Sallam, Jenifer Tidwell, \n" +
      "                and John Valente.\n" +
      "Squirrels: 3 1/8\n" +
      "________________________________________________________________";
  }

  private String[][] pinfo =
  {{"traceKeys",     "string",
    "space delimited set of string keys specifying general areas of tracing"},
   {"messages",      "string",
    "space delimited set of string keys specifying specific tracing messages"}
  };

  @Override
  public String[][] getParameterInfo() {
    return pinfo;
  }
    
  @Override
  public void init () {
    String traceKeys = getParameter("traceKeys");
    String messages = getParameter("messages");
    Trace.send(10, traceKey, i18nTrace, "initializeTracing");
    if (traceKeys != null) {
      Trace.setTraceOn(true);
      Trace.setExceptionTraceOn(true);
      traceListener.initialize(traceKeys, Trace.ALL_LEVELS, messages);
    }

    // Will only be using the ItemRetriever to retrieve instances from one
    // class
    retriever.setItemClassName("KB-WORKSPACE");

    buildUI();
    //    buildWkspHolder();

    setLayout(new BorderLayout());
    add(uiHolder, "East");

    validate();
    Trace.send(10, traceKey, i18nTrace, "showApplet");
    setVisible(true);
  }

  /** Make the label second-last in the row, and non-expandable.
   */
  private void addLabel(String label, GridBagConstraints c,
			GridBagLayout gridbag) {
    c.gridwidth = GridBagConstraints.RELATIVE;
    c.fill = GridBagConstraints.NONE;
    Label labelThing = new Label(i18n.getString(label), Label.RIGHT);
    gridbag.setConstraints(labelThing, c);
    uiHolder.add(labelThing);
  }

  /** Make a label/component pair, with the component as the last
   * thing in the row.
   */
  private Component addThing(String label,
			     Component cmp,
			     GridBagConstraints c,
			     GridBagLayout gridbag) {
    addLabel(label, c, gridbag);
    c.fill = GridBagConstraints.BOTH;
    c.gridwidth = GridBagConstraints.REMAINDER;
    gridbag.setConstraints(cmp, c);
    uiHolder.add(cmp);
    return cmp;
  }

  /** Builds the section on the right of the applet where users can
   * specify the important things such as "url", "host", "port",
   * and "workspace". Initializes the instance variables <code>urlField,
   * hostField, portField, </code>and <code>workspaceNameField</code>.
   * Adds the applet as an ActionListener to the getWkspButton.
   */
  protected void buildUI() {
    GridBagLayout gridbag = new GridBagLayout();
    GridBagConstraints c = new GridBagConstraints();
    uiHolder = new SimpleContainer();
    uiHolder.setLayout(gridbag);
    urlField = (TextField)addThing("brokerUrl", new TextField(), c, gridbag);
    hostField = (TextField)addThing("host",
				    new TextField("localhost"), c, gridbag);
    portField = (TextField)addThing("port", new TextField("1111"), c, gridbag);
    workspaceNameField = (TextField)addThing("workspace",
					     new TextField(), c, gridbag);
    getWkspButton = new Button(i18n.getString("getWksp"));
    c.gridwidth = GridBagConstraints.REMAINDER;
    c.fill = GridBagConstraints.NONE;
    gridbag.setConstraints(getWkspButton, c);
    uiHolder.add(getWkspButton);
    getWkspButton.addActionListener(this);
  }

  private Container uiHolder, wkspHolder;
  
  protected TextField hostField;
  protected TextField portField;
  /** If this is non-empty when the getWkspButton is pressed, it causes
   * the applet to run in a "pure-Java", "three-tier" mode.
   */
  protected TextField urlField;
  protected TextField workspaceNameField;
  protected Button getWkspButton;

  /** Puts the <code>view</code> into a lightweight Container
   * in the "center" of the Applet.
   */
  private void buildWkspHolder() {
    if (wkspHolder != null) {
      return;
    }

    // Make the workspace visible within this applet

    if (view == null)
      view = new WorkspaceView();

    // use a really lightweight container: this is all that is
    // necessary, and it works better than Panel with the
    // double buffering in PersistentCanvas.
    wkspHolder = new SimpleContainer();

    wkspHolder.setLayout (new BorderLayout ());
    add(wkspHolder, "Center");

    // Setup scroll bars for the WorkspaceView, and hook them up
    // to the view.
    Rectangle tmpbounds = wkspHolder.getBounds();
    WorkspaceViewScrollbar hscroll =
      new WorkspaceViewScrollbar(view,Scrollbar.HORIZONTAL, 0,1,
			tmpbounds.x,tmpbounds.x + tmpbounds.width);
    WorkspaceViewScrollbar vscroll =
      new WorkspaceViewScrollbar(view,Scrollbar.VERTICAL, 0,1,
			tmpbounds.y,tmpbounds.y + tmpbounds.height);
    view.addScrollbar(vscroll,false);
    view.addScrollbar(hscroll,true);

    // put the scrollbars and WorkspaceView into the wkspHolder
    wkspHolder.add("South",  hscroll);
    wkspHolder.add("East",   vscroll);
    wkspHolder.add("Center", view);
    wkspHolder.validate();
    wkspHolder.setVisible(true);

    // hook up the containment tree
    validate();

    // smoother drawing: relies on the containment tree being hooked
    // up (the Image is provided by the first native window found
    // among the parents of the view).
    view.setDoubleBuffered (true);
  }

  ItemRetriever retriever = new ItemRetriever();

  /** This is the method that actually reads the values out of
   * the user-input fields on the right of the applet, then uses
   * that information to get the workspace from the specified G2.
   */
  @Override
  public void actionPerformed(java.awt.event.ActionEvent event) {
    // Get user input
    String host = hostField.getText();
    String port = portField.getText();
    String url = urlField.getText();
    // These are listed in upper case in G2
    String workspaceName = workspaceNameField.getText().toUpperCase();

    // Clean up the url not to pass in an empty string
    if ("".equals(url))
      url = null;

    // initialize the remaining necessary information on the ItemRetriever
    retriever.setConnectionInfo(new TwConnectionInfo
				(url, host, port,
				 // Want sharable connections
				  false, true));

    // Tell the retriever which workspace you want.
    retriever.setItemName(workspaceName);

     try {
       // Obtain the workspace based on name.
       KbWorkspace workspace = (KbWorkspace)retriever.retrieveItem();

       // display this workspace in the WorkspaceView.
       view.setWorkspace(workspace);
       validate();
     } catch (Exception ex) {
       System.out.println("Couldn't get workspace because: " + ex.getMessage());
       ex.printStackTrace();
     }
  }

  @Override
  public void start() {
    // For some reason, it is best not to build the wkspHolder
    // in the init() method along with the uiHolder. It works
    if (wkspHolder == null)
      buildWkspHolder();
    super.start();
  }

  /**
   * The application needs to know how to route notification
   * messages. It needs access to the UI if the message is
   * to be conveyed to the user.
   */

  @Override
  public void handleNtwNotification (NtwNotification notfn) {
    System.out.println ("Telewindows handling Notification: " + notfn);
    if (notfn.notfnCode == NtwNotification.TIMEOUT) {
      showStatus(notfn.details);
    }
    else if (notfn.notfnCode == NtwNotification.UPDATE) {
      showStatus(notfn.details);
    }
    System.out.println ("Unhandled Notification: " + notfn.details);
  }

  @Override
  public void update(Graphics g) {
    paint(g);
  }
  
}

class SimpleContainer extends Container {
}

