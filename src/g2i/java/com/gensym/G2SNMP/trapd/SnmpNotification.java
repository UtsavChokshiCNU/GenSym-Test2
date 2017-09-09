/*
 * SnmpNotification.java
 *
 * Created on August 2, 2000, 4:09 PM
 */

package com.gensym.G2SNMP.trapd;

import com.adventnet.snmp.snmp2.*;
import com.gensym.util.Sequence;
import com.gensym.G2SNMP.rpc.*;
import java.net.*;
import com.gensym.G2SNMP.util.DNSLookup;

/**
 *  The SnmpNotification class applies the Facade design pattern to the 
 *  problem of interfacing to and extracting information from three (or more) 
 *  different types of SNMP notifications: SNMPv1 trap, SNMPv2 trap, and 
 *  SNMPv2 INFORM. The interface parallels the parameters that are passed back 
 *  G2, providing the proper types.
 *
 * @author  Hank Streeter
 * @version 2-Aug-2000
 */

public class SnmpNotification
{
    private SnmpPDU     notification;               //  Supplied notification
    private byte        notificationType;           //  Type of this instance v1 or v2 trap, or INFORM
    private boolean     varBindsScanned = false;    //  Indicates whether the varbinds have been scanned for 
                                                    //  embedded trap PDU information
    private int         isEnterpriseSpecific = -1;  //  Indicates whether this notification is enterprise-
                                                    //  specific (1), not (0), or undetermined (-1).
    private final int   SYS_UP_TIME_VARBIND = 0;    
    private final int   SNMP_TRAP_OID_VARBIND = 1;
    private final int   MIN_SNMPV2_LAST_VARBIND_INDEX = SNMP_TRAP_OID_VARBIND;
    
    private final String    SNMP_TRAP_OID = ".1.3.6.1.6.3.1.1.4.1";
    private final String    SNMP_TRAP_ENTERPRISE = ".1.3.6.1.6.3.1.1.4.3";
    private final String    PRIVATE_ENTERPRISES = ".1.3.6.1.4.1";
    private final int       ENTERPRISE_SUBID_START_INDEX = 13; 
    
    private final String    SNMPV2_TRAPS = ".1.3.6.1.6.3.1.1.5";
    private final int       SNMPV2_GENERIC_TYPE = 19;
  	//public static boolean ALWAYS_RESOLVE_NAME = true;
	  //public static void set_always_resolve_name (boolean resolveName){
	  //	ALWAYS_RESOLVE_NAME = resolveName;
	  //}

    /** Creates new SnmpNotification from the supplied PDU */
    public SnmpNotification( SnmpPDU aNotification ) 
    {    
        //  Confirm that the supplied PDU is indeed one of the notification
        //  types: SNMPv1 trap, SNMPv2 trap, SNMPv2 INFORM.
        
        if ( !( ( aNotification.getCommand() == SnmpAPI.TRP_REQ_MSG ) ||
                ( aNotification.getCommand() == SnmpAPI.TRP2_REQ_MSG ) ||
                ( aNotification.getCommand() == SnmpAPI.INFORM_REQ_MSG ) ) )
           System.out.println( "ERROR: Cannot create SnmpNotificationPDU from supplied PDU." );
        else 
        {
            notification = aNotification;
            notificationType = notification.getCommand();
        }
    }

    /** Answer the error status of the notifiaction.                        */
    public Integer getErrorStatus()
    {
        return notification.getErrstat();
    }

    /** Answer the error string corresponding to the error status of this
        notification                                                        */
    public String getErrorString()
    {
        return SnmpException.exceptionString( (byte)notification.getErrstat() );
    }

    /** Answer the request ID for the notification.                         */
    public String getRequestID()
    {
        return TypeConverter.fixResultID( notification.getReqid() );
    }

    /** Answer the SNMP version for the notification.                       */
    public Integer getVersion()
    {
        return notification.getVersion();
    }
 
