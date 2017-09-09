package com.gensym.wksp;

import java.awt.Component;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JTextField;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;

public class ExpressionPanel extends CellPanel {

  private JTextField expression;
  private static Symbol EXPRESSION_ = Symbol.intern("EXPRESSION"),
    CELL_EVALUATION_ATTRIBUTES_ = Symbol.intern("CELL-EVALUATION-ATTRIBUTES"),
    PRIORITY_ = Symbol.intern("PRIORITY"),
    SCAN_INTERVAL_ = Symbol.intern("SCAN-INTERVAL"),
    INITIAL_SCAN_WAIT_INTERVAL_ = Symbol.intern("INITIAL-SCAN-WAIT-INTERVAL"),
    VALUE_DOMAIN_ = Symbol.intern("VALUE-DOMAIN"),
    UPDATE_ONLY_WHEN_SHOWN_ = Symbol.intern("UPDATE-ONLY-WHEN-SHOWN"),
    TRACING_MESSAGE_LEVEL_ = Symbol.intern("TRACING-MESSAGE-LEVEL"),
    WARNING_MESSAGE_LEVEL_ = Symbol.intern("WARNING-MESSAGE-LEVEL"),
    BREAKPOINT_LEVEL_ = Symbol.intern("BREAKPOINT-LEVEL"),
    TIME_OUT_WHEN_REQUESTING_DATA_SEEKING_ = Symbol.intern("TIME-OUT-WHEN-REQUESTING-DATA-SEEKING"),
    MAY_REQUEST_EVENT_UPDATES_ = Symbol.intern("MAY-REQUEST-EVENT-UPDATES"),
    MAY_REQUEST_DATA_SEEKING_ = Symbol.intern("MAY-REQUEST-DATA-SEEKING"),
    TRACING_AND_BREAKPOINTS_ = Symbol.intern("TRACING-AND-BREAKPOINTS");
  private static Object[] domainVals = new Object[3];
  private static Object[] debugOptions = new Object[4];
  static {
    domainVals[0] = "";
    domainVals[1] = "g2-simulator";
    domainVals[2] = "inference-engine";
    debugOptions[0] = new Integer(0);
    debugOptions[1] = new Integer(1);
    debugOptions[2] = new Integer(2);
    debugOptions[3] = new Integer(3);
  }
  
  public ExpressionPanel (Structure cellInfo) {
    super(cellInfo);
    populatePanel(EXPRESSION_, 10);
  }

  @Override
  protected void populateVectors() {
    super.populateVectors();
    labels.add("Priority:");
    labels.add("Scan Interval:");
    labels.add("Initial Scan Wait Interval:");
    labels.add("Time Out When Requesting Data Seeking:");
    labels.add("Update Only When Shown:");
    labels.add("May Request Event Updates:");
    labels.add("May Request Data Seeking:");
    labels.add("Value Domain:");
    labels.add("Trace Message Level:");
    labels.add("Warning Message Level:");
    labels.add("Break Message Level:");
    symbols.add(PRIORITY_);
    symbols.add(SCAN_INTERVAL_);
    symbols.add(INITIAL_SCAN_WAIT_INTERVAL_);
    symbols.add(TIME_OUT_WHEN_REQUESTING_DATA_SEEKING_);
    symbols.add(UPDATE_ONLY_WHEN_SHOWN_);
    symbols.add(MAY_REQUEST_EVENT_UPDATES_);
    symbols.add(MAY_REQUEST_DATA_SEEKING_);
    symbols.add(VALUE_DOMAIN_);
    symbols.add(TRACING_MESSAGE_LEVEL_);
    symbols.add(WARNING_MESSAGE_LEVEL_);
    symbols.add(BREAKPOINT_LEVEL_);
 }

