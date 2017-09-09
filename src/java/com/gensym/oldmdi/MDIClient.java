package com.gensym.oldmdi;
import java.awt.*;
import gjt.RowLayout;
import gjt.Orientation;

class MDIClient extends Panel implements MDITilingConstants, Runnable {
  private static Color bgColor = Color.gray;
  private static int docSerialID = 0;
  private static final int MAX_DOCUMENT_COUNT = 20;
  private MDIDocNC currentDoc;
  private MDIDocNC[] mdiDocuments = new MDIDocNC[MAX_DOCUMENT_COUNT];
  private Component[] docFocusTarget = new Component[MAX_DOCUMENT_COUNT];
  private MDIMenuItem[] docMenuEntries = new MDIMenuItem[MAX_DOCUMENT_COUNT];
  private MDIWindowManager wm = new MDIWindowManager (this, MDIWindowManager.EXPLICIT_FOCUS, true);
  private Insets stdInsets = new Insets (2, 2, 2, 2);
  private Insets minimzedIconsInsets = new Insets (2, 2, 23, 2);
  private MDITBAnimator animatingTB;
  private Rectangle[] mappedAnimationBounds = new Rectangle[20],
    unmappedAnimationBounds = new Rectangle[20],
    docBounds = new Rectangle[20];
  static final int THREAD_ICONIFY = 0, THREAD_RESTORE = 1;
  private MDIDocNC threadData;
  private int threadCode;
  MDIMenu docAppendMenu;
  MDIIconPanel iconPanel = new MDIIconPanel ();

  public MDIClient () {
    setLayout (null);
    animatingTB = new MDITBAnimator (this);
    add (iconPanel);
    setBackground (bgColor);
  }

  void setDocMenu (MDIMenu windowMenu) {
    docAppendMenu = windowMenu;
    docAppendMenu.addSeparator ();
  }

  public synchronized void addNewDocument (MDIDocNC newDoc, String title, Dimension clientRequest) {
    int width, height;
    mdiDocuments[newDoc.id = docSerialID++] = newDoc;
    /* This gets around a null pointer exception
       Hack for now. 3/25/97 vkp */
    docFocusTarget[newDoc.id] = newDoc;
    newDoc.client = this;
    Dimension size = size ();
    if (clientRequest != null) {
      Insets insets = newDoc.insets ();
      MDIDocTB tb = newDoc.getTitleBar ();
      int extraWidth = insets.left + insets.right;
      int extraHeight = insets.top + tb.preferredSize().height + insets.bottom;
      width = clientRequest.width + extraWidth;
      height = clientRequest.height + extraHeight;
      if (width > size.width)
	width = size.width - 40;
      if (height > size.height)
	height = size.height - 40;
    } else {
      width = size.width - 40;
      height = size.height - 40;
    }
    newDoc.reshape (20, 20, width, height); // This should depend on prev
    add (newDoc);
    wm.addDocument (newDoc);
    docAppendMenu.add (docMenuEntries[newDoc.id] = new MDIMenuItem (title));
    newDoc.invalidate ();
    newDoc.validate ();
    newDoc.requestFocus ();
  }

  public synchronized MDIDoc getFocusDocument () {
    /*
    if (currentDoc == null) {
      try {
	System.out.println ("Waiting for Focus Document to get a value");
	System.out.flush ();
	wait ();
      } catch (InterruptedException ie) {}
    }
    System.out.println ("In MDIClient::getFocusDocument () -> currentDoc=" + currentDoc);
    */
    if (currentDoc == null)
      return null;

    return currentDoc.docClient;
  }

  synchronized void handleDocMenuChoice (MDIMenuItem menuItm) {
    for (int i=0; i<docSerialID; i++)
      if (menuItm == docMenuEntries[i]) {
	mdiDocuments[i].requestFocus ();
	return;
      }
  }

  MDIDocNC getFocusDocumentNC () {
    return currentDoc;
  }

  public int getDocumentCount () {
    return docSerialID;
  }

  public MDIDocNC[] getDocumentsNC () {
    return mdiDocuments;
  }

