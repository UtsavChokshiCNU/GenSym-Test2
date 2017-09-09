package com.gensym.uitools.inspect.trees;

import java.util.Enumeration;
import javax.swing.JTable;
import javax.swing.event.ListSelectionListener;
import javax.swing.tree.TreeNode;
import javax.swing.table.TableColumnModel;
import com.gensym.uitools.tables.ItemTableModel;
import com.gensym.ntw.TwAccess;
import com.gensym.util.Structure;
import com.gensym.classes.Item;
import com.gensym.classes.G2Definition;
import com.gensym.classes.ModuleInformation;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Module;
import com.gensym.ntw.util.BasicTreeNode;
import com.gensym.util.Symbol;
import com.gensym.uitools.tables.TableSorter;
import com.gensym.uitools.inspect.TableInputHandler;
import com.gensym.uitools.inspect.InspectItemCommands;
import com.gensym.uitools.utils.JExplorerSplitPane;
import com.gensym.uitools.utils.JExplorerTableModel;
import com.gensym.jgi.G2AccessException;
import com.gensym.dlg.ErrorDialog;
import com.gensym.util.Sequence;
import com.gensym.message.Trace;
import com.gensym.util.WorkspaceAdapter;

public class InspectGraphExplorerSplitPane extends JExplorerSplitPane
{
  private InspectTreeView inspectTreeView;
  private Symbol rpcName;
  private TwAccess connection;
  private ItemTableModel itemTableModel;
  
  public InspectGraphExplorerSplitPane(TwAccess cxn,
				       Symbol rpcName,
				       Structure inspectRootNodeData,
				       ColumnSpecification columnSpec)
  {
    this(new InspectTreeView(cxn, inspectRootNodeData),
	 createTableModel(columnSpec));
    this.connection = cxn;
    this.rpcName = rpcName;
    int[] preferredColumnWidths = columnSpec.preferredColumnWidths;
    initColumnWidths(preferredColumnWidths);
    initInputHandling();
  }

  @Override
  protected void addChildrenForNode(TreeNode node) {
    super.addChildrenForNode(node);
    InspectNodeInstanceData nodeData =
      (InspectNodeInstanceData)((BasicTreeNode)node).getUserObject();
    G2Definition definition = getG2Definition(nodeData);
    if (definition != null)
      addChildrenForDefinition(definition);
    Module module = getModule(nodeData);
    if (module != null)
      addChildrenForModule(module);
    Item item = nodeData.getItem();  
    if (item instanceof KbWorkspace)
      addChildrenForWorkspace((KbWorkspace)item);
  }

  private Module getModule(InspectNodeInstanceData nodeData) {
    Module module = nodeData.getModule();
    if (module == null) {
      Item item = nodeData.getItem();
      try {
	if (item instanceof ModuleInformation) {
	  module = connection.getKb().getModule(((ModuleInformation)item).getTopLevelModule());
	  nodeData.setModule(module);
	}
      } catch (G2AccessException g2ae) {
	Trace.exception(g2ae);
      }
    }
    return module;
  }

