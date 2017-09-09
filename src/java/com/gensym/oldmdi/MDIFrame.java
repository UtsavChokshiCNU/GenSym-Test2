
package com.gensym.oldmdi;
import java.awt.*;
import gjt.RowLayout;
import gjt.ImageButton;
import gjt.Orientation;
import com.gensym.util.*;
import com.gensym.core.GensymApplication;
import com.gensym.message.*;
import com.gensym.ntw.MDIToolBar;

public class MDIFrame extends Frame {
  private MDIClient mdiClient;
  private MDIStatusBar statusBar;
  public MDIToolBar toolBar;
  private boolean appHasFocus = false;
  // These menu items are exported...
  // Hard coded string. Arrrgh. Is that the right sound?
  public  static final MDIMenuItem TILEHORIZ_MENUITEM = new MDIMenuItem ("Tile Horizontally");
  public  static final MDIMenuItem TILEVERT_MENUITEM = new MDIMenuItem ("Tile Vertically");
  public  static final MDIMenuItem CASCADE_MENUITEM  = new MDIMenuItem ("Cascade");

  public MDIFrame () {
    this ("Untitled");
  }

  public MDIFrame (String title) {
    super (title);
    setLayout (new BorderLayout ());
    add ("North", toolBar = new MDIToolBar ());
    add ("South", statusBar = new MDIStatusBar ());
    add ("Center", (mdiClient = new MDIClient ()));
    MDIDocTB.init ();
    pack ();
  }

  public synchronized void setMenuBar (MenuBar mb, MDIMenu windowMenu) {
    super.setMenuBar (mb);
    mdiClient.setDocMenu (windowMenu);
  }

  public MDIDoc  createNewDocument (String title) {
    return createNewDocument (title, (Dimension)null);
  }

  public synchronized MDIDoc createNewDocument (String title, Dimension clientRequest) {
    MDIDocNC newDoc = new MDIDocNC (title);
    mdiClient.addNewDocument (newDoc, title, clientRequest);
    return newDoc.docClient;
  }

  public synchronized void addNewDocument (String title, MDIDoc client) {
    MDIDocNC newDoc = new MDIDocNC (title, client);
    mdiClient.addNewDocument (newDoc, title, (Dimension)null);
  }

  @Override
  public boolean handleEvent (Event evt) {
    if (evt.target instanceof MDIMenuItem) {
      MDIMenuItem origMenuItm = (MDIMenuItem) ((MDIMenuItem)evt.target).getOriginal ();
      if (origMenuItm == TILEHORIZ_MENUITEM)
	mdiClient.rearrange (mdiClient.TILE_HORIZONTALLY);
      else if (origMenuItm == TILEVERT_MENUITEM)
	mdiClient.rearrange (mdiClient.TILE_VERTICALLY);
      else if (origMenuItm == CASCADE_MENUITEM)
	mdiClient.rearrange (mdiClient.TILE_CASCADE);
      else if (origMenuItm.getParent () == mdiClient.docAppendMenu)
	mdiClient.handleDocMenuChoice (origMenuItm);
      else if (!(mdiClient.getFocusDocument () == null))
	mdiClient.getFocusDocument ().handleMenuEvent (evt);
    }

    // Other MDI Events..

    if (evt.id == Event.WINDOW_DESTROY)
      System.exit (1); // Should ask the application!
    return super.handleEvent (evt);
  }

  public MDIDoc getFocusDocument () {
    return mdiClient.getFocusDocument ();
  }

  public void updateStatusBar (String displayTxt, int duration) {
    statusBar.setStatus (displayTxt, duration);
  }
}

// This should move to NtwFrame!!

class MDIStatusBar extends Panel implements Runnable {

  private Dimension preferredSize = new Dimension (100, 22);
  private Font stdFont = new Font ("sansserif", Font.PLAIN, 12);
  private String initialStatus = "Ready";
  private String currentStatus = initialStatus;
  private int noticeDuration;
  private int updateCount = 0;

  public MDIStatusBar () {
    setBackground (Color.lightGray);
  }

  @Override
  public Dimension preferredSize () {
    return preferredSize;
  }

  @Override
  public void paint (Graphics g) {
    g.setFont (stdFont);
    g.drawString (currentStatus, 10, 15);
  }

  public void setStatus (String newStatus, int duration) {
    currentStatus = newStatus;
    noticeDuration = duration;
    updateCount++;
    repaint ();
    new Thread (this).start ();
  }

  public void resetStatus () {
    currentStatus = initialStatus;
    repaint ();
  }

  @Override
  public void run () {
    int currentCount = updateCount;
    try {
      Thread.currentThread().sleep (noticeDuration*1000);
    } catch (InterruptedException ie) { }
    if (currentCount == updateCount)
      resetStatus ();
  }
}



class SimpleMDIDoc extends MDIDoc {

  @Override
  public boolean handleMDIEvent (Event evt) {
    System.out.println ("SimpleMDIDoc : Not handling MDI Event");
    return super.handleMDIEvent (evt);
  }

  @Override
  public boolean handleMenuEvent (Event evt) {
    System.out.println ("SimpleMDIDoc : Not handling MDI Menu Event");
    return true;
  }

  @Override
  public void paint (Graphics g) {
    g.setColor (Color.pink);
    g.fillRect (0, 0, 1000, 1000);
  }
}
