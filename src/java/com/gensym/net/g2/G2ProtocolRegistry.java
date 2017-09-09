
package com.gensym.net.g2;

import java.util.Hashtable;

public class G2ProtocolRegistry {
  
  private static Hashtable interpreterTable = new Hashtable (9);

  public static void loadInterpreters () {
    try {
      Class.forName ("com.gensym.net.g2.NamedMediaBinHandler");
      Class.forName ("com.gensym.net.g2.NamedMediaBinQueryHandler");
      Class.forName ("com.gensym.net.g2.ServerFileSystemHandler");
    } catch (ClassNotFoundException cnfe) {
      com.gensym.message.Trace.exception (cnfe);	// Should never happen!
    }
  }

  /**
   * Leave all access to be package private for now. -vkp, 4/21/98
   */
  static Interpreter findInterpreter (String magicMarker) {
    return (Interpreter) interpreterTable.get (magicMarker);
  }

  static void registerInterpreter (String key, Interpreter i) {
    interpreterTable.put (key, i);
  }

  static void deregisterInterpreter (String key, Interpreter i) {
    if (interpreterTable.get (key).equals(i))
      interpreterTable.remove (key);
  }

}
