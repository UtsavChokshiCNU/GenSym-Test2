package com.gensym.gda.queues;

import java.util.Vector;
import java.util.Hashtable;
import java.util.Enumeration;
import javax.swing.table.*;
import java.awt.Component;
import java.awt.Color;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2ItemDeletedException;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.ntw.util.G2ColorMap;
import com.gensym.ntw.TwAccess;
import com.gensym.classes.modules.gqm.GqmQueue;
import com.gensym.classes.modules.gqm.GqmEntry;
import com.gensym.message.Trace;
import com.gensym.classes.modules.grl.*;
import java.lang.ArrayIndexOutOfBoundsException;

public class MessageBrowserTableModel extends AbstractTableModel 
{
    private Vector data;
    private Vector nonViewData;
    private MessageBrowserColumnModel colModel;
    private boolean lockView;
    private TableSorter sorter;
    private Hashtable serverMsgs = new Hashtable();
    private Hashtable serversState = new Hashtable();
    private Hashtable serversHighestPriority = new Hashtable();
    private Hashtable serversToggleButtons = new Hashtable();
    private Vector filters;
    private final Symbol GQM_PRIORITY_ = Symbol.intern ("GQM-PRIORITY");
   
    public MessageBrowserTableModel (MessageBrowserColumnModel columnModel)
    {
        this ();
        colModel = columnModel;
        lockView = false;
    }

    public MessageBrowserTableModel ()
    {
        data = new Vector();    //*** initSize, increment);3000,500 ***
        nonViewData = new Vector ();
        filters = new Vector ();
    }

    public void setServerState (GqmQueue queue, Boolean state) 
    {
        serversState.put (queue, state);
    }

    public void setColumnModel (MessageBrowserColumnModel columnModel)
    {
        colModel = columnModel;
    }

    public void addSorter (TableSorter sorterInstance) 
    {
        sorter = sorterInstance;
    }

    public TableSorter getSorter () 
    {
        return sorter;
    }

    //*** Returns -1 if no match is found ***
    public int getIndexFromModel (MessageBrowserMessage msg) 
    {
        int retInd = -1;

        for (int i = 0; i < data.size (); i++) 
        {
            if (data.elementAt(i).equals (msg)) 
            {
                retInd = i;
                break;
            }
        }
        return retInd;
    }

    public void toggleLockView () 
    {
        if (lockView)
        {
            lockView = false;
            applyFiltering ();
            fireChange ();    //$$$ Can we retain row selection here?? $$$
        }
        else
            lockView = true;
    }

    public boolean getLockView()
    {
        return lockView;
    }

    public MessageBrowserColumnModel getColumnModel () 
    {
        return colModel;
    }

    public Vector getMsgsForServer (GqmQueue queue) 
    {
        return (Vector) serverMsgs.get (queue);
    }

    public void removeMsgsForServerFromNonView (GqmQueue queue) 
    {
        int i;
        Vector msgs = (Vector) getMsgsForServer (queue);

        if (msgs != null) 
        {
            //*** Remove all message from nonViewData for the server ***
            for (i = 0; i < msgs.size(); i++) 
            {
                nonViewData.removeElement (msgs.elementAt (i));
            }
            msgs.removeAllElements ();
        }
    }

    public MessageBrowserFilter getFilter (int forInd) 
    {
        int i;
        int ind = -1;

        for (i = 0; i < filters.size(); i++) 
        {
            MessageBrowserFilter msgFilter = (MessageBrowserFilter) filters.elementAt (i);
            if (msgFilter.getIndex () == forInd) 
            {
                ind = i;
                break;
            }
        }
        if (ind == -1)
            return null;
        else
            return (MessageBrowserFilter) filters.elementAt (ind);
    }

    public void addFilter (MessageBrowserFilter filter) 
    {
        filters.addElement (filter);
    }

