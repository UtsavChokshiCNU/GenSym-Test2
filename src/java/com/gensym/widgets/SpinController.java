/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved. 
 * 
 *   SpinController.java 
 * 
 * 
 */ 

package com.gensym.widgets;

import java.awt.Component;
import java.awt.TextComponent;
import java.io.IOException;
import java.io.NotActiveException;
import java.io.ObjectInputStream;
import java.io.Serializable;
import java.lang.ClassNotFoundException;
import java.text.DecimalFormat;
import java.text.ParseException;
import javax.swing.text.JTextComponent;

import com.gensym.message.Resource;
import com.gensym.core.util.ScientificDecimalFormat;
import com.gensym.core.util.WrappingException;

public class SpinController implements Serializable, SpinListener {

  private static final Resource i18n =
  Resource.getBundle("com.gensym.widgets.Messages");

  static final long serialVersionUID = 2L;

  private boolean wrap;

  public boolean getWrap(){
      return wrap;
  }

  public void setWrap(boolean wrap){
    this.wrap = wrap;
  }

  private double increment;
  
  public double getIncrement(){
      return increment;
  }

  public void setIncrement(double increment){
    this.increment = increment;
  }

  private double minValue;

  public double getMinValue(){
      return minValue;
  }

  public void setMinValue(double minValue){
    this.minValue = minValue;
  }

  private double maxValue;

  public double getMaxValue(){
      return maxValue;
  }

  public void setMaxValue(double maxValue){
    this.maxValue = maxValue;
  }

  public double incrementDouble(double currentValue, boolean up) {
    double newValue =
      up ? currentValue + increment : currentValue - increment;
    
    double range = maxValue - minValue;
    
    if (up && newValue > maxValue) {
      if (wrap) {
	for (; newValue > maxValue; newValue -= range)
	  ;
      } else {
	newValue = maxValue;
      }
    } else if (!up && newValue < minValue) {
      if (wrap) {
	for (; newValue < minValue; newValue += range)
	  ;
      } else {
	newValue = minValue;
      }
    }
    return newValue;
  }

  //
  // Maybe this text-based part should be in another class?
  //

  private DecimalFormat formatter = new ScientificDecimalFormat();

  public DecimalFormat getNumberFormatter(){
      return formatter;
  }

  public void setNumberFormatter(DecimalFormat numberFormatter){
    this.formatter = numberFormatter;
  }

  private boolean hasDecimalPoint(String string) {
    return (string.indexOf(formatter.getDecimalFormatSymbols().getDecimalSeparator()) != -1);
  }

  private static boolean isLong(double number) {
    return Math.round(number) == number &&
      (Long.MIN_VALUE <= number && number <= Long.MAX_VALUE);
  }

  public String increment(String newValue, boolean up)
  throws ParseException {
    double number = formatter.parse(newValue).doubleValue();

    double incrementedNumber = incrementDouble(number, up);

    // figuring out how to format the new number is the interesting
    // part of this whole operation...
    // what follows is a naive way of figuring this out.
    return makeText(incrementedNumber, !hasDecimalPoint(newValue));

  }

  private String makeText(double value, boolean tryInt) {
    String output;

    synchronized (formatter) {
      if (isLong(value) && tryInt) {
	int fractionDigits = formatter.getMaximumFractionDigits();
	formatter.setMaximumFractionDigits(0);
	output = formatter.format(value);
	formatter.setMaximumFractionDigits(fractionDigits);
      } else {
	output = formatter.format(value);
      }
    }

    return output;      
  }    

  //
  // maybe the hookup stuff could also be a separate class
  //

  private Component textWidget;

  public Component getTextWidget(){
      return textWidget;
  }

  public void setTextWidget(Component textWidget){
    this.textWidget = textWidget;
  }

  public void putValue(long value)
  throws IllegalArgumentException {
    checkValue(value);
    setNewText(makeText(value, true));
  }

  public void putValue(double value)
  throws IllegalArgumentException {
    checkValue(value);
    setNewText(makeText(value, false));
  }

  private void checkValue(double value)
  throws IllegalArgumentException {
    if (value < minValue || value > maxValue)
      throw new IllegalArgumentException(i18n.format("valueOutOfBounds",
						     new Object[]
						     {new Double(value),
							new Double(minValue),
							new Double(maxValue)}));
  }

  private String getCurrentText() {
    if (textWidget instanceof JTextComponent)
      return ((JTextComponent)textWidget).getText();
    else if (textWidget instanceof TextWidget)
      return ((TextWidget)textWidget).getText();
    else
      throw new RuntimeException("unexpectedFieldClass");
  }

  private void setNewText(String text) {
    if (textWidget instanceof JTextComponent)
      ((JTextComponent)textWidget).setText(text);
    else if (textWidget instanceof TextWidget)
      ((TextWidget)textWidget).setText(text);
  }

  private void spin(boolean up) {
    try {
      setNewText(increment(getCurrentText(), up));
    } catch (ParseException pe) {
      throw new WrappingException(pe);
    }
  }

  @Override
  public void spinUp(SpinEvent event) {
    spin(true);
  }
  
  @Override
  public void spinDown(SpinEvent event) {
    spin(false);
  }


  private void readObject(ObjectInputStream stream) throws
                   ClassNotFoundException, IOException, NotActiveException{
    stream.defaultReadObject();
    if (formatter == null)
      formatter = new ScientificDecimalFormat();
  }  
}
