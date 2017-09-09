/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 IconKBTools.java
 *
 */
package com.gensym.ntw.util.uitools;

import java.awt.Image;
import java.util.Enumeration;

import com.gensym.classes.Entity;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Module;
import com.gensym.classes.SystemTable;
import com.gensym.classes.Connection;
import com.gensym.classes.ImplAccess;
import com.gensym.classes.ImageDefinition;
import com.gensym.classes.TypeInBox;
import com.gensym.classes.FunctionDefinition;
import com.gensym.classes.GenericFormula;
import com.gensym.classes.Rule;
import com.gensym.classes.NameBox;
import com.gensym.classes.ProcedureInvocation;
import com.gensym.classes.Chart;
import com.gensym.classes.TrendChart;
import com.gensym.classes.FreeformTable;
import com.gensym.classes.Message;
import com.gensym.classes.LogbookPage;
import com.gensym.classes.BorderlessFreeText;
import com.gensym.classes.FreeText;
import com.gensym.classes.ActionButton;
import com.gensym.classes.MessageBoard;
import com.gensym.classes.TableItem;
import com.gensym.draw.ColorTable;
import com.gensym.icons.IconDescription;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2Access;
import com.gensym.message.Trace;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.wksp.WorkspaceColorTable;
import com.gensym.ntw.util.CrossSectionPattern;
import java.awt.Color;
import com.gensym.ntw.util.WindowUtil;
import java.awt.Graphics;
import javax.swing.ImageIcon;
import com.gensym.ntw.util.G2ColorMap;
import java.awt.Toolkit;

public class IconKBTools {
  
  private static final Symbol IMAGE_DEFINITION_ = Symbol.intern ("IMAGE-DEFINITION");
  private static final Class thisClass = com.gensym.ntw.util.uitools.IconKBTools.class;
  private static final ImageIcon
  KB_WORKSPACE = new ImageIcon(Toolkit.getDefaultToolkit().getImage(thisClass.getResource("kbworkspace.gif"))),
    MODULE = new ImageIcon(Toolkit.getDefaultToolkit().getImage(thisClass.getResource("module.gif"))),
    SYSTEM_TABLE = new ImageIcon(Toolkit.getDefaultToolkit().getImage(thisClass.getResource("system-table.gif"))),
    FUNCTION_DEFINITION = new ImageIcon(Toolkit.getDefaultToolkit().getImage(thisClass.getResource("function-definition.gif"))),
    GENERIC_FORMULA = new ImageIcon(Toolkit.getDefaultToolkit().getImage(thisClass.getResource("generic-formula.gif"))),
    RULE =  new ImageIcon(Toolkit.getDefaultToolkit().getImage(thisClass.getResource("free-text.gif"))),
    NAME_BOX = new ImageIcon(Toolkit.getDefaultToolkit().getImage(thisClass.getResource("name-box.gif"))),
    CHART = new ImageIcon(Toolkit.getDefaultToolkit().getImage(thisClass.getResource("chart.gif"))),
    TREND_CHART = new ImageIcon(Toolkit.getDefaultToolkit().getImage(thisClass.getResource("trend-chart.gif"))),
    FREEFORM_TABLE = new ImageIcon(Toolkit.getDefaultToolkit().getImage(thisClass.getResource("freeform-table.gif"))),
    FREE_TEXT = new ImageIcon(Toolkit.getDefaultToolkit().getImage(thisClass.getResource("free-text.gif"))),
    LOGBOOK = new ImageIcon(Toolkit.getDefaultToolkit().getImage(thisClass.getResource("logbook.gif"))),
    BORDERLESS_FREE_TEXT = new ImageIcon(Toolkit.getDefaultToolkit().getImage(thisClass.getResource("borderless-free-text.gif"))),
    TYPE_IN_BOX = new ImageIcon(Toolkit.getDefaultToolkit().getImage(thisClass.getResource("type-in-box.gif"))),
    ACTION_BUTTON = new ImageIcon(Toolkit.getDefaultToolkit().getImage(thisClass.getResource("action-button.gif"))),
    TABLE_ITEM_WITH_HEADER = new ImageIcon(Toolkit.getDefaultToolkit().getImage(thisClass.getResource("table-item-with-header.gif")));
	
  public static ImageIcon getIconForItem(Item item, boolean withColorOverrides) {
    return getIconForItem(item, withColorOverrides, 24, 24);
  }
  
