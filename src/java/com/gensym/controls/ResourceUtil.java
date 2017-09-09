/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ResourceUtil.java
 *
 */

/** A utility class used to retrieve a named resource bundle
*/
package com.gensym.controls;

import com.gensym.message.Resource;
import java.util.MissingResourceException;
import com.gensym.message.Trace;

class ResourceUtil {

  /** Retrieve a resource based on a String
   */
  public static Resource getBundle(String resourceName) {
    Resource bundle = null;

    if (!(resourceName.trim()).equals(""))
      try {
        bundle = Resource.getBundle(resourceName.trim());
      }
      catch (MissingResourceException ex) {
        Trace.exception (ex, null);
      }

    return bundle;
  }

}

