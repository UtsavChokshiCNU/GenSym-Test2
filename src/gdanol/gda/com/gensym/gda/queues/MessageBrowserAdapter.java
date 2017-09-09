package com.gensym.gda.queues;

import javax.swing.*;
import javax.swing.table.*;
import javax.swing.event.TableModelEvent;
import java.awt.*;
import java.awt.event.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.Dimension;
import java.awt.Color;
import java.awt.BorderLayout;
import java.util.Vector;
import java.util.Enumeration;
import java.util.Hashtable;
import com.gensym.message.Trace;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.modules.grl.*;
import com.gensym.classes.modules.gqm.GqmEntry;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;

public class MessageBrowserAdapter
        implements G2_RemoteQueueEventListener
{
    private MessageBrowserTableModel tableModel;
    private Hashtable msghash;

    public MessageBrowserAdapter (MessageBrowserTableModel tableModel)
    {
        this.tableModel = tableModel;
        msghash = new Hashtable();
    }

    private static final Symbol
        REMOTE_QUEUE_EVENT_LIST_ = Symbol.intern ("REMOTE-QUEUE-EVENT-LIST"),
        MONITORED_ATTRIBUTE_NAME_ = Symbol.intern ("MONITORED-ATTRIBUTE-NAME");

    private void addOrRemoveQueueEventList (G2_RemoteQueueEvent arg1,
                                           boolean add, boolean hashAttrValsImmediate)
    {
        GqmEntry entryObj;
        MessageBrowserMessage msgObj;

        try 
        {
            Structure data = arg1.getRemoteQueueEventData();
            Sequence items = (Sequence) data.getAttributeValue (REMOTE_QUEUE_EVENT_LIST_, null);
            if (items != null) 
            {
                Enumeration e = items.elements ();
                TableSorter sorter = tableModel.getSorter ();
                if (add) 
                {
                    while (e.hasMoreElements()) 
                    {
                        entryObj = (GqmEntry) e.nextElement ();
                        msgObj = (MessageBrowserMessage) new MessageBrowserMessageImpl (entryObj, true);
                        if (hashAttrValsImmediate)
                            msgObj.hashImportantAttributes ();
                        msghash.put (entryObj, msgObj);
                        if (tableModel.addRow (msgObj, arg1)) 
                        {
                            int ind = tableModel.getDataSize ();
                            sorter.tableChanged (new TableModelEvent (tableModel, ind));
                        }
                    }

                    if ( ! tableModel.getLockView ()) 
                    {
                        tableModel.fireChangeNoSort ();
                    }
                }
                else 
                {
                    while (e.hasMoreElements()) 
                    {
                        entryObj = (GqmEntry) e.nextElement ();
                        msgObj = (MessageBrowserMessage) msghash.get (entryObj);
                        tableModel.removeRow (msgObj, arg1);
                    }
                }

            }
        }
        catch (G2AccessException g2ae)    { Trace.exception(g2ae); }
    }

    public  void queueItemsAdded (G2_RemoteQueueEvent arg1) 
    {
        //System.err.println("MessageBrowserAdapter::queueItemsAdded()-->");
        addOrRemoveQueueEventList (arg1, true, true);
    }

    public  void queueItemsRemoved (G2_RemoteQueueEvent arg1) 
    {
        addOrRemoveQueueEventList (arg1, false, false);
    }

    private static final Symbol ACKNOWLEDGEMENT_STATUS_ = Symbol.intern ("ACKNOWLEDGEMENT-STATUS");

    public  void queueItemsAttributeChanged (G2_RemoteQueueEvent arg1) 
    {
        try 
        {
            Structure data = arg1.getRemoteQueueEventData ();
            Sequence items = (Sequence) data.getAttributeValue (REMOTE_QUEUE_EVENT_LIST_, null);
            Symbol monitoredAttributeName = (Symbol) data.getAttributeValue (MONITORED_ATTRIBUTE_NAME_, null);
            if (items != null) 
            {
                GqmEntry entryObj;
                MessageBrowserMessage msgObj;

                Enumeration e = items.elements();
                MessageBrowserColumnModel colModel = tableModel.getColumnModel();
                int colInd = colModel.getColumnIndex(ACKNOWLEDGEMENT_STATUS_);

                while(e.hasMoreElements()) 
                {
                    entryObj = (GqmEntry) e.nextElement ();
                    msgObj = (MessageBrowserMessage) msghash.get (entryObj);
                    try 
                    {
                        Object newValue = entryObj.getPropertyValue (monitoredAttributeName);
                        msgObj.setValueForAttributeFromMessage (monitoredAttributeName, newValue);
                    } 
                    catch (com.gensym.util.NoSuchAttributeException nsae)    { Trace.exception(nsae); }
                }
                tableModel.fireSorterTableChanged ();
            }
        } 
        catch (G2AccessException g2ae)    { Trace.exception(g2ae); }
    }

    public  void queueReceivedInitialState (G2_RemoteQueueEvent arg1) 
    {
        addOrRemoveQueueEventList (arg1, true, false);
        tableModel.applyFiltering ();

        try 
        {
            Structure data = arg1.getRemoteQueueEventData ();
            Sequence items = (Sequence) data.getAttributeValue (REMOTE_QUEUE_EVENT_LIST_, null);
            if (items != null) 
            {
                Enumeration e = items.elements ();
                MessageAttrHashThread thread = new MessageAttrHashThread (e, msghash);
                thread.runThread ();
            }
        }
        catch (G2AccessException e) 
        {
            System.err.println ("MessageBrowserAdapter::queueReceivedInitialState()--> " + e);
        }
    }

    public  void queueInvalidateState (G2_RemoteQueueEvent arg1) 
    {
        tableModel.removeAll ();
        addOrRemoveQueueEventList (arg1, true, false);
    }
    
}
