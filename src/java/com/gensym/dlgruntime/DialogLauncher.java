
package com.gensym.dlgruntime;

import com.gensym.dlgruntime.DialogResource;
import com.gensym.classes.Item;
import com.gensym.controls.ItemProxy;
import java.awt.Component;
import com.gensym.controls.DialogCommand;

public interface DialogLauncher {

  /**
   * Launch the dialog from the resource filling the named ItemProxies
   * with the stubs passed in.
   */
  public void launch (Component component, ItemProxy[] proxies, String[] proxyNames,
                      Item[] stubs, DialogCommand closers);


  /**
   * A convenience method for launching a dialog that has one and only
   * one (possibly unnamed) ItemProxy.
   */
  public void launch (Component component, ItemProxy proxy, Item stub, DialogCommand closers);

}
