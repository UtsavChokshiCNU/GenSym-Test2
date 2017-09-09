package com.gensym.uitools.inspect;

import javax.swing.JTable;
import javax.swing.JScrollPane;
import javax.swing.JPanel;
import com.gensym.util.Symbol;
import com.gensym.uitools.tables.ItemTableModel;
import java.util.Enumeration;
import java.util.Vector;
import java.awt.BorderLayout;
import com.gensym.uitools.utils.StatusBar;
import com.gensym.classes.Item;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.event.MouseListener;
import com.gensym.uitools.utils.JExplorerTableCellRenderer;
import javax.swing.ListSelectionModel;
import java.util.Hashtable;
import com.gensym.jgi.G2Access;
import javax.swing.JTabbedPane;
import javax.swing.SwingConstants;
import javax.swing.event.ChangeListener;
import javax.swing.event.ChangeEvent;
import com.gensym.classes.KbWorkspace;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import javax.swing.table.JTableHeader;
import java.awt.Font;
import com.gensym.uitools.utils.WhiteBackgroundJScrollPane;
import java.awt.Component;
import javax.swing.JComponent;
import javax.swing.border.EmptyBorder;
import javax.swing.border.LineBorder;

public class InspectSessionViewer extends JPanel
implements InspectSessionListener, ChangeListener
{
  static Font theFont = new Font("sansserif", Font.PLAIN, 11);
  static Font theBoldFont = new Font("sansserif", Font.BOLD, 11);
  private static final Symbol FINISHED_ = Symbol.intern ("FINISHED");  
  private ItemTableModel model;
  private InspectSessionViewerTableCellRenderer cellRenderer; 
  private Hashtable statusBars = new Hashtable();
  private JTabbedPane statusBarPanel;
  private JTable table;
  private static Image noItemImage, itemImage;
  private static EmptyBorder noBorder = new EmptyBorder(0,0,0,0);
  private static EmptyBorder leftBorder = new EmptyBorder(0,10,0,0);
  private ConnectionFilter connectionFilter;
  private boolean showItemsWhenFound = false;
  private boolean recievingUpdates = true;
  private Boolean started = Boolean.FALSE;

  public InspectSessionViewer()
  {
    table = new JTable();
    connectionFilter = new ConnectionFilter();
    table.setSelectionMode(ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);
    table.setShowGrid(false);
    table.setShowHorizontalLines(false);
    table.setShowVerticalLines(false);
    table.setIntercellSpacing(new java.awt.Dimension(7,0));
    table.setRowHeight(20);
    //table.sizeColumnsToFit(table.AUTO_RESIZE_OFF);
    cellRenderer = new InspectSessionViewerTableCellRenderer(null);
    table.setDefaultRenderer(Object.class, cellRenderer);
    //table.setAutoResizeMode(table.AUTO_RESIZE_OFF);
    JTableHeader header = table.getTableHeader();
    header.setUpdateTableInRealTime(false);
    header.setFont(theFont);
    header.setAlignmentY(0);
    header.setAlignmentX(0);
    statusBarPanel = new JTabbedPane();
    statusBarPanel.addChangeListener(this);
    statusBarPanel.setTabPlacement(SwingConstants.BOTTOM);
    JScrollPane scrollPane = new WhiteBackgroundJScrollPane(table);
    setLayout(new BorderLayout());
    add(BorderLayout.CENTER, scrollPane);
    add(BorderLayout.SOUTH, statusBarPanel);
  }

  class InspectSessionViewerTableCellRenderer extends JExplorerTableCellRenderer
  {
    private ItemTableModel model;
    InspectSessionViewerTableCellRenderer(ItemTableModel model) {
      super(model);
      this.model = model;
    }
    void setModel(ItemTableModel model) {
      this.model = model;
      setJTableIconFactory(model);
    }
    @Override
    public Component getTableCellRendererComponent(JTable table,
						   Object value,
						   boolean isSelected,
						   boolean hasFocus,
						   int row,
						   int column){
      JComponent component = (JComponent)
	super.getTableCellRendererComponent(table,
					    value,
					    isSelected,
					    hasFocus,
					    row,
					    column);
      if (model != null && model.getRow(row) == null) {
	component.setFont(theBoldFont);
	component.setBorder(noBorder);
      } else {
	component.setBorder(leftBorder);
	component.setFont(theFont);
      }
      return component;
    }
  }
  
  private java.awt.Dimension lastVisibleSize;
  @Override
  public void setVisible(boolean visible) {
    if (!visible)
      lastVisibleSize = getSize();
    super.setVisible(visible);
    if (visible)
      setSize(lastVisibleSize);
  }
  
  public JTable getTable()
  {
    return table;
  }

  public boolean isViewAsText()
  {
    if (model != null)
      return model.isViewAsText();
    else
      return false;
  }

  public void setStatusBarVisible(boolean statusBarVisible)
  {
    statusBarPanel.setVisible(statusBarVisible);
    revalidate();
  }

  public boolean isStatusBarVisible()
  {
    return statusBarPanel.isVisible();
  }
  
  public void setViewAsText(boolean viewAsText)
  {
    if (model != null)
      model.setViewAsText(viewAsText);
  }

  public InspectSessionViewer(ItemTableModel model)
  {
    this();
    setModel(model);
  }

  public void clear()
  {
    connectionFilter.setConnection(null);
    if (model != null) {
      synchronized(model) {
	model.removeAll();
      }
      model.update();
    }
    statusBarPanel.removeAll();
    statusBars.clear();
    validate();
  }
  
  public void setAutomaticAttributeUpdates(boolean automaticAttributeUpdates)
  {
    if (model != null)
      model.setAutomaticAttributeUpdates(automaticAttributeUpdates);
  }

  public boolean isAutomaticAttributeUpdates()
  {
    if (model != null)
      return model.isAutomaticAttributeUpdates();
    else
      return false;
  }

  public boolean isShowItemsWhenFound()
  {
    return showItemsWhenFound;
  }  

  public void setShowItemsWhenFound(boolean showItemsWhenFound)
  {
    this.showItemsWhenFound = showItemsWhenFound;
  }  
  
  private ServerStatusBar allStatusBar = new ServerStatusBar(1,null);
  public void setModel(ItemTableModel model)
  {
    cellRenderer.setModel(model);
    if (this.model != null)
      this.model.removeFilter(connectionFilter);
    boolean viewAsText = isViewAsText();
    boolean automaticUpdates = isAutomaticAttributeUpdates();
    this.model = model;
    if (model != null)
      model.addFilter(connectionFilter);
    setViewAsText(viewAsText);
    setAutomaticAttributeUpdates(automaticUpdates);
    if (model != null) 
      table.setModel(model);
  }

  public boolean isRecievingUpdates(){
    return recievingUpdates;
  }

  private Vector cachedEvents = new Vector();  
  private void decacheEvents() {
    Enumeration e = cachedEvents.elements();
    while (e.hasMoreElements())
      handleEvent((InspectSessionEvent)e.nextElement());
    cachedEvents.clear();
  }
  
  public void setRecievingUpdates(boolean recievingUpdates){
    synchronized(cachedEvents) {
      decacheEvents();
      this.recievingUpdates = recievingUpdates;
    }
  }

  @Override
  public void infoUpdated(InspectSessionEvent event)
  {
    if (!recievingUpdates) {
      cachedEvents.addElement(event);
      return;
    } else
      handleEvent(event);
  }

  private void handleEvent(InspectSessionEvent event)
  {
    Symbol status = event.getStatus();    
    synchronized(started) {
      if (!started.booleanValue() && !FINISHED_.equals(status)) {
	model.removeAll();//clear out any default messages
	started = Boolean.TRUE;
      }
    }
    InspectSession session = (InspectSession)event.getSource();

    int itemsToExamine = event.getItemsToExamine();
    int numberOfItemsExaminedSoFar = event.getNumberOfItemsExaminedSoFar();
    int numberOfItemsFound = event.getNumberOfItemsFound();
    Object server = event.getServer();
    String statusString0="",statusString1="",statusString2="", tabString;
    if (server instanceof G2Access)
      tabString = ((G2Access)server).toShortString();
    else
      tabString = server.toString();
    ServerStatusBar statusBar = (ServerStatusBar)statusBars.get(server);
    if (statusBar == null) {
      statusBar = new ServerStatusBar(3,server);
      statusBars.put(server, statusBar);
      statusBarPanel.addTab(tabString,statusBar);
      if (statusBarPanel.getTabCount() == 2) {
	//PBK i18n
	statusBarPanel.insertTab("   All   ",
				 null,
				 allStatusBar,
				 "Show all items",0);
      }      
    }
    statusBarPanel.setSelectedComponent(statusBar);
    
    if (itemsToExamine != 0) {
      //PBK i18n
      statusString0 =
	(numberOfItemsExaminedSoFar*100/itemsToExamine) + "% done";
      statusString1 =
	"Searched " + numberOfItemsExaminedSoFar + " of " + itemsToExamine;
      statusString2 = 
	"Found " + numberOfItemsFound + " " + session.getClassName() + "(s)";
    } else {
      statusString0 = " No " + session.getClassName() + "s to examine";
    }
    statusBar.setStatus(statusString0,0);
    statusBar.setStatus(statusString1,1);
    statusBar.setStatus(statusString2,2);
    statusBarPanel.invalidate();
    statusBarPanel.repaint();
    
    Vector newItemsFound = event.getNewItemsFound();
    Enumeration e = newItemsFound.elements();
    boolean needUpdate = false;
    while(e.hasMoreElements()) {
      Object elt = e.nextElement();
      if (elt instanceof Item) {
	Item item = (Item)elt;
	if (model.addRow(item))
	  needUpdate = true;
	if (showItemsWhenFound) {
	  try {
	    Item[] items = InspectItemCommands.getWorkspaceAndItemOnWksp(item);
	    if (items != null)
	      InspectItemCommands.goToItem((Item)items[InspectItemCommands.ITEM],
					   (KbWorkspace)items[InspectItemCommands.WKSP]);
	  } catch (G2AccessException g2ae) {
	    Trace.exception(g2ae);
	  }
	}
      } else if (elt instanceof String) {
	model.addLabel((String)elt);
	needUpdate = true;
      }
      else {
	System.out.println("GOT: " + elt);
      }
    }
    if (needUpdate)
      model.update();
  }

  @Override
  public void stateChanged(ChangeEvent statusBarChanged) {
    ServerStatusBar statusBar = (ServerStatusBar)statusBarPanel.getSelectedComponent();
    if (statusBar != null) 
      connectionFilter.setConnection((G2Access)statusBar.server);
    else 
      connectionFilter.setConnection(null);
    model.filter();
    if (statusBar == allStatusBar) {
      //PBK i18n
      String statusString = "Total Items: " + model.getRowCount();
      statusBar.setStatus(statusString, 0);
    }
  }
  
}

class ServerStatusBar extends StatusBar {
  Object server;
  ServerStatusBar(int rows, Object server) {
    super(rows);
    this.server=server;
  }
}
