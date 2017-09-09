package com.gensym.gda.queues;

import java.awt.*;
import javax.swing.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.event.ActionEvent;
import com.gensym.message.Resource;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2AccessException;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.core.UiApplication;
import com.gensym.dlg.WarningDialog;
import com.gensym.classes.modules.gqm.GqmQueue;
import com.gensym.classes.modules.gqm.GqmEntry;
import com.gensym.classes.modules.gda.GdaAlarmQueue;
import com.gensym.classes.modules.gda.GdaAlarmEntry;
import com.gensym.classes.UiClientSession;
import com.gensym.gda.queues.MessageBrowserTable;
import com.gensym.gda.queues.MessageBrowserTableModel;
import com.gensym.gda.queues.MessageBrowserMessageImpl;

public final class DetailAlarmViewCommand extends AbstractCommand 
{
    public static final String DETAILALARMVIEW = "DetailAlarmView"; 
      
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
    
    private static final Symbol GDA_GET_HISTORY_ = Symbol.intern ("GDA-GET-HISTORY");
    private static final Symbol GDA_GET_EXPLANATION_ = Symbol.intern ("GDA-GET-EXPLANATION");
    private static final Symbol GDA_GET_ADVICE_ = Symbol.intern ("GDA-GET-ADVICE");
    
    //*** Remove if selection dialog is used ***
    private static final Symbol TARGET_QUEUE_NAME_ = Symbol.intern ("MESSAGE-QUEUE");
  
    public DetailAlarmViewCommand (UiApplication app, TwAccess cxn, MessageBrowserTable table)
    {
        super (new CommandInformation[] {
        new CommandInformation (DETAILALARMVIEW, true, shortResource, longResource, "details.gif", 
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
          
        if (cmdKey.equals (DETAILALARMVIEW))
        {
             try
            {
                GdaAlarmEntry entry =  (GdaAlarmEntry) ((MessageBrowserMessageImpl) (tableModel.getRow (selectedRow))).getMessage ();
                UiClientSession client = cxn.getSession ();
                detailFrame = new JFrame ("Alarm Entry Detail");
                detailFrame.setSize (300,250);
                detailFrame.addWindowListener (new WindowAdapter() 
                        { public void windowClosing (WindowEvent e) {detailFrame.dispose ();}});
                
                List dispList = new List ();    //*** Create a display list ***
                //$$$ Note:  We should probably get the entry instead of all these RPC calls $$$
                String [] comments = (entry.getGqmComments ()).getTextArrayContents ();
                Sequence historySeq = (Sequence) cxn.callRPC (GDA_GET_HISTORY_, new Object[] {entry, client});
                Sequence explanationSeq = (Sequence) cxn.callRPC (GDA_GET_EXPLANATION_, new Object[] {entry, client});
                Object [] history = historySeq.getContents (); 
                Object [] explanation = explanationSeq.getContents ();
                String advice = (String) cxn.callRPC (GDA_GET_ADVICE_, new Object[] {entry, client});               

                dispList.add ("Time: " + new Double (entry.getGqmCreationTime ()).toString ());
                dispList.add ("Severity: " + new Integer (entry.getGdaSeverity ()).toString ());
                dispList.add ("Message: " + entry.getGqmMessageText ().toString ());
                dispList.add ("Acknowledged: " + new Boolean (entry.getAcknowledged ()).toString ());
                if (! advice.equals (""))
                    dispList.add ("Advice: " + advice);
                if (comments.length > 0)
                {
                    dispList.add ("Comments:");
                    for (i = 0; i < comments.length; i++)
                    {
                        dispList.add ("    " + comments[i]);
                    }
                }

                dispList.add ("History:");
                for (i = 0; i < history.length; i++)
                {
                    dispList.add ("    " + (String) history[i]);
                }
                
                if (explanation.length > 0)
                {
                    dispList.add ("Explanation:");
                    for (i = 0; i < explanation.length; i++)
                    {
                        dispList.add ("    " + (String) explanation[i]);
                    }
                }
                
                JScrollPane scrollPane = new JScrollPane (dispList);
                scrollPane.setPreferredSize (new Dimension (250, 200));
                detailFrame.getContentPane ().add ("North", scrollPane);
                detailFrame.setVisible (true);
                //### ((MessageBrowserTableModel) tableModel).fireChange ();  WHY?? ###
            }
            catch (G2AccessException gae)    { System.err.println ("Unexpected Exception : " + gae); }
        }
    }

}
