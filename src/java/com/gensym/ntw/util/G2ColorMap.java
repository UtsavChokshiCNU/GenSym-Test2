package com.gensym.ntw.util;


import java.util.*;
import java.awt.*;
import com.gensym.util.*;
import com.gensym.message.*;

/**
 * <b>SYNOPSIS:</b><p>
 */

public class G2ColorMap implements com.gensym.util.symbol.G2ColorSymbols {

  private static Resource i18n =
  Resource.getBundle("com.gensym.resources.TraceMessages");
  private static MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.util", G2ColorMap.class);

  private static Hashtable table = new Hashtable (89);

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

  public static final Color TRANSPARENT = new Color(255,255,255);
  
  public static Color get(Symbol g2_color) {
    return (Color) table.get(g2_color);
  }

  public static Color get(Object g2Color) {
    try {
      Symbol color = (Symbol)g2Color;
      return get(color);
    } catch (ClassCastException cce) {
      Trace.exception(cce);
      return Color.black;
    }
  }

  public static Color get(Structure struct, Symbol propname) throws
  NoSuchAttributeException {
    return get((Symbol)(struct.getAttributeValue(propname)));
  }

  public static Color get(Structure struct, Symbol propname,
			  Color defaultColor) {
    Color val = defaultColor;
    try {
      val = get(struct, propname);
    } catch (NoSuchAttributeException nsae) {
    Trace.send(5, traceKey, i18n, "g2cmInvalidColor", nsae, val);
    }

    if (val == null)
      return defaultColor;
    else
      return val;
  }
  
