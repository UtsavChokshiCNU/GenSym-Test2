/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 RMIWorkspaceEvent.java
 *
 *   Description: 
 *     Encapsulates workspace information for queueing and transmission
 *     
 *
 *	 Author:
 *		R. Penny		Aug/97
 *
 *     
 *   Modifications:
 *
 */

package com.gensym.ntw.rmi;

import com.gensym.util.*;
import com.gensym.message.*;

import java.util.EventObject;
import java.io.Serializable;
import com.gensym.classes.Item;

/** Encapsulates workspace information for transmission and queueing */

public class RMIWorkspaceEvent extends EventObject implements Serializable {
  private Symbol notificationCode;
  private Item item;
  private Structure newInfo;
  private int subscriptionHandle;
  private TwRMIAccess source;

  public RMIWorkspaceEvent (TwRMIAccess source,
			    Symbol notificationCode,
			    Item item,
			    Structure newInfo,
			    int subscriptionHandle) {
    super(source);
    this.notificationCode = notificationCode;
    this.item = item;
    this.newInfo = newInfo;
    this.subscriptionHandle = subscriptionHandle;
  }

  public Symbol getNotificationCode() {
    return notificationCode;
  }

  public Item getItem() {
    return item;
  }

  public Structure getNewInfo() {
    return newInfo;
  }

  public int getSubscriptionHandle() {
    return subscriptionHandle;
  }
}
