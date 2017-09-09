
package com.gensym.nols.help;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.*;
import java.util.*;

import com.sun.java.swing.*;
import com.sun.java.swing.text.*;
import com.sun.java.swing.border.*;
import com.sun.java.swing.event.*;
import com.sun.java.swing.tree.*;

import com.gensym.nols.main.*;


public class NolAssistantFrame extends JFrame {
	private NolAssistantTree tree;

	public NolAssistantFrame(NolMainFrame frame){
		super();
		setTitle("NeurOn-Line Methodology Assistant");
		tree = new NolAssistantTree(frame);
		getContentPane().setLayout(new BorderLayout());    
		getContentPane().add("Center", tree);
	}
}


 /**
 * NolAssistantTree
 * @version     1.1 August 30, 1998
 * @author      Brian O. Bush
 **/

class NolAssistantTree extends JSplitPane {
    private JEditorPane htmlPane;
	private NolMainFrame mainFrame;
	private ControlAction actionListener;
	private PageLoader pageLoader;
	protected String nolPath;
    private URL defaultURL;
	private URL currentURL;
	private int actionFlag; // 0: button 1: contents; 2: tree
	private JTree tree;
	private DefaultMutableTreeNode root;
	private DefaultMutableTreeNode currentNode;
    protected static ResourceBundle resources = null;
	private Stack history;
	private Stack future;
	
    private static boolean DEBUG = false;

    static {
        try {
            resources = ResourceBundle.getBundle("NolAssistantTree", 
                                                 Locale.getDefault());
        } catch (MissingResourceException mre) {
            System.err.println("NolAssistantTree.properties not found");
            System.exit(1);
        }
    }

    public NolAssistantTree() {
        super(HORIZONTAL_SPLIT);
		mainFrame = null;		

		actionFlag = -1;
		actionListener =  new ControlAction();	
		pageLoader = new PageLoader(null);
		nolPath = "file:/NeurOnLine/com/gensym/nols/docs/";

		// initialize history and future (URL) stack
		history = new Stack();
		future = new Stack();

		//Create the nodes.
        root = new DefaultMutableTreeNode(new BookInfo
			(resources.getString("TreeTitle"),  "default.html"));
		currentNode = root;
		createTree(root);  // recursively create tree...

        //Create a tree that allows one selection at a time.
        tree = new JTree(root);
        tree.getSelectionModel().setSelectionMode
                (TreeSelectionModel.SINGLE_TREE_SELECTION);

        // Set the icon for leaf nodes.
		NolAssistantCellRenderer renderer = new NolAssistantCellRenderer();
        tree.setCellRenderer(renderer);
	
		// set the spacing between rows
		tree.setRowHeight(20);  // -- looks good to me?

		// select the top 
		tree.setSelectionPath(new TreePath(root));
		
		// Listen for when the selection changes.
        tree.addTreeSelectionListener(new TreeSelectionListener() {
            public void valueChanged(TreeSelectionEvent e) {
                DefaultMutableTreeNode node = (DefaultMutableTreeNode)
                                   (e.getPath().getLastPathComponent());
				currentNode = node;
                Object nodeInfo = node.getUserObject();
                BookInfo book = (BookInfo)nodeInfo;
                displayURL(book.bookURL);
				//pushHistoricURL(book.bookURL);
                if (DEBUG) {
                    System.out.print(book.bookURL + ":\n");
                    //System.out.println(nodeInfo.toString());
                }
            }
        });

        // Create the scroll pane and add the tree to it. 
        JScrollPane treeView = new JScrollPane(tree);

        // Create the HTML viewing pane.
        htmlPane = new JEditorPane();
		htmlPane.addHyperlinkListener(actionListener);
        htmlPane.setEditable(false);

		// initialize the default viewing page for the htmlPane
		initDefaultPage();

        JScrollPane htmlView = new JScrollPane(htmlPane);
		JPanel content = new JPanel();
		content.setLayout(new BorderLayout());  
		content.add("Center", htmlView);
		content.add("East", getControlPanel());


        //Add the scroll panes to this panel.
        add(treeView);
        add(content);

        Dimension minimumSize = new Dimension(100, 100);
        htmlView.setMinimumSize(minimumSize);
        treeView.setMinimumSize(minimumSize);
        //setDividerLocation(100); //XXX: ignored! bug 4101306
        //workaround for bug 4101306:
        treeView.setPreferredSize(new Dimension(280, 400));  // first changes the width, second changes the height

        setPreferredSize(new Dimension(900, 500));
    }

