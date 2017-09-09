/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 MDIManager.java
 *
 */

package com.gensym.mdi;

import java.awt.Color;
import java.awt.Component;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.util.Enumeration;
import java.util.Vector;
import java.awt.Image;
import javax.swing.JDesktopPane;
import javax.swing.JLayeredPane;
import javax.swing.JMenuItem;
import javax.swing.JMenuBar;
import javax.swing.JMenu;
import javax.swing.ImageIcon;

import com.gensym.dlg.SelectionDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.dlg.StandardDialog;
import com.gensym.ui.Command;
import com.gensym.message.Resource;
import com.gensym.core.util.QuickSorter;
import com.gensym.message.Trace;

/** 
 *  Each MDIFrame contains a MDIManager.  The management of child documents is
 *  delegated to the MDIManager. For example, the following adds a document to 
 *  the MDIFrame:
 *  <code>mdiFrame.getManager().addDocument(document);</code>
 *<p>
 *  The MDIManager maintains the 
 *  the "active" document, maintains the notion of a "next" documnet,
 *  maintains the window menus for all documents, 
 *  determines the default size and location of new documents, arranges documents 
 *  (tile and cascade), and manages the document's menu bars.
 *</p><p>
 *  Clients may add themselves as listeners to receive notification of new
 *  documents being added.
 *</p>
 *  @see com.gensym.mdi.MDIFrame
 *  @see com.gensym.mdi.MDIDocument 
 *  @see com.gensym.mdi.MDIListener
 */
public final class MDIManager extends JDesktopPane implements MDITilingConstants{
  private static final int INITIAL_CHILD_CAPACITY = 20;
  private static final int MAX_NUMBER_OF_WINDOW_MENU_ENTRIES = 9;
  private static final int X_OFFSET = 10;
  private static final int Y_OFFSET = 10;
  private static final Color darkGray = new Color(103, 103, 103);
  private static final Integer CHILD_FRAME_LAYER = JLayeredPane.DEFAULT_LAYER; 
  private static Resource i18n = Resource.getBundle("com.gensym.resources.Messages");
  private MDIFrame frame;
  private Vector children;
  private Vector orderedChildren; 
  private int activeWindowMenuIndex;
  private JMenuItem[] moreMenuEntries;
  private MDIDocument[] moreWindows;
  private String defaultDocumentTitle;
  private int frameCount;
  private Vector positions; 
  private int nextPosition;
  private Vector orderedSnapshot;
  private int nextChildIndex;
  private boolean snapshotValid;
  private MDITilingManager tilingManager;
  private MDITilingCommand tilingHandler;
  private Vector listeners;
  private Vector docListeners;
  private ActionListener actionListener;
  private StandardDialogClient dialogClient;

  MDIManager(MDIFrame frame){
    this.frame = frame;
    setDesktopManager(new MDIFrameManager());
    init();
  }

  private void init(){
    children = new Vector(INITIAL_CHILD_CAPACITY);
    orderedChildren = new Vector(INITIAL_CHILD_CAPACITY);
    actionListener = new ActionAdapter();
    activeWindowMenuIndex = 0;
    moreMenuEntries = new JMenuItem[2];
    String moreLabel = i18n.getString("moreMenuItemLabel");
    moreMenuEntries[0] = new JMenuItem(moreLabel);
    moreMenuEntries[0].addActionListener(actionListener);
    moreMenuEntries[1] = new JMenuItem(moreLabel);
    moreMenuEntries[1].addActionListener(actionListener);
    defaultDocumentTitle = i18n.getString("defaultChildFrameTitle");
    frameCount = 0;
    positions = new Vector(INITIAL_CHILD_CAPACITY);
    nextPosition = 0;
    orderedSnapshot = null;
    nextChildIndex = 0;
    snapshotValid = false;
    tilingHandler = new MDITilingCommand(this);
    tilingManager= new MDITilingManager();
    setBackground(this.darkGray);
    setOpaque(true);
    listeners = new Vector();
    docListeners = new Vector();
    dialogClient = new DialogClientAdapter();
    putClientProperty ("JDesktopPane.dragMode", "outline");
  }

  /**  Adds a document of the default size to the client at the default location.*/
  public void addDocument(MDIDocument document){
    addDocument(document, (Dimension) null);
  }

