
//
// BrowserCommands.java
//
// Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
//

package com.gensym.demos.g2studiosample.commands;


import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Frame;
import java.awt.Point;
import java.awt.event.ActionEvent;
import java.util.Vector;
import java.awt.Event;
import javax.swing.KeyStroke;

import com.gensym.message.Resource;
import com.gensym.ntw.TwAccess;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.CommandGroupInformation;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.StructuredCommandInformation;
import com.gensym.ui.SubCommandInformation;
import com.gensym.ntw.util.BrowserSymbols;
import com.gensym.ntw.util.ClassBrowserScrollPane;
import com.gensym.ntw.util.ModuleBrowserScrollPane;
import com.gensym.uitools.browsers.ObjectBrowserScrollPane;
import com.gensym.uitools.browsers.WorkspaceBrowserScrollPane;
import com.gensym.uitools.utils.ComponentVisibilityEventSource;
import com.gensym.uitools.utils.ComponentVisibilityListener;
import com.gensym.uitools.utils.ComponentVisibilityEvent;
import com.gensym.util.Symbol;
import javax.swing.JDialog;
import javax.swing.WindowConstants;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JLabel;
import java.awt.Insets;
import javax.swing.border.EtchedBorder;
import javax.swing.border.EmptyBorder;
import javax.swing.border.CompoundBorder;
import javax.swing.JTree;
import com.gensym.uitools.utils.FontUtil;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.Color;
import java.awt.BorderLayout;
import javax.swing.JFrame;
import javax.swing.ImageIcon;
import java.awt.Toolkit;
import javax.swing.border.LineBorder;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseAdapter;
import javax.swing.JComponent;
import java.awt.Cursor;
import javax.swing.tree.TreePath;
import javax.swing.event.TreeExpansionListener;
import javax.swing.event.TreeExpansionEvent;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import com.gensym.util.Structure;
import com.gensym.uitools.inspect.trees.InspectTreeView;
import com.gensym.message.Trace;
import com.gensym.jgi.G2AccessException;
import com.gensym.shell.util.ContextChangedListener;
import com.gensym.shell.util.ContextChangedEvent;
import javax.swing.JScrollPane;
import com.gensym.ntw.util.KbModuleListener;
import com.gensym.ntw.util.KbEvent;
import com.gensym.classes.Kb;
import com.gensym.ui.toolbar.ToolBar;
import javax.swing.JCheckBox;
import com.gensym.mdi.MDIFrame;
import javax.swing.JSplitPane;


public final class BrowserCommands extends AbstractStructuredCommand {
  public static final String MODULE_BROWSER = "ModuleBrowser";
  public static final String CLASS_BROWSER = "ClassBrowser";
  public static final String WORKSPACE_BROWSER = "WorkspaceBrowser";
  public static final Symbol
  G2_GET_MODULE_HIERARCHY_ = Symbol.intern ("G2-GET-MODULE-HIERARCHY"),
    G2_GET_CLASS_HIERARCHY_ = Symbol.intern ("G2-GET-CLASS-HIERARCHY"),
    G2_GET_WORKSPACE_HIERARCHY_ = Symbol.intern ("G2-GET-WORKSPACE-HIERARCHY");
  private Symbol hierarchyRPCName = G2_GET_MODULE_HIERARCHY_;
  private Object[] hierarchyRPCArgs = new Object[]{null};
  private static final String shortResource = "BrowsersResource";
  private static final String longResource = "BrowsersResource";
  private static final String mnemonicResource = "MnemonicResource";
  private static Resource shortBundle
  = Resource.getBundle("com/gensym/demos/g2studiosample/commands/BrowsersResource");

  private MDIFrame frame;
  private ConnectionManager connectionManager;
  private ContextChangedAdapter contextChangedListener;  
  private ComponentVisibilityEventPane browserPanel;

  public BrowserCommands(MDIFrame frame, ConnectionManager connectionManager) {
    super(new CommandInformation[] {
	  new CommandInformation(MODULE_BROWSER, true, shortResource, longResource,
				 "moduleHierarchy.gif", null, Boolean.TRUE, true,
				 mnemonicResource, null),
	    new CommandInformation(CLASS_BROWSER, true, shortResource, longResource,
				   "classHierarchy.gif", null, Boolean.FALSE, true,
				   mnemonicResource, null),
	    new CommandInformation(WORKSPACE_BROWSER, true, shortResource, longResource,
				   "workspaceHierarchy.gif", null, Boolean.FALSE, true,
				   mnemonicResource, null)});
    this.frame = frame;
    this.connectionManager = connectionManager;
    contextChangedListener = new ContextChangedAdapter();
    connectionManager.addContextChangedListener(contextChangedListener);
    this.browserPanel = createBrowserPanel();
  }

