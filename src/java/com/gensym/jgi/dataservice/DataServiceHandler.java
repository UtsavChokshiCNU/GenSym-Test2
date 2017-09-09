package com.gensym.jgi.dataservice;

import com.gensym.util.*;
import com.gensym.classes.Item;  
import com.gensym.jgi.dataservice.*;

/**
 * A DataServiceHandler provides Raw Data Service callbacks.
 */
public interface DataServiceHandler {

  public void dispatchDataServiceEvent(Object data, int eventId, Object[] indentifyingAtts);

}
