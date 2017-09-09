
package com.gensym.util;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.Serializable;
import java.util.Enumeration;
import java.util.Vector;

/**
 * A class to hold attributes. Attributes have a symbolic name and
 * an Object value.
 */
public class Structure implements Cloneable, Serializable {

  /*
   * Allow deserialization
   */
  static final long serialVersionUID = -6367124813476730770L;

  private Vector slots;
  private volatile Symbol[] slotKeys;
  public Object[] slotValues;
  private int numSlots, capacity;
  private static final Object emptymarker = new Object ();

  /**
   * Constructs a Structure that initially has no attributes.
   */
  public Structure () {
  }


  /**
   * Constructs a Structure that initially has the specified
   * attribute names and values. It throws an NtwIllegalArgumentException if the
   * two arrays are of unequal length.
   * @param keys a symbol array naming the attributes
   * @param values an object array of the attribute values
   */
  public Structure (Symbol[] keys, Object[] values) throws NtwIllegalArgumentException {
    numSlots = keys.length;
    //long startTime = System.currentTimeMillis();

    if (numSlots != values.length)
      throw new NtwIllegalArgumentException ("Unequal Property and Value Arrays");
    init (keys, values, numSlots);
  }

  /**
   * A highly optimized constructor. It takes over the arrays
   * that are passed to it without copying. The caller must
   * give up these objects and never modify them again.
   * @undocumented
   */
  public Structure (Symbol[] keys, Object[] values, int numSlots) {
    slotKeys = keys;
    slotValues = values;
    this.numSlots = capacity = numSlots;
  }

  /**
   * Constructs a Structure that initially has <pre>numslots</pre>
   * number of attributes, named by <pre>keys</pre> and with
   * values <pre>values</pre>. Throws an NtwIllegalArgumentException
   * if there are not enough elements in either array.
   * @param keys a symbol array naming the attributes
   * @param values an object array of the attribute values
   * @param numslots the number of attributes to add
   */
  public Structure (Symbol[] keys, Symbol[] values, int numSlots) 
       throws NtwIllegalArgumentException {
    if ((keys.length < numSlots) || (values.length < numSlots))
      throw new NtwIllegalArgumentException ("Arrays not long enough");
    init (keys, values, numSlots);
  }

  private void init (Symbol[] keys, Object[] values, int numSlots) {
    slotKeys = new Symbol[numSlots];
    slotValues = new Object[numSlots];
    System.arraycopy (keys, 0, slotKeys, 0, numSlots);
    System.arraycopy (values, 0, slotValues, 0, numSlots);
    this.numSlots = numSlots;
    capacity = numSlots;
  }

  /**
   * Constructs a new Structure containing the attributes specified.
   * @param slots an array of parameters that represent the attributes.
   */
  public Structure (Property[] slots) {
    numSlots = slots.length;
    slotKeys = new Symbol[numSlots];
    slotValues = new Object[numSlots];
    for (int i=0; i<numSlots; i++) {
      slotKeys[i] = slots[i].key;
      slotValues[i] = slots[i].value;
    }
  }

  /**
   * Constructs a new Structure with the requested space requested.
   * It will have no attributes initially.
   * @param numslots the initial capacity of the Structure. A negative
   * number is ignored.
   */
  private Structure (int numSlots) {
    //System.out.println ("Structure (" + numSlots + ") called");
    ensureCapacity (numSlots);
  }

  private void ensureCapacity (int limit) {
    if (slotKeys == null || numSlots == 0) {
      slotKeys = new Symbol [limit];
      slotValues = new Object [limit];
      capacity = limit;
    } else {
      if (capacity >= limit)
	return;
      int newCapacity = capacity*2;
      if (newCapacity < limit)
	newCapacity = limit;
      Symbol[] newSlotKeys = new Symbol [newCapacity];
      Object[] newSlotValues = new Object [newCapacity];
      System.arraycopy (slotKeys, 0, newSlotKeys, 0, numSlots);
      System.arraycopy (slotValues, 0, newSlotValues, 0, numSlots);
      slotKeys = newSlotKeys;
      slotValues = newSlotValues;
      capacity = newCapacity;
    }
  }

