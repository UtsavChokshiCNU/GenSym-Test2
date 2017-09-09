/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TrendChartEvent.java
 *
 *   Description: 
 *     
 *
 *	 Author:
 *		Robert Penny		July/97
 *
 *     
 *   Modifications:
 *
 */


package com.gensym.ntw.util;

import com.gensym.classes.Item;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.util.SerializableSourceEvent;
import com.gensym.message.Resource;
import com.gensym.util.symbol.TrendChartSymbols;

/** These are the events issued by TrendCharts as part of the
 * TrendChart protocol.
 * @see com.gensym.ntw.TwGateway.representTrendChart
 * @see com.gensym.ntw.TwGateway.HANDLETRENDCHARTSUBSCRIPTION
 */
public class TrendChartEvent extends SerializableSourceEvent
implements TrendChartSymbols{

  public static final int SLOT_CHANGE = 0;
  public static final int ACTIVATION = 1;
  public static final int CLOCK_DISCONTINUITY = 2;
  public static final int GENERAL_UPDATE = 3;
  public static final int ELEMENT_ADDED = 4;
  public static final int ELEMENT_DELETED = 5;

  public static final Symbol ELEMENT_ADDED_ = Symbol.intern ("ELEMENT-ADDED");
  public static final Symbol ELEMENT_DELETED_ = Symbol.intern ("ELEMENT-DELETED");
  private static final Resource i18nError =
              Resource.getBundle("com.gensym.resources.Errors");

  /** The unique identifier of the underlying item in G2 */
  private int subscriptionHandle;
  /** */
  private int ID;
  /** The actual information being passed back by G2. It is up to the
   * subscriber to understand the internal structure of this Structure.
   */
  private Structure newInfo;

  public TrendChartEvent (Object source,
			  Item item,
			  int subscriptionHandle,
			  Symbol notificationType,
			  Structure newInfo) {
    super(source);
    this.subscriptionHandle = subscriptionHandle;
    ID = mapCodeToID(notificationType);
    this.newInfo = newInfo;
  }

  public Item getItem() {
    return (Item)getSource();
  }

  public int getSubscriptionHandle() {
    return subscriptionHandle;
  }

  protected Symbol mapIDToCode(int ID) {
    switch (ID) {
    case GENERAL_UPDATE:
      return GENERAL_UPDATE_;
    case SLOT_CHANGE:
      return SLOT_CHANGE_;
    case ACTIVATION:
      return ACTIVATION_;
    case CLOCK_DISCONTINUITY:
      return CLOCK_DISCONTINUITY_;
    case ELEMENT_ADDED:
      return ELEMENT_ADDED_;
    case ELEMENT_DELETED:
      return ELEMENT_DELETED_;
    default: 
      throw new IllegalArgumentException(i18nError.format("InvalidEventID", ID, this));
    }
  }

  protected int mapCodeToID(Symbol modificationCode) {
    if (GENERAL_UPDATE_.equals(modificationCode))
      return GENERAL_UPDATE;
    else if (SLOT_CHANGE_.equals(modificationCode))
      return SLOT_CHANGE;
    else if (ACTIVATION_.equals(modificationCode))
      return ACTIVATION;
    else if (CLOCK_DISCONTINUITY_.equals(modificationCode))
      return CLOCK_DISCONTINUITY;
    else if (ELEMENT_ADDED_.equals(modificationCode))
      return ELEMENT_ADDED;
    else if (ELEMENT_DELETED_.equals(modificationCode))
      return ELEMENT_DELETED;
    else
      throw new IllegalArgumentException(i18nError.format("InvalidEventCode",
							  modificationCode,
							  this));
  }

  public int getID() {
    return ID;
  }

  public Symbol getNotificationType() {
    return mapIDToCode(ID);
  }

  public Structure getNewInfo() {
    return newInfo;
  }

  @Override
  public String toString() {
    return "[" + getClass() + ": " + source + ", " + 
      ", " + mapIDToCode(ID) + ": " + newInfo + "]";
  }
}
    
    
