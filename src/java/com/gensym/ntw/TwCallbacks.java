/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TwCallbacks.java
 *
 *     
 *   Modifications:
 *
 */
package com.gensym.ntw;

import com.gensym.jgi.G2Callbacks;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.message.*;
import com.gensym.classes.Item;

public interface TwCallbacks extends G2Callbacks {

  public void handleWorkspaceSubscriptions(WorkspaceEvent event);

  public Object HANDLEWORKSPACESUBSCRIPTIONS(Symbol notificationCode, //modfnCode
					     Item itm, 
					     Structure extraInfo,
					     int subscriptionHandle);

  public void processWorkspaceShowingEvent(WorkspaceShowingEvent event);
}
