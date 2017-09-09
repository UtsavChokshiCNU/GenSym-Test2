package com.gensym.beansruntime;

/**
 * A class loader that is used byt the JarLoader to
 * load the classes and resources.
 *
 * Class instances are given an cookie string to identify their
 * resources but our client code creates a single instance only.  This
 * is because it is impossible in general to pass values across from
 * classes in one classloader to another.
 *
 * Some of the code used here probably should be part of JDK1.(2, I guess);
 * much of it is in the sun.* classes in JDK1.1 but that is not good enough
 * since our code only depends on jdk1.1.
 *
 * This class loader can load from:
 *   - the system classes/resources (CLASSPATH)
 *   - JAR files
 *   - specific files
 *   - specific overrides for resources
 *
 *  This code still needs a cleanup pass...
 */

import java.io.*;
import java.util.*;
import java.net.*;

// Dependencies on sun.* classes;  the fewer the better
import sun.awt.image.*;


public class G2ClassLoader extends ClassLoader {
  public static final String urlPrefix = "SIMPLE";
  private static final String protocolPathProp = "java.protocol.handler.pkgs";
  private static boolean debug = false; // debugging?
  private static boolean newattr = true;
  private String cookie;	// name of the jar file

  // all instances, by cookie.  We really only instantiate one, see next
  private static Hashtable loaders = new Hashtable();

  // The only G2ClassLoader we actually instantiate
  public static final G2ClassLoader ourLoader = createLoader("ComponentEditor", null);

  // Additional directory from where to look for resources...
  // (after CLASSPATH and loaded JARs).
  // -- currently unused --
  private String localResourceDirectory;

  // Overrides for local resources
  private Hashtable localOverrides = new Hashtable();

  /*
   * Previously loaded classes remembered
   */
  private Hashtable definedClassesTable = new Hashtable (11);

  /**
   * Create a SipleClassLoader.  It is identified by a cookie string
   */
  private G2ClassLoader(String cookie, String dir) {
    debug("("+cookie+")");
    this.cookie = cookie;
    this.localResourceDirectory = dir;
    loaders.put(cookie, this);
  }

  // Resource Hash
  private Hashtable resourceHash = new Hashtable();
  // Mime type hash
  private Hashtable mimeHash = new Hashtable();

  // Used to remember bytecodes, and local classes
  private Hashtable bytecodes = new Hashtable();


  /**
   * Set some bytecodes as a definition for a class.
   * Do not actually define the class until later
   */

  public void setDefinition(String name, byte[] buf) {
    bytecodes.put(name, buf);
  }

  /**
   * Define a class from the bytecodes that were collected early...
   */

  /**
   * May want to add some support for reporting classes replicated across
   * different JAR files.
   */

  public synchronized void applyDefinitions(Vector classList) {
    applyDefinitions(classList,null);
  }

  /**
   * @undocumented
   */
  public synchronized void applyDefinitions(Vector classList, Counter counter) {
    // go through the bytecode arrays defininng.
    // NOTE: sometimes a forward reference forces a class
    // to get defined early; in that case, skip it!
    debug("ApplyDefinitions/START");
    for (Enumeration k = classList.elements();
	 k.hasMoreElements();) {
      String classname = (String) k.nextElement();
      debug("ApplyDefinitions/Considering "+classname);
      Class c = findLoadedClass(classname);
      if (counter != null) {
    	  counter.click();
      }
      try {
	if (c == null) {
	  try {
	    c = findSystemClass(classname);
	    debug("  findSystemClass returned " + c);
	  } catch (ClassNotFoundException e) {
	    // Drop through.
	  }
	}
	if (c == null) {
	  // Not yet defined, do so.
	  applyDefinition(classname, true);
	}
      } catch (NoClassDefFoundError error)
	{
	  debug("__________________________");
	  debug("className "+classname);
	  System.out.println("WARNING: the class "+classname+" could not find");
	}
    }
    debug("ApplyDefinitions/END");
  }


