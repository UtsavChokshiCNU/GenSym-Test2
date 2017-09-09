
package com.gensym.data;

import java.util.Hashtable;
import java.io.Serializable;
import java.io.*;

/** 
 * A class used for interning Strings as "symbols". Symbols have the following property:
 * <pre>Symbol.intern (String s1) == (Symbol.intern (String s2)) </pre>
 * iff <pre>s1.equals (s2)</pre><p>
 *
 * Symbols should typically be interned in static initialization code.<p>
 *
 * @see     String
 * @version 1.00, 09/14/99
 * @author  vkp
 */

public class Symbol implements Serializable {

  /*
   * Allow deserialization
   */
  static final long serialVersionUID = -8292678086170318269L;

  private String value;
  private static Hashtable internset;
  private static int requestedHashSize = -1;
  private static float requestedLoadFactor = -1.0f;

  static {
    //Class editor = com.gensym.beansruntime.SymbolEditor.class;
    //java.beans.PropertyEditorManager.registerEditor(Symbol.class,editor);
  }

  private static synchronized void makeHashtable () {
    if (internset == null) {
      if (requestedHashSize == -1)
	requestedHashSize = 2671;
      if (requestedLoadFactor > 0.0 && requestedLoadFactor <= 1.0)
	internset = new Hashtable (requestedHashSize, requestedLoadFactor);
      else
	internset = new Hashtable (requestedHashSize);
    }
  }

  /**
   * Initializes the Hashtable used to keep symbols. If this is not
   * called before a symbol is interned, the table is initialized to
   * with the default size.
   * NOTE: This method should only be called from within a "main" method.
   * @param hashsize the size of the intern table
   * @exception AlreadyInitializedException if the Hashtable has already been sized.
   */
  public static void initialize (int hashsize) throws AlreadyInitializedException {
    if (hashsize <= 0)
      throw new IllegalArgumentException ("Initial size must be > 0");
    if (requestedHashSize > 0)
      throw new AlreadyInitializedException();
    else
      requestedHashSize = hashsize;
  }

  /**
   * Initializes the hashtable used to keep symbols. If this is not
   * called before a symbol is interned, the table is initialized to
   * with the default size.
   * NOTE: This method should only be called from within a "main" method.
   * @param hashsize the size of the intern table.
   * @param loadFactor the load factor used by the intern table.
   * @exception AlreadyInitializedException if the Hashtable has already been sized.
   */
  
  public static void initialize (int hashsize, float loadFactor)
  throws AlreadyInitializedException {
    if (hashsize <= 0)
      throw new IllegalArgumentException ("Initial size must be > 0");
    if (requestedHashSize > 0)
      throw new AlreadyInitializedException();
    else {
      requestedHashSize = hashsize;
      requestedLoadFactor = loadFactor;
    }
  }

  /**
   * Returns the number of interned symbols.
   * Can be used during development to determine what arguments to use
   * for <code>initialize()</code>.
   */
  public static int size() {
    if (internset == null)
      return 0;
    else
      return internset.size();
  }

  private Symbol (String symval) {
    value = symval;
  }

  private static int numCalls = 0;
  public static final boolean traceIntern = false;
  /**
   * Interns a symbol and returns it.
   * @param symval a string that is interned as a symbol
   * @return the interned symbol
   */
  public static Symbol intern (String symval) {
    if (traceIntern)
      Thread.dumpStack ();
    Symbol s;
    numCalls++;
    if (internset == null)
      makeHashtable ();
    synchronized (internset) {
      s = (Symbol)internset.get (symval);
      if ( s == null )
	s = new Symbol (symval);
    }
    return s;
  }

  /**
   * Give this symbol a localIndex that is understood locally
   * to enable integer comparisons for symbol equality.
   */
  private void readObject(ObjectInputStream stream) throws ClassNotFoundException, IOException {
    stream.defaultReadObject();
  }
    
  public Symbol resolveObject() {
    return intern (this.value);
  }

  /**
   * Returns a String description of this Symbol.
   * <bold>NOTE:</bold> <em>Do not use the return value in a call to
   * <code>intern</code></em>.
   * @return a String description
   * @see #getPrintValue
   */
  @Override
  public String toString () {
    return value;
  }

  /**
   * Returns the String that was interned for the Symbol. The
   * return value has the property that:<P>
   * <pre> (Symbol.intern (mySymbol.getPrintValue ()).equals (mySymbol)) </pre>
   * will be true. This property is not shared by the String returned from
   * Symbol.toString ().
   * @return the String value of the Symbol
   */
  public String getPrintValue () {
    return value;
  }

  /**
   * Debugging methods
   * @undocumented
   */
  public static void dumpStats () {
    System.out.println ("There are " + internset.size () + " symbols");
    System.out.println ("There were " + numCalls + " calls to Symbol.intern");
  }

  public static final class AlreadyInitializedException extends RuntimeException {

    AlreadyInitializedException() {
      super ();
    }

  }
}
