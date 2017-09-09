package com.gensym.uitools.utils;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.Dimension;
import java.awt.Insets;
import java.awt.Window;
import java.awt.Component;
import java.awt.Font;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.border.EtchedBorder;
import javax.swing.border.BevelBorder;
import javax.swing.border.EmptyBorder;
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JComboBox;
import javax.swing.JSplitPane;
import javax.swing.JTree;
import com.gensym.jdlg.JInputDialog;
import com.gensym.dlg.ErrorDialog;
import com.gensym.ui.menu.CMenuBar;
import com.gensym.ui.menu.CMenu;
import com.gensym.message.Resource;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import javax.swing.tree.TreePath;
import com.gensym.ui.toolbar.ToolBar;

public class JExplorer extends JPanel {
  private static Font defaultFont = new Font("sansserif", Font.PLAIN, 11);
  private static final Insets menuInsets = null;//new Insets(0,0,0,0);
  private static final Resource mnemonicsi18n  
  = Resource.getBundle("com/gensym/uitools/utils/JExplorerMnemonicResource");
  private static final Resource i18n
  = Resource.getBundle("com/gensym/uitools/utils/JExplorerShortResource");
  private Font font = defaultFont;
  private JPanel inputPanel;
  private Object[] currentArguments;
  JExplorerSplitPane splitPane;
  public static final int VIEW_DETAILS = 0, VIEW_LIST = 1;

  public JExplorer(String[] argumentLabels,
		   JTree tree,
		   JExplorerTableModel tableModel,
		   JTableIconFactory tableIconFactory,
		   Component container)
  {
    this(argumentLabels,
	 new JExplorerSplitPane(tree, tableModel, tableIconFactory),
	 container);
  }
  
  public JExplorer(String[] argumentLabels,
		   JExplorerSplitPane splitPane,
		   Component container)
  {
    this(argumentLabels, splitPane, container, true, true);
  }

  public JExplorer(String[] argumentLabels,
		   JExplorerSplitPane splitPane,
		   Component container,
		   boolean showMenuBar,
		   boolean showToolBar) {
    if (argumentLabels != null)
      currentArguments = new Object[argumentLabels.length];
    else
      currentArguments = new Object[0];
    this.splitPane = splitPane;
    ActionListener argumentListener = new ArgumentListener();
    RootNodeRefresher rootRefresher = new RootNodeRefresher();
    splitPane.tree.addMouseListener(rootRefresher);
    
    setLayout(new BorderLayout());
    
    int topPanelCount = 0;
    if (argumentLabels != null) { 
      inputPanel = createInputPanel(argumentLabels,
				    currentArguments,
				    argumentListener,
				    font);
      if (inputPanel != null)
	topPanelCount++;
    }
    JExplorerMainMenuCommands commands =
      new JExplorerMainMenuCommands(this, container);    
    CMenuBar mainMenu = null;
    if (showMenuBar)
      mainMenu = createMenuBar(this, commands, container);
    if (mainMenu != null)
      topPanelCount++;

    ToolBar toolbar = null;
    if (showToolBar)
      toolbar = createToolBar(this, commands, container);
      
    JPanel topPanel = new JPanel();
    topPanel.setLayout(new GridLayout(topPanelCount,1));    
    if (mainMenu != null)
      topPanel.add(mainMenu);

    if (toolbar != null && inputPanel != null) {
      JPanel barPanel = new JPanel();
      barPanel.setLayout(new BorderLayout());
      barPanel.add(inputPanel, "Center");
      barPanel.add(toolbar, "East");
      topPanel.add(barPanel);
    } else {
      if (inputPanel != null)
	topPanel.add(inputPanel);
      if (toolbar != null)
	topPanel.add(toolbar);
    }
    
    
    add(topPanel, "North");  
    add(splitPane, "Center");    
  }

  @Override
  public void setFont(Font font) {
    this.font = font;
  }

  protected ToolBar createToolBar(JExplorer explorer,
				  JExplorerMainMenuCommands commands,
				  Component container) {
    ToolBar toolbar = new ToolBar ();
    toolbar.setBorder(new BevelBorder(BevelBorder.LOWERED));
    toolbar.add(commands,commands.EXPAND_ALL);
    toolbar.add(commands,commands.COLLAPSE_ALL);
    toolbar.addSeparator();    
    toolbar.add(commands,commands.REFRESH_VIEW);
    toolbar.addSeparator();
    toolbar.add(commands,commands.VIEW_LIST);
    toolbar.add(commands,commands.VIEW_DETAILS);
    //toolbar.add(commands, EDIT_ATTRIBUTES);
    return toolbar;
  }
  