  private Class applyDefinition(String name, boolean resolve) {
    debug("applyDefinition("+name+")");
    byte buf[] = (byte []) bytecodes.get(name);
    if (buf == null) {
      debug("  is null");
      return null;
    } else {
      Class c = super.defineClass(null, buf, 0, buf.length);
      if (c != null && resolve) {
	resolveClass(c);
      }
      // Check that the loaded class has the name we expect
      if (!c.getName().equals(name)) {
	System.err.println("\nWARNING: file name versus class name mismatch");
	String fname = name.replace('.', '/') + ".class";
	System.err.println("    JAR entry \"" + fname + "\" was expected "
			   + "to contain class \"" + name + "\"");
	System.err.println("    but instead contained class \"" + c.getName() + "\"");
	System.err.println("    This may cause future class-loading problems.\n");
      }
      return c;
    }
  }

  /**
   * Define a class from a file
   */

  private static byte[] getByteArray(InputStream is) throws IOException {
    int len = 0;
    byte buff[] = new byte[512];
    for (;;) {
      if (len == buff.length) {
	// Allocate a new, bigger, buffer.
	byte newBuff[] = new byte[buff.length * 2];
	System.arraycopy(buff, 0, newBuff, 0, len);
	buff = newBuff;
      }
      int r = is.read(buff, len, buff.length-len);
	    
      if (r < 0) {
	break;
      }
      len += r;
    }
    return buff;
  }

  /** Load a class from an array of bytes
  */
  public Class loadClass(byte[] bytes)
  {
    Class c = super.defineClass(null, bytes, 0, bytes.length);
    return c;
  }
  
  /**
   * Define a class with caching
   * @param className the name of the Class
   * @param bytes the bytes defining the class
   * @return a newly generated or previously defined class
   */
  public Class loadClass (String className, byte[] bytes) {
    Class newClass = (Class) definedClassesTable.get (className);
   
    debug("loadClass lookup("+className+
	  ")="+newClass);
    if (newClass == null) {
      newClass = loadClass (bytes);
      definedClassesTable.put (className, newClass);
    }
    return newClass;
  }

  public void reallyResolveClass(Class c)
  {
    resolveClass(c);
  }

  /**
   * Public version of findLoadedClass() to expose it across
   */

  @Override
  public Class findClass(String name) {
    return findLoadedClass(name);
  }

  /**
   * This is the main method for ClassLoaders, that is being redefined
   */

  @Override
  protected Class loadClass(String name, boolean resolve)
throws ClassNotFoundException {
  debug("loadClass("+name+", "+resolve+")");
  Class cl = findLoadedClass(name);

  if (cl == null) {
    try {
      cl = findSystemClass(name);
      debug("  findSystemClass returned " + cl);
      return cl;
    } catch (ClassNotFoundException e) {
      // Drop through.
    }
  }

  if (cl == null) {
    debug("  not loaded");
    cl = applyDefinition(name, resolve);
  }

  if (cl == null) {
    throw new ClassNotFoundException(name);
  }
  if (resolve) {
    resolveClass(cl);
  }
  return cl;
  }

  /**
   * The resource stuff
   */

  /**
   * Assign an InputStream as the source for a given property name
   * This value comes first after the system resources
   */

  public void setLocalResourceSource(String name, InputStreamProducer isp) {
    localOverrides.put(name, isp);
  }

  public void putLocalResource(String name, byte[] data, String type) {
    debug("putLocalResource for "+name+" is "+data);
    resourceHash.put(name, data);
    mimeHash.put(name, type);
  }

  @Override
  public URL getResource(String name) {
    debug("getResource("+name+")");
    URL back = getSystemResource(name);
    if (back != null) {
      debug("getResource("+name+"): "+back);
      return back;
    }
    return getLocalResource(name);
  }

  @Override
  public InputStream getResourceAsStream(String name) {
    InputStream back = getSystemResourceAsStream(name);
    if (back != null) {
      debug("getResourceAsStream("+name+") is a system resource");
      return back;
    }
    return getLocalResourceAsStream(name);
  }


