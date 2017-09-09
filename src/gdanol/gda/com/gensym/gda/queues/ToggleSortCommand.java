package com.gensym.gda.queues;

import java.awt.Frame;
import java.awt.event.ActionEvent;
import com.gensym.message.Resource;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.gda.queues.MessageBrowserTable;

public final class ToggleSortCommand extends AbstractCommand 
{
    public static final String TOGGLESORT = "ToggleSort";    
    private static final String shortResource = "ShortResource";
    private static final String longResource = "LongResource";
    private static final String mnemonicResource = "MnemonicResource";
    private Resource i18n = Resource.getBundle ("com.gensym.gda.commands.Errors");
    private MessageBrowserTable table;
  
    public ToggleSortCommand (MessageBrowserTable table)
    {
        super (new CommandInformation[] {
        new CommandInformation (TOGGLESORT, true, shortResource, longResource, "togglesort.gif", 
			     null, null, true, mnemonicResource, null)});
        this.table = table;
    }

    public void actionPerformed (ActionEvent e)
    {
        String cmdKey = e.getActionCommand ();
        if (cmdKey == null) 
            return;
        if (!isAvailable (cmdKey))
            return;
            
        if (cmdKey.equals (TOGGLESORT))
        {
            table.toggleSortOrder ();
        }
    }

}
