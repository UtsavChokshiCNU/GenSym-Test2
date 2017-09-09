
package com.gensym.classes;

import java.util.Hashtable;
import java.util.Enumeration;
import java.util.Vector;
import java.net.URL;
import java.net.MalformedURLException;

import com.gensym.core.DebugUtil;
import com.gensym.core.IntHashtable;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.message.MessageKey;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2Gateway;
import com.gensym.jgi.G2ConnectionInfo;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2SecurityException;
import com.gensym.jgi.ConnectionResolver;
import com.gensym.jgi.G2ItemDeletedException;
import com.gensym.jgi.G2ConnectionAdapter;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.util.ClassManager;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.CorruptionException;
import com.gensym.util.AttributeDenotation;
import com.gensym.util.Denotation;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.ItemEvent;
import com.gensym.util.ItemListener;
import com.gensym.util.WorkspaceEvent;
import com.gensym.util.UnexpectedException;
import com.gensym.util.StubInvalidationListener;
import com.gensym.util.StubInvalidationEvent;


public abstract class G2__BaseImpl implements G2__Base, G2__RemoteStub, ImplAccess, com.gensym.util.symbol.SystemAttributeSymbols, java.io.Serializable {

  static final long serialVersionUID = 2L;

  public static final Symbol g2ClassName = null;

  /*
   * Standard Tracing Requirements
   */
  private static MessageKey traceKey =
  Trace.registerMessageKey ("com.gensym.util.classes",
			    G2__BaseImpl.class);
  private static MessageKey traceAttrAccessKey =
         Trace.registerMessageKey ("com.gensym.classes.attr",
				   G2__BaseImpl.class);
  private static Resource i18nTrace =
  Trace.getBundle("com.gensym.classes.TraceMessages");
  private static final int DEF_TRACE_LEVEL = 5;
  private static final int DEF_WARN_LEVEL  = 2;
  
  private static final boolean attributeTracing = true;

  static Symbol CLASS_ATTRIBUTES_ = Symbol.intern ("CLASS-ATTRIBUTES");
  static Symbol INSTANCE_ATTRIBUTES_ = Symbol.intern ("INSTANCE-ATTRIBUTES");
  static Symbol DIRECT_SUPERIOR_CLASSES_ = Symbol.intern ("DIRECT-SUPERIOR-CLASSES");
  static Symbol CLASS_INHERITANCE_PATH_  = Symbol.intern ("CLASS-INHERITANCE-PATH");
  
  private static final Symbol ATTRIBUTE_NAME_ =
  Symbol.intern ("ATTRIBUTE-NAME");

  private static final Symbol G2_GET_ATTRIBUTE_VALUES_OF_ITEM_ = Symbol.intern ("G2-GET-ATTRIBUTE-VALUES-OF-ITEM");
  private static final Symbol G2_GET_TEXT_OF_ATTRIBUTE_        = Symbol.intern ("G2-GET-TEXT-OF-ATTRIBUTE");
  private static final Symbol G2_GET_ATTRIBUTE_TEXTS_OF_ITEM_  = Symbol.intern ("G2-GET-ATTRIBUTE-TEXTS-OF-ITEM");
  private static final Symbol G2_CONCLUDE_IN_ITEM_             = Symbol.intern ("G2-CONCLUDE-IN-ITEM");

  // To keep control of data stored outside instances, a three-tiered hashtable is needed.
  // This is the "outer most" hashtable.
  private static final Hashtable contextHash = new Hashtable();
  private static final Hashtable contextWrappedHash = new Hashtable();

  // These are set to be Strings only for ease of debugging.
  // For performance, == is performed on these, so the contents
  // and class of these objects is irrelevant
  private static final java.lang.Object IMMUTABLE = "IMMUTABLE";
  private static final java.lang.Object WORKSPACE_UPDATES = "WORKSPACE_UPDATES";
  private static final java.lang.Object ITEM_UPDATES = "ITEM_UPDATES";
  private static final java.lang.Object NO_UPDATES = "NO_UPDATES";
  
  /*
   * This table holds the list of all known virtual attributes. Since
   * user-defined attributes should not shadow virtual-attributes
   * we assume that if the the attribute is not updatable
   * by subscribing to its denotation. By default, the value
   * associated with the class-name key is Boolean.FALSE.
   * In those cases where the virtual attribute update
   * is received via a workspace subscription, the value
   * is Boolean.TRUE.
   */
  private static final Hashtable virtualAttributesTable = new Hashtable (73);
  private static final Hashtable workspaceUpdatableSlots = new Hashtable(1);
  static {
    workspaceUpdatableSlots.put(CONNECTION_STYLE_, WORKSPACE_UPDATES);
  }

  static {
    virtualAttributesTable.put (CLASS_, IMMUTABLE);
    virtualAttributesTable.put (FOUNDATION_CLASS_, IMMUTABLE);
    virtualAttributesTable.put (NAMES_, ITEM_UPDATES);
    virtualAttributesTable.put (ITEM_STATUS_, ITEM_UPDATES);
    virtualAttributesTable.put (ITEM_ACTIVE_, ITEM_UPDATES);
    virtualAttributesTable.put (CONTAINING_MODULE_, NO_UPDATES);
    virtualAttributesTable.put (ITEM_NOTES_, ITEM_UPDATES);
    virtualAttributesTable.put (ITEM_X_POSITION_, WORKSPACE_UPDATES);
    virtualAttributesTable.put (ICON_X_POSITION_, NO_UPDATES);
    virtualAttributesTable.put (ITEM_Y_POSITION_, WORKSPACE_UPDATES);
    virtualAttributesTable.put (ICON_Y_POSITION_, NO_UPDATES);
    virtualAttributesTable.put (ICON_HEADING_, WORKSPACE_UPDATES);
    virtualAttributesTable.put (ICON_REFLECTION_, WORKSPACE_UPDATES);
    virtualAttributesTable.put (ITEM_HEIGHT_, WORKSPACE_UPDATES);
    virtualAttributesTable.put (ICON_HEIGHT_, NO_UPDATES);
    virtualAttributesTable.put (ITEM_WIDTH_, WORKSPACE_UPDATES);
    virtualAttributesTable.put (ICON_WIDTH_, NO_UPDATES);
    virtualAttributesTable.put (BACKGROUND_COLOR_, WORKSPACE_UPDATES);
    virtualAttributesTable.put (FOREGROUND_COLOR_, WORKSPACE_UPDATES);
    virtualAttributesTable.put (TEXT_COLOR_, WORKSPACE_UPDATES);
    virtualAttributesTable.put (BORDER_COLOR_, WORKSPACE_UPDATES);
    virtualAttributesTable.put (STRIPE_COLOR_, WORKSPACE_UPDATES);
    virtualAttributesTable.put (CONNECTION_POSITION_SEQUENCE_, WORKSPACE_UPDATES);
    virtualAttributesTable.put (MANUALLY_DISABLEDQ_, WORKSPACE_UPDATES);
    virtualAttributesTable.put (ICON_COLOR_, WORKSPACE_UPDATES);
    virtualAttributesTable.put (RELATIONSHIPS_, NO_UPDATES); //not true
    virtualAttributesTable.put (ITEMS_IN_THIS_RELATION_, NO_UPDATES);//not true
    virtualAttributesTable.put (NAME_BOX_, NO_UPDATES);
    virtualAttributesTable.put (TEXT_ALIGNMENT_, ITEM_UPDATES);
    virtualAttributesTable.put (CURRENT_ATTRIBUTE_DISPLAYS_, NO_UPDATES);
    virtualAttributesTable.put (TABLE_HEADER_, NO_UPDATES);
    virtualAttributesTable.put (VALUES_FOR_TABLE_OF_VALUES_, NO_UPDATES);
    virtualAttributesTable.put (CHART_AXIS_COMPUTED_DETAILS_, ITEM_UPDATES);
    virtualAttributesTable.put (CHART_DATA_SERIES_, ITEM_UPDATES);
    virtualAttributesTable.put (TABLE_CELLS_, WORKSPACE_UPDATES);
    virtualAttributesTable.put (EVALUATION_ATTRIBUTES_, NO_UPDATES);
    virtualAttributesTable.put (VALUE_STRUCTURE_, NO_UPDATES);
    virtualAttributesTable.put (VALUE_STRUCTURE_USING_UNIX_TIME_, NO_UPDATES);
    virtualAttributesTable.put (EFFECTIVE_DATA_TYPE_, NO_UPDATES);
    virtualAttributesTable.put (HISTORY_, NO_UPDATES);
    virtualAttributesTable.put (HISTORY_USING_UNIX_TIME_, NO_UPDATES);
    virtualAttributesTable.put (G2_ARRAY_SEQUENCE_, NO_UPDATES);
    virtualAttributesTable.put (G2_LIST_SEQUENCE_, NO_UPDATES);
    virtualAttributesTable.put (ICON_VARIABLES_, WORKSPACE_UPDATES);
    virtualAttributesTable.put (TABLE_ROWS_, WORKSPACE_UPDATES); 
    virtualAttributesTable.put (TABLE_FONT_SIZE_, IMMUTABLE);
    virtualAttributesTable.put (REPRESENTED_ITEM_, IMMUTABLE);
    virtualAttributesTable.put (TABLE_LAYOUT_, NO_UPDATES);
    virtualAttributesTable.put (FORMAT_TYPE_, WORKSPACE_UPDATES);
    virtualAttributesTable.put (TEXT_X_MAGNIFICATION_, WORKSPACE_UPDATES);
    virtualAttributesTable.put (TEXT_Y_MAGNIFICATION_, WORKSPACE_UPDATES);
    virtualAttributesTable.put (VALUE_TO_DISPLAY_, NO_UPDATES); //check
    virtualAttributesTable.put (BUTTON_STATUS_, NO_UPDATES); //check
    virtualAttributesTable.put (SLIDER_VALUE_, NO_UPDATES); //check
    virtualAttributesTable.put (TYPE_IN_BOX_VALUE_, NO_UPDATES); //check
    virtualAttributesTable.put (ITEM_COLOR_PATTERN_, WORKSPACE_UPDATES);
    virtualAttributesTable.put (LAYER_POSITION_, WORKSPACE_UPDATES);
    virtualAttributesTable.put (NAME_BOX_ITEM_, NO_UPDATES);
    virtualAttributesTable.put (CACHED_MEDIA_BIN_, NO_UPDATES);
    virtualAttributesTable.put (ATTRIBUTE_DISPLAY_ITEMS_, NO_UPDATES);
    virtualAttributesTable.put (REPRESENTATION_TYPE_, IMMUTABLE);
    virtualAttributesTable.put (CONNECTION_POSITION_SEQUENCE_, WORKSPACE_UPDATES);
    virtualAttributesTable.put (CONNECTION_IS_DIRECTED_, WORKSPACE_UPDATES);
    virtualAttributesTable.put (TEXT_, ITEM_UPDATES);
    virtualAttributesTable.put (TYPE_IN_BOX_VARIABLE_OR_PARAMETER_, NO_UPDATES);
    //ui-client-* could be updated by the real slot that underlies them
    virtualAttributesTable.put (UI_CLIENT_USER_MODE_, NO_UPDATES); 
    virtualAttributesTable.put (UI_CLIENT_USER_NAME_, NO_UPDATES);
    virtualAttributesTable.put (UI_CLIENT_REMOTE_HOST_NAME_, NO_UPDATES);
    virtualAttributesTable.put (UI_CLIENT_OPERATING_SYSTEM_TYPE_, NO_UPDATES);
    virtualAttributesTable.put (UI_CLIENT_TIME_OF_LAST_CONNECTION_, NO_UPDATES);
    virtualAttributesTable.put (UI_CLIENT_USER_NAME_IN_OPERATING_SYSTEM_, NO_UPDATES);
    virtualAttributesTable.put (UI_CLIENT_SPECIFIC_LANGUAGE_, NO_UPDATES);
    virtualAttributesTable.put (UI_CLIENT_CONNECTION_STATUS_, NO_UPDATES);
    virtualAttributesTable.put (UI_CLIENT_USER_IS_VALID_, NO_UPDATES);
    virtualAttributesTable.put (UI_CLIENT_MODE_IS_VALID_, NO_UPDATES);
    virtualAttributesTable.put (UI_CLIENT_INTERFACE_, NO_UPDATES);
    virtualAttributesTable.put (PERMANENT_, NO_UPDATES);
    virtualAttributesTable.put (TRANSIENT_, NO_UPDATES);
  }

