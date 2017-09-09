
package com.gensym.net.g2;

import java.net.*;
import com.gensym.jgi.G2Gateway;

/**
 * The class <code>com.gensym.net.g2.Handler</code> is a protocol
 * handler that knows how to resolve <code>g2</code> URLs. In order to
 * use this class, the application must either have the System property
 * java.protocol.handler.pkgs set to include com.gensym.net (in which
 * case, an instance of this class will be created the first time a
 * URL with the g2 protocol is created), or else
 * install a URLStreamHandlerFactory that returns an instance of this
 * class.<p>
 *
 * A typical example of a g2 URL is
 * g2://bombay:1111/get-named-item?class=pump&name=ethylene-tank-outlet
 *
 * @author vkp
 * @version 1.0 3/5/97
 */

public class Handler extends URLStreamHandler {

  /** Zero arg constructor called by StreamHandlerFactory
   */
  public Handler () {
  }

  @Override
  public URLConnection openConnection (URL g2url) throws java.io.IOException {
    //System.out.println ("In g2/Handler -> openConnection ()");
    //Thread.dumpStack ();
    String path = g2url.getFile ();
    String magicMarker = path.substring (1, path.indexOf ('/', 1));
    Interpreter pathInterpreter = G2ProtocolRegistry.findInterpreter (magicMarker);
    if (pathInterpreter == null)
      throw new MalformedURLException ("Unknown magic marker <" + magicMarker + ">in URL");
    URLConnection urlCnxn = pathInterpreter.createConnection (g2url);
    return urlCnxn;
  }
}
