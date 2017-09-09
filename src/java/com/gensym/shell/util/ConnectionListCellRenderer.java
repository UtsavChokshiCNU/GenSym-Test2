package com.gensym.shell.util;

import java.awt.Component;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.DefaultListCellRenderer;

import com.gensym.jgi.G2Access;

/**
 * @undocumented
 */
public class ConnectionListCellRenderer extends DefaultListCellRenderer {

   @Override
   public Component getListCellRendererComponent(JList list,
                                       Object value,
                                       int index,
                                       boolean isSelected,
                                        boolean cellHasFocus) {

        if (value instanceof G2Access)
            value = ((G2Access) value).toShortString();

        return super.getListCellRendererComponent(list,
                                        value,
                                        index,
                                        isSelected,
                                        cellHasFocus);

    }
    
}
