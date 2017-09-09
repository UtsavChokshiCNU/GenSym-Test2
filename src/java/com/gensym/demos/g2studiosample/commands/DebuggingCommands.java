package com.gensym.demos.g2studiosample.commands;

import java.awt.event.ActionEvent;
import java.awt.Image;
import java.awt.Toolkit;
import java.util.Vector;
import java.awt.Component;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.util.KbModuleListener;
import com.gensym.ntw.util.KbEvent;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.ItemListener;
import com.gensym.util.ItemEvent;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.shell.util.ContextChangedListener;
import com.gensym.shell.util.ContextChangedEvent;
import com.gensym.classes.Item;
import com.gensym.classes.DebuggingParameters;
import com.gensym.classes.Kb;
import com.gensym.classes.Module;
import com.gensym.util.symbol.SystemAttributeSymbols;


public class DebuggingCommands extends AbstractCommand
{
  private Component comp;
  private ItemAdapter itemAdapter;
  private KbModuleListener moduleListener;  
  private DebuggingParameters debuggingParameters;
  private static final Symbol[] neededAttributes =
  {SystemAttributeSymbols.TRACING_AND_BREAKPOINTS_ENABLEDQ_,
   SystemAttributeSymbols.DISASSEMBLER_ENABLEDQ_};
  private ConnectionManager connectionManager;
  private Kb kb;
  private boolean disassemblerEnabled, debuggingEnabled;    
  private static final String shortResource = "DebuggingCommandShortResource";
  private static final String longResource = "DebuggingCommandShortResource";
  private ContextChangedAdapter contextChangedListener;
  public static final String DEBUGGING_ENABLED = "DebuggingEnabled";
  public static final String DISASSEMBLER_ENABLED = "DisassemblerEnabled";

  class ItemAdapter implements ItemListener {
    @Override
    public void itemModified(ItemEvent ie) {
      try {
	if (debuggingParameters != null) {
	  debuggingEnabled = debuggingParameters.getTracingAndBreakpointsEnabled();
	  disassemblerEnabled = debuggingParameters.getDisassemblerEnabled();
	}
	updateAvailability();	
      } catch (G2AccessException g2ae){
	Trace.exception(g2ae);
      }
    }
    @Override
    public void itemDeleted(ItemEvent ie) {
    }
    @Override
    public void receivedInitialValues(ItemEvent ie) {
      try {
	if (debuggingParameters != null) {
	  debuggingEnabled = debuggingParameters.getTracingAndBreakpointsEnabled();
	  disassemblerEnabled = debuggingParameters.getDisassemblerEnabled();
	}
	updateAvailability();
      } catch (G2AccessException g2ae){
	Trace.exception(g2ae);
      }
    }
  }
  
  public DebuggingCommands(ConnectionManager connectionManager)
  {
    super(new CommandInformation[]{
	new CommandInformation(DEBUGGING_ENABLED, true,
			       shortResource, longResource,
			       "debugging-mode.gif",
			       null,
			       Boolean.FALSE,
			       true),
	new CommandInformation(DISASSEMBLER_ENABLED, true,
			       shortResource, longResource,
			       "disassembler-mode.gif",
			       null,
			       Boolean.FALSE,
			       true)});
    itemAdapter = new ItemAdapter();
    moduleListener = new ModuleListener();
    this.connectionManager = connectionManager;
    setConnection(connectionManager.getCurrentConnection());    
    contextChangedListener = new ContextChangedAdapter();    
    connectionManager.addContextChangedListener(contextChangedListener);    
  }

  private void setTopLevelModuleForCurrentKb() {
    new Thread(new Runnable() {
      @Override
      public void run() {
	if (kb != null) {
	  try {
	    Module mod = kb.getTopLevelModule();
	    if (mod != null) {
	      setDebuggingParameters(mod.getDebuggingParameters());
	      return;
	    }
	  } catch (G2AccessException g2ae) {
	    Trace.exception(g2ae);
	  }
	}
	setDebuggingParameters(null);
      }}).start();
  }
  
  private void setDebuggingParameters(DebuggingParameters debuggingParameters) {
    if (this.debuggingParameters == debuggingParameters) {
      updateAvailability();
      return;
    }
    if (this.debuggingParameters != null) {
      try {
	this.debuggingParameters.removeItemListener(itemAdapter, neededAttributes);
      } catch (G2AccessException g2ae) {
	Trace.exception(g2ae);
      }
    }
    debuggingEnabled = false;
    disassemblerEnabled = false;
    this.debuggingParameters = debuggingParameters;
    if (debuggingParameters != null) {
      try {      
	debuggingParameters.addItemListener(itemAdapter, neededAttributes);
      } catch (G2AccessException g2ae) {
	Trace.exception(g2ae);
      }
    }
    updateAvailability();    
  }

  public void setConnection(TwAccess connection){
    try {
      if (kb != null)
	kb.removeKbModuleListener(moduleListener);
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
    if (connection != null)
      kb = connection.getKb();
    else
      kb = null;
    if (kb != null) {
      try {
	kb.addKbModuleListener(moduleListener);
	return;
      } catch (G2AccessException g2ae) {
	Trace.exception(g2ae);
	return;
      }
    } 
    setDebuggingParameters(null);
  }

  class ModuleListener implements KbModuleListener {
    @Override
    public void receivedInitialModules (KbEvent evt) { setTopLevelModuleForCurrentKb();}
    @Override
    public void moduleCreated (KbEvent evt) { setTopLevelModuleForCurrentKb();}
    @Override
    public void moduleDeleted (KbEvent evt) { setTopLevelModuleForCurrentKb();}
    @Override
    public void moduleNameChanged (KbEvent evt) {setTopLevelModuleForCurrentKb();}
    @Override
    public void moduleDependencyChanged (KbEvent evt) { setTopLevelModuleForCurrentKb();}
    @Override
    public void kbCleared (KbEvent evt) {setTopLevelModuleForCurrentKb();}
    @Override
    public void topLevelWorkspaceAdded(KbEvent evt) {}
    @Override
    public void topLevelWorkspaceDeleted(KbEvent evt) {}
  }
  
  
  /**
   * @undocumented
   */
  public void setComponentForDebuggingVisibility(Component comp) {
    this.comp = comp;
    if (comp != null) comp.setVisible(debuggingEnabled);
  }
  
  class ContextChangedAdapter implements ContextChangedListener{
    @Override
    public void currentConnectionChanged(ContextChangedEvent e){
      setConnection(e.getConnection());
    }
  }

  private void updateAvailability()
  {
    if (comp != null) comp.setVisible(debuggingEnabled);        
    setState(DEBUGGING_ENABLED, debuggingEnabled?Boolean.TRUE:Boolean.FALSE);
    setState(DISASSEMBLER_ENABLED, disassemblerEnabled?Boolean.TRUE:Boolean.FALSE);
    setAvailable(DEBUGGING_ENABLED, kb != null);
    setAvailable(DISASSEMBLER_ENABLED, kb != null);
  }

  @Override
  protected void setAvailable(String cmdKey, boolean state) {
    super.setAvailable(cmdKey, state);
  }
  
  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (debuggingParameters == null) return;
    try {
      if (DEBUGGING_ENABLED.equals(cmdKey)) 
	debuggingParameters.setTracingAndBreakpointsEnabled(!debuggingEnabled);
      else if (DISASSEMBLER_ENABLED.equals(cmdKey))
	debuggingParameters.setDisassemblerEnabled(!disassemblerEnabled);
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
  }
  
}
