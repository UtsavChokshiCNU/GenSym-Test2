package com.gensym.wksp;

import java.io.IOException;
import java.awt.*;
import java.beans.*;
import java.util.Observable;
import java.util.Observer;
import java.util.Vector;
import java.util.Hashtable;
import java.util.Enumeration;
import com.gensym.message.Trace;
import com.gensym.classes.Item;
import com.gensym.ntw.TwGateway;
import com.gensym.ntw.TwAccess;
import com.gensym.classes.G2ForeignObject;
import com.gensym.classes.G2ForeignSerializable;
import com.gensym.classes.G2JavaBean;
import com.gensym.classes.ImplAccess;
import com.gensym.classes.G2Definition;
import com.gensym.classes.modules.t2beans.ForeignClassDefinition;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.jgi.*;
import com.gensym.draw.*;

public class TestBeanElement extends Container implements DrawElement, WorkspaceElement {

  private G2ForeignObject itm;
  private Object bean;
  private Component beanComponent;
  private Rectangle[] bounds;
  private WorkspaceView view;
  private WorkspaceElementHelper helper;
  private static final String TRANSPARENT = "transparent";
  private static int borderWidth = 0;
  private static Color borderColor = null;
  private Observer scrollHandlerForHeavyWeightComponent;
  static boolean beansDebug;

  static {
    String borderWidthString = System.getProperty ("com.gensym.wksp.beans.borderwidth", "0");
    String borderColorString = System.getProperty ("com.gensym.wksp.beans.bordercolor", TRANSPARENT);
    try {
      borderWidth = Integer.parseInt (borderWidthString, 10);
      if (!borderColorString.equals (TRANSPARENT)) {
	borderColor = new Color (Integer.decode (borderColorString).intValue ());
      }
    } catch (Exception e) {
      Trace.exception (e);
    }
  }

  TestBeanElement (G2ForeignObject itm, WorkspaceView view) throws G2AccessException {
    this.itm = itm;
    this.view = view;
    helper = new WorkspaceElementHelper (this, this, this, itm, view);
    setLayout (null);
    setBackground (borderColor);
    bean = resolveObject (itm, view);
    beanComponent = (Component)bean;
    //System.out.println ("TBE: Created bean -> " + bean);
    add (beanComponent);
    bounds = WorkspaceElementHelper.getExactBounds (itm);
    view.addElement ((WorkspaceElement)this);
    int xOffset = 0; //view.getScrollState (true).getViewMin ();
    int yOffset = 0; //view.getScrollState (false).getViewMin ();
    setBounds (bounds[0].x - xOffset - borderWidth, 
	       bounds[0].y - yOffset - borderWidth,
	       bounds[0].width + borderWidth*2,
	       bounds[0].height + borderWidth*2);
    if (beansDebug)
      System.out.println ("BeanElement Cxr: Setting Bounds to : " + bounds[0]);
    if (!isLightweight (beanComponent)) {
      scrollHandlerForHeavyWeightComponent = new Observer () {
	@Override
	public void update (Observable o, Object data) {
	  resizeChild (bounds[0].width, bounds[0].height);
	}
      };
      view.addScrollObserver (scrollHandlerForHeavyWeightComponent, true);
      view.addScrollObserver (scrollHandlerForHeavyWeightComponent, false);
    }
    registerBeanForForeignObject (itm);
  }

  @Override
  public void paint (Graphics g) {
    if (borderColor != null) {
      g.setColor (getBackground ());
      g.fillRect (0, 0, 1000, 1000);
    }
    super.paint (g);
    if (isCut ()) {
      Rectangle[] exbnds = getExactBounds ();
      Rectangle bnds = exbnds[0];
      helper.paintCutStatus (g, bnds.x, bnds.y, bnds.width, bnds.height);
    }
  }

  @Override
  public void handleWorkspaceItemMoved (WorkspaceEvent event) {
    helper.shift (event);
  }

