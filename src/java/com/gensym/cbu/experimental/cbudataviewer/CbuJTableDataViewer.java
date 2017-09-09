package com.gensym.cbu.experimental.cbudataviewer;

import javax.swing.JTable;
import javax.swing.table.AbstractTableModel;
import java.util.Vector;
import javax.swing.event.TableModelEvent;

public class CbuJTableDataViewer extends JTable implements CbuDataAdapterListener 
{
  CbuJTableTableModel tableModel
;
  public CbuJTableDataViewer()
  {
    super(new CbuJTableTableModel());
    tableModel = (CbuJTableTableModel)dataModel;
  }

  public void setPropertiesToDisplay(String[] dataProperties) 
  {
    tableModel.setPropertiesToDisplay(dataProperties);
  }

  public void setLabels(String[] propertyLabels) 
  {
    tableModel.setLabels(propertyLabels);
  }
  
  @Override
  public void addCbuData(CbuData data) 
  {
    tableModel.addElement(data);
  }
  
  @Override
  public void removeCbuData(CbuData data) 
  {
    tableModel.removeElement(data);
  }

  @Override
  public void cbuDataChanged(CbuData data, String propertyName, Object newPropertyValue)
  {
    tableModel.cbuDataChanged(data, propertyName, newPropertyValue);
  }
}

class CbuJTableTableModel extends AbstractTableModel 
{
  Vector dataProperties = new Vector();
  Vector propertyLabels = new Vector();
  Vector data = new Vector();
  
  void setPropertiesToDisplay(String[]  dataProperties)
  {
    this.dataProperties = new Vector();
    for (int i = 0; i < dataProperties.length; i++)
	this.dataProperties.add(dataProperties[i]);
    fireTableStructureChanged();    
  }

  public void setLabels(String[] propertyLabels) 
  {
    this.propertyLabels = new Vector();
    for (int i = 0; i < propertyLabels.length; i++)
	this.propertyLabels.add(propertyLabels[i]);
    fireTableStructureChanged();    
  }

  void addElement(CbuData cbuData) 
  {
    data.addElement(cbuData);
    fireTableChanged(new TableModelEvent(this));
    //fire row insert?
  }

  void removeElement(CbuData cbuData)
  {
    data.remove(cbuData);
    fireTableChanged(new TableModelEvent(this));
    // fire row delete?
  }

  void cbuDataChanged(CbuData cbuData, String propertyName, Object newPropertyValue)
  {
    fireTableChanged(new TableModelEvent(this, 
					 data.indexOf(cbuData),
					 data.indexOf(cbuData), 
					 dataProperties.indexOf(propertyName)));
  }

  //TABLE MODEL INTERFACE  
  @Override
  public int getColumnCount() 
  {
    return dataProperties.size();
  }

  @Override
  public int getRowCount() 
  {
    return data.size();
  }

  @Override
  public String getColumnName(int i) 
  {
    if (propertyLabels.size() > i)
      return (String)propertyLabels.elementAt(i);
    else
      return "";
  }

  @Override
  public Object getValueAt(int row, int column) 
  {
    Object value = null;

    if (data.size() > row)
      {
	CbuData cbuData = (CbuData)data.elementAt(row);
	if (dataProperties.size() > column)
	  value = cbuData.getPropertyValue((String)dataProperties.elementAt(column));
      }
    return value;
  }
}
