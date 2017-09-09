package com.gensym.gda.controls;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.JComponent;
import java.util.Vector;
import com.gensym.widgets.LWButton;
import com.gensym.widgets.Spin;
import com.gensym.widgets.SpinListener;


/**This control contains {@link FocusedSpin} control (subclass of com.gensym.widgets.Spin).
All its methods are supported. In addition methods
{@link #setRepeatInterval(int)}, {@link #getRepeatInterval()}, 
{@link #setRepeatWait(int)}, {@link #getRepeatWait()} have been added.
The control uses {@link com.gensym.gda.controls.SpinController com.gensym.gda.controls.SpinController} 
instead of {@link com.gensym.widgets.SpinController com.gensym.widgets.SpinController}.
*/
public class JSpin extends JPanel implements ActionListener {

    public JSpin() {
        this(new JTextField(0));
    }

    public JSpin(JComponent component) {
    	super(new BorderLayout());
    	spin = new FocusedSpin(component);
    	add(spin,BorderLayout.CENTER);
    	setBorder(component.getBorder());
    	component.setBorder(null);
    	
     removeSpinListener(getSpinController());
    	SpinController c =new SpinController();
		c.setTextWidget(component);
    	setSpinController(c);
    	addSpinListener(c);
    	findButtons();
    	setRepeatInterval(200);
     }

	/**
	com.gensym.widgets.Spin class has not provide public access to Spin buttons and its methods.
	This method finds this buttons and stores in upButton and downButton variables.
	*/
	private void findButtons() {
		Component[] components = spin.getComponents();
		Component[] buttons = ((Container)components[0]).getComponents();
		upButton=(LWButton)buttons[0];
		downButton=(LWButton) buttons[1];
		upButton.addActionListener(this);
		downButton.addActionListener(this);
	}

	public void actionPerformed(ActionEvent actionevent) {
  }

	public void requestFocus() {
		spin.getSpinController().getTextWidget().requestFocus();
	}

	//Spin methods support.
		
	public void addSpinListener(SpinListener spinlistener) {
    	spin.addSpinListener(spinlistener);
    }

    public double getIncrement() {return spin.getIncrement();}

    public double getMaxValue() {return spin.getMaxValue();}

    public double getMinValue() {return spin.getMinValue();}

    public com.gensym.widgets.SpinController getSpinController(){
    	return spin.getSpinController();	
    }

    public JComponent getTextWidget() {return (JComponent)spin.getTextWidget();}

    public boolean getWrap() {return spin.getWrap();}

    public void putValue(double d){spin.putValue(d);}

    public void putValue(long l) {spin.putValue(l);}

    public void removeSpinListener(SpinListener spinlistener) {
		spin.removeSpinListener(spinlistener);
    }

    public void setEnabled(boolean flag){
    	spin.setEnabled(flag);
    	super.setEnabled(flag);
    }

    public void setIncrement(double d) {spin.setIncrement(d);}
    
    public void setMaxValue(double d) {spin.setMaxValue(d);}

    public void setMinValue(double d) {spin.setMinValue(d);}

    public void setSpinController(com.gensym.widgets.SpinController spincontroller) {
        spin.setSpinController(spincontroller);
    }

    public void setWrap(boolean flag) {spin.setWrap(flag);}


	//additional methods
	
    public void setRepeatInterval(int i) {
    	upButton.setRepeatInterval(i);
    	downButton.setRepeatInterval(i);
    }

    public void setRepeatWait(int i) {
    	upButton.setRepeatWait(i);
    	downButton.setRepeatWait(i);
      
    }
    public int getRepeatInterval() {return upButton.getRepeatInterval();}

    public int getRepeatWait(){return upButton.getRepeatWait();}


	private FocusedSpin spin;
	protected LWButton upButton;
	protected LWButton downButton;
}