  /**
   * Returns a copy of the Structure. Neither the attribute
   * names nor the values are cloned.
   */
  @Override
  public synchronized Object clone () {
    Structure copy = new Structure (numSlots);
    //System.out.println ("Structure.clone [# = " + numSlots + ", #copy = " + copy.numSlots + "]");
    System.arraycopy (slotKeys, 0, copy.slotKeys, 0, numSlots);
    System.arraycopy (slotValues, 0, copy.slotValues, 0, numSlots);
    copy.numSlots = numSlots;
    return copy;
  }

  /**
   * Returns a copy of the Structure.  Values are cloned (uniquely).
   * @deprecated
   */
  /*
   * Has not been updated. Will be deleted. -vkp, 3/6/98
   */
  protected synchronized Object cloneForDeserializer () {
    int numslots = getAttributeCount ();
    Structure copy = new Structure (numSlots);
    for (int i=0; i<numslots; i++) 
      { 
	Property property = (Property) slots.elementAt(i);
	Property clonedProperty  
	  = new Property(Symbol.intern(property.key.toString()),
			 Deserializer.makeUnique(property.value));
	copy.slots.addElement (clonedProperty);
      }
    return copy;
  }

  /**
   * Returns an enumeration of the Structure attribute names.
   * This is not a snapshot. In order to get a static copy,
   * clone this structure before calling getAttributeNames.
   * @see Structure#getAttributeValues
   * @see Structure#clone
   */
  public Enumeration getAttributeNames () {
    StructureEnumerator se = new StructureEnumerator (slotKeys, numSlots);
    return se;
  }

  /**
   * Returns an enumeration of the Structure attribute values.
   * This is not a snapshot. In order to get a static copy,
   * clone this structure before calling getAttributeValues.
   * @see Structure#getAttributeNames
   * @see Structure#clone
   */
  public Enumeration getAttributeValues () {
    StructureEnumerator se = new StructureEnumerator (slotValues, numSlots);
    return se;
  }

  /**
   * Returns a printable description of the structure. It is simply a
   * concatenation of the symbolic attribute names and their values.
   */
  @Override
  public String toString () {
    StringBuffer buf = new StringBuffer ();
    buf.append ("Structure {");
    for (int i=0; i<numSlots; i++) {
      Symbol key = slotKeys[i];
      String s1 = (key != null ? key.getPrintValue() : "null Attribute Name !!!");
      Object o  = slotValues[i];
      String s2 = (o != null ? o.toString() : "null");
      buf.append (s1 + ":" + s2);
      if (i < numSlots - 1) {
	buf.append (", ");
      }
    }
    buf.append ("}");
    return buf.toString ();
  }

  /**
   * Determines if one structure is functionally? equal to another.
   * Two structures are equal if they contain the same attributes
   * and the attribute values are equal.
   * @param s the structure to compare <pre>this</pre> structure to.
   * @return a boolean indicating whether the structures are equal or not
   */
  /* This should probably use the Enumeration interface and not access
   * the private slots! */
  @Override
  public boolean equals (Object o) {
    if (o == null || !getClass().equals(o.getClass())){
      return false;
    }
    
    if (this == o){
      return true;
    }
    Structure s = (Structure)o;
    int numSlotsalt = s.numSlots;

    if (numSlots != numSlotsalt)
      return false;
    for (int i=0; i<numSlots; i++) {
      Symbol matchkey = slotKeys[i];
      Object matchvalue = slotValues[i];
    matchfound: {
	for (int j=0; j<numSlotsalt; j++) {
	  Symbol altKey = s.slotKeys[j];
	  Object altValue = s.slotValues[j];
	  if (matchkey.equals(altKey)) { // Disallows null keys!
	    if (matchvalue == null && altValue == null) 
	      break matchfound;
	    if (matchvalue != null && altValue != null && matchvalue.equals (altValue))
	      break matchfound;
	    else
	      return false;
	  }
	}
	return false;
      }
    }
    return true;
  }

