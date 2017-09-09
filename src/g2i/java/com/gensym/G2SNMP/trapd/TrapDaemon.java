package com.gensym.G2SNMP.trapd;

import com.gensym.G2SNMP.Task;
import com.gensym.G2SNMP.rpc.FilterAccess;
import com.adventnet.snmp.snmp2.SnmpPDU;
import com.adventnet.snmp.snmp2.SnmpSession;
import com.adventnet.snmp.snmp2.SnmpAPI;
import com.adventnet.snmp.snmp2.SnmpException;
import com.adventnet.snmp.snmp2.UDPProtocolOptions;
import com.adventnet.snmp.beans.*;
import com.gensym.jgi.G2Connection;
import com.gensym.util.Structure;
import java.lang.reflect.Method;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.nio.charset.Charset;

import com.gensym.util.Symbol;
import com.gensym.G2SNMP.JsnmpBridge;
import com.gensym.G2SNMP.rpc.TypeConverter;
import com.adventnet.snmp.snmp2.usm.*;
import com.adventnet.snmp.snmp2.*;


/**
   This class represents the object that
   - listens to incoming traps,
   - logs them in the log file,
   - filters them,
   - puts them into a FIFO queue,
   - transmits them to Integrity.

   05/30/01 WSM
      I changed the way in which the TrapDaemon works.  I removed the extension of a
      TrapListener from the implements.  By implementing a TrapListener the bridge
      was confined to using the JDK 1.1 event model.  Since we are releasing this under
      JDK 1.3, I have changed it.  It now uses the callback method to process the incoming
      traps.  Under the implementation of a TrapListener the receivedTrap method was called.

      The original sources before any modifications were made are saved as G2SNMP-source-E3001.zip.

*/
public final class TrapDaemon extends Task implements FilterAccess {
	public final int trapQueueInitialCapacity = 1000;  /* Modified WSM Jan 22, 2003: originally 100 */
    public final int trapFilterInitialCapacity = 20; /* Modified WSM Jan 22, 2003: originally 10 */
	public final int trapForwarderInitialTimeStep = 5; /* Modified WSM Jan 22, 2003: originally 50 */
    private TrapQueue trapQueue;
    private TrapFilter trapFilter;
    private TrapForwarder trapForwarder;
	public static final Symbol addFilteredTrapRPD = Symbol.intern("G2SNMP_ADD_FILTERED_TRAP");
    public static final Symbol deleteFilteredTrapRPD = Symbol.intern("G2SNMP_DELETE_FILTERED_TRAP");
	private boolean trapDaemonDebug;
	private byte[] engineId;
	static final int USM_SECURITY_MODEL = 3;
	public static final Symbol deleteUSMUserRPD = Symbol.intern("G2SNMPV3_DELETE_USER_ENTRY");
	public static final Symbol createUSMUserRPD = Symbol.intern("G2SNMPV3_CREATE_USER_ENTRY");
	public static final Symbol AlwaysResolveNameRPD = Symbol.intern("G2SNMP_ALWAYS_RESOLVE_HOSTNAME");

		/**
       The constructor that
	   - sets (creates) attributes,
       - starts a listening session.
       @roseuid 365D21C40359
     */
	public TrapDaemon(SnmpAPI snmpApi, G2Connection g2connection, String ppdFileName, String mibNames, int port) throws com.gensym.G2SNMP.TaskInitException {
		super (snmpApi, g2connection);

        //APIv4
        UDPProtocolOptions sessionOpt;

		trapQueue = new TrapQueue(trapQueueInitialCapacity, snmpApi);
		trapFilter = new TrapFilter(ppdFileName, trapFilterInitialCapacity);
		trapForwarder = new TrapForwarder(trapForwarderInitialTimeStep, g2connection, trapQueue, trapFilter);
		registerRPCs(g2connection);
		trapDaemonDebug = snmpApi.getDebug();
		
		// Set the local listening port to 162 and open the session.
		//APIv3->snmpSession.setLocalPort (162);
		// Have to create a new UDPProtocolOptions for the session before any communication can happen.
		snmpSession.setProtocolOptions(new UDPProtocolOptions());
		sessionOpt = (UDPProtocolOptions)snmpSession.getProtocolOptions();
		sessionOpt.setLocalPort (port);
		
		try {
		  snmpSession.open();
		} catch (SnmpException e) {
		  System.out.println ("Error opening socket: " + e);
		}
		// Set the community string to null.  The community string in the PDU will override
		// the one defined in the session.
		snmpSession.setCommunity ( null);
		
		// Disables the effect of automatically responding to Inform requests.  These
		// are handled by the bridge itself.
		snmpSession.setAutoInformResponse (false);
	}
	
