package com.gensym.math;

import java.io.Serializable;

import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;

public class Utilities implements Cloneable, Serializable{
	private static double inverseLn10 = 1.0/Math.log(10);

	Utilities() {
		super();
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		return super.clone();
	}

	public static final void disp(double[] array) {
		disp(array,5);
	}

	public static final void disp(double[][] array) {
		disp(array,5);
	}

	public static final void disp(double[] array, int digits) {
		String s = "";
		String num = "";
		String spaces = "               ";
		int fieldWidth = digits + 9;
		int nspaces;
		for(int c=0;c<array.length;c++) {
			num = Utilities.formatDouble(array[c], digits);
			nspaces = fieldWidth - num.length();
		 	s += spaces.substring(1,nspaces) + num;
		}
		s = s + "\n";
		System.out.println(""+s);
	}

	public static final void disp(double[][] array, int digits) {
		String s = "";
		String num = "";
		String spaces = "               ";
		int fieldWidth = digits + 9;
		int nspaces;
		for(int r=0;r<array.length;r++)	{
			if(array[r] != null) {
		 		for(int c=0;c<array[r].length;c++) {
					num = Utilities.formatDouble(array[r][c], digits);
					nspaces = fieldWidth - num.length();
		 			s += spaces.substring(1,nspaces) + num;
				}
				s = s + "\n";
			}
		}
		System.out.println(""+s);
	}

	public static final String formatDouble(final double value, final int sigDigits) {
		// rounds to given number of significant digits, and presents in shortest format
		double val = value;
		if (Double.compare(val, 0.0) == 0) 
			return "0.0";
		
		if (Double.isNaN(val)) 
			return "NaN";
		
		if (Double.isInfinite(val)){	
			if (val < 0.0) 
				return "-Inf";
			else
				return "Inf";
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
		int magnitude = (int) Math.floor(inverseLn10*Math.log(val));
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
			while (digits.endsWith("0")){
				digits = digits.substring(0, digits.length() - 1);
			}
		}
		//System.out.println("stripped to "+digits);
		if (magnitude < -3 || magnitude >= sigDigits) {
			// represent in scientific notation
			if(digits.length() > 1) {
				formatted = sign+digits.substring(0, 1)+"."+digits.substring(1)+"e"+magnitude;
			}else{
				formatted = sign+digits+"."+"e"+magnitude;
			}
			return formatted;
		} else if (magnitude >= 0) {
			if (magnitude == sigDigits - 1) {
				formatted = sign+digits.substring(0, magnitude+1)+".";
			}else {
				formatted = sign+digits.substring(0, magnitude+1)+"."+digits.substring(magnitude+1);
			}
			return formatted;
		}else if (magnitude == -1) {
			return sign+"0."+digits;
		}else if (magnitude == -2) {
			return sign+"0.0"+digits;
		}else {
			return sign+"0.00"+digits;	  // magnitude = -3
		}
	}

	
/** Convert a data string to a data array. The double values can
	be separated by Tab, Space and comma. */
	public static void string2Data(final String S, final int nvals, final double[] dataArray) {
		int i,endIndex,sep1,sep2,sep3;
		String str = S.trim();
		String NumString;
		boolean noMoreVals = false;
		for(i=0;i<nvals;i++) {
			if(noMoreVals) {
				dataArray[i] = 0.0;
			}else {
				sep1 = str.indexOf('\u0020');
				sep2 = str.indexOf('\u0009');
				sep3 = str.indexOf(",");
				endIndex = str.length();
				if(sep1>0) {
					endIndex = Math.min(endIndex,sep1);
				}
				if(sep2>0){
					endIndex = Math.min(endIndex,sep2);
				}
				if(sep3>0){
					endIndex = Math.min(endIndex,sep3);
				}
				NumString = str.substring(0,endIndex);
				if(NumString.indexOf("NaN") != -1){
					dataArray[i] = Double.NaN;
				}else{
					dataArray[i] = Double.valueOf(NumString).doubleValue();
				}
				try {
					str = str.substring(endIndex + 1);
				} catch (StringIndexOutOfBoundsException B) {
					noMoreVals = true;
				}
				str = str.trim();
			}
		}
	}

