

package com.gensym.net.g2;

import java.net.*;
import com.gensym.jgi.*;
import com.gensym.util.*;
import com.gensym.message.*;
import java.util.*;
import com.gensym.classes.Item;
import com.gensym.classes.ImplAccess;
import java.io.IOException;
import java.lang.reflect.*;

public class G2URL {
  private URL trueURL;
  public String urlPath;
  private URLConnection cachedCxn;
  private static Hashtable itemCache = new Hashtable (5);

  public G2URL (String urlpath) throws MalformedURLException {
    trueURL = new URL (urlpath);
  }

  public G2URL (Item itm, String urlPath) throws MalformedURLException {
    this (((ImplAccess)itm).getContext ().toURLString () + "//named-item?class=unused&name=unused" + urlPath);
    this.urlPath = urlPath;
    putRootItem (trueURL, itm);
  }

  public static Object getRootItem (Object key) {
    return itemCache.get (key);
  }

  public static Object putRootItem (Object key, Object value) {
    return itemCache.put (key, value);
  }

  public static void removeRootItem (Object key) {
    itemCache.remove (key);
  }

  public Object getContent () throws IOException {
    return trueURL.getContent ();
  }

  public boolean setContent (Object newValue) throws IOException {
    G2Connection urlc = (G2Connection) trueURL.openConnection ();
    //To hell with abstraction -  com.gensym.net.contents.item_or_value
    return new com.gensym.net.contents.g2.item_or_value ().setContent (urlc, newValue).booleanValue ();
  }

  public void resetCache () {
    cachedCxn = null;
  }
}
