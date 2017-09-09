
package com.gensym.jgi.download;

import com.gensym.util.*;


  /* Check all properties have attribute names
   * match existence and argument types of getter and setter pairs (interface / implementation)
   * check only overrides of attribtutes defined by this class
   * Check all methods have interface and implementation and check arg types
   * Check all methods have names
   * Events?
   * No duplicate names in events, methods, and properties
   */
class MalformedOverridesException extends Exception {

  MalformedOverridesException (String details) {
    super (details);
    fillInStackTrace ();
  }
}
