/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ItemEvent.java
 *
 *   Description: 
 *     
 *
 *	 Author:
 *		Robert Penny		May/97
 *
 *     
 *   Modifications:
 *
 */
package com.gensym.util;

import com.gensym.classes.Item;

import com.gensym.message.Resource;

public class ItemEvent extends SerializableSourceEvent {

  private static final Resource i18nError =
  Resource.getBundle("com.gensym.resources.Errors");

  private static final Symbol MODIFY_ = Symbol.intern ("MODIFY"),
    DELETE_ = Symbol.intern ("DELETE"),
    INITIAL_VALUE_ = Symbol.intern ("INITIAL-VALUE");

  public static final int MODIFY = 0;
  public static final int DELETE = 1;
  public static final int INITIAL_VALUE = 2;
  
  private int ID;
  protected Item item;
  protected Sequence denotation;
  protected Object newValue;
  protected Object userData;
  protected int subscriptionHandle;

  public ItemEvent(Object source, Symbol code, Item itm,
		     Sequence denotation,
		     Object value, Object data, int handle) {
    super(source);
    item = itm;
    ID = mapCodeToID(code);
    this.denotation = denotation;
    newValue = value;
    userData = data;
    subscriptionHandle = handle;
  }

  protected Symbol mapIDToCode(int ID) {
    switch (ID) {
    case MODIFY:
      return MODIFY_;
    case DELETE:
      return DELETE_;
    case INITIAL_VALUE:
      return INITIAL_VALUE_;
    default: 
      throw new IllegalArgumentException(i18nError.format("InvalidEventID", ID, this));
    }
  }

  protected int mapCodeToID(Symbol modificationCode) {
    if (MODIFY_.equals(modificationCode))
      return MODIFY;
    else if (DELETE_.equals(modificationCode))
      return DELETE;
    else if (INITIAL_VALUE_.equals(modificationCode))
      return INITIAL_VALUE;
    else
      throw new IllegalArgumentException(i18nError.format("InvalidEventCode",
							  modificationCode,
							  this));
  }

  public Symbol getModificationCode() {
    return mapIDToCode(ID);
  }

  public int getID() {
    return ID;
  }

  public Item getItem() {
    return item;
  }

  public Sequence getDenotation() {
    return denotation;
  }

  public Object getNewValue() {
    return newValue;
  }

  public Object getUserData() {
    return userData;
  }

  public Integer getSubscriptionHandle() {
    return subscriptionHandle;
  }

  @Override
  public String toString () {
    return super.toString () + "{" +
      mapIDToCode(ID) + " : on " + item +  ", Dentn = " +
      denotation + ", new value = " + newValue + "}";
  }
}
