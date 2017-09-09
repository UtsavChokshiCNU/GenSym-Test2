
package com.gensym.wksp;

import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.jgi.*;
import com.gensym.ntw.*;
import com.gensym.draw.*;
import java.awt.*; //Rectangle
import java.util.Locale;
import java.util.Enumeration;
import java.util.Vector;
import java.util.Hashtable;
import com.gensym.wksp.configurations.*;
import com.gensym.classes.UserMenuChoice;
import com.gensym.classes.Block;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;


public class WorkspaceElementHelper
implements ConfigurationSymbols {

  private static AnimationThread animationThread;

  /**
   * @undocumented
   */
  public static void animate(Animation animation) {
    // first protect against the thread having been
    // killed by the Applet Context
    if (animationThread == null || !animationThread.isAlive()) {
      animationThread = new AnimationThread();
      animationThread.start();
    }
    animationThread.addAnimation(animation);
  }

  //  private WorkspaceElement[] subWorkspaceElements;
  private boolean isSelected = false;
  private boolean isCut = false;
  private static final Object stdWkspElementMenu = null;//PopupMenuUtility.createMenu ();
  private boolean workspaceElementDebugP = false;
  private WorkspaceElement wElement;
  private DrawElement dElement;
  private Component component;
  private Item item;
  private WorkspaceView view;
  private static final Integer defaultInterval = new Integer(1000);
  private static final Symbol  
  PATH_ = Symbol.intern ("PATH"),
    RETURN_RPC_NAME_ = Symbol.intern ("RETURN-RPC-NAME"),
    ID_ = Symbol.intern ("ID"),
    INTERVAL_ = Symbol.intern ("INTERVAL"),
    X_OFFSET_ = Symbol.intern ("X-OFFSET"),
    Y_OFFSET_ = Symbol.intern ("Y-OFFSET");
  public static boolean userMenuChoiceMode1 = true;
  
  public WorkspaceElementHelper(WorkspaceElement wElement,
				DrawElement dElement,
				Component component,
				Item item,
				WorkspaceView view)
  throws G2AccessException {
    this.wElement = wElement;
    this.dElement = dElement;
    this.component = component;
    this.item = item;
    this.view = view;
    dElement.setCanvas(view);
  }

  private void invalidateElement(Component elt) {
    view.invalidateElement(elt);
  }

  private void invalidate(Rectangle[] oldBounds) {
    view.invalidate(oldBounds);
  }
  
  public Item getItem() {
    return item;
  }
  
  public void select () {
    isSelected = true;
  }

  public void unselect () {
    isSelected = false;
  }

  public boolean isSelected () {
    return isSelected;
  }

  boolean isCut () {
    return isCut;
  }

  void setCut (boolean newCutState) {
    isCut = newCutState;
    view.invalidateElement (((Component)dElement));
  }

  /**
   * @return true iff this element contains the Point (x,y)
   * Uses the exactBounds in its computation.
   */
  public boolean contains(int x, int y)
  {
    Rectangle[] bounds = dElement.getExactBounds();
    x = x + bounds[0].x;
    y = y + bounds[0].y;
    int length = bounds.length;

    for (int i = 0 ; i<length ; i++)
      if (bounds[i].contains(x,y))
        return true;

    return false;
  }

  /**
   * @return a more exact array of bounds than that provided
   * by getBounds.  PersistentCanvas may optimize its drawing
   * and input event to component mapping using these more
   * precise bounds, if the component implements DrawElement.
   */
  public static Rectangle[] getExactBounds (Item item)
       throws G2AccessException
  {
    Rectangle itemBounds = ((com.gensym.classes.ImplAccess)item).getBounds();//hack
    itemBounds.y = - itemBounds.y;
    Rectangle[] exactBounds = {itemBounds};
    return exactBounds;
  }

  public void notifyCommandHandler(WorkspaceElement element) {
    view.elementChanged ((WorkspaceElement)wElement);
  }

  void shiftTo(int newLeft, int newTop) {
    DrawElement element = dElement;    
    Rectangle[] currentBounds = element.getExactBounds();
    int length = currentBounds.length;
    Rectangle[] oldBounds = new Rectangle[length];
    for (int i = 0; i < length; i++) 
      oldBounds[i] = new Rectangle(currentBounds[i]);
    Rectangle oldBound = oldBounds[0];
    int oldLeft = oldBound.x;
    int oldTop = oldBound.y;
    int deltaX = newLeft - oldLeft;
    newTop = -newTop;//WE'RE STILL USING INTERNAL COORDS in ntw
    int deltaY = newTop - oldTop;
    view.shiftElement(component, deltaX, deltaY);
    notifyCommandHandler(wElement);
  }


  private static final Integer ZERO = new Integer(0);
  public void shift(WorkspaceEvent event) {
    DrawElement element = dElement;
    Structure extraInfo = event.getInfo();
    Sequence path = (Sequence)extraInfo.getAttributeValue(PATH_, null);
    if (path != null) {
      Object id = extraInfo.getAttributeValue(ID_, null);
      Symbol rpcName = (Symbol)extraInfo.getAttributeValue(RETURN_RPC_NAME_, null);
      int xOffset = ((Integer)extraInfo.getAttributeValue(X_OFFSET_, ZERO)).intValue();
      int yOffset = ((Integer)extraInfo.getAttributeValue(Y_OFFSET_, ZERO)).intValue();              
      int interval = ((Integer)extraInfo.getAttributeValue(INTERVAL_, defaultInterval)).intValue();
      try {
	Animation animation =
	  new DefaultWorkspaceElementAnimation(this, dElement,path,
					       xOffset, yOffset, interval,
					       System.currentTimeMillis(),
					       rpcName,id);	
	animate(animation);
      } catch (NoSuchAttributeException nsae) {
	Trace.exception(nsae);//--->malformed x,y path
      }
    } else {
      Rectangle newBounds = WorkspaceUtil.boundsStructureToBounds(extraInfo);
      if (newBounds != null) 
	shiftTo(newBounds.x, newBounds.y);
      else
	System.out.println("INVALID NEW BOUNDS in MOVE\n");
    }
  }

  public void shift(int deltaX, int deltaY) {
    view.elementChanged (wElement);
  }
  
  public void resize(WorkspaceEvent event) {
    WorkspaceElement element = wElement;
    if (element != null) { 
      Rectangle[] currentBounds = dElement.getExactBounds();
      int length = currentBounds.length;
      Rectangle[] oldBounds = new Rectangle[length];
      for (int i = 0; i < length; i++) 
	oldBounds[i] = new Rectangle(currentBounds[i]);
      Structure boundsStructure = event.getInfo();
      Rectangle newBounds = WorkspaceUtil.boundsStructureToBounds(boundsStructure);
      if (newBounds != null) {
	if (wElement instanceof WorkspaceIconImpl) //hack; icons are actually 1 bigger
	  component.setSize(newBounds.width + 1,newBounds.height + 1); 
	else
	  component.setSize(newBounds.width,newBounds.height);
	invalidate(oldBounds);
	invalidateElement(component);
	notifyCommandHandler(wElement);
      } else
	System.out.println("INVALID NEW BOUNDS in RESIZE\n");
    } else
      System.out.println("Can not resize non existent element\n");
}

  public DraggingGhost getDraggingGhost (int left, int top, int width, int height) {
    Color ghostColor = Color.gray;
    DraggingGhost ghost = new DraggingGhost ();
    ghost.elements = new Component[4];
    ghost.elements[0] = new LineElement (ghostColor, left, top, left+width, top);
    ghost.elements[1] = new LineElement (ghostColor, left+width, top, left+width, top+height);
    ghost.elements[2] = new LineElement (ghostColor, left+width, top+height, left, top+height);
    ghost.elements[3] = new LineElement (ghostColor, left, top+height, left, top);
    ghost.boundsArray[0] = new Rectangle (left, top, width+2, height+2);
    return ghost;
  }

  /**
   *@returns a DraggingGhost encompassing the element's bounds.
   */ 
  public DraggingGhost getDraggingGhost () {
    Rectangle eltBounds = (dElement.getExactBounds())[0];
    int left = eltBounds.x;
    int top = eltBounds.y;
    int width = eltBounds.width, height = eltBounds.height;
    left -=1; top -=1; width +=1; height +=1;
    return getDraggingGhost (left, top, width, height);
  }

  /**
   *@returns a DraggingGhost extending from the (top,left) of the item
   * to (currentX,currentY).
   */
  public DraggingGhost getDraggingGhost (int markerLocn, int currentX, int currentY) {
    Rectangle eltBounds = (dElement.getExactBounds())[0];
    int left = eltBounds.x, top = eltBounds.y,
      width = currentX - left, height = currentY - top;
    left -=1; top -=1; width +=1; height +=1;
    return getDraggingGhost (left, top, width, height);
  }

  public Symbol getG2ClassName() throws G2AccessException {
    return item.getG2ClassName();
  }

  public String getPrettyClassName() {
    String name = "default";
    try {
      name = WorkspaceUtil.computePrettyClassName(getG2ClassName().toString());
    } catch (G2AccessException ae) {}
    return name;
  }

  private Hashtable systemMenuCache = new Hashtable (23);
  private MenuItem getSystemMenuItem(Symbol systemMenuChoice_) {
    MenuItem smi;
    if ((smi = (MenuItem) systemMenuCache.get (systemMenuChoice_)) == null) {
      String systemMenuChoice = systemMenuChoice_.getPrintValue ();
      systemMenuCache.put
	(systemMenuChoice_, smi = new MenuItem
	 (WorkspaceUtil.computePrettyClassName (systemMenuChoice)));
      smi.setActionCommand (systemMenuChoice);
    }
    return smi;
  }

  public PopupMenu getContextMenu () {
    String newEditMenuString = getPrettyClassName();
    ((PopupMenu)stdWkspElementMenu).setLabel(newEditMenuString);
    resetUserMenuItems();
    resetSystemMenuItems();

    Boolean permitted = Boolean.FALSE;
    Sequence choiceRestrictions = null;
    Symbol userMode = Symbol.intern("FOO-MODE");//hack
    //SYSTEM-MENU-CHOICES
    try {
      ConfigurationSupport.setUserMode(userMode);
      Sequence systemMenuChoices = //not in g250r1 
	 (Sequence)((Block)item).getSystemMenuChoicesForClass();
      Structure restrictionStruct
	= ConfigurationSupport.getChoiceRestrictions(item, ITEM_MENU_);
      permitted 
	= (Boolean)restrictionStruct.getAttributeValue(PERMITTED_, Boolean.FALSE);
      choiceRestrictions
	= (Sequence) restrictionStruct.getAttributeValue(CHOICE_RESTRICTIONS_, new Sequence());
      Sequence filteredSystemMenuChoices 
	= ConfigurationSupport.filterChoicesByRestrictions(systemMenuChoices,
							   choiceRestrictions,
							   permitted.booleanValue());
      Enumeration e = filteredSystemMenuChoices.elements();
      if (e.hasMoreElements())
 	((PopupMenu)stdWkspElementMenu).addSeparator();
      while(e.hasMoreElements()) {
 	addSystemMenuChoice(getSystemMenuItem((Symbol)e.nextElement()));
      }
    } catch (G2AccessException g2ae) {System.out.println(g2ae);}
    //USER-MENU-CHOICES
    try {
      Sequence userMenuChoices = null;
      if (userMenuChoiceMode1) {
	userMenuChoices = item.getCurrentUserMenuChoices(userMode);
      }
      else 
	userMenuChoices 
	  = ConfigurationSupport.filterChoicesByRestrictions(getUserMenuChoicesForClass(item),
							     choiceRestrictions,
							     permitted.booleanValue());
      if (userMenuChoices != null) {
	Enumeration e = userMenuChoices.elements();
	if (e.hasMoreElements())
	  ((PopupMenu)stdWkspElementMenu).addSeparator();
	while(e.hasMoreElements()) {
	  UserMenuChoice userMenuChoice = (UserMenuChoice)e.nextElement();
	  addUserMenuChoice(userMenuChoice);
	}
      }
    } catch (G2AccessException g2ae) {System.out.println(g2ae);}
    return ((PopupMenu)stdWkspElementMenu);
  }

  private Sequence getUserMenuChoicesForClass(Item item) {
    //TBD
    return new Sequence();
  }
  
  private static Vector currentUserMenuItems = new Vector();
  private static WkspElementMenuHandler userMenuItemHandler = new WkspElementMenuHandler ();

  private static void resetUserMenuItems() {
    boolean hadUserMenuItems = false;
    for (Enumeration e = currentUserMenuItems.elements(); e.hasMoreElements();) {
      hadUserMenuItems = true;
      MenuItem m = (MenuItem)e.nextElement();
      ((PopupMenu)stdWkspElementMenu).remove(m);
    }
    if (hadUserMenuItems) {
      int count = ((PopupMenu)stdWkspElementMenu).getItemCount();
      ((PopupMenu)stdWkspElementMenu).remove(count - 1);
    }
    currentUserMenuItems.removeAllElements();
  }
     
  private void addUserMenuChoice(UserMenuChoice umc)
       throws G2AccessException
  {
    UserMenuItem umi = new UserMenuItem (umc, item);
    umi.addActionListener (userMenuItemHandler);
    currentUserMenuItems.addElement(umi);
    ((PopupMenu)stdWkspElementMenu).add(umi);
  }
 
  private static Vector currentSystemMenuItems = new Vector();
  private static WkspElementMenuHandler systemMenuItemHandler = new WkspElementMenuHandler ();
  private static void resetSystemMenuItems() {
    boolean hadSystemMenuItems = false;
    for (Enumeration e = currentSystemMenuItems.elements(); e.hasMoreElements();) {
      hadSystemMenuItems = true;
      MenuItem m = (MenuItem)e.nextElement();
      ((PopupMenu)stdWkspElementMenu).remove(m);
    }
    if (hadSystemMenuItems) {
      int count = ((PopupMenu)stdWkspElementMenu).getItemCount();
      ((PopupMenu)stdWkspElementMenu).remove(count - 1);
    }
    currentSystemMenuItems.removeAllElements();
  }
       
  private void addSystemMenuChoice(MenuItem smi)
       throws G2AccessException
  {    
    smi.addActionListener (systemMenuItemHandler);
    currentSystemMenuItems.addElement(smi);
    ((PopupMenu)stdWkspElementMenu).add(smi);
  }
 
  public void receivedInitialValues (ItemEvent e) {
    //
  }

  public void itemModified (ItemEvent e) {
    //System.out.println("ELEMENT RECIEVED UPDATE" + e);
    view.invalidateElement(component);
  }

  public void itemDeleted (ItemEvent e) {
    //System.out.println("ELEMENT RECIEVED UPDATE" + e);
  }

  private static Image colorSheet = java.awt.Toolkit.getDefaultToolkit ().createImage
  (new com.gensym.ntw.util.ColorSheetProducer (200, 200,
					       0x50, 0x00, 0x00, 0x00));

  void paintDecorations(Graphics g) {
    if(WorkspaceView.annotationsVisible) {
      WorkspaceView.annotationDrawer.drawAnnotations(component, item, g);
    }
    if (isCut) {
      Rectangle[] exbnds = dElement.getExactBounds ();
      Rectangle bnds = exbnds[0];
      paintCutStatus (g, bnds.x, bnds.y, bnds.width, bnds.height);
    }
  }      

  void paintCutStatus (Graphics g, int left, int top, int width, int height) {
    left = 0; top = 0;
    while (left < width && top < height) {
      g.drawImage (colorSheet, left, top, null);
      left += 200;
      if (left > width) {
	left = 0;
	top  += 200;
      }
    }      
  }

  public void dispose() throws G2AccessException {
    systemMenuCache.clear() ;
    systemMenuCache = null ;
    item = null ;
    view = null ;
    component = null ;
    dElement = null ;
    wElement = null ;
  }

}

