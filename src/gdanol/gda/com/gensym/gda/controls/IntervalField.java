
package com.gensym.gda.controls;

import com.gensym.controls.AttributeEditor;

import com.gensym.dlgevent.*;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.controls.FieldType;
import com.gensym.types.IntegerType;
import com.gensym.types.G2SyntaxException;
import com.gensym.types.G2TokenizerException;
import com.gensym.types.G2ParserException;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.controls.LimitMode;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.Vector;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.KeyStroke;
import javax.swing.JLabel;
import javax.swing.SwingConstants;

/**
*An editor for time interval values. Currently consists of three spin controls
*for hours, minutes and seconds. If FieldType is Float the editor allows
*entering float hours, minutes and seconds.
*/
public class IntervalField extends JPanel implements FocusListener, AttributeEditor, Boundary, ObjectChangeListener {
    private static final int nFields = 5;
    public static final String[] TIME_UNITS = new String[] {"weeks", "days", "hours", "minutes", "seconds"};
    protected  String[] delimeters = new String[] {"weeks", "days", ":", ":"};
    private static final int[] intervalInts = new int[] {604800, 86400, 3600, 60, 1};
    private static final int[] intervalInPredInts = new int[] {7, 24, 60, 60, 1};
    private int invalidFieldNumber = nFields - 1;
    protected static final int MAXIMUM_G2_INT = 0x1FFFFFFF;

    protected static Resource i18n = Resource.getBundle("com.gensym.gda.controls.Messages");
            
    protected G2textfield[] intervalField;
    private FieldType fieldType;
    private Vector listeners;
    private Symbol attribute;

    protected G2SpinField spin;
    protected int startIndex;
	protected boolean createTopLabels;
	protected Vector labels;
	
    public IntervalField() {
    	startIndex=2;
		createTopLabels = true;
    	createField();
    }

    public IntervalField(int startindex, boolean createtoplabels) {
		startIndex=startindex;
		createTopLabels = createtoplabels;
		if (createTopLabels) {
			delimeters[0]=":";
			delimeters[1]=":";
		}
		createField();
    }
    
	protected void createField() {
		isValid=true;       
		labels = new Vector();
    	GridBagLayout gridbag = new GridBagLayout();
    	GridBagConstraints c = new GridBagConstraints();
		LimitMode limitMode = new LimitMode("inclusive");
    	setMaxValueMode(limitMode);
    	setMinValueMode(limitMode);
    	setLayout(gridbag);

/*    	c.fill = GridBagConstraints.BOTH;
    	c.weighty=1.0;
    	c.weightx=1.0;
*/
    	KeyStroke enter = KeyStroke.getKeyStroke(KeyEvent.VK_ENTER, 0);
    	intervalField = new G2textfield[nFields];
    
	    int nCol = 3;
     
    	for (int i = startIndex; i < nFields; i++){
			
            intervalField[i] = new G2textfield();
	        if (i>0)
	        	nCol=2;
	        intervalField[i].setColumns(nCol);
	        intervalField[i].setLowerLimitMode(limitMode);
	        intervalField[i].setUpperLimitMode(limitMode);
	        intervalField[i].setLowerLimit(0);

            if(i==startIndex)
              setBorder(intervalField[i].getBorder());
            intervalField[i].setBorder(null);
            if (i==nFields-1) {
	        	spin = new G2SpinField(intervalField[i]);
            }
            intervalField[i].getKeymap().removeKeyStrokeBinding(enter);
            intervalField[i].addFocusListener(this);
            intervalField[i].addObjectChangeListener(this);
			try{
                intervalField[i].setHorizontalAlignment(JTextField.CENTER);
            }catch(IllegalArgumentException e){} 

			//place textfields
	        c.weightx = (i<=1 ? 1.0 : 0.2);
	        c.weighty=1.0;
	        c.fill=GridBagConstraints.BOTH;
	        c.gridy = 1;
            if (i!=nFields-1) {
            	gridbag.setConstraints(intervalField[i], c);
            	add(intervalField[i]);
            } else {
            	gridbag.setConstraints(spin, c);
            	add(spin);
            }
			//place labels
	        c.fill=GridBagConstraints.HORIZONTAL;
            c.weighty=0.0;
            c.weightx = 0.0;
            if (createTopLabels) {
	            c.gridy = 0;
        		JLabel l = new JLabel(AbstractAttributeEditor.localize(TIME_UNITS[i]), SwingConstants.CENTER);
        		labels.add(l);
            	gridbag.setConstraints(l, c);
	            add(l);
            }             

			//place delimeters
			if (i<delimeters.length) {
				if (createTopLabels) {
		            c.gridy = 0;
    	    		JLabel l = new JLabel(delimeters[i], SwingConstants.CENTER);
    	    		labels.add(l);
        	    	gridbag.setConstraints(l, c);
	        	  	add(l);
				}
				c.gridy=1;				
		        c.fill=GridBagConstraints.BOTH;
    	        c.weighty=1.0;
				JTextField l = new JTextField(delimeters[i]);
				l.setEnabled(false);
				l.setBorder(null);
    	        gridbag.setConstraints(l, c);
        	    add(l);
			}
			
        }
        
        setFieldType(new FieldType("Integer"));
        spin.setFieldType(new FieldType("Integer"));
        spin.setMinValue(0);
        spin.setIncrement(1);
        spin.setMaxValue(MAXIMUM_G2_INT);
        for (int i=startIndex;i<nFields -1;i++) {
        	intervalField[i].addKeyListener(spin);
        }
        
        setMinValue(0);
        setMaxValue(Integer.MAX_VALUE);
	}
    
