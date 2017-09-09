package com.gensym.demos.g2studiosample.commands;

import java.awt.event.*;
import com.gensym.ui.*;
import com.gensym.mdi.*;
import com.gensym.shell.util.*;
import com.gensym.ntw.TwAccess;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2ConnectionAdapter;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.message.Trace;
import java.awt.Frame;
import javax.swing.JFrame;
import java.awt.Image;
import java.awt.Toolkit;
import java.util.Vector;
import com.gensym.shell.util.ContextChangedListener;
import com.gensym.shell.util.ContextChangedEvent;
import com.gensym.ntw.util.PackagePreparationListener;
import com.gensym.ntw.util.PackagePreparationEvent;
import com.gensym.classes.Item;

public class PackagePreparationCommands extends AbstractStructuredCommand
{
  private MDIFrame frame;
  private ConnectionManager connectionManager;
  private TwAccess currentConnection;
  private boolean isPPMode, isSimMode; 
  private static final Symbol
  G2_SET_PACKAGE_PREPARATION_MODE_ = Symbol.intern ("G2-SET-PACKAGE-PREPARATION-MODE"),
    G2_GET_PACKAGE_PREPARATION_MODE_ = Symbol.intern ("G2-GET-PACKAGE-PREPARATION-MODE"),
    G2_SET_SIMULATE_PROPRIETARY_MODE_ = Symbol.intern ("G2-SET-SIMULATE-PROPRIETARY-MODE"),
    G2_GET_SIMULATE_PROPRIETARY_MODE_ = Symbol.intern ("G2-GET-SIMULATE-PROPRIETARY-MODE"),
    G2_STRIP_ALL_TEXTS_ = Symbol.intern ("G2-STRIP-ALL-TEXTS"),
    G2_MAKE_KB_PROPRIETARY_ = Symbol.intern ("G2-MAKE-KB-PROPRIETARY"),
    G2_FLUSH_ALL_CHANGE_LOGS_ = Symbol.intern ("G2-FLUSH-ALL-CHANGE-LOGS");    
  
  private static final String shortResource = "PackagePreparationCommandShortResource";
  private static final String longResource = "PackagePreparationCommandShortResource";
  public static final String PACKAGE_PREPARATION_MODE = "PackagePreparationMode";
  public static final String SIMULATE_PROPRIETARY_MODE = "SimulateProprietaryMode";
  public static final String STRIP_TEXTS_NOW = "StripTextsNow";
  public static final String FLUSH_CHANGE_LOG_FOR_ENTIRE_KB = "FlushChangeLogForEntireKb";
  public static final String MAKE_WORKSPACES_PROPRIETARY_NOW = "MakeWorkspacesProprietaryNow";
  public static final String PACKAGE_PREPARATION_TOOLS = "PackagePreparationTools";
  
  private PackagePreparationAdapter packagePreparationAdapter;
  private CxnAdapter cxnAdapter;
  private ContextChangedAdapter contextChangedListener;
  
  public PackagePreparationCommands(MDIFrame frame,
				    ConnectionManager connectionManager)
  {
    super(new CommandInformation[]{
      new CommandInformation(PACKAGE_PREPARATION_MODE, true,
			     shortResource, longResource,
			     "package-preparation.gif",
			     null,
			     Boolean.FALSE,
			     true),
	new CommandInformation(SIMULATE_PROPRIETARY_MODE, true,
			       shortResource, longResource,
			       "lock.gif",
			       null,
			       Boolean.FALSE,
			       true),
	new SubCommandInformation(PACKAGE_PREPARATION_TOOLS, true,
				  shortResource, longResource,
				  null,//gif
				  null,
				  null,
				  null,
				  new CommandInformation[] {
	  new CommandInformation(STRIP_TEXTS_NOW,true,
				 shortResource, longResource,
				 "strip-text.gif",
				 null, null, true),
	    new CommandInformation(FLUSH_CHANGE_LOG_FOR_ENTIRE_KB, true,
				   shortResource, longResource,
				   "flush-change-log.gif",
				   null, null, true),
	    new CommandInformation(MAKE_WORKSPACES_PROPRIETARY_NOW, true,
				   shortResource, longResource,
				   "make-workspaces-proprietary.gif",
				   null, null, true)})});

    this.frame = frame;
    this.connectionManager = connectionManager;
    packagePreparationAdapter = new PackagePreparationAdapter();
    cxnAdapter = new CxnAdapter();
    setConnection(connectionManager.getCurrentConnection());    
    contextChangedListener = new ContextChangedAdapter();    
    connectionManager.addContextChangedListener(contextChangedListener);    
  }

