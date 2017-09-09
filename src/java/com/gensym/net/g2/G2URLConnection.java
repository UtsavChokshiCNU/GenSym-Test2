
package com.gensym.net.g2;

import java.net.*;
import com.gensym.jgi.*;

abstract class G2URLConnection extends URLConnection {

  G2URLConnection (URL url) {
    super (url);
  }

  protected G2Access openConnection (URL url) throws G2AccessInitiationException, ConnectionTimedOutException {
    String host = url.getHost ();
    String port = Integer.toString (url.getPort ());
    G2Access context = G2Gateway.getOrMakeConnection (new G2ConnectionInfo (host, port));
    return context;
  }

  /**
   * Skip the "magic" marker
   */
  protected String getTruePath (String file) {
    return file.substring (file.indexOf ('/', 1));
  }
}
