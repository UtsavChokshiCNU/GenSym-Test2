package com.gensym.G2SNMP.rpc;

import java.util.Enumeration;
import java.net.InetAddress;
import java.nio.charset.Charset;
import java.util.Vector;
import com.adventnet.snmp.snmp2.*;
import com.adventnet.snmp.mibs.LeafSyntax;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.G2SNMP.JsnmpBridge;
import com.adventnet.snmp.snmp2.usm.*;

/**
   This class is a collection of type conversion routines.
   All the methods are static.
*/
public final class TypeConverter{

    /**
    Constants for the structure fields
    */
    public static final Symbol ENTERPRISE_ID = Symbol.intern("ENTERPRISE-ID");
	public static final Symbol AGENT_IP_ADDRESS = Symbol.intern("AGENT-IP-ADDRESS");
    public static final Symbol RESULT_ID = Symbol.intern("RESULT-ID");
    public static final Symbol GENERIC_TRAP_ID = Symbol.intern("GENERIC-TRAP-ID");
    public static final Symbol SPECIFIC_TRAP_ID = Symbol.intern("SPECIFIC-TRAP-ID");
	public static final Symbol AGENT_RUN_TIME = Symbol.intern("AGENT-RUN-TIME");

    public static final Symbol NON_REPEATERS = Symbol.intern("NON-REPEATERS");
    public static final Symbol MAX_REPETITIONS = Symbol.intern("MAX-REPETITIONS");


	public static final Symbol VARIABLE_OID = Symbol.intern("VARIABLE-OID");
	public static final Symbol VARIABLE_ASN1_TYPE = Symbol.intern("VARIABLE-ASN1-TYPE");
    public static final Symbol VARIABLE_VALUE = Symbol.intern("VARIABLE-VALUE");
    public static final Symbol ERROR_CODE = Symbol.intern("ERROR-CODE");
	public static final Symbol ERROR_STRING = Symbol.intern("ERROR-STRING");
	public static final Symbol NODE_NAME = Symbol.intern("NODE-NAME");
	public static final Symbol VARIABLES = Symbol.intern("VARIABLES");

	// snmpv3 specific
	public static final Symbol PORT_ID = Symbol.intern ("PORT");
	public static final Symbol USERNAME = Symbol.intern("USERNAME");
	public static final Symbol ENGINE_ID = Symbol.intern("ENGINE-ID");
	public static final Symbol AUTH_PROTOCOL = Symbol.intern("AUTH-PROTOCOL");
	public static final Symbol AUTH_PASSWORD = Symbol.intern("AUTH-PASSWORD");
	public static final Symbol PRIV_PASSWORD = Symbol.intern("PRIV-PASSWORD");
	public static final Symbol CONTEXT_ID = Symbol.intern("CONTEXT-ID");
	public static final Symbol CONTEXT_NAME = Symbol.intern("CONTEXT-NAME");
	static final int USM_SECURITY_MODEL = 3;
	static int authProtocol = USMUserEntry.NO_AUTH;

	private static final int timeOutErrorCode = -1;
	/*
	2^^29 - 1
	*/
	public static final int MAXIMUM_G2_INT = 0x1FFFFFFF;
	public static final long MIN_TIME_TICK = 0L;
	public static final long MAX_TIME_TICK = 0xFFFFFFFFL;

	/* 2^31-1 */
	public static final int MAX_SPECIFIC_ID = 0x7FFFFFFF;
	public static final int MIN_SPECIFIC_ID = 0;
	public static final int MAX_GENERIC_ID = 6;
	public static final int MIN_GENERIC_ID = 0;

	public static boolean ALWAYS_RESOLVE_NAME = true;

	public static void set_always_resolve_name (boolean resolveName){
		JsnmpBridge.debugOut("TypeConverter: alwaysResolveName = " +  resolveName);
		ALWAYS_RESOLVE_NAME = resolveName;
	}

