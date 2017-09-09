
package com.gensym.util;
import java.io.Serializable;
import java.util.Vector;

/**
 * A Sequence is just a collection of things in G2.
 * It is implemented by subclassing Vector. Use the methods
 * in that class to access and set elements. In the not so
 * distant future, we might add more G2 sequence like
 * operations, such as remove-last, etc.
 * @version 1.00 11/23/96
 * @author vkp
 * @see java.util.Vector
 */
public class Sequence extends Vector implements Serializable {

  /*
   * Allow deserialization
   */
  static final long serialVersionUID = -1857879552953906482L;

  /**
   * Use only this constructor for now.
   * @param initialCapacity the initial capacity of the Sequence
   */
  public Sequence (int initialCapacity) {
    super (initialCapacity);
  }

  public Sequence () {
    super ();
  }

  /**
   * Returns a printable representation of the Sequence.
   * This is necessary because toString is declared as final
   * in Vector.
   * @return a printable String description of the Sequence
   * @see java.util.Vector#toString
   */
  public String print () {
    //System.out.println("Sequence is " + elementData.toString());
    //System.out.println ("has " + elementCount +  " elements");
    //for (int i=0; i<elementCount; i++)
    //System.out.println("["+i+"]"+ elementData[i]);
    return ("Sequence of " + elementCount + " elements " + super.toString());
  }

  public String expand () {
    StringBuffer sb = new StringBuffer ();
    sb.append ("Sequence is ").append(elementCount).append(" elements");
    for (int i=0; i<elementCount; i++)
      sb.append("[").append(i).append("]").append(elementData[i]);
    return sb.toString();
  }

  public Object[] getContents () {
    Object[] contents = new Object[elementCount];
    for (int i=0; i<elementCount; i++)
      contents[i] = elementData[i];
    return contents;
  }

  /**
   * Compares two Sequences for equality.
   * Two Sequences are equal iff they are of the same length and
   * their corresponding elements are equal to each other.
   * @param obj   the reference object with which to compare.
   * @return  <code>true</code> if this object is the same as the obj
   *          argument; <code>false</code> otherwise.
   */
  @Override
  public boolean equals (Object obj) {
    if (obj == null || !getClass().equals(obj.getClass())){
      return false;
    }
    Sequence seq2 = (Sequence)obj;
    if (elementCount != seq2.elementCount)
      return false;
    for (int i=0; i<elementCount; i++){
      if (!elementData[i].equals(seq2.elementData[i])){
    	  return false;
      }
    }
    return true;
  }

  /**
   * Determines a hash code for using a Sequence as a key
   * in a hash table.
   * @return a hash code for this Sequence
   */
  @Override
  public int hashCode () {
    int code = 0;
    for (int i=0; i<elementCount; i++)
      code ^= elementData[i].hashCode ();
    return code;
  }

  /**
   * Appends the contents of the argument to this Sequence.
   * It is most efficient when this Sequence does not need to
   * be expanded to fit the new contents.
   * @param otherSequence the Sequence whose contents should be appended to this Sequence.
   */
  public synchronized void concatenate (Sequence otherSequence) {
    int combinedCount = elementCount + otherSequence.elementCount;
    ensureCapacity (combinedCount);
    System.arraycopy(otherSequence.elementData, 0, elementData, elementCount, otherSequence.elementCount);
    elementCount = combinedCount;
  }

  /**
   * @undocumented For VB use since it cannot call addElement (java.lang.Object)
   */
  public void addStringElement (String element) {
    addElement (element);
  }

  /**
   * @undocumented For VB use because of bug passing ""
   */
  public void addEmptyStringElement () {
    addElement ("");
  }

  /**
   * @undocumented For VB use since it cannot call addElement (java.lang.Object)
   */
  public void addIntElement (int element) {
    addElement (element);
  }
 
  /**
   * @undocumented For VB use since it cannot call addElement (java.lang.Object)
   */
  public void addDoubleElement (double element) {
    addElement (element);
  }

  /**
   * @undocumented For VB use since it cannot call addElement (java.lang.Object)
   */
  public void addBooleanElement (boolean element) {
    addElement (element);
  }

  /**
   * @undocumented For VB use since it cannot call addElement (java.lang.Object)
   */
  public void addPseudoBooleanElement (int element) {
    addElement ((element != 0) ? Boolean.TRUE : Boolean.FALSE);
  }
  
  /**
   * @undocumented For VB use since it cannot call insertElement (java.lang.Object, int)
   */
  public void insertStringElementAt (String element, int index) {
    insertElementAt (element, index);
  }

  /**
   * @undocumented For VB use because of bug passing ""
   */
  public void insertEmptyStringElementAt (int index) {
    insertElementAt ("", index);
  }

  /**
   * @undocumented For VB use since it cannot call insertElement (java.lang.Object, int)
   */
  public void insertIntegerElementAt (int element, int index) {
    insertElementAt (element, index);
  }

  /**
   * @undocumented For VB use since it cannot call insertElement (java.lang.Object, int)
   */
  public void insertBooleanElementAt (boolean element, int index) {
    insertElementAt (element, index);
  }

  /**
   * @undocumented For VB use since it cannot call insertElement (java.lang.Object, int)
   */
  public void insertPseudoBooleanElementAt (int element, int index) {
    insertElementAt ((element != 0) ? Boolean.TRUE : Boolean.FALSE, index);
  }

  /**
   * @undocumented For VB use since it cannot call insertElement (java.lang.Object, int)
   */
  public void insertDoubleElementAt (double element, int index) {
    insertElementAt (element, index);
  }
}