	public TrapDaemon(SnmpAPI snmpApi, G2Connection g2connection, String ppdFileName, String mibNames) throws com.gensym.G2SNMP.TaskInitException {
//	public TrapDaemon(SnmpAPI snmpApi, G2Connection g2connection, Text ppdFileName, Text mibNames) throws com.gensym.G2SNMP.TaskInitException {
		this(snmpApi, g2connection, ppdFileName, mibNames, 162);
	}

   public TrapDaemon(SnmpAPI snmpApi,G2Connection g2connection, String ppdFileName, String mibNames,
					String engineID, String userName, int port, String authPassword,
					String privPassword, String authProtocol) throws com.gensym.G2SNMP.TaskInitException {

		super (snmpApi, g2connection);

                //APIv4
                UDPProtocolOptions sessionOpt;
                
        Charset charset = Charset.defaultCharset();
		engineId = engineID.getBytes(charset);
		trapQueue = new TrapQueue(trapQueueInitialCapacity, snmpApi);
		trapFilter = new TrapFilter(ppdFileName, trapFilterInitialCapacity);
		trapForwarder = new TrapForwarder(trapForwarderInitialTimeStep, g2connection, trapQueue, trapFilter);
		registerRPCs(g2connection);
		try{
			Class theClass = this.getClass();
			System.out.println ("registering delete USM Entry");
			Method DeleteUSMEntryMethod = theClass.getMethod(
				"deleteUSMUser",
				new Class[] {
					Class.forName("java.lang.String")});
			Method CreateUSMEntryMethod = theClass.getMethod(
				"createUSMUser",
				new Class[] {
					Class.forName("java.lang.String"),
					Class.forName("java.lang.String"),
					Class.forName("java.lang.String"),
					Class.forName("java.lang.String")});
			System.out.println ("Registering Resolve Name option");
			Method AlwaysResolveNameMethod = theClass.getMethod(
				"alwaysResolveName",
				new Class[] {Boolean.TYPE});

			g2connection.registerJavaMethod(this, DeleteUSMEntryMethod, deleteUSMUserRPD, false);
			g2connection.registerJavaMethod(this, CreateUSMEntryMethod, createUSMUserRPD, false);
			g2connection.registerJavaMethod(this, AlwaysResolveNameMethod,
				AlwaysResolveNameRPD, false);

		} catch (Exception e) {
			throw new com.gensym.G2SNMP.TaskInitException(e.getMessage());
		}
		trapDaemonDebug = snmpApi.getDebug();


		// Set the local listening port to 162 and open the session.
		//APIv3->snmpSession.setLocalPort (port);
		// Have to create a new UDPProtocolOptions for the session before any communication can happen.
		snmpSession.setProtocolOptions(new UDPProtocolOptions());
        sessionOpt = (UDPProtocolOptions)snmpSession.getProtocolOptions();
		sessionOpt.setLocalPort (port);

		// Set the community string to null.  The community string in the PDU will override
		// the one defined in the session.
		snmpSession.setCommunity ( null);

		// Disables the effect of automatically responding to Inform requests.  These
		// are handled by the bridge itself.
		snmpSession.setAutoInformResponse (false);
		int proto;
		if (authProtocol.equals("SHA")){
			proto = USMUserEntry.SHA_AUTH;
//			secLevel |= 0x01;
		}else if (authProtocol.equals("MD5")){
			proto = USMUserEntry.MD5_AUTH;
//			secLevel |= 0x01;
		}else{
			proto = USMUserEntry.NO_AUTH;
		}

		deleteUSMUser(userName);
		createUSMTable(userName.getBytes(charset), proto, authPassword, privPassword, snmpApi);

		try {
		  snmpSession.open();
		} catch (SnmpException e) {
		  System.out.println ("Error opening socket: " + e);
		}
   }

