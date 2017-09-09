package com.gensym.editor.icon.g2;

import com.gensym.util.ItemListener;
import com.gensym.util.ItemEvent;
import com.gensym.editor.icon.core.ObjectChangedListener;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;

class G2ItemChangedAdapter implements ItemListener {
  private ObjectChangedListener objectChangedListener;
  public static final Symbol
  NAME_ = Symbol.intern ("NAME"),
    ICON_DESCRIPTION_ = Symbol.intern ("ICON-DESCRIPTION");
  
  public G2ItemChangedAdapter(ObjectChangedListener objectChangedListener) {
    this.objectChangedListener = objectChangedListener;
  }
  @Override
  public void receivedInitialValues (ItemEvent e) {}


  private void notifyListenerWhenAppropriate(ItemEvent e) {
    Sequence denotationSequence = e.getDenotation();
    Structure denotation = (Structure) denotationSequence.elementAt(0);
    Symbol attributeName =
      (denotation!=null?(Symbol)denotation.getAttributeValue(NAME_, null):null);
    if (ICON_DESCRIPTION_.equals(attributeName)) {
      objectChangedListener.objectChanged(e);  
    }
  }
  
  @Override
  public void itemModified (ItemEvent e) {
    notifyListenerWhenAppropriate(e);
    
  }
  @Override
  public void itemDeleted (ItemEvent e){
    notifyListenerWhenAppropriate(e);
  }  
}