  private static Sequence makeWorkspaceInitialInfoList() {
    Sequence initialInfoList = new Sequence();
    for (Enumeration en = virtualAttributesTable.keys();
	 en.hasMoreElements();) {
      Symbol attr = (Symbol)en.nextElement();
      java.lang.Object value = virtualAttributesTable.get(attr);
      if (WORKSPACE_UPDATES.equals(value) || IMMUTABLE.equals(value)) {
	initialInfoList.addElement(attr);
      }
    }
    for (Enumeration en = workspaceUpdatableSlots.keys();
	 en.hasMoreElements();) {
      Symbol attr = (Symbol)en.nextElement();
      java.lang.Object value = workspaceUpdatableSlots.get(attr);
      if (WORKSPACE_UPDATES.equals(value)) {
	initialInfoList.addElement(attr);
      }
    }
    return initialInfoList;
  }

  private static Sequence workspaceInitialInfoList =
  makeWorkspaceInitialInfoList();

  private static final int UNINITIALIZED_DEFINITION_FLAG = -1;
  public static final int SYSTEM_CLASS_FLAG = -2;
    
  private com.gensym.jgi.ConnectionResolver connectionResolver;
  
  // This is the "second tier" of hashtable: it is a pointer to the one
  // contained in contextHash for a given context.
  private transient IntHashtable itemHash;

  private int handle;
  /** This key can be used as a hashCode stand-in when the G2Access is known
   * to be the correct one for this Item. It is used internally during finalize
   * to remove the Item data from the appropriate Item hashtable. */
  private Integer handleKey;
  private int definitionHandle = UNINITIALIZED_DEFINITION_FLAG;
  private int definitionHandleVersion = UNINITIALIZED_DEFINITION_FLAG;

  private transient int hashCode;
  private transient boolean hashIsNotSet = true;
  private boolean itemIsValid;

  /**
   * @deprecated Made public temporarily
   */
  protected transient ItemData data;

  protected transient ClassManager classManager;
  /** This object's connection to the G2 from whence it originated */
  protected transient G2Access context;

  // It would be nicer to do this as follows:
  // protected void setWrapped(G2__BaseImpl wrapped) {
  //   wrapped.wrapper = this;
  // }
  // However, since this involves re-doing classtools code for
  // generating uses of that method, we'll leave it for when
  // we have to upgrade our classtools. rpenny 11/22/99
  /**
   *@undocumented
   */
  public G2__BaseImpl wrapper;
  
  private static final java.lang.Object notDownloaded = new java.lang.Object ();

  static final Symbol WILDCARD_ = Symbol.intern("*") ;
  static final Symbol[] WILDCARD_ARRAY = {WILDCARD_};

  G2__BaseImpl () {
    handle = 0;
    handleKey =  -super.hashCode();
    data = makeDataForItem();
    data.attributes = new Structure();
    itemIsValid = true;
  }


  /* Because we are supporting both the "old" three argument constructor and the
     "new" four argument constructor, we are separating out some of the
     otherwise duplicated code here in a two argument constructor (which should
     never be called by outside code, but probably we can't enforce that.) */
  G2__BaseImpl (G2Access context, int handle) {
    this.context = context;
    classManager = context.getClassManager();
    connectionResolver =
      ConnectionResolver.getConnectionResolver((G2Gateway)context);
    this.handle = handle;

    int handleKeyInt = (handle == 0 ? -super.hashCode () : handle);
    handleKey = handleKeyInt;
    if (handle == 0) {
      // Generate a negative unique number for by-copy Item's 
      // (i.e. wont conflict with "by-handle" data
      //handleKeyInt = -super.hashCode();
      // If an independant construction, must ensure that the CLASS att is set
    } else {
    }

    data = makeDataForItem ();
  }


