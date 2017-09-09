
package com.gensym.net.contents.g2;

import java.net.*;
import java.io.IOException;
import com.gensym.net.g2.*;
import java.lang.reflect.InvocationTargetException;

public class item_or_value extends ContentHandler {
  private static final Object GET_MARKER = new Object ();
  private static final boolean urlHandlingDebug = false;

  @Override
  public Object getContent (URLConnection urlc) throws IOException {
    return getOrSetContent (urlc, GET_MARKER);
  }

  public Boolean setContent (URLConnection urlc, Object newValue) throws IOException {
    return (Boolean)getOrSetContent (urlc, newValue);
  }

  private final Object getOrSetContent (URLConnection urlc, Object newValueOrGetCode) throws IOException {
    G2Connection g2urlc = (G2Connection)urlc;
    String errorDetails = null;
    try {
      G2URLOperation o = g2urlc.getOperation ();
      if (urlHandlingDebug)
	System.out.println ("First Operation for resolving URL = " + o);
      Object x = G2URL.getRootItem (urlc);
      if (x == null)
	x = o.execute ();
      G2URLOperation postOp;
      if (GET_MARKER.equals(newValueOrGetCode)) {
	postOp = g2urlc.getPostGetOperation ();
	if (postOp == null)
	  return x;
      } else {
	postOp = g2urlc.getPostSetOperation ();
	if (postOp == null)
	  throw new IOException ("Internal error in item_or_value::setContent. Report to vkp.");
	postOp.setArgByName ("new-value", newValueOrGetCode);
      }
      postOp.setArgByName ("item", x);
      return postOp.execute ();
    }
    catch (IllegalAccessException iae) {
      errorDetails = iae.toString ();
    } catch (InvocationTargetException ite) {
      errorDetails = ite.toString ();
    } catch (Exception e) {
      e.printStackTrace ();
      throw new IOException (e.toString ());
    }
    if (errorDetails != null)
      throw new IOException (errorDetails);
    return null;	
  }
}

