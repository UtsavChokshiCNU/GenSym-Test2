package com.gensym.gda.queues;

//import java.awt.Frame;
import java.awt.event.ActionEvent;
import com.gensym.message.Resource;
import com.gensym.util.Symbol;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
//import com.gensym.classes.modules.gqm.GqmQueue;
//import com.gensym.classes.modules.gqm.GqmEntry;
import com.gensym.gda.queues.MessageBrowserTable;
import com.gensym.gda.queues.MessageBrowserTableModel;
//import com.gensym.gda.queues.MessageBrowserMessageImpl;

public final class LockViewCommand extends AbstractCommand 
{
    public static final String LOCKVIEW = "LockView"; 
      
    private static final String shortResource = "ShortResource";
    private static final String longResource = "LongResource";
    private static final String mnemonicResource = "MnemonicResource";
    private Resource i18n = Resource.getBundle ("com.gensym.gda.commands.Errors");
    private MessageBrowserTable table;
    private MessageBrowserTableModel tableModel;
  
    public LockViewCommand (MessageBrowserTable table)
    {
        super (new CommandInformation[] {
        new CommandInformation (LOCKVIEW, true, shortResource, longResource, "lockview.gif", 
			     null, null, true, mnemonicResource, null)});
        this.table = table;
        tableModel = table.getTableModel ();
    }

    public void actionPerformed (ActionEvent e)
    {
        String cmdKey = e.getActionCommand ();
        if (cmdKey == null) 
            return;
        if (!isAvailable (cmdKey))
            return;
        //### int selectedRow = table.getSelectedRow ();
        //### if (selectedRow < 0)
        //###    return;
            
        if (cmdKey.equals (LOCKVIEW))
        {
            tableModel.toggleLockView ();
            System.out.println (tableModel.getLockView());
        }
    }

}
