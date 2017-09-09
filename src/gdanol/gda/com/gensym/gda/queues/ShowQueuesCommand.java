package com.gensym.gda.queues;

import com.gensym.core.UiApplication;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2Connection;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwGateway;
import com.gensym.ntw.util.*;
import com.gensym.shell.util.*;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.StructuredCommandInformation;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.SubCommandInformation;
import com.gensym.ui.CommandGroupInformation;
import com.gensym.classes.UiClientSession;
import com.gensym.classes.Entity;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.TextArray;
import com.gensym.classes.modules.gqs.*;
import com.gensym.classes.modules.gqm.*;
import com.gensym.util.Symbol;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIToolBarPanel;
import com.gensym.gda.queues.*;
import com.gensym.gda.commands.gdaAbstractCommand;
import com.gensym.gda.queues.MessageQueuePanel;
import com.gensym.gda.queues.ErrorQueuePanel;
import com.gensym.gda.queues.ExplanationQueuePanel;
import com.gensym.gda.queues.AlarmQueuePanel;
import java.lang.reflect.Method;
import java.awt.*;
import java.awt.event.*;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Hashtable;
import java.util.Properties;
import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JPanel;
import javax.swing.table.TableColumnModel;
import javax.swing.table.TableColumn;

public class ShowQueuesCommand extends gdaAbstractCommand
{
    public static final String QUEUES = "Queues";
    public static final String ALARM_QUEUE = "AlarmQueue";
    public static final String EXPLANATION_QUEUE = "ExplanationQueue";
    public static final String ERROR_QUEUE = "ErrorQueue";
    public static final String MESSAGE_QUEUE = "MessageQueue";

    private static final String shortResource = "ShortResource";
    private static final String longResource = "LongResource";
    private static final String mnemonicResource = "MnemonicResource";
    
    //$$$ Ultimately the index size should go in a preference or properties object $$$
    private static FrameIndex [] frameIndices = new FrameIndex [20];
    protected Symbol object_ = Symbol.intern ("OBJECT");
	
    protected static String emptyString = "";
    protected static Color [] severityColors = new Color [16];
    protected TwAccess cxn;
    
    public static final Symbol GQM_QUEUE_CLASS_ = Symbol.intern ("GQM-QUEUE");
    public static final Symbol GDA_ALARM_QUEUE_CLASS_ = Symbol.intern ("GDA-ALARM-QUEUE");
    public static final Symbol Q_TIME_ = Symbol.intern ("GQM-CREATION-TIME");
    public static final Symbol Q_MESSAGE_TEXT_ = Symbol.intern ("GQM-MESSAGE-TEXT");
    public static final Symbol Q_SEVERITY_ = Symbol.intern ("GDA-SEVERITY");
    public static final Symbol Q_ACK_ = Symbol.intern ("ACKNOWLEDGED");
    private static final Symbol QNAME_FOR_CAT_ = Symbol.intern ("GDLUISUP-GET-QUEUE-NAME-FOR-CATEGORY");
    private static final Symbol GET_SEVERITY_COLORS_ = Symbol.intern ("GDA-GET-SEVERITY-COLORS");     
    private final static Resource i18n = Resource.getBundle ("com.gensym.gda.queues.Queues");
    
    public ShowQueuesCommand (UiApplication uiApp)
    {
        super (uiApp, new CommandInformation[] {
	  new SubCommandInformation (QUEUES, true, shortResource, longResource, null, null, null, mnemonicResource, new CommandInformation[] 
            {
	new CommandInformation (ALARM_QUEUE, true, shortResource, longResource, null, null, null, true, mnemonicResource, null),
                new CommandInformation (EXPLANATION_QUEUE, true, shortResource, longResource, null, null, null, true, mnemonicResource, null),
               	new CommandInformation (ERROR_QUEUE, true, shortResource, longResource, null, null, null, true, mnemonicResource, null),
               	new CommandInformation (MESSAGE_QUEUE, true, shortResource, longResource, null, null, null, true, mnemonicResource, null)
            })
        });

       try
       {
           FileInputStream is = new FileInputStream ("/com/gensym/gda/queues/Queues.properties");
            System.getProperties().load (is);
            System.getProperties ().list(System.out);
            is.close ();
        }
       catch (FileNotFoundException fnfe)    { System.err.println (fnfe); }              
       catch (IOException ioe)    { System.err.println (ioe); }
        
        //*** Get the connection & register showQueue with G2 ***
        GetConnectionThread conThread = new GetConnectionThread (this);
        Thread xThread = new Thread (conThread);
        xThread.start ();
    }