  /** Adds a document of the given dimension to the client at the default 
   *  location. */
  public void addDocument(MDIDocument document, Dimension dimension){
    if (positions.size() <= nextPosition) positions.addElement(document);
    else positions.setElementAt(document, nextPosition);
    MDIDocument previousChild;
    boolean maximize = false;
    if (nextPosition == 0) previousChild = null;
    else{
      previousChild = (MDIDocument)positions.elementAt(nextPosition - 1);
      if (previousChild.isMaximum()){
	try{previousChild.setMaximum(false);}
	catch (java.beans.PropertyVetoException ex){}      
	maximize = true;
      }
    }
    setNextPosition(nextPosition + 1);
    boolean checkDimension = true;
    if (dimension == null){
      dimension = calculateDimension(previousChild);
      checkDimension = false;
    }
    int x = calculateXPosition(previousChild);
    int y = calculateYPosition(previousChild);
    addDocument(document, dimension.width, dimension.height, x, y, checkDimension);
    if (maximize) 
      try{document.setMaximum(true);}
      catch (java.beans.PropertyVetoException ex){}
  }

  private  void setNextPosition(int startingPosition){
    boolean foundNullPosition = false;
    for (int i=startingPosition; i<positions.size(); i++){
      if (positions.elementAt(i) == null){
	nextPosition = i;
	foundNullPosition = true;
	break;
      }
    }
    if (!foundNullPosition) nextPosition = positions.size();
  }    

  private Dimension calculateDimension(MDIDocument previousChild){
    Dimension d;
    if (previousChild == null){
      d = getSize();
      d.width = d.width - X_OFFSET;
      d.height = d.height - Y_OFFSET;
    }
    else d = previousChild.getSize();
    return new Dimension(d.width - X_OFFSET, d.height - Y_OFFSET);
  }

  private int calculateXPosition(MDIDocument previousChild){
    if (previousChild == null) return X_OFFSET;
    return previousChild.getX() + X_OFFSET;
  }

  private int calculateYPosition(MDIDocument previousChild){
    if (previousChild == null) return Y_OFFSET;
    return previousChild.getY() + Y_OFFSET;
  }

  /**  Adds a document of the given size to client at the given location. */
  public void addDocument(MDIDocument document, int width, int height, int x, int y){
    addDocument(document, width, height, x, y, true);
  }

  private synchronized void addDocument(MDIDocument document, int width, int height, int x, int y, boolean checkDimension){
    if (checkDimension){
      //if ((x + width > getWidth())||(y + height > getHeight())){
	//removeChildFromPositions(document);
	//addDocument(document); //ignore specified dimension/location
	//return;
      //}
      int mgrWidth = getWidth();
      int mgrHeight = getHeight();
      if (x + width > mgrWidth)
	width = mgrWidth - x - X_OFFSET;
      if (y + height > mgrHeight)
	height = mgrHeight - y - Y_OFFSET;
    }
    String title = document.toShortString();
    if ((title == null)||(title.equals(""))){
      frameCount = frameCount + 1;
      title = defaultDocumentTitle+frameCount;
      document.setTitle(title);
    }
    Image frameIcon = getMDIFrame().getIconImage();
    if (frameIcon != null &&
 	(document.getFrameIcon() == null ||
 	 document.getFrameIcon().equals(MDIDocument.defaultIcon)))
      document.setFrameIcon (new ImageIcon (frameIcon));
    children.addElement(document);
    document.getMenuEntry(0).addActionListener(actionListener);
    document.getMenuEntry(1).addActionListener(actionListener);
    document.setLayer(CHILD_FRAME_LAYER);
    document.setBounds(x, y, width, height);
    //frame.setJMenuBar(document.frameMenuBar);
    add(document);
    document.validate ();
    tilingHandler.setAvailable(true);
    if ((!noDocuments())&&(getActiveDocument().isMaximum())){
	try{
	  getActiveDocument().setMaximum(false);
	  document.setMaximum(true);
	}
	catch (java.beans.PropertyVetoException ex){} 
    }
    try{document.setSelected(true);} 
    catch (java.beans.PropertyVetoException ex){
      if (!orderedChildren.contains(document)) orderedChildren.insertElementAt(document, 0);
    }
    document.setVisible(true);
    notifyDocumentAdded(new MDIEvent(this, document));
  }

