package com.gensym.wksp;

import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import javax.swing.border.LineBorder;
import javax.swing.JComboBox;
import javax.swing.JTextField;
import com.gensym.gcg.EditedBySubDialog;
import com.gensym.gcg.G2ColorField;
import com.gensym.gcg.SubDialogLauncher;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;

public class FormatPanel extends CellPanel {

  private static Symbol CELL_FORMAT_ = Symbol.intern("CELL-FORMAT"),
    BACKGROUND_COLOR_ = Symbol.intern("BACKGROUND-COLOR"),
    BORDER_COLOR_ = Symbol.intern("BORDER-COLOR"),
    TEXT_ALIGNMENT_ = Symbol.intern("TEXT-ALIGNMENT"),
    TEXT_SIZE_ = Symbol.intern("TEXT-SIZE"),
    TEXT_COLOR_ = Symbol.intern("TEXT-COLOR");
  private static Object[] textAlignOptions = new Object[4];
  private static Object[] fontOptions = new Object[4];
  static {
    textAlignOptions[0] = "";
    textAlignOptions[1] = "left";
    textAlignOptions[2] = "center";
    textAlignOptions[3] = "right";
    fontOptions[0] = "";
    fontOptions[1] = "small";
    fontOptions[2] = "large";
    fontOptions[3] = "extra-large";
  }
  public FormatPanel (Structure settings) {
    super(settings);
    populatePanel(CELL_FORMAT_, 20);
  }

  @Override
  protected void populateVectors() {
    super.populateVectors();
    labels.add("Border Color:");
    labels.add("Text Color:");
    labels.add("Text Alignment:");
    labels.add("Text Size:");
    labels.add("Background Color:");
    symbols.add(BORDER_COLOR_);
    symbols.add(TEXT_COLOR_);
    symbols.add(TEXT_ALIGNMENT_);
    symbols.add(TEXT_SIZE_);
    symbols.add(BACKGROUND_COLOR_);
  }
  protected G2ColorField setupColorArea(String contents, int width,
					Symbol attribute) {
    GridBagConstraints textAreaConstraints = new GridBagConstraints();
    textAreaConstraints.insets = new Insets(1,2,1,2);

    G2ColorField textArea = new G2ColorField();
    if (contents != "")
      textArea.setText(contents);
    textArea.setColumns(width);
    textArea.setBorder(new LineBorder(Color.black));
    thisLayout.setConstraints(textArea, textAreaConstraints);
    textArea.setMinimumSize(new Dimension(100, 20));
    textArea.setAttribute(attribute);
    return textArea;
  }
  
  @Override
  protected void populatePanel(Symbol structureName, int width) {
    Structure settings = (Structure)cellInfo.getAttributeValue
      (structureName, new Structure());
    SubDialogLauncher sdl;
    JComboBox comboBox;
    GridBagConstraints gbc = new GridBagConstraints();
    gbc.gridwidth = GridBagConstraints.REMAINDER;
    gbc.fill = GridBagConstraints.HORIZONTAL;
    gbc.insets = new Insets(1,2,1,2);

    for (int j = 0; j<2; j++) {
      add(setupLabel(labels.elementAt(j).toString()));
      textAreas.add(setupColorArea(settings.getAttributeValue
				((Symbol)symbols.elementAt(j),
				 "").toString().toLowerCase(), width-2,
				   (Symbol)symbols.elementAt(j)));
      add((Component)textAreas.elementAt(j));
      sdl = new SubDialogLauncher((EditedBySubDialog)textAreas.elementAt(j));
      thisLayout.setConstraints(sdl, gbc);
      add(sdl);
    }
    add(setupLabel(labels.elementAt(2).toString()));
    comboBox = new JComboBox(textAlignOptions);
    comboBox.setSelectedItem(settings.getAttributeValue
			     ((Symbol)symbols.elementAt(2),
			      "").toString().toLowerCase());
    textAreas.add(comboBox);
    thisLayout.setConstraints(comboBox, gbc);
    add((Component)textAreas.elementAt(2));
    add(setupLabel(labels.elementAt(3).toString()));
    comboBox = new JComboBox(fontOptions);
    comboBox.setSelectedItem(settings.getAttributeValue
			     ((Symbol)symbols.elementAt(3),
			      "").toString().toLowerCase());
    textAreas.add(comboBox);
    thisLayout.setConstraints(comboBox, gbc);
    add((Component)textAreas.elementAt(3));
    add(setupLabel(labels.elementAt(4).toString()));
    textAreas.add(setupTextArea(settings.getAttributeValue
				((Symbol)symbols.elementAt(4),
				 "").toString().toLowerCase(), width));
    add((Component)textAreas.elementAt(4));
   
  }
  
  @Override
  protected Structure getResults() {
    Structure retVal = new Structure();
    String tempVal;
    boolean empty = true;
    int last = textAreas.size()-1;

    tempVal = ((JTextField)textAreas.elementAt(last)).getText();
    if (tempVal.compareTo("") != 0) {
      if (tempVal.indexOf(' ') > -1)
	retVal.setAttributeValue((Symbol)symbols.elementAt(last),
				 tempVal);
      else
	retVal.setAttributeValue((Symbol)symbols.elementAt(last),
			       Symbol.intern(tempVal.toUpperCase()));
      empty = false;
    }
    for (int i=0; i<2; i++) {
      tempVal = ((G2ColorField)textAreas.elementAt(i)).getText();
      if (tempVal.compareTo("") != 0) {
	retVal.setAttributeValue((Symbol)symbols.elementAt(i),
				 Symbol.intern(tempVal.toUpperCase()));
	empty = false;
      }
    }
    for (int i=2; i<4; i++) {
      tempVal = ((JComboBox)textAreas.elementAt(i)).getSelectedItem().toString();
      if (tempVal.compareTo("") != 0) {
	retVal.setAttributeValue((Symbol)symbols.elementAt(i),
				 Symbol.intern(tempVal.toUpperCase()));
	empty = false;
      }
    }
    if (empty) return null; else return retVal;
  }
  
}
