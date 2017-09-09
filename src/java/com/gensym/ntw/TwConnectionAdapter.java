
package com.gensym.ntw;

import com.gensym.jgi.G2ConnectionAdapter;

public class TwConnectionAdapter extends G2ConnectionAdapter implements TwConnectionListener {

  @Override
  public void loggedIn (TwConnectionEvent evt) {}

  @Override
  public void loggedOut (TwConnectionEvent evt) {}

  @Override
  public void userModeChanged (TwConnectionEvent evt) {}


}
