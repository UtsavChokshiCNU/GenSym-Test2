/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.ActiveXNullException.java
 *
 *   Author: Stephen Flores
 */
package com.gensym.com;

/* This not really an ActiveX exception, it is just a way to send a per
   version license authentication string from Java to the native license
   checking code. The class will only be shipped in the licensed version.
   The native code will try to get the class, create an instance and
   check for the proper per version message. */
class ActiveXNullException extends ActiveXException {

  /* Zero argument constructor. */
  ActiveXNullException() {
    super("114252");
  }

  /* Since all the other exceptions have this, to help disguise the licecse
     code, we have a string constructor, but it do not create an object that
     will pass the native license check. */
  ActiveXNullException(String message) {
    super();
  }
}
