package com.gensym.ntw.attrdisplays;


import java.util.Vector;
import java.util.Hashtable;
import javax.swing.DefaultListModel;
import com.gensym.uitools.attrdisplays.layoutmodel.AttributeDisplayLayoutEditor;
import com.gensym.uitools.attrdisplays.layoutmodel.AttributeDisplayLayout;
import com.gensym.uitools.attrdisplays.layoutmodel.AttributeDisplayLayoutImpl;
import com.gensym.uitools.attrdisplays.layoutmodel.LayoutTableModel;
import com.gensym.uitools.attrdisplays.layoutmodel.LayoutStructure;
import com.gensym.uitools.attrdisplays.layoutmodel.VectorsNotSameLengthException;

public  class G2AttributeDisplayLayoutEditor extends AttributeDisplayLayoutEditor{

  public G2AttributeDisplayLayoutEditor(Object[] choices) {
    super(choices);
  }

  public G2AttributeDisplayLayoutEditor(Vector initialLayouts, Object[] choices) {
    super(initialLayouts, choices);
  }

  @Override
  public AttributeDisplayLayout createAttributeDisplayLayout() {
    try {
      AttributeDisplayLayout adl = super.createAttributeDisplayLayout();
      adl.setGlobalLayout(new G2GlobalLayout());
      return adl;
    } catch (VectorsNotSameLengthException vnsle){
      //no vectors in LayoutStructure constructor call, this is moot.
    }
    return null;
  }

  private AttributeDisplayLayout orderAttributes(AttributeDisplayLayout adl) {
    Hashtable hashTable = new Hashtable();
    LayoutStructure[] layoutArray = adl.getRows();
    for (int i = 0; i<layoutArray.length; i++) {
      hashTable.put(layoutArray[i].getRowKey(), layoutArray[i]);
    }
    adl.setRows(new Vector());
    for (int j=0; j<choices.length; j++) {
      LayoutStructure temp = (LayoutStructure)hashTable.get(choices[j]);
      if (temp != null) adl.addAttributeRow(temp);
    }
    return adl;
  }
  @Override
  public LayoutTableModel createLayoutTableModel(AttributeDisplayLayout adl) {
    if (adl == null) return new G2LayoutTableModel();
    adl = orderAttributes(adl);
    return new G2LayoutTableModel(adl.getRows());
  }

  @Override
  public DefaultListModel createListModel (LayoutTableModel tableModel) {
    DefaultListModel listModel = new DefaultListModel();
    for (int i=0; i<choices.length; i++)
      listModel.addElement(choices[i]);
    if (tableModel == null) return listModel;
    for (int j=0;j<tableModel.getRowCount(); j++)
      listModel.removeElement(tableModel.getValueAt(j, 0));
    return listModel;
  }

  @Override
  public Object createLayoutStructure(Object key) {
    try {
      LayoutStructure newLayout = new LayoutStructure(key);
      newLayout.setAttributeValue(G2LayoutTableModel.ROW_KEY, key);
      newLayout.setAttributeValue(G2LayoutTableModel.ROW_LAYOUT, 
				  new Boolean(false));
      return newLayout;
    } catch (VectorsNotSameLengthException vnsle) {
      //no vectors in LayoutStructure constructor call, this is moot.
    }
    return null;
  }
  
}
