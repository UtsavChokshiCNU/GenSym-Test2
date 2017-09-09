package com.gensym.jgi.download.local;

import java.net.MalformedURLException;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import com.gensym.fida.*;
import com.gensym.fida.support.*;
import com.gensym.classes.Item;
import com.gensym.classes.G2Definition;
import com.gensym.classes.Definition;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2Connection;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2JavaStubController;
import com.gensym.util.Symbol;
import javax.naming.NamingException;

public class ExternalG2RTObjectManager extends ObjectManagerImpl
{

  Item g2ObjectManager;

  static final Symbol _REGISTER_EXTERNAL_G2ITEM = 
              Symbol.intern("G2RTI-REGISTER-EXTERNAL-G2ITEM");
  static final Symbol _RECORD_EXTERNAL_OBJECT_REGISTRATION = 
              Symbol.intern("G2RTI-RECORD-EXTERNAL-OBJECT-REGISTRATION");
  static final Symbol MOVE_ = 
              Symbol.intern("MOVE");
  static final Symbol URL_ =
              Symbol.intern("URL");

  public ExternalG2RTObjectManager(Environment environment)
  {
    super(environment);
  }

  public void setG2ObjectManager(Item g2ObjectManager)
  {
    this.g2ObjectManager = g2ObjectManager;
  }

  /**
   * Register an object with this G2 FIDARuntime Environment such that it belongs to a specified 
   * application Environment. The Object is bound into the Environments name space, 
   * assigned an Id and an ObjectContainer.
   * Once the object is part of the FIDA network 
   */
  public ObjectContainer register(Object obj) 
       throws RegistrationException
  {
    System.out.println("ExternalG2RTObjectManager::register  " + obj);
    try {
      ExternalG2RTRuntime runtime = (ExternalG2RTRuntime)getEnvironment().getRuntime();
      G2RTExportManager exportManager = runtime.getExportManager();
      G2Access connection = exportManager.getConnection();
      Item g2RuntimeInterface = runtime.getG2RuntimeInterface(); // Runtime in G2
      
      ObjectContainer container = lookupContainer(obj);
      if (container != null) {
	if (container.getApplicationEnvironment().getObjectManager() != this)
	  throw new RegistrationException("Can not register " + obj + 
					  " as it is already registered with another ObjectManager");
	return container;
      }
      
      if (obj instanceof com.gensym.g2export.G2ProxyAccess) {
	throw new RegistrationException("Can't register a G2Proxy back into G2");
      } else if (obj instanceof com.gensym.g2export.G2__Base) {
	// Move back into G2 and let it register there
	Item g2Item = exportManager.createByCopyG2ItemVersionOfLocalItem((com.gensym.g2export.G2__Base)obj);
	Object g2ret = connection.callRPC(_REGISTER_EXTERNAL_G2ITEM, 
					  new Object[] {g2RuntimeInterface, 
							  getEnvironment().getApplicationName(),
							  g2Item});
	// Must return a ObjectContainer after the register via G2
	Object convG2Ret = 
	  G2JavaStubController.getG2JavaStubController().resolveG2Stubs(connection, 
									null, 
									g2ret);
	System.out.println("ExternalG2RTObjectManager::register after G2__Base register in G2 and conv, got back " + convG2Ret);
	if (!(convG2Ret instanceof ObjectContainer)) {
	  throw new RegistrationException("Registering local g2 item (g2Item) via G2 did not return a ObjectContainer");
	} else {
	  return (ObjectContainer)convG2Ret;
	}
      } else {
	// A non G2 (exported) object, need to create a proxy for this and inform G2
	// Convert to something we can send to G2
      Object g2obj = G2JavaStubController.getG2JavaStubController().resolveJavaObject(connection, 
										      obj);
      // Note this constructor will register the container in with the ObjectCacheManager
      container = 
	ObjectContainerImpl.getObjectContainer(obj,
					       getEnvironment());
      containerHash.put(obj, container);
      try {
	container.setRegisteredName(container.getUuid()); // puts in the name space
      } catch (NamingException e) {
	throw new RegistrationException(e, e.toString());
      }
      // If this object is a DistrubutedObject let him know that he is registered
      if (obj instanceof DistributedObject) {
	DistributedObject dobj = (DistributedObject)obj;
	dobj.onRegistration(container);
      }
      
      // let G2 know
      connection.callRPC(_RECORD_EXTERNAL_OBJECT_REGISTRATION, 
			 new Object[] {g2RuntimeInterface, 
					 getEnvironment().getApplicationName(),
					 g2obj});
      
      return container;
      }
    } catch (G2AccessException e) {
      throw new RegistrationException(e, e.toString());
    } catch (Exception e) {
      e.printStackTrace();
      throw new RegistrationException(e, e.toString());
    }
  }

