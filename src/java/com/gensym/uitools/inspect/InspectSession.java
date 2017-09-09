package com.gensym.uitools.inspect;

import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import java.util.Hashtable;
import java.util.Vector;
import java.util.Enumeration;
import java.lang.reflect.Method;
import com.gensym.message.Trace;
import com.gensym.util.Structure;

public class InspectSession {

  private String filterText;
  private Vector connections, infoListeners;
  private static Hashtable servers = new Hashtable();
  private Hashtable sessions = new Hashtable();
  private static Method callbackMethod;
  private static final Symbol
  INSPECT_CALLBACK_ = Symbol.intern ("INSPECT-CALLBACK"),
    G2_START_INSPECT_SESSION_ = Symbol.intern ("G2-START-INSPECT-SESSION"),
    G2_PAUSE_INSPECT_SESSION_ = Symbol.intern ("G2-PAUSE-INSPECT-SESSION"),
    G2_ABORT_INSPECT_SESSION_ = Symbol.intern ("G2-ABORT-INSPECT-SESSION"),
    G2_RESUME_INSPECT_SESSION_ = Symbol.intern ("G2-RESUME-INSPECT-SESSION");
  private static final Symbol URL_ = Symbol.intern ("URL");
  public static final String SHOW = "show on a workspace ";
  public static final String RECOMPILE = "recompile ";
  public static final String SAVE = "write to the file ";
  public static final String CHECK_MODULARIZATION = "check for consistent modularization";
  private String prefix = SHOW;
  private boolean started = false;
  private ErrorHandler errorHandler;
  private String className, itemName, extraFilters;
  static {
    try {
      callbackMethod
	= InspectSession.class.getDeclaredMethod("inspectCallback",
						 new Class[]
						 {Symbol.class,
						    Integer.TYPE,
						    Integer.TYPE,
						    Integer.TYPE,
						    Sequence.class,
						    Object.class});
      
    } catch (NoSuchMethodException nsme) { 
      Trace.exception(nsme);
    }
  }

  public InspectSession(String filterText)
  {
    this.filterText = filterText;
    //commandText = "replace mom with dad in every procedure";//OK
    //commandText = "replace dad with mom in every procedure"; //OK   
    //commandText = "highlight mom in every procedure";    //OK
    //commandText =  "check for consistent modularization";//OK
    //commandText = "recompile every procedure assigned to module affff";//OK
    //commandText = "write to the file \"/home/pbk/fud\" every procedure";//OK        
    init();
  }

  public String getPrefix() {
    return prefix;
  }
  
  public void setPrefix(String prefix) {
    this.prefix = prefix;
  }
  
  public InspectSession(String className,
			String itemName,
			String extraFilters)
  {
    this(className, itemName, extraFilters, null);
  }
  
  public InspectSession(String className,
			String itemName,
			String extraFilters,
			Symbol[] attributes)
  {    
    this(createFilterText(className, itemName, extraFilters, attributes));
    this.className = className;
    this.itemName = itemName;
    this.extraFilters = extraFilters;
  }
  
  public String getClassName(){
    return className;
  }

  public String getItemName() {
    return itemName;
  }

  public String getExtraFilters() {
    return extraFilters;
  }

  private static String pprintAttributes(Symbol[] attributes) {
    String res = " the ";
    int count = attributes.length;
    for (int i=0;i<count;i++) {
      res+=attributes[i].toString().toLowerCase();
      if (i < (count-1)) {
	if (i == (count-2))
	  res+=" and ";
	else
	  res+=", ";
      }
    }
    res+=" of ";
    return res;
  }
  
  private static String createFilterText(String className,
					 String itemName,
					 String extraFilters,
					 Symbol[] attributes)
  {
    String filterText;
    if (itemName != null && !"".equals(itemName)) {
      if (className == null || "".equals(className))
	filterText = itemName;
      else
	filterText = " the " + className + " named " + itemName;
    } else
      filterText = " every " + className + " " + extraFilters;
    if (attributes != null) 
      filterText = pprintAttributes(attributes) + filterText;
    return filterText;
  }

  public String getFilterText() {
    return filterText;
  }
  
  @Override
  public String toString()
  {
    return prefix+filterText;
  }
  
  private void init() {
    connections = new Vector();
    infoListeners = new Vector();
  }

  public void setErrorHandler(ErrorHandler errorHandler)
  {
    this.errorHandler = errorHandler;
  }

  /**
   * If session is already started, does not send any
   * old information that has already been recieved.
   */
  public void addInspectSessionListener(InspectSessionListener infoListener)
  {
    infoListeners.addElement(infoListener);
  }

  public boolean removeInspectSessionListener(InspectSessionListener infoListener)
  {
    return infoListeners.removeElement(infoListener);
  }

  public Vector getConnections() {
    return (Vector)connections.clone();
  }
  
  public void addConnection(G2Access connection)
  {
    if (connections.contains(connection)) return;
    connections.addElement(connection);
    
    registerInspectCallback(connection);
    
    if (started)
      start(connection, createCommandText());
  }

  private String createCommandText() {
    if (filterText == null)
      return prefix;
    else
      return prefix+filterText;
  }
  