    public void commandPerformed (ActionEvent actionevent) 
    {
        String s = actionevent.getActionCommand ();
        String queueCat;
        Symbol queueName;
        if (cxn == null)
            cxn = (TwAccess) currentConnection;
        UiClientSession client = cxn.getSession ();
        
        if (s.equals (ERROR_QUEUE)) 
            queueCat = new String ("EQ");
        else if (s.equals (EXPLANATION_QUEUE)) 
            queueCat = new String ("XQ");
        else if (s.equals (ALARM_QUEUE))
            queueCat = new String ("AQ");
        else    // MESSAGE_QUEUE or invalid queue
            queueCat = new String ("MQ");
            
        try
        {
            queueName = (Symbol) cxn.callRPC (QNAME_FOR_CAT_, new Object [] {queueCat, client});
            showQueue (queueCat, queueName);
        }
        catch (G2AccessException gae)    { System.err.println ("G2 Access Exception while showing queue: " + gae); }
    }
    
    public void showQueue (String category, Symbol queueName)
    {
        JFrame queueFrame = null;

        if (viewExistsForQueue (queueName))    //*** Return an existing view if one is available ***
            queueFrame = getFrameForQueue (queueName);
        else   //*** Otherwise build a view ***
        {
            if (category.equals ("AQ"))
                setSeverityColors (cxn, cxn.getSession ());
            queueFrame = buildQueueFrame (category, queueName);
        }
        
        if (queueFrame != null)
            queueFrame.setVisible (true);
    }

    public void updateAvailability () 
    {
        if (currentConnection == null)
            setAvailable (QUEUES, false);
        else 
            setAvailable (QUEUES, true);
     }
        
    public JFrame buildQueueFrame (String queueCategory, Symbol queueName)
    {
        JFrame queueFrame;
        Symbol queueClass;
    
         if (cxn == null)
             System.out.println ("Connection has been broken");
         if (queueCategory.equals ("AQ"))
             queueClass = GDA_ALARM_QUEUE_CLASS_;
         else
             queueClass = GQM_QUEUE_CLASS_;
            
        //*** Create columns ***
        MessageBrowserColumn[] columns = getQueueColumns (queueCategory);
                
        //*** Create column model ***
        MessageBrowserColumnModel columnModel = new MessageBrowserColumnModel ();
        columnModel.addColumns (columns);
                
        //*** Create the view ***
        MessageBrowser browser = new MessageBrowser (cxn, columnModel);
                        
        //*** Add table & toolbar to view ***
        try
        {
            GqmQueue theQueue = (GqmQueue) cxn.getUniqueNamedItem (queueClass, queueName);               
            browser.addServer (theQueue);
            MessageBrowserTable table = browser.getTableView ();
            table.setSourceName (queueName);
            table.setColumnWidths (new int [10]);    //*** Initialize widths to default values ***
            table.clearSelection ();
               
            MDIToolBarPanel queuePanel = createQueuePanel (app, cxn, browser, queueCategory);
            browser.add (queuePanel, BorderLayout.NORTH);
        }
        catch (G2AccessException gae)    { System.err.println (gae); }
                
        //*** Put the view on the frame ***
        queueFrame = new JFrame (queueName.toString ());
        queueFrame.getContentPane ().setLayout (new BorderLayout ());
        queueFrame.getContentPane ().add (browser, BorderLayout.CENTER);
        queueFrame.pack();
        return queueFrame;         
    }
    
    public MDIToolBarPanel createQueuePanel ( UiApplication app, TwAccess cxn, MessageBrowser browser, String queueCategory)
    {
        if (queueCategory.equals ("AQ"))
            return new AlarmQueuePanel (app, cxn, browser);
        else if (queueCategory.equals ("XQ"))
            return new ExplanationQueuePanel (app, cxn, browser);
        else if (queueCategory.equals ("EQ"))
            return new ErrorQueuePanel (app, cxn, browser);
        else
            return new MessageQueuePanel (app, cxn, browser);
    }
    