	public boolean alwaysResolveName(boolean ResolveName)
	{
		JsnmpBridge.debugOut("alwaysResolveName = " +  ResolveName);
		TypeConverter.set_always_resolve_name(ResolveName);
		return true;
	}

	/**
	   Required to satisfy the Task interface.
	   @roseuid 36627A8902CF
	 */
	public boolean authenticate(SnmpPDU pdu, String community) {
		if (pdu == null) {
			System.out.println ("PDU received is null.");
			return false;
		}
		if(pdu.getVersion() == SnmpAPI.SNMP_VERSION_3)
		{
			if (pdu.getCommand()==SnmpAPI.TRP2_REQ_MSG)
				return true;
//			return !((Snmp3Message)pdu.getMsg()).isAuthenticationFailed();
			Snmp3Message msg = (Snmp3Message)pdu.getMsg();
			boolean authBool = msg.isAuthenticationFailed();
			if(!authBool){
				USMUserEntry entry = (USMUserEntry)msg.getSecurity();
				USMUserEntry localEntry =
						((USMUserTable)snmpApi.getSecurityProvider().
						getTable(3)).getEntry(entry.getUserName(),
						entry.getEngineID());
				if(localEntry != null){
					JsnmpBridge.debugOut("Message's security level = " +
							entry.getSecurityLevel());
					JsnmpBridge.debugOut("LocalEntry's security level = " +
							localEntry.getSecurityLevel());
					authBool = ( entry.getSecurityLevel() ==
							localEntry.getSecurityLevel() );
				}
			}
			return authBool;
		}else{
			System.out.println ("authenticate:  Community = " + community);
			System.out.println ("authenticate:  pdu.community = " +  pdu.getCommunity());
			//Commenting out for now, until a better understanding:
			//return pdu.getCommunity().equals (community);
			//returning true initiates a call to the callback method.
			return true;
		}
	}

	/**
	   Required to satisfy the Task interface.
	   @roseuid 36627A8B00FC                                                           te
	 */
	public boolean callback(SnmpSession session, SnmpPDU pdu, int requestId) {
          //APIv4
          UDPProtocolOptions opt = (UDPProtocolOptions)pdu.getProtocolOptions();
          UDPProtocolOptions sessionOpt;

		if( pdu.getCommand() == SnmpAPI.TRP_REQ_MSG) {
			JsnmpBridge.debugOut( "SNMPv1 trap received." );
		}
		else if( pdu.getCommand() == SnmpAPI.TRP2_REQ_MSG) {
			JsnmpBridge.debugOut( "SNMPv2 trap received." );
            //  The SNMPv2 trap PDU does not contain agent address information.
            //  The trapEvent does contain the source of the trap. This info
            //  is placed in the SNMP PDU for use downstream.
            pdu.setAgentAddress( pdu.getAgentAddress() );
        }
        else if ( pdu.getCommand() == SnmpAPI.INFORM_REQ_MSG) {
			JsnmpBridge.debugOut( "SNMPv2 INFORM received." );
			//  The SNMPv2 INFORM PDU does not contain agent address information.
            //  The trapEvent does contain the source of the trap. This info
            //  is placed in the SNMP PDU for use downstream.

            String addresses[];
            //  Acknowledge INFORM request.
            SnmpSession ackSession = new SnmpSession( snmpApi );
            //APIv3->ackSession.setPeername( opt.getRemoteHost() );
            sessionOpt = (UDPProtocolOptions)ackSession.getProtocolOptions();
            sessionOpt.setRemoteHost( opt.getRemoteHost() );
            try
            {
            ackSession.open();
            }
            catch ( SnmpException e_open )
            {
              System.out.println( "ERROR: Unable to open SNMP session for INFORM acknowledgement." );
            }
            SnmpPDU acknowledgePDU = pdu.copy();
            // wsm
            //APIv3->addresses = ackSession.getLocalAddresses();
            addresses = sessionOpt.getLocalAddresses();

            if (trapDaemonDebug) {
              UDPProtocolOptions ackOpt = (UDPProtocolOptions)acknowledgePDU.getProtocolOptions();
              System.out.println ("TrapD: PDU.remoteHost= " + ackOpt.getRemoteHost());
              System.out.println ("TrapD: PDU.remotePort = " + ackOpt.getRemotePort());
              //APIv3->System.out.println ("TrapD: Session.PeerName = " + ackSession.getPeername ());
              System.out.println ("TrapD: Session.PeerName = " + sessionOpt.getRemoteHost ());
              //APIv3->System.out.println ("TrapD: Session.RemotePort = " + ackSession.getRemotePort());
              System.out.println ("TrapD: Session.RemotePort = " + sessionOpt.getRemotePort());
              for (int j = 0; j < addresses.length; j++) {
                System.out.println ("TrapD: Session.LocalAddress = " + addresses[j]);
              }
              //APIv3->System.out.println ("TrapD: Session.LocalPort = " + ackSession.getLocalPort ());
              System.out.println ("TrapD: Session.LocalPort = " + sessionOpt.getLocalPort ());
              System.out.println ("TrapD: trap.RemoteHost = " + opt.getRemoteHost());
              System.out.println ("TrapD: trap.RemotePort = " + opt.getRemotePort());
            }
            acknowledgePDU.setErrstat( SnmpAPI.SNMP_ERR_NOERROR );
            acknowledgePDU.setErrindex( SnmpAPI.SNMP_ERR_NOERROR );
            acknowledgePDU.setCommand( SnmpAPI.GET_RSP_MSG );
            try
            {
              ackSession.send( acknowledgePDU );
              ackSession.close();
            }
            catch ( SnmpException e_send )
            {
              System.out.println( "ERROR: Unable to send INFORM acknowledgement." );
            }
            pdu.setAgentAddress( pdu.getAgentAddress() );
        }

        if (trapFilter.shouldForward(pdu)){
            trapQueue.putLast(pdu);
            if (trapQueue.getCount() == 1){
                trapForwarder.lookForTrap();
            }
            JsnmpBridge.debugOut("PDU is put in trap queue " + pdu.toString());
        } else {
            JsnmpBridge.debugOut("PDU is NOT put in trap queue " + pdu.toString());
        }
        // returning false indicates there is to be more processing done on the PDU.
        return false;
    }

