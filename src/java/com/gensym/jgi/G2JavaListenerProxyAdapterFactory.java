package com.gensym.jgi;

import java.util.Vector;
import java.util.Hashtable;
import java.lang.reflect.*;
import com.gensym.classes.Item;
import com.gensym.util.Symbol;
import com.gensym.util.DownLoad;
import com.gensym.util.Sequence;
import com.gensym.classes.G2Definition;
import com.gensym.classes.Definition;

/**
 * This class implements JavaObjectForG2ItemFactory, which will (create via
 * getJavaObjectForG2Item) a listener adapter for a G2Item which implements
 * any  G2 Java interfaces. The listener adpater passes any calls to the orginal G2 item.
 */
public class G2JavaListenerProxyAdapterFactory implements JavaObjectForG2ItemFactory {

  private static final Symbol JAVA_CLASSNAME_ = Symbol.intern("JAVA-CLASSNAME");

  // Table of adapters for a given g2proxy
  private Hashtable associatedAdapters = new Hashtable();

  /**
   * If the G2 proxy actually implements Java listeners (via Javalink/professional stubs, 
   * try to create an adapter that implements those listeners
   */
  @Override
  public Object getJavaObjectForG2Item(G2Access g2connection, Object targetObj, Item g2Proxy)
    {
      try {
	// Do we have an adapter for this class already
	Symbol g2ClassName = g2Proxy.getG2ClassName();
	Object adapterObj = associatedAdapters.get(g2ClassName);
	if (adapterObj != null && adapterObj instanceof Boolean)
	  return g2Proxy; // Tried to create an adapter previously for this G2 class and found no interfaces

	Constructor adapterCons = null;
	G2JavaStubController controller = G2JavaStubController.getG2JavaStubController();
	if (adapterObj == null) {
	  Vector interfaceList = new Vector();
	  lookupJavaInterfacesImplementedByG2Class(g2connection, g2Proxy, interfaceList);
	  if (!interfaceList.isEmpty()) {
	    adapterCons = 
	      G2JavaStubInterfaceGenerator.getAdapterConstructor(controller.getDownloader(), 
								 interfaceList, 
								 g2connection, 
								 g2ClassName);
	    associatedAdapters.put(g2ClassName, adapterCons);
	  } else {
	    associatedAdapters.put(g2ClassName, new Boolean(false)); // no adapter as no interfaces to implement
	    return g2Proxy;
	  }
	} else
	 adapterCons = (Constructor)adapterObj;

	Object adapter = G2JavaStubInterfaceGenerator.createAdapter(adapterCons, 
							  controller,  
							  g2connection,
							  g2Proxy);
	controller.associate((G2Connection)g2connection, g2Proxy, adapter);
	return adapter;
      } catch (Exception e) {
	RuntimeException newe =  new RuntimeException(e.toString());
	e.printStackTrace();
	throw newe;
      }
    }

  /** 
   * Moved through the G2 class hier for g2proxy, looking for any implemented Java interfaces
   * We can ascertain that a G2 CLASS-DEFINITION is an imported Java stub, as the CLASS-DEFINITION
   * will have a java-classname attribute (which is the fully qualified class that the definition represents).
   * We only include interfaces found at the leafs of the inheritance tree.
   */
  void lookupJavaInterfacesImplementedByG2Class(G2Access g2connection,
						  Item g2Proxy, 
						  Vector interfaceList) throws G2AccessException {
	com.gensym.util.ClassManager classManager = g2connection.getClassManager();
	G2Definition g2def = classManager.getDefinition(g2Proxy.getG2ClassName());
	boolean javaClassDefNotFound = true;
	Sequence clh = g2def.getClassInheritancePath();
	
	for (int i = 0; i < clh.size()-1; i++) {
	  G2JavaStubController controller = G2JavaStubController.getG2JavaStubController();
	  DownLoad downloader = controller.getDownloader();
	  Symbol curG2ClassName = (Symbol)clh.elementAt(i);
	  Symbol supG2ClassName = (Symbol)clh.elementAt(i+1);
	  G2Definition curG2def = classManager.getDefinition(curG2ClassName);
	  Sequence currentInhPath = curG2def.getClassInheritancePath();
	  G2Definition supG2def = classManager.getDefinition(supG2ClassName);
	  Sequence superInhPath = supG2def.getClassInheritancePath();

	  //System.out.println("Looking at " + g2def + " " + currentInhPath);
	  boolean multiInheritedBreak = (currentInhPath.size()-1 != superInhPath.size());
	  if (javaClassDefNotFound || multiInheritedBreak) {
	    // Multi Inherited or we did not found a Java class definition in a single inheritance path 
	    //System.out.println("Trying for java-def " + g2def);

	    // There was no Java class definition in the last single inheritance path
	    if (multiInheritedBreak) {
	    	javaClassDefNotFound = false;
	    }
	    
	    String javaClassName = null;
	    if (supG2def instanceof Definition) {
	      try {
		javaClassName = (String)((Definition)supG2def).getPropertyValue(JAVA_CLASSNAME_);
	      } catch (Exception e) {} // Not a java proxy definition, does not have JAVA_CLASSNAME_
	      if (javaClassName != null) {
		//System.out.println("Found java class name " + javaClassName);
		try {
		  Class javaClass = downloader.lookupClass(javaClassName);
		  if (javaClass != null && javaClass.isInterface()) {
		    interfaceList.addElement(javaClass);
		    System.out.println("Selected Interface " + javaClass);
		  }
		} catch (ClassNotFoundException e) {
		  System.err.println("lookupJavaInterfacesImplementedByG2Class Could not find " + javaClassName); 
		}
		javaClassDefNotFound = false;
	      } else
		javaClassDefNotFound = true; // still not found a java class definition
	    }
	  }
	}

    }
}
  
