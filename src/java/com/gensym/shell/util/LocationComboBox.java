/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 LocationComboBox.java
 *
 */
package com.gensym.shell.util;

import java.awt.Font;
import java.awt.Dimension;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JComboBox;
import javax.swing.ComboBoxEditor;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.dlg.ErrorDialog;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwGateway;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.ConnectionTimedOutException;
import com.gensym.jgi.G2AccessInitiationException;
import java.util.Enumeration;
import com.gensym.message.Resource;
import com.gensym.ntw.TooManyLoginAttemptsException;
import com.gensym.dlg.WarningDialog;
import com.gensym.ntw.LoginFailedException;
import com.gensym.ntw.OkException;
import com.gensym.ntw.TwConnectionInfo;
import java.util.StringTokenizer;
import com.gensym.message.Trace;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIApplication;
import com.gensym.mdi.MDIEvent;
import com.gensym.mdi.MDIManager;
import com.gensym.mdi.MDIDocument;
import com.gensym.mdi.MDIToolBarPanel;
import com.gensym.mdi.MDIListener;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeEvent;
import com.gensym.wksp.WorkspaceElement;
import com.gensym.wksp.WorkspaceView;
import com.gensym.classes.ImplAccess;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Block;
import javax.swing.ComboBoxModel;
import com.gensym.ntw.LoginRequest;
import com.gensym.shell.dialogs.LoginDialog;
import javax.swing.JEditorPane;
import javax.swing.JScrollPane;
import javax.swing.event.HyperlinkEvent;
import javax.swing.text.html.HTMLFrameHyperlinkEvent;
import javax.swing.text.html.HTMLDocument;
import javax.swing.event.HyperlinkListener;
import com.gensym.util.AttributeDenotation;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.uitools.utils.WaitAnimator;
import java.net.URL;

public class LocationComboBox extends JComboBox implements HyperlinkListener
{
  private ConnectionManager cxnManager;
  private ContextChangedAdapter contextChangedListener;
  private LocateThread locateThread;
  MDIFrame frame;
  private DocumentAdapter documentAdapter = new DocumentAdapter();
  WaitAnimator waitAnimator;
  LoginRequest loginRequest = new LoginRequest();

