package com.gensym.uitools.inspect;

import java.util.Vector;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.event.ActionEvent;
import java.awt.Rectangle;
import java.awt.Window;
import java.awt.Event;
import javax.swing.JFrame;
import javax.swing.JDialog;
import javax.swing.KeyStroke;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.CommandGroupInformation;
import com.gensym.ui.StructuredCommandInformation;
import com.gensym.ui.SubCommandInformation;
import com.gensym.ui.CommandInformation;
import com.gensym.mdi.MDIFrame;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.ntw.TwAccess;
import com.gensym.util.Symbol;
import com.gensym.uitools.utils.JExplorer;
import com.gensym.uitools.inspect.trees.InspectGraphExplorerSplitPane;
import com.gensym.uitools.inspect.trees.ColumnSpecification;
import com.gensym.shell.util.ContextChangedListener;
import com.gensym.shell.util.ContextChangedEvent;
import com.gensym.uitools.inspect.trees.InspectTreeView;
import com.gensym.shell.util.TW2Document;
import java.awt.Dimension;

public class InspectSessionCommands extends AbstractStructuredCommand
implements InspectSessionCommandsConstants
{
  private static Image magnifyingGlassIcon;
  private MDIFrame frame;
  private ConnectionManager connectionManager;
  private ContextChangedAdapter contextChangedListener;    

  public InspectSessionCommands(MDIFrame frame,
				ConnectionManager connectionManager)
  {
    super(new StructuredCommandInformation[]{
      new CommandGroupInformation("Search",
				  new CommandInformation[]{
	new CommandInformation(INSPECT, false,
			       shortResource, longResource,
			       "find.gif",
			       null, null, false,
			       mnemonicResource,
			       KeyStroke.getKeyStroke('F', Event.CTRL_MASK))}),
      new CommandGroupInformation("Modularization",
				  new CommandInformation[]{	
	new CommandInformation(CHECK_MODULARIZATION, false,
			       shortResource, longResource,
			       "view.gif",
			       null, null, false,
			       mnemonicResource,
			       null)}),
	new CommandGroupInformation("Class, module and workspace hierarchies",
				    new CommandInformation[]{
	  new CommandInformation(CLASS_HIERARCHY, false,
				 shortResource, longResource,
				 "class-hierarchy.gif",
				 null, null, false,
				 mnemonicResource, null),
	    new CommandInformation(MODULE_HIERARCHY, false,
				   shortResource, longResource,
				   "module-hierarchy.gif",
				   null, null, false,
				   mnemonicResource, null),
	    new CommandInformation(WORKSPACE_HIERARCHY, false,
				   shortResource, longResource,
				   "workspace-hierarchy.gif",
				   null, null, false,
				   mnemonicResource, null)}),
	  new CommandGroupInformation("Procedure and Method Hierarchies",
				      new CommandInformation[]{	  	  
	    new SubCommandInformation(METHOD_HIERARCHIES,
				      false,
				      shortResource, longResource,
				      null, null, null,
				      new StructuredCommandInformation[] {
	      new CommandInformation(METHOD_INHERITANCE_PATH, false,
				     shortResource, longResource,
				     "method-inheritance-path.gif",
				     null, null, false,
				     mnemonicResource, null),
		new CommandInformation(METHOD_HIERARCHY, false,
				       shortResource, longResource,
				       "method-hierarchy.gif",
				       null, null, false,
				       mnemonicResource, null)}),
	      new SubCommandInformation(PROCEDURAL_HIERARCHIES,
					false,
					shortResource, longResource,
					null, null, null,
					new StructuredCommandInformation[] {	      
		new CommandInformation(PROCEDURE_INVOCATION_HIERARCHY, false,
				       shortResource, longResource,
				       "procedure-invocation-hierarchy.gif",
				       null, null, false,
				       mnemonicResource, null),
		  new CommandInformation(PROCEDURE_CALLING_HIERARCHY, false,
					 shortResource, longResource,
					 "procedure-calling-hierarchy.gif",
					 null, null, false,
					 mnemonicResource, null),
		  new CommandInformation(PROCEDURE_CALLER_HIERARCHY, false,
					 shortResource, longResource,
					 "procedure-caller-hierarchy.gif",
					 null, null, false,
					 mnemonicResource, null)})})});
    this.frame = frame;
    magnifyingGlassIcon =
      Toolkit.getDefaultToolkit().getImage(this.getClass().getResource("view.gif"));
    //if (magnifyingGlassIcon != null)
    //  frame.setIconImage(magnifyingGlassIcon);      
    this.connectionManager = connectionManager;
    contextChangedListener = new ContextChangedAdapter();    
    connectionManager.addContextChangedListener(contextChangedListener);
    updateAvailability();
  }

  class ContextChangedAdapter implements ContextChangedListener{
    @Override
    public void currentConnectionChanged(ContextChangedEvent e){
      updateAvailability();
    }
  }
  
  private void updateAvailability() {
    boolean available = connectionManager.getCurrentConnection() != null;
    setAvailable(INSPECT, available);
    setAvailable(CHECK_MODULARIZATION, available);
    setAvailable(METHOD_INHERITANCE_PATH, available);
    setAvailable(METHOD_HIERARCHY, available); 
    setAvailable(PROCEDURE_INVOCATION_HIERARCHY, available);
    setAvailable(PROCEDURE_CALLING_HIERARCHY, available);
    setAvailable(PROCEDURE_CALLER_HIERARCHY, available);
    setAvailable(CLASS_HIERARCHY, available);
    setAvailable(MODULE_HIERARCHY, available);
    setAvailable(WORKSPACE_HIERARCHY, available);
    setAvailable(PROCEDURAL_HIERARCHIES, available);
    setAvailable(METHOD_HIERARCHIES, available); 
  }
  
  private static void centerWindowInWindow(Window child,
					   Window parent,
					   int childWidth,
					   int childHeight) {
    Rectangle bnds = parent.getBounds();
    int x = bnds.x+bnds.width/2;
    int y = bnds.y+bnds.height/2;
    child.setBounds(x-childWidth/2,y-childHeight/2,
		    childWidth, childHeight);
  }
  
  private void showInspectHierarchy(Symbol rpcName,
				    String[] argumentLabels,
				    String mainTitle,
				    ColumnSpecification columnSpec,
				    boolean refreshOnLaunch,
				    boolean autoExpand)
  {
    if (columnSpec == null)
      columnSpec = defaultColumnSpec;
    //JDialog view = new JDialog(frame);
    TwAccess connection = connectionManager.getCurrentConnection();
    mainTitle +=" -- " + connection.toShortString();
    InspectDocument view = new InspectDocument(connection);
    InspectGraphExplorerSplitPane splitPane = 
      new InspectGraphExplorerSplitPane(connection,rpcName,null,columnSpec);
    InspectTreeView tree = splitPane.getTreeView();
    tree.setAutoExpand(autoExpand);
    JExplorer explorer = new JExplorer(argumentLabels,splitPane, view, false, true);
    //view.addWindowListener(new WindowDisposer());
    view.getContentPane().add(explorer,"Center");
    view.setTitle(mainTitle);
    frame.getManager().addDocument(view);
    //centerWindowInWindow(view, frame, 700, 325);
    //view.setVisible(true);
    view.setSize(700,325);
    if (refreshOnLaunch)
      explorer.refresh();
  }
  
  class InspectDocument extends TW2Document {
    public InspectDocument(TwAccess connection){
      super(connection);
    }
  }
  

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (CLASS_HIERARCHY.equals(cmdKey)) {
      showInspectHierarchy(G2_GET_CLASS_HIERARCHY_,
			   CLASS_HIERARCHY_LABELS,
			   CLASS_HIERARCHY_TITLE, null, false, true);
    } else if (MODULE_HIERARCHY.equals(cmdKey)) {
      showInspectHierarchy(G2_GET_MODULE_HIERARCHY_,
			   MODULE_HIERARCHY_LABELS,
			   MODULE_HIERARCHY_TITLE, null, true, true);
    } else if (WORKSPACE_HIERARCHY.equals(cmdKey)) {
      showInspectHierarchy(G2_GET_WORKSPACE_HIERARCHY_,
			   WORKSPACE_HIERARCHY_LABELS,
			   WORKSPACE_HIERARCHY_TITLE, null, false, false);
    } else if (PROCEDURE_INVOCATION_HIERARCHY.equals(cmdKey)) {
      showInspectHierarchy(G2_GET_PROCEDURE_INVOCATION_HIERARCHY_,
			   null,
			   PROCEDURE_INVOCATION_HIERARCHY_TITLE, null, true, true);
    } else if (PROCEDURE_CALLING_HIERARCHY.equals(cmdKey)) {
      showInspectHierarchy(G2_GET_PROCEDURE_CALLING_HIERARCHY_,
			   PROCEDURE_CALLING_HIERARCHY_LABELS,
			   PROCEDURE_CALLING_HIERARCHY_TITLE, null, false, false);
    } else if (PROCEDURE_CALLER_HIERARCHY.equals(cmdKey)) {
      showInspectHierarchy(G2_GET_PROCEDURE_CALLER_HIERARCHY_,
			   PROCEDURE_CALLER_HIERARCHY_LABELS,			  
			   PROCEDURE_CALLER_HIERARCHY_TITLE, null, false, false);
    } else if (METHOD_INHERITANCE_PATH.equals(cmdKey)) {
      showInspectHierarchy(G2_GET_METHOD_INHERITANCE_PATH_,
			   METHOD_INHERITANCE_PATH_HIERARCHY_LABELS,
			   METHOD_INHERITANCE_PATH_TITLE, null, false, false);
    } else if (METHOD_HIERARCHY.equals(cmdKey)) {
      showInspectHierarchy(G2_GET_METHOD_HIERARCHY_,
			   METHOD_HIERARCHY_LABELS,
			   METHOD_HIERARCHY_TITLE, null, false, false);
    } else if (CHECK_MODULARIZATION.equals(cmdKey)) {
      JDialog inspectFrame = new JDialog(frame);
      //if (magnifyingGlassIcon != null) inspectFrame.setIconImage(magnifyingGlassIcon);      
      inspectFrame.setTitle("Check Modularization");
      int defaultWidth = 430; int defaultHeight = 225;
      centerWindowInWindow(inspectFrame, frame, defaultWidth, defaultHeight);
      inspectFrame.addWindowListener(new java.awt.event.WindowAdapter() {
	@Override
	public void windowClosing(java.awt.event.WindowEvent e ) {
	  ((JDialog)e.getSource()).setVisible(false);
	  ((JDialog)e.getSource()).dispose();
	}
      });
      InspectWindow inspectWindow = new CheckModularizationWindow(inspectFrame);
      TwAccess currentConnection = connectionManager.getCurrentConnection();
      inspectWindow.addConnection(currentConnection);
      inspectWindow.selectConnection(currentConnection);
      inspectFrame.getContentPane().add(inspectWindow);
      inspectFrame.setVisible(true);
      inspectWindow.getControlPanel().find();
    } else if (INSPECT.equals(cmdKey)) {
      JDialog inspectFrame = new JDialog(frame);
      //if (magnifyingGlassIcon != null) inspectFrame.setIconImage(magnifyingGlassIcon);      
      inspectFrame.setTitle("Find Items");
      int defaultWidth = 430; int defaultHeight = 225;
      centerWindowInWindow(inspectFrame, frame, defaultWidth, defaultHeight);
      inspectFrame.addWindowListener(new java.awt.event.WindowAdapter() {
	@Override
	public void windowClosing(java.awt.event.WindowEvent e ) {
	  ((JDialog)e.getSource()).setVisible(false);
	  ((JDialog)e.getSource()).dispose();
	}
      });
      InspectWindow inspectWindow = new InspectWindow(inspectFrame);      
      TwAccess[] connections = connectionManager.getOpenConnections();
      for (int i=0;i<connections.length;i++) 
	inspectWindow.addConnection(connections[i]);
      inspectWindow.selectConnection(connectionManager.getCurrentConnection());
      inspectFrame.getContentPane().add(inspectWindow);
      inspectFrame.setVisible(true);
    }
  }
    
}

class WindowDisposer extends WindowAdapter
{
    @Override
    public void windowClosing(WindowEvent e) {
      //((JFrame)e.getSource()).getContentPane().removeAll();
      e.getWindow().dispose();
    }
}
  