  /**
   * Returns a hash code for the structure.
   * @return an integer hash code
   */
  @Override
  public int hashCode () {
    int code = 0;
    for (int i=0; i<numSlots; i++) {
      Object value = slotValues[i];
      code ^= slotKeys[i].hashCode() ^ (value != null ? value.hashCode () : 0);
    }
    return code;
  }

  /**
   * Returns the number of attributes in the structure.
   */
  public int getAttributeCount () {
    return numSlots;
  }

  /**
   * Accesses a named attribute.
   * @param propname a symbol naming an attribute
   * @return the value of the attribute if it exists
   */
  public Object getAttributeValue (Symbol propname) throws NoSuchAttributeException {
    Object target = getAttributeValue (propname, emptymarker);
    if (emptymarker.equals(target))
      throw new NoSuchAttributeException (propname + " does not exist");
    return target;
  }

  /**
   * Accesses a named attribute.
   * @param propname a symbol naming an attribute
   * @param defaultvalue the object to return if the attribute does not exist in
   * the structure.
   * @return the value of the attribute if it exists or the default value.
   */
  public synchronized Object getAttributeValue (Symbol propname, Object defaultvalue) {
    int propIndex = getAttributeIndexIfAny (propname);
    return propIndex != -1 ? slotValues[propIndex] : defaultvalue;
  }

  /**
   * Concludes a value for an attribute.
   * @param propname a symbol naming an attribute
   * @param propvalue the new value for the attribute
   */
  public synchronized void setAttributeValue (Symbol propname, Object propvalue) {
    if (propname == null)
      throw new NullPointerException();
    
    int propIndex = getAttributeIndexIfAny (propname);
    if (propIndex != -1)
      slotValues[propIndex] = propvalue;
    else
      addAttribute (propname, propvalue);
  }

  /**
   * Removes an attribute from a structure.
   * @param propname a symbol naming the attribute to remove
   */
  public void deleteAttribute (Symbol propname) {
    int propIndex = getAttributeIndexIfAny (propname);
    if (propIndex != -1) {
      if (propIndex != numSlots - 1) {
	System.arraycopy (slotKeys, propIndex + 1, slotKeys, propIndex, numSlots - 1 - propIndex);
	System.arraycopy (slotValues, propIndex + 1, slotValues, propIndex, numSlots - 1 - propIndex);
      } else {
	// Drop these so that they don't get serialized! -vkp, 8/19/98
	slotKeys[propIndex] = null;
	slotValues[propIndex] = null;
      }
      numSlots--;
    }
  }

  /**
   * Obtains the slot holding the name-value pair for any property
   * Returns null if the attribute does not exist in the structure.
   * In order to ensure safe multi-threaded operation, this method
   * must only be called after locking the Structure.
   * @param a symbol naming the attribute
   * @return a property (or null if the named attribute does not exist)
   */
  private final int getAttributeIndexIfAny (Symbol propname) {
    for (int i=0; i<numSlots; i++) {
      if ((slotKeys[i]).equals(propname))
	return i;
    }
    return -1;
  }

  /**
   * Adds an attribute to the structure. The attribute must not already
   * exist in the structure.
   * @param propname a symbol naming the attribute to add
   * @param propvalue the initial value of the attribute
   * @see Structure#getAttributeValue
   * @deprecated Will soon be removed. Use Structure#setAttributeValue instead.
   */
  public void addAttribute (Symbol propname, Object propvalue) {
    ensureCapacity (numSlots + 1);
    slotKeys[numSlots] = propname;
    slotValues[numSlots++] = propvalue;
  }