	public static int getNumberCount(final String S) {
		int len,count=0,endIndex,sep1,sep2,sep3;
		String str = S.trim();
		while(true) {
			sep1 = str.indexOf('\u0020');
			sep2 = str.indexOf('\u0009');
			sep3 = str.indexOf(",");
			endIndex = str.length();
			if(sep1>0){
				endIndex = Math.min(endIndex,sep1);
			}
			if(sep2>0){
				endIndex = Math.min(endIndex,sep2);
			}
			if(sep3>0){
				endIndex = Math.min(endIndex,sep3);
			}
			count++;
			try {
				str = str.substring(endIndex+1);
			} catch (StringIndexOutOfBoundsException B) {
				break;
			}
			str = str.trim();
		}
		return count;
	}


	// The following special function have been moved here from Tom Dyar's Rank class 
	/** Returns the value ln[Tau(xx)] for xx > 0. Full accuracy is obtained for xx > 1. For 0 < xx < 1, the reflection formula can be used first
	* @return double
	* @param XX double
	*/
	public static final double gammln(double XX) {
		double x, tmp, ser;
		double cof[] = {76.18009173, -86.50532033, 24.01409822, -1.231739515, 0.120858003e-2, -0.536382e-5};
		int j;	
		x = XX - 1.0;
		tmp = x + 5.5;
		tmp -= (x + 0.5)*Math.log(tmp);
		ser = 1.0;
		for (j=0; j<=5; j++) {
			x += 1.0;
			ser += cof[j]/x;
		}	
		return -tmp + Math.log(2.50662827465*ser);
	}

	/**
	* Incomplete gamma function
	* @return double
	* @parameter a double
	* @parameter x double
	 * @exception com.gensym.math.MathException The exception description.
	 */
	public static final double gammp(double a, double x) throws MathException {
		double ans;
		Matrix gamser,gammcf,gln;
		if (x < 0.0 || a <= 0.0) {
			throw new MathException("Invalid arguments in routine gammp");
		}
		if (x < (a+1.0)) {
			gamser = Matlib.createMatrix();
			gln = Matlib.createMatrix();
			gser(gamser,a,x,gln);
			ans = gamser.get(0,0);
			gamser.clear();
			gln.clear();
			return ans;
		} else {
			gammcf = Matlib.createMatrix();
			gln = Matlib.createMatrix();
			gcf(gammcf,a,x,gln);
			ans = 1.0 - gammcf.get(0,0);
			gammcf.clear();
			gln.clear();
			return ans;
		}
	}

	/**
	* Returns the complementary error function erfc(x) with fractional error everywhere less than 1.2 x 10^-7
	* @return double
	* @param x double
	 */
	// THIS DOES NOT GIVE CORRECT RESULTS!  (COMPARE TO MATLAB)
	public static final double erfcc(double x) {
		double t, z, ans;
		z = Math.abs(x);
		t = 1.0/(1.0 + 0.05*z);
		ans = t*Math.exp(-z*z - 1.26551223 + t*(1.00002368 + t*(0.37409196 + t*(0.09678418 + 
				t*(-0.18628806 + t*(0.27886807 + t*(-1.13520398 + t*(1.48851587 + 
				t*(-0.82215223 + t*0.17087277)))))))));
//System.out.println("x = "+x+", erfc(x) = "+ans);
		return x >= 0.0 ? ans : 2.0 - ans;
	}

	/**
	* @return double
	* @parameter X double
	* @exception com.gensym.math.MathException The exception description.
	*/
	public static final double erff(double X) throws MathException {
		return X < 0.0 ? -gammp(0.5,X*X) : gammp(0.5,X*X);
	}

	
	public static final void gcf(Matrix gammcf, double a, double x, Matrix gln) throws MathException {
		int i, ITMAX = 100;
		double an,b,c,d,del,h, EPS = 3.0e-7, FPMIN = 1.0e-30;
		gln.redimension(1,1);
		gln.set(0,0,gammln(a));
		b = x + 1.0 - a;
		c = 1.0/FPMIN;
		d = 1.0/b;
		h = d;
		for (i=1; i<=ITMAX; i++) {
			an = -i*(i - a);
			b += 2.0;
			d = an*d + b;
			if (Math.abs(d) < FPMIN){
				d=FPMIN;
			}
			c = b + an/c;
			if (Math.abs(c) < FPMIN){
				c = FPMIN;
			}
			d = 1.0/d;
			del = d*c;
			h *= del;
			if (Math.abs(del - 1.0) < EPS) {
				break;
			}
		}
		if (i > ITMAX){
			throw new MathException("a too large, ITMAX too small in gcf");
		}
		gammcf.redimension(1,1);
		gammcf.set(0,0,Math.exp(-x + a*Math.log(x) - (gln.get(0,0)))*h);
	}

