
package com.gensym.wksp;

import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.ntw.*;
import com.gensym.ntw.util.SelectionListener;
import com.gensym.ntw.util.SelectionEvent;
import com.gensym.irm.*;
import com.gensym.jgi.G2AccessException;
import java.util.*;
import java.awt.*;
import java.awt.event.*;
import com.gensym.draw.*;
import com.gensym.classes.KbWorkspace;
import com.gensym.dispatcher.TableDrivenEventHandler ;


/**
 * A helper class for mantaining and showing a set of workspaces.
 * The <code>addWorkspace</code> and <code>setWorkspace</code> methods.
 * may throw checked exceptions in future releases.
 */

public class MultipleWorkspaceView
extends Container
implements Scrollable {

  static final long serialVersionUID = 4095711762746731029L;
  private WorkspaceView currentView;
  private Vector workspaces;
  private ViewScrollbar horizontalScrollbar;
  private ViewScrollbar verticalScrollbar;

  /**
   * Constructs an empty <code>MultipleWorkspaceView</code> with a
   * <code>BorderLayout</code>.
   */
  public MultipleWorkspaceView () {
    setLayout(new BorderLayout ());    
    this.workspaces = new Vector();
  }


  private WorkspaceView getView(int index) {
    return ((ViewEntryData)workspaces.elementAt(index)).view;
  }

  private int findWorkspaceIndex (KbWorkspace wksp) {
    for (int i=0; i<workspaces.size (); i++)
      if (((ViewEntryData)workspaces.elementAt (i)).wksp.equals (wksp))
	return i;
    return -1;
  }

  private KbWorkspace getWorkspaceAtIndex (int index) {
    ViewEntryData ved = (ViewEntryData)workspaces.elementAt (index);
    return ved.wksp;
  }

  private void storeView(int index, WorkspaceView view) {
    ViewEntryData ved = (ViewEntryData)workspaces.elementAt (index);
    ved.view = view;
  }

  private boolean getHistoryAtIndex (int index) {
    ViewEntryData ved = (ViewEntryData)workspaces.elementAt (index);
    return ved.keepHistory;
  }

  private int currentIndex() {
    if (currentView != null) {
      KbWorkspace currentWorkspace = currentView.getWorkspace();
      return findWorkspaceIndex (currentWorkspace);
    } else
      return -1;
  }

  private int nextIndex() {
    int currentIndex = currentIndex();
    int nextIndex = currentIndex + 1;
    if (nextIndex >= workspaces.size())
      nextIndex = 0;
    return nextIndex;
  }

  private int previousIndex() {
    int currentIndex = currentIndex();
    int previousIndex = currentIndex - 1;
    if (previousIndex < 0)
      previousIndex = (workspaces.size() - 1);
    return previousIndex;
  }

  private void setCurrentWorkspace(int index) {
    if (workspaces.size() == 0) return;
    KbWorkspace wksp = getWorkspaceAtIndex (index);
    boolean keepHistory = getHistoryAtIndex (index);
    if (currentView == null || (currentView.getWorkspace() != wksp)) {
      removeCurrentView();
      //repaint(); //refresh with a message that were changing views?
      if (keepHistory) {
	currentView = getView(index);
	if (currentView == null) {
	  currentView = WorkspaceView.createWorkspaceView(this, wksp);
	  //currentView.setEventHandler (new RubberBandHandler ());
	  storeView(index,currentView);	
	} 
      } else {
	currentView = WorkspaceView.createWorkspaceView(this, wksp);
	//currentView.setEventHandler (new RubberBandHandler ());
	storeView(index,currentView);
      }
      addSelectionListenersToCurrentView();
      currentView.setLocation(0,0);
      add("Center",currentView);
      if (verticalScrollbar != null) {
	currentView.addScrollbar(verticalScrollbar, false);
      }
      if (horizontalScrollbar != null) {
	currentView.addScrollbar(horizontalScrollbar, true);
      }
      Rectangle bounds = getBounds();
      //this will resynch the scrollbars
      currentView.setBounds(0, 0, bounds.width, bounds.height);
      repaint();
    }
  }

  private void removeCurrentView(){
    if (currentView == null) return;
    if (verticalScrollbar != null)
      currentView.removeScrollbar(verticalScrollbar, false);
    if (horizontalScrollbar != null)
      currentView.removeScrollbar(horizontalScrollbar, true);
    removeSelectionListenersFromCurrentView();
    EventHandler eh = currentView.getEventHandler() ;
    currentView.setEventHandler(null) ;
    if (eh instanceof TableDrivenEventHandler)
      ((TableDrivenEventHandler)eh).dispatch = null ;
    remove(currentView);
    currentView = null;
  }

  /**
   * Sets the current workspace for this view to the first occurence
   * of the given workspace.  A view new for this workspace will be made
   * at this time.  (If keepHistory is true for the workspace and a
   * view is already cached then the view will be retrieved from the
   * view cache.)  This view will then be shown as the current view.
   * All scroll bars will automatically be reset according to the scrollstate
   * of this view.  If the previously shown workspace does not keep a view
   * history then the handle to its view is dropped at this time, allowing
   * it to be garbage collected.
   * @param <code>wksp</code> the <code>KbWorkspace</code> to set as the current workspace.
   */
  public void setCurrentWorkspace(KbWorkspace wksp)
       throws WorkspaceNotAddedException
  {
    if (findWorkspaceIndex (wksp) >= 0) //workspaces.contains(wksp))
      setCurrentWorkspace(findWorkspaceIndex (wksp)); //workspaces.indexOf(wksp));
    else
      throw new WorkspaceNotAddedException(wksp);
  }

  /**
   * Sets the current workspace to the workspace that follows
   * the current workspace in the multiple view's workspace list.
   * @see #setCurrentWorkspace
   */
  public void nextWorkspace() {
    setCurrentWorkspace(nextIndex());
  }

  /**
   * Sets the current workspace to the workspace that precedes
   * the current workspace in the multiple view's workspace list.
   * @see #setCurrentWorkspace
   */
  public void previousWorkspace() {
    setCurrentWorkspace(previousIndex());
  }

  /**
   * Is <code>wksp</code> already listed in this view.
   */
  public boolean contains(KbWorkspace wksp) {
    return (findWorkspaceIndex (wksp) >= 0); //workspaces.contains(wksp);
  }

  /**
   * Adds the workspace to the end of the workspace list.
   * A view for this workspace is not constructed until this
   * workspace is viewed for the first time.
   * @param <code>wksp</code> the <code>KbWorkspace</code> to be added.
   * @param <code>keepHistory</code> a <code>boolean</code> specifying whether to cache
   * the view for this workspace, once it is constructed.
   */
  public void addWorkspace(KbWorkspace wksp, boolean keepHistory) {
    workspaces.addElement (new ViewEntryData (wksp, keepHistory));
  }

  /**
   * Removes the first occurence of the given workspace from the
   * list of workspaces.  If a view is cached for this workspace, it
   * too will be decached at this time.  If this workspace is the current
   * workspace, then the current workspace will first be set to the next
   * workspace in the workspace list, after which, the given workspace
   * will be removed.
   * @param <code>wksp</code> the <code>KbWorkspace</code> to remove.
   * @return true if the <code>KbWorkspace wksp</code> was in the
   * list of workspaces, false otherwise.
   */
  public boolean removeWorkspace(KbWorkspace wksp) {
    int index = findWorkspaceIndex (wksp);
    if (index != -1) {
      Object viewToRemove = getView (index);
      workspaces.removeElementAt(index);
      if (currentView == viewToRemove) {
	if (workspaces.size () > 0)
	  nextWorkspace();
	else {
	  removeCurrentView();
	  repaint();
	}
      }
      ((WorkspaceView) viewToRemove).dispose();
      return true;
    } else
      return false;
  }
  
  /**
   * Gets the current <code>WorkspaceView</code>.
   * @return the <code>WorkspaceView</code> that is currently showing.
   */
  public WorkspaceView getCurrentView() {
    return currentView;
  }

  /**
   * Gets all the workspaces than can be shown.
   * @return an array of <code>KbWorkspace</code>s corresponding to
   * the multiple view's current list of workspaces.
   */
  public KbWorkspace[] getWorkspaces() {
    int count = workspaces.size();
    KbWorkspace[] workspaceArray = new KbWorkspace[count];
    for (int i=0; i<workspaces.size(); i++)
      workspaceArray[i] = ((ViewEntryData)workspaces.elementAt (i)).wksp;
    return workspaceArray;
  }


  
  ////Scrollable Interface


  @Override
  public void addScrollbar(ViewScrollbar scrollbar, boolean isHorizontal) {
    if (isHorizontal)
      horizontalScrollbar = scrollbar;
    else
      verticalScrollbar = scrollbar;
    if (currentView != null)
      currentView.addScrollbar(scrollbar, isHorizontal);
  }

  @Override
  public void removeScrollbar(ViewScrollbar scrollbar, boolean isHorizontal) {
    if (currentView != null)
      currentView.removeScrollbar(scrollbar, isHorizontal);
    if (isHorizontal)
      horizontalScrollbar = null;
    else
      verticalScrollbar = null;
  }
  
  @Override
  public void addScrollObserver (java.util.Observer o, boolean isHorizontal) {
    /*if (isHorizontal)
      horizontalObservers.add(o);
      else
      verticalObservers.add(o);
      if (currentView != null)
      */
    if (currentView != null)
      currentView.addScrollObserver(o, isHorizontal);
  }
  
  @Override
  public ViewScrollState getScrollState(boolean isHorizontal) {
    if (currentView != null)
      return currentView.getScrollState(isHorizontal);
    else
      return null;
  }
  
  @Override
  public void setScroll() {
    if (currentView != null)
      currentView.setScroll();
  }
  
  @Override
  public void setScroll(int logicalLeft, int logicalTop,
                        int logicalRight, int logicalBottom) {
    if (currentView != null)
      currentView.setScroll(logicalLeft, logicalTop,
			    logicalRight, logicalBottom);
  }
  
  @Override
  public void setScroll(int logicalLeft, int logicalTop,
                        int logicalRight, int logicalBottom,
                        int viewLeft, int viewTop,
                        int viewRight, int viewBottom) {
    if (currentView != null)
      currentView.setScroll(logicalLeft, logicalTop,
			    logicalRight, logicalBottom,
			    viewLeft, viewTop,
			    viewRight, viewBottom);
  }
  
  @Override
  public void growLogical(int size, boolean isHorizontal, 
                          boolean setMinimum) {
    if (currentView != null)
      currentView.growLogical(size, isHorizontal, setMinimum);
  }
  
  @Override
  public void scrollView(int distance, boolean is_horizontal) {
    if (currentView != null)
      currentView.scrollView(distance, is_horizontal);
  }
  

  /**
   * @deprecated As of version 1.1, use scrollToLocation(int, int) instead.
   */
  @Override
  public void scrollViewAbsolute(int new_view_min, boolean is_horizontal) {
    if (currentView != null)
      currentView.scrollViewAbsolute(new_view_min, is_horizontal);
  }

  /**
   * Scroll the current WorkspaceView.
   * @see com.gensym.wksp.WorkspaceView#scrollToLocation
   * @since Telewindows2 Toolkit 1.1 rev. 0
   */
  public void scrollToLocation(int x, int y){
    if (currentView != null)
      currentView.scrollToLocation(x, y);
  }
  
  /**
   * Clears the selection and adds the given elements to the
   * selection of the current view.
   * @see #addElementsToSelection
   */
  public void selectElements (WorkspaceElement[] newSelection) {
    if (currentView != null)
      currentView.selectElements(newSelection);
  }
  
  /**
   * Adds the given elements to the selection of the current view.
   */
  public void addElementsToSelection (WorkspaceElement[] newSelection) {
    if (currentView != null)
      currentView.addElementsToSelection(newSelection);
  }
  
  /**
   * Adds the given element to the selection of the current view.
   */    
  public void addElementToSelection (WorkspaceElement newElt) {
    if (currentView != null)
      currentView.addElementToSelection(newElt);
  }
  
  /**
   * Removes the given elements to the selection of the current view.
   */
  public void removeElementsFromSelection (WorkspaceElement[] eltsToRemove) {
    if (currentView != null)
      currentView.removeElementsFromSelection(eltsToRemove);
  }
  
  /**
   * Removes the given element to the selection of the current view.
   */
  public void removeElementFromSelection (WorkspaceElement eltToRemove) {
    if (currentView != null)
      currentView.removeElementFromSelection(eltToRemove);
  }
  
  /**
   * @return the current selection of the current view.
   */
  public WorkspaceElement[] getSelection () {
    if (currentView != null)
      return currentView.getSelection();
    else
      return null;
  }

  /**
   * For VB only
   * @undocumented
   */
  public Sequence getSelectionAsSequence() {
    if (currentView != null)
      return currentView.getSelectionAsSequence();
    else
      return null;
  }
  
  /**
   * Clears the current selection of the current view.
   */  
  public void clearSelection () {
    if (currentView != null)
      currentView.clearSelection();
  }
  
  /**
   * Moves the current selection of the current view by the given deltas.
   * @param <code>deltaX</code> the horizontal distance by which each element should be moved.
   * @param <code>deltaY</code> the vertical distance by which each element should be moved.
   * @param <code>enlargeWorkspaceIfNecessary</code> if true instructs G2 to stretch the workspace,
   * otherwise the element is constrained within the workspace's margins.
   */    
  public void moveSelection (int deltaX, int deltaY, boolean enlargeWorkspaceIfNecessary) {
   if (currentView != null)
     currentView.moveSelection(deltaX, deltaY, enlargeWorkspaceIfNecessary);
  }
  
  /**
   * Resizes the current selection of the current view to the given bounds.
   */  
  public void resizeSelection (int left, int top, int right, int bottom) {
    if (currentView != null)
     currentView.resizeSelection(left, top, right, bottom);
  }
  
  /**
   * Adds all of current workspace's elements to the current selection.
   */
  public void selectAll () {
    if (currentView != null)
      currentView.selectAll();
  }
  
  /**
   * Deletes the items corresponding to each of the elements
   * in the current selection of the current view.
   */  
  public void deleteSelection () {
    if (currentView != null)
      currentView.deleteSelection();
  }

  private Vector selectionListeners = new Vector();
  private void addSelectionListenersToCurrentView()
  {
    if (currentView != null) { 
      int listenerCount;
      Vector listeners = null;
      synchronized (selectionListeners) {
	listenerCount = selectionListeners.size();
	if (listenerCount == 0)
	  return;
	listeners = (Vector) selectionListeners.clone();
      }
      for (int i=0; i<listenerCount; i++) {
	SelectionListener listener = ((SelectionListener)listeners.elementAt (i));
      if (listener != null)
 	currentView.addSelectionListener(listener);
      }
    }
  }
  
  private void removeSelectionListenersFromCurrentView()
  {
    if (currentView != null) { 
      int listenerCount;
      Vector listeners = null;
      synchronized (selectionListeners) {
	listenerCount = selectionListeners.size();
	if (listenerCount == 0)
	  return;
	listeners = (Vector) selectionListeners.clone();
      }
      for (int i=0; i<listenerCount; i++) {
	SelectionListener listener = ((SelectionListener)listeners.elementAt (i));
      if (listener != null)
 	currentView.removeSelectionListener(listener);
      }
    }
  }
  
  /**
   * Adds a new <code>SelectionListener</code> to this multiple view.
   * @param <code>sl</code> the <code>SelectionListener</code> to add to the
   * current view.
   */    
  public void addSelectionListener (SelectionListener sl) {
    selectionListeners.addElement(sl);
    if (currentView != null)
      currentView.addSelectionListener(sl);
  }
  
  /**
   * Remove a <code>SelectionListener</code> from this multiple view.
   * @param <code>sl</code> the <code>SelectionListener</code> to remove from
   * current view.
   */    
  public void removeSelectionListener (SelectionListener sl) {
    selectionListeners.removeElement(sl);
    if (currentView != null)
      currentView.removeSelectionListener(sl);
  }
  
  /**
   * Sets the current block increment used for scrolling.
   * This is typically used for scrolling pages at a time.
   */
  public void setBlockIncrement(int blockIncrement)
  {
    if (currentView != null)
      currentView.setBlockIncrement(blockIncrement);
  }
  
  /**
   * Sets the current unit increment used for scrolling.
   * This is typically used for scrolling using the arrow keys.
   */
  public void setUnitIncrement(int unitIncrement)
  {
    if (currentView != null)
      currentView.setUnitIncrement(unitIncrement);
  }
  
  /**
   * Get the current block increment for this multipleView.
   * This is typically used for scrolling pages at a time.
   * @return the current block increment used for scrolling.
   */
  public int getBlockIncrement()
  {
    if (currentView != null)
      return currentView.getBlockIncrement();
    else
      return 0;
  }
  
  /**
   * Get the current unit increment for this multipleView.
   * This is typically used for scrolling using the arrow keys.
   * @return the current unit increment used for scrolling.
   */
  public int getUnitIncrement()
  {
    if (currentView != null)
      return currentView.getUnitIncrement();
    else
      return 0;
  }
  
  /**
   * Scrolls the currentView up by the current unit increment.
   */
  public void scrollUnitUp()
  {
    if (currentView != null)
      currentView.scrollUnitUp();
  }
  
  /**
   * Scrolls the current view down by the current unit increment.
   */        
  public void scrollUnitDown()
  {
    if (currentView != null)
      currentView.scrollUnitDown();
  }
  
  /**
   * Scrolls the current view to the left by the current unit increment.
   */        
  public void scrollUnitLeft()
  {
    if (currentView != null)
      currentView.scrollUnitLeft();
  }
  
  /**
   * Scrolls the current view to the right by the current unit increment.
   */      
  public void scrollUnitRight()
  {
    if (currentView != null)
      currentView.scrollUnitRight();
  }
  
  /**
   * Scrolls the current view up by the current block increment.
   */
  public void scrollBlockUp()
  {
    if (currentView != null)
      currentView.scrollBlockUp();
  }
  
  /**
   * Scrolls the current view down by the current block increment.
   */        
  public void scrollBlockDown()
  {
    if (currentView != null)
      currentView.scrollBlockDown();
  }
  
  /**
   * Scrolls the current view to the left by the current block increment.
   */        
  public void scrollBlockLeft()
  {
    if (currentView != null)
      currentView.scrollBlockLeft();
  }
  
  /**
   * Scrolls the current view to the right by the current block increment.
   */    
  public void scrollBlockRight()
  {
    if (currentView != null)
      currentView.scrollBlockRight();
  }
  
}



class ViewEntryData {

  KbWorkspace wksp;
  boolean keepHistory;
  WorkspaceView view;

  ViewEntryData (KbWorkspace wksp, boolean keepHistory) {
    this.wksp = wksp;
    this.keepHistory = keepHistory;
  }

  @Override
  public String toString () {
    return "{wksp = " + wksp + ", keepUpdated = " + keepHistory + ", view = " + view + "}";
  }

}