	public static SnmpPDU g2SequenceToPdu(SnmpAPI snmpApi,
										  int reqCode,
										  String node_name,
										  String community,
										  Sequence variables) throws TypeConversionException {
          //APIv4
          UDPProtocolOptions opt;

		try {
			InetAddress address = InetAddress.getByName(node_name);
//			System.out.println ("Address = " + address);
			SnmpPDU pdu = new SnmpPDU();

            pdu.setCommand((byte)reqCode);
            /* Issue HQ-5327864: by setting the DNS Lookup to FALSE, there appears to be no
               delay in sending out the PDU. */
            //setDNSLookup is not performed as per AdventNet SNMP APIv4 migration guide.
            //APIv3->pdu.setDNSLookup (false);

            //APIv3->pdu.setAddress(address);
			opt = new UDPProtocolOptions();
//            opt = (UDPProtocolOptions)pdu.getProtocolOptions();
            opt.setRemoteAddress(address);
			//opt.setRemotePort (160);
			pdu.setProtocolOptions(opt);
			pdu.setCommunity(community);
			for (Enumeration enum1 = variables.elements(); enum1.hasMoreElements(); ) {
                Structure struct = (Structure)enum1.nextElement();
                if (struct == null) {
                    // do nothing with empty structure
                    continue;
                }
                // Get structure attribute for OID
                SnmpOID oid = getOidAttributeValue(struct, VARIABLE_OID);

                try {
                    String value = getValueAttributeValue(struct, VARIABLE_VALUE).toString();
                    Integer type = getIntegerAttributeValue(struct, VARIABLE_ASN1_TYPE);
                    // if value or type isn't specified properly, then add empty varbind
                    if ((value == null) || (type == null)) {
                        if (pdu.getCommand() == SnmpAPI.SET_REQ_MSG ||
                            pdu.getCommand() == SnmpAPI.TRP_REQ_MSG ||
                            pdu.getCommand() == SnmpAPI.TRP2_REQ_MSG) {
                            throw new TypeConversionException("Empty " + VARIABLE_VALUE +
                                " or " + VARIABLE_ASN1_TYPE +
								" is not allowed for the request of type " +
                                reqCode);
                        }
                        pdu.addNull( oid );
                    } else { // Try to add VarBind with newly created OID and existed value
                        addVarBind(pdu, oid, type.byteValue(), value);
                    }
				} catch(TypeConversionException e){
					if (pdu.getCommand() == SnmpAPI.SET_REQ_MSG ||
					pdu.getCommand() == SnmpAPI.TRP_REQ_MSG ||
					pdu.getCommand() == SnmpAPI.TRP2_REQ_MSG) {
					   throw e;
					} // if the command is not SET or TRAP then add empty varbind
					pdu.addNull( oid );
				 }
			}
			return pdu;
		} catch(java.util.NoSuchElementException e) {
            throw new TypeConversionException("Can't get next element of sequence: " + e.getMessage());
        } catch (java.net.UnknownHostException e){
            throw new TypeConversionException("Unknown host " + node_name);
        }
	}
	public static SnmpPDU g2SequenceToV3Pdu(SnmpAPI snmpApi,
										  int reqCode,
										  String node_name,
										  String community,
										  String wcommunity,
										  int port,
										  String engine_id,
										  String userName,
										  String auth_protocol,
										  String authPassword,
										  String privPassword,
										  String context_id,
										  String contextName,
										  Sequence variables) throws TypeConversionException {
                //APIV4
                UDPProtocolOptions opt;
                
        Charset charset = Charset.defaultCharset();
        
		SnmpPDU pdu = g2SequenceToPdu(snmpApi, reqCode, node_name, community, variables);
		if (pdu != null){
		//try {
			//APIv3->if (port != 0)	pdu.setRemotePort (port); else pdu.setRemotePort(162);
                        opt = (UDPProtocolOptions)pdu.getProtocolOptions();
			if (port != 0)	opt.setRemotePort (port); else opt.setRemotePort(162);
			JsnmpBridge.debugOut("UserName = " + userName + ", id =" + engine_id );
			opt.setRemotePort (port);
			pdu.setUserName(userName.getBytes(charset));
			pdu.setUserName(userName.getBytes(charset));
			pdu.setContextName(contextName.getBytes(charset));
			pdu.setContextID(context_id.getBytes(charset));
			if (auth_protocol.equals ("SHA"))
				authProtocol = USMUserEntry.SHA_AUTH;
			else
				authProtocol = USMUserEntry.MD5_AUTH;
			pdu.setContextID (context_id.getBytes(charset));
			//USMUtils.init_v3_params(userName, authProtocol, authPassword, privPassword, node_name,session.getRemotePort(),session);
		}
		return pdu;
	}