  @Override
  public void paint (Graphics g) {
    Rectangle paintArea = g.getClipRect ();
    Dimension size = size ();
    int width = size.width;
    int height = size.height;

    g.setColor (bgColor);
    g.fillRect (2, 2, width - 2, height - 2);

    if ((paintArea.x > 1) && (paintArea.y > 1) 
	&& (paintArea.x + paintArea.width < size.width - 2)
	&& (paintArea.y + paintArea.height < size.height -2))
      return;

    g.setColor (Color.gray);
    g.drawLine (0, 0, width, 0);
    g.drawLine (0, 0, 0, height);
    g.setColor (Color.black);
    g.drawLine (1, 1, width, 1);
    g.drawLine (1, 1, 1, height);

    g.setColor (Color.lightGray);
    g.drawLine (1, height - 2, width - 2, height - 2);
    g.drawLine (width - 2, height - 2, width - 2, 1);
    g.setColor (Color.white);
    g.drawLine (0, height - 1, width - 1, height - 1);
    g.drawLine (width - 1, height - 1, width - 1, 0);

  }

  @Override
  public Insets insets () {
    return stdInsets;
  }

  @Override
  public boolean handleEvent (Event evt) {
    if (evt.id == Event.KEY_PRESS) {
      int keyID = evt.key;
      /*
      System.out.println ("Client got Key: " + keyID + " : [" + 
			  (evt.controlDown() ? "CTRL," : "") +
			  (evt.metaDown() ? "ALT," : "") + "]");
			  */
      System.out.flush ();
      if (keyID == 9 && evt.controlDown ())
	shiftFocusToNextDocument ();
    }
    return super.handleEvent (evt);
  }

  private void shiftFocusToNextDocument () {
    int currentIndex = currentDoc.id;
    //System.out.println ("CurrentDOC = " + currentIndex + " : Total# = " + docSerialID );
    mdiDocuments[(++currentIndex < docSerialID ? currentIndex : 0)].docClient.requestFocus ();
    docFocusTarget[currentIndex < docSerialID ? currentIndex : 0].requestFocus ();
  }

  void handleMDIFocus (MDIDocNC doc, Component targetFocus, boolean gettingFocus) {
    currentDoc = (gettingFocus ? doc : null);
    /*
    if (gettingFocus) {
      synchronized (this) {
	notify ();
      }
    }
    */
    if (!gettingFocus)
      docFocusTarget[doc.id] = targetFocus;
    else
      wm.handleFocusEvent (doc);
    //System.out.println ("Focus Target : " + (gettingFocus ? "<-  " : "->  ") + targetFocus);
  }
  
  void setMDIFocus (MDIDocNC doc) {
    docFocusTarget[doc.id].requestFocus ();
  }

  final void handleMouseEvent (MDIDocNC doc, Event evt) {
    wm.handleMouseEvent (doc, evt);
  }

  final void rearrange (int arrangementCode) {
    switch (arrangementCode) {
    case TILE_HORIZONTALLY:
    case TILE_VERTICALLY:
    case TILE_CASCADE:
      wm.tile (arrangementCode);
      break;
    }
  }

  void setThreadJob (MDIDocNC doc, int jobCode) {
    threadData = doc;
    threadCode = jobCode;
  }

  @Override
  public void run () {
    MDIDocNC doc = threadData;
    if (threadCode == THREAD_ICONIFY)
      iconify (doc);
    else
      restore (doc);
  }

  void iconify (MDIDocNC doc) {
    String title = doc.getTitle ();
    Rectangle tbBounds = doc.getTBBounds ();
    Rectangle docEdges = doc.bounds ();
    Point docLocn = doc.location ();
    Rectangle iconBounds = iconPanel.getNextIconBounds ();
    Point panelLocn = iconPanel.location ();

    tbBounds.translate (docLocn.x, docLocn.y);
    iconBounds.translate (panelLocn.x, panelLocn.y);
    mappedAnimationBounds[doc.id] = tbBounds;
    unmappedAnimationBounds[doc.id] = iconBounds;
    docBounds[doc.id] = docEdges;
    //System.out.println ("Iconifying from " + tbBounds + " -> to -> " + iconBounds);
    //System.out.println ("Animator = " + animatingTB);
    
    animatingTB.setParameters (title,
			       tbBounds.x, tbBounds.y, tbBounds.width,
			       iconBounds.x, iconBounds.y, iconBounds.width);
    animatingTB.animate ();
    unmap (doc);
  }

