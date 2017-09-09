package com.gensym.demos.g2studiosample;

import java.util.Vector;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.Color;
import java.awt.Component;
import javax.swing.DefaultListModel;
import javax.swing.ListSelectionModel;
import javax.swing.JList;
import javax.swing.DefaultListCellRenderer;
import javax.swing.JSeparator;
import com.gensym.util.Symbol;
import com.gensym.editor.text.Prompter;
import com.gensym.editor.text.PromptsUpdatedListener;
import com.gensym.editor.text.PromptsUpdatedEvent;
import com.gensym.editor.text.PromptSelectionListener;
import com.gensym.editor.text.PromptCategory;
import com.gensym.editor.text.G2SideParser;

public class PromptArea extends JList
implements PromptsUpdatedListener, Prompter {
  DefaultListModel model;
  private JSeparator separator;
  PromptArea() {
    this(new DefaultListModel());      
    addMouseListener(new MouseAdapter() {
      @Override
      public void mouseClicked(MouseEvent e) {
	if (e.getClickCount() == 1) {
	  PromptArea promptArea = PromptArea.this;
	  int index = promptArea.locationToIndex(e.getPoint());
	  Object selection = promptArea.model.elementAt(index);
	  if (selection instanceof PromptCategory) {
	    Vector categoryPrompts = ((PromptCategory)selection).getCompletions();
	    int insertIndex = promptArea.model.indexOf(promptArea.separator) + 1;
	    promptArea.model.removeRange(insertIndex+1, model.getSize()-1);
	    if (categoryPrompts != null) {
	      for (int i=0;i<categoryPrompts.size();i++) {
		Object prompt = categoryPrompts.elementAt(i);
		if (prompt instanceof Symbol)
		  prompt = ((Symbol)prompt).getPrintValue().toLowerCase();
		promptArea.model.insertElementAt(prompt, insertIndex++);
	      }
	    }
	  } else {
	    updatePromptSelectionListener(selection.toString());
	  }
	}
      }
    });
    separator =  new JSeparator();
    separator.setBackground(Color.black);
    separator.setForeground(Color.black);      
  }
  private Vector listeners = new Vector();
  @Override
  public void addPromptSelectionListener(PromptSelectionListener l) {
    listeners.addElement(l);
  }
  @Override
  public void removePromptSelectionListener(PromptSelectionListener l) {
    listeners.removeElement(l);      
  }
  private void updatePromptSelectionListener(String prompt) {
    PromptSelectionListener[] lstnrs;
    synchronized(listeners) {
      lstnrs = new PromptSelectionListener[listeners.size()];
      listeners.copyInto(lstnrs);
    }
    for (int i=0;i<lstnrs.length;i++) 
      lstnrs[i].promptSelected(prompt);
  }
  private PromptArea(DefaultListModel model) {
    super(model);
    this.model = model;
    setCellRenderer(new PromptAreaCellRenderer());
    setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
  }
  @Override
  public String getFirstItem() {
    int index = model.indexOf(separator)+1;
    if (model.size()>index)
      return (String)model.elementAt(index);
    else
      return null;
  }
  @Override
  public String getLastItem() {
    int index = model.indexOf(separator)+1;
    int size = model.size();
    if (size>index)
      return (String)model.elementAt(size-1);
    else
      return null;
  }    
  @Override
  public void requestFocus() {
    //don't want it to ever get focus
  }
    
  @Override
  public void updatePrompts(PromptsUpdatedEvent e) {
    model.clear();      
    if (e == null) return;
    String[] promptStrings = e.getCategoryPrompts();
    for (int i=0; i < promptStrings.length; i++) {
      model.addElement(new PromptCategory(promptStrings[i],(G2SideParser)e.getSource()));
    }      
    model.addElement(separator);
    promptStrings = e.getCompletionPrompts();
    for (int i=0; i < promptStrings.length; i++) {
      model.addElement(promptStrings[i]);
    }
  }
}

class PromptAreaCellRenderer extends DefaultListCellRenderer {
  @Override
  public Component getListCellRendererComponent(JList list,
						Object value,            
						int index,               
						boolean isSelected,      
						boolean cellHasFocus) {
    if (value instanceof Component)
      return (Component)value;
    else {
      setText(value.toString());
      setBackground(Color.white);
      setForeground(Color.black);
      return this;
    }
  }
}
