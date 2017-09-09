package com.gensym.nols.util;

import java.util.*;
import java.awt.*;
import java.io.*;
import java.text.*;

public class DecimalParser {
	
	public DecimalParser() {
		super();
	}

	public static final double parse(String NumString, String decFormatLocalString)
		throws ParseException{	
		DecimalFormat dFormat = new DecimalFormat();
		if(decFormatLocalString.equals("French")){
			DecimalFormatSymbols decSym = new DecimalFormatSymbols(Locale.FRANCE);
			decSym.setDecimalSeparator(',');
			decSym.setGroupingSeparator(' ');
			dFormat.setDecimalFormatSymbols(decSym);
		}else if(decFormatLocalString.equals("German")){
			DecimalFormatSymbols decSym = new DecimalFormatSymbols(Locale.GERMANY);
			decSym.setDecimalSeparator(',');
			decSym.setGroupingSeparator('.');
			dFormat.setDecimalFormatSymbols(decSym);
		}else if(decFormatLocalString.equals("Italian")){
			dFormat.setDecimalFormatSymbols(new DecimalFormatSymbols(Locale.ITALY));
		}					
		double data = dFormat.parse(NumString).doubleValue();
		return data;
	}

}
