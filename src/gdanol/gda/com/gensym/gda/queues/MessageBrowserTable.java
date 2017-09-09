package com.gensym.gda.queues;

import java.awt.Color;
import javax.swing.*;
import javax.swing.table.*;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.TwAccess;
import com.gensym.util.Symbol;

public class MessageBrowserTable extends JTable
{
    private int modelRowCount = 0;
    private MessageBrowserTableModel tableModel;
    private TwAccess cxn;
    private TableSorter sorterInstance;
    private Symbol sourceName;
    
    private static final Symbol OBJ_ = Symbol.intern ("OBJ");
    private static final Symbol NAME_ = Symbol.intern ("NAME");

    public MessageBrowserTable (TwAccess con, 
                                MessageBrowserColumnModel columnModel)
    {
        this (con, columnModel, new MessageBrowserTableModel (columnModel));
    }

    private MessageBrowserTable (TwAccess con,
                                MessageBrowserColumnModel columnModel,
                                MessageBrowserTableModel tableModel)
    {
        this (con, columnModel, tableModel, new TableSorter (tableModel));
    }

    private MessageBrowserTable (TwAccess con,
                                MessageBrowserColumnModel columnModel,
                                MessageBrowserTableModel tableModel,
                                TableSorter sorter)
    {
        super (sorter);
        cxn = con;
        this.tableModel = tableModel;
        this.sorterInstance = sorter;
        tableModel.addSorter (sorter);
        sorter.addMouseListenerToHeaderInTable (this); 
        setCellSelectionEnabled (false);
        setColumnSelectionAllowed (false);
        setSelectionForeground (Color.white);
        setSelectionBackground (Color.black);
        setDefaultRenderer (String.class, new BrowserMessageLineView ());
        setDefaultRenderer (Integer.class, new  BrowserMessageLineView());
        setDefaultRenderer (Double.class, new BrowserMessageLineView ());
        setDefaultRenderer (Symbol.class, new BrowserMessageLineView ());
    }

    public MessageBrowserTableModel getTableModel () 
    {
        return tableModel;
    }

    public TableSorter getTableSorter () 
    {
        return sorterInstance;
    }

    public TwAccess getContext ()
    {
        return cxn;
    }
    
    public void setSourceName (Symbol srcName)
    {
        sourceName = srcName;
    }
    
    public Symbol getSourceName ()
    {
        return sourceName;
    }

    public void setColumnWidths (int [] widthArray)
    {
        int cCount = getColumnCount ();
        int wCount = widthArray.length;
        MessageBrowserTableModel tableModel = getTableModel ();
        MessageBrowserColumnModel mbColModel = tableModel.getColumnModel();
        TableColumnModel colModel = getColumnModel ();
        
        //*** Sets widths according to the following scheme: ***
        //***  If matching width array element is > 0 --> sets width to element value ***
        //***  If matching width array element is <= 0 sets default width ***
        //***  If width array is shorter than columns --> no change for missing values ***
        //***  Extraneous width values are ignored ***   

        for (int x = 0; x < cCount; x++)
        {
            TableColumn column = colModel.getColumn (x);
            
            if (x >= wCount)    //*** Don't change if missing value ***
                continue;
            if (widthArray [x] <= 0)    //*** Use default ***
            {
                MessageBrowserColumn mbColumn = mbColModel.getColumn (x);
                column.setPreferredWidth (mbColumn.getDefaultWidth ());
            }
            else    //*** Change to specified width ***
                column.setPreferredWidth (widthArray [x]);
        }
    }

    public void toggleSortOrder () 
    {
        sorterInstance.toggleSortOrder (this);
    }

    public void sortTable (int sortcol) 
    {
        sorterInstance.sortTable (this, sortcol);
    }

    public boolean isSortOrderAscending () 
    {
        return sorterInstance.isSortOrderAscending ();
    }

    public boolean getLockView () 
    {
        return tableModel.getLockView ();
    }

    public MessageBrowserMessage getRow (int i) 
    {
        return tableModel.getRow (sorterInstance.getRowMapping (i));
    }
}



