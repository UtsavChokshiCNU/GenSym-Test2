package com.gensym.G2SNMP;

import com.gensym.G2SNMP.rpc.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.adventnet.snmp.snmp2.*;
import com.adventnet.snmp.snmp2.usm.*;
import com.gensym.jgi.G2Connection;
import java.util.*;
import java.net.InetAddress;
import java.nio.charset.Charset;
import java.util.Enumeration;
import java.lang.reflect.Method;
import com.gensym.util.Symbol;
import java.security.*;
/**
   Class description goes here
*/
public final class Transactor extends Task {
	public static final int DEFAULT_TIMEOUT = 8;    // in tenths of a second
	private static final int defaultTimeout = DEFAULT_TIMEOUT * 100;  // ms
	private static final int defaultRetries = 3;
	private int timeout = defaultTimeout;
	private int retries = defaultRetries;
	private static final int initialVectorCapacity = 10;
	private static final int timeOutErrorCode = -1;
	static final int USM_SECURITY_MODEL = 3;
	public static final Symbol BlockingTransactionRPD = Symbol.intern("G2SNMP_BLOCKING_TRANSACTION");
	public static final Symbol NonBlockingTransactionRPD = Symbol.intern("G2SNMP_NONBLOCKING_TRANSACTION");
//	public static final Symbol ReceiveNonblocking = Symbol.intern ("TEST-RECEIVE-RPC");
	public static final Symbol ReceiveNonblocking = Symbol.intern ("G2SNMP_RECEIVE_NONBLOCKING");
	public static final Symbol ModifyCommParamsRPD = Symbol.intern("G2SNMP_MODIFY_COMM_PARAMS");
	public static final Symbol UseSnmpDefaultsRPD = Symbol.intern("G2SNMP_USE_SNMP_DEFAULTS");
	public static final Symbol UseSnmpCommParamsRPD = Symbol.intern("G2SNMP_USE_SNMP_COMM_PARAMS");
	public static final Symbol NonBlockingSnmpv3TransactionRPD = Symbol.intern("G2SNMPV3_NONBLOCKING_TRANSACTION");
	public static final Symbol BlockingSnmpv3TransactionRPD = Symbol.intern("G2SNMPV3_BLOCKING_TRANSACTION");
	public static final Symbol AlwaysResolveNameRPD = Symbol.intern("G2SNMP_ALWAYS_RESOLVE_HOSTNAME");
	public static final Symbol DeleteUSMEntryRPD = Symbol.intern("G2SNMPV3_DELETE_USM_ENTRY");
	public static final Symbol DeleteSnmpv3EntryRPD = Symbol.intern("G2SNMPV3_DELETE_SNMPV3_ENTRY");

	public static final ArrayList invalidOidList =  new ArrayList();
	public static final String[] ErrorMessages = new String[]{"usmStatsUnsupportedsecLevels",
														 "usmStatsNotInTimeWindows",
														 "usmStatsUnknownUserNames",
														 "usmStatsUnknownEngineIDs",
														 "usmStatsWrongDigests",
														 "usmStatsDecryptionErrors"};


	private Vector syncSendReqIds;
	int authProtocol = USMUserEntry.NO_AUTH;

	public Transactor(SnmpAPI snmpApi, G2Connection g2connection, int timeout) throws TaskInitException {
		super (snmpApi, g2connection);

		modifyCommParams(timeout, defaultRetries);
		useSnmpCommParams();

		syncSendReqIds = new Vector(initialVectorCapacity);

		registerRPCs(g2connection);
		invalidOidList.add(".1.3.6.1.6.3.15.1.1.1.0");
		invalidOidList.add(".1.3.6.1.6.3.15.1.1.2.0");
		invalidOidList.add(".1.3.6.1.6.3.15.1.1.3.0");
		invalidOidList.add(".1.3.6.1.6.3.15.1.1.4.0");
		invalidOidList.add(".1.3.6.1.6.3.15.1.1.5.0");
		invalidOidList.add(".1.3.6.1.6.3.15.1.1.6.0");

		try{
			snmpSession.open();
		} catch (SnmpException e){
			throw new TaskInitException(e.toString());
		}
	}

	public boolean authenticate(SnmpPDU pdu, String community) {
// HFS       return snmpApi.authenticate(pdu, community);
		return true;
	}

	/**
	   @roseuid 36628CAB0126
	 */
	public boolean callback(SnmpSession session, SnmpPDU pdu, int requestId) {
		JsnmpBridge.debugOut("callback, reqID = "+requestId);
		if (syncSendReqIds.contains(requestId)){
			// response to a synchronous request => needs outside processing
			return false;
		}
		startReceiveNonblocking( TypeConverter.pduToG2Structure(pdu, ""),
								 requestId);
		return true;
	}

