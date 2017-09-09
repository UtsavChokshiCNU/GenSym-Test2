/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2ColorsDialog.java
 *
 */
package com.gensym.editor.color;

import java.awt.Button;
import java.awt.Color;
import java.awt.Frame;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;

public class G2ColorRegionsDialog extends StandardDialog {

  private G2ColorRegionsPanel regionsPanel = null;

  /**
   * @param parentFrame The Frame that is the parent for this instance of
   * G2ColorRegionsDialog
   * @param title A String containing the title for this instance of
   * G2ColorRegionsDialog
   * @param isModal A boolean value indicating whether or not this instance of
   * G2ColorRegionsDialog should be modal
   * @param client The StandardDialogClient for this G2ColorRegionsDialog
   */
  public G2ColorRegionsDialog (Frame parentFrame, String title,
			       boolean isModal,
			       StandardDialogClient client) { 

    this(parentFrame, title, isModal,
	 new String[] {OK_LABEL, APPLY_LABEL, CANCEL_LABEL},
	 new int[] {OK, APPLY, CANCEL},
	 new G2ColorRegionsPanel(),
	 client);
  }

  private G2ColorRegionsDialog(Frame parentFrame,
			       String title,
			       boolean isModal,
			       String[] labels,
			       int[] ids,
			       G2ColorRegionsPanel regionsPanel,
			       StandardDialogClient client)
  {
    super(parentFrame, title, isModal,
	  labels, ids, regionsPanel,
	  new DialogClient(client, regionsPanel));
    this.regionsPanel = regionsPanel;
  }
  
  /**
   * Gets the current regions as modified by this dialog.
   * @returns a Structure whose attribute names are Symbols
   * naming color regions and whose attribute values are
   * Symbols naming g2 colors.
   */
  public Structure getRegions()
  {
    return regionsPanel.getRegions();
  }

  /**
   * Initializes the regions for this Dialog
   * @param regions a Structure whose attribute names are Symbols
   * naming color regions and whose attribute values are
   * Symbols naming g2 colors.
   */
  public void setRegions(Structure regions)
  {
    regionsPanel.setRegions(regions);
  }

  void addRegion(Symbol regionName,
		 Symbol currentColorName)
  {
    regionsPanel.addRegion(regionName, currentColorName);
  }

  void clearRegions()
  {
    regionsPanel.clearRegions();
    regionsPanel.repaint();
  }
       
  void addRegions(Structure regions)
  {
    regionsPanel.addRegions(regions);
  }
  
}

  class DialogClient implements StandardDialogClient , java.io.Serializable {
    private StandardDialogClient userClient;
    private G2ColorRegionsPanel panel;
    
    DialogClient(StandardDialogClient userClient,
			G2ColorRegionsPanel panel)
    {
      this.userClient = userClient;
      this.panel = panel;
    }
    
    @Override
    public void dialogDismissed (StandardDialog dlg, int code) {
      if (code == com.gensym.dlg.CommandConstants.APPLY ||
	  code == com.gensym.dlg.CommandConstants.OK)
	panel.setSelectedColor(panel.getSelectedColorString());
      if (userClient != null)
	userClient.dialogDismissed(dlg, code);
    }
  }
