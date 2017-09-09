/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 MessageBrowserMessage.java
 *
 */

package com.gensym.gda.queues;

import com.gensym.util.Symbol;
import java.awt.Color;

public interface MessageBrowserMessage 
{
    public void hashImportantAttributes ();
    public int getRowIndex (String creationTime, String messageText);
    public Object getValueForAttributeFromMessage (Symbol attributeName);
    public void setValueForAttributeFromMessage (Symbol attributeName, Object value);
    public void setValueAt (Object aValue, int row, int column, String colName);
    public Color getBackgroundColor();
    public Color getForegroundColor();
}
