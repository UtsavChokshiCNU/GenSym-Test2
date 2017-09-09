/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2EditModulePanel.java
 *
 *  Description:
 *
 *
 *	 Author:
 *		Todd O'Brien		Feb/98
 *
 *     
 *   Modifications:
 *
 */

package com.gensym.g2studio.dialogs;

import com.gensym.classes.Module;
import com.gensym.dlg.TabGroupPanel;
import com.gensym.message.Resource;
import com.gensym.uiutil.StandardGridBagPanel;

/**
 */
public class G2EditModulePanel extends TabGroupPanel
{
  private static Resource shortBundle = Resource.getBundle("com/gensym/g2studio/dialogs/CommandShortResource");

  /**
   */
  public G2EditModulePanel(Module module)
  {  
    super();
    addTab(shortBundle.getString("ModuleAttributesTabLabel"), 
	   new G2ModuleAttributesPanel(module));
    addTab(shortBundle.getString("WorkspacesTabLabel"),
	   new G2WorkspacesPanel(module));
    addTab(shortBundle.getString("SystemTablesTabLabel"), 
	   new G2SystemTablesPanel(module));
  }

}