  /**
   * Creates a combo box which uses its current text a url for going to 
   * an item at a particular connection, or just to open a connection to 
   * that particular g2 server.
   */  
  public LocationComboBox(ConnectionManager cxnManager,
			  MDIFrame frame,
			  WebBrowserCreator webBrowserCreator,
			  WaitAnimator waitAnimator) {
    this.waitAnimator = waitAnimator;
    this.webBrowserCreator = webBrowserCreator;
    this.frame = frame;
    this.cxnManager = cxnManager;
    contextChangedListener = new ContextChangedAdapter();
    cxnManager.addContextChangedListener(contextChangedListener);    
    setFont(new Font("Arial", Font.PLAIN, 12));
    setEditable(true);
    addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent e) {
        LocationComboBox lcb = (LocationComboBox)e.getSource();
	String url = ((String)lcb.getSelectedItem());
	if (url == null) return;
	url = url.trim();
	if (url.equals("")) return;
	Object[] location = parseURL(url);	
	if (location == null) return;//ERROR!!!

	String origurl = url;
	String protocal = (String) location[0];
	if (G2_PROTOCAL.equals(protocal)) {
	  String host = (String) location[1];
	  String port = (String) location[2];
	  String subprotocal = (String)location[3];    	
	  String itemDenotation = (String)location[4];
	  AttributeDenotation valueDenotation = (AttributeDenotation)location[5];    
	  lcb.removeItem(url);    
	  url = G2_PROTOCAL+"://"+host+":"+port+"/";
	  if (itemDenotation != null) {
	    url+=subprotocal+"/"+itemDenotation;
	  }
	  if (valueDenotation != null) {
	    url+=pprintValueDenotation(valueDenotation);
	  }
	  setURL(url);
	  if (locateThread == null || !locateThread.isAlive()) {
	    locateThread = new LocateThread();
	    locateThread.setLocationComboBox(lcb);
	    locateThread.start();
	  }
	  locateThread.setInfo(lcb.cxnManager,host, port, lcb.loginRequest,
			       subprotocal, itemDenotation, valueDenotation);
	  localChange = true;
	  synchronized(locateThread) {
	    locateThread.search();
	  }
	} else if (MAIL_PROTOCAL.equals(protocal)) {
	  String address = (String) location[1];
	  handleEmailRequest(address);
	} else if (HTTP_PROTOCAL.equals(protocal) ||
		   FILE_PROTOCAL.equals(protocal)) {
	  setURL(url);
	  if (webBrowser == null) 
	    createWebBrowser();
	  lcb.waitAnimator.setBusy();
	  try {
	    webBrowser.setSelected(true);
	    if (webBrowser.isIcon())
	      webBrowser.setIcon(false);
	    webBrowser.setPage(url);
	  } catch (java.io.IOException ioe) {
	    System.out.println(ioe);//put up dialog
	  } catch (java.beans.PropertyVetoException pve) {
	    Trace.exception(pve);
	  }
	  lcb.waitAnimator.setIdle();
	}
      }
    });
    addMDIListeners(frame);
  }

  private static void handleEmailRequest(String address) {
    new WarningDialog(null, "Mail protocal not yet implemented", true, 
		      "Unable to email to " + address + "  \nThe mail protocal is not yet implemented.  \nPlease use your a seperate email program.",
		      null).setVisible(true);
  }
  
  public void setLoginRequest(LoginRequest loginRequest) {
    this.loginRequest = loginRequest;
  }
  
  WebBrowserDocument webBrowser;
  private WebBrowserCreator webBrowserCreator;
  void createWebBrowser() {
    webBrowser = webBrowserCreator.createWebBrowser();
    webBrowser.getEditorPane().addHyperlinkListener(this);    
    frame.getManager().addDocument(webBrowser);
  }    
  
  private static String pprintValueDenotation(AttributeDenotation valueDenotation) {
    String val="";    
    try {
      Enumeration e = valueDenotation.elements();
      while (e.hasMoreElements()) {
	Structure attr = (Structure)e.nextElement();
	val+="@"+attr.getAttributeValue(AttributeDenotation.NAME_).toString().toLowerCase();
      }
    } catch (NoSuchAttributeException nsae) {
      val = "MALFORMED G2 ATTRIBUTE URL";
      Trace.exception(nsae);      
    }
    return val;    
  }
    
  @Override
  public void hyperlinkUpdate(HyperlinkEvent hle) {
    HyperlinkEvent.EventType type = hle.getEventType();
    if (hle == null) return;
    URL theURL = hle.getURL();
    if (theURL == null) return;
    String url = theURL.toString();
    if (HyperlinkEvent.EventType.ACTIVATED == type) {
      if (url.startsWith(G2_PROTOCAL) || (url.startsWith(MAIL_PROTOCAL))) {
	removeItem(url);
	insertItemAt(url,0);
	setSelectedItem(url);
      } else 
	setURL(url);
    } 
  }
  
  private boolean localChange;
  private static String makeURL(TwAccess cxn) {
    if (cxn == null) return "";
    TwConnectionInfo info = (TwConnectionInfo)((com.gensym.jgi.G2Gateway)cxn).getG2ConnectionInfo();
    String url = "g2://"+info.getHost()+":"+info.getPort()+"/";
    return url;
  }

  class DocumentAdapter implements PropertyChangeListener, MDIListener{
    @Override
    public void documentAdded(MDIEvent event) {
      MDIDocument document = event.getDocument();
      document.addPropertyChangeListener(this);
      if (document instanceof WorkspaceDocument) {
	WorkspaceDocument wkspDoc = (WorkspaceDocument)document;
	setURLForDocument(wkspDoc);
      }
    }
    
    @Override
    public void propertyChange(PropertyChangeEvent e) {
      MDIDocument document = (MDIDocument)e.getSource();
      if (e.getPropertyName().equals(MDIDocument.IS_SELECTED_PROPERTY)){
	Boolean selected = (Boolean)e.getNewValue();
	if (selected.booleanValue())
	  setURLForDocument(document);
	else
	  setURLForDocument(null);
      } else if (e.getPropertyName().equals(MDIDocument.IS_CLOSED_PROPERTY)){
	document.removePropertyChangeListener(this);
	if (document == webBrowser) {
	  webBrowser.getEditorPane().removeHyperlinkListener(LocationComboBox.this);
	  webBrowser = null;
	}
	setURLForDocument(null);
      } else if (document.isClosed()) {
	if (document == webBrowser) {
	  webBrowser.getEditorPane().removeHyperlinkListener(LocationComboBox.this);
	  webBrowser = null;
	}
	setURLForDocument(null);
      }
    }
  }    
  private void addMDIListeners(MDIFrame frame) {
    if (frame != null) {
      MDIManager manager = frame.getManager();
      manager.addMDIListener(documentAdapter);
      
      MDIDocument[] docs = manager.getDocuments();
      for (int i=0; i<docs.length; i++){
	if (docs[i] instanceof WorkspaceDocument)
	  docs[i].addPropertyChangeListener(documentAdapter);
      }
    }
  }

  private void setURLForDocument(MDIDocument document) {
    if (document == null) {
      MDIDocument activeDocument = frame.getManager().getActiveDocument();
      if (activeDocument == null) 
	setURL(makeURL(cxnManager.getCurrentConnection()));
    } else if (document instanceof WorkspaceDocument) {
      WorkspaceView view = ((WorkspaceDocument)document).getWorkspaceView();
      KbWorkspace wksp = view.getWorkspace();	
      String url = makeURL((TwAccess)((ImplAccess)wksp).getContext());
      WorkspaceElement[] selection = view.getSelection();
      Item item = wksp;
      if (selection != null && selection.length > 0) {
	item = selection[0].getItem();
      }
      String itemDenotation=null;
      String subProtocal = null;
      try {
	if ((item instanceof Block) &&
	    !(item instanceof com.gensym.classes.ClassDefinition)) {
	  Object names = ((Block)item).getNames();
	  if (names == null)
	    names = ((Block)wksp).getNames();
	  if (names instanceof Symbol)
	    itemDenotation=names.toString().toLowerCase();
	  else if (names instanceof Sequence)
	    itemDenotation=((Sequence)names).elementAt(0).toString();
	  if (itemDenotation != null)
	    subProtocal = NAMED_ITEM_SUBPROTOCAL;
	}
	if (itemDenotation == null) {
	  Structure texts =(Structure)
	    ((com.gensym.classes.G2__BaseImpl)item).getAttributeTexts(UUID_DENOTATION);
	  itemDenotation=(String)texts.getAttributeValue(UUID_, null);
	  if (itemDenotation != null) {
	    itemDenotation = itemDenotation.substring(1,itemDenotation.length()-1);
	    subProtocal = UUID_SUBPROTOCAL;
	  }
	}
      } catch (G2AccessException g2ae) {
	Trace.exception(g2ae);
      }
      if (subProtocal != null && itemDenotation != null)
	url+=subProtocal+"/"+itemDenotation;
      setURL(url);
    } else if (document instanceof WebBrowserDocument) {
      Object page = ((WebBrowserDocument)document).getEditorPane().getPage();
      if (page != null)
	setURL(page.toString());
    }
  }
  
  private static final Symbol UUID_ = Symbol.intern ("UUID");
  static final String UUID_SUBPROTOCAL = "with-uuid";
  static final String NAMED_ITEM_SUBPROTOCAL = "named";  
  private static final Sequence UUID_DENOTATION = new Sequence();
  static {
    UUID_DENOTATION.addElement(UUID_);
  }
  
  
  void setURL(String url) {
    if (contains(url)) {
      //removeItem(url);
    } else 
      insertItemAt(url,0);
    ComboBoxEditor cbe = (ComboBoxEditor)getEditor();    
    cbe.setItem(url);	
  }
  
  boolean contains(Object obj) {
    ComboBoxModel model = getModel();
    try {
      for (int i=0;i<model.getSize();i++) {
	if (obj.equals(model.getElementAt(i)))
	  return true;
      }
    } catch (RuntimeException re) {
      //We'd actually rather catch array index/null pointer exceptions than
      //risk a thread deadlock caused by synchronizing around the model.
      //The worst thing that will happen is that a url will get entered into
      //the combobox more than once.
    }
    return false;
  }
  
  class ContextChangedAdapter implements ContextChangedListener{
    @Override
    public void currentConnectionChanged(ContextChangedEvent e){
      if (localChange) {
	localChange = false;
	return;
      }
      //if (!e.isConnectionNew()) return;
      TwAccess cxn = e.getConnection();
      setURL(makeURL(cxn));
    }
  }

  private static final String delims = "/:@";
  private static final String G2_PROTOCAL = "g2";
  private static final String FILE_PROTOCAL = "file";
  private static final String HTTP_PROTOCAL = "http";
  private static final String MAIL_PROTOCAL = "mailto";  
  private Object[] parseURL(String url) {
    StringTokenizer tokenizer = new StringTokenizer(url, delims);
    String firstToken = null;
    String protocal = null;
    while (firstToken == null && tokenizer.hasMoreTokens()) {
      firstToken = tokenizer.nextToken();
      if (firstToken.toLowerCase().equals(G2_PROTOCAL)) {
	protocal = G2_PROTOCAL;
	firstToken = null;
      } else if (firstToken.toLowerCase().equals(FILE_PROTOCAL)) {
	protocal = FILE_PROTOCAL;
	firstToken = null;
      } else if (firstToken.toLowerCase().equals(HTTP_PROTOCAL)) {
	protocal = HTTP_PROTOCAL;
	firstToken = null;
      } else if (firstToken.toLowerCase().equals(MAIL_PROTOCAL)) {
	protocal = MAIL_PROTOCAL;
	firstToken = null;
      }
    }
    if (FILE_PROTOCAL.equals(protocal)) {
      return new String[] {FILE_PROTOCAL, url};
    } else if (HTTP_PROTOCAL.equals(protocal)) {
      return new String[] {HTTP_PROTOCAL, url};
    } else if (MAIL_PROTOCAL.equals(protocal)) {
      String address = null;
      address=firstToken;
      if (tokenizer.hasMoreTokens())
	address=address+"@"+tokenizer.nextToken();
      else
	address = null;
      return new String[] {MAIL_PROTOCAL, address};
    } else if (G2_PROTOCAL.equals(protocal)) {
      String host = "localhost";
      String port = "1111";
      String subprotocal = null;
      String itemDenotation = null;
      AttributeDenotation valueDenotation = null;
      if (firstToken != null) {
	try {
	  Integer.parseInt(firstToken);
	  port = firstToken;
	} catch (NumberFormatException nfe) {
	  host = firstToken;
	  if (tokenizer.hasMoreTokens())
	    port = tokenizer.nextToken();
	}
	if (tokenizer.hasMoreTokens())
	  subprotocal = tokenizer.nextToken();      
	if (tokenizer.hasMoreTokens())
	  itemDenotation = tokenizer.nextToken();
	if (itemDenotation == null && subprotocal != null) {
	  //assume it's a named item and fill in the subprotocal
	  itemDenotation = subprotocal;
	  subprotocal = NAMED_ITEM_SUBPROTOCAL;
	}
	if (tokenizer.hasMoreTokens()) {
	  while(tokenizer.hasMoreTokens()) {
	    Symbol attributeName = Symbol.intern(((String)tokenizer.nextToken()).toUpperCase());
	    if (valueDenotation == null)
	      valueDenotation = new AttributeDenotation(attributeName);
	    else
	      valueDenotation.addElement((new AttributeDenotation(attributeName)).elementAt(0));
	  }
	}
      }
      return new Object[] {protocal, host,port,subprotocal,itemDenotation,valueDenotation};
    } else
      return null;
  }

  
  /**
   * @undocumented
   */
  @Override
  public void setEnabled(boolean enabled) {
    super.setEnabled(enabled);
    if (!enabled) {
      ComboBoxEditor cbe = (ComboBoxEditor)getEditor();      
      cbe.setItem("  ");
    } 
  }
}