    /** Scan the varbinds in the notification for notification definition
        information. This includes sysUpTime, enterpriseID, trap OID, and
        generic and specific types. This is done here in a single method
        in order to minimize the amount of varbind list processing. This
        method is invoked by any of the other accessor methods for the 
        aforementioned information, and is only invoked once.               */
    private void scanVarBinds()
    {
        if ( !varBindsScanned )
        {
            varBindsScanned = true;
        }
        else
            return;
    }

    /** Answer the enterprise OID for the notification. This is a standard
        field in SNMPv1 traps. In SNMPv2 traps and INFORMs, the enterprise
        must be extracted from one of the following locations:
        (1) The last varbind in the trap. If the last varbind has an OID
            of .1.3.6.1.6.3.1.1.4.3, use the corresponding variable value.
        (2) The snmpTrapOID varbind, the second in the trap. If the
            corresponding varible contains the 'private enterprises'
            prefix .1.3.6.1.4.1, then .1.3.6.1.4.1.x is the
            enterprise.
        (3) If this is a 'standard' trap (e.g. coldStart), then the
            concept of 'enterprise' is not applicable.                      */

    public String getEnterprise()
    {
        String varbindlist;

        if ( notificationType == SnmpAPI.TRP_REQ_MSG )
            return notification.getEnterprise().toString();
        else if ( ( notificationType == SnmpAPI.TRP2_REQ_MSG ) ||
                  ( notificationType == SnmpAPI.INFORM_REQ_MSG ) )
        {
            // testing
            //System.out.println ("Received a TRP2_REQ_MSG or an INFORM_REQ_MSG");
            //varbindlist = notification.printVarBinds ();
            //System.out.println ("Varbinds:\n"+ varbindlist);
            //  Per RFC1907, check the last varbind to see if its OID defines
            //  the snmpTrapEnterprise, .1.3.6.1.6.3.1.1.4.3. If it does, use
            //  the corresponding variable value.

            int lastVarBindIndex = notification.getVariableBindings().size() - 1;
            //System.out.println ("LastVarBindIndex: " + notification.getVariable (lastVarBindIndex));
            if ( notification.getObjectID( lastVarBindIndex ).toString().startsWith( SNMP_TRAP_ENTERPRISE ) )
            {
                return ( (SnmpOID)( notification.getVariable( lastVarBindIndex ) ) ).toString();
            }
            else
            {
                //  If the last varbind is NOT the snmpTrapEnterprise, then check
                //  the second varbind, the snmpTrapOID, to see if it contains
                //  .1.3.6.1.4.1, defining .private.enterprises. If it does,
                //  extract the portion of the OID up to the enterprise ID
                //  (one subidentifier beyond the end of the .private.enterprises).
                //  Otherwise, this is a standard SNMPv2 trap and the
                //  enterprise is not applicable.

                //System.out.println ("ObjectID [1]= " + notification.getObjectID (SNMP_TRAP_OID_VARBIND));
                //System.out.println ("Variable [1] = " + notification.getVariable (SNMP_TRAP_OID_VARBIND));
                if ( notification.getObjectID( SNMP_TRAP_OID_VARBIND ).toString().startsWith( SNMP_TRAP_OID ) )
                {
                    String value = ( (SnmpOID)( notification.getVariable( SNMP_TRAP_OID_VARBIND ) ) ).toString();
                    System.out.println ("value = " + value);
                    if (value.startsWith (SNMPV2_TRAPS))
                    {
                        return SNMPV2_TRAPS;
                    }
                    else
                    {
                        // 3/6/01 WSM took out due to some traps not having a .0 as part of the value
                        //value = value.substring( 0, ( value.indexOf( ".0" ) ) );
                        return value;
                    }
                }
                else
                {
                    System.out.println( "ERROR: Incorrect OID in snmpTrapOID varbind. \n" +
                                        "       Expected .1.3.6.1.6.3.1.1.4.1 but found: " +
                                        notification.getObjectID( SNMP_TRAP_OID_VARBIND ).toString() + "." );
                    return null;
                }
            }
        }
        else
        {
            return null;
        }  
    }

