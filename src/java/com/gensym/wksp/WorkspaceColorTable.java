package com.gensym.wksp;

import java.awt.Color;
import com.gensym.util.Symbol;
import com.gensym.ntw.util.G2ColorMap;
import com.gensym.draw.ColorTable;

/**
 *
 */

public class WorkspaceColorTable extends ColorTable {
  
  static final long serialVersionUID = 366619609659853485L;
  /**
   *@param g2_color May be a String version of one of the following: { <p>
   <b> aquamarine black blue brown cadet-blue coral cyan 
   dark-gray dark-slate-blue dim-gray forest-green gold
   goldenrod gray green green-yellow indian-red khaki  
   light-blue light-gray lime-green magenta maroon
   medium-aquamarine medium-blue medium-goldenrod medium-orchid  
   orange pale-green pink plum purple red salmon sienna
   sky-blue  slate-blue tan thistle turquoise violet violet-red 
   wheat white yellow  </b> }<p>
   *@return the corresponding java Color.
   */

  private static Symbol TRANSPARENT_ = Symbol.intern ("TRANSPARENT");

  @Override
  public Color lookup (Object key) {
    Color c = (Color) get(key);
    if (c != null)
      return c;
    if (key instanceof Symbol)
      return (Color) G2ColorMap.get ((Symbol)key);
    else
      return null;
  }

  public static ColorTable createDefaultColorTable() {
    ColorTable table = new WorkspaceColorTable();
    return table;
  }

}
