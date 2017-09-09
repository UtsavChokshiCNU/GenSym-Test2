
package com.gensym.net.g2;

import java.net.*;
import com.gensym.jgi.G2Gateway;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2ConnectionInfo;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.classes.MediaBin;
import java.util.*;
import java.io.IOException;
import java.io.InputStream;

/**
 * This class is a representation of an open connection to a G2
 * as a result of opening a URL. It can be used to resolve the URL
 * and download its contents. This might not suppport all the generic
 * methods that can be called. (Mostly throws exceptions for
 * getting the InputStream, bytes, or ContentHeaders). The latter
 * might actually be supported if we can actually determine the
 * type of the item that can be retreived as an RPC call.
 */

public class G2MediaConnection extends G2URLConnection {

  private com.gensym.jgi.G2Connection context;
  private static final java.io.PrintStream o = System.out;
  private static final boolean urlXnDebug = false;
  private MediaBin mediaBin;
  private Vector location;
  private String fileName;
  private Structure descpn;

  private static final Symbol MEDIA_BIN_ = Symbol.intern ("MEDIA-BIN");
  
  G2MediaConnection (URL g2url) {
    super (g2url);
  }

  @Override
  public String getContentType () {
    if (urlXnDebug)
      o.println ("Returning g2/item-or-value from getContentType()");
    return "g2/data";
  }


  @Override
  public void connect () throws IOException {
    try {
      if (!connected) {
	String host = url.getHost ();
	String port = Integer.toString (url.getPort ());
	G2Access contextLocal = G2Gateway.getOrMakeConnection (new G2ConnectionInfo (host, port));
	setupAccess (contextLocal);
	connected = true;
      }
    } catch (Exception e) {
      Trace.exception (e, null);
      throw new IOException (e.toString ());
    }
  }


  private void setupAccess (G2Access context) throws G2AccessException {
    String path = url.getFile ();
    //System.out.println ("Getting File = " + path);
    path = getTruePath (path);
    StringTokenizer tknzr = new StringTokenizer (path, "/", false);
    location = new Vector (3);
    while (tknzr.hasMoreTokens ()) {
      String token = tknzr.nextToken ();
      location.addElement (token);
    }
    String binName = (String) location.firstElement ();
    fileName = (String) location.lastElement ();
    location.removeElementAt (location.size () - 1);
    location.removeElementAt (0);
    Symbol binName_ = Symbol.intern (binName);
    mediaBin = (MediaBin) context.getUniqueNamedItem (MEDIA_BIN_, binName_);
  }


  private static final Symbol CREATE_DATE_ = Symbol.intern ("CREATE-DATE"),
    SIZE_IN_BYTES_ = Symbol.intern ("SIZE-IN-BYTES");

  @Override
  public long getLastModified () {
    ensureHeader ();
    Double Date = (Double) descpn.getAttributeValue (CREATE_DATE_, null);
    long date = (long)Date.doubleValue ();
    return date;
  }

  private void ensureHeader () {
    try {
      connect ();
      if (descpn == null) {
	descpn = mediaBin.describe (location, fileName);
      }
    } catch (Exception e) {
      Trace.exception (e, null);
    }
  }

  @Override
  public int getContentLength () {
    ensureHeader ();
    Integer length = (Integer) descpn.getAttributeValue (SIZE_IN_BYTES_, null);
    return length.intValue ();
  }

  @Override
  public InputStream getInputStream () throws IOException {
    connect ();
    return mediaBin.makeBinaryInputStream (location, fileName);
  }

}
