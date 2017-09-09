package com.gensym.widgets;

import javax.swing.JList;
import javax.swing.ListModel;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionListener;
import javax.swing.ListCellRenderer;
import javax.swing.DefaultListModel;
import javax.swing.JViewport;
import javax.swing.JScrollPane;
import javax.swing.plaf.ListUI;

public class ScrollList extends JScrollPane{

  final long serialVersionUID = 2L; 
  private JList wrapped = new JList();
  public ScrollList(){
    wrapped = new JList();
    initialize();
  }

  public ScrollList(java.util.Vector vector0){
    wrapped = new JList(vector0);
    initialize();
  }

  public ScrollList(ListModel listModel0){
    wrapped = new JList(listModel0);
    initialize();
  }

  public ScrollList(Object[] object0){
    wrapped = new JList(object0);
    initialize();
  }

  // custom code

  private void initialize() {
    setViewportView (wrapped);
    wrapped.setModel(new DefaultListModel());
  }    

  public void addElement(Object obj) {
    ((DefaultListModel)wrapped.getModel()).addElement(obj);
  }

  // end custom code.

  public void addListSelectionListener(ListSelectionListener listSelectionListener0){
    wrapped.addListSelectionListener(listSelectionListener0);
    return;
  }

  public void addSelectionInterval(int int0, int int1){
    wrapped.addSelectionInterval(int0, int1);
    return;
  }

  public void clearSelection(){
    wrapped.clearSelection();
    return;
  }

  //     protected ListSelectionModel createSelectionModel(){
  //       ListSelectionModel returnVar = null;
  //       returnVar = wrapped.createSelectionModel();
  //       return returnVar;
  //     }

  public void ensureIndexIsVisible(int int0){
    wrapped.ensureIndexIsVisible(int0);
    return;
  }

  //     protected void fireSelectionValueChanged(int int0, int int1, boolean boolean2){
  //       wrapped.fireSelectionValueChanged(int0, int1, boolean2);
  //       return;
  //     }

  @Override
  public javax.accessibility.AccessibleContext getAccessibleContext(){
    javax.accessibility.AccessibleContext returnVar = null;
    returnVar = wrapped.getAccessibleContext();
    return returnVar;
  }

  public int getAnchorSelectionIndex(){
    int returnVar = (int)0;
    returnVar = wrapped.getAnchorSelectionIndex();
    return returnVar;
  }

  public java.awt.Rectangle getCellBounds(int int0, int int1){
    java.awt.Rectangle returnVar = null;
    returnVar = wrapped.getCellBounds(int0, int1);
    return returnVar;
  }

  public ListCellRenderer getCellRenderer(){
    ListCellRenderer returnVar = null;
    returnVar = wrapped.getCellRenderer();
    return returnVar;
  }

  public int getFirstVisibleIndex(){
    int returnVar = (int)0;
    returnVar = wrapped.getFirstVisibleIndex();
    return returnVar;
  }

  public int getFixedCellHeight(){
    int returnVar = (int)0;
    returnVar = wrapped.getFixedCellHeight();
    return returnVar;
  }

  public int getFixedCellWidth(){
    int returnVar = (int)0;
    returnVar = wrapped.getFixedCellWidth();
    return returnVar;
  }

  public int getLastVisibleIndex(){
    int returnVar = (int)0;
    returnVar = wrapped.getLastVisibleIndex();
    return returnVar;
  }

  public int getLeadSelectionIndex(){
    int returnVar = (int)0;
    returnVar = wrapped.getLeadSelectionIndex();
    return returnVar;
  }

  public int getMaxSelectionIndex(){
    int returnVar = (int)0;
    returnVar = wrapped.getMaxSelectionIndex();
    return returnVar;
  }

  public int getMinSelectionIndex(){
    int returnVar = (int)0;
    returnVar = wrapped.getMinSelectionIndex();
    return returnVar;
  }

  public ListModel getModel(){
    ListModel returnVar = null;
    returnVar = wrapped.getModel();
    return returnVar;
  }

  public java.awt.Dimension getPreferredScrollableViewportSize(){
    java.awt.Dimension returnVar = null;
    returnVar = wrapped.getPreferredScrollableViewportSize();
    return returnVar;
  }

  public java.lang.Object getPrototypeCellValue(){
    java.lang.Object returnVar = null;
    returnVar = wrapped.getPrototypeCellValue();
    return returnVar;
  }

  public int getScrollableBlockIncrement(java.awt.Rectangle rectangle0, int int1, int int2){
    int returnVar = (int)0;
    returnVar = wrapped.getScrollableBlockIncrement(rectangle0, int1, int2);
    return returnVar;
  }

  public boolean getScrollableTracksViewportHeight(){
    boolean returnVar = false;
    returnVar = wrapped.getScrollableTracksViewportHeight();
    return returnVar;
  }

  public boolean getScrollableTracksViewportWidth(){
    boolean returnVar = false;
    returnVar = wrapped.getScrollableTracksViewportWidth();
    return returnVar;
  }

  public int getScrollableUnitIncrement(java.awt.Rectangle rectangle0, int int1, int int2){
    int returnVar = (int)0;
    returnVar = wrapped.getScrollableUnitIncrement(rectangle0, int1, int2);
    return returnVar;
  }

