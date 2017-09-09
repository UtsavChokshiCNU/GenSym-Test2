/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ZoomPanel.java
 *
 */
package com.gensym.uiutil.dialogs;

import java.awt.Component;
import java.awt.Graphics;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.event.FocusListener;
import java.awt.event.FocusEvent;
import java.awt.event.ItemListener;
import java.awt.event.ItemEvent;
import java.awt.event.KeyListener;
import java.text.ParseException;
import javax.swing.ButtonGroup;
import javax.swing.JToggleButton;
import javax.swing.JTextField;
import javax.swing.JRadioButton;
import javax.swing.JPanel;
import javax.swing.border.TitledBorder;
import javax.swing.border.EtchedBorder;
import com.gensym.message.Resource;
import com.gensym.widgets.Spin;
import com.gensym.widgets.SpinListener;
import com.gensym.widgets.SpinEvent;

public class ZoomPanel extends JPanel{
  
  private static Resource i18nMsgs = Resource.getBundle("com.gensym.uiutil.dialogs.Messages");
  private static Resource i18nErrors = Resource.getBundle("com.gensym.uiutil.dialogs.Errors");

  private static final double[] defaultScales = new double[]{4, 2, 1, .75, .5, .25};
  private static final String[] defaultLabels = new String[]{i18nMsgs.getString("Zoom400"),
							     i18nMsgs.getString("Zoom200"),
							     i18nMsgs.getString("Zoom100"),
							     i18nMsgs.getString("Zoom75"),
							     i18nMsgs.getString("Zoom50"),
							     i18nMsgs.getString("Zoom25")};
  private ButtonGroup group;
  private ZoomRadioButton[] buttons;
  private ZoomRadioButton rbFit;
  private PercentZoomButton rbPercent;
  
  private JRadioButton button = null;

  public ZoomPanel(double currentZoomX, double currentZoomY, double zoomToFit){
    this(defaultScales, defaultLabels, true, true, currentZoomX, currentZoomY, zoomToFit);
  }

  public ZoomPanel(double[] values, String[] labels, boolean zoomToFit, boolean zoomPercent,
		   double currentZoomX, double currentZoomY, double zoomToFitValue){
    setBorder(new TitledBorder(new EtchedBorder(), i18nMsgs.getString("ZoomTo")));
    group = new ButtonGroup();

    setLayout(new GridBagLayout());
    GridBagConstraints constraints = new GridBagConstraints();
    constraints.anchor = GridBagConstraints.WEST;
    constraints.gridwidth = GridBagConstraints.REMAINDER;
    constraints.weightx = 0.1;
    constraints.weighty = 0.1;

    if (zoomToFit)
      rbFit = createZoomButton(i18nMsgs.getString("ZoomToFit"), zoomToFitValue, constraints, zoomPercent);

    if (values == null)
      values = defaultScales;
    if (labels == null)
      labels = defaultLabels;
    int len = values.length;
    buttons = new ZoomRadioButton[len];
    for (int i=0; i<len; i++)
      buttons[i] = createZoomButton(labels[i], values[i], constraints, zoomPercent);

    if (zoomPercent)
      rbPercent = createPercentZoomButton(i18nMsgs.getString("ZoomPercent"), constraints);
    
    if (currentZoomX == currentZoomY){
      for (int i=0; i<len; i++){
	if (currentZoomX == buttons[i].getZoomAmount()){
	  button = buttons[i];
	  break;
	}
      }
      if (button == null && zoomToFit && currentZoomX == rbFit.getZoomAmount())
	button = rbFit;
      else if (button == null && zoomPercent){
	button = rbPercent;
	rbPercent.setZoomAmount(currentZoomX);
      }
      if (button != null)
	button.setSelected(true); 
    }
  }

  private boolean firstPaint = true;
  @Override
  public void paint (Graphics g) {
    super.paint (g);
    if (firstPaint){
      if (button != null)
	button.requestFocus();
      firstPaint = false;
    }
  }

  private ZoomRadioButton createZoomButton(String label, double zoomAmount, 
					   GridBagConstraints c, boolean zoomPercent){
    ZoomRadioButton rb = new ZoomRadioButton(label, zoomAmount);
    group.add(rb);
    add(rb, c);
    if (zoomPercent)
      rb.addItemListener(new RadioButtonListener());
    return rb;
  }

  private PercentZoomButton createPercentZoomButton(String label, GridBagConstraints constraints){
    Spin percentSpin = new Spin();
    percentSpin.setMinValue(0);
    percentSpin.setMaxValue(1000000);
    percentSpin.setIncrement(1);

    PercentZoomButton rb = new PercentZoomButton(label, percentSpin);
    constraints.gridwidth = 1;
    group.add(rb);
    add(rb, constraints);

    constraints.gridwidth = GridBagConstraints.REMAINDER;
    constraints.weightx = 0.9;
    constraints.fill = GridBagConstraints.HORIZONTAL;
    add(percentSpin, constraints);

    return rb;
  }

