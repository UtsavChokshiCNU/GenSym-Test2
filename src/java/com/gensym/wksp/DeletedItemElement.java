package com.gensym.wksp;


import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.*;
import com.gensym.message.*;
import java.awt.Rectangle;
import java.awt.PopupMenu;
import java.awt.Component;

/**
 * Element that represents an Item that has already been
 * deleted in G2 by the time we process the workspaceItemAdded
 * event.
 */
class DeletedItemElement extends Component implements WorkspaceElement {

  private Item itm;
  DeletedItemElement (Item itm) {
    this.itm = itm;
    setBounds (0, 0, 0, 0);
  }

  @Override
  public void handleWorkspaceItemMoved (WorkspaceEvent event) {}

  @Override
  public void handleWorkspaceItemResized (WorkspaceEvent event) {}

  @Override
  public void handleWorkspaceItemColorsChanged (WorkspaceEvent event) {}

  @Override
  public Item getItem() {
    return itm;
  }

  @Override
  public void select () {}

  @Override
  public void unselect () {}

  @Override
  public boolean isSelected () {
    return false;
  }

  @Override
  public DraggingGhost getDraggingGhost (int left, int top, int width, int height) {
    return null;
  }

  @Override
  public DraggingGhost getDraggingGhost () {
    return null;
  }
  
  @Override
  public DraggingGhost getDraggingGhost (int markerLocn, int currentX, int currentY) {
    return null;
  }

  @Override
  public PopupMenu getContextMenu () {
    return null;
  }

  @Override
  public boolean isCut () {
    return false;
  }

  @Override
  public void setCut (boolean newCutState) {
  }

  @Override
  public void receivedInitialValues (com.gensym.util.ItemEvent ie) {}

  @Override
  public void itemModified (com.gensym.util.ItemEvent ie) {}

  @Override
  public void itemDeleted (com.gensym.util.ItemEvent ie) {}

  @Override
  public void dispose() {}

  @Override
  public String toString () {
    return super.toString () + hashCode ();
  }
}


