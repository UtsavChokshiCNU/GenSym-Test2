
package com.gensym.wksp;

import java.awt.*;
import java.io.ObjectInputStream;
import java.io.IOException;
import java.io.Serializable;
import java.util.Vector;

import com.gensym.message.Trace;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.ItemListener;
import com.gensym.util.ItemEvent;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Item;
import com.gensym.draw.*;
import com.gensym.ntw.TwConnection;
import com.gensym.ntw.WorkspaceShowingEvent;
import com.gensym.ntw.WorkspaceShowingListener;
import com.gensym.ntw.util.CollectionEvent;
import com.gensym.ntw.util.CollectionListener;
import com.gensym.ntw.util.SelectionEvent;
import com.gensym.ntw.util.SelectionListener;
import com.gensym.ntw.util.WorkspaceDisplayer;
import com.gensym.ntw.util.DefaultWorkspaceShowingAdapter;
import com.gensym.ntw.util.WorkspaceDisplayStyle;
import com.gensym.ntw.util.VersionHelper;
import com.gensym.controls.ItemRetrievalEvent;
import com.gensym.controls.ItemRetrievalListener;


/**
 * A bean for displaying one workspace at a time from a set of workspaces.
 * Essentially a wrapper around <code>MultipleWorkspaceView</code>.
 * Users wanting this view to handle show and hide events from g2 need
 * to add this panel as a WorkspaceShowingListener to the g2 connection.
 * @see com.gensym.wksp.MultipleWorkspaceView
 */
public class MultipleWorkspacePanel extends com.gensym.util.DoubleBufferPanel implements WorkspaceShowingListener, WorkspaceDisplayer, com.gensym.util.symbol.WorkspaceShowingSymbols, ItemRetrievalListener {

  static final long serialVersionUID = 3416968328157382062L;
  private MultipleWorkspaceView view;
  private boolean showNewWorkspaces = true;
  private boolean updateWhileHidden = false;
  private ViewScrollbar hscroll, vscroll;
  private Vector collectionListeners;
  
  /**
   * Initializes the scrollbars and the underlying <code>MultipleWorkspaceView</code>.
   */
  public MultipleWorkspacePanel () {
    collectionListeners = new Vector ();
    setLayout (new BorderLayout ());
    add (view = new MultipleWorkspaceView (), "Center");
    hscroll
      = new ViewScrollbar (view, Scrollbar.HORIZONTAL,0,100,0,100);
    vscroll
      = new ViewScrollbar (view, Scrollbar.VERTICAL, 0,100,0,100);
    view.addScrollbar(vscroll,false);
    view.addScrollbar(hscroll,true);
    add(hscroll, "South");
    add(vscroll, "East");
    //view.setDoubleBuffered (true);
  }

  @Override
  public void update (Graphics g) {
    paint (g);
  }

  /**
   * Add <code>wksp</code> to the list of workspaces that can be
   * displayed. If <code>showNewWorkspace</code> is true, then calls
   * <code>setCurrentWorkspace</code> with this workspace, after it has
   * been added.
   * @param <code>wksp</code> a <code>KbWorkspace</code> obtained from G2.
   */
  public void addWorkspace (KbWorkspace wksp) {
    view.addWorkspace (wksp, updateWhileHidden);
    fireCollectionChangeEvent();
  }  

  /**
   * @undocumented non-overridden method for VB
   */
  public void addWorkspaceForVB (KbWorkspace wksp) {
    addWorkspace (wksp);
  }


  /**
   * @undocumented non-overridden method for VB
   */
  public void addWorkspaceForVBTwo (KbWorkspace wksp, int updateWhileHiddenPseudoBoolean) {
    addWorkspace (wksp, !(updateWhileHiddenPseudoBoolean == 0));
  }

  private ItemListener itemDeletedAdapter;
  
  /**
   * Add <code>wksp</code> to the list of workspaces that can be
   * displayed.
   * @param <code>wksp</code> a <code>KbWorkspace</code> obtained from G2.
   * @param <code>updateWhileHidden</code> keep this workspace up-to-date, even when
   * it is not showing in the panel.
   */
  public void addWorkspace (KbWorkspace wksp, boolean updateWhileHidden) {
    view.addWorkspace (wksp, updateWhileHidden);
    fireCollectionChangeEvent();
    if (showNewWorkspaces) {
      try {
	view.setCurrentWorkspace(wksp);
      } catch (WorkspaceNotAddedException newe) {
	Trace.exception(newe);
      }
    }
    try {
      if (itemDeletedAdapter == null)
	itemDeletedAdapter = new ItemListener() {
	@Override
	public void receivedInitialValues (ItemEvent e) {}
	@Override
	public void itemModified (ItemEvent e) {}
	@Override
	public void itemDeleted (ItemEvent e) {
	  KbWorkspace deletedWorkspace = (KbWorkspace)e.getItem();
	  removeWorkspace(deletedWorkspace);
	}
      };
      wksp.addItemListener(itemDeletedAdapter);
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
      removeWorkspace(wksp);
    }
  }