    /** Answer the address of the agent that generated the notification. This
        is a standard field in SNMPv1 traps, but is NOT a required field in 
        SNMPv2 traps and INFORMs.                                           */
    public String getAgentAddress()
    {
        String hostIdentifier;
        
//        System.out.println( "Entering SnmpNotification.getAgentAddress()..." );
        
        if ( notificationType == SnmpAPI.TRP_REQ_MSG )
        {
//            System.out.println( "Leaving SnmpNotification.getAgentAddress()..." );
          // Added 8/23/02 WSM
          if (TypeConverter.ALWAYS_RESOLVE_NAME)
            return DNSLookup.inetAddrToString( notification.getAgentAddress().getAddress() );
          else
            return notification.getAgentAddr();

			// return notification.getAgentAddress().toString();
		}
		else if ( ( notificationType == SnmpAPI.TRP2_REQ_MSG ) ||
				  ( notificationType == SnmpAPI.INFORM_REQ_MSG ) )
		{
			//  Agent address seems to appear in next-to-last varbind if the
			//  snmpTrapEnterprise varbind is not present.
			//  If the varbind is present, extract the agent 'value.' This
			//  may be a dotted IP address or a hostname. The translation
			//  'agentInfo.toString()' can be slow due to DNS look-up.

			if ( notification.getAgentAddress() != null )
        if (TypeConverter.ALWAYS_RESOLVE_NAME)
  				return notification.getAgentAddress().toString();
        else
          return notification.getAgentAddr();
			else
			{
				int lastVarBindIndex = notification.getVariableBindings().size() - 1;
				if ( lastVarBindIndex > MIN_SNMPV2_LAST_VARBIND_INDEX )     //  Are there more than the minimum number of varbinds?
				{
					//  Check to see if last varbind is the snmpTrapEnterprise varbind.
					//  If not, see if it contains a valid agent address or hostname.
					if ( notification.getObjectID( lastVarBindIndex ).toString().indexOf( SNMP_TRAP_ENTERPRISE, 0 ) < 0 )
					{
						hostIdentifier = notification.getVariable( lastVarBindIndex ).toString();
						try
						{
              // Added 8/23/02 WSM
              if (TypeConverter.ALWAYS_RESOLVE_NAME)
							  return InetAddress.getByName( hostIdentifier ).getHostAddress();
              else
                return hostIdentifier;
						}
						catch ( UnknownHostException eLast )
						{
							//  Check the next-to-last varbind.
							hostIdentifier = notification.getVariable( lastVarBindIndex - 1 ).toString();
							try
							{
                // Added 8/23/02 WSM
                if (TypeConverter.ALWAYS_RESOLVE_NAME)
								  return InetAddress.getByName( hostIdentifier ).getHostAddress();
                else
                  return hostIdentifier;
							}
							catch ( UnknownHostException eNextLast )
							{
								return "Not supplied";
							}
						}
					}
					else   //  Otherwise, check the next-to-last varbind.
					{
						hostIdentifier = notification.getVariable( lastVarBindIndex - 1 ).toString();
						try
						{
              // Added 8/23/02 WSM
              if (TypeConverter.ALWAYS_RESOLVE_NAME)
							  return InetAddress.getByName( hostIdentifier ).getHostAddress();
              else
                return hostIdentifier;
						}
						catch ( UnknownHostException eNextLast )
						{
							return "Not supplied";
						}
					}
				}
				else
				{
					return "Not supplied";
				}
			}
		}
		else
			return null;
	}

