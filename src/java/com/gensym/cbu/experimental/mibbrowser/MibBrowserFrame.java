package com.gensym.cbu.experimental.mibbrowser;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.tree.*;
import java.util.*;
import com.sun.xml.tree.*;
import org.w3c.dom.*;
import com.adventnet.snmp.mibs.*;


public class MibBrowserFrame extends JFrame
  implements FileOpenActionListener, ActionListener, TreeSelectionListener,
  MibFileLoaderListener
{
  JPanel mainLeftPanel, mainRightPanel, statusPanel;
  JTextArea status;
  JSplitPane splitPane;
  FileOpenAction fileOpenAction;
  FileExitAction fileExitAction;
  HelpAboutAction helpAboutAction;
  MibFileOrganizer mfo;
  AttributeTable attributeTable;
  AttributePanel attributePanel;
  final MibOperations mibOperations = new MibOperations();

  @Override
  public void loadingFile(String mibFile)
    {
      status.setText("loading required file: " + mibFile);
    }

  @Override
  public void loadError(String mibFile, String msg) {
    status.setText("ERROR LOADING MIB FILE: " + mibFile + "(" + msg + ")");
  }

  public void requiredFileLoaded(MibModule mibModule)
    {
      status.setText("required file loaded: " + mibModule);
      mfo.add(mibModule);
    }

  public void loadFinished(MibModule mibModule) {
    status.setText("mib file loaded: " + mibModule);
    mfo.add(mibModule);
  }

  //FileOpenActionListener Interface
  @Override
  public void openFile(final File file) {
    openFile(file, true);
  }

  public void openFile(final File file, final boolean recurse) {
    final MibFileLoaderNew loader = new MibFileLoaderNew(mibOperations);
    loader.setSearchPath(new MibDirectories().directories);
    loader.addMibFileLoaderListener(this);
    SwingWorker loaderThread = new SwingWorker() {


      @Override
      public Object construct() {
        if(file.isFile())
          loader.loadMibFile(file);
        else if (file.isDirectory())
          loader.loadAllMibFiles(file, recurse);
        return loader;
      }

    	@Override
    	public void finished() {
  	  }
    };
  }
  //end FileOpenActionListener Interface

  public void loadMibFile(final String fileName) {
    final SwingWorker sw = new SwingWorker () {
      MibModule mibModule = null;
    	@Override
	    public Object construct() {
        Thread.currentThread().setPriority(Thread.MIN_PRIORITY);
        status.setText("LOADING MIB FILE: " + fileName);
	      try {
          mibOperations.setThrowFileNotFound(true);
          mibModule = mibOperations.loadMibModule(fileName);
          System.out.println("MODULE: " + mibModule.toString());
        } catch (FileNotFoundException fnfe) {
          System.err.println("Required MIB not found. "+ fnfe);
        } catch (Exception ex) {
	 	      System.err.println("Error loading MIBs:\n "+ex);
          status.setText("Error loading MIB FILE: "+ex);
	      }
        return mibModule;
	    }

	    @Override
	    public void finished() {
        if (mibModule != null)
          mfo.add(mibModule);
        status.setText("Done.");
	    }
    };
  }

  public MibBrowserFrame ()
    {
	super("MIB Browser");

	//setLookAndFeel();

  mibOperations.setThrowFileNotFound(true);
	Container container = getContentPane();

	createActions();
	addMenuBar();
	//addToolBar(container);

	mainLeftPanel = new JPanel();
	mainLeftPanel.setBackground(new Color(255,255,255));
	mainLeftPanel.setLayout(new BoxLayout(mainLeftPanel,
					      BoxLayout.Y_AXIS));

	mainRightPanel = new JPanel();
	mainRightPanel.setBackground(new Color(255,255,255));
	mainRightPanel.setLayout(new BoxLayout(mainRightPanel,
					       BoxLayout.Y_AXIS));

/*
	attributeTable = new AttributeTable();
	JScrollPane mainRightScrollPane = new JScrollPane(attributeTable.getTable());
	mainRightPanel.add(mainRightScrollPane);
*/
	attributePanel = new AttributePanel();
//	JScrollPane mainRightScrollPane = new JScrollPane(attributePanel);
	mainRightPanel.add(attributePanel);

	splitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT,
				   mainLeftPanel,
				   mainRightPanel);
	container.add(splitPane, BorderLayout.CENTER);
	splitPane.setDividerLocation(300);
	splitPane.setOneTouchExpandable(false);

	mfo = new MibFileOrganizer();
	mfo.getTree().addTreeSelectionListener(this);

		JScrollPane scrollPane = new JScrollPane(mfo.getTree());
	mainLeftPanel.add(scrollPane);

	statusPanel = new JPanel();
	statusPanel.setBorder(BorderFactory.createEtchedBorder());
	statusPanel.setLayout(new BorderLayout());
	container.add(statusPanel, BorderLayout.SOUTH);

  status = new JTextArea();
  status.setBackground(statusPanel.getBackground());
  status.setLineWrap(true);
  status.setWrapStyleWord(true);
  status.setRows (1);
	//status.setHorizontalAlignment(JLabel.LEFT);
	status.setText(" ");
	statusPanel.add(new JScrollPane(status,
                  JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,
                  JScrollPane.HORIZONTAL_SCROLLBAR_NEVER), BorderLayout.CENTER);

	setBounds(50,50,800,600);
	setVisible(true);
	setDefaultCloseOperation(DISPOSE_ON_CLOSE);	

	addWindowListener(new WindowAdapter () {
		@Override
		public void windowClosed(WindowEvent e)
		{
		    System.exit(0);
		}
	    });

	//openFile(new File("D:/gensym/Pinpoint/Event Handling/mibs/RFC1155-SMI"), false);
	//openFile(new File("D:/gensym/Pinpoint/Event Handling/mibs/BRIDGE-MIB"), false);
	//openFile(new File("D:/gensym/Pinpoint/Event Handling/mibs/BRIDGE-MIB"), false);
  	//openFile(new File("D:/gensym/Pinpoint/Event Handling/mibs"), true);
  	//openFile(new File("D:/gensym/Pinpoint/Event Handling/mibs"), true);
  	//openFile(new File("D:/gensym/Pinpoint/Event Handling/mibs"), true);
  }


    void createActions()
    {
	fileOpenAction = new FileOpenAction();
	fileOpenAction.addFileOpenActionListener((FileOpenActionListener)this);
	fileExitAction = new FileExitAction();
	helpAboutAction = new HelpAboutAction();
    }

    void addMenuBar()
    {
	//in the constructor for a JFrame subclass:
	JMenuBar menuBar;
	JMenu menu;
	JMenuItem menuItem;
	
	//Create the menu bar.
	menuBar = new JMenuBar();
	setJMenuBar(menuBar);

	//File Menu
	menu = new JMenu("File");
	menuBar.add(menu);

	menuItem = menu.add(fileOpenAction);
	menuItem.setToolTipText((String)fileOpenAction
				.getValue(Action.SHORT_DESCRIPTION));

 	menuItem = menu.add("Save Open Files As XML");
	menuItem.setToolTipText("Save all open traps & notifications");
  menuItem.setActionCommand("FILE_SAVE_MENU");
  menuItem.addActionListener(this);

	menu.addSeparator();

	menuItem = menu.add(fileExitAction);	
	menuItem.setToolTipText((String)fileExitAction
				.getValue(Action.SHORT_DESCRIPTION));


	//View
	//menu = new JMenu("View");
	//menuBar.add(menu);


	//Help
	menu = new JMenu("Help");
	menuBar.add(menu);

	menuItem = menu.add(helpAboutAction);
	menuItem.setToolTipText((String)helpAboutAction
				.getValue(Action.SHORT_DESCRIPTION));
    }

  //ActionListener Interface
  @Override
  public void actionPerformed(ActionEvent e) {
    String actionCommand = e.getActionCommand();
    if( actionCommand.equals("FILE_SAVE_MENU")) {
      saveAllOpenAsXML();
      }
  }
  //end ActionListener Interface


  
  void addToolBar(Container container)
    {
      JToolBar toolBar = new JToolBar();
      JButton button;
      
      button = toolBar.add(fileOpenAction);
      button.setToolTipText((String)fileOpenAction
			      .getValue(Action.SHORT_DESCRIPTION));

      container.add(toolBar, BorderLayout.NORTH);
    }

  void setLookAndFeel()
    {
      	try {
	    UIManager.setLookAndFeel(UIManager.
				     getSystemLookAndFeelClassName());
	} 
	catch (UnsupportedLookAndFeelException e) {
	    System.out.println("Unsupported L&F Error:" + e);	    
	}
	catch (ClassNotFoundException e) {
	    System.out.println("Unsupported L&F Error:" + e);	    
	}
	catch (InstantiationException e) {
	    System.out.println("Unsupported L&F Error:" + e);	    
	}
	catch (IllegalAccessException e) {
	    System.out.println("Unsupported L&F Error:" + e);
	}
    }


  @Override
  public void valueChanged(TreeSelectionEvent e) {
    JTree jTree = (JTree)e.getSource();
    DefaultMutableTreeNode node = (DefaultMutableTreeNode)
      jTree.getLastSelectedPathComponent();
    //System.out.println("node selected : " + node);
    //System.out.println(node + " has "
    //	       + node.getChildCount() + " children");
    if (node == null) return;
    Object uo = node.getUserObject();
    attributePanel.showAttributes(mibOperations,uo);

/*
    attributeTable.removeRows();

    Object object = node.getUserObject();
    if (object instanceof MibFileObject) {
      attributeTable.showObject((MibFileObjectTableObject)object);
    }
*/
  }

  private String unformatString(String s)
    {
      if (s != null) {
        StringBuffer results = new StringBuffer();
        StringTokenizer st = new StringTokenizer(s);
        while(st.hasMoreTokens()){
        	results.append(st.nextToken() + " ");
        }
        return results.toString();
      }
      return null;
    }



  void saveAllOpenAsXML()
  {
    JTree tree = mfo.getTree();
    TreeModel model = tree.getModel();
    DefaultMutableTreeNode treeRoot = (DefaultMutableTreeNode)model.getRoot();
    DefaultMutableTreeNode mibLeaf;
    MibModule mibModule;
    for (int i = 0; i < model.getChildCount(treeRoot); i++) {
      mibLeaf = (DefaultMutableTreeNode)model.getChild(treeRoot,i);
      status.setText("Saving " +
                    ((MibModule)mibLeaf.getUserObject()).getName() +
                    " as XML");
      saveAsXML((MibModule)(mibLeaf.getUserObject()));
    }
  }

  void saveAsXML (MibModule mibModule)
  {
    Enumeration trapEnum = mibModule.getDefinedTraps();
    Enumeration notificationEnum = mibModule.getDefinedNotifications();

    if (trapEnum.hasMoreElements() || notificationEnum.hasMoreElements())
    {
      XmlDocument	doc = new XmlDocument ();
      doc.setDoctype (
    	    null,	// no public identifier
    	    "TrapTargetReport.dtd",
    	    null	// no internal subset
    	    );
     	ElementNode	root = (ElementNode) doc.createElement ("MIB");
     	doc.appendChild (root);
      Element name = doc.createElement("NAME");
      root.appendChild(name);
      name.appendChild(doc.createTextNode(mibModule.getName()));

      if (trapEnum.hasMoreElements())
      {
        if (trapEnum.hasMoreElements()) {
      	  Element traps = (Element) doc.createElement ("TRAPS");
          root.appendChild (traps);

          MibTrap trap;
          for( ; trapEnum.hasMoreElements(); ) {
             trap = (MibTrap)trapEnum.nextElement();
             writeTrap(doc, traps, trap);
          }
        }
      }

        if ( notificationEnum.hasMoreElements()) {
       	  Element notifications = (Element) doc.createElement ("NOTIFICATIONS");
          root.appendChild (notifications);

          MibNode notification;
          for( ; notificationEnum.hasMoreElements(); ) {
             notification = (MibNode)notificationEnum.nextElement();
             writeNotification(doc, notifications, notification);
          }
        }

      String _XMLFilePath = "D:\\gensym\\Pinpoint\\Event Handling\\MibXMLFiles";
      File f = new File(_XMLFilePath, mibModule.getName() + ".xml");
      try {
      	Writer out = new FileWriter (f);
      	doc.write (out);
      	out.flush ();
        out.close();
        } catch (IOException ioe) {
          status.setText (ioe.toString());
        }

      try {
        StringBuffer buffer = new StringBuffer();
        String line;
        String evilText = " encoding=\"Cp1252\"";
        BufferedReader reader = new BufferedReader(new FileReader(f));
        while ( (line = reader.readLine()) != null)
            buffer.append(line);
        reader.close();

        buffer.delete(buffer.toString().indexOf (evilText),
                      buffer.toString().indexOf (evilText) + evilText.length());

        Writer writer = new FileWriter(f);
        writer.write(buffer.toString());
        writer.flush();
        writer.close();
      } catch (IOException ioe) {
          status.setText (ioe.toString());
        }
      }
  }

  void writeTrap(XmlDocument doc, Element traps, MibTrap trap)
  {
    Element trapElement = (Element) doc.createElement("TRAP");
    traps.appendChild(trapElement);

    Element attribute = doc.createElement("NAME");
    trapElement.appendChild(attribute);
    attribute.appendChild(doc.createTextNode(trap.getName()));

    attribute = doc.createElement("ENTERPRISE_OID");
    trapElement.appendChild(attribute);
    //attribute.appendChild(doc.createTextNode("" + trap.getEnterpriseString()));
    attribute.appendChild(doc.createTextNode("" + trap.getEnterprise()));

    attribute = doc.createElement("GENERIC_TRAP_TYPE");
    trapElement.appendChild(attribute);
    attribute.appendChild(doc.createTextNode("6"));

    attribute = doc.createElement("SPECIFIC_TRAP_TYPE");
    trapElement.appendChild(attribute);
    attribute.appendChild(doc.createTextNode("" + trap.getValue()));

    attribute = doc.createElement("DESCRIPTION");
    trapElement.appendChild(attribute);
    attribute.appendChild(
        doc.createTextNode(
            unformatString(trap.getDescription())));

    Vector variables = trap.getVariables();
    if( variables != null) {
      for (Enumeration e = variables.elements(); e.hasMoreElements();)
      {
        String varName = (String)e.nextElement();
        Vector vars = mibOperations.getNodesFromString(varName);
        MibNode var = (MibNode)vars.elementAt(0);
        Element varbind = doc.createElement("VARBIND");
        trapElement.appendChild(varbind);

        attribute = doc.createElement("NAME");
        varbind.appendChild(attribute);
        attribute.appendChild(doc.createTextNode(var.getLabel()));

        attribute = doc.createElement("ENTERPRISE_OID");
        varbind.appendChild(attribute);
        attribute.appendChild(doc.createTextNode("" + var.getNumberedOIDString()));

        attribute = doc.createElement("DESCRIPTION");
        varbind.appendChild(attribute);
        attribute.appendChild(
          doc.createTextNode(
            unformatString(var.getDescription())));

        attribute = doc.createElement("PART_OF_TARGET");
        varbind.appendChild(attribute);
        attribute.appendChild(doc.createTextNode("FALSE"));
      }
    }
  }

  void writeNotification(XmlDocument doc,
                          Element notifications,
                          MibNode notification)
  {
    Element notificationElement = (Element) doc.createElement("NOTIFICATION");
    notifications.appendChild(notificationElement);

    Element attribute = doc.createElement("NAME");
    notificationElement.appendChild(attribute);
    attribute.appendChild(doc.createTextNode(notification.getLabel()));

    attribute = doc.createElement("ENTERPRISE_OID");
    notificationElement.appendChild(attribute);
    //attribute.appendChild(doc.createTextNode("" + notification.getEnterpriseString()));
    attribute.appendChild(doc.createTextNode("" + notification.getNumberedOIDString()));

    attribute = doc.createElement("DESCRIPTION");
    notificationElement.appendChild(attribute);
    attribute.appendChild(
        doc.createTextNode(
            unformatString(notification.getDescription())));

    String objectNames = notification.getObjectNames();
    Vector objects = mibOperations.getNodesFromString(objectNames);
    if( objects != null) {
      for (Enumeration e = objects.elements(); e.hasMoreElements();)
      {
        //String varName = (String)e.nextElement();
        //Vector vars = mibOperations.getNodesFromString(varName);
        //MibNode var = (MibNode)vars.elementAt(0);
        MibNode var = (MibNode)e.nextElement();
        Element varbind = doc.createElement("VARBIND");
        notificationElement.appendChild(varbind);

        attribute = doc.createElement("NAME");
        varbind.appendChild(attribute);
        attribute.appendChild(doc.createTextNode(var.getLabel()));

        attribute = doc.createElement("ENTERPRISE_OID");
        varbind.appendChild(attribute);
        attribute.appendChild(doc.createTextNode("" + var.getNumberedOIDString()));

        attribute = doc.createElement("DESCRIPTION");
        varbind.appendChild(attribute);
        attribute.appendChild(
          doc.createTextNode(
            unformatString(var.getDescription())));

        attribute = doc.createElement("PART_OF_TARGET");
        varbind.appendChild(attribute);
        attribute.appendChild(doc.createTextNode("FALSE"));
      }
    }
  }


}