  protected CMenuBar createMenuBar(JExplorer explorer,
				   JExplorerMainMenuCommands mainMenuCommands,				   
				   Component container) {
    CMenuBar mainMenu = new CMenuBar();
    mainMenu.setBorder(new EtchedBorder());
    CMenu fileMenu = new CMenu(i18n.getString("file"));
    fileMenu.setMnemonic(mnemonicsi18n.getString("file").charAt(0));    
    fileMenu.add(mainMenuCommands,mainMenuCommands.CLOSE);
    mainMenu.add(fileMenu);
    CMenu viewMenu = new CMenu(i18n.getString("view"));
    viewMenu.setMnemonic(mnemonicsi18n.getString("view").charAt(0));
    viewMenu.add(mainMenuCommands,mainMenuCommands.VIEW_LIST);
    viewMenu.add(mainMenuCommands,mainMenuCommands.VIEW_DETAILS);
    viewMenu.addSeparator();
    viewMenu.add(mainMenuCommands,mainMenuCommands.EXPAND_ALL);
    viewMenu.add(mainMenuCommands,mainMenuCommands.COLLAPSE_ALL);
    viewMenu.addSeparator();    
    viewMenu.add(mainMenuCommands,mainMenuCommands.REFRESH_VIEW);
    viewMenu.addSeparator();
    viewMenu.add(mainMenuCommands,mainMenuCommands.EDIT_ATTRIBUTES);
    mainMenu.add(viewMenu);
    //CMenu goMenu = new CMenu(i18n.getString("go"));
    //mainMenu.add(goMenu);
    CMenu helpMenu = new CMenu(i18n.getString("help"));
    helpMenu.setMnemonic(mnemonicsi18n.getString("help").charAt(0));    
    helpMenu.add(mainMenuCommands,mainMenuCommands.ABOUT);
    mainMenu.add(helpMenu);
    //mainMenu.setHelpMenu(helpMenu);
    mainMenu.setBorderPainted(true);
    FontUtil.initMenuElement(mainMenu, menuInsets, font);
    return mainMenu;
  }

  class RootNodeRefresher extends MouseAdapter {
    @Override
    public void mouseReleased(MouseEvent e) {
      if (e.getClickCount() > 1) {
	int x = e.getX();
	int y = e.getY();
	TreePath path = splitPane.tree.getPathForLocation(x, y);     
	if (path != null &&
	    splitPane.tree.getModel().getRoot() == path.getLastPathComponent())
	  refresh();
      }
    }
  }
  
  class ArgumentListener implements ActionListener {
    boolean removing = false;
    @Override
    public void actionPerformed(ActionEvent ae) {
      if (removing) return;
      IndexedJComboBox comboBox = (IndexedJComboBox)ae.getSource();
      String newText = comboBox.getSelectedItem().toString().trim();     
      if (newText.equals(""))
	currentArguments[comboBox.index] = null;
      else {
	removing = true;
	comboBox.removeItem(newText);
	comboBox.insertItemAt(newText,0);
	comboBox.setSelectedItem(newText);
	removing = false;
	currentArguments[comboBox.index] = newText;
      }
      refresh();
    }
  }

  public void setViewType(int type) {
    splitPane.setViewType(type);
  }
  
  public void refresh() {
    splitPane.tree.clearSelection();
    splitPane.refresh(currentArguments);
    splitPane.tree.setSelectionRow(0);    
  }
  
  private static JPanel createInputPanel(String[] labels,
					 Object[] initialValues,
					 ActionListener actionListener,
					 Font font)
  {
    JPanel inputPanel = new JPanel();
    inputPanel.setBorder(new EtchedBorder());
    int count = labels.length;
    inputPanel.setLayout(new GridLayout(1,count));
    for (int i=0;i<count;i++) {
      JLabel label = new JLabel(labels[i]);
      label.setBorder(new EmptyBorder(new Insets(0,10,0,3)));
      label.setFont(font);
      Object initialValue = initialValues[i];
      JComboBox comboBox = new IndexedJComboBox(initialValue!=null?
						 initialValue.toString():"",
						 i);
      comboBox.setBorder(new BevelBorder(BevelBorder.LOWERED));
      //new EmptyBorder(new Insets(0,10,0,5)));
      if (actionListener != null) comboBox.addActionListener(actionListener);
      JPanel subPanel = new JPanel();
      subPanel.setLayout(new BorderLayout());
      subPanel.add(label,"West");
      subPanel.add(comboBox, "Center");
      inputPanel.add(subPanel);
    }
    return inputPanel;
  }
}

class IndexedJComboBox extends JComboBox {
  int index;
  IndexedJComboBox(Object initialValue, int index) {
    super();
    if (!("".equals(initialValue)))
      addItem(initialValue);
    setSelectedItem(initialValue);
    setEditable(true);
    this.index = index;
  }
}


