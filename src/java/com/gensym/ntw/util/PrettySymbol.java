package com.gensym.ntw.util;

import com.gensym.util.Symbol;

public class PrettySymbol {

  private Symbol sym;
  private String name;

  public PrettySymbol(Symbol sym) {
    this.sym = sym;
    name = sym.prettyName();
  }

  public Symbol getSymbol() {
    return sym;
  }
  
  @Override
  public String toString() {
    return name;
  }

  @Override
  public int hashCode() {
    return sym.hashCode();
  }

  @Override
  public boolean equals(Object other) {
    return (other instanceof PrettySymbol) &&
      (sym.equals(((PrettySymbol)other).getSymbol()));
  }
}