  private static Boolean isPPMode(TwAccess connection) {
    try {
      return (Boolean)connection.callRPC(G2_GET_PACKAGE_PREPARATION_MODE_,
					 new Object[] {});
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
      return Boolean.FALSE;
    }    
  }
  
  private static Boolean isSimMode(TwAccess connection) {
    try {
      return (Boolean)connection.callRPC(G2_GET_SIMULATE_PROPRIETARY_MODE_,
					 new Object[] {});
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
      return Boolean.FALSE;
    }          
  }
  
  public void setConnection(TwAccess connection){
    //stop listening to old current connection
    if (currentConnection != null) {
      currentConnection.removePackagePreparationListener(packagePreparationAdapter);
      currentConnection.removeG2ConnectionListener(cxnAdapter);
    }
    //set new current connection
    currentConnection = connection;
    //start listening to new current connection
    if (currentConnection != null) {
      currentConnection.addPackagePreparationListener(packagePreparationAdapter);
      currentConnection.addG2ConnectionListener(cxnAdapter);
      isPPMode = isPPMode(currentConnection).booleanValue();
      isSimMode = isSimMode(currentConnection).booleanValue();
    }  
    updateAvailability();
  }

  class ContextChangedAdapter implements ContextChangedListener{
    @Override
    public void currentConnectionChanged(ContextChangedEvent e){
      setConnection(e.getConnection());
    }
  }

  class CxnAdapter extends G2ConnectionAdapter {
    private void setCommandsAvailable(boolean avail) {
      setAvailable(STRIP_TEXTS_NOW, avail);
      setAvailable(MAKE_WORKSPACES_PROPRIETARY_NOW, avail);
    }
    @Override
    public void g2IsPaused(G2ConnectionEvent e) {
      setCommandsAvailable(true);
    }
    @Override
    public void g2IsReset(G2ConnectionEvent e) {
      setCommandsAvailable(true);
    }
    @Override
    public void g2IsResumed(G2ConnectionEvent e) {
      setCommandsAvailable(false);
    }
    @Override
    public void g2IsStarted(G2ConnectionEvent e) {
      setCommandsAvailable(false);
    }
  }
  
  private Image grayLock =
  Toolkit.getDefaultToolkit().getImage(getClass().getResource("unlocked.gif"));
  private Image redLock =
  Toolkit.getDefaultToolkit().getImage(getClass().getResource("red-lock.gif"));    
  private void updateAvailability()
  {
    if (isSimMode)
      setIcon(SIMULATE_PROPRIETARY_MODE,Command.SMALL_ICON, redLock);
    else
      setIcon(SIMULATE_PROPRIETARY_MODE,Command.SMALL_ICON, grayLock);
    if (comp != null) comp.setVisible(isPPMode);    
    setState(PACKAGE_PREPARATION_MODE, isPPMode?Boolean.TRUE:Boolean.FALSE);
    setState(SIMULATE_PROPRIETARY_MODE, isSimMode?Boolean.TRUE:Boolean.FALSE);
    setAvailable(PACKAGE_PREPARATION_MODE, currentConnection != null);
    setAvailable(SIMULATE_PROPRIETARY_MODE, currentConnection != null);
    setAvailable(STRIP_TEXTS_NOW, currentConnection != null && isPPMode);
    setAvailable(MAKE_WORKSPACES_PROPRIETARY_NOW, currentConnection != null && isPPMode);
    setAvailable(FLUSH_CHANGE_LOG_FOR_ENTIRE_KB, currentConnection != null && isPPMode);
  }

  private java.awt.Component comp;
  /**
   * @undocumented
   */
  public void setComponentForPPVisibility(java.awt.Component comp) {
    this.comp = comp;
    if (comp != null) comp.setVisible(isPPMode);
  }

  class PackagePreparationAdapter implements PackagePreparationListener {
    @Override
    public void enterPackagePreparationMode(PackagePreparationEvent evt) {
      isPPMode = true;
      updateAvailability();
    }
    @Override
    public void leavePackagePreparationMode(PackagePreparationEvent evt) {
      isPPMode = false;
      updateAvailability();      
    }
    @Override
    public void enterSimulateProprietaryMode(PackagePreparationEvent evt) {
      isSimMode = true;
      updateAvailability();            
    }
    @Override
    public void leaveSimulateProprietaryMode(PackagePreparationEvent evt) {
      isSimMode = false;
      updateAvailability();            
    }
  }
  
  @Override
  protected void setAvailable(String cmdKey, boolean state) {
    super.setAvailable(cmdKey, state);
  }
  
