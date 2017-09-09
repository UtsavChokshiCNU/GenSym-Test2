/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 WorkspaceEvent.java
 *
 *   Description: 
 *     
 *
 *	 Author:
 *		Paul B. Konigsberg, Robert Penny		May/97
 *
 *     
 *   Modifications:
 *
 */
package com.gensym.util;

import com.gensym.classes.Item;
import java.util.EventObject;
import java.io.Serializable;

/**
 * The workspace event
 *
 */
public class WorkspaceEvent extends SerializableSourceEvent {
  static final long serialVersionUID = 3301054445043171568L;
  private Item item;
  private Structure info;
  private int id;

  private static final Symbol
  ITEM_INSERT_                = Symbol.intern ("ITEM-INSERT"),
  ITEM_REMOVE_                = Symbol.intern ("ITEM-REMOVE"),
  ITEM_MOVE_                  = Symbol.intern ("ITEM-MOVE"),
  ITEM_RESIZE_                = Symbol.intern ("ITEM-RESIZE"),
  ITEM_ROTATE_                = Symbol.intern ("ITEM-ROTATE"),
  ITEM_COLOR_PATTERN_CHANGE_  = Symbol.intern ("ITEM-COLOR-PATTERN-CHANGE"),
  ITEM_ICON_VARIABLES_CHANGE_ = Symbol.intern ("ITEM-ICON-VARIABLES-CHANGE"),
  ITEM_CHANGE_                = Symbol.intern ("ITEM-CHANGE"),
  WORKSPACE_RESIZED_          = Symbol.intern ("WORKSPACE-RESIZED"),
  INITIAL_DOWNLOAD_           = Symbol.intern ("INITIAL-DOWNLOAD"),
  ITEM_LAYER_CHANGE_          = Symbol.intern ("ITEM-LAYER-CHANGE");
  public static final int
    ITEM_INSERT                = 0,
    ITEM_REMOVE                = 1,
    ITEM_MOVE                  = 2,
    ITEM_RESIZE                = 3,
    ITEM_ROTATE                = 4,
    ITEM_COLOR_PATTERN_CHANGE  = 5,
    ITEM_ICON_VARIABLES_CHANGE = 6,
    ITEM_CHANGE                = 7,
    WORKSPACE_RESIZED          = 8,
    INITIAL_DOWNLOAD           = 9,
    ITEM_LAYER_CHANGE          = 10;

  /**
   * Constructs a WorkspaceEvent with the specified (Workspace) source,
   * notification code, originating Item, and the extra event information.
   * @param source the workspace where the event originated
   * @code a symbol specifying the type of event
   * @item the item on the workspace that caused the event, if any
   * @extraInfo more information regarding the event
   */  
  public WorkspaceEvent (Object source,
			 Symbol code,
			 Item item,
			 Structure extraInfo) {
    super (source);
    this.item = item;
    info = extraInfo;
    id = mapCodeToID (code);
  }

  /**
   * Returns the notification code of the event
   */
  public Symbol getNotificationCode () {
    return getNotificationCode (id);
  }

  /**
   * @return The notication code Symbol corresponding
   * to the event ID.
   */
  public static Symbol getNotificationCode (int ID) {
    switch (ID) {
    case ITEM_INSERT:
      return ITEM_INSERT_;
    case ITEM_REMOVE:
      return ITEM_REMOVE_;
    case ITEM_MOVE:
      return ITEM_MOVE_;
    case ITEM_RESIZE:
      return ITEM_RESIZE_;
    case ITEM_ROTATE:
      return ITEM_ROTATE_;
    case ITEM_COLOR_PATTERN_CHANGE:
      return ITEM_COLOR_PATTERN_CHANGE_;
    case ITEM_ICON_VARIABLES_CHANGE:
      return ITEM_ICON_VARIABLES_CHANGE_;
    case ITEM_CHANGE:
      return ITEM_CHANGE_;
    case WORKSPACE_RESIZED:
      return WORKSPACE_RESIZED_;
    case INITIAL_DOWNLOAD:
      return INITIAL_DOWNLOAD_;
    case ITEM_LAYER_CHANGE:
      return ITEM_LAYER_CHANGE_;
    default:
      throw new RuntimeException ("Unknown ID (" + ID + ") in WorkspaceEvent");
    }
  }

  /**
   * @return The integer ID representing the type of event
   */
  public int getID () {
    return id;
  }

  /**
   * @returns the Item for this event, if
   *  this was an add or remove item event.
   */
  public Item getItem () {
    return item;
  }

  /**
   * Returns any extra information about the event
   */
  public Structure getInfo () {
    return info;
  }

  private int mapCodeToID (Symbol notfnCode) {
    if (notfnCode.equals (ITEM_INSERT_))
      return ITEM_INSERT;
    else if (notfnCode.equals (ITEM_REMOVE_))
      return ITEM_REMOVE;
    else if (notfnCode.equals (ITEM_MOVE_))
      return ITEM_MOVE;
    else if (notfnCode.equals (ITEM_RESIZE_))
      return ITEM_RESIZE;
    else if (notfnCode.equals (ITEM_ROTATE_))
      return ITEM_ROTATE;
    else if (notfnCode.equals (ITEM_COLOR_PATTERN_CHANGE_))
      return ITEM_COLOR_PATTERN_CHANGE;
    else if (notfnCode.equals (ITEM_ICON_VARIABLES_CHANGE_))
      return ITEM_ICON_VARIABLES_CHANGE;
    else if (notfnCode.equals (ITEM_CHANGE_))
      return ITEM_CHANGE;
    else if (notfnCode.equals (WORKSPACE_RESIZED_))
      return WORKSPACE_RESIZED;
    else if (notfnCode.equals (INITIAL_DOWNLOAD_))
      return INITIAL_DOWNLOAD;
    else if (notfnCode.equals (ITEM_LAYER_CHANGE_))
      return ITEM_LAYER_CHANGE;
      throw new RuntimeException ("Unexpected notification code " + notfnCode.getPrintValue ()
				  + " in WorkspaceEvent.");
  }

  private static final Symbol[] notificationCodes =
  {  ITEM_INSERT_, ITEM_REMOVE_, ITEM_MOVE_,
     ITEM_RESIZE_, ITEM_ROTATE_, ITEM_COLOR_PATTERN_CHANGE_,
     ITEM_ICON_VARIABLES_CHANGE_,ITEM_CHANGE_,
     WORKSPACE_RESIZED_, INITIAL_DOWNLOAD_, ITEM_LAYER_CHANGE_ };

  @Override
  public String toString () {
    return getClass().getName() + "[source=" + getSource () +
      ", notfn=" + notificationCodes[id] +
      ", item=" + item +
      ", info=" + info;
  }

}

