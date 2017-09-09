package com.gensym.uitools.inspect;

import com.gensym.message.Resource; 
import com.gensym.uitools.utils.TabbedControlPanel;
import com.gensym.uitools.utils.GensymLogoAnimator;
import com.gensym.util.ActivityDisplay;
import com.gensym.uitools.utils.MultiEditPanel;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JScrollPane;
import javax.swing.text.JTextComponent;
import javax.swing.JTextField;
import javax.swing.JList;
import javax.swing.DefaultListModel;
import javax.swing.ListCellRenderer;
import java.awt.Component;
import com.gensym.ntw.TwAccess;
import java.awt.Frame;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.util.StringTokenizer;
import com.gensym.util.Symbol;
import java.util.Vector;
import com.gensym.jgi.G2Access;
import java.awt.Color;
import java.awt.Image;
import javax.swing.ImageIcon;
import javax.swing.Icon;
import java.awt.Toolkit;
import java.awt.Insets;

public class InspectControlPanel extends TabbedControlPanel
implements ActivityDisplay, ActionListener
{
  static Resource i18n
  = Resource.getBundle("com/gensym/uitools/inspect/InspectShortResource");    
  private MultiEditPanel mainPanel, viewParametersPanel;
  private JList connectionsJList;
  private static String[] mainPanelLabels = {i18n.getString("ClassNamePrompt"),
					     i18n.getString("ItemNamePrompt"),
					     i18n.getString("InspectExtraFilters")};
  private static String[] tabLabels = {i18n.getString("nameAndTypeTab"),
				       i18n.getString("viewParametersTab"),
				       i18n.getString("locationTab")};
  private static String[] viewParametersPanelLabels
  = {i18n.getString("InspectDisplayAttributes")};
  private static String[] mainPanelInitialValues = {"","",""};
  private static String[] viewParametersPanelInitialValues = {"",""};
  private JButton runButton, clearButton, pauseResumeButton, stopButton;
  private GensymLogoAnimator activityDisplay;
  private ClassBrowserButtonAdapter adapter;
  private boolean running, paused;
  public static final String FIND = i18n.getString("find");
  public static final String RECOMPILE = i18n.getString("recompile");
  public static final String WRITE = i18n.getString("write");  
  public static final String PAUSE = i18n.getString("pause");
  public static final String RESUME = i18n.getString("resume");
  public static final String STOP = i18n.getString("stop");
  public static final String CLEAR = i18n.getString("clear");
  
  public InspectControlPanel(Frame focalFrame) {
    this(new ClassBrowserButtonAdapter(focalFrame));
  }

  private InspectControlPanel(ClassBrowserButtonAdapter adapter)
  {
    this(createMainPanel(adapter),
	 adapter,
	 new MultiEditPanel(viewParametersPanelLabels,
			    viewParametersPanelInitialValues),
	 new JList(new DefaultListModel()),
	 new JDefaultButton(FIND),
	 new JButton(CLEAR),	 
	 new JButton(PAUSE),
	 new JButton(STOP),
	 new GensymLogoAnimator());
  }

  private static final int CLASSNAME_INDEX = 0;
  /*private static final Icon classdefIcon =
    new ImageIcon(Toolkit.getDefaultToolkit().getImage
    (InspectControlPanel.class.getResource("classdef.gif")));*/
  private static MultiEditPanel createMainPanel(ClassBrowserButtonAdapter adapter)
  {
    //classdefIcon
    JButton classBrowserButton = new JButton(i18n.getString("browse")+"...");
    //classBrowserButton.setMargin(new Insets(-2,0,-6,0));//t,l,b,r
    classBrowserButton.setToolTipText(i18n.getString("browseClassHierarchy"));
    
    JButton[] buttons = new JButton[mainPanelLabels.length];
    buttons[CLASSNAME_INDEX] = classBrowserButton;
    MultiEditPanel mep =
      new MultiEditPanel(mainPanelLabels, mainPanelInitialValues, buttons);
    JTextField textField = mep.getTextField(CLASSNAME_INDEX);
    adapter.setTextField(textField);    
    classBrowserButton.addActionListener(adapter);   
    return mep;
  }

  public void setRunButtonText(String text) {
    runButton.setText(text);
  }
  
  private InspectControlPanel(MultiEditPanel mainPanel,
			      ClassBrowserButtonAdapter adapter,
			      MultiEditPanel viewParametersPanel,
			      JList connectionsJList,
			      JDefaultButton runButton,
			      JButton clearButton,
			      JButton pauseResumeButton,
			      JButton stopButton,
			      GensymLogoAnimator activityDisplay)
  {
    super(new Component[]
	  {mainPanel,viewParametersPanel, connectionsJList},
	  tabLabels,
	  new JButton[] {runButton, //clearButton,
			   pauseResumeButton,stopButton},
	  (Component)activityDisplay);
    pauseResumeButton.setEnabled(false);
    stopButton.setEnabled(false);
    this.adapter = adapter;
    adapter.setControlPanel(this);
    this.connectionsJList = connectionsJList;
    connectionsJList.setBackground(Color.white);
    connectionsJList.setCellRenderer(new ConnectionCellRenderer());
    this.mainPanel = mainPanel;
    JTextField classField = mainPanel.getTextField(0);
    classField.requestFocus();
    classField.addActionListener(this);
    this.viewParametersPanel = viewParametersPanel;
    this.runButton = runButton;
    runButton.setPreferredSize(new java.awt.Dimension(75,23));
    this.pauseResumeButton = pauseResumeButton;
    this.stopButton = stopButton;
    runButton.setToolTipText(i18n.getString("startSearch"));
    this.clearButton = clearButton;
    clearButton.setToolTipText(i18n.getString("clearSearchResults"));
    this.activityDisplay = activityDisplay;
    addActionListener(this);
  }

  @Override
  public void actionPerformed(ActionEvent ae) {
    if (ae.getSource() instanceof JTextField)
      find();
    String cmd = ae.getActionCommand();
    if (CLEAR.equals(cmd)) {
      if (!running)
	runButton.setEnabled(true);
    } else if (STOP.equals(cmd)) {
      paused = false;
    } else if (FIND.equals(cmd)||RECOMPILE.equals(cmd)||WRITE.equals(cmd)) {
      paused = false;
    } else if (PAUSE.equals(cmd)) {
      paused = true;
      pauseResumeButton.setText(RESUME);
    } else if (RESUME.equals(cmd)) {
      paused = false;
      pauseResumeButton.setText(PAUSE);
    }
  }
  
  class ConnectionCellRenderer extends JLabel implements ListCellRenderer {
    ConnectionCellRenderer()
    {
      setOpaque(true);
    }
    
    @Override
    public Component getListCellRendererComponent(JList list,
						  Object value,            
						  int index,               
						  boolean isSelected,      
						  boolean cellHasFocus)
    {
      G2Access cxn = (G2Access)value;
      if (isSelected) {
	setForeground(list.getSelectionForeground());
	setBackground(list.getSelectionBackground());
      } else {
	setBackground(Color.white);
	setForeground(Color.black);
      }
      setText(cxn.toShortString());
      return this;
    }
  }

  public void addConnection(G2Access connection)
  {
    ((DefaultListModel)connectionsJList.getModel()).addElement(connection);
  }

  public void removeConnection(G2Access connection)
  {
    ((DefaultListModel)connectionsJList.getModel()).removeElement(connection);
  }
  
  public void selectConnection(G2Access connection)
  {
    int index = ((DefaultListModel)connectionsJList.getModel()).indexOf(connection);
    if (index > -1)
      connectionsJList.addSelectionInterval(index, index);
  }

  @Override
  public void setBusy() {
    if (running && !paused)
      activityDisplay.setBusy();
  }

  public void setRunning(boolean running)
  {
    if (this.running == running) return;
    this.running = running;
    if (running) {
      //runButton.setEnabled(false);      
      pauseResumeButton.setEnabled(true);
      stopButton.setEnabled(true);
    } else {
      pauseResumeButton.setEnabled(false);
      stopButton.setEnabled(false);
      pauseResumeButton.setText(PAUSE);
    }
  }
  
  @Override
  public void setIdle() {
    activityDisplay.setIdle();
  }

  public void find() {
    clear();
    runButton.doClick();
  }

  public void stop() {
    stopButton.doClick();
  }

  public void pause() {
    if (PAUSE.equals(pauseResumeButton.getText()))
      pauseResumeButton.doClick();
  }
  
  public void resume() {
    if (RESUME.equals(pauseResumeButton.getText()))
      pauseResumeButton.doClick();
  }
  
  public void clear(){
    clearButton.doClick();
  }
  
  public void addActionListener(ActionListener listener) {
    runButton.addActionListener(listener);
    clearButton.addActionListener(listener);
    pauseResumeButton.addActionListener(listener);
    stopButton.addActionListener(listener);
  }

  public void removeActionListener(ActionListener listener) {
    runButton.removeActionListener(listener);
    clearButton.removeActionListener(listener);
    pauseResumeButton.removeActionListener(listener);
    stopButton.removeActionListener(listener);    
  }

  public Object[] getSelectedConnections()
  {
    return connectionsJList.getSelectedValues();
  }

  public String getClassName() {
    return mainPanel.getResults()[0];
  }

  public void setClassName(String className) {
    mainPanel.setTextFieldValue(0,className);
  }
  
  public String getItemName() {
    return mainPanel.getResults()[1];
  }

  public void setItemName(String itemName) {
    mainPanel.setTextFieldValue(1, itemName);
  }
       
  public String getExtraFilters() {
    return mainPanel.getResults()[2];
  }  

  public void setExtraFilters(String extraFilters)
  {
    mainPanel.setTextFieldValue(2, extraFilters);
  }
  
  public Symbol[] getDisplayAttributes() {
    return parseAttributes(viewParametersPanel.getResults()[0]);      
  }

  private static String printArray(Object[] array) {
    String str="";
    if (array != null)
      for (int i=0;i<array.length;i++)
	str+=(array[i].toString().toLowerCase() + " ");
    return str;
  }
  
  public void setDisplayAttributes(Symbol[] attributes)
  {
    viewParametersPanel.setTextFieldValue(0, printArray(attributes));
  }
  
  private static Symbol[] parseAttributes(String attributes)
  {
    StringTokenizer st = new StringTokenizer(attributes);
    Vector attrs = new Vector();
    while (st.hasMoreTokens()) {
      attrs.addElement(Symbol.intern(st.nextToken().toUpperCase()));
    }
    Symbol[] attrsArray = new Symbol[attrs.size()];
    attrs.copyInto(attrsArray);
    return attrsArray;
  }
  
}