	public static SnmpPDU g2SequenceToTrapPdu(SnmpAPI snmpApi,
											  int reqCode,
											  String node_name,
											  String community,
											  Structure trap_parameters,
											  Sequence variables) throws TypeConversionException {
                //APIv4
                UDPProtocolOptions opt;

		SnmpPDU pdu = g2SequenceToPdu(snmpApi, reqCode, node_name, community, variables);

        try {
			//APIv3->pdu.setRemotePort(snmpApi.SNMP_TRAP_PORT);
                        opt = (UDPProtocolOptions)pdu.getProtocolOptions();
			opt.setRemotePort(snmpApi.SNMP_TRAP_PORT);
			pdu.setAgentAddress(InetAddress.getByName(getStringAttributeValue(trap_parameters, AGENT_IP_ADDRESS)));
			Number buffer = getNumberAttributeValue(trap_parameters,AGENT_RUN_TIME);
			if ((buffer.doubleValue() > MAX_TIME_TICK)||
                (buffer.doubleValue() < MIN_TIME_TICK)){
                throw new TypeConversionException("Value " +
                                      buffer.doubleValue() +
									  " is out of interval [" + MIN_TIME_TICK +
                                      "; " + MAX_TIME_TICK + "] for agent-uptime");
			}

            pdu.setUpTime(buffer.longValue());
			pdu.setEnterprise(getOidAttributeValue(trap_parameters, ENTERPRISE_ID));
            pdu.setTrapType(intToGenericId( getIntegerAttributeValue(trap_parameters,
                                                                GENERIC_TRAP_ID).intValue()));
			pdu.setSpecificType(doubleToSpecificId(getNumberAttributeValue(trap_parameters,
                                                                SPECIFIC_TRAP_ID).doubleValue()));

        }catch (java.net.UnknownHostException e) {
                throw new TypeConversionException("Unknown host " + node_name);
        }
        return pdu;

	}
	public static SnmpPDU g2SequenceToV3TrapPdu(SnmpAPI snmpApi,
											  int reqCode,
											  String node_name,
											  String community,
											  Structure trap_parameters,
											Sequence variables) throws TypeConversionException {
		SnmpPDU pdu = g2SequenceToPdu(snmpApi, reqCode, node_name, community, variables);
		Number buffer = getNumberAttributeValue(trap_parameters,AGENT_RUN_TIME);
		if ((buffer.doubleValue() > MAX_TIME_TICK)||
			(buffer.doubleValue() < MIN_TIME_TICK)){
			throw new TypeConversionException("Value " +
								  buffer.doubleValue() +
									  " is out of interval [" + MIN_TIME_TICK +
									  "; " + MAX_TIME_TICK + "] for agent-uptime");
		}
		pdu.setUpTime(buffer.longValue());
		return pdu;
	}

	public static SnmpPDU g2SequenceToGetbulkPdu(SnmpAPI snmpApi,
											  int reqCode,
											  String node_name,
											  String community,
											  Structure getbulk_parameters,
											  Sequence variables) throws TypeConversionException {

        SnmpPDU pdu = g2SequenceToPdu(snmpApi, reqCode, node_name, community, variables);

        pdu.setErrstat(getIntegerAttributeValue(getbulk_parameters, NON_REPEATERS).intValue());
        pdu.setErrindex(getIntegerAttributeValue(getbulk_parameters, MAX_REPETITIONS).intValue());
        return pdu;
    }

	public static Structure pduToG2Structure(SnmpPDU pdu, String sentToNode) {
        Structure result = new Structure();
        Integer error_code;
        String error_string;
        String node = sentToNode;
        Sequence resSequence = new Sequence();

        // APIv4 change
        UDPProtocolOptions opt;

        // timeout
		if (pdu == null) {
            if (sentToNode != null && !"".equals(sentToNode)){
                error_string = "Request timed out to: " + sentToNode;
            }else{
				error_string = "Request timed out";
            }
			JsnmpBridge.debugOut(error_string);
            error_code = timeOutErrorCode;
        } else {
        	//TLEE changed to address the issue HQ-4176710
			// APIv3 -> node = pdu.getAddress().getHostName();
			opt = (UDPProtocolOptions)pdu.getProtocolOptions();
            node = opt.getRemoteHost();
            
			error_code = pdu.getErrstat();
			error_string = SnmpException.exceptionString((byte)pdu.getErrstat());
			resSequence = getVarBindSequence(pdu.getVariableBindings());
		}
		result.setAttributeValue(NODE_NAME, node);
		result.setAttributeValue(ERROR_CODE, error_code);
		result.setAttributeValue(ERROR_STRING, error_string);
		result.setAttributeValue(VARIABLES, resSequence);
		return result;
    }

