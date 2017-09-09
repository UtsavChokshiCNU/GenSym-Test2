package com.gensym.dispatcher;

/**
 * Noop
 */

public final class Noop extends SimpleAction
{
  private static boolean debug = false;
  
  @Override
  public String toString()
  {
    return "";
  }

  @Override
  public Object invoke(DispatchTable table) {
    if (debug)
      System.out.println("NOOP");
    return null;
  }
}
