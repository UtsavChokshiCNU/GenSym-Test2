package com.gensym.g2scriptruntime;

import java.security.SecureRandom;
import java.util.*;

import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;

public class G2Functions {

  private static boolean debug = false;
  static double LOG10E = 0.434294481903251816668; // approximation, but do we need it any better than this?
  static double LOG2E = 1.442695040888963387; // approximation

  public static Object abs(Object num) {
    if (num instanceof Number)
      return new Double(java.lang.Math.abs(((Number) num).doubleValue()));
    throw new ArithmeticException("Argument to abs() function is not a number: " + num);
  }

  public static Object arctan(Object num) {
    if (num instanceof Number)
      return new Double(java.lang.Math.atan(((Number) num).doubleValue()));
     throw new ArithmeticException("Argument to arctan() function is not a number: " + num);
  }

  public static Object arctan(Object num1, Object num2) {
    if ((num1 instanceof Number) && (num2 instanceof Number))
      return new Double(java.lang.Math.atan2(((Number) num1).doubleValue(), ((Number) num2).doubleValue()));
    throw new ArithmeticException("At least one argument to arctan() function is not a number: " + num1 + ";" + num2);
  }

  /** Returns the average of the numbers in the array passed to it
  **/
  public static double average(double[] args) {
    double sum = 0.0;
    for (int i = 0; i < args.length; i++) {
    	sum += args[i];
    }
    return (double) (sum / (double) args.length);
  }

  /** Returns the average of the numbers in the array passed to it
  **/
  public static Object average(Object[] args) {
    double sum = 0.0;
    for (int i = 0; i < args.length; i++) {
      if (args[i] instanceof Object)
	sum += ((Number) args[i]).doubleValue();
      else // not a Number - illegal argument
	throw new ArithmeticException("At least one argument to average() function is not a number.");
    }
    return new Double((double) (sum / (double) args.length));
  }

  public static Object ceil(Object num) {
    if (num instanceof Number)
      return new Double(java.lang.Math.ceil(((Number) num).doubleValue()));
    throw new ArithmeticException("Argument to ceil() function is not a number: " + num);
  }

  public static Object cos(Object num) {
    if (num instanceof Number)
      return new Double(java.lang.Math.cos(((Number) num).doubleValue()));
    throw new ArithmeticException("Argument to cos() function is not a number: " + num);
  }

  public static Object exp(Object num) {
    if (num instanceof Number)
      return new Double(java.lang.Math.exp(((Number) num).doubleValue()));
    throw new ArithmeticException("Argument to exp() function is not a number: " + num);
  }

  public static Object expt(Object num1, Object num2) {
    if (num1 instanceof Number && num2 instanceof Number)
      return new Double(java.lang.Math.pow(((Number) num1).doubleValue(), ((Number) num2).doubleValue()));
    throw new ArithmeticException("At least one argument to expt() function is not a number: " + num1 + "; " + num2);
  }

  /**  Imitates the G2 expt() fucntion when both args are integral
  **/
  public static int pow(int x, int y) {
    return (int) java.lang.Math.pow((double) x, (double) y);
  }

  public static int floor(double x) {
    return (int) java.lang.Math.floor(x);
  }

  public static Object floor(Object num) {
    if (num instanceof Number)
      return (int) java.lang.Math.floor(((Number) num).doubleValue());
    throw new ArithmeticException("Argument to floor() method is not a number: " + num);
  }

  public static Object ln(Object num) {
    if (num instanceof Number)
      return new Double(java.lang.Math.log(((Number) num).doubleValue()));
    throw new ArithmeticException("Argument to ln() function is not a number: " + num);
  }

  /** Returns the result of log(x) base 10.
   *  Implemented as per the ieee754_log10 definition.
   *  This can be found at www.netlib.org/fdlibm/e_log10.c 
   *  (fdlibm = freely distributable math library)
  **/
  public static double log(double x) {
    // log(x) = log(e) * ln(x)
    if (x < 0.00) // log of negative number is NaN
      return Double.NaN;
    if (new Double(x).isInfinite()) // log of positive infinity is positive infinity
      return Double.POSITIVE_INFINITY;
    if (new Double(x).isNaN()) // log of NaN is the same NaN
      return x;
    return java.lang.Math.log(x) * LOG10E;
  }