  void frameActivated(MDIDocument child){
    if (!noDocuments()){
      MDIDocument previousActiveFrame = (MDIDocument)orderedChildren.elementAt(orderedChildren.size() - 1);
      if (!child.equals(previousActiveFrame)){
	orderedChildren.removeElement(child);
	orderedChildren.addElement(child);
	popWindowMenuItems(previousActiveFrame.windowMenu);
      }
      previousActiveFrame.setMenuEntriesState(false);
    }
    else orderedChildren.addElement(child);
    snapshotValid = false;
    activateMenuBar(child);
    activateToolBarPanel(child);
    notifyActiveDocumentChanged(new DocumentEvent(this, child));
  }

  private boolean documentsModifyMenuBar = true;
  private boolean documentsModifyToolBar = true;

  /**
   * @undocumented because it is not a well thought out API
   */
  public boolean getDocumentsModifyMenuBar(){
      return documentsModifyMenuBar;
  }

  /**
   * @undocumented
   */
  public void setDocumentsModifyMenuBar(boolean documentsModifyMenuBar){
    this.documentsModifyMenuBar = documentsModifyMenuBar;
  }

  /**
   * @undocumented because it is not a well thought out API
   */
  public boolean getDocumentsModifyToolBar(){
      return documentsModifyToolBar;
  }

  /**
   * @undocumented
   */
  public void setDocumentsModifyToolBar(boolean documentsModifyToolBar){
    this.documentsModifyToolBar = documentsModifyToolBar;
  }
  
  void activateMenuBar(MDIDocument child){
    updateWindowMenu(child.windowMenu);
    if (getDocumentsModifyMenuBar()) {
      child.setMenuEntriesState(true);
      frame.setJMenuBar(child.frameMenuBar);
    }
  }

  void activateToolBarPanel(MDIDocument child){
    if (getDocumentsModifyToolBar()) 
      frame.setToolBarPanel(child.toolBarPanel);
  }
   
  private void updateWindowMenu(JMenu windowMenu){
    if (windowMenu == null) return;
    popWindowMenuItems(windowMenu);
    if (activeWindowMenuIndex == 0) activeWindowMenuIndex = 1;
    else activeWindowMenuIndex = 0;
    windowMenu.addSeparator();
    Enumeration enumeration = children.elements();
    MDIDocument childDoc;
    int menuEntryCount = 0;
    //push on menu entries, stop at max and push on more menu entry
    while (enumeration.hasMoreElements()){
      childDoc = (MDIDocument)enumeration.nextElement();
      windowMenu.add(childDoc.getMenuEntry(activeWindowMenuIndex));
      menuEntryCount++;
      if ((menuEntryCount == MAX_NUMBER_OF_WINDOW_MENU_ENTRIES)&&
	  (children.size() > MAX_NUMBER_OF_WINDOW_MENU_ENTRIES)){
	windowMenu.add(moreMenuEntries[activeWindowMenuIndex]);
	break;
      }
    }
  }

  private void popWindowMenuItems(JMenu windowMenu){
    if (windowMenu == null) return;
    int count = windowMenu.getMenuComponentCount();
    //pop more menu entry, if it exists
    if ((count > 0)&&(children.size() >= MAX_NUMBER_OF_WINDOW_MENU_ENTRIES)){
      if ((windowMenu.getMenuComponent(count - 1).equals(moreMenuEntries[0]))||
	  (windowMenu.getMenuComponent(count - 1).equals(moreMenuEntries[1]))){
	windowMenu.remove(count - 1);
	count = count - 1;
      }
    }
    if ((count > 0)&&(windowMenu.getMenuComponent(count - 1) instanceof
	MDICheckBoxMenuItem)){
      //pop all MDICheckBoxMenuItems
      for (int i=count-1; i>=0; i--){
	java.awt.Component menuItem = windowMenu.getMenuComponent(i);
	windowMenu.remove(i);
	if (!(menuItem instanceof MDICheckBoxMenuItem)) break;
      }
    }
    else if ((count > 0)&&(windowMenu.getMenuComponent(count-1) instanceof javax.swing.JSeparator))
      windowMenu.remove(count-1);
  }

  void frameDeactivated(MDIDocument child){
    if (getDocumentsModifyMenuBar())
      frame.setJMenuBar(frame.getDefaultMenuBar());
    notifyActiveDocumentChanged(new DocumentEvent(this, null));
  }

