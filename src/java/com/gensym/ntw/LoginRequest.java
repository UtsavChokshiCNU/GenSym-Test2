/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 LoginRequest.java
 *
 */
package com.gensym.ntw;

import java.util.Locale;
import java.net.InetAddress;
import java.nio.charset.Charset;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

import com.gensym.util.Symbol;
import com.gensym.util.UnexpectedException;
import com.gensym.message.*;
import com.gensym.core.GensymApplication;

/** This should only be Serialized over secure sockets.
 */
public class LoginRequest implements java.io.Serializable {
  
  private static final Symbol ADMINISTRATOR_ = Symbol.intern ("ADMINISTRATOR");

  Symbol userMode;
  Symbol userName;
  transient Symbol userPassword; // encrypted at some point
  String encodedPassword;
  String sessionNonce;
  Symbol language;
  String hostName;
  Symbol osType;
  String userNameFromSystem;
  String okFile;

  public LoginRequest() {
    this (ADMINISTRATOR_);
  }

  public LoginRequest(Symbol userMode) {
    this(userMode, null, null, null);
  }

  public LoginRequest(Symbol userMode,
		      Symbol userName,
		      Symbol userPassword) { // encrypted at some point
    this(userMode, userName, userPassword, null);
  }

  public LoginRequest(Symbol userMode,
		      Symbol userName,
		      Symbol userPassword,
		      String okFile) {
    this.userMode = userMode == null ? ADMINISTRATOR_ : userMode;
    this.userName = userName;
    userNameFromSystem = System.getProperty ("user.name");
    if (userName == null) {
      if (userNameFromSystem != null)
	this.userName = Symbol.intern (userNameFromSystem.toUpperCase());
      //System.out.println ("USER NAME = " + this.userName + "\nName from system = <" + userNameFromSystem + ">");
    }
    this.userPassword = userPassword;
    initializeClientData();
    if (okFile!=null)
      this.okFile = okFile;
    else
      this.okFile = lookForDefaultOKFile();
    //  These two lines are convenient for tracking all the various instances
    //  of LoginRequests that are made and where from.
    //System.out.println("Made a LoginRequest with okFile = \"" + this.okFile + "\" at:");
    //Thread.dumpStack();
  }

  /* We get here if there was no -ok argument on the command line.
   * If this is a named T2 there will be a specification of the location 
   * of the ok file included in the properties file, and thence
   * incorporated into the System properties by GensymApplication.
   */
  private String lookForDefaultOKFile() {
    // make sure the properties file has been read. This call is
    // cheap for every call after the first
    GensymApplication.initialize();
    return System.getProperty("com.gensym.resources.okFile", null);
  }

  private void initializeClientData() {
    language = determineLanguage();

    // may not be possible due to applet security
    hostName = determineHostName();
    osType = determineOsType();
  }

  private static Symbol determineLanguage() {
    Locale locale = Resource.getDefaultLocale();
    locale = (locale == null ? Locale.getDefault() : locale);

    return Symbol.intern(locale.getDisplayLanguage().toUpperCase());
  }

  private static String determineHostName() {
    try {
      return InetAddress.getLocalHost().getHostName();
    } catch (SecurityException se) {
      Trace.exception(se);
      return null;
    } catch (java.net.UnknownHostException uhe) {
      Trace.exception(uhe);
      return null;
    }
  }

  private static final String WINDOWS_SUBSTRING = "windows";

  public static final Symbol WIN32_ = Symbol.intern ("WIN32");
  public static final Symbol UNIX_ = Symbol.intern ("UNIX");

  private static Symbol determineOsType() {
    try {
      String osName = System.getProperty("os.name").toLowerCase();
      if (osName.indexOf(WINDOWS_SUBSTRING) != -1)
	return WIN32_;
      else return UNIX_;
    } catch (SecurityException se) {
      Trace.exception(se);
      return null;
    }
  }

  String getNonce() {
    return sessionNonce;
  }

  private static final byte[] NONCE = ":nonce:".getBytes(Charset.defaultCharset());
  void setNonce(String nonce) {
    try {
      sessionNonce = nonce;

      if (userPassword == null) {
	encodedPassword = null;
	return;
      }

      String userDigest = digestUser();
      
      MessageDigest md = MessageDigest.getInstance("MD5");
      
      md.reset();
      Charset charset = Charset.defaultCharset();
      md.update(userDigest.getBytes(charset));
      md.update(NONCE);
      md.update(nonce.getBytes(charset));

      encodedPassword = toHex(md.digest());

      //encodedPassword = new String(md.digest());
    } catch (NoSuchAlgorithmException nsae) {
      throw new UnexpectedException(nsae);
    }
  }

  private static final byte[] USER = "user:".getBytes(Charset.defaultCharset());
  private static final byte[] PASSWORD = ":password:".getBytes(Charset.defaultCharset());

  private String digestUser()
  throws NoSuchAlgorithmException {

    MessageDigest md = MessageDigest.getInstance("MD5");
    Charset charset = Charset.defaultCharset();
    // This is exactly how G2 hashes the username and password
    md.reset();
    md.update(USER);
    md.update(userName.getPrintValue().toLowerCase().getBytes(charset));
    md.update(PASSWORD);
    md.update(userPassword.getPrintValue().toLowerCase().getBytes(charset));
    
    byte[] digest = md.digest();
    
    return toHex(digest);
  }

  private String toHex(byte[] bytes) {
    int length = bytes.length;

    StringBuffer buf = new StringBuffer();

    for (int i = 0; i < length; i++) {
      int bite = bytes[i];
      if (bite < 0)
	bite = 256 + bite;
      
      if (bite < 16)
	buf.append("0");
      
      buf.append(Integer.toHexString(bite));
    }

    return buf.toString();
  }

  /**
   * Returns the result of hashing the password with the userName,
   * userPassword and the nonce.
   * @undocumented
   */
  public String getEncodedPassword() {
    return encodedPassword;
  }

  /** Returns the user mode of this request.
   */
  public Symbol getUserMode() {
    return userMode;
  }

  /** Returns the user name of this request.
   */
  public Symbol getUserName() {
    return userName;
  }

  @Override
  public String toString () {
    return getClass().getName() + "(" + userMode + ":" + userName + ":" +
      ":" + language + ":" + hostName + ":" + osType + ")";
  }
}