    public NolAssistantTree(NolMainFrame frame) {
		this();
		mainFrame = frame;	
	}

   /**
     * Create a leaf.
	 *
     */
    protected DefaultMutableTreeNode createLeaf(String key) {
		//if(DEBUG) System.out.println("LOADING TREE: processing key = " + key);
		String[] itemKeys = tokenize(getResourceString(key));

		DefaultMutableTreeNode leaf = new DefaultMutableTreeNode(new BookInfo (
			getResourceString(key + "LABEL"), 
			getResourceString(key + "URL")));

		if(itemKeys == null) return leaf;

		for (int i = 0; i < itemKeys.length; i++) {
			DefaultMutableTreeNode newLeaf = createLeaf(itemKeys[i]);
			leaf.add(newLeaf);
		}
		return leaf;
    }


    /**
     * Create the tree for the app.  By default this pulls the
     * definition of the tree from the associated resource file. 
     */
    private void createTree(DefaultMutableTreeNode top) {

		String[] rootKeys = tokenize(getResourceString("root"));
		for (int i = 0; i < rootKeys.length; i++) {
			DefaultMutableTreeNode k = createLeaf(rootKeys[i]);
			if (k != null) {
				top.add(k);
			}
		}
    }

	
    private String getResourceString(String nm) {
		String str;
		try {
			str = resources.getString(nm);
		} catch (MissingResourceException mre) {
			str = null;
		}
		return str;
    }


   /**
     * Take the given string and chop it up into a series
     * of strings on whitespace boundries.  This is useful
     * for trying to get an array of strings out of the
     * resource file.
     */
    protected String[] tokenize(String input) {
		Vector v = new Vector();
		if(input == null) {
			return null;
		}
		StringTokenizer t = new StringTokenizer(input);
		String cmd[];

		while (t.hasMoreTokens())
			v.addElement(t.nextToken());
		cmd = new String[v.size()];
		for (int i = 0; i < cmd.length; i++)
			cmd[i] = (String) v.elementAt(i);

		return cmd;
    }

 
	private boolean searchTreeAndSelect(URL u) {

		DefaultMutableTreeNode targetNode = null;
		Enumeration enum = root.preorderEnumeration();
		boolean found = false;
		while(enum.hasMoreElements()) {
			targetNode = (DefaultMutableTreeNode) enum.nextElement();
            Object nodeInfo = targetNode.getUserObject();
            BookInfo book = (BookInfo)nodeInfo;
            if(((book.bookURL).toString()).compareTo(u.toString()) == 0) {
				found = true;
				break;
			}
		}
		enum = null;

		if (!found) return false;
		else {
			tree.setSelectionPath(new TreePath(targetNode.getPath()));
			currentNode = targetNode;
			return true;
		}
	}
	
	
	/**
	 * BookInfo
	 * @version     1.0 August 20, 1998
	 * @author      Brian O. Bush
	 **/
    private class BookInfo {
        public String bookName;
        public URL bookURL;
        public String prefix = nolPath; 

        public BookInfo(String book, String filename) {
            bookName = book;
            try {
                bookURL = new URL(prefix + filename);
            } catch (java.net.MalformedURLException exc) {
                System.err.println("Attempted to create a BookInfo "
                                   + "with a bad URL: " + bookURL);
                bookURL = null;
            }
        }
        @Override
		public String toString() {
            return bookName;
        }
    }