	/** Answer the hostname of the agent that generated the notification. This
		is a standard field (via the agent address field) in SNMPv1 traps, but
		is NOT a required field in SNMPv2 traps and INFORMs.                 */
	public String getAgentHostName()
	{
//		System.out.println( "Entering SnmpNotification.getAgentHostName()..." );
		String hostIdentifier;

		if ( notificationType == SnmpAPI.TRP_REQ_MSG )
		{
			String agentAddress = DNSLookup.inetAddrToString( notification.getAgentAddress().getAddress() );
//            System.out.println( "Processing address: " + agentAddress );
            
            if ( DNSLookup.getName( agentAddress ) != null )
            {
//                System.out.println( "Leaving SnmpNotification.getAgentHostName() via DNSLookup..." );
				return DNSLookup.getName( agentAddress );
            }
            else
            {
                //  Need to add code to cache any maps found this way.
//                System.out.println( "Leaving SnmpNotification.getAgentHostName() via SnmpPdu..." );
        // Added 8/23/02 WSM
    		//System.out.println("SnmpNotification: Trap Request Message");
        if (TypeConverter.ALWAYS_RESOLVE_NAME)
				  return notification.getAgentAddress().getHostName();
        else
          return notification.getAgentAddr();
			}
		}
		else if ( ( notificationType == SnmpAPI.TRP2_REQ_MSG ) ||
				  ( notificationType == SnmpAPI.INFORM_REQ_MSG ) )
		{
			//  Agent address seems to appear in next-to-last varbind if the
			//  snmpTrapEnterprise varbind is not present.
			//  If the varbind is present, extract the agent 'value.' This
			//  may be a dotted IP address or a hostname. The translation
			//  'agentInfo.toString()' can be slow due to DNS look-up.

			if ( notification.getAgentAddress() != null )
      {
        // Added 8/23/02 WSM
    		//System.out.println("SnmpNotification: getAgentAddress is NOT null.");
        if (TypeConverter.ALWAYS_RESOLVE_NAME)
  				return notification.getAgentAddress().getHostName();
        else
          return notification.getAgentAddr();
      }
			else
			{
				//TLEE 04/03/02 Added
				try {
          // Added 8/23/02 WSM
          //System.out.println("SnmpNotification:  1");
          if (TypeConverter.ALWAYS_RESOLVE_NAME)
          {
            // Not sure why we are using the getRemoteHost instead of
            //    notification.getAgentAddress().getHostName().
            //System.out.println("SnmpNotification:   1.1");
					  InetAddress address = InetAddress.getByName(notification.getRemoteHost());
					  return address.getHostName();
          }
          else {
            //System.out.println ("SnmpNotification:  1.2 getAgentAddr = " + notification.getAgentAddr());
            return notification.getAgentAddr();
          }
				}catch(UnknownHostException e){}

				int lastVarBindIndex = notification.getVariableBindings().size() - 1;
				if ( lastVarBindIndex > MIN_SNMPV2_LAST_VARBIND_INDEX )     //  Are there more than the minimum number of varbinds?
				{
					//  Check to see if last varbind is the snmpTrapEnterprise varbind.
					//  If not, see if it contains a valid agent address or hostname.
					if ( notification.getObjectID( lastVarBindIndex ).toString().indexOf( SNMP_TRAP_ENTERPRISE, 0 ) < 0 )
					{
						hostIdentifier = notification.getVariable( lastVarBindIndex ).toString();
						try
						{
              // Added 8/23/02 WSM
          		System.out.println("SnmpNotification:   2");
              if (TypeConverter.ALWAYS_RESOLVE_NAME)
  							return InetAddress.getByName( hostIdentifier ).getHostName();
              else
                return hostIdentifier;
						}
						catch ( UnknownHostException eLast )
						{
							//  Check the next-to-last varbind.
							hostIdentifier = notification.getVariable( lastVarBindIndex - 1 ).toString();
							try
							{
                // Added 8/23/02 WSM
          		  //System.out.println("SnmpNotification:   3");
                if (TypeConverter.ALWAYS_RESOLVE_NAME)
  								return InetAddress.getByName( hostIdentifier ).getHostName();
                else
                  return hostIdentifier;
							}
							catch ( UnknownHostException eNextLast )
							{
								return "Not supplied";
							}
						}
					}
					else   //  Otherwise, check the next-to-last varbind.
					{
						hostIdentifier = notification.getVariable( lastVarBindIndex - 1 ).toString();
						try
						{
              // Added 8/23/02 WSM
          		//System.out.println("SnmpNotification:   4");
              if (TypeConverter.ALWAYS_RESOLVE_NAME)
  							return InetAddress.getByName( hostIdentifier ).getHostName();
              else
                return hostIdentifier;
						}
						catch ( UnknownHostException eNextLast )
						{
							return "Not supplied";
						}
					}
				}
				else
				{
					return "Not supplied";
				}
			}
		}
		else
			return null;
	}

