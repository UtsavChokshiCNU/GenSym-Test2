package com.gensym.g2script;

import java.lang.reflect.Field;

public class ReservedSymbolManager implements G2ScriptTokenTypes
{

  private static class LazyReservedSymbolManagerHolder {
    private static final ReservedSymbolManager INSTANCE = new ReservedSymbolManager();
  }
  
  public static int getTokenTypeIfAny(final String string)
  {
    ReservedSymbolManager rsm = LazyReservedSymbolManagerHolder.INSTANCE;
    try 
      {
	Field field = rsm.getClass().getField(string.replace('-','_'));
	return field.getInt(rsm);
      }
    catch (Exception e)
      {
	// e.printStackTrace();
	return -1;
      }
  }
}