  void frameClosing(MDIDocument child){
    /*
      if (!child.isSelected()) 
      try{cild.setSelected(true);}
      catch (java.beans.PropertyVetoException ex){}
    */
    children.removeElement(child);
    orderedChildren.removeElement(child);
    MDICheckBoxMenuItem mi0 = child.getMenuEntry(0);
    MDICheckBoxMenuItem mi1 = child.getMenuEntry(1);
    mi0.removeActionListener(actionListener);
    mi1.removeActionListener(actionListener);
    popWindowMenuItems(child.windowMenu);
    //child.removeMenuEntries();
    mi0.child = null;
    mi1.child = null;
    child.menuEntries = null;
    int index = positions.indexOf(child);
    if (index >= 0) {
      positions.setElementAt(null, index);
      if (index < nextPosition) nextPosition = index;
    }
    if (orderedSnapshot != null) orderedSnapshot.removeAllElements();
    snapshotValid = false;
    remove(child);
    if (children.size() == 0)
      notifyActiveDocumentChanged(new DocumentEvent(this, null));
  }

  void frameClosed(){
    if (noDocuments()){
      updateWindowMenu(frame.getDefaultWindowMenu());
      if (getDocumentsModifyMenuBar())
	frame.setJMenuBar(frame.getDefaultMenuBar());
      if (getDocumentsModifyToolBar()) 
	frame.setToolBarPanel(frame.getDefaultToolBarPanel());
      tilingHandler.setAvailable(false);
    }
    else{
      try{
	MDIDocument docToSelect = (MDIDocument)orderedChildren.elementAt(orderedChildren.size() - 1);
	if (docToSelect.isSelected())
	  updateWindowMenu(docToSelect.windowMenu);
	else
	  docToSelect.setSelected(true);
      } catch(java.beans.PropertyVetoException e){}
    }
    repaint();
  }

  /** Returns the current active document */
  public MDIDocument getActiveDocument(){
    if (noDocuments()) return null;
    else return (MDIDocument)orderedChildren.elementAt(orderedChildren.size() - 1);
  }

  public void activatePreviousDocument() {
    int size = orderedChildren.size();
    if (size < 1) return;
    MDIDocument child;
    if (size == 1)
      child = (MDIDocument)orderedChildren.elementAt(0);
    else{
      if (!snapshotValid){
	orderedSnapshot = (Vector)orderedChildren.clone();
	nextChildIndex = size - 2;
      }
      nextChildIndex++;
      if (nextChildIndex >= size)
	nextChildIndex = 0;
      int index = nextChildIndex+1;
      if (index >= size)
	index = 0;
      child = (MDIDocument)orderedSnapshot.elementAt(index);
    }
    try{
      child.setSelected(true);
      snapshotValid = true;      
    }
    catch (java.beans.PropertyVetoException e){
      Trace.exception(e);
    }    
  }
  
  /** Activates (sets focus to) the next document */
  public void activateNextDocument(){
    if (orderedChildren.size() < 1) return;
    MDIDocument child;
    if (orderedChildren.size() == 1)
      child = (MDIDocument)orderedChildren.elementAt(0);
    else{
      if (!snapshotValid){
	orderedSnapshot = (Vector)orderedChildren.clone();
	nextChildIndex = orderedChildren.size() - 2;
      }
      child = (MDIDocument)orderedSnapshot.elementAt(nextChildIndex);
      nextChildIndex = nextChildIndex - 1;
      if (nextChildIndex < 0) nextChildIndex = orderedChildren.size() - 1;  
    }
    try{
      child.setSelected(true);
      snapshotValid = true;      
    }
    catch (java.beans.PropertyVetoException e){
      Trace.exception(e);
    }
  }

  /** Arranges all the documents according to arrangementCode. 
   *  @see com.gensym.mdi.MDITilingConstants */
  public  void arrange(int arrangementCode){
    if (noDocuments()) return;
    resetPositions();
    switch(arrangementCode){
    case TILE_HORIZONTALLY:
    case TILE_VERTICALLY:
    case TILE_CASCADE:
      tilingManager.clearLayoutComponents();
      MDIDocument child; 
      Enumeration enumeration = orderedChildren.elements();
      while (enumeration.hasMoreElements()){
	child = (MDIDocument)enumeration.nextElement();
	if (!(child.isIcon())) tilingManager.addLayoutComponent(child);
      }
      tilingManager.setTilingParameters(arrangementCode);
      setLayout(tilingManager);
      invalidate();
      validate();
      setLayout(null);
      tilingManager.clearLayoutComponents();
    }
  }

  private  void resetPositions(){
    for (int i=0; i<positions.size(); i++) positions.setElementAt(null, i);
    nextPosition = 0;
  }

  void removeChildFromPositions(MDIDocument child){
    int index = positions.indexOf(child);
    if (index >= 0){
      positions.setElementAt(null, index);
      if (index < nextPosition) nextPosition = index;
    }
  }

