package com.gensym.g2script;

import antlr.CommonAST;

public class G2ScriptAST extends CommonAST
{
  Object value = null;
  int lineNumber = -1;

  void setValue(Object value)
  {
    this.value = value;
  }

  Object getValue()
  {
    return value;
  }
  
  void setLineNumber(int lineNumber)
  {
    this.lineNumber = lineNumber;
  }
  
  int getLineNumber()
  {
    return lineNumber;
  }

}