	public static Sequence getVarBindSequence( Vector variables){
        Sequence result = new Sequence();
        if (variables == null) {
            return result;
        }
        for (Enumeration e = variables.elements();e.hasMoreElements(); ) {
            SnmpVarBind varbind = (SnmpVarBind)e.nextElement();
            Structure structVarBinds = new Structure();
            Integer error_code;
            String error_string;
            if (varbind.getErrindex() != 0) {
                error_code = varbind.getErrindex();
                error_string = SnmpException.exceptionString((byte)(varbind.getErrindex()));
            } else {
                error_code = 0;
                error_string = SnmpException.exceptionString((byte)0);
            }
            // Convert value to the correct G2-acceptable type
            Object value = varbind.getVariable();
            int type = ((SnmpVar)value).getType();
System.out.println("ASN1 type = " + type);
            switch (type) {
                case SnmpAPI.INTEGER:
                    value = getG2quantity(((SnmpInt)value).intValue());
                    break;
                case SnmpAPI.STRING:
                    value = makePrintableString(((SnmpString)value).toBytes());
                    break;
                case SnmpAPI.TIMETICKS:
                    value = getG2timeticks(((SnmpTimeticks)value).longValue());
                    break;
                case SnmpAPI.OPAQUE:
                    value = makePrintableString(((SnmpOpaque)value).toBytes());
                    break;
                case SnmpAPI.IPADDRESS:
                // 8/30/02
                //  Originally we had value=((SnmpIpAddress)value).toHostName(), but this
                //    did a DNS lookup on the IP address.  Since we always want to return
                //    the IP address it is changed to ((SnmpIpAddress)value).toString().
                //    The SnmpIpAddress.toString() method will always return the IP address
                //    in a string format.
                      value = ((SnmpIpAddress)value).toString();
                    break;
                case SnmpAPI.COUNTER:
                    value = getG2quantity(((SnmpCounter)value).longValue());
                    break;
                case SnmpAPI.COUNTER64:
                    long[] longs = (long[])((SnmpCounter64)value).toValue();
                    long val = (longs[1] << 32) + longs[0];
                    double dblVal = val < 0 ? val + 18446744073709551616.0 : val;
                    if (dblVal > MAXIMUM_G2_INT){
                        value = dblVal;
                    } else {
                        value = (int)java.lang.Math.round(dblVal);
                    }
                    break;
                case SnmpAPI.OBJID:
                    value = value.toString();
                    break;
                case SnmpAPI.UNSIGNED32:
                    value = getG2quantity(((SnmpUnsignedInt)value).longValue());
                    break;
                case SnmpAPI.NULLOBJ:
                    value = null;
                    break;
                default:
                    error_code = -1;
                    error_string = "Unknown variable type " + ((SnmpVar)value).getType();
                    JsnmpBridge.debugOut("Can't get Varbind. " + error_string);
                    value = null;
            }
            structVarBinds.setAttributeValue(ERROR_CODE, error_code);
            structVarBinds.setAttributeValue(ERROR_STRING, error_string);
            structVarBinds.setAttributeValue(VARIABLE_ASN1_TYPE, type);
            structVarBinds.setAttributeValue(VARIABLE_OID, varbind.getObjectID().toString());
            structVarBinds.setAttributeValue(VARIABLE_VALUE, value);
            result.addElement(structVarBinds);
        }
        return result;
    }