  G2__BaseImpl (G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    this(context, handle);
    //    com.gensym.tests.Debug3Tier.add_data ("create(5)", this + "(" + handle + "v" + handleVersion + ")");

    this.wrapper = wrap;
    if (handle > 0 && wrap == null ) {
      IntHashtable itemHashLocal = getItemHash();
      synchronized (itemHashLocal) {
	ItemData hashedData = (ItemData)itemHashLocal.get(handle);
	if (hashedData == null) {
	  itemHashLocal.put(handle, data);
	  this.handleVersion = handleVersion;
    	  data.handleVersion = handleVersion;
	  itemIsValid = true;
	} else {

	  //com.gensym.tests.Debug3Tier.add_data ("found-prior(5)", "This = " + this + "; prior data = " + hashedData + " ; new = " + data);
	    if (handleVersion < hashedData.handleVersion) {
		// can happen if an instance of a user-class gets deleted
		// and its ICP handle re-used before it is able to finish
		// downloading its own class information
	      //com.gensym.tests.Debug3Tier.add_data ("create-wierd(5)", this + ";old " + hashedData + "; new = " + data);
		invalidateSelf();
		if (com.gensym.core.GensymApplication.getDevOption())
		  System.out.println("Warning:  Current item being created has already been deleted in G2:  " + this + "(v" + handleVersion + "); current version = " + hashedData.handleVersion);
	    } else if (handleVersion == hashedData.handleVersion) {
		// Why would this be?
		// (Note: we saw this error message when it was before the
		//        handle version was set up.  We think that it
		//        really should have been one of the other error
		//        conditions, probably the last one: new handle version
		//        > hashed data's version.)
	      //com.gensym.tests.Debug3Tier.add_data ("create-wierd2(5)", this + ";saved=" + hashedData + ";new = " + data);

		(new InvalidItemException((Item)this, "New item found duplicate data in hash table " + this + "(" + handle + "v" + handleVersion + ");previousData=" + hashedData)).printStackTrace();
		// Reusing old data.  Right?  Dunno.
		data = hashedData;
	    } else { // this is even more confusing if this were to happen
		// This would mean that this item is more recent than
		// the data in the hashtable is, but for some reason
		// the data in the hashtable didn't get cleared out
		// when the previous item got destroyed.
		// NOTE: haven't seen this case either
		// Note 2: as above, we may have seen it, but aren't sure.
	      //com.gensym.tests.Debug3Tier.add_data ("create-wierd3(5)", this + ";saved =" + hashedData + " ; new = " + data);
		hashedData.itemIsValid = false;
		(new InvalidItemException((Item)this, "New item replacing data in hash table " + this + ";previousData=" + hashedData)).printStackTrace();
		// This wasn't done in the constructor if there was previous data
		// but we're overwriting the old data now, so fix up the hashtable too.
		IntHashtable myItemHash = getItemHash();
		synchronized (myItemHash) {
		    myItemHash.put(handle, data);
		}
	    }
	}
      }
    }
    synchronized(data) {
      data.referenceCount++;
    }
    data.attributes = (attributes != null ? attributes : new Structure());
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "creatingItemImpl",
		context, handle, attributes);
    }

  
  /* HQ-4463966: This is the old constructor */
  private ItemData savedHashedData = null;

  G2__BaseImpl (G2Access context, int handle, Structure attributes) {
    this (context,handle);
    if (handle > 0) {
      IntHashtable itemHashLocal = getItemHash();
      synchronized (itemHashLocal) {
	ItemData hashedData = (ItemData)itemHashLocal.get(handle);
	if (hashedData == null)
	  itemHashLocal.put(handle, data);
	else
	  //this is an error condition, but we can't figure out what
	  //the problem is until we have had the handle version set
	  //properly, which sadly cannot be done in this constructor,
	  //because it doesn't take enough arguments, and there are
	  //10,000 inheritors, so changing the argument list of this
	  //constructor is not practical.  yduJ, 10/21/02
	  //com.gensym.tests.Debug3Tier.add_data ("found-prior(3)", "This = " + this + "; prior data = " + hashedData + " ; new = " + data);
	  savedHashedData = hashedData;
      }
    }
    synchronized(data) {
      data.referenceCount++;
    }
    data.attributes = (attributes != null ? attributes : new Structure());
//     com.gensym.tests.Debug3Tier.add_data ("create(3)", this + " itemData: " + data);
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "creatingItemImpl",
		context, handle, attributes);
    }



  /**
   * @undocumented
   */
  public java.lang.Object getG2ItemLock() {
    return getData();
  }

  public abstract Symbol getG2ClassName() throws G2AccessException;

  private void _setDefinition(G2Definition definition) {
    if (definition != null) {// Mark as such
      data.definition = definition;
      data.fullyInitialized = true;
      if (definition instanceof G2__BaseImpl) {
	definitionHandle = ((G2__BaseImpl)data.definition).handle;
	definitionHandleVersion = ((G2__BaseImpl)data.definition).handleVersion;
      } else {
	definitionHandle = ((SystemClassDefinitionImpl)data.definition).getClassID();
	definitionHandleVersion = SYSTEM_CLASS_FLAG;
      }
    }
  }

  /**
   * Should only be called, when there is absolute knowledge that this stub represents
   * an instance of the specified G2 Class Name.
   * @undocumented
   */
  public void setInternalG2ClassName(Symbol g2ClassNameIn) {
    synchronized(data) {
      data.attributes.setAttributeValue (CLASS_, g2ClassNameIn);
      if (handle != 0)
	_setDefinition(context.getClassManager().getDefinition0 (g2ClassNameIn));
    }
  }

  @Override
  public G2Definition getDefinition () throws G2AccessException {
    synchronized (data) {
      if (data.definition == null) {
	if (!data.fullyInitialized)
	  _setDefinition(context.getClassManager().getDefinition0 ((Symbol)data.attributes.getAttributeValue (CLASS_, null)));
	else {// 3rd tier
	  if (Trace.getTraceOn())
	    Trace.send(DEF_TRACE_LEVEL, traceKey, i18nTrace,
		       "3tierGetDefinition", definitionHandle,
		       definitionHandleVersion, this);
	  if (definitionHandle == UNINITIALIZED_DEFINITION_FLAG) { // wasn't set in middle-tier
	    Trace.send(DEF_TRACE_LEVEL, traceKey, i18nTrace,
		       "g2biDefinitionNotItitialized", this);
	    _setDefinition(((G2Gateway)context).getDefinition((Item)this));
	  } else
	    data.definition =
	      (G2Definition)((G2Gateway)context).getDefinition(definitionHandle,
							       definitionHandleVersion);
	}
      }
    }
    return data.definition;
  }

  protected final java.lang.Object getStaticAttributeValue (Symbol attrName) throws G2AccessException {

    java.lang.Object staticAttrValue =
      classManager.getClassAttributeValue (getG2ClassName (), attrName);
    return staticAttrValue;
  }

  // HACK: should not be here. should be removed once all our user classes
  // have been regenerated (for ScienceSystems too?)
  /**
   * @undocumented
   */
  protected final void setStaticAttributeValue(Symbol attrName, java.lang.Object value) {
  }

  /**
   * Gets a copy of the attributes of the item
   */
  @Override
  public Structure getAttributes () {
    synchronized (data) {
      return (Structure)getActualAttributes().clone ();
    }
  }

  /**
   * This is part of the pseudo-class stuff. An item may be embedded inside
   * another item, in which case the "real" ItemData is the ItemData that
   * belongs to the outer item.
   * @undocumented
   * @see com.gensym.jgi.download.PseudoClassGenerator
   */
   protected final ItemData getPrincipalData() {
     if (wrapper == null)
       return data;
     else
       return wrapper.data;
   }

  /**
   * This is part of the pseudo-class stuff
   * @undocumented
   * @see com.gensym.jgi.download.PseudoClassGenerator
   */
  protected final Structure getActualAttributes() {
    if (wrapper == null)
      return data.attributes;
    else
      return wrapper.data.attributes;
  }

  /**
   * @deprecated Do not use this directly
   */
  @Override
  public final G2Access getContext () {
    return context;
  }

  private java.lang.Object downloadAttribute(Symbol attrName, boolean all) throws G2AccessException {
//       com.gensym.util.Debug3Tier.add_data ("downloadAttribute;", this + ";" +
// 					   attrName + ";" + all + ";" + isValid());
    // Start up registration here...
    AttributeDenotation attrDentn;
    if (all)
      attrDentn = AttributeDenotation.WILDCARD_DENOTATION;
    else
      attrDentn = newAttributeDenotation (attrName);
    if (attributeTracing) {
      Trace.send (DEF_TRACE_LEVEL, traceAttrAccessKey, i18nTrace,
		  "iidownloadAttribute", this, attrName);
    }
    //System.out.println ("   HACK: Getting Attribute value with denotation = " + attrDentn.print () + " of size " + attrDentn.size ());
    java.lang.Object retnValue = context.getValue ((Item)this, attrDentn);
    //System.out.println ("   HACK: Dowloaded value = " + retnValue);
    //DebugUtil.setPause (true);
    //DebugUtil.pause ("downloadAttribute (" + attrName + ", " + all + ") >", true);
    if (all) {
      data.setAttributes ((Structure) retnValue); // We already have the lock
      retnValue = ((Structure)retnValue).getAttributeValue (attrName, null);
    }
//      System.out.println ("   HACK: Dowloaded value for attribute: " +
//      attrName + " = " + retnValue + " this=" + this);
    return retnValue;
  }

  /** @undocumented.
   * for three tiers - return retrieved data from G2
   */
  protected final Sequence makeSnapshot(Symbol[] attrNames) {
    if (data.subscriptionManager == null) {
    	return null;
    }
    Sequence rtnData = new Sequence();
    try {
      java.lang.Object attributes = null;
      for (int i = 0; i < attrNames.length; i++) {
        if (attrNames[i].equals(WILDCARD_))
          attributes = data.attributes;
        else
          attributes = data.attributes.getAttributeValue(attrNames[i]);

        rtnData.add(new Structure(new Symbol[] {INITIAL_VALUE_, SUBSCRIPTION_HANDLE_},
                                  new java.lang.Object[] {attributes,
                                                          data.subscriptionManager.getHandleByAttributeName(attrNames[i])},
                                                          2));
      }
    }
    catch (NoSuchAttributeException ex) {
      throw new CorruptionException(ex, "NO such attribute");
    }
    //catch (NtwIllegalArgumentException ex) {
    //   ex.printStackTrace();
    //}

    return rtnData;
  }

  /**
   * @undocumented Hack to reduce RPC's in class loading
   * @deprecated
   */
 /*public void subscribe () throws G2AccessException {
    Vector vec = new Vector();
    vec.add(WILDCARD_);
    subscribe(vec);
  } */

  //@author fy 2/25/00
  public void subscribe (Vector attributeNames) throws G2AccessException {
    //Make attribute denotations
    Sequence attributeDenotation = new Sequence();
    int wildcardIndex = -1;
    for (int i=0; i < attributeNames.size(); i++) {
      if (attributeNames.elementAt(i).equals(WILDCARD_)) {
	wildcardIndex = i;
        attributeDenotation.insertElementAt(WILDCARD_DENOTATION, 0);
      } else {
        AttributeDenotation attrDentn = new AttributeDenotation((Symbol) attributeNames.elementAt(i));
        attributeDenotation.addElement(attrDentn);
      }
    }
    if (wildcardIndex > 0) {
      attributeNames.removeElementAt(wildcardIndex);
      attributeNames.insertElementAt(WILDCARD_, 0);
    }
    java.lang.Object  initData = null;
    synchronized (data) { // each item subscribed to G2 once
	Sequence subscpnData = context.subscribeToItemMultiple ((Item)this, attributeDenotation, USER_DATA);
	// the subscribe() method may be called independently
        if (data.subscriptionManager == null)
          data.subscriptionManager = new SubscriptionManager();

	DebugUtil.pause ("subscribe [case 1] >", true);
	try {
          for (int i=0; i < subscpnData.size(); i++) {
	    Integer sHandle = ((Integer) ((Structure) subscpnData.get(i)).getAttributeValue (SUBSCRIPTION_HANDLE_));
	    initData = ((Structure) subscpnData.get(i)).getAttributeValue (INITIAL_VALUE_);
            //update subscriptionManager/attributeHandledata for unsubscribing and making snap shot for tree-tier later
	    data.subscriptionManager.setAttributeHandleData((Symbol) attributeNames.get(i), sHandle.intValue());
            //add the data into attribute
            if (attributeNames.elementAt(i).equals(WILDCARD_)) {
              data.attributes = (Structure) initData;
	    }
            else {
		      if (data.attributes == null){
		    	  data.attributes = new Structure();	      
		      }
              data.attributes.setAttributeValue((Symbol) attributeNames.get(i), initData);
	    }
          }
	} catch (NoSuchAttributeException nsae) {
	  throw new CorruptionException(nsae, "No such attribute");
	}      

	DebugUtil.pause ("subscribe [case 2] >", true);

    }
    //System.out.println (" subscribe () returning -> " + initData);
    Trace.send (DEF_WARN_LEVEL, traceKey, i18nTrace, "iisubscribe",
		this, initData);
				
    //return initData;
  }


  //Unsubscribe multiple attributes - fy 02/24/00
  void unsubscribe (Vector attributeNames) throws G2AccessException {
    if (data.subscriptionManager == null) {
    	return;
    }

    Sequence seq = new Sequence();

    // Find out corresponding subscribeHandle for attributeNames
    //int[] subscribedHandles = new int[attributeNames.size()];
    for (int i=0; i < attributeNames.size(); i++) {
       int sHandle = data.subscriptionManager.getHandleByAttributeName((Symbol) attributeNames.get(i));
       seq.addIntElement(sHandle);
       if (sHandle != 0)
            data.subscriptionManager.removeAttributeHandleData((Symbol) attributeNames.get(i), 0);
    }

    if (isValid())
      context.unsubscribeToItemMultiple (seq);


  }

  /*private boolean currentlySubscribed () {
    return data.itemCurrentlySubscribed;
  } */

  public void dispose () {
//     com.gensym.util.Debug3Tier.add_data ("dispose", this);
    if (handle <= 0){
    	return; //by-copy case
    }
    IntHashtable itemHashLocal = getItemHash();
    synchronized (itemHashLocal) {
      ItemData hashedData = (ItemData)itemHashLocal.get(handle);

      // NOTE: due to the possibility that an item can have dispose
      // called on it even after its ICP handle has been reused,
      // it is best to check the handleVersion before doing anything
      // bad to the itemHash (such as removing an ItemData that really
      // belongs to some other item.
      if (hashedData != null && hashedData.handleVersion <= handleVersion) {
	itemHashLocal.remove(handle);
	hashedData.itemIsValid = false;
//      com.gensym.util.Debug3Tier.add_data ("dispose-ok", this + ";" + hashedData.handleVersion);
      }
    }
    classManager = null;
    itemIsValid = false;
    // dispatch the callback
    notifyInvalidationListeners ();
  }
  // Should note that this signature is no longer used.
  //fy modified 02/25/00 for multiple attribute case
  @Override
  public void processItemEvent (ItemEvent ie) {
    int eventID = ie.getID();
    ItemData principalData = getPrincipalData();

    if (principalData == null)
      return;  // we can't do anything without this!!!

    //get subscriptionManager
    SubscriptionManager subscriptionManager = principalData.subscriptionManager;
    if (subscriptionManager == null){
    	return;
    }
    ItemListener itemListener = null;

    // This code is being paranoid about making sure that
    // the item never fails to send an itemDeleted event
    // in any situation where it has any chance of sending
    // the event, even if it has become invalid for some
    // reason.
    if (!isValid()) {
      if (eventID == ItemEvent.DELETE) {
	itemListener = subscriptionManager.getAllListeners();
	if (itemListener != null)
	  itemListener.itemDeleted (ie);
      }
      return;
    }

    updateLocalCache (ie);
    //get attribute name
    Symbol attributeName = null;
    Structure str = (Structure) ie.getDenotation().elementAt(0);
    try {
      attributeName = (Symbol) str.getAttributeValue(Denotation.NAME_);
    }
    catch (NoSuchAttributeException ex) {
      throw new CorruptionException(ex, "No such attribute");
    }
    //get active listeners if there is wildcard in attributeHashtable add its listener into
    itemListener = subscriptionManager.getItemListeners(attributeName);

    Trace.send (DEF_WARN_LEVEL, traceKey, i18nTrace, "processItmEvt",
		ie.getItem (), ie.getModificationCode(), itemListener);
    if (itemListener != null)	// We could be subscribing just to keep the cache current
      switch(eventID) 
	{
	case ItemEvent.MODIFY:
	  itemListener.itemModified (ie);
	  break;
	case ItemEvent.DELETE:
	  invalidateSelf();
          //      com.gensym.util.Debug3Tier.add_data ("delete", this);
	  itemListener.itemDeleted (ie);
	  break;
	default:
	  throw new RuntimeException ("New event type in ItemEvent. Please ask vkp to add case in processItemEvent");
	}
  }
	

  private static final java.lang.Object ATTRIBUTES_KEY = new java.lang.Object();

  /*
   * The guts of getting attribute values. I'm not entirely satisfied with
   * the implementation. On one hand, we need to be efficient about not
   * calling G2 to get information piecemeal, on the other, subscribing to
   * all attributes is a heavy load on the server. But this code is trying
   * to be too smart about it. It needs to be simpler -vkp, 11/12/97
   */
  private java.lang.Object getAttributeValueImpl (Symbol attrName) throws G2AccessException {
    synchronized (data.attributes) {
      Structure attributes = data.attributes;
      java.lang.Object attrValue = attributes.getAttributeValue (attrName, notDownloaded);
      if (attributeTracing) {
	Trace.send (DEF_TRACE_LEVEL, traceAttrAccessKey, i18nTrace, "getAttrValue",
		    this, attrName, attrValue,
		    attributeIsCached (attrName) ? Boolean.TRUE : Boolean.FALSE);
	Trace.send (DEF_TRACE_LEVEL, traceAttrAccessKey, i18nTrace, "itemImplState",
		    new java.lang.Object [] 
		    {attributeSendsUpdates (attrName) ? Boolean.TRUE : Boolean.FALSE,
		     data.workspaceCurrentlySubscribed ? Boolean.TRUE : Boolean.FALSE,
		     virtualAttributesTable.get (attrName)});
      }

      // Deal with by copy case
      if (handle <= 0) {
	if (notDownloaded.equals(attrValue))
	  return null;
	else
	  return attrValue;
      }


      boolean isCached = attributeIsCached (attrName);
      if (!isCached) {
        attrValue = downloadAttribute (attrName, false);
      } else {
        if (notDownloaded.equals(attrValue)){ // maybe this should throw an exception?
          attrValue = downloadAttribute (attrName, false);
          attributes.addAttribute(attrName, attrValue);
        }
      }

      if (attributeTracing)
	Trace.send (DEF_TRACE_LEVEL, traceAttrAccessKey, i18nTrace, "retnAttrValue",
		    this, attrName, attrValue);
      return attrValue;
    }
  }

  /**
   * Have subclasses implement this properly!
   */
  protected final boolean attributeIsImmutable (Symbol attrName) {
    return (IMMUTABLE.equals(virtualAttributesTable.get(attrName)));
  }

  /*
   * The attribute may be cachable if we can get updates by subscribing
   * to the item or if it is a virtual attribte that is kept up to
   * date by the workspace protocol.
   */
  private final boolean attributeIsCached (Symbol attrName) {
    boolean isSubscribed = false;
    java.lang.Object profile = virtualAttributesTable.get(attrName);
    java.lang.Object slotProfile = workspaceUpdatableSlots.get(attrName);
    if (data.subscriptionManager != null) {
      isSubscribed = data.subscriptionManager.isSubscribed(attrName, this);
    }
    boolean isWorkspaceUpdates = WORKSPACE_UPDATES.equals(slotProfile) || WORKSPACE_UPDATES.equals(profile);
    return (isSubscribed || IMMUTABLE.equals(profile) || (isWorkspaceUpdates && data.workspaceCurrentlySubscribed));
  }

  /*
   * This returns true for the subset of virtual attributes that
   * are kept current by Workspace subscription.
   */
  private boolean attributeUpdatedByWorkspace (Symbol attrName) {    
    return (WORKSPACE_UPDATES.equals(virtualAttributesTable.get (attrName)) ||
	     WORKSPACE_UPDATES.equals(workspaceUpdatableSlots.get (attrName)));
  }

  /**
   * Changed data structure to allow the distinction to be made
   * for different types of attribute updates.
   * @undocumented   
   * rpenny 8/3/98
   */
  protected boolean attributeSendsUpdates (Symbol attrName) {
    java.lang.Object updateProfile = virtualAttributesTable.get (attrName);
    return (updateProfile == null || ITEM_UPDATES.equals(updateProfile));
  }

  // Callable from subclasses. Returns success/failure?
  protected final boolean setAttributeValue (Symbol attrName, java.lang.Object newValue) throws G2AccessException {
    if (wrapper != null)
      return wrapper.setAttributeValue(attrName, newValue);
    if (handle <= 0)
      // By copy
      {
	data.attributes.setAttributeValue (attrName, newValue);
	// fire event;
	return true;
      }
    else
      // By handle
      {
	if (cacheAttributeWriteMode) {
	  if (attributeWriteCache == null) // check due to serialization
	    attributeWriteCache = new Structure(); 
	  attributeWriteCache.setAttributeValue(attrName, newValue);
	  return true;
	} else {
	  AttributeDenotation attrDentn =
	    newAttributeDenotation (attrName);
	  return setItemValue (attrDentn, newValue);
	}
      }
  }

  transient boolean cacheAttributeWriteMode = false;
  transient Structure attributeWriteCache = new Structure();
 
  /** 
   * If called with true any attributes set on a "by-handle" item will not be 
   * written to the G2 item, but cached until flushAttributeWriteCache is called.
   * @param status set true to enable the AttributeWritesCache.
   */
  @Override
  public void setAttributeWritesAreCached(boolean mode) {
    cacheAttributeWriteMode = mode;
  }

  /**
   * Return the status of the AttributeWriteCache.
   * @return false == The AttributeWriteCache is disabled, any attribute sets
   *                  will be passed to the G2 item (default).
   *         true  == The AttributeWriteCache is enabled, any attribute sets
   *                  will be not be passed to G2, until flushAttributeWriteCache is called.
   */
  @Override
  public boolean isAttributeWritesCached() {
    return cacheAttributeWriteMode;
  }

  /**
   * Send any attribute updates currently "waiting" to be written back to 
   * the item in G2 from the AttributeWriteCache. The attribute changes are sent
   * using one network call.
   */
  @Override
  public void flushAttributeWriteCache() throws G2AccessException {
    checkItemValidity();
    context.returnValues(new Item[] {(Item)this}, 
			 new Structure[] {attributeWriteCache}, 
			 null, 
			 null);
    attributeWriteCache = new Structure();
  }

  private static final AttributeDenotation newAttributeDenotation(final Symbol attr){
	Symbol attribute = attr;
    Symbol classQualifier = AttributeDenotation.getAttributeClassQualifier(attribute);
    if (classQualifier != null)
    	attribute = AttributeDenotation.getSimpleAttributeName(attribute);
    
    return new AttributeDenotation(attribute, classQualifier);
  }
    
  /*
   * Returns the value of the attribute named by
   * the argument.
   */
  protected final java.lang.Object getAttributeValue (Symbol attrName) throws G2AccessException {
    if (wrapper != null)
      return wrapper.getAttributeValue(attrName);
    else
      return getAttributeValueImpl (attrName);
    /*
      if (attrValue == empty)
      throw new AttributeLookupError ("Attribute " + attrName + " does not exist in ." + this
      + ".\nThis is an error. Please report this.");
      return attrValue;
      */
  }
  
  /** 
   * This method looks up a value of an attribute in the Items local Cache and does not cause an
   * RPC call to G2 for the item.
   * When Items are sent from G2 to Java BY-COPY-AND-HANDLE, they may be created with
   * pre initialized attribute values sent from G2. This method can be used to retrieve these values
   * without causing an RPC call to G2.
   */
  @Override
  public java.lang.Object getCachedAttributeValue(Symbol attrName, java.lang.Object defaultValue) {
    if (data.attributes == null) {
    	return defaultValue;
    }
    return data.attributes.getAttributeValue(attrName, defaultValue);
  }

  /**
   *@undocumented
   * When Items pass from G2 BY-COPY-AND-HANDLE, then may have attributes set, that need updating
   * straight into the local attributes store.
   */
  public void updateCachedAttributeValue(Structure attributesToUpdate) {
    synchronized(data) {
      if (data.attributes == null){
    	  return;
      }
      for (Enumeration e = attributesToUpdate.getAttributeNames(); e.hasMoreElements();) {
	Symbol attrName = (Symbol)e.nextElement();
	data.attributes.setAttributeValue(attrName, attributesToUpdate.getAttributeValue(attrName, null));
      }
    }
  }

  /**
   * @undocumented Might be nice to make public someday
   */
  public KbWorkspace getParentWorkspace () {
    return data.parentWorkspace;
  }

  /**
   * Temporary measure to compensate for lack of updates for
   * such things as ITEM-CONFIGURATIONS and CONNECTION-STYLE
   * in the workspace protocol.
   * @undocumented
   */
  public void refreshWsInfo(KbWorkspace ws, Structure info) {
    if (ws.equals(data.parentWorkspace)) {
      java.lang.Object value = info.getAttributeValue(ITEM_CONFIGURATION_, notDownloaded);
      if (!notDownloaded.equals(value))
	data.wsSnapshotOfConfiguration = (Sequence)value;

      value = info.getAttributeValue(CONNECTION_STYLE_, notDownloaded);
      if (!notDownloaded.equals(value))
	data.wsSnapshotOfConnectionStyle = (Symbol)value;

      value = info.getAttributeValue(CONNECTION_POSITION_SEQUENCE_,
				     notDownloaded);
      if (!notDownloaded.equals(value))
	data.attributes.setAttributeValue(CONNECTION_POSITION_SEQUENCE_,
					  (Sequence)value);
    }
  }
    
  /**
   * @deprecated Made public temporarily
   * @undocumented
   */
  public void updateItemForWorkspaceEvent (com.gensym.util.WorkspaceEvent evt) {
    // based on the type of event, update the corresponding attributes
    // so that getAttributeValue returns the correct value
    
    int id = evt.getID ();
    Structure eventInfo = evt.getInfo ();
    switch (id)
      {
      case WorkspaceEvent.ITEM_INSERT:
		  setWorkspaceUpdates (true); 
		  setInitialInfo(eventInfo);
		  break;
      case WorkspaceEvent.ITEM_REMOVE: 
    	  setWorkspaceUpdates (false);
    	  data.itemIsProprietaryThroughContainment = null; 
    	  break;
      case WorkspaceEvent.ITEM_MOVE:   
    	  setBoundsFromWorkspaceEvent (eventInfo); 
    	  break;
      case WorkspaceEvent.ITEM_RESIZE: 
    	  setSizeFromWorkspaceEvent (eventInfo);  
    	  break;
      case WorkspaceEvent.ITEM_ROTATE: 
    	  setHeadingAndReflectionFromWorkspaceEvent (eventInfo); 
    	  break;
      case WorkspaceEvent.ITEM_COLOR_PATTERN_CHANGE: 
    	  setIconColorPatternFromWorkspaceEvent (eventInfo); 
    	  break;
      case WorkspaceEvent.ITEM_ICON_VARIABLES_CHANGE: 
    	  setIconVariablesFromWorkspaceEvent (eventInfo); 
    	  break;
      case WorkspaceEvent.ITEM_CHANGE: /* Update Virtual Attr? */
	handleWorkspaceItemChange(eventInfo);
	break;
      default:
      }
  }
  
  private static final Integer ZERO = 0;
  private static final Integer NINETY = 90;
  private static final Integer ONE_EIGHTY = 180;
  private static final Integer TWO_SEVENTY = 270;

  private static final Symbol LEFT_   = Symbol.intern ("LEFT");
  private static final Symbol TOP_    = Symbol.intern ("TOP");
  private static final Symbol RIGHT_  = Symbol.intern ("RIGHT");
  private static final Symbol BOTTOM_ = Symbol.intern ("BOTTOM");

  private static final Symbol NORMAL_ = Symbol.intern ("NORMAL");
  private static final Symbol CLOCKWISE_90_ = Symbol.intern ("CLOCKWISE-90");
  private static final Symbol CLOCKWISE_180_ = Symbol.intern ("CLOCKWISE-180");
  private static final Symbol CLOCKWISE_270_ = Symbol.intern ("CLOCKWISE-270");
  private static final Symbol REFLECTED_ = Symbol.intern ("REFLECTED");
  private static final Symbol REFLECTED_CLOCKWISE_90_ = Symbol.intern ("REFLECTED-CLOCKWISE-90");
  private static final Symbol REFLECTED_CLOCKWISE_180_ = Symbol.intern ("REFLECTED-CLOCKWISE-180");
  private static final Symbol REFLECTED_CLOCKWISE_270_ = Symbol.intern ("REFLECTED-CLOCKWISE-270");
  private static final Symbol LEFT_RIGHT_ = Symbol.intern ("LEFT-RIGHT");
  private static final Symbol NEW_ROTATION_ = Symbol.intern ("NEW-ROTATION");

  private void setHeadingAndReflectionFromWorkspaceEvent (Structure eventInfo) {
    Symbol orientation = (Symbol) eventInfo.getAttributeValue(NEW_ROTATION_, null);
    Integer rotation = ZERO;
    Symbol reflection = null;
    
    if (orientation == null || (orientation.equals (NORMAL_))) {
      // do nothing, initial values correct
    } else if (orientation.equals (CLOCKWISE_90_))
      rotation = NINETY;
    else if (orientation.equals (CLOCKWISE_180_))
      rotation = ONE_EIGHTY;
    else if (orientation.equals (CLOCKWISE_270_))
      rotation = TWO_SEVENTY;
    else if (orientation.equals (REFLECTED_))
      reflection = LEFT_RIGHT_;
    else if (orientation.equals (REFLECTED_CLOCKWISE_90_)) {
      rotation = NINETY;
      reflection = LEFT_RIGHT_;
    } else if (orientation.equals (REFLECTED_CLOCKWISE_180_)) {
      rotation = ONE_EIGHTY;
      reflection = LEFT_RIGHT_;
    } else if (orientation.equals (REFLECTED_CLOCKWISE_270_)) {
      rotation = TWO_SEVENTY;
      reflection = LEFT_RIGHT_;
    }

    synchronized(data) {
      data.attributes.setAttributeValue(ICON_HEADING_, rotation);
      data.attributes.setAttributeValue(ICON_REFLECTION_, reflection);
    }
  }

  private static final Symbol COLOR_PATTERN_CHANGES_ = Symbol.intern ("COLOR-PATTERN-CHANGES");

  private void setIconVariablesFromWorkspaceEvent (Structure variableOverrides) {
    data.attributes.setAttributeValue (ICON_VARIABLES_, variableOverrides);
  }

  private void setIconColorPatternFromWorkspaceEvent (Structure eventInfo) {
    Structure colorPatternChanges = (Structure) eventInfo.getAttributeValue (COLOR_PATTERN_CHANGES_, null);
    synchronized (data) {
      Structure itemColorPattern = (Structure) data.attributes.getAttributeValue (ITEM_COLOR_PATTERN_, null);
      Enumeration attrNames = colorPatternChanges.getAttributeNames ();
      while (attrNames.hasMoreElements ()) {
	Symbol attrName = (Symbol) attrNames.nextElement ();
	java.lang.Object newColorName = colorPatternChanges.getAttributeValue (attrName, null);
	itemColorPattern.setAttributeValue (attrName, newColorName);
	if (virtualAttributesTable.get (attrName) != null) // standard layer?
	  data.attributes.setAttributeValue (attrName, newColorName);
      }
    }
  }


   private static final Symbol NEW_VALUE_ = Symbol.intern ("NEW-VALUE");
   /** 
    * @undocumented
    */
   protected final void handleWorkspaceItemChange(Structure newInfo) {
     if (newInfo == null) {
       System.out.println("Warning: handleWorkspaceItemChange received null newInfo, this = " + this);
       return;
     }
     Symbol attrName = (Symbol)newInfo.getAttributeValue(ATTRIBUTE_NAME_, null);
     if (attrName == null) {
       System.out.println("malformed ITEM_CHANGE structure=" + newInfo);
       return;
     }
     if (!attributeUpdatedByWorkspace(attrName))
       return;

     java.lang.Object newValue = newInfo.getAttributeValue(NEW_VALUE_, notDownloaded);
     if (notDownloaded.equals(newValue)) {
       System.out.println("malformed ITEM_CHANGE structure=" + newInfo);
     } else {
       if ((TABLE_CELLS_.equals(attrName) || TABLE_ROWS_.equals(attrName)) &&
	   !(newValue instanceof Sequence)) {
	 handleTableCellChanged(newInfo, newValue, attrName);
       } else {
	 synchronized (data) {
	   data.attributes.setAttributeValue(attrName, newValue);
	 }
       }
     }
   }

  //
  // What follows deals with specific kinds of changes that can
  // come in as part of the workspace protocol
  //

  private static final Symbol ROW_INDEX_ = Symbol.intern ("ROW-INDEX");
  private static final Symbol COLUMN_INDEX_ = Symbol.intern ("COLUMN-INDEX");
  private static final Symbol CELL_ATTRIBUTE_NAME_ = Symbol.intern ("CELL-ATTRIBUTE-NAME");
  private static final Symbol CELL_DISPLAY_TEXT_ = Symbol.intern ("CELL-DISPLAY-TEXT");
  private static final Symbol LEFT_TEXT_ = Symbol.intern ("LEFT-TEXT");
  private static final Symbol RIGHT_TEXT_ = Symbol.intern ("RIGHT-TEXT");

  private void handleTableCellChanged (Structure newInfo,
				       java.lang.Object newValue,
				       Symbol attributeName) {
    try {
      Sequence tableCells = (Sequence)getAttributeValueImpl(attributeName);
      int rowIndex
	= ((Integer)newInfo.getAttributeValue(ROW_INDEX_, null)).intValue();
      int columnIndex
	= ((Integer)newInfo.getAttributeValue(COLUMN_INDEX_, null)).intValue();
      Symbol slotName = (Symbol)newInfo.getAttributeValue(CELL_ATTRIBUTE_NAME_);

		if (TABLE_CELLS_.equals(attributeName)) {
			Sequence row = (Sequence)tableCells.elementAt(rowIndex);
			Structure cell = (Structure)row.elementAt(columnIndex);
			cell.setAttributeValue(slotName, newValue);
		} else { //TABLE_ROWS_ case
			//Additional check added to address a  bug regarding displaying attribute displays
			if (rowIndex >= 0 && rowIndex < tableCells.size()) {
				Structure row = (Structure)tableCells.elementAt(rowIndex);
				if (CELL_DISPLAY_TEXT_.equals(slotName))
					row.setAttributeValue(RIGHT_TEXT_, newValue);
				else
					row.setAttributeValue(LEFT_TEXT_, newValue);
			}
		}
    } catch (G2AccessException g2ae) {
      throw new UnexpectedException(g2ae); // shouldn't have even called G2
    } catch (NoSuchAttributeException nsae) {
      throw new CorruptionException(nsae); // structure was malformed
    }
  }

  protected final void setWorkspaceUpdates (boolean updateState) {
    data.workspaceCurrentlySubscribed = updateState;
    if (!updateState) {		// Losing updates. Clean up cached attribute values
      for (Enumeration e = virtualAttributesTable.keys ();
	   e.hasMoreElements ();) {
	Symbol attrName = (Symbol) e.nextElement ();
	if (attributeUpdatedByWorkspace (attrName))
	  data.attributes.deleteAttribute (attrName);
      }
      for (Enumeration e = workspaceUpdatableSlots.keys ();
	   e.hasMoreElements ();) {
	Symbol attrName = (Symbol) e.nextElement ();
	if (attributeUpdatedByWorkspace (attrName))
	  data.attributes.deleteAttribute (attrName);
      }
    }
  }

  /* Should be on KbWorkspaceImpl */
  protected final void setWorkspaceUpdatesForItem (boolean updateState, G2__BaseImpl itmOnWksp) {
    itmOnWksp.setWorkspaceUpdates (updateState);
  }

  protected static final Symbol TW_WORKSPACE_ITEM_POSITION_ = Symbol.intern ("TW-WORKSPACE-ITEM-POSITION");

  protected void setBoundsFromWorkspaceEvent (Structure eventInfo) {
    try {
      Structure attributes = data.attributes;
      int left = ((Integer)eventInfo.getAttributeValue (LEFT_)).intValue ();
      int top = ((Integer)eventInfo.getAttributeValue (TOP_)).intValue ();
      int right = ((Integer)eventInfo.getAttributeValue (RIGHT_)).intValue ();
      int bottom = ((Integer)eventInfo.getAttributeValue (BOTTOM_)).intValue ();
      //These two computations are wrong for some rotations.
      attributes.setAttributeValue (ITEM_X_POSITION_, (left + right) >> 1);
      attributes.setAttributeValue (ITEM_Y_POSITION_, -((-top - bottom) >> 1));

      attributes.setAttributeValue (ITEM_WIDTH_, right - left);
      attributes.setAttributeValue (ITEM_HEIGHT_, top - bottom);
    } catch (NoSuchAttributeException nsae) {
      Trace.exception (nsae, null);
      //System.out.println ("Workspace event info = " + eventInfo);
    }
  }

  protected final void setSizeFromWorkspaceEvent (Structure eventInfo) {
    try {
      Structure attributes = data.attributes;
      int left = ((Integer)eventInfo.getAttributeValue (LEFT_)).intValue ();
      int top = ((Integer)eventInfo.getAttributeValue (TOP_)).intValue ();
      int right = ((Integer)eventInfo.getAttributeValue (RIGHT_)).intValue ();
      int bottom = ((Integer)eventInfo.getAttributeValue (BOTTOM_)).intValue ();
      //These two computations are wrong for some rotations.
      if (!((this instanceof TableItem) && (left == 0) && (top == 0))) {
	attributes.setAttributeValue (ITEM_X_POSITION_, (left + right) >> 1);
	attributes.setAttributeValue (ITEM_Y_POSITION_, -((-top - bottom) >> 1));
      }      
      attributes.setAttributeValue (ITEM_WIDTH_, right - left);
      attributes.setAttributeValue (ITEM_HEIGHT_, top - bottom);
    } catch (NoSuchAttributeException nsae) {
      Trace.exception (nsae, null);
      //System.out.println ("Workspace event info = " + eventInfo);
    }
  }

  // The following two methods are accessors to optimization snapshots
  // of some specific pieces of Item state. For WorkspaceView use only!

  /**
   * This returns the snapshot of the configuration that was sent
   * when the item was downloaded as part of representWorkspace.
   * @undocumented
   */
  @Override
  public Sequence getItemConfigurationSnapshot() throws G2AccessException {
    // actually get it if this item does not have workspace updates
    if (data.workspaceCurrentlySubscribed && !attributeIsCached(ITEM_CONFIGURATION_))    //? for WILDCARD
      return data.wsSnapshotOfConfiguration;
    else
      return (Sequence)getAttributeValueImpl(ITEM_CONFIGURATION_);
  }

  /**
   * @undocumented
   */
  @Override
  public Vector getCompleteConfigurationSnapshot() throws G2AccessException {
    KbWorkspace wksp = data.parentWorkspace;
    // this could happen if an item gets transferred off the current ws while
    // multiple items are selected and a user is trying to
    // get a popup on that ws. The popup could be confused, but we won't
    // bomb...
    if (wksp == null)
      return new Vector();
    else {
      Vector snapshot = wksp.getContainmentHierarchyItemConfigurationSnapshot();
      Vector config = getItemConfigurationSnapshot();
      if (config != null)
	snapshot.insertElementAt(config, 0);
      return snapshot;
    }
  }
    
  /**
   * Returns the ConnectionStyle snapshot that was sent
   * when the item was downloaded as part of representWorkspace.
   * @undocumented
   */
  @Override
  public Symbol getConnectionStyleSnapshot() {
    return data.wsSnapshotOfConnectionStyle;
  }

  /**
   * @returns an all-new initial-info structure (for workspace-protocol
   * use only)
   * @undocumented
   */
  public Structure getInitialInfo() throws G2AccessException {
    // this count could be stored at class load too
    int count = workspaceInitialInfoList.size();
    Structure initialInfo = new Structure();
      
    synchronized (data) {
      Structure attrs = data.attributes;
	for (int i = 0; i < count; i++) {
	  Symbol attr = (Symbol)workspaceInitialInfoList.elementAt(i);
	  java.lang.Object obj = attrs.getAttributeValue(attr, notDownloaded);
	  if (!notDownloaded.equals(obj))
	    initialInfo.setAttributeValue(attr, obj);
	}
	initialInfo.setAttributeValue(CONNECTION_STYLE_, data.wsSnapshotOfConnectionStyle);
	initialInfo.setAttributeValue(ITEM_CONFIGURATION_, data.wsSnapshotOfConfiguration);
    }
    return initialInfo;
  }

  /**
   * @undocumented
   */
  private static final Symbol POSITION_OR_NEXT_LOWER_ITEM_ = Symbol.intern ("POSITION-OR-NEXT-LOWER-ITEM");
    
  public void setInitialInfo(Structure initialInfo)
  {
    synchronized (data) {
//       com.gensym.util.Debug3Tier.add_data ("setInitialInfo", this + ";" + initialInfo);
      Enumeration names = initialInfo.getAttributeNames();
      Structure attrs = data.attributes;
      Symbol attrName;
      java.lang.Object newValue;
      while (names.hasMoreElements()) {
	attrName = (Symbol)names.nextElement();
	// this comes in in the "extra-info", but is not an attribute
	// of the item. If the value is an item, this can result in a nasty
	// leak if it gets put into the data.attributes
	if (POSITION_OR_NEXT_LOWER_ITEM_.equals(attrName))
	  continue;
	newValue = initialInfo.getAttributeValue(attrName, null);
	// The following is for elminating RPC calls on a per-item
	// basis in workspace download.
	if (CONNECTION_STYLE_.equals(attrName))
	  data.wsSnapshotOfConnectionStyle = (Symbol)newValue;
	else if (ITEM_CONFIGURATION_.equals(attrName))
	  data.wsSnapshotOfConfiguration = (Sequence)newValue;
	else
	  attrs.setAttributeValue (attrName, newValue);
      }
    }
  }
  
  /**
   * Gets the value of a named attribute
   * @param attrName a <code>Symbol</code> naming an attribute of the <code>Item</code>
   * @return the value of the desired attribute. This may be null if the attribute
   *         exists but has no value.
   * @exception G2AccessException problems with the call
   */
  /* The difference between this and getAttributeValue is that this method could
   * get called with a bogus attribute-name, since it is public
   */
  @Override
  public java.lang.Object getPropertyValue (Symbol attrName) throws G2AccessException, NoSuchAttributeException {
    //int attrKind = (getManager?).getAttributeKind (getClassName (), attrName);
    return getAttributeValueImpl (attrName);
  }

  /**
   * Sets the value of a named attribute
   * @param attrName a <code>Symbol</code> naming an attribute of the <code>Item</code>
   * @param newValue the new value for the attribute
   * @exception G2AccessException
   */
  @Override
  public void setPropertyValue (Symbol attrName, java.lang.Object newValue) throws G2AccessException {
    setAttributeValue (attrName, newValue);
  }

  private void updateLocalCache (ItemEvent ie) {
    Sequence denotation = ie.getDenotation ();
    // destructively modifies the denotation.
    AttributeDenotation.denormalizeDenotation(denotation);    
    java.lang.Object newValue = ie.getNewValue ();
    Trace.send (DEF_WARN_LEVEL, traceKey, i18nTrace, "updateItmCache",
		denotation, newValue);
    Symbol attrName_ = 
      (Symbol) ((Structure)denotation.elementAt (0)).getAttributeValue
                                                       (Denotation.NAME_, null);
    synchronized (data) {
      data.attributes.setAttributeValue (attrName_, newValue);
    }
  }

  /**
   * @undocumented For VB use since it cannot call setPropertyValue (java.lang.Object)
   */
  public void setStringPropertyValue (Symbol attrName, java.lang.String newValue) throws G2AccessException {
    setAttributeValue (attrName, newValue);
  }

  /**
   * @undocumented For VB use to get around the inability to pass ""
   */
  public void setEmptyStringPropertyValue (Symbol attrName) throws G2AccessException {
    setAttributeValue (attrName, "");
  }

  /**
   * @undocumented For VB use since it cannot call setPropertyValue (java.lang.Object)
   */
  public void setIntPropertyValue (Symbol attrName, int newValue) throws G2AccessException {
    setAttributeValue (attrName, newValue);
  }

  /**
   * @undocumented For VB use since it cannot call setPropertyValue (java.lang.Object)
   */
  public void setDoublePropertyValue (Symbol attrName, double newValue) throws G2AccessException {
    setAttributeValue (attrName, newValue);
  }

  /**
   * @undocumented For VB use since it cannot call setPropertyValue (java.lang.Object)
   */
  public void setBooleanPropertyValue (Symbol attrName, boolean newValue) throws G2AccessException {

    setAttributeValue (attrName, newValue ? Boolean.TRUE : Boolean.FALSE);
  }

  /**
   * @undocumented For VB use since it cannot call setPropertyValue (java.lang.Object)
   */
  public void setPseudoBooleanPropertyValue (Symbol attrName, int newValue) throws G2AccessException {

    setAttributeValue (attrName, (newValue != 0) ? Boolean.TRUE : Boolean.FALSE);
  }

  private int makeHashCode() {
    if (handle > 0)
      return (context.hashCode() ^ handle ^ (handleVersion << 24));
    else {
      if (context != null)
	Trace.send (DEF_WARN_LEVEL, traceKey, i18nTrace, "possInvldHndl",
		    getClass (), handleKey);
      return super.hashCode();
    }
  }
  
  @Override
  public int hashCode() {
    if (hashIsNotSet) {
      hashCode = makeHashCode();
      hashIsNotSet = false;
    }
    return hashCode;
  }

  int getObjectHashCode () {
    return super.hashCode ();
  }

  @Override
  public boolean equals(java.lang.Object obj) {
    if (obj == null || !(obj.getClass().equals(this.getClass())))
      return false;

    G2__BaseImpl other = (G2__BaseImpl)obj;

    if (handle > 0) {
      return ((other.handle == handle) &&
	      (other.handleVersion == handleVersion) &&
	      context.equals(other.context));
    } else {
      if (data == null) {
	return other.data == null;
      } else {
	// Assume that the only 'instance data' for a "by copy" object will be 
	// its attributes
	if (data.attributes == null) {
	  return other.data.attributes == null; // hey, do we know any better?
	} else {
	  return data.attributes.equals(other.data.attributes);
	}
      }
    }
  }

  @Override
  public String toString () {
    // Change here is to allow deubgging statements at all points
    // in the constructor without throwing null pointer exception.
    // Also some three-tier debugging can end up dealing with items
    // whose data is null.
    if (data==null)
      return super.toString () + "(" + super.hashCode() + ";" + "data NULL, # = " + handleKey.toString () + "v" +
	handleVersion+ ";" + isValid() + ")";
    else if (data.attributes != null)
      return super.toString () + "(" + super.hashCode() + ";" + data.attributes.getAttributeValue (CLASS_, null) +
      ", # = " + handleKey.toString () + "v" + handleVersion +
      (data.itemIsValid ? ", ok" : ", deleted") +
      (data.fullyInitialized ? "" : ", Uninitialized Definition") +
      ";" + isValid() + ")";
    else return super.toString () + "(" + super.hashCode() + ";" + "NO_ATTRIBUTES" +
	   ", # = " + handleKey.toString () + "v" + handleVersion +
	   (data.itemIsValid ? ", ok" : ", deleted") +
	   (data.fullyInitialized ? "" : ", Uninitialized Definition") +
	   ";" + isValid() + ")";
  }

  private final IntHashtable ensureHash (java.lang.Object key, Hashtable hash) {
    IntHashtable foundHash = null;
    synchronized (hash) {
      foundHash = (IntHashtable)hash.get(key);

      if (foundHash == null) {
	foundHash = new IntHashtable();
	hash.put(key, foundHash);
	if (key instanceof G2Gateway){
	  ((G2Gateway)key).addG2ConnectionListener(closingAdapter);
	}
      }
    }

    return foundHash;
  }

    // fix this: I'm pretty confident that there is no danger
    // of not synchronizing this, as interleaved calls are guaranteed
    // to return the same hashtable.
    // fix this: this will be a big hashtable, so we need to tweak the
    // parameters of this hashtable (need to pass them in to ensureHash).
  private IntHashtable getItemHash() {
    if (itemHash != null)
      return itemHash;

    itemHash = ensureHash(context, contextHash);

    return itemHash;
  }

  // Warning: make sure that this is never called from withing
  // the constructor of G2__BaseImpl (and also therefore
  // not within makeDataForItem)
  void checkItemValidity () throws G2ItemDeletedException {
    if (!isValid())
      throw new G2ItemDeletedException ("Item " + this + " has been deleted");
  }

  /**
   * Returns the ItemData object that stores the actual data for this
   * item. */
  protected ItemData getData() {
    synchronized (data) {
      return data;
    }
  }

  /**
   * @undocumented
   * Exposed for storing definitions by handle.
   */
  public final int getHandle () {
    return handle;
  }

  private void invalidateSelf() {
    itemIsValid = false;
    if (data != null)
      data.itemIsValid = false;
  }

  @Override
  public boolean isValid() {
    // Warning:
    // Items that are otherwise valid will appear "invalid" if they
    // are asked too early in their constructor (should
    // only affect debugging statements placed in the
    // constructor or within makeDataForItem, which is
    // called in the constructor).
    return itemIsValid && data != null && data.itemIsValid;
  }

  /**
   * @undocumented
   */
  public int getHandleVersion () {
    return handleVersion;
  }

  /**
   * @undocumented
   * HQ-4463966:
   * This method is only used with the "old" three argument constructor.  This
   * system has some timing races, but we are leaving it here for backwards
   * compatibility.  A warning will be printed for each class which means to be
   * redownload (see jgi/download/DefaultStubFactory.java).
   */
  public void setHandleVersion (int handleVersion) {
    this.handleVersion = handleVersion;
    data.handleVersion = handleVersion;
    //after the handle version has been set, the item can be declared valid.
    itemIsValid = true;
    //     com.gensym.util.Debug3Tier.add_data ("version", this);

    // See comment in constructor: if there already exists data for
    // this item at constructor time, then an item with this handle
    // already existed.  This really shouldn't happen, because the
    // item and its data should be deleted when the handle is reused,
    // but various timing issues can prevent us from happening.
    if (savedHashedData != null) {
      if (handleVersion < savedHashedData.handleVersion) {
	// can happen if an instance of a user-class gets deleted
	// and its ICP handle re-used before it is able to finish
	// downloading its own class information
	// 	  com.gensym.util.Debug3Tier.add_data ("create-wierd(3)", this + ";" + savedHashedData.handleVersion);
	invalidateSelf();
	if (com.gensym.core.GensymApplication.getDevOption())
	  System.out.println("Warning in setHandleVersion:  Current item being created has already been deleted in G2:  " + this + "(v" + handleVersion + "); current version = " + savedHashedData.handleVersion);
      } else if (handleVersion == savedHashedData.handleVersion) {
	// Why would this be?
	// (Note: we saw this error message when it was before the
	//        handle version was set up.  We think that it
	//        really should have been one of the other error
	//        conditions, probably the last one: new handle version
	//        > saved hashed data's version.
	// 	com.gensym.util.Debug3Tier.add_data ("create-wierd2(3)", this + ";" + savedHashedData.handleVersion);

	(new InvalidItemException((Item)this, "New item found duplicate data in hash table " + this + ";previousData=" + savedHashedData)).printStackTrace();
	// Reusing old data.  Right?  Dunno.
	data = savedHashedData;
      } else { // this is even more confusing if this were to happen
	// This would mean that this item is more recent than
	// the data in the hashtable is, but for some reason
	// the data in the hashtable didn't get cleared out
	// when the previous item got destroyed.
	// NOTE: haven't seen this case either
	// Note 2: as above, we may have seen it, but aren't sure.
	// 	  com.gensym.util.Debug3Tier.add_data ("create-wierd3(3)", this + ";" + savedHashedData.handleVersion);
	savedHashedData.itemIsValid = false;
	(new InvalidItemException((Item)this, "New item replacing data in hash table " + this + ";previousData=" + savedHashedData)).printStackTrace();
	// This wasn't done in the constructor if there was previous data
	// but we're overwriting the old data now, so fix up the hashtable too.
	IntHashtable itemHashLocal = getItemHash();
	synchronized (itemHashLocal) {
	  itemHashLocal.put(handle, data);
	}
      }
      savedHashedData = null; //don't let this happen again.
    }
  }

  /**
   * Is this object operating locally or remotely.
   * WARNING called by generated G2 method implementation stubs
   */
  public boolean isByHandle() {
    return (handle > 0);
  }

  /**
   * Is this object operating remotely ? 
   * An G2 Item sent from G2 can be sent as;
   * 1. "BY HANDLE" in which case this Item represents a remote G2 object.
   * 2. "BY COPY" the object is locally held and has no relation to an exisiting G2 Object. 
   */
  @Override
  public boolean isItemLocal() {
    return (!(handle > 0));
  }

  /**
   * This exists to enable us to determine when handles are reassigned.
   * It is not necessary if we have absolute references.
   */
  private int handleVersion;

  /** locates or makes an ItemData */
  private ItemData findDataForItem (boolean contextMakesStubs) {
    // used to be protected
    //if (data != null)
    //return data;

    IntHashtable itemHashLocal = getItemHash();
    Trace.send(20, traceKey, i18nTrace, "iifindDataForItem",
	       this, context, itemHashLocal, handleKey);
    //    Trace.backTrace(20, traceKey);
    synchronized (itemHashLocal){
      ItemData itemData = (ItemData)itemHashLocal.get(handle);

      // NOTE: it is NOT OK to throw exceptions during readObject on  the third
      // tier, as the third-tier can receive a whole vector of events. If an exception
      // is thrown during the readObject, all the events in that vector will get
      // thrown away. It is OK that an exception be thrown during the processing of
      // one of those events, because special code has been put into place to
      // handle that occurence.
      // HOWEVER, it IS OK to throw exceptions in the middle-tier (== contextMakesStubs)
      // since the readObject on the middle-tier gets called during individual
      // RPC's from the client, and the client is expecting those to fail if,
      // for example, it is making a call that involves an item that has been
      // deleted in the server, but about which the client hasn't yet been told.

      if (contextMakesStubs) {
	// I separate these two clauses to differentiate the two cases (data is null
	// or data has newer version) for debugging purposes only. The two
	// cases are functionally equivalent to the end user. The only internal
	// difference is "has the IPC handle been reused already?".
	if (itemData == null) { 
// 	  com.gensym.util.Debug3Tier.add_data ("2nd-tier-got-null-data", this);
	  invalidateSelf();
	  throw new InvalidItemException ((Item)this, "Item has been deleted " + this);
	} else if (handleVersion < itemData.handleVersion) {
// 	  com.gensym.util.Debug3Tier.add_data ("2nd-tier-got-old-version", this);
	  invalidateSelf();
	  throw new InvalidItemException ((Item)this, "The Item has been deleted " + this);
	} else if (handleVersion > itemData.handleVersion) {
// 	  com.gensym.util.Debug3Tier.add_data ("2nd-tier-got-new-version", this);
	  // by rights this should be an Error, the trouble is that if an Error
	  // gets thrown during readObject (where this is often called from), then
	  // if that readObject is part of an RMI call, the Error turns into a
	  // "socket write failed", thus losing any information about the root
	  // cause of the failure
	  throw new  InvalidItemException((Item)this, "Item Data problem. The 3rd tier sent to the 2nd tier a version newer than the 2nd-tier's current version");
	}
      } else {
	if (itemData == null) {
	  itemData = makeConfiguredItemData(itemHashLocal);
	} else {
	  /* Assumption: Came from 2nd tier. If we support 3rd tier clients
	     communicating directly, then this should be an InvalidItemException*/
	  if (handleVersion < itemData.handleVersion) {
	    invalidateSelf();
//  	    com.gensym.util.Debug3Tier.add_data ("3rd-tier-version-old", this);
	    //throw new java.lang.Error ("Item Data problem. 3rd tier got version older than current version");
	  }
	  if (itemDeleted || handleVersion > itemData.handleVersion) {
	    //dispose (); don't dispose on third tier: not guaranteed,
	    // and this causes problems
	    itemData = makeConfiguredItemData(itemHashLocal);
	    if (itemDeleted) {
	      invalidateSelf();
	    }
	  }
	}
      }
      return itemData;
    }
  }

  /**
   * Called only on third tier
   */
  private ItemData makeConfiguredItemData(IntHashtable hashForItems) {
    ItemData itemData = makeDataForItem();
    itemData.handleVersion = handleVersion;
    // the following is always considered to be true on the
    // third tier.
    itemData.fullyInitialized = true;
    hashForItems.put(handle, itemData);
    return itemData;
  }
    

  /**
   * This method is called from within the constructor to set
   * up the data cache for the item. Subclasses may override this
   * to return more specific objects with additional attributes.
   *
   * Every time this is called, we need to set the handleVersion
   * in the data, unless in the BY-COPY case.
   */
  protected ItemData makeDataForItem () {
    return new ItemData ();
  }

  //This method is not used in ItemImpl(attributes) leave it here because it is
  //a public interface of G2__Base. SystemItemImpl, RootIiteImpl, IntegerVariableImpl,
  //QuantitativeVariableImpl, G2VariableImpl, VariableImpl, VariableOrParameterImpl,
  //ObjectImpl implement the method
  //We used to throw a runtime exception, but instead we are now just returning false.
  @Override
  public boolean isLocallyCached () {
    return false;
  }

  @Override
  public void setLocallyCached (boolean cacheLocally) {
  }

  /* Cleans out the ItemData from the ItemHash */
