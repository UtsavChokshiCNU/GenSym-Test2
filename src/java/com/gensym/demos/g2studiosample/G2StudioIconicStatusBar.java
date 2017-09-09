package com.gensym.demos.g2studiosample;

import java.awt.Toolkit;
import java.awt.Component;
import java.awt.Image;
import java.awt.Frame;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import com.gensym.uitools.utils.IconicStatusBar;
import com.gensym.util.Symbol;
import com.gensym.message.Trace;
import com.gensym.gcg.NotesTextArea;
import com.gensym.controls.DialogCommand;
import com.gensym.classes.Block;
import com.gensym.classes.Item;
import com.gensym.classes.ImplAccess;
import com.gensym.jgi.G2AccessException;
import com.gensym.wksp.WorkspaceElement;
import com.gensym.ntw.TwAccess;
import com.gensym.dlg.StandardDialog;
import com.gensym.util.ItemListener;
import com.gensym.util.ItemEvent;
import com.gensym.util.symbol.SystemAttributeSymbols;

public class G2StudioIconicStatusBar extends IconicStatusBar 
implements ItemListener {
  private static final String NOTES = "Notes", PERMANENT = "Permanent";
  private static final Symbol OK_ = Symbol.intern("OK");
  private static final String NOTES_FOR = "Notes for ";
  private static final Image notesImage
  = Toolkit.getDefaultToolkit().getImage(G2StudioIconicStatusBar.class.getResource("notes.gif"));
  //Image isPermanentImage =
  //Toolkit.getDefaultToolkit().getImage(G2StudioIconicStatusBar.class.getResource("notes.gif"));
  private WorkspaceElement[] selection;
  private Frame frame;
  private static final Symbol[] neededAttributes
  = {SystemAttributeSymbols.ITEM_STATUS_,SystemAttributeSymbols.ITEM_NOTES_};

  public G2StudioIconicStatusBar(Frame frame) {
    this.frame = frame;
    ActionListener notesListener = new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent ae) {
	for (int i=0;i<selection.length;i++) {
	  WorkspaceElement elt = selection[i];
	  Item item = elt.getItem();
	  Block b = (Block)item;
	  TwAccess currentConnection = (TwAccess)((ImplAccess)item).getContext();
	  try {
	    boolean hasNotes = (!b.getItemStatus().equals(OK_) || b.getItemNotes() != null);
	    if (hasNotes) {
	      String title = NOTES_FOR + item.getTableHeader();
	      (new NotesDialog(G2StudioIconicStatusBar.this.frame, currentConnection, item, title)).setVisible(true);
	    }
	  } catch (G2AccessException g2ae) {
	    Trace.exception(g2ae);
	  }
	}     
      }	
    };
    addIcon(NOTES, notesImage, notesListener);
    //addIcon(PERMANENT, isPermanentImage, null);
    updateIcons(null);          
  }

  public void updateIcons(WorkspaceElement[] selection) {
    try {
      removeItemListeners(this.selection);
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
    this.selection = selection;
    try {
      addItemListeners(selection);
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
    updateIconsForSelection(selection);
  }

  public void removeItemListeners(WorkspaceElement[] selection) throws G2AccessException
  {
    if (selection == null) return;
    for (int i=0;i<selection.length;i++) {
      Item itm = selection[i].getItem();
      itm.removeItemListener(this, neededAttributes);
    }
  }
  
  public void addItemListeners(WorkspaceElement[] selection) throws G2AccessException
  {
    if (selection == null) return;
    for (int i=0;i<selection.length;i++) {
      Item itm = selection[i].getItem();
      itm.addItemListener(this, neededAttributes);
    }
  }
  
  @Override
  public void itemModified(ItemEvent ie) {
    updateIconsForSelection(selection);
  }
  @Override
  public void itemDeleted(ItemEvent ie) {}
  @Override
  public void receivedInitialValues(ItemEvent ie) {}
  
  private void updateIconsForSelection(WorkspaceElement[] selection) {
    Component notes = getComponent(NOTES);
    //Component permanent = iconicStatusBar.getComponent(PERMANENT);
    boolean haveNotes = false;
    //boolean isPermanent = false;
    if (selection != null) {
      for (int i=0;i<selection.length&&!haveNotes;i++) {
	WorkspaceElement elt = selection[i];
	Block b = (Block)elt.getItem();
	try {
	  haveNotes = (!b.getItemStatus().equals(OK_) || b.getItemNotes() != null);//NOTE attrs not cached!
	  //isPermanent = ((Item)b).getPermanent();
	} catch (G2AccessException g2ae) {
	  Trace.exception(g2ae);
	}
      }     
    }
    notes.setEnabled(haveNotes);
    //permanent.setEnabled(isPermanent);
  }

  class NotesDialog extends StandardDialog {
    NotesDialog(Frame frame, TwAccess connection, Item item, String title) throws G2AccessException {
      super(frame,
	    title,
	    false,
	    new String[] {OK_LABEL},
	    new int[] {OK},
	    new NotesTextArea(connection,item, new DialogCommand()),
	    null);
      setSize(400,300);
    }
  }
  
}
