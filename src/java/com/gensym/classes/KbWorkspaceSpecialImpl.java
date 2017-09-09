
package com.gensym.classes;

import java.util.Vector;

import com.gensym.core.GensymApplication;
import com.gensym.jgi.*;
import com.gensym.util.*;
import com.gensym.message.*;
import java.util.Enumeration;
import com.gensym.util.symbol.G2ClassSymbols;

public class KbWorkspaceSpecialImpl extends ItemImpl {

  /**
   * Standard Tracing Requirements
   * @undocumented
   */
  public static boolean traceOn = false;
  private static MessageKey traceKey =
  Trace.registerMessageKey ("com.gensym.util.classes",
			    KbWorkspaceImpl.class);
  private static Resource i18nTrace =
  Trace.getBundle("com.gensym.classes.TraceMessages");
  private static Resource i18n = Resource.getBundle("com.gensym.classes.Messages");

  private static final Symbol WORKSPACE_INITIAL_DATA_  = Symbol.intern ("WORKSPACE-INITIAL-DATA"),
                              SUBSCRIPTION_HANDLE_     = Symbol.intern ("SUBSCRIPTION-HANDLE"),
                              TW_WORKSPACE_ITEM_PROXY_ = Symbol.intern ("TW-WORKSPACE-ITEM-PROXY"),
                              ITEM_INFO_LIST_          = Symbol.intern ("ITEM-INFO-LIST"),
    ITEM_DATA_LIST_ = Symbol.intern("ITEM-DATA-LIST"),
    G2_SHOW_WORKSPACE_ = Symbol.intern ("G2-SHOW-WORKSPACE"),
    G2_HIDE_WORKSPACE_ = Symbol.intern ("G2-HIDE-WORKSPACE");

  private static final Symbol INITIAL_DOWNLOAD_ = Symbol.intern ("INITIAL-DOWNLOAD");

  private static final Symbol POSITION_OR_NEXT_LOWER_ITEM_
  = Symbol.intern ("POSITION-OR-NEXT-LOWER-ITEM");
  private static final Symbol WORKSPACE_BACKGROUND_COLOR_ = Symbol.intern ("WORKSPACE-BACKGROUND-COLOR");
  private static final Symbol WORKSPACE_DIMENSIONS_ = Symbol.intern ("WORKSPACE-DIMENSIONS");
  private static final Symbol WORKSPACE_FOREGROUND_COLOR_ = Symbol.intern ("WORKSPACE-FOREGROUND-COLOR");

  private static final Symbol G2_GET_UPDATED_WORKSPACE_INFORMATION_ = Symbol.intern ("G2-GET-UPDATED-WORKSPACE-INFORMATION");
  /** Workspaces need data not captured by ItemData */
  @Override
  protected ItemData makeDataForItem() {
    return new WorkspaceData();
  }