  public static Object log(Object num) {
    if (num instanceof Number)
      return new Double(log(((Number) num).doubleValue()));
    throw new ArithmeticException("Argument to log() function is not a number: " + num);
  }

  /**  Returns the largest double in the given array.
  **/
  public static double max(double[] args) {
    double max = args[0];
    for (int i = 1; i < args.length; i++)
      if (args[i] > max)
	max = args[i];
    return max;
  }

  /**  Returns the largest Number in the given array.
  **/
  public static Object max(Object[] args) {
    Number max = null;
    if (args[0] instanceof Number)
      max = (Number) args[0];
    for (int i = 1; i < args.length; i++) {
      if (args[i] instanceof Number) {
	if (((Number) args[i]).doubleValue() > max.doubleValue())
	  max = (Number) args[i];
      }
      else
	throw new ArithmeticException("At least one argument to max() function is not a number: " + args[i]);
    }
    return max;
  }

  /**  Returns the smallest double in the given array.
  **/
  public static double min(double[] args) {
    double min = args[0];
    for (int i = 1; i < args.length; i++)
      if (args[i] < min)
	min = args[i];
    return min;
  }

  /**  Returns the smallest Number in the given array.
  **/
  public static Object min(Object[] args) {
    Number min = null;
    if (args[0] instanceof Number)
      min = (Number) args[0];
    for (int i = 1; i < args.length; i++)
      if (args[i] instanceof Number) {
	if (((Number) args[i]).doubleValue() < min.doubleValue())
	  min = (Number) args[i];
      }
      else
	throw new ArithmeticException("At least one argument to min() function is not a number: " + args[i]);
    return min;
  }

  /**  Returns the integral value of the quotient of the two given terms.
  **/
  public static long quotient(double dividend, double divisor) {
    return (long) java.lang.Math.round((double) (dividend/divisor));
  }

  public static Object quotient(Object dividend, Object divisor) {
    if (dividend instanceof Number && divisor instanceof Number)
      return quotient(((Number) dividend).doubleValue(), ((Number) divisor).doubleValue());
    throw new ArithmeticException("At least one argument to quotient() function is not a number: " + dividend + "; " + divisor);
  }

  /** Returns an integer (ret) in the range 0 <= ret < x
  **/
  public static int random(int x) {
    if (x < 0) 
      throw new ArithmeticException("Argument to random(int) must be positive: " + x);
    SecureRandom random = new SecureRandom();
    double rand = random.nextDouble() * x; // transpose scale to given int
    return (int) rand;
  }

  /** Returns an integer (ret) in the range x <= ret <= y
  **/
  public static int random(int x, int y) {
    if (x > y)
      throw new ArithmeticException("Second argument to random(int, int) must be greater than or equal to first argument: " + x + ", " + y);
    SecureRandom random = new SecureRandom();
    double rand = random.nextDouble() * (y - x);
    return (int) (rand + x);
  }

  /** Returns a double (ret) in the range 0.0 <= ret < x
  **/
  public static double random(double x) {
    if (x < 0.00)
      throw new ArithmeticException("Argument to random(double) must be positive: " + x);
    SecureRandom random = new SecureRandom();
    return random.nextDouble() * x;
  }

  /** Returns a double (ret) in the range x <= ret < y
  **/
  public static double random(double x, double y) {
    if (x > y) 
      throw new ArithmeticException("Second argument to random(double, double) must greater than or equal to first argument: " + x + ", " + y);
    SecureRandom random = new SecureRandom();
    double rand = random.nextDouble() * (y - x);
    return (double) (rand + x);
  }

  /** Returns a double (ret) in the range 0.0 <= ret < x
  **/
  public static Object random(Object x) {
    if (x instanceof Number)
      return new Double(random(((Number) x).doubleValue()));
    throw new IllegalArgumentException("Argument to random(Object) is not a Number: " + x);
  }