  /** Returns the number of documents in the client. */
  public int getDocumentCount(){
    return orderedChildren.size();
  }

  private boolean noDocuments(){
    return (orderedChildren.size() == 0);
  }

  /** Returns an array of all documents */
  public MDIDocument[] getDocuments(){
    MDIDocument[] c = new MDIDocument[orderedChildren.size()];
    orderedChildren.copyInto(c);
    return c;
  }

  /** 
   *  Returns command for tiling MDIDocuments. Actions include Tile Horizontally,
   *  Tile Vertically, and Cascade. 
   */
  public Command getTilingCommand(){
    return (Command)tilingHandler;
  }

  /** Returns the MDIFrame this MDIManager manages. */
  public MDIFrame getMDIFrame(){
    return frame;
  }

  /** Adds a MDIListener. */
  public void addMDIListener(MDIListener listener){
    listeners.addElement(listener);
  }

  /** Removes a MDIListener. */
  public void removeMDIListener(MDIListener listener){
    listeners.removeElement(listener);
  }

  private void notifyDocumentAdded(MDIEvent event){
    if (listeners.size() < 1) return;
    Vector mdiListeners;
    synchronized(this) {mdiListeners = (Vector)listeners.clone();}
    Enumeration l = mdiListeners.elements();
    while (l.hasMoreElements())
      ((MDIListener)l.nextElement()).documentAdded(event);
  }

  /**
   * @undocumented
   */
  public void addDocumentListener(DocumentListener listener){
    docListeners.addElement(listener);
  }

  /**
   * @undocumented
   */
  public void removeDocumentListener(DocumentListener listener){
    docListeners.removeElement(listener);
  }

  private void notifyActiveDocumentChanged(DocumentEvent event){
    if (docListeners.size() < 1) return;
    Vector listeners;
    synchronized(this) {listeners = (Vector)docListeners.clone();}
    Enumeration l = listeners.elements();
    while (l.hasMoreElements())
      ((DocumentListener)l.nextElement()).activeDocumentChanged(event);
  }
  

  class ActionAdapter implements ActionListener{
    @Override
    public void actionPerformed(ActionEvent e){
      Object source = e.getSource();
      if (source instanceof MDICheckBoxMenuItem){
	MDICheckBoxMenuItem menuEntry = (MDICheckBoxMenuItem)source;
	MDIDocument child = menuEntry.getMDIDocument();
	if (menuEntry.getState()){
	  if (child.equals(getActiveDocument())) return;
	  menuEntry.setState(false);
	  try{
	    if (child.isIcon()) child.setIcon(false);
	    child.setSelected(true);
	  } catch (java.beans.PropertyVetoException ex){}
	}
	else{
	  if (child.equals(getActiveDocument())) menuEntry.setState(true);
	  if (child.isIcon()) 
	    try{child.setIcon(false);} 
	  catch (java.beans.PropertyVetoException ex){}
	}
      }
      else{//selected more...
	int len = children.size();
	String[] initialValues = new String[len];
	moreWindows = new MDIDocument[len];
	children.copyInto(moreWindows);
	Enumeration enumeration = children.elements();
	int i = 0;
	while (enumeration.hasMoreElements()){
	  initialValues[i] = ((MDIDocument)enumeration.nextElement()).toShortString();
	  i++;
	}
	QuickSorter qs = new QuickSorter () {
	  @Override
	  public boolean lessThan(Object a, Object b) {
	    return a.toString().toLowerCase().
	      compareTo(b.toString().toLowerCase()) < 0;
	  }
	};
	qs.quickSortInPlace (initialValues, moreWindows);
	String title = i18n.getString("moreWindowsDlgTitle");
	String label = i18n.getString("moreWindowsDlgLabel");
	new SelectionDialog(frame, title, true, label, initialValues, false, -1, true,
			    dialogClient).setVisible(true);
      }
    } 
  }

  class DialogClientAdapter implements StandardDialogClient{
    @Override
    public void dialogDismissed (StandardDialog d, int cmdCode){
      SelectionDialog dlg = (SelectionDialog)d;
      if(dlg.wasCancelled()) return;
      int index = dlg.getResult();
      try{
	MDIDocument child = moreWindows[index];
	if (child.isIcon()) child.setIcon(false);
	child.setSelected(true);
	moreWindows = null;
      }
      catch(java.beans.PropertyVetoException ex){}
    }
  }

}







