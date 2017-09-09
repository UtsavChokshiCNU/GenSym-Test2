
//Title:        G2 Studio
//Version:      
//Copyright:    Copyright (c) 1999
//Author:       fy
//Company:      gensym
//Description:  Your description

package com.gensym.editor.text;

import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

public class G2FreeTextFontSizePanel extends JPanel {
  private Object[] fontSizes = new Object [] {"","8", "9", "10", "11", "12", "14",
                                     "16", "18", "20", "22", "24", "26",
                                     "28", "30", "32", "34", "36", "48","72"};
  private JComboBox jComboBox = new JComboBox(fontSizes);
  private JLabel jLabel = new JLabel();
  private FlowLayout flowLayout = new FlowLayout(1, 2, 15);

  public G2FreeTextFontSizePanel() {
    try  {
      jbInit();
    }
    catch(Exception ex) {
      ex.printStackTrace();
    }
  }

  public int getSelectedFontSize () {
    if (jComboBox.getSelectedIndex() == 0) return 0;
    String selectedSize = (String) jComboBox.getSelectedItem();
    return (new Integer(selectedSize)).intValue();
  }

  private void jbInit() throws Exception {
    this.setLayout(flowLayout);
    jLabel.setText("Font Size:");

    this.add(jLabel);
    this.add(jComboBox);
  }

}                                                                          