class LocateThread extends Thread {
  static final int WKSP = 0;
  static final int ITEM = 1;
  static final Symbol ITEM_ = Symbol.intern("ITEM");
  static final Symbol GO_TO_ITEM_ = Symbol.intern("GO-TO-ITEM");    
  String host, port, itemDenotation, subProtocal, brokerURL;
  AttributeDenotation valueDenotation;
  LocationComboBox lcb;
  ConnectionManager cxnMgr;
  LoginRequest loginRequest;
  
  void setInfo(ConnectionManager cxnMgr,
	       String host, String port,
	       LoginRequest loginRequest,
	       String subProtocal,
	       String itemDenotation,
	       AttributeDenotation valueDenotation) {
    this.loginRequest = loginRequest;
    this.cxnMgr = cxnMgr;
    this.host = host;
    this.port = port;
    this.subProtocal = subProtocal;
    this.itemDenotation = itemDenotation;
    this.valueDenotation = valueDenotation;    
  }  

  void setLocationComboBox(LocationComboBox lcb) {
    this.lcb = lcb;
  }
  private static Item[] getWorkspaceAndItemOnWksp(Item item)
       throws G2AccessException
  {
    Sequence containment = item.getContainmentHierarchy();
    containment.insertElementAt(item, 0);
    Enumeration items = containment.elements();
    Item itemOnWksp = item;
    while (items.hasMoreElements()){
      Item itm = (Item)items.nextElement();
      if (itm instanceof KbWorkspace){
	Item[] itms = new Item[2];
	itms[WKSP] = itm;
	itms[ITEM] = itemOnWksp;
	return itms;
      }
      else itemOnWksp = itm;
    }
    return null;
  }
  