    // **************************
    public void applyFiltering () 
    {
        int i, j, k;
        MessageBrowserMessage msg;
        MessageBrowserFilter filter;
        Vector tempData = new Vector();
        boolean anyFilterOn = false;

        final Symbol SC_PRIORITY_FILTER_ = Symbol.intern ("SC-PRIORITY-FILTER");
        final Symbol OBJECT_FILTERS_ = Symbol.intern ("OBJECT-FILTERS");
        final Symbol ATTRIBUTE_FILTERS_ = Symbol.intern ("ATTRIBUTE-FILTERS");

        //*** Do nothing if View Locked ***
        if (lockView) 
            return;

        //*** Check if all filters are off ***
        for (i = 0; i < filters.size(); i++) 
        {
            if (((MessageBrowserFilter) filters.elementAt (i)).getState ()) 
            {
                anyFilterOn = true;
                break;
            }
        }

        if (! serversState.contains (new Boolean (true))) 
        {
            nonViewData.removeAllElements ();
            return;
        }

        if (! anyFilterOn) 
        {
            //*** Move all rows from nonViewData to data ***
            for (i = 0; i < nonViewData.size(); i++) 
            {
                data.addElement (nonViewData.elementAt (i));
            }
            nonViewData.removeAllElements ();
            fireChange ();
            return;
        }

        //*** Move all rows from data to nonViewData ***
        for (i = 0; i < data.size(); i++) 
        {
            nonViewData.addElement (data.elementAt (i));
        }
        data.removeAllElements ();

        //*** Apply filter to all msgs in nonViewData ***
        //*** Msgs that are true for filter are to be moved to data ***
        Object msgVal, msgOFilVal;
        
        for (i = 0; i < nonViewData.size(); i++) 
        {
            msg = (MessageBrowserMessage) nonViewData.elementAt (i);
            for (j = 0; j < filters.size(); j++) 
            {
                filter = (MessageBrowserFilter) filters.elementAt (j);
                if (filter.getState()) 
                {
                    boolean pass = doesMsgPassFilter (msg, filter);
                    if (pass) 
                    {
                        MessageBrowserFilter otherFilter;

                        boolean show = true;
                        for (k = 0; k < filters.size (); k++) 
                        {
                            otherFilter = (MessageBrowserFilter) filters.elementAt (k);
                            if ((! otherFilter.equals (filter)) & (otherFilter.getState ())) 
                            {
                                pass = doesMsgPassFilter (msg, otherFilter);
                                if (((! otherFilter.isFilterOR ()) || (! filter.isFilterOR ())) & (! pass)) 
                                {
                                    show = false;
                                    break;
                                }
                            }
                        }
                        if (show) 
                        {
                            tempData.addElement (msg);
                            break;
                        }
                    }
                }
            }
        }

        //*** Remove the msgs moved to data from nonViewData ***
        for (i = 0; i < tempData.size(); i++) 
        {
            data.addElement (tempData.elementAt (i));
            nonViewData.removeElement (tempData.elementAt (i));
        }

        //System.out.println("nonview="+nonViewData.size()+"; data="+data.size()+"; 2");

        fireChange ();
    }
    // **************************
    
    public boolean doesMsgPassFilter (MessageBrowserMessage msg, MessageBrowserFilter filter) 
    {
        Symbol attrName;
        Object msgVal;
        Object filterVal = new String ("");
        boolean passOrFail = true;

        Enumeration eN = ((Sequence) filter.getAttributeNames()).elements();
        Enumeration eV = ((Sequence) filter.getWorkingValues()).elements();

        Sequence values = (Sequence) filter.getWorkingValues ();
        while (eN.hasMoreElements()) 
        {
            attrName = (Symbol) eN.nextElement();
            msgVal = msg.getValueForAttributeFromMessage (attrName);
            //System.out.println("MBTM:245-->attrName="+attrName+"; attrVal="+msgVal+"; filterVal="+filterVal);
            if (values.size () == 0) 
            {
                passOrFail = false;
                break;
            }
            if (values.contains (msgVal)) 
            {
                passOrFail = true;
                break;
            }
            else
                for (int z = 0; z < values.size(); z++) 
                {
                    passOrFail = matchFilterVal (msgVal.toString (), values.elementAt (z).toString ());
                    if (passOrFail)    //*** Match found ***
                        break;
                }
        }
        return passOrFail;
    }
    