	/** Answer the generic type of the notification. This is a standard field
		for SNMPv1 traps but not for SNMPv2c traps.                         */
	public Integer getTrapType()
	{
		if ( notificationType == SnmpAPI.TRP_REQ_MSG )
			return notification.getTrapType();
		else if ( ( notificationType == SnmpAPI.TRP2_REQ_MSG ) ||
				  ( notificationType == SnmpAPI.INFORM_REQ_MSG ) )
		{
			if ( notification.getVariable( SNMP_TRAP_OID_VARBIND ).toString().startsWith( PRIVATE_ENTERPRISES ) )
				return 6;
			else
			{
				String varBindVariable = notification.getVariable( SNMP_TRAP_OID_VARBIND ).toString();
				if ( varBindVariable.startsWith( SNMPV2_TRAPS ) )
				{
					int genericType = Character.digit( varBindVariable.charAt( SNMPV2_GENERIC_TYPE ), 10 );
					return genericType - 1;
				}
				else
				{   //Added 1/22/01 WSM
					return notification.getTrapType ();
				}
			}
		}
		else
			return null;
	}

	/** Answer the specific type of the notification. This is a standard field
		for SNMPv1 traps but not for SNMPv2c traps.                         */
	public Object getSpecificType()
	{
		if ( notificationType == SnmpAPI.TRP_REQ_MSG )
			return TypeConverter.getG2quantity( notification.getSpecificType() );
		else if ( ( notificationType == SnmpAPI.TRP2_REQ_MSG ) ||
				  ( notificationType == SnmpAPI.INFORM_REQ_MSG ) )
		{
			String varBindVariable = notification.getVariable( SNMP_TRAP_OID_VARBIND ).toString();
			if ( varBindVariable.startsWith( PRIVATE_ENTERPRISES ) )
			{
				int separatorIndex = varBindVariable.indexOf( ".0." );
				if ( separatorIndex > 0 )
				{
					String specificTypeString = varBindVariable.substring( separatorIndex + 3, varBindVariable.length() );
					return TypeConverter.getG2quantity( Long.parseLong( specificTypeString ));
				}
				else
					return TypeConverter.getG2quantity(0L );
			}
			else
				return TypeConverter.getG2quantity( 0L );
		}
		else
			return null;
	}

	/** Answer the system uptime of the host generating the notification.
		This is a standard field in SNMPv1 traps, but is placed in the
		first varbind for SNMPv2 traps and INFROMs.                         */
    // May 15, 2002
    //  Calling getG2timeticks instead of getG2quantity due to G2's Integer limitation.
	public Object getUpTime()
	{
		if ( notificationType == SnmpAPI.TRP_REQ_MSG )
			return TypeConverter.getG2timeticks( notification.getUpTime() );
		else if ( ( notificationType == SnmpAPI.TRP2_REQ_MSG ) ||
				  ( notificationType == SnmpAPI.INFORM_REQ_MSG ) )
		{
			return TypeConverter.getG2timeticks( ( (SnmpTimeticks)( notification.getVariable( SYS_UP_TIME_VARBIND ) ) ).longValue() );
		}
		else
			return null;
	}

	/** Answer the all variable bindings of the notifiaction.               */
	public Sequence getVariableBindings()
	{
		return TypeConverter.getVarBindSequence( notification.getVariableBindings() );
	}

    /** Answer the community string for the notification.                   */
    public String getCommunity()
    {
        return notification.getCommunity();
    }
}