//   protected void finalize () {
//     // Clean up registrations, hashtables, and listeners here...
    
//     synchronized(data) {
//       if(--data.referenceCount <= 0) {
//  	getItemHash().remove(handleKey);
//  	Trace.send(20, traceKey, i18nTrace, "iiclearingItemData");
//       }
//     }
//   }
   

  private boolean itemDeleted;

  private void writeObject (java.io.ObjectOutputStream stream) throws java.io.IOException {
    stream.defaultWriteObject ();
//     com.gensym.util.Debug3Tier.add_data ("write", this);
    if (handle >0) {
      // fix this: find out when this is null
      if (data == null) {
	//Thread.dumpStack ();
	data = (ItemData)itemHash.get (handle);
      }
      if (data == null || handleVersion < data.handleVersion)
	itemDeleted = true; //throw new InvalidItemException (this, "Item has been deleted");
      if ((data != null) && handleVersion > data.handleVersion)
	// Used to throw Error here. Trouble is that can result in loss of information,
	// as the facilities doing the writing don't handle Errors well.
	throw new RuntimeException ("Problem with ItemData. Encountered Item with higher version than expected. " + this);
    } else // by-copy case
      stream.writeObject (data.attributes);
  }

  private void readObject (java.io.ObjectInputStream stream) throws java.io.IOException, ClassNotFoundException{
    stream.defaultReadObject();
//     com.gensym.util.Debug3Tier.add_data ("read", this);
    if (handle == 0) {
      data = makeDataForItem ();
      data.attributes = (Structure) stream.readObject ();
    } else {
      // NOTE: order is important. Context must also
      // be resolved before calling findDataForItem
      try {
	context = connectionResolver.getContext();
 	if (context == null) {
	  // NOTE: this happens if the connection has
	  // been closed in the middle tier, and a
	  // call from the client reaches the server afterwards.
	  invalidateSelf();
 	  Trace.exception(new InvalidItemException((Item)this, "Item read by server after connection closed: " + this));
 	  return;
 	}
	classManager = context.getClassManager();
	data = findDataForItem(((G2Gateway)context).makesOwnStubs());
	if (data == null) {
	  invalidateSelf();
	  return;
	}
	synchronized(data) {
	  data.referenceCount++;
	}
	// These are not in the same synchronized block
	// because the referenceCount does not need
	// to be co-ordinated with the attributes field.
	synchronized (data) {
	  if (data.attributes == null)
	    data.attributes = new Structure();
	}
	Class[] interfaces = getClass().getInterfaces();
	for (int i = 0; i < interfaces.length; i++)
	  ((G2Gateway)context).storeInterfaceForG2Class(interfaces[i]);
	Trace.send(1, traceKey, i18nTrace, "iireadObject",
		   this, context, classManager, connectionResolver);
      } catch (Exception ex) {
	Trace.exception(ex);
	throw new com.gensym.util.UnexpectedException(ex);
      }
    }
  }

  /**
   * The G2 named equivalent of <code>instanceof</code>.
   * Use instead of getting the class from G2 in order to call
   * instanceOf(). This method doesn't require that the class named by
   * <code>g2ClassName_</code> be loaded on the client.
   * @return <code>true</code> if "<item> is a <g2ClassName_>" would return
   * <code>true</code> for this item in G2, false otherwise
   */
  @Override
  public boolean isInstanceOfG2Class(Symbol g2ClassName_) {
    try {
      G2Definition definition = getDefinition();
      Sequence inheritance = definition.getSystemClassInheritancePath();
      return inheritance.contains(g2ClassName_);
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
      throw new UnexpectedException(g2ae);
    }
  }

  /**
   * @undocumented
   */
  protected static final java.lang.Object invokeTwAccessMethod (G2Access context,
							  String methodName,
							  Class[] argTypes,
							  java.lang.Object[] args) throws G2SecurityException, G2AccessException
  {
    try {
      Class contextClassObject = Class.forName("com.gensym.ntw.TwAccess");
      java.lang.reflect.Method method
	= contextClassObject.getMethod(methodName, argTypes);
      if (contextClassObject.isInstance(context))
	return method.invoke(context, args);
      else
	throw new G2SecurityException(context +
				      " must be an instance of TwAccess to invoke " +
				      method);	
    } catch (ClassNotFoundException nsce) {
      throw new G2SecurityException("TwAccess is required to invoke " + methodName);
    } catch (NoSuchMethodException nsme) {
      Trace.exception(nsme);
    } catch (java.lang.reflect.InvocationTargetException ite) {
      Trace.exception(ite);
      if (ite.getTargetException () instanceof G2AccessException)
	throw (G2AccessException)ite.getTargetException ();
      Trace.exception (ite.getTargetException ());
    } catch (IllegalAccessException iae) {
      Trace.exception(iae);
    }
    return null;
  }

  /**
   * @undocumented
   */
  protected static final UiClientSession retrieveSession(G2Access context)
  throws G2SecurityException {
    try {
      return (UiClientSession)invokeTwAccessMethod(context, "retrieveSession", null, null);
    } catch (G2AccessException g2ae) {
      Trace.exception (g2ae);
      throw new UnexpectedException (g2ae, "While trying to retrive session from gateway");
    }
  }
  
  /**
   * Generically call an RPC across my connection.
   * WARNING Called by generated G2 method implementation stubs
   */
  public java.lang.Object callRPC(Symbol rpcName, java.lang.Object[] args) throws G2AccessException {
    //checkItemValidity (); -> mg, Who calls this and should it be protected?
    return context.callRPC(rpcName, args);
  }

  /**
   * @undocumented For VB use to expose method calls. In VB the name
   * "callMethod" gives an error when using the Microsoft VM, so we
   * have this one with a different name to work around that.
   */
  public java.lang.Object callMethodForVB (Symbol methodName, Sequence argsSeq, int timeOut) throws G2AccessException {
    return callMethod (methodName, argsSeq, timeOut);
  }

  /**
   * @undocumented For VB use to expose method calls
   */
  public java.lang.Object callMethod (final Symbol methodName, final Sequence argsSeq, final int timeOut) throws G2AccessException {
	checkItemValidity ();
	Sequence sequence = (Sequence)argsSeq.clone();
	sequence.insertElementAt(this, 0);
    java.lang.Object[] args = new java.lang.Object[sequence.size ()];
    sequence.copyInto (args);
    checkItemValidity ();
    return context.callRPC (methodName, args, timeOut);
  }

  /**
   * @undocumented For VB use to expose method calls
   */
  public void startMethod (final Symbol methodName, final Sequence argsSeq) throws G2AccessException {
    checkItemValidity ();
    Sequence sequence = (Sequence)argsSeq.clone();
    sequence.insertElementAt(this, 0);
    java.lang.Object[] args = new java.lang.Object[sequence.size ()];
    sequence.copyInto (args);
    checkItemValidity ();
    context.startRPC (methodName, args);
  }

  /**
   * @undocumented For VB use to expose method calls
   */
  @Override
  public java.lang.Object callMethod (Symbol methodName, java.lang.Object[] args, int timeOut) throws G2AccessException {
    checkItemValidity ();
    return context.callRPC (methodName, args, timeOut);
  }

  /**
   * @undocumented For VB use to expose method calls
   */
  @Override
  public void startMethod (Symbol methodName, java.lang.Object[] args) throws G2AccessException {
    checkItemValidity ();
    context.startRPC (methodName, args);
  }

  /**
   * @undocumented
   */
  @Override
  public Structure getAttributeValues (Sequence attributeNames)
        throws G2AccessException
  {
    if (isItemLocal())
      return getAttributes();
    else {
      checkItemValidity ();
      java.lang.Object[] args = new java.lang.Object[] {this, attributeNames};
      return (Structure) callRPC (G2_GET_ATTRIBUTE_VALUES_OF_ITEM_, args);
    }
  }


  /**
   * @undocumented
   */
  @Override
  public Structure getAttributeTexts (Sequence attributeNames) throws G2AccessException
  {
    checkItemValidity ();
    java.lang.Object[] args = new java.lang.Object[] {this, attributeNames};
    return (Structure) callRPC (G2_GET_ATTRIBUTE_TEXTS_OF_ITEM_, args);
  }

  /**
   * @undocumented
   */
  public java.lang.Object getAttributeText (Symbol attributeName_)
        throws G2AccessException
  {
    checkItemValidity ();
    java.lang.Object[] args = new java.lang.Object[] {this, attributeName_, null};
    return callRPC (G2_GET_TEXT_OF_ATTRIBUTE_, args);
  }

  /**
   * @undocumented
   */
  public boolean setItemValue (Denotation denotation,
			       java.lang.Object value) 
       throws G2AccessException
  {
    checkItemValidity ();

    Boolean retnvalue = (Boolean)
     context.callRPC(G2_CONCLUDE_IN_ITEM_, 
		     new java.lang.Object[] {this, denotation, value});
    return retnvalue.booleanValue ();
  }

  private static Symbol _getAttributesVisibleInMode_Symbol 
                        = Symbol.intern("G2-GET-ATTRIBUTES-VISIBLE-IN-MODE");
  /**
   * Will return a sequence of symbols containing all the visible
   * attribute names.
   */
  @Override
  public Sequence getVisibleAttributes (Symbol userMode) throws G2AccessException {
    checkItemValidity ();
    java.lang.Object[] args = new java.lang.Object[] {this, userMode};
    return (Sequence) context.callRPC (_getAttributesVisibleInMode_Symbol, args);
  }
    
  /**
   * Returns the (cached?) introspective information regarding
   * the attributes of the class.
   */
  @Override
  public Sequence getAttributeDescriptions (Sequence attrNames) throws G2AccessException {
    checkItemValidity ();
    return context.getAttributeDescriptions (getG2ClassName (), attrNames);
  }

  @Override
  public Sequence getAttributeDescriptions () throws G2AccessException {
    checkItemValidity ();
    return context.getAttributeDescriptions (getG2ClassName (), new Sequence ());
  }

  private static final Sequence WILDCARD_DENOTATION = AttributeDenotation.WILDCARD_DENOTATION;
  static final java.lang.Object USER_DATA = 30;