  public int getSelectedIndex(){
    int returnVar = (int)0;
    returnVar = wrapped.getSelectedIndex();
    return returnVar;
  }

  public int[] getSelectedIndices(){
    int[] returnVar = null;
    returnVar = wrapped.getSelectedIndices();
    return returnVar;
  }

  public java.lang.Object getSelectedValue(){
    java.lang.Object returnVar = null;
    returnVar = wrapped.getSelectedValue();
    return returnVar;
  }

  public Object[] getSelectedValues(){
    Object[] returnVar = null;
    returnVar = wrapped.getSelectedValues();
    return returnVar;
  }

  public java.awt.Color getSelectionBackground(){
    java.awt.Color returnVar = null;
    returnVar = wrapped.getSelectionBackground();
    return returnVar;
  }

  public java.awt.Color getSelectionForeground(){
    java.awt.Color returnVar = null;
    returnVar = wrapped.getSelectionForeground();
    return returnVar;
  }

  public int getSelectionMode(){
    int returnVar = (int)0;
    returnVar = wrapped.getSelectionMode();
    return returnVar;
  }

  public ListSelectionModel getSelectionModel(){
    ListSelectionModel returnVar = null;
    returnVar = wrapped.getSelectionModel();
    return returnVar;
  }

  //     public plaf.ListUI getUI(){
  //       plaf.ListUI returnVar = null;
  //       returnVar = wrapped.getUI();
  //       return returnVar;
  //     }

  //     public java.lang.String getUIClassID(){
  //       java.lang.String returnVar = null;
  //       returnVar = wrapped.getUIClassID();
  //       return returnVar;
  //     }

  public boolean getValueIsAdjusting(){
    boolean returnVar = false;
    returnVar = wrapped.getValueIsAdjusting();
    return returnVar;
  }

  public int getVisibleRowCount(){
    int returnVar = (int)0;
    returnVar = wrapped.getVisibleRowCount();
    return returnVar;
  }

  public java.awt.Point indexToLocation(int int0){
    java.awt.Point returnVar = null;
    returnVar = wrapped.indexToLocation(int0);
    return returnVar;
  }

  public boolean isSelectedIndex(int int0){
    boolean returnVar = false;
    returnVar = wrapped.isSelectedIndex(int0);
    return returnVar;
  }

  public boolean isSelectionEmpty(){
    boolean returnVar = false;
    returnVar = wrapped.isSelectionEmpty();
    return returnVar;
  }

  public int locationToIndex(java.awt.Point point0){
    int returnVar = (int)0;
    returnVar = wrapped.locationToIndex(point0);
    return returnVar;
  }

  //     protected java.lang.String paramString(){
  //       java.lang.String returnVar = null;
  //       returnVar = wrapped.paramString();
  //       return returnVar;
  //     }

  public void removeListSelectionListener(ListSelectionListener listSelectionListener0){
    wrapped.removeListSelectionListener(listSelectionListener0);
    return;
  }

  public void removeSelectionInterval(int int0, int int1){
    wrapped.removeSelectionInterval(int0, int1);
    return;
  }

  public void setCellRenderer(ListCellRenderer listCellRenderer0){
    wrapped.setCellRenderer(listCellRenderer0);
    return;
  }

  public void setFixedCellHeight(int int0){
    wrapped.setFixedCellHeight(int0);
    return;
  }

  public void setFixedCellWidth(int int0){
    wrapped.setFixedCellWidth(int0);
    return;
  }

  public void setListData(java.util.Vector vector0){
    wrapped.setListData(vector0);
    return;
  }

  public void setListData(java.lang.Object[] object0){
    wrapped.setListData(object0);
    return;
  }

  public void setModel(ListModel listModel0){
    wrapped.setModel(listModel0);
    return;
  }

  public void setPrototypeCellValue(java.lang.Object object0){
    wrapped.setPrototypeCellValue(object0);
    return;
  }

  public void setSelectedIndex(int int0){
    wrapped.setSelectedIndex(int0);
    return;
  }

  public void setSelectedIndices(int[] int0){
    wrapped.setSelectedIndices(int0);
    return;
  }

  public void setSelectedValue(java.lang.Object object0, boolean boolean1){
    wrapped.setSelectedValue(object0, boolean1);
    return;
  }

  public void setSelectionBackground(java.awt.Color color0){
    wrapped.setSelectionBackground(color0);
    return;
  }

  public void setSelectionForeground(java.awt.Color color0){
    wrapped.setSelectionForeground(color0);
    return;
  }

  public void setSelectionInterval(int int0, int int1){
    wrapped.setSelectionInterval(int0, int1);
    return;
  }

  public void setSelectionMode(int int0){
    wrapped.setSelectionMode(int0);
    return;
  }

  public void setSelectionModel(ListSelectionModel listSelectionModel0){
    wrapped.setSelectionModel(listSelectionModel0);
    return;
  }

  public void setUI(ListUI listUI0){
    wrapped.setUI(listUI0);
    return;
  }

  public void setValueIsAdjusting(boolean boolean0){
    wrapped.setValueIsAdjusting(boolean0);
    return;
  }

  public void setVisibleRowCount(int int0){
    wrapped.setVisibleRowCount(int0);
    return;
  }

  @Override
  public void updateUI(){
    super.updateUI();
    if (wrapped != null)
      wrapped.updateUI();
    return;
  }

}