  /**
   * Return a URL to the desired resource.
   */
  private URL getLocalResource(String name) {
    debug("getLocalResource("+name+")");
    // Check if there is an override
    Object o;
    o = localOverrides.get(name);
    if (o == null) {
      // Check on the JAR objects
      debug("ResourceHash check on "+name);
      o = resourceHash.get(name);
    }
    if (o == null && localResourceDirectory != null) {
      // Try in localResourceDirectory
      File f = new File(localResourceDirectory, name);
      if (f.exists()) {
    	  o = 1; // anything will do
      }
    }
    if (o != null) {
      // Create a URL to refer to this resource
      try {
	URL url = new URL("jarresource",
			  null,
			  "/"+urlPrefix+
			  cookie+"/+/"+name);
	debug("  "+url.toExternalForm());
	return url;
      } catch (Exception e) {
	debug("Exception "+e+" while building a resource URL");
	return null;
      }
    }
    return null;
  }

  private InputStream getLocalResourceAsStream(String name) {
    debug("getLocalResourceAsStream("+name+")");
    Object o;
    // Check if there is an override
    o = localOverrides.get(name);
    if (o!=null) {
      return ((InputStreamProducer) o).getInputStream();
    }
    // Check data loaded from JAR
    o = resourceHash.get(name);
    if (o != null) {
      debug("Found resource: " + name +
	    " in the classloader: "+cookie);
      byte[] buf = (byte []) o;
      return new ByteArrayInputStream(buf);
    }
    if (localResourceDirectory != null) {
      // Now try in localResourceDirectory
      File f = new File(localResourceDirectory, name);
      debug("getLocalResourceAsStream for "+name+"? "+f);
      try {
	return new FileInputStream(f);
      } catch (Exception ex) {
	return null;
      }
    }
    return null;
  }

  /**
   * Returns an InputStream on the resource
   */

  public static G2ClassLoader createLoader(String cookie,
					       String dir) {
    G2ClassLoader back = getLoader(cookie);
    if (back != null) {
      if (!back.localResourceDirectory.equals(dir)) {
	throw new Error("internal error!");
      }
      return back;
    } else {
      return new G2ClassLoader(cookie, dir);
    }
  }

  private static G2ClassLoader getLoader(String cookie) {
    return (G2ClassLoader) loaders.get(cookie);
  }

  // get the local resource object...

  public static Object getLocalResource(String cookie,
					String name) {
    debug("getLocalResource("+cookie+", "+name+")");
    G2ClassLoader cl = getLoader(cookie);

    // Check if there is an override
    Object o = cl.localOverrides.get(name);
    if (o!=null) {
      return ((InputStreamProducer) o).getInputStream();
    }
    // Check data loaded from JAR
    String type = (String) cl.mimeHash.get(name);
    if (type!=null) {
      // Came from JAR
      byte[] buf = (byte []) cl.resourceHash.get(name);
      if (type.startsWith("image")) {
	debug ("Type = image of length " + buf.length);
	return new ByteArrayImageSource(buf);
      } else {
	return new ByteArrayInputStream(buf);
      }
    }
    if (cl.localResourceDirectory != null) {
      // Check into localResourceDirectory
      File f = new File(cl.localResourceDirectory, name);
      if (f.exists()) {
	try {
	  URL url = new URL("file",
			    null,
			    f.getAbsolutePath());
	  return url.getContent();
	} catch (Exception e) {
	  throw new Error("no such resource"); // should it be a security error?
	}
      }
    }
    return null;
  }

  // REMIND - simplify the whole cookie thing.

  public static InputStream getLocalResourceAsStream(String cookie,
						     String name) {
    G2ClassLoader cl = getLoader(cookie);
    return cl.getLocalResourceAsStream(name);
  }

  /**
   * Debugging stuff
   */
  private static void debug(String msg) {
    if (debug) {
      System.err.println("G2ClassLoader:: "+msg);
      System.err.flush();
    }
  }

  /**
   * Initialization of statics
   */
  static {
    // Add this protocol type to the http properties
    Properties newP = new Properties(System.getProperties());
    newP.put(protocolPathProp,
	     newP.getProperty(protocolPathProp)+"|com.gensym.beansruntime");
    System.setProperties(newP);
  }
}
