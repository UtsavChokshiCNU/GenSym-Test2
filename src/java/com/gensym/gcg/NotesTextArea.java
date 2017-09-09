package com.gensym.gcg;

import com.gensym.classes.Block;
import com.gensym.classes.Item;
import com.gensym.controls.DialogCommand;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.dlgruntime.DialogCommandListener;
import com.gensym.dlgruntime.DialogCommandEvent;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2ConnectionAdapter;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.jgi.G2ConnectionListener;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.util.ItemEvent;
import com.gensym.util.ItemListener;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.util.symbol.VirtualAttributeSymbols;

/**
 *  NotesTextArea is a component for displaying the notes attribute of an item. 
 *  NotesTextArea is automatically hooked-up to stay in sync with G2.  NotesTextArea
 *  unhooks itself when it receives a dialogShutdown event from the DialogCommand.
 */
public class NotesTextArea extends G2ReadOnlyTextArea{

  private static final Symbol TYPE_ = Symbol.intern("TYPE");
  private static final Symbol NAME_ = Symbol.intern("NAME");
  private static final Symbol ATTRIBUTE_ = Symbol.intern("ATTRIBUTE");
  private static final Symbol VIRTUAL_ATTRIBUTE_ = Symbol.intern("VIRTUAL-ATTRIBUTE");
  private static final Symbol OK_ = Symbol.intern("OK");
  private static final Symbol[] neededAttributes 
 = {SystemAttributeSymbols.NOTES_,
    VirtualAttributeSymbols.ITEM_STATUS_,
    VirtualAttributeSymbols.ITEM_NOTES_};
  private G2ConnectionListener g2ConnectionListener;
  private ItemListener itemListener;
  private DialogCommand dialogCommand;
  private DialogCommandListener cmdListener;
  private OptionalComponentDisplayer displayer;
  private boolean interesting = false;

  public NotesTextArea(TwAccess connection, Item item, DialogCommand dialogCommand) throws G2AccessException{
    super(connection, item, SystemAttributeSymbols.NOTES_, null);
    createDenotation();
    itemListener = new StatusChangeAdapter();
    item.addItemListener(itemListener, neededAttributes);
    g2ConnectionListener = new ClosingAdapter();
    connection.addG2ConnectionListener(g2ConnectionListener);
    this.dialogCommand = dialogCommand;
    cmdListener = new CommandAdapter();
    dialogCommand.addDialogCommandListener(cmdListener);
  }
  
  void setNotesDisplayer(OptionalComponentDisplayer displayer) {
    this.displayer=displayer;
  }

  @Override
  void update() throws G2AccessException{
    super.update();
    setInteresting();
  }

  private void setInteresting() throws G2AccessException{
    if (item instanceof Block){
      Block b = (Block)item;
      interesting= (!b.getItemStatus().equals(OK_) || b.getItemNotes() != null);
    }
    else{
      String currentText = textArea.getText();
      interesting = (currentText != null && !currentText.equals("OK"));
    }
    if (displayer != null){
      if (interesting)
	displayer.showComponent();
      else
	displayer.hideComponent();
    }
    //System.out.println("interesting="+interesting+"  text="+textArea.getText());
  }

  boolean isInteresting(){
    return interesting;
  }

  private void createDenotation(){
    denotation = new Structure();
    denotation.setAttributeValue(TYPE_, ATTRIBUTE_);
    denotation.setAttributeValue(NAME_, SystemAttributeSymbols.NOTES_);
  }

  @Override
  public void objectUpdated(ObjectUpdateEvent event){
    //do nothing - use itemListener instead
  }

  private void cleanup(){
    try{
      if (item != null)
	item.removeItemListener(itemListener, neededAttributes);
    }
    catch(G2AccessException ex){
      Trace.exception(ex);
    }
    item = null;
    if (connection != null)
      connection.removeG2ConnectionListener(g2ConnectionListener);
    connection = null;
    if (dialogCommand != null)
      dialogCommand.removeDialogCommandListener(cmdListener);
    dialogCommand = null;
  }

  class CommandAdapter implements DialogCommandListener{
    @Override
    public void dialogChangesFlushed (DialogCommandEvent event){}
    @Override
    public void dialogLaunched(DialogCommandEvent event){}
    @Override
    public void dialogShutdown(DialogCommandEvent event){
      cleanup();
    }
  }
  
  class ClosingAdapter extends G2ConnectionAdapter{
    public void connectionClosed(G2ConnectionEvent event){
      cleanup();
    }
  }

  public boolean itemNotesModified(ItemEvent event){
    Sequence denotation = event.getDenotation();
    if (!denotation.isEmpty() && denotation.elementAt(0) instanceof Structure){
      Structure denotationElement = (Structure)denotation.elementAt(0);
      if (denotationElement.getAttributeValue(SystemAttributeSymbols.TYPE_, null).equals(ATTRIBUTE_) ||
	  denotationElement.getAttributeValue(SystemAttributeSymbols.TYPE_, null).equals(VIRTUAL_ATTRIBUTE_)){
	Symbol attributeName = (Symbol)denotationElement.getAttributeValue(NAME_, null); 
	return (attributeName.equals(SystemAttributeSymbols.NOTES_) || 
		attributeName.equals(VirtualAttributeSymbols.ITEM_STATUS_) || 
		attributeName.equals(VirtualAttributeSymbols.ITEM_NOTES_));
      }
      else 
	return false;
    }
    return false;
  }

  class StatusChangeAdapter implements ItemListener{
    @Override
    public void receivedInitialValues (ItemEvent e){
      try{
	update();
      }
      catch(G2AccessException ex){
	Trace.exception(ex);
      }
    }
    @Override
    public void itemModified (ItemEvent e){
      try{
	if (itemNotesModified(e))
	  update();
      }
      catch(G2AccessException ex){
	Trace.exception(ex);
      }
    }
    @Override
    public void itemDeleted(ItemEvent event){
      cleanup();
    }
  }
}
