package com.gensym.uitools.palettes;

import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.StructuredCommandInformation;
import com.gensym.ui.SubCommandInformation;
import java.awt.event.ActionEvent;
import com.gensym.message.Resource;
import java.util.MissingResourceException;
import java.util.Hashtable;
import java.util.Vector;
import com.gensym.jgi.G2AccessException;
import java.awt.Component;
import com.gensym.message.Trace;

public abstract class DynamicPaletteCommand extends AbstractStructuredCommand
{

  private Hashtable palettesTable = new Hashtable (17);
  private Resource shortResource, longResource;
  private Hashtable paletteGroups;
  private String top;
  private DynamicTabbedPalette tabbedPalette;

  
  public DynamicPaletteCommand (DynamicTabbedPalette tabbedPalette)
  {
    super (new CommandInformation[]{});

    this.tabbedPalette = tabbedPalette;
  }


  public void setStructure(Hashtable paletteGroups,
			   Resource shortResource,
			   Resource longResource,
			   String topGroupName)
  {
    this.shortResource = shortResource;
    this.longResource = longResource;    
    this.top = topGroupName;
    this.paletteGroups=paletteGroups;
    reset();
  }

  public Resource getShortResource()
  {
    return shortResource;
  }

  public Resource getLongResource()
  {
    return longResource;
  }
  
  private void reset()
  {
    setStructuredKeys(makeCommandInformationArray((String[])paletteGroups.get(top),
						  null, //Boolean.FALSE,
						  shortResource,
						  longResource,
						  paletteGroups));
  }
  
  private static CommandInformation[] makeCommandInformationArray
  (String[] commandKeys,
   Boolean initialState,
   Resource shortResource,
   Resource longResource,
   Hashtable paletteGroups)
  {
    CommandInformation[] ci = new CommandInformation[commandKeys.length];    
    for (int i=0; i<commandKeys.length; i++) {
      String key = commandKeys[i];
      String [] group = (String[]) paletteGroups.get(key);
      String shortDesc, longDesc;
      try {
	shortDesc = shortResource.getString(key);
	longDesc = longResource.getString(key);
      } catch (MissingResourceException mre) {
	shortDesc = key;
	longDesc = key;
      }      
      if (group != null)
	ci[i] =
	  new SubCommandInformation(key, true,
				    null,
				    null,
				    null, null, null,
				    shortDesc, longDesc,
				    null, null,
				    makeCommandInformationArray(group,
								initialState,
								shortResource,
								longResource,
								paletteGroups));
      else {
	ci[i] = new CommandInformation(key, true, null, null, null, null, 
				       initialState, true,
				       shortDesc, longDesc, null, null);
      }
    }
    return ci;
  }

  private static String[] filterDuplicates(String[] names) {
    Vector nms = new Vector();
    for (int i=0;i<names.length;i++) {
      String name = names[i];
      if (!nms.contains(name))
	nms.addElement(name);
      else
	System.out.println("ERROR: recieved duplicate palette: " + name +
			   " ...cont..");
    }
    String[] fNames = new String[nms.size()];
    nms.copyInto(fNames);
    return fNames;
  }

  public static final String CUSTOME_USER_PALETTES_KEY = "CUSTOME-USER-PALETTES-KEY";  
  public String[] getUserPaletteNames() {
    return (String[])paletteGroups.get(CUSTOME_USER_PALETTES_KEY);
  }
  
  
  public void setUserPaletteNames(String[] names)
  {
    names = filterDuplicates(names);
    paletteGroups.put(CUSTOME_USER_PALETTES_KEY, names);
    reset();
  }
  
  @Override
  public void actionPerformed (ActionEvent aEvt) {
    String cmdKey = aEvt.getActionCommand ();
    //System.out.println ("State of " + cmdKey + " =  " + paletteCommand.getState (cmdKey));
    if (getPaletteState(cmdKey))
      removePalette (cmdKey);
    else {
      try {
	addPalette (cmdKey);
      } catch (PaletteCreationException pce) {
	Trace.exception(pce);
      }
    }
  }

  protected void setPaletteState(String paletteKey, boolean state)
  {
    setState(paletteKey, state?Boolean.TRUE:Boolean.FALSE);      
  }

  public boolean getPaletteState(String paletteKey)
  {
    Boolean state = getState(paletteKey);
    if (state == null)
      state = Boolean.FALSE;
    return state.booleanValue();
  }
  
  public void addPalette (String paletteKey)
       throws PaletteCreationException
  {
    Component palette = createPalette(paletteKey);      
    String tabLabel = getPaletteLabel(paletteKey);
    palettesTable.put (paletteKey, palette);
    setPaletteState(paletteKey,true);
    tabbedPalette.addPalette(tabLabel, palette);
  }

  public void removePalette (String paletteKey) {
    Component palette = (Component)palettesTable.remove(paletteKey);
    tabbedPalette.removePalette(palette);
    setPaletteState(paletteKey,false);
  }
  
  protected String getPaletteLabel(String paletteKey)
  {
    String shortDesc = null;
    try {
      shortDesc = shortResource.getString(paletteKey);
    } catch (MissingResourceException mre) {
      shortDesc = paletteKey;
    }
    return shortDesc;
  }
  
  protected abstract Component createPalette(String paletteKey)
       throws PaletteCreationException;

    
}
