package com.gensym.dlg;

import java.awt.*;
import java.awt.event.*;
import java.util.Vector;
import javax.swing.event.EventListenerList;
import javax.swing.event.ChangeListener;
import javax.swing.event.ChangeEvent;

/**
 *
 * TabGroupPanel.java <p>
 *
 */

public class TabGroupPanel extends Panel implements MouseListener
{
  private int tabHeight;
  private int tabWidth;
  private int tabPageHeight;
  private int tabPageWidth;
  private int selected = -1;
  private int[] tabRightBorder;
  
  private Insets insets;
  private Panel tabPanel;
  private Vector tabs = new Vector();
  private Vector labels = new Vector();
  private EventListenerList listenerList = new EventListenerList();
  private transient ChangeEvent changeEvent = null;
  
  public TabGroupPanel(){
    GridBagLayout gridbag = new GridBagLayout();
    GridBagConstraints c = new GridBagConstraints();
    setLayout(gridbag);
    tabHeight = 21;
    
    c.weightx = 1.0;
    c.weighty = 1.0;
    c.fill = GridBagConstraints.BOTH;
    insets = new Insets(tabHeight+5,6,6,5);
    c.insets = insets;
    tabPanel = makePanel(gridbag,c);
    tabPanel.setLayout(new CardLayout());
    
    setBackground(SystemColor.control);
    addMouseListener(this);
  }	

  public void setInsets(Insets insets) {
    this.insets = new Insets(tabHeight+insets.top, insets.left, insets.bottom, insets.right);
  }
  
  /**
   * add a tab page to the tab dialog, with a title and component.
   *
   * @param title The title of the tab.
   * @param component The component to be inserted in the tab page. 
   */
  
  public void addTab(String title, Component component){
    tabs.addElement(component);
    labels.addElement(title);
    tabPanel.add(title,component);
    if (tabs.size() == 1){
      addAccessibleSelection(0);
    }
    invalidate();
    repaint();
  }

  public void insertTab(String title, Component component, int index ){
    tabs.insertElementAt(component, index);
    labels.insertElementAt(title, index);
    tabPanel.add(component, title, index);
    if (tabs.size() == 1){
      addAccessibleSelection(0);
    }
    invalidate();
    repaint();
  }
  private Panel makePanel(GridBagLayout gridbag,
			  GridBagConstraints c) {
    Panel panel = new Panel();
    gridbag.setConstraints(panel, c);
    add(panel);
    return(panel);
  }
  
  /**
   * select a tab.
   *
   * @param index The index of the tab to be selected.
   */
  
  public void addAccessibleSelection(int index) {
    ((CardLayout)tabPanel.getLayout()).show(tabPanel,(String)(labels.elementAt(index)));
    selected = index;
    repaint();
  }
  
  /**
   * @param index index of the tab page that holds the component.
   * @return The component at the specified index.
   */
  
  public Component getComponentAt(int index) {
    return ((Component)(tabs.elementAt(index)));
  }
  
  public int getSelectedIndex() {
    return selected;
  }
  
  /**
   * get the title of a tab page.
   *
   * @param index index of the tab page.
   * @return title of the tab page.
   *
   */
  
  public int getTabHeight(){
    return tabHeight;
  }
  
  public String getTitleAt(int index) {
    return ((String)(labels.elementAt(index)));
  }
  
  public void removeTabAt(int index) {
    tabs.removeElementAt(index);
    labels.removeElementAt(index);
    if (selected > index)
    {
	selected--;
	((CardLayout)tabPanel.getLayout()).
	  show(tabPanel,(String)(labels.elementAt(selected)));
    }
    repaint();
  }
  
  public void setComponentAt(int index, Component component){
    tabs.setElementAt(component, index);
  }
  
  public void setTitleAt(int index, String title){
    labels.setElementAt(title, index);
  }
  
  @Override
  public void paint(Graphics g) {
    tabPageWidth = getSize().width;
    tabPageHeight = getSize().height;
    g.setColor(Color.white);
    g.drawLine(0,tabHeight,0,tabPageHeight); 
    
    g.setColor(Color.gray);
    g.drawLine(1,tabPageHeight-2,tabPageWidth-2,tabPageHeight-2);
    g.drawLine(tabPageWidth-2,tabHeight,tabPageWidth-2,tabPageHeight-1);
    
    g.setColor(Color.black);
    g.drawLine(0,tabPageHeight-1,tabPageWidth-1,tabPageHeight-1);
    g.drawLine(tabPageWidth-1,tabHeight,tabPageWidth-1,tabPageHeight-1);
    
    paintTab(g);
  }
  
