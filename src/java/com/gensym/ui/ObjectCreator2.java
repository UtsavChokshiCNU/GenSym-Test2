package com.gensym.ui;

import java.awt.Image;
import java.awt.event.ActionListener;
import javax.swing.Icon;

/** 
 *  An ObjectCreator2 is an improvement to the ObjectCreator interface
 *  that lets implementors really use Icons, the Swing sense, to draw 
 *  the pictures on the buttons of a palette.
 *  @see com.gensym.ui.ObjectCreator
 *  @see com.gensym.ui.palette.Palette
 */
public interface ObjectCreator2 extends ObjectCreator
{
  public Icon getIcon2(String key, int size);
}
