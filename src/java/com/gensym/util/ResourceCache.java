
package com.gensym.util;

import java.util.Hashtable;
import java.net.URL;
import java.net.MalformedURLException;
import java.io.*;
import com.gensym.message.Trace;

public abstract class ResourceCache {

  private static final Hashtable registry = new Hashtable (23);
  private static String cacheDir;

  static {
    cacheDir = System.getProperty ("com.gensym.resourcecache.repository");
    if (cacheDir == null)
      cacheDir = System.getProperty ("java.io.tmpdir");
    // read cache manifest
  }

  /*
   * Need a string key so that we can use it as a persistent
   * name for the resource. Is this too restrictive?
   */
  public static URL registerResource (String key, Object data) {
    registry.put (key, data);
    System.out.println ("ResourceCache -> putting for " + key);
    try {
      File resourceFile = new File (cacheDir, key);
      FileOutputStream fos = new FileOutputStream (resourceFile);
      ObjectOutputStream oos = new ObjectOutputStream (fos);
      oos.writeObject (data);
      oos.close ();
    } catch (java.io.IOException ioe) {
      Trace.exception (ioe);
    }
    try {
      URL url =  new URL ("memcache:///" + key);
      return url;
    } catch (MalformedURLException mue) {
      throw new RuntimeException ("Illegal setup. Handler for memcache protocol not found : " + mue);
    }
  }

  public static Object retreiveResource (String key) {
    System.out.println ("ResourceCache -> retreiving for " + key);
    Object data = registry.get (key);
    if (data == null) {
      File f = new File (cacheDir, key);
      if (f.exists ()) {
	try {
	  FileInputStream fis = new FileInputStream (f);
	  ObjectInputStream ois = new ObjectInputStream (fis);
	  data = ois.readObject ();
	} catch (java.io.IOException ioe) {
	  Trace.exception (ioe);
	} catch (java.lang.ClassNotFoundException cnfe) {
	  Trace.exception (cnfe);
	}
      }
    }
    return data;
  }

  public static URL isResourceCached (String key) {
    File f = new File (cacheDir, key);
    if (f.exists ()) {
      try {
	return new URL ("memcache:///" + key);
      } catch (MalformedURLException mue) {
      throw new RuntimeException ("Illegal setup. Handler for memcache protocol not found : " + mue);
      }
    }
    return null;
  }

  /*
   * TO DO: caching mechanism
   */
}
