
package com.gensym.tracebeans;

import java.awt.*;
import java.awt.event.*;

public class TraceControlPanel extends Container implements ItemListener, ActionListener {
    
  Checkbox onOffSwitch;
  private Button clearButton;
  private ExceptionTraceDisplay owner;

  TraceControlPanel (ExceptionTraceDisplay owningDisplay) {
    owner = owningDisplay;
    setLayout (new FlowLayout ());
    add (onOffSwitch = new Checkbox ("Trace Exceptions"));
    add (clearButton = new Button ("Clear"));
    onOffSwitch.addItemListener (this);
    clearButton.addActionListener (this);
  }

  @Override
  public void itemStateChanged (ItemEvent ie) {
    if (!java.beans.Beans.isDesignTime())
      owner.setTracingOn (ie.getStateChange() == ItemEvent.SELECTED);
  }

  @Override
  public void actionPerformed (ActionEvent ae) {
    int numChars = owner.displayArea.getText().length ();
    owner.displayArea.replaceRange ("", 0, numChars);
  }

}

