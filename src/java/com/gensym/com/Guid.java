/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 com.gensym.com.Guid.java
 *
 *   Author: John Valente
 */
package com.gensym.com;

import java.io.Serializable;

/** A Guid, which is an acronym for Globally Unique IDentifier,
 *  is used to refer to ActiveX objects by their Class ID.  
 *  Class ID's are just one usage of GUIDs, and this class 
 *  certainly could be used for other things, but we currently 
 *  don't have any other uses for it.<p>
 *  The subcomponents of a GUID do have some meaning.  Some
 *  part of it is the machine ID, another part is the date,
 *  etc.  The variable names don't reflect that because we are
 *  trying to match the definition in <code>msdev\include\wtypes.h:</code> 
 *  <pre>
 *  <code>
 *   typedef struct  _GUID
 *    {
 *    DWORD Data1;
 *    WORD Data2;
 *    WORD Data3;
 *    SHORT Data4[ 8 ];
 *    }	GUID; </code></pre>
 *  We didn't want to go the full blown route and make 
 *  data4 be an array because of the messiness of passing 
 *  arrays between Java and C.  There are functions in
 *  JavaContainer.dll for converting Java Guids to C GUIDs
 *  and vice versa.
 */
public class Guid implements Serializable 
{

   static final long serialVersionUID = 643715504276946206L;

  /** Data of the Guid.  Guids are just about data; they are
   *  much more like structures than objects;  therefore,
   *  their data is accessible as fields rather than get/set
   *  methods.
   */
  public int d1;
  /** Data of the Guid.  Guids are just about data; they are
   *  much more like structures than objects;  therefore,
   *  their data is accessible as fields rather than get/set
   *  methods.
   */
  public int d2, d3;
  /** Data of the Guid.  Guids are just about data; they are
   *  much more like structures than objects;  therefore,
   *  their data is accessible as fields rather than get/set
   *  methods.
   */
  public short d40, d41, d42, d43, d44, d45, d46, d47;


  /** Constructs a Guid from the properly typed data supplied.
    */
  public Guid(int d1, int d2, int d3, short d40, short d41,
	      short d42, short d43, short d44, short d45, short d46,
	      short d47) {
    this.d1 = d1;
    this.d2 = d2;
    this.d3 = d3;
    this.d40 = d40;
    this.d41 = d41;
    this.d42 = d42;
    this.d43 = d43;
    this.d44 = d44;
    this.d45 = d45;
    this.d46 = d46;
    this.d47 = d47;
  }

  /** Constructs a Guid from the integer values supplied.
   *  Sometimes Java's strong-typing is a great big pain.
   */
  public Guid(int d1, int d2, int d3, int d40, int d41,
	      int d42, int d43, int d44, int d45, int d46,
	      int d47) {
    this(d1,
	 (int) d2,
	 (int) d3,
	 (short) d40,
	 (short) d41,
	 (short) d42,
	 (short) d43,
	 (short) d44,
	 (short) d45,
	 (short) d46,
	 (short) d47);
  }

  /** Constructs a null Guid, i.e., one with zeros for all of its values.
   */
  public Guid() {
    this(0,
	 (int) 0,
	 (int) 0,
	 (short) 0,
	 (short) 0,
	 (short) 0,
	 (short) 0,
	 (short) 0,
	 (short) 0,
	 (short) 0,
	 (short) 0);
  }

  
  /*  I think that the C Windows API function for creating
   *  a GUID from a string requires that it be enclosed in
   *  curly braces, like<b>
   *  "{8e27c92b-1264-101c-ffffff8a2f-42240ffffff9c2}".
   *  We should support that too.
   */

  /** Constructs a Guid from a String of the form
   *  "8e27c92b-1264-101c-ffffff8a2f-42240ffffff9c2".<br>
   */
  public Guid(String guid) {
    this((int) Long.parseLong(guid.substring(0, 8), 16),
	 Integer.parseInt(guid.substring( 9, 13), 16),
	 Integer.parseInt(guid.substring(14, 18), 16),
	 Integer.parseInt(guid.substring(19, 21), 16),
	 Integer.parseInt(guid.substring(21, 23), 16),
	 Integer.parseInt(guid.substring(24, 26), 16),
	 Integer.parseInt(guid.substring(26, 28), 16),
	 Integer.parseInt(guid.substring(28, 30), 16),
	 Integer.parseInt(guid.substring(30, 32), 16),
	 Integer.parseInt(guid.substring(32, 34), 16),
	 Integer.parseInt(guid.substring(34, 36), 16));
  }



