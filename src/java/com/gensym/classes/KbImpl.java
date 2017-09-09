
package com.gensym.classes;

import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.io.Serializable;
import java.nio.charset.Charset;
import java.util.Enumeration;
import java.util.Locale;
import com.gensym.core.util.WrappingException;
import com.gensym.jgi.*;
import com.gensym.ntw.*;
import com.gensym.ntw.util.*;
import com.gensym.ntw.util.KbModuleListener;
import com.gensym.util.*;
import com.gensym.message.*;

/**
 * Only public because it needs to be created when the context
 * is created. This class should not be documented.
 */
public final class KbImpl implements Kb, Serializable {

  private static final MessageKey moduleTraceKey =
    Trace.registerMessageKey ("com.gensym.module", KbImpl.class);
  private static Resource i18nTrace =
    Trace.getBundle("com.gensym.classes.TraceMessages", Locale.getDefault());
  private static final int DEF_TRACE_LEVEL     = 5;
  private static final int DEF_WARN_LEVEL      = 2;
  private static final int BASIC_TRACE_LEVEL   = 3;
  private static final int MINIMAL_TRACE_LEVEL = 4;

  private static final Symbol MODULES_ = Symbol.intern("MODULES");
  private static final Symbol LOGBOOK_ = Symbol.intern("LOGBOOK");
  private static final Symbol MESSAGE_BOARD_ = Symbol.intern("MESSAGE-BOARD");

  protected transient TwAccess context;

  private transient KbData kbData;

  private ConnectionResolver connectionResolver;

  private transient Sequence messageBoardMessages;
  private transient Sequence logbookMessages;
  private transient StubInvalidationListener invalidationAdapterForMessageBoard;
  private transient StubInvalidationListener invalidationAdapterForLogbook;

  private static final java.lang.Object NULL = new java.lang.Object ();

  public KbImpl (TwAccess context) {
    this.context = context;
    connectionResolver = ConnectionResolver.getConnectionResolver ((G2Gateway)context);
    kbData = new KbData ();
    messageBoardMessages = new Sequence();
    logbookMessages = new Sequence();
    invalidationAdapterForMessageBoard = 
        new StubInvalidationAdapter(this, 
				    KbEvent.KB_MESSAGE_BOARD_MESSAGE_DELETED,
				    messageBoardMessages);
    invalidationAdapterForLogbook = 
        new StubInvalidationAdapter(this, 
				    KbEvent.KB_LOGBOOK_MESSAGE_DELETED,
				    logbookMessages);
    //new KbDescriberThread().start (); //-> Debugging only
  }

  @Override
  public Module getTopLevelModule () throws G2AccessException {
    ensureSubscriptions ();
    return kbData.topLevelModule;
  }

  private void readObject(java.io.ObjectInputStream stream) throws java.io.IOException, ClassNotFoundException {
    stream.defaultReadObject();
    context = (TwAccess) connectionResolver.getContext();
    kbData = ((KbImpl)context.getKb ()).kbData;
  }


