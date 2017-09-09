package com.gensym.util;

/**
 * This subclass of Sequence provides setUnqiueElement, addUniqueElement and insertUniqueElement
 * which will not insert/add a duplicate Object into the Sequence when the allowDuplicateElements
 * property is false;
 */
public class CheckedSequence extends Sequence
{
 
  static final long serialVersionUID = -1857879552954906482L;
  private boolean allowDuplicateElements = true;

  public CheckedSequence (int initialCapacity) {
    super (initialCapacity);
  }

  public CheckedSequence () {
    super ();
  }

  public CheckedSequence (Sequence seq) {
    this(seq.size());
    seq.copyInto(elementData);
  }

  public void addUniqueElement(Object newElement)
  {
    if (allowDuplicateElements ||
	!contains(newElement))
      addElement(newElement);
  }

  public void setUniqueElementAt(Object newElement, int index)
  {
    if (allowDuplicateElements ||
	!contains(newElement))
      setElementAt(newElement,index);
  }

  public void insertUniqueElementAt(Object newElement, int index)
  {
    if (allowDuplicateElements ||
	!contains(newElement))
      insertElementAt(newElement,index);
  }

  public void setAllowDuplicateElements(boolean state) {
    allowDuplicateElements = state;
  }

  public boolean getAllowDuplicateElements() {
    return allowDuplicateElements;
  }
}
