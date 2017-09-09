/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2ConnectionInfo.java
 *
 *  Description:
 *               Connection information
 *
 *	 Author:
 *		Robert Penny, Vikram Pillai	Oct/97
 *
 *     
 *   Modifications:
 *
 */

package com.gensym.jgi;

import java.net.InetAddress;

import com.gensym.message.Resource;

/**
 * A Connection info object contains all the information necessary to get
 * a handle on a specific instance of G2Access (actually G2Gateway).
 * A G2ConnectionInfo object is used as the lookup into a collection of
 * G2Access objects to determine which one matches the requirements of
 * the requested connection. The match is performed by the
 * <code>match(G2ConnectionInfo other)</code> method. This method can be
 * overriden by subclasses to change the semantics of how a valid match
 * is determined. Instances of G2ConnectionInfo are implicitly constructed
 * by <code>getOrMakeConnection</code> in
 * <code>com.gensym.jgi.G2Gateway</code>,
 * <code>com.gensym.rmi.G2RMIAccessBrokerImpl</code>,
 * and <code>com.gensym.ntw.TwGateway</code>
 * @see com.gensym.jgi.G2Gateway#getOrMakeConnection()
 * @see #matches(G2ConnectionInfo other)
 */
public class G2ConnectionInfo implements java.io.Serializable {
  static final long serialVersionUID = 53867498537949282L;
  private static Resource i18n =
  Resource.getBundle("com.gensym.jgi.Messages");
  //  public static final String TCP_IP = "TCP_IP";
  public static final String LOCALHOST = "localhost";
  public static final String DEFAULT_HOST = LOCALHOST;
  public static final String DEFAULT_PORT  = "1111";
  public static final String DEFAULT_CONNECTION_CLASS_NAME =
  "com.gensym.jgi.G2Access";
  public static final String DEFAULT_GSI_INTERFACE_CLASS_NAME = "GSI-INTERFACE";
  public static final String GSI_PROTOCOL = "GSI";
  public static final String RMI_PROTOCOL = "RMI";

  public static final Boolean SHARABLE_TRUE = Boolean.TRUE;
  public static final Boolean SHARABLE_FALSE = Boolean.FALSE;
  public static final Boolean FORCENEW_TRUE = Boolean.TRUE;
  public static final Boolean FORCENEW_FALSE = Boolean.FALSE;
  public static final Boolean SECURE_TRUE = Boolean.TRUE;
  public static final Boolean SECURE_FALSE = Boolean.FALSE;

  public static final Boolean DEFAULT_SHARABLE = SHARABLE_TRUE;
  public static final Boolean DEFAULT_FORCENEW = FORCENEW_FALSE;
  public static final Boolean DEFAULT_SECURE = SECURE_FALSE;

  private static volatile String
  defaultLogicalName,
    defaultBrokerURL,
    defaultConnectionClassName = DEFAULT_CONNECTION_CLASS_NAME,
    defaultGsiInterfaceClassName = DEFAULT_GSI_INTERFACE_CLASS_NAME,
    defaultProtocol, defaultHostName, defaultPortName, defaultRpis;

  
  private String      brokerURL;
  private String      logicalName;
  private String      hostName;
  private String      portName;
  private String      connectionClassName;
  private String      gsiInterfaceClassName;
  private String      interfaceName;
  private String      protocol;
  //private String      network;
  private Boolean     isPerm;
  private String      rpis;
  private Boolean    sharable = DEFAULT_SHARABLE;
  private Boolean    forceNew = DEFAULT_FORCENEW;
  private Boolean    secure = DEFAULT_SECURE;

  private InetAddress host;
  private int         port;
  //  The following could be used to optimize .equals()
  //  private final int   connectionUID;
  private int   internalHashcode;
  private boolean hashCodeIsSet = false;

  public G2ConnectionInfo() {
  }

  /** Make a simple G2ConnectionInfo with minimal specifications
   * as to what kind of connection it is.
   * @param hostName the network name of the computer on which the desired
   * G2 is running.
   * @param portName the port number at which the G2 is listening for GSI
   * connections (as a String).
   */
  public G2ConnectionInfo (String hostName, String portName) {
    this (null, hostName, portName); // URL = null
  }