  private static void goTo(Item item, KbWorkspace wksp)
       throws G2AccessException
  {
    if (wksp != null){
      Structure particulars = new Structure();
      if (!(item instanceof com.gensym.classes.Connection)) {
	//show doesn't work well with connections(6/12/99)
	particulars.setAttributeValue(ITEM_, item);	
	particulars.setAttributeValue(GO_TO_ITEM_, new Boolean(true));
      }
      wksp.show(particulars);
    }   
  }

  public void search() {
    lcb.waitAnimator.setBusy();
    notify();
  }

  private String createWebPageForDenotation(Item item,
					    Sequence denotation,
					    Object value) {
    String itemName = "";
    try {
      itemName = item.getTableHeader();
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
    String title = "Value of item"; 
    return "<html><head><title>"+title+"</title></head><body text=\"#000000\" bgcolor=\"#CCCCCC\" link=\"#0000EE\" vlink=\"#551A8B\" alink=\"#FF0000\">&nbsp;<table BORDER WIDTH=\"100%\" ><tr><td><h2>Item:</h2></td><td>"+itemName+"</td></tr><tr><td><h2>Attribute Denotation:</h2></td><td>"+denotation+"</td></tr><tr><td><h2>Value:</h2></td><td>"+value+"</td></tr></table></body></html>";
    
  }
  
  @Override
  public void run() {
    while (true) {
      try {
	TwConnectionInfo cxnInfo = new TwConnectionInfo(brokerURL, host, port);

	//just using the checking mechanism thats private to LoginDialog(open up later)
	LoginDialog loginDialog = new LoginDialog(null,"Login", true, null);
	loginDialog.setConnectionInformation(cxnInfo);
	cxnInfo = loginDialog.getConnectionInformation();
	TwAccess connection = null;
	if (cxnInfo != null) {//--> bad host or port
	  connection = cxnMgr.openConnection(cxnInfo);
	  cxnMgr.setCurrentConnection(connection);//???
	}
	if (connection != null && !connection.isLoggedIn()) {
	  //LoginDialog loginDialog = new LoginDialog(null, "Login", true, null);
	  //loginDialog.setConnectionInformation(cxnInfo);
	  loginDialog.setEditableTabPages(loginDialog.CONNECTION_TAB_PAGE, false);
	  loginDialog.selectTabPage(loginDialog.SECURITY_TAB_PAGE);
	  loginDialog.setLoginRequest(loginRequest);
	  loginDialog.setVisible(true);
	  if (!loginDialog.wasCancelled()) 
	    connection.login(loginDialog.getLoginRequest());
	  else 
	    connection.closeConnection();
	}
	if (connection != null && connection.isLoggedIn()) {
	  if (subProtocal != null) {
	    Item item = null;
	    if (subProtocal.equals(LocationComboBox.UUID_SUBPROTOCAL)) {
	      item = connection.getItemWithUUID(itemDenotation);
	    } else if (subProtocal.equals(LocationComboBox.NAMED_ITEM_SUBPROTOCAL)) 
	      item = connection.getUniqueNamedItem(ITEM_, Symbol.intern(itemDenotation.toUpperCase()));
	    if (item != null) {
	      if (valueDenotation != null) {
		Object value = connection.getValue(item, valueDenotation);
		if (value instanceof Item) {
		  item = (Item)value;
		} else {
		  String webPage = createWebPageForDenotation(item, valueDenotation, value);
		  JEditorPane editorPane = null;
		  if (lcb.webBrowser == null)
		    lcb.createWebBrowser();
		  editorPane = lcb.webBrowser.getEditorPane();
		  editorPane.setContentType("text/html; charset=EUC-JP");
		  editorPane.setText(webPage);
		  lcb.webBrowser.setTitle(lcb.getSelectedItem().toString());
		  item = null;
		}
	      }
	      if (item != null) {
		Item [] items = getWorkspaceAndItemOnWksp(item);
		if (items != null) {
		  goTo(items[ITEM], (KbWorkspace)items[WKSP]);
		} else
		  new ErrorDialog(null,"Can not go to item", false,
				  itemDenotation+" exists, but is not on a workspace.",
				  null).setVisible(true);
	      }
	    }
	  }
	}
      } catch (G2AccessException g2ae) {
	String hostPortInfo = "  ("+host+" : "+port+")";          
	handleLoginFailureException(g2ae, hostPortInfo);
      }
      host = null; port = null; subProtocal = null; itemDenotation = null;
      try {
	lcb.waitAnimator.setIdle();
	synchronized(this) {
	  wait();
	}
      } catch (InterruptedException ie) {
	Trace.exception(ie);
      }      
    }
  }

  private static Resource i18n = Resource.getBundle("com/gensym/shell/commands/Errors");  
  final String cxnErrorTitle = i18n.getString("UnableToConnectDialogTitle");
  
  protected void handleLoginFailureException (G2AccessException gae, String hostPortInfo) {
    String loginError = gae.getMessage();
    if (gae instanceof G2AccessInitiationException) {
      new WarningDialog(null, cxnErrorTitle, true, 
			i18n.format("UnableToOpenConnectionWithReason", 
				    hostPortInfo, loginError), null).setVisible(true);

    } else if (gae instanceof ConnectionTimedOutException) {
      new WarningDialog(null, cxnErrorTitle, true, 
			i18n.format("UnableToOpenConnectionWithReason", 
				    hostPortInfo, loginError), null).setVisible(true);

    } else if ( (gae instanceof TooManyLoginAttemptsException)
		|| (gae instanceof OkException)
		|| ( (gae instanceof LoginFailedException)
		     && ( loginError.equals("NO-AVAILABLE-FLOATING-LICENSES") ) ) ) {
      new WarningDialog(null, cxnErrorTitle, true, 
			i18n.format("UnableToOpenConnectionWithReason", 
				    hostPortInfo, loginError), null).setVisible(true);
      //unloggedInConnection.closeConnection();
      //unloggedInConnection = null;

    } else if (gae instanceof LoginFailedException) {
      /*
       * Error is one of the following:
       *   USER-NAME-REQUIRED
       *   PASSWORD-REQUIRED
       *   UNKNOWN-USER-OR-BAD-PASSWORD
       *   UNAUTHORIZED-MODE
       * Display informational message and let the user try again
       */
      new WarningDialog(null, cxnErrorTitle, true, 
			i18n.format("UnableToOpenConnectionWithReason", 
				    hostPortInfo, loginError), null).setVisible(true);
      //loginDialog.setLoginRequest(previousLoginRequest);
      //loginDialog.selectTabPage(loginDialog.SECURITY_TAB_PAGE);
    } else {
      new WarningDialog(null, "Item does not exist", true, 
			gae.getMessage(), null).setVisible(true);
    }
  }
}











