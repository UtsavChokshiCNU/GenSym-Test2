/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2CellRenderer.java
 *
 */

package com.gensym.jcontrols;

import java.io.IOException;
import java.awt.Component;
import javax.swing.JList;
import javax.swing.JLabel;
import javax.swing.ListCellRenderer;
import javax.swing.UIManager;
import javax.swing.border.Border;
import javax.swing.border.EmptyBorder;
//import javax.swing.

import com.gensym.controls.FieldType;
import com.gensym.controls.Formatter;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.NoSuchAttributeException;

class G2CellRenderer extends JLabel implements ListCellRenderer {

  static final long serialVersionUID = -8343996553693877944L;
  private static final Border noFocusBorder = new EmptyBorder(1, 1, 1, 1);

  public G2CellRenderer() {
    this(new FieldType(), null);
  }

  public G2CellRenderer(G2Listbox list) {
    this(new FieldType(), list);
  }

  public G2CellRenderer(FieldType fieldType, G2Listbox list) {
    setOpaque(true);
    setBorder(noFocusBorder);
    setFieldType(fieldType);
    // setting here to avoid deadlock during getListCellRendereComponent
    if (list != null)
      setFont(list.getFont());
  }

  private Formatter formatter;

  public Formatter getFormatter(){
      return formatter;
  }

  public void setFormatter(Formatter formatter){
    this.formatter = formatter;
    if ("Attribute".equals(formatter.getStyle()))
      structureAttribute = Symbol.intern(formatter.getAttributeName());
    else
      structureAttribute = null;
  }

  private FieldType fieldType;

  public FieldType getFieldType(){
      return fieldType;
  }

  public void setFieldType(FieldType fieldType){
    this.fieldType = fieldType;
  }

  private Symbol structureAttribute;

  public Symbol getStructureAttribute(){
      return structureAttribute;
  }

  public void setStructureAttribute(Symbol structureAttribute){
    this.structureAttribute = structureAttribute;
  }

  @Override
  public Component getListCellRendererComponent(JList list,
						Object value,
						int index,
						boolean isSelected,
						boolean cellHasFocus)
  {
    try {
      // fix this: don't know if we should continue to support
      // formatter

      if (value instanceof Structure &&
	  "Attribute".equals(formatter.getStyle())) {
	//value = ((Structure)value).getAttributeValue(structureAttribute);
	setText(formatter.format(value));
      } else {
	setText(fieldType.objectToString(value));
      }
    } catch (IOException ioe) {
      // fix this: do i18n
      setText("***ERROR. " + fieldType + " unable to format " + value);
//     } catch (NoSuchAttributeException nsae) {
//       setText("***ERROR. " + fieldType + " unable to format " + value);
    }
    if (isSelected) {
      setBackground(list.getSelectionBackground());
      setForeground(list.getSelectionForeground());
    }
    else {
      setBackground(list.getBackground());
      setForeground(list.getForeground());
    }
    setEnabled(list.isEnabled());
    // setting here causes a deadlock during initialization
    //setFont(list.getFont());
    setBorder(cellHasFocus ? UIManager.getBorder("List.focusCellHighlightBorder") : noFocusBorder);
    return this;
  }
}