    /**
       @roseuid 3662A98D000F
     */
	public void AddFilteredTrap(Structure params) {
        try{
            trapFilter.registerTrap(com.gensym.G2SNMP.rpc.TypeConverter.getStringAttributeValue(params, com.gensym.G2SNMP.rpc.TypeConverter.ENTERPRISE_ID),
                                    com.gensym.G2SNMP.rpc.TypeConverter.getIntegerAttributeValue(params, com.gensym.G2SNMP.rpc.TypeConverter.GENERIC_TRAP_ID).intValue(),
                                    com.gensym.G2SNMP.rpc.TypeConverter.getNumberAttributeValue(params, com.gensym.G2SNMP.rpc.TypeConverter.SPECIFIC_TRAP_ID).doubleValue());
        }catch(com.gensym.G2SNMP.rpc.TypeConversionException e){
            JsnmpBridge.debugOut("Error adding filtered trap " + e.getMessage());
            sendMessage("Error adding filtered trap", "", e.getMessage(), 3);
        }
    }

    /**
       @roseuid 3662A99003B7
     */
	public void DeleteFilteredTrap(Structure params) {
        try{
            trapFilter.deregisterTrap(com.gensym.G2SNMP.rpc.TypeConverter.getStringAttributeValue(params, com.gensym.G2SNMP.rpc.TypeConverter.ENTERPRISE_ID),
                                    com.gensym.G2SNMP.rpc.TypeConverter.getIntegerAttributeValue(params, com.gensym.G2SNMP.rpc.TypeConverter.GENERIC_TRAP_ID).intValue(),
                                    com.gensym.G2SNMP.rpc.TypeConverter.getNumberAttributeValue(params, com.gensym.G2SNMP.rpc.TypeConverter.SPECIFIC_TRAP_ID).doubleValue());
        }catch(com.gensym.G2SNMP.rpc.TypeConversionException e){
            JsnmpBridge.debugOut("Error deleting filtered trap " + e.getMessage());
            sendMessage("Error deleting filtered trap", "", e.getMessage(), 3);
        }
    }