	public static final void gser(Matrix gamser, double a, double x, Matrix gln) throws MathException {
		int n, ITMAX = 100; 
		double sum,del,ap, EPS = 3.0e-7;
		gln.redimension(1,1);
		gamser.redimension(1,1);
		gln.set(0,0,gammln(a));
		if (x <= 0.0) {
			if (x < 0.0) {
				throw new MathException ("x less than 0 in routine gser");
			}
			gamser.set(0,0,0.0);
			return;
		} else {
			ap=a;
			del = sum = 1.0/a;
			for (n=1; n<=ITMAX; n++) {
				++ap;
				del *= x/ap;
				sum += del;
				if (Math.abs(del) < Math.abs(sum)*EPS) {
					gamser.set(0,0,sum*Math.exp(-x+a*Math.log(x)-(gln.get(0,0))));
					return;
				}
			}
			throw new MathException ("a too large, ITMAX too small in routine gser");
		}
	}


	/** Calculates the "continued fraction" for incomplete beta function, betaIncomplete
	* @param a double
	* @param b double
	* @param x double
	* @exception com.gensym.math.MathException The exception description.
	*/
	public static final double betacf (double a, double b, double x) throws MathException{
		double qap, qam, qab, em, tem, d;
		double bz, bm = 1.0, bp, bpp;
		double az = 1.0, am = 1.0, ap, app, aold;
		int i, m;
		int ITMAX = 100;
		double EPS = 3.0e-7;
		qab = a + b;
		qap = a + 1.0;
		qam = a - 1.0;
		bz = 1.0 - qab*x/qap;
		for (m=1; m<=ITMAX; m++) {
			em = (double) m;
			tem = em + em;
			d = em*(b - em)*x/((qam + tem)*(a + tem));		
			ap = az + d*am; // One step (the even one) of the recurrence;
			bp = bz + d*bm;
			d = -(a +em)*(qab + em)*x/((qap + tem)*(a + tem));
			app = ap + d*az; // Next step of the recurrence (the odd one);
			bpp = bp + d*bz;	
			aold = az;  // Save the old answer
			am = ap/bpp;  // Renormalize to prevent overflows
			bm = bp/bpp;
			az = app/bpp;
			bz = 1.0;
			if (Math.abs(az - aold) < (EPS*Math.abs(az))) {
				return az;
			}
		}
		throw new MathException ("a or b too big, or ITMAX too small in BETACF");
	}

	/**
	* @param A com.gensym.math.matrix.Matrix
	* @param B com.gensym.math.matrix.Matrix
	* @param X com.gensym.math.matrix.Matrix
	* @param Y com.gensym.math.matrix.Matrix
	* @exception com.gensym.math.MathException The exception description.
	*/
	public static final double betaincomplete(double a, double b, double x) throws MathException {
		double bt;
		if (x < 0.0 || x > 1.0) 
			throw new MathException ("Bad x in routine betai");
		
		if (Double.compare(x, 0.0) == 0 || Double.compare(x, 1.0) == 0) 
			bt=0.0;
		else 
			bt=Math.exp(gammln(a+b)-gammln(a)-gammln(b)+a*Math.log(x)+b*Math.log(1.0-x));
		
		if (x < (a+1.0)/(a+b+2.0))
			return bt*betacf(a,b,x)/a;
		else 
			return 1.0-bt*betacf(b,a,1.0-x)/b;
	}

	public static final String indent(int indentNumber){
		String str = "";
		for (int i=0;i<indentNumber;i++){
			str = str + "\t";
		}
		return str;
	}
}