    private void initDefaultPage() {
        String s = null;
        try {
            s = nolPath + "default.html";
            //if (DEBUG) {
            //    System.out.println("defaut page URL is " + s);
            //}
            defaultURL = new URL(s);
			currentURL = defaultURL;
            displayURL(defaultURL);
			pushHistoricURL(defaultURL);
        } catch (Exception e) {
            System.err.println("Couldn't access default URL: " + s);
        }
    }

    private void displayURL(URL url) {
        try {
            htmlPane.setPage(url);
			currentURL = url;
			pushHistoricURL(currentURL);
			//if (DEBUG) System.out.println("\t--> NOW Displaying page: " + currentURL);
        } catch (IOException e) {
            System.err.println("Attempted to read a bad URL: " + url);
        }
    }

	// STACK FOR HISTORY
	private void pushHistoricURL(URL url) {
		URL oldURL;
		if(history.empty())
			oldURL = defaultURL;
		else	
			oldURL = (URL)history.peek();
		//if (DEBUG) System.out.println("Peeking at previous URL = " + oldURL);
		if(!oldURL.equals(url)) {
			history.push(url);
			if (DEBUG) System.out.println("\t--Pushing URL = " + url + " onto History stack");
		}
	}

	private URL popHistoricURL() {
		if(history.empty())
			return defaultURL;
		else {
		URL tempURL = (URL) history.pop();;
		if((currentURL.toString()).compareTo(tempURL.toString()) == 0) { 
			if(!history.empty())
				tempURL = (URL) history.pop(); 
		}
		//	while(currentURL.equals(tempURL)) 
		//		tempURL = (URL) history.pop();
		if (DEBUG) System.out.println("\t--Popping URL = " + tempURL + " from History stack");
		return tempURL;
		}
	}

	// STACK FOR FUTURE
	private void pushFuturisticURL(URL url) {
		URL oldURL;
		if(future.empty())
			oldURL = defaultURL;
		else	
			oldURL = (URL)future.peek();
		//if (DEBUG) System.out.println("Peeking at previous future URL = " + oldURL);
		if(!oldURL.equals(url)) {
			future.push(url);
				if (DEBUG) System.out.println("\t--Pushing URL = " + url + " onto Future stack");
		}
	}

	private URL popFuturisticURL() {
		if(future.empty())
			return defaultURL;
		else {
			URL tempURL = (URL) future.pop();;
			if((currentURL.toString()).compareTo(tempURL.toString()) == 0) { 
				if(!future.empty()) 
					tempURL = (URL) future.pop(); 
			}
			if (DEBUG) System.out.println("\t--Popping URL = " + tempURL + " from Future stack");
			return tempURL;
		}
	}

