/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      SystemClassDefinitionImpl.java
 *
 *
 *        Author: vkp
 *       Version: 1.0
 *          Date: Tue Oct 21 19:26:33 EDT 1997
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.jgi.*;
import com.gensym.message.Resource;
import com.gensym.util.UnexpectedException;

public class SystemClassDefinitionImpl extends java.lang.Object
implements G2Definition, com.gensym.util.symbol.DefinitionSymbols,
java.io.Serializable {

  static final long serialVersionUID = 2L;
  public static final Symbol SYSTEM_CLASS_DEFINITION_ = Symbol.intern ("SYSTEM-CLASS-DEFINITION");
  static final Symbol g2ClassName = SYSTEM_CLASS_DEFINITION_;
  private static final Resource i18n =
  Resource.getBundle("com.gensym.classes.Messages");

  private static final int UNITIALIZED_CLASS_ID = 0;

  private Structure attributes;
  private Symbol className;
  private int classID = UNITIALIZED_CLASS_ID;

  public SystemClassDefinitionImpl (Symbol g2ClassName, Structure classAttributes) {
    className = g2ClassName;
    attributes = classAttributes;
    fixupClassInheritancePathAttributes ();
  }


  @Override
  public com.gensym.util.Symbol getClassName() {
    return className;
  }

  /**
   * @undocumented
   */
  public int getClassID() {
    return classID;
  }

  /**
   * @undocumented
   */
  public void setClassID(int classID) {
    if (this.classID != UNITIALIZED_CLASS_ID) // has already been set
      throw new UnexpectedException(null, i18n.format("scdAttemptToResetClassID",
						      this));
    this.classID = classID;
  }

  @Override
  public com.gensym.util.Sequence getDirectSuperiorClasses() {
    return (com.gensym.util.Sequence) attributes.getAttributeValue (DIRECT_SUPERIOR_CLASSES_, null);
  }

  @Override
  public com.gensym.util.Sequence getClassSpecificAttributes() {
    return (com.gensym.util.Sequence) attributes.getAttributeValue (CLASS_SPECIFIC_ATTRIBUTES_, null);
  }

  public com.gensym.util.Sequence getInstanceConfiguration () {
    return null;
  }

  @Override
  public boolean getInstantiate() {
    Boolean retnvalue = (Boolean)attributes.getAttributeValue (INSTANTIATE_, null);
    return retnvalue.booleanValue ();
  }

  @Override
  public boolean getIncludeInMenus() {
    Boolean retnvalue = (Boolean) attributes.getAttributeValue (INCLUDE_IN_MENUS_, null);
    return retnvalue.booleanValue ();
  }

  @Override
  public com.gensym.util.Sequence getClassInheritancePath () {
    return (com.gensym.util.Sequence) attributes.getAttributeValue (CLASS_INHERITANCE_PATH_, null);
  }

  @Override
  public com.gensym.util.Sequence getSystemClassInheritancePath () {
    return (com.gensym.util.Sequence) attributes.getAttributeValue (SYSTEM_CLASS_INHERITANCE_PATH_, null);
  }

  @Override
  public com.gensym.util.Sequence getInheritedAttributes () {
    return new Sequence (); // Fill this in...
  }

  @Override
  public com.gensym.util.Sequence getInitializableSystemAttributes () {
    return new Sequence (); // Fill this in...
  }

  @Override
  public com.gensym.util.Sequence getAttributeInitializations() {
    return new Sequence (); // Fill this in...
  }

  @Override
  public com.gensym.util.Structure getIconDescription() {
    return (com.gensym.util.Structure) attributes.getAttributeValue (ICON_DESCRIPTION_, null);
  }

  public com.gensym.util.Structure getCrossSectionPattern() {
    return (com.gensym.util.Structure) attributes.getAttributeValue (CROSS_SECTION_PATTERN_, null);
  }

  public java.lang.Object getStubLength() {
    return attributes.getAttributeValue (STUB_LENGTH_, null);
  }

  public com.gensym.util.Symbol getJunctionBlock() {
    return (com.gensym.util.Symbol) attributes.getAttributeValue (JUNCTION_BLOCK_FOR_CLASS_, null);
  }

  public com.gensym.util.Structure getDefaultMessageProperties() {
    return (com.gensym.util.Structure) attributes.getAttributeValue (DEFAULT_MESSAGE_PROPERTIES_, null);
  }

  @Override
  public java.lang.Object getClassAttributeValue (com.gensym.util.Symbol attrName) {
    java.lang.Object returnValue =
      attributes.getAttributeValue (attrName, null);
    //System.out.println("Attr: " + attrName + "; Val: " + returnValue);
    return returnValue;
  }


  private void fixupClassInheritancePathAttributes () {
    Sequence clsInhPathFull = (Sequence) attributes.getAttributeValue (CLASS_INHERITANCE_PATH_, null);
    attributes.setAttributeValue (SYSTEM_CLASS_INHERITANCE_PATH_, clsInhPathFull);
    Sequence clsInhPathUser = new Sequence ();
    for (int i=0; i<clsInhPathFull.size (); i++) {
      java.lang.Object nextClassName = clsInhPathFull.elementAt (i);
      clsInhPathUser.addElement (nextClassName);
      if (com.gensym.util.symbol.G2ClassSymbols.ITEM_.equals (nextClassName))
	break;
    }
    attributes.setAttributeValue (CLASS_INHERITANCE_PATH_, clsInhPathUser);
  }

  @Override
  public String toString() {
    return super.toString() + "(" + className + ";id=" + classID + ")";
  }

}
