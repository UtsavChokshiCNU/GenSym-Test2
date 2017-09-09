package com.gensym.jgi;

/**
 * The details of an RPC Definition.
 *
 * @version     1.00, 25-April-1997
 * @author      M.D.Gribble
 */
class RPCDefinition
{
  Object handle;
  int timeout = 0;

  @Override
  public String toString () {
    return "RPC (Handle = " + handle + ")";
  }
}
