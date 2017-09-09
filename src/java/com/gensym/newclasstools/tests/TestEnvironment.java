package com.gensym.newclasstools.tests;

import com.gensym.denali.eval.RuntimeEnvironment;
import com.gensym.denali.eval.CompileEnvironment;
import com.gensym.denali.eval.CompilerException;
import com.gensym.denali.eval.SettingException;
import com.gensym.denali.eval.Expr; // for UnboundVariableException

public class TestEnvironment implements RuntimeEnvironment, CompileEnvironment
{

  Integer intvar = new Integer(17);
  Integer integervar = new Integer(23);
  
  public boolean isDefined(String var) {

    if (var.equals("intvar")) return true;
    if (var.equals("integervar")) return true;
    return false;
  }

  public Class getVariableType(String var) {
    if (var.equals("intvar")) return Integer.TYPE;
    if (var.equals("integervar")) return Integer.class;
    return null;
  }

  public Object getValue(String var) throws Expr.UnboundVariableException {
    if (var.equals("intvar")) {System.out.println("getvalue got intvar value of " + intvar); return intvar;}
    if (var.equals("integervar")) {System.out.println("getvalue got integervar value of " + integervar); return integervar;}
    throw new Expr.UnboundVariableException("No variable named " + var);
  }

  public void setValue(String var, Object newValue) throws SettingException {
    System.out.println("setValue called; trying to set " + var + " to " + newValue);
    if (var.equals("intvar")) {intvar = (Integer)newValue; return;}
    if (var.equals("integervar")) {integervar = (Integer)newValue; return;}
    throw new SettingException("No variable named " + var);
  }
}


