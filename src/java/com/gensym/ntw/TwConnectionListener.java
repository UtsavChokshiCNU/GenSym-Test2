
package com.gensym.ntw;

import com.gensym.jgi.G2ConnectionListener;

public interface TwConnectionListener extends G2ConnectionListener {

  /**
   * Called when the a login is made through this Connection.
   * This is the point at which the connection becomes <i>active</i>
   */
  public void loggedIn (TwConnectionEvent evt);

  /**
   * Called when the connection logs out.
   * The connection is <i>inactive</i> after this point.
   */
  public void loggedOut (TwConnectionEvent evt);

  /**
   * Called when the user-mode of the connection changes.
   */
  public void userModeChanged (TwConnectionEvent evt);

}
