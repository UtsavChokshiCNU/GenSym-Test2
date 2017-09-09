package com.gensym.nols.data;

public class FormulaException extends Exception {

  public FormulaException (String ErrorDetails) {
    super(ErrorDetails);
  }

  @Override
  public String toString () {
	return (""+ super.toString());
  }
  
}
