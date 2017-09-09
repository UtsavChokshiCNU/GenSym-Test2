package com.gensym.controls;

import java.util.EventListener;

public interface TwActiveXConnectionListener extends EventListener {

  /**
   * Called when the a login is made through this Connection.
   * This is the point at which the connection becomes <i>active</i>
   */
  public void loggedIn (TwActiveXConnectionEvent evt);

  /**
   * Called when the connection logs out.
   * The connection is <i>inactive</i> after this point.
   */
  public void loggedOut (TwActiveXConnectionEvent evt);

  /**
   * Called when the user-mode of the connection changes.
   */
  public void userModeChanged (TwActiveXConnectionEvent evt);
}