  void restore (MDIDocNC doc) {
    String title = doc.getTitle ();
    Rectangle tbBounds = mappedAnimationBounds[doc.id];
    Rectangle iconBounds = unmappedAnimationBounds[doc.id];

    animatingTB.setParameters (title,
			       iconBounds.x, iconBounds.y, iconBounds.width,
			       tbBounds.x, tbBounds.y, tbBounds.width);
    animatingTB.animate ();
    map (doc);
    setMDIFocus (doc);
  }

  private void unmap (MDIDocNC doc) {
    //System.out.println ("Unmapping " + doc);
    //System.out.println ("Doc before client.remove : " + doc.paramString ());
    remove (doc);
    doc.unmap ();
    //System.out.println ("Doc after client.remove : " + doc.paramString ());
    iconPanel.addIcon (doc);
  }

  private void map (MDIDocNC doc) {
    iconPanel.removeIcon (doc);
    doc.map ();
    Rectangle docEdges = docBounds[doc.id];
    doc.reshape (docEdges.x, docEdges.y, docEdges.width, docEdges.height);
    add (doc);
    validate ();
  }

  @Override
  public void reshape (int x, int y, int width, int height) {
    super.reshape (x, y, width, height);
    iconPanel.reshape (2, height - 27, width - 4, 25);
  }
}


class MDIIconPanel extends Panel {

  private static LayoutManager stdIconPanelLayoutMgr = new RowLayout (Orientation.LEFT,
								      Orientation.BOTTOM, 0);
  private MDIDocNC[] unMappedDocs = new MDIDocNC[20];
  private int unMappedDocCount = 0;
  private int stdIconWd = 150, stdIconHt = 50;
  
  MDIIconPanel () {
    setLayout (stdIconPanelLayoutMgr);
  }
  
  @Override
  public void paint (Graphics g) {
    g.setColor (Color.gray);
    Dimension size = size ();
    g.fillRect (0, 0, size.width, size.height);
  }

  Rectangle getNextIconBounds () {
    if (unMappedDocCount != 0) {
      Rectangle r =unMappedDocs[unMappedDocCount - 1].bounds();
      r.translate(stdIconWd, stdIconHt);
      return r;
    } else
      return new Rectangle (0, 0, stdIconWd, stdIconHt);
  }

  synchronized void addIcon (MDIDocNC doc) {
    unMappedDocs[unMappedDocCount++] = doc;
    //System.out.println ("Doc before addIcon : " + doc.paramString ());
    doc.reshape (-1, -1, 1, 1);
    add (doc);
    invalidate ();
    validate ();
    //System.out.println ("Iconified Document  : " + doc.paramString ());
  }

  synchronized void removeIcon (MDIDocNC doc) {
    int i;
    for (i=0; i<unMappedDocCount; i++)
      if (unMappedDocs[i] == doc) break;
    for (int j=i; j<unMappedDocCount - 1; j++)
      unMappedDocs[j] = unMappedDocs[j+1];
    unMappedDocCount--;
    remove (doc);
    validate ();
  }

  @Override
  public boolean handleEvent (Event evt) {
    if (evt.id == Event.MOUSE_DOWN &&
	evt.metaDown ())
      list (System.out, 2);
    return super.handleEvent (evt);
  }
    
}


class ColoredPanel extends Panel {
  private Color color;
  private String colorName;
  private static Dimension stdDims = new Dimension (150, 21);

  ColoredPanel (Color color) {
    this.color = color;
    colorName = (color == Color.green ? "GREEN" : "BLUE");
  }

  @Override
  public Dimension preferredSize () {
    return stdDims;
  }

  @Override
  public Dimension minimumSize () {
    return stdDims;
  }

  @Override
  public boolean handleEvent (Event evt) {
    if (evt.id == Event.WINDOW_DESTROY) {
      //System.out.println("Handling window destroy event");
      System.exit (1);
    }
    return super.handleEvent (evt);
  }

  @Override
  public void reshape (int x, int y, int width, int height) {
    super.reshape (x, y, width, height);
    Rectangle r = new Rectangle (x, y, width, height);
    //System.out.println ("  CP: In Panel -> " + r);
    Point parentLocn = getParent().location ();
    r.translate (parentLocn.x, parentLocn.y);
    //System.out.println ("  CP: In Parent -> " + r);
    System.out.flush ();
  }
    
  @Override
  public void paint (Graphics g) {
    Dimension size = size ();
    g.setColor (color);
    g.fillRect (0, 0, size.width, size.height);
  }

}