    private boolean matchFilterVal (String msgVal, String filterVal) 
    {
        //*** Convert the strings to uppercase ***
        msgVal = msgVal.toUpperCase ();
        filterVal = filterVal.toUpperCase ();

        if (msgVal.length () < filterVal.length ())
            return false;

        boolean match = false;
        boolean star = false;
        int fi = 0; int mi = 0;
        int filterValSize = filterVal.length () - 1;
        if (filterValSize == -1)    //*** filterVal has zero length ***
            return false;
        String next = "";

        //System.out.println("\nstart matching\n filterValSize="+filterValSize+"; filterVal="+filterVal);
        int msgInc = 0;
        while (true) 
        {
            //System.out.println("begining --> fi="+fi+"; mi="+mi);
            if (star) 
            {
                msgVal = msgVal.substring (mi);
                //System.out.println("msgVal="+msgVal);
                int posN = msgVal.indexOf (next);
                //System.out.println("if (star) -->posN="+posN+"; for next="+next);
                if (posN == -1)
                    return false;
                else
                    mi = posN;
            }

            //System.out.println("mi="+mi+"; fi="+fi);
            //System.out.println("msgVal.substring(mi,mi+1)="+msgVal.substring(mi,mi+1)+"; filterVal.substring(fi,fi+1)="+filterVal.substring(fi,fi+1));

            if (filterVal.substring (fi,fi+1).equals ("?") || filterVal.substring (fi,fi+1).equals (msgVal.substring (mi,mi+1))) 
            {
                star = false;
                match = true;
                mi++;
                //System.out.println("if equals(?) -->mi="+mi);
            }
            else if (filterVal.substring (fi,fi+1).equals ("*")) 
            {
                    //System.out.println ("if equals(*) -->fi="+fi);
                    // get next character from filterVal

                    if (fi < filterValSize) 
                    {
                        next = filterVal.substring (fi+1,fi+2);
                        star = true;
                        match = true;
                        //System.out.println("if equals(*) (fi < filterValSize)-->next="+next+"; fi="+fi);
                    }
                    else 
                    {
                        //System.out.println("* is the last char, returning 'true'");
                        return true;
                    }
                }
                else
                    return false;

            if (fi < filterValSize)
                fi++;
            else if (star)
                return true;
            else
                return match;
        }
    }

    public void moveDataFromView (Vector msgs) 
    {
        MessageBrowserMessage msg;
        int count = msgs.size ();
        int i;

        for (i = 0; i < msgs.size (); i++) 
        {
            msg = (MessageBrowserMessage) msgs.elementAt (i);
            data.removeElement (msg);
        }

        if (count > 0)
            fireChange ();
    }

    public void moveDataToNonview (Vector msgs) 
    {
        int i, count;
        MessageBrowserMessage msg;

        count = msgs.size();

        for (i = 0; i < msgs.size(); i++) 
        {
            msg = (MessageBrowserMessage) msgs.elementAt (i);
            nonViewData.addElement (msg);
        }
    }

    //*** Return true if row added to data, else return false if row added to nonViewData ***
    public boolean addRow (MessageBrowserMessage msg, G2_RemoteQueueEvent event) 
    {
        int i;
        MessageBrowserFilter filter = null;
        boolean dontFilter = false;
        boolean noFilterSelected = true;

        if (lockView) 
        {
            nonViewData.addElement (msg);
            return false;
        }

        for (i = 0; i<filters.size(); i++) 
        {
            filter = (MessageBrowserFilter) filters.elementAt (i);
            if (filter.getState ()) 
            {
                noFilterSelected = false;
                boolean pass = doesMsgPassFilter (msg, filter);
                //System.out.println("after doesMsgPassFilter(): pass="+pass);
                if (pass)
                    dontFilter = true;
                else if (! filter.isFilterOR ()) 
                {
                        dontFilter = false;
                        break;
                }
            }
        }
        if (noFilterSelected)
            dontFilter = true;
        //System.out.println("dontFilter="+dontFilter+"; filters.size()="+filters.size());

        GqmQueue queue = (GqmQueue) event.getSource ();

        Vector msgVector = (Vector) serverMsgs.get (queue);
        if (msgVector == null) 
        {
            msgVector = new Vector ();
            msgVector.addElement (msg);
            serverMsgs.put (queue, msgVector);
        }
        else
            msgVector.addElement (msg);

        //*** Change color of server according to the highest priority ***
        //System.out.println("serversHighestPriority size="+serversHighestPriority.size()+"; msg="+msg);
        Integer msgPri = (Integer) msg.getValueForAttributeFromMessage (GQM_PRIORITY_);
        if (msgPri == null) 
        {
            Trace.exception (new Throwable ("Error: Priority of message is null"));
             return false;
        }
        //System.out.println("msg priority="+msgPri.intValue());
        Integer pri = (Integer) serversHighestPriority.get (queue);
        //System.out.println("highest priority: pri="+pri+"; for server: queue="+queue);
        if (pri != null) 
        {
            if (msgPri.intValue () < pri.intValue()) 
            {
                serversHighestPriority.put (queue, msgPri);
                setBackgroundColorOfServerButton (queue, msg, msgPri);
            }
        }
        else 
        {
            serversHighestPriority.put (queue, msgPri);
            setBackgroundColorOfServerButton (queue, msg, msgPri);
        }

        // insert into data vector only if filtering allows
        if ((dontFilter) || (filters.size () == 0)) 
        {
            data.addElement (msg);
            return true;
        }
        else 
        {
            nonViewData.addElement (msg);
            return false;
        }
    }

