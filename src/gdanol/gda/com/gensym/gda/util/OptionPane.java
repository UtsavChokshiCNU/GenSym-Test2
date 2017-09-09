package com.gensym.gda.util;

import java.awt.*;
import java.awt.event.*;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import javax.swing.JOptionPane;
import javax.swing.JDialog;
import javax.swing.Icon;
import com.gensym.classes.Item;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.util.ItemListener;
import com.gensym.util.ItemEvent;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;


/**
This class constructs the warning or confirmation dialog. To show the dialog use the 
{@link #showOptionDialog()} method. 
If the Item comm is an instance of gfr-confirm class then 
the {@link com.gensym.util.ItemListener ItemListener}
is added to this item. If the gfr-confirmation attribute of item received 
the value timeout then the dialog is canceled. When the user presses any 
button on the confirmation dialog the corresponding value 
is concluded to the gfr-confirmation attribute of Item.
*/
public class OptionPane extends JOptionPane implements ItemListener{


  /**
    This constructor creates OptionPane as described in {@link 
    javax.swing.JOptionPane#JOptionPane(Object, int, int, Icon, Object[],
    Object) JOptionPane}. If <code>comm</code> is an instance of gfr-confirm object then
    the {@link com.gensym.util.ItemListener ItemListener} is added to listen 
    for the gfr-confirmation attribute of <code>comm</code>.
    */
  public OptionPane(Item comm, Component parentComponent, Object message,
		    String title, int optionType,
		    int messageType, Icon icon,
		    Object[] options, Object initialValue) {
    
    super(message, messageType, optionType, icon, options, initialValue);
    communication=comm;
    try {
      if (!communication.isInstanceOfG2Class(GFR_CONFIRM_))
	communication=null;
      if (communication!=null)
	communication.addItemListener(this);
    } catch (G2AccessException gae) {
      communication=null;//Probably, item has been deleted
      Trace.exception(gae);
    }
    
    dialog = createDialog(parentComponent, title);
    setInitialValue(initialValue);
  }
  
  
  protected int getDialogOption(Object selectedValue) {
    if(selectedValue == null)
      return CLOSED_OPTION;
    if(options == null) {
      if(selectedValue instanceof Integer)
	return ((Integer)selectedValue).intValue();
      return CLOSED_OPTION;
    }
    for(int counter = 0, maxCounter = options.length;
	counter < maxCounter; counter++) {
      if(options[counter].equals(selectedValue))
	return counter;
    }
    return CLOSED_OPTION;
  }
  
  
  
  /**
    Shows the dialog created by constructor.
    */
  public void showOptionDialog() {
    
    SwingWorker worker = new SwingWorker() {
      public Object construct() {
	dialog.show();
	
	Object selectedValue = OptionPane.this.getValue();
	int dialogOption=getDialogOption(selectedValue);
	
	concludeValueForOption(dialogOption, optionType);
	try {
	  if (communication!=null)
	    communication.removeItemListener(OptionPane.this);
	} catch (G2AccessException e) {Trace.exception(e);}
	return null;
      }
    };
    worker.start();
    
  }
  
  /**
    Do nothing.
    */
  public void receivedInitialValues(ItemEvent e) {}
  
  /**
    Listens for the gfr-confirmation attribute, and if the new value is timeout then
    hides the dialog.
    */
  public void itemModified(ItemEvent e) {
    Structure structure = (Structure)e.getDenotation().get(0);
    Symbol symbol = (Symbol)structure.getAttributeValue(NAME_, null);
    if (GFR_CONFIRMATION_.equals(symbol)&& 
	TIMEOUT_.equals(e.getNewValue()) && 
	dialog !=null) {
      dialog.dispose();
      try {communication.removeItemListener(this);
      } catch (G2AccessException gae) {Trace.exception(gae);}
    }
    
  }
  
  /**
    Do nothing.
    */
  public void itemDeleted(ItemEvent e) {
  }
  
  /**
    Concludes the value to the gfr-confirmation attribute depend on the type of 
    OptionPane and the selected button.
    */
  protected void concludeValueForOption(int dialogOption, int optionType) {
    
    if (communication==null) 
      return;
    
    Symbol value;
    switch (dialogOption) {
    case OK_OPTION:
      value = (optionType == JOptionPane.OK_CANCEL_OPTION) ? OK_ : YES_;
      break;
    case NO_OPTION:
      value = NO_;
      break;
    default:
      value = CANCEL_;
      break;
    }
    
    try {communication.setPropertyValue(GFR_CONFIRMATION_, value);
    } catch (G2AccessException gae) {Trace.exception(gae);}
  }
  
  protected Item communication;
  protected JDialog dialog;
  
  protected static final Symbol YES_ = Symbol.intern("YES");
  protected static final Symbol NO_ = Symbol.intern("NO");
  protected static final Symbol OK_ = Symbol.intern("OK");
  protected static final Symbol CANCEL_ = Symbol.intern("CANCEL");
  protected static final Symbol TIMEOUT_ = Symbol.intern("TIMEOUT");
  protected static final Symbol NAME_ = Symbol.intern("NAME");
  protected static final Symbol GFR_CONFIRMATION_ = Symbol.intern("GFR-CONFIRMATION");
  protected static final Symbol GFR_CONFIRM_ = Symbol.intern("GFR-CONFIRM");
}

