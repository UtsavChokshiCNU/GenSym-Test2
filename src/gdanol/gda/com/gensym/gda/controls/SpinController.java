package com.gensym.gda.controls;

import java.text.DecimalFormat;
import java.text.DecimalFormatSymbols;
import java.text.ParseException;


/**
Sublcass of com.gensym.widgets.SpinController. Forcibly Set decimal separator 
as point due to bug in Spin (if separator is other then point Spin fails).
if TextWidget contains nothing when spinning the default value will be set.
*/
public class SpinController extends com.gensym.widgets.SpinController {
    
	
	public SpinController() {
		setNumberFormatter(new DecimalFormat());
    	DecimalFormat format = getNumberFormatter();
    	DecimalFormatSymbols symbols = format.getDecimalFormatSymbols();
    	symbols.setDecimalSeparator('.');
    	format.setDecimalFormatSymbols(symbols);
    	format.setGroupingUsed(false);
	}

	protected String checkString(String s, boolean flag) {
		if (!s.equals("")) 
			return s;
			
		double minValue = getMinValue();
		double maxValue = getMaxValue();
		DecimalFormat numberFormatter = getNumberFormatter();
		
		if (minValue <=0 && maxValue>=0)
			return numberFormatter.format(0);
		if (minValue >0) 
			return numberFormatter.format(minValue);
		
		return numberFormatter.format(maxValue);			
	}

    public String increment(String s, boolean flag) throws ParseException {
		return super.increment(checkString(s, flag), flag);
    }


}