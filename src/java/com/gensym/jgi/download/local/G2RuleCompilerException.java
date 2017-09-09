package com.gensym.jgi.download.local;

/**
 * Exception while compiling G2 Source.
 */
public class G2RuleCompilerException extends G2ClassCompilerException {

  public G2RuleCompilerException (String ErrorDetails) {
    super(ErrorDetails);
  }
  
  public G2RuleCompilerException (Exception compilerException, String ErrorDetails) {
    super(compilerException, ErrorDetails);
  }

 
}
