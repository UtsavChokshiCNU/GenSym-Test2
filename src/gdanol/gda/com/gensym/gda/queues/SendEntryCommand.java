package com.gensym.gda.queues;

import java.awt.Frame;
import java.awt.event.ActionEvent;
import com.gensym.core.UiApplication;
import com.gensym.message.Resource;
import com.gensym.util.Symbol;
import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2AccessException;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.dlg.WarningDialog;
import com.gensym.classes.modules.gqm.GqmQueue;
import com.gensym.classes.modules.gqm.GqmEntry;
import com.gensym.gda.queues.MessageBrowserTable;
import com.gensym.gda.queues.MessageBrowserTableModel;
import com.gensym.gda.queues.MessageBrowserMessageImpl;

public final class SendEntryCommand extends AbstractCommand 
{
    public static final String SENDENTRY = "SendEntry"; 
      
    private static final String shortResource = "ShortResource";
    private static final String longResource = "LongResource";
    private static final String mnemonicResource = "MnemonicResource";
    private Resource i18n = Resource.getBundle ("com.gensym.gda.commands.Errors");
    private MessageBrowserTable table;
    private GqmQueue sourceQueue, targetQueue;
    private MessageBrowserTableModel tableModel;
    
    private TwAccess cxn;
    
    //*** Remove if selection dialog is used ***
    private static final Symbol TARGET_QUEUE_NAME_ = Symbol.intern ("MESSAGE-QUEUE");
  
    public SendEntryCommand (UiApplication app, TwAccess cxn, MessageBrowserTable table)
    {
        super (new CommandInformation[] {
        new CommandInformation (SENDENTRY, true, shortResource, longResource, "sendto.gif", 
			     null, null, true, mnemonicResource, null)});
        this.table = table;
        this.cxn = cxn;
        tableModel = table.getTableModel ();
    }

    public void actionPerformed (ActionEvent e)
    {
        String cmdKey = e.getActionCommand ();
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
                    
        if (cmdKey.equals (SENDENTRY))
        {
             try
            {
                sourceQueue = (GqmQueue) cxn.getUniqueNamedItem (Symbol.intern ("GQM-QUEUE"), TARGET_QUEUE_NAME_);
                targetQueue = sourceQueue;
                GqmEntry entry =  (GqmEntry) ((MessageBrowserMessageImpl) (tableModel.getRow (selectedRow))).getMessage ();
                cxn.callRPC (Symbol.intern ("GDL-RPC-SEND-TO-QUEUE"), new Object [] {entry, sourceQueue, targetQueue});
            }
            catch (G2AccessException gae)    { System.err.println ("Unexpected Exception : " + gae); }
        }
    }
    
            /*** Use this if target queue selection is desired ***    
            try
            {
                 vrow =  (GqmEntry) ((MessageBrowserMessageImpl) (tableModel.getRow (selectedrows[0]))).getMessage ();
                 final GqmEntry entry = vrow;
            
                StandardDialogClient sendHandler = new StandardDialogClient () {
                    public void dialogDismissed (StandardDialog d, int code) 
                   {
                        if (d.wasCancelled ())
                           return;
                       SelectionDialog sd = (SelectionDialog) d;
                       int sIndex = sd.getResult ();
                       Symbol targetQName = (Symbol) qNames.elementAt (sIndex);
                   
                       cxn.callRPC (Symbol.intern ("GDL-RPC-SEND-TO-QUEUE"), 
                                           new Object [] {entry, table.getQueueName (), targetQName});  
                   }
               };
                   
               SelectionDialog sendDialog = new SelectionDialog (UiApplication.getCurrentFrame (), "Send to Queue",
                               false, "Select Target Queue", qNames, false, SelectionDialog.NO_SELECTION, true,
                               sendHandler).setVisible (true);
           }
           catch (G2AccessException gae)    { System.err.println ("Unexpected Exception : " + gae); }
           catch (Exception e)    
          { 
               System.out.println ("Send dialog error:  " + e.toString ()); 
               new WarningDialog (app.getCurrentFrame (), "Send error", true, e.toString (), null).setVisible (true);
          } ***/

}