  /**
   * @undocumented Called from ntw.TwGateway, ntw.rmi.TwRMIClientImpl, wksp.WorkspaceViewAdapter
   */
  public void processWorkspaceEvent (WorkspaceEvent evt) {
   WorkspaceListener workspaceListener = null;
   WorkspaceData wsData = (WorkspaceData)data;
    
   if (wsData == null)
     return;

   synchronized(wsData) {
     workspaceListener = wsData.workspaceListener;
     // If the RunMethodThread gets behind it is very possible
     // that events could come through after the last workspaceListener
     // has been removed. This checks for that situation.
     if (!isValid() || workspaceListener == null)
       return;
   }
    
        Symbol notfnCode = evt.getNotificationCode ();
        Item changedItem = evt.getItem ();
	
        if (changedItem == null)
          System.out.println ("Got WorkspaceEvent with null item -> " + evt);
        else if (!changedItem.isValid()) {
	  boolean actuallyRemoved = false;
	  synchronized (wsData) {
	    actuallyRemoved = wsData.items.removeElement(changedItem);
	  }
	  if (actuallyRemoved) {
// 	    com.gensym.util.Debug3Tier.add_data ("remove", changedItem);
	    wsData.workspaceListener.workspaceItemRemoved (evt);
	  }
	  return;
	}
	else
          ((G2__BaseImpl)changedItem).updateItemForWorkspaceEvent (evt);
        int id = evt.getID ();
    
        Trace.send(30, traceKey, i18nTrace,
    	       "kbwiprocessWorkspaceEvent", notfnCode, changedItem,
    	       wsData.workspaceListener);
    
        switch (id)
          {
          case WorkspaceEvent.ITEM_INSERT:
    	workspaceItemAdded(changedItem, wsData, evt);
    	wsData.workspaceListener.workspaceItemAdded (evt);
    	break;
          case WorkspaceEvent.ITEM_REMOVE:
	    synchronized (wsData) {
	      wsData.items.removeElement(changedItem);
	    }
// 	    com.gensym.util.Debug3Tier.add_data ("remove2", changedItem);
    	wsData.workspaceListener.workspaceItemRemoved (evt);
    	break;
          case WorkspaceEvent.ITEM_MOVE: wsData.workspaceListener.workspaceItemMoved (evt); break;
          case WorkspaceEvent.ITEM_RESIZE: wsData.workspaceListener.workspaceItemResized (evt); break;
          case WorkspaceEvent.ITEM_ROTATE: wsData.workspaceListener.workspaceItemRotated (evt); break;
          case WorkspaceEvent.ITEM_COLOR_PATTERN_CHANGE: wsData.workspaceListener.workspaceItemColorsChanged (evt); break;
          case WorkspaceEvent.ITEM_ICON_VARIABLES_CHANGE: wsData.workspaceListener.workspaceItemIconVariablesChanged (evt); break;
          case WorkspaceEvent.ITEM_CHANGE: wsData.workspaceListener.workspaceItemAttributesChanged (evt); break;
          case WorkspaceEvent.WORKSPACE_RESIZED: wsData.workspaceListener.workspaceResized (evt); break;
	  case WorkspaceEvent.ITEM_LAYER_CHANGE:
	  handleItemLayerChange(evt); break;
          }      
  }

  /**
   * @undocumented
   */
  public static final Symbol ITEM_REMOVE_ = Symbol.intern ("ITEM-REMOVE");
  /**
   * @undocumented
   */
  public static final Symbol ITEM_INSERT_ = Symbol.intern ("ITEM-INSERT");
  private void handleItemLayerChange(WorkspaceEvent event) {
    try {
      java.lang.Object source = event.getSource();
      Item item = event.getItem();
      Structure info = event.getInfo();
      java.lang.Object positionOrNextLowerItem =
	info.getAttributeValue(POSITION_OR_NEXT_LOWER_ITEM_, null);
      Structure initialInfo = ((G2__BaseImpl)item).getInitialInfo();
      initialInfo.setAttributeValue(POSITION_OR_NEXT_LOWER_ITEM_, positionOrNextLowerItem);
      processWorkspaceEvent(new WorkspaceEvent(source, ITEM_REMOVE_, item, null));
      processWorkspaceEvent(new WorkspaceEvent(source, ITEM_INSERT_, item,
					       initialInfo));
    } catch (G2AccessException g2ae) {
      throw new UnexpectedException(g2ae);
    }
  }
    
  /**
   * Register for notification of changes to Items on the kb-workspace.
   * This information is typically necessary to render a view of the
   * kb-workspace.
   * @exception G2AccessException If an error occurs during
   * communication with G2.
   */
  public void addWorkspaceListener (WorkspaceListener wl) 
  throws G2AccessException {
    WorkspaceData wsData = (WorkspaceData)data;
    synchronized(wsData) {
      Structure initialInfo;
      if (wsData.subscribedToWksp) {
	initialInfo = makeWorkspaceSnapshot();
      } else {
	try {
	  initialInfo = representWorkspace();
	} catch (NoSuchAttributeException nsae) {
	  throw new CorruptionException(nsae);
	}
      }
      
      wsData.workspaceListener =
	EventMulticaster.add (wsData.workspaceListener, wl);
      wl.receivedInitialDownload(new WorkspaceEvent(this,
						    INITIAL_DOWNLOAD_,
						    this,
						    initialInfo));
    }
    decacheEvents(context, wsData.activeSubscriptionIndex);
  }