    private void setBackgroundColorOfServerButton (GqmQueue server, MessageBrowserMessage msg, Integer pri) 
    {
        int priority = pri.intValue ();
        Component button = (Component) serversToggleButtons.get (server);
        //System.out.println("serversToggleButtons size="+serversToggleButtons.size());
        if (button == null)
            return;
        Color c = getBackgroundColorForPriority (msg, pri);
        button.setBackground (c);
        button.repaint ();
    }

    public void setDefBackgroundColorOfServerButton (GqmQueue server) 
    {
        Component button = (Component) serversToggleButtons.get (server);
        if (button == null)
            return;
        serversHighestPriority.remove(server);
        button.setBackground(Color.lightGray);
        button.repaint();
    }

    public void addServerToggleButtonToHash (GqmQueue server, java.awt.Component button) 
    {
        serversToggleButtons.put(server, button);
    }

    private static Hashtable priorityColorMap = new Hashtable ();
    
    private Color getBackgroundColorForPriority (MessageBrowserMessage inMsg, Integer priority)
    {
        if (priority.intValue () == 9999)
            return Color.lightGray;

        Symbol colorSymbol = (Symbol) priorityColorMap.get (priority);
        if (colorSymbol == null) 
        {
            Symbol GET_BACKGROUND_COLOR_FOR_PRIORITY_ = Symbol.intern ("GET-BACKGROUND-COLOR-FOR-PRIORITY");
            GqmEntry msg = ((MessageBrowserMessageImpl) inMsg).getMessage ();
            try 
            {
               TwAccess cxn = (TwAccess) ((com.gensym.classes.ItemImpl) msg).getContext ();
                colorSymbol = (Symbol) cxn.callRPC (GET_BACKGROUND_COLOR_FOR_PRIORITY_, new Object[] {priority});
                priorityColorMap.put (priority, colorSymbol);
            }
            catch (G2AccessException gae) { Trace.exception(gae);  }
        }
        if (colorSymbol == null)
            return Color.white;
        else
            return G2ColorMap.get (colorSymbol);
    }

    public void removeRow (MessageBrowserMessage msg, G2_RemoteQueueEvent event) 
    {
        if (data.removeElement (msg))
            fireChangeNoSort ();
        else
            nonViewData.removeElement (msg);

        GqmQueue queue = (GqmQueue) event.getSource ();
        Vector msgVector = (Vector) serverMsgs.get (queue);
        msgVector.removeElement (msg);
        Integer curHighInteger = (Integer) serversHighestPriority.get (queue);
        int curHigh = 9999;
        if (curHighInteger != null)
            curHigh = curHighInteger.intValue ();
        Integer newPri = getHighestPriorityInMsgs (msgVector, curHigh);
        serversHighestPriority.put (queue, newPri);
        setBackgroundColorOfServerButton (queue, msg, newPri);
    }

