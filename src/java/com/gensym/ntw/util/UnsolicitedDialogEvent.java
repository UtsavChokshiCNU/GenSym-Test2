package com.gensym.ntw.util;

import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.ntw.TwAccess;
import com.gensym.classes.Item;

public class UnsolicitedDialogEvent extends java.util.EventObject {
  public static final int DIALOG_ENTERED = 0;
  public static final int DIALOG_EXITED = 1;
  public static final int DIALOG_UPDATED = 2;  
  private static final Integer ZERO = 0;
  static final Symbol
  ENTER_ = Symbol.intern ("ENTER"),
    UPDATE_ = Symbol.intern ("UPDATE"),
    TYPE_ = Symbol.intern ("TYPE"),
    TEXT_ = Symbol.intern ("TEXT"),
    BUTTON_ = Symbol.intern ("BUTTON"),
    CHECK_BOX_ = Symbol.intern ("CHECK-BOX"),
    VALUE_ = Symbol.intern ("VALUE"),
    ITEM_ = Symbol.intern ("ITEM");
  private int id;
  private Structure data;
  private int dialogID;
  private Item clientItem;
  private Symbol dialogName;
  private Symbol eventType;
  private Sequence dialogInfo;

  @Override
  public String toString() {
    return eventType+" "+dialogName;
  }
  
  public UnsolicitedDialogEvent(TwAccess source,
				int dialogID,
				Item clientItem,
				Symbol dialogName,
				Symbol eventType,
				Sequence dialogInfo) 				
  {
    super (source);
    this.dialogID = dialogID;
    this.clientItem = clientItem;
    this.dialogName = dialogName;
    this.eventType = eventType;
    this.dialogInfo = dialogInfo;
    this.id = ENTER_.equals(eventType)?DIALOG_ENTERED:
      (UPDATE_.equals(eventType)?DIALOG_UPDATED:DIALOG_EXITED);
  }

  public int getDialogID() {
    return dialogID;
  }

  public Item getClientItem() {
    return clientItem;
  }

  public Symbol getDialogName() {
    return dialogName;
  }

  public Sequence getDialogInfo() {
    return dialogInfo;
  }  
  
  /**
   * The id indicating the type of event
   */
  public int getID () {
    return id;
  }

}

