
package com.gensym.oldmdi;
import java.awt.*;
import com.gensym.ntw.util.WindowUtil;
import gjt.ImageButtonEvent;

class MDIDocNC extends Panel {
  private MDIFrame  frame;
  MDIClient client;
  private MDIDocTB  titleBar;
  boolean hasFocus = false;
  int id;
  private static Insets stdmdiDocInsets = new Insets (4, 4, 4, 4);
  private static Dimension iconDimensions = new Dimension (150, 25);
  MDIDoc docClient;
  private Rectangle mappedBounds, previousTBBounds;
  private boolean isMapped = true;
  static MDIDocNC docptr;
  private int mx, my, ox, oy; // For moves

  @Override
  public Insets insets () {
    return stdmdiDocInsets;
  }

  MDIDocNC (String title) {
    // Create the standard document
    this (title, new MDIDoc ());    
    //System.out.println ("@5"); System.out.flush ();
  }

  MDIDocNC (String title, MDIDoc client) {

    docClient = client;
    //docClient.resize (200, 200);
    //System.out.println ("@3"); System.out.flush ();
    setLayout (new BorderLayout ());
    //System.out.println ("@3.1"); System.out.flush ();
    add ("North", titleBar = new MDIDocTB (title));
    //System.out.println ("@3.2"); System.out.flush ();
    add ("Center", docClient);
    //System.out.println ("@4"); System.out.flush ();
    docptr = this;
  }
  
  @Override
  public void paint (Graphics g) {
    Dimension size = size ();
    int width  = size.width;
    int height = size.height;

    // RB - Outside
    g.setColor (Color.black);
    g.drawLine (width - 1, 0, width - 1, height - 1);
    g.drawLine (width - 1, height - 1, 0, height - 1);

    // RB - Inside
    g.setColor (Color.gray);
    g.drawLine (width - 2, 1, width - 2, height - 2);
    g.drawLine (width - 2, height - 2, 1, height - 2);


    // LT - Inside
    g.setColor (Color.white);
    g.drawLine (1, 1, width - 1, 1);
    g.drawLine (1, 1, 1, height - 1);

    // LT - Outside
    g.setColor (Color.lightGray);
    g.drawLine (0, 0, width, 0);
    g.drawLine (0, 0, 0, height);

    g.fillRect (2, 2, width - 4, 2);
    g.fillRect (width - 4, 2, 2, height - 4);
    g.fillRect (2, 2, 2, height - 4);
    g.fillRect (2, height - 4, width - 4, 2);
  }

  @Override
  public boolean handleEvent (Event evt) {
    if (evt.id == Event.KEY_ACTION) {
      int keyID = evt.key;
      if (keyID >= Event.UP && keyID <= Event.RIGHT)
	handleResizeKey (evt);
    } else if (evt.id == Event.GOT_FOCUS || evt.id == Event.LOST_FOCUS) {
      hasFocus = (evt.id == Event.GOT_FOCUS);
      client.handleMDIFocus (this, (Component)evt.target, hasFocus);
      titleBar.repaint ();
    } else if (evt.id >= Event.MOUSE_DOWN &&
	       evt.id <= Event.MOUSE_DRAG) {
      client.handleMouseEvent (this, evt);
    } else if (evt.target == titleBar.minimizeButton
	       && (evt instanceof ImageButtonEvent)
	       && ((ImageButtonEvent)evt).isActivated ()) {
      //System.out.println ("<<<< Iconifying? >>>> on Btn event ->" + evt);
      client.setThreadJob (this, (isMapped ? client.THREAD_ICONIFY : client.THREAD_RESTORE));
      new Thread (client).start ();
    }
    return super.handleEvent (evt);
  }

  public void handleResizeKey (Event evt) {
    int delta = 1;
    int xDelta, yDelta;

    if (evt.controlDown ())
      delta = 10;
    else if (evt.metaDown ())
      delta = 100;
    int keyID = evt.key;
    if (keyID == Event.UP || keyID == Event.DOWN) {
      xDelta = 0;
      if (keyID == Event.UP)
	yDelta = -delta;
      else
	yDelta = delta;
    } else {
      yDelta = 0;
      if (keyID == Event.LEFT)
	xDelta = -delta;
      else
	xDelta = delta;
    }
    Dimension size = size ();
    if (evt.shiftDown ()) {
      Point currentLocn = location ();
      //move (currentLocn.x + xDelta, currentLocn.y + yDelta);
      WindowUtil.setLocation (this, currentLocn.x + xDelta, currentLocn.y + yDelta);
    } else {
      resize (size.width + xDelta, size.height + yDelta);
      invalidate ();
      validate ();
    }
    requestFocus ();
  }

  @Override
  public boolean mouseDown (Event evt, int x, int y) {
    mx = x; my = y;
    Point locn = getLocation ();
    ox = locn.x; oy = locn.y;
    return true;
  }

  @Override
  public boolean mouseDrag (Event evt, int x, int y) {
    if ((mx != x) || (my == y)) {
      WindowUtil.setLocation (this, ox + x - mx, oy+ y - my);
      ox = ox + x - mx;
      oy = oy + y - my;
    }
    return true;
  }

  /*
  public boolean mouseUp (Event evt, int x, int y) {
    //System.out.println ("Mouse Up at (" + x + "," + y + ")");
    //System.out.println ("ox,oy = (" + ox + "," + oy);
    return true;
  }
  */

  @Override
  public Dimension preferredSize () {
    return iconDimensions;
  }

  @Override
  public Dimension minimumSize () {
    return iconDimensions;
  }

  @Override
  public boolean hasFocus () {
    return hasFocus;
  }

  public boolean isMapped () {
    return isMapped;
  }

  Point getTBOffset () {
    return new Point (4, 4);
  }

  Rectangle getTBBounds () {
    return (previousTBBounds = titleBar.bounds ());
  }

  Rectangle getPreviousTBBounds () {
    return previousTBBounds;
  }

  String getTitle () {
    return titleBar.title;
  }

  void map () {
    isMapped = true;
  }

  void unmap () {
    isMapped = false;
  }

  MDIDocTB getTitleBar () {
    return titleBar;
  }

  @Override
  public String paramString () {
    return (super.paramString () + "[Valid = " + isValid () + ", " +
	    "Visible = " + isVisible () + ", " +
	    "Enabled = " + isEnabled () + "]");
  }
}