	/**
	   @roseuid 3662A75C01CB
	 */
	public void registerRPCs(G2Connection g2connection) throws TaskInitException {
		super.registerRPCs (g2connection);
		Class theClass = this.getClass();
		try {
			System.out.println ("registering Blocking Transaction");
			Method BlockingTransactionMethod = theClass.getMethod(
				"blockingTransaction",
				new Class[] {
					Class.forName("java.lang.String"),
					Integer.TYPE,
					Integer.TYPE,
					Class.forName("java.lang.String"),
					Class.forName("java.lang.String"),
					Class.forName("com.gensym.util.Structure"),
					Class.forName("com.gensym.util.Sequence")
				});
			System.out.println ("registering NonBlocking Transaction");
			Method NonBlockingTransactionMethod = theClass.getMethod(
				"nonBlockingTransaction",
				new Class[] {
					Class.forName("java.lang.String"),
					Integer.TYPE,
					Integer.TYPE,
					Class.forName("java.lang.String"),
					Class.forName("java.lang.String"),
					Class.forName("com.gensym.util.Structure"),
					Class.forName("com.gensym.util.Structure"),
					Class.forName("com.gensym.util.Sequence")
				});
			System.out.println ("registering non Blocking Snmpv3 Transaction");
			Method NonBlockingSnmpv3TransactionMethod = theClass.getMethod(
				"nonBlockingSnmpv3Transaction",
				new Class[] {
					Class.forName("java.lang.String"),         //Transaction-tagname
					Integer.TYPE,                              //snmp version
					Integer.TYPE,						       //request code
					Class.forName("java.lang.String"),         //node-name
					Class.forName("java.lang.String"),         //community-name
					Class.forName("java.lang.String"),         //write community-name
					Integer.TYPE,                              //port
					Class.forName("java.lang.String"),         //engine-id
					Class.forName("java.lang.String"),         //username
					Class.forName("java.lang.String"),         //auth protocol
					Class.forName("java.lang.String"),         //auth password
					Class.forName("java.lang.String"),         //priv password
					Class.forName("java.lang.String"),         //context-id
					Class.forName("java.lang.String"),         //context name
					Class.forName("com.gensym.util.Structure"),
					Class.forName("com.gensym.util.Structure"),
					Class.forName("com.gensym.util.Sequence")
				});
			System.out.println ("registering Blocking Snmpv3 Transaction");
			Method BlockingSnmpv3TransactionMethod = theClass.getMethod(
				"blockingSnmpv3Transaction",
				new Class[] {
					Class.forName("java.lang.String"),         //Transaction-tagname
					Integer.TYPE,                              //snmp version
					Integer.TYPE,						       //request code
					Class.forName("java.lang.String"),         //node-name
					Class.forName("java.lang.String"),         //community-name
					Class.forName("java.lang.String"),         //write community-name
					Integer.TYPE,                              //port
					Class.forName("java.lang.String"),         //engine-id
					Class.forName("java.lang.String"),         //username
					Class.forName("java.lang.String"),         //auth protocol
					Class.forName("java.lang.String"),         //auth password
					Class.forName("java.lang.String"),         //priv password
					Class.forName("java.lang.String"),         //context-id
					Class.forName("java.lang.String"),         //context name
					Class.forName("com.gensym.util.Structure"),
					Class.forName("com.gensym.util.Sequence")
				});
			System.out.println ("Registering Resolve Name option");
			Method AlwaysResolveNameMethod = theClass.getMethod(
				"alwaysResolveName",
				new Class[] {Boolean.TYPE});
			System.out.println ("registering Modify Comm Params");
			Method ModifyCommParamsMethod = theClass.getMethod(
				"modifyCommParams",
				new Class[] {
					Integer.TYPE,
					Integer.TYPE
				});
			System.out.println ("registering delete USM Entry");
			Method DeleteUSMEntryMethod = theClass.getMethod(
				"deleteUSMEntry",
				new Class[] {
					Class.forName("java.lang.String"),
					Class.forName("java.lang.String"),
					Integer.TYPE
				});
			System.out.println ("registering delete SNMPv3 Entry");
			Method DeleteSnmpv3EntryMethod = theClass.getMethod(
				"deleteSnmpv3Entry",
				new Class[] {
					Class.forName("java.lang.String"),
					Integer.TYPE
				});
			System.out.println ("registering Use SNMP Defaults");
			Method UseSnmpDefaultsMethod =
				theClass.getMethod("useSnmpDefaults", new Class[0]);
			Method UseSnmpCommParamsMethod =
				theClass.getMethod("useSnmpCommParams", new Class[0]);

			g2connection.registerJavaMethod(this, BlockingTransactionMethod,
				BlockingTransactionRPD, true);
			g2connection.registerJavaMethod(this, NonBlockingTransactionMethod,
				NonBlockingTransactionRPD, true);
			g2connection.registerJavaMethod(this, BlockingSnmpv3TransactionMethod,
				BlockingSnmpv3TransactionRPD, true);
			g2connection.registerJavaMethod(this, NonBlockingSnmpv3TransactionMethod,
				NonBlockingSnmpv3TransactionRPD, true);
			g2connection.registerJavaMethod(this, ModifyCommParamsMethod,
				ModifyCommParamsRPD, false);
			g2connection.registerJavaMethod(this, UseSnmpDefaultsMethod,
				UseSnmpDefaultsRPD, false);
			g2connection.registerJavaMethod(this, UseSnmpCommParamsMethod,
				UseSnmpCommParamsRPD, false);
			g2connection.registerJavaMethod(this, AlwaysResolveNameMethod,
				AlwaysResolveNameRPD, false);
			g2connection.registerJavaMethod(this, DeleteUSMEntryMethod,
				DeleteUSMEntryRPD, false);
			g2connection.registerJavaMethod(this, DeleteSnmpv3EntryMethod,
				DeleteSnmpv3EntryRPD, false);

		} catch (NoSuchMethodException e){
			throw new TaskInitException(e.getMessage());
		} catch (ClassNotFoundException e){
			throw new TaskInitException(e.getMessage());
		} catch (RuntimeException e){
			throw new TaskInitException(e.getMessage());
		}
        JsnmpBridge.debugOut("registerRPCs(G2Connection g2connection)");
    }