  /** Make a simple G2ConnectionInfo with minimal specifications
   * as to what kind of connection it is, allowing secure connection (on
   * those platforms where security is supported).
   * @param hostName the network name of the computer on which the desired
   * G2 is running.
   * @param portName the port number at which the G2 is listening for GSI
   * connections (as a String).
   * @param secure true to request SSL security, false otherwise.
   */
  public G2ConnectionInfo (String hostName, String portName, boolean secure) {
    this (null, null, hostName, portName,  // URL = null, logical = null
	  null, null, //g2ConnectionClassName, gsiInterfaceClassName
	  null, // interfaceName
	  null, // protocol
	  null, // isPerm
	  "",   // RPIS
	  DEFAULT_FORCENEW.booleanValue(),  // forceNew
	  DEFAULT_SHARABLE.booleanValue(),  // shareable
	  secure); 
  }

  /** Make a simple G2ConnectionInfo with minimal specifications
   * as to what kind of connection it is.
   * @param brokerURL applicable for a three-tier client: specifies the
   * URL of the middle tier.
   * @param hostName the network name of the computer on which the desired
   * G2 is running.
   * @param portName the port number at which the G2 is listening for GSI
   * connections (as a String).
   */
  public G2ConnectionInfo (String brokerURL, String hostName,
			   String portName) {
    this (brokerURL, 
	  hostName, 
	  portName, 
	  null, // connectionClassName
	  null, // gsiInterfaceClassName
	  DEFAULT_FORCENEW.booleanValue(),  // forceNew
	  DEFAULT_SHARABLE.booleanValue()); // shareable
  }

  /** Make a simple G2ConnectionInfo with minimal specifications
   * as to what kind of connection it is.
   * @param brokerURL applicable for a three-tier client: specifies the
   * URL of the middle tier.
   * @param hostName the network name of the computer on which the desired
   * G2 is running.
   * @param portName the port number at which the G2 is listening for GSI
   * connections (as a String).
   * @param forceNew set true to force a new connection, even if there is already a connection
   *           open that matches these settings
   * @param sharable if true (default), the G2Connection created is allowed to be shared
   *           (i.e. getOrMakeConnection() will return the same open G2Connection if 
   *            it's G2ConnectionInfo match). 
   */
  public G2ConnectionInfo (String brokerURL, 
			   String hostName,
			   String portName,
			   boolean forceNew,
			   boolean sharable) {
    this (brokerURL, 
	  hostName, 
	  portName, 
	  null, // connectionClassName
	  null, // gsiInterfaceClassName
	  forceNew, 
	  sharable); 
  }

  /** @param brokerURL applicable for a three-tier client: specifies the
   * URL of the middle tier.
   * @param logicalName allows application builders to associate a logical name
   * with a specific combination of other parameters. This can be useful if
   * the host and port for a given "logical g2" may change for some reason.
   * @param hostName the network name of the computer on which the desired
   * G2 is running.
   * @param portName the port number at which the G2 is listening for GSI
   * connections (as a String).
   * @param connectionClassName the name of the Java class for the resulting
   * connection. This Java class must implement com.gensym.jgi.G2Connection
   * @param gsiInterfaceClassName the subclass of GSI-INTERFACE to be created
   * to handle the connection from the G2 side.
   * @param forceNew set true to force a new connection, even if there is already a connection
   *           open that matches these settings
   * @param sharable if true (default), the G2Connection created is allowed to be shared
   *           (i.e. getOrMakeConnection() will return the same open G2Connection if 
   *            its G2ConnectionInfo matches). 
   */
  public G2ConnectionInfo (String brokerURL, 
			   String hostName, 
			   String portName,
			   String g2ConnectionClassName,
			   String gsiInterfaceClassName,
			   boolean forceNew,
			   boolean sharable) {
    this (brokerURL, null, hostName, portName, g2ConnectionClassName,
	  gsiInterfaceClassName,
	  null, // interfaceName
	  null, // protocol
	  null, // isPerm
	  "",   // RPIS
	  forceNew,
	  sharable);
    internalHashcode = generateHashcode();
  }

