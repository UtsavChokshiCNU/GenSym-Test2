/*
 * @(#)ItemData.java	1.0 97/11/05
 * 
 * Copyright (c) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 
 */
package com.gensym.classes;

import java.util.Vector;

import com.gensym.util.*;
import com.gensym.message.*;

/**
 * A package private class that is used to hold the data in a G2
 * KbWorkspace stub. This facilitates 3-tier operation where a number
 * of copies of the stub may be created by deserialization. The
 * data for the item is held in a ItemData kept in a hashtable.
 *
 * @version    1.00 11/07/97
 * @author     rpenny
 */
public class WorkspaceData extends ItemData {
  /**
   * @deprecated
   */
  public volatile WorkspaceListener workspaceListener;
  /**
   * @deprecated
   */
  public volatile boolean subscribedToWksp = false;
  /**
   * @deprecated
   */
  public volatile int activeSubscriptionIndex;
  /**
   * @deprecated
   */
  public volatile Sequence items;

  public volatile boolean configurationSnapshotCached;

  public volatile Vector containmentHierarchyItemConfigurationSnapshot;
}
