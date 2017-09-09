package com.gensym.jgi.download.local;

/**
 * Exception while compiling G2 Source.
 */
public class G2ClassCompilerException extends RuntimeException {

  Exception compilerException = null;

  public G2ClassCompilerException (String ErrorDetails) {
    super(ErrorDetails);
  }
  
  public G2ClassCompilerException (Exception compilerException, String ErrorDetails) {
    super(ErrorDetails);
    this.compilerException = compilerException;
  }

  @Override
  public String toString() {
    return ("The G2 source compiler reported the following while compiling a G2 class: \n" 
            + super.toString() +
	     (compilerException == null ? "." : ".Exception was " + compilerException.toString()));
  }
  
}