//   /** this current implementation is maintained completely outside
//    * of the WILDCARD_DENOTATION subscription of addItemListener.
//    * It is really intended for supporting a generalization of
//    * things like addValueListener on VariableOrParameterSpecialImpl.
//    * It is currently needed to support addValueListener in three-tier.
//    * It does not address the issue of real Denotation equivalency,
//    * but simply rests on Sequence.equals() to avoid some duplication
//    * of subscription.
//    * @undocumented
//    */
//   public Structure addItemListenerForDenotationRetrievingState(ItemListener newListener,
// 							       Sequence denotation)
//   throws G2AccessException {
//     synchronized (data) {
//       Integer handle = getHandleForDenotation(denotation);
//       ItemListener l = (handle == null ? null :
// 			getListenerForHandle(handle));
//       Structure initData = null;
//       if (l == null) {
// 	try {
// 	  Structure subscpnData =
// 	    context.subscribeToItem(this, denotation, USER_DATA);
// 	  handle =
// 	    (Integer)subscpnData.getAttributeValue(SUBSCRIPTION_HANDLE_);
// 	  initData =
// 	    (Structure)subscpnData.getAttributeValue(INITIAL_VALUE_);
// 	  putHandleForDenotation(denotation, handle);
// 	} catch (NoSuchAttributeException nsae) {
// 	  throw new G2AccessException(nsae);
// 	}
//       } else {
// 	initData = makeSnapshot(denotation, handle);
//       }

