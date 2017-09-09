package com.gensym.nols.chart.line;

public class StringFormatter { 
	private static double inverseLn10 = 1.0/Math.log(10.0);

	public static String DoubleToString(final double value, final int sigDigits) {
		// rounds to given number of significant digits, and presents in shortest format
		double val = value;
		if (Double.isNaN(val)){
			return "NaN";
		}
		if (Double.isInfinite(val)){
			return "Infinite";
		}
		if (Double.compare(val, 0.0) == 0){
			return "0.0";
		}
		boolean negative;
		String sign;
		if (val < 0.0) {
			negative = true;
			sign = "-";
			val = Math.abs(val);
		} else {
			negative = false;
			sign = "";
		}
		if(val>=1000||val<0.01){
			double ord = Math.log(val)/Math.log(10.0);
			int iord = (int)Math.floor(ord);
			val = val/Math.pow(10,iord);
			String formatted = sign+DoubleToString(val, sigDigits)+"E"+iord;
			return formatted;
		}

		int magnitude = (int) Math.floor(StringFormatter.inverseLn10*Math.log(val));
		String digits = ""+(int) Math.rint(Math.pow(10.0, -magnitude + sigDigits - 1.0d)*val);
		// must correct for rounding up into a new order of magnitude
		if (digits.length() > sigDigits) {
			++magnitude;
			digits = digits.substring(0, digits.length() - 1);
		}
		//System.out.println("val = "+value+" digits = "+digits+" magnitude = "+magnitude+" negative = "+negative);
		String formatted;
		if (magnitude < 0 || magnitude >= sigDigits) {
			// strip trailing zeros
			while (digits.endsWith("0")) {
				digits = digits.substring(0, digits.length() - 1);
			}
		}
		//System.out.println("stripped to "+digits);
		if (magnitude < -3 || magnitude >= sigDigits) {
			// represent in scientific notation
			if(digits.length() > 1) {
				formatted = sign+digits.substring(0, 1)+"."+digits.substring(1)+"e"+magnitude;
			}else {
				formatted = sign+digits+"."+"e"+magnitude;
			}
			return formatted;
		} else if (magnitude >= 0) {
			if (magnitude == sigDigits - 1) {
				formatted = sign+digits.substring(0, magnitude+1)+".";
			} else {
				formatted = sign+digits.substring(0, magnitude+1)+"."+digits.substring(magnitude+1);
			}
			return formatted;
		} 
		else if (magnitude == -1) {
			return sign+"0."+digits;
		}else if (magnitude == -2) {
			return sign+"0.0"+digits;
		}else {
			return sign+"0.00"+digits;	  // magnitude = -3
		}
	}
}
