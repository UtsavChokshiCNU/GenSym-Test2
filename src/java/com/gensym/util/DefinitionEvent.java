/*
 * @(#)DefinitionEvent.java 1.0 97/10/22
 *
 * Copyright (C) 1986-2017 Gensym Corporation. All Rights reserved.
 *
 */

package com.gensym.util;

import com.gensym.classes.Definition;
import com.gensym.message.Resource;

/**
 * An event that encapsulates a change made to a Classefinition in G2.
 * It is spawned out of an ItemEvent from a Definition object.
 * 
 * @version 1.0 10/22/97
 * @author vkp
 */
public class DefinitionEvent extends java.util.EventObject implements java.io.Serializable {

  private Definition originatingDefn;
  private int             id;
  private Symbol          changedAttr;
  private Object          newValue;
  private Object          oldValue;

  private static final Resource i18nError =
  Resource.getBundle("com.gensym.resources.Errors");

  /**
   * The class-name change event type.
   */
  public static final int CLASS_NAME_CHANGED = 0;

  /**
   * The direct-superior-classes change event type
   */
  public static final int DIRECT_SUPERIOR_CLASSES_CHANGED = 1;

  /**
   * The class-specific-attributes change event type.
   */
  public static final int CLASS_SPECIFIC_ATTRIBUTES_CHANGED = 3;

  /**
   * The class-inheritance-path change event type.
   */
  public static final int CLASS_INHERITANCE_PATH_CHANGED = 2;

  /**
   * The static-attributes change event-type
   */
  public static final int STATIC_ATTRIBUTE_CHANGED = 4;
  
  /**
   * The class deletion event type.
   */
  public static final int DELETED = 5;

  /**
   * Constructs a DefinitionEvent object with the specified source.
   * @param source the definition where the event is being dispatched from
   * @param dentn the denotation of the changed value, if any
   * @param newValue the new value in the slot
   */
  public DefinitionEvent (Definition source,
			  int eventType,
			  Definition originatingDefn,
			  Symbol attrName,
			  Object newValue,
			  Object oldValue) {
    super (source);
    this.originatingDefn = originatingDefn;
    this.id              = eventType;
    this.changedAttr     = attrName;
    this.newValue        = newValue;
    this.oldValue        = oldValue;
  }

  /**
   * Get the definition that was actually modified.
   * @return the original definition that started this change chain
   * @deprecated under consideration whether to add to API
   */

  public Definition getDefinitionOriginatingChange () {
    return originatingDefn;
  }

  /**
   * Get the denotation that represents the changed slot, if any
   */
  public Symbol getAttributeName () {
    return changedAttr;
  }

  /**
   * Get the new value of the slot, if any
   */
  public Object getNewValue () {
    return newValue;
  }

  /**
   * @undocumented
   */
  public Object getOldValue() {
    return oldValue;
  }

  /**
   * Get the type of the class change event
   */
  public int getEventType () {
    return id;
  }

  private String mapIDToCode (int ID) {
    switch (ID) {
    case CLASS_NAME_CHANGED:
      return "CLASS-NAME";
    case DIRECT_SUPERIOR_CLASSES_CHANGED:
      return "DIRECT-SUPERIOR-CLASSES";
    case CLASS_SPECIFIC_ATTRIBUTES_CHANGED:
      return "CLASS-SPECIFIC-ATTRIBUTES";
    case CLASS_INHERITANCE_PATH_CHANGED:
      return "CLASS-INHERITANCE-PATH";
    case STATIC_ATTRIBUTE_CHANGED:
      return "STATIC-ATTRIBUTE";
    case DELETED:
      return "DELETED";
    default:
      throw new IllegalArgumentException(i18nError.format("InvalidEventID", ID, this));
    }
  }

  @Override
  public String toString () {
    return super.toString() + " " + mapIDToCode (id) +
      "{orig defn = " + originatingDefn +
      (changedAttr != null ? ", Attr = " + changedAttr : "") +
      ", Value  = " + newValue + "}";
  }
      
}