    /**
       @roseuid 3662A99500B1
     */
	public void registerRPCs(G2Connection g2connection) throws com.gensym.G2SNMP.TaskInitException {
        super.registerRPCs (g2connection);
        Class theClass = this.getClass();
        try{
            Method addMethod = theClass.getMethod(
                "AddFilteredTrap",
				new Class[] {
					Class.forName("com.gensym.util.Structure")});
            Method deleteMethod = theClass.getMethod(
				"DeleteFilteredTrap",
				new Class[] {
					Class.forName("com.gensym.util.Structure")});
			g2connection.registerJavaMethod(this, addMethod, addFilteredTrapRPD, false);
			g2connection.registerJavaMethod(this, deleteMethod, deleteFilteredTrapRPD, false);
		} catch (Exception e) {
			throw new com.gensym.G2SNMP.TaskInitException(e.getMessage());
		}
	}

    protected void finalize() {
        JsnmpBridge.debugOut("TrapDaemon.finalize ().");
        if (!finalized) {
            trapQueue.clear();
            trapForwarder.stop();
        }
        super.finalize();
    }
	/*
	 * Method to create the USM user entry in the USM table and the engine Id 
	 * entry in the engine table.
	 */
  public void createUSMTable(byte[] name, int authProtocol,
					String authPassword, String privPassword, SnmpAPI api)
  {
        //APIv4
        UDPProtocolOptions opt;
    Charset charset = Charset.defaultCharset();
	byte level = 0;
	USMUserEntry entry = new USMUserEntry(name, engineId);
	entry.setAuthProtocol(authProtocol);

	if ((authProtocol != USMUserEntry.NO_AUTH) && (authPassword != null) && (authPassword.length() !=0 ) )
	{
	  byte[] authKey = USMUtils.password_to_key(authProtocol,
											authPassword.getBytes(charset),
											authPassword.getBytes(charset).length,
											engineId);
	  entry.setAuthKey(authKey);
	  level = 1;

	  if ((privPassword != null)  && (privPassword.length() !=0) )
	  {
		byte[] tempKey = USMUtils.password_to_key(authProtocol,
											privPassword.getBytes(charset),
											privPassword.getBytes(charset).length,
											engineId);
		byte privKey[]=new byte[16];
		System.arraycopy(tempKey,0,privKey,0,16);
		entry.setPrivKey(privKey);
		level |= 2;
	  }
	}
JsnmpBridge.debugOut("TrapDaemon::Set USM "+new String(entry.getUserName()) + " security lever =" +level);
	entry.setSecurityLevel(level);

		USMUserTable USMTable = (USMUserTable)api.getSecurityProvider().
											getTable(USM_SECURITY_MODEL);
		USMTable.addEntry(entry);

	byte[] names=entry.getUserName();
	byte[] id=entry.getEngineID();

	//APIv3->SnmpEngineEntry e = new SnmpEngineEntry("localhost", snmpSession.getLocalPort() );
        opt = (UDPProtocolOptions)snmpSession.getProtocolOptions();
	SnmpEngineEntry e = new SnmpEngineEntry("localhost", opt.getLocalPort() );
	e.setEngineID(engineId);
	entry.setEngineEntry(e);
	api.setSnmpEngineID(engineId);
  }
  
  public boolean deleteUSMUser(String name){

	try{
		USMUserTable USMTable = (USMUserTable)snmpApi.getSecurityProvider().
											getTable(USM_SECURITY_MODEL);
		return (USMTable.removeEntry (name.getBytes(Charset.defaultCharset()), engineId));
	}catch(Exception e){
	}
	return false;

}
  public boolean createUSMUser(String userName, String authProtocol, String authPassword, String privPassword ){

		int proto;
		if (authProtocol.equals("SHA")){
			proto = USMUserEntry.SHA_AUTH;
//			secLevel |= 0x01;
		}else if (authProtocol.equals("MD5")){
			proto = USMUserEntry.MD5_AUTH;
//			secLevel |= 0x01;
		}else{
			proto = USMUserEntry.NO_AUTH;
		}
		createUSMTable(userName.getBytes(Charset.defaultCharset()), proto, authPassword, privPassword, snmpApi);
		return true;
  }

}