    private Integer getHighestPriorityInMsgs (Vector msgVector, int curHigh) 
    {
        int vSize = msgVector.size ();
        int lowestPri = 9999;
        if (vSize > 0)
            for (int i=0; i<vSize; i++) 
            {
                MessageBrowserMessage msg = (MessageBrowserMessage) msgVector.elementAt (i);
                Integer Pri = (Integer) msg.getValueForAttributeFromMessage (GQM_PRIORITY_);
                /*** Check to see if Pri is null for some reason, Pri is null sometimes when 
                        the lifetime of message is 1 second ?? ***/
                if (Pri == null)
                    return new Integer (1);
                else 
                {
                    int msgPri = Pri.intValue ();

                    if (msgPri == curHigh) 
                    {
                        lowestPri = curHigh;
                        break;
                    }
                    else if (msgPri < lowestPri)
                        lowestPri = msgPri;
                }
            }
        return new Integer (lowestPri);
    }

    public int getDataSize() 
    {
        return data.size();
    }

    public void removeAll ()
    {
        data.removeAllElements ();
        fireChange ();
    }

    public MessageBrowserMessage getRow (int index) 
    {
        return (MessageBrowserMessage) data.elementAt (index);
    }

    //*** Return value of -1 indicates that row does not exist ***
    public int getRowIndex (String creationTime, String messageText) 
    {
        int i;
        MessageBrowserMessage msg;
        int res = -1;

        for (i = 0; i < data.size(); i++) 
        {
            msg = (MessageBrowserMessage) data.elementAt (i);
            res = msg.getRowIndex (creationTime, messageText);

            if (res == 1)
                return i;
        }
        return res;
    }

    public int getColumnCount ()
    {
        return colModel.getDisplayableColumns ();
    }

    public int getRowCount ()
    {
        return data.size ();
    }

    private Object getValueForAttributeFromMessage (int row, Symbol attributeName)
    {
        MessageBrowserMessage msg = (MessageBrowserMessage) data.elementAt (row);
        return msg.getValueForAttributeFromMessage (attributeName);
    }

    private Object castAttributeValue (Object attributeValue, String attributeType, String boolStr)
    {
        if (attributeType.equals("Boolean")) 
        {
            if (attributeValue.toString().equals (boolStr))
                return new Boolean (true);
            else
                return new Boolean (false);
        }
        else if (attributeType.equals ("int") || attributeType.equals ("integer-cell"))
                return (Integer) attributeValue;
        else if (attributeType.equals ("String") || attributeType.equals ("text-cell"))
                return attributeValue.toString ();
        else
                return attributeValue;
    }

    public String getColumnName (int column) 
    {
        MessageBrowserColumn col = colModel.getColumn (column);
        return col.getColName ();
    }

    public Object getValueAt (int row, int col) 
    {
        MessageBrowserColumn column = colModel.getColumn (col);
        String colName = column.getColName ();
        Symbol attributeName = column.getG2AttributeName ();
        String attributeType = column.getAttributeType ();
        Object attributeValue = getValueForAttributeFromMessage (row, attributeName);
        String boolStr = column.getBoolTag ();
        return castAttributeValue (attributeValue, attributeType, boolStr);
    }

    public Class getColumnClass (int col)
    {
        //*** Catching ArrayIndexOutOfBoundsException here temporarily ***
        try 
        {
            Object obj = getValueAt (0, col);
            return obj.getClass();
        } 
        catch (ArrayIndexOutOfBoundsException aiobe)    { return null; }
    }

    public boolean isCellEditable (int row, int col)
    {
        return false;
    }

    public void setValueAt (Object aValue, int row, int column) 
    {
        MessageBrowserMessage msg = (MessageBrowserMessage) data.elementAt (row);
        String colName = getColumnName (column);
        msg.setValueAt  (aValue, row, column, colName);
    }

    public void fireChange () 
    {
        fireTableDataChanged ();
        sorter.sortByColumn (sorter.getLastSortedColumn (), sorter.isSortOrderAscending ());
    }

    public void fireChangeNoSort () 
    {
        fireTableDataChanged ();
    }

    public void fireSorterTableChanged() 
    {
        sorter.fireSorterTableChanged ();
    }
}