  private WorkspaceAdapter wkspListener = new WorkspaceAdapter();
  private void addChildrenForWorkspace(KbWorkspace wksp) {
    try {
      wksp.addWorkspaceListener(wkspListener);
      Item[] items = wksp.getItems();
      wksp.removeWorkspaceListener(wkspListener);
      for (int i=0;i<items.length;i++)
	itemTableModel.addRow(items[i]);
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
  }

  
  private void addChildrenForModule(Module module) {
    //add top level workspaces for this module
    KbWorkspace[] workspaces = module.getTopLevelKbWorkspaces();
    for (int i=0;i<workspaces.length;i++)
      itemTableModel.addRow(workspaces[i]);
    
    //add system tables for this module
    Sequence tables = module.getSystemTables();
    Enumeration e = tables.elements();
    while (e.hasMoreElements()) {
      Item item = (Item)e.nextElement();
      if (!(item instanceof ModuleInformation))
	itemTableModel.addRow(item);
    }
  }
  
  private G2Definition getG2Definition(InspectNodeInstanceData nodeData) {
    Item item = nodeData.getItem();
    G2Definition definition = null;
    if (item instanceof G2Definition)
      definition = (G2Definition)item;
    else {
      Symbol className = Symbol.intern(nodeData.getTextRepresentation());
      try {
	definition = connection.getDefinition(className);
      } catch(G2AccessException g2ae) {
	//OK, so it's not a class. 
      }
    }
    return definition;
  }

  private void addChildrenForDefinition(G2Definition definition) {
    try {
      Sequence instances = connection.getStrictInstancesOfClass(definition.getClassName());
      Enumeration e = instances.elements();
      while (e.hasMoreElements()) 
	itemTableModel.addRow((Item)e.nextElement());
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }    
  }
  
  private InspectGraphExplorerSplitPane(InspectTreeView inspectTreeView,
					ItemTableModel tableModel)
  {
    super(inspectTreeView, new JExplorerTableSorter(tableModel),tableModel);
    this.inspectTreeView = inspectTreeView;
    itemTableModel = tableModel;
  }  

  public InspectTreeView getTreeView() {
    return inspectTreeView;
  }
  
  @Override
  public void refresh(Object[] currentArguments) {
    int argCount = currentArguments.length;
    Object[] transformedArguments = new Object[argCount];
    for (int i=0;i<argCount;i++) {
      String argumentText = (String)currentArguments[i];
      if (argumentText != null)
	transformedArguments[i] = Symbol.intern(argumentText.toUpperCase());
    }
    try {
      inspectTreeView.setRootNodeData
	((Structure)connection.callRPC(rpcName,transformedArguments));
    } catch (G2AccessException g2ae) {
      (new ErrorDialog(null, "", true, g2ae.getMessage(), null)).setVisible(true);
    }
  }  

  private void initColumnWidths(int[] preferredColumnWidths) {
    TableColumnModel columnModel = table.getColumnModel();
    for (int i=0;i<preferredColumnWidths.length;i++)  
      columnModel.getColumn(i).setPreferredWidth(preferredColumnWidths[i]);
  }

  private void initInputHandling() {    
    ((TableSorter)table.getModel()).addMouseListenerToHeaderInTable(table);
    InspectItemCommands inspectItemCommands = new InspectItemCommands();
    TableInputHandler tableInputHandler
      = new TableInputHandlerForSortingModel(table,inspectItemCommands);
    table.getSelectionModel().addListSelectionListener
      ((ListSelectionListener)tableInputHandler);    
    table.addMouseListener(tableInputHandler);
  }
    
  private static ItemTableModel createTableModel
  (ColumnSpecification columnSpec) {
    ItemTableModel itemTableModel =  new ItemTableModel();
    Symbol[] columnNames = columnSpec.columnNames;
    boolean[] columnViewAsTexts = columnSpec.columnViewAsTexts;
    for (int i=0;i<columnNames.length;i++)  
      itemTableModel.addColumn(columnNames[i],columnViewAsTexts[i]);
    return itemTableModel;   
  }
}

class JExplorerTableSorter extends TableSorter
implements JExplorerTableModel {
  JExplorerTableSorter(ItemTableModel model) {
    super(model);
  }
  @Override
  public void removeAll() {
    ((ItemTableModel)getModel()).removeAll();
  }
  @Override
  public void update() {
    ((ItemTableModel)getModel()).update();
  }
  @Override
  public void addRow(TreeNode node) {
    InspectNodeInstanceData nodeData =
      (InspectNodeInstanceData)((BasicTreeNode)node).getUserObject();
    Item item = nodeData.getItem();
    if (item != null)
      ((ItemTableModel)getModel()).addRow(item);
  }
}
class TableInputHandlerForSortingModel extends TableInputHandler {
  TableInputHandlerForSortingModel(JTable table,
				   InspectItemCommands inspectItemCommands){
    super(table, inspectItemCommands);
  }
  @Override
  protected ItemTableModel getModel() {
    TableSorter sorter = (TableSorter)table.getModel();
    return (ItemTableModel)sorter.getModel();
  }
  @Override
  protected int[] getSelectedRows() {
    TableSorter sorter = (TableSorter)table.getModel();
    int[] rows = table.getSelectedRows();
    int count = rows.length;
    int[] unsortedRows = new int[count];
    for (int i=0;i<count;i++)
      unsortedRows[i]=sorter.getRowMapping(rows[i]);
    return unsortedRows;
  }
}