  /** Returns a double (ret) in the range x <= ret < y
  **/
  public static Object random(Object x, Object y) {
    if (x instanceof Number && y instanceof Number)
      return new Double(random(((Number) x).doubleValue(), ((Number) y).doubleValue()));
    throw new IllegalArgumentException("At least one argument to random(Object, Object) is not a Number: " + x + ", " + y);
  }

  public static Object remainder(Object dividend, Object divisor) {
    if (dividend instanceof Number && divisor instanceof Number)
      return new Double(java.lang.Math.IEEEremainder(((Number) dividend).doubleValue(), ((Number) divisor).doubleValue()));
    throw new ArithmeticException("At least one argument to remainder() function is not a number: " + dividend + "; " + divisor);
  }

  public static Object round(Object num) {
    if (num instanceof Number)
      return java.lang.Math.round(((Number) num).doubleValue());
    throw new ArithmeticException("Argument to round() function is not a number: " + num);
  }

  public static Object sin(Object num) {
    if (num instanceof Number)
      return java.lang.Math.sin(((Number) num).doubleValue());
    throw new ArithmeticException("Argument to sin() function is not a number: " + num);
  }

  public static Object sqrt(Object num) {
    if (num instanceof Number)
      return java.lang.Math.sqrt(((Number) num).doubleValue());
    throw new ArithmeticException("Argument to sqrt() function is not a number: " + num);
  }

  public static Object tan(Object num) {
    if (num instanceof Number)
      return java.lang.Math.tan(((Number) num).doubleValue());
    throw new ArithmeticException("Argument to tan() function is not a number: " + num);
  }

  /** Returns the truncated form of the decimal portion of the given double.
   *  Always truncates towards zero
  **/ 
  public static int truncate(double x) {
    return (int) x;
  }

  public static Object truncate(Object num) {
    if (num instanceof Number)
      return truncate(((Number) num).doubleValue());
    throw new ArithmeticException("Argument to truncate() function is not a number: " + num);
  }

  /** Returns the quantity equivalent of the boolean value passed to it.
   *  @param truthValue the truth value to evaluate
   *  @return the numeric equivalent of the truth value (1.0 for true, 0.0 for false)
  **/
  public static double quantity(boolean tv) {
    return (tv? 1.0 : 0.0);
  }

  public static double quantity(final String text) {
	String textLocal = text;
    if (!textBeginsWithQuantity(textLocal) && textLocal.charAt(0) != '-') { // invalid string
      throw new ArithmeticException("Text passed to quantity() function does not begin with a numeric: " + textLocal);
    }
    String copy = textLocal;
    
    if (debug) 
      System.out.println("quantity(" + textLocal + ")");
    Vector digits = new Vector();
    boolean negative = false;
    int digitCount = 0;
    if (textLocal.charAt(0) == '-') {
      negative = true;
      textLocal = textLocal.substring(1);
      digitCount++;
    }
    double result = 0.0;
    int floatPos = 0;
    boolean endOfNumberReached = false;
    while (!textLocal.equals("") && !endOfNumberReached) {
      //      if (debug)
      //System.out.println("text = " + text);
      //      int temp = Character.getNumericValue(text.charAt(0));
      //      if (temp < 0.0) // not a digit 
      //        break;
      //      digits.addElement(new Integer(temp));
      if (textLocal.charAt(0) == '.') {
	if (floatPos == 0) {
	  floatPos = digitCount;
	  textLocal = textLocal.substring(1);
	  digitCount++; // include this digit in the number
	}
	else endOfNumberReached = true; // second '.' char - end of number
      }
      if (textBeginsWithQuantity(textLocal))
	digitCount++; // include this digit in the number
      else 
	break;
      textLocal = textLocal.substring(1);
    }
    if (debug) 
      System.out.println("Parsed: " + (negative ? "-" : "") + "(floatPos = " + floatPos + "; digitCount = " + digitCount + ")");
    return new Double(copy.substring(0, digitCount)).doubleValue();
  }

  public static double quantity(Object x) {
    if (x instanceof String)
      return quantity((String) x);
    if (x instanceof Boolean)
      return quantity(((Boolean) x).booleanValue());
    throw new IllegalArgumentException("Object passed to quantity() must be either a string or a boolean: " + x);
  }