  /**
   * Dispatches the Event through the KbModuleListener interface
   * This should be protected at best but needs to be public because the
   * events are constructed in the Gateway.
   * @param evt The KbEvent to dispatch
   * @undocumented
   */
  public void processKbEvent (final KbEvent evt) {
    Trace.send (DEF_TRACE_LEVEL, moduleTraceKey, i18nTrace, "processKbEvent", evt);
    KbEvent event = syncLocalData (evt);
    if (event == null) // Spurious event from G2.
      return;
    KbModuleListener listener = kbData.listener;
    KbMessageListener msgListener = kbData.msgListener;
    switch (event.getID ())
      {
      case KbEvent.MODULE_INITIAL_DOWNLOAD:
      case KbEvent.KB_MESSAGES_INITIAL_DOWNLOAD:	  
	//listener.receivedInitialModules (evt);
	break;
      case KbEvent.MODULE_CREATED:
	if (listener != null) {
		listener.moduleCreated (event);
	}
	break;
      case KbEvent.MODULE_DELETED:
	if (listener != null){
		listener.moduleDeleted (event);
	}
	break;
      case KbEvent.MODULE_NAME_CHANGED:
	if (listener != null){
		listener.moduleNameChanged (event);
	}
	break;
      case KbEvent.MODULE_DEPENDENCY_CHANGED:
	if (listener != null) {
		listener.moduleDependencyChanged (event);
	}
	break;
      case KbEvent.KB_CLEARED:
	if (listener != null) {
		listener.kbCleared (event);
	}
	break;
      case KbEvent.KB_LOGBOOK_MESSAGE_ADDED:
      case KbEvent.KB_MESSAGE_BOARD_MESSAGE_ADDED:
	if (msgListener != null) {
		msgListener.kbMessageAdded (event);
	}
	break;
      case KbEvent.KB_LOGBOOK_MESSAGE_DELETED:
      case KbEvent.KB_MESSAGE_BOARD_MESSAGE_DELETED:
	if (msgListener != null) {
		msgListener.kbMessageDeleted (event);
	}
	break;
      case KbEvent.TOP_LEVEL_KB_WORKSPACE_ADDED:
	if (listener != null) {
		listener.topLevelWorkspaceAdded (event);
	}
	break;
      case KbEvent.TOP_LEVEL_KB_WORKSPACE_DELETED:
	if (listener != null) {
		listener.topLevelWorkspaceDeleted (event);
	}
	break;
      default:
	throw new RuntimeException ("Unexpected id <" + event.getID () + "> in KbEvent. Please report to vkp.");
      }
  }

  /**
   * Retrieves a module by name.
   * Returns null if no such module exists
   * @param moduleName The name of the module. This can be null.
   * @return A Module with this value for the TOP-LEVEL-MODULE attribute.
   */
  @Override
  public Module getModule (Symbol moduleName) throws G2AccessException {
    ensureSubscriptions ();
    java.lang.Object moduleKey = (moduleName == null ? NULL : moduleName);
    return (Module) kbData.moduleTable.get (moduleKey);
  }

  /**
   * By the time this method returns, we are guaranteed
   * that the Kb is set up with the correct data structures.
   * Note that this didn't necessarily have to return anything.
   * It is just a horrible optimization that will confuse
   * all subsequent readers. It is used only in addKbModuleListener
   * so that the snapshot does not need to recreated. And
   * since this method is private, I figured, why not? -vkp, 2/25/98
   */
  private Structure ensureSubscriptions () throws G2AccessException {
    if (!kbData.currentlySubscribed) {
      synchronized (kbData) {	// Prevents events being delivered to us
	Structure initialData = context.subscribeToModules ();
	Sequence initialModulesData = (Sequence)initialData.getAttributeValue(MODULES_,null);
	Sequence initialLogbookData = (Sequence)initialData.getAttributeValue(LOGBOOK_, null);
	Sequence initialMessageBoardData = (Sequence)initialData.getAttributeValue(MESSAGE_BOARD_, null);
	kbData.currentlySubscribed = true;
	initializeModulesForKb (initialModulesData);
	initializeLogbookForKb(initialLogbookData);
	initializeMessageBoardForKb(initialMessageBoardData);
	return initialData;
      }
    } else
      return null;
  }

  private static final Symbol IS_TOP_LEVEL_ = Symbol.intern ("IS-TOP-LEVEL");

  private void initializeModulesForKb (Sequence initialModulesData) {
    for (int i=0; i<initialModulesData.size (); i++) {
      Structure moduleData = (Structure) initialModulesData.elementAt (i);
      Trace.send (DEF_TRACE_LEVEL, moduleTraceKey, i18nTrace, "initializeMod", moduleData);
      Module module = new ModuleImpl (this, moduleData);
      Trace.send (DEF_TRACE_LEVEL, moduleTraceKey, i18nTrace, "createdMod", module);
      boolean isTopLevel = ((Boolean)moduleData.getAttributeValue (IS_TOP_LEVEL_, null)).booleanValue ();
      addModule (module, isTopLevel);
    }
  }

  private void initializeLogbookForKb(Sequence initialLogbookData){
    logbookMessages.ensureCapacity(initialLogbookData.size());
    Enumeration msgs = initialLogbookData.elements();
    while (msgs.hasMoreElements()){
      Item message = (Item)msgs.nextElement();
      ((ItemImpl)message).addStubInvalidationListener(invalidationAdapterForLogbook);
      logbookMessages.addElement(message);
    }
  }

