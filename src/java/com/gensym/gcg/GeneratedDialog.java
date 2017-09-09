package com.gensym.gcg;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.util.Locale;
import javax.swing.JDialog;

import com.gensym.classes.Block;
import com.gensym.classes.ClassDefinition;
import com.gensym.classes.Definition;
import com.gensym.classes.G2Definition;
import com.gensym.classes.Item;
import com.gensym.controls.DialogCommand;
import com.gensym.controls.ItemProxy;
import com.gensym.dlg.CommandConstants;
import com.gensym.dlg.ErrorDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.QuestionDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.dlgruntime.DialogCommandListener;
import com.gensym.dlgruntime.DialogCommandEvent;
import com.gensym.dlgruntime.SingleItemEditor;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2CommunicationErrorEvent;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.jgi.G2ConnectionListener;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.util.ClassManager;
import com.gensym.util.DefinitionListener;
import com.gensym.util.DefinitionEvent;
import com.gensym.util.ItemEvent;
import com.gensym.util.ItemListener;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.AttributeTypeSpecificationSymbols;

class GeneratedDialog extends JDialog implements DefinitionListener, DialogCommandListener, ItemListener, G2ConnectionListener, WindowListener, SingleItemEditor{

  private static final Resource i18n = Resource.getBundle("com.gensym.gcg.UiLabels");

  private TwAccess connection;
  private Item item;
  private ItemProxy itemProxy;
  private DialogCommand dialogCommand;
  private G2Definition definition;
  private Frame aFrame;
  private Locale locale;
  private boolean needUpdating;
  private boolean isClassNameChanged;
						     
  GeneratedDialog(Frame frame, TwAccess connection, ItemProxy itemProxy, DialogCommand dialogCommand, Container c, boolean live, Locale locale ) throws G2AccessException{
    super(frame, "", false /*modal*/);
    this.aFrame = frame;
    this.connection = connection;
    this.item = itemProxy.getProxy();
    this.itemProxy = itemProxy;
    this.dialogCommand = dialogCommand;
    this.locale = locale;
    
    setupTitle();
    
    dialogCommand.addDialogCommandListener(this);
    if (live){
      item.addItemListener(this);
      ClassManager classManager = connection.getClassManager();
      definition = classManager.getDefinition(item.getG2ClassName());
      if (definition instanceof Definition)
	((Definition)definition).addDefinitionListener(this);
    }
    addWindowListener(this);
    connection.addG2ConnectionListener(this);
    
    getContentPane().setLayout(new BorderLayout());
    getContentPane().add(c, BorderLayout.CENTER);
  }

  @Override
  public DialogCommand getDialogCommand(){
    return dialogCommand;
  }
  
  @Override
  public ItemProxy getProxy(){
    return itemProxy;
  }

  private static final int MINIMUM_WIDTH = 200;

  @Override
  public Dimension getPreferredSize(){
    Dimension size = super.getPreferredSize();
    if (size.width < MINIMUM_WIDTH)
      size.width = MINIMUM_WIDTH;
    return size;
  }
  
  private void setupTitle(){
    Symbol className = null;
    try{
      className = item.getG2ClassName();
      Object namesObject;
      Block block = (Block) item;
      if (block instanceof ClassDefinition){
	namesObject = ((ClassDefinition)block).getClassName ();
	if (namesObject.equals (AttributeTypeSpecificationSymbols.NONE_))
	  namesObject = null;
      }
      else
	namesObject = block.getNames();
      
      if (namesObject == null)
	setTitle(i18n.format("unnamedItemDialogTitle", className));
      else if (namesObject instanceof Symbol)
	setTitle(i18n.format("namedItemDialogTitle", namesObject, className));
      else if (namesObject instanceof Sequence)
	setTitle(i18n.format("namedItemDialogTitle", ((Sequence)namesObject).elementAt(0),className));
    } catch (G2AccessException e){
      // Some items, like procedures, do not have names, in the normal
      // fashion.  In this case, go with the default.
      setTitle(i18n.format("unnamedItemDialogTitle", className));
    }
  }

  //Post a question dialog when items in the dialog get changed from G2 - FY 01/31/00
  private void refreshDlg() {
        QuestionDialog dlg = new QuestionDialog(aFrame, i18n.format("questionDlgTitle", null),
                                                false, i18n.format("questionDlgMsg", null),
                                                new QuestionDialogClient());
        dlg.setVisible(true);

  }

