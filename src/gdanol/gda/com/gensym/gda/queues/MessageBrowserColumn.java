package com.gensym.gda.queues;

import javax.swing.table.*;
import com.gensym.util.Symbol;

public class MessageBrowserColumn extends TableColumn 
{
    private String columnName;
    private int display;
    private int defaultWidth;
    private Symbol g2AttributeName;
    private String attributeType;
    private String boolTag;

    public MessageBrowserColumn (String colNam, int show, int maxW, int minW, int defaultWidth, 
                    Symbol g2AttributeName, String attributeType, String boolStr) 
    {
        super.setMaxWidth (maxW);
        super.setMinWidth (minW);
        super.setPreferredWidth (defaultWidth);
        columnName = colNam;
        display = show;
        this.g2AttributeName = g2AttributeName;
        this.attributeType = attributeType;
        this.defaultWidth = defaultWidth;
        this.boolTag = boolStr;
    }

    public String getBoolTag ()
    {
        return boolTag;
    }

    public String getName ()
    {
        return columnName;
    }

    public int getDefaultWidth ()
    {
        return defaultWidth;
    }

    public Symbol getG2AttributeName ()
    {
        return g2AttributeName;
    }

    public String getAttributeType ()
    {
        return attributeType;
    }

    public String getColName () 
    {
        return columnName;
    }

    public void showColumn () 
    {
        display = 1;
    }

    public void hideColumn () 
    {
        display = 0;
    }

    public void setDisplayProperty (int show) 
    {
        display = show;
    }

    public int getDisplayProperty () 
    {
        return display;
    }
    
    public String toString ()
    {
        String s = new String ("MessageBrowserColumn -  columnName: " + columnName + "  display: " + display + 
                            "  g2AttributeName: " + g2AttributeName + "  attributeType: " + attributeType + 
                            "  boolTag: " + boolTag + "  defWidth: " + defaultWidth + "  minWidth: " + minWidth + "  maxWidth: " + maxWidth);
        return s;
    }
    
}
