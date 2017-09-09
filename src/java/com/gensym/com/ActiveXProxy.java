/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.ActiveXProxy.java
 *
 *  Authors: John Valente, Allan Scott
 */
package com.gensym.com;

import java.lang.InterruptedException;

import java.io.Serializable;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.File;
import java.io.IOException;
import java.util.Vector;
import java.util.Hashtable;
import java.util.Enumeration;
import java.lang.reflect.Method;
import java.lang.reflect.Constructor;
import java.awt.Dimension;

/**
 * <p>
 * The class <code>ActiveXProxy</code> runs the thread for a Java class 
 * which is based on an ActiveX component.  All of the calls which manipulate 
 * an ActiveX component as part of a visual container, and all of the automation
 * calls, go through this class.<p>
 * <p>
 * This package is heavily dependent on native code (JavaContainer.dll).
 * In the context of this class, a "client site" is an integer which
 * is the address of an object created in the native code.  Most of 
 * the information about the object is kept in C.  The client site is
 * the one piece of information needed to refer to the object from
 * Java. 
 * <p>
 * A single ActiveXProxy can be directly associated with only one Java Class which
 * implements <code>ActiveXComponent</code>.  However multiple instances of
 * Java Classes that implement <code>ActiveXDispatchable</code> can use the
 * same ActiveXProxy using different dispatch pointers.  A dispatch pointer
 * in this case is an integer that represents an automation interface (typically
 * IDispatch) that can be manipulated in C.
 */
