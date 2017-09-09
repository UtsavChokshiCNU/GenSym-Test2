
package com.gensym.util;
import java.util.Hashtable;
import java.io.Serializable;
import java.io.*;

/** 
 * A class used for interning Strings as "symbols". Symbols have the following property:
 * <pre>Symbol.intern (String s1).equals (Symbol.intern (String s2)) </pre>
 * iff <pre>s1.equals (s2)</pre><p>
 *
 * Symbols should typically be interned in static initialization code.<p>
 *
 * @see     String
 * @version 1.00, 11/09/96
 * @author  vkp
 */
public class Symbol implements Serializable {

  /*
   * Allow deserialization
   */
  static final long serialVersionUID = -8292678086170318269L;

  private static final boolean DEVELOPMENT_MODE = false;
  private transient int localIndex;
  private String value;
  private static volatile Hashtable internset;
  private static int indexGenerator = 0;
  private static boolean initializing;
  private static int requestedHashSize = -1;
  private static float requestedLoadFactor = -1.0f;

  static {
    Class editor = SymbolEditor.class;
    java.beans.PropertyEditorManager.registerEditor(Symbol.class,editor);
  }

    /* Initialize known symbols
       OK G2ClassSymbols
       OK VirtualAttributeSymbols
       OK SystemAttributeSymbols
       OK G2TypeSymbols
       OK AttributeExportSymbols
       OK AttributeTypeSpecificationSymbols
       OK MethodExportSymbols
       OK OverrideSymbols
       OK DefinitionSymbols
       OK ChartSymbols
       OK TrendChartSymbols
       OK WorkspaceShowingSymbols
       */
  private static void populate () {
    try {
      initializing = true;
      Class.forName ("com.gensym.util.symbol.G2ClassSymbols");
      Class.forName ("com.gensym.util.symbol.VirtualAttributeSymbols");
      Class.forName ("com.gensym.util.symbol.SystemAttributeSymbols");
      Class.forName ("com.gensym.util.symbol.G2TypeSymbols");
      Class.forName ("com.gensym.util.symbol.AttributeExportSymbols");
      Class.forName ("com.gensym.util.symbol.AttributeTypeSpecificationSymbols");
      Class.forName ("com.gensym.util.symbol.MethodExportSymbols");
      Class.forName ("com.gensym.util.symbol.OverrideSymbols");
      Class.forName ("com.gensym.util.symbol.DefinitionSymbols");
      Class.forName ("com.gensym.util.symbol.ChartSymbols");
      Class.forName ("com.gensym.util.symbol.TrendChartSymbols");
      Class.forName ("com.gensym.util.symbol.WorkspaceShowingSymbols");
    } catch (ClassNotFoundException cnfe) {
      throw new Error ("Required class not found. " + cnfe);
    }
    initializing = false;
  }

  private static void makeHashtable () {
    if (requestedHashSize == -1)
      requestedHashSize = 2671;
    if (requestedLoadFactor > 0.0 && requestedLoadFactor <= 1.0)
      internset = new Hashtable (requestedHashSize, requestedLoadFactor);
    else
      internset = new Hashtable (requestedHashSize);
    //long t0 = System.currentTimeMillis ();
    populate ();
    //long t1 = System.currentTimeMillis ();
    //System.out.println ("Populating Table took : " + (t1 - t0) + "ms");
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
    setIndex();
    // Set Index without checking
  }

  private final void setIndex() {
    synchronized(Symbol.class) {
      if (internset == null)
	makeHashtable ();

      Symbol interned = (Symbol)internset.get(value);
      
      if (interned == null) {
	internset.put(value, this);
	localIndex = ++indexGenerator;
	return;
      }

      if (!this.equals(interned))
	localIndex = interned.localIndex;
    }
  }

  private static int numCalls = 0;
  public static final boolean traceIntern = false;
  /**
   * Interns a symbol and returns it.  Symbol text should be uppercase.
   * By convention, variable names should be 
   * uppercased and end with an underscore. For example, <br>
   * <code>Symbol A_HANDY_SYMBOL_ = Symbol.intern("A-HANDY-SYMBOL");</code>
   * @param symval a string that is interned as a symbol
   * @return the interned symbol
   */
  public static Symbol intern (String symval) {
    //System.out.println("******* Java Symbol Intern " + symval);
    if (traceIntern)
      Thread.dumpStack ();
    Symbol s;
    numCalls++;
    if (internset == null)
      makeHashtable ();
    if (DEVELOPMENT_MODE) {
      int symLength = symval.length ();
      char[] stringChars = new char[symLength];
      for (int i=0; i<symLength; i++)
	stringChars[i] = Character.toUpperCase (symval.charAt (i));
      String strcopy = new String (stringChars);
      if (!symval.equals (strcopy))
	throw new Error ("Possible incorrect capitalization of String to intern as Symbol. " +
			 symval + " != " + strcopy);
    }
    if (false) {//initializing) {
      if (DEVELOPMENT_MODE && (s = (Symbol)internset.get (symval)) != null)
	throw new Error ("Duplicate symbol while initializing : " + s.getPrintValue ());
      s = new Symbol (symval);
    } else {
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
    setIndex();
  }
    
  @Override
  public final boolean equals (Object obj) {
    if (this == obj)
      return true;
    if (obj instanceof Symbol) {
      return (((Symbol)obj).localIndex == localIndex);
    }
    else
      return false;
  }

  @Override
  public final int hashCode () {
    return localIndex;
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
   *@undocumented
   *Returns a String, lower cased, hyphens replaced by spaces.
   */
  public String prettyName() {
    StringBuffer buffer;
    buffer = new StringBuffer(value.toString().replace('-', ' ').
			      toLowerCase());
    buffer.setCharAt(0, Character.toUpperCase(buffer.charAt(0)));
    return buffer.toString();
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
}