  /** @param brokerURL applicable for a three-tier client: specifies the
   * URL of the middle tier.
   * @param logicalName allows application builders to associate a logical name
   * with a specific combination of other parameters. This can be useful if
   * the host and port for a given "logical g2" may change for some reason.
   * @param hostName the network name of the computer on which the desired
   * G2 is running.
   * @param portName the port number at which the G2 is listening for GSI
   * connections (as a String).
   * @param connectionClassName the name of the Java class for the resulting
   * connection. This Java class must implement com.gensym.jgi.G2Connection
   * @param gsiInterfaceClassName the subclass of GSI-INTERFACE to be created
   * to handle the connection from the G2 side.
   */
  public G2ConnectionInfo (String brokerURL, String hostName, String portName,
			   String g2ConnectionClassName,
			   String gsiInterfaceClassName) {
    this (brokerURL, null, hostName, portName, g2ConnectionClassName,
	  gsiInterfaceClassName,
	  null, // interfaceName
	  null, // protocol
	  null, // isPerm
	  "",   // RPIS
	  DEFAULT_FORCENEW.booleanValue(),  // forceNew
	  DEFAULT_SHARABLE.booleanValue()); // shareable
    internalHashcode = generateHashcode();
  }

  /** Full featured constructor for exact specifications of all aspects of
   * the connection, excepting forceNew and sharable.
   * @param brokerURL applicable for a three-tier client: specifies the
   * URL of the middle tier.
   * @param logicalName allows application builders to associate a logical name
   * with a specific combination of other parameters. This can be useful if
   * the host and port for a given "logical g2" may change for some reason.
   * @param hostName the network name of the computer on which the desired
   * G2 is running.
   * @param portName the port number at which the G2 is listening for GSI
   * connections (as a String).
   * @param connectionClassName the name of the Java class for the resulting
   * connection. This Java class must implement com.gensym.jgi.G2Connection
   * @param gsiInterfaceClassName the subclass of GSI-INTERFACE to be created
   * to handle the connection from the G2 side.
   * @param interfaceName the name given to the instance of GSI-INTERFACE
   * @param protocol only "GSI" and "RMI" are supported at the moment.
   * @param isPerm is the connection to be permananent
   * (usually <code>true</code>)
   * @param rpis Remote Procedure Identification String. */
  public G2ConnectionInfo (String brokerURL,
			   String logicalName,
			   String hostName,
			   String portName,
			   String connectionClassName,
			   String gsiInterfaceClassName,
			   String interfaceName,
			   String protocol,
			   Boolean isPerm,
			   String rpis) {
    this (brokerURL, logicalName, hostName, portName, connectionClassName,
	  gsiInterfaceClassName, interfaceName, protocol, isPerm, rpis, 
	  DEFAULT_FORCENEW.booleanValue(),  // forceNew
	  DEFAULT_SHARABLE.booleanValue()); // shareable
    internalHashcode = generateHashcode();
  }

  /** Constructor for backwards compatibility from before we introduced secure.
   * @param brokerURL applicable for a three-tier client: specifies the
   * URL of the middle tier.
   * @param logicalName allows application builders to associate a logical name
   * with a specific combination of other parameters. This can be useful if
   * the host and port for a given "logical g2" may change for some reason.
   * @param hostName the network name of the computer on which the desired
   * G2 is running.
   * @param portName the port number at which the G2 is listening for GSI
   * connections (as a String).
   * @param connectionClassName the name of the Java class for the resulting
   * connection. This Java class must implement com.gensym.jgi.G2Connection
   * @param gsiInterfaceClassName the subclass of GSI-INTERFACE to be created
   * to handle the connection from the G2 side.
   * @param interfaceName the name given to the instance of GSI-INTERFACE
   * @param protocol only "GSI" and "RMI" are supported at the moment.
   * @param isPerm is the connection to be permananent
   * (usually <code>true</code>)
   * @param rpis Remote Procedure Identification String.
   * @param forceNew set true to force a new connection, even if there is already a connection
   *           open that matches these settings
   * @param sharable if true (default), the G2Connection created is allowed to be shared
   *           (i.e. getOrMakeConnection() will return the same open G2Connection if 
   *            its G2ConnectionInfo matches). */
  public G2ConnectionInfo (String brokerURL,
			   String logicalName,
			   String hostName,
			   String portName,
			   String connectionClassName,
			   String gsiInterfaceClassName,
			   String interfaceName,
			   String protocol,
			   Boolean isPerm,
			   String rpis,
			   boolean forceNew,
			   boolean sharable) {

    this (brokerURL, logicalName, hostName, portName, connectionClassName,
	  gsiInterfaceClassName, interfaceName, protocol, isPerm, rpis, 
	  forceNew, sharable,
	  DEFAULT_SECURE.booleanValue()); // secure
    internalHashcode = generateHashcode();
  }

  /** Full featured constructor for exact specifications of all aspects of
   * the connection.
   * @param brokerURL applicable for a three-tier client: specifies the
   * URL of the middle tier.
   * @param logicalName allows application builders to associate a logical name
   * with a specific combination of other parameters. This can be useful if
   * the host and port for a given "logical g2" may change for some reason.
   * @param hostName the network name of the computer on which the desired
   * G2 is running.
   * @param portName the port number at which the G2 is listening for GSI
   * connections (as a String).
   * @param connectionClassName the name of the Java class for the resulting
   * connection. This Java class must implement com.gensym.jgi.G2Connection
   * @param gsiInterfaceClassName the subclass of GSI-INTERFACE to be created
   * to handle the connection from the G2 side.
   * @param interfaceName the name given to the instance of GSI-INTERFACE
   * @param protocol only "GSI" and "RMI" are supported at the moment.
   * @param isPerm is the connection to be permananent
   * (usually <code>true</code>)
   * @param rpis Remote Procedure Identification String. 
   * @param forceNew set true to force a new connection, even if there is already a connection
   *           open that matches these settings
   * @param sharable if true (default), the G2Connection created is allowed to be shared
   *           (i.e. getOrMakeConnection() will return the same open G2Connection if 
   *            it's G2ConnectionInfo match). 
   * @param secure if true, the G2Connection created will use SSL encryption to 
   *           write to the G2 connection.  Not available in 3-tier mode. 
   *           Not available on all platforms
   */
  public G2ConnectionInfo (String brokerURL,
			   String logicalName,
			   String hostName,
			   String portName,
			   String connectionClassName,
			   String gsiInterfaceClassName,
			   String interfaceName,
			   String protocol,
			   Boolean isPerm,
			   String rpis,
			   boolean forceNew,
			   boolean sharable,
			   boolean secure) {

    this.brokerURL = brokerURL;
    this.hostName = hostName;
    this.portName = portName;
    this.connectionClassName = connectionClassName;
    this.gsiInterfaceClassName = gsiInterfaceClassName;
    this.interfaceName = interfaceName;
    this.protocol = protocol;
    this.isPerm  = isPerm;
    this.rpis    = rpis;
    this.sharable = (sharable ? SHARABLE_TRUE : SHARABLE_FALSE);
    this.forceNew = (forceNew ? FORCENEW_TRUE : FORCENEW_FALSE);
    this.secure = (secure ? SECURE_TRUE : SECURE_FALSE);
    //System.out.println("newG2ConnectionInfo: " + toString());
    //Thread.dumpStack();
    initialize();
    internalHashcode = generateHashcode();
  }

  /** Called by the constructor to determine internal consistency and
   * fill in certain defaults.
   * The main consistency check currently performed is brokerURL/protocol
   * consistency:
   * A null brokerURL implies the GSI_PROTOCOL, while a non-null brokerURL
   * implies the RMI_PROTOCOL.
   */
  protected void initialize() {
    try {
      //      this.host = (hostName == null ? null :
      //	   InetAddress.getByName (hostName));
      this.port = ((portName == null) ? -1 :
		   Integer.parseInt (portName));
    } catch (Exception e) {
      //System.out.println("Bad port number: " + portName);
      e.printStackTrace();
      throw new IllegalArgumentException (e.toString ());
    }
    
    if (brokerURL == null) {
      if (protocol == null) {
	protocol = GSI_PROTOCOL;
      } else if (!protocol.equals(GSI_PROTOCOL)) {
	throw new
	  IllegalArgumentException(i18n.format("g2ciProtocolURLMismatch",
					       protocol, brokerURL));
      }
    } else if (defaultProtocol == null || GSI_PROTOCOL.equals(defaultProtocol)) {
      protocol = RMI_PROTOCOL;
    }
  }