  /**
   * @undocumented
   */
  public Structure addWorkspaceListenerRetrievingState(WorkspaceListener wl)
  throws G2AccessException {
    refreshItemDataForWorkspace(null, wl);
    synchronized(data) {
      addWorkspaceListener(wl);
      return makeWorkspaceSnapshot();
    }
  }

  /**
   * @undocumented
   * @deprecated
   */
  public int getG2WkspSubscriptionHandle() {
    return ((WorkspaceData)data).activeSubscriptionIndex;
  }

  /**
   * Deregister for notification regarding changes on the kb-workspace
   * @exception G2AccessException If an error occurs during
   * communication with G2.
   */
  public void removeWorkspaceListener (WorkspaceListener wl) throws G2AccessException {
    WorkspaceData wsData = (WorkspaceData)data;
    synchronized(data) {
      wsData.workspaceListener =
	EventMulticaster.remove (wsData.workspaceListener, wl);
      
      if (wsData.workspaceListener == null && wsData.subscribedToWksp) {
	unrepresentWorkspace(context,wsData.activeSubscriptionIndex);
	wsData.subscribedToWksp = false;
	setWorkspaceUpdates (false);
      }
    }
  }

  // Algorithm similar to workspaceItemAdded in WorkspaceViewAdaptor
  /** Puts <code>element</code> into the correct position in
   * <code>elements</code> according to the information provided by
   * <code>positionInfo</code>.
   */
  private void workspaceItemAdded(Item item, WorkspaceData wsData,
				  WorkspaceEvent event) {
    if (item instanceof G2__BaseImpl)
      ((G2__BaseImpl)item).data.parentWorkspace = this;
    Sequence items = wsData.items;
    synchronized (wsData) {
      if (items.contains (item))
        return;
    }
    Structure extraInfo = event.getInfo();
    java.lang.Object positionInfo
      = extraInfo.getAttributeValue(POSITION_OR_NEXT_LOWER_ITEM_, null);

    if (item.equals(positionInfo)) {
      positionInfo = null;
      extraInfo.deleteAttribute(POSITION_OR_NEXT_LOWER_ITEM_);
    }
    
    synchronized (wsData) {
      if (positionInfo == null) {
	if (item instanceof Connection && item.isValid ()) {
	  try {
	    Sequence connectionIO = ((Connection)item).getConnectionInputAndOutput();
	    java.lang.Object inputObject = connectionIO.elementAt(0);
	    if (inputObject instanceof Item)
	      positionInfo = inputObject;
	  } catch(G2AccessException g2ae) {
	    Trace.exception(g2ae);
	  }
	}
      }
      if (positionInfo == null) {
	items.addElement(item);
      } else if (positionInfo instanceof Symbol) {
	items.insertElementAt(item, 0);
      } else {
	int nextLowerItemPosition =
	  items.lastIndexOf(positionInfo);
	if (nextLowerItemPosition > -1) {
	  items.insertElementAt(item, nextLowerItemPosition + 1);
	} else {
	  items.addElement(item);
	  Trace.exception(new IllegalArgumentException
			  (i18n.format("kbwiPositionElementNotFound",
				       new java.lang.Object [] {item, this, positionInfo})));
	}
      }
    }
  }    

  /**
   * @undocumented Returns the items on the workspace
   * if it is subscribed to. Returns null otherwise.
   */
  public Item[] getItems () {
    synchronized (data) {
      Sequence items = ((WorkspaceData)data).items;
      if (items == null)
	return null;
      Item[] array = new Item[items.size()];
      items.copyInto(array);
      return array;
    }
  }

  private static final Symbol PROPRIETARY_PACKAGE_ = Symbol.intern ("PROPRIETARY-PACKAGE");
  private static final Symbol G2_GET_TEXT_OF_ATTRIBUTE_ = Symbol.intern ("G2-GET-TEXT-OF-ATTRIBUTE");
  /**
   * @undocumented
   * Determines if this kb-workspace has any restrictions placed on
   * it. Returns TRUE if found, FALSE if it is definitely not
   * proprietary, null, if there is not declaration.
   * @see com.gensym.classes.ItemImpl#isProprietary
   */

