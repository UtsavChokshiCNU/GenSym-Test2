package com.gensym.devtools;

/**
 * The command failed exception.
 * Raised when a command fails for any reason.
 * @version August 2000
 * @author Brian O. Bush
 */
public class CommandFailedException
extends Exception
{
  public CommandFailedException(String msg) {
    super(msg);
  }
}
