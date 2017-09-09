package com.gensym.jgi.download.local;

import java.util.Enumeration;
import java.lang.reflect.Field;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.Hashtable;
import com.gensym.fida.*;
import com.gensym.fida.support.*;
import com.gensym.classes.Item;
import com.gensym.classes.G2Definition;
import com.gensym.classes.G2__BaseImpl;
import com.gensym.classes.Entity;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Connection;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.JavaObjectForG2ItemFactory;
import com.gensym.jgi.G2ItemForJavaObjectFactory;
import com.gensym.jgi.G2JavaStubController;
import com.gensym.jgi.G2Connection;
import com.gensym.jgi.download.G2StubResolver;
import com.gensym.jgi.download.G2StubCreationException;
//import com.gensym.jgi.download.local.denali.DenaliWorkspaceConverter;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.G2ClassTranslator;
import com.gensym.util.Sequence;
import com.gensym.message.Trace;

public class G2RTExportManager implements JavaObjectForG2ItemFactory,
                                          G2ItemForJavaObjectFactory,
                                          com.gensym.g2export.G2ObjectConverter
{
  private G2Access connection; 
  private ExternalG2RTRuntime runtime;
  private G2JavaStubController g2JavaStubController = 
              G2JavaStubController.getG2JavaStubController();
  private Hashtable registeredG2Items = new Hashtable();
  private Hashtable proxyConstructorTable = new Hashtable();
  private static final Class[] proxyConstructorSig = 
                      new Class[] {com.gensym.classes.G2__Base.class};

  public static final Symbol G2RTI_OBJECT_PROXY_ = Symbol.intern("G2RTI-OBJECT-PROXY");
  public static final Symbol G2RTI_REMOTE_RUNTIME_ = Symbol.intern("G2RTI-REMOTE-RUNTIME");
  public static final Symbol URL_ = Symbol.intern("URL");
  public static final Symbol _EXT_CLASS_NAME_ = Symbol.intern("_EXT-CLASS-NAME");
  public static final Symbol _ASSOCIATED_RUNTIME_NAME = Symbol.intern("_ASSOCIATED-RUNTIME-NAME");
  public static final Symbol CURRENT_LOCATION_ = Symbol.intern("CURRENT-LOCATION");
  public static final Symbol _ORIGINAL_PROXY_SEQ_ = Symbol.intern("_ORIGINAL_PROXY_SEQ");
  public static final Symbol _NEW_PROXY_SEQ_ = Symbol.intern("_NEW-PROXY-SEQ");
  public static final Symbol G2RT_MOBILITY_EVENT_ = Symbol.intern("G2RT-MOBILITY-EVENT");
  

  G2RTExportManager (G2Access connection, ExternalG2RTRuntime runtime)
  {
    this.connection = connection;
    this.runtime = runtime;
    LocalStubClassLoader classLoader = 
      DownloadLocalClasses.getLocalStubClassLoaderForConnection(connection, false);
    classLoader.setClassManager(runtime.getApplication(null, null).getClassManager()); 
    g2JavaStubController.setJavaObjectForG2ItemFactory(connection, this);
    g2JavaStubController.setG2ItemForJavaObjectFactory(connection, this);
    com.gensym.g2export.G2__BaseImpl.setG2ObjectConverter(this);
  }

  G2Access getConnection()
  {
    return connection;
  }

  public Object createLocalVersionOfG2Item(Item g2Item)
       throws G2AccessException,
	      ClassManagerException
  {
    try {
      // Check for G2rt objects here
      Class localClazz = getJavaClassFromExportIfNecessary((G2Definition)g2Item.getDefinition(), false);
      com.gensym.g2export.Item localItem = (com.gensym.g2export.Item)localClazz.newInstance();
	updateLocalItemFromG2Item(g2Item, localItem);
      return localItem;
    } catch (InstantiationException e) {
      throw new ClassManagerException(e, e.toString());
    } catch (IllegalAccessException e) {
      throw new ClassManagerException(e, e.toString());
    }
  }

  public Item createG2ItemVersionOfLocalItem(com.gensym.g2export.G2__Base localItem)
       throws G2AccessException
  {
      Symbol g2ClassName = localItem.getG2ClassName();
      Item g2Item = connection.createItem(g2ClassName);
      updateG2ItemFromLocalItem(g2Item, localItem);
      return g2Item;
  }

  public Item createByCopyG2ItemVersionOfLocalItem(com.gensym.g2export.G2__Base localItem)
       throws G2AccessException
  {
    try {
      Symbol g2ClassName = localItem.getG2ClassName();
      Item g2Item = G2StubResolver.createStubForG2Interface(Item.class);
      updateG2ItemFromLocalItem(g2Item, localItem);
      ((G2__BaseImpl)g2Item).setInternalG2ClassName(localItem.getG2ClassName());
      System.out.println(g2Item.getAttributeValues(new Sequence()));
      return g2Item;
    } catch (G2StubCreationException e) {
      Trace.exception(e);
    }
    return null;
  }


  public void updateLocalItemFromG2ItemOld(Item item, 
					com.gensym.g2export.G2__Base localItem)
       throws G2AccessException,
	 ClassManagerException
  {
    try {
      
      // There must be a much better faster way of doing this !
      Structure atts = ((com.gensym.classes.G2__BaseImpl)item).getAttributes();
      for (Enumeration e = atts.getAttributeNames(); e.hasMoreElements();) {
	Symbol attName = (Symbol)e.nextElement();
	Object value = atts.getAttributeValue(attName, null);  
	Object localValue = value;
	System.out.println("Converting " + attName + " " + value);
	if (value instanceof Item) {
	  value = createLocalProxyVersionOfG2Item((Item)value);
	}
	String fieldName = 
	  G2ClassTranslator.createJavaNameFromG2Name(attName);
	try {
	  Field field = localItem.getClass().getField(fieldName);
	  field.set(localItem, localValue);
	} catch (NoSuchFieldException ex) {
	  System.out.println("Ignoring " + fieldName + " writing from " + item + " to " + localItem);
	}
	}
    } catch (Exception e) {
      if (e instanceof ClassManagerException)
	throw (ClassManagerException)e;
      else
	throw new ClassManagerException(e, e.toString());
    }
  }

  public void updateLocalItemFromG2Item(Item item, 
					com.gensym.g2export.G2__Base localItem)
       throws G2AccessException,
	 ClassManagerException
  {
    Structure atts = item.getAttributeValues(new Sequence());
    System.out.println("updateLocalItemFromG2Item " + item + " " + atts.toString());
    ((com.gensym.g2export.G2__BaseImpl)localItem).updateLocalAttributesFromG2(atts);
    // And any subworkspace
    if (item instanceof Entity) {
      KbWorkspace sws = ((Entity)item).getSubworkspace();
      System.out.println("Workspace " + sws);
      if (sws != null) {
	//com.gensym.g2export.KbWorkspace lsws = new com.gensym.g2export.KbWorkspaceImpl();
	//((com.gensym.g2export.Entity)localItem).setSubworkspace(lsws);
	//DenaliWorkspaceConverter.updateLocalKbWorkspaceFromG2Workspace(sws, lsws, this);
      }
    }
  }

  public void updateG2ItemFromLocalItem(Item item,
					com.gensym.g2export.G2__Base localItem)
       throws G2AccessException
  {
    Structure atts = ((com.gensym.g2export.G2__BaseImpl)localItem).updateG2AttributesFromLocal();

    if (!(item.isItemLocal()))
      item.setAttributeWritesAreCached(true);

    for (Enumeration e = atts.getAttributeNames(); e.hasMoreElements();) {
      Symbol attName = (Symbol)e.nextElement();
      Object attVal = atts.getAttributeValue(attName, null);
      if (attVal != null)
	item.setPropertyValue(attName, attVal);
    }
    if (!(item.isItemLocal())) {
      item.flushAttributeWriteCache();
      item.setAttributeWritesAreCached(false);
    }
  }

  // Implement G2ObjectConverter for conversion of 
  // Attributes and parameters from G2 to Local 
  // (and visa versa ...see com.gensym.g2export.G2__BaseImpl

  @Override
  public java.lang.Object toLocalAttribute(java.lang.Object obj)
  {
    try {
      // Rules of translation...
      if (obj instanceof Sequence ||
	  obj instanceof Structure ||
	  obj instanceof Object[])
	// Any embedded object in seq, Stru, [] are 
	// converted to local proxy (see getJavaObjectForG2Item below) 
	return g2JavaStubController.resolveG2Stubs(connection, null, obj);
      else
	// Any attribute which is a G2 object, is converted into a local (by-copy) version 
	if (obj instanceof com.gensym.classes.G2__Base) {
	  Object localItem = createLocalVersionOfG2Item((Item)obj);
	  return localItem;
	}
    } catch (Exception e) {
      throw new RuntimeException(e.toString());
    }
    return obj;
  }

  @Override
  public java.lang.Object toG2Attribute(java.lang.Object obj)
  {
    try {
      // Any attribute which is a G2 object, is converted into a local (by-copy) version 
      if (obj instanceof com.gensym.g2export.G2__Base) {
	Object g2Item = createByCopyG2ItemVersionOfLocalItem((com.gensym.g2export.G2__Base)obj);
	return g2Item;
      } else
	return g2JavaStubController.resolveJavaObject(connection, obj);
    } catch (Exception e) {
      throw new RuntimeException(e.toString());
    }
  }

  @Override
  public java.lang.Object toLocalParameter(java.lang.Object obj)
  {
    try {
      return g2JavaStubController.resolveG2Stubs(connection, null, obj);
    } catch (G2AccessException e) {
      throw new RuntimeException(e.toString());
    }
  }

  @Override
  public java.lang.Object toG2Parameter(java.lang.Object obj)
  {    
    try {
      if (obj instanceof ObjectProxy) {
	return createByCopyG2ObjectProxy((ObjectProxy)obj);
      } else if (obj instanceof MobilityEvent) {
	return createByCopyG2MobilityEvent((MobilityEvent)obj);
      }
      
      return g2JavaStubController.resolveJavaObject(connection, obj);
    } catch (G2AccessException e) {
      throw new RuntimeException(e.toString());
    }
  }

  /**
   * This method will return the stub for a given G2 class def.
   * If the class has not been previously downloaded, it will be created
   */
  public Class getJavaClassFromExportIfNecessary(G2Definition classDefToExport,
						 boolean getInterface) // otherwise stub
       throws ClassManagerException,
	      G2AccessException
  {
    Symbol g2ClassName = classDefToExport.getClassName();
    Class clazz = DownloadLocalClasses.getClassForG2Class(connection, 
							  g2ClassName,
							  getInterface); 
    return clazz;
  }

   /**
   * This method will return the stub for a given G2 class def.
   * If the class has not been previously downloaded, it will be created
   */
  public String getJavaClassNameFromExportIfNecessary(G2Definition classDefToExport)
       throws ClassManagerException,
	      G2AccessException
  {
    return getJavaClassFromExportIfNecessary(classDefToExport, false).getName();
  }

  public Class getProxyForG2ClassAndExportIfNecessary(G2Definition classDefToExport)
       throws G2AccessException
  {
    Symbol g2ClassName = classDefToExport.getClassName();
    Class clazz = DownloadLocalClasses.getG2ProxyStubClass(connection,
							  g2ClassName);
    return clazz;
  }

  public Object createLocalProxyVersionOfG2Item(Item g2Item) 
       throws G2AccessException, ClassManagerException
  {
    try {
      com.gensym.g2export.G2__BaseImpl localItem = 
	(com.gensym.g2export.G2__BaseImpl)registeredG2Items.get(g2Item);
      if (localItem == null) {
	// Check for G2rt objects here
	Class localClazz = getProxyForG2ClassAndExportIfNecessary((G2Definition)g2Item.getDefinition());
	Constructor cons = (Constructor)proxyConstructorTable.get(localClazz);
	if (cons == null) {
	  cons = localClazz.getConstructor(proxyConstructorSig);
	  proxyConstructorTable.put(localClazz, cons);
	}
	localItem = 
	  (com.gensym.g2export.G2__BaseImpl)cons.newInstance(new Object[] {g2Item});
	//g2JavaStubController.associate((G2Connection)connection,
	//							 g2Item,
	//							 localItem);
	registeredG2Items.put(g2Item, localItem);
	// Light Registration, so the Wrapper has a ObjectProxy for remote comms
	// Rem and ObjectProxy is only used for message passing/method calling by the wrapper.
	// The object will not be exposed in the name space
	ObjectContainer container = localItem.getObjectContainer();
	if (container == null) {
	  // Light Registration, so the Wrapper has a ObjectProxy for remote comms
	  // Rem and ObjectProxy is only used for message passing/method calling by the wrapper.
	  // The object will not be exposed in the name space
	  container = 
	    ObjectContainerImpl.getObjectContainer(localItem, 
						   runtime.getApplication(null, null));
	  localItem.setObjectContainer(container);
	}
      }
      return localItem;
    } catch (InstantiationException e) {
      throw new ClassManagerException(e, e.toString());
    } catch (IllegalAccessException e) {
      throw new ClassManagerException(e, e.toString());
    } catch (NoSuchMethodException e) {
      throw new ClassManagerException(e, e.toString());
    } catch (InvocationTargetException e) {
      Throwable targetEx = e.getTargetException();
      throw new ClassManagerException(targetEx, targetEx.toString());
    }
  }

  // Implement G2ItemForJavaObjectFactory
  @Override
  public Item getG2ItemForJavaObject(G2Access connection, Object javaObject) 
       throws G2AccessException
  {

    if (javaObject instanceof com.gensym.g2export.G2ProxyAccess) {
      com.gensym.classes.G2__Base g2Item = 
	((com.gensym.g2export.G2ProxyAccess)javaObject)._getG2Item();
      if (g2Item != null)
	return (Item)g2Item;
    }

    if (javaObject instanceof com.gensym.g2export.G2__Base) {
      com.gensym.g2export.G2__Base exportedObj = (com.gensym.g2export.G2__Base)javaObject;
      Symbol g2ParentClassName = exportedObj.getG2ClassName();
      // An exported G2 class, send back a proxy subclasses from the original class
      return connection.getG2ProxyForJavaObject(javaObject.getClass().getName(),
						g2ParentClassName,
						javaObject);
    }
    return null; // must retrun null if we have not found anything
  }

  // Implement JavaItemForG2ItemFactory
  @Override
  public Object getJavaObjectForG2Item(G2Access connection, Object targetObject, Item g2Item)
  {
    System.out.println("G2RTExportManager::getJavaObjectForG2Item " + targetObject + " " + g2Item);
    // We dont want to interfer with Items passed to these targets or static methods
    if (targetObject == ExternalG2RTObjectManager.class ||
	targetObject == ExternalG2RTMessageManager.class ||
	targetObject == ExternalG2RTRuntime.class ||
	targetObject instanceof ExternalG2RTObjectManager || 
	targetObject instanceof ExternalG2RTClassManager ||
	targetObject instanceof ExternalG2RTRuntime)
      return null;

    // Certain FIDA Objects need conversion
    try {
       Symbol g2ClassName = g2Item.getG2ClassName();
      if (g2ClassName.equals(G2RTI_OBJECT_PROXY_)) {
	String url = (String)g2Item.getPropertyValue(URL_);
	return ObjectProxyImpl.getObjectProxy(url);
      } else if (g2ClassName.equals(G2RTI_REMOTE_RUNTIME_)) {
	String url = (String)g2Item.getPropertyValue(URL_);
	return runtime.getRuntime(url);
      }
      return createLocalProxyVersionOfG2Item(g2Item);
    } catch (Exception e) {
      throw new RuntimeException(e.toString());
    }
  }

  public Item createByCopyG2ObjectProxy(ObjectProxy proxy) 
  {
    try {
      Item g2Proxy = G2StubResolver.createStubForG2Interface(Item.class);
      g2Proxy.setPropertyValue(URL_, proxy.getUrl());
      g2Proxy.setPropertyValue(_EXT_CLASS_NAME_, proxy.getClassName());
      g2Proxy.setPropertyValue(_ASSOCIATED_RUNTIME_NAME, runtime.getRegisteredName());
      ((G2__BaseImpl)g2Proxy).setInternalG2ClassName(G2RTI_OBJECT_PROXY_);
      return g2Proxy;
    } catch (G2AccessException e) {
      Trace.exception(e);
    } catch (G2StubCreationException e) {
      Trace.exception(e);
    }
    return null;
  }

  public Item createByCopyG2MobilityEvent(MobilityEvent event)
  {
    try {
      Item g2Event = G2StubResolver.createStubForG2Interface(Item.class);
      g2Event.setPropertyValue(CURRENT_LOCATION_, event.getCurrentLocation());
      Sequence seq1 = new Sequence();
      ObjectProxy lastProxy = event.getOriginalProxy();
      if (lastProxy != null)
	seq1.addElement(createByCopyG2ObjectProxy(lastProxy));
      Sequence seq2 = new Sequence();
      ObjectProxy newProxy = event.getNewObjectProxy();
      if (newProxy != null)
	seq2.addElement(createByCopyG2ObjectProxy(newProxy));
      g2Event.setPropertyValue(_ORIGINAL_PROXY_SEQ_, seq1);
      g2Event.setPropertyValue(_NEW_PROXY_SEQ_, seq2);
      ((G2__BaseImpl)g2Event).setInternalG2ClassName(G2RT_MOBILITY_EVENT_);
      return g2Event;
    } catch (G2AccessException e) {
      throw new RuntimeException(e.toString());
    } catch (G2StubCreationException e) {
      throw new RuntimeException(e.toString());
    }
  }

  //public static final Symbol _GET_WS_CONNECTIONS_RPC = Symbol.intern("_G2RT-GET-WORKSPACE-CONNECTIONS");

  // NOTE: this is a pure hack until we have good kb support for ws emitting
  /**
   * NOT USED ....
  public void updateLocalKbWorkspaceFromG2Workspace(KbWorkspace g2kbw, 
						    com.gensym.g2export.KbWorkspace localkbw)
       throws G2AccessException,
	      ClassManagerException
  {
    // Get the items on the workspace
    G2Access connection = ((G2__BaseImpl)g2kbw).getContext();
    Sequence cseq = (Sequence)connection.callRPC(_GET_WS_CONNECTIONS_RPC, new Object[] {g2kbw});
    System.out.println(cseq);
    Hashtable kbitems = new Hashtable();
    for (Enumeration ce = cseq.elements(); ce.hasMoreElements();) {
      Item e = (Item)ce.nextElement();
      if (e instanceof com.gensym.classes.Connection) {
	com.gensym.g2export.Connection localConnection = new com.gensym.g2export.ConnectionImpl();
	Sequence connectionData = ((Connection)e).getConnectionInputAndOutput();
	System.out.println("ConnectionData " + connectionData);
	if (connectionData != null) {
	  Object connectionItem = connectionData.elementAt(0); // input to connection
	  if (connectionItem instanceof Entity) {
	    com.gensym.g2export.Entity localInput = (com.gensym.g2export.Entity)kbitems.get(connectionItem);
	    if (localInput == null)
	      localInput = (com.gensym.g2export.Entity)createLocalVersionOfG2Item((Item)connectionItem);
	    localConnection.setConnectionInput((com.gensym.g2export.Item)localInput);
	    localInput.addInputConnection(localConnection);
	    kbitems.put(connectionItem, localInput);
	  }
	  connectionItem = connectionData.elementAt(1); // output from connection
	  if (connectionItem instanceof Entity) {
	    com.gensym.g2export.Entity localOutput = (com.gensym.g2export.Entity)kbitems.get(connectionItem);
	    if (localOutput == null)
	      localOutput = (com.gensym.g2export.Entity)createLocalVersionOfG2Item((Item)connectionItem);
	    localConnection.setConnectionOutput((com.gensym.g2export.Item)localOutput);
	    localOutput.addOutputConnection(localConnection);
	    kbitems.put(connectionItem, localOutput);
	  }
	}
      }
    }
  }
  **/


}