  @Override
  public void handleWorkspaceItemResized (WorkspaceEvent event) {
    if (borderWidth != 0) {
      Structure boundsStructure = (Structure) event.getInfo ().clone ();
      Integer left, top, right, bottom;
      left   = (Integer)boundsStructure.getAttributeValue (WorkspaceUtil.sleft, null);
      top    = (Integer)boundsStructure.getAttributeValue (WorkspaceUtil.stop, null);
      right  = (Integer)boundsStructure.getAttributeValue (WorkspaceUtil.sright, null);
      bottom = (Integer)boundsStructure.getAttributeValue (WorkspaceUtil.sbottom, null);
      boundsStructure.setAttributeValue (WorkspaceUtil.sleft,
					 new Integer (left.intValue() - borderWidth));
      boundsStructure.setAttributeValue (WorkspaceUtil.stop,
					 new Integer (top.intValue() + borderWidth));
      boundsStructure.setAttributeValue (WorkspaceUtil.sright,
					 new Integer (right.intValue() + borderWidth));
      boundsStructure.setAttributeValue (WorkspaceUtil.sbottom,
					 new Integer (bottom.intValue() - borderWidth));
      event = new WorkspaceEvent (event.getSource (),
				  event.getNotificationCode (),
				  event.getItem (),
				  boundsStructure);
    }
    helper.resize (event);
  }

  @Override
  public void handleWorkspaceItemColorsChanged (WorkspaceEvent event) {
    // ignore;
  }

  @Override
  public Item getItem() {
    return itm;
  }

  @Override
  public void select () {
    helper.select ();
  }

  @Override
  public void unselect () {
    helper.unselect ();
  }

  @Override
  public boolean isSelected () {
    return helper.isSelected();
  }

  
  /**
   *@returns a DraggingGhost encompassing the element's bounds.
   */ 
  @Override
  public DraggingGhost getDraggingGhost () {
    Rectangle eltBounds = getExactBounds()[0];
    int left = eltBounds.x;
    int top = eltBounds.y;
    int width = eltBounds.width, height = eltBounds.height;
    left -=1; top -=1; width +=1; height +=1;
    return getDraggingGhost (left, top, width, height);
  }

  @Override
  public DraggingGhost getDraggingGhost (int markerLocn, int currentX, int currentY) {
    return null;
  }

  @Override
  public DraggingGhost getDraggingGhost (int left, int top, int width, int height) {
    Color Xcolor = Color.orange;
    Color ghostColor = Color.gray;
    DraggingGhost ghost = new DraggingGhost ();
    ghost.elements = new Component[6];
    ghost.elements[2] = new LineElement (ghostColor, left, top, left+width, top);
    ghost.elements[3] = new LineElement (ghostColor, left+width, top, left+width, top+height);
    ghost.elements[4] = new LineElement (ghostColor, left+width, top+height, left, top+height);
    ghost.elements[5] = new LineElement (ghostColor, left, top+height, left, top);
    int[] xPts = new int [4];
    int[] yPts = new int [4];
    xPts[0] = left;  xPts[1] = left + Math.round (width*0.1f);
    xPts[2] = left + width; xPts[3] = left + Math.round (width*0.9f);
    yPts[0] = top; yPts[1] = top; yPts[2] = top + height; yPts[3] = top + height;
    ghost.elements[0] = new PolygonElement (Xcolor, 4, xPts, yPts);
    xPts[0] = left + Math.round (0.9f*width); xPts[1] = left + width;
    xPts[2] = left + Math.round (0.1f*width); xPts[3] = left;    
    ghost.elements[1] = new PolygonElement (Xcolor, 4, xPts, yPts);
    ghost.boundsArray[0] = new Rectangle (left, top, width+2, height+2);
    return ghost;
  }

  @Override
  public PopupMenu getContextMenu () {
    return null;
  }

  @Override
  public boolean isCut () {
    return helper.isCut ();
  }

  @Override
  public void setCut (boolean newCutState) {
    helper.setCut (newCutState);
  }

  @Override
  public void receivedInitialValues (com.gensym.util.ItemEvent ie) {}

  @Override
  public void itemModified (com.gensym.util.ItemEvent ie) {}

  @Override
  public void itemDeleted (com.gensym.util.ItemEvent ie) {}

