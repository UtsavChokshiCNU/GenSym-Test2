package com.gensym.jgi;

import java.util.Hashtable;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.classes.Item;

/** Corresponds to a "thing of interest" in G2. A Designation is
 * a combination of an item and a denotation. A typical example of
 * a Designation would be a particular attribute of an item, e.g.,
 * "the level of tank1".
 * Designations can be subscribed to, and events will be broadcast when
 * changes occur to the designation in G2.
 *
 * @see com.gensym.util.G2ItemProxy
 * @see com.gensym.util.Sequence
 */

public class Designation implements java.io.Serializable {

  //
  // Class variables
  //

  /** To support the idea that a combination of item and denotation
   * is unique, Designations use an interning mechanism.
   */
  protected static Hashtable internedTable = new Hashtable();

  /** Events from G2 are given subscription ID's */
  protected static Hashtable subscriptionTable = new Hashtable();

  //
  // Instance variables
  //
  
  protected Item proxy;
  protected Sequence denotation;

  public Designation() {
    super();
  }

  public static Designation getOrMakeDesignation(Item proxy,
						 Sequence denotation) {
    return new Designation(proxy, denotation);
  }
    

  private Designation(Item proxy, Sequence denotation) {
    this.proxy = proxy;
    this.denotation = denotation;
  }

  
    
  public Sequence getDenotation() {
    return denotation;
  }

  public Item getItem() {
    return proxy;
  }

}
