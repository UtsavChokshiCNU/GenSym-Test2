package com.gensym.uitools.inspect;

import com.gensym.uitools.tables.ItemTableModel;
import com.gensym.util.Symbol;
import java.awt.event.ActionListener;
import com.gensym.message.Resource; 
import java.awt.event.ActionEvent;
import com.gensym.dlg.ErrorDialog;
import com.gensym.ntw.TwAccess;
import java.awt.BorderLayout;
import javax.swing.JPanel;
import java.awt.event.MouseListener;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import com.gensym.ui.RepresentationConstraints;
import javax.swing.SwingConstants;
import com.gensym.message.Trace;
import com.gensym.classes.Item;
import com.gensym.jgi.G2AccessException;
import javax.swing.JTable;
import java.awt.Window;
import java.awt.Frame;
import java.awt.Dialog;
import java.awt.Font;
import java.awt.Component;
import java.awt.Insets;
import java.awt.Container;
import java.awt.Dimension;
import javax.swing.event.ListSelectionListener;
import javax.swing.event.ListSelectionEvent;
import javax.swing.SwingConstants;
import javax.swing.AbstractButton;
import com.gensym.ui.RepresentationConstraints;
import com.gensym.ui.menu.CMenu;
import com.gensym.ui.menu.CMenuBar;
import com.gensym.jgi.G2Access;
import com.gensym.uitools.utils.FontUtil;

