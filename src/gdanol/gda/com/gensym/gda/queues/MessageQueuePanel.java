package com.gensym.gda.queues;

import javax.swing.*;
import javax.swing.table.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.Dimension;
import java.awt.Color;
import java.awt.BorderLayout;
import java.util.Vector;
import java.util.Enumeration;
import com.gensym.classes.modules.grl.*;
import com.gensym.classes.modules.gqm.GqmEntry;
import com.gensym.classes.modules.gqm.GqmQueue;
import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2AccessException;
import com.gensym.core.UiApplication;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.ItemEvent;
import com.gensym.util.ItemListener;
import com.gensym.classes.TextArray;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.dlg.SelectionDialog;
import com.gensym.mdi.MDIToolBarPanel;
import com.gensym.ui.toolbar.ToolBar;
import com.gensym.gda.queues.MessageBrowser;
import com.gensym.gda.queues.MessageBrowserTable;
import com.gensym.gda.queues.MessageBrowserTableModel;
import com.gensym.gda.queues.ToggleSortCommand;
import com.gensym.gda.queues.SendEntryCommand;
import com.gensym.gda.queues.LockViewCommand;
import com.gensym.gda.queues.DetailViewCommand;
import com.gensym.gda.queues.RemoveSelectedCommand;
import com.gensym.gda.queues.RemoveAllCommand;

public class MessageQueuePanel extends MDIToolBarPanel
{	
    private int modelRowCount = 0;
    private MessageBrowserTableModel tableModel;
    private JFrame detailFrame;
    private MessageBrowserTable table;
    private MessageBrowser browser;
    private ToolBar toolBar;
    
    private TwAccess cxn;
    private ToggleSortCommand sortCommand;
    private SendEntryCommand sendCommand;
    private LockViewCommand lockViewCommand;
    private DetailViewCommand detailViewCommand;
    private RemoveSelectedCommand removeSelectedCommand;
    private RemoveAllCommand removeAllCommand;
    
    private static final Symbol OBJ_ = Symbol.intern ("OBJ");
    private static final Symbol NAME_ = Symbol.intern ("NAME");
    private static final Symbol MQ_NAME_ = Symbol.intern ("MESSAGE-QUEUE");
    
    public MessageQueuePanel (UiApplication app, TwAccess cxn, MessageBrowser msgBrowser) 
    {
        super ();
        browser = msgBrowser;  
        table = browser.getTableView ();
        tableModel = table.getTableModel ();

        sortCommand = new ToggleSortCommand (table);
        sendCommand = new SendEntryCommand (app, cxn, table);
        lockViewCommand = new LockViewCommand (table);
        detailViewCommand = new DetailViewCommand (app, cxn, table);
        removeSelectedCommand = new RemoveSelectedCommand (app, cxn, table);
        removeAllCommand = new RemoveAllCommand (app, cxn, table);
        
        toolBar = new ToolBar ();
        toolBar.add (sortCommand);
        toolBar.add (sendCommand);
        toolBar.add (detailViewCommand);
        toolBar.add (lockViewCommand);
        toolBar.add (removeSelectedCommand);
        toolBar.add (removeAllCommand);
        this.add (toolBar);
    }

}