	private JPanel getControlPanel(){
 		JPanel control = new JPanel();
		control.setBackground(getContentPane().getBackground());
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
		control.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
				"", TitledBorder.LEFT , TitledBorder.TOP));




		URL url = this.getClass().getResource("../images/next.gif");
		ImageIcon nextIcon = new ImageIcon(url);
		url = this.getClass().getResource("../images/back.gif");
		ImageIcon backIcon = new ImageIcon(url);
		JPanel controlsPane = new JPanel(new GridLayout(2,1,5,5));

		JPanel historyControl = new JPanel();
		historyControl.setBorder(BorderFactory.createTitledBorder("History:"));		
		JButton backHistoryButton = new JButton(backIcon);
		backHistoryButton.addActionListener(actionListener);
		backHistoryButton.setActionCommand("History Back");
		backHistoryButton.setToolTipText("Back");
		historyControl.add(backHistoryButton);
	
		JButton forwardHistoryButton = new JButton(nextIcon);
		forwardHistoryButton.addActionListener(actionListener);
		forwardHistoryButton.setActionCommand("History Forward");
		forwardHistoryButton.setToolTipText("Forward");
		historyControl.add(forwardHistoryButton);
		controlsPane.add(historyControl);

		JPanel topicControl = new JPanel(new GridLayout(2,1,5,5));
		topicControl.setBorder(BorderFactory.createTitledBorder("Topic:"));
		JButton previousButton = new JButton("Previous");
		previousButton.addActionListener(actionListener);
		previousButton.setToolTipText("Previous Topic");

		JButton nextButton = new JButton("Next");
		nextButton.addActionListener(actionListener);
		nextButton.setToolTipText("Next Topic");

		topicControl.add(previousButton);
		topicControl.add(nextButton);
		controlsPane.add(topicControl);

		control.add(Box.createRigidArea(NolMainFrame.vpad20));
		control.add(controlsPane);
		control.add(Box.createRigidArea(NolMainFrame.vpad500));
		control.add(Box.createVerticalGlue());
		return control;
	}

	private void linkActivated(URL u) {
		pageLoader.setParameters(u);
		searchTreeAndSelect(u);
		SwingUtilities.invokeLater(pageLoader);
    }


    private class ControlAction extends AbstractAction implements HyperlinkListener, ChangeListener {

		ControlAction() {
			super("controlAction");
		}

        public void actionPerformed(ActionEvent e) {
			actionFlag = 0;
			String command = e.getActionCommand();
			if(command.equals("Previous")) {
				// walk tree up
				DefaultMutableTreeNode node = currentNode.getPreviousNode();
				if(node != null) {
					currentNode = node;
					Object nodeInfo = node.getUserObject();
					BookInfo book = (BookInfo)nodeInfo;
					displayURL(book.bookURL);
					tree.setSelectionPath(new TreePath(node.getPath()));
				}
			} else if(command.equals("Next")) {
				// walk tree down
				DefaultMutableTreeNode node = currentNode.getNextNode();
				if(node != null){
					currentNode = node;
					Object nodeInfo = node.getUserObject();
					BookInfo book = (BookInfo)nodeInfo;
					displayURL(book.bookURL);
					tree.setSelectionPath(new TreePath(node.getPath()));
				}
			} else if(command.equals("History Back")) {
				pushFuturisticURL(currentURL);
				URL tempURL = popHistoricURL();
				displayURL(tempURL);
				searchTreeAndSelect(tempURL);
			} else if(command.equals("History Forward")) {
				pushHistoricURL(currentURL);
				URL tempURL = popFuturisticURL();
				displayURL(popFuturisticURL());
				searchTreeAndSelect(tempURL);
			}
		}

		public void hyperlinkUpdate(HyperlinkEvent e) {
			actionFlag = 1;
			if (e.getEventType() == HyperlinkEvent.EventType.ACTIVATED) {
				if (DEBUG) System.out.println("Want to go to " + e.getURL());
				if(e.getSource() instanceof JEditorPane){ 
					URL url = e.getURL();
					String urlString = url.toString();
					if (DEBUG) System.out.println("linkActivated="+urlString);
					if(mainFrame != null) {
						if(urlString.indexOf("actionlink/importAction") != -1){
							mainFrame.importActionPerformed();
							actionFlag = -1;
							return;
						} else if(urlString.indexOf("actionlink/defineLabelAction") != -1){
							mainFrame.newlabelActionPerformed();
							actionFlag = -1;
							return;
						} else if(urlString.indexOf("actionlink/spreadsheetAction") != -1){
							mainFrame.spreadsheetActionPerformed();
							actionFlag = -1;
							return;
						} else if(urlString.indexOf("actionlink/chartAction") != -1){
							mainFrame.lineChartActionPerformed();
							actionFlag = -1;
							return;
						}else if(urlString.indexOf("actionlink/histogramActionPerformed") != -1){
							mainFrame.histogramActionPerformed();
							actionFlag = -1;
							return;
						}else if(urlString.indexOf("actionlink/projectmapActionPerformed") != -1){
							mainFrame.projectmapActionPerformed();
							actionFlag = -1;
							return;
						}else if(urlString.indexOf("actionlink/lineChartActionPerformed") != -1){
							mainFrame.lineChartActionPerformed();
							actionFlag = -1;
							return;
						}else if(urlString.indexOf("actionlink/newcaseAction") != -1){
							mainFrame.newpreprocessorActionPerformed();
							actionFlag = -1;
							return;
						}else if(urlString.indexOf("actionlink/showTransformerAction") != -1){
			//				mainFrame.showTransformerWKSP();
							actionFlag = -1;
							return;
						}else if(urlString.indexOf("actionlink/predictiveModelAction") != -1){
							mainFrame.newpredictmodelActionPerformed();
							actionFlag = -1;
							return;
						}else if(urlString.indexOf("actionlink/optimizationModelAction") != -1){
							mainFrame.newoptimizemodelActionPerformed();
							actionFlag = -1;
							return;
						}else if(urlString.indexOf("actionlink/replaceActionPerformed") != -1){
//							mainFrame.replaceActionPerformed();
							actionFlag = -1;
							return;
						}
					}
					linkActivated(e.getURL());
				}
			}
		}

		
		public void stateChanged(ChangeEvent e){
			if(actionFlag !=  -1) return;
		}

	}

    /**
     * temporary class that loads synchronously (although
     * later than the request so that a cursor change
     * can be done).
     */
    class PageLoader implements Runnable {
		private URL url;

		PageLoader(URL u) {
			url = u;
		}

		public void setParameters(URL u){
			url = u;
		}

        @Override
		public void run() {
			if (url == null) {
				htmlPane.repaint();
			} else {
				displayURL(url);
			}
		}
    }


	/**
      * NolAssistantCellRenderer
	  * @version     1.0 August 21, 1998
	  * @author      Brian O. Bush
	  **/

	class NolAssistantCellRenderer extends JLabel implements TreeCellRenderer {

		public NolAssistantCellRenderer() {
			 setHorizontalAlignment(JLabel.LEFT);
		}

		public Dimension getMinimumSize(){
			return 	new Dimension(150,20);
		}

		public Dimension getPreferredSize(){
			Dimension dim = super.getPreferredSize();
			return 	new Dimension(dim.width+20,dim.height);
		}

		public Component getTreeCellRendererComponent(JTree tree, Object  value, boolean sel, boolean expanded, boolean leaf, int row, boolean hasFocus) 
		{
 			String stringValue = tree.convertValueToText(value, sel, expanded, leaf, row, hasFocus);
			setText(stringValue);

			if(sel) {
				setBackground(java.awt.SystemColor.activeCaption);
				setForeground(java.awt.SystemColor.activeCaptionText);
				URL url = this.getClass().getResource("../images/arrow.gif");
				setIcon(new ImageIcon(url));
				//setIcon(new ImageIcon("images/Project.gif"));
				}
			else {  // set all other objects to that of the plain leaf icon
				setBackground(tree.getBackground());
				setForeground(UIManager.getColor("Tree.textNonSelectionColor"));
				setIcon(UIManager.getIcon("Tree.leafIcon"));
				}
			return this;
		 }

		public void paint(Graphics g) {
			
			Color bColor = getBackground();
			if(bColor != null) {
				Icon currentI = getIcon();
				g.setColor(bColor);
				if(currentI != null && getText() != null) {
					int offset = (currentI.getIconWidth() + getIconTextGap());
					g.fillRect(offset, 0, getWidth() - 1 - offset, getHeight() - 1);
				} else {
					g.fillRect(0, 0, getWidth()-1, getHeight()-1);
				}
			}
			super.paint(g);
		}

	 }


    public static void main(String[] args) {
        /*
         * Create a window.  Use JFrame since this window will include 
         * lightweight components.
         */
        JFrame frame = new JFrame("NeurOnLine II Methodology Assistant");

		try {
			UIManager.setLookAndFeel("com.sun.java.swing.plaf.windows.WindowsLookAndFeel");
        } catch (Throwable t) {
            System.out.println("uncaught exception: " + t);
            t.printStackTrace();
        }

        WindowListener l = new WindowAdapter() {
            @Override
			public void windowClosing(WindowEvent e) {System.exit(0);}
        };
        frame.addWindowListener(l);

        frame.getContentPane().add("Center", new NolAssistantTree());
        frame.pack();
        frame.show();
    }
}
