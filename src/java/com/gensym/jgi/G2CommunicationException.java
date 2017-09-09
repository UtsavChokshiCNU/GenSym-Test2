package com.gensym.jgi;

import java.io.PrintWriter;
import com.gensym.message.Resource;

/**
 * Signals that a G2 communication problem has occured.
 *
 * @version     1.00 12-june-1997
 * @author      M.D.Gribble
 */

public class G2CommunicationException
       extends java.lang.RuntimeException {

  protected static Resource i18n =  Resource.getBundle("com.gensym.resources.Errors");
  private Throwable nestedException;

  public G2CommunicationException () {
    super ();
    
  }

  public G2CommunicationException (String key) {
    super (key);
    
  }

	 
  public G2CommunicationException (Throwable ex) {
    nestedException = ex;
  }

  public G2CommunicationException (Throwable ex, String message) {
    super(message);
    nestedException = ex;
  }

  @Override
  public void printStackTrace() {
    super.printStackTrace();
    if (nestedException != null) {
      System.err.println(i18n.getString("nestedException"));
      nestedException.printStackTrace();
    } else {
      System.err.println(i18n.getString("noNestedException"));
    }
  }

  @Override
  public void printStackTrace(PrintWriter writer) {
    super.printStackTrace(writer);
    if (nestedException != null) {
      writer.println(i18n.getString("nestedException"));
      nestedException.printStackTrace(writer);
    } else {
      writer.println(i18n.getString("noNestedException"));
    }
  }

  @Override
  public String toString () {
    String string = (nestedException == null ? super.toString() :
		     super.toString() + nestedException.toString ());
    return string;
  }

}
