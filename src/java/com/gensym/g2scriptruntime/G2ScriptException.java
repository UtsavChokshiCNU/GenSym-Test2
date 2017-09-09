package com.gensym.g2scriptruntime;

import com.gensym.util.Symbol;

public class G2ScriptException extends Exception
{
  Symbol errorSymbol = null;

  public G2ScriptException()
  {
    super();
  }

  public G2ScriptException(String message)
  {
    super(message);
  }

  public G2ScriptException(Symbol symbol, String message)
  {
    super(message);
    this.errorSymbol = symbol;
  }
}