  /** Returns the string with every word capitalized.
  **/
  public static String capitalizeWords(String text) {
    char[] chars = new char[text.length()];
    char previousChar, curChar = text.charAt(0);
    if (!Character.isWhitespace(curChar)) // if the first char is not white space, then capitalize it
      chars[0] = Character.toUpperCase(curChar);
    else 
      chars[0] = curChar;
    for (int i = 1; i < chars.length; i++) {
      previousChar = curChar;
      curChar = text.charAt(i);
      if ((!Character.isWhitespace(curChar)) && (Character.isWhitespace(previousChar))) // this is the beginning of a word
	chars[i] = Character.toUpperCase(curChar);
      else 
	chars[i] = curChar;
    }
    return new String(chars); 
  }

  public static String capitalizeWords(Object text) {
    if (text instanceof String)
      return capitalizeWords((String) text);
    throw new IllegalArgumentException("Argument to capitalizeWords() function is not a string: " + text);
  }

  public static String getFromText(Object text, Object start, Object end) {
    if (start instanceof Number && end instanceof Number) {
      if (text instanceof String) {
	int from = ((Number) start).intValue() - 1; // G2 indexes strings from 1, not zero
	int to = ((Number) end).intValue() - 1;
	return ((String) text).substring(from, to);
      }
      throw new IllegalArgumentException("Object passed to getFromText() function is not a string: " + text);
    }
    throw new IllegalArgumentException("At least one argument to getFromText() function is not a number: " + 
				       start + "; " + end);
  }

  /**  Returns a string consisting of the second argument with the first argument
   *   inserted at the position indicated by the thrid argument.
   *   @param insText the text to be inserted into the text string
   *   @param text the text to insert the insText into
   *   @param position the index at which to insert the text (starting from 1, NOT 0)
  **/
  public static String insertInText(String insText, String text, int position) {
    return text.substring(0,position - 1) + insText + text.substring(position - 1, text.length());
  }

  public static String insertInText(Object insText, Object text, Object position) {
    if (position instanceof Number) {
      if (insText instanceof String && text instanceof String) {
	return insertInText((String) insText, (String) text, ((Number) position).intValue());
      }
      throw new IllegalArgumentException("At least one object passed to insertInText() function is not a string: " +
					 insText + "; " + text);
    }
    throw new IllegalArgumentException("Numeric argument to insertInText() function is not a number: " + position);
  }

  /**  Tests if the first argument is a substring of the second.
   *   This method is not case-sensitive.
   *   @param sub the substring to search for
   *   @param full the full string to search in
   *   @returns true if sub is a substring of full, false otherwise
  **/
  public static boolean isContainedInText(String sub, String full) {
    return (full.toLowerCase().indexOf(sub.toLowerCase()) != -1);
  }

  public static boolean isContainedInText(Object sub, Object full) {
    if (sub instanceof String && full instanceof String)
      return isContainedInText((String) sub, (String) full);
    throw new IllegalArgumentException("At least one object passed to isContainedInString() function is not a string: " +
				       sub + "; " + full);
  }

  public static int lengthOfText(Object text) {
    if (text instanceof String)
      return ((String) text).length();
    throw new IllegalArgumentException("Argument to lengthOfText() function is not a string: " + text);
  }

  public static String lowerCaseText(Object text) {
    if (text instanceof String)
      return ((String) text).toLowerCase();
    throw new IllegalArgumentException("Argument to lowerCaseText() function is not a string: " + text);
  }

  /** Returns the initialString with the chars between the two
   *  other args removed.
   *  @param initialString the string to manipulate
   *  @param start the first char to remove (one relative)
   *  @param end the last char to remove (one relative)
  **/
  public static String omitFromText(String initialString, int start, int end) {
    return initialString.substring(0, start - 1) + initialString.substring(end - 1, initialString.length());
  }

  public static String omitFromText(Object initialString, Object start, Object end) {
    if (initialString instanceof String) {
      if (start instanceof Number && end instanceof Number)
	return omitFromText((String) initialString, ((Number) start).intValue(), ((Number) end).intValue());
      throw new IllegalArgumentException("At least one numeric argument to omitFromText() function is not a number: " +
					 start + "; " + end);
    }
    throw new IllegalArgumentException("First argument to omitFromText() function is not a string: " + initialString);
  }

