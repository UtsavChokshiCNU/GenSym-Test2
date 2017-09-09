package com.gensym.util;

import java.text.DecimalFormat;
import java.text.DecimalFormatSymbols;
import java.text.FieldPosition;

import com.gensym.util.MathUtils;

/** Uses scientific notation to ensure the maximum useful information
 * about the number will be formatted */
public class ScientificDecimalFormat extends DecimalFormat {

  /** The string that is used to indicate the beginning of
   * exponent part of the number defaults to the string "e".
   */
  public static final String DEFAULT_EXPONENT_MARKER = "e";
  private String exponentMarker = DEFAULT_EXPONENT_MARKER;
  private boolean preserveInts = false;

  public ScientificDecimalFormat() {
    super();
    setMinimumFractionDigits(1);
  }

  public ScientificDecimalFormat(String pattern) {
    super(pattern);
    setMinimumFractionDigits(1);
  }

  public ScientificDecimalFormat(String pattern,
				 DecimalFormatSymbols symbols) {
    super(pattern, symbols);
    setMinimumFractionDigits(1);
  }

  @Override
  public StringBuffer format(long x, StringBuffer buf, FieldPosition pos) {
    return format((double)x, buf, pos, true);
  }
  
  public StringBuffer format(int x, StringBuffer buf, FieldPosition pos) {
    return format((double)x, buf, pos, true);
  }
  
  /** Uses scientific notation to ensure that the maximum useful information
   * about the number can be formatted, given the values of
   * getMaximumIntegerDigits() and getMaximumFractionDigits.
   */
  @Override
  public StringBuffer format(double x, StringBuffer buf, FieldPosition pos) {
    return format(x,buf,pos,false);
  }
  
  private StringBuffer format(final double x, final StringBuffer buf, 
		  final FieldPosition pos, final boolean wasOriginallyInt)
  {
	double value = x;
    int exponent = 0;
    double absX = Math.abs(value);
    
    if (absX >= 1) {
      int maxIntegerDigits = getMaximumIntegerDigits();
      int powerOfTen = MathUtils.getIntegerPowerOfTen(absX);
      if ((powerOfTen + 1 > maxIntegerDigits) && (maxIntegerDigits >= 1)) {
	exponent = powerOfTen;
	value = value/(Math.pow(10, exponent));
      }
    } else {
      int maxFractionDigits = getMaximumFractionDigits();
      int powerOfTen = Math.abs(MathUtils.getIntegerPowerOfTen(absX));
      if (powerOfTen > maxFractionDigits) {
	exponent = - powerOfTen;
	value = value * (Math.pow(10, powerOfTen));
      }
    }
    
    // deal with small numbers here
    // System.out.println("exp = "+exponent+" wOT "+wasOriginallyInt+
    //		       " pres "+preserveInts);

    if (exponent == 0) 
      {
	if (wasOriginallyInt && preserveInts)
	  {
	    int fractionDigits = getMinimumFractionDigits();
	    setMinimumFractionDigits(0);
	    StringBuffer res = super.format((int)value, buf, pos);
	    setMinimumFractionDigits(fractionDigits);
	    return res;
	  }
	else
	  return super.format(value, buf, pos);
      } 
    else 
      {
	super.format(value, buf, pos);
	buf.append(exponentMarker);
	buf.append(exponent);
	return buf;
      }
  }      

  public void setPreserveInts(boolean preserveInts)
  {
    this.preserveInts = preserveInts;
  }

  public boolean getPreserveInts()
  {
    return preserveInts;
  }

  public static void main(String[] args) {
    ScientificDecimalFormat nf = new ScientificDecimalFormat();

    // nf.setMaximumIntegerDigits(6);
    // System.out.println(nf.format(123456));
    // System.out.println("toString: " + Double.toString(Double.MAX_VALUE));
    // nf.setMaximumFractionDigits(3);
    nf.setMaximumIntegerDigits(5);
    nf.setMinimumIntegerDigits(1);
    nf.setMaximumFractionDigits(3);
    nf.setMinimumFractionDigits(1);
    nf.setGroupingUsed(false);
    nf.setPreserveInts(false);
    System.out.println("\""+nf.format(23923.0)+"\"");
    System.out.println("\""+nf.format(23923)+"\"");
    nf.setPreserveInts(true);
    System.out.println("\""+nf.format(23923.0)+"\"");
    System.out.println("\""+nf.format(23923)+"\"");
  }
}
