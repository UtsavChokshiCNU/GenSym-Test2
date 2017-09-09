
package com.gensym.clscupgr;

import java.util.Hashtable;
import java.util.Enumeration;

import com.gensym.message.Trace;
import com.gensym.util.Symbol;
import com.gensym.util.UnexpectedException;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.jgi.G2ConnectionAdapter;
import com.gensym.classes.Kb;
import com.gensym.classes.Module;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.util.KbModuleAdapter;
import com.gensym.ntw.util.KbEvent;
import com.gensym.util.UnexpectedException;

/**
 * Handles loading and unloading of modules consistently.
 * Creates a ModuleHandler for each (registered) module
 * and calls moduleLoaded when the named module is loaded
 * and calls moduleUnloaded whenever the module is deleted,
 * the KB is cleared or the connection is closed.
 */
public class ModuleManager implements UtilityModuleNames {

  private static Hashtable handlerFactories = new Hashtable();

  /**
   * Register a ModuleHandler factory object that will be called whenever
   * the named module is loaded in G2. If you wish for an existing ModuleHandler
   * be re-used when a module is loaded, it is up to your factory to
   * keep track of the instances it hands out.
   * <p>
   * It is best to call this method before any connections are made.
   * @throws ModuleHandlerFactoryAlreadyRegisteredException
   */
  public static void registerModuleHandlerFactory(Symbol moduleName,
						  ModuleHandlerFactory newFactory)
  throws ModuleHandlerFactoryAlreadyRegisteredException {
    ModuleHandlerFactory factory =
      (ModuleHandlerFactory)handlerFactories.get(moduleName);
    if (factory != null)
      throw new ModuleHandlerFactoryAlreadyRegisteredException(moduleName,
							       factory);
    handlerFactories.put(moduleName, newFactory);
  }

  /**
   * Unregisters the factory for a given module
   * @returns the registered factory, or null if no factory was registered.
   */
  public static ModuleHandlerFactory unregisterModuleHandlerFactory(Symbol moduleName) {
    return (ModuleHandlerFactory)handlerFactories.remove(moduleName);
  }

  /**
   * @returns the registered factory, or null if no factory was registered.
   */
  public static ModuleHandlerFactory getRegisteredModuleHandlerFactory(Symbol moduleName) {
    return (ModuleHandlerFactory)handlerFactories.get(moduleName);
  }



  private TwAccess cxn;
  private Hashtable loadedModules = new Hashtable ();

  public ModuleManager (TwAccess cxn) {
    this.cxn = cxn;
    cxn.addG2ConnectionListener (new ModuleConnectionAdapter ());
  }

  /**
   * Listener method. Do not call.
   * Looks for a ModuleHandlerFactory for this moduleName_, then calls
   * its makeModuleHandler method. If this method returns a ModuleHandler, then
   * the ModuleHandler has its moduleLoaded method called.
   */
  public void moduleLoaded (Symbol moduleName_) {
    if (moduleName_ == null)
      return;
    ModuleHandlerFactory factory = (ModuleHandlerFactory)handlerFactories.get(moduleName_);
    if (factory != null) {
      ModuleHandler handler = factory.makeModuleHandler(cxn, moduleName_);
      if (handler != null) {
	loadedModules.put (moduleName_, handler);
	handler.moduleLoaded (cxn, moduleName_);
      }
    }
  }

  /**
   * Listener method. Do not call.
   * If this moduleName_ has an associated ModuleHandler, then that
   * ModuleHandler has its moduleUnloaded method called.
   */
  public void moduleUnloaded (Symbol moduleName_) {
    if (moduleName_ != null) {
      ModuleHandler handler = (ModuleHandler) loadedModules.remove (moduleName_);
      if (handler != null)
	handler.moduleUnloaded (cxn, moduleName_);
    }
  }

  private void unloadAllModules () {
    Enumeration moduleNames = loadedModules.keys ();
    while (moduleNames.hasMoreElements ())
      moduleUnloaded ((Symbol)moduleNames.nextElement ());
  }

  /**
   * @undocumented (??) maybe it's ok to be public
   */
  public ModuleHandler getModuleHandler(Symbol moduleName) {
    return (ModuleHandler)loadedModules.get(moduleName);
  }

  class ModuleInitializer extends KbModuleAdapter {
    @Override
    public void receivedInitialModules (KbEvent evt) {
      try {
	Kb kb = (Kb)evt.getSource ();
	Module[] initialModules = kb.getModules ();
	for (int i=0; i<initialModules.length; i++) {
	  //System.out.println ("initialModules = " + initialModules[i].getName());
	  moduleLoaded (initialModules[i].getName());
	}
      } catch (G2AccessException g2ae) {
	Trace.exception (g2ae);
      }
    }
    @Override
    public void moduleCreated (KbEvent evt) {
      //System.out.println ("Module Created: " + evt.getModule ().getName());
      moduleLoaded (evt.getModule().getName());
    }
    @Override
    public void moduleDeleted (KbEvent evt) {
      //System.out.println ("Module Deleted: " + evt.getModule ().getName());
      moduleUnloaded (evt.getModule().getName());
    }
    @Override
    public void kbCleared (KbEvent evt) {
      //System.out.println ("KB cleared");
      unloadAllModules ();
    }
  }

  class ModuleConnectionAdapter extends G2ConnectionAdapter {
    @Override
    public void g2ConnectionInitialized (G2ConnectionEvent evt) {
      try {
	cxn.getKb().addKbModuleListener (new ModuleInitializer ());
      } catch (G2AccessException g2ae) {
	Trace.exception (g2ae);
	throw new UnexpectedException (g2ae);
      }
    }
    @Override
    public void g2ConnectionClosed (G2ConnectionEvent evt) {
      unloadAllModules ();
    }
  }
}
