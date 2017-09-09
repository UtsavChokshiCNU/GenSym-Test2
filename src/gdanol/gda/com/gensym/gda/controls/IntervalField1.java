
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
import com.gensym.controls.LimitMode;

import com.gensym.gda.dialogs.blocks.gdaPanel;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.Vector;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.KeyStroke;
import javax.swing.JLabel;
import javax.swing.SwingConstants;

public class IntervalField1 extends JPanel implements FocusListener, AttributeEditor{
    private static final int nFields = 5;
    public static final String[] TIME_UNITS = new String[] {"weeks", "days", "hours", "minutes", "seconds"};
    protected  String[] delimeters = new String[] {"weeks", "days", ":", ":"};
    private static final int[] intervalInts = new int[] {604800, 86400, 3600, 60, 1};
    private static final int[] intervalInPredInts = new int[] {7, 24, 60, 60, 1};
    private int invalidFieldNumber = 0;
    protected static final int MAXIMUM_G2_INT = 0x1FFFFFFF;

    protected static Resource i18n = Resource.getBundle("com.gensym.gda.controls.Messages");
            
    protected G2textfield[] intervalField;
    private FieldType fieldType;
    private Vector listeners;
    private Symbol attribute;

    protected G2SpinField spin;
    protected int startIndex;
	protected boolean createTopLabels;
    public IntervalField1() {
    	startIndex=0;
		createTopLabels = false;
    	createField();
    }

