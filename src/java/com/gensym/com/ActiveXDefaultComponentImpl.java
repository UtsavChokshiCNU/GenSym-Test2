/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.ActiveXDefaultComponentImpl.java
 *
 *   Author: Allan Scott
 */

package com.gensym.com;

import java.awt.Canvas;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.LayoutManager;
import java.awt.LayoutManager2;
import java.awt.Point;
import java.awt.Rectangle;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyVetoException;
import java.beans.BeanInfo;
import java.beans.EventSetDescriptor;

import com.gensym.tracebeans.TraceElement;
import com.gensym.tracebeans.TraceElementVector;

import java.io.Serializable;

import java.util.Vector;



/** The class <code>ActiveXDefaultComponentImpl</code> provides an
* implementation of the <code>ActiveXDefaultComponent</code> interface.
* This class is abstract because the implementation is incomplete. The
* primary reason it is incomplete is that it does not provide the
* code that creates an <code>ActiveXProxy</code>.
* <p>
* <code>BeanXporter</code> emits subclasses of this class for each
* CO_CLASS in the type library.  The class <code>ActiveXGenericComponent</code>
* also extends this class.
* <p>
* @see ActiveXGenericComponent
* @see BeanXporter
*/
public abstract class ActiveXDefaultComponentImpl  extends Canvas
                                  implements Serializable,
                                             ActiveXDefaultComponent,
                                             ActiveXRuntimeConstants,
                                             ActiveXTraceLevels
{
  static final long serialVersionUID = -3111900335335073601L;

  /** @undocumented */
  protected static final int PREFERRED_WIDTH  = 300;
  /** @undocumented */
  protected static final int PREFERRED_HEIGHT = 400;
  /** @undocumented */
  protected static final int MIN_WIDTH  = 1;
  /** @undocumented */
  protected static final int MIN_HEIGHT = 1;
  /** @undocumented */
  protected static final int MAX_WIDTH  = 10000;
  /** @undocumented */
  protected static final int MAX_HEIGHT = 10000;
  
  /** @undocumented */
  protected boolean hasBeenAdded = false;    
  /** @undocumented */
  protected boolean activateOnLoad = true;
  /** @undocumented */
  protected transient Hwnd hWnd = null;
  /** @undocumented */
  protected boolean usesGivenProxy = false;
  /** @undocumented */
  protected transient boolean frozen = false;

  /** @undocumented */
  protected transient int dispatchPointer = AX_NO_DISPATCH;
  /** @undocumented */
  protected transient ActiveXDispatchable axDispatch = null;
  /** @undocumented */
  protected ActiveXProxy axProxy;  
  /** @undocumented */
  protected static Guid classID = null;

  // ******************* Constructors *************************

  /** Construct an <code>ActiveXDefaultComponentImpl</code> from an
  * instance that implements the <code>ActiveXDispatchable</code>
  * interface.  This can throw an <code>ActiveXCastException</code>
  * in the case that this is an incompatable conversion.
  */
  public ActiveXDefaultComponentImpl (ActiveXDispatchable axDispatch) 
    throws ActiveXCastException 
  {
    super();
    this.axDispatch = axDispatch; 
    dispatchPointer = axDispatch.getDispatchPointer();
    axProxy = axDispatch.getActiveXProxy();
    usesGivenProxy = true;    
  }
  
  /**  Zero argument constructor required to allow subclasses to
  * define Java beans.
  */
  public ActiveXDefaultComponentImpl() 
  {  
    super();
  }


  // ********************** Adding into a container *************
  
    
  /** @undocumented */
  @Override
  public void addNotify () {
    boolean loadedp;

    loadedp = false;
    super.addNotify();    

    if ((axProxy != null) && axProxy.hasBeenLoaded()) {
      loadedp = true;
    }

    setVisible(true);

    if (hWnd == null) {
      hWnd = new Hwnd(this);
      if (axProxy != null) {
	axProxy.setHWnd(hWnd);
	if(loadedp) {
	  axProxy.startDaemon();
	}
      }
    }
    if (hWnd.handleToPeer == Hwnd.NO_HWND) {
      message(AX_ERROR, "Failed to obtain HWND for " + this);
    }
  }

  //******************** Implementation of ActiveXDispatchable ****

  /**
  * Implementation of <code>ActiveXDispatchable</code> interface
  * @see ActiveXDispatchable
  */
  @Override
  public ActiveXProxy getActiveXProxy() {
      return axProxy;
  }

  /**
  * Implementation of <code>ActiveXDispatchable</code> interface
  * @see ActiveXDispatchable
  */
  @Override
  public int getDispatchPointer() {
      return dispatchPointer;
  }

  /**
  * Implementation of <code>ActiveXDispatchable</code> interface
  * @see ActiveXDispatchable
  */
  @Override
  public int getDispatchPointer(ActiveXProxy proxy)
  {
    // If proxy is the same there is no need for marshalling
    if (proxy == axProxy)
    {
      return dispatchPointer;
    }
    // Otherwize need to marshall the pointer to the 
    // thread of my current proxy
    else {     
      int stream = axProxy.marshalInterface(dispatchPointer);
      if (stream == 0)
         return dispatchPointer;

      return proxy.getMarshaledInterface(stream);
    }
  }

  /**
  * Implementation of <code>ActiveXDispatchable</code> interface
  * @see ActiveXDispatchable
  */
  @Override
  public Variant axInvoke(String methodName,
                          Vector args) 
                          throws ActiveXException 
  {
    if (axProxy == null) { 
      throw new ActiveXMissingProxyException(this); 
    }
    return axDispatch.axInvoke(methodName, args);
  }

  /**
  * Implementation of <code>ActiveXDispatchable</code> interface
  * @see ActiveXDispatchable
  */
  @Override
  public Variant axInvoke(String methodName,
                          int dispatchType,
                          boolean voidReturn,
                          Vector args)
                          throws ActiveXException 
  {
    if (axProxy == null) { 
      throw new ActiveXMissingProxyException(this); 
    }
    return axDispatch.axInvoke(methodName, dispatchType, voidReturn, args);
  }

  /**
  * Implementation of <code>ActiveXDispatchable</code> interface
  * @see ActiveXDispatchable
  */
  @Override
  public Variant axInvoke(int memid,
                          Vector args) 
                          throws ActiveXException
  { 
    if (axProxy == null) { 
      throw new ActiveXMissingProxyException(this); 
    }
    return axDispatch.axInvoke(memid, args);
   }

  /**
  * Implementation of <code>ActiveXDispatchable</code> interface
  * @see ActiveXDispatchable
  */
  @Override
  public Variant axInvoke(int memid,
                          int dispatchType,
                          boolean voidReturn,
                          Vector args)
                          throws ActiveXException 
  {
    if (axProxy == null) { 
      throw new ActiveXMissingProxyException(this); 
    }
    return axDispatch.axInvoke(memid, dispatchType, voidReturn, args);
  }

  /**
  * Implementation of <code>ActiveXDispatchable</code> interface
  * @see ActiveXDispatchable
  */
  @Override
  public Variant getAxProperty(String propertyName)
                                  throws ActiveXException
  {
    if (axProxy == null) { 
      throw new ActiveXMissingProxyException(this); 
    }
    return axDispatch.getAxProperty(propertyName);
  }

  /**
  * Implementation of <code>ActiveXDispatchable</code> interface
  * @see ActiveXDispatchable
  */
  @Override
  public Variant getAxProperty(int memid)
                                  throws ActiveXException 
  {
    if (axProxy == null) { 
      throw new ActiveXMissingProxyException(this); 
    }
    return axDispatch.getAxProperty(memid);
  }

  /**
  * Implementation of <code>ActiveXDispatchable</code> interface
  * @see ActiveXDispatchable
  */
  @Override
  public void setAxProperty(String propertyName,
                            Variant newValue)
                            throws ActiveXException 
  {
    if (axProxy == null) { 
      throw new ActiveXMissingProxyException(this); 
    }
    axDispatch.setAxProperty(propertyName, newValue);
  }

  /**
  * Implementation of <code>ActiveXDispatchable</code> interface
  * @see ActiveXDispatchable
  */
  @Override
  public void setAxProperty(int memid,
                            Variant newValue)
                            throws ActiveXException
  {
    if (axProxy == null) { 
      throw new ActiveXMissingProxyException(this); 
    }
    axDispatch.setAxProperty(memid, newValue);
  }

  //******************** Implementation of ActiveXComponent ****

  /**
  * Implementation of <code>ActiveXComponent</code> interface
  * @see ActiveXComponent
  */
  @Override
  public Guid getClassID () {
      return classID;
  }

  /**
  * Implementation of <code>ActiveXComponent</code> interface
  * @see ActiveXComponent
  */
  @Override
  public void setClassID (Guid classID) throws PropertyVetoException {
     throw new PropertyVetoException("ClassID change disallowed",
                    new PropertyChangeEvent(this, "classID",
                                            this.classID, classID));  
  
  }       

  /**
  * Implementation of <code>ActiveXComponent</code> interface
  * @see ActiveXComponent
  */
  @Override
  public boolean getActivateOnLoad() {
     return activateOnLoad;
  }

  /**
  * Implementation of <code>ActiveXComponent</code> interface
  * @see ActiveXComponent
  */
  @Override
  public void setActivateOnLoad(boolean activateOnLoad) {
     this.activateOnLoad = activateOnLoad;
  }

  /**
  * Implementation of <code>ActiveXComponent</code> interface
  * @see ActiveXComponent
  */
  @Override
  public void proxyActivated() {
    if (axProxy != null) {  
      dispatchPointer = axProxy.getDispatchPointer();
      axDispatch = new ActiveXDispatchableImpl(dispatchPointer, axProxy);
    }
  }

  /**
  * Implementation of <code>ActiveXComponent</code> interface
  * @see ActiveXComponent
  */
  @Override
  public void activate() throws ActiveXException {
    Dimension size = getSize();
    int width = size.width;
    int height = size.height;

    if (axProxy == null) {
      throw new ActiveXMissingProxyException(this);
    } else {               
      dispatchPointer = axProxy.getDispatchPointer();
      
      axDispatch = new ActiveXDispatchableImpl(dispatchPointer,axProxy);
     
      if (dispatchPointer == AX_NO_DISPATCH) {
        message(AX_PROGRESS, "failed to get dispatchPointer: " + this);  
      } else {
	message(AX_PROGRESS, "got dispatchPointer: " + this + " = " + dispatchPointer);
      }
      axProxy.activate(0, 0, height, width);
    }
  }

  /**
  * Implementation of <code>ActiveXComponent</code> interface
  *
  * This method is provided to work around a problem with ActiveX controls that
  * allocate a large amount of resources. Since the size of the Java wrapper
  * object for a control is small, Java may not detect the need to garbage
  * collect after a wrapper object is no longer referenced and has allocated
  * a large amount of resources.
  *
  * @see ActiveXComponent
  */
  @Override
  public void delete () throws ActiveXException {
    if (axProxy == null)
      return;

     message(AX_PROGRESS, "ActiveXDefaultComponentImpl.delete calling" +
       "ActiveXProxy.delete");

     axProxy.delete(); /* Should stop the proxy thread. This is not safe code
                         because this proxy could be referenced by more than
                         one object. This problem is that the axProxy is
                         running in thread so a finalizer will no fire
                         after we dereference all of the proxies. It should be
                         the Ole request queue running in a thread and the
                         finalizer of ActiveXProxy should shut down the queue.
                       */
    /* note: the following is the desired code, the above code is a work
       around our design limitation. */
    /* De-reference the proxy and ask the user to garbage
       collect. If we have the last reference
       to the proxy then the proxy's finalizer will run and
       delete the ActiveX object during garbage collection. */
    axProxy = null;
  }

  //******************** Implementation of ActiveXDisplayComponent ****

  /**
  * Implementation of <code>ActiveXDisplayComponent</code> interface
  * @see ActiveXDisplayComponent
  */
  @Override
  public void setFrozen(boolean freeze) {
      frozen = freeze;
      if (frozen == false)
        repaint();
  }

  /* Note - may want to call IViewObject::freeze()  for this and still 
  * allow repaints. When QueryInterface is functional on all emitted 
  * controls, users will be able to do this for themselves.
  */

  /**
  * Implementation of <code>ActiveXDisplayComponent</code> interface
  * @see ActiveXDisplayComponent
  */
  @Override
  public boolean getFrozen() {
      return frozen;
  }

  /**
  * Implementation of <code>ActiveXDisplayComponent</code> interface
  * @see ActiveXDisplayComponent
  */
  @Override
  public void repaint() {
    if (! frozen)
      super.repaint();
  }

  //******************** UI related methods ******************

  /** @undocumented */
  @Override
  public Dimension getPreferredSize() 
  {
    return new Dimension(PREFERRED_WIDTH, PREFERRED_HEIGHT);
  }

  /** @undocumented */
  @Override
  public Dimension getMinimumSize() 
  {
    return new Dimension(MIN_WIDTH, MIN_HEIGHT);
  }

  /** @undocumented */
  @Override
  public Dimension getMaximumSize() 
  {
    return new Dimension(MAX_WIDTH, MAX_HEIGHT);
  }

  /** @undocumented */
  @Override
  public void setSize(int width, int height) {
    super.setSize(width, height);
  }

  /** @undocumented */
  @Override
  public void setSize(Dimension dimension) {
    super.setSize(dimension);
  }

  /** @undocumented */
  public void makeBig() {
    setSize(500, 400);
  }

  /** @undocumented */
  @Override
  public void setBounds (int x, int y, int width, int height) {
    message(AX_DATA_DUMPS, "Setting Bounds");
    super.setBounds(x, y, width, height);
    setClientBounds(0,0,width,height);
  }

  /** @undocumented */
  private void setClientBounds(int x, int y, int width, int height) {
    if (axProxy != null)
      axProxy.resize(y, x, height, width);
   }

  /** @undocumented */
  @Override
  public void paint (Graphics g) {
    Dimension sz;
    
    if (isAlive())
      g.setColor(getBackground());
    else g.setColor(Color.black);
    sz = getSize();
    g.fillRect(0, 0, sz.width, sz.height);
    
    Hwnd hWnd2 = new Hwnd(this);
    if (axProxy != null) {
	if (! hWnd2.equals(hWnd)) 
      {
        hWnd = hWnd2;
        axProxy.setHWnd(hWnd);
      }
    }

    render(0, 0);
  }

  /** @undocumented */
  public void paint (Graphics g, Color outlineColor) {
    paint(g);
  }

  /** @undocumented */
  protected void render (int x, int y) {
    if (hWnd != null) {
      int x0, x1, y0, y1;

      Dimension size = getSize();
   
      int width = size.width;
      int height = size.height;

      x0 = x;
      y0 = y;

      x1 = x0 + width;
      y1 = y0 + height;

      if (axProxy == null) {
	message(AX_DATA_DUMPS, "Not rendering object " + this +
		" -> in Proxy -> " + axProxy);
	return;
      }
      message(AX_DATA_DUMPS, "Rendering object " + this +
	      " -> in Proxy -> " + axProxy);
      axProxy.render(x0, y0, x1, y1);
    }
  }

  /** @undocumented */
  public void update () {
    if (axProxy != null) {
      message(AX_DATA_DUMPS,
	      "ActiveXComponent updating");
      axProxy.update();
    } else
      message(AX_MORE_DETAIL,
	      "Not updating because there's no object");
  }

  /** @undocumented */
  @Override
  protected void finalize() throws Throwable {
      message(AX_PROGRESS, "ActiveXDefaultComponentImpl.finalize has " +
        "been called");
      if (! usesGivenProxy)
        delete();
  }

  /** Use Gensym's tracing mechanism to send a trace message at
  * a specified trace level.  The possible trace levels are defined
  * by <code>ActiveXTraceLevels</code>
  * @see ActiveXTraceLevels
  */
  protected void message(int d, String m) {
    com.gensym.com.NativeMethodBroker.traceln(d, m);
  }

  /** Use Gensym's tracing mechanism to send a trace message at
  * a default trace level.
  */
  protected void message(String m) {
    com.gensym.com.NativeMethodBroker.traceln(m);
  }

  /** @undocumented */
  public boolean isAlive () {
    return ((axProxy != null) && (axProxy.isAlive()));
  }
  
  /** @undocumented */
  protected void addActiveXEventListener(ActiveXEventListener l,
                                         Class listenerClass)
    throws ActiveXException
  {
     ActiveXEventSetDescriptor eventSet;
     eventSet = findEventSetDescriptor(l, listenerClass);

     if (axProxy == null || (dispatchPointer == AX_NO_DISPATCH))
       throw new ActiveXMissingProxyException(this);

     axProxy.addActiveXEventListener(dispatchPointer, l, eventSet);
  }

  /** @undocumented */
  protected void removeActiveXEventListener(ActiveXEventListener l,
                                            Class listenerClass)
    throws ActiveXException
  {
    ActiveXEventSetDescriptor eventSet;
    eventSet = findEventSetDescriptor(l, listenerClass);

    if (axProxy == null || (dispatchPointer == AX_NO_DISPATCH))
       throw new ActiveXMissingProxyException(this);

    axProxy.removeActiveXEventListener(dispatchPointer, l, eventSet);
  }

  private ActiveXEventSetDescriptor findEventSetDescriptor
    (ActiveXEventListener l, 
     Class beanInfoClass) throws ActiveXException 
  {
    ActiveXEventSetDescriptor set = null;

    try {
      BeanInfo beanInfo = (BeanInfo) beanInfoClass.newInstance();

      EventSetDescriptor[] eventSets =
          beanInfo.getEventSetDescriptors();

      Class listenerType;
      Class listenerClass = l.getClass();

      for(int i = 0; i < eventSets.length; i++)
      {
        listenerType = eventSets[i].getListenerType();
        if (listenerType.isAssignableFrom(listenerClass)) {
            set =  (ActiveXEventSetDescriptor) eventSets[i];
            break;
        }
      }
    }
    catch (Exception e) {      
        e.printStackTrace();
    }     
    if (set == null) {
      throw new ActiveXException("Attempt to register invalid event interface");
    }

    return set;
  }

  /** Return a string that represents this object.
  */
  @Override
  public String toString() {
    Rectangle bounds = getBounds();
    int top = bounds.y;
    int left = bounds.x;
    int width = bounds.width;
    int height = bounds.height;

    if (hWnd == null) {
      return("an InsertableActiveXObject (package com.gensym.com), " + 
	     ((classID == null) ? "ID = null " : classID.toString()) +
	     ", containing " + axProxy +
	     " of size  [" + width + ", " + height + "]" +
             super.toString());
    } else {
      return("an InsertableActiveXObject (package com.gensym.com), " + 
	     ((classID == null) ? "ID = null" : classID.toString()) +
	     ", containing " + axProxy +
	     ", at (" + left + ", " + top + "),  " +
	     "of size  [" + width + ", " + height + "]" +
             super.toString());
    }
  }
}
