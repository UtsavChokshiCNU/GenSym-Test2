package com.gensym.shell.commands;

import java.awt.event.ActionEvent;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.AbstractCommand;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.ntw.TwAccess;
import com.gensym.util.Symbol;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.shell.util.ContextChangedListener;
import com.gensym.shell.util.ContextChangedEvent;
import com.gensym.dlg.QuestionDialog;
import com.gensym.message.Resource;

 /** 
 * Command for actions upon a G2 connection, currently including shut-down.
 */
public class G2Commands extends AbstractCommand
{
  private ConnectionManager connectionManager;
  private ContextChangedAdapter contextChangedListener;  
  private TwAccess currentConnection;  
  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private static final String mnemonicResource = "MnemonicResource";    
  /** Command key to shut down G2. */  
  public static final String SHUT_DOWN_G2 = "ShutDownG2";
  private static Resource i18n = Resource.getBundle("com.gensym.shell.commands.CommandShortResource");


  /**
   *  Creates a G2Commands for a single connection application.
   */
  public G2Commands(TwAccess connection){
    super(new CommandInformation[]{
      new CommandInformation(SHUT_DOWN_G2, true,
			     shortResource, longResource,
			     "shutdown_g2.gif",
			     null, null, true,
			     mnemonicResource, null)});
    setConnection(connection);
  }

  /**
   *  Creates a G2Commands for a multiple connection application.
   */  
  public G2Commands(ConnectionManager connectionManager)
  {
    this(connectionManager.getCurrentConnection());        
    this.connectionManager = connectionManager;
    contextChangedListener = new ContextChangedAdapter();    
    connectionManager.addContextChangedListener(contextChangedListener);    
  }

  /**
   * Sets the current connection.  This command's actions act upon the current
   * connection.  Single connection application should use this method to
   * inform this command about changes in the current connection.
   */  
  public void setConnection(TwAccess connection){
    currentConnection = connection;
    updateAvailability();
  }

  class ConfirmShutDownDialog extends QuestionDialog {
    boolean confirmed = false;
    ConfirmShutDownDialog() {
      super(null, i18n.getString("ShutDownG2?"), true,
	    i18n.getString("AreYouSureYouWantToShutDownG2?"), null);
    }
    @Override
    protected void dispatchCallback (int code) {
      confirmed = (code == YES);      
      super.dispatchCallback(code);
    }
  }
  
  private void shutDownG2() {
    ConfirmShutDownDialog dlg = new ConfirmShutDownDialog();
    dlg.setVisible(true);
    if (dlg.confirmed)
    (new ShutDownG2Thread(currentConnection)).start();    
  }

  class ContextChangedAdapter implements ContextChangedListener{
    @Override
    public void currentConnectionChanged(ContextChangedEvent e){
      setConnection(e.getConnection());
    }
  }
  
  private void updateAvailability()
  {
    setAvailable(SHUT_DOWN_G2, currentConnection != null);//check if its running?
  }

  @Override
  protected void setAvailable(String cmdKey, boolean state) {
    super.setAvailable(cmdKey, state);
  }
  
  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (SHUT_DOWN_G2.equals(cmdKey)) 
      shutDownG2();
  }


  private static final Symbol
  G2_SHUTDOWN_G2_PROCESS_ = Symbol.intern ("G2-SHUTDOWN-G2-PROCESS"),
    REQUESTED_ = Symbol.intern ("REQUESTED");  
  class ShutDownG2Thread extends Thread {
    private TwAccess connection;
    ShutDownG2Thread(TwAccess connection) {
      this.connection = connection;
    }
    @Override
    public void run() {
      try {
	if (connection != null) {
	  connection.callRPC(G2_SHUTDOWN_G2_PROCESS_, new Object[] {REQUESTED_});
	}
      } catch (G2AccessException g2ae) {
	Trace.exception(g2ae);
      }
    }
  }
}