  /** Constructs a Guid from a String of the form
   *  "{8e27c92b-1264-101c-ffffff8a2f-42240ffffff9c2}",
   *  as the C Windows API function for creating
   *  a GUID from a string does.
   */
  public static Guid makeGuidFromString(String guid) {
    Guid returnGuid;
    try {
      if (guid.charAt(0) == '{') {
	returnGuid = 
	  new Guid((int) Long.parseLong(guid.substring(1, 9), 16),
		   Integer.parseInt(guid.substring(10, 14), 16),
		   Integer.parseInt(guid.substring(15, 19), 16),
		   Integer.parseInt(guid.substring(20, 22), 16),
		   Integer.parseInt(guid.substring(22, 24), 16),
		   Integer.parseInt(guid.substring(25, 27), 16),
		   Integer.parseInt(guid.substring(27, 29), 16),
		   Integer.parseInt(guid.substring(29, 31), 16),
		   Integer.parseInt(guid.substring(31, 33), 16),
		   Integer.parseInt(guid.substring(33, 35), 16),
		   Integer.parseInt(guid.substring(35, 37), 16));
	return returnGuid;
      } else {
	returnGuid = 
	  new Guid((int) Long.parseLong(guid.substring(0, 8), 16),
		   Integer.parseInt(guid.substring( 9, 13), 16),
		   Integer.parseInt(guid.substring(14, 18), 16),
		   Integer.parseInt(guid.substring(19, 21), 16),
		   Integer.parseInt(guid.substring(21, 23), 16),
		   Integer.parseInt(guid.substring(24, 26), 16),
		   Integer.parseInt(guid.substring(26, 28), 16),
		   Integer.parseInt(guid.substring(28, 30), 16),
		   Integer.parseInt(guid.substring(30, 32), 16),
		   Integer.parseInt(guid.substring(32, 34), 16),
		   Integer.parseInt(guid.substring(34, 36), 16));
	return returnGuid;
      }
    } catch (NumberFormatException nfe) {
      NativeMethodBroker.traceln(ActiveXTraceLevels.AX_ERROR,
				 "Number Format Exception trying to create " +
				 "Guid from " + guid + ": " + nfe);
      return new Guid();
    }
  }




  /** Returns true if the Guid is equal to GUID_NULL. */
  public boolean isNullGuid() {
    return ((d1 == 0) &&
	    (d2 == (int) 0) &&
	    (d3 == (int) 0) &&
	    (d40 == (short) 0) &&
	    (d41 == (short) 0) &&
	    (d42 == (short) 0) &&
	    (d43 == (short) 0) &&
	    (d44 == (short) 0) &&
	    (d45 == (short) 0) &&
	    (d46 == (short) 0) &&
	    (d47 == (short) 0));
  }

  
  private String toZeroPaddedHexString(int number, int fieldSize) {
    String orig;
    int len;

    orig = Integer.toHexString(number);
    len = orig.length();
    if (len < fieldSize) {
      int i;
      for (i=0; i<(fieldSize - len); i++) {
	orig = "0" + orig;
      }
    }
    return orig;
  }


  /* Silly test main.  Make public to use. */
  private static void main (String[] args) {
    Guid g;

    g = new Guid("00020821-0000-0000-C000-000000000046");
    // Using System.out.print here is ok because this is a 
    // separate application.
    System.out.println("                     " + g);
    for (int i=0; i<args.length; i++) {
      System.out.println("                     " + makeGuidFromString(args[i]));
    }
  }

 @Override
 public int hashCode()
 {
   return toString().hashCode();
 }

 @Override
 public boolean equals(Object o)
 {
   return o.hashCode() == hashCode();
 }


  /** Prints a Guid like this: "8e27c92b-1264-101c-ffffff8a2f-42240ffffff9c2" */
  @Override
  public String toString() {
    return toZeroPaddedHexString(d1, 8) + "-" + 
      toZeroPaddedHexString((int) d2, 4) + "-" + 
      toZeroPaddedHexString((int) d3, 4) + "-" + 
      toZeroPaddedHexString((int) d40, 2) +
      toZeroPaddedHexString((int) d41, 2) + "-" + 
      toZeroPaddedHexString((int) d42, 2) +
      toZeroPaddedHexString((int) d43, 2) +
      toZeroPaddedHexString((int) d44, 2) +
      toZeroPaddedHexString((int) d45, 2) +
      toZeroPaddedHexString((int) d46, 2) +
      toZeroPaddedHexString((int) d47, 2);
  }

}
