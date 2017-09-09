package com.gensym.editor.icon.dlgs;

import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.JComboBox;
import javax.swing.JScrollPane;
import javax.swing.JLabel;
import javax.swing.JTable;
import javax.swing.table.TableModel;
import javax.swing.JButton;
import java.awt.BorderLayout;
import javax.swing.SwingConstants;
import java.awt.Frame;
import java.util.Vector;
import java.awt.Container;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.CommandConstants;
import java.awt.GridLayout;
import com.gensym.editor.icon.core.Parameter;
import com.gensym.editor.icon.core.IconEditorCanvas;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import java.awt.GridBagLayout;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Color;
import javax.swing.DefaultCellEditor;
import com.gensym.dlg.InputDialog;
import com.gensym.editor.icon.core.Evaluator;
import com.gensym.editor.icon.core.VariableTableModel;
import com.gensym.editor.icon.core.BadValueForTypeException;
import com.gensym.dlg.ErrorDialog;
import com.gensym.editor.icon.core.VariableSimulationTableModel;

public class CanvasPropertiesDialog extends StandardDialog implements CommandConstants {
  private PropertiesPanel propertiesPanel;
  IconEditorCanvas canvas;

  public static final int VARIABLES_TAB = 0;
  public static final int SIMULATION_PARAMETERS_TAB = 1;
  
  public CanvasPropertiesDialog (Frame parent,
				 IconEditorCanvas canvas)
  {    
    super (parent, "Properties", true,
	   new String[] {OK_LABEL, CANCEL_LABEL},
	   new int[] {OK, CANCEL},
           new PropertiesPanel(canvas.getEvaluator()),
	   null);
    this.canvas = canvas;
    propertiesPanel= (PropertiesPanel) getDialogComponent ();
    pack ();
  }

  public void setSelectedTab(int index) {
    propertiesPanel.setSelectedTab(index);
  }
  
  @Override
  protected void dispatchCallback (int code) {
    if (code == OK) {
      Evaluator evaluator = canvas.getEvaluator();
      if (evaluator != null) 
	evaluator.setParameters(propertiesPanel.getParameters());
      propertiesPanel.vsep.saveResults();      
    }
   super.dispatchCallback(code);
  }
  
}
       
class PropertiesPanel extends com.gensym.uitools.utils.TabbedControlPanel
implements ActionListener
{
  static final String ADD = "Add";
  static final String REMOVE = "Remove";    
  VariableTableModel variablesModel;
  VariableSimulationEditPanel vsep;
  JComboBox comboBox;
  JTable table;

  PropertiesPanel(Evaluator evaluator)
  {
    this(new JButton(ADD),
	 new JButton(REMOVE),
	 evaluator.getVariableTableModel(),
	 new VariableSimulationEditPanel
	 (new VariableSimulationTableModel(evaluator.getParameters())));

  }

  Parameter[] getParameters() {
    return variablesModel.getParameters();
  }

  void setSelectedTab(int index) {
    tabbedPane.setSelectedIndex(index);
  }
  
  
  private static JScrollPane createScrollingTable(JTable table) {
    JScrollPane scrollpane = new JScrollPane(table);
    scrollpane.setPreferredSize(new Dimension(500,200));    
    return scrollpane;
  }

  PropertiesPanel(JButton addButton,
		  JButton removeButton,
		  VariableTableModel variablesModel,
		  VariableSimulationEditPanel vsep) {
    this(addButton, removeButton, variablesModel, new JTable(variablesModel), vsep);
  }
  
  PropertiesPanel(JButton addButton,
		  JButton removeButton,
		  VariableTableModel variablesModel,
		  JTable table,
		  VariableSimulationEditPanel vsep) {
    super(new Component[] {createScrollingTable(table), vsep},
    new String[] {"Variables", "Simulation Preferences"},
    new JButton[] {addButton, removeButton},
    new Component(){});
    this.variablesModel = variablesModel;
    this.table = table;
    this.vsep = vsep;
    Class[] defaultVariableTypes=variablesModel.getDefaultParameterTypes();    
    comboBox = new JComboBox(defaultVariableTypes);
    table.setDefaultEditor(Class.class, new DefaultCellEditor(comboBox));    
    addButton.addActionListener(this);
    removeButton.addActionListener(this);
  }

  @Override
  public void actionPerformed(ActionEvent ae) {
    String cmd = ae.getActionCommand();
    if (ADD.equals(cmd)) {
      //Class[] defaultVariableTypes=variablesModel.getDefaultParameterTypes();    
      //comboBox = new JComboBox(defaultVariableTypes);
      //USE comboBox instead of text field for Type
      InputDialog id = new InputDialog(null,
				       "New variable",
				       true,
				       new String[] {"Name", "Type", "Value"},
				       new String[] {"", "", ""},
				       null);
      id.setVisible(true);
      if (!id.wasCancelled()) {
	String[] results = id.getResults();
	Class type = null;
	try {
	  type = Class.forName(results[1]);
	} catch (ClassNotFoundException cnfe) {
	  System.out.println("COULDNT FIND CLASS" + results[1]);
	  type = Integer.class;
	}
	Object value = null;
	try {
	  value = variablesModel.castValue(results[2], type);
	} catch (BadValueForTypeException bvfte) {
	  (new ErrorDialog(null, "Bad value for type", true,
			   bvfte.getMessage(), null)).setVisible(true);
	  return;
	}
	Parameter newParam = new Parameter(results[0], type, value);
	int selectedIndex = table.getSelectedRow();
	int rowCount = table.getRowCount();
	if (selectedIndex == -1)
	  selectedIndex = rowCount-1;
	if (selectedIndex == rowCount)
	  selectedIndex = rowCount-1;
	variablesModel.addRow(newParam, selectedIndex+1);
	vsep.getModel().addRow(newParam, selectedIndex+1);
	comboBox.removeAllItems();
	Class[] choices = variablesModel.getDefaultParameterTypes();
	for (int i=0;i<choices.length;i++) 
	  comboBox.addItem(choices[i]);
      }
    } else if (REMOVE.equals(cmd)) {
      int selectedIndex = table.getSelectedRow();
      if (selectedIndex != -1) {
	Parameter param = variablesModel.getRow(selectedIndex);
	variablesModel.removeRow(param);
	vsep.getModel().removeRow(param);
      }
    }
  }
}

