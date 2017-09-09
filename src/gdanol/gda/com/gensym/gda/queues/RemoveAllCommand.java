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

public final class RemoveAllCommand extends AbstractCommand 
{
    public static final String REMOVEALL = "RemoveAll"; 
      
    private static final String shortResource = "ShortResource";
    private static final String longResource = "LongResource";
    private static final String mnemonicResource = "MnemonicResource";
    private Resource i18n = Resource.getBundle ("com.gensym.gda.commands.Errors");
    private MessageBrowserTable table;
    private MessageBrowserTableModel tableModel;
    private UiApplication app;
    private TwAccess cxn;
  
    public RemoveAllCommand (UiApplication app, TwAccess cxn, MessageBrowserTable table)
    {
        super (new CommandInformation[] {
        new CommandInformation (REMOVEALL, true, shortResource, longResource, "removeall.gif", 
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
            
        if (cmdKey.equals (REMOVEALL))
        {
            int visibleEntryCount = tableModel.getDataSize ();            
            MessageBrowserMessageImpl [] rowsToRemove = new MessageBrowserMessageImpl [visibleEntryCount];

            if (visibleEntryCount == 0)
            {
                new WarningDialog (ShowQueuesCommand.getFrame (table), "Warning", true, "No Items to Remove", null).setVisible (true);
                return;
            }
                 
            for (i = 0; i < visibleEntryCount; i++) 
            {
                rowsToRemove[i] = (MessageBrowserMessageImpl) tableModel.getRow (i);
            }
            
            Sequence entrySeq = new Sequence (visibleEntryCount);
            
            for (i = 0; i < rowsToRemove.length; i++) 
            {
                entry = (GqmEntry) rowsToRemove[i].getMessage ();
                entrySeq.addElement (entry);  
            }
            
            try   { cxn.callRPC (Symbol.intern ("GDL-RPC-REMOVE-ITEMS"), new Object [] {table.getQueueName (), entrySeq}); }
            catch (G2AccessException gae)    { System.err.println ("Unexpected Exception : " + gae); }
        }
    }

}
