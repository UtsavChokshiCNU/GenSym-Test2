/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TwConnectionInfo.java
 *
 */
package com.gensym.ntw;

import com.gensym.jgi.G2ConnectionInfo;

/**
 * The class of connection info that is geared towards
 * making TwGateway/Telewindows2 connections.
 */
public class TwConnectionInfo extends G2ConnectionInfo {
  static final long serialVersionUID = -1546687557110380722L;
  public TwConnectionInfo() {
    this(null, null, null);
  }

  public TwConnectionInfo (String hostName, String portName) {
    this (null, hostName, portName); // URL = null
  }

  public TwConnectionInfo (String brokerURL, String hostName,
			   String portName) {
    this (brokerURL, 
	  hostName, 
	  portName, 
	  (brokerURL == null ? TwGateway.DEFAULT_TWO_TIER_CLASS_NAME :
	   TwGateway.DEFAULT_RMI_CLASS_NAME),
	  "UI-CLIENT-INTERFACE", // CxnClass = GSI-INTERFACE class = null
	  false,
	  true);
  }

  public TwConnectionInfo (String brokerURL, 
			   String hostName,
			   String portName,
			   boolean forceNew,
			   boolean sharable) {
    this (brokerURL, 
	  hostName, 
	  portName, 
	  (brokerURL == null ? TwGateway.DEFAULT_TWO_TIER_CLASS_NAME :
	   TwGateway.DEFAULT_RMI_CLASS_NAME),
	  "UI-CLIENT-INTERFACE", // CxnClass = GSI-INTERFACE class = null
	  forceNew, 
	  sharable); 
  }

  public TwConnectionInfo (String brokerURL, 
			   String hostName, 
			   String portName,
			   String g2ConnectionClassName,
			   String gsiInterfaceClassName,
			   boolean forceNew,
			   boolean sharable) {
    this(brokerURL, null, hostName, portName,
	 g2ConnectionClassName, gsiInterfaceClassName,
	 null, null, null, "", forceNew, sharable);
  }

  public TwConnectionInfo (String brokerURL,
			   String logicalName,
			   String hostName, 
			   String portName,
			   String g2ConnectionClassName,
			   String gsiInterfaceClassName,
			   String interfaceName,
			   String protocol,
			   Boolean isPerm,
			   String rpis,
			   boolean forceNew,
			   boolean sharable) {
    super (brokerURL, logicalName, hostName, portName, g2ConnectionClassName,
	   gsiInterfaceClassName, interfaceName, protocol, isPerm, rpis,
	   forceNew, sharable);
  }

  public TwConnectionInfo (String brokerURL,
			   String logicalName,
			   String hostName, 
			   String portName,
			   String interfaceName,
			   String protocol,
			   Boolean isPerm,
			   String rpis,
			   boolean forceNew,
			   boolean sharable) {
    super (brokerURL,
	   logicalName,
	   hostName,
	   portName,
	  (brokerURL == null ? TwGateway.DEFAULT_TWO_TIER_CLASS_NAME :
	   TwGateway.DEFAULT_RMI_CLASS_NAME),
	  "UI-CLIENT-INTERFACE", // CxnClass = GSI-INTERFACE class = null
	   interfaceName,
	   protocol,
	   isPerm,
	   rpis,
	   forceNew,
	   sharable);
  }
}
