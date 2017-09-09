package com.gensym.wksp;

import java.awt.Component;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JTextField;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;

public class EvaluationPanel extends CellPanel {

  private static Symbol CELL_EVALUATION_ATTRIBUTES_ = Symbol.intern("CELL-EVALUATION-ATTRIBUTES"),
    PRIORITY_ = Symbol.intern("PRIORITY"),
    SCAN_INTERVAL_ = Symbol.intern("SCAN-INTERVAL"),
    INITIAL_SCAN_WAIT_INTERVAL_ = Symbol.intern("INITIAL-SCAN-WAIT-INTERVAL"),
    VALUE_DOMAIN_ = Symbol.intern("VALUE-DOMAIN"),
    UPDATE_ONLY_WHEN_SHOWN_ = Symbol.intern("UPDATE-ONLY-WHEN-SHOWN"),
    TRACE_MESSAGE_LEVEL_FOR_COMPUTATION_STYLE_ = Symbol.intern("TRACE-MESSAGE-LEVEL-FOR-COMPUTATION-STYLE"),
    WARNING_MESSAGE_LEVEL_FOR_COMPUTATION_STYLE_ = Symbol.intern("WARNING-MESSAGE-LEVEL-FOR-COMPUTATION-STYLE"),
    BREAK_MESSAGE_LEVEL_FOR_COMPUTATION_STYLE_ = Symbol.intern("BREAK-MESSAGE-LEVEL-FOR-COMPUTATION-STYLE"),
    TIME_OUT_WHEN_REQUESTING_DATA_SEEKING_ = Symbol.intern("TIME-OUT-WHEN-REQUESTING-DATA-SEEKING"),
    MAY_REQUEST_EVENT_UPDATES_ = Symbol.intern("MAY-REQUEST-EVENT-UPDATES"),
    MAY_REQUEST_DATA_SEEKING_ = Symbol.intern("MAY-REQUEST-DATA-SEEKING");
  private static Object[] domainVals = new Object[3];
  private static Object[] debugOptions = new Object[5];
  static {
    domainVals[0] = "";
    domainVals[1] = "g2-simulator";
    domainVals[2] = "inference-engine";
    debugOptions[0] = "";
    debugOptions[1] = new Integer(0);
    debugOptions[2] = new Integer(1);
    debugOptions[3] = new Integer(2);
    debugOptions[4] = new Integer(3);
  }
  
  public EvaluationPanel (Structure cellInfo) {
    super(cellInfo);
    populatePanel(null, 10);
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
    symbols.add(TRACE_MESSAGE_LEVEL_FOR_COMPUTATION_STYLE_);
    symbols.add(WARNING_MESSAGE_LEVEL_FOR_COMPUTATION_STYLE_);
    symbols.add(BREAK_MESSAGE_LEVEL_FOR_COMPUTATION_STYLE_);
 }

  @Override
  protected void populatePanel(Symbol structureName, int width) {
    Structure evalAttrs = (Structure)cellInfo.getAttributeValue(CELL_EVALUATION_ATTRIBUTES_, new Structure());

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
	((JComboBox)textAreas.elementAt(k)).setSelectedItem(evalAttrs.getAttributeValue((Symbol)symbols.elementAt(k), ""));
	add((Component)textAreas.elementAt(k));
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
    Structure evalAttrs = new Structure();
    Structure tracingStuff = new Structure();
    String cellVal;
    boolean empty = true;
    boolean noTrace = true;
    boolean cellBool;
    Object cellObj;
    
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
      if (cellObj instanceof Integer) {
	noTrace = false;
	evalAttrs.setAttributeValue((Symbol)symbols.elementAt(k),
				    cellObj);
      } 
    }
    for (int j = 4; j<7; j++) {
      cellBool = ((JCheckBox)textAreas.elementAt(j)).isSelected();
      evalAttrs.setAttributeValue((Symbol)symbols.elementAt(j),
				  new Boolean(cellBool));
    }
    return evalAttrs;
  }
}