  Object resolveObject (G2ForeignObject itm, WorkspaceView view) {
    String className = null;
    try {
      java.lang.Object obj = null;
      if (itm instanceof G2ForeignSerializable) {
	try {
	  obj = ((G2JavaBean)itm).retrieveObject ();
	} catch (G2AccessException g2ae) {
	  Trace.exception (g2ae);
	} catch (Exception e) {
	  Trace.exception (e);
	}
      }
      if (obj != null)
	return obj;
      G2Definition defn = itm.getDefinition ();
      if (!(defn instanceof ForeignClassDefinition))
	return new NoBean (defn.getClassName ().getPrintValue());
      ForeignClassDefinition foreignDefn = (ForeignClassDefinition) itm.getDefinition ();
      className = foreignDefn.getExternalClassName ();
      return Beans.instantiate (getClass().getClassLoader (), className);
    } catch (G2AccessException g2ae) {
      Trace.exception (g2ae);
      return new NoBean ("Unknown Bean Class");
    } catch (ClassNotFoundException cnfe) {
      Trace.exception (cnfe);
      return new NoBean (className);
    } catch (IOException ioe) {
      Trace.exception (ioe);
    }
    return null;
  }

  private static Insets insets = new Insets (borderWidth, borderWidth, borderWidth, borderWidth);
  @Override
  public Insets getInsets () {
    return insets;
  }

  @Override
  public void shift (int shift_x, int shift_y) {
    bounds[0].translate(shift_x, shift_y);
    Point location = getLocation();
    setLocation(location.x + shift_x, location.y + shift_y);
  }

  @Override
  public Rectangle[] getExactBounds () {return bounds;}
  @Override
  public void setCanvas (PersistentCanvas canvas) {}
  @Override
  public void changeColor(Object logicalColor, Color color) {}
  @Override
  public void changeColor(Object logicalColor, Object colorKey) {}
  @Override
  public Object[] getLogicalColors() {return null;}

  @Override
  public void repaint (long tm, int x, int y, int width, int height) {
    view.invalidateElement (this);
  }

  @Override
  public void dispose () {
    try {
      if (!isLightweight (beanComponent)) {
	view.removeScrollObserver (scrollHandlerForHeavyWeightComponent, true);
	view.removeScrollObserver (scrollHandlerForHeavyWeightComponent, false);
      }
      deregisterBeanForForeignObject (itm);
    } catch (G2AccessException g2ae) {
      Trace.exception (g2ae);
    }
    bean = null;
    beanComponent = null;
  }

  void registerBeanForForeignObject (G2ForeignObject obj) throws G2AccessException {
    if (bean instanceof NoBean)
      return;
    BeansDeferredCaller.getCaller().register (obj, bean);
  }

  void deregisterBeanForForeignObject (G2ForeignObject obj) throws G2AccessException {
    if (bean instanceof NoBean || !obj.isValid ())
      return;
    BeansDeferredCaller.getCaller().deregister (obj, bean);
  }


  /**
   * Obtained from sun.awt.windows.WToolkit - 1.1.7
   */
  private boolean isLightweight (Component bean) {
    return !(bean instanceof Button ||
	     bean instanceof Canvas ||
	     bean instanceof Checkbox ||
	     bean instanceof Choice ||
	     bean instanceof Panel ||
	     bean instanceof ScrollPane ||
	     bean instanceof Window ||
	     bean instanceof Label ||
	     bean instanceof List ||
	     bean instanceof Scrollbar ||
	     bean instanceof TextComponent);
  }

  java.lang.Object getBean () {
    return bean;
  }

  @Override
  public void reshape (int x, int y, int width, int height) {
    if (beansDebug)
      System.out.println ("BeanElement reshape (" +
			  new Rectangle (x, y, width, height)  + ")");
    super.reshape (x, y, width, height);
    bounds[0] = new Rectangle (x + borderWidth,
			       y + borderWidth,
			       width - borderWidth*2,
			       height - borderWidth*2);
    if (beanComponent == null) // we're already disposed!
      return;
    if (isLightweight (beanComponent))
      beanComponent.setBounds (borderWidth, borderWidth,
			       width - borderWidth*2, height - borderWidth*2);
    else
      resizeChild (width - borderWidth*2, height - borderWidth*2);
  }

  private void resizeChild (int width, int height) {
    Point origin = new Point (0, 0);
    view.translateWindowToView (origin);
    beanComponent.setBounds (borderWidth - origin.x,
			     borderWidth - origin.y,
			     width,
			     height);
  }


}


class BeansDeferredCaller extends G2ConnectionAdapter implements Runnable {
 