    public IntervalField1(int startindex, boolean createtoplabels) {
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
        GridBagLayout gridbag = new GridBagLayout();
        GridBagConstraints c = new GridBagConstraints();
		LimitMode limitMode = new LimitMode("inclusive");
        setLayout(gridbag);

        c.fill = GridBagConstraints.HORIZONTAL;
        KeyStroke enter = KeyStroke.getKeyStroke(KeyEvent.VK_ENTER, 0);
        intervalField = new G2textfield[nFields];
        
        int nCol = 3;
         
        for (int i = startIndex; i < nFields; i++){
//            nCol = (i > 0) && (i < (nFields - 1)) ? 2 : 3;
			
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
			try{
                intervalField[i].setHorizontalAlignment(JTextField.CENTER);
            }catch(IllegalArgumentException e){} 

			
	        c.weightx = (i<=1 ? 1.0 : 0.2);
	        c.gridy = 1;
            if (i!=nFields-1) {
            	gridbag.setConstraints(intervalField[i], c);
            	add(intervalField[i]);
            } else {
            	gridbag.setConstraints(spin, c);
            	add(spin);
            }
            if (createTopLabels) {
	            c.gridy = 0;
        		JLabel l = new JLabel(AbstractAttributeEditor.localize(TIME_UNITS[i]), SwingConstants.CENTER);
            	gridbag.setConstraints(l, c);
	            add(l);
            }        
            c.weightx = 0.0;
//        	JLabel l = new JLabel(AbstractAttributeEditor.localize(TIME_UNITS[ i ]));
			if (i<delimeters.length) {
				if (createTopLabels) {
		            c.gridy = 0;
    	    		JLabel l = new JLabel(delimeters[i], SwingConstants.CENTER);
        	    	gridbag.setConstraints(l, c);
	        	  	add(l);
				}
				c.gridy=1;				
				JTextField l = new JTextField(delimeters[i]);
				l.setEnabled(false);
				l.setBorder(null);
//				l.setColumn
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
            /* suxx
            try{
                intervalField[nFields - 1].setText(fieldType.objectToString(new Double(timeVals[nFields - 1])));
            }catch (IOException e){
                
            }
            */
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
    }
    
    public void focusGained(FocusEvent e){
   		spin.setTextWidget((G2textfield)e.getSource());
        processFocusEvent(e);
    }
    
    public void focusLost(FocusEvent e){
        if(!e.isTemporary()){
            try{
                fireObjectChange(getInterval());
            }catch(G2SyntaxException exc){
                System.out.println(exc.getMessage());
                fireObjectChange(null);
            }
        }
        processFocusEvent(e);
    }
    
    public Object getInterval() throws G2SyntaxException{
        double rez = 0;
        for (int i = startIndex; i < nFields; i++){
            try{
            	String text = intervalField[i].getText();
            	if (text==null || text.equals(""))
            		text="0";
                rez += Double.parseDouble(text)*intervalInts[i];
                
                if(lowerLimitMode == null)
                    setupDefaultLimits();
                if(lowerLimitMode.isExclusive() && (rez <= lowerLimit)){
                    isValid = false;
                    throw new G2SyntaxException("Value out of range: " + rez + " <= " + lowerLimit);
                }
                if(lowerLimitMode.isInclusive() && (rez < lowerLimit)){
                    isValid = false;
                    throw new G2SyntaxException("Value out of range: " + rez + " < " + lowerLimit);
                }
                if(upperLimitMode.isExclusive() && (rez >= upperLimit)){
                    isValid = false;
                    throw new G2SyntaxException("Value out of range: " + rez + " >= " + upperLimit);
                }
                if(upperLimitMode.isInclusive() && (rez > upperLimit)){
                    isValid = false;
                    throw new G2SyntaxException("Value out of range: " + rez + " > " + upperLimit);
                }
            } catch (NumberFormatException exc) {
                invalidFieldNumber = i;
	        	isValid = false;
                throw new G2SyntaxException(AbstractAttributeEditor.localize("wrong-interval"));
            }
        }
        
        try{
        	isValid = true;
            return fieldType.stringToObject((fieldType.getType() instanceof IntegerType)?Integer.toString((int)rez):Double.toString(rez));
        }catch(G2TokenizerException e){
        	isValid = false;
            throw new G2SyntaxException(AbstractAttributeEditor.localize(e.getMessage()));        
        }catch(G2ParserException e){
            isValid = false;
            throw new G2SyntaxException(AbstractAttributeEditor.localize(e.getMessage()));
        }catch(IOException e){
            isValid = false;
            throw new G2SyntaxException(AbstractAttributeEditor.localize("wrong-interval"));
        }
        
        /*        
        if (fieldType.getType() instanceof IntegerType)
            return new Integer((int)rez);
        else
            return new Double(rez);
        */
    }
    
    
    public void requestFocus(){
        intervalField[invalidFieldNumber].requestFocus();
    }
    
    public G2textfield[] getFields(){
        return intervalField;
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
         
           public LimitMode getLowerLimitMode()
    {
        return lowerLimitMode;
    }

    public void setLowerLimitMode(LimitMode limitmode)
    {
        lowerLimitMode = limitmode;
    }

    public double getLowerLimit()
    {
        return lowerLimit;
    }

    public void setLowerLimit(double d)
    {
        lowerLimit = d;
    }

    public LimitMode getUpperLimitMode()
    {
        return upperLimitMode;
    }

    public void setUpperLimitMode(LimitMode limitmode)
    {
        upperLimitMode = limitmode;
    }

    public double getUpperLimit()
    {
        return upperLimit;
    }

    public void setUpperLimit(double d)
    {
        upperLimit = d;
    }

    
/*    protected FocusListener fieldFocusListener = new FocusListener() {
    	public void focusGained(FocusEvent e) {
    		spin.setTextWidget((G2textfield)e.getSource());
    	}
    	
    	public void focusLost(FocusEvent e) {
    	}
	};    
*/
    private void setupDefaultLimits()
    {
        lowerLimitMode = new LimitMode();
        upperLimitMode = new LimitMode();
        lowerLimit = 0.0D;
        upperLimit = 100D;
    }

    private LimitMode lowerLimitMode;
    private LimitMode upperLimitMode;
    private double lowerLimit;
    private double upperLimit;
   
    protected boolean isValid;
}