    public void addObjectChangeListener(ObjectChangeListener objectchangelistener){ 
        if(listeners == null)
            listeners = new Vector();
        listeners.addElement(objectchangelistener);
    }
    
    public synchronized void removeObjectChangeListener(ObjectChangeListener objectchangelistener) {
        if(listeners == null) {
            return;
        } else {
            listeners.removeElement(objectchangelistener);
            return;
        }
    }

    public void setAttribute(Symbol atr){
        attribute = atr;
    } 
    
    public Symbol getAttribute(){
        return attribute;
    } 
        
    public void objectUpdated(ObjectUpdateEvent event) {        
        Structure values = (Structure) event.getUpdatedObject();
        try {
            double interval = ((Number)values.getAttributeValue(getAttribute())).doubleValue();
            setEnabled(true);
            double[] timeVals = new double[] {0,0,0,0,0};
            int i;
            for (i = startIndex; i < nFields - 1; i++)
                timeVals[i] = java.lang.Math.floor(interval / intervalInts[i]);
            timeVals[nFields - 1] = interval;
            for (i = nFields - 1; i > startIndex ; i--)
                timeVals[i] -= timeVals[i-1] * intervalInPredInts[i-1];
            for (i = startIndex; i < nFields - 1; i++){
                intervalField[ i ].setText(Long.toString((long)timeVals[i]));
            }
            
            if (fieldType.getType() instanceof IntegerType)
                intervalField[nFields - 1].setText(Integer.toString((int)timeVals[nFields - 1]));
            else
                intervalField[nFields - 1].setText(Double.toString(timeVals[nFields - 1]));

        } catch (NoSuchAttributeException e) {
            setEnabled(false);
        }
    }
    
    public void setFieldType(FieldType type) {

        fieldType = (type == null)? new FieldType("Integer"):type;
        for (int i = startIndex; i < nFields; i++)
            intervalField[ i ].setFieldType(fieldType);
    }

    public FieldType getFieldType() { 
        return fieldType;
    }

    public void setEnabled(boolean enabled) {
        super.setEnabled(enabled);
        for (int i = startIndex; i < nFields; i++)
            intervalField[ i ].setEnabled(enabled);
        for (int i=0; i<labels.size();i++)
        	((JLabel)labels.get(i)).setEnabled(enabled);
        spin.setEnabled(enabled);
    }
    
    public void focusGained(FocusEvent e){
   		spin.setTextWidget((G2textfield)e.getSource());
		Object source = e.getSource();
        int index = -1;
        for (int i = startIndex; i < nFields; i++){
            if (source == intervalField[i])
                index = i;
        }
        
        if (index == -1)
            return;
        double maxvalue = Math.floor(Double.parseDouble(intervalField[index].getText()) + 
                    ((getMaxValue() - getRawInterval())/intervalInts[index]));
        if (index > 0)
            maxvalue = Math.min(intervalInPredInts[index - 1] - 1, maxvalue);
        spin.setMaxValue(maxvalue);
        
        double minvalue = Math.ceil(Double.parseDouble(intervalField[index].getText()) + 
                    ((getMinValue() - getRawInterval())/intervalInts[index]));
        if (index > 0)
            minvalue = Math.max(0, minvalue);
        spin.setMinValue(minvalue);        
       
    }
    
    public void focusLost(FocusEvent e) {}
 
 
 	public void objectChanged (ObjectChangeEvent e) {
 		try {
 			fireObjectChange(getInterval());
 		} catch (G2SyntaxException gse) {
 			Trace.exception(gse);
 		}
 	}
    
    private double getRawInterval(){
        double rez = 0;
        for (int i = startIndex; i < nFields; i++){
            try{
                String text = intervalField[i].getText();
                if (text==null || text.equals(""))
                    text="0";
                rez += Double.parseDouble(text)*intervalInts[i];    
            } catch (NumberFormatException exc) {
                invalidFieldNumber = i;
                isValid = false;
                throw exc; 
            }   
        }
        return rez;
    }
    
    public Object getInterval() throws G2SyntaxException{
        double rez = getRawInterval();
        
        if(minValueMode == null)
            setupDefaultLimits();
        if(minValueMode.isExclusive() && (rez <= minValue)){
            isValid = false;
            throw new G2SyntaxException("Value out of range: " + rez + " <= " + minValue);
        }
        if(minValueMode.isInclusive() && (rez < minValue)){
            isValid = false;
            throw new G2SyntaxException("Value out of range: " + rez + " < " + minValue);
        }
        if(maxValueMode.isExclusive() && (rez >= maxValue)){
            isValid = false;
            throw new G2SyntaxException("Value out of range: " + rez + " >= " + maxValue);
        }
        if(maxValueMode.isInclusive() && (rez > maxValue)){
            isValid = false;
            throw new G2SyntaxException("Value out of range: " + rez + " > " + maxValue);
        }
        
        try{
        	isValid = true;
            return fieldType.stringToObject((fieldType.getType() instanceof IntegerType)?Integer.toString((int)rez):Double.toString(rez));
        }catch(G2TokenizerException e){
        	isValid = false;
            throw new G2SyntaxException(e.getMessage());        
        }catch(G2ParserException e){
            isValid = false;
            throw new G2SyntaxException(e.getMessage());
        }catch(IOException e){
            isValid = false;
            throw new G2SyntaxException(AbstractAttributeEditor.localize("wrong-interval"));
        }
        
    }
    
    /**
    *If there exists a field vith invalid value then this field gets the focus,
    *Othewise the first one receives it.
    */
    public void requestFocus(){
        intervalField[invalidFieldNumber].requestFocus();
    }
    
    public G2textfield[] getFields(){

        G2textfield[] fields = new G2textfield[intervalField.length-startIndex];
        for (int i=startIndex; i<intervalField.length;i++) {
        	fields[i-startIndex]=intervalField[i];
        }
        
        return fields;
    }
    
    protected void fireObjectChange(Object obj)
    {
        Vector vector;
        synchronized(this) 
        {
            if(listeners == null)
            {
                return;
            }
            vector = (Vector)listeners.clone();
        }
        ObjectChangeEvent objectchangeevent;
        if(attribute.equals(""))
            objectchangeevent = new ObjectChangeEvent(this, obj);
        else
            objectchangeevent = new ObjectChangeEvent(this, obj, attribute.toString());
        for(int i = 0; i < vector.size(); i++)
        {
            ObjectChangeListener objectchangelistener = (ObjectChangeListener)vector.elementAt(i);
            objectchangelistener.objectChanged(objectchangeevent);
        }

    }
 
 	public boolean isValid() {
 			for (int i=startIndex;i<intervalField.length; i++) {
 				if (!intervalField[i].isValid())
 					return false;
 			}
 			return isValid;
 		}
 		
    public void setValid(boolean valid) {
		for (int i=startIndex;i<intervalField.length; i++) {
 			intervalField[i].setValid(valid);
 		}
    }

         
    public LimitMode getMinValueMode() {
        return minValueMode;
    }

    public void setMinValueMode(LimitMode limitmode) {
        minValueMode = limitmode;
    }

    public double getMinValue()
    {
        return minValue;
    }

    public void setMinValue(double d)
    {
        minValue = d;
    }

    public LimitMode getMaxValueMode()
    {
        return maxValueMode;
    }

    public void setMaxValueMode(LimitMode limitmode)
    {
        maxValueMode = limitmode;
    }

    public double getMaxValue()
    {
        return maxValue;
    }

    public void setMaxValue(double d)
    {
        maxValue = d;
    }

    private void setupDefaultLimits()
    {
        minValueMode = new LimitMode();
        maxValueMode = new LimitMode();
        minValue = 0.0D;
        maxValue = 100D;
    }

    private LimitMode minValueMode;
    private LimitMode maxValueMode;
    private double minValue;
    private double maxValue;
   
    protected boolean isValid;
}