  /** Returns the position of subString within fullString.
   *  @param subString the substring to search for
   *  @param fullString the string to search in
   *  @returns the starting position of the subString within the fullString (one-relative - zero if not found)
  **/
  public static int positionOfText(String subString, String fullString) {
    return fullString.indexOf(subString) + 1;
  }

  public static int positionOfText(Object subString, Object fullString) {
    if (subString instanceof String && fullString instanceof String)
      return positionOfText((String) subString, (String) fullString);
    throw new IllegalArgumentException("At least one argument to positionOfText() function is not a string: " +
					subString + "; " + fullString);
  }

  /** Replaces the text between start and end in initialString with newString and returns the resulting String.
   *  @param newString the string to insert
   *  @param initialString the string to work with
   *  @param start the (one-relative) index
   *  @param end the (one-relative) index
  **/
  public static String replaceInText(String newString, String initialString, int start, int end) {
    return initialString.substring(0, start - 1) +
      newString + initialString.substring(end - 1, initialString.length());
  }

  public static String replaceInText(Object newString, Object initialString, Object start, Object end) {
    if (start instanceof Number && end instanceof Number) {
      if (newString instanceof String && initialString instanceof String) {
	return replaceInText((String) newString, 
			     (String) initialString, 
			     ((Number) start).intValue(),
			     ((Number) end).intValue());
      }
      throw new IllegalArgumentException("At least one textual argument to replaceInText() function is not a string: " +
					 newString + "; " + initialString);
    }
    throw new IllegalArgumentException("At least one numeric argument to replaceInText() function is not a number: " +
				       start + "; " + end);
  }

  /** Returns true if text begins with a numeric character, false otherwise
  **/
  public static boolean textBeginsWithQuantity(String text) {
    return Character.isDigit(text.charAt(0));
  }

  public static boolean textBeginsWithQuantity(Object text) {
    if (text instanceof String)
      return textBeginsWithQuantity((String) text);
    throw new IllegalArgumentException("Argument to textBeginsWithQuanity() function is not a string: " + text);
  }

  public static String upperCaseText(Object text) {
    if (text instanceof String)
      return ((String) text).toUpperCase();
    throw new IllegalArgumentException("Argument to upperCaseText() function is not a string: " + text);
  }

  /** Removes the element at position pos (zero-relative) and replaces it with item
   *  @param seq the sequence to start from
   *  @param pos the (zero-relative) index of the element to replace
   *  @param item the item to replace the element with
  **/
  public static Sequence changeElement(Sequence seq, int pos, Object item) {
    Sequence newSeq = new Sequence();
    newSeq.concatenate(seq);
    newSeq.removeElementAt(pos);
    newSeq.insertElementAt(item, pos);
    return newSeq;
  }

  public static Sequence changeElement(Object seq, Object pos, Object item) {
    if (seq instanceof Sequence) {
      if (pos instanceof Number) {
	return changeElement((Sequence) seq, ((Number) pos).intValue(), item);
      }
      throw new IllegalArgumentException("Integral argument to changeElement() function is not a number: " + pos);
    }
    throw new IllegalArgumentException("Sequence argument to changeElement() function is not a sequence: " + seq);
  }

  /** Concatenates the given sequences to the end of the given sequence and returns it.
   *  @param seq the sequence to work with
   *  @param seqs the sequences to concatenate
   *  @returns a new Sequence with the given sequences concatenates to the end
  **/
  public static Sequence concatenate(Sequence[] seqs) {
    Sequence newSeq = new Sequence();
    newSeq.concatenate(seqs[0]);
    for (int i = 1; i < seqs.length; i++)
      newSeq.concatenate(seqs[i]);
    return newSeq;
  }

  public static Sequence concatenate(Object[] seqs) {
    for (int i = 0; i < seqs.length; i++)
      if (!(seqs[i] instanceof Sequence))
	throw new IllegalArgumentException("At least one of the objects passed to concatenate() function is not a sequence " + seqs[i]);
    return concatenate((Sequence[]) seqs);
  }

  /** Inserts the given object at the beginning of the sequence and returns it.
   *  @param seq the sequence to work with
   *  @param item the object to insert
   *  @returns a new Sequence with the item inserted at the beginning
  **/
  public static Sequence insertAtBeginning(Sequence seq, Object item) {
    Sequence newSeq = new Sequence();
    newSeq.addElement(item);
    newSeq.concatenate(seq);
    return newSeq;
  }

  public static Sequence insertAtBeginning(Object seq, Object item) {
    if (seq instanceof Sequence)
      return insertAtBeginning((Sequence) seq, item);
    throw new IllegalArgumentException("First argument to insertAtBeginning() function is not a sequence: " + seq);
  }

  /** Inserts the given object at the end of the sequence and returns it.
   *  @param seq the sequence to work with
   *  @param item the object to insert
   *  @returns a new Sequence with the item inserted at the end
  **/
  public static Sequence insertAtEnd(Sequence seq, Object item) {
    Sequence newSeq = new Sequence();
    newSeq.concatenate(seq);
    newSeq.addElement(item);
    return newSeq;
  }

  public static Sequence insertAtEnd(Object seq, Object item) {
    if (seq instanceof Sequence)
      return insertAtEnd((Sequence) seq, item);
    throw new IllegalArgumentException("First argument to insertAtEnd() function is not a sequence: " + seq);
  }

  /** Returns a new sequence with the second argument inserted after the first occurence of the third argument
   *  @param seq the sequence to work with
   *  @param item the object to insert
   *  @param target the object to insert the item after
   *  @returns a new sequence with the item inserted after the first occurence of the target.
   *  Will return null if the target is not contained within the given sequence.
  **/  
  public static Sequence insertAfter(Sequence seq, Object item, Object target) {
    Sequence newSeq = new Sequence();
    newSeq.concatenate(seq);
    int position = newSeq.indexOf(target); // find first occurence of target
    if (position == -1) {
    	return null; // target is not within given sequence
    }
    newSeq.insertElementAt(item, position + 1); // insert item after target position
    return newSeq;
  }

  public static Sequence insertAfter(Object seq, Object item, Object target) {
    if (seq instanceof Sequence)
      return insertAfter((Sequence) seq, item, target);
    throw new IllegalArgumentException("First argument to insertAfter() function is not a sequence: " + seq);
  }

  /** Returns a new sequence with the third argument inserted before the given index
   *  @param seq the sequence to work with
   *  @param index the position to insert the element before
   *  @param item the object to insert
   *  @returns a new sequence with the item inserted before the given index.
   *  Will return null if the index is out of range (index <  0 OR index > n - 1).
  **/  
  public static Sequence insertBeforeElement(Sequence seq, int index, Object item) {
    Sequence newSeq = new Sequence();
    newSeq.concatenate(seq);
    if ((index < -1) || (index > newSeq.size())) 
      throw new ArrayIndexOutOfBoundsException("Cannot insert before element no. " + index);
    newSeq.insertElementAt(item, index); // insert item at target position
    return newSeq;
  }

  public static Sequence insertBeforeElement(Object seq, Object index, Object item) {
    if (seq instanceof Sequence) {
      if (index instanceof Number)
	return insertBeforeElement((Sequence) seq, ((Number) index).intValue(), item);
      throw new IllegalArgumentException("Second argument to insertBeforeElement() function is not a number: " + index);
    }
    throw new IllegalArgumentException("First argument to insertBeforeElement() function is not a sequence: " + seq);
  }

  /** Returns a new sequence with the third argument inserted after the given index
   *  @param seq the sequence to work with
   *  @param index the position to insert the element after
   *  @param item the object to insert
   *  @returns a new sequence with the item inserted after the given index.
   *  Will return null if the index is out of range (index <  -1 OR index > n - 1).
  **/
  public static Sequence insertAfterElement(Sequence seq, int index, Object item) {
    Sequence newSeq = new Sequence();
    newSeq.concatenate(seq);
    if ((index < -1) || (index > newSeq.size()))
      throw new ArrayIndexOutOfBoundsException("Cannot insert before element no. " + index);
    newSeq.insertElementAt(item, index + 1); // insert item at target position
    return newSeq;
  }