  @Override
  protected void populatePanel(Symbol structureName, int width) {
    Structure evalAttrs = (Structure)cellInfo.getAttributeValue(CELL_EVALUATION_ATTRIBUTES_, new Structure());

      add(setupLabel("Expression:"));
      expression = setupTextArea(cellInfo.getAttributeValue(structureName, "").toString(), width);
      add(expression);
      for (int i=0; i<4; i++) {
	add(setupLabel(labels.elementAt(i).toString()));
	textAreas.add(setupTextArea(evalAttrs.getAttributeValue
				    ((Symbol)symbols.elementAt(i),
				     "").toString().toLowerCase(), width));
	add((Component)textAreas.elementAt(i));
      }
      for (int j=4; j<7; j++) {
	add(setupLabel(labels.elementAt(j).toString()));
	textAreas.add(setupCheckBox(new Boolean(evalAttrs.getAttributeValue
				    ((Symbol)symbols.elementAt(j),
				     "").toString().toLowerCase())));
	add((Component)textAreas.elementAt(j));
      }
      add(setupLabel(labels.elementAt(7).toString()));
      textAreas.add(setupComboBox(domainVals));
      add((Component)textAreas.elementAt(7));
      ((JComboBox)textAreas.elementAt(7)).setSelectedItem(evalAttrs.getAttributeValue((Symbol)symbols.elementAt(7), "").toString().toLowerCase());
      for (int k=8; k<11; k++) {
	add(setupLabel(labels.elementAt(k).toString()));
	textAreas.add(setupComboBox(debugOptions));
	add((Component)textAreas.elementAt(k));
      }
      Structure tracingStuff = (Structure)evalAttrs.getAttributeValue(TRACING_AND_BREAKPOINTS_, null);
      if (tracingStuff != null) {
	for (int i=8; i<11; i++) {
	  ((JComboBox)textAreas.elementAt(i)).setSelectedItem(tracingStuff.getAttributeValue((Symbol)symbols.elementAt(i), ""));
	}
      }
  }

  private JCheckBox setupCheckBox (Boolean value) {
    GridBagConstraints gbc = new GridBagConstraints();
    JCheckBox box;
    if (value != null)
      box = new JCheckBox("", value.booleanValue());
    else box = new JCheckBox();
    gbc.anchor = GridBagConstraints.WEST;
    gbc.insets = new Insets(1, 15, 1, 2);
    gbc.gridwidth = GridBagConstraints.REMAINDER;
    thisLayout.setConstraints(box, gbc);
    return box;
  }
  
  private JComboBox setupComboBox(Object[] choices) {
    GridBagConstraints gbc = new GridBagConstraints();
    JComboBox box = new JComboBox(choices);

    gbc.anchor = GridBagConstraints.EAST;
    gbc.insets = new Insets(1, 15, 1, 2);
    gbc.gridwidth = GridBagConstraints.REMAINDER;
    gbc.fill = GridBagConstraints.HORIZONTAL;
    thisLayout.setConstraints(box, gbc);
    return box;
  }
  
  @Override
  protected Structure getResults() {
    Structure contents = new Structure();
    Structure evalAttrs = new Structure();
    Structure tracingStuff = new Structure();
    String cellVal;
    boolean empty = true;
    boolean noTrace = true;
    boolean cellBool;
    Object cellObj;
    
    cellVal = expression.getText();
    if (cellVal.compareTo("") != 0) {
      contents.setAttributeValue(EXPRESSION_, cellVal);
      for (int i=0; i<4; i++) {
	cellVal = ((JTextField)textAreas.elementAt(i)).getText();
	if (cellVal.compareTo("") != 0) {
	  empty = false;
	  evalAttrs.setAttributeValue((Symbol)symbols.elementAt(i),
				      new Integer(cellVal));
	}
      }
      cellVal = ((JComboBox)textAreas.elementAt(7)).getSelectedItem().toString();
      if (cellVal.compareTo("") != 0) {
	empty = false;
	evalAttrs.setAttributeValue((Symbol)symbols.elementAt(7),
				    Symbol.intern(cellVal.toUpperCase()));
      }
      for (int k = 8; k<11; k++) {
	cellObj = ((JComboBox)textAreas.elementAt(k)).getSelectedItem();
	noTrace = false;
	tracingStuff.setAttributeValue((Symbol)symbols.elementAt(k),
				       cellObj);
      }
      if (!noTrace)
	evalAttrs.setAttributeValue(TRACING_AND_BREAKPOINTS_, tracingStuff);
      for (int j = 4; j<7; j++) {
	cellBool = ((JCheckBox)textAreas.elementAt(j)).isSelected();
	evalAttrs.setAttributeValue((Symbol)symbols.elementAt(j),
				    new Boolean(cellBool));
      }
      if (!empty)
	contents.setAttributeValue(CELL_EVALUATION_ATTRIBUTES_, evalAttrs);
      return contents;
    } else return null;
  }
}
