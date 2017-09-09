/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 BrowserMessageLineView.java
 *
 */

package com.gensym.gda.queues;

import java.awt.Component;
import java.awt.Color;
import java.awt.Font;
import javax.swing.JTable;
import javax.swing.JTextArea;
import javax.swing.table.TableCellRenderer;
import javax.swing.border.Border;
import javax.swing.border.EmptyBorder;
import javax.swing.UIManager;
import java.io.Serializable;
import com.gensym.classes.modules.gqm.GqmEntry;
import com.gensym.classes.modules.gda.GdaAlarmEntry;

public class BrowserMessageLineView extends JTextArea implements TableCellRenderer, Serializable 
{
    protected static Border noFocusBorder;

    public BrowserMessageLineView () 
    {
        super ();
        setLineWrap (true);
        setWrapStyleWord (false);
        noFocusBorder = new EmptyBorder (1, 2, 1, 2);
        setOpaque (true);
        setBorder (noFocusBorder);
    }

    public void updateUI () 
    {
        super.updateUI ();
        setForeground (null);
        setBackground (null);
    }

    public Component getTableCellRendererComponent (JTable table, Object value,
            boolean isSelected, boolean hasFocus, int row, int column) 
    {    
        if (table.isRowSelected (row)) 
        {
            super.setForeground (table.getSelectionForeground ());
            super.setBackground (table.getSelectionBackground ());
        }
        else 
        {
            super.setForeground (getForegroundColor (table, row));
            super.setBackground (getBackgroundColor (table, row));   
        }

        setFont (table.getFont ());
        setBorder (noFocusBorder);
        setValue (value);
        return this;
    }

    protected void setValue (Object value) 
    {
        setText ((value == null) ? "" : value.toString ());
    }

    private Color getBackgroundColor (JTable table, int rowNumber)
    {
        if (table instanceof MessageBrowserTable) 
        {
            try 
            {
                MessageBrowserMessage msg = ((MessageBrowserTable) table).getRow (rowNumber);
                return msg.getBackgroundColor ();
            }
            catch (ArrayIndexOutOfBoundsException aiobe)    { return Color.gray;}
        }
        else
            return Color.white;
    }

    private Color getForegroundColor (JTable table, int rowNumber) 
    {
        if (table instanceof MessageBrowserTable) 
        {
            try 
            {
                MessageBrowserMessage msg = ((MessageBrowserTable) table).getRow (rowNumber);
                return msg.getForegroundColor ();
            }
            catch (ArrayIndexOutOfBoundsException aiobe) { return Color.black; }
        }
        else
            return Color.black;
    }
}