  public void paintTab(Graphics g) {
    
    int tabX = 2;
    int tabY = 2;
    int tabRight = 0;
    int tabBottom = tabHeight;
    int tempX = 0;
    int tempY = 0;
    int tempRight = 0;
    String name = "";
    FontMetrics metrics = null;
    tabRightBorder = new int[tabs.size()];
    
    for (int i = 0; i<tabs.size(); i++) {
      name = (String)(labels.elementAt(i));
      metrics = g.getFontMetrics(getFont());
      tabWidth = metrics.stringWidth(name) + 14;
      tabRightBorder[i] = ( (i>0) ? (tabWidth+tabRightBorder[i-1]) : tabWidth);
      tabRight = tabWidth;
      tabBottom = tabHeight;
      
      if (selected != i) {
	paintOneTab(g,tabX,tabY,tabRight,tabBottom);
	g.drawString(name, tabX+7, metrics.getHeight()+1);
	tabX += tabRight;
      }
      else {
	tempX = tabX - 2;
	tempY = tabY - 2;
	tempRight = tabRight + 4;
	tabX += tabRight;
      }
      g.setColor(Color.white);
      g.drawLine(0,tabBottom,tabPageWidth-1,tabBottom);
    }
    if (selected > -1 && !labels.isEmpty()) {
      paintOneTab(g,tempX,tempY,tempRight,tabBottom);
      g.drawString((String)(labels.elementAt(selected)), tempX+7, metrics.getHeight()+1);
    }
  }
  
  
  private void paintOneTab(Graphics g, int left, int top, int right, int bottom) {
    g.setColor(SystemColor.control);
    g.drawRect(left,top,right,bottom);
    g.fillRect(left,top,right,bottom);
    
    //paint left border and top border white
    g.setColor(Color.white);
    g.drawLine(left,top+2,left,bottom);
    g.drawLine(left+2,top,left+right-3,top);
    g.drawLine(left+1,top+1,left+1,top+1);
    
    //paint right border dark gray
    g.setColor(Color.gray);
    g.drawLine(left+right-2,top+2,left+right-2,bottom);
    
    //paint right border black
    g.setColor(Color.black);
    g.drawLine(left+right-1,top+2,left+right-1,bottom);
    g.drawLine(left+right-2,top+1,left+right-2,top+1);
  }
  
  @Override
  public Dimension getPreferredSize() {
    int largestWidth = 0;
    int largestHeight = 0;
    for (int i=0; i < tabs.size(); i++) {
      Dimension thisSize = ((Component)tabs.elementAt(i)).getPreferredSize();
      largestWidth = (thisSize.width > largestWidth) ? thisSize.width 
	: largestWidth;
      largestHeight = (thisSize.height > largestHeight) ? thisSize.height
	: largestHeight;
    }
    return new Dimension (largestWidth + insets.left + insets.right, 
			  largestHeight + insets.top + insets.bottom);
  }

  public void addChangeListener(ChangeListener l) {
    listenerList.add(ChangeListener.class, l);
  }

  public void removeChangeListener(ChangeListener l) {
    listenerList.remove(ChangeListener.class, l);
  }

  private void fireStateChanged() {
    // Guaranteed to return a non-null array
    Object[] listeners = listenerList.getListenerList();
    // Process the listeners last to first, notifying
    // those that are interested in this event
    for (int i = listeners.length-2; i>=0; i-=2) {
      if (listeners[i]==ChangeListener.class) {
        // Lazily create the event:
        if (changeEvent == null)
          changeEvent = new ChangeEvent(this);
        ((ChangeListener)listeners[i+1]).stateChanged(changeEvent);
      }
    }
  }

  @Override
  public void mousePressed(MouseEvent e) {
    int x = e.getX();
    int y = e.getY();
		
    if ((y<=tabHeight) && (y>=0)) {
      for (int i=0; i<tabs.size(); i++) {
	if (x<tabRightBorder[i]){
	  //tabPanel.setBounds(1,22,getSize().width-3, getSize().height-25);
	  ((CardLayout)tabPanel.getLayout()).show(tabPanel,(String)(labels.elementAt(i)));
	  selected = i;
          fireStateChanged();
	  break;
	}
      }
      repaint();
    }
  }

  public void selectTab(int index) {
    addAccessibleSelection(index);
    fireStateChanged();
  }


  @Override
  public void mouseEntered(MouseEvent e) { }
  @Override
  public void mouseExited(MouseEvent e) { }
  @Override
  public void mouseClicked(MouseEvent e) { }
  @Override
  public void mouseReleased(MouseEvent e) { }
}