  public JPanel getBrowserPanel() {
    return browserPanel;
  }
  
  public void setBrowser(String browserCommandKey) {
    boolean isNull = browserCommandKey == null;
    if (MODULE_BROWSER.equals(browserCommandKey)) 
      setHierarchyType(G2_GET_MODULE_HIERARCHY_, new Object[]{null}, true, 3);
    else if(CLASS_BROWSER.equals(browserCommandKey))
      setHierarchyType(G2_GET_CLASS_HIERARCHY_, new Object[]{null}, true, 2);
    else if(WORKSPACE_BROWSER .equals(browserCommandKey)) 
      setHierarchyType(G2_GET_WORKSPACE_HIERARCHY_, new Object[]{null}, false, 0);
    updateStates(browserCommandKey);
    boolean visible = (browserCommandKey!=null);
    if (!visible)
      browserPanel.setPreferredSize(browserPanel.getSize());
    browserPanel.setVisible(visible);

    if (visible) {
      javax.swing.JSplitPane splitPane = null;
      java.awt.Component parent = browserPanel;
      while(splitPane == null && parent != null) {
	parent = parent.getParent();
	if (parent instanceof javax.swing.JSplitPane)
	  splitPane = (javax.swing.JSplitPane)parent;
      }
      if (splitPane != null)
	splitPane.resetToPreferredSizes();
    }
  }

  private void updateStates(String currentCommandKey) {
    setState(MODULE_BROWSER, Boolean.FALSE);
    setState(CLASS_BROWSER, Boolean.FALSE);
    setState(WORKSPACE_BROWSER, Boolean.FALSE);
    if (currentCommandKey!=null)
      setState(currentCommandKey, Boolean.TRUE);
  }
  
  @Override
  public void actionPerformed(ActionEvent event) {
    String commandKey = event.getActionCommand();
    setBrowser(commandKey);
  }
  
  static ImageIcon hideIcon = new ImageIcon(Toolkit.getDefaultToolkit().getImage(com.gensym.demos.g2studiosample.commands.BrowserCommands.class.getResource("hide.gif")));  
  class HideButton extends JButton {
    HideButton() {
      super(hideIcon);
      setRolloverEnabled(true);
      setMargin(new Insets(1,2,2,2));
      //setPreferredSize(new Dimension(16,16));
    }
    @Override
    protected void paintBorder(Graphics g) {
      if (getModel().isRollover() || getModel().isPressed())
	super.paintBorder(g);
    }
  }