	static void addVarBind(SnmpPDU pdu, SnmpOID oid, byte type, String value)throws TypeConversionException {

//  HFS It seems they want to create a varbind on the given pdu with the specified oid, type, and value
//      What's the easiest way to do this with the new version of the API?

        if (type == SnmpAPI.NULLOBJ) {
            pdu.addNull(oid);
        } else {        
            try {        
                SnmpVarBind varBind = new SnmpVarBind(oid, SnmpVar.createVariable(value, type));
                pdu.addVariableBinding(varBind);        
            }    
            catch (SnmpException e) {
                throw new TypeConversionException("Cannot create variable: " + oid + " of type " + type + " with value: " + value);        
            }
        }        
        
        
/*        LeafSyntax syntax = new LeafSyntax("", type);   // HFS Best guess is that this creates a generic variable of the specified type
        SnmpVarBind varbind = new SnmpVarBind();    // HFS Need to move this into following block to use SnmpVarBind constructor
        try {
            varbind.setVariable(syntax.createVariable(value));
            if (varbind.getVariable() == null) {
                if (type == SnmpAPI.NULLOBJ) {
                    pdu.addNull( oid );
                } else {
                    throw new TypeConversionException("Cannot create variable: " + oid + " of type " + type + " with value: " + value);
                }
            } else {
                varbind.setObjectID(oid);
                pdu.addVariableBinding(varbind);
            }
        }
        catch (SnmpException e) {
            throw new TypeConversionException("Cannot create variable: " + oid + " of type " + type + " with value: " + value);
        } */

    }

	public static Structure errorToG2Structure(String sentToNode, String errString, int errCode  ) {
        Structure result = new Structure();
        result.setAttributeValue(NODE_NAME, sentToNode);
        result.setAttributeValue(ERROR_CODE, errCode);
        result.setAttributeValue(ERROR_STRING, errString);
		result.setAttributeValue(VARIABLES, new Sequence());
        return result;
    }

  // Changing the type to a double due to G2's limitation on integer types.
  public static Object getG2timeticks(long value) {
    return value;
  }

	public static Object getG2quantity(long value){
        if (java.lang.Math.abs(value) > MAXIMUM_G2_INT){
            // return new Double(value); HFS Hack for agent activation time
            return MAXIMUM_G2_INT;
        } else {
            return Long.valueOf(value).intValue();
        }
    }

	public static Integer getIntegerAttributeValue(Structure struct, Symbol attr_name)
        throws TypeConversionException{

        try{
            return (Integer)struct.getAttributeValue(attr_name);
        }catch (com.gensym.util.NoSuchAttributeException e){
            throw new TypeConversionException(e.getMessage());
        }catch ( java.lang.NumberFormatException e){
            throw new TypeConversionException("Invalid number format for the attibute " + attr_name);
        }catch ( java.lang.ClassCastException e){
            throw new TypeConversionException("Invalid type conversion for the attribute " + attr_name);
        }
    }

	public static Number getNumberAttributeValue(Structure struct, Symbol attr_name)
        throws TypeConversionException{

        try{
			return (Number)struct.getAttributeValue(attr_name);
        }catch (com.gensym.util.NoSuchAttributeException e){
            throw new TypeConversionException(e.getMessage());
        }catch ( java.lang.NumberFormatException e){
            throw new TypeConversionException("Invalid number format for the attibute " + attr_name);
        }catch ( java.lang.ClassCastException e){
            throw new TypeConversionException("Invalid type conversion for the attribute " + attr_name);
        }
    }

	public static String getStringAttributeValue(Structure struct, Symbol attr_name)
        throws TypeConversionException{

        try{
            return (String)struct.getAttributeValue(attr_name);
        }catch (com.gensym.util.NoSuchAttributeException e){
            throw new TypeConversionException(e.getMessage());
        }catch ( java.lang.ClassCastException e){
            throw new TypeConversionException("Invalid type conversion for the attribute " + attr_name);
        }
    }

	public static Object getValueAttributeValue(Structure struct, Symbol attr_name)
        throws TypeConversionException{

        try{
            Object res = struct.getAttributeValue(attr_name);
            if (res instanceof Double) {
                return ((Double)res).longValue();
            }
            if (res instanceof Integer ||
                res instanceof String ||
                res instanceof Symbol) {
                return res;
            } else {
                throw new TypeConversionException("Invalid type " +
                            res.getClass().getName() +
                            " for the attribute " + attr_name);
            }
        } catch (com.gensym.util.NoSuchAttributeException e) {
            throw new TypeConversionException(e.getMessage());
        }
    }

	public static SnmpOID getOidAttributeValue(Structure struct, Symbol attr_name)
        throws TypeConversionException{
        return stringToOid(getStringAttributeValue(struct, attr_name));
    }

    public static SnmpOID stringToOid(String str) throws TypeConversionException{
System.out.println ("Processing OID:" + str);
        SnmpOID oid = new SnmpOID(str);
		if (oid.toValue() == null) {
            throw new TypeConversionException("Invalid OID argument: " + str);
        }
        return oid;
    }

