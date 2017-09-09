package com.gensym.gda.queues;

import java.util.Vector;
import com.gensym.util.Symbol;

public class MessageBrowserColumnModel extends Object 
{
    private Vector columns;

    public MessageBrowserColumnModel () 
    {
        columns = new Vector (20, 5);
    }

    public void addColumn (MessageBrowserColumn newColumn)
    {
        //### System.out.println ("MBColMod:  " + newColumn.toString());
        columns.addElement (newColumn);
    }

    public void addColumns (MessageBrowserColumn[] columns)
    {
        for (int i=0; i < columns.length; i++)
            addColumn (columns[i]);

        //hardcoded to enable sorting on creation-time to work at all times
        // irrespective of the column being displayed
        if (getColumnIndex (Symbol.intern ("GQM-CREATION-TIME")) < 0) 
        {
            MessageBrowserColumn col = new MessageBrowserColumn ("Time", 1, 1, 1, 1, 
                            Symbol.intern ("GQM-CREATION-TIME"), "String", "CREATED");
            addColumn (col);
        }
    }

    public MessageBrowserColumn getColumn (int index)
    {
        return (MessageBrowserColumn) columns.elementAt (index);
    }

    //*** getColumnIndex() returns -1 if no match is found for g2AttrName ***
    public int getColumnIndex (Symbol g2AttrName) 
    {
        int ind = -1;
        MessageBrowserColumn col;
        
        for (int i = 0 ; i < columns.size (); i++) 
        {
            col = (MessageBrowserColumn) columns.elementAt (i);
            if (col.getG2AttributeName().equals (g2AttrName)) 
            {
                ind = i;
                break;
            }
        }
        return ind;
    }

    public int getDisplayableColumns () 
    {
        int i;
        int count = 0;
        MessageBrowserColumn col;
        
        for (i = 0; i < columns.size(); i++) 
        {
            col = (MessageBrowserColumn) columns.elementAt (i);
            if (col.getDisplayProperty () == 1)
                count++;
        }
        return count;
    }
    
    public String toString ()
    {
        String s = new String ("MessageBrowserColumnModel:  columns=" + columns.size () + "  Displayable columns=" + getDisplayableColumns ());
        return s;
    }

}
