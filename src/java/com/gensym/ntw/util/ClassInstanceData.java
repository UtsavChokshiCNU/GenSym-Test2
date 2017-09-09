/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ClassInstanceData.java
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
import com.gensym.util.Symbol;

import javax.swing.ImageIcon;

public class ClassInstanceData extends ObjectInstanceData {

  // constructor used for the roots & base-classes for G2 hierarchies
  public ClassInstanceData(Symbol hierarchyType) {
    super(hierarchyType);
    setDataType(hierarchyType);
    setTextRepresentation(determineStringValueForDataType(getDataType()));
    setToolTipRepresentation(determineToolTipForDataType(getDataType()));
   
    if (hierarchyType.equals(MODULE_HIERARCHY_))
      setIconRepresentation(BrowserIcons.moduleIcon);
   
    else if (hierarchyType.equals(WORKSPACE_HIERARCHY_))
      setIconRepresentation(BrowserIcons.kbWorkspaceIcon);
   
    else if (hierarchyType.equals(CLASS_HIERARCHY_))
      setIconRepresentation(BrowserIcons.classDefinitionIcon);
    
    else if (hierarchyType.equals(KNOWLEDGE_BASE_))
      setIconRepresentation(BrowserIcons.kbWorkspaceIcon);
    
    else if (hierarchyType.equals(UNREQUIRED_MODULES_))
      setIconRepresentation(BrowserIcons.moduleIcon);
  }

  public ClassInstanceData(Module module) {
    super(module);  
  }

  public ClassInstanceData(KbWorkspace workspace) {
    super(workspace);
  }

  public ClassInstanceData(G2Definition g2Definition) {
    super(g2Definition);
  }

  public ClassInstanceData(ClassDefinition classDefinition) {
    super(classDefinition);
  }

  public ClassInstanceData(Item item) {
    super(item);
  }

  @Override
  public String determineToolTipForDataType(Symbol dataType) {
    String tooltip = "";
    Symbol name_;
    Symbol containingModule;

    if (dataType.equals(ITEM_)) {
      tooltip = item.toString();
    }

    else if (dataType.equals(MODULE_)) {
      name_ = module.getName();
      tooltip = (name_ != null ? name_.toString() : UNSPECIFIED);
      //System.out.println("mod: "+mod+" modName: "+mod.getName()+" isTopLevel? "+mod.isTopLevel());
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

    else if (dataType.equals(MODULE_HIERARCHY_)) {
      //if (baseClass.equals(ROOT_))
      //tooltip = "Root node for showing the entire module hierarchy";
      //else
      if (module != null) {
	tooltip = toString();
      } else {
	tooltip = "Root node for showing the entire module hierarchy";
      }
    }

    else if (dataType.equals(WORKSPACE_HIERARCHY_)) {
      //if (baseClass.equals(ROOT_))
      //tooltip = "the root for the entire knowledge-base workspace hierarchy";
      //else {
	try {
	  KbWorkspace wksp = (KbWorkspace)item;
	  if (wksp != null) {
	    name_ = (Symbol)wksp.getNames();
	    if (name_ == null) name_ = DEFAULT_WORKSPACE_NAME_;
	    containingModule = wksp.getContainingModule();
	    tooltip = containingModule+":: "+name_;
	  } else {
	    tooltip = "the root for the entire knowledge-base workspace hierarchy";
	  }
	} catch (G2AccessException gae) {
	  Trace.exception(gae); 
	}
	// }
    }

    else if (dataType.equals(CLASS_HIERARCHY_)) {
      if (item != null) {
	tooltip = toString();  //baseClass+": a system defined class";
      } else {
	//if (baseClass.equals(ROOT_)) 
	tooltip = "the root for the entire knowledge-base class hierarchy";
      }
    }

    else if (dataType.equals(KNOWLEDGE_BASE_)) {
      tooltip = "the root for the entire knowledge-base workspace hierarchy";
    }

    else if (dataType.equals(UNREQUIRED_MODULES_)) {
      tooltip = "Root node for showing the unrequired modules";
    }

    return tooltip;
  }
}