    /**
       @roseuid 3662B3B90140
     */
	public Structure modifyCommParams(int timeout, int retries) {

        if (timeout > 0) {
			this.timeout = timeout * 100;
        } else {
			this.timeout = DEFAULT_TIMEOUT * 100;
            sendMessage("Error modifying comm params", "", "non-positive timeout specified. Using default value", 3);
        }

        if (retries > 0) {
            this.retries = retries;
        } else {
            this.retries = defaultRetries;
            sendMessage("Error modifying comm params", "", "non-positive number of retries specified. Using default value", 3);
        }

        JsnmpBridge.debugOut("modifyCommParams: timeout: " + this.timeout + " ms, retries: " + this.retries);

        try {
            return new Structure(
                new Symbol[] {TypeConverter.ERROR_CODE, TypeConverter.ERROR_STRING},
                new Object[] {0, String.valueOf(this.timeout/100) + "-" + String.valueOf(this.retries)});
        } catch(com.gensym.util.NtwIllegalArgumentException e) {
            sendMessage("Error modifying comm params", "", "Error creating return structure", 3);
            return new Structure();
        }
    }

    /**
       @roseuid 3662B3BB023D
     */
	public Structure useSnmpDefaults() {
        snmpSession.setTimeout(this.defaultTimeout);
        snmpSession.setRetries(this.defaultRetries);
        JsnmpBridge.debugOut("useSnmpDefaults: timeout: " + this.defaultTimeout + " ms, retries: " + this.defaultRetries);
        try {
            return new Structure(
                new Symbol[] {TypeConverter.ERROR_CODE, TypeConverter.ERROR_STRING},
                new Object[] {0, "GSI_SUCCESS"});
        } catch (com.gensym.util.NtwIllegalArgumentException e) {
            sendMessage("Error using snmp defaults", "", "Error creating return structure", 3);
            return new Structure();
        }
    }