  private void setPackagePreparationMode(Boolean state) {
    if (state.booleanValue()) {
      QuestionDialog dlg = new QuestionDialog(frame,
					      "Enter Package Preparation mode?",
					      true,
					      "Enter Package Preparation mode? \n(This will add options to menus that allow for potentially dangerous and irreversible changes to the KB.)",
					      null);
      dlg.setVisible(true);
      if (dlg.wasCancelled()) {
	setState(PACKAGE_PREPARATION_MODE, Boolean.TRUE);	
	setState(PACKAGE_PREPARATION_MODE, Boolean.FALSE);
	return;
      }
    }
    G2Access currentConnection = connectionManager.getCurrentConnection();
    try {
      if (currentConnection != null) {
	currentConnection.callRPC(G2_SET_PACKAGE_PREPARATION_MODE_, new Object[] {state});
      }
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }        
  }
    
  private void setSimulateProprietaryMode(Boolean state) {
    G2Access currentConnection = connectionManager.getCurrentConnection();
    try {
      if (currentConnection != null) {
	currentConnection.callRPC(G2_SET_SIMULATE_PROPRIETARY_MODE_, new Object[] {state});
      }
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }        
  }
    
  private void stripTextsNow() {
    QuestionDialog dlg = new QuestionDialog(frame,
					    "Strip texts now?",
					    true,
					    "Strip texts now? \n(This will permanently remove most of the text associated with all items that have been marked to be stripped of their text.  These changes will be irreversible.)",
					      null);
    dlg.setVisible(true);
    if (dlg.wasCancelled())
      return;
    G2Access currentConnection = connectionManager.getCurrentConnection();
    try {
      if (currentConnection != null) {
	currentConnection.callRPC(G2_STRIP_ALL_TEXTS_, new Object[] {});
      }
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }                
  }

  private void makeWorkspacesProprietaryNow() {
    QuestionDialog dlg = new QuestionDialog(frame,
					    "Make workspaces in this KB proprietary now?",
					    true,
					    "Make workspaces in this KB proprietary now? \n(This will cause workspaces that have been given a potential proprietary package to become permanently proprietary to those packages and thus severely restricted in their uses.  Once that has been done, this KB, or any KB that has merged in those workspaces, will only be allowed to execute with special authorization codes obtained through Gensym Corporation.  These changes will be irreversible.)",
					      null);
    dlg.setVisible(true);
    if (dlg.wasCancelled())
      return;    
    G2Access currentConnection = connectionManager.getCurrentConnection();
    try {
      if (currentConnection != null) {
	currentConnection.callRPC(G2_MAKE_KB_PROPRIETARY_, new Object[] {});
      }
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }                
  }

  private void flushChangeLogForEntireKb() {
    QuestionDialog dlg = new QuestionDialog(frame,
					    "Flush change log for entire KB?",
					    true,
					    "Flush change log for entire KB?",
					    null);
    dlg.setVisible(true);
    if (dlg.wasCancelled())
      return;        
    G2Access currentConnection = connectionManager.getCurrentConnection();
    try {
      if (currentConnection != null) {
	currentConnection.callRPC(G2_FLUSH_ALL_CHANGE_LOGS_, new Object[] {});
      }
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }                
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (PACKAGE_PREPARATION_MODE.equals(cmdKey)) {
      setPackagePreparationMode(isPPMode?Boolean.FALSE:Boolean.TRUE);
    } else if (SIMULATE_PROPRIETARY_MODE.equals(cmdKey)) {
      setSimulateProprietaryMode(isSimMode?Boolean.FALSE:Boolean.TRUE);
    } else if (STRIP_TEXTS_NOW.equals(cmdKey))
      stripTextsNow();
    else if (MAKE_WORKSPACES_PROPRIETARY_NOW.equals(cmdKey))
      makeWorkspacesProprietaryNow();
    else if (FLUSH_CHANGE_LOG_FOR_ENTIRE_KB.equals(cmdKey))
      flushChangeLogForEntireKb();
  }
    
}
class QuestionDialog extends com.gensym.dlg.QuestionDialog {
  private int reasonForCallback;
  public QuestionDialog (Frame   frame,
			 String  title,
			 boolean isModal,
			 String  message,
			 com.gensym.dlg.StandardDialogClient client) {
    super(frame, title, isModal, message, client);
  }
  @Override
  protected void dispatchCallback (int code) {
    reasonForCallback = code;
    super.dispatchCallback(code);
  }  
  @Override
  public boolean wasCancelled() {
    return (super.wasCancelled() || reasonForCallback == NO);
  }
}
