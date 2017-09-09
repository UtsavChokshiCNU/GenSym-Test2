/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2Palette.java
 *
 */


package com.gensym.ntw.util;

import com.gensym.ntw.TwAccess;
import com.gensym.message.Resource;
import com.gensym.ui.ObjectCreator;
import com.gensym.ui.RepresentationConstraints;
import com.gensym.ui.palette.Palette;
import com.gensym.ui.palette.PaletteEvent;

/** A G2Palette is a palette for creating G2 items.  A G2Palette can create items
 *  from a single G2. */
public class G2Palette extends Palette {

  private TwAccess context;
  private static final Resource i18n = Resource.getBundle("com/gensym/uiutil/Errors");
  private PaletteEvent event;
  private int constraintType;

  /** Creates a G2Palette with the specified connection and a default name. */
  public G2Palette(TwAccess connection){
    this(connection, null);
  }

  /** Creates a G2Palette with the specified connection and name. */
  public G2Palette(TwAccess connection, String name){
    super(name);
    if ((connection == null) || (!connection.isAlive()))
      throw new IllegalArgumentException(i18n.getString("illegalCxn"));
    this.context = connection;
    notifyPaletteCreated();
  }

  // This here is a little bit icky.  The problem is that G2Palette needs
  // to set the context BEFORE any listeners are notified of paletteCreated.
  @Override
  protected void notifyPaletteCreated(PaletteEvent event){
    this.event = event;
  }

  private void notifyPaletteCreated(){
    super.notifyPaletteCreated(event);
  }
  public void setButtonStyle(int constraintType) {
    this.constraintType = constraintType;
  }

  public int getButtonStyle() {
    return constraintType;
  }

  /** Returns the connection associated with this G2Palette. */
  public TwAccess getConnection(){
    return context;
  }

  /** Checks to ensure only G2ObjectCreators are added and that the Palette's and
   *  and ObjectCreator's connection are the same. */
  @Override
  public void add(ObjectCreator objectCreator){
    checkObjectCreator(objectCreator);
    super.add(objectCreator);
  }

  /** Checks to ensure only G2ObjectCreators are added and that the Palette's and
   *  and ObjectCreator's connection are the same. */
  @Override
  public void add(ObjectCreator objectCreator, RepresentationConstraints constraints){
    checkObjectCreator(objectCreator);
    super.add(objectCreator, constraints);
  }

  /** Checks to ensure only G2ObjectCreators are added and that the Palette's and
   *  and ObjectCreator's connection are the same. */
  @Override
  public void add(ObjectCreator objectCreator, String key){
    checkObjectCreator(objectCreator);
    super.add(objectCreator, key);
  }

  /** Checks to ensure only G2ObjectCreators are added and that the Palette's and
   *  and ObjectCreator's connection are the same. */
  @Override
  public void add(ObjectCreator objectCreator, String key, RepresentationConstraints constraints){
    checkObjectCreator(objectCreator);
    super.add(objectCreator, key, constraints);
  }

  private void checkObjectCreator(ObjectCreator objectCreator){
    if (!(objectCreator instanceof G2ObjectCreator))
      throw new IllegalArgumentException(i18n.getString("G2ObjectCreatorsOnly"));

    if (!(context.equals(((G2ObjectCreator)objectCreator).getConnection())))
      throw new IllegalArgumentException(i18n.getString("DifferentContexts"));
  }
}