  private final int hashPart(Object part) {
    return (part == null ? 1 : part.hashCode());
  }

  /** Expensive: cache this hashcode */
  private int generateHashcode() {
    return
      hashPart(brokerURL) |
      hashPart(logicalName) |
      hashPart(hostName) |
      hashPart(portName) |
      hashPart(gsiInterfaceClassName) |
      hashPart(connectionClassName) |
      hashPart(protocol) |
      hashPart(rpis) |
      hashPart(forceNew) |
      hashPart(sharable);
  }

  /** Returns a cached hashcode based on all the string variables in the
   * G2ConnectionInfo object. */
  @Override
  public int hashCode() {
    if (hashCodeIsSet)
      return internalHashcode;
    else {
      internalHashcode = generateHashcode();
      return internalHashcode;
    }
  }

  /** A field by field match of two G2ConnectionInfo objects of the same
   * class.
   */
  @Override
  public boolean equals(Object obj) {
    if (obj == null ||
	(!getClass().equals(obj.getClass()))) {
      return false;
    }
    
    G2ConnectionInfo other = (G2ConnectionInfo)obj;
    
    boolean isURLInfoMatched = compareWithNulls(brokerURL, other.brokerURL) &&
					  	      compareWithNulls(logicalName, other.logicalName) &&
					  	      compareWithNulls(hostName, other.hostName) &&
					  	      compareWithNulls(portName, other.portName);
  
  boolean isConnectionInfoMatched = compareWithNulls(connectionClassName, other.connectionClassName) &&
  								compareWithNulls(gsiInterfaceClassName, other.gsiInterfaceClassName) &&
  								compareWithNulls(protocol, other.protocol) &&
  								compareWithNulls(rpis, other.rpis);
  
  return isURLInfoMatched &&
		isConnectionInfoMatched &&
    	compareWithNulls(forceNew, other.forceNew) &&
    	compareWithNulls(sharable, other.sharable);
  }

  /** Does a match based on all the string variables and returns true
   * if all of those "match" using compareWithNulls(Object, Object, Object),
   * false otherwise.
   *
   * Not strictly true: if the logicalName is non-null for both
   * G2ConnectionInfo objects, then if the logicalNames
   * match, it returns true without checking the other fields.
   *
   * @see #compareWithNulls(Object, Object, Object);
   * @see #compareConnectionClassNames() */
  public boolean matches(G2ConnectionInfo other) {
    if (other == null)
      return false;

    /* Robert, this always returns true for logicalName and brokerURL = null -vkp, 12/2/97
       This results in only one connection ever being created.
       Am commenting out for now...
    if (compareWithNulls(logicalName, other.logicalName))
      return compareWithNulls(brokerURL, other.brokerURL, defaultBrokerURL);
      */
    
    // We do not have a match if this ConnectionInfo is not sharable
    if (!sharable.booleanValue())
      return false;

    boolean isURLInfoMatched = compareWithNulls(brokerURL, other.brokerURL, defaultBrokerURL) &&
    	      compareWithNulls(logicalName, other.logicalName) &&
    	      compareWithNulls(hostName, other.hostName, DEFAULT_HOST) &&
    	      compareWithNulls(portName, other.portName, DEFAULT_PORT);
    
    boolean isConnectionInfoMatched = compareWithNulls(connectionClassName, other.connectionClassName,
		    								defaultConnectionClassName) &&
    								compareWithNulls(gsiInterfaceClassName, other.gsiInterfaceClassName,
    										defaultGsiInterfaceClassName) ;
    return isURLInfoMatched &&
      isConnectionInfoMatched &&
      compareWithNulls(protocol, other.protocol, defaultProtocol) &&
      compareWithNulls(rpis, other.rpis, defaultRpis);
  }

  /** The URL to the remote rmiregistry. Used in a three-tier connection using
   * RMI */
  public String getBrokerURL() {
    return brokerURL;
  }

  /** Allows applications to specify a logical name that represents a
   * (possibly changing) specific combination of the other variables.
   */
  public String getLogicalName() {
    return logicalName;
  }

  public String getHost() {
    return hostName;
  }

  public String getPort() {
    return portName;
  }

  public boolean getSecure() {
    return secure.booleanValue();
  }

