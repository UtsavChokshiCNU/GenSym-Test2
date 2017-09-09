package com.gensym.wksp;

import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import java.util.Vector;
import javax.swing.border.LineBorder;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;

public class CellPanel extends JPanel {

  protected Structure cellInfo;
  protected GridBagLayout thisLayout;
  protected Vector labels, textAreas, symbols;
  
  public CellPanel (Structure cellInfo) {
    thisLayout = new GridBagLayout();
    setLayout(thisLayout);
    this.cellInfo = cellInfo;
    populateVectors();
  }

  protected JLabel setupLabel(String labelText) {
    JLabel label = new JLabel();
    GridBagConstraints labelConstraints = new GridBagConstraints();
    labelConstraints.anchor = GridBagConstraints.EAST;
    labelConstraints.insets = new Insets(1,2,1,2);

    label.setText(labelText);
    thisLayout.setConstraints(label, labelConstraints);
    return label;
  }

  protected JTextField setupTextArea(String contents, int width) {
    GridBagConstraints textAreaConstraints = new GridBagConstraints();
    textAreaConstraints.gridwidth = GridBagConstraints.REMAINDER;
    textAreaConstraints.insets = new Insets(1,2,1,2);

    JTextField textArea = new JTextField(contents);
    textArea.setColumns(width);
    textArea.setBorder(new LineBorder(Color.black));
    thisLayout.setConstraints(textArea, textAreaConstraints);
    textArea.setMinimumSize(new Dimension(100, 20));
    return textArea;
  }
  
  protected void populatePanel(Symbol structureName, int width) {
    Structure settings = (Structure)cellInfo.getAttributeValue
      (structureName, new Structure());
    for (int i=0; i<labels.size(); i++) {
      add(setupLabel(labels.elementAt(i).toString()));
      textAreas.add(setupTextArea(settings.getAttributeValue
				  ((Symbol)symbols.elementAt(i),
				   "").toString().toLowerCase(), width));
      add((Component)textAreas.elementAt(i));
    }
  }
  
  protected Structure getResults() {
    Structure retVal = new Structure();
    String tempVal;
    boolean empty = true;

    for (int i=0; i<textAreas.size(); i++) {
      tempVal = ((JTextField)textAreas.elementAt(i)).getText();
      if (tempVal.compareTo("") != 0) {
	retVal.setAttributeValue((Symbol)symbols.elementAt(i),
				 new Integer(tempVal));
	empty = false;
      }
    }
    if (empty) return null; else return retVal;
  }

  protected void populateVectors() {
    labels = new Vector();
    symbols = new Vector();
    textAreas = new Vector();
  }

}
