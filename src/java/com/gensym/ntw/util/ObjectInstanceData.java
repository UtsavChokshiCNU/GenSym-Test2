
/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ObjectInstanceData.java
 *
 */
package com.gensym.ntw.util;

import java.awt.Font;
import java.awt.Toolkit;

import com.gensym.classes.Block;
import com.gensym.classes.Entity;
import com.gensym.classes.ClassDefinition;
import com.gensym.classes.G2Definition;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Module;
import com.gensym.classes.Procedure;
import com.gensym.classes.SystemClassDefinitionImpl;
import com.gensym.classes.TextBox;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.ntw.util.uitools.IconKBTools;
import com.gensym.util.Symbol;

import javax.swing.Icon;
import javax.swing.ImageIcon;

public class ObjectInstanceData implements InstanceData, BasicObjectDataRenderer, BrowserSymbols {
  
  static protected Font defaultFont;
  static protected Font boldFont;
  static {
    try {
      defaultFont = new Font("SansSerif", Font.PLAIN, 12);
    } catch (Exception e) {}
    try {
      boldFont = new Font("SansSerif", Font.BOLD, 12);
    } catch (Exception e) {}
  }

  protected Symbol    dataType = UNKNOWN_;

  protected Icon icon = null;
  protected Item      item = null;
  protected String    string = "";
  protected String    tooltip = "";
  protected Font      font = defaultFont;

  protected Module    module;
  protected G2Definition g2Definition;

  private boolean WITH_COLOR_OVERRIDES = true;

  @Override
  public BasicObjectDataRenderer getRenderer()
  {
    return this;
  }
  
  public ObjectInstanceData(Symbol objectType) {
    //setFont(boldFont);
    setDataType(objectType);
    setTextRepresentation(determineStringValueForDataType(getDataType()));
    setToolTipRepresentation(determineToolTipForDataType(getDataType()));
   
    if (objectType.equals(OBJECT_HIERARCHY_))
      setIconRepresentation(BrowserIcons.moduleIcon);
  }

  public ObjectInstanceData(Module module) {
    //System.out.println("\nObjectInstanceData for module: "+module+"  name: "+module.getName());
    setModule(module);
    //System.out.println("after setModule: "+this.module);
    //setFont(boldFont);
    setDataType(MODULE_);
    setTextRepresentation(determineStringValueForDataType(getDataType()));
    setToolTipRepresentation(determineToolTipForDataType(getDataType()));
    setIconRepresentation(BrowserIcons.moduleIcon);
    //System.out.println("leaving ObjectInstanceData for module\n");
  }

  public ObjectInstanceData(KbWorkspace workspace) {
    setItem(workspace);
    setFont(defaultFont);
    setDataType(KB_WORKSPACE_);
    setTextRepresentation(determineStringValueForDataType(getDataType()));
    setToolTipRepresentation(determineToolTipForDataType(getDataType()));
    setIconRepresentation(BrowserIcons.kbWorkspaceIcon);
  }

  public ObjectInstanceData(G2Definition g2Definition) {
    setItem(g2Definition);
    /*
    if (g2Definition instanceof ClassDefinition)
      setFont(defaultFont);
    else
      setFont(boldFont);
    */
    setDataType(G2_DEFINITION_);
    setTextRepresentation(determineStringValueForDataType(getDataType()));
    setToolTipRepresentation(determineToolTipForDataType(getDataType()));
    setIconRepresentation(BrowserIcons.classDefinitionIcon);
  }

  public ObjectInstanceData(ClassDefinition classDefinition) {
    setItem((Item)classDefinition); // setItem without cast to Item is ambiguous
    setFont(defaultFont);
    setDataType(CLASS_DEFINITION_);
    setTextRepresentation(determineStringValueForDataType(getDataType()));
    setToolTipRepresentation(determineToolTipForDataType(getDataType()));
    setIconRepresentation(determineIconForItem(item));
  }

  public ObjectInstanceData(Item item) {
    setItem(item);
    setFont(defaultFont);
    setDataType(determineDataTypeForItem(item));
    setTextRepresentation(determineStringValueForDataType(getDataType()));
    setToolTipRepresentation(determineToolTipForDataType(getDataType()));
    setIconRepresentation(determineIconForItem(item));
  }

  private void setItem(G2Definition g2Def) {
    g2Definition = g2Def;
  }

  // BEGIN: InstanceData
  @Override
  public void setItem(Item item) {
    this.item = item;
  }

  @Override
  public Item getItem() {
    return item;
  }

  @Override
  public void setModule(Module module) {
    //System.out.println("in setModule: "+module+"  name: "+module.getName());
    this.module = module;
    //System.out.println("leaving setModule");
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
  public void setDataType(Symbol type) {
    dataType = type;
  }

  @Override
  public Symbol getDataType() {
    return dataType;
  }

  private Symbol determineDataTypeForItem(Item item) {
    Symbol type_;
    if (item instanceof Entity) {
      if (item instanceof ClassDefinition)
	type_ = CLASS_DEFINITION_;
      else if (item instanceof Procedure)
	type_ = PROCEDURE_;
      else type_ = ENTITY_;
    } else if (item instanceof TextBox) {
      type_ = TEXT_BOX_;
    } else type_ = ITEM_;
    return type_;
  }

  @Override
  public Icon determineIconForItem(Item item) {
    return IconKBTools.getIconForItem(item, WITH_COLOR_OVERRIDES, 16,16);
  }

  @Override
  public String determineStringValueForDataType(Symbol dataType) {
    //System.out.println("determineStringValueForDataType: "+item);
    String stringValue = dataType.toString();

    Symbol name_;
    if (dataType.equals(ITEM_)) {
      try {
	G2Definition g2Def = item.getDefinition();
	if (g2Def != null) {
	  name_ = (Symbol)((Block)item).getNames();
	  if (name_ != null)
	    stringValue = name_.toString();
	}
      } catch (G2AccessException gae) {
	Trace.exception(gae);
	//System.out.println(gae);
      }
    } 

    else if (dataType.equals(ENTITY_)) {
      try {
	name_ = (Symbol)((Entity)item).getNames();
	if (name_ != null)
	  stringValue = name_.toString();
	else
	  stringValue = NONE_.toString();
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
    }

    else if (dataType.equals(TEXT_BOX_)) {
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
    }

    else if (dataType.equals(PROCEDURE_)) {
      try {
	String text = ((Procedure)item).getText();
	if (text != null) {
	  int iPos = text.indexOf("(");
	  if (iPos > 0)
	    stringValue = text.substring(0, iPos);
	}
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
    }
  
    else if (dataType.equals(KB_WORKSPACE_)) {
      try {
	name_ = (Symbol)((KbWorkspace)item).getNames();
	if (name_ == null) name_ = DEFAULT_WORKSPACE_NAME_;
	stringValue = name_.toString();
      } catch (G2AccessException gae) {
	Trace.exception(gae);
	//System.out.println(gae);
      }
    }

    else if (dataType.equals(MODULE_)) {
      name_ = module.getName();
      stringValue = (name_ != null ? name_.toString() : UNSPECIFIED);
    }

    else if (dataType.equals(CLASS_DEFINITION_)) {
      try {
	stringValue = ((ClassDefinition)item).getClassName().toString();
      } catch (G2AccessException gae) {
	Trace.exception(gae);
	//System.out.println(gae);
      }
    }

    else if (dataType.equals(G2_DEFINITION_)) {
      try {
	stringValue = g2Definition.getClassName().toString();
      } catch (G2AccessException gae) {
	Trace.exception(gae);
	//System.out.println(gae);
      }
    }

    else {
      stringValue = dataType.toString();
    }

    return stringValue;
  }

  @Override
  public String determineToolTipForDataType(Symbol dataType) {
    String tooltip = "";
    Symbol name_;
    Symbol containingModule;

    if (dataType.equals(ITEM_)) { // entity, textbox, procedure
      tooltip = toString();
    }

    else if (dataType.equals(PROCEDURE_)) {
      try {
	tooltip = ((Procedure)item).getDefinition().getClassName().toString();
	String text = ((Procedure)item).getText();
	if (text != null) {
	  int iPos = text.indexOf(")");
	  if (iPos > 0)
	    text = text.substring(0, iPos+1);
	}
	tooltip += ": "+text;
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
    }

    else if (dataType.equals(CLASS_DEFINITION_)) {
      try {
	G2Definition g2Def = (G2Definition)item;
	if (g2Def instanceof SystemClassDefinitionImpl)
	  tooltip = g2Def.getClassName()+", a system-defined class";
	else {
	  containingModule = ((Block)g2Def).getContainingModule();
	  tooltip = g2Def.getClassName()+", defined in "+containingModule;
	}
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
    }

    else if (dataType.equals(ENTITY_)) {
      tooltip = toString();
      try {
	tooltip = tooltip+", a "+item.getDefinition().getClassName().toString();
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
    }

    else if (dataType.equals(TEXT_BOX_)) {
      try {
	String text = ((TextBox)item).getText();
	int len = text.length();
	if (len > 100)
	  text = text.substring(0, 99);
	tooltip = text;
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
    }

    else if (dataType.equals(MODULE_)) {
      name_ = module.getName();
      tooltip = (name_ != null ? name_.toString() : UNSPECIFIED);
      if (module.isTopLevel())  
	tooltip = tooltip+", the top-level module";
    }

    else if (dataType.equals(KB_WORKSPACE_)) {
      try {
	KbWorkspace wksp = (KbWorkspace)item;
	name_ = (Symbol)wksp.getNames();
	if (name_ == null) name_ = DEFAULT_WORKSPACE_NAME_;
	containingModule = wksp.getContainingModule();
	tooltip = containingModule+":: "+name_;
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
    }

    else if (dataType.equals(OBJECT_HIERARCHY_)) {
      tooltip = "The root of the object hierarchy";
    }

    return tooltip;
  }

  @Override
  public String toString() {
    return getTextRepresentation();
  }
  // END: InstanceData

  // BEGIN: BasicObjectDataRenderer
  @Override
  public void setTextRepresentation(String text) {
    string = text;
  }

  @Override
  public String getTextRepresentation() {
    return string.toLowerCase();
  }

  @Override
  public void setToolTipRepresentation(String tip) {
    tooltip = tip;
  }

  @Override
  public String getToolTipRepresentation() {
    return tooltip;
  }

  @Override
  public void setIconRepresentation(Icon icon) {
    this.icon = icon;
  }

  @Override
  public Icon getIconRepresentation() {
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
  // END: BasicObjectDataRenderer
}
