package com.gensym.demos.g2studiosample;

import java.awt.GridBagConstraints;
import javax.swing.event.HyperlinkEvent;
import javax.swing.event.HyperlinkListener;
import com.gensym.uitools.utils.StatusBar;
import com.gensym.message.Trace;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.jgi.G2CommunicationErrorEvent;
import com.gensym.ntw.TwConnectionListener;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwConnectionEvent;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.shell.util.ContextChangedListener;
import com.gensym.shell.util.ContextChangedEvent;

public class G2StudioStatusBar extends StatusBar
implements HyperlinkListener, TwConnectionListener
{
  public static final int MAIN_DISPLAY_AREA = 0, G2_STATE = 1, HOST_PORT = 2;
  private ContextChangedListener contextListener;  
  private TwAccess currentConnection;    
  
  public G2StudioStatusBar(ConnectionManager cxnMgr) {
    super(3);
    GridBagConstraints gbc = new GridBagConstraints();
    gbc.weightx = 2;
    gbc.fill = GridBagConstraints.HORIZONTAL;//NONE;    
    setConstraints(MAIN_DISPLAY_AREA,gbc);
    gbc.weightx = .2;
    setConstraints(G2_STATE,gbc);
    gbc.weightx = .3;    
    setConstraints(HOST_PORT,gbc);
    setStatus("no connection", HOST_PORT);
    cxnMgr.addContextChangedListener(contextListener = new ContextChangedAdapter());    
  }

  class ContextChangedAdapter implements ContextChangedListener {
    @Override
    public void currentConnectionChanged(ContextChangedEvent e) {
      TwAccess connection = e.getConnection();
      setConnection(connection);
    }
  }
  
  private void setConnection(TwAccess cxn) {
    if (currentConnection != null)
      currentConnection.removeTwConnectionListener(this);
    currentConnection = cxn;
    String hostPort = "no connection", g2State = "";
    if (cxn != null && cxn.isAlive()) {
      cxn.addTwConnectionListener(this);
      try {
	hostPort = cxn.g2GetHostName()+":"+cxn.g2GetPortNumberOrName();
	g2State = cxn.getG2State().toString().toLowerCase();
      } catch (G2AccessException g2ae) {
	Trace.exception(g2ae);
      }
    }
    setStatus(hostPort, HOST_PORT);
    setStatus(g2State, G2_STATE);
  }

  @Override
  public void hyperlinkUpdate(HyperlinkEvent hle) {
    HyperlinkEvent.EventType type = hle.getEventType();
    if (hle == null) return;
    String url = hle.getURL().toString();
    if (HyperlinkEvent.EventType.ENTERED == type)
      setStatus(url, MAIN_DISPLAY_AREA);
    else if (HyperlinkEvent.EventType.EXITED == type) 
      setStatus("", MAIN_DISPLAY_AREA);
    //xField.setText("");
    //yField.setText("");
  }
  

  @Override
  public void loggedOut(TwConnectionEvent e){
    if (currentConnection == e.getSource()) {
      setStatus("", HOST_PORT);
      setStatus("", G2_STATE);
    }
  }  
  @Override
  public void g2IsStarted(G2ConnectionEvent e){
    if (currentConnection == e.getSource())
      setStatus("started", G2_STATE);
  }
  @Override
  public void g2IsPaused(G2ConnectionEvent e){
    if (currentConnection == e.getSource())
      setStatus("paused", G2_STATE);
  }
  @Override
  public void g2IsResumed(G2ConnectionEvent e){
    if (currentConnection == e.getSource())
      setStatus("resumed", G2_STATE);
  }
  @Override
  public void g2IsReset(G2ConnectionEvent e) {
    if (currentConnection == e.getSource())
      setStatus("reset", G2_STATE);
  }
  @Override
  public void communicationError(G2CommunicationErrorEvent e){}  
  @Override
  public void g2MessageReceived(G2ConnectionEvent e){}
  @Override
  public void loggedIn(TwConnectionEvent e){}  
  @Override
  public void readBlockage(G2ConnectionEvent e){}  
  @Override
  public void writeBlockage(G2ConnectionEvent e){}
  @Override
  public void g2ConnectionInitialized(G2ConnectionEvent e) {}
  @Override
  public void g2ConnectionClosed(G2ConnectionEvent e) {}
  @Override
  public void userModeChanged(TwConnectionEvent e){}  
  
}

