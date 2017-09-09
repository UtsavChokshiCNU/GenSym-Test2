/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 MDITilingCommand.java
 *
 */
package com.gensym.mdi;

import java.awt.event.ActionEvent;
import com.gensym.message.Resource;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;

class MDITilingCommand extends AbstractCommand{
  private static final String TILE_VERTICALLY = "TileVertically";
  private static final String TILE_HORIZONTALLY = "TileHorizontally";
  private static final String TILE_CASCADE = "TileCascade";
  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private static final String mnemonicResource = "MnemonicResource";
  private static Resource i18n = Resource.getBundle("com.gensym.resources.Errors");
  private MDIManager client;

  public MDITilingCommand(MDIManager client){
    super(new CommandInformation[]{
      new CommandInformation(TILE_VERTICALLY, true, shortResource, longResource,
			     "tile_vertically.gif", null, null, true, mnemonicResource, null),
      new CommandInformation(TILE_HORIZONTALLY, true, shortResource, longResource,
			     "tile_horizontally.gif", null, null, true, mnemonicResource, null),
      new CommandInformation(TILE_CASCADE, true, shortResource, longResource,
			     "cascade.gif", null, null, true, mnemonicResource, null)});
    this.client = client;
    setAvailable(false);
  }

  void setAvailable(boolean available){
    setAvailable(TILE_VERTICALLY, available);
    setAvailable(TILE_HORIZONTALLY, available);
    setAvailable(TILE_CASCADE, available);
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String keyCmd = e.getActionCommand();
    if (!isAvailable(keyCmd)) 
      throw new IllegalStateException(i18n.getString("unavailableCommand"));
    int tilingCode = MDITilingConstants.TILE_CASCADE;
    if (TILE_VERTICALLY.equals(keyCmd))
      tilingCode = MDITilingConstants.TILE_VERTICALLY;
    else if (TILE_HORIZONTALLY.equals(keyCmd))
      tilingCode = MDITilingConstants.TILE_HORIZONTALLY;
    client.arrange(tilingCode);
  }

}
