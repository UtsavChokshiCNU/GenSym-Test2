package com.gensym.shell.util;

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
import java.awt.Cursor;
import java.io.IOException;
import java.util.Vector;

public class WebBrowserDocument extends MDIDocument implements HyperlinkListener {
  private JEditorPane pane;
  private Vector history = new Vector();
  private int currentIndex = -1;
  
  public WebBrowserDocument() {
    super(((MDIFrame)MDIApplication.getCurrentFrame()).getDefaultMenuBar(), 
	  ((MDIFrame)MDIApplication.getCurrentFrame()).getDefaultWindowMenu(),
	  ((MDIFrame)MDIApplication.getCurrentFrame()).getDefaultToolBarPanel());

    pane = new javax.swing.JTextPane();//JEditorPane();
    pane.setEditable(false);    
    pane.addHyperlinkListener(this);
    getContentPane().add(new JScrollPane(pane));
    //JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
    //JScrollPane.HORIZONTAL_SCROLLBAR_NEVER));
  }

  public JEditorPane getEditorPane() {
    return pane;
  }

  public String goBack() throws IOException{
    int prevIndex = currentIndex;
    currentIndex = Math.max(0,currentIndex-1);
    if (prevIndex == currentIndex) return null;
    Object historyElement = history.elementAt(currentIndex);
    if (historyElement instanceof String)
      setPage((String)historyElement, false);
    return ((String)historyElement);
  }

  public String goForward() throws IOException{
    int prevIndex = currentIndex;
    currentIndex = Math.min(currentIndex+1, history.size()-1);	
    if (prevIndex == currentIndex) return null;
    Object historyElement = history.elementAt(currentIndex);
    if (historyElement instanceof String)
      setPage((String)historyElement, false);
    return ((String)historyElement);
  }

  private void addToHistory(Object historyElement) {
    history.insertElementAt(historyElement,++currentIndex);
  }
  
  public void setPage(String url) throws IOException{
    setPage(url, true);
  }

  public void setPage(String url, boolean addToHistory) throws IOException {
    setTitle(url);
    if (addToHistory)
      addToHistory(url);
    pane.setPage(url);
  }

  @Override
  public void setTitle(String title) {
    super.setTitle(title);
    repaint();
  }
  
  @Override
  public void hyperlinkUpdate(HyperlinkEvent hle) {
    HyperlinkEvent.EventType type = hle.getEventType();
    java.net.URL url = hle.getURL();
    String urlString= url.toString();
    if (urlString.startsWith("g2://")) return;
    if (urlString.startsWith("mailto")) return;
    if (HyperlinkEvent.EventType.ENTERED == type) {
      //pane.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
    } else if (HyperlinkEvent.EventType.EXITED == type) {
      //pane.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
    } else if (HyperlinkEvent.EventType.ACTIVATED == type) {
      if (hle instanceof HTMLFrameHyperlinkEvent) {
	HTMLFrameHyperlinkEvent  evt = (HTMLFrameHyperlinkEvent)hle;
	HTMLDocument doc = (HTMLDocument)pane.getDocument();
	addToHistory(urlString);//addToHistory(evt);
	doc.processHTMLFrameHyperlinkEvent(evt);
      } else {
	try {
	  setTitle(urlString);
	  addToHistory(urlString);
	  pane.setPage(url);
	} catch (java.io.IOException ioe) {
	  Trace.exception(ioe);
	}
      }	
    }
  }
  
}