  /**
   * Starts this <code>InspectSession</code>
   */
  public void start()
  {
    start(createCommandText());
  }
  
  private void start(String commandText)
  {
    started = true;
    synchronized (connections) {
      Enumeration e = connections.elements();
      while (e.hasMoreElements()) {
	start((G2Access)e.nextElement(), commandText);
      }
    }
  }

  public void stop() 
  {
    started = false;
    synchronized (connections) {
      Enumeration e = connections.elements();
      while (e.hasMoreElements()) {
	stop((G2Access)e.nextElement());
      }
    }
  }

  public void pause() 
  {
    started = false;
    synchronized (connections) {
      Enumeration e = connections.elements();
      while (e.hasMoreElements()) {
	pause((G2Access)e.nextElement());
      }
    }
  }
  
  public void resume() 
  {
    started = false;
    synchronized (connections) {
      Enumeration e = connections.elements();
      while (e.hasMoreElements()) {
	resume((G2Access)e.nextElement());
      }
    }
  }
  
  private void start(G2Access connection, String commandText) 
  {
    Structure identifier = new Structure();
    identifier.setAttributeValue(URL_, connection.toURLString());
    try {
      Integer sessionId = 
	(Integer) connection.callRPC(G2_START_INSPECT_SESSION_,
			   new Object[]
			   { commandText,
			       INSPECT_CALLBACK_,
			       identifier,
			       new Integer(1),
			       new Float(.5)});
      sessions.put(connection,sessionId);
    } catch (G2AccessException g2ae) {
      if (errorHandler != null) {
	errorHandler.handleError(new InspectSessionException(this, g2ae));
      }
    }
  }

  private void stop(G2Access connection) {
    try {
      connection.callRPC(G2_ABORT_INSPECT_SESSION_,
			 new Object[]
			 { sessions.get(connection)});
    } catch (G2AccessException g2ae) {
      if (errorHandler != null) {
	errorHandler.handleError(new InspectSessionException(this, g2ae));
      }
    }    
  }

  private void pause(G2Access connection) {
    try {
      connection.callRPC(G2_PAUSE_INSPECT_SESSION_,
			 new Object[]
			 { sessions.get(connection)});
    } catch (G2AccessException g2ae) {
      if (errorHandler != null) {
	errorHandler.handleError(new InspectSessionException(this, g2ae));
      }
    }    
  }

  private void resume(G2Access connection) {
    try {
      connection.callRPC(G2_RESUME_INSPECT_SESSION_,
			 new Object[]
			 { sessions.get(connection)});
    } catch (G2AccessException g2ae) {
      if (errorHandler != null) {
	errorHandler.handleError(new InspectSessionException(this, g2ae));
      }
    }    
  }
  
  public void dispose() {
    errorHandler = null;
    servers.clear();
    connections.removeAllElements();
    infoListeners.removeAllElements();
  }
  
  private void updateListeners(Symbol status,
			       int itemsToExamine,
			       int numberOfItemsExaminedSoFar,
			       int numberOfItemsFound,
			       Sequence itemList,
			       G2Access cxn)
  {
    int listenerCount;
    Vector listeners = null;
    synchronized (infoListeners) {
      listenerCount = infoListeners.size();
      if (listenerCount == 0)
	return;
      listeners = (Vector) infoListeners.clone();
    }
    InspectSessionEvent inspectInfoEvent
      = new InspectSessionEvent(this,
				status,
				itemsToExamine,
				numberOfItemsExaminedSoFar,
				numberOfItemsFound,
				itemList,
				cxn);
    for (int i=0; i<listenerCount; i++) {
      InspectSessionListener listener =
	((InspectSessionListener)listeners.elementAt(i));
      if (listener != null)
 	listener.infoUpdated(inspectInfoEvent);
    }
  }

  private void registerInspectCallback(G2Access cxn)
  {
    if (cxn != null) {
      servers.put(cxn.toURLString(), cxn);
      if (callbackMethod != null) {
	cxn.registerJavaMethod(this,
			       callbackMethod,
			       INSPECT_CALLBACK_,
			       false);
      }
    }
  }
  
  @Override
  public boolean equals(Object obj)
  {
    if (obj instanceof InspectSession) {
      InspectSession inspectSession = (InspectSession)obj;
      return (className != null &&
	      className.equals(inspectSession.getClassName()) &&
	      itemName != null &&
	      itemName.equals(inspectSession.getItemName()) &&
	      extraFilters != null &&
	      extraFilters.equals(inspectSession.getExtraFilters()));
    }
    return false;
  }
  
  /**
   *@undocumented
   */
  public void inspectCallback(Symbol status,
			      int itemsToExamine,
			      int numberOfItemsExaminedSoFar,
			      int numberOfItemsFound,
			      Sequence itemList,
			      Object identifier)
  {
    //synchronized (this) {
      Structure identifierStruct = (Structure)identifier;
      String url = (String)identifierStruct.getAttributeValue(URL_, null);
      G2Access cxn = (G2Access) servers.get(url);
      updateListeners(status,
		      itemsToExamine,
		      numberOfItemsExaminedSoFar,
		      numberOfItemsFound,
		      itemList,
		      cxn);
      //}
  }
  
}
