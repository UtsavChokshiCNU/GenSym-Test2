
/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 InspectNodeInstanceData.java
 *
 */
package com.gensym.uitools.inspect.trees;

import java.awt.Font;
import java.awt.Toolkit;

import com.gensym.classes.Item;
import com.gensym.classes.TextBox;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.ntw.util.uitools.IconKBTools;
import com.gensym.util.Symbol;
import com.gensym.ntw.util.InstanceData;
import com.gensym.ntw.util.BasicObjectDataRenderer;
import com.gensym.ntw.util.BrowserSymbols;
import com.gensym.classes.Module;
import com.gensym.classes.ModuleInformation;
import com.gensym.classes.SystemTable;
import com.gensym.classes.G2Definition;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Procedure;
import com.gensym.classes.MethodDeclaration;
import com.gensym.ntw.util.BrowserIcons;

import javax.swing.Icon;
import javax.swing.ImageIcon;
import com.gensym.util.ItemListener;
import com.gensym.util.ItemEvent;
import com.gensym.util.symbol.SystemAttributeSymbols;

public class InspectNodeInstanceData implements InstanceData,
  BasicObjectDataRenderer, BrowserSymbols
{
  private static final String NO_NAME = "NO-NAME";
  private static Icon gensymLogo = null;
  static final String KNOWLEDGE_BASE = "Knowledge Base";
  
  protected Symbol dataType = null;
  protected Module module;
  protected G2Definition g2Definition;
  protected static Font defaultFont, boldFont;
  static {
    try {
      defaultFont = new Font("SansSerif", Font.PLAIN, 11);
    } catch (Exception e) {}
    try {
      boldFont = new Font("SansSerif", Font.BOLD, 11);
    } catch (Exception e) {}
  }
  protected Icon icon = null;
  protected Item item = null;
  protected String string = null;
  protected String tooltip = null;
  protected Font font = defaultFont;
  private Object object;  
  private static boolean WITH_COLOR_OVERRIDES = true;
  private ItemListener itemListener;


  @Override
  public void setModule(Module module) {
    this.module = module;
  }

  @Override
  public Module getModule() {
    return module;
  }

  @Override
  public G2Definition getG2Definition() {
    return g2Definition;
  }
  
  @Override
  public BasicObjectDataRenderer getRenderer()
  {
    return this;
  }

  public InspectNodeInstanceData(Object object) {
    if (object instanceof Item) {
      itemListener = new ItemListener() {
	@Override
	public void itemModified(ItemEvent ie) {
	}
	@Override
	public void itemDeleted(ItemEvent ie) {
	}
	@Override
	public void receivedInitialValues(ItemEvent ie) {
	}
      };
      setItem((Item)object);
    } else {
      this.object = object;
      String label = object.toString();
      setTextRepresentation(label);
      setToolTipRepresentation(label);
    }
  }
  
  @Override
  public void setItem(Item item) {
    if (this.item !=  null) {
      try {
	this.item.removeItemListener(itemListener, getNeededAttributes(this.item));
      } catch (G2AccessException g2ae) {
	Trace.exception(g2ae);
      }
    }
    this.item = item;
    if (item != null) {
      try {
	item.addItemListener(itemListener, getNeededAttributes(item));
      } catch (G2AccessException g2ae) {
	Trace.exception(g2ae);
      }
    }
  }

  private static Symbol[] getNeededAttributes(Item itm) {
    if (itm instanceof ModuleInformation)
      return new Symbol[] {SystemAttributeSymbols.TOP_LEVEL_MODULE_,
			     SystemAttributeSymbols.ITEM_NOTES_,
			     SystemAttributeSymbols.ITEM_STATUS_};
    else {
      Symbol[] attrs1 = com.gensym.ntw.util.AttributeHelper.getNeededAttributes(itm);
      int count = attrs1.length;
      Symbol[] attrs = new Symbol[count+2];
      System.arraycopy(attrs1, 0, attrs, 0, count);
      attrs[count] = SystemAttributeSymbols.ITEM_NOTES_;
      attrs[count+1]= SystemAttributeSymbols.ITEM_STATUS_;
      return attrs;
    }
  }
  
  @Override
  public Item getItem() {
    return item;
  }

  @Override
  public void setDataType(Symbol type) {
    dataType = type;
  }

  @Override
  public Symbol getDataType() {
    if (dataType == null && item != null)
      setDataType(determineDataTypeForItem(item));
    return dataType;
  }

  private Symbol determineDataTypeForItem(Item item) {
    Symbol type;
    if (item instanceof TextBox) 
      type = TEXT_BOX_;
    else if (item instanceof KbWorkspace)
      type = KB_WORKSPACE_;
    else if (item instanceof ModuleInformation)
      type = MODULE_;
    else if (item instanceof Procedure && !(item instanceof MethodDeclaration))
      type = PROCEDURE_;
    else if (item instanceof G2Definition)
      type = G2_DEFINITION_;
    else
      type = ITEM_;
    return type;
  }

  /* boolean proprietary = false;
     try {
     proprietary = item.isProprietaryThroughContainment();
     } catch (G2AccessException g2ae) {
     Trace.exception(g2ae);
     }
     if (proprietary)
     return IconKBTools.getIconForItem(item, WITH_COLOR_OVERRIDES, 10,10);
     else*/  
  @Override
  public Icon determineIconForItem(Item item) {
    return makeIcon(item);
  }

  static Icon makeIcon(Item item) {
    if (item instanceof KbWorkspace)
      return BrowserIcons.kbWorkspaceIcon;
    else if (item instanceof ModuleInformation)
      return BrowserIcons.moduleIcon;
    else if (item instanceof SystemTable)
      return BrowserIcons.systemTableIcon;
    else
      return IconKBTools.getIconForItem(item, WITH_COLOR_OVERRIDES, 16,16);
  }
  
  @Override
  public String determineStringValueForDataType(Symbol dataType) {
    String stringValue = NO_NAME;
    if (dataType.equals(TEXT_BOX_)) {
      try {
	G2Definition g2Def = item.getDefinition();
	if (g2Def != null) {
	  stringValue = g2Def.getClassName().toString()+": ";
	  String text = ((TextBox)item).getText();
	  if (text != null) {
	    int endIndex = (text.length() >= 25 ? 24 : text.length());
	    stringValue = stringValue + text.substring(0, endIndex) + "...";
	  }
	}
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
    } else if (item != null) {
      try {
	if (item instanceof ModuleInformation) {
	  Symbol moduleName = ((ModuleInformation)item).getTopLevelModule();//NOTE attr not cached!
	  if (moduleName != null)
	    stringValue = moduleName.toString();
	  else
	    stringValue = "Unnamed module";
	} else
	  stringValue = com.gensym.ntw.util.AttributeHelper.getTableHeader(item);
	stringValue = stringValue.toLowerCase();
      } catch (G2AccessException g2ae) {
	Trace.exception(g2ae);
      }
    }
    return stringValue;
  }
  
  @Override
  public String determineToolTipForDataType(Symbol dataType) {
    return string;
  }
  
  @Override
  public String toString() {
    return getTextRepresentation();
  }

  @Override
  public void setTextRepresentation(String text) {
    string = text;
  }

  @Override
  public String getTextRepresentation() {
    if (string == null)
      setTextRepresentation(determineStringValueForDataType(getDataType()));
    return string;
  }

  @Override
  public void setToolTipRepresentation(String tip) {
    tooltip = tip;
  }

  @Override
  public String getToolTipRepresentation() {
    if (tooltip == null)
      setToolTipRepresentation(determineToolTipForDataType(getDataType()));
    return tooltip;
  }

  @Override
  public void setIconRepresentation(Icon icon) {
    this.icon = icon;
  }

  @Override
  public Icon getIconRepresentation() {
    if (icon == null && item != null)
      setIconRepresentation(determineIconForItem(item));
    else if (KNOWLEDGE_BASE == object) {
      if (gensymLogo == null)
	gensymLogo = new ImageIcon(Toolkit.getDefaultToolkit().getImage
				   (this.getClass().getResource("gensym_logo.gif")));
      setIconRepresentation(gensymLogo);
    }
    return icon;
  }

  @Override
  public void setFont(Font font) {
    this.font = font;
  }

  @Override
  public Font getFont() {
    return font;
  }

}