  public static Sequence insertAfterElement(Object seq, Object index, Object item) {
    if (seq instanceof Sequence) {
      if (index instanceof Number)
	return insertAfterElement((Sequence) seq, ((Number) index).intValue(), item);
      throw new IllegalArgumentException("Second argument to insertAfterElement() function is not a number: " + index);
    }
    throw new IllegalArgumentException("First argument to insertAfterElement() function is not a sequence: " + seq);
  }

  /** Returns a new sequence with the item at the given index removed
   *  @param seq the sequence to work with
   *  @param index the (zero-relative) position of the element to remove
   *  @returns a new sequence with the element at the given index removed
  **/
  public static Sequence remove(Sequence seq, int index) {
    Sequence newSeq = new Sequence();
    newSeq.concatenate(seq);
    if ((index < 0) || (index >= newSeq.size()))
      throw new ArrayIndexOutOfBoundsException("Cannot remove element no. " + index);
    newSeq.removeElementAt(index);
    return newSeq;
  }

  public static Sequence remove(Object seq, Object index) {
    if (seq instanceof Sequence) {
      if (index instanceof Number)
	return remove((Sequence) seq, ((Number) index).intValue());
      throw new IllegalArgumentException("Second argument to remove() function is not a number: " + index);
    }
    throw new IllegalArgumentException("First argument to remove() function is not a sequence: " + seq);    
  }

  /** Returns a new sequence containing only the items between the given indices
   *  @param seq the sequence to work with
   *  @param start the (zero-relative) position of the first element to include
   *  @param end the (zero-relative) position of the last element to include
   *  @returns a new sequence containing only the items between the given indices
  **/
  public static Sequence portion(Sequence seq, int start, int end) {
    Sequence newSeq = new Sequence();
    if ((start < 0) || (start > seq.size()))
      throw new ArrayIndexOutOfBoundsException("Cannot access element no. " + start);
    if ((end < 0) || (end > seq.size()))
      throw new ArrayIndexOutOfBoundsException("Cannot access element no. " + end);
    if (start > end) {
    	return newSeq;
    }
    for (int i = start; i <= end; i++) 
      newSeq.addElement(seq.elementAt(i));
    return newSeq;
  }

  public static Sequence portion(Object seq, Object start, Object end) {
    if (seq instanceof Sequence) {
      if (start instanceof Number && end instanceof Number)
	return portion((Sequence) seq, ((Number) start).intValue(), ((Number) end).intValue());
      throw new IllegalArgumentException("At least one integral argument to portion() is not a number: " + 
					 start + "; " + end);
    }
    throw new IllegalArgumentException("First argument to portion() is not a sequence: " + seq);
  }

  /** Returns a new sequence containing the given objects
   *  @param objects the array of objects to include in the sequence
   *  @returns a new sequence containing the given objects
  **/
  public static Sequence sequence(Object[] objects) {
    Sequence newSeq = new Sequence(objects.length);
    for (int i = 0; i < objects.length; i++)
      newSeq.addElement(objects[i]);
    return newSeq;
  }

  /** Returns a new structure with the value of the given attribute replaced with the given value.
   *  If the given attribute is not part of the given structure, the attribute will be added to the new structure.
   *  @param struct the structure to work with
   *  @param attributeName the name of the attribute whose value to change
   *  @param value the new value of the attribute
   *  @returns a new structure with the value of the given attribute replaced with the given value
  **/
  public static Structure changeAttribute(Structure struct, Symbol attributeName, Object value) {
    Structure newStruct = new Structure();
    java.util.Enumeration enumAtts = struct.getAttributeNames();
    boolean attFound = false; // set to true if we find the required attribute
    while (enumAtts.hasMoreElements()) {
      Symbol attName = (Symbol) enumAtts.nextElement();
      Object attValue = null;
      if (attName.toString().equalsIgnoreCase(attributeName.toString())) { // this is the one we want to replace
	attFound = true;
	attValue = value;
      }
      else {
	try {
	  attValue = struct.getAttributeValue(attName);
	} catch (com.gensym.util.NoSuchAttributeException nsae) {} // will never happen
      }
      newStruct.addAttribute(attName, attValue);
    }
    if (!attFound)
      newStruct.addAttribute(attributeName, value);
    return newStruct;
  }

