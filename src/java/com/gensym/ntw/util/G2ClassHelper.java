package com.gensym.ntw.util;

import java.awt.Image;
import java.awt.Toolkit;
import com.gensym.classes.G2Definition;
import com.gensym.icons.IconDescription;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.util.ClassBrowserScrollPane;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.G2ClassSymbols;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.wksp.WorkspaceColorTable;
import com.gensym.draw.ColorTable;
import java.util.Enumeration;

class G2ClassHelper{

  static final int SMALL_ICON = 0;
  static final int LARGE_ICON = 1;

  private static final Class thisClass = com.gensym.ntw.util.G2ClassHelper.class;

  private static Image messageIcon16x16;
  private static Image messageIcon;
  private static Image nonEntityIcon16x16;
  private static Image nonEntityIcon;

  private static final String NO_SUCH_CLASS_ERROR_TEXT = "NO-SUCH-CLASS-ERROR";

  static G2Definition getDefinitionForClassName(TwAccess context, Symbol className) throws G2AccessException{
    try{
      G2Definition def = context.getClassManager().getDefinition(className);
      return def;
    }
    catch(G2AccessException ex){
      if (isNoSuchClassException(ex))
	return null;
      else
	throw ex;
    }
  }

  static boolean isNoSuchClassException(G2AccessException ex){
    return (ex.getMessage().indexOf (NO_SUCH_CLASS_ERROR_TEXT) >= 0);
  }

  //better name? pbk will see if there is a better rule
  static boolean isInstanceAllowedOnWorkspace(G2Definition def) throws G2AccessException{
    if (def != null){
      Sequence inheritancePath = def.getSystemClassInheritancePath();
      if (!inheritancePath.contains(G2ClassSymbols.BLOCK_) ||
	  inheritancePath.contains(G2ClassSymbols.CONNECTION_) ||
	  inheritancePath.contains(G2ClassSymbols.WORKSPACE_) ||
	  inheritancePath.contains(G2ClassSymbols.PROCEDURE_INVOCATION_) ||
	  inheritancePath.contains(G2ClassSymbols.SIMULATION_SUBTABLE_) ||
	  inheritancePath.contains(G2ClassSymbols.SYSTEM_TABLE_) ||
	  inheritancePath.contains(G2ClassSymbols.ERROR_) ||
	  inheritancePath.contains(G2ClassSymbols.G2_JAVA_BEAN_))
	return false;
      else 
	return true;
    }
    return false;
  }

  private static Structure transformColorValues(Structure regionOverrides,
						ColorTable colorTable) {
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

  private static ColorTable colorTable = new WorkspaceColorTable();
  static Image getIconForClass(TwAccess context,
			       G2Definition def,
			       Symbol className,
			       Structure regionOverrides,     			       
			       Structure variableOverrides,
			       int size) throws G2AccessException
  {
    regionOverrides = transformColorValues(regionOverrides, colorTable);
    Sequence inheritancePath = def.getSystemClassInheritancePath();
    String iconFileName = null;
    if (inheritancePath.contains(G2ClassSymbols.TEXT_BOX_)){
      initializeImages();
      return (size == SMALL_ICON ? messageIcon16x16 : messageIcon);
    }
    else if (!inheritancePath.contains(G2ClassSymbols.ENTITY_) ||
	     inheritancePath.contains(G2ClassSymbols.TYPE_IN_BOX_)){
      initializeImages();
      return (size == SMALL_ICON ? nonEntityIcon16x16 : nonEntityIcon);
    }
    return createImageFromIconDescription(context, className,
					  regionOverrides,		  
					  variableOverrides,
					  size);
  }

  private static void initializeImages(){
    if (messageIcon16x16 == null){
      messageIcon16x16 = Toolkit.getDefaultToolkit().getImage(thisClass.getResource("message16x16.gif"));
      messageIcon = Toolkit.getDefaultToolkit().getImage(thisClass.getResource("message.gif"));
      nonEntityIcon16x16 = Toolkit.getDefaultToolkit().getImage(thisClass.getResource("non-entity16x16.gif"));
      nonEntityIcon = Toolkit.getDefaultToolkit().getImage(thisClass.getResource("non-entity.gif"));
    }
  }

  private static Image createImageFromIconDescription(TwAccess context,
						      Symbol className,
						      Structure regionOverrides,     
						      Structure variableOverrides,
						      int size) throws G2AccessException
  {
    IconDescription iconDescrip = new G2IconDescription(className, context);
    if (size == SMALL_ICON)
      return iconDescrip.createImage(16, 16, 0, null, false,
				     regionOverrides,
				     variableOverrides);
    else
      return iconDescrip.createImage(32, 32, 0, null, false,
				     regionOverrides,
				     variableOverrides);
  }
}
