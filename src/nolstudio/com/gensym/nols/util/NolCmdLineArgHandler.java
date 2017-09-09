package com.gensym.nols.util;

/**
 * A class for parsing command line arguments passed to a
 * java application. By default, an exact match is attempted.
 * This can optionally be made into a fuzzy match (user has
 * typed in sufficient characters to uniquely identify the
 * option or switch).
 *
 * @version 1.1 07/24/97
 * @author  vkp
 */

public class NolCmdLineArgHandler {
  private String[] args, allowedKeys;
  private boolean allowFuzzyMatches;
  private static java.io.PrintStream o = System.out;


  /**
   * Constructs a new default CmdLineArgHandler
   * @param args the arguments to the java application
   */
  public NolCmdLineArgHandler (String[] args) {
    this (args, null, false);
  }

  /**
   * Constructs a CmdLineArgHandler
   * @param args the arguments to the java application
   * @param fullArgSet the set of all possible options/switches. This may be null
   * @param allowFuzzyMatches whether or not to perform fuzzy matches
   */
  public NolCmdLineArgHandler (String[] args, String[] fullArgSet, boolean allowFuzzyMatches) {
    this.args = args;
    this.allowedKeys = fullArgSet;
    this.allowFuzzyMatches = allowFuzzyMatches;
  }

  /**
   * Returns the value for the option from the command line
   * @param option the option being queried
   * @return A string as the option value or null if the option was not specified
   */
  // No default value needed because the return is tightly typed.
  public String getOptionValue (String option) {
    for (int i=0; i<args.length; i++)
      if (fequals (option, args[i]) && (i+1 < args.length))
	return args[i+1];
    return null;
  }

  /**
   * Returns an array of values for an option on the command-line
   */
  public String[] getOptionValues (String option) {
    for (int i=0; i<args.length; i++) {
      if (fequals (option, args[i])) {
	int nextOptionIndex = i+1;
	for (nextOptionIndex = i+1; nextOptionIndex<args.length; nextOptionIndex++) {
	  if (args[nextOptionIndex].startsWith ("-", 0) ||
	      args[nextOptionIndex].startsWith ("+", 0))
	    break;
	}
	int numOptionValues = nextOptionIndex - (i + 1);
	String[] values = new String [numOptionValues];
	System.arraycopy (args, i+1, values, 0, numOptionValues);
	return values;
      }
    }
    return null;
  }

  /**
   *
   */
  public long getOptionLong (String option, long defaultValue)
  throws NumberFormatException {
    String valueString = getOptionValue(option);
    if (valueString == null)
      return defaultValue;
    else
      return Long.parseLong(valueString);
  }

  /**
   * Indicates whether the switch was specified on the command line
   * @param zwitch the switch being queried
   * @return A boolean indicating the switch status
   */
  public boolean getSwitchValue (String zwitch) {
    for (int i=0; i<args.length; i++)
      if (fequals (zwitch, args[i]))
	return true;
    return false;
  }
  
  private boolean fequals (String optionA, String optionB) {
    if (!allowFuzzyMatches)
      return optionA.equals (optionB);
    int optALength = optionA.length ();
    int optBLength = optionB.length ();
    if (optALength < optBLength)
      return false;
    if (!optionB.equals (optionA.substring (0, optBLength)))
      return false;
    for (int i=0; i<allowedKeys.length; i++)
      if ((!optionA.equals (allowedKeys[i])) &&
	  (allowedKeys[i].length () >= optBLength) &&
	  (optionB.equals (allowedKeys[i].substring (0, optBLength))))
	return false;
    return true;
  }
}