class ClassBrowserButtonAdapter implements ActionListener
{
  private static final Symbol ITEM_ = Symbol.intern ("ITEM");  
  private JTextField textField;
  private Frame parentFrame;
  private TwAccess connection;
  private InspectControlPanel ipc;

  void setTextField(JTextField textField)
  {
    this.textField = textField;
  }
  
  void setControlPanel(InspectControlPanel ipc)
  {
    this.ipc = ipc;
  }
  
  ClassBrowserButtonAdapter(Frame parentFrame)
  {
    this.parentFrame = parentFrame;
  }
  
  @Override
  public void actionPerformed(ActionEvent ae) {
    Object[] connections = ipc.getSelectedConnections();
    for (int i=0;i<connections.length;i++) {
      Object connection = connections[i];
      if (connection instanceof TwAccess) {
	TextSettingClassBrowser browser =
	  new TextSettingClassBrowser(textField,
				      parentFrame,
				      (TwAccess)connection,
				      ITEM_);
	browser.setTitle(InspectControlPanel.i18n.getString("browseClassHierarchy") +
			 " - " + 
			 ((TwAccess)connection).toShortString());
	browser.setVisible(true);
      }
    }
  }
  
}

  class JDefaultButton extends JButton {
    JDefaultButton(String label) {
      super(label);
    }
    @Override
    public boolean isDefaultButton() {
      return true;
    }
  }