    private MessageBrowserColumn[] getQueueColumns (String queueCategory)
     {
         MessageBrowserColumn[] cols;
         
         if (queueCategory.equals ("AQ"))
         {
             MessageBrowserColumn col1 = new MessageBrowserColumn ("Time", 1, 200, 100, 150, Q_TIME_, "String", "TEST1");
             MessageBrowserColumn col2 = new MessageBrowserColumn ("Sev", 1, 100, 50, 50, Q_SEVERITY_, "String", "TEST2");
             MessageBrowserColumn col3 = new MessageBrowserColumn ("Message", 1, 500, 300, 400, Q_MESSAGE_TEXT_, "String", "TEST3");
             MessageBrowserColumn col4 = new MessageBrowserColumn ("Ack", 1, 100, 50, 75, Q_ACK_, "String", "TEST4");
             cols = new MessageBrowserColumn [] {col1, col2, col3, col4};
         }
         else
         {
             MessageBrowserColumn col1 = new MessageBrowserColumn ("Time", 1, 200, 100, 150, Q_TIME_, "String", "TEST1");
             MessageBrowserColumn col2 = new MessageBrowserColumn ("Message", 1, 500, 300, 400, Q_MESSAGE_TEXT_, "String", "TEST2");
             cols = new MessageBrowserColumn [] {col1, col2};
         }
         return cols;
     }

    public static Frame getFrame (Component comp)
    {
        Component c = comp;
        
        while (true)
        {
            if (c == null || c instanceof Frame)
                break;
            c = c.getParent ();
        }
        return (Frame) c;
    }
    
    public static Color getColorForSeverity (int sev)
    {
        if (sev < 0 || sev >= 16)
            return Color.gray;
        return severityColors [sev];
    }
    
    public void setSeverityColors (TwAccess conn, UiClientSession cSess)
    {
        String [] gdaSeverityColors;
    
        try
        {
            gdaSeverityColors = ((TextArray) conn.callRPC (GET_SEVERITY_COLORS_, new Object [] {cSess})).getTextArrayContents ();
         
            for (int x = 0; x < 16; x++)
            {
                severityColors [x] = Color.getColor (new String ("user.G2Color." + gdaSeverityColors [x]));
                if (severityColors [x] == (Color) null)
                    severityColors [x] = Color.gray; 
            }   
        }
        catch (G2AccessException gae)    { System.err.println ("Connection lost while setting severity colors: " + gae); }
    }
    
    public static boolean viewExistsForQueue (Symbol theName)
    {
        for (int x = 0; x < 20; x++)
        {
            if (frameIndices [x] == null)
                continue;
            if ((frameIndices [x]).qFrame == null)    //*** Outdated - clear it out ***
                frameIndices [x] = (FrameIndex) null;
            if ((frameIndices [x]).qName == theName)
                return true;
        }
        return false;
    }
        
    public static JFrame getFrameForQueue (Symbol theName)
    {
        for (int x = 0; x < 20; x++)
        {
            if (frameIndices [x] == null)
                continue;
            if ((frameIndices [x]).qFrame == null)    //*** Outdated - clear it out ***
                frameIndices [x] = (FrameIndex) null;
            if ((frameIndices [x]).qName == theName)
                return (frameIndices [x]).qFrame;
        }
        return (JFrame) null;
    }
    
    class FrameIndex extends Object
    {
        Symbol qName;
        JFrame qFrame;
        
        FrameIndex (Symbol theQueue, JFrame theFrame)
        {
            qName = theQueue;
            qFrame = theFrame;
            boolean inserted = false;
            
            for (int x = 0; x < 20; x++)
            {
                if (frameIndices [x] == null || (frameIndices [x]).qFrame == null)
                {
                    frameIndices [x] = this;
                    inserted = true;
                }
            }
            if ( !(inserted) )
                System.err.println ("Frame indexes exhausted");
        }        
    }
        
    class GetConnectionThread implements Runnable
    {
        private Object callingInstance;
        
        public GetConnectionThread (Object caller)
        {
            super ();
            callingInstance = caller;
        }
        
        public void run () 
        {
            int xx = 0;

            while (cxn == null)
            {
                try    { Thread.sleep (100); }
                catch (InterruptedException ie)    { System.err.println (ie); }
                xx++;
                if (xx > 100)
                    break;
                cxn = (TwAccess) currentConnection;
            }

            try    
            {
                java.lang.reflect.Method method = callingInstance.getClass ().getDeclaredMethod ("showQueue", new Class [] {String.class, Symbol.class});
                cxn.registerJavaMethod (callingInstance, method, Symbol.intern ("SHOW-QUEUE-REMOTE"), false);
            }
            catch (SecurityException se)    { System.err.println (se); }
            catch (NoSuchMethodException nsme)    { System.out.println ("Invalid method"); }                 
        }
    }    
}



