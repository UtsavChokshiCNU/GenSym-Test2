package com.gensym.jgi;

import com.gensym.util.*;
import com.gensym.classes.Item;
import com.gensym.jgi.dataservice.*;

/**
 * This is the superior classes of any DataService
 */
public class JGIDataService implements DataServiceHandler {

  protected G2Connection connection;
  protected DataServiceListener listener;

  public JGIDataService(G2Connection connection, DataServiceListener listener) {
    this.connection = connection;
    this.listener = listener;
    if (!(G2Gateway.class.isAssignableFrom(connection.getClass())))
      throw new RuntimeException("DataService only supported from a G2Gateway, connection is a " + 
				 connection.getClass() + " which is not assignable from G2Gateway");
    ((G2Gateway)connection).setDataServiceHandler(this);  
  }

  @Override
  public void dispatchDataServiceEvent(Object data, int eventId, Object[] identifingAttributes) {
    System.out.println("JGIDataService dispatchDataServiceEvent" + " " + eventId);
  }
}
