package com.gensym.controls;

import java.io.Serializable;

import com.gensym.ntw.TwConnectionAdapter;
import com.gensym.ntw.TwConnectionEvent;

class TwActiveXConnectionAdapter extends TwConnectionAdapter implements Serializable {
  private TwActiveXConnector connector;

  public TwActiveXConnectionAdapter (TwActiveXConnector connector) {
    this.connector = connector;
  }

  @Override
  public void loggedIn (TwConnectionEvent evt) {
    connector.redispatchTwConnectionEvent(evt);
  }
  
  @Override
  public void loggedOut (TwConnectionEvent evt) {
    connector.redispatchTwConnectionEvent(evt);
  }
  
  @Override
  public void userModeChanged (TwConnectionEvent evt) {
    connector.redispatchTwConnectionEvent(evt);
  }
}    
