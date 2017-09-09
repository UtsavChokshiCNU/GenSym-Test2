package com.gensym.demos.dialogapplet;

import com.gensym.dlgruntime.*;
import com.gensym.controls.*;
import com.gensym.classes.Item;
import java.awt.*;


public class DialogAppletLauncher implements DialogLauncher
{
  
  @Override
  public void launch (Component component, ItemProxy proxy, 
		      Item stub, DialogCommand closers)
  {

  }
  
  @Override
  public void launch (Component component, ItemProxy[] proxies,
		      String[] proxyNames, Item[] stubs, DialogCommand closer) {
    if (proxyNames != null && proxyNames.length != stubs.length)
      throw new IllegalArgumentException ("ProxyNames and Stubs must be of equal length");

    if (closer == null)
      closer = new DialogCommand ();
    ItemProxy proxy = null;

    //closer.addDialogStateListener(this);
    closer.setProxies (proxies);
    
    // This is for the case when there is only one
    // item specified, and there is only one proxy
    // in the dialog and no name was specified
    if (proxies.length == 1 && stubs.length == 1 && proxyNames == null) {
      proxy = proxies[0];
      try {			// throw these!
	proxy.setProxy(stubs[0]);
	proxy.download();
      } catch (Exception e) {
	e.printStackTrace();
      }
    }
    // Otherwise try to match up the items and
    // the proxies
    else
      {
	for (int i=0; i < proxies.length; i++) {
	  proxy = proxies[i];
	  
	  for (int j=0; j < proxyNames.length; j++) {
	    if (proxy.getName().equals(proxyNames[j])) {
	      if (stubs[j] != null) {
		try {	// throw these
		  proxy.setProxy(stubs[j]);
		  proxy.download();
		} catch (Exception e) {
		  e.printStackTrace();
		}
	      }
	    }
	  }
	}
      }
    
  
    
  }
}