  void setKeyInterpreter(KeyListener keyListener){
    if (rbFit != null)
      rbFit.addKeyListener(keyListener); 
    for (int i=0; i<buttons.length; i++)
      buttons[i].addKeyListener(keyListener); 
    if (rbPercent != null)
      rbPercent.addKeyListener(keyListener);
  }

  String validateInput(){
    if (rbPercent == null) return null;
    double value;
    value = getValue();
    if (value < 0){
      rbPercent.selectPercent();
      return i18nErrors.format("InvalidPercentValue", getValueAsText());
    }
    return null;
  }

  double getValue(){
    return ((ZoomButtonModel)group.getSelection()).getZoomAmount();
  }

  String getValueAsText(){
    return ((ZoomButtonModel)group.getSelection()).getZoomAmountAsText();
  }

  class RadioButtonListener implements ItemListener{
    @Override
    public void itemStateChanged(ItemEvent event){
      if (!event.getSource().equals(rbFit) && event.getStateChange() == event.SELECTED){
	ZoomRadioButton rb = (ZoomRadioButton)event.getSource();
	double value = rb.getZoomAmount();
	rbPercent.setZoomAmount(value);
      }
    }
  }

  class ZoomRadioButton extends JRadioButton{

    ZoomRadioButton(String label, double zoomAmount){
      super(label);
      setModel(new ZoomButtonModel(zoomAmount));
    }

    double getZoomAmount(){
      return ((ZoomButtonModel)getModel()).getZoomAmount();
    }

    String getZoomAmountAsText(){
      return ((ZoomButtonModel)getModel()).getZoomAmountAsText();
    }
  }

  class ZoomButtonModel extends JToggleButton.ToggleButtonModel{

    private double zoomAmount;
    private Spin spin; //bad

    ZoomButtonModel(double zoomAmount){
      this.zoomAmount = zoomAmount;
    }

    ZoomButtonModel(Spin spin){
      this.spin = spin;
    }

    double getZoomAmount(){

      if (spin != null){
	try{
	  return (spin.getSpinController().getNumberFormatter().parse(((JTextField)spin.getTextWidget()).getText().trim()).doubleValue())/100;
	}
	catch(ParseException ex){
	  return -1;
	}
      }
      else
	return zoomAmount;
    }

    String getZoomAmountAsText(){
     if (spin != null){
	return ((JTextField)spin.getTextWidget()).getText();
      }
      else
	return ""+zoomAmount;
    }
  }

  class PercentZoomButton extends JRadioButton implements ItemListener, FocusListener, SpinListener{

    private Spin percentSpin;

    PercentZoomButton(String label, Spin spin){
      super(label);
      setModel(new ZoomButtonModel(spin));
      percentSpin = spin;
      addItemListener(this);
      percentSpin.getTextWidget().addFocusListener(this);
      percentSpin.addSpinListener(this);
    }

    private void selectPercent(){
      Component c = percentSpin.getTextWidget();
      if (c instanceof JTextField)
	((JTextField)c).selectAll();
    }

    @Override
    public void itemStateChanged(ItemEvent event){
		if (event.getStateChange() == event.SELECTED){
			Component c = percentSpin.getTextWidget();  // these two lines added by bbush, 2-13-2000
			if(c instanceof JTextField) {
				JTextField txtField = (JTextField)percentSpin.getTextWidget();
				if (!txtField.hasFocus()  && txtField.isDisplayable()){
					txtField.requestFocus();
					int pos = txtField.getText().length();
					txtField.setCaretPosition(pos);
				}
			}
		} else{
			Component c = percentSpin.getTextWidget();
			if (c instanceof JTextField)
				((JTextField)c).select(0, 0);
		}
	}

    @Override
    public void focusGained(FocusEvent event){
      if (!isSelected()) setSelected(true);
    }
  
    @Override
    public void focusLost(FocusEvent event){
    }

    @Override
    public void spinUp(SpinEvent event){
      if (!isSelected()) setSelected(true);
    }

    @Override
    public void spinDown(SpinEvent event){
      if (!isSelected()) setSelected(true);
    }

    void setZoomAmount(double zoomAmount){
      double newZoomAmount = zoomAmount*100; 
      if (percentSpin.getMaxValue() < newZoomAmount)
	percentSpin.setMaxValue(newZoomAmount);
      percentSpin.putValue(newZoomAmount);
    }

    @Override
    public void addKeyListener(KeyListener keyListener){
      super.addKeyListener(keyListener);
      percentSpin.getTextWidget().addKeyListener(keyListener);
    }

  }
}
