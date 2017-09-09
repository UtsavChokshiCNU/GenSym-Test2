package com.gensym.demos.g2studiosample.util;

import javax.swing.JComboBox;
import java.awt.Dimension;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.ComboBoxEditor;
import com.gensym.util.Symbol;
import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.ItemListener;
import com.gensym.util.ItemEvent;
import com.gensym.classes.DebuggingParameters;
import com.gensym.shell.util.ContextChangedListener;
import com.gensym.shell.util.ContextChangedEvent;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.classes.Module;
import com.gensym.message.Trace;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import javax.swing.ListCellRenderer;
import javax.swing.DefaultListCellRenderer;
import javax.swing.JLabel;
import javax.swing.JList;
import java.awt.Component;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.util.NoSuchAttributeException;

public class TracingMessageLevelComboBox extends JComboBox {
  private static final Symbol
     ALL_ATTRIBUTES_ = Symbol.intern ("*"),
     NAME_ = Symbol.intern ("NAME");
  private static final Symbol[] neededAttributes = {SystemAttributeSymbols.TRACING_MESSAGE_LEVEL_};
  private TwAccess currentConnection;
  private ItemAdapter itemAdapter;
  private ContextChangedAdapter contextChangedListener;
  private ConnectionManager connectionManager;  
  private DebuggingParameters debuggingParameters;    
  private static final String
  LEVEL_ZERO = "0 (no trace messages)",
    LEVEL_ONE = "1 (trace messages on entry and exit)",
    LEVEL_TWO = "2 (trace messages at major steps)",
    LEVEL_THREE = "3 (trace messages at every step)";
  /**
   * Creates a combo box for setting the TracingMessage level of 
   * the current connection.
   */
  public TracingMessageLevelComboBox() {
    this((TwAccess)null);
  }

  /**
   * Creates a combo box for setting the TracingMessage level of 
   * the current connection.
   * @param connection the connection to set as the current connection.
   */
  public TracingMessageLevelComboBox(TwAccess connection) {
    super(new Object[] {new Integer(0), new Integer(1),new Integer(2),new Integer(3)});
    setRenderer(new MyCellRenderer());
    setConnection(connection);    
    setToolTipText("Tracing Message Level");
    setFont(com.gensym.uitools.utils.FontUtil.sanserifPlain11);
    setPreferredSize(new Dimension(180, 20));
    setEnabled(false);
    addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent e) {
        TracingMessageLevelComboBox tmlcb = (TracingMessageLevelComboBox)e.getSource();
	tmlcb.setTracingMessageLevel();
      } 
    });     
  }

  /**
   * Creates a combo box for setting the TracingMessage level of 
   * the current connection.
   * @param connectionManager a connectionManager from which to 
   * determine the current connection.
   */
  public TracingMessageLevelComboBox(ConnectionManager connectionManager) {
    this(connectionManager.getCurrentConnection());
    itemAdapter = new ItemAdapter();
    this.connectionManager = connectionManager;    
    contextChangedListener = new ContextChangedAdapter();
    connectionManager.addContextChangedListener(contextChangedListener);    
  }

  
  private void updateDisplay(ItemEvent e) {
    Sequence denotationSequence = e.getDenotation();
    Structure denotation = (Structure) denotationSequence.elementAt(0);
    Symbol attributeName
      = (denotation!=null?(Symbol)denotation.getAttributeValue(NAME_, null):null);
    if (SystemAttributeSymbols.TRACING_MESSAGE_LEVEL_.equals(attributeName)) {
      updateDisplay((Integer)e.getNewValue());
    } else if (ALL_ATTRIBUTES_.equals(attributeName)) {
      Structure attrs = (Structure)e.getNewValue();
      updateDisplay((Integer)attrs.getAttributeValue(SystemAttributeSymbols.TRACING_MESSAGE_LEVEL_, null));
    }
  }

  class MyCellRenderer extends DefaultListCellRenderer {
     public MyCellRenderer() {
         setOpaque(true);
     }
     @Override
     public Component getListCellRendererComponent(JList list,
						   Object value,
						   int index,
						   boolean isSelected,
						   boolean cellHasFocus)
    {
      super.getListCellRendererComponent(list,value, index, isSelected, cellHasFocus);
      switch (((Integer)value).intValue()) {
      case 0: setText(LEVEL_ZERO); break;
      case 1: setText(LEVEL_ONE); break;
      case 2: setText(LEVEL_TWO); break;
      case 3: setText(LEVEL_THREE); break;	
      }
      return this;
    }
  }
   
  private void updateDisplay(Integer level) {
    getModel().setSelectedItem(level);      
  }
  
  private void setTracingMessageLevel() {
    Integer newLevel = (Integer)getSelectedItem();
    try {
      debuggingParameters.setPropertyValue(SystemAttributeSymbols.TRACING_MESSAGE_LEVEL_, newLevel);
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
  }

  private DebuggingParameters getDebuggingParameters() {
    if (currentConnection == null) return null;
    try {
      Module mod = currentConnection.getKb().getTopLevelModule();
      if (mod != null)
	return mod.getDebuggingParameters();
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
    return null;
  }

  /**
   * Sets the current connection to be used when going to an item.
   * @param connection the <code>TwAccess</code> to use as the 
   * current connection.
   */
  public void setConnection(TwAccess connection){
    if (debuggingParameters != null) {
      try {
	debuggingParameters.removeItemListener(itemAdapter, neededAttributes);
      } catch (G2AccessException g2ae) {
	Trace.exception(g2ae);
      }
    }
    currentConnection = connection;
    debuggingParameters = getDebuggingParameters();
    if (debuggingParameters != null) {
      try {      
	debuggingParameters.addItemListener(itemAdapter, neededAttributes);
      } catch (G2AccessException g2ae) {
	Trace.exception(g2ae);
      }
    }
    setEnabled(currentConnection != null);
  }

  class ItemAdapter implements ItemListener {
    @Override
    public void itemModified(ItemEvent ie) {
      updateDisplay(ie);
    }
    @Override
    public void itemDeleted(ItemEvent ie) {
    }
    @Override
    public void receivedInitialValues(ItemEvent ie) {
      try {
	updateDisplay((Integer)debuggingParameters.getPropertyValue
		      (SystemAttributeSymbols.TRACING_MESSAGE_LEVEL_));
      } catch (G2AccessException g2ae) {
	Trace.exception(g2ae);
      } catch (NoSuchAttributeException nsae) {
	Trace.exception(nsae);
      }      
    }
  }
  

  class ContextChangedAdapter implements ContextChangedListener{
    @Override
    public void currentConnectionChanged(ContextChangedEvent e){
      setConnection(e.getConnection());
    }
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