  static BeansDeferredCaller theCaller;
  private CallList regList, unregList;
  private Hashtable regTable = new Hashtable (5), unregTable = new Hashtable (5);
  private static final Symbol NONE_ = Symbol.intern ("NONE");
  private static final Symbol T2BEANS_REGISTER_STUB_FOR_BEAN_ = Symbol. intern ("T2BEANS-REGISTER-STUB-FOR-BEAN");
  private static final Symbol T2BEANS_DEREGISTER_STUB_FOR_BEAN_ = Symbol.intern ("T2BEANS-DEREGISTER-STUB-FOR-BEAN");

  static BeansDeferredCaller getCaller () {
    if (theCaller == null) {
      theCaller = new BeansDeferredCaller ();
      synchronized (theCaller) {
	Thread callThread = new Thread (theCaller, "Deferred Beans Registration Handler");
	callThread.start ();
	try {
	  theCaller.wait ();
	} catch (InterruptedException ie) {
	  Trace.exception (ie);
	}
      }
    }
    return theCaller;
  }

  synchronized void register (G2ForeignObject obj, Object bean) throws G2AccessException {
    TwAccess cxn = (TwAccess) ((ImplAccess)obj).getContext ();
    DeferredCallData regData = new DeferredCallData (cxn, obj, bean);
    if (cxn.getG2State ().equals (G2Gateway.RUNNING_))
      register0 (regData);
    else {
      Vector regList = getRegistrationList (cxn);
      regList.addElement (regData);
      notify ();
    }
  }

  synchronized void deregister (G2ForeignObject obj, Object bean) throws G2AccessException {
    TwAccess cxn = (TwAccess) ((ImplAccess)obj).getContext ();
    DeferredCallData unregData = new DeferredCallData (cxn, obj, bean);
    if (cxn.getG2State ().equals (G2Gateway.RUNNING_))
      deregister0 (unregData);
    else {
      Vector regList = getRegistrationList (cxn);
      int regIndex = regList.indexOf (unregData);
      if (regIndex >= 0) {
	regList.removeElementAt (regIndex);
      } else {
	Vector unregList = getDeregistrationList (cxn);
	unregList.addElement (unregData);
	notify ();
      }
    }
  }

  private CallList getRegistrationList (TwAccess cxn) {
    CallList regList = (CallList) regTable.get (cxn);
    if (regList == null) {
      regList = new CallList (cxn, this);
      regTable.put (cxn, regList);
    }
    return regList;
  }

  private CallList getDeregistrationList (TwAccess cxn) {
    CallList unregList = (CallList) unregTable.get (cxn);
    if (unregList == null) {
      unregList = new CallList (cxn, this);
      unregTable.put (cxn, unregList);
    }
    return unregList;
  }

  @Override
  public synchronized void run () {

    notify ();
    while (true) {
      try {
	wait ();
	if (TestBeanElement.beansDebug)
	  System.out.println (" -> Caller waking up");
	Enumeration keys = regTable.keys ();
	while (keys.hasMoreElements ()) {
	  TwAccess cxn = (TwAccess) keys.nextElement ();
	  CallList regList = getRegistrationList (cxn);
	  for (int i=regList.size(); i-->0;) {
	    if (cxn.getG2State ().equals (G2Gateway.RUNNING_)) {
	      try {
		DeferredCallData regData = (DeferredCallData) regList.elementAt (i);
		register0 (regData);
		regList.removeElementAt (i);
	      } catch (G2AccessException g2ae) {
		if (cxn.getG2State ().equals (G2Gateway.RUNNING_)) {
		  System.err.println ("Error registering Bean! " + g2ae);
		  Trace.exception (g2ae);
		}
	      }
	    }
	  }
	  if (regList.isEmpty ()) {
	    regTable.remove (cxn);
	    regList.dispose ();
	  }
	}
	keys = unregTable.keys ();
	while (keys.hasMoreElements ()) {
	  TwAccess cxn = (TwAccess) keys.nextElement ();
	  CallList unregList = getDeregistrationList (cxn);
	  for (int i=unregList.size(); i-->0;) {
	    if (cxn.getG2State ().equals (G2Gateway.RUNNING_)) {
	      try {
		DeferredCallData unregData = (DeferredCallData) unregList.elementAt (i);
		deregister0 (unregData);
		unregList.removeElementAt (i);
	      } catch (G2AccessException g2ae) {
		if (cxn.getG2State ().equals (G2Gateway.RUNNING_)) {
		System.err.println ("Error deregistering Bean! " + g2ae);
		Trace.exception (g2ae);
		}
	      }
	    }
	  }
	  if (unregList.isEmpty ()) {
	    unregTable.remove (cxn);
	    unregList.dispose ();
	  }
	}
      } catch (InterruptedException ie) {
	System.err.println ("Beans Deferred Thread Quitting! " + ie);
	Trace.exception (ie);
      } catch (G2AccessException g2ae) {
	System.err.println ("Problems getting G2 State : " + g2ae);
	Trace.exception (g2ae);
      }
    }
  }

