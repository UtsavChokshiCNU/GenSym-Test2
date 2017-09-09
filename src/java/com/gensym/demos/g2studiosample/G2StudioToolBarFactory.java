package com.gensym.demos.g2studiosample;

import java.awt.Component;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.Color;
import java.awt.Insets;
import java.awt.Dimension;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.BorderLayout;
import java.awt.event.ActionListener;
import javax.swing.JTextField;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.BevelBorder;
import com.gensym.util.WorkspaceAdapter;
import com.gensym.util.WorkspaceEvent;
import com.gensym.message.Trace;
import com.gensym.core.ToolBarFactory;
import com.gensym.mdi.MDIToolBarPanel;
import com.gensym.mdi.MDIFrame;
import com.gensym.ui.toolbar.ToolBar;
import com.gensym.message.Resource;
import com.gensym.uitools.utils.FontUtil;
import com.gensym.uitools.inspect.InspectSessionCommands;
import com.gensym.uitools.utils.VariableWidthBevelBorder;
import com.gensym.uitools.utils.StatusDisplay;
import com.gensym.uitools.utils.WaitAnimator;
import com.gensym.editor.text.G2FontSizeJComboBox;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.ItemListener;
import com.gensym.util.ItemEvent;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.wksp.WorkspaceView;
import com.gensym.wksp.WorkspaceElement;
import com.gensym.ntw.util.VersionHelper;
import com.gensym.ntw.util.SelectionListener;
import com.gensym.ntw.util.SelectionEvent;
import com.gensym.shell.util.LocationComboBox;
import com.gensym.shell.util.ConnectionTabPane;
import com.gensym.shell.util.WorkspaceDocument;
import com.gensym.shell.util.MDIFrameWorkspaceSelectionAdapter;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.shell.util.UserModePanel;
import com.gensym.shell.util.HostPortPanel;
import com.gensym.shell.util.ZoomComboBox;
import com.gensym.shell.commands.ProjectCommands;
import com.gensym.shell.commands.WorkspaceInstanceCommands;
import com.gensym.shell.commands.ItemCommands;
import com.gensym.shell.commands.ViewCommands;
import com.gensym.shell.commands.ZoomCommands;
import com.gensym.shell.commands.WorkspaceAnnotationCommands;
import com.gensym.demos.g2studiosample.commands.NavigationCommands;
import com.gensym.demos.g2studiosample.commands.PackagePreparationCommands;
import com.gensym.demos.g2studiosample.commands.DebuggingCommands;
import com.gensym.demos.g2studiosample.util.BreakPointLevelComboBox;
import com.gensym.demos.g2studiosample.util.TracingMessageLevelComboBox;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.util.Symbol;