  /**
   * @undocumented
   */
  public boolean workspaceIsProprietary (Sequence containers, int index) throws G2AccessException {
    boolean wkspIsProprietary = false;
    ItemData principalData = getPrincipalData();
    if (principalData.itemIsProprietaryThroughContainment != null)
      return principalData.itemIsProprietaryThroughContainment.booleanValue ();
    
    if (containers == null)
      containers = getContainmentHierarchy();
    java.lang.Object[] rpcArgs = new java.lang.Object[] {this, PROPRIETARY_PACKAGE_, Boolean.FALSE};
    java.lang.Object y = context.callRPC (G2_GET_TEXT_OF_ATTRIBUTE_, rpcArgs);
    String propPackage = (String)y;
    if (propPackage.equals ("none")) {
      if (containers.size () > index + 2) {
	KbWorkspace nextWksp = (KbWorkspace) containers.elementAt (index + 2);
	wkspIsProprietary = nextWksp.workspaceIsProprietary (containers, index + 2);
      }
    } else if (propPackage.equals ("not proprietary"))
      wkspIsProprietary = false; //redundant but more readable
    else {
      wkspIsProprietary = true;
    }
    
    if (wkspIsProprietary)
      getPrincipalData().itemIsProprietaryThroughContainment = Boolean.TRUE;
    else
      getPrincipalData().itemIsProprietaryThroughContainment = Boolean.FALSE;
    
    return wkspIsProprietary;
  }

  private static void decacheEvents(G2Access context,
				    Integer activeSubscriptionIndex)
       throws G2AccessException
  {
    invokeTwAccessMethod(context, "decacheEvents",
			 new Class[]{Integer.class},
			 new java.lang.Object[]{activeSubscriptionIndex});
  }
       
  private static Structure representWorkspace(G2Access context,
					      KbWorkspace workspace)
       throws G2AccessException
  {
    return (Structure)invokeTwAccessMethod(context, "representWorkspace",
					   new Class[]{KbWorkspace.class},
					   new java.lang.Object[]{workspace});
  }

  private void unrepresentWorkspace (G2Access context,
				     int activeSubscriptionIndex)
       throws G2AccessException
  {
    invokeTwAccessMethod(context, "unrepresentWorkspace",
			 new Class[]{Integer.TYPE},
			 new java.lang.Object[]{activeSubscriptionIndex});
    WorkspaceData wsData = (WorkspaceData)data;
    wsData.containmentHierarchyItemConfigurationSnapshot = null;
    for(Enumeration en = wsData.items.elements(); en.hasMoreElements();) {
      Item itm = (Item) en.nextElement();
      setWorkspaceUpdatesForItem (false, (G2__BaseImpl)itm);
    }
    // let go of the items so they can be reclaimed; don't do this as null
    // for fear of null pointer exceptions.
    wsData.items = new Sequence(0);
  }

 
  /**
   * Temporary measure to compensate for the lack of updates
   * (via the workapce protocol) for such things
   * as the ITEM-CONFIGURATIONS and CONNECTION-STYLES.
   * Only does something if there is an existing subscription.
   * The WorkspaceListener argument is for the support of three
   * tier connections: the TwRMIServerImpl has no UiClientSession
   * object of its own, and must use the one from the
   * TwServerQueueManager (which will be the WorkspaceListener
   * in that case). In the two-tier case, retrieveSession ignores
   * its argument.
   * @undocumented
   */
  public void refreshItemDataForWorkspace(Sequence attrsToRefresh, WorkspaceListener wl) throws G2AccessException {
    if (!((WorkspaceData)data).subscribedToWksp) {
      return;
    }
    
    UiClientSession session =
      (UiClientSession)invokeTwAccessMethod(context, "retrieveSession",
     					    new Class[]{java.lang.Object.class},
     					    new java.lang.Object[]{wl});
    if (session == null)
      throw new G2AccessException(i18n.getString("notLoggedIn"));
    
    Structure initialData =
      (Structure)context.callRPC(G2_GET_UPDATED_WORKSPACE_INFORMATION_,
 				 new java.lang.Object[] {session, this, attrsToRefresh});
    
    Sequence items =
      (Sequence)initialData.getAttributeValue(ITEM_INFO_LIST_, null);
    Sequence itemDatas =
      (Sequence)initialData.getAttributeValue(ITEM_DATA_LIST_, null);
    //System.out.println("representWorkspace " + items + ";" + itemDatas);
    updateBounds(initialData);
    int count = items.size();
    for (int i=0;i<count;i++) {
      G2__BaseImpl itm = (G2__BaseImpl)items.elementAt(i);
      itm.refreshWsInfo(this, (Structure)itemDatas.elementAt(i));
    }
  }

