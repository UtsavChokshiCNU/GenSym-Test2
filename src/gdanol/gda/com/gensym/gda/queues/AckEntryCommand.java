package com.gensym.gda.queues;

import java.awt.*;
import javax.swing.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.event.ActionEvent;
import com.gensym.message.Resource;
import com.gensym.util.Symbol;
import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2AccessException;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.core.UiApplication;
import com.gensym.dlg.WarningDialog;
import com.gensym.classes.modules.gda.GdaAlarmEntry;
import com.gensym.classes.UiClientSession;
import com.gensym.gda.queues.MessageBrowserTable;
import com.gensym.gda.queues.MessageBrowserTableModel;
import com.gensym.gda.queues.MessageBrowserMessageImpl;

public final class AckEntryCommand extends AbstractCommand 
{
    public static final String ACKENTRY = "AcknowledgeEntry"; 
    private static final String shortResource = "ShortResource";
    private static final String longResource = "LongResource";
    private static final String mnemonicResource = "MnemonicResource";
    private Resource i18n = Resource.getBundle ("com.gensym.gda.commands.Errors");
    private MessageBrowserTable table;
    private MessageBrowserTableModel tableModel;
    private JFrame detailFrame;
    private UiApplication app;
    private TwAccess cxn;
  
    public AckEntryCommand (UiApplication app, TwAccess cxn, MessageBrowserTable table)
    {
        super (new CommandInformation[] {
        new CommandInformation (ACKENTRY, true, shortResource, longResource, "ack.gif", 
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
          
        if (cmdKey.equals (ACKENTRY))
        {
             try
            {
                GdaAlarmEntry entry =  (GdaAlarmEntry) ((MessageBrowserMessageImpl) (tableModel.getRow (selectedRow))).getMessage ();
                UiClientSession client = cxn.getSession ();
                cxn.callRPC (Symbol.intern ("GDA-RPC-ACKNOWLEDGE-ALARM-ENTRY"), new Object [] {entry, client});
            }
            catch (G2AccessException gae)    { System.err.println ("Unexpected Exception : " + gae); }
        }
    }

}