  //Post an error dialog when there is an error rebuilding the dialog from G2 - FY 02/02/00
  private void postErrorDlg(String msg) {
        ErrorDialog dlg = new ErrorDialog(aFrame, i18n.format("errorDlgTitle", null),
                                          false, msg, new ErrorDialogClient());
  }

  @Override
  public void dialogChangesFlushed (DialogCommandEvent event){}
  @Override
  public void dialogLaunched(DialogCommandEvent event){}
  @Override
  public void dialogShutdown(DialogCommandEvent event){
    if (item == null){
    	return;
    }
    try{
      item.removeItemListener(this);
    }
    catch(G2AccessException ex){
      Trace.exception(ex);
    }
    item = null;
    connection.removeG2ConnectionListener(this);
    connection = null;
    dialogCommand.removeDialogCommandListener(this);
    try{
      if (definition instanceof Definition)
	((Definition)definition).removeDefinitionListener(this);
    }
    catch(G2AccessException ex){
      Trace.exception(ex);
    }
    definition = null;
    setVisible(false);
    dispose();
  }
  
  @Override
  public void receivedInitialValues (ItemEvent e){}
  @Override
  public void itemModified (ItemEvent e){}
  @Override
  public void itemDeleted (ItemEvent e){
    if (item != null)   //Dialog is closed if item is null
      dialogCommand.close();
  }
  
  @Override
  public void staticAttributeChanged (DefinitionEvent e){}
  @Override
  public void directSuperiorClassesChanged (DefinitionEvent e){
  // will get a classInheritancePathChanged event also,
  // so don't need to handle this one explicitly.
  }

  @Override
  public void classInheritancePathChanged (DefinitionEvent e){
         if (!needUpdating && !isClassNameChanged) {
           needUpdating = true;
           isClassNameChanged = false;
           refreshDlg();
        }
  }

  @Override
  public void deleted (DefinitionEvent e){
  // dialog is closed for us already by this time.
   }

  @Override
  public void classSpecificAttributesChanged (DefinitionEvent e){
        if (!needUpdating) {
          needUpdating = true;
          refreshDlg();
        }
  }

  @Override
  public void classNameChanged (DefinitionEvent e){
    setupTitle();
    isClassNameChanged = true;
  }
  
  @Override
  public void windowActivated(WindowEvent e){}
  @Override
  public void windowClosed(WindowEvent e){
     if (item != null)  //dialog is closed if item is null
      dialogCommand.close();
 }
  @Override
  public void windowDeactivated(WindowEvent e){}
  @Override
  public void windowDeiconified(WindowEvent e){}
  @Override
  public void windowIconified(WindowEvent e){}
  @Override
  public void windowOpened(WindowEvent e){}
  @Override
  public void windowClosing(WindowEvent event){
    if (item != null)   //dialog is closed if item is null
      dialogCommand.close();
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
    if (item != null)   //dialog is closed if item is null
      dialogCommand.close();
  }

  //Dialog client for question dialog  - FY 01/31/00
  class QuestionDialogClient implements StandardDialogClient {
    @Override
    public void dialogDismissed (StandardDialog dlg, int code) {

          switch (code) {
            case CommandConstants.YES:    //Users hit YES button
              dispose();
              try {
                connection.getDialogManager().editItem(aFrame, item,
                                  connection.getUserMode(), locale);
                }
                catch (G2AccessException ex){
                  Trace.exception(ex);
                  postErrorDlg(ex.toString());
                }
                catch (java.net.MalformedURLException murle) {
                  Trace.exception(murle);
                  postErrorDlg(murle.toString());
                }
                catch (com.gensym.dlgruntime.ResourceInstantiationException rie) {
                  Trace.exception(rie);
                  postErrorDlg(rie.toString());
                }

                break;

            case CommandConstants.NO:     //Users hit NO button
              dispose();
              break;

            default:        //Users hit CANCEL button
              break;
          }
    }
  }

    //Dialog client for error dialog - FY 02/02/00
    class ErrorDialogClient implements StandardDialogClient {
      @Override
      public void dialogDismissed (StandardDialog dlg, int code) {
        dispose();
    }
  }
}