  private void initializeMessageBoardForKb(Sequence initialMessageBoardData){
    messageBoardMessages.ensureCapacity(initialMessageBoardData.size());
    Enumeration msgs = initialMessageBoardData.elements();
    while (msgs.hasMoreElements()){
      Item message = (Item)msgs.nextElement();
      ((ItemImpl)message).addStubInvalidationListener(invalidationAdapterForMessageBoard);
      messageBoardMessages.addElement(message);
    }
  }

  private Module addModule (Structure moduleData) {
    Module module = new ModuleImpl (this, moduleData);
    boolean isTopLevel = ((Boolean)moduleData.getAttributeValue (IS_TOP_LEVEL_, null)).booleanValue ();
    addModule (module, isTopLevel);
    return module;
  }

  private void addModule (Module module, boolean isTopLevel) {
    Symbol moduleName = module.getName ();
    java.lang.Object moduleKey = (moduleName == null ? NULL : moduleName);
    kbData.moduleTable.put (moduleKey, module);
    if (isTopLevel) {		// Old top-level module is no longer so! ?
      ModuleImpl oldTopLevelModule = (ModuleImpl) kbData.topLevelModule;
      if (oldTopLevelModule != null) // Might not have been set up yet!
	oldTopLevelModule.setTopLevel (false);
      kbData.topLevelModule = module;
    }
  }

  private void removeModule (Module module) {
    Symbol moduleName = module.getName ();
    java.lang.Object moduleKey = (moduleName == null ? NULL : moduleName);
    kbData.moduleTable.remove (moduleKey);
    if (module.equals (kbData.topLevelModule))
      kbData.topLevelModule = null; // Should be transient? -vkp, 2/24/98
  }

  private void renameModule (Module module, Symbol newName) {
    Symbol oldName = module.getName ();
    java.lang.Object moduleKey = (oldName == null ? NULL : oldName);
    ((ModuleImpl)module).setName (newName);
    kbData.moduleTable.remove (moduleKey);
    moduleKey = (newName == null ? NULL : newName); // revert module-name to null. People do this.
    kbData.moduleTable.put (moduleKey, module);
  }

  private void updateModuleDependencies (Module module, Sequence reqdModules) {
    ((ModuleImpl)module).setRequiredModules (reqdModules);
  }

  private void updateTopLevelWorkspaces (Module module, KbWorkspace wksp, boolean add) {
    if (add)
      ((ModuleImpl)module).addTopLevelKbWorkspace (wksp);
    else
      ((ModuleImpl)module).removeTopLevelKbWorkspace (wksp);
  }

  private void clearModules () {
    kbData.moduleTable.clear ();
    kbData.topLevelModule = null;
    try {
      G2__BaseImpl.invokeTwAccessMethod(context,
                                        "clearModuleMappings",
                                        null,
                                        null);
    }
    catch (G2AccessException e) {
      // We don't expect to ever reach here because
      // clearModuleMappings shouldn't have acessed G2.
      throw new WrappingException (e);
    }
  }

  @Override
  public Module[] getModules () throws G2AccessException {
    synchronized (kbData) {	// Slight overkill
      ensureSubscriptions ();
      Module[] moduleArray = new Module[kbData.moduleTable.size ()];
      int  i = 0;
      for (Enumeration e = kbData.moduleTable.elements ();
	   e.hasMoreElements ();)
	moduleArray[i++] = (Module) e.nextElement ();
      return moduleArray;
    }
  }

  @Override
  public void addKbModuleListener (KbModuleListener newListener) throws G2AccessException {
    synchronized (kbData) {	// Prevents listeners being called with events
      kbData.listener = NtwEventMulticaster.add (kbData.listener, newListener);
      Sequence initialModulesData;
      if (!kbData.currentlySubscribed){
	Structure initialData = ensureSubscriptions ();
	initialModulesData = (Sequence)initialData.getAttributeValue(MODULES_, null);
      }
      else
	initialModulesData = makeModuleSnapshot ();
      dispatchReceptionCallback	// Only needs to go to the new KbModuleListener
	(newListener,
	 new KbEvent (this, null, KbEvent.MODULE_INITIAL_DOWNLOAD, initialModulesData));
    }
  }

  public Structure addKbModuleListenerRetrievingState (KbModuleListener newListener) throws G2AccessException {
    synchronized (kbData) {
      addKbModuleListener (newListener);
      return makeSnapshot ();
    }
  }

  @Override
  public void removeKbModuleListener (KbModuleListener oldListener) throws G2AccessException {
    synchronized (kbData) {
      kbData.listener = NtwEventMulticaster.remove (kbData.listener, oldListener);
      if (kbData.listener == null && kbData.msgListener == null)
	context.unsubscribeToModules ();
    }
  }

  @Override
  public void addKbMessageListener(KbMessageListener listener) throws G2AccessException{
    synchronized (kbData) {	// Prevents listeners being called with events
      kbData.msgListener = NtwEventMulticaster.add (kbData.msgListener, listener);
      Structure initialMessageData = new Structure();
      if (!kbData.currentlySubscribed){
	Structure initialData = ensureSubscriptions ();
	initialMessageData.setAttributeValue(LOGBOOK_, initialData.getAttributeValue(LOGBOOK_, null));
	initialMessageData.setAttributeValue(MESSAGE_BOARD_, initialData.getAttributeValue(MESSAGE_BOARD_, null));
      }
      else
	initialMessageData = makeMessageSnapshot ();
      listener.receivedInitialContents(new KbEvent(this, null, KbEvent.KB_MESSAGES_INITIAL_DOWNLOAD, 
						   initialMessageData));
    }
  }

  @Override
  public void removeKbMessageListener (KbMessageListener listener) throws G2AccessException {
    synchronized (kbData) {
      kbData.msgListener = NtwEventMulticaster.remove (kbData.msgListener, listener);
      if (kbData.msgListener == null && kbData.listener == null)
	context.unsubscribeToModules ();
    }
  }
  
  private void dispatchReceptionCallback (KbModuleListener listener,
					  KbEvent evt) { // Called within lock. Guarantees order.
    listener.receivedInitialModules (evt);
  }

  private Structure makeSnapshot(){
    Sequence modules = makeModuleSnapshot();
    Structure messages = makeMessageSnapshot();
    messages.setAttributeValue(MODULES_, modules);
    return messages;
  }

  private Sequence makeModuleSnapshot () {	// Called within lock
    Sequence snapshot = new Sequence (kbData.moduleTable.size ());
    for (Enumeration e = kbData.moduleTable.elements ();
	 e.hasMoreElements ();) {
      Module module = (Module) e.nextElement ();
      snapshot.addElement (((ModuleImpl)module).makeSnapshot());
    }
    Trace.send (DEF_TRACE_LEVEL, moduleTraceKey, i18nTrace, "kbSnapshot", 
		kbData.moduleTable.size (), snapshot);
    return snapshot;
  }

  private Structure makeMessageSnapshot (){
    Structure messages = new Structure();
    Sequence logbookMsgs = new Sequence();
    Enumeration msgs = logbookMessages.elements();
    while (msgs.hasMoreElements()){
      logbookMsgs.addElement(msgs.nextElement());
    }
    messages.setAttributeValue(LOGBOOK_, logbookMsgs);
    Sequence messageBoardMsgs = new Sequence();
    msgs = messageBoardMessages.elements();
    while (msgs.hasMoreElements()){
      messageBoardMsgs.addElement(msgs.nextElement());
    }
    messages.setAttributeValue(MESSAGE_BOARD_, messageBoardMsgs);
    return messages;
  }

  @Override
  public Module getModule (ModuleInformation mi) throws G2AccessException {
    ensureSubscriptions ();
    for (Enumeration e = kbData.moduleTable.elements ();
	 e.hasMoreElements ();) {
      Module module = (Module) e.nextElement ();
      Trace.send (DEF_TRACE_LEVEL, moduleTraceKey, i18nTrace, "getModuleCheck",
		  mi, module.getName (), module.getModuleInformation (),
		  new Boolean (module.getModuleInformation ().equals (mi)));
      if (module.getModuleInformation ().equals (mi))
	return module;
    }
    throw new RuntimeException ("Error in module lookup from MI. Please see vkp"); // Should not happen
  }

  public java.lang.Object getKbLock () {
    return kbData;
  }

  public Module createNewModule (Structure particulars) {
    return new ModuleImpl (this, particulars);
  }

  /**
   * This method updates the data structures maintained in the Kb
   * and Module classes to reflect the changes in the KbEvent.
   * It returns a KbEvent object that is suitable for dispatch
   * to KbModuleListeners
   */
  private KbEvent syncLocalData (final KbEvent evt) {
	KbEvent event = evt; 
    synchronized (kbData) {	// Prevent other threads from interfering
      Item item;
      switch (event.getID ())
	{
	case KbEvent.MODULE_INITIAL_DOWNLOAD: // initial data is set up by using subscribeToModul in ensureSubscriptions
	case KbEvent.KB_MESSAGES_INITIAL_DOWNLOAD: //initialization is done in ensureSuscriptions()
	case KbEvent.KB_LOGBOOK_MESSAGE_DELETED: //sync is done in ItemListener
	case KbEvent.KB_MESSAGE_BOARD_MESSAGE_DELETED: //sync is done in ItemListener
	  break;
	case KbEvent.MODULE_CREATED:
	  Module newModule = addModule ((Structure) event.getData ());
	  event = new KbEvent (this, newModule, KbEvent.MODULE_CREATED, event.getData ());
	  break;
	case KbEvent.MODULE_DELETED:
	  removeModule (event.getModule ());
	  break;
	case KbEvent.MODULE_NAME_CHANGED:
	  Module changedModule = event.getModule ();
	  Symbol oldName = changedModule.getName ();
	  Symbol newName = (Symbol)event.getData ();
	  if ((newName == null && oldName== null ) || (newName != null && newName.equals (oldName)))
		  return null; // spurious event. filter
	  renameModule (changedModule, newName);
	  break;
	case KbEvent.MODULE_DEPENDENCY_CHANGED:
	  updateModuleDependencies (event.getModule (), (Sequence) event.getData ());
	  break;
	case KbEvent.KB_CLEARED:
	  clearModules ();
	  break;
	case KbEvent.TOP_LEVEL_KB_WORKSPACE_ADDED:
	case KbEvent.TOP_LEVEL_KB_WORKSPACE_DELETED:
	  if (event.getModule () == null) // Probably after clear-kb.
	    return null;
	  updateTopLevelWorkspaces (event.getModule (), (KbWorkspace)event.getData (),
				    event.getID() == KbEvent.TOP_LEVEL_KB_WORKSPACE_ADDED);
	  break;
	case KbEvent.KB_LOGBOOK_MESSAGE_ADDED:
	  item = (Item)event.getData();
	  ((ItemImpl)item).addStubInvalidationListener(invalidationAdapterForLogbook);
	  logbookMessages.addElement(item);
	  break;
	case KbEvent.KB_MESSAGE_BOARD_MESSAGE_ADDED:
	  item = (Item)event.getData();
	  ((ItemImpl)item).addStubInvalidationListener(invalidationAdapterForMessageBoard);
	  messageBoardMessages.addElement(item);
	  break;
	default:
	  throw new RuntimeException ("Unexpected code <" + event.getID () + "> in KbEvent. Please report to vkp.");
	}
      return event;
    }
  }


  class StubInvalidationAdapter implements StubInvalidationListener{
    private Kb kb;
    private int id;
    private Sequence list;

    StubInvalidationAdapter(Kb kb, int id, Sequence list){
      this.kb = kb;
      this.id = id;
      this.list = list;
    }

    @Override
    public void stubIsInvalid (StubInvalidationEvent event){
      Item message = (Item)event.getSource();
      list.removeElement(message);
      ((ItemImpl)message).removeStubInvalidationListener(this);
      KbEvent evt = new KbEvent(kb, null, id, message);
      processKbEvent(evt);
    }
  }

  void pprint (PrintWriter out) {
    kbData.pprint (out);
  }

  class KbDescriberThread extends Thread {

    KbDescriberThread () {
      super ("kb-describer");
    }

    @Override
    public void run () {
      PrintWriter out = new PrintWriter (new OutputStreamWriter(System.out, Charset.defaultCharset()));
      while (true) {
	try {
	  out.println ("Describing " + KbImpl.this);
	  pprint (out);
	  out.flush ();
	  sleep (20000);
	} catch (InterruptedException ie) {
	  Trace.exception (ie);
	}
      }
    }
  }

}
