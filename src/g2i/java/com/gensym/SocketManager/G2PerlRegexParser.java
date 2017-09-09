package com.gensym.SocketManager;


import org.apache.oro.text.regex.*;

public class G2PerlRegexParser {

  PatternMatcher matcher = new Perl5Matcher();
  PatternCompiler compiler = new Perl5Compiler();
  Pattern pattern;
  PatternMatcherInput input;
  MatchResult result;

  int beginOffset = 0;
  int endOffset = 0;


  public G2PerlRegexParser() {
  }


  public boolean isMatched(String patternStr, String matchStr, boolean caseInSensitive, boolean isMultiline, boolean isExtended){

    try{ // get PERL REGEX for this expression-to-match
      if(!caseInSensitive && !isMultiline && !isExtended){
        pattern = compiler.compile(patternStr, Perl5Compiler.SINGLELINE_MASK);
      } else if(!caseInSensitive && !isMultiline && isExtended){
        pattern = compiler.compile(patternStr, Perl5Compiler.EXTENDED_MASK | Perl5Compiler.SINGLELINE_MASK );
      } else if(!caseInSensitive && isMultiline && !isExtended){
        pattern = compiler.compile(patternStr, Perl5Compiler.MULTILINE_MASK);
      } else if(!caseInSensitive && isMultiline && isExtended){
        pattern = compiler.compile(patternStr, Perl5Compiler.MULTILINE_MASK | Perl5Compiler.EXTENDED_MASK);
      } else if(caseInSensitive && !isMultiline && !isExtended){
        pattern = compiler.compile(patternStr, Perl5Compiler.CASE_INSENSITIVE_MASK | Perl5Compiler.SINGLELINE_MASK);
      } else if(caseInSensitive && !isMultiline && isExtended){
        pattern = compiler.compile(patternStr, Perl5Compiler.CASE_INSENSITIVE_MASK | Perl5Compiler.EXTENDED_MASK | Perl5Compiler.SINGLELINE_MASK);
      } else if(caseInSensitive && isMultiline && !isExtended){
        pattern = compiler.compile(patternStr, Perl5Compiler.CASE_INSENSITIVE_MASK | Perl5Compiler.MULTILINE_MASK);
      }else if(caseInSensitive && isMultiline && isExtended){
        pattern = compiler.compile(patternStr, Perl5Compiler.CASE_INSENSITIVE_MASK| Perl5Compiler.MULTILINE_MASK | Perl5Compiler.EXTENDED_MASK);
      }

      input = new PatternMatcherInput(matchStr);  // create a holder to pattern match against for the string-to-match
      int i=0;
      if(matcher.contains(input, pattern)) {   // loop and signal all matches
        result = matcher.getMatch();
        beginOffset = result.beginOffset(0);
        endOffset = result.endOffset(0);
        return true;
      }
    }catch(MalformedPatternException mpe){
      G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION, "This string "+patternStr+" is no good as a pattern!");
    }
    return false;
  }

  public boolean isValidPattern(String patternStr){
    try{
      compiler.compile(patternStr);  // try to get PERL REGEX for this expression-to-match
    }catch(MalformedPatternException mpe){
      G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION,"This string "+patternStr+" is no good as a pattern!");
      return false;
    }
    return true;
  }


}