  /**
   * Removes the first occurence of the given workspace from the
   * list of workspaces.  If a view is cached for this workspace, it
   * too will be decached at this time.  If this workspace is the current
   * workspace, then the current workspace will first be set to the next
   * workspace in the workspace list, after which, the given workspace
   * will be removed.
   * @param <code>wksp</code> the workspace to remove.
   * @return true if the <code>KbWorkspace wksp</code> was in the list
   * of workspaces, false otherwise.
   */
  public boolean removeWorkspace(KbWorkspace wksp)
  {
    try {
      wksp.removeItemListener(itemDeletedAdapter);
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
    if (view.removeWorkspace(wksp)) {
      fireCollectionChangeEvent();
      return true;
    }
    return false;
  }
  
  void fireCollectionChangeEvent() {
    int listenerCount;
    Vector listeners = null;
    synchronized (collectionListeners) {
      listenerCount = collectionListeners.size ();
      if (listenerCount != 0)
	listeners = (Vector) collectionListeners.clone ();
    }
    if (listenerCount != 0) {
      CollectionEvent collectionEvent = new CollectionEvent(this);
      for (int i=0; i<listenerCount; i++)
	((CollectionListener)listeners.elementAt(i)).collectionChanged(collectionEvent);
    }
  }

  /**
   * Gets all the workspaces than can be shown.
   * @return an array of workspaces corresponding to
   * the multiple view's current list of workspaces.
   */
  public KbWorkspace[] getWorkspaces()
  {
    return view.getWorkspaces();
  }

  /**
   * Adds the specified collection listener to receive collection events from this panel.
   */
  public void addCollectionListener(CollectionListener collectionListener)
  {
    collectionListeners.addElement(collectionListener); 

  }
  /**
   * Removes the specified key listener so it no longer receives key events from this component.
   */
  public void removeCollectionListener(CollectionListener collectionListener)
  {
    collectionListeners.removeElement(collectionListener); 
  }

  public void addScrollbar (ViewScrollbar scrollbar, boolean isHorizontal) {
    view.addScrollbar (scrollbar, isHorizontal);
  }

  public void removeScrollbar (ViewScrollbar scrollbar, boolean isHorizontal) {
    view.removeScrollbar (scrollbar, isHorizontal);
  }

  /**
   * Set <code>wksp</code> to be the workspace currently displayed.
   */
  public void setCurrentWorkspace (KbWorkspace wksp)
       throws WorkspaceNotAddedException
  {
    view.setCurrentWorkspace (wksp);
  }

  /**
   * Cause the panel to display the next workspace in its list.
   */
  public void nextWorkspace() {
    view.nextWorkspace ();
  }

  /**
   * Cause the panel to display the previous workspace in its list.
   */
  public void previousWorkspace() {
    view.previousWorkspace ();
  }

  /**
   * Is <code>wksp</code> already listed in the <code>MulitpleWorkspaceView</code>.
   */
  public boolean contains(KbWorkspace wksp) {
    return view.contains(wksp);
  }

  private WorkspaceShowingListener showingAdapter = new PanelShowingAdapter ();

  class PanelShowingAdapter extends DefaultWorkspaceShowingAdapter implements Serializable {

    PanelShowingAdapter () {
      super (null);
    }

    @Override
    public java.lang.Object getDisplayContainer (KbWorkspace wksp, WorkspaceDisplayStyle style) {
      if (style == null)
	return MultipleWorkspacePanel.this;
      else
	return super.getDisplayContainer (wksp, style);
    }
  }

  private void readObject (ObjectInputStream stream) throws IOException, ClassNotFoundException {
    stream.defaultReadObject ();
    if (showingAdapter == null)
      showingAdapter = new PanelShowingAdapter ();
  }

  /**
   * Handle a request to show a particuliar workspace.
   */
  @Override
  public void showWorkspace(WorkspaceShowingEvent event) {
    showingAdapter.showWorkspace (event);
  }

  @Override
  public boolean displayWorkspace (TwConnection cxn, KbWorkspace wksp, Structure showParticulars) {
    WorkspaceView currentView = null;
    if (!view.contains(wksp)){
      addWorkspace(wksp, updateWhileHidden);
      currentView = view.getCurrentView();
    } else if (showNewWorkspaces) {
      try {
	view.setCurrentWorkspace(wksp);
	currentView = view.getCurrentView();
      } catch (WorkspaceNotAddedException newe) {
	Trace.exception(newe);
      }
    }
    if (currentView != null)//(view contains wksp && showNewWorkspaces == false) => (currentView == null)
      currentView.showWorkspace(showParticulars);
    
    return true;
  }

  /**
   * Handle a request to hide a particuliar workspace.
   */
  @Override
  public void hideWorkspace (WorkspaceShowingEvent event) {
    showingAdapter.hideWorkspace (event);
  }

  @Override
  public boolean removeWorkspace (TwConnection cxn, KbWorkspace wksp, Structure particulars) {
    removeWorkspace(wksp);
    return true;
  }

  /**
   * Scrolls the workspace view to the given location.
   * @param x The x position in workspace coordinates
   * @param y The y position in workspace coordinates
   */
  public void scrollToLocation(int x, int y)
  {
    view.scrollToLocation (x, y);
  }
  
 /**
   * Set whether to automatically show newly retrieved workspaces.
   * Defaults  to <code>true</code>.
   */
  public void setShowNewWorkspaces(boolean show) {
    showNewWorkspaces = show;
  }

  /**
   * For COM.
   * @undocumented
   */
  public void setShowNewWorkspacesForVB(int pseudoBoolean) {
    setShowNewWorkspaces(!(pseudoBoolean == 0));
  }

  /**
   * Will this panel automatically show new workpaces as they are
   * received.
   */
  public boolean getShowNewWorkspaces() {
    return showNewWorkspaces;
  }

  /**
   * Set whether to automatically show newly retrieved workspaces.
   * Defaults  to <code>true</code>.
   * @deprecated
   * @see #setShowNewWorkspaces
   */
  public void setShowNewWorkspace(boolean show) {
    showNewWorkspaces = show;
  }

  /**
   * Will this panel automatically show new workpaces as they are
   * received.
   * @deprecated
   * @see #getShowNewWorkspaces
   */
  public boolean getShowNewWorkspace() {
    return showNewWorkspaces;
  }

  /**
   * Will newly added workspaces be automatically kept up to date 
   * even when they are not visible.
   * Defaults to <code>false</code>.
   */
  public void setUpdateWhileHidden(boolean update) {
    updateWhileHidden = update;
  }

  /**
   * For COM.
   * @undocumented
   */
  public void setUpdateWhileHiddenForVB(int pseudoBoolean) {
    setUpdateWhileHidden(!(pseudoBoolean == 0));
  }

  /**
   * Will newly added workspaces be automatically kept up to date 
   * even when they are not visible.
   */
  public boolean getUpdateWhileHidden() {
    return updateWhileHidden;
  }

  /**
   * Will newly added workspaces be automatically kept in history.
   * Defaults to <code>false</code>.
   * @deprecated
   * @see #setUpdateWhileHidden
   */
  public void setKeepInHistory(boolean keep) {
    updateWhileHidden = keep;
  }

  /**
   * Will newly added workspaces be automatically kept in history.
   * @deprecated
   * @see #getUpdateWhileHidden
   */
  public boolean getKeepInHistory() {
    return updateWhileHidden;
  }

  /**
   * Add the retrieved item to the list of workspaces, causing it
   * to be shown, if so requested.
   * @see setShowNewWorkspaces
   * @exception IllegalArgumentException when the event contains an
   * <code>Item</code> that is not a <code>KbWorkspace</code>.
   */
  @Override
  public void itemRetrieved(ItemRetrievalEvent event) {
    Item item = event.item;

    if (!(item instanceof KbWorkspace)) {
      throw new IllegalArgumentException();
    }

    KbWorkspace wksp = (KbWorkspace)item;

    if (!view.contains(wksp)) {
      addWorkspace(wksp, updateWhileHidden);
    } else if (showNewWorkspaces) {
      try {
	view.setCurrentWorkspace(wksp);
      } catch (WorkspaceNotAddedException newe) {
	Trace.exception(newe);
      }
    }
  }

  /**
   * Currently prints a message to standard out if an itemRetrieval
   * fails.
   */
  @Override
  public void itemRetrievalFailed(ItemRetrievalEvent event) {
    String message = event.message.getMessage();
    Throwable ex = event.exception;
    if (message != null)
      System.out.println(message);

    if (ex != null) {
      System.out.println(ex.getMessage());
      ex.printStackTrace();
    }
  }

  /**
   * Resizes the panel, reinitializing the scollbars if neccessary
   */
  @Override
  public void reshape (int x, int y, int width, int height) {
    super.reshape (x, y, width, height);
    remove (hscroll);
    remove (vscroll);
    remove (view);
    add (vscroll, "East");
    add (hscroll, "South");
    add (view, "Center");
    doLayout ();
  }

  /**
   * Find an element created from the <code>Item item</code>.
   * @param <code>item</code> the <code>Item</code> for which to find a
   * <code>WorkspaceElement</code>.
   * @return The last <code>WorkspaceElement</code> that was added
   * to this view whose item is equal to <code>item</code>, or null if no
   * such element exists.
   * @see com.gensym.wksp.WorkspaceElement#getItem()
   * @see com.gensym.wksp.WorkspaceView#findElement
   */
  public WorkspaceElement findElement(Item item) {
    if (view != null) {
      WorkspaceView wView = view.getCurrentView();
      if (wView != null)
	return wView.findElement(item);
    }
    return null;
  }
  
  /**
   * Clears the selection and adds the given elements to the
   * selection of the current view.
   * @see addElementsToSelection
   */
  public void selectElements (WorkspaceElement[] newSelection) {
    if (view != null)
      view.selectElements(newSelection);
  }
  
  /**
   * Adds the given elements to the selection of the current view.
   */
  public void addElementsToSelection (WorkspaceElement[] newSelection) {
    if (view != null)
      view.addElementsToSelection(newSelection);
  }
  
  /**
   * Adds the given element to the selection of the current view.
   */      
  public void addElementToSelection (WorkspaceElement newElt) {
    if (view != null)
      view.addElementToSelection(newElt);
  }
  
  /**
   * Removes the given elements from the selection of the current view.
   */
  public void removeElementsFromSelection (WorkspaceElement[] eltsToRemove) {
    if (view != null)
      view.removeElementsFromSelection(eltsToRemove);
  }
  
  /**
   * Removes the given element from the selection of the current view.
   */
  public void removeElementFromSelection (WorkspaceElement eltToRemove) {
    if (view != null)
      view.removeElementFromSelection(eltToRemove);
  }
  
  /**
   * @return the current selection of the current view.
   */
  public WorkspaceElement[] getSelection () {
    if (view != null)
      return view.getSelection();
    else
      return null;
  }

  /**
   * For VB only
   * @undocumented
   */
  public Sequence getSelectionAsSequence() {
    if (view != null)
      return view.getSelectionAsSequence();
    else
      return null;
  }
  
  
  /**
   * Clears the current selection of the current view.
   */    
  public void clearSelection () {
    if (view != null)
      view.clearSelection();
  }
  
  /**
   * Moves the current selection of the current view by the given deltas.
   * @param <code>deltaX</code> the horizontal distance by which each element should be moved.
   * @param <code>deltaY</code> the vertical distance by which each element should be moved.
   * @param <code>enlargeWorkspaceIfNecessary</code> if true instructs G2 to stretch the workspace,
   * otherwise the element is constrained within the workspace's margins.
   */    
  public void moveSelection (int deltaX, int deltaY, boolean enlargeWorkspaceIfNecessary) {
   if (view != null)
     view.moveSelection(deltaX, deltaY, enlargeWorkspaceIfNecessary);
  }

  /**
   * For COM.
   * @undocumented
   */
  public void moveSelectionForVB (int deltaX, int deltaY, int pseudoBoolean) {
    moveSelection(deltaX, deltaY, !(pseudoBoolean == 0));
  }

  /**
   * Resizes the current selection of the current view to the given bounds.
   */    
  public void resizeSelection (int left, int top, int right, int bottom) {
    if (view != null)
     view.resizeSelection(left, top, right, bottom);
  }
  
  /**
   * Adds all of current workspace's elements to the current selection.
   */
  public void selectAll () {
    if (view != null)
      view.selectAll();
  }
  
  /**
   * Deletes the items corresponding to each of the elements
   * in the current selection of the current view.
   */    
  public void deleteSelection () {
    if (view != null)
      view.deleteSelection();
  }
  
  /**
   * @param <code>sl</code> the <code>SelectionListener</code> to add.
   */   
  public void addSelectionListener (SelectionListener sl) {
    if (view != null)
      view.addSelectionListener(sl);
  }
  
  /**
   * @param <code>sl</code> the <code>SelectionListener</code> to remove.
   */    
  public void removeSelectionListener (SelectionListener sl) {
    if (view != null)
      view.removeSelectionListener(sl);
  }
  
  /**
   * Sets the current block increment used for scrolling.
   * This is typically used for scrolling pages at a time.
   */
  public void setBlockIncrement(int blockIncrement)
  {
    if (view != null)
      view.setBlockIncrement(blockIncrement);
  }
  
  /**
   * Sets the current unitIncrement used for scrolling.
   * This is typically used for scrolling using the arrow keys.
   */
  public void setUnitIncrement(int unitIncrement)
  {
    if (view != null)
      view.setUnitIncrement(unitIncrement);
  }
  
  /**
   * @return the current blockIncrement used for scrolling.
   * This is typically used for scrolling pages at a time.
   */
  public int getBlockIncrement()
  {
    if (view != null)
      return view.getBlockIncrement();
    else
      return 0;
  }
  
  /**
   * @return the current unitIncrement used for scrolling.
   * This is typically used for scrolling using the arrow keys.
   */
  public int getUnitIncrement()
  {
    if (view != null)
      return view.getUnitIncrement();
    else
      return 0;
  }
  
  /**
   * Scrolls the current view up by the current unit increment.
   */
  public void scrollUnitUp()
  {
    if (view != null)
      view.scrollUnitUp();
  }
  
  /**
   * Scrolls the current view down by the current unit increment.
   */            
  public void scrollUnitDown()
  {
    if (view != null)
      view.scrollUnitDown();
  }
  
  /**
   * Scrolls the current view to the left by the current unit increment.
   */            
  public void scrollUnitLeft()
  {
    if (view != null)
      view.scrollUnitLeft();
  }
  
  /**
   * Scrolls the current view to the right by the current unit increment.
   */          
  public void scrollUnitRight()
  {
    if (view != null)
      view.scrollUnitRight();
  }
  
  /**
   * Scrolls the current view up by the current block increment.
   */
  public void scrollBlockUp()
  {
    if (view != null)
      view.scrollBlockUp();
  }
  
  /**
   * Scrolls the current view down by the current block increment.
   */            
  public void scrollBlockDown()
  {
    if (view != null)
      view.scrollBlockDown();
  }
  
  /**
   * Scrolls the current view to the left by the current block increment.
   */            
  public void scrollBlockLeft()
  {
    if (view != null)
      view.scrollBlockLeft();
  }
  
  /**
   * Scrolls the current view to the right by the current block increment.
   */  
  public void scrollBlockRight()
  {
    if (view != null)
      view.scrollBlockRight();
  }

  /**
   * @undocumented Needed for method dispatch in VB to work around
   * Plug-in bug of not delivering exceptions
   */
  public Object getThis () {
    return this;
  }

  /**
   * Sets the scale of the WorkspaceView currently displayed
   * Only available in JDK1.2
   * @see com.gensym.wksp.WorkspaceView#isScalingAvailable
   */
  public void setCurrentScale(double scale){
    WorkspaceView currentView = view.getCurrentView();
    if (currentView == null) return;
    VersionHelper.setScale(currentView, scale, scale);
  }

  /**
   * Returns the scale of the WorkspaceView currently displayed
   * Only available in JDK1.2
   * @see com.gensym.wksp.WorkspaceView#isScalingAvailable
   */
  public double getCurrentScale(){
    WorkspaceView currentView = view.getCurrentView();
    if (currentView == null) return 1.0;
    return VersionHelper.getScaleX(currentView);
  }

  /**
   * Sets the current WorkspaceView to scale to fit
   * Only available in JDK1.2
   * @see com.gensym.wksp.WorkspaceView#isScalingAvailable
   */
  public void setScaledToFit(boolean scaledToFit){
    WorkspaceView currentView = view.getCurrentView();
    if (currentView == null) return;
    VersionHelper.setScaledToFit(currentView, scaledToFit);
  }

  /**
   * Returns true if the current WorkspaceView is scaled to fit
   * Only available in JDK1.2
   * @see com.gensym.wksp.WorkspaceView#isScalingAvailable
   */
  public boolean isScaledToFit(){
    WorkspaceView currentView = view.getCurrentView();
    if (currentView == null) return false;
    return VersionHelper.isScaledToFit(currentView);
  }

}