  /** Specifies what class the actual connection to G2 should be.
   * Currently does no internal verification that this is a valid class,
   * but it is recommended that this be at least an implementation of
   * com.gensym.jgi.G2Access, and most likely a subclass of
   * com.gensym.jgi.G2Gateway */
  public String getConnectionClassName() {
    return connectionClassName;
  }

  /** This is the name of the GSI-INTERFACE subclass to be used for the
   * connection within G2. */
  public String getGsiInterfaceClassName() {
    return gsiInterfaceClassName;
  }

  /** This is the name of the GSI-INTERFACE instance to be used for the
   * connection within G2. */
  public String getGsiInterfaceName() {
    return interfaceName;
  }

  /**
   * @deprecated use getGsiInterfaceName
   * @see #getGsiInterfaceName
   */
  public String getInterfaceName() {
    return getGsiInterfaceName();
  }

  /** Currently only RMI_PROTOCOL (three-tier) and GSI_PROTOCOL (two-tier)
   * are recognized */
  public String getProtocol() {
    return protocol;
  }

  /** Remote Procedure Identification String.
   * @deprecated use getRemoteProcessInitString
   * @see #getRemoteProcessInitizationString*/
  public String getRpis() {
    return getRemoteProcessInitString();
  }

  /**
   * Remote Procedure Initialization String.
   */
  public String getRemoteProcessInitString() {
    return rpis;
  }    

  public Boolean getPermanent() {
    return isPerm;
  }

  /** Is the G2Connection created from this G2ConnectionInfo, sharable */
  public boolean isSharable() {
    return sharable.booleanValue();
  }

  /** Will this G2ConnectionInfo always create a new connection */
  public boolean isForceNew() {
   return forceNew.booleanValue();
  }

  //
  // SETTING/GETTING DEFAULTS
  //

  public static void setDefaultBrokerURL(String brokerURL) {
    defaultBrokerURL = brokerURL;
  }

  public static void setDefaultLogicalName(String logicalName) {
    defaultLogicalName = logicalName;
  }

  public static void setDefaultHostName(String hostName) {
    defaultHostName = hostName;
  }

  public static void setDefaultPortName(String portName) {
    defaultPortName = portName;
  }

  public static void setDefaultConnectionClassName(String connectionClassName) {
    defaultConnectionClassName = connectionClassName;
  }

  public static void setDefaultGsiInterfaceClassName(String gsiInterfaceClassName) {
    defaultGsiInterfaceClassName = gsiInterfaceClassName;
  }

  public static void setDefaultProtocol(String protocol) {
    defaultProtocol = protocol;
  }

  /** Remote Procedure Identification String */
  public static void setDefaultRpis(String rpis) {
    defaultRpis = rpis;
  }


  //
  // UTILITY METHODS
  //
  
  /** Returns <code>true</code> if <code>localValue.equals(otherValue)
   * </code> where a null value for <code>otherValue</code> are treated
   * as matching with <code>defaultValue</code>, while a null value for
   * <code>localValue</code> automatically return true. */
  public static final boolean
  compareWithNulls(Object localValue, Object otherValue, Object defaultValue) {
    if (localValue == null)
      return true;
    // The following is a more narrow possibility
    //return ((otherValue == null) || otherValue.equals(defaultValue));

    if (otherValue == null)
      return localValue.equals(defaultValue);
    
    return localValue.equals(otherValue);
  }

  /** Utility field comparator for .equals().
   * Returns <code>true</code> if <code>localValue.equals(otherValue)
   * </code> or if both are null. */
  public static final boolean
  compareWithNulls(Object localValue, Object otherValue) {
    if (localValue == null)
      return otherValue == null;
    return localValue.equals(otherValue);
  }

  private String stringValue;
  @Override
  public String toString() {
    if (stringValue == null)
      stringValue = getClass().getName() + ": " +
	brokerURL + "|" +
	logicalName + "|" +
	hostName +"|" +
	portName + "|" +
	connectionClassName + "|" +
	gsiInterfaceClassName + "|" +
	interfaceName + "|" +
	protocol + "|" +
	isPerm + "|" +
	rpis + "|" +
	forceNew + "|" +
	sharable;
      
    return stringValue;
  }

}
