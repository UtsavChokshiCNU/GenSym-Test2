package com.gensym.G2SNMP;

import com.adventnet.snmp.snmp2.SnmpClient;
import com.gensym.G2SNMP.rpc.*;
import com.adventnet.snmp.snmp2.SnmpPDU;
import com.adventnet.snmp.snmp2.SnmpSession;
import com.gensym.jgi.G2Connection;
import com.gensym.jgi.G2Gateway;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.adventnet.snmp.snmp2.SnmpAPI;
import java.lang.reflect.Method;
//import com.gensym.G2SNMP;


/**
   This class is an abstract parent for TrapDaemon and Transactor.
*/
public abstract class Task implements SnmpClient, Default {
    protected SnmpSession snmpSession;
    protected G2Connection g2connection;
    protected SnmpAPI snmpApi;
    protected boolean finalized = false;
    public static final Symbol shutDownRPD = Symbol.intern("G2SNMP_SHUTDOWN");
//	public void TrapDaemon(SnmpAPI snmpApi, G2Connection g2connection, String ppdFileName, String mibNames) throws com.gensym.G2SNMP.TaskInitException {}
//	public void TrapDaemon(SnmpAPI snmpApi,G2Connection g2connection, String ppdFileName, String mibNames,
//					String engineID, String userName, int port, String authPassword,
//					String privPassword, String authProtocol) throws com.gensym.G2SNMP.TaskInitException {}



    /**
       This method is defined in AdventNet's interface SnmpClient.
       It uses the default JsnmpBridge method of printing a string.
       @roseuid 365EB5AE031F
     */
    public void debugPrint(String debugOutput) {
        JsnmpBridge.debugOut(debugOutput);
    }

//	public Task () {
//	}

    /**
       This is a constructor of Tasks that just initializes fields.
       @roseuid 366BE90F0229
     */
    public Task(SnmpAPI snmpApi, G2Connection g2connection) throws TaskInitException {
        JsnmpBridge.debugOut("Task.Task (api, g2con).");
        this.snmpApi = snmpApi;
        this.g2connection = g2connection;
        snmpSession = new SnmpSession(snmpApi);
        snmpSession.addSnmpClient(this);
        snmpSession.setAutoInformResponse(true);
    }

    /**
       This is a destructor of Tasks. Unfortunately it can (sic!) be called
       more than once (by garbage collector and/or explicitly). That is why
       I do need to check whether it was already called as SnmpSession does
       not like to be closed more than once.
       @roseuid 366BE90F0229
     */
    protected void finalize() {
        if (!finalized) {
            finalized = true;
            snmpSession.close();
        }
    }

    /**
       This method is a generic sender of messages to G2 via
       the G2SNMP_RECEIVE_MESSAGE RPC defined in G2Procedures.
       The method's parameters were mapped from the RPC's signature.
     */
    public void sendMessage(String tag, String nodeName, String msg, int errorCode) {
        JsnmpBridge.debugOut("Task.sendMessage (" + msg + ")");
        if (g2connection != null) {
            Object[] parameters = new Object[4];
            parameters[0] = tag;
            parameters[1] = nodeName;
            parameters[2] = msg;
            parameters[3] = errorCode;
            g2connection.startRPC(com.gensym.G2SNMP.rpc.G2Procedures.ReceiveMessage, parameters);
        }
    }

    public void shutDown() {
        JsnmpBridge.debugOut("Task.shutDown()");
        g2connection.closeConnection();
        JsnmpBridge.stateOut("A connected G2 asked to shut down.");
        System.exit (0);
    }


    /**
       This method registers just one RPC common for all Tasks.
       So, every Task subclass should use super(g2connection).
     */
    public void registerRPCs(G2Connection g2connection) throws com.gensym.G2SNMP.TaskInitException {
        Class theClass = this.getClass();
        try{
            Method shutDownMethod =
                theClass.getMethod("shutDown", new Class[0]);
            g2connection.registerJavaMethod(this, shutDownMethod, shutDownRPD, false);
        } catch (Exception e) {
            throw new com.gensym.G2SNMP.TaskInitException(e.getMessage());
        }
    }

}