
package com.gensym.util;

import com.gensym.core.GensymApplication;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2Gateway;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.Definition;
import com.gensym.classes.G2Definition;
import com.gensym.classes.G2__BaseImpl;
import com.gensym.classes.SystemClassDefinitionImpl;
import com.gensym.core.IntHashtable;
import java.util.Hashtable;
import java.util.Locale;
import java.util.Vector;

/**
 * A class that manages the fanout from the changes to G2 Class Definitions.
 */
import com.gensym.message.Trace;
import com.gensym.message.Resource;
import com.gensym.message.MessageKey;

/**
 * A class that manages G2 class definitions on the client.
 * There is a ClassManager associated with every connection.
 * The ClassManager can be queried for the definitions of a
 * G2 class named by a symbol and to determine the value of
 * a class attribute that could possibly be inherited from
 * a superior Definition.
 *
 * @author vkp
 * @version 1.00 - 
 * @version 1.01 - 5/23/98. Added API Doc. Introduced separate
 *                          ClassManager for system classes.
 */
public class ClassManager implements
com.gensym.util.symbol.DefinitionSymbols,
  com.gensym.util.symbol.AttributeExportSymbols,
  com.gensym.util.symbol.G2ClassSymbols {

    /*
     * Standard Tracing Requirements
     */
    static MessageKey traceKey =
    Trace.registerMessageKey("com.gensym.util.classmanager",
			     ClassManager.class);
    static Resource i18nTrace =
    Trace.getBundle("com.gensym.util.Messages", Locale.getDefault());
    static final int DEF_TRACE_LEVEL = 5;

    static final Resource i18n =
    Resource.getBundle("com.gensym.util.Messages");
  private G2Access context;
    /**
     * Use getDefinition (key) instead of defnsTable.get(key)
     * In order to work in both 2 and 3 tier.
     */
  protected Hashtable defnsTable;
    /**
     * @undocumented
     */
  protected IntHashtable defnsHandleTable = new IntHashtable(211);
  protected IntHashtable systemDefnsHandleTable = new IntHashtable(211);

  private Hashtable adapterTable = new Hashtable (101);

  private static final Symbol ENTITY_ = Symbol.intern ("ENTITY");

  private static Boolean sharingSystemClasses;
  private static SystemClassManager systemClassManager;

  private static Symbol[] slotsWithG2Inheritance =
  {ICON_DESCRIPTION_,
   CROSS_SECTION_PATTERN_,
   STUB_LENGTH_,
   DEFAULT_MESSAGE_PROPERTIES_,
   INITIAL_HEIGHT_,
   INITIAL_WIDTH_,
   SYSTEM_MENU_CHOICES_};
  private static Symbol[] classDefiningInheritableSlot = 
  {ENTITY_,
   CONNECTION_,
   CONNECTION_,
   MESSAGE_,
   KB_WORKSPACE_,
   KB_WORKSPACE_,
   BLOCK_};
  private static Symbol[][] classesNotInheritingSlot = 
  {{CONNECTION_},
   {},
   {},
   {},
   {},
   {},
   {}};
  private static final int INHERITED_SLOTS_COUNT = slotsWithG2Inheritance.length;
  private Hashtable[] slotTables;
    Integer hc;

  public ClassManager (G2Access context) {
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "newClassManager", this, hc = hashCode ());
    this.context = context;
    defnsTable = new Hashtable(211);
    slotTables = new Hashtable[INHERITED_SLOTS_COUNT];
    for (int i=0; i<INHERITED_SLOTS_COUNT; i++)
      slotTables[i] = new Hashtable (53); // Only need for user classes
    synchronized (ClassManager.class) {
      if (sharingSystemClasses == null) {
	sharingSystemClasses =
	  new Boolean (System.getProperty ("com.gensym.class.sharesystemclasses", "true").equalsIgnoreCase ("true"));
	// Ensure static systemClassManager always has a context
	if (sharingSystemClasses.booleanValue ())
	  systemClassManager = new SystemClassManager (context);
      }
    }
  }

    /**
     * By the time this is called, we are guaranteed that all superclasses
     * and their definitions have been downloaded. this method ensures
     * that all the necessary inherited attributes are wired correctly
     * for user defined classes. Just stores system defined classes, as
     * the wiring is unnecessary.
     */

  public void storeClassDefinition (Symbol g2ClassName,
				    G2Definition definition,
				    boolean isSystemClass) {
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "storeClassDefn", hc, g2ClassName, definition);
    if (isSystemClass && sharingSystemClasses.booleanValue ()) {
      systemClassManager.storeClassDefinition (g2ClassName, definition);
      return;
    }
    if (defnsTable.get(g2ClassName) != null)
      return;
    if (!isSystemClass) {
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "doWiring", hc, g2ClassName);
      doWiring ((Definition)definition);
      createSlotsForInheritableAttributes (g2ClassName, (Definition)definition);
      adapterTable.put (g2ClassName, new DefinitionAdapter ()); // decache on class invalidation
    }
    defnsTable.put (g2ClassName, definition);
    // Support for retrieving by handle
    if (!isSystemClass)
      defnsHandleTable.put(((G2__BaseImpl)definition).getHandle(), definition);
    else
      systemDefnsHandleTable.put(((SystemClassDefinitionImpl)definition).getClassID(), definition);
  }

    /**
     * @undocumented
     */
  private void takeDefinitionFromDefnsTable(Definition definition,
					    Symbol className) {
    synchronized (defnsTable) {
      Object defnForThisName = defnsTable.get(className);
      if (definition.equals(defnForThisName))
	defnsTable.remove(className);
      else
	throw new CorruptionException(null, i18n.format("definitionMissingWhenRemoved",
							className,
							definition));
    }
  }

    /**
     * @undocumented
     */
  public void unloadClassDefinition(Definition definition,
				    Symbol className) {
    takeDefinitionFromDefnsTable(definition, className);
    
    if (definition instanceof G2__BaseImpl) {// all Definitions will satisfy this
      int handle = ((G2__BaseImpl)definition).getHandle();
      synchronized (defnsHandleTable) {
	Object defnForThisHandle = defnsHandleTable.get(handle);
	if (definition.equals(defnForThisHandle))
	  defnsHandleTable.remove(handle);
	else
	  throw new CorruptionException(null, i18n.format("definitionMissingWhenRemoved2",
							  definition));
      }
    }    
  }

    /*
     * Creates the initial slots for a user-class
     */
  private void createSlotsForInheritableAttributes (Symbol g2ClassName, G2Definition definition) {
    try {
      for (int i=0; i<INHERITED_SLOTS_COUNT; i++) {
	Symbol slotName = slotsWithG2Inheritance[i];
	java.lang.Object slotValue = null;
	/*System.out.println ("In createSlotsForInheritableAttributes -> isSubClass (" + g2ClassName +
	  ", " + classDefiningInheritableSlot[i] + ") = " +
	  isSubClass (definition, classDefiningInheritableSlot[i]));*/
	if (classHasAttribute (definition, i)) //isSubClass (definition, classDefiningInheritableSlot[i]))
	  slotValue = getAttributeValueFromDefinition (definition, slotName); //definition.getClassAttributeValue (slotName);
	Symbol classWithValue = (slotValue == null ? null : g2ClassName);
	slotTables[i].put (g2ClassName, new InheritedSlot (slotValue, slotValue, classWithValue));
      }
    } catch (G2AccessException gae) {
      Trace.exception (gae, "Error making slot in " + definition + " for class " + g2ClassName);
    }
  }


    /*
     * Some classes don't 'inherit' attributes. For example, Connection, though a subclass
     * of entity has no icon-description
     */
  private boolean classHasAttribute (G2Definition definition, int attrIndex) throws G2AccessException {
    boolean isSubClassOfClassDefiningAttribute = 
      isSubClass (definition, classDefiningInheritableSlot[attrIndex]);
    if (!isSubClassOfClassDefiningAttribute)
      return false;
    Symbol[] classesExcluded = classesNotInheritingSlot[attrIndex];
    for (int i=0; i<classesExcluded.length; i++) {
      if (isSubClass (definition, classesExcluded[i]))
	return false;
    }
    return true;
  }

  private boolean isSubClass (G2Definition definition,
			      Symbol classToCheck_) throws G2AccessException {
    Sequence inhPathFromDefinition = definition.getSystemClassInheritancePath ();
    for (int i=0; i<inhPathFromDefinition.size (); i++)
      if ((inhPathFromDefinition.elementAt (i)).equals (classToCheck_))
	return true;
    return false;
  }

  private java.lang.Object getAttributeValueFromDefinition (G2Definition defn, Symbol attrName) throws G2AccessException {
    if (attrName.equals (SYSTEM_MENU_CHOICES_) &&
	defn instanceof Definition)
      return null;
    return defn.getClassAttributeValue (attrName);
  }

    /*
     * Performs the hookups necessary so that effective changes to slot
     * values (in place or inherited values) are propagated to all the
     * appropriate classes.
     */
  private void doWiring (Definition defn) {
    Sequence superiorClasses = null;
    Symbol defnClassName = null;
    try {
      SelfClassListener selfListener = new SelfClassListener (this, defn);
    } catch (G2AccessException gae) {
      Trace.exception (gae, null);
    }
  }

    /**
     * This provides local access to the defnsTable. It
     * only attempts to abstract away the existence of
     * a separate System ClassManager.
     */
    /** @undocumentated */
  public G2Definition getDefinition0 (Symbol g2ClassName_) {
    G2Definition definition = (G2Definition) defnsTable.get (g2ClassName_);
    if (definition != null)
      return definition;
    if (sharingSystemClasses.booleanValue() &&
	com.gensym.classes.SystemPredicate.isSystemClass (g2ClassName_))
      return systemClassManager.getDefinition0 (g2ClassName_);
    return null;
  }

    /**
     * Returns the G2Definition corresponding to a G2 class-name.
     * @param g2ClassName_ a Symbol naming a G2 class that exists in
     *          the remote G2
     * @return the G2Definition object corresponding to the named class
     * @throws G2AccessException if there are any communication errors or
     *           if no class exists by that name
     */
  public G2Definition getDefinition (Symbol g2ClassName_) throws G2AccessException {
    G2Definition definition = getDefinition0 (g2ClassName_);
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "getDefn", hc, g2ClassName_, context);
    if (definition == null) {
      //      if (com.gensym.classes.SystemPredicate.isSystemClass (g2ClassName_)){}
      definition = context.getDefinition (g2ClassName_);
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "getDefnFromContext",
		  hc, g2ClassName_, context, definition);
      storeClassDefinition (g2ClassName_, definition,
			    !(definition instanceof Definition));
      defnsTable.put(g2ClassName_, definition);
    }
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "getDefnRetn", hc, g2ClassName_, definition);
    return definition;
  }

    /**
     * @undocumented
     */
  public G2Definition getDefinition (int handle, int handleVersion) {
    if (handleVersion == G2__BaseImpl.SYSTEM_CLASS_FLAG) {
      if (sharingSystemClasses.booleanValue()) {
	return (G2Definition)systemClassManager.getDefinition(handle);
      } else {
	return (G2Definition)systemDefnsHandleTable.get(handle);
      }
    }

    G2__BaseImpl definition = (G2__BaseImpl)defnsHandleTable.get(handle);
    if (definition == null)
      return null;
    int storedHandleVersion = definition.getHandleVersion();
    if (storedHandleVersion == handleVersion)
      return (G2Definition)definition;
    else
      return null;
  }
    

    /**
     * Returns an already loaded G2Definition. This is to be called
     * only if the caller knows that it exists.
     * @param g2ClassName_ a Symbol naming the G2 class.
     * @throws G2AccessException if no class by that name has been stored
     */
    G2Definition getLoadedDefinition (Symbol g2ClassName_) throws G2AccessException {
      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "getLoadedDefinition",
		  hc, g2ClassName_);
      G2Definition definition = getDefinition0 (g2ClassName_);
      if (definition == null)
	throw new G2AccessException (i18n.format("noSuchClassInG2", g2ClassName_));
      return definition;
    }

    /**
     * Always returns a non-null value for the attribute, if possible.
     * It walks up the inheritance tree for inheritable attributes,
     * if necessary.
     */
  public java.lang.Object getClassAttributeValue (Symbol className, Symbol attrName) throws G2AccessException {
    //System.out.println("Getting attr " + attrName + " for " + className +
    //                   " hash: " + " context: " + context);
    G2Definition defn = getDefinition (className);// Force Loading if necessary
    if (defn instanceof Definition // user-defined-class
	&& slotIsInheritable (attrName)) {
      return getInheritableSlotValue (defn, attrName);
    } else 
      return defn.getClassAttributeValue (attrName);
  }
    
    final boolean slotIsInheritable (Symbol attrName) {
      for (int i=0; i<INHERITED_SLOTS_COUNT; i++)
	if (attrName.equals (slotsWithG2Inheritance[i]))
	  return true;
      return false;
    }

  private void resetInheritableSlots(G2Definition defn) throws G2AccessException{
    for (int i=0; i<INHERITED_SLOTS_COUNT; i++) {
      Symbol attrName = slotsWithG2Inheritance[i];
      Symbol defnClassName = defn.getClassName ();
      Hashtable slotTable  = getSlotTable (attrName);
      InheritedSlot slot   = (InheritedSlot) slotTable.get (defnClassName);
      slot.classInheritedFrom = null;
    }
  }

  private java.lang.Object getInheritableSlotValue (G2Definition defn, Symbol attrName) throws G2AccessException {
    Symbol defnClassName = defn.getClassName ();
    Hashtable slotTable  = getSlotTable (attrName);
    InheritedSlot slot   = (InheritedSlot) slotTable.get (defnClassName);
    if (slot.classInheritedFrom == null)
      updateSlot (slot, defn, attrName);
    return slot.value;
  }

  private final Hashtable getSlotTable (Symbol attrName) {
    for (int i=0; i<INHERITED_SLOTS_COUNT; i++)
      if (attrName.equals (slotsWithG2Inheritance[i]))
	return slotTables[i];
    throw new Error ("No SlotTable for " + attrName + ". Should never happen");
  }

    InheritedSlot getSlot (G2Definition defn, Symbol attrName) throws G2AccessException {
      Hashtable slotTable = getSlotTable (attrName);
      return (InheritedSlot) slotTable.get (defn.getClassName ());
    }

  private void updateSlot (InheritedSlot slot, G2Definition defn, Symbol attrName) {
    try {
      Symbol defnClassName = defn.getClassName ();
      Sequence classInheritancePath = defn.getClassInheritancePath(); // system classes not necessary
      for (int i=0; i<classInheritancePath.size (); i++) {
	Symbol superClass = (Symbol)classInheritancePath.elementAt (i);
	G2Definition superDefn = (G2Definition) getDefinition (superClass);
	//System.out.println ("Super definition for " + superClass + " = " + superDefn);
	//System.out.println ("UpdateSlot for " + defnClassName + " -> " + superDefn.getClassName ());
	// This should be a check of the InheritedSlots to see if classInheritedFrom
	// is the same as the class. If so use it, else continue;
	java.lang.Object slotValue = getAttributeValueFromDefinition (superDefn, attrName); //superDefn.getClassAttributeValue (attrName);
	if (slotValue != null) {
	  slot.setSlotValue (slotValue, this);
	  slot.classInheritedFrom = superClass;
	  break;
	}
      }
      if (slot.value == null)
	System.err.println ("WARNING: tried to get slot value for " + attrName + " for " +
			    defnClassName + " and failed to find a value. Returning null.");
      //System.out.println ("Updated " + attrName + " of " + defn.getClassName () + " = " + slot.value);
    } catch (G2AccessException gae) {
      Trace.exception (gae, null);
    }
  }

    /**
     * To be used by SystemClassManager to handle
     * the switching of its context to any live
     * connection.
     */
    void setContext (G2Access context) {
      this.context = context;
    }

    G2Access getContext() {
      return context;
    }

    /**
     * Debugging method
     */
    void dumpSlotTables () {
      if (false) {
	for (int i=0; i<INHERITED_SLOTS_COUNT; i++)
	  System.out.println (slotsWithG2Inheritance[i] + " = " + slotTables[i]);
      }
    }

    Object getAdapter (Symbol className_) {
      return adapterTable.get (className_);
    }


    static void debugPrintln(Object obj) {
      if(GensymApplication.getDevOption())
	System.out.println(obj);
    }

    /**
     * A class used by a user Definition to listen to its own
     * changes. The DefinitionEvent corresponding to a change is
     * fired by the Item. The ClassManager needs to be notified
     * of this change so it can update its Slots corresponding
     * to the Definition.
     */
    class SelfClassListener implements DefinitionListener {

      private ClassManager classManager;
      private Definition definition;
      private SubClassListener subClassListener;

      // variables for dealing with messages coming in while
      // initializing (i.e., after addDefinitionListener, and
      // before wireSubClassListener is finished)
      private volatile boolean fullyInitialized = false;
      private Vector pendingClassEvents = null;
      private Object pendingEventLock = new Object();

      SelfClassListener (ClassManager classManager, Definition definition) throws G2AccessException {
	this.classManager = classManager;
	this.definition = definition;

	// We are being careful that there might be changes coming from G2
	// for this definition, before we are fully set up.
	//
	// Each listener stores pendingEvents in a vector if events come before
	// we are fully initialized. This vector is flushed once we are
	// fullyIntialized.
	//
	// If we do get events during this process,
	// the worst that could happen is that we may do a little unnecessary
	// work under some circumstances, but we will always finish up
	// in the correct state.
	fullyInitialized = false;
	definition.addDefinitionListener(this);
	  
	Sequence superiorClasses = definition.getDirectSuperiorClasses ();
	Sequence classInheritancePath = definition.getClassInheritancePath();
	subClassListener = new SubClassListener (definition,
						 classInheritancePath,
						 superiorClasses);
	wireSubclassListener(superiorClasses);

	flushPendingEvents();
	  
	//this.cdm = cdm;
      }

      private void flushPendingEvents () {
	Vector currentEvents;
	synchronized(pendingEventLock) {
	  // Since this method calls itself recursively at the end,
	  // this method will eventually be called with
	  // pendingClassEvents == null.
	  if (pendingClassEvents == null) {
	    fullyInitialized = true;
	    return;
	  }
	  currentEvents = pendingClassEvents;
	  pendingClassEvents = null;
	}

	int size = currentEvents.size();
	for (int i = 0; i < size; i++) {
	  DefinitionEvent e = (DefinitionEvent)currentEvents.elementAt(i);

	  // NOTE: we bypass the real listener methods to avoid confusion
	  // between real events from outside and events processed from
	  // within here. Knowing whether to queue an event requires a distinction
	  // between the two types of events.
	  switch (e.getEventType()) {
	  case DefinitionEvent.CLASS_NAME_CHANGED:
	    classNameChangedImpl(e);
	    break;
	  case DefinitionEvent.CLASS_SPECIFIC_ATTRIBUTES_CHANGED:
	    classAttributeChangedImpl(e);
	    break;
	  case DefinitionEvent.DIRECT_SUPERIOR_CLASSES_CHANGED:
	    directSuperiorClassesChangedImpl(e);
	    break;
	  case DefinitionEvent.CLASS_INHERITANCE_PATH_CHANGED:
	    classInheritancePathChangedImpl(e);
	    staticAttributeChangedImpl(e);
	    deletedImpl(e);
	    break;
	  case DefinitionEvent.STATIC_ATTRIBUTE_CHANGED:
	    staticAttributeChangedImpl(e);
	    deletedImpl(e);
	    break;
	  case DefinitionEvent.DELETED:
	    deletedImpl(e);
	    break;
	  default:
	  }
	}
	// Recursively check if any events came in while we were processing
	// the last batch. We will always recurse at least once if there
	// were any pendingEvents.
	flushPendingEvents();
      }

      // final for optimization purposes
      // Note that event though fullyInitialized is checked in every
      // place this is called, we redo the check here in a thread-safe
      // manner, as the other checks are not thread-safe
      private final void storeEvent(Object o) {
	synchronized(pendingEventLock) {
	  if (!fullyInitialized) {
	    if (pendingClassEvents == null) {
	      pendingClassEvents = new Vector();
	    }
	    pendingClassEvents.addElement(o);
	  }
	}
      }	

      private void wireSubclassListener(Sequence superiorClasses) throws G2AccessException {
	for (int i=0; i<superiorClasses.size (); i++) {
	  Symbol directSuperiorClassName = (Symbol) superiorClasses.elementAt (i);
	  G2Definition directSuperior =
	    (G2Definition) classManager.getDefinition0 (directSuperiorClassName);
	  if (directSuperior instanceof Definition)
	    ((Definition)directSuperior).addDefinitionListener (subClassListener);
	}
      }

      private void unWireSubclassListener(Sequence superiorClasses) throws G2AccessException {
	for (int i=0; i<superiorClasses.size (); i++) {
	  Symbol directSuperiorClassName = (Symbol) superiorClasses.elementAt (i);
	  G2Definition directSuperior =
	    (G2Definition) classManager.getDefinition (directSuperiorClassName);
	  if (directSuperior instanceof Definition)
	    ((Definition)directSuperior).removeDefinitionListener (subClassListener);
	}
      }

      public void classAttributeChanged (DefinitionEvent e) {
	// fullyIntialized can only change from false to true.
	// This first test is an optimization for the most common case to
	// avoid an unnecessary method call and the lock it grabs.
	if (!fullyInitialized)
	  storeEvent(e);
	else
	  classAttributeChangedImpl(e);
      }

      public void classAttributeChangedImpl (DefinitionEvent e) {
	try {
	  ClassManager cdm = ClassManager.this;

	  Object newValue = e.getNewValue ();
	  //System.out.println ("SELF Attribute of " + ((Definition)e.getSource()).getClassName() + " changed. Updating Self");
	  G2Definition defn   = (G2Definition) e.getSource ();
	  Definition origDefn = e.getDefinitionOriginatingChange ();
	  Symbol attributeName = e.getAttributeName ();
	  if (!cdm.slotIsInheritable(attributeName))
	    return;
	  InheritedSlot classSlot = cdm.getSlot (defn, attributeName);
      
	  if (origDefn.equals (defn)) {
	    classSlot.placeValue = newValue;
	    classSlot.setSlotValue (newValue, cdm);
	  } else {
	    classSlot.classInheritedFrom = null;
	    cdm.updateSlot (classSlot, defn, attributeName);
	  }

	} catch (Exception ex) {
	  ex.printStackTrace ();
	}
      }

      @Override
      public void staticAttributeChanged (DefinitionEvent e) {
	if (!fullyInitialized)
	  storeEvent(e);
	else
	  staticAttributeChangedImpl(e);
      }

      public void staticAttributeChangedImpl (DefinitionEvent e) {
	try {
	  ClassManager cdm = ClassManager.this;

	  Object newValue = e.getNewValue ();
	  //System.out.println ("SELF Attribute " + e.getAttributeName () + " of " + ((Definition)e.getSource()).getClassName() + " changed. Updating Self");
	  G2Definition defn   = (G2Definition) e.getSource ();
	  Definition origDefn = e.getDefinitionOriginatingChange ();
	  Symbol attributeName = e.getAttributeName ();
	  if (!cdm.slotIsInheritable(attributeName))
	    return;
	  InheritedSlot classSlot = cdm.getSlot (defn, attributeName);
      
	  if (origDefn.equals (defn)) {
	    classSlot.placeValue = newValue;
	    if (newValue != null) {
	      classSlot.classInheritedFrom = defn.getClassName ();
	      classSlot.setSlotValue (newValue, cdm);
	      return;
	    }	  
	  }
	  classSlot.classInheritedFrom = null;
	  cdm.updateSlot (classSlot, defn, attributeName);

	} catch (Exception ex) {
	  ex.printStackTrace ();
	}
      }

      @Override
      public void classNameChanged (DefinitionEvent e) {
	if (!fullyInitialized)
	  storeEvent(e);
	else
	  classNameChangedImpl(e);
      }

      public void classNameChangedImpl (DefinitionEvent e) {
	debugPrintln ("SELF Name changed. Updating Self");
	if (e.getEventType() == DefinitionEvent.CLASS_NAME_CHANGED) {
	  Symbol oldName = (Symbol)e.getOldValue();
	  Definition def = (Definition)getDefinition0(oldName);
	  G2Gateway cnxn = (G2Gateway)context;
	  if (def != null) {
	    unloadClassDefinition(def, oldName);
	  }
	  Symbol newName = (Symbol)e.getNewValue();
	  storeClassDefinition(newName, def, false);
	}      
      }

      @Override
      public void directSuperiorClassesChanged (DefinitionEvent e) {
	if (!fullyInitialized)
	  storeEvent(e);
	else
	  directSuperiorClassesChangedImpl(e);
      }

      public void directSuperiorClassesChangedImpl (DefinitionEvent e) {
	debugPrintln ("SELF Direct Superiors changed. Updating Self");
	Sequence newSuperiors = (Sequence)e.getNewValue();
	subClassListener.reWire(newSuperiors);
      }

      @Override
      public void deleted (DefinitionEvent e) {
	if (!fullyInitialized)
	  storeEvent(e);
	else
	  deletedImpl(e);
      }

      public void deletedImpl (DefinitionEvent e) {
	Definition defn   = (Definition) e.getSource ();
	try{
	  Symbol className = defn.getClassName();
	  unloadClassDefinition(defn, className);    
	  ((G2Gateway)context).unloadClass(className);
	  debugPrintln ("SELF deleted. Updating Self");
	} catch (G2AccessException g2ae) {
	  // should be cached, so should not throw this exception
	  throw new UnexpectedException(g2ae);
	}
      }

      private void unloadClassDefinition(Definition definition,
					 Symbol className) {
	ClassManager.this.unloadClassDefinition(definition, className);
	try {
	  definition.removeDefinitionListener(this);
	  subClassListener.unhookSelf();
	} catch (G2AccessException g2ae) {
	  throw new UnexpectedException(g2ae);
	}
      }    

      @Override
      public void classInheritancePathChanged (DefinitionEvent e) {
	if (!fullyInitialized)
	  storeEvent(e);
	else
	  classInheritancePathChangedImpl(e);
      }

      public void classInheritancePathChangedImpl (DefinitionEvent e) {
	debugPrintln ("SELF inheritance path changed. Updating Self");
	G2Gateway cnxn = (G2Gateway)context;
	try {
	  Symbol className = definition.getClassName();
	  cnxn.unloadClass(className);
	  cnxn.getDefinition(className);
	  resetInheritableSlots(definition);
	} catch (G2AccessException g2ae) {
	  throw new UnexpectedException(g2ae);
	}
      }

      @Override
      public void classSpecificAttributesChanged (DefinitionEvent e) {
	if (!fullyInitialized)
	  storeEvent(e);
	else
	  classSpecificAttributesChangedImpl(e);
      }

      public void classSpecificAttributesChangedImpl (DefinitionEvent e) {
	debugPrintln ("SELF class specific attributes changed. Updating Self");
      }

    }



    /**
     * A class that is used by Definition to listen to and respond to
     * changes in its direct-superior classes. This is how the class
     * system is kept in sync with changes to the definition item
     * in G2.
     */
    class SubClassListener implements DefinitionListener {

      private Definition defn;
      private Sequence classInheritancePath;
      private Sequence directSuperiors;

      SubClassListener (G2Definition defn,
			Sequence classInheritancePath,
			Sequence directSuperiors) {
	this.defn = (Definition)defn;
	this.classInheritancePath = classInheritancePath;
	this.directSuperiors = directSuperiors;
      }

      void reWire(Sequence newSuperiors) {
	rehookSelf(directSuperiors, newSuperiors);
	directSuperiors = newSuperiors;
      }

      void unhookSelf() throws G2AccessException {
	int size = directSuperiors.size();
	for (int i = 0; i < size; i++) {
	  Object definition = directSuperiors.elementAt(i);
	  if (definition instanceof Definition) {
	    ((Definition)definition).removeDefinitionListener(this);
	  }
	}
      }

      /**
       * There has been no attempt to optimize the algorithm here, on the
       * principle that both Sequences will be very short, while the
       * classes in these Sequences may have long listener lists...
       */
      private void rehookSelf(Sequence oldSuperiors, Sequence newSuperiors) {
	Sequence classesRemoved =
	  oldSuperiors == null ? new Sequence() : (Sequence)oldSuperiors.clone();
	Sequence classesAdded =
	  newSuperiors == null ? new Sequence() : (Sequence)newSuperiors.clone();

	int size = classesRemoved.size();
	int index;

	// Ensure that classesRemoved and classesAdded both
	// have the correct members.
	for (int i = 0; i < size; i++) {
	  Symbol oldSuperior = (Symbol)oldSuperiors.elementAt(i);
	  if ((index = classesAdded.indexOf(oldSuperior)) != -1) {
	    classesAdded.removeElementAt(index);
	    classesRemoved.removeElement(oldSuperior);
	  }
	}

	ClassManager cdm = ClassManager.this;
	// unhook from the classesRemoved
	size = classesRemoved.size();
	for (int i = 0; i < size; i++) {
	  try {
	    G2Definition def =
	      cdm.getDefinition((Symbol)classesRemoved.elementAt(i));
	    if (def instanceof Definition)
	      ((Definition)def).removeDefinitionListener(this);
	  } catch (G2AccessException g2ae) {
	    Trace.exception(g2ae);
	  }
	}

	// hook up to the classesAdded
	size = classesAdded.size();
	for (int i = 0; i < size; i++) {
	  try {
	    G2Definition g2Def =
	      cdm.getDefinition((Symbol)classesAdded.elementAt(i));
	    // ensure that the class associated with this definition
	    // is actually loaded.
	    //Symbol className = g2Def.getClassName();
	    //((G2Gateway)context).getDefinition(className);
	    if (g2Def instanceof Definition) {
	      ((Definition)g2Def).addDefinitionListener(this);
	    }
	  } catch (G2AccessException g2ae) {
	    Trace.exception(g2ae);
	  }
	}
      }
	


      public void classAttributeChanged (DefinitionEvent e) {
	try {
	  ClassManager cdm = ClassManager.this;
	  Object newValue = e.getNewValue ();
	  //System.out.println ("New Value = " + newValue + "\nDenotation = " + com.gensym.core.DebugUtil.describe (e.getDenotation ()));
	  Symbol attributeName = e.getAttributeName ();
	  if (!cdm.slotIsInheritable(attributeName))
	    return;
	  InheritedSlot classSlot = cdm.getSlot (defn, attributeName);
	  Definition origDefn = e.getDefinitionOriginatingChange ();
	  Symbol changedClassName = ((Definition) e.getSource ()).getClassName ();
	  try {
	    if (!classSlot.value.equals (newValue) &&
		superClassChangeAffectsThisClass (changedClassName, classSlot.classInheritedFrom, classInheritancePath))
	      defn.processDefinitionEvent (new DefinitionEvent (defn,
								e.getEventType (),
								origDefn,
								attributeName,
								newValue,
								classSlot.value));
	  } catch (Exception ex) {
	    ex.printStackTrace ();
	  }
	} catch (G2AccessException gae) {
	  Trace.exception (gae, null);
	}
      }

      @Override
      public void staticAttributeChanged (DefinitionEvent e) {
	try {
	  debugPrintln ("SUB: Definition Attribtute changed. Updating!" +
			e);
	  ClassManager cdm = ClassManager.this;
	  Object newValue = e.getNewValue ();
	  //System.out.println ("New Value = " + newValue + "\nDenotation = " + com.gensym.core.DebugUtil.describe (e.getDenotation ()));
	  Symbol attributeName = e.getAttributeName ();
	  if (!cdm.slotIsInheritable(attributeName))
	    return;
	  InheritedSlot classSlot = cdm.getSlot (defn, attributeName);
	  Definition origDefn = e.getDefinitionOriginatingChange ();
	  Symbol changedClassName = ((Definition) e.getSource ()).getClassName ();
	  //System.out.println ("slotvalue = " + classSlot.value + " && newvalue = " + newValue);
	  if ((!classSlot.value.equals (newValue)) &&
	      superClassChangeAffectsThisClass (changedClassName, classSlot.classInheritedFrom, classInheritancePath))
	    defn.processDefinitionEvent (new DefinitionEvent (defn,
							      e.getEventType (),
							      origDefn,
							      attributeName,
							      newValue,
							      classSlot.value));
	} catch (G2AccessException gae) {
	  Trace.exception (gae, null);
	}
      }

      @Override
      public void classNameChanged (DefinitionEvent e) {
	debugPrintln ("SUB: Definition Name changed. Updating!");
      }
  
      @Override
      public void directSuperiorClassesChanged (DefinitionEvent e) {
	debugPrintln ("SUB: Definition direct-superior-classes changed. Updating");
      }

      @Override
      public void deleted (DefinitionEvent e) {
	debugPrintln ("SUB: Definition deleted. Updating");
      }

      @Override
      public void classInheritancePathChanged (DefinitionEvent e) {
	debugPrintln ("SUB: Definition inheritance-path changed. Updating");
      }

      @Override
      public void classSpecificAttributesChanged (DefinitionEvent e) {
	debugPrintln ("SUB: Definition class-specific-attributes changed. Updating");
      }

      private boolean superClassChangeAffectsThisClass (Symbol changedClassName,
							Symbol currentInheritedClassName,
							Sequence classInheritancePath) {
	/*System.out.print ("superClassChangeAffectsThisClass (" +
	  changedClassName + ", " + currentInheritedClassName + ", " +
	  classInheritancePath + ") = ");*/
	for (int i=0; i<classInheritancePath.size (); i++) {
	  Symbol className = (Symbol)classInheritancePath.elementAt (i);
	  if (className.equals (changedClassName))
	    {/*System.out.println ("T");*/return true;}
	  else if (className.equals (currentInheritedClassName))
	    {/*System.out.println ("F");*/return false;}
	}
	throw new RuntimeException ("Inconsistency in fanning out class changes. Please report this.");
      }

    }

}


/*
 * A class used to keep the pair of effective (possibly inherited) and
 * the in-place value together.
 */
class InheritedSlot {
  Object value;
  Object placeValue;
  Symbol classInheritedFrom;

  InheritedSlot (Object placeValue, Object value, Symbol classWithValue) {
    this.placeValue = placeValue;
    this.value      = value;
    this.classInheritedFrom = classWithValue;
  }

  void setSlotValue (Object newValue, ClassManager cdm) {
    value = newValue;
    if (false) {
      System.out.println ("Setting slot value from " + value + " to " + newValue);
      if (value == null || newValue == null)
	Thread.dumpStack ();
      cdm.dumpSlotTables ();
    }
  }

  @Override
  public String toString () {
    return "{" + placeValue + ", " + value + " from " + classInheritedFrom + "}";
  }

}


class SystemClassManager extends ClassManager {
  private int classIDGenerator = 1;

  SystemClassManager (G2Access context) {
    super (context);
    setContext (context);
  }

  @Override
  public void storeClassDefinition (Symbol g2ClassName,
				    G2Definition definition,
				    boolean isSystemClass) {
    throw new IllegalArgumentException ("System class manager called with Illegal arguments - " + g2ClassName);

  }

  public void storeClassDefinition (Symbol g2ClassName,
				    G2Definition definition) {
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "storeClassDefn", hc, g2ClassName, definition);
    synchronized (defnsTable) {
      if (defnsTable.get(g2ClassName) != null) {
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "classDefnFound",
		    g2ClassName);
	return;
      }
      defnsTable.put (g2ClassName, definition);
      SystemClassDefinitionImpl sysDef = (SystemClassDefinitionImpl)definition;
      int classID = sysDef.getClassID();
      if (classID == 0) {
	if(((G2Gateway)getContext()).makesOwnStubs()) {
	  classID = classIDGenerator++;
	  sysDef.setClassID(classID);
	} else {
	  throw new UnexpectedException(null, i18n.format("uninitializedSystemClass",
							  definition));
	}
      }
      systemDefnsHandleTable.put(classID, definition);
      try {
      } catch (Exception ex) {
	Trace.exception(ex);
      }
    }
  }

  /** @undocumented **/
  @Override
  public G2Definition getDefinition0 (Symbol g2ClassName_) {
    return (G2Definition) defnsTable.get (g2ClassName_);
  }

  /** @undocumented */
  public G2Definition getDefinition(int classID) {
    return (G2Definition) systemDefnsHandleTable.get(classID);
  }

}