  private ComponentVisibilityEventPane createBrowserPanel() {
    ComponentVisibilityEventPane panel = new ComponentVisibilityEventPane();
    panel.setBorder(new LineBorder(Color.lightGray, 3));
    panel.setLayout(new BorderLayout());

    ToolBar header = new ToolBar();
    header.add(this, MODULE_BROWSER);
    header.add(this, CLASS_BROWSER);
    header.add(this, WORKSPACE_BROWSER);    
    header.setBorder(null);
    header.setBackground(Color.lightGray);

    JPanel headerPanel = new JPanel();
    headerPanel.setLayout(new BorderLayout());
    headerPanel.add(header, "Center");
    JButton hideButton = new HideButton();
    hideButton.addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent ae) {
	setBrowser(null);
	
      }
    });
    headerPanel.add(hideButton, "East");
    headerPanel.setBorder(new CompoundBorder(new EtchedBorder(),
					     new EmptyBorder(new Insets(3,10,3,3))));    
    panel.add(headerPanel, "North");

    TwAccess cxn = connectionManager.getCurrentConnection();
    Structure inspectRootNodeData = null;
    try {
      if (cxn != null)
	inspectRootNodeData = (Structure)cxn.callRPC(hierarchyRPCName,hierarchyRPCArgs);
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
    tree = new InspectTreeView(cxn, true, inspectRootNodeData);

    //tree.addTreeExpansionListener(new TreeInvalidator());

    temporarilyFixRightButtonNotSelecting(tree); //remove after it's fixed in T2 (12/13/99)
    tree.setRowHeight(17);
    tree.setFont(FontUtil.sanserifPlain11);
    panel.setPreferredSize(new Dimension(175,300));
    panel.add(new JScrollPane(tree));
    
    return panel;
  }

  @Override
  protected void setAvailable(String key, boolean status) {
    super.setAvailable(key, status);
  }

  InspectTreeView tree;
  TwAccess currentConnection;
  class ContextChangedAdapter implements ContextChangedListener, KbModuleListener{
    @Override
    public void currentConnectionChanged(ContextChangedEvent e){
      try {
	if (currentConnection != null) {
	  Kb kb = currentConnection.getKb();
	  if (kb != null)
	    kb.removeKbModuleListener(this);
	}
      } catch (G2AccessException g2ae) {
	Trace.exception(g2ae);
      }
      currentConnection = e.getConnection();
      if (currentConnection != null) {
	try {
	  Kb kb = currentConnection.getKb();
	  if (kb != null)
	    kb.addKbModuleListener(this);
	} catch (G2AccessException g2ae) {
	  Trace.exception(g2ae);
	}
      } 
      download();
    }

    @Override
    public void receivedInitialModules (KbEvent evt) {}
    @Override
    public void moduleCreated (KbEvent evt){
      download();
    }
    @Override
    public void moduleDeleted (KbEvent evt) {
      download();
    }
    @Override
    public void moduleNameChanged (KbEvent evt) {
      download();
    }
    @Override
    public void moduleDependencyChanged (KbEvent evt){
      download();
    }
    @Override
    public void kbCleared (KbEvent evt) {
      tree.setRootNodeData(null);
    }
    @Override
    public void topLevelWorkspaceAdded(KbEvent evt){}
    @Override
    public void topLevelWorkspaceDeleted(KbEvent evt){}
    
  }

  void setHierarchyType(Symbol rpcName, Object[] args, boolean autoExpand, int autoExpandDepth) {
    hierarchyRPCName = rpcName;
    hierarchyRPCArgs = args;
    tree.setAutoExpand(autoExpand);
    tree.setAutoExpandDepth(autoExpandDepth);
    download();
  }
  
  void download() {
    new Thread(new Runnable() {
      @Override
      public void run() {
	if (tree != null) {
	  try {
	    browserPanel.setCursor(new Cursor(Cursor.WAIT_CURSOR));
	    tree.setConnection(currentConnection);
	    Structure inspectRootNodeData = null;		  	
	    try {
	      if (currentConnection != null)
		inspectRootNodeData=(Structure)currentConnection.callRPC(hierarchyRPCName,hierarchyRPCArgs);
	    } catch (G2AccessException g2ae) {
	      Trace.exception(g2ae);
	    }
	    tree.setRootNodeData(inspectRootNodeData);
	  } finally {
	    browserPanel.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
	  }    
	}
      }}).start();
  }  
  class TreeInvalidator implements TreeExpansionListener {
    @Override
    public void treeCollapsed(TreeExpansionEvent event) {
      JTree tree = (JTree) event.getSource();
      DefaultMutableTreeNode parentNode
	= (DefaultMutableTreeNode)event.getPath().getLastPathComponent();
      parentNode.removeAllChildren();
      ((DefaultTreeModel)tree.getModel()).reload(parentNode);
    }
    @Override
    public void treeExpanded(TreeExpansionEvent event){}
  }

  class ComponentVisibilityEventPane extends JPanel implements ComponentVisibilityEventSource {
    private Vector visibilityListeners = new Vector();
    @Override
    public void addComponentVisibilityListener(ComponentVisibilityListener listener) {
      visibilityListeners.addElement(listener);
    }
    
    @Override
    public void removeComponentVisibilityListener(ComponentVisibilityListener listener) {
      visibilityListeners.removeElement(listener);
    }

    @Override
    public void setVisible(boolean visible) {
      super.setVisible(visible);
      fireComponentVisibilityEvent();
    }
    
    void fireComponentVisibilityEvent() {
      int listenerCount;
      Object[] listeners = null;
      synchronized (visibilityListeners) {
	listenerCount = visibilityListeners.size();
	if (listenerCount != 0){
	  listeners = new Object[listenerCount];
	  visibilityListeners.copyInto(listeners);
	}
      }
      if (listenerCount != 0) {
	ComponentVisibilityEvent visibilityEvent = new ComponentVisibilityEvent(this);
	if (listeners != null)
	  for (int i=0; i<listenerCount; i++) 
	    ((ComponentVisibilityListener)listeners[i]).visibilityChanged(visibilityEvent);
      }
    }
  }
  
  class TmpMouseEventListener extends MouseAdapter {
    private void selectForRightButton(MouseEvent e) {
      JTree tree = (JTree)e.getSource();
      int x = e.getX();
      int y = e.getY();
      TreePath path = tree.getPathForLocation(x, y);  
      if (path != null) 
	tree.setSelectionPath(path);
    }
    @Override
    public void mousePressed(MouseEvent e) {
      if (e.isPopupTrigger())
	selectForRightButton(e);
    }
    @Override
    public void mouseReleased(MouseEvent e) {
      if (e.isPopupTrigger())
	selectForRightButton(e);
    }
  }
  private void temporarilyFixRightButtonNotSelecting(JTree tree) {
    tree.addMouseListener(new TmpMouseEventListener());
  }

}




