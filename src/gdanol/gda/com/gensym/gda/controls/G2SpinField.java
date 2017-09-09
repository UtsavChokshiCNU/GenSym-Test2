
package com.gensym.gda.controls;


import java.awt.event.ActionEvent;
import java.awt.event.FocusEvent;
import java.awt.event.KeyListener;
import java.awt.event.KeyEvent;

import javax.swing.JLabel;

import com.gensym.controls.FieldType;
import com.gensym.controls.AttributeEditor;
import com.gensym.controls.LimitMode;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.dlgevent.ObjectChangeListener;
import com.gensym.util.Symbol;
import com.gensym.jcontrols.G2TextField;
import com.gensym.widgets.SpinEvent;

/**
*This class implements AttributeEditor. 
*Use spin buttons or keyboard keys UpArrow and DownArrow to increment and decrement spin value or
enter new value in the text field.
*/
public class G2SpinField extends JSpin implements AttributeEditor, KeyListener, Boundary {

  private G2textfield textField;
  private boolean emptyFieldImpliesNull = false;
  
  public G2SpinField(G2textfield field) {
  	super(field);
    textField = field;
   	textField.addKeyListener(this);
    textField.setFieldType(new FieldType("Quantity"));
    setMinValue(-Double.MAX_VALUE);
    setMaxValue(Double.MAX_VALUE);
    setIncrement(1);
	LimitMode limitMode = new LimitMode("inclusive");
	textField.setLowerLimitMode(limitMode);
	textField.setUpperLimitMode(limitMode);  			
  }

  public G2SpinField() {
    this(new G2textfield());
}
  
  public G2SpinField(double min, double max, double increment) {
  	this();
  	setMinValue(min);
  	setMaxValue(max);
  	setIncrement(increment);
  }


	public void setTextWidget(G2textfield field) {
		textField=field;
		getSpinController().setTextWidget(field);
	}
  public G2textfield getTextField() {return textField;}

  public void setAttribute(Symbol attribute_) {textField.setAttribute(attribute_);}

  public Symbol getAttribute() {return textField.getAttribute();}

  public void setFieldType(FieldType type) {textField.setFieldType(type);}

  public FieldType getFieldType() {return textField.getFieldType();}

  public synchronized void addObjectChangeListener(ObjectChangeListener listener) {
    textField.addObjectChangeListener(listener);
  }

  public synchronized void removeObjectChangeListener(ObjectChangeListener listener) {
    textField.removeObjectChangeListener(listener);
  }

  public void setEmptyFieldImpliesNull(boolean emptyFieldImpliesNull) {
    textField.setEmptyFieldImpliesNull(emptyFieldImpliesNull);

    this.emptyFieldImpliesNull = emptyFieldImpliesNull;
  }

  public void actionPerformed(ActionEvent event) {
    if (emptyFieldImpliesNull && textField.getText().equals("")) {
      textField.setText("0");
    } else {
      super.actionPerformed(event);
    }

    textField.focusLost(new FocusEvent(textField, FocusEvent.FOCUS_LOST));
  }


  public void objectUpdated(ObjectUpdateEvent event) {
    textField.objectUpdated(event);
  }

	public void setMinValue(double minvalue) {
		super.setMinValue(minvalue);
		textField.setLowerLimit(minvalue);
	}

	public void setMaxValue(double maxvalue) {
		super.setMaxValue(maxvalue);
		textField.setUpperLimit(maxvalue);
	}

	public void keyTyped(KeyEvent event) {}
	public void keyReleased(KeyEvent event) {}
	public void keyPressed(KeyEvent event) {
		SpinController c = (SpinController)getSpinController();
		G2textfield textField;
		textField = (G2textfield) getTextWidget();
		int code = event.getKeyCode();
		if (code == KeyEvent.VK_UP)
		{
			c.spinUp(new SpinEvent(this, true));
		}
		if (code == KeyEvent.VK_DOWN)
		{
			c.spinDown(new SpinEvent(this, false));
		}
	}

}