  /** Returns a new structure with the value of the given attribute replaced with the given value.
   *  If the given attribute is not part of the given structure, the attribute will be added to the new structure.
   *  @param struct the structure to work with
   *  @param attributeName the name of the attribute whose value to change
   *  @param value the new value of the attribute
   *  @returns a new structure with the value of the given attribute replaced with the given value
  **/
  public static Structure changeAttribute(Object struct, Object attributeName, Object value) {
    if (struct instanceof Structure) {
      if (attributeName instanceof Symbol)
	return changeAttribute((Structure) struct, (Symbol) attributeName, value);
      throw new IllegalArgumentException("Second argument to changeAttribute() function is not a Symbol: " + attributeName);
    }
    throw new IllegalArgumentException("First argument to changeAttribute() fucntion is not a Structure: " + struct);
  }


  /** Returns a new structure with the given attribute removed (if found).
   *  @param struct the structure to work with
   *  @param attributeName the name of attribute to remove
   *  @returns a new structure with the given attribute removed (if found).
  **/
  public static Structure removeAttribute(Structure struct, Symbol attributeName) {
    Structure newStruct = new Structure();
    java.util.Enumeration enumAtts = struct.getAttributeNames();
    while (enumAtts.hasMoreElements()) {
      Symbol attName = (Symbol) enumAtts.nextElement();
      if (!attName.toString().equalsIgnoreCase(attributeName.toString())) { // this is the one we want to replace
	try {
	  newStruct.addAttribute(attName, struct.getAttributeValue(attName));
	} catch (com.gensym.util.NoSuchAttributeException nsae) {} // will never happen
      }
    }
    return newStruct;
  }

  /** Returns a new structure with the given attribute removed (if found).
   *  @param struct the structure to work with
   *  @param attributeName the name of attribute to remove
   *  @returns a new structure with the given attribute removed (if found).
  **/
  public static Structure removeAttribute(Object struct, Object attributeName) {
    if (struct instanceof Structure) {
      if (attributeName instanceof Symbol)
	return removeAttribute((Structure) struct, (Symbol) attributeName);
      throw new IllegalArgumentException("Second argument to removeAttribute() function is not a symbol: " + attributeName);
    }
    throw new IllegalArgumentException("First argument to removeAttribute() function is not a structure : " + struct);
  }

  public static Symbol symbol(Object text) {
    if (text instanceof String)
      return Symbol.intern((String) text);
    throw new IllegalArgumentException("Argument to symbol() function is not a String: " + text);
  } 

  public static int year(int time) {
    System.out.println("Year of " + time);
    Date date = new Date((long) time);
    System.out.println("Year of " + date);
    return date.getYear();
  }

  public static int month(int time) {
    System.out.println("Month of " + time);
    Date date = new Date((long) time);
    return date.getMonth();
  }

  public static int dayOfTheMonth(int time) {
    Date date = new Date((long) time);
    return date.getDay();
  }

  public static Symbol dayOfTheWeek(int time) {
    Date date = new Date((long) time);
    switch (date.getDay()) { 
    case 0: return Symbol.intern("Sunday");
    case 1: return Symbol.intern("Monday");
    case 2: return Symbol.intern("Tuesday");
    case 3: return Symbol.intern("Wednesday");
    case 4: return Symbol.intern("Thursday");
    case 5: return Symbol.intern("Friday");
    case 6: return Symbol.intern("Saturday");
    default:
    }
    throw new IllegalArgumentException("Argument to dayOfTheWeek() function is not a valid time: " + time);
  }

  public static int minute(int time) {
    Date date = new Date((long) time);
    return date.getMinutes();
  }

  public static int hour(int time) {
    Date date = new Date((long) time);
    return date.getHours();
  }

  public static int second(int time) {
    Date date = new Date((long) time);
    return date.getSeconds();
  }

  public static int time(int year, int month, int day, int hour, int minute, int second) {
    Date date = new Date(year, month, day, hour, minute, second);
    return (int) date.getTime();
  }

}
