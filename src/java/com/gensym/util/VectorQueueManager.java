/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved. 
 * 
 *   VectorQueueManager.java 
 * 
 * 
 */ 
  
package com.gensym.util;

import com.gensym.core.util.BaseVectorQueueManager;

/** A class that accumulates events, then processes them in groups.
 * Is useful in cases where some efficiency can be derived in the
 * processing of events in groups rather than one-at-a-time.
 */
public abstract class VectorQueueManager extends BaseVectorQueueManager {
}
	