public class ActiveXProxy implements ActiveXTraceLevels, 
                                     ActiveXRuntimeConstants,
                                     Runnable, Serializable                                     
{ 

  static final long serialVersionUID = -2068643956264469978L;

  static final byte OTR_ERROR  = -1;
  static final byte DIE        =  0;
  static final byte INSERT     =  1;
  static final byte UPDATE     =  2;
  static final byte ACTIVATE   =  3;
  static final byte RENDER     =  4;
  static final byte INVOKE     =  5; 
  static final byte DELETE     =  6;
  static final byte SAVE       =  7;
  static final byte COPY       =  8;
  static final byte RESIZE     =  9;
  static final byte CHECK_CAST = 10; 
  static final byte GET_CLSID  = 11; 
  static final byte EVENT_LISTEN  = 12;
  static final byte EVENT  = 13;
  static final byte MARSHAL_INTERFACE  = 14;
  static final byte GET_MARSHALED_INTERFACE  = 15;
  

  private static final byte UPDATE_HEARTBEAT =  5; 
  private static final byte POLL_FOR_RESULT_HEARTBEAT = 10; 
  private static final boolean traceTime = false;

  private class OleThreadRequest implements Serializable
  { 
    byte messageType;
    int top, left, bottom, right;
    int dispatchPointer = AX_NO_DISPATCH;
    Guid classID  = null;
    int memid = 0;
    int dispatchType = AX_INVOKE;
    boolean voidReturn = false;
    Variant newValue = null;
    Variant returnValue = null;
    boolean returnCheck = false;
    Guid returnClsid = null;
    Vector args = null;
    String name = null;
    boolean dispatchByName = false;
    boolean finished = false;
    boolean add;
    Variant[] eventArguments;
    String eventName;
    int dispid;
    ActiveXException exception = null;

    OleThreadRequest (byte messageType,
                      int top, int left,
                      int bottom, int right) {
      this.messageType = messageType;
      this.top = top;
      this.left = left;
      this.bottom = bottom;
      this.right = right;
    }

    OleThreadRequest (byte messageType, 
                      int dispatchPointer) {
      this.messageType = messageType;
      this.dispatchPointer = dispatchPointer;
    }


    OleThreadRequest (byte messageType, 
                      int dispatchPointer, int memid,
                      int dispatchType,
                      boolean voidReturn,
                      Vector args) {
      this.messageType = messageType;
      this.dispatchPointer = dispatchPointer;
      this.memid = memid;
      this.dispatchType = dispatchType;
      this.voidReturn = voidReturn;
      this.args = args;
    }

    OleThreadRequest (byte messageType, 
                      int dispatchPointer, String name,
                      int dispatchType,
                      boolean voidReturn,
                      Vector args) {
      this.messageType = messageType;
      this.dispatchPointer = dispatchPointer;
      this.name = name;
      this.dispatchType = dispatchType;
      this.voidReturn = voidReturn;
      dispatchByName = true;
      memid = 0;
      this.args = args;
    }

    OleThreadRequest (byte messageType, 
      int dispatchPointer, Guid classID) {
        this.messageType = messageType;
        this.dispatchPointer = dispatchPointer;
        this.classID = classID;  
    } 


    OleThreadRequest (byte messageType, 
                      int iunknownPointer, 
                      Guid classID,
                      boolean add) 
    {
        this.messageType = messageType;
        this.dispatchPointer = iunknownPointer;
        this.classID = classID;
        this.add = add;
    } 

    OleThreadRequest (byte messageType, 
                      Guid classID,
                      int dispid,
                      String eventName,
                      Variant[] eventArguments) 
    {
        this.messageType = messageType;
        this.classID = classID;
        this.dispid = dispid;
        this.eventName = eventName;
        this.eventArguments = eventArguments;
    } 

    OleThreadRequest () {
      this.messageType = OTR_ERROR;
      this.top = 0;
      this.left = 0;
      this.bottom = 0;
      this.right = 0;
    }

    OleThreadRequest(byte messageType, String name) {
      this.messageType = messageType;
      this.name = name;
    }

    
    @Override
    public String toString () {
      switch (messageType) {
      case OTR_ERROR:
        return("OTR_ERROR");
      case INSERT:
        return("INSERT");
      case UPDATE:
        return("UPDATE");
      case ACTIVATE:
        return("ACTIVATE: (" + left + ", " + top + ") - (" + right + ", " +
               bottom + ")");
      case RESIZE:
        return("RESIZE: (" + left + ", " + top + ") - (" + right + ", " +
               bottom + ")");
      case RENDER:
        return("RENDER: (" + left + ", " + top + ") - (" + right + ", " +
               bottom + ")");
      case INVOKE:
        return("INVOKE");
      case DELETE:
        return("DELETE");
      case COPY:
        return("COPY: (" + left + ", " + top + ") - (" + right + ", " +
               bottom + ")");
      case SAVE:
        return("SAVE: (" + name + ")");
      case CHECK_CAST:
        return("CHECK_CAST");
      case GET_CLSID:
        return("GET_CLSID");
      case EVENT:
        return "EVENT";
      case EVENT_LISTEN:
        return "EVENT_LISTEN";
      case MARSHAL_INTERFACE:
        return "MARSHAL";
      case GET_MARSHALED_INTERFACE:
        return "GET_MARSHALED_INTERFACE"; 
      default:
        return("Big time problem with OleThreadRequest " + messageType);
      }
    }
  }


  private class ThreadRequestQueue implements Serializable
  {
    OleThreadRequest current;
    ThreadRequestQueue next;

    ThreadRequestQueue () {
      current = null;
      next = null;
    }

    ThreadRequestQueue (OleThreadRequest newRequest) {
      current = newRequest;
      next = null;
    }

    void insertNonEmpty (OleThreadRequest newRequest) {
      if (next == null)
        next = new ThreadRequestQueue(newRequest);
      else
        next.insertNonEmpty(newRequest);
    }

    void add (OleThreadRequest newRequest) {
      if (current == null)
        current = newRequest;
      else 
        insertNonEmpty(newRequest);
    }

    OleThreadRequest pop () {
      OleThreadRequest answer;

      if (current == null) {
        // Could throw an exception here, but why bother?
        return null;
      } else if (next == null) {
        answer = current;
        current = null;
        return answer;
      } else {
        answer = current;
        current = next.current;
        next = next.next;
        return answer;
      }
    }

    boolean isEmpty() {
      return (current == null);
    }

    @Override
    public String toString () {
      String answer;
      ThreadRequestQueue iterator;

      answer = "Queue:\n";
      for (iterator = this; iterator != null; iterator = iterator.next)
        answer += ("  " + iterator.current.toString());
      return answer;
    }

  }

  private static final String fatalErrorMessage = 
  "ERROR: Unsatisfied Link Error.  ActiveX functionality will not be " +
  "present.  You should shut down this Java VM and check your environment " +
  "for JavaContainer.dll, and check that it is in your PATH.  Attempts to " +
  "use ActiveX features during this session may be unpredictable.";


  private transient int clientSite = AX_NO_CLIENT_SITE;
  private transient int hWndHandle = Hwnd.NO_HWND;
  private ThreadRequestQueue messagesWaiting = null;
  private OleThreadRequest notifyMessage = null;
  private ActiveXComponent wrapper = null;
  private Guid classID = null;
  private ActiveXModes modes = null;
  private Hashtable listeners = new Hashtable();

  private transient Thread daemon = null;

  private transient boolean loaded = false;
  private transient String fileLoadedFrom = null;;
  private int saveId = 0;   

  private native static void start_up();
  private native static void update_stuff();
  private native static void shut_down(int clientSite);
  private native static int insert_object_from_clsid_with_license(Guid clsid, int hWnd, String license);
  private native static int instantiate_uninsertable_object_with_license(Guid clsid, String license);
  private native static int insert_object_from_file(String fileName);
  private native int marshal_interface(int clientSite, int dispatchPointer);
  private native int get_marshaled_interface(int clientSite, int streamPointer);

  private native Variant com_Invoke(int clientSite, int dispatchPointer,
                                    int memid, int dispatchType, boolean voidReturn, Vector args)
                                    throws ActiveXException;

  private native Variant com_Invoke_by_name(int clientSite, int dispatchPointer,
                                            String methodName, int dispatchType, boolean voidReturn, Vector args)
                                            throws ActiveXException;

  private native static void delete_object(int clientSite);
  private native static boolean activate_object(int clientSite, int hWnd,
                                                int top, int left, 
                                                int bottom, int right, boolean inPlace);
  private native static void render_object(int clientSite, int hWnd,
                                           int top, int left, int bottom, int right);
  private native static void resize_object(int clientSite,
                                           int top, int left, int bottom, int right);
  private native static void copy_object(int clientSite, int top, int left, 
                                         int bottom, int right);
  /* Saves the given client site. */
  private native static String save_object(int clientSite, String componentFileName);
  /* Loads a new client site from persistent store. */
  private native static int load_object(String componentFileName);
  /* Determines whether the activeX object is open in the window */
  private native static boolean is_open_in_window(int clientSite);

  private native static boolean check_cast(int clientSite, int dispatchPointer, Guid classID);
  private native static Guid get_clsid(int clientSite, int dispatchPointer);


  /** Creates a thread which will run a new Active X control.  The
   *  control will draw itself into the Hwnd given, and will be
   *  further contained inside of the wrapper given.  How the object
   *  is created, located, and activated is controlled by the
   *  ActiveXModes argument, which includes the class id.
   *
   *  @see com.gensym.com.ActiveXModes 
   *  @see com.gensym.com.ActiveXComponent
   */
  public ActiveXProxy (Hwnd hWnd, ActiveXModes modes,
                       ActiveXComponent wrapper)
                       throws ActiveXException 
  {
    boolean libraryIsLoaded;

    classID = modes.getClassID();
    message(AX_MORE_DETAIL, "Creating ActiveXProxy: hwnd = " + hWnd +
            ", classid = " + classID + ", wrapper = " + wrapper);
    

    if (hWnd != null) {
        hWndHandle = hWnd.handleToPeer;
    }

    if (wrapper == null) {
      throw new ActiveXException("An ActiveXProxy cannot function without a valid wrapper");
    }
    this.wrapper = wrapper;
    if ((classID == null) || (classID.isNullGuid())) {
      throw new ActiveXException("An ActiveXProxy cannot function without a valid class ID");
    }

    libraryIsLoaded = NativeMethodBroker.loadLibrary();

    if (!libraryIsLoaded) {
      throw new ActiveXException("Could not locate JavaContainer dynamic library");
    }

    this.modes = modes;
    messagesWaiting = new ThreadRequestQueue();
    message(AX_PROGRESS, "created ActiveXProxy " + this + " for wrapper " +
            wrapper);
    startDaemon();
  }


  /** Creates an ActiveXProxy of the given class ID, with the
   *  default ActiveXModes.
   */
  public ActiveXProxy (Hwnd hWnd, Guid classID, ActiveXComponent wrapper) 
    throws ActiveXException
  {
    this(hWnd, new ActiveXModes(classID), // default modes
         wrapper);
  }


  /** Will run the thread if everything is ok.  If there is no
   *  corresponding server that is up and running and ready to
   *  serve, this thread will not run.
   */
  @Override
  public void run () {
      boolean activateStatus;

      startUp();        
      if (loaded) {
        File fi =  new File(fileLoadedFrom);
        clientSite = load_object(fileLoadedFrom);
        message(AX_PROGRESS,"Client Site found: " + clientSite);
        if (! fi.delete()) {
          message(AX_ERROR,"Failed to delete temporary file: " + fileLoadedFrom);
        }
      } else { 
        clientSite = insertObjectFromActiveXModes(modes, hWndHandle);
      }
      if (clientSite == AX_NO_CLIENT_SITE) {
        // Just progress because the C code will handle communicating
        // this failure.
        message(AX_PROGRESS, "Error: client site was null");
        return;
      }
      NativeMethodBroker.registerProxy(clientSite, this);
      try {
        if((! loaded) || (wrapper.getActivateOnLoad()))
          wrapper.activate();
        if (loaded) {
          addAllActiveXListeners();
          restoreTransientEventSets(); 
        }
      }
      catch (ActiveXException e) 
      { 
        e.printStackTrace();
      }
      while (true) {
        long timeBefore = 0;
        long timeAfter;
        int counter = 0;
        if (messagesWaiting.isEmpty()) {
            try {
              // if (wrapper.isOpenInWindow) {
              // We should want to only call update_stuff when isOpenInWindow
              // is true.  However, the call to OnShowWindow, which the only
              // thing which changes the value of isOpenInWindow, obviously
              // must come before the control has shut down.  Therefore,
              // we can't immediately stop listening at that point.  Perhaps
              // it would work to continue to listen for a few seconds after
              // receiving the notification, or perhaps even not acting on
              // the notification for a few seconds.  Either of those seem
              // enormously hacky, however, so for now, every object will
              // just poll constantly.
              
              if (traceTime)
                timeBefore = System.currentTimeMillis();  
              update_stuff();
              
              Thread.sleep(UPDATE_HEARTBEAT);

              if (traceTime) {
                timeAfter = System.currentTimeMillis();
                System.out.println("Update and sleep took " + (timeAfter - timeBefore) +
                 "(millis)");
              }
            }  
            catch (InterruptedException e) {
              message(AX_ERROR, "INTERRUPTED EXCEPTION.  ");
              message(AX_DATA_DUMPS, "(This should never happen.)");
            }  
        }
        notifyMessage = messagesWaiting.pop();
        

        if (notifyMessage != null) {
          
          synchronized (notifyMessage) {   
            message(AX_PROGRESS, notifyMessage.toString());
            switch (notifyMessage.messageType) {
            case OTR_ERROR:
              message(AX_ERROR, "ERROR: thread was activated without an action.\n");
              return;
            case DELETE:
              try {
                removeAllActiveXListeners();
              }
              catch (ActiveXException e)
              {
              }
              deleteObject(clientSite);
              break; 
            case UPDATE:   
              update_stuff();
              break;
            case ACTIVATE:
              activateStatus =
                activate_object(clientSite, hWndHandle,
                notifyMessage.top, notifyMessage.left,
                notifyMessage.bottom, notifyMessage.right,
                false);
              if (activateStatus) {
                resize(notifyMessage.top, notifyMessage.left,
                  notifyMessage.bottom, notifyMessage.right);
              } else {
                message(AX_ERROR, "ERROR: unable to activate object.  Quitting thread.");
                return;
              }
              break;
            case RENDER:
              render_object(clientSite, hWndHandle,
                notifyMessage.top, notifyMessage.left,
                notifyMessage.bottom, notifyMessage.right);
              break;
            case RESIZE:
              resize_object(clientSite,
                notifyMessage.top, notifyMessage.left,
                notifyMessage.bottom, notifyMessage.right);
              break;
            case COPY:
              copy_object(clientSite, 
                notifyMessage.top, notifyMessage.left,
                notifyMessage.bottom, notifyMessage.right);
              break;
            case INVOKE:
              if (traceTime)
                timeBefore = System.currentTimeMillis();
              comInvokeWithinThread(notifyMessage);
              if (traceTime) {
                timeAfter = System.currentTimeMillis();
                System.out.println("Invoke within thread took " + (timeAfter - timeBefore) +
                 "(millis)");
              }
              break;
            case SAVE:
              notifyMessage.name = save_object(clientSite, notifyMessage.name);
              break;
            case CHECK_CAST:
              notifyMessage.returnCheck 
                = check_cast(clientSite,
                notifyMessage.dispatchPointer,
                notifyMessage.classID);
              break;
            case GET_CLSID:
              notifyMessage.returnClsid = 
                get_clsid(clientSite,
                      notifyMessage.dispatchPointer);
              break;
            case EVENT_LISTEN:
              event_listen(clientSite, 
                           notifyMessage.dispatchPointer, 
                           notifyMessage.classID,
                           notifyMessage.add);
              break;
            case EVENT:
              forwardActiveXEvent1(notifyMessage.classID,
                                   notifyMessage.dispid,
                                   notifyMessage.eventName,
                                   notifyMessage.eventArguments);
              break;
            case MARSHAL_INTERFACE:
              notifyMessage.dispatchPointer = 
                marshal_interface(clientSite, notifyMessage.dispatchPointer);
              break;
            case GET_MARSHALED_INTERFACE:
              notifyMessage.dispatchPointer = get_marshaled_interface(clientSite, notifyMessage.dispatchPointer);
              break;
            default:
              message(AX_ERROR, "ERROR: unknown action:" + notifyMessage);
            } 
            notifyMessage.finished = true;
            notifyMessage.notifyAll();
            if ((notifyMessage.messageType == DELETE) ||
                (notifyMessage.messageType == DIE))
                {
                    message(AX_PROGRESS, "*** STOPING ***");
                    return;
                }
            
          }
        }
      }
  }


  /** Returns the client site.  The client site is an integer
   *  which is the address of a COMOBJ structure in C.  We 
   *  never send any other data from that structure into Java.
   *  All of the processing goes on in C, and all we need to
   *  do in C to find out what object Java is referring to is
   *  to cast the integer:
   *  <code>(PCOMOBJ) client_site_from_java</code>
   */
  public int getClientSite () {
    return clientSite;
  }

  /** Returns true if the ActiveXProxy is alive and running. */
  public boolean isAlive () {
    return (daemon != null) && daemon.isAlive();
  }

  /** Asks the control to activate itself.  Called by default when the
   *  thread is started.  Editing can only be done when the object is
   *  activated.
   */
  public void activate (int top, int left, int bottom, int right) {
    if ((wrapper instanceof ActiveXComponent) &&
        (clientSite == AX_NO_CLIENT_SITE)) {
        message(AX_PROGRESS, "Not activating due to null client site: " + clientSite);
    } else {
      synchronized (this) {
        messagesWaiting.add
          (new OleThreadRequest(ACTIVATE,
                                top, left, bottom, right));
        message(AX_MORE_DETAIL, messagesWaiting.toString());
        notify();
      }
    }
  }

  /** Resize the underlying ActiveX component using these
  * co-ordinates
  */
  public void resize (int top, int left, int bottom, int right) {
    if ((wrapper instanceof ActiveXComponent) &&
        (clientSite == AX_NO_CLIENT_SITE)) {
          
    } else {
      synchronized (this) {
        messagesWaiting.add
          (new OleThreadRequest(RESIZE,
                                top, left, bottom, right));
        message(AX_MORE_DETAIL, messagesWaiting.toString());
        notify();
      }
    }
  }


  /** Asks the control to update itself.  Updates are done
   *  automatically, so this should never be necessary.
   */
  public void update () {
    synchronized (this) {
      messagesWaiting.add
        (new OleThreadRequest(UPDATE,
                              0, 0, 0, 0));
      notify();
    }
  }

  /** Tells the control where to draw itself.  This information
   *  is set up by the constructor if the ActiveXProxy is 
   *  instantiated "normally", but in the case of deserializing,
   *  it needs to be created anew.
   * 
   *  @see com.gensym.com.Hwnd
   */
  public void setHWnd (Hwnd hWnd) {
    hWndHandle = hWnd.handleToPeer;
  }

  /** Returns true if this instance was created by deserialization.
   */
  public boolean hasBeenLoaded () {
    return loaded;
  }

  /** Asks the control to draw itself in the dimensions specified.
   *  The control draws directly onto the window, bypassing the
   *  AWT entirely.
   */
  public void render (int left, int top, int right, int bottom) {
    
    if ((clientSite != AX_NO_CLIENT_SITE) || loaded) {
      synchronized (this) {
        messagesWaiting.add(new OleThreadRequest(RENDER,
                                                 top, left, bottom, right));
        notify();
      }
    }
  }

  /**
  * @undocumented
  */
  public void repaint() {
    ActiveXDisplayComponent axDisplay;
    if (wrapper instanceof ActiveXDisplayComponent) {
      axDisplay = (ActiveXDisplayComponent) wrapper;
      axDisplay.repaint();
    }
  }

  /**
  * @undocumented
  */
  int marshalInterface(int interfacePointer)
  {
    OleThreadRequest request;
    Thread current;  

    request = 
      new OleThreadRequest(MARSHAL_INTERFACE,
      interfacePointer);

    current = Thread.currentThread();
    
    if (current == daemon)
    {
      request.dispatchPointer = 
                marshal_interface(clientSite, notifyMessage.dispatchPointer);
    }

    else {
      synchronized (this)
      {
        messagesWaiting.add(request);
        notify();
      }
      while (!request.finished) {      
        synchronized(request) {
          try {
            request.wait(POLL_FOR_RESULT_HEARTBEAT);
          }
          catch (InterruptedException e) {          
          }
        }  
      }
    }
    return request.dispatchPointer;
  }

  /**
  * @undocumented
  */
  int getMarshaledInterface(int stream)
  {
    Thread current;  

    OleThreadRequest request = 
      new OleThreadRequest(GET_MARSHALED_INTERFACE,
      stream);

    current = Thread.currentThread();
    
    if (current == daemon)
    {
      request.dispatchPointer =
          get_marshaled_interface(clientSite, stream);
    }
    else {
      synchronized (this)
      {
        messagesWaiting.add(request);
        notify();
      }
      while (!request.finished) {      
        synchronized(request) {
          try {
            request.wait(POLL_FOR_RESULT_HEARTBEAT);
          }
          catch (InterruptedException e) {          
          }
        }  
      }
    }    
    return request.dispatchPointer; 
  }


  private transient Hashtable transientEventSets = new Hashtable();
  
  class PersistentEventLink implements Serializable {
    private String beaninfoName;
    private int eventSetID;

    public PersistentEventLink(String beaninfoName,
                     int eventSetID)
    {
        this.beaninfoName = beaninfoName;
        this.eventSetID = eventSetID;
    }

    public void restoreActiveXEventSetDescriptor()
    {
        Class beanInfoClass;
        ActiveXBeanInfo beanInfo;
        ActiveXEventSetDescriptor evt;

        try {
            beanInfoClass = Class.forName(beaninfoName);
            beanInfo = (ActiveXBeanInfo) beanInfoClass.newInstance();

            evt = beanInfo.getActiveXEventSetDescriptor(eventSetID);
            transientEventSets.put(this, evt);
        }
        catch (Exception e)
        {
          e.printStackTrace();
          System.out.println("Failed to restore a persistent link");
          return;
        }

    }
  }



  /**
  * @undocumented
  */
  public void forwardActiveXEvent(Guid iid,
                                  int dispid, 
                                  String eventName,
                                  Variant[]  arguments) 
  {
    OleThreadRequest request;
    
    request = new OleThreadRequest(EVENT,
      iid, dispid, eventName, arguments); 
        
    messagesWaiting.add(request);
   
  }

  public void forwardActiveXEvent1(Guid iid,
                                   int dispid, 
                                   String eventName,
                                   Variant[]  arguments) 
  {
    ActiveXEvent axEvent;
    Enumeration e;
    ActiveXEventListener l;
    ActiveXEventSetDescriptor eventSet;
    Method method;       
    Constructor construct;

    try {
      Hashtable interfaces = 
        (Hashtable) listeners.get(iid);
    
      if (interfaces == null)
        return;

      e = interfaces.keys();
      
      while( e.hasMoreElements()) {
        l  = (ActiveXEventListener) e.nextElement();

        //eventSet = (ActiveXEventSetDescriptor) interfaces.get(l);

        PersistentEventLink evt = (PersistentEventLink) interfaces.get(l);
        eventSet = (ActiveXEventSetDescriptor) transientEventSets.get(evt);
        
        try {
          method = eventSet.getListenerMethod(dispid);
          construct = eventSet.getEventConstructor();

          // The following cruft exists to deal with the wonderful problems introduced
          // by environments where the same classes can be loaded both from the 
          // system class loader and from a jar.  In single class-
          // loader environments this is not a problem to worry about.
          //
          // I would rather take the performance hit here than mess up the
          // ActiveXEventSet API by passing around ClassLoaders.
          //
          // I am willing to write the cruft because I know that this
          // situation will happen and I prefer to have the event mechanism
          // degrade smoothly rather than just fail.
          //
          // Note -  do not remove this code when Gensym's Component Editor has
          // been fixed - it is not going to be the first or the last
          // environment that has this problem.
          Class declaringClass = method.getDeclaringClass();
          Class listenerClass = l.getClass();


          if ((declaringClass == null) && (listenerClass != null))
          {
            // An odd case - this will only work if this class was loaded
            // by the system class loader
            Class newDeclaringClass = Class.forName(declaringClass.getName());
            String methodName = method.getName();      
            Class[] methodArgs = method.getParameterTypes();
            Class argType1 = methodArgs[0];
            Class eventType = Class.forName(argType1.getName());
            method = newDeclaringClass.getMethod(methodName,new Class[] {eventType}); 
            construct = eventType.getConstructor(new Class [] {
              Object.class,
                String.class,
                Variant[].class
            });                                      
          }
          else if ((declaringClass != null)
            &&
            (! declaringClass.isAssignableFrom(listenerClass)))
          {
            // This is the case that the Gensym Component Editor 
            // exercises
            ClassLoader listenerLoader =  listenerClass.getClassLoader();
            Class newDeclaringClass = listenerLoader.loadClass(declaringClass.getName());
            String methodName = method.getName();
            Class[] methodArgs = method.getParameterTypes();
            Class argType1 = methodArgs[0];
            Class eventType = listenerLoader.loadClass(argType1.getName());
            method = newDeclaringClass.getMethod(methodName,new Class[] {eventType}); 
            construct = eventType.getConstructor(new Class [] {
              Object.class,
                String.class,
                Variant[].class
            });                                      
          }      
          // End of Cruft

          // The happy and hopefully normal case
          axEvent = 
            (ActiveXEvent) construct.newInstance(
            new Object[] {(Object) wrapper,
            method.getName(), 
            arguments}
          ); 
            
          method.invoke(l,new Object[] { axEvent });
        }
        catch (Exception r)
        {
          r.printStackTrace();
        }
      }
    }
    catch (Throwable t)
    {
       t.printStackTrace();
    }

  }

  /**
  *
  */
  public void addActiveXEventListener(int iunknown,
                                      ActiveXEventListener l,
                                      ActiveXEventSetDescriptor eventSet)
                                      throws  ActiveXException
  {
    Class listenerType;
    Hashtable interfaces;
    Guid iid;

    iid = eventSet.getIID();

    listenerType = eventSet.getListenerType();

    if (! listenerType.isInstance(l))
    {
      throw new ActiveXException("Attempt to register Invalid Event Listener");
    }

    synchronized(listeners)
    {
      if (! listeners.containsKey(iid))
      {
        interfaces = new Hashtable();
        
        // Put a PersistentEventLink instead of the EventSet

        // interfaces.put(l,eventSet);
        int eventSetID = eventSet.getEventSetID();
        String beanInfoName = eventSet.getBeanInfoClassName();
        PersistentEventLink evt = 
          new PersistentEventLink(beanInfoName,
                                  eventSetID);
                                  
        interfaces.put(l,evt);
        transientEventSets.put(evt, eventSet);

        listeners.put(iid, interfaces);
        
        // Need to do the thread queue thing here
        addActiveXListener1(iunknown, iid);

      }
      else {
        interfaces = (Hashtable) listeners.get(iid);
        if (! interfaces.containsKey(l)) {
          int eventSetID = eventSet.getEventSetID();
          String beanInfoName = eventSet.getBeanInfoClassName();
          PersistentEventLink evt = 
          new PersistentEventLink(beanInfoName,
                                  eventSetID);                                  
          interfaces.put(l,evt);
          transientEventSets.put(evt, eventSet);
        } 
      }
    }
  }

  /* Do this at exit time I think - or before every save?
  */
  private void removeAllActiveXListeners()
                  throws ActiveXException
  {
     Hashtable interfaces;
     Enumeration e;
     Guid iid;
     
     e = listeners.keys();

     while(e.hasMoreElements())
     {
       iid = (Guid) e.nextElement();
       removeActiveXListener1(clientSite, iid);      
     }
  }


  /* Do this at load time
  */
  private void addAllActiveXListeners()
                throws ActiveXException
  {
    Enumeration e;
    Guid iid;
     
     e = listeners.keys();

     while(e.hasMoreElements())
     {
       iid = (Guid) e.nextElement();
       addActiveXListener1(getDispatchPointer(), iid);      
     }
  }

    /* Do this at load time to restore the ActiveXEventDescriptorSet
    * references - because ActiveXEventDescriptorSet is not Serializable.
    */
  private void restoreTransientEventSets()
                throws ActiveXException
  {
    Hashtable interfaces;
    Enumeration e, e2;
    PersistentEventLink p;
    ActiveXEventSetDescriptor eventSet;
    ActiveXEventListener l;

    e = listeners.elements();

     while(e.hasMoreElements())
     {
        interfaces = (Hashtable) e.nextElement();

        e2 = interfaces.keys();

        while(e2.hasMoreElements())
        {
          l = (ActiveXEventListener) e2.nextElement();

          p = (PersistentEventLink) interfaces.get(l);
          
          p.restoreActiveXEventSetDescriptor();

        }
     }    
  }


  private native static boolean event_listen(int clientSite,
                                             int iunknown,
                                             Guid iid,
                                             boolean add);

  private void addActiveXListener1(int iunknown, Guid iid)
    throws ActiveXException
  {
    if (clientSite == AX_NO_CLIENT_SITE)
      throw new ActiveXException("Client Site undefined");

    synchronized (this) {
        messagesWaiting.add
          (new OleThreadRequest(EVENT_LISTEN,
                                iunknown, iid, true));
        message(AX_MORE_DETAIL, messagesWaiting.toString());
        notify();
      }
  }
                                   

  public void removeActiveXEventListener(int iunknown, 
                                         ActiveXEventListener l,
                                         ActiveXEventSetDescriptor eventSet)
                      throws ActiveXException
  {
    Hashtable eventSets;
    Hashtable interfaces;
    Class listenerType;
    Guid iid;

    listenerType = eventSet.getListenerType();

    if (! listenerType.isInstance(l))
    {
      throw new ActiveXException("Attempt to register Invalid Event Listener");
    }

    iid = eventSet.getIID();

    synchronized(listeners)
    {
       if (! listeners.containsKey(iid)) 
        return;

       interfaces = (Hashtable) listeners.get(iid);

       if (! interfaces.containsKey(l))
         return;

       PersistentEventLink p = (PersistentEventLink) interfaces.get(l);
       transientEventSets.remove(p);
       interfaces.remove(l);

       if (interfaces.isEmpty())

         removeActiveXListener1(iunknown, iid);
    
    }
  }  

  private void removeActiveXListener1(int iunknown, Guid iid)
    throws ActiveXException
  {
    if (clientSite == AX_NO_CLIENT_SITE)
      throw new ActiveXException("Client Site undefined");

    synchronized (this) {
        messagesWaiting.add
          (new OleThreadRequest(EVENT_LISTEN,
                                iunknown, iid, false));
        message(AX_MORE_DETAIL, messagesWaiting.toString());
        notify();
      }
  }

  /** 
   * Set a simple property using the name of the property. This method
   * is a convenience for properties that can be set with one
   * argument.  The dipstach type used by this method is
   * ActiveXRuntimeConstants.AX_PROPERTYSET.
  */
  public void setAxProperty(int dispatchPointer,
                            int memid, Variant newValue) 
                          throws ActiveXException
  { 
    Vector v = new Vector();
    v.addElement(newValue);
    axInvoke(dispatchPointer,memid,ActiveXDispatchable.AX_PROPERTYSET,true,v);
  }

  /** Set a simple property using the memid of the property. This method
  * is a convenience for properties that can be set with one
  * argument.  The dipstach type used by this method is
  * ActiveXRuntimeConstants.AX_PROPERTYSET.
  *<p>
  * The memid integer can be derived by reading a type library.
  */
  public void setAxProperty(int dispatchPointer,
                             String propertyName, Variant newValue)
                            throws ActiveXException
  {
    Vector v = new Vector();
    v.addElement(newValue);
    axInvoke(dispatchPointer,propertyName,ActiveXDispatchable.AX_PROPERTYSET,true,v);
  }

  /** Get a simple property using the memid of the property. This method
  * is a convenience for properties that do not require any
  * arguments.  The dipstach type used by this method is
  * ActiveXRuntimeConstants.AX_PROPERTYGET.
  * <p>
  * The memid integer can be derived by reading a type library.
  */
  public Variant getAxProperty(int dispatchPointer, int memid)
                          throws ActiveXException
  {
    return axInvoke(dispatchPointer,memid,ActiveXDispatchable.AX_PROPERTYGET,
                     false,(Vector) null);
  }
  
  
  /** Set a simple property using the name of the property. This method
  * is a convenience for properties that can be set with one
  * argument.  The dipstach type used by this method is
  * ActiveXRuntimeConstants.AX_PROPERTYSET.
  */
  public Variant getAxProperty(int dispatchPointer, String propertyName)
                                throws ActiveXException
  {
    return axInvoke(dispatchPointer,propertyName,ActiveXDispatchable.AX_PROPERTYGET,
                     false,(Vector) null);
  }

  /** Invoke a method using a memid integer,
  * The dispatch type used will be ActiveXRuntimeConstants.AX_INVOKE.
  *<p>
  * The memid integer can be derived by reading a type library.
  */
  public Variant axInvoke(int dispatchPointer, int memid, 
                           boolean voidReturn, Vector args)
                           throws ActiveXException
  {
    return axInvoke(dispatchPointer, memid, AX_INVOKE, voidReturn, args);
  }

  /** Invoke a method using the name of the method
  * The dispatch type used will be ActiveXRuntimeConstants.AX_INVOKE.
  *<p>
  */
  public Variant axInvoke(int dispatchPointer, String name, 
                           boolean voidReturn, Vector args)
                         throws ActiveXException
  {
    return axInvoke(dispatchPointer, name, AX_INVOKE, voidReturn, args);
  }

  /** Invoke a method or property using its memid. and specifying 
  * the type of dispatch to use, whether the method is expected 
  * to return nothing, and passing in the required arguments in
  * a Vector.
  *<p>
  * The type of dispatch to use is specified by an integer flag. 
  * The available dispatch types are specified by the following
  * final constants:
  * <ul>
  * <li> ActiveXRuntimeConstants.AX_INVOKE
  * <li> ActiveXRuntimeConstants.AX_PROPERTYGET
  * <li> ActiveXRuntimeConstants.AX_PROPERTYSET
  * </ul>
  * The voidReturn flag allows the ActiveXProxy to optimize how the
  * automation call is made. 
  *<p>
  * The memid integer can be derived by reading a type library.
  */
  public Variant axInvoke(int dispatchPointer, int memid, int dispatchType, 
                           boolean voidReturn, Vector args)
                           throws ActiveXException
  {
    OleThreadRequest threadRequest;
    Thread current;  

    long timeBefore = 0;
    long timeAfter;
    if (traceTime)
      timeBefore = System.currentTimeMillis();
   
    threadRequest = new OleThreadRequest
        (INVOKE, dispatchPointer, memid, dispatchType, voidReturn, args);

    current = Thread.currentThread();

    if (current == daemon) {
      comInvokeWithinThread(threadRequest);  
    }
    else {
      synchronized (this) { 
        messagesWaiting.add(threadRequest);
        notify();
      }
      while (!threadRequest.finished) {      
        synchronized(threadRequest) {
          try {
            threadRequest.wait(POLL_FOR_RESULT_HEARTBEAT);
          }
          catch (InterruptedException e) {          
          }
        }  
      }
    }

    if (traceTime) {
      timeAfter = System.currentTimeMillis();
      System.out.println("It took " + (timeAfter - timeBefore) + " (millis) "
        + " to  dispatch with voidReturn = " +voidReturn + " and args = " + args);
    }

    if (threadRequest.exception != null)
      throw threadRequest.exception;

    if (threadRequest.returnValue == null) {
      return new Variant();
    } else {
      return threadRequest.returnValue;
    }
  }

  /** Invokes a method with the specified name through the IDispatch
   *  interface with the address given.
   */
  public Variant axInvoke(int dispatchPointer, String name, int dispatchType, 
                             boolean voidReturn, Vector args)
                           throws ActiveXException
   {
    Thread current;  
    OleThreadRequest threadRequest;
    
    current = Thread.currentThread();

    threadRequest = new OleThreadRequest
        (INVOKE, dispatchPointer, name, dispatchType, voidReturn, args);

    if (current == daemon)
    {
      comInvokeWithinThread(threadRequest);
    }
    else {
    synchronized (this) {    
       messagesWaiting.add(threadRequest);
       notify();
      }
      while (!threadRequest.finished) {
        synchronized(threadRequest) {
          try {
            threadRequest.wait(POLL_FOR_RESULT_HEARTBEAT);
          }
          catch (InterruptedException e) {

          }
        }
      }
    }

    if (threadRequest.exception != null)
      throw threadRequest.exception;

    if (threadRequest.returnValue == null) {
      return new Variant();
    } else {
      return threadRequest.returnValue;
    }
  }

  /** Given a dispatch pointer that is managed by this ActiveXProxy
  * and a classID check to see whether it is possible to cast this
  * dispatch pointer into one described by the classID.
  */
  public boolean checkCast(int dispatchPointer, Guid classID) 
  {
    OleThreadRequest threadRequest;
    Thread current;

    threadRequest = new OleThreadRequest
           (CHECK_CAST, dispatchPointer, classID);

    current = Thread.currentThread();

    if (current == daemon)
    {
      notifyMessage.returnCheck 
                = check_cast(clientSite,
                notifyMessage.dispatchPointer,
                notifyMessage.classID);
    }
    else {
      synchronized (this) {
         
         messagesWaiting.add(threadRequest);
         notify();
     }
     while (!threadRequest.finished) {
       synchronized(threadRequest) {
         try {
           threadRequest.wait(POLL_FOR_RESULT_HEARTBEAT);
         }
         catch (InterruptedException e) {
           
         }
       }
     }
    }
    return threadRequest.returnCheck;
  }

  /** Given a dispatch pointer that is managed by this ActiveXProxy
  * and return the classID of the interface that it represents
  */
  public Guid getClassID(int dispatchPointer) 
  {
    OleThreadRequest threadRequest;
    Thread current;

    threadRequest = new OleThreadRequest
	(GET_CLSID, dispatchPointer);
      
    current = Thread.currentThread();

    if (current == daemon)
    {
      notifyMessage.returnClsid = 
                get_clsid(clientSite,
                      notifyMessage.dispatchPointer);
    }
    else
    {
      synchronized (this) {
        threadRequest = new OleThreadRequest
          (GET_CLSID, dispatchPointer);
        messagesWaiting.add(threadRequest);
        notify();
      }
      while (!threadRequest.finished) {
        synchronized(threadRequest) {
          try {
            threadRequest.wait(POLL_FOR_RESULT_HEARTBEAT);
          }
          catch (InterruptedException e) {
          }
        }    
      }
    }
    return threadRequest.returnClsid;
  }

  /** Return a String that represents this ActiveXProxy
  */
  @Override
  public String toString () {
    return((isAlive() ? "running " : "dead ") +
           "ActiveXProxy with clientSite = " + Integer.toHexString(clientSite));
  }


  /* Used to start the daemon thread that propagates requests onto the
   * ActiveX object.  Normally this thread is started when creating a new
   * ActiveXProxy.  In the case that a ActiveXProxy has been loaded from 
   * a serialization this will have to be called explicitly.  
   */
  void startDaemon () {
    if (daemon == null) {
      daemon = new Thread((Runnable) this);    
      daemon.start();
    }
  }

  /* A synchronous activation method, for the case where activation is 
   * required before completing a message that is already in the middle
   * of being executed.
   */
  private void activateWithinThread (int top, int left, int bottom, int right) {
    activate_object(clientSite, hWndHandle, top, left, bottom, right,
                    false);
    resize(notifyMessage.top, notifyMessage.left,
           notifyMessage.bottom, notifyMessage.right);
  }

  /** Checks to see whether the clientSite is currently 
   *  active.  If it is not then this will try to activate.
   *  The boolean return value indicates whether the clientSite is
   *  now active after the call to this method.
   */
  private int activateIfNotAlready () {
      if (wrapper instanceof ActiveXDisplayComponent)
      { 
        ActiveXDisplayComponent axDisplay = (ActiveXDisplayComponent) wrapper; 
        Dimension size = axDisplay.getSize();
        int width = size.width;
        int height = size.height;        
        activateWithinThread (0, 0, height, width);          
      }
      else {
        activateWithinThread (0, 0, 0, 0);
      }
      wrapper.proxyActivated();
      if (wrapper instanceof ActiveXDispatchable) {
          ActiveXDispatchable dispWrapper 
            = (ActiveXDispatchable) wrapper;
          return dispWrapper.getDispatchPointer();
      }
      return AX_NO_DISPATCH;
  }

  private void comInvokeWithinThread (OleThreadRequest notifyMessage) {
      int dispatchPointer;
      Variant returnValue;

      try {
      
        if (!(wrapper instanceof ActiveXDispatchable))
        { 
        notifyMessage.returnValue = new Variant();
        notifyMessage.finished = true;
        return;
      }

      ActiveXDispatchable dispWrapper 
        = (ActiveXDispatchable) wrapper;

      dispatchPointer = notifyMessage.dispatchPointer;
      if (dispatchPointer == AX_NO_DISPATCH) {
        dispatchPointer = dispWrapper.getDispatchPointer();
      }
      if (dispatchPointer == AX_NO_DISPATCH) {
        dispatchPointer = activateIfNotAlready();
      }

      int dispatchType = notifyMessage.dispatchType;
      boolean voidReturn = notifyMessage.voidReturn;
      
      if (dispatchPointer == AX_NO_DISPATCH) {
        message(AX_ERROR, "Attempting to invoke without a dispatch");
        notifyMessage.returnValue = new Variant();
        return;
      }
      
      Vector args = notifyMessage.args;
      if (args != null && args.size() == 0)
        args = null;

      if (is_open_in_window(clientSite)) {
        message(AX_PROGRESS, "Invoking " + Integer.toHexString(dispWrapper.getDispatchPointer()));
        if (notifyMessage.dispatchByName) {
          String methodName = notifyMessage.name;
          message(AX_PROGRESS, "\nAttempting to invoke " + methodName + 
            " from " + Integer.toHexString(dispatchPointer));
          
          notifyMessage.returnValue =
            com_Invoke_by_name(clientSite, dispatchPointer,
            methodName, dispatchType, voidReturn, args);
            
          message(AX_PROGRESS, "Called Method " + methodName + " from " + 
            dispatchPointer + ": " + notifyMessage.returnValue);
        } else {
          int memid = notifyMessage.memid;
      
          message(AX_PROGRESS, "\nAttempting to invoke " + Integer.toHexString(memid) +
            " from " + Integer.toHexString(dispatchPointer));
            
          notifyMessage.returnValue =
            com_Invoke(clientSite, dispatchPointer, memid, dispatchType, 
            voidReturn, args);
          
          message(AX_PROGRESS, "Called Method " + Integer.toHexString(memid) + " from " +
            dispatchPointer + ": " + notifyMessage.returnValue);
          }
        }   else {
        message(AX_ERROR, "Failed to invoke method, object cannot be activated.");
        notifyMessage.returnValue = new Variant();
        }
      }
      catch (ActiveXException e)
      {
          notifyMessage.exception = e; 
      }
  }
   

  /*  Kills the thread and uninitializes OLE, as quickly as possible.
   *  Does not clean up its data structures.  This should be called
   *  before shutting down whatever top-level application is containing
   *  it.  (In other words, before System.exit().)  If the application
   *  is going to continue to run, and just this object should stop,
   *  use the delete() method instead.  If the application is shutting
   *  down, it's always a good idea to call OleUninitialize, so this
   *  method should be called first.
   */
  private void die (int clientSite) {
    // Does not even bother deleting the object from C.  Use
    // "delete" for that.  This means ...
    //daemon.stop();
    shut_down(clientSite);
  }


  /** Hypothetically, copies the object to the clipboard.  I
   *  don't recall trying this any time in the last six months.
   *  (JV, 11/10/97)
   *  Made private, jv 1/10/98.
   */
  private void copy (int clientSite, int top,
                     int left, int bottom, int right) {
    synchronized (this) {
      messagesWaiting.add
        (new OleThreadRequest(COPY,
                              top, left, bottom, right));
      notify();
    }
  }

  /** Cleans up some data structures and stops the thread.  This
   *  is very poorly tested at this point.  There's no way to 
   *  call it.
   */
  // Made package-private, jv 1/21/98
  protected void delete () {
    OleThreadRequest request = 
        new OleThreadRequest(DELETE,
                              0, 0, 0, 0);
    synchronized (this) {
      messagesWaiting.add(request);
      notify();
    }
    while (!request.finished) {      
      synchronized(request) {
        try {
          request.wait(POLL_FOR_RESULT_HEARTBEAT);
        }
        catch (InterruptedException e) {          
        }
      }  
    }
  }

  /** Get the default dispatch pointer associated with clientSite
  * managed by this ActiveXProxy
  */
  public int getDispatchPointer() 
  {
    return NativeMethodBroker.getDispatchPointer(clientSite);
  }

  /* Insert an ActiveX object according to the creation mode specified 
   * in the ActiveXModes argument.
   */
  private int insertObjectFromActiveXModes (ActiveXModes modes, int hwnd) {
    message(AX_PROGRESS, "Insert object from ActiveXModes");

    if (modes.isCreateNew()) {
      if (modes.isNotInsertable()) {
        message(AX_PROGRESS, "isNotInsertable");
        return instantiateUninsertableObject(modes.getClassID(),
                                             modes.getLicense());
      } else if (modes.isCreateFromFile()) {
        message(AX_PROGRESS, "isCreateFromFile");
        return insertObjectFromFile(modes.getFileLocationIfAny());
      } else {
        message(AX_PROGRESS, "not from file, insertable");
        return insertObjectFromClsid(modes.getClassID(),hwnd,
                                     modes.getLicense());
      }
    } else {
      message(AX_ERROR, "Linking is currently unsupported");
      return AX_NO_CLIENT_SITE; 
    }
  }


  /* Starts up an ActiveX server, and returns a pointer to the
   * client site.
   */
  private int insertObjectFromClsid (Guid clsid, int hWnd, License license) {
    int result;
    String licenseKey;

    message(AX_MORE_DETAIL, "Inside non-synchronized method.  Guid = " + clsid);
    if (!clsid.isNullGuid()) {
      if (license == null)
        licenseKey = null;
      else 
      {
        licenseKey = license.getLicenseKey();
      }
      result = insert_object_from_clsid_with_license(clsid, hWnd, licenseKey);
      message(AX_MORE_DETAIL, "Got result: " + result);
      return result;
    } else {
      return AX_NO_CLIENT_SITE;
    }
  }

  private int instantiateUninsertableObject (Guid clsid, License license) {
    int result;
    String licenseKey;

    message(AX_PROGRESS, "instantiating uninsertable object: " + clsid);
    if (!clsid.isNullGuid()) {
      if (license == null)
        licenseKey = null;
      else 
      {
        licenseKey = license.getLicenseKey();
      }
      result = instantiate_uninsertable_object_with_license(clsid, licenseKey);
      message(AX_MORE_DETAIL, "Got result: " + result);
      return result;
    } else {
      return AX_NO_CLIENT_SITE;
    }
  }

  /* Starts up an ActiveX server by creating an object from a file, and
   * returns a pointer to the client site if successful
   */
  private int insertObjectFromFile (String fileName) {
    int result; 

    if (fileName != null) {
      result = insert_object_from_file(fileName);
      message(AX_MORE_DETAIL,"Got result: " + result);
      return result;
    } else {
      return AX_NO_CLIENT_SITE;
    }
  }


  /* Initializes OLE.  Should be called once per thread.  Since
   * an ActiveXProxy is a thread, should be called once per
   * ActiveXProxy.  No other class should call it.
   */
  private void startUp () {
    NativeMethodBroker.loadLibrary(false);
    try {
      start_up();
    } catch (UnsatisfiedLinkError e) {
      try {
        NativeMethodBroker.loadLibrary(true);
        NativeMethodBroker.traceln(AX_PROGRESS, "There apparently were problems " +
                                   "in initially loading JavaContainer.dll. " +
                                   "It appears to be ok now.  Error message " +
                                   "was " + e.getMessage());
        start_up();
      } catch (UnsatisfiedLinkError e2) {
        NativeMethodBroker.traceln(AX_ERROR, fatalErrorMessage +
                                   "  Error message was: " + e2.getMessage());
        // Really should exit here.
        // System.exit(-1);
      }
    }
  }


  private void deleteObject (int clientSite) {
    delete_object(clientSite);
    shut_down(clientSite);
    NativeMethodBroker.deregisterProxy(this);
  }


  private static void message (String msg) {
    NativeMethodBroker.traceln(msg);
  }

  private static void message (int debugLevel, String msg) {
    NativeMethodBroker.traceln(debugLevel, msg);
  }

  /**
   * Write an ActiveX proxy into an ObjectOutputStream. This method
   * writes the persistent data for the ActiveX object into the 
   * stream as well as the data for the java object.<p> 
   *
   * The java object is always written into the stream first,
   * followed by a long.  The long indicates the size of the 
   * ActiveX object written into the stream.<p>
   * 0 is written to the stream if the ActiveX object cannot be
   * serialized.  This can happen if the ActiveX object does not
   * implement a persistence interface (such as IPersistStorage,
   * IPersistStream, or IPersistFile), or if there is some failure
   * in the mechanism used to write the persistent data.  These 
   * failures are indicated by error messages.<p>
   *
   * If the ActiveX object can be serialized, then the long that is
   * written to the stream is the size in bytes of the persistent
   * data of the ActiveX object. The persistent data is always written
   * in the IStorage format.<p>
   */
  private void writeObject (java.io.ObjectOutputStream out) throws IOException {
    message(AX_PROGRESS,"Serialize activeX control");
    if (clientSite != AX_NO_CLIENT_SITE) {
      String componentFileName = generateComponentFileName("x0p");
      message(AX_PROGRESS,componentFileName);                                
      OleThreadRequest saveRequest = new OleThreadRequest(SAVE,
                                                          componentFileName);
      messagesWaiting.add(saveRequest);
        
      // busy wait - there must be a better way
      while (!saveRequest.finished) {
        synchronized(saveRequest) {
            try {
                saveRequest.wait(POLL_FOR_RESULT_HEARTBEAT);
            }
            catch (InterruptedException e) {

            }
        }
      }                       
        
      componentFileName = saveRequest.name;
      out.defaultWriteObject();
      if (componentFileName.equals("")) {
        message(AX_PROGRESS,
                "Cannot serialize activeX control, continuing anyway");
        out.writeLong(0);
      } else {
        File f = new File(componentFileName);
        FileInputStream fi = new FileInputStream(f);
        long sofar = 0;
        int num = -1;
        int filelen = (int)f.length();
        out.writeLong(filelen);
        message(AX_PROGRESS, "Writing the size of COM storage: " + filelen);
        byte[] buffer = new byte[1024];

        /* The storage file could be many Megs so work in 1K chunks */
        do {
          num = fi.read(buffer,0,1024);
          if (num >= 0) {
            out.write(buffer,0,num);
            sofar += num;
          }
        }
        while (num == 1024);

        message(AX_PROGRESS, "Read " + sofar + " bytes from a storage file");

        fi.close();
        if (! f.delete())
          message(AX_ERROR,"Failed to delete temporary file: " + 
                  componentFileName);
      }
    }
  }

  /**
   * Read an ActiveX proxy from an ObjectInputStream. This method
   * loads the persistent data for the ActiveX object as well as the
   * persistent data for the java object.<p>
   * 
   * First this method will load the java object using the method
   * <code> defaultReadObject()</code>. It will then read a long from the
   * input stream.  This is the number of bytes in the serialization of
   * the ActiveX object.<p>
   *
   * In the case there is no persistent data for the ActiveX object, a
   * new object of the same CLASSID will be created.<p>
   *
   * If there is persistent data fot the ActiveX object then an ActiveX
   * object is loaded from the persistent data.<p>
   * 
   */
  private void readObject (java.io.ObjectInputStream in) throws IOException  {
    message(AX_PROGRESS,"Deserialize activeX control");
    try {
      in.defaultReadObject();
      long length = in.readLong();
      message(AX_PROGRESS, "Read the size of COM storage: " + length);
      String componentFileName = generateComponentFileName("x1p");
      if (length > 0) {
        FileOutputStream fi = new FileOutputStream(componentFileName);
        byte[] buffer = new byte[1024];
        long sofar = 0;
        int num = -1;
        int bytesToRead = 0;

        /* The storage file could be many Megs so work in 1K chunks */
        while (sofar < length) {
          /* don't read more than we wrote */
          bytesToRead = (int)Math.min(1024, length - sofar);
          num = in.read(buffer, 0, bytesToRead);
          if (num < 0 ) {
            message(AX_ERROR,
              "Unexpectedly encountered the end of the serialization stream");
            break;
          }
          
          sofar += num;
          fi.write(buffer, 0, num);
        } 

        fi.close();
        message(AX_PROGRESS, "Created a " + sofar + " byte storage file.");
      }
      boolean libraryIsLoaded = NativeMethodBroker.loadLibrary();
      if (!libraryIsLoaded) {
        throw new IOException("Could not locate JavaContainer dynamic library");
      }
          
      messagesWaiting = new ThreadRequestQueue();
      if (length > 0) {
        loaded = true;
        fileLoadedFrom = componentFileName;
      }
      transientEventSets = new Hashtable();
    }
    catch (ClassNotFoundException e) {
      throw new IOException(e.toString());
    }
  }

  /** The current implementation of ActiveX object persistence
   * used by this class requires the ability to read and write
   * from temporary files.  The filenames are generated to be unique
   * and the path in which these temporary files are created is
   * determined by the following alogirithm<p>
   * Find the first writable directory in the following list<br>
   * i) The System property: com.gensym.temp<br>
   * ii) The System property: com.gensym.beaneditor.jarlocation<br>
   * iii) The System property: user.dir<br>
   * iv) The System property: user.home<br>
   */
  private String generateComponentFileName (String suffix) {
    return FileBroker.generateTemporaryFileName(hashCode(),
                                                clientSite,
                                                saveId,
                                                suffix);
  }
}



