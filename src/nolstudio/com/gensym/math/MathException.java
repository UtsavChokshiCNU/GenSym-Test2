package com.gensym.math;

public class MathException extends Exception {

  public MathException (String ErrorDetails) {
    super(ErrorDetails);
  }

  @Override
  public String toString () {
	return (""+ super.toString());
  }
  
}