  private void register0 (DeferredCallData data) throws G2AccessException {
    TwAccess cxn = data.cxn;
    G2ForeignObject obj = data.g2bean;
    java.lang.Object javaBean = data.javabean;
    Item beanProxyInG2 = 
      cxn.getG2ProxyForJavaObject (null,
				   NONE_,
				   javaBean);
    if (TestBeanElement.beansDebug)
      System.out.println ("REG: Got Bean Proxy in G2 : " + beanProxyInG2);
    
    cxn.callRPC (T2BEANS_REGISTER_STUB_FOR_BEAN_,
		 new java.lang.Object[] {beanProxyInG2, obj, cxn.retrieveSession ()});
  }
  
  private void deregister0 (DeferredCallData data) throws G2AccessException {
    TwAccess cxn = data.cxn;
    G2ForeignObject obj = data.g2bean;
    java.lang.Object javaBean = data.javabean;
    Item beanProxyInG2 = 
      cxn.getG2ProxyForJavaObject (null,
				   NONE_,
				   javaBean);
    if (TestBeanElement.beansDebug)
      System.out.println ("DEREG: Got Bean Proxy in G2 : " + beanProxyInG2);
    
    if (beanProxyInG2.isValid ()) // might already be deleted!
      cxn.callRPC (T2BEANS_DEREGISTER_STUB_FOR_BEAN_,
		   new java.lang.Object[] {beanProxyInG2, obj, cxn.retrieveSession ()});
  }
}



class DeferredCallData {

  TwAccess cxn;
  G2ForeignObject g2bean;
  java.lang.Object javabean;

  DeferredCallData (TwAccess cxn, G2ForeignObject obj, java.lang.Object javaBean) {
    this.cxn = cxn;
    this.g2bean = obj;
    this.javabean = javaBean;
  }

  @Override
  public boolean equals (Object o) {
    if (!(o instanceof DeferredCallData))
      return false;
    DeferredCallData other = (DeferredCallData)o;
    return (cxn.equals (other.cxn) &&
	    g2bean.equals (other.g2bean) &&
	    javabean.equals (other.javabean));
  }
}

class CallList extends Vector implements G2ConnectionListener {

  private TwAccess cxn;
  private BeansDeferredCaller caller;
  
  CallList (TwAccess cxn, BeansDeferredCaller caller) {
    this.cxn = cxn;
    this.caller = caller;
    cxn.addG2ConnectionListener (this);
  }

  private void notifyCaller () {
    synchronized (caller) {
      if (TestBeanElement.beansDebug)
	System.out.println ("Notifying caller of state change");
      caller.notify ();
    }
  }

  void dispose () {
    cxn.removeG2ConnectionListener (this);
  }

  @Override
  public void g2IsPaused(G2ConnectionEvent event) {}
  
  @Override
  public void g2IsResumed(G2ConnectionEvent event) {
    notifyCaller ();
  }

  @Override
  public void g2IsReset(G2ConnectionEvent event) {}

  @Override
  public void g2IsStarted(G2ConnectionEvent event) {
    notifyCaller ();
  }
  
  @Override
  public void g2ConnectionClosed(G2ConnectionEvent event) {
    dispose ();
  }

  @Override
  public void g2ConnectionInitialized(G2ConnectionEvent event) {}
 
  @Override
  public void g2MessageReceived(G2ConnectionEvent event) {}

  @Override
  public void communicationError(G2CommunicationErrorEvent error_event) {}

  @Override
  public void readBlockage(G2ConnectionEvent event) {}

  @Override
  public void writeBlockage(G2ConnectionEvent event) {}


}
