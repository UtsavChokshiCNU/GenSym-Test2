package com.gensym.uitools.palettes;

import com.gensym.ntw.TwAccess;
import javax.swing.JTabbedPane;
import java.util.Hashtable;

public class MultipleConnectionDynamicTabbedPalette
extends DynamicTabbedPalette
{
  private TwAccess currentConnection;
  private Hashtable paletteGroups;
  private String titleBase;

  public MultipleConnectionDynamicTabbedPalette(String titleBase)
  {
    super(titleBase);
    this.titleBase = titleBase;
    paletteGroups = new Hashtable(7);
  }

  public TwAccess getConnection()
  {
    return currentConnection;
  }

  protected String getTitle(String titleBase) {
    String newTitle = titleBase;
    if (currentConnection != null)
      newTitle+=" ("+currentConnection.toShortString()+")";
    return newTitle;
  }
  
  public void setConnection(TwAccess currentConnection) {
    if (currentConnection == this.currentConnection) return;
    this.currentConnection = currentConnection;
    setTitle(getTitle(titleBase));        
    if (currentConnection == null) {
      setPaletteGroup(null);
    } else {
      JTabbedPane group = (JTabbedPane) paletteGroups.get(currentConnection);
      if (group == null) {
	group = createPaletteGroup();
	paletteGroups.put(currentConnection, group);
      }
      setPaletteGroup(group);
    }
  }
}
