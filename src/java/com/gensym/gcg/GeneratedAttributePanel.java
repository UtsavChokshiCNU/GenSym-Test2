package com.gensym.gcg;

import java.awt.Component;
import java.awt.Container;
import java.awt.BorderLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import com.gensym.classes.Item;
import com.gensym.controls.AttributeEditor;
import com.gensym.controls.DialogCommand;
import com.gensym.controls.ItemProxy;
import com.gensym.dlgruntime.DialogCommandListener;
import com.gensym.dlgruntime.DialogCommandEvent;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2CommunicationErrorEvent;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.jgi.G2ConnectionListener;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.util.ItemEvent;
import com.gensym.util.ItemListener;
import com.gensym.util.NoSuchAttributeException;
import java.awt.Color;

class GeneratedAttributePanel extends JPanel implements ItemListener, DialogCommandListener, G2ConnectionListener{

  private static final int Y_INSET = 3;
  private static final int X_INSET = 3;
  private static final Color DEFAULT_NOTES_COLOR = java.awt.Color.red;  

  private TwAccess connection;
  private Item item;
  private DialogCommand dialogCommand;
  private JTabbedPane tabThing = new JTabbedPane();
  
  private boolean hasNotesPanel = false;
  private String notesTabTitle = null;
  private JScrollPane notesPanel = null;
  
  GeneratedAttributePanel(TwAccess connection, ItemProxy itemProxy, DialogCommand dialogCommand, G2AttributeGroup[] groups, boolean live) throws G2AccessException{
    this.connection = connection;
    this.item = itemProxy.getProxy();
    this.dialogCommand = dialogCommand;
    dialogCommand.addDialogCommandListener(this);
    setLayout(new BorderLayout());
    add(tabThing, BorderLayout.CENTER);
    
    GridBagConstraints labelConstraints = new GridBagConstraints();
    labelConstraints.anchor = GridBagConstraints.EAST;
    labelConstraints.insets = new Insets(Y_INSET, X_INSET, Y_INSET, X_INSET);
    labelConstraints.weighty = 1.0;
    labelConstraints.gridx = 0;
    GridBagConstraints editorConstraints = new GridBagConstraints();
    editorConstraints.fill = GridBagConstraints.BOTH;
    editorConstraints.insets = new Insets(Y_INSET, X_INSET, Y_INSET, X_INSET);
    editorConstraints.weightx = 1.0;
    editorConstraints.weighty = 1.0;
    editorConstraints.gridx = 1;
    GridBagConstraints buttonConstraints = new GridBagConstraints();
    buttonConstraints.anchor = GridBagConstraints.SOUTHWEST;
    buttonConstraints.gridwidth = GridBagConstraints.REMAINDER;
    buttonConstraints.insets = new Insets(Y_INSET, 0, Y_INSET, X_INSET);
    buttonConstraints.weighty = 1.0;
    buttonConstraints.gridx = 2;
    
    try{
      itemProxy.download();
    }
    catch(NoSuchAttributeException ex){
      Trace.exception(ex);
    }

    for (int i=0; i<groups.length; i++){
      String label = groups[i].getName();
      Color labelColor = null;
      JPanel page = new JPanel();
      JScrollPane scrollPane = new JScrollPane(page);
      GridBagLayout gridBag = new GridBagLayout();
      page.setLayout(gridBag);
      G2AttributeEditor[] editorList = groups[i].getEditors();
      int numberOfEditors = editorList.length;
      boolean okToAddPanel = (numberOfEditors > 0);
      for (int j=0; j<numberOfEditors; j++){
	G2AttributeEditor g2AttributeEditor = editorList[j];
	Component editorLabel = g2AttributeEditor.getLabel();
	AttributeEditor editor = g2AttributeEditor.getEditor();
	if (editor instanceof Component){
	  if (editor instanceof NotesTextArea){
	    NotesTextArea notesEditor = (NotesTextArea)editor;
	    notesEditor.setNotesDisplayer(new OptionalComponentDisplayer() {
	      @Override
	      public void hideComponent(){
		if (hasNotesPanel){
		  hasNotesPanel = false;
		  int index = tabThing.indexOfComponent(notesPanel);
		  if (index >= 0)
		    tabThing.removeTabAt(index);
		}
	      }
	      
	      @Override
	      public void showComponent(){
		if (!hasNotesPanel){
		  hasNotesPanel = true;
		  tabThing.addTab(notesTabTitle, notesPanel);
		  tabThing.setForegroundAt(tabThing.indexOfComponent(notesPanel),
					   DEFAULT_NOTES_COLOR);
		}
	      }
	    });
	    notesTabTitle = label;
	    notesPanel = scrollPane;
	    hasNotesPanel = notesEditor.isInteresting();
	    okToAddPanel = hasNotesPanel;
	    labelColor = DEFAULT_NOTES_COLOR;
	  }
	  labelConstraints.gridy = j;
	  editorConstraints.gridy = j;
	  buttonConstraints.gridy = j;
	  if (editorLabel != null)
	    page.add(editorLabel, labelConstraints);
	  
	  page.add((Component)editor, editorConstraints);
	  if (editor instanceof EditedBySubDialog)
	    page.add(new SubDialogLauncher((EditedBySubDialog)editor), buttonConstraints);	  
	  
	}
      }
      if (okToAddPanel) {
	tabThing.addTab(label, scrollPane);
	if (labelColor != null)
	  tabThing.setForegroundAt(tabThing.indexOfComponent(scrollPane), labelColor);
      }
    }
    
    if (live){
      try{
	item.addItemListener(this);
      } catch(G2AccessException e){
	Trace.exception(e);
      }
    }
  }

  @Override
  public void receivedInitialValues (ItemEvent e){}
  @Override
  public void itemModified(ItemEvent e){}
  @Override
  public void itemDeleted (ItemEvent e){
    disablePanel();
    cleanup();
  }

  private void disablePanel(){
    for (int i=0; i<tabThing.getTabCount(); i++){
      Container c = (Container)tabThing.getComponentAt(i);
      Component[] components = c.getComponents();
      for (int j=0; j<components.length; j++)
	components[j].setEnabled(false);
    }
  }
  
  private void cleanup(){
    if (item == null) {
    	return;
    }
    try{
      item.removeItemListener(this);
    }
    catch(G2AccessException ex){
      Trace.exception(ex);
    }
    item = null;
    dialogCommand.removeDialogCommandListener(this);
    dialogCommand = null;
  }
  
  @Override
  public void dialogChangesFlushed (DialogCommandEvent event){}
  @Override
  public void dialogLaunched(DialogCommandEvent event){}
  @Override
  public void dialogShutdown(DialogCommandEvent event){
    cleanup();
  }

  @Override
  public void g2IsPaused(G2ConnectionEvent event){}
  @Override
  public void g2IsResumed(G2ConnectionEvent event){}
  @Override
  public void g2IsReset(G2ConnectionEvent event){}
  @Override
  public void g2IsStarted(G2ConnectionEvent event){}
  @Override
  public void g2ConnectionInitialized(G2ConnectionEvent event){}
  @Override
  public void g2MessageReceived(G2ConnectionEvent event){}
  @Override
  public void communicationError(G2CommunicationErrorEvent error_event){}
  @Override
  public void readBlockage(G2ConnectionEvent event){}
  @Override
  public void writeBlockage(G2ConnectionEvent event){}
  @Override
  public void g2ConnectionClosed(G2ConnectionEvent event){
    disablePanel();
    cleanup();
  }
}