  private static final Symbol LEFT_ = Symbol.intern ("LEFT"),
   TOP_ = Symbol.intern ("TOP"),
   RIGHT_ = Symbol.intern ("RIGHT"),
   BOTTOM_ = Symbol.intern ("BOTTOM");
  
  private void updateBounds(Structure initialData) {
    java.lang.Object temporary = initialData.getAttributeValue(WORKSPACE_DIMENSIONS_, null);

    Integer width = null;
    Integer height = null;
    Integer centerX = null;
    Integer centerY = null;
    if (temporary != null) {
      try {
	if (temporary instanceof Structure) {
	  Structure dimensions = (Structure)temporary;
	  Integer left = (Integer)dimensions.getAttributeValue(LEFT_);
	  Integer top = (Integer)dimensions.getAttributeValue(TOP_);
	  Integer right = (Integer)dimensions.getAttributeValue(RIGHT_);
	  Integer bottom = (Integer)dimensions.getAttributeValue(BOTTOM_);
	  width = right - left;
	  height = bottom - top;
	  centerX = left + width/2;
	  centerY = -(top + height/2);       
	} else if (temporary instanceof java.awt.Rectangle) {
	  /* if we are in the third tier, then the bounds have already been
	     set and will be returned as a java.awt.Rectangle, and so we need
	     to handle that case.  We invert the algorithm used by
	     ItemImpl.getBounds in order to choose our center points. */
	  java.awt.Rectangle dimensions = (java.awt.Rectangle)temporary;
	  width = dimensions.width;
	  height = dimensions.height;
	  centerX = dimensions.x + width/2;
	  centerY = dimensions.y - height/2;
	}
	synchronized (data) {
	  data.attributes.setAttributeValue(ITEM_X_POSITION_, centerX);
	  data.attributes.setAttributeValue(ITEM_Y_POSITION_, centerY);
	  data.attributes.setAttributeValue(ITEM_WIDTH_, width);
	  data.attributes.setAttributeValue(ITEM_HEIGHT_, height);                  
	}
      } catch (NoSuchAttributeException nsae) {
	Trace.exception(nsae);
      }
    }

  }

  private Structure representWorkspace() throws G2AccessException,
  NoSuchAttributeException{
    
    WorkspaceData wsData = (WorkspaceData)data;
    synchronized (wsData) {
      wsData.containmentHierarchyItemConfigurationSnapshot = null;
      Structure initialInfo = representWorkspace(context,(KbWorkspace)this);
      Structure initialData =
    	(Structure)initialInfo.getAttributeValue(WORKSPACE_INITIAL_DATA_);
      setWorkspaceUpdates (true);
      wsData.subscribedToWksp = true;
      Integer subscriptionHandle =
    	((Integer)initialInfo.getAttributeValue (SUBSCRIPTION_HANDLE_, null));
      wsData.activeSubscriptionIndex = subscriptionHandle.intValue ();
      Sequence items =
	(Sequence)initialData.getAttributeValue(ITEM_INFO_LIST_, null);
      Sequence itemDatas =
	(Sequence)initialData.getAttributeValue(ITEM_DATA_LIST_, null);
      updateBounds(initialData);      
      //System.out.println("representWorkspace " + items + ";" + itemDatas);
      int count = items.size();
      for (int i=0;i<count;i++) {
	Item itm = (Item)items.elementAt(i);
	((G2__BaseImpl)itm).data.parentWorkspace = this;
	if (itemDatas != null) {
	  Structure info = (Structure)itemDatas.elementAt(i);
	  ((G2__BaseImpl)itm).setInitialInfo(info);
	}
	if (itm != null) {
	  setWorkspaceUpdatesForItem (true, (G2__BaseImpl)itm);
	} else {
	  throw new UnexpectedException(null, "null item");
	}
      }
      wsData.items = items;
      return initialInfo;
    }
  }