  static {
    table.put (TRANSPARENT_, TRANSPARENT);
    table.put (FOREGROUND_, Color.black);
    table.put (AQUAMARINE_, new Color (127 , 255 , 212));  		
    table.put (BLACK_, Color.black);
    table.put (BLUE_, Color.blue);
    //    table.put (BLUE_VIOLET_, new Color (159 , 95 , 159));
    table.put (BROWN_, new Color (165 , 42 , 42));
    table.put (CADET_BLUE_, new Color (95 , 158 , 160));
    table.put (CORAL_, new Color (255 , 127 , 80));
    //    table.put (CORNFLOWER_BLUE_, new Color (66 , 66 , 111));
    table.put (CYAN_, Color.cyan);
    table.put (DARK_GREY_, Color.gray);    
    table.put (DARK_GRAY_, Color.gray);
    //    table.put (DARK_GREEN_, new Color (47, 79, 47));
    //    table.put (DARK_OLIVE_GREEN_, new Color (79, 79, 47));	       
    //    table.put (DARK_ORCHID_, new Color (153, 50, 204));
    table.put (DARK_SLATE_BLUE_, new Color (72, 61, 139));	
    //    table.put (DARK_SLATE_GRAY_, new Color (47, 79 ,79 ));
    //    table.put (DARK_TURQUOISE_, new Color (112, 147, 219));
    table.put (DIM_GRAY_, new Color (105 ,105 ,105));
    table.put (DIM_GREY_, new Color (105 ,105 ,105));
    //    table.put (FIREBRICK_, new Color (142, 35, 35));
    table.put (FOREST_GREEN_, new Color (34, 139, 34));
    table.put (GOLD_, new Color (255, 215, 0));	       
    table.put (GOLDENROD_, new Color (218, 165, 32));
    table.put (GREY_, new Color (169, 169, 169));
    table.put (GRAY_, new Color (169, 169, 169));
    table.put (GREEN_, Color.green);
    table.put (GREEN_YELLOW_, new Color (173, 255, 47));
    table.put (INDIAN_RED_, new Color (205 ,92, 92));
    table.put (KHAKI_, new Color (240, 230, 140));
    table.put (LIGHT_BLUE_, new Color (173, 216, 230));		
    table.put (LIGHT_GRAY_, new Color (211, 211, 211));
    table.put (LIGHT_GREY_, new Color (211, 211, 211));
    table.put (EXTRA_LIGHT_GREY_, new Color(229, 229, 229));
    table.put (EXTRA_LIGHT_GRAY_, new Color(229, 229, 229));
    //   table.put (LIGHT_STEEL_BLUE_, new Color (143 ,143, 188));
    table.put (LIME_GREEN_, new Color (50, 205 ,50));
    table.put (MAGENTA_, Color.magenta);
    table.put (MAROON_, new Color (128, 0, 0));
    table.put (MEDIUM_AQUAMARINE_, new Color (102, 205, 170));		
    table.put (MEDIUM_BLUE_, new Color (0 ,0 ,205));
    //    table.put (MEDIUM_FOREST_GREEN_, new Color (107, 142, 35));
    table.put (MEDIUM_GOLDENROD_, new Color (234, 234, 173));
    table.put (MEDIUM_ORCHID_, new Color (186, 85, 211));
    //    table.put (MEDIUM_SEA_GREEN_, new Color (66, 111, 66));	       
    //    table.put (MEDIUM_SLATE_BLUE_, new Color (127, 0, 255));								
    //    table.put (MEDIUM_SPRING_GREEN_, new Color (127, 255, 0));		
    //    table.put (MEDIUM_TURQUOISE_, new Color (112, 219, 219));					
    //    table.put (MEDIUM_VIOLET_RED_, new Color (219, 112, 147));				
    //    table.put (MIDNIGHT_BLUE_, new Color (47, 47, 79));
    //    table.put (NAVY_BLUE_, new Color (35, 35, 142 navy));
    table.put (ORANGE_, new Color (255, 165, 0));
    table.put (PALE_GREEN_, new Color (152, 251, 152));
    table.put (PINK_, new Color (255, 192, 203));	       
    table.put (PLUM_, new Color (221, 160, 221));
    table.put (PURPLE_, new Color (128, 0, 128));
    table.put (RED_, Color.red);
    table.put (SALMON_, new Color (250, 128, 114));				
    //    table.put (SEA_GREEN_, new Color (35, 142, 107));		
    table.put (SIENNA_, new Color (160, 82, 45));
    table.put (SKY_BLUE_, new Color (135, 206, 235));
    table.put (SLATE_BLUE_, new Color (106, 90, 205));
    //    table.put (SPRING_GREEN_, new Color (0, 255, 127));
    //    table.put (STEEL_BLUE_, new Color (35, 107, 142));
    table.put (TAN_, new Color (210, 180, 140));	       
    table.put (THISTLE_, new Color (216, 191, 216));
    table.put (TURQUOISE_, new Color (64, 224, 208));
    table.put (VIOLET_, new Color (238 ,130, 238));
    table.put (VIOLET_RED_, new Color (204, 50, 153));
    table.put (WHEAT_, new Color (245, 222, 179));
    table.put (WHITE_, Color.white);
    table.put (YELLOW_, Color.yellow);
    //   table.put (YELLOW_GREEN_, new Color (153, 204, 50));

    table.put (SMOKE_, new Color(245, 245, 245));
    table.put (FLORAL_WHITE_, new Color(255, 250, 240));
    table.put (LINEN_, new Color(250, 240, 230));
    table.put (ANTIQUE_WHITE_, new Color(250, 235, 215));
    table.put (IVORY_, new Color(255, 255, 240));
    table.put (AZURE_, new Color(240, 255, 255));
    table.put (LAVENDER_, new Color(230, 230, 250));
    table.put (LIGHT_STEEL_BLUE_, new Color(176, 196, 222));
    table.put (POWDER_BLUE_, new Color(176, 224, 230));
    table.put (PALE_TURQUOISE_, new Color(175, 238, 238));
    table.put (LIGHT_CYAN_, new Color(224, 255, 255));
    table.put (PALE_GOLDENROD_, new Color(238, 232, 170));
    table.put (LIGHT_GOLDENROD_YELLOW_, new Color(250, 250, 210));
    table.put (LIGHT_YELLOW_, new Color(255, 255, 224));
    table.put (LIGHT_GOLDENROD_, new Color(238, 221, 130));
    table.put (BEIGE_, new Color(245, 245, 220));
    table.put (LIGHT_PINK_, new Color(255, 182, 193));
    
 }

  public static Enumeration getColors () {
    return table.keys ();
  }

}
