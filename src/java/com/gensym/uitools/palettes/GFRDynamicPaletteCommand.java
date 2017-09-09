package com.gensym.uitools.palettes;

import java.util.Hashtable;
import com.gensym.ntw.TwAccess;
import com.gensym.message.Resource;
import java.awt.Component;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.Symbol;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Entity;
import com.gensym.classes.Item;
import com.gensym.util.symbol.G2ClassSymbols;

public class GFRDynamicPaletteCommand extends DynamicPaletteCommand
{
  private Hashtable paletteMap;
  private TwAccess connection;
  private Hashtable connectionStates;
  
  public void setPaletteMap(Hashtable paletteMap)
  {
    this.paletteMap = paletteMap;
  }

  public GFRDynamicPaletteCommand(DynamicTabbedPalette tabbedPalette,
				  Hashtable groups,
				  Resource shortResource,
				  Resource longResource,
				  String top)
  {
    super(tabbedPalette);
    connectionStates = new Hashtable();
    setStructure(groups, shortResource, longResource, top);
    setAvailability();
  }

  public void setAvailability() {
    String[] keys = getKeys();
    for (int i=0; i<keys.length; i++) {
      String key = keys[i];
      setAvailable(key, !getPaletteState(key) && (connection != null));
    }
  }

  @Override
  protected void setPaletteState(String paletteKey, boolean state)
  {
    Hashtable states=(Hashtable)connectionStates.get(connection);
    if (states == null) {
      states = new Hashtable();
      connectionStates.put(connection, states);
    }
    setAvailable(paletteKey, !state);
    states.put(paletteKey, state?Boolean.TRUE:Boolean.FALSE);
  }

  @Override
  public boolean getPaletteState(String paletteKey)
  {
    boolean state = false;
    Hashtable states=null;
    if (connection != null)
      states = (Hashtable)connectionStates.get(connection);
    if (states != null) {
      Boolean stateObj = (Boolean)states.get(paletteKey);
      if (stateObj != null)
	state = stateObj.booleanValue();
    }
    return state; 
  }
  
    
  public void setConnection(TwAccess connection)
  {
    this.connection = connection;
    setAvailability();
  }
  
  @Override
  protected Component createPalette(String paletteKey)
       throws PaletteCreationException
  {
    Symbol paletteObjectName_ = null;
    if (paletteMap != null)
      paletteObjectName_ = (Symbol) paletteMap.get (paletteKey);
    if (paletteObjectName_ == null)
      paletteObjectName_ = Symbol.intern(paletteKey.toUpperCase());
    try {
      Item paletteObject
	= connection.getUniqueNamedItem(G2ClassSymbols.ITEM_, paletteObjectName_);
      KbWorkspace paletteWorkspace = ((Entity)paletteObject).getSubworkspace ();
      GFRColumnPalette palette
	= new GFRColumnPalette (paletteKey, connection, paletteWorkspace);
      return palette;
    } catch (G2AccessException g2ae) {
      throw new PaletteCreationException(g2ae);
    }
  }
  
}  