  /**
   * @undocumented.
   */
  private Structure makeWorkspaceSnapshot() throws G2AccessException {
    Structure wkspInitialData = new Structure();
    Structure returnValue = new Structure();
    WorkspaceData wsData = (WorkspaceData)data;
    synchronized (wsData) {
      wkspInitialData.setAttributeValue(ITEM_INFO_LIST_,
					((wsData).items).clone());
      wkspInitialData.setAttributeValue(ITEM_DATA_LIST_,
					makeItemDataList());
      wkspInitialData.setAttributeValue(WORKSPACE_DIMENSIONS_,
					getBounds());
      wkspInitialData.setAttributeValue(WORKSPACE_BACKGROUND_COLOR_,
 					getBackgroundColor());
      wkspInitialData.setAttributeValue(WORKSPACE_FOREGROUND_COLOR_,
 					getForegroundColor());
      returnValue.setAttributeValue(SUBSCRIPTION_HANDLE_, wsData.activeSubscriptionIndex);
      returnValue.setAttributeValue(WORKSPACE_INITIAL_DATA_,
				    wkspInitialData);
      return returnValue;
    }
  }

  private Sequence makeItemDataList() throws G2AccessException{
    Sequence items = ((WorkspaceData)data).items;
    int count = items.size();
    if (count == 0)
      return null;
    
    Sequence itemDataList = new Sequence();
    for (int i = 0; i < count; i++) {
      Structure info = ((G2__BaseImpl)items.elementAt(i)).getInitialInfo();
      itemDataList.addElement(info);
    }
    return itemDataList;
  }

  private static final Symbol garbageMode = Symbol.intern("FOO-MODE");
  
  /* communicate between workspace document and workspace about sizing.  
     Otherwise you have a race.  But not export to users. */

  private boolean shrinkwrapping = false;

  /**
   * @undocumented
   */
  public void setShrinkwrapping (boolean value) {
    shrinkwrapping = value;
  }
  /**
   * @undocumented
   */
  public boolean getShrinkwrapping () {
    return shrinkwrapping;
  }

  /**
   * Sets the bounds of this workspace to a minimum size surrounding 
   * this workspaces items.
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */                             
  public void shrinkWrap()
       throws G2AccessException
  {
    /*yduj: as far as I can tell, what this code does is to request
      the G2 set the workspace bounds to the bounds of the first
      element on the workspace.  G2 itself has code that says "but
      everything else won't fit!  I'll just make it big enough to fit,
      OK?"  Then, we later get a resize event for the change in size
      of the workspace (interestingly, it is a resize item, rather
      than a resize workspace event), and so eventually we have a clue
      how big the workspace is.  However, the person responsible for
      this horrible kluge should at least be embarrassed about it!
      And should have commented what they were doing originally.  I
      think it's kind of odd that we go to all this careful calculation
      of the size, rather than just saying one pixel will do, given
      what we're really doing.*/
    Item[] items = getItems();
    if (items == null ||
	items.length == 0) return;
    Item item = items[0];
    int x = item.getItemXPosition();
    int y = item.getItemYPosition();
    int width = item.getItemWidth();
    int height = item.getItemHeight();
    int lft = x - (width/2);
    int rgt = lft + Math.max(width, 1);
    int top = y + (height/2);
    int bot = top - Math.max(height, 1);
    shrinkwrapping = true;
    setBounds (lft, top, rgt, bot);
  }

