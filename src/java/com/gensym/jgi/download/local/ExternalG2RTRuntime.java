package com.gensym.jgi.download.local;

import com.gensym.fida.*;
import com.gensym.fida.support.*;
import com.gensym.fida.support.message.*;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.JGInterface;
import com.gensym.jgi.TaskHandler;
import com.gensym.classes.ImplAccess;
import com.gensym.classes.GsiInterface;
import com.gensym.classes.Item;

public class ExternalG2RTRuntime extends GensymFIDARuntime
{

  G2RTExportManager exportManager;
  Item g2RuntimeInterface;

  private ExternalG2RTRuntime(String domain,
		       String runtimeName,
		       String registryHost,
		       int registryPort)
       throws FIDARuntimeException
  {
    super(domain, runtimeName, registryHost, registryPort);
  }

  private ExternalG2RTRuntime(String domain,
			 String runtimeName)
       throws FIDARuntimeException
  {
    super(domain, runtimeName);
  }


  public static ExternalG2RTRuntime getExternalG2RTRuntime(String domain,
						 String runtimeName,
						 String registryHost,
						 int registryPort,
						 GsiInterface g2RuntimeInterface)
       throws FIDARuntimeException,
	      FactoryAlreadySetException
  {
    // First Check if there is a Runtime installed
    try {
      FIDARuntime runtime = FIDARuntimeSystem.getFIDARuntime();
      if (runtime != null && !(runtime instanceof ExternalG2RTRuntime))
	throw new FIDARuntimeException("A Runtime has already been installed in this JavaLink G2Runtime" +
				     " Gateway but it is not of the correct type");
      else if (runtime != null)
	return (ExternalG2RTRuntime)runtime;
    } catch (RuntimeNotFoundException e) {
      // dont care, we are going to create one
    }
    FIDARuntimeSystem.setFIDARuntimeFactory(runtimeFactory);
    ExternalG2RTRuntime runtime = 
      (ExternalG2RTRuntime)FIDARuntimeSystem.getFIDARuntime(domain,
							    runtimeName,
							    registryHost,
							    registryPort);
    G2Access connection = ((ImplAccess)g2RuntimeInterface).getContext();
    runtime.g2RuntimeInterface = g2RuntimeInterface;
    runtime.exportManager = new G2RTExportManager(connection, 
						  runtime);

    JGInterface.setMethodDispatchHandler(new TaskHandler() {
       @Override
       public boolean start(Runnable task,
		       Object target,
		       boolean runInQueuedThreadRequest) {
	 // really dumb, does not queue threads
	 new Thread(task).start();
	 return true;
       }
    });

    return runtime;
  }

  public Item getG2RuntimeInterface()
  {
    return g2RuntimeInterface;
  }

  public G2RTExportManager getExportManager()
  {
    return exportManager;
  }

  private static final FIDARuntimeFactory runtimeFactory = 
  new FIDARuntimeFactory() {
    public FIDARuntime createFIDARuntime(String domain,
				     String runtimeName,
				     String registryHost,
				     int registryPort)
      throws FIDARuntimeException {
      return new ExternalG2RTRuntime(domain,
				     runtimeName,
				     registryHost,
				     registryPort);
    }
  };

  private static final ObjectManagerFactory objectManagerFactory = 
  new ObjectManagerFactory() {
    public ObjectManager createObjectManager(Environment environment) {
      return new ExternalG2RTObjectManager(environment);
    }
  };

  private static final ClassManagerFactory classManagerFactory = 
  new ClassManagerFactory() {
    public ClassManager createClassManager(Environment environment) {
      return new ExternalG2RTClassManager(environment);
    }
  };

  static {
    try {
      // Ensure we are using the correct ObjectManager
      EnvironmentImpl.setObjectManagerFactory(objectManagerFactory);
      EnvironmentImpl.setClassManagerFactory(classManagerFactory);
      ExternalG2RTMessageManager.setMessageManagerImplFactory();
    } catch (Exception e) {
      throw new Error("Cant set ExternalG2ObjectManager factory, due to " + e.toString());
    }
  }

}

  