//       putListenerForHandle(handle, newListener, l);

//       newListener.receivedInitialValues(new ItemEvent(this,
// 						      INITIAL_VALUE_,
// 						      this,
// 						      denotation,
// 						      initData, USER_DATA,
// 						      handle.intValue()));
//       return initData;
//     }
//   }

//   /** @undocumented
//    */
//   public void removeItemListenerForDenotation(ItemListener oldl,
// 					      Sequence denotation)
//   throws G2AccessException{
//     synchronized (data) {
//       Integer handle = getHandleForDenotation(denotation);
//       ItemListener l = (handle == null ? null :
// 			getListenerForHandle(handle));
//       ItemListener resultingListener =
// 	EventMulticaster.remove(l, oldl);

//       if (resultingListener == null) { // last listener gone
// 	data.handle2ListenerMap.remove(handle);
// 	context.unsubscribeToItem(handle.intValue());
// 	data.denotation2HandleMap.remove(denotation);
//       } else {
// 	data.handle2ListenerMap.put(handle, resultingListener);
//       }
//     }
//   }

//   /** This is presumed to be called from within a synchronized block.
//    */
//   private Integer getHandleForDenotation(Sequence denotation) {
//     Hashtable map = data.denotation2HandleMap;
//     if (map == null) {
//       map = data.denotation2HandleMap = new Hashtable();
//       return null;
//     }
//     return (Integer)map.get(denotation);
//   }