public class InspectWindow extends JPanel
implements ActionListener, InspectSessionListener
{
  private static Resource i18n
  = Resource.getBundle("com/gensym/uitools/inspect/InspectShortResource");
  private static String FIND = i18n.getString("find");
  private static final String DEFAULT_ERROR_LOCATION_MESSAGE
  = " inspect session request.";
  private static final String MODULARIZATION_IS_OK = i18n.getString("modularizationOK");
  
  private ErrorHandler defaultErrorHandler = new ErrorHandler()
  {
    @Override
    public void handleError(Exception e) {
      String message = null;
      if (e instanceof InspectSessionException) {
	if (historyCommand != null)
	  historyCommand.removeSession(((InspectSessionException)e).getSource());
	controlPanel.setIdle();
	controlPanel.setRunning(false);
	sessionViewer.setRecievingUpdates(false);
	message = ((InspectSessionException)e).getSource().toString();
      } else
	message = DEFAULT_ERROR_LOCATION_MESSAGE;
      message=e.getMessage() + " in:\n" + message;
      new ErrorDialog((window instanceof Frame)? (Frame)window:null,
		      i18n.getString("inspectExecutionError"),
		      true, message,
		      null).setVisible(true);
    }	    
  };
  private InspectSessionViewer sessionViewer;
  private InspectControlPanel controlPanel;
  private MouseListener tableInputHandler;
  static final Resource i18ui =
  Resource.getBundle ("com/gensym/uitools/inspect/InspectMainMenuShortResource");
  private static final Symbol TABLE_HEADER_ = Symbol.intern ("TABLE-HEADER");
  private InspectHistoryCommand historyCommand;
  private InspectItemCommands inspectItemCommands;
  private InspectMainMenuCommands inspectMainMenuCommands;
  private Window window;
  private InspectSession inspectSession;
  private static Insets buttonInsets = new Insets(0,10,0,10);
  private static Insets menuInsets = null;//new Insets(2,0,2,5);
  
  public InspectWindow(Window window)
  {
    this.window = window;
    setResizability(false);
    window.addWindowListener(new java.awt.event.WindowAdapter() {
      @Override
      public void windowClosing(java.awt.event.WindowEvent e ) {
	dispose();
      }
    });    
    setLayout(new BorderLayout());
    
    sessionViewer = new InspectSessionViewer();
    JTable table = sessionViewer.getTable();
    inspectItemCommands = new InspectItemCommands();
    inspectItemCommands.setWindow(window);
    tableInputHandler = createTableInputHandler(table,inspectItemCommands);
    
    table.getSelectionModel().addListSelectionListener
      ((ListSelectionListener)tableInputHandler);
    table.addMouseListener(tableInputHandler);
    controlPanel = new InspectControlPanel((window instanceof Frame)?
					   (Frame)window:null);
    controlPanel.addActionListener(this);
    CMenuBar mainMenuBar = createMainMenu(window, inspectItemCommands, sessionViewer);
    FontUtil.initMenuElement(mainMenuBar, menuInsets, FontUtil.sanserifPlain11);
    JPanel mainPanel = new JPanel();
    mainPanel.setLayout(new BorderLayout());
    mainPanel.add(BorderLayout.NORTH, controlPanel);
    mainPanel.add(BorderLayout.CENTER, sessionViewer);
    add(BorderLayout.NORTH, mainMenuBar);
    add(BorderLayout.CENTER, mainPanel);
    setFont(FontUtil.sanserifPlain11);
    setButtonMarginsForContainer(this, buttonInsets);
    sessionViewer.setVisible(false);
  }

  public InspectControlPanel getControlPanel() {
    return controlPanel;
  }

  public InspectSessionViewer getInspectSessionViewer() {
    return sessionViewer;
  }
  
  private void setButtonMarginsForContainer(Container container,
					    Insets margins)
  {
    if (container instanceof AbstractButton)
      ((AbstractButton)container).setMargin(margins);
    else {
      Component[] components = container.getComponents();
      for (int i=0;i<components.length;i++) {
	Component component = components[i];
	if (component instanceof Container)
	  setButtonMarginsForContainer((Container)component,
				       margins);
      }
    }
  }  

  @Override
  public void setFont(Font font) {
    super.setFont(font);
    FontUtil.setFontForContainer(this, font, false);
  }
  
  public void addConnection(TwAccess connection)
  {
    controlPanel.addConnection(connection);
  }

  public void removeConnection(TwAccess connection)
  {
    controlPanel.removeConnection(connection);
  }
  
  public void selectConnection(TwAccess connection)
  {
    controlPanel.selectConnection(connection);
  }
  
  protected CMenuBar createMainMenu(Window window,
				    InspectItemCommands inspectItemCommands,
				    InspectSessionViewer sessionViewer)
  {
    RepresentationConstraints menuConstraints = 
      new RepresentationConstraints(RepresentationConstraints.TEXT_AND_ICON,
				    SwingConstants.LEFT, 
				    SwingConstants.CENTER, 
				    SwingConstants.RIGHT, 
				    SwingConstants.CENTER);    
    CMenuBar applnMenuBar = new com.gensym.ui.menu.CMenuBar();
    CMenu fileMenu = new CMenu(i18ui.getString ("file"));
    fileMenu.setMnemonic(i18ui.getString("FileMenuMnemonic").charAt(0));
    inspectMainMenuCommands = new InspectMainMenuCommands(window, this);
    historyCommand = new InspectHistoryCommand(this);
    fileMenu.add(historyCommand);
    fileMenu.addSeparator();
    fileMenu.add(inspectMainMenuCommands, inspectMainMenuCommands.EXIT,
		 menuConstraints);
    applnMenuBar.add(fileMenu);
    CMenu editMenu = new CMenu(i18ui.getString ("edit"));
    editMenu.setMnemonic(i18ui.getString("EditMenuMnemonic").charAt(0));
    editMenu.add(inspectItemCommands, menuConstraints);
    editMenu.addSeparator();
    editMenu.add(inspectMainMenuCommands, inspectMainMenuCommands.SELECT_ALL,
		 menuConstraints);
    editMenu.add(inspectMainMenuCommands, inspectMainMenuCommands.INVERT_SELECTION);
    applnMenuBar.add(editMenu);
    CMenu viewMenu = new CMenu(i18ui.getString ("view"));
    viewMenu.setMnemonic(i18ui.getString("ViewMenuMnemonic").charAt(0));
    viewMenu.add(inspectMainMenuCommands, inspectMainMenuCommands.VIEW_STATUS_BAR);
    viewMenu.add(inspectMainMenuCommands, inspectMainMenuCommands.VIEW_CONTROL_PANEL);
    applnMenuBar.add(viewMenu);
    CMenu optionsMenu = new CMenu(i18ui.getString ("options"));
    optionsMenu.setMnemonic(i18ui.getString("OptionsMenuMnemonic").charAt(0));
    optionsMenu.add(inspectMainMenuCommands,
		    inspectMainMenuCommands.SHOW_ITEMS_WHEN_FOUND);
    optionsMenu.add(inspectMainMenuCommands,
		    inspectMainMenuCommands.AUTOMATIC_ATTRIBUTE_UPDATES);
    optionsMenu.addSeparator();
    optionsMenu.add(inspectMainMenuCommands,
		    inspectMainMenuCommands.FORCE_RECOMPILE);
    optionsMenu.add(inspectMainMenuCommands, inspectMainMenuCommands.SAVE_RESULTS);
    applnMenuBar.add(optionsMenu);    
    CMenu helpMenu = new CMenu(i18ui.getString ("help"));
    helpMenu.setMnemonic(i18ui.getString("HelpMenuMnemonic").charAt(0));
    helpMenu.add(inspectMainMenuCommands, inspectMainMenuCommands.ABOUT,
		 menuConstraints);
    applnMenuBar.add(helpMenu);
    return applnMenuBar;
  }
  
  private MouseListener createTableInputHandler(JTable table,
						InspectItemCommands commands)
  {
    return new TableInputHandler(table,commands);
  }

  private static final int CLEARED_SIZE = 225,
    VIEWER_HEIGHT = 150;
  private void adjustParentSize(int height) {
    Dimension size = window.getSize();
    size.height = height;    
    window.setSize(size);
    window.validate();
  }

  private void setResizability(boolean state) {
    if (window instanceof Frame)
      ((Frame)window).setResizable(state);
    else
      ((Dialog)window).setResizable(state);
  }
  
  @Override
  public void actionPerformed(ActionEvent ae) {
    String cmd = ae.getActionCommand();
    if (InspectControlPanel.CLEAR.equals(cmd)) {
      sessionViewer.setVisible(false);      
      adjustParentSize(CLEARED_SIZE);
      sessionViewer.clear();
      sessionViewer.setRecievingUpdates(false);
      setResizability(false);
    } else if (InspectControlPanel.PAUSE.equals(cmd)) {
      sessionViewer.setRecievingUpdates(false);
      inspectSession.pause();
      controlPanel.setIdle();
    } else if (InspectControlPanel.RESUME.equals(cmd)) {
      sessionViewer.setRecievingUpdates(true);
      controlPanel.setBusy();      
      inspectSession.resume();
    } else if (InspectControlPanel.STOP.equals(cmd)) {
      inspectSession.stop();            
      controlPanel.setIdle();
      controlPanel.setRunning(false);
      sessionViewer.setRecievingUpdates(false);
    } else if (InspectControlPanel.FIND.equals(cmd)||
	       InspectControlPanel.RECOMPILE.equals(cmd)||
	       InspectControlPanel.WRITE.equals(cmd)) {
      setResizability(true);
      adjustParentSize(CLEARED_SIZE+VIEWER_HEIGHT);      
      sessionViewer.setVisible(true);
      Object[] connections = controlPanel.getSelectedConnections();
      if (connections.length > 0) {
	controlPanel.setRunning(true);
	controlPanel.setBusy();
      }
      doInspect(controlPanel.getClassName(),
		controlPanel.getItemName(),
		controlPanel.getExtraFilters(),
		controlPanel.getDisplayAttributes(),
		connections);
      sessionViewer.setRecievingUpdates(true);      
    }
  }

  public void dispose() {
    if (inspectSession != null)
      inspectSession.dispose();
    inspectSession = null;
    if (historyCommand != null) {
      historyCommand.dispose();
      historyCommand = null;
    }
    sessionViewer.setModel(null);
    sessionViewer = null;
    controlPanel = null;
    tableInputHandler = null;
    inspectItemCommands.setModel(null);    
    inspectItemCommands = null;
    if (inspectMainMenuCommands != null)
      inspectMainMenuCommands.setModel(null);    
    inspectMainMenuCommands = null;
    window = null;
  }

  public InspectSession getCurrentInspectSession() {
    return inspectSession;
  }

  String getPrettyPrefix() {
    if (InspectSession.SHOW.equals(prefix)) {
      if (sessionViewer.isShowItemsWhenFound())
	return i18n.getString("GoTo");
      else
	return i18n.getString("Inspect");
    } else
      return prefix+" ";
  }

  void adjustTitle() {
    String title = getPrettyPrefix();
    if (inspectSession != null) {
      String suffix = inspectSession.getFilterText();
      if (title.endsWith(" "))
	title+=suffix;
      else title+=" "+suffix;
    } 
    if (window instanceof Dialog)
      ((Dialog)window).setTitle(title);
    else if (window instanceof Frame)
      ((Frame)window).setTitle(title);
  }

  private String prefix = InspectSession.SHOW;
  public void setPrefix(String prefix) {
    this.prefix = prefix;
    if (inspectSession != null)
      inspectSession.setPrefix(prefix);
    adjustTitle();
  }
  
  private void doInspect(String className,
			 String itemName,
			 String extraFilters,
			 Symbol[] attributesToDisplay,
			 Object[] connections)
  {
    if (inspectSession != null) {
      inspectSession.dispose();
      inspectSession = null;
    }
    String defaultLabel = null;
    if (InspectSession.CHECK_MODULARIZATION.equals(prefix)) {
      defaultLabel = MODULARIZATION_IS_OK;
      inspectSession = new InspectSession("");
    } else if (InspectSession.SHOW.equals(prefix))
      inspectSession =
	new InspectSession(className, itemName, extraFilters);
    else
      inspectSession =
	new InspectSession(className, itemName, extraFilters, attributesToDisplay); 
    inspectSession.setPrefix(prefix);    
    adjustTitle();
    if (historyCommand != null)
      historyCommand.addSession(inspectSession, attributesToDisplay);
    inspectSession.setErrorHandler(defaultErrorHandler);
    ItemTableModel itemTableModel = new ItemTableModel();
    if (defaultLabel != null)
      itemTableModel.addLabel(defaultLabel);

    if (attributesToDisplay.length == 0) {
      itemTableModel.addColumn(TABLE_HEADER_);
      itemTableModel.setDisplayColumnNames(false);
    } else 
      for (int i=0;i<attributesToDisplay.length;i++) 
	itemTableModel.addColumn(attributesToDisplay[i]);
    sessionViewer.setModel(itemTableModel);
    //window.validate();
    inspectItemCommands.setModel(itemTableModel);
    if (inspectMainMenuCommands != null)
      inspectMainMenuCommands.setModel(itemTableModel);
    inspectSession.addInspectSessionListener(sessionViewer);
    inspectSession.addInspectSessionListener(this);
    for (int i=0;i<connections.length;i++) 
      inspectSession.addConnection((G2Access)connections[i]);
    inspectSession.start();
  }

  private static final Symbol FINISHED_ = Symbol.intern ("FINISHED");
  @Override
  public void infoUpdated(InspectSessionEvent event)
  {
    Symbol status = event.getStatus();
    if (FINISHED_.equals(status)) {
      controlPanel.setIdle();
      controlPanel.setRunning(false);
    } else 
      controlPanel.setBusy();
  }    
  
}
  