    /**
       @roseuid 3662B3BC007C
     */
	public Structure useSnmpCommParams() {
		snmpSession.setTimeout(this.timeout);
        snmpSession.setRetries(this.retries);
        JsnmpBridge.debugOut("useSnmpCommParams: timeout: " + this.timeout + " ms, retries: " + this.retries);
        try{
            return new Structure(
                new Symbol[] {TypeConverter.ERROR_CODE, TypeConverter.ERROR_STRING},
                new Object[] {0, "GSI_SUCCESS"});
        } catch (com.gensym.util.NtwIllegalArgumentException e) {
            sendMessage("Error using comm params", "", "Error creating return structure", 3);
            return new Structure();
        }
    }
    /**
       Called by G2 to perform a nonblocking transaction.
	   Change the return type to String to return text result-ids
       (see also the TypeConverter.fixResultID method).
    */
	//public Integer nonBlockingTransaction(String tagname,
	public String nonBlockingTransaction(String tagname,
										 int snmpVersion,
										 int reqCode,
										 String node_name,
										 String community,
										 Structure getbulk_parameters,
										 Structure trap_parameters,
										 Sequence variables) {
		int resInt = 0;
		// Integer result = null;
		String result = null;

		JsnmpBridge.debugOut ("node_name = " + node_name + " tagname = " + tagname + 
                  "  snmpVersion = " + snmpVersion + " community = " + community + " reqCode = " + reqCode);
		if ((snmpVersion != SnmpAPI.SNMP_VERSION_1) &&
			(snmpVersion != SnmpAPI.SNMP_VERSION_2C)) {
			JsnmpBridge.debugOut("Error (nonblocking transaction): wrong SNMP version parameter " + snmpVersion);
			sendMessage("Error (nonblocking transaction)", node_name, "wrong SNMP version parameter " + snmpVersion, 1);
			startReceiveNonblocking( TypeConverter.errorToG2Structure(node_name,
										"Error (nonblocking transaction): wrong SNMP version parameter " + snmpVersion,
										25),
									 (resInt = snmpApi.genReqID()));
			LogFile.logTransaction(reqCode, node_name, false);
			return TypeConverter.fixResultID(resInt);
		}

		Exception except = null;

		try {
			SnmpPDU pdu;
                        //APIv4
                        UDPProtocolOptions opt;

			JsnmpBridge.debugOut ("trap req msg = " + ((int)SnmpAPI.TRP_REQ_MSG & 0xFF));
			JsnmpBridge.debugOut ("trap2 req msg = " + ((int)SnmpAPI.TRP2_REQ_MSG& 0xFF));
			JsnmpBridge.debugOut ("inform req msg = " + ((int)SnmpAPI.INFORM_REQ_MSG& 0xFF));
			JsnmpBridge.debugOut ("getbulk req msg = " + ((int)SnmpAPI.GETBULK_REQ_MSG& 0xFF));
			switch ((byte)reqCode) {
			case SnmpAPI.TRP_REQ_MSG:
				pdu = TypeConverter.g2SequenceToTrapPdu(snmpApi, reqCode, node_name, community, trap_parameters,variables);
				//APIv3->pdu.setRemotePort(snmpApi.SNMP_TRAP_PORT);
                                opt = (UDPProtocolOptions)pdu.getProtocolOptions();
				opt.setRemotePort(snmpApi.SNMP_TRAP_PORT);
				snmpSession.setVersion(SnmpAPI.SNMP_VERSION_1);
				 break;
			case SnmpAPI.TRP2_REQ_MSG:
			case SnmpAPI.INFORM_REQ_MSG:
				pdu = TypeConverter.g2SequenceToPdu(snmpApi, reqCode, node_name, community, variables);
				//APIv3->pdu.setRemotePort(snmpApi.SNMP_TRAP_PORT);
                                opt = (UDPProtocolOptions)pdu.getProtocolOptions();
				opt.setRemotePort(snmpApi.SNMP_TRAP_PORT);
				snmpSession.setVersion(SnmpAPI.SNMP_VERSION_2C);
				break;
			case SnmpAPI.GETBULK_REQ_MSG:
				pdu = TypeConverter.g2SequenceToGetbulkPdu(snmpApi, reqCode, node_name, community, getbulk_parameters, variables);
				snmpSession.setVersion(SnmpAPI.SNMP_VERSION_2C);
				break;
			default:
				pdu = TypeConverter.g2SequenceToPdu(snmpApi, reqCode, node_name, community, variables);
				snmpSession.setVersion(snmpVersion);
			}

			snmpSession.setCommunity(community);
                        // Sending out the request
			result = TypeConverter.fixResultID(snmpSession.send(pdu));
			LogFile.logTransaction(reqCode, node_name, true);

		} catch (TypeConversionException e) {
			except = e;
		} catch (SnmpException e) {
			except = e;
		}
		if (except != null) {
			JsnmpBridge.debugOut("Error (nonblocking transaction): " + except.getMessage() + " (Node " + node_name + ")");
			sendMessage("Error (nonblocking transaction)",
				node_name, except.getMessage(), 1);
			startReceiveNonblocking( TypeConverter.errorToG2Structure(node_name,
										"Error (nonblocking transaction): " + except.getMessage(),
										25),
									 (resInt = snmpApi.genReqID()));
			result = TypeConverter.fixResultID(resInt);
			LogFile.logTransaction(reqCode, node_name, false);
		}
		return result;
	}
	public boolean alwaysResolveName(boolean ResolveName)
	{
		JsnmpBridge.debugOut("alwaysResolveName = " +  ResolveName);
		TypeConverter.set_always_resolve_name(ResolveName);
		return true;
	}
	public boolean deleteSnmpv3Entry (String hostname, int port){
		snmpApi.getSnmpEngine().removeEntry(hostname,port);
		return true;
	}
	public boolean deleteUSMEntry (String username, String hostname, int port)
	{

		try {
			//ut.removeAllEntries();
			USMUserTable ut = (USMUserTable)snmpApi.getSecurityProvider().getTable(USM_SECURITY_MODEL);
			ut.removeEntry(username.getBytes(Charset.defaultCharset()), snmpApi.getSnmpEngine().getEntry(hostname,port).getEngineID());
			snmpApi.getSnmpEngine().removeEntry(hostname,port);
		}catch(Exception e){

			JsnmpBridge.debugOut("deleteUSMEntry exception thrown:" + e.getMessage() + ". User:" + username + " not found at "+  hostname + ":" + port);
			return false;
		}
		JsnmpBridge.debugOut("Deleted : username=" + username +  ",host= " + hostname + ":" + port);
		return true;
	}
	public boolean deleteUSMUser(String name, byte[] engineid){

	try{
		USMUserTable USMTable = (USMUserTable)snmpApi.getSecurityProvider().getTable(USM_SECURITY_MODEL);
			return (USMTable.removeEntry (name.getBytes(Charset.defaultCharset()), engineid ));
	}catch(Exception e){
		SnmpString s = new SnmpString(engineid);
		JsnmpBridge.debugOut("deleteUSMUser error:" + e.getMessage() + ", username:engineid = "+ name +":"+ s.toByteString() );
	}
		return false;
	}
	/**
	   Called by G2 to perform a nonblocking Snmpv3 transaction.
	   Change the return type to String to return text result-ids
	   (see also the TypeConverter.fixResultID method).
	*/