  public ObjectProxy getObjectProxyForG2Item(Item obj)
       throws RegistrationException,
              ClassManagerException,
	      G2AccessException
  {
     G2RTExportManager exportManager = 
      ((ExternalG2RTRuntime)getEnvironment().getRuntime()).getExportManager();
    return getObjectProxy(exportManager.createLocalProxyVersionOfG2Item(obj));
  }

  public ObjectContainer registerG2Item(Item obj) 
       throws MalformedURLException,
	      RegistrationException,
	      G2AccessException,
	      NoSuchMethodException,
	      InstantiationException,
	      IllegalAccessException,
	      InvocationTargetException,
	      ClassManagerException
  {
    System.out.println("ExternalG2RTObjectManager::registerG2Item " + obj);
    G2RTExportManager exportManager = 
      ((ExternalG2RTRuntime)getEnvironment().getRuntime()).getExportManager();
    return super.register(exportManager.createLocalProxyVersionOfG2Item(obj));
    // Dont call this.register as it will reregister with G2
  }

  public void unregisterG2Item(Item obj)
       throws RegistrationException
  {
    try {
      G2RTExportManager exportManager = 
	((ExternalG2RTRuntime)getEnvironment().getRuntime()).getExportManager();
      super.unregister(exportManager.createLocalProxyVersionOfG2Item(obj));
    } catch (G2AccessException e) {
      throw new RegistrationException(e, e.toString());
    } catch (ClassManagerException e) {
      throw new RegistrationException(e, e.toString());
    }
  }


  public ObjectContainer getObjectContainerForG2Item(Item obj)
       throws RegistrationException
  {
    try {
      G2RTExportManager exportManager = 
	((ExternalG2RTRuntime)getEnvironment().getRuntime()).getExportManager();
      return getObjectContainer(exportManager.createLocalProxyVersionOfG2Item(obj));
    } catch (G2AccessException e) {
      throw new RegistrationException(e, e.toString());
    } catch (ClassManagerException e) {
      throw new RegistrationException(e, e.toString());
    }
  }

  public ObjectProxy move(Object obj, String destinationRuntimeURLString)
       throws RegistrationException,
	      MobilityException,
	      MalformedURLException
  {
    try {
      ExternalG2RTRuntime runtime = (ExternalG2RTRuntime)getEnvironment().getRuntime();
      G2RTExportManager exportManager = runtime.getExportManager();
      Object g2RegObj = obj;
      if (obj instanceof com.gensym.g2export.G2ProxyAccess) {
	// convert into real local obj
	
	g2RegObj = ((com.gensym.g2export.G2ProxyAccess)obj)._getG2Item();
      }
      Item g2Proxy = (com.gensym.classes.Item)
	exportManager.getConnection().callRPC(MOVE_, 
					      new Object[] {g2ObjectManager,
							      g2RegObj, 
							      destinationRuntimeURLString});
      String url = (String)g2Proxy.getPropertyValue(URL_);
      return ObjectProxyImpl.getObjectProxy(url);
    } catch (G2AccessException e) {
      throw new MobilityException(e, e.toString());
    } catch (com.gensym.util.NoSuchAttributeException e) {
      throw new MobilityException(e, e.toString());
    }
  }