  /**
   * Adds attribute specified by the argument to the structure.
   * The attribute must not already exist in the structure.
   * @param p the property to be added as an attribute
   * @see Structure#getAttributeValue
   * @deprecated Will Soon be removed. Use Structure#setAttributeValue instead.
   */
  public synchronized void addAttribute (Property p) {
    addAttribute (p.key, p.value);
  }

  /**
   * Return the Vector containing the structrure contents.
   * @deprecated
   * @return a Vector of Properties representing the Structures contents
   */
  protected Vector getAttributes() {
    // Major hack. I'm sorry.
    fillInSlotsVector ();
    return slots;
  }

  private void fillInSlotsVector () {
    slots = new Vector (numSlots);
    for (int i=0; i<numSlots; i++)
      slots.addElement (new Property (slotKeys[i], slotValues[i]));
  }

  //  public void pprint(PrintWriter writer, int level) {}

  public boolean getBoolean(Symbol propname) throws NoSuchAttributeException {
    return ((Boolean)getAttributeValue(propname)).booleanValue();
  }

  public boolean getBoolean(Symbol propname, boolean defaultvalue) {
    int propIndex = getAttributeIndexIfAny (propname);
    return propIndex != 1 ?
      ((Boolean)slotValues[propIndex]).booleanValue() : defaultvalue;
  }

  public long getLong(Symbol propname) throws NoSuchAttributeException {
    return ((Number)getAttributeValue(propname)).longValue();
  }

  private void readObject (ObjectInputStream in) throws IOException, ClassNotFoundException {
    in.defaultReadObject();
    if (slots != null)
      upgrade ();
  }

  private void upgrade () {
    numSlots = slots.size ();
    ensureCapacity (numSlots);
    Class svClass = slotValues.getClass().getComponentType ();
    //System.out.println ("Structure().upgrade ->\nSlotValueArray ComponentType = " + svClass);
    for (int i=0; i<numSlots; i++) {
      Property p  = (Property)slots.elementAt (i);
      /*System.out.println ("Key = " + DebugUtil.describe (p.key) +
			  "\n  Value = " + DebugUtil.describe (p.value));
      Class valueClass = p.value.getClass ();
      System.out.println ("   " + valueClass + "  Assignable ? = " + svClass.isAssignableFrom (valueClass));
      */
      Symbol s = p.key;
      Object v = p.value;
      slotKeys[i] = s;
      slotValues[i] = v;
    }
    slots = null;
  }

  /**
   * @undocumented For VB use since it cannot call setAttributeValue (propName, java.lang.Object)
   */
  public void setStringAttributeValue (Symbol propname, String propvalue) {
    setAttributeValue (propname, propvalue);
  }

  /**
   * @undocumented For VB use because of bug passing ""
   */
  public void setEmptyStringAttributeValue (Symbol propName) {
    setAttributeValue (propName, "");
  }

  /**
   * @undocumented For VB use since it cannot call setAttributeValue (propName, java.lang.Object)
   */
  public void setIntAttributeValue (Symbol propname, int propvalue) {
    setAttributeValue (propname, propvalue);
  }

  /**
   * @undocumented For VB use since it cannot call setAttributeValue (propName, java.lang.Object)
   */
  public void setDoubleAttributeValue (Symbol propname, double propvalue) {
    setAttributeValue (propname, propvalue);
  }

  /**
   * @undocumented For VB use since it cannot call setAttributeValue (propName, java.lang.Object)
   */
  public void setBooleanAttributeValue (Symbol propname, boolean propvalue) {
    setAttributeValue (propname, propvalue);
  }

  /**
   * @undocumented For VB use since it cannot call setAttributeValue (propName, java.lang.Object)
   */
  public void setPseudoBooleanAttributeValue (Symbol propname, int propvalue) {
    setAttributeValue (propname, (propvalue != 0) ? Boolean.TRUE : Boolean.FALSE);
  }

}