	public String nonBlockingSnmpv3Transaction(final String tagname ,
												final int snmpVersion,
												final int reqCode,
												final String node_name,
												final String community,
												final String wcommunity,
												final int port,
												final String engine_id,
												final String userName,
												final String auth_protocol,
												final String auth_password,
												final String priv_password,
												final String context_id,
												final String contextName,
												final Structure getbulk_parameters,
												final Structure trap_parameters,
												final Sequence variables) {

		String engineId = engine_id;
		int resInt = 0;
		String result = null;
		int i=-1;
                //APIv4
                UDPProtocolOptions opt;
                UDPProtocolOptions sessionOpt;

		if ((snmpVersion == SnmpAPI.SNMP_VERSION_1) ||
			(snmpVersion == SnmpAPI.SNMP_VERSION_2) ||
			(snmpVersion == SnmpAPI.SNMP_VERSION_2C) ){

			result = nonBlockingTransaction( tagname,
										  snmpVersion,
										  reqCode,
										  node_name,
										  community,
										  getbulk_parameters,
										  trap_parameters,
										  variables);
			return result;
		}

		Charset charset = Charset.defaultCharset();
		
		JsnmpBridge.debugOut("\n\n******\nEntering nonblockingSnmpv3Request .....");
		if ((snmpVersion != SnmpAPI.SNMP_VERSION_3)) {
			JsnmpBridge.debugOut("Error (SNMPv3 nonblocking transaction): wrong SNMP version parameter " + snmpVersion);
			sendMessage("Error (SNMPv3 nonblocking transaction)", node_name, "Expecting SNMPv3 but received wrong SNMP version parameter " + snmpVersion, 1);
			LogFile.logTransaction(reqCode, node_name, false);
			startReceiveNonblocking( TypeConverter.errorToG2Structure(node_name,
										"Error (SNMPv3 nonblocking transaction): wrong SNMP version parameter " + snmpVersion,
										25),
									 (resInt = snmpApi.genReqID()));
			LogFile.logTransaction(reqCode, node_name, false);
			return TypeConverter.fixResultID(resInt);
		}
		Exception except = null;
		SnmpPDU pdu;
		SnmpSession session = new SnmpSession(snmpApi);
		session.setVersion(SnmpAPI.SNMP_VERSION_3);
		//APIv3->session.setRemotePort (port);
                sessionOpt = (UDPProtocolOptions)session.getProtocolOptions();
		sessionOpt.setRemotePort (port);
		session.setWriteCommunity(wcommunity);
		session.setCommunity(community);
		//APIv3->session.setPeername(node_name);
		sessionOpt.setRemoteHost(node_name);
		try {
			if (userName.equals("")){
					throw new SnmpException("Invalid User Name");
			}
			if (auth_protocol.equals ("SHA"))
				authProtocol = USMUserEntry.SHA_AUTH;
			else if  (auth_protocol.equals ("MD5"))
				authProtocol = USMUserEntry.MD5_AUTH;
			else
				authProtocol = USMUserEntry.NO_AUTH;
			switch ((byte)reqCode) {
			case SnmpAPI.GETBULK_REQ_MSG:
				pdu = TypeConverter.g2SequenceToGetbulkPdu(snmpApi, reqCode, node_name, community, getbulk_parameters, variables);
				break;
			case SnmpAPI.TRP2_REQ_MSG:
				if(engineId.startsWith("0x") || engineId.startsWith("0X"))
						engineId = TypeConverter.HextoString(engineId);
				deleteUSMUser(userName, snmpApi.getSnmpEngineID());
				pdu = TypeConverter.g2SequenceToV3TrapPdu(snmpApi, reqCode, node_name, community, trap_parameters,variables);
				TypeConverter.createUSMTable(userName.getBytes(), engineId.getBytes(), authProtocol,
								auth_password, priv_password, snmpApi);
JsnmpBridge.debugOut("\nFinished createUSMTable " + ",input engineID= " + engineId + ", SnmpAPI.SNMP_VERSION_3= "+SnmpAPI.SNMP_VERSION_3 + ", auth_password=" + auth_password + ", priv_password=" + priv_password);
//				if (authProtocol ==  USMUserEntry.NO_AUTH){
					session.open();
					pdu.setUserName(userName.getBytes(charset));
					pdu.setCommand((byte)reqCode);
					pdu.setContextName(contextName.getBytes(charset));
					pdu.setContextID(context_id.getBytes(charset));
					return (TypeConverter.fixResultID(session.send(pdu)));
//				}else{
//					break;
//				}
			default:
				pdu = TypeConverter.g2SequenceToPdu(snmpApi, reqCode, node_name, community, variables);
			}
			session.open();
			pdu.setUserName(userName.getBytes(charset));

//APIv3->JsnmpBridge.debugOut("\nUsername= "+userName+",prot= "+authProtocol+",pass= "+auth_password+",priv= "+priv_password+",peername= "+session.getPeername()+".");
                        sessionOpt = (UDPProtocolOptions)session.getProtocolOptions();
JsnmpBridge.debugOut("\nUsername= "+userName+",prot= "+authProtocol+",pass= "+auth_password+",priv= "+priv_password+",peername= "+sessionOpt.getRemoteHost()+".");
			// Replaced by the line below comment as suggested by AdventNet.
			//   USMUtils.init_v3_params(userName, authProtocol, auth_password, priv_password, session.getPeername(), port, session);
			//APIv3->USMUtils.init_v3_parameters(userName, authProtocol, auth_password, priv_password, session.getPeername(), port, session);
			USMUtils.init_v3_parameters(userName, authProtocol, auth_password, priv_password, sessionOpt.getRemoteHost(), port, session);
JsnmpBridge.debugOut("\nFinished USMUtils.init_v3_parameters()");
			pdu.setCommand((byte)reqCode);
			//APIv3->pdu.setRemotePort(port);
                        opt = (UDPProtocolOptions)pdu.getProtocolOptions();
			opt.setRemotePort(port);
			pdu.setContextName(contextName.getBytes(charset));
			pdu.setContextID(context_id.getBytes(charset));
			session.setTimeout(this.timeout);
			session.setRetries(this.retries);
			session.addSnmpClient(this);
			session.setCallbackthread(true);
			result = TypeConverter.fixResultID(session.send(pdu));
		} catch (SnmpException e) {
			result=TypeConverter.fixResultID(resInt);
			JsnmpBridge.debugOut("SnmpException:" + e.getMessage());
		} catch (TypeConversionException e) {
			result=TypeConverter.fixResultID(resInt);
			JsnmpBridge.debugOut("TypeConversionException:" + e.getMessage());
		}
/*		try{
			Thread.sleep(2000);
		}catch(Exception e){JsnmpBridge.debugOut("Exception:" + e.getMessage());};
*/		return result;
	}
	public Structure blockingSnmpv3Transaction(String tagname ,
											   int snmpVersion,
											   int reqCode,
											   String node_name,
											   String community,
											   String wcommunity,
											   int port,
											   String engine_id,
											   String userName,
											   String auth_protocol,
											   String auth_password,
											   String priv_password,
											   String context_id,
											   String contextName,
											   Structure getbulk_parameters,
											   Sequence variables) {
                //APIv4
                UDPProtocolOptions sessionOpt;

		int i=-1;
JsnmpBridge.debugOut("\n\n******\nEntering blockingSnmpv3Transaction .....");
		if ((snmpVersion == SnmpAPI.SNMP_VERSION_1) ||
			(snmpVersion == SnmpAPI.SNMP_VERSION_2) ||
			(snmpVersion == SnmpAPI.SNMP_VERSION_2C) ){

			return blockingTransaction(tagname,
									   snmpVersion,
									   reqCode,
									   node_name,
									   community,
									   getbulk_parameters,
									   variables);
		}
		
		Charset charset = Charset.defaultCharset();
		
		if ((snmpVersion != SnmpAPI.SNMP_VERSION_3)) {
			JsnmpBridge.debugOut("Error (blocking transaction): wrong SNMP version parameter " + snmpVersion);
			sendMessage("Error (blocking transaction)", node_name, "Expecting SNMPv3 but received wrong SNMP version parameter " + snmpVersion, 1);
			LogFile.logTransaction(reqCode, node_name, false);
			return TypeConverter.errorToG2Structure(node_name, "Error (blocking transaction): wrong SNMP version parameter " + snmpVersion, 26);
		}

		if (((byte)reqCode == SnmpAPI.TRP_REQ_MSG) ||
			((byte)reqCode == SnmpAPI.TRP2_REQ_MSG)){
			JsnmpBridge.debugOut("Error (blocking transaction): cannot perform blocking request for the request code " + reqCode);
			sendMessage("Error (blocking transaction)", node_name, "cannot perform blocking request for the request code " + reqCode, 1);
			LogFile.logTransaction(reqCode, node_name, false);
			return TypeConverter.errorToG2Structure(node_name, "Error (blocking transaction): cannot perform blocking request for the request code " + reqCode, 26);
		}
		Structure result = null;
		Exception except = null;
		SnmpPDU pdu;
		SnmpSession session = new SnmpSession(snmpApi);
		session.setVersion(SnmpAPI.SNMP_VERSION_3);
		try {
			if (userName.equals(""))
				throw new SnmpException("Invalide User Name");
			switch ((byte)reqCode) {
//			case SnmpAPI.INFORM_REQ_MSG:
//				pdu = TypeConverter.g2SequenceToPdu(snmpApi, reqCode, node_name, community, variables);
///				session.setVersion(SnmpAPI.SNMP_VERSION_2C);
//				break;
			case SnmpAPI.GETBULK_REQ_MSG:
				pdu = TypeConverter.g2SequenceToGetbulkPdu(snmpApi, reqCode, node_name, community, getbulk_parameters, variables);
				break;
			default:
				pdu = TypeConverter.g2SequenceToPdu(snmpApi, reqCode, node_name, community, variables);

			}
			if (pdu==null) throw new SnmpException("SNMPV3 Request timed Out");
			//APIv3->session.setRemotePort (port);
                        sessionOpt = (UDPProtocolOptions)session.getProtocolOptions();
			sessionOpt.setRemotePort (port);
			pdu.setUserName(userName.getBytes(charset));
			pdu.setCommand((byte)reqCode);
			//APIv3->session.setPeername(node_name);
			sessionOpt.setRemoteHost(node_name);
			if (userName.equals(""))
				throw new SnmpException("Invalid User Name");
			if (auth_protocol.equals ("SHA"))
				authProtocol = USMUserEntry.SHA_AUTH;
			else if  (auth_protocol.equals ("MD5"))
				authProtocol = USMUserEntry.MD5_AUTH;
			else
				authProtocol = USMUserEntry.NO_AUTH;
			session.open();
//APIv3->JsnmpBridge.debugOut("\nUsername="+userName+",prot="+authProtocol+",passw="+auth_password+",priv="+priv_password+",peername="+session.getPeername()+".");
                        sessionOpt = (UDPProtocolOptions)session.getProtocolOptions();
JsnmpBridge.debugOut("\nUsername="+userName+",prot="+authProtocol+",passw="+auth_password+",priv="+priv_password+",peername="+sessionOpt.getRemoteHost()+".");
			// Replaced by the line below comment as suggested by AdventNet.
      //   USMUtils.init_v3_params(userName, authProtocol, auth_password, priv_password, session.getPeername(),port,session);
			//APIv3->USMUtils.init_v3_parameters(userName, authProtocol, auth_password, priv_password, session.getPeername(),port,session);
			USMUtils.init_v3_parameters(userName, authProtocol, auth_password, priv_password, sessionOpt.getRemoteHost(),port,session);
JsnmpBridge.debugOut("\nFinished USMUtils.init_v3_parameters()");
			pdu.setContextName(contextName.getBytes(charset));
			pdu.setContextID(context_id.getBytes(charset));
			int reqid = snmpApi.genReqID();
			pdu.setReqid(reqid);
			Integer reqidObj = reqid;
			// Add reqid to the storage
			syncSendReqIds.addElement(reqidObj);
			session.setTimeout(this.timeout);
			session.setRetries(this.retries);
JsnmpBridge.debugOut("SyncSending..."); 
			pdu = session.syncSend(pdu);
			if (pdu==null) throw new SnmpException("SNMPV3 Request timed Out");
JsnmpBridge.debugOut("======\nTransactor.blockingSnmpv3Transaction,  pdu : "+pdu.getMsg()+"\n"+pdu.getVariableBinding(0).getObjectID().toString()+"\n======");
			if ((i = invalidOidList.indexOf(pdu.getVariableBinding(0).getObjectID().toString()))!= -1 )
				throw new SnmpException("SNMPV3 Request failed: "+ ErrorMessages[i]);
			session.close ();
			// Remove reqid from the storage
			syncSendReqIds.removeElement(reqidObj);
			// Fill in result structure
			result = TypeConverter.pduToG2Structure(pdu, node_name);
			JsnmpBridge.debugOut(result.toString());
			LogFile.logTransaction(reqCode, node_name, true);
		} catch (SnmpException e) {
			except = e;
		} catch (TypeConversionException e) {
			except = e;
		}
		if (except != null){
			JsnmpBridge.debugOut("Error (Snmpv3 blocking transaction): " + except.getMessage() + " (Node " + node_name + ")");
			sendMessage("Error (Snmpv3 blocking transaction)",
				node_name, except.getMessage(), 1);
			result = TypeConverter.errorToG2Structure(node_name, "Error (Snmpv3 blocking transaction): " + except.getMessage(), 26);
			LogFile.logTransaction(reqCode, node_name, false);
		}
		return result;

	}
	/**
	   Called by G2 to perform a blocking transaction.
	   @roseuid 36777D5B029E
	 */
	public Structure blockingTransaction(String tagname,
										 int snmpVersion,
										 int reqCode,
										 String node_name,
										 String community,
										 Structure getbulk_parameters,
										 Sequence variables) {
		UDPProtocolOptions opt;

		if ((snmpVersion != SnmpAPI.SNMP_VERSION_1) &&
			(snmpVersion != SnmpAPI.SNMP_VERSION_2C)) {
			JsnmpBridge.debugOut("Error (blocking transaction): wrong SNMP version parameter " + snmpVersion);
			sendMessage("Error (blocking transaction)", node_name, "wrong SNMP version parameter " + snmpVersion, 1);
			LogFile.logTransaction(reqCode, node_name, false);
			return TypeConverter.errorToG2Structure(node_name, "Error (blocking transaction): wrong SNMP version parameter " + snmpVersion, 26);
		}

		if (((byte)reqCode == SnmpAPI.TRP_REQ_MSG) ||
			((byte)reqCode == SnmpAPI.TRP2_REQ_MSG) ||
			((byte)reqCode == SnmpAPI.INFORM_REQ_MSG)){
			JsnmpBridge.debugOut("Error (blocking transaction): cannot perform blocking request for the request code " + reqCode);
			sendMessage("Error (blocking transaction)", node_name, "cannot perform blocking request for the request code " + reqCode, 1);
			LogFile.logTransaction(reqCode, node_name, false);
            return TypeConverter.errorToG2Structure(node_name, "Error (blocking transaction): cannot perform blocking request for the request code " + reqCode, 26);
		}

		Structure result = null;
		Exception except = null;

		try {
			SnmpPDU pdu;
			switch ((byte)reqCode) {
			case SnmpAPI.INFORM_REQ_MSG:
				pdu = TypeConverter.g2SequenceToPdu(snmpApi, reqCode, node_name, community, variables);
				snmpSession.setVersion(SnmpAPI.SNMP_VERSION_2C);
				break;
			case SnmpAPI.GETBULK_REQ_MSG:
				pdu = TypeConverter.g2SequenceToGetbulkPdu(snmpApi, reqCode, node_name, community, getbulk_parameters, variables);
				snmpSession.setVersion(SnmpAPI.SNMP_VERSION_2C);
				break;
			default:
				pdu = TypeConverter.g2SequenceToPdu(snmpApi, reqCode, node_name, community, variables);
				snmpSession.setVersion(snmpVersion);
			}

System.out.println ("PDU Community name = '" + pdu.getCommunity() + "'");
			int reqid = snmpApi.genReqID();
			pdu.setReqid(reqid);

			Integer reqidObj = reqid;
			// Add reqid to the storage
			syncSendReqIds.addElement(reqidObj);

			snmpSession.setCommunity(community);
System.out.println ("snmpSession Community name = '" + snmpSession.getCommunity() + "'");
			pdu = snmpSession.syncSend(pdu);
			// Remove reqid from the storage
			syncSendReqIds.removeElement(reqidObj);
			// Fill in result structure
			result = TypeConverter.pduToG2Structure(pdu, node_name);
			JsnmpBridge.debugOut(result.toString());
			LogFile.logTransaction(reqCode, node_name, true);
		} catch (SnmpException e) {
			except = e;
		} catch (TypeConversionException e) {
			except = e;
		}
		if (except != null){
			JsnmpBridge.debugOut("Error (blocking transaction): " + except.getMessage() + " (Node " + node_name + ")");
			sendMessage("Error (blocking transaction)",
				node_name, except.getMessage(), 1);
			result = TypeConverter.errorToG2Structure(node_name, "Error (blocking transaction): " + except.getMessage(), 26);
			LogFile.logTransaction(reqCode, node_name, false);
		}
		return result;
	}


	private void startReceiveNonblocking(Structure result, int reqId){

		Object[] parameters = new Object[1];
		result.setAttributeValue(TypeConverter.RESULT_ID, TypeConverter.fixResultID(reqId));
		parameters[0] = result;

		if (g2connection != null){
			if (g2connection.isAlive()) {
				try {
                                        // Calling the G2 procedure to receive the information
					this.g2connection.callRPC(ReceiveNonblocking, parameters);
				} catch (com.gensym.jgi.G2AccessException e) {
JsnmpBridge.debugOut ("Transactor.startReceiveNonblocking::error message = "+e.getMessage());
				}
			}
		}
	}

}