  /**
   * Requests G2 to show this workspace on this item's UiClientSession.
   * this workspaces items.
   * @param particulars a structure containing more specific instructions
   * as to how to show the workspace, which may contain any of the
   * following attributes:
   *  <code>
   *  symbolic-x-scale 
   *  symbolic-y-scale 
   *  symbolic-x-in-workspace 
   *  symbolic-y-in-workspace 
   *  symbolic-x-in-window 
   *  symbolic-y-in-window 
   *  x-offset-units 
   *  y-offset-units 
   *  symbolic-x-offset-direction 
   *  symbolic-y-offset-direction 
   *  x-magnification 
   *  y-magnification 
   *  x-in-workspace 
   *  y-in-workspace 
   *  x-in-window 
   *  y-in-window
   *  </code>. 
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call.
   */                             
  public void show(Structure particulars)
       throws G2AccessException
  {
    UiClientSession uiClientSession = retrieveSession(context);
    java.lang.Object[] args
      = new java.lang.Object[] {this, particulars, uiClientSession};
    context.callRPC(G2_SHOW_WORKSPACE_, args);
  }

  /**
   * Requests G2 to hide this workspace on this item's UiClientSession.
   * this workspaces items.
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call.
   */                             
  public void hide()
       throws G2AccessException
  {
    UiClientSession uiClientSession = retrieveSession(context);
    java.lang.Object[] args
      = new java.lang.Object[] {this, uiClientSession};
    context.callRPC(G2_HIDE_WORKSPACE_, args);
  }

  /**
   * @undocumented
   */
  public Vector getContainmentHierarchyItemConfigurationSnapshot()
  throws G2AccessException {
    Vector returnValue;
    synchronized (data) {
      returnValue = ((WorkspaceData)data).containmentHierarchyItemConfigurationSnapshot;
    }
    
    if (returnValue == null) {
      Sequence containmentHierarchy = getContainmentHierarchy();
      if (containmentHierarchy == null) // paranoia
	containmentHierarchy = new Sequence();
      containmentHierarchy.insertElementAt(this, 0);
      returnValue = new Vector();
      int size = containmentHierarchy.size();
      for (int i = 0; i < size; i++) {
	Item item = (Item)containmentHierarchy.elementAt(i);
	Sequence configurations = item.getItemConfigurationSnapshot();
	if (configurations != null)
	  returnValue.addElement(configurations);
      }
      KbConfiguration kbConfiguration =
	(KbConfiguration)context.getUniqueNamedItem(G2ClassSymbols.KB_CONFIGURATION_,
						    G2ClassSymbols.KB_CONFIGURATION_);
      Sequence configurations = kbConfiguration.getItemConfigurationSnapshot();
      if (configurations != null)
	returnValue.addElement(configurations);
    }
    synchronized (data) {
      WorkspaceData wsData = (WorkspaceData)data;
      if (wsData.containmentHierarchyItemConfigurationSnapshot == null)
	 wsData.containmentHierarchyItemConfigurationSnapshot = returnValue;
    }
    return (Vector)returnValue.clone();
  }

  /**
   * @undocumented
   */
  @Override
  public Vector getCompleteConfigurationSnapshot() throws G2AccessException {
    return getContainmentHierarchyItemConfigurationSnapshot();
  }

  /**
   * This goes to G2 only the first time.
   * @undocumented
   */
  @Override
  public Sequence getItemConfigurationSnapshot() throws G2AccessException {
    WorkspaceData wsData = (WorkspaceData)data;
    ItemData principalData = getPrincipalData();    
    if (wsData.configurationSnapshotCached) {
      return principalData.wsSnapshotOfConfiguration;
    } else {
      principalData.wsSnapshotOfConfiguration = getItemConfiguration();
      wsData.configurationSnapshotCached = true;
      return principalData.wsSnapshotOfConfiguration;
    }
  }

  /**
   * Changed data structure to allow the distinction to be made
   * for different types of attribute updates.
   * Background color and foreground color are different attributes
   * for workspaces, in difference to the same attributes on items,
   * which are virtual attributes.
   * @undocumented   
   */
  @Override
  protected boolean attributeSendsUpdates (Symbol attrName) {
    return super.attributeSendsUpdates(attrName) ||
      BACKGROUND_COLOR_.equals(attrName) ||
      FOREGROUND_COLOR_.equals(attrName);
  }

}
