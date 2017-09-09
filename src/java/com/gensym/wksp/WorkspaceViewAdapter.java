package com.gensym.wksp;

import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.ntw.*;
import com.gensym.irm.*;
import com.gensym.draw.*;
import com.gensym.classes.Item;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2ItemDeletedException;
import java.util.*;
import java.awt.*;
import java.awt.event.*;
import com.gensym.classes.Connection;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Message;
import com.gensym.ntw.util.G2FontMap;
import javax.swing.*;


/**
 * WorkspaceViewAdapter
 *
 */

public class WorkspaceViewAdapter extends WorkspaceAdapter
implements FieldEditListener, KeyListener {

  KbWorkspace wksp;
  WorkspaceView view;
  private volatile Vector cachedEvents;
  private volatile boolean viewIsReceivingEvents;
  private String currentFieldEditValue;
  private Message message;
  private JTextField theEditBox;   //private TextField editBox;
  private WorkspaceElement messageView;
  private static final Symbol NEW_VALUE_ = Symbol.intern ("NEW-VALUE");
  private static final Symbol MESSAGE_ = Symbol.intern ("MESSAGE");
  //EXITs are from the EDITOR(buttons or keys)
  private static final Symbol CANCEL_EXIT_ = Symbol.intern ("CANCEL-EXIT");
  private static final Symbol END_EXIT_ = Symbol.intern ("END-EXIT");
  private static final Symbol TAB_EXIT_ = Symbol.intern ("TAB-EXIT");
  //ACTIONs are from the kb
  private static final Symbol CANCEL_ACTION_ = Symbol.intern ("CANCEL-ACTION");
  private static final Symbol END_ACTION_ = Symbol.intern ("END-ACTION");
  private Hashtable deletedItems = new Hashtable ();
  private static boolean inPlace = false;
  private static Frame fieldEditFrame = new Frame();
  private static final Symbol EDITOR_BLOCK_FONT_OVERRIDE_ = Symbol.intern ("EDITOR-BLOCK-FONT-OVERRIDE"),
    EDITOR_BACKGROUND_COLOR_OVERRIDE_ = Symbol.intern ("EDITOR-BACKGROUND-COLOR-OVERRIDE"),
    EDITOR_TEXT_COLOR_OVERRIDE_ = Symbol.intern ("EDITOR-TEXT-COLOR-OVERRIDE"),
    IN_PLACE_EDITING_ = Symbol.intern ("IN-PLACE-EDITING"),
    EDITOR_FONT_SIZE_OVERRIDE_ = Symbol.intern ("EDITOR-FONT-SIZE-OVERRIDE"),
    EDITOR_INITIAL_EDITOR_HEIGHT_OVERRIDE_ = Symbol.intern ("EDITOR-INITIAL-EDITOR-HEIGHT-OVERRIDE"),
    CLEAR_BEFORE_EDIT_ = Symbol.intern ("CLEAR-BEFORE-EDIT");
  // cannot-enter-for-some-unknown-reason, cannot-enter-because-restricted
  // cannot-enter-becasue-not-showing, cannot-enter-because-field-edit-in-progress

  WorkspaceViewAdapter(WorkspaceView view) {
    this.view = view;
    wksp = view.getWorkspace();
    // This synchronized is not technically necessary, but
    // expresses the data elements protected elsewhere
    // by this lock
    synchronized (decacheLock) {
      viewIsReceivingEvents = view.isReceivingEvents();
      if (!viewIsReceivingEvents)
	cachedEvents = new Vector();
    }
    try {
      TwAccess context
	= (TwAccess)((com.gensym.classes.ImplAccess)wksp).getContext(); //hack for now
      context.addFieldEditListener(this);
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
  }

  private static final Object decacheLock = new Object();

  public void decacheEvents() {
    //System.out.println("START DECACHING");
    //com.gensym.tests.Debug3Tier.add_data ("decacheEvents", this + ";" + Thread.currentThread());
    Vector events = null;
    int count = 0;

    while (!viewIsReceivingEvents) {
      count++;
      synchronized (decacheLock) {
	if (cachedEvents != null && !cachedEvents.isEmpty()) {
	  events = cachedEvents;
	  cachedEvents = new Vector();
	}
      }
      if (events != null) {
	Enumeration e = events.elements();
	//System.out.println("DECACHING: " + count + ";" + events.size());
	//com.gensym.tests.Debug3Tier.add_data ("decacheEvents2", count + ";" + events.size());
	while (e.hasMoreElements()) {
	  Object event = e.nextElement();
	  //com.gensym.tests.Debug3Tier.add_data ("decacheEvents3", event.hashCode() + ";" + count);
	  if (event instanceof WorkspaceEvent)
	    processWorkspaceEvent((WorkspaceEvent)event);
	  else
	    processFieldEditEvent((FieldEditEvent)event);
	}
      }
      synchronized (decacheLock) {
	//com.gensym.tests.Debug3Tier.add_data ("decacheEvents4", new Integer(count));
	if (cachedEvents == null || cachedEvents.isEmpty()) {
	  //com.gensym.tests.Debug3Tier.add_data ("decacheEvents5", new Integer(count));
	  viewIsReceivingEvents = true;
	  cachedEvents = null;
	}
      }
    }
    //com.gensym.tests.Debug3Tier.add_data ("decacheEvents6 STOP", new Integer(count));
    //System.out.println("STOP DECACHING");
  }

  /**
   * returns true if it acually cached or processed the event
   * itself
   */
  private boolean cacheEvent(EventObject event) {
    if (viewIsReceivingEvents) {
      //com.gensym.tests.Debug3Tier.add_data ("cacheEvents0 ", event.hashCode() + ";" + event);
      return false;
    } else {
      synchronized (decacheLock) {
	// check again inside the lock
	// NOTE: viewIsReceivingEvents can go from false to true,
	// but not in the other direction
	if (viewIsReceivingEvents) {
	  //com.gensym.tests.Debug3Tier.add_data ("cacheEvents1", new Integer(event.hashCode()));
	  return false;
	} else {
	  //com.gensym.tests.Debug3Tier.add_data ("cacheEvents2", new Integer(event.hashCode()));
	  cachedEvents.addElement(event);
	  return true;
	}
      }
    }
  }
  
  private void processWorkspaceEvent (WorkspaceEvent evt)
  {
    try {
    switch (evt.getID()) {
    case WorkspaceEvent.ITEM_INSERT: workspaceItemAddedImpl (evt); break;
    case WorkspaceEvent.ITEM_REMOVE: workspaceItemRemovedImpl (evt); break;
    case WorkspaceEvent.ITEM_MOVE: workspaceItemMovedImpl (evt); break;
    case WorkspaceEvent.ITEM_RESIZE: workspaceItemResizedImpl (evt); break;
    case WorkspaceEvent.ITEM_ROTATE: workspaceItemRotatedImpl (evt); break;
    case WorkspaceEvent.ITEM_COLOR_PATTERN_CHANGE: workspaceItemColorsChangedImpl (evt); break;
    case WorkspaceEvent.ITEM_ICON_VARIABLES_CHANGE: workspaceItemIconVariablesChangedImpl (evt); break;
    case WorkspaceEvent.ITEM_CHANGE: workspaceItemAttributesChangedImpl (evt); break;
      // fix this: why is this event not handled here?
    case WorkspaceEvent.WORKSPACE_RESIZED: workspaceResized (evt); break;
    }
    } catch (NullPointerException ex) {
      // If an event is processed for an item not on the workspace,
      // and we are still either caching or decaching events (as
      // opposed to processing them directly), then we just trace
      // the exception because it means that we are probably processing
      // and event that precedes the item list that the WorkspaceView
      // is using as its starting point, so the "out of order" event
      // has been taken care of by the state the WorkspaceView is using
      // for that item. Also, since viewIsReceivingEvents is a one-way
      // boolean, I am not bothering to synchronize
      if (!viewIsReceivingEvents)
	Trace.exception(ex);
      else
	throw ex;
    }
  }

  private void processFieldEditEvent(FieldEditEvent event) {
    switch (event.getID()) {
    case FieldEditEvent.CANCEL: cancelFieldEditImpl(event); break;
    case FieldEditEvent.CREATE: createFieldEditImpl(event); break;
    case FieldEditEvent.REFRESH: refreshFieldEditImpl(event); break;
    case FieldEditEvent.UPDATE: updateFieldEditImpl(event); break;
    case FieldEditEvent.END: endFieldEditImpl(event); break;
    }
  }
  
  private WorkspaceElement findElement(Item item) {
    WorkspaceElement elt = view.findElement(item);
    return (elt == null ? (WorkspaceElement)deletedItems.get (item) : elt);
  }

  @Override
  public void workspaceItemMoved(WorkspaceEvent event)
  {
    //com.gensym.tests.Debug3Tier.add_data ("moveElement1", event.getItem() + ";" + viewIsReceivingEvents + ";" + Thread.currentThread());
    if (!cacheEvent(event))
      workspaceItemMovedImpl(event);
  }

  private void workspaceItemMovedImpl(WorkspaceEvent event)
  {
    Item item = event.getItem();
    if (!item.isValid()) return;
    WorkspaceElement element = findElement(item);
    if (element == null) {
      //com.gensym.tests.Debug3Tier.add_data ("moveElement2", event.getItem() + ";" + viewIsReceivingEvents + ";" + Thread.currentThread());
      // 	System.err.println ("No element found for " + item + ". Raising exception to G2");
      // 	Thread.dumpStack ();
      // 	System.out.flush (); System.err.flush ();
    }
    element.handleWorkspaceItemMoved(event);
  }
    
  @Override
  public void workspaceItemResized(WorkspaceEvent event)
  {
    if (!cacheEvent(event))
      workspaceItemResizedImpl(event);
  }


  private void workspaceItemResizedImpl(WorkspaceEvent event) {
    Item item = event.getItem();
    if (!item.isValid()) return;
    WorkspaceElement element = findElement(item);
    if (element != null)
      element.handleWorkspaceItemResized(event);
    else if (item instanceof KbWorkspace) {
      Structure boundsStructure = event.getInfo();
      Rectangle newBounds = WorkspaceUtil.boundsStructureToBounds(boundsStructure);
      newBounds.y = -newBounds.y;
      Rectangle viewBounds = view.getViewBounds();
      int newRight = newBounds.x + newBounds.width,
	newBottom =  newBounds.y + newBounds.height;
      view.setScroll(newBounds.x, newBounds.y, newRight, newBottom);
      view.invalidate(new Rectangle[]{newBounds});
      if (newBounds.width < viewBounds.width || newBounds.height < viewBounds.height) {
	//Our current implementation is to change the document size to match the
	//G2 workspace size in those cases when G2 is getting smaller
	//(shrinkwrapping), and to add scrollbars if the G2 workspace size gets
	//larger.  This is a preference of rethink and escor.
	view.shrinkWrapDocument();
      }
      try {
	// if our "grandparent" is a JScrollPane, then we need to inform it of the size change
	if (view.getParent ().getParent () instanceof JScrollPane) {
	  JScrollPane scrollView =(JScrollPane)(view.getParent ().getParent ());
	  scrollView.revalidate();
	}
      } catch (Exception e) {
	Trace.exception (e);
      }
    }
  }

  @Override
  public void workspaceItemRotated(WorkspaceEvent event)
  {
    if (!cacheEvent(event))
      workspaceItemRotatedImpl(event);
  }

  private void workspaceItemRotatedImpl(WorkspaceEvent event) {
    Item item = event.getItem();
    if (!item.isValid()) return;
    WorkspaceElement element = findElement(item);
    if (element instanceof DeletedItemElement)
      return;
    ((WorkspaceIcon)element).handleWorkspaceItemRotated(event);
  }

  @Override
  public void workspaceItemColorsChanged(WorkspaceEvent event)
  {
    if (!cacheEvent(event))
      workspaceItemColorsChangedImpl(event);
  }

  private void workspaceItemColorsChangedImpl(WorkspaceEvent event) {
    Item item = event.getItem();
    if (!item.isValid()) return;
    WorkspaceElement element = findElement(item);
    if (element != null)
      element.handleWorkspaceItemColorsChanged(event);
    else if (item instanceof KbWorkspace) {
      view.handleColorsChanged(event);
    }
  }

  @Override
  public void workspaceItemIconVariablesChanged(WorkspaceEvent event)
  {
    if (!cacheEvent(event))
      workspaceItemIconVariablesChangedImpl(event);
  }

  private void  workspaceItemIconVariablesChangedImpl(WorkspaceEvent event) {
    Item item = event.getItem();
    if (!item.isValid()) return;
    WorkspaceElement element = findElement(item);
    if (element instanceof DeletedItemElement)
      return;
    ((WorkspaceIcon)element).handleWorkspaceItemIconVariablesChanged(event);
  }

  private final static Symbol attributeName_ = Symbol.intern("ATTRIBUTE-NAME");
  private final static Symbol tableRows_ = Symbol.intern("TABLE-ROWS");
  private final static Symbol TABLE_CELLS_ = Symbol.intern("TABLE-CELLS");
  private final static Symbol VALUE_TO_DISPLAY_ = Symbol.intern("VALUE-TO-DISPLAY");
  private final static Symbol BUTTON_STATUS_ = Symbol.intern("BUTTON-STATUS");
  private static final Symbol SLIDER_VALUE_ = Symbol.intern ("SLIDER-VALUE");
  private static final Symbol TYPE_IN_BOX_VALUE_ = Symbol.intern ("TYPE-IN-BOX-VALUE");
  private static final Symbol TYPE_IN_BOX_VARIABLE_OR_PARAMETER_
  = WorkspaceTypeInBox.TYPE_IN_BOX_VARIABLE_OR_PARAMETER_;
  private static final Symbol MANUALLY_DISABLEDQ_ = Symbol.intern ("MANUALLY-DISABLED?");
  @Override
  public void workspaceItemAttributesChanged(WorkspaceEvent event)
  {
    if (!cacheEvent(event))
      workspaceItemAttributesChangedImpl(event);
  }

  private void workspaceItemAttributesChangedImpl(WorkspaceEvent event) {
    Item item = event.getItem();
    if (!item.isValid()) return;
    Structure updateInfo = event.getInfo();
    WorkspaceElement element = findElement(item);
    if (updateInfo == null) {
      Trace.exception
	(new UnexpectedException
	 (new Exception("NULL UPDATE INFO IN VIEW ADAPTER ITEM CHANGE " +
			event + item)));
      return;
    }
    if (element instanceof DeletedItemElement)
      return;
    
    Symbol attributeName 
      = ((Symbol)updateInfo.getAttributeValue(attributeName_, null));
    if (tableRows_.equals(attributeName) ||
	TABLE_CELLS_.equals(attributeName)) {
      if (event.getInfo().getAttributeValue(WorkspaceElement.NEW_VALUE_, "*error*")
	  instanceof Sequence)
	((WorkspaceTable)element).handleTableCellsChanged(event);
      else
	((WorkspaceTable)element).handleTableCellChanged(event);
    } else if ((WorkspaceConnection.CONNECTION_STYLE_.equals(attributeName)) &&
	       (element instanceof WorkspaceConnection))
      ((WorkspaceConnection)element).handleConnectionStyleChanged(event);
    else if ((WorkspaceConnection.CONNECTION_IS_DIRECTED_.equals(attributeName))
	     &&(element instanceof WorkspaceConnection))
      ((WorkspaceConnection)element).handleConnectionIsDirectedChanged(event);
    else if ((VALUE_TO_DISPLAY_.equals(attributeName))&& (element instanceof WorkspaceDial))
      ((WorkspaceDial)element).handleValueToDisplayChanged(event);
    else if ((VALUE_TO_DISPLAY_.equals(attributeName))&& (element instanceof WorkspaceMeter))
      ((WorkspaceMeter)element).handleValueToDisplayChanged(event);
    else if ((BUTTON_STATUS_.equals(attributeName)) && (element instanceof WorkspaceRadioButton))
      ((WorkspaceRadioButton)element).handleButtonStatusChanged(event);
    else if ((BUTTON_STATUS_.equals(attributeName)) && (element instanceof WorkspaceCheckBox))
      ((WorkspaceCheckBox)element).handleButtonStatusChanged(event);
    else if ((SLIDER_VALUE_.equals(attributeName)) && (element instanceof WorkspaceSlider))
      ((WorkspaceSlider)element).handleSliderValueChanged(event);
    else if ((TYPE_IN_BOX_VALUE_.equals(attributeName)) &&
	     (element instanceof WorkspaceTypeInBox))
      ((WorkspaceTypeInBox)element).handleTypeInBoxValueChanged(event);
    else if ((TYPE_IN_BOX_VARIABLE_OR_PARAMETER_.equals(attributeName)) &&
	     (element instanceof WorkspaceTypeInBox))
      ((WorkspaceTypeInBox)element).handleTypeInBoxVariableOrParameterChanged(event);
    else if (((WorkspaceTextBox.TEXT_X_MAGNIFICATION_.equals(attributeName)) ||
	      (WorkspaceTextBox.TEXT_Y_MAGNIFICATION_.equals(attributeName)) ||
	      (WorkspaceTextBox.FORMAT_TYPE_.equals(attributeName)))  &&
	     (element instanceof WorkspaceTextBox))
      ((WorkspaceTextBox)element).handleWorkspaceItemFontChanged(event);
    else if (MANUALLY_DISABLEDQ_.equals(attributeName)) {
      if (element instanceof Component) {
	view.invalidateElement((Component)element);
      }
    }
  }

  private static final Symbol POSITION_OR_NEXT_LOWER_ITEM_
  = Symbol.intern ("POSITION-OR-NEXT-LOWER-ITEM");
  private static final Symbol TOP_ = Symbol.intern ("TOP");
  @Override
  public void workspaceItemAdded (WorkspaceEvent event) {
    //System.out.println ("workspaceItemAdded (" + event + ")");
    //com.gensym.tests.Debug3Tier.add_data ("addElement1", event.hashCode() + ";" + viewIsReceivingEvents + ";" + Thread.currentThread());
    if (!cacheEvent(event))
      workspaceItemAddedImpl(event);
  }

  private void workspaceItemAddedImpl (WorkspaceEvent event) {
    //com.gensym.tests.Debug3Tier.add_data ("addElementImpl1", event.hashCode() + ";" + viewIsReceivingEvents + ";" + Thread.currentThread());
    Item item = event.getItem();
    //if (!item.isValid()) return;
    Structure extraInfo = event.getInfo();
    WorkspaceElement element = findElement(item);
    if (element == null) {
      try {
	WorkspaceElement newElement = view.createElement(item);
	Object positionOrNextLowerItem
	  = extraInfo.getAttributeValue(POSITION_OR_NEXT_LOWER_ITEM_, null);
	int elementPosition = 0;
	if (positionOrNextLowerItem == null) {
	  //System.out.println ("WVA: position = null");
	  if (item instanceof Connection && item.isValid ()) {
	    //System.out.println ("WVA: Special case of Xn");
	    Sequence connectionIO = ((Connection)item).getConnectionInputAndOutput();
	    Object inputObject = connectionIO.elementAt(0);
	    //System.out.println ("WVA: Terminals = " + connectionIO + " Next lower = " + inputObject);
	    if (inputObject instanceof Item) {
	      Component nextLowerItem = (Component) findElement((Item)inputObject);
	      //System.out.println ("WVA: lowerElement = " + nextLowerItem);
	      elementPosition = view.getElementPosition(nextLowerItem);
	      //System.out.println ("WVA: Position = " + elementPosition);
	      //view.dumpItems ();
	    }
	  }	      
	} else if (positionOrNextLowerItem instanceof Symbol)
	  elementPosition = -1 ; // add at end/bottom
	else {
	  Component nextLowerItem = (Component) findElement((Item)positionOrNextLowerItem);
	  elementPosition = view.getElementPosition(nextLowerItem);
	}
	//System.out.println ("Adding " + newElement + " for " + item + " over " + positionOrNextLowerItem + " at location = " + elementPosition);
	view.addElement(newElement, elementPosition);
	//System.out.println ("Added " + view.findElement (item) + " for " + item); System.out.flush ();
	view.removeItemPendingSelection (item);
      } catch (G2ItemDeletedException g2ide) {
	deletedItems.put (item, new DeletedItemElement (item));
	//System.out.println ("YOOOOHOOO! Made " + deletedItems.get (item) +  " for " + item); System.out.flush ();
      } catch (G2AccessException g2ae) {
	Trace.exception(g2ae);
	NtwNotification error
	  = new NtwNotification(NtwNotification.EXCEPTION, g2ae,
				"ERROR creating WorkspaceElement for " + item +
				" in WorkspaceViewAdapter.\n");
	Trace.exception(g2ae);
	error.send();
      }
    } else {
      //com.gensym.tests.Debug3Tier.add_data ("addElement2", event.hashCode() + ";" + viewIsReceivingEvents + ";" + Thread.currentThread());
      Trace.exception(new Exception("Can not add element because " +
				    element +
				    " already exists.\n"));
    }
  }

  @Override
  public void workspaceItemRemoved (WorkspaceEvent event) {
    //com.gensym.tests.Debug3Tier.add_data ("removeElement1", event.getItem() + ";" + viewIsReceivingEvents + ";" + Thread.currentThread());
    if (!cacheEvent(event))
      workspaceItemRemovedImpl(event);
  }

  private void workspaceItemRemovedImpl (WorkspaceEvent event) {
    Item item = event.getItem();
    //if (!item.isValid()) return;
    Structure extraInfo = event.getInfo();
    WorkspaceElement element = findElement(item);
    if (element != null)
      view.checkClipboard (element);
    if (element instanceof DeletedItemElement){
      //System.out.println ("Removing " + deletedItems.remove (item) + " for " + item);
      view.removeElement (element);
    } else if (element != null) {
      view.removeElement(element);
      try {
	element.dispose ();
      } catch (G2AccessException g2ae) {
	Trace.exception (g2ae);
      }
    } else {
      // This is because of a bug in Workspace protocol that sends duplicate notifications
      if (!(item instanceof com.gensym.classes.Connection))
	Trace.exception(new Exception("Can not remove non existent element for " + item));
    }
  }

  @Override
  public void receivedInitialDownload(WorkspaceEvent event) {
  }

  public void dispose()
  {
    try {
      TwAccess context
	= (TwAccess)((com.gensym.classes.ImplAccess)wksp).getContext(); //hack for now
      context.removeFieldEditListener(this);
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
  }


  //FIELD EDIT STUFF

  private void killFieldEdit()
  {
    JTextField editBox = theEditBox;
    if (editBox != null) {
      editBox.removeKeyListener(this);
      if (!inPlace) {
	fieldEditFrame.remove(editBox);
	fieldEditFrame.setVisible(false);
      } else 
	view.removeElement(editBox);
      inPlace = false;
      theEditBox = null;
      message = null;
      messageView = null;
    }
  }

  private void update(TwAccess context)
       throws G2AccessException
  {
    JTextField editBox = theEditBox;
    if (editBox == null) {
      //System.out.println("NULL EB");
      return;
    }
    currentFieldEditValue = editBox.getText();
    context.updateFieldEdit(currentFieldEditValue);
  }
  
  private void update()
  {
    try {
      KbWorkspace workspace = view.getWorkspace();
      TwAccess context
	= (TwAccess)((com.gensym.classes.ImplAccess)workspace).getContext(); //hack for now
      update(context);
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
  }
  
  private void end(Symbol status, boolean doUpdate) {
    KbWorkspace workspace = view.getWorkspace();
    try {
      TwAccess context
	= (TwAccess)((com.gensym.classes.ImplAccess)workspace).getContext(); //hack for now
      if (doUpdate)
	update(context);
      context.finishFieldEditAndRecordStatus(status);
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
    killFieldEdit();
  }

  class FocusedJTextField extends JTextField {
    @Override
    public boolean isManagingFocus() {
      return true;
    }
    @Override
    public void repaint(long tm, int x, int y, int width, int height)
    {
      if (inPlace) {
	if (view != null)
	  view.invalidateElement(FocusedJTextField.this);
	else {
	  //System.out.println ("BOO BOO"); System.out.flush ();
	}
      } else
	super.repaint(tm,x,y,width,height);
    }
    
  };
  class FocusedJPasswordField extends JPasswordField {
    @Override
    public boolean isManagingFocus() {
      return true;
    }
    @Override
    public void repaint(long tm, int x, int y, int width, int height)
    {
      if (inPlace)
	if (view != null)
	  view.invalidateElement(this);
	else {
	  //System.out.println ("BOO BOO"); System.out.flush ();
	}
      else
	super.repaint(tm,x,y,width,height);
    }
  };

  @Override
  public void createFieldEdit(FieldEditEvent event)
  {
    if (!cacheEvent(event))
      createFieldEditImpl(event);
  }

  private void createFieldEditImpl(FieldEditEvent event) {
    if (event.getWorkspace() != view.getWorkspace()) return;
    Structure particulars = event.getParticulars();
    message = (Message)particulars.getAttributeValue(MESSAGE_, null);
    Object blockFontOverride
      = particulars.getAttributeValue(EDITOR_BLOCK_FONT_OVERRIDE_, null);
    Object backgroundColorOverride
      = particulars.getAttributeValue(EDITOR_BACKGROUND_COLOR_OVERRIDE_, null);
    Object textColorOverride
      = particulars.getAttributeValue(EDITOR_TEXT_COLOR_OVERRIDE_, null);
    Object inPlaceEditing
      = particulars.getAttributeValue(IN_PLACE_EDITING_, null);
    Object fontSizeOverride
      = particulars.getAttributeValue(EDITOR_FONT_SIZE_OVERRIDE_, null);
    Object initialHeightOverride
      = particulars.getAttributeValue(EDITOR_INITIAL_EDITOR_HEIGHT_OVERRIDE_, null);
    Object clearBeforeEdit
      = particulars.getAttributeValue(CLEAR_BEFORE_EDIT_, null);
    
    boolean blockFont = false;
    if (blockFontOverride != null) 
      blockFont = true;
    
    if (blockFont) {
      theEditBox = new FocusedJPasswordField();
      ((JPasswordField)theEditBox).setEchoChar((char)10046);
    } else 
      theEditBox = new FocusedJTextField();
    
    JTextField editBox = theEditBox;
    if (backgroundColorOverride != null)
      theEditBox.setBackground(view.getColorTable().lookup(backgroundColorOverride));
    if (textColorOverride != null)
      theEditBox.setForeground(view.getColorTable().lookup(textColorOverride));
    
    try {
      currentFieldEditValue = message.getText();
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
      currentFieldEditValue = "---";
    }
    
    if (clearBeforeEdit == null) editBox.setText(currentFieldEditValue);
    
    editBox.addKeyListener(this);
    messageView = view.findElement(message);
    if (messageView instanceof DeletedItemElement)
      return;
    
    Font theFont;
    if (blockFont)
      theFont = G2FontMap.get(G2FontMap.LARGE_);
    else if (fontSizeOverride == null) 
      theFont = ((WorkspaceTextBoxImpl)messageView).getTextCell().getFont();
    else 
      theFont = com.gensym.ntw.util.G2FontMap.get((Symbol)fontSizeOverride);
    
    Rectangle bnds = ((Component)messageView).getBounds();
    editBox.setFont(theFont);
    if (initialHeightOverride != null)
      bnds.height = ((Integer)initialHeightOverride).intValue();
    editBox.setBounds(bnds);
    editBox.setEditable(true);
    
    if (inPlaceEditing != null) 
      inPlace = true;
    if (inPlace)
      view.addElement(editBox);
    else {
      fieldEditFrame.add(editBox);	
      Dimension size = editBox.getSize();
      int titleBarHeight = fieldEditFrame.getInsets().top;
      size.height+=titleBarHeight;
      fieldEditFrame.setSize(size);
      fieldEditFrame.setLocation(0,0);
      fieldEditFrame.setVisible(true);
    }
    editBox.requestFocus();
  }

  @Override
  public void cancelFieldEdit(FieldEditEvent event)
  {
    if (!cacheEvent(event))
      cancelFieldEditImpl(event);
  }

  private void cancelFieldEditImpl(FieldEditEvent event) {
    if (event.getWorkspace() != view.getWorkspace()) return;
    end(CANCEL_ACTION_, false);
  }

  @Override
  public void refreshFieldEdit(FieldEditEvent event)
  {
    if (!cacheEvent(event))
      refreshFieldEditImpl(event);
  }

  private void refreshFieldEditImpl(FieldEditEvent event) {
    if (event.getWorkspace() != view.getWorkspace()) return;
    currentFieldEditValue
      = (String)event.getParticulars().getAttributeValue(NEW_VALUE_,
							 currentFieldEditValue);
    JTextField editBox = theEditBox;
    if (editBox != null) {
      editBox.setText(currentFieldEditValue);
      view.invalidateElement(editBox);
    }
  }
  
  @Override
  public void updateFieldEdit(FieldEditEvent event)
  {
    if (!cacheEvent(event))
      updateFieldEditImpl(event);
  }

  private void updateFieldEditImpl(FieldEditEvent event) {
    if (event.getWorkspace() != view.getWorkspace()) return;    
    update();
  }
  
  @Override
  public void endFieldEdit(FieldEditEvent event)
  {
    if (!cacheEvent(event))
      endFieldEditImpl(event);
  }

  private void endFieldEditImpl(FieldEditEvent event) {
    if (event.getWorkspace() != view.getWorkspace()) return;    
    end(END_ACTION_, true);
  }
  
  @Override
  public void keyPressed(KeyEvent e)
  {
    JTextField editBox = theEditBox;
    if (editBox == null)
      return;
    //view.invalidateElement(editBox);
    char key = e.getKeyChar();
    switch (e.getKeyCode()) {
    case KeyEvent.VK_TAB:
      end(TAB_EXIT_, true); break;
    case KeyEvent.VK_ENTER:
    case KeyEvent.VK_ACCEPT:
      end(END_EXIT_, true); break;
    case KeyEvent.VK_CANCEL:
    case KeyEvent.VK_ESCAPE:
      end(CANCEL_EXIT_, false); break;
    case KeyEvent.VK_A:
      if (e.isControlDown())
	end(CANCEL_EXIT_, false); break;
    }
    
  }
  
  @Override
  public void keyTyped(KeyEvent e)
  {
    //System.out.println("E" +e);
    JTextField editBox = theEditBox;
    if (editBox != null)
      view.invalidateElement(editBox);
  }
  @Override
  public void keyReleased(KeyEvent e)
  {
    //System.out.println("E" +e);
    //view.invalidateElement(editBox);
  }

  @Override
  public KbWorkspace getWorkspace() {
    return view.getWorkspace();
  }
}