  public static ImageIcon getIconForItem(Item item,
					 boolean withColorOverrides,
					 int width, int height)
  {
    ImageIcon icon = null;

    if (item == null) return icon;
	
    // special case for: kb-workspace, module, system-table
    if (item instanceof KbWorkspace)
      icon = KB_WORKSPACE;
    else if (item instanceof Module)
      icon = MODULE;
    else if (item instanceof SystemTable)
      icon = SYSTEM_TABLE;
    else if (item instanceof Connection) 
      return new ImageIcon(createImage((Connection)item));
    else if (item instanceof FunctionDefinition)
      return FUNCTION_DEFINITION;
    else if (item instanceof GenericFormula)
      return GENERIC_FORMULA;
    else if (item instanceof Rule)
      return RULE;
    else if (item instanceof NameBox)
      return NAME_BOX;
    else if (item instanceof ProcedureInvocation)
      return FREE_TEXT;
    else if (item instanceof Chart)
      return CHART;
    else if (item instanceof TrendChart)
      return TREND_CHART;
    else if (item instanceof FreeformTable)
      return FREEFORM_TABLE;
    else if (item instanceof Message)
      return FREE_TEXT;
    else if (item instanceof LogbookPage)
      return LOGBOOK;
    else if (item instanceof BorderlessFreeText)
      return BORDERLESS_FREE_TEXT;
    else if (item instanceof FreeText)
      return FREE_TEXT;
    else if (item instanceof TypeInBox)
      return TYPE_IN_BOX;
    else if (item instanceof ActionButton)
      return ACTION_BUTTON;
    else if (item instanceof MessageBoard)
      return null;//fix this
    else if (item instanceof TableItem)
      return TABLE_ITEM_WITH_HEADER;
    else if (item instanceof Entity) {
      try {
	Image smallImage;
	Structure iconDescription = ((Entity)item).getIconDescriptionForClass();
	if (withColorOverrides) {
	  Structure colorOverrides = ((Entity)item).getItemColorPattern();
	  if (colorOverrides != null)
	    colorOverrides = transformColorValues(colorOverrides);
	  smallImage = createImage(iconDescription,
				   ((ImplAccess)item).getContext(),
				   width, height, colorOverrides);
	} else {
	  smallImage = createImage(iconDescription,
				   ((ImplAccess)item).getContext(),
				   width, height, null);
	}
	if (smallImage != null) 
	  icon = new ImageIcon(smallImage);
      } catch (G2AccessException gae) {
	Trace.exception(gae);
	System.out.println(gae);
      }
    } 
    return icon;
  }

  private static Image createImage(Connection connection)
  {
    Image image = null;
    try {
      CrossSectionPattern csp
	= new CrossSectionPattern(connection.getCrossSectionPatternForClass());
      Structure colorMap = csp.getColorMap();
      Object[] regions = csp.getRegions();
      int[] widths = csp.getWidths();
      int iconWidth = 50;
      int iconHeight = 0;      
      for (int i=0;i<widths.length;i++) {
	iconHeight+=widths[i];
      }
      image = WindowUtil.createImage(iconWidth, iconHeight);
      Graphics g = image.getGraphics();
      int currentY=0;
      for (int i=0;i<widths.length;i++) {
	int height = widths[i];
	Object region = regions[i];
	Symbol colorName = (Symbol)colorMap.getAttributeValue((Symbol)region,
							      region);
	Color color = G2ColorMap.get(colorName);
	g.setColor(color);
	g.fillRect(0,currentY,iconWidth,height);
	currentY+=height;
      }
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
    return image;
  }
  
  private static Image createImage(Structure iconDescription,
				   G2Access cxn,
				   int width,
				   int height,
				   Structure colorOverrides)
       throws G2AccessException
  {
    IconDescription iconDescrip = new IconDescription(iconDescription);
    Symbol imageName = iconDescrip.getBackgroundImageName();
    if (imageName != null) {
      ImageDefinition imageDef =
	(ImageDefinition)cxn.getUniqueNamedItem (IMAGE_DEFINITION_, imageName);
      if (imageDef.getWidthOfImage () != null) {
	Image image = imageDef.getImage();
	iconDescrip.setBackgroundImage(image,
				       imageDef.getWidthOfImage().intValue(),
				       imageDef.getHeightOfImage().intValue());
      }
    }            
    return iconDescrip.createImage(width, height, 0, null, false, colorOverrides, null);
  }

  private static ColorTable colorTable = WorkspaceColorTable.createDefaultColorTable();
  private static Structure transformColorValues(Structure regionOverrides)
  {
    if (regionOverrides == null)
      return regionOverrides;
    else {
      regionOverrides = (Structure) regionOverrides.clone();
      Symbol regionName; Object color;
      for (Enumeration regionNames
	     = regionOverrides.getAttributeNames(); regionNames.hasMoreElements();) {
	regionName = (Symbol) regionNames.nextElement();
	color = regionOverrides.getAttributeValue(regionName, null);
	if (color instanceof Symbol)
	  regionOverrides.setAttributeValue(regionName,
					    colorTable.lookup(color));
      }
    }
    return regionOverrides;
  }
}
