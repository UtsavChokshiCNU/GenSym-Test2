package com.gensym.gda.queues;

import java.awt.Frame;
import java.awt.event.ActionEvent;
import com.gensym.message.Resource;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2AccessException;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.dlg.WarningDialog;
import com.gensym.core.UiApplication;
import com.gensym.classes.modules.gqm.GqmEntry;
import com.gensym.gda.queues.MessageBrowserTable;
import com.gensym.gda.queues.MessageBrowserTableModel;
import com.gensym.gda.queues.MessageBrowserMessageImpl;

public final class RemoveSelectedCommand extends AbstractCommand 
{
    public static final String REMOVESEL = "RemoveSelected"; 
      
    private static final String shortResource = "ShortResource";
    private static final String longResource = "LongResource";
    private static final String mnemonicResource = "MnemonicResource";
    private Resource i18n = Resource.getBundle ("com.gensym.gda.commands.Errors");
    private MessageBrowserTable table;
    private MessageBrowserTableModel tableModel;
    private UiApplication app;
    private TwAccess cxn;
  
    public RemoveSelectedCommand (UiApplication app, TwAccess cxn, MessageBrowserTable table)
    {
        super (new CommandInformation[] {
        new CommandInformation (REMOVESEL, true, shortResource, longResource, "removesel.gif", 
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
        GqmEntry entry;
        
        if (cmdKey == null) 
            return;
        if (!isAvailable (cmdKey))
            return;
        int selectedRows [] = table.getSelectedRows ();
        if (selectedRows.length == 0)
        {
            new WarningDialog (ShowQueuesCommand.getFrame (table), "Warning", true, "No Item was Selected", null).setVisible (true);
            return;
        }
            
        if (cmdKey.equals (REMOVESEL))
        {
            try
            {
                MessageBrowserMessageImpl [] rowsForDelete = new MessageBrowserMessageImpl [selectedRows.length];
                for (i = 0; i < selectedRows.length; i++) 
                {
                    rowsForDelete[i] = (MessageBrowserMessageImpl) tableModel.getRow (selectedRows[i]);
                }
            
               Sequence entrySeq = new Sequence (selectedRows.length);
            
                for (i = 0; i < selectedRows.length; i++) 
               {
                    entry = (GqmEntry) rowsForDelete[i].getMessage ();
                    entrySeq.addElement (entry);
                }

                cxn.callRPC (Symbol.intern ("GDL-RPC-REMOVE-ITEMS"), new Object [] {table.getQueueName (), entrySeq});
                table.clearSelection ();
                // ((MessageBrowserTableModel) tableModel).fireChange ();
            }
            catch (G2AccessException gae)    { System.err.println ("Unexpected Exception : " + gae); }
        }
    }

}