public class G2StudioToolBarFactory
implements ToolBarFactory, SelectionListener 
{
  private static final Resource i18ui = Resource.getBundle ("com/gensym/demos/g2studiosample/UiLabels");  
  private Shell shell;
  private MDIToolBarPanel defaultToolBarPanel;
  private ToolBar navigationToolBar, projectToolBar, layoutToolBar;
  private ConnectionTabPane connectionTabPane;  
  private JPanel southernPanel;
  private JTextField xField, yField, height, width;  
  private TextFieldListener textFieldListener = new TextFieldListener();
  private WSListener workspaceListener = new WSListener();
  private ItemListener itemListener = new ItemAdapter();
  private KbWorkspace currentWorkspace;
  private Item currentItem;
  private WorkspaceElement[] currentSelection;
  private Object currentSelectionLock = new Object();
  private WorkspaceView view;
  private G2StudioCommands studioCommands;
  private G2StudioIconicStatusBar iconicStatusBar;
  private LocationComboBox locationComboBox;
  private WaitAnimator waitAnimator;
  
  public G2StudioToolBarFactory(Shell shell)
  {
    this.shell = shell;    
    this.waitAnimator = shell.getWaitBar();
    this.locationComboBox = shell.getLocationComboBox();
    this.iconicStatusBar = shell.getIconicStatusBar();
    new MDIFrameWorkspaceSelectionAdapter((MDIFrame)shell.getCurrentFrame()).addSelectionListener(this);
    this.studioCommands = shell.getG2StudioCommands();
  }
  
  @Override
  public Component getToolBarComponent(Object focalObject) {
    if (focalObject instanceof Shell || focalObject instanceof WorkspaceDocument)
      return getDefaultToolBarPanel();
    else
      return getSouthernPanel();
  }
  
  protected MDIToolBarPanel getDefaultToolBarPanel() {
    if (defaultToolBarPanel == null) {
      MDIToolBarPanel panel = new MDIToolBarPanel();  
      GridBagLayout layout = new GridBagLayout();
      panel.setLayout(layout);
      GridBagConstraints constraints = new GridBagConstraints();
      constraints.fill = constraints.NONE;
      constraints.anchor = constraints.WEST;
      constraints.gridwidth = constraints.REMAINDER;
      constraints.weightx = 1;
      
      ToolBar tb1 = getProjectToolBar();    
      ToolBar tb2 = getNavigationToolBar();
      ToolBar tb3 = getPackagePreparationToolBar();
      ToolBar tb4 = getDebuggingToolBar();
      
      layout.setConstraints(tb1, constraints);
      panel.add(tb1);
      constraints.fill=constraints.HORIZONTAL;
      layout.setConstraints(tb2, constraints);    
      panel.add(tb2);
      constraints.fill = constraints.NONE;
      
      constraints.weightx = .05;    
      constraints.gridwidth = constraints.RELATIVE;
      layout.setConstraints(tb3, constraints);        
      panel.add(tb3);
      constraints.weightx = .95;
      layout.setConstraints(tb4, constraints);        
      panel.add(tb4);
      defaultToolBarPanel = panel;
    }
    return defaultToolBarPanel;
  }


  protected JPanel getSouthernPanel() {
    if (southernPanel == null) {
      southernPanel = new JPanel();
      southernPanel.setLayout(new BorderLayout());    
      
      JPanel panel = new JPanel();
      panel.setLayout(new BorderLayout());      
      
      panel.add(waitAnimator,BorderLayout.WEST);
      StatusDisplay statusDisplay = shell.getStatusDisplay();
      if (statusDisplay instanceof Component)
	panel.add((Component)statusDisplay,BorderLayout.CENTER);
      panel.add(iconicStatusBar, BorderLayout.EAST);
      southernPanel.add(getLayoutToolBar(), BorderLayout.WEST);    
      southernPanel.add(getConnectionTabPane(), BorderLayout.NORTH);
      southernPanel.add(panel, BorderLayout.SOUTH);
    }
    return southernPanel;
  }
    
  public ConnectionTabPane getConnectionTabPane() {
    if (connectionTabPane == null) {
      connectionTabPane = new ConnectionTabPane(shell.getCurrentFrame(),
						shell.getConnectionManager());
      connectionTabPane.setFont(FontUtil.sanserifPlain11);
      studioCommands.getComponentVisibilityCommands().addComponent(connectionTabPane,
								   i18ui.getString("connectionTabs"));       
    }
    return connectionTabPane;
  }
      
  public ToolBar getLayoutToolBar() {
    if (layoutToolBar == null) {
      layoutToolBar = new ToolBar ();
      layoutToolBar.setFloatable(false);
      layoutToolBar.setMargin(new Insets(0,0,0,0));
      layoutToolBar.add(studioCommands.getNudgeCommands());
      //layoutToolBar.addSeparator();
      layoutToolBar.add(studioCommands.getAlignmentCommands());
      //layoutToolBar.addSeparator();
      layoutToolBar.add(studioCommands.getOrderCommands());
      //layoutToolBar.addSeparator();
      layoutToolBar.setFloatable(false);
      layoutToolBar.setBorderPainted(true);
      layoutToolBar.setBorder(new VariableWidthBevelBorder(BevelBorder.RAISED, Color.white, Color.gray));
      //layoutToolBar.setMaximumSize(new Dimension(100, layoutToolBar.getMaximumSize().height));
      
      xField = addLabeledTextField("  "+i18ui.getString ("xpos")+" ",layoutToolBar,textFieldListener);
      yField = addLabeledTextField("  "+i18ui.getString ("ypos")+" ",layoutToolBar,textFieldListener);
      width = addLabeledTextField("  "+i18ui.getString ("width")+" ",layoutToolBar,textFieldListener);
      height = addLabeledTextField("  "+i18ui.getString ("height")+" ",layoutToolBar,textFieldListener);
      xField.setEditable(true);
      yField.setEditable(true);
      studioCommands.getComponentVisibilityCommands().addComponent(layoutToolBar,
								   i18ui.getString("layoutToolBar"));      
    }
    return layoutToolBar;
  }
    
  private static JTextField addLabeledTextField(String label,
						ToolBar toolbar,
						ActionListener actionListener) {
    JLabel lbl = new JLabel(label);
    JTextField field = new JTextField();
    field.setFont(FontUtil.sanserifPlain11);
    lbl.setFont(FontUtil.sanserifPlain11);    
    field.setColumns(5);    
    field.addActionListener(actionListener);
    toolbar.add(lbl);
    toolbar.add(field);
    return field;
  }
          
  public ToolBar getProjectToolBar() {
    if (projectToolBar == null) {
      ToolBar tb = new ToolBar();
      tb.setFloatable(false);    
      tb.setBorder(new VariableWidthBevelBorder(BevelBorder.RAISED, Color.white, Color.gray));
      tb.setBorderPainted(true);    
      tb.setMargin(new Insets(0,0,0,0));
      tb.add(studioCommands.getWorkspaceCommands());
      tb.addSeparator();
      ProjectCommands projectCommands = studioCommands.getProjectCommands();
      tb.add(projectCommands, projectCommands.SAVE_PROJECT);    
      tb.addSeparator();      
      tb.add(studioCommands.getWorkspaceInstanceCommands(),WorkspaceInstanceCommands.PRINT_WORKSPACE);
      tb.addSeparator();
      tb.add(studioCommands.getEditCommands());
      tb.addSeparator();
      tb.add(new G2FontSizeJComboBox((MDIFrame)shell.getCurrentFrame()));    
      tb.addSeparator();
      ItemCommands itemCommands = studioCommands.getItemCommands();
      tb.add(itemCommands, ItemCommands.COLOR);
      tb.addSeparator();
      tb.add(itemCommands, ItemCommands.ITEM_PROPERTIES);
      tb.addSeparator();
      tb.add(studioCommands.getCondensedG2StateCommands());
      tb.addSeparator();
      ViewCommands viewCommand = studioCommands.getViewCommands();
      tb.add(viewCommand, viewCommand.VIEW_LOGBOOK);
      tb.add(viewCommand, viewCommand.VIEW_MESSAGE_BOARD);
      tb.addSeparator();
      try {
	UserModePanel ump = new UserModePanel (shell.getConnectionManager(), true);
	//ump.getComponents().setFont(FontUtil.sanserifPlain11);
	ump.setMaximumSize(new Dimension(120,ump.getMaximumSize().height));
	tb.add (ump);
      } catch (G2AccessException gae) {
	Trace.exception (gae);
      }
      tb.addSeparator();
      PackagePreparationCommands packagePreparationCommands = studioCommands.getPackagePreparationCommands();
      tb.add(packagePreparationCommands, packagePreparationCommands.PACKAGE_PREPARATION_MODE);
      tb.add(packagePreparationCommands, packagePreparationCommands.SIMULATE_PROPRIETARY_MODE);
      tb.add(studioCommands.getDebuggingCommands(), DebuggingCommands.DEBUGGING_ENABLED);
      
      if (VersionHelper.isUsingJava2D(this.getClass())) {
	tb.addSeparator();
	ZoomCommands zoomHandler = studioCommands.getZoomCommands();
	tb.add(zoomHandler, zoomHandler.ZOOM_IN);
	tb.add(zoomHandler, zoomHandler.ZOOM_OUT);
	ZoomComboBox zoomBox = new ZoomComboBox((MDIFrame)shell.getCurrentFrame());
	zoomBox.setFont(FontUtil.sanserifPlain11);
	zoomBox.setMaximumSize(new Dimension(60,zoomBox.getMaximumSize().height));
	tb.add(zoomBox);      
      }
      tb.addSeparator();      
      tb.add(studioCommands.getWorkspaceAnnotationCommands(),
	     WorkspaceAnnotationCommands.TOGGLE_ANNOTATION_VISIBILITY);
      tb.addSeparator();
      tb.add(studioCommands.getInspectSessionCommands(),InspectSessionCommands.INSPECT);
      projectToolBar = tb;
      studioCommands.getComponentVisibilityCommands().addComponent(projectToolBar, i18ui.getString("projectToolBar"));          
    }
    return projectToolBar;
  }

  public ToolBar getNavigationToolBar() {
    if (navigationToolBar == null) {
      ToolBar tb = new ToolBar ();
      tb.setFloatable(false);
      tb.setMargin(new Insets(0,0,0,0));
      tb.setBorder(new VariableWidthBevelBorder(BevelBorder.RAISED, Color.white, Color.gray));
      tb.setBorderPainted(true);

      NavigationCommands navigationCommands = studioCommands.getNavigationCommands();
      tb.add(navigationCommands, navigationCommands.GO_HOME);
      tb.add(navigationCommands, navigationCommands.GO_BACK);
      tb.add(navigationCommands, navigationCommands.GO_FORWARD);
      JLabel locationLabel = new JLabel("Location");
      locationLabel.setBorder(new javax.swing.border.EmptyBorder(0,5,0,5));
      locationLabel.setDisplayedMnemonic('L');
      locationLabel.setLabelFor(locationComboBox);
      tb.add(locationLabel);
      tb.add(locationComboBox);
      FontUtil.setFontForContainer
	(tb, FontUtil.sanserifPlain11, true);
      tb.add(navigationCommands, navigationCommands.STOP_DOWNLOAD);
      navigationToolBar = tb;
      studioCommands.getComponentVisibilityCommands().addComponent(navigationToolBar, i18ui.getString("navigationToolBar"));    
    }
    return navigationToolBar;
  }

  public ToolBar getPackagePreparationToolBar() {
    ToolBar tb = new ToolBar();
    tb.setBorder(new VariableWidthBevelBorder(BevelBorder.RAISED, Color.white, Color.gray));
    tb.setBorderPainted(true);        
    //tb.setMargin(new java.awt.Insets(0,0,0,0));

    PackagePreparationCommands packagePreparationCommands
      = studioCommands.getPackagePreparationCommands();    
    tb.add(packagePreparationCommands, packagePreparationCommands.STRIP_TEXTS_NOW);
    tb.add(packagePreparationCommands, packagePreparationCommands.FLUSH_CHANGE_LOG_FOR_ENTIRE_KB);
    tb.add(packagePreparationCommands, packagePreparationCommands.MAKE_WORKSPACES_PROPRIETARY_NOW);
    packagePreparationCommands.setComponentForPPVisibility(tb);
    //compVisibilityCommands.addComponent(tb, i18ui.getString("packagePrepToolBar"));            
    return tb;
  }

  public ToolBar getDebuggingToolBar() {
    ConnectionManager cxnMgr = shell.getConnectionManager();
    ToolBar tb = new ToolBar();
    tb.setBorder(new VariableWidthBevelBorder(BevelBorder.RAISED, Color.white, Color.gray));
    tb.setBorderPainted(true);        
    tb.setMargin(new Insets(0,0,0,0));
    DebuggingCommands debuggingCommands = studioCommands.getDebuggingCommands();
    tb.add(debuggingCommands, DebuggingCommands.DISASSEMBLER_ENABLED);
    tb.add(new BreakPointLevelComboBox(cxnMgr));
    tb.add(new TracingMessageLevelComboBox(cxnMgr));
    debuggingCommands.setComponentForDebuggingVisibility(tb);
    //compVisibilityCommands.addComponent(tb, i18ui.getString("debuggingToolBar"));        
    return tb;
  }

  public void removeItemListeners(WorkspaceElement[] selection) throws G2AccessException
  {
    if (selection == null) return;
    for (int i=0;i<selection.length;i++) {
      Item itm = selection[i].getItem();
      itm.removeItemListener(itemListener,
			     com.gensym.ntw.util.AttributeHelper.getNeededAttributes(itm));
    }
  }
  
  public void addItemListeners(WorkspaceElement[] selection) throws G2AccessException
  {
    if (selection == null) return;
    for (int i=0;i<selection.length;i++) {
      Item itm = selection[i].getItem();
      itm.addItemListener(itemListener,
			  com.gensym.ntw.util.AttributeHelper.getNeededAttributes(itm));
    }
  }

  @Override
  public void selectionChanged(SelectionEvent event){
    view = null;
    try {
      removeItemListeners(currentSelection);
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
    synchronized (currentSelectionLock) {
      currentSelection = null;
    }
    try {
      if (currentWorkspace != null)
	currentWorkspace.removeWorkspaceListener(workspaceListener);
      currentWorkspace = null;
      currentItem = null;
      Object source = event.getSource();
      if (source instanceof WorkspaceView) 
	view = (WorkspaceView)source;
      if (view != null) {
	currentWorkspace = view.getWorkspace();
	currentWorkspace.addWorkspaceListener(workspaceListener);
	synchronized (currentSelectionLock) {	
	  currentSelection = view.getSelection();
	}
	try {
	  addItemListeners(currentSelection);
	} catch (G2AccessException g2ae) {
	  Trace.exception(g2ae);
	}	  
	updateForSelection();
      }
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    } 
  }
  
  private void updateForSelection() throws G2AccessException {
    String status = "";
    if (currentSelection != null) {
      if (currentSelection.length == 1) {
	currentItem = currentSelection[0].getItem();
	height.setText(""+currentItem.getItemHeight());
	width.setText(""+currentItem.getItemWidth());
	height.setBackground(Color.white);
	width.setBackground(Color.white);
      } else {
	currentItem = view.getWorkspace();
	height.setText("");
	width.setText("");
	height.setBackground(Color.lightGray);
	width.setBackground(Color.lightGray);
      }
      status = com.gensym.ntw.util.AttributeHelper.getTableHeader(currentItem);
      //status = currentItem.getTableHeader();//THIS ATTRIBUTE IS NOT CACHED!
      Point center = view.getCurrentSelectionCenter();
      if (center != null) {
	xField.setText(""+(int)center.getX());
	yField.setText(""+(int)center.getY());
      } else {
	xField.setText("");
	yField.setText("");
      }
    }
    StatusDisplay statusDisplay = shell.getStatusDisplay();
    if (statusDisplay != null)
      shell.getStatusDisplay().setStatus(status,G2StudioStatusBar.MAIN_DISPLAY_AREA);    
    if (status == "") {
      xField.setText("");
      yField.setText("");
    }
  }
  

  class TextFieldListener implements ActionListener {
    @Override
    public void actionPerformed(ActionEvent e) {
      WorkspaceView view = ((WorkspaceDocument)((MDIFrame)shell.getCurrentFrame()).
			    getManager().getActiveDocument()).
	getWorkspaceView();
      JTextField source = (JTextField)e.getSource();
      int newValue = new Integer(source.getText()).intValue();
      if (view != null) {
	try {
	  Point point = view.getCurrentSelectionCenter();
	  if (source == xField) {
	    view.moveSelection((int)(newValue - point.getX()), 0, true);
	  } else if (source == yField) {
	    view.moveSelection(0, (int)(point.getY() - newValue), true);
	  } else {
	      WorkspaceElement[] selection = view.getSelection();
	      if (selection.length == 1) {
		Item item = selection[0].getItem();
		Rectangle bounds = item.getBounds();
		int left=0, right=0, top=0, bottom=0;
		if (source == height) {
		  left=(int)bounds.getX();
		  right=left+(int)bounds.getWidth();
		  top=(int)(bounds.getY()+((newValue-bounds.getHeight())/2));
		  bottom=top-newValue;
		} else if (source == width) {
		  top=(int)bounds.getY();
		  bottom=top-(int)bounds.getHeight();
		  left=(int)(bounds.getX()-((newValue-bounds.getWidth())/2));
		  right=left+newValue;
		}
		item.setBounds(left, top, right, bottom);
	      }
	  }
	} catch (G2AccessException gae) {
	  Trace.exception(gae);
	  ((JTextField)source).setForeground(Color.red);
	}
      }
    }
  }

  class ItemAdapter implements ItemListener {
    @Override
    public void itemModified(ItemEvent ie) {
      try {
      	updateForSelection();
      } catch (G2AccessException g2ae) {
	Trace.exception(g2ae);
      }
    }
    @Override
    public void itemDeleted(ItemEvent ie) {}
    @Override
    public void receivedInitialValues(ItemEvent ie) {}
  }
  
  class WSListener extends WorkspaceAdapter {
    @Override
    public void workspaceItemResized(WorkspaceEvent e) {
      Item item = e.getItem();
      if (item == currentItem) {
	try {  
	  height.setText(""+item.getItemHeight());
	  width.setText(""+item.getItemWidth());
	} catch (G2AccessException gae) {
	  Trace.exception(gae);
	  height.setForeground(Color.red);
	  width.setForeground(Color.red);
	}
      }
    }
    @Override
    public void workspaceItemMoved(WorkspaceEvent e) {
      Item item = e.getItem();
      WorkspaceView view = ((WorkspaceDocument)((MDIFrame)shell.getCurrentFrame()).
			    getManager().getActiveDocument()).getWorkspaceView();
      boolean selectedElementIsBeingMoved = false;
      synchronized (currentSelectionLock) {
	if (currentSelection == null) return;	
	for (int x = 0; x<currentSelection.length; x++) {
	  WorkspaceElement elt = currentSelection[x];
	  if (item == elt.getItem()) 
	    selectedElementIsBeingMoved = true;
	    break;
	}
      }
      if (selectedElementIsBeingMoved) {
	try {
	  Point center = view.getCurrentSelectionCenter();
	  if (center != null) {
	    xField.setText(""+(int)center.getX());
	    yField.setText(""+(int)center.getY());
	  }
	} catch (G2AccessException gae) {
	  Trace.exception (gae);
	  xField.setForeground(Color.red);
	  yField.setForeground(Color.red);
	}
      }
    }
  }
  
}
