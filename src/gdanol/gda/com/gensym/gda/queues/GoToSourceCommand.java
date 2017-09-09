package com.gensym.gda.queues;

import java.awt.*;
import javax.swing.*;
import java.awt.event.ActionEvent;
import com.gensym.message.Resource;
import com.gensym.util.Symbol;
import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2AccessException;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.core.UiApplication;
import com.gensym.dlg.WarningDialog;
import com.gensym.classes.UiClientSession;
import com.gensym.classes.modules.gqm.GqmQueue;
import com.gensym.classes.modules.gqm.GqmEntry;
import com.gensym.gda.queues.MessageBrowserTable;
import com.gensym.gda.queues.MessageBrowserTableModel;
import com.gensym.gda.queues.MessageBrowserMessageImpl;

public final class GoToSourceCommand extends AbstractCommand 
{
  public static final String GOTOSOURCE = "GoToSource"; 
      
  private static final String shortResource = "ShortResource";
  private static final String longResource = "LongResource";
  private static final String mnemonicResource = "MnemonicResource";
  private Resource i18n = Resource.getBundle ("com.gensym.gda.commands.Errors");
  private MessageBrowserTable table;
  private GqmQueue sourceQueue, targetQueue;
  private MessageBrowserTableModel tableModel;
  private JFrame detailFrame;
  private UiApplication app;
  private TwAccess cxn;
  
  public GoToSourceCommand (UiApplication app, TwAccess cxn, MessageBrowserTable table)
  {
    super (new CommandInformation[] { new CommandInformation (GOTOSOURCE, true, shortResource, longResource, "arrow.gif", 
							      null, null, true, mnemonicResource, null)});
    this.table = table;
    this.app = app;
    this.cxn = cxn;
    tableModel = table.getTableModel ();
  }

  public void actionPerformed (ActionEvent e)
  {
    String cmdKey = e.getActionCommand ();
    int i;
    
    if (cmdKey == null) 
      return;
    if (!isAvailable (cmdKey))
      return;
    int selectedRow = table.getSelectedRow ();
    if (selectedRow < 0)
      {
	new WarningDialog (ShowQueuesCommand.getFrame (table), "Warning", true, "No Item was Selected", null).setVisible (true);
	return;
      }
    
    if (cmdKey.equals (GOTOSOURCE))
      {
	try
	  {
	    GqmEntry entry =  (GqmEntry) ((MessageBrowserMessageImpl) (tableModel.getRow (selectedRow))).getMessage ();
	    UiClientSession client = cxn.getSession ();
	    cxn.callRPC (Symbol.intern ("GDLUISUP-GO-TO-ENTRY-SOURCE"), new Object [] {entry, client});
	  }
	catch (G2AccessException gae)    { System.err.println ("Unexpected Exception : " + gae); }
      }
  }
  
}