    public static int intToGenericId(int gen)throws TypeConversionException{
        if ((gen < MIN_GENERIC_ID)|| (gen > MAX_GENERIC_ID))
            throw new TypeConversionException("Value " + gen +
                                   " is out of interval [" + MIN_GENERIC_ID +
                                   "; " + MAX_GENERIC_ID + "] for generic-id");
        return gen;

    }

	public static int doubleToSpecificId(double spec)throws TypeConversionException{
        if ((spec < MIN_SPECIFIC_ID)|| (spec > MAX_SPECIFIC_ID))
            throw new TypeConversionException("Value " + spec +
                                   " is out of interval [" + MIN_SPECIFIC_ID +
                                   "; " + MAX_SPECIFIC_ID + "] for specific-id");
        return (int)java.lang.Math.round(spec);

    }

	public static String makePrintableString(byte[] bytes) {

        boolean convert = false;

        int len = bytes.length;
        for (int i = 0; i < len; i++) {
            byte b = bytes[i];
            if (b < 0x20 || b > 0x7E) {
                convert = true;
                break;
            }
        }

        if (!convert)
            return new String(bytes, Charset.defaultCharset());

        StringBuffer buf = new StringBuffer(2 + len * 3);
        buf.append("0x");
        for (int i = 0; true; ) {
            int value = (int)bytes[i] & 0xFF;
            buf.append(Character.forDigit(value / 0x10, 0x10));
            buf.append(Character.forDigit(value % 0x10, 0x10));
            if (++i >= len)
                break;
            buf.append(" ");
        }

        return buf.toString();

    }

	/**
	   Use this method to create a valid result-id (within G2's integer range)
       from a result-id generated by AdventNet.
     */
	//public static Integer fixResultID(int intResultId) {
	public static String fixResultID(int intResultId) {
		// change this to "return String.valueOf(intResultId % 0x20000000);"
		// to return text result-ids

		// return new Integer(intResultId % 0x20000000);  // modulo 2^29
		return String.valueOf (intResultId % 0x20000000);
	}
public static void createUSMTable(byte[] name, byte[] engineID,
									int authProtocol, String authPassword,
									String privPassword, SnmpAPI api)
	{
	byte level = 0;
	USMUserTable uut = (USMUserTable)api.getSecurityProvider().
											getTable(USM_SECURITY_MODEL);
	USMUserEntry entry = new USMUserEntry(name, engineID);
	entry.setAuthProtocol(authProtocol);

	Charset charset = Charset.defaultCharset();
	if ((authProtocol != USMUserEntry.NO_AUTH) && (authPassword != null)&& (authPassword.length () != 0))
	{
		byte[] authKey = USMUtils.password_to_key(authProtocol,
											authPassword.getBytes(charset),
											authPassword.getBytes(charset).length,
											engineID);
			entry.setAuthKey(authKey);
			level = 1;

			if ((privPassword != null)&&(privPassword.length()!=0))
			{
				byte[] tempKey = USMUtils.password_to_key(authProtocol,
											privPassword.getBytes(charset),
											privPassword.getBytes(charset).length,
											engineID);
				byte privKey[]=new byte[16];
				System.arraycopy(tempKey,0,privKey,0,16);
				entry.setPrivKey(privKey);
				level |= 2;
			}
	}
JsnmpBridge.debugOut("TypeConverter::Set USM "+new String(entry.getUserName()) + "; sec lever =" +level);

	entry.setSecurityLevel(level);
	uut.addEntry(entry);
	api.setSnmpEngineID(engineID);
	}
	public static String StringtoHex(String s){
		int i;
		String sRet = "0x";
		byte[] b= s.getBytes(Charset.defaultCharset());
		for (i=0; i< b.length;i++){
			sRet = sRet.concat(Integer.toHexString((int)b[i] &0xFF).toUpperCase()) ;
		}
		return sRet;
	}
	public static String HextoString(String s){
		byte[] temp= { (byte)0 };
		String sRet= "";
		String str;

		for(int i = 2; i < s.length(); i+=2)
		{
			str = s.substring(i,i+2);
			temp[0] = (byte)Integer.parseInt(str,16);
			sRet = sRet.concat (new String(temp, Charset.defaultCharset()));
		}
		return sRet;
	}
}