  /**
   * Overridden by subclasses to return the "real" object, in the case
   * that a registered object is a proxy.
   */
  protected Object getRealObjectForMobility(Object obj)
       throws FIDARuntimeException
  {
    ExternalG2RTRuntime runtime = (ExternalG2RTRuntime)getEnvironment().getRuntime();
    G2RTExportManager exportManager = runtime.getExportManager();
    try {
      if (obj instanceof com.gensym.g2export.G2ProxyAccess) {
	// convert into real local obj
	
	com.gensym.classes.G2__Base g2Item = ((com.gensym.g2export.G2ProxyAccess)obj)._getG2Item();
	return exportManager.createLocalVersionOfG2Item((Item)g2Item);
      } if (obj instanceof com.gensym.classes.Item) {
	return exportManager.createLocalVersionOfG2Item((com.gensym.classes.Item)(obj));
      }
    } catch (G2AccessException e) {
      throw new FIDARuntimeException(e, e.toString());
    }
    return obj;
  }

  public ObjectProxy moveG2ItemFromG2(Item g2Item, String destinationFIDARuntimeURL)
       throws RegistrationException,
	      MalformedURLException,
	      ClassManagerException,
	      RuntimeNotFoundException,
	      RemoteFIDARuntimeException
  {
    try {
      ExternalG2RTRuntime runtime = (ExternalG2RTRuntime)getEnvironment().getRuntime();
      G2RTExportManager exportManager = runtime.getExportManager();
      com.gensym.g2export.Item localItem = 
	(com.gensym.g2export.Item)exportManager.createLocalVersionOfG2Item(g2Item);
      RemoteFIDARuntime remoteRuntime = 
	runtime.getRuntime(destinationFIDARuntimeURL);
      RemoteApplicationEnvironment remoteApplication = 
	remoteRuntime.getApplication(getEnvironment().getApplicationName());
      RemoteObjectManager remoteObjectManager = remoteApplication.getObjectManager();
      ObjectProxy proxy = remoteObjectManager.register((java.io.Serializable)localItem);
      return proxy;
    } catch (G2AccessException e) {
      throw new RegistrationException(e, e.toString());
    } catch (ClassManagerException e) {
      throw new RegistrationException(e, e.toString());
    }
  }

  /**
   * Convenice Method for G2 to create an instance of in a remote runtime.
   */
  public ObjectProxy createInstance(RemoteObjectManager remoteObjectManager,
				    Definition classDef,
				    Object initObject,
				    String codebase)
       throws ClassManagerException,
	      G2AccessException,
	      RemoteFIDARuntimeException,
	      RegistrationException,
	      ClassNotFoundException,
	      CreationException,
	      MalformedURLException
  {
    G2RTExportManager exportManager = 
      ((ExternalG2RTRuntime)getEnvironment().getRuntime()).getExportManager();
    String className = exportManager.getJavaClassNameFromExportIfNecessary((G2Definition)classDef);
    //System.out.println("EG2RTOM: " + className + " " + initObject + " " + codebase);
    return remoteObjectManager.create(className, initObject, codebase);
  }

  public static Object getRegisteredObjectFromObjectProxyForG2(Item dummy, // just to get g2Connection
							       ObjectProxy proxy)
       throws RemoteObjectAccessException, G2AccessException
  {
    Object obj = proxy.getRegisteredObject();
    if (obj instanceof com.gensym.g2export.G2ProxyAccess) {
      com.gensym.classes.G2__Base g2Item = ((com.gensym.g2export.G2ProxyAccess)obj)._getG2Item();
      if (g2Item != null)
	return g2Item;
    }
    if (obj instanceof com.gensym.g2export.G2__Base) {
      com.gensym.g2export.G2__Base exportedObj = (com.gensym.g2export.G2__Base)obj;
      G2Connection connection = (G2Connection)((com.gensym.classes.G2__BaseImpl)dummy).getContext();
      Symbol g2ParentClassName = exportedObj.getG2ClassName();
      // An exported G2 class, send back a proxy subclasses from the original class
      return connection.getG2ProxyForJavaObject(obj.getClass().getName(),
						g2ParentClassName,
						obj);
    }
    else
      return obj; // Only work for Items or Java Classes that have been exported into G2
  }


}
