package com.gensym.editor.icon.dlgs;

import javax.swing.JPanel;
import javax.swing.JTable;
import javax.swing.JComboBox;
import javax.swing.JScrollPane;
import javax.swing.DefaultCellEditor;
import com.gensym.editor.icon.shell.IconEditorSimulationCommands;
import com.gensym.editor.icon.core.VariableSimulationTableModel;
import com.gensym.editor.icon.core.Parameter;
import com.gensym.editor.icon.simulation.SimulationExpression;
import java.awt.Dimension;

public class VariableSimulationEditPanel extends JPanel {

  private VariableSimulationTableModel model;
  
  public VariableSimulationEditPanel(VariableSimulationTableModel model)
  {
    this.model = model;
    JTable table = new JTable(model);
    JComboBox comboBox =
      new JComboBox(IconEditorSimulationCommands.expressionKeyMap.keySet().toArray());
    table.setDefaultEditor(String.class, new DefaultCellEditor(comboBox));
    JScrollPane scrollpane = new JScrollPane(table);
    scrollpane.setPreferredSize(new Dimension(500,200));    
    add(scrollpane);
  }

  public VariableSimulationTableModel getModel() {
    return model;
  }
  
  public void saveResults() {
    Parameter[] params = model.getParameters();
    String[] keys = model.getExpressionKeys();
    for (int i=0;i<params.length;i++) {
      Parameter param = params[i];
      String oldKey = param.getSimulationPreferenceKey();
      String newKey = keys[i];
      if (newKey == null)
	newKey = IconEditorSimulationCommands.SCALAR;
      if (oldKey == null)
	oldKey = IconEditorSimulationCommands.SCALAR;
      if (!(oldKey.equals(newKey))) {
	Object  oldExpression =
	  IconEditorSimulationCommands.expressionKeyMap.get(oldKey);
	if (oldExpression instanceof SimulationExpression) 
	  ((SimulationExpression)oldExpression).removeVariableListener(param, oldKey);
	Object newExpression =
	  IconEditorSimulationCommands.expressionKeyMap.get(newKey);
	if (newExpression instanceof SimulationExpression) 
	  ((SimulationExpression)newExpression).addVariableListener(param, newKey);	
	param.setSimulationPreferenceKey(newKey);
      }
    }
  }
  
}
