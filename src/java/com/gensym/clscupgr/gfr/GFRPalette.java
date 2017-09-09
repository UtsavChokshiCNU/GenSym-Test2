
package com.gensym.clscupgr.gfr;

import java.util.Vector;
import java.util.Hashtable;

import com.gensym.ui.*;
import com.gensym.ui.palette.*;
import com.gensym.classes.modules.gfr.*;
import com.gensym.util.*;
import com.gensym.uiutil.*;
import com.gensym.ntw.*;
import com.gensym.ntw.util.G2Palette;
import com.gensym.ntw.util.G2ObjectCreator;
import com.gensym.jgi.*;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Item;

/**
 * A class that presents a palette of all the ITEMs on a specific
 * KB-WORKSPACE that have "GFR palette behavior" in G2.
 */
public class GFRPalette extends G2Palette {
  
  private ObjectCreator creator;

  /**
   * Construct a palette of every ITEM that has "gfr palette behavior" that
   * is on the specified workspace.
   * @param name the name of the palette
   * @param context the connection to G2
   * paletteWksp a KB-WORKSPACE that has on it one or more ITEMs with
   * "GFR palette behavior"
   */
  public GFRPalette (String name, TwAccess context, KbWorkspace paletteWksp) throws G2AccessException {
    super (context, name);
    creator = new GFRObjectCreator (context, paletteWksp);
    add (creator);
  }
  
}


class GFRObjectCreator extends G2ObjectCreator implements ObjectCreator {

  private static final String[] noStrings = new String[0];
  private static final Symbol GFR_TEXT_RESOURCE_GROUP_ = Symbol.intern("GFR-TEXT-RESOURCE-GROUP");
  private static final Symbol UNSPECIFIED_ = Symbol.intern("UNSPECIFIED");
  private Item[] paletteItems;

  GFRObjectCreator (TwAccess context, KbWorkspace paletteWksp) throws G2AccessException {
    super (context, noStrings);
    paletteItems = collectPaletteItems (context, paletteWksp);
    setStructuredKeys (paletteItems);
    context.addG2ConnectionListener (new CreationAccessAdapter ());
  }

  private WorkspaceListener adapter;
  private Item[] collectedItems;
  private Hashtable descriptionTable = new Hashtable();

  private static final Symbol WORKSPACE_INITIAL_DATA_ = Symbol.intern ("WORKSPACE-INITIAL-DATA");
  private static final Symbol ITEM_INFO_LIST_ = Symbol.intern ("ITEM-INFO-LIST");

  /*
   * Use the WorkspaceListener capability to retrieve the items on the workspace
   * WARNING: This method has knowledge of the format of the initial download
   * and needs to be updated if it changes - vkp, 8/9/98
   */
  Item[] collectPaletteItems (TwAccess context, KbWorkspace paletteWksp) throws G2AccessException {
    paletteWksp.addWorkspaceListener (adapter = new WorkspaceAdapter () {
      @Override
      public void receivedInitialDownload (WorkspaceEvent event) {
	try {
	  Structure info = event.getInfo ();
	  Structure wkspData = (Structure) info.getAttributeValue (WORKSPACE_INITIAL_DATA_, null);
	  Sequence items = (Sequence) wkspData.getAttributeValue (ITEM_INFO_LIST_, null);
	  Vector itemsList = new Vector ();
	  for (int i=0; i<items.size (); i++) {
	    Item wkspItem = (Item) items.elementAt (i);
	    if (wkspItem instanceof GfrPaletteWindow) {
	      GfrPaletteWindow paletteWindow = (GfrPaletteWindow)wkspItem;
	      Item paletteItem = GFRAPI.getPaletteItem (getConnection (), paletteWindow);
	      itemsList.addElement (paletteItem);
	      Symbol resourceName_ = paletteWindow.getGfrHelpTextResource();
	      //System.out.println(resourceName_);
	      if (!resourceName_.equals(UNSPECIFIED_)){
		Symbol messageName_ = paletteWindow.getGfrHelpMessageName();
		//System.out.println(messageName_);
		if (!messageName_.equals(UNSPECIFIED_)){
		  Item item = getConnection().getUniqueNamedItem(GFR_TEXT_RESOURCE_GROUP_, resourceName_);
		  if (item instanceof GfrTextResourceGroup){
		    GfrTextResourceGroup resourceGroup = (GfrTextResourceGroup)item;
		    String description = resourceGroup.gfrLocalizeMessage(messageName_, getConnection().retrieveSession().getUiClientSpecificLanguage(), getConnection().retrieveSession());
		    //System.out.println(description);
		    Symbol paletteClass_ = paletteItem.getG2ClassName();
		    
		    //THIS NEEDS TO BE UPDATED IN CASE THERE IS MORE THAN ONE INSTANCE
		    //OF THE SAME CLASS ON A GIVEN PALETTE(<class-name>(#1),...)
		    descriptionTable.put(paletteClass_.getPrintValue(), description);
		  }
		}
	      }
	    }
	  }
	  collectedItems = new Item[itemsList.size ()];
	  itemsList.copyInto (collectedItems);
	  KbWorkspace wksp = (KbWorkspace) event.getSource ();
	  wksp.removeWorkspaceListener (this);
	} catch (G2AccessException gae) {
	  com.gensym.message.Trace.exception (gae);
	}
      }
    });
    return collectedItems;
  }

  @Override
  public String getDescription(String key, int type){
    String description = (String)descriptionTable.get(key);
    if (description == null) return super.getDescription(key, type);
    else return description;
  }

  @Override
  public Object createObject(String key) {
    Item paletteItem = getPaletteItem(key);
    try{    
      return GFRAPI.createPaletteClone(getConnection(), paletteItem);
    } catch(G2AccessException ex){
      throw new UnexpectedException(ex);
    }
  }

  private void setAvailableAll (boolean available) {
    String[] keys = getKeys ();
    for (int i=0; i<keys.length; i++)
      setAvailable (keys[i], available);
  }

  class CreationAccessAdapter extends G2ConnectionAdapter {

    CreationAccessAdapter () throws G2AccessException {
      Symbol g2State = getConnection ().getG2State ();
      if (!g2State.equals (G2Gateway.RUNNING_))
	setAvailableAll (false);
    }
    
    @Override
    public void g2IsPaused (G2ConnectionEvent event) {
      setAccessEnabled (false);
    }
    
    @Override
    public void g2IsResumed (G2ConnectionEvent event) {
      setAccessEnabled (true);
    }
    
    @Override
    public void g2IsReset (G2ConnectionEvent event) {
      setAccessEnabled (false);
    }
    
    @Override
    public void g2IsStarted (G2ConnectionEvent event) {
      setAccessEnabled (true);
    }
    
    @Override
    public void g2ConnectionClosed (G2ConnectionEvent event) {
      setAccessEnabled (false);
    }
    
    @Override
    public void g2ConnectionInitialized (G2ConnectionEvent event) {
      // Do nothing?
    }

    private void setAccessEnabled (boolean allowAccess) {
      setAvailableAll (allowAccess);
    }
    
  }

}