//   /** putHandleForDenotation MUST NEVER be called before
//    * getHandleForDenotation. If this becomes necessary, the null check
//    * for the Hashtable must be added to this method. Also is presumed
//    * to be called from within a synchronized block.
//    */
//   private void putHandleForDenotation(Sequence denotation, Integer handle) {
//     data.denotation2HandleMap.put(denotation, handle);
//   }
    
//   /** This is presumed to be called from within a synchronized block.
//    */
//   private ItemListener getListenerForHandle(Integer handle) {
//     Hashtable map = data.handle2ListenerMap;
//     if (map == null) {
//       map = data.handle2ListenerMap = new Hashtable();
//       return null;
//     }
//     return (ItemListener)map.get(handle);
//   }

//   /** putListenerForHandle MUST NEVER be called before
//    * getListenerForHandle. If this becomes necessary, the null check
//    * for the Hashtable must be added to this method. Also is presumed
//    * to be called from within a synchronized block.
//    */
//   private void putListenerForHandle(Integer handle, ItemListener newListener,
// 				    ItemListener currentListener) {
//     ItemListener il = EventMulticaster.add(currentListener, newListener);
//     data.handle2ListenerMap.put(handle, il);
//   }

//   /** Bypasses the question of updates waiting in the RunMethodThread
//    * that were sent by G2 before this RPC call is made: when these
//    * updates are processed, they can reflect state older than that
//    * represented by this snapshot.
//    *@undocumented.
//    */
//   protected Structure makeSnapshot(Sequence denotation, Integer handle) 
//   throws G2AccessException{
//     return
//       new Structure();
// //     new Symbol[] {INITIAL_VALUE_, SUBSCRIPTION_HANDLE_},
// //                     new java.lang.Object[]
// // 		    {context.getValue (this, denotation), handle},
// // 		    2);
//   }    
    
  private static final String fileSeparator = System.getProperty ("file.separator");

  private static final Symbol SOURCE_   = Symbol.intern ("SOURCE");
  private static final Symbol FILE_     = Symbol.intern ("FILE");
  private static final Symbol URL_      = Symbol.intern ("URL");
  private static final Symbol PROTOCOL_ = Symbol.intern ("PROTOCOL");
  private static final Symbol LOCATION_ = Symbol.intern ("LOCATION");
  private static final Symbol HOST_     = Symbol.intern ("HOST");
  private static final Symbol PORT_     = Symbol.intern ("PORT");

  /**
   * Returns a structure with information regarding which
   * resource to use for an editing dialog for an item
   * @param itm the item for which we want a dialog
   * @param userMode the mode for which the dialog is needed
   * @param locale the locale for which the dialog is needed
   * @return a structure with information as to the name? of the dialog and
   *         its applicability?
   */
  @Override
  public Structure getDialog (Symbol userMode, Structure locale) throws G2AccessException, MalformedURLException {
    Structure result = null; //((com.gensym.ntw.TwAccess)context).getDialog (this, userMode, locale);
    if (result == null)
      return EMPTY_STRUCTURE;
    if (result.getAttributeValue (SOURCE_, null) != null)
      transformToURL (result);
    return result;
  }

  private static final Structure EMPTY_STRUCTURE = new Structure ();

  private void transformToURL (Structure result) throws G2AccessException, MalformedURLException {
    try {
      java.lang.Object src = result.getAttributeValue (SOURCE_);
      //System.out.println ("Source of Resource = " + src);
      String location      = (String) result.getAttributeValue (LOCATION_);
      if (src instanceof MediaBin) {
	MediaBin mediaBin = (MediaBin)src;
	Symbol binName = (Symbol) mediaBin.getNames ();
	G2ConnectionInfo cxnInfo = ((G2Gateway)context).getG2ConnectionInfo ();
	String host = cxnInfo.getHost ();
	String port = cxnInfo.getPort ();
	String urlString = "g2://" + host + ":" + port + "/" + com.gensym.net.g2.NamedMediaBinHandler.MAGIC_MARKER +
	  binName + location;
	URL url = new URL (urlString);
	//System.out.println ("Made URL = " + url);
	result.setAttributeValue (URL_, url);
      } else if (src instanceof Symbol && src.equals (URL_)) {
	Symbol protocol_ = (Symbol)result.getAttributeValue (PROTOCOL_);
	if (protocol_ == null)
	  throw new MalformedURLException ("Missing PROTOCOL component for resource URL");
	String protocol = protocol_.getPrintValue ().toLowerCase ();
	String host     = (String) result.getAttributeValue (HOST_, null);
	String port     = (String) result.getAttributeValue (PORT_, null);
	String urlString = protocol + "://" + (host == null ? "" : host)
	  + (port == null ? "" : ":" + port)
	  + location;
	URL url = new URL (urlString);
	result.setAttributeValue (URL_, url);
      } else if (src instanceof Symbol && src.equals (FILE_)) {
	if ("\\".equals(fileSeparator))
	  location = location.replace ('\\', '/');
	String urlString = "file:///" + location;
	URL url = new URL (urlString);
	result.setAttributeValue (URL_, url);
      } else
	throw new MalformedURLException ("Illegal Resource Description!");
    } catch (NoSuchAttributeException nsae) {
      throw new MalformedURLException ("Illegal ResourceDescription2!");
    }
  }

  /**
   * G2__RemoteStub Implementation
   */
  // if the stub is invalid, it should notify the listener when
  // it is added
  @Override
  public void addStubInvalidationListener (StubInvalidationListener l) {
    synchronized (data) {
      if (data.invalidationListeners == null)
	data.invalidationListeners = new Vector ();
      data.invalidationListeners.addElement (l);
    }
  }

  @Override
  public void removeStubInvalidationListener (StubInvalidationListener l) {
    synchronized (data) {
      if (data.invalidationListeners != null)
	data.invalidationListeners.removeElement (l);
    }
  }

  private void notifyInvalidationListeners () {
    if (data.invalidationListeners == null ||
	data.invalidationListeners.isEmpty())
      return;
    StubInvalidationEvent invldtnEvent = new StubInvalidationEvent (this);
    Vector listeners;
    synchronized (data.invalidationListeners) {
      listeners = (Vector)data.invalidationListeners.clone();
    }
    for (int i=0; i< listeners.size(); i++)
      ((StubInvalidationListener)listeners.elementAt (i)).stubIsInvalid (invldtnEvent);
  }

  /**
   * Null implementation of ImplAccess
   */
  @Override
  public java.awt.Rectangle getBounds () throws G2AccessException {
    throw new java.lang.Error ("G2__BaseImpl.getBounds called. Please report to Customer Support.");
  }

  @Override
  public Structure addItemListenerRetrievingState (ItemListener l) throws G2AccessException {
    throw new java.lang.Error ("G2__BaseImpl.addItemListenerRetrievingState called. Please report to Customer Support.");
  }

  @Override
  public Sequence addItemListenerRetrievingStateMultiple (ItemListener l, Sequence denotation_sequences) throws G2AccessException {
    throw new java.lang.Error ("G2__BaseImpl.addItemListenerRetrievingStateMultiple called. Please report to Customer Support.");
  }

  @Override
  public void  removeItemListenerForThreeTiers(com.gensym.util.ItemListener l, Sequence subscriptionHandles)
    throws com.gensym.jgi.G2AccessException {
    throw new java.lang.Error ("G2__BaseImpl.removeItemListenerForThreeTiers called. Please report to Customer Support.");
  }

  public void dumpWkspItemList () {
    if (!(this instanceof KbWorkspace))
      return;
    WorkspaceData wkspData = (WorkspaceData)data;
    Sequence items = wkspData.items;
    System.out.println ("There are " + items.size () + " items on " + this);
    for (int i=0; i<items.size (); i++)
      System.out.println ("##"+ i + " = " + items.elementAt (i));
  }

  static G2ConnectionAdapter closingAdapter =
  new G2ConnectionAdapter() {
    @Override
    public void g2ConnectionClosed(G2ConnectionEvent e) {
      G2Access contextLocal = (G2Access)e.getSource();
      contextHash.remove(contextLocal);
      contextLocal.removeG2ConnectionListener(this);      
    }
  };

}


