package com.gensym.G2SNMP;

import com.adventnet.snmp.snmp2.SnmpPDU;
import com.adventnet.snmp.snmp2.SnmpAPI;
import com.adventnet.snmp.snmp2.UDPProtocolOptions;
import java.io.PrintWriter;
import java.nio.charset.Charset;
import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStreamWriter;

import com.gensym.G2SNMP.util.DNSLookup;


/**
   This object once instantiated logs traps and transactions.
   The log formats are described in the bridge specification (Exhibit A).
   All methods are intentionally static to be called as LogFile.logXXX().
   In the case the log does not exist, the methods return normally.
*/
public class LogFile {
    private int MAX_LOG_LINES;
    private int todayFileNo;
    private int loggedLines;
    private String fileName;
    /**
       This is a reference to the LogFile object. It is null when
       logging is disabled.
     */
    private static LogFile theLog = null;
    private static final String DEFAULT_FILE_NAME = "straps";
    private String todayFileId;

    /**
       This is a constructor of LogFile class.
       @roseuid 365D57270185
     */
    public LogFile(final String fileName, final String title, final int maxLogLines) {
        String logFileName = fileName;
    	if (logFileName == null)
    		logFileName = DEFAULT_FILE_NAME;
        JsnmpBridge.debugOut("LogFile.LogFile ('" + logFileName + "', " + maxLogLines + ").");
        synchronized (LogFile.class) {
			theLog = this;
		}
		this.fileName = logFileName;
        MAX_LOG_LINES = maxLogLines;
        todayFileId = getDayId();
        todayFileNo = firstFreeFileNo(0);
        loggedLines = 0;
        logString(title + " log started at " + currentTimeStamp());
    }

    /**
       This method logs an outgoing SNMP transaction.
       @roseuid 365D57A40080
     */
    public static synchronized void logTransaction(int type, String node, boolean success) {
        JsnmpBridge.debugOut("LogFile.logTransaction (" + type + ", " + node + ", " + success  + ").");
        String transactionType;
        switch ((byte)type){
        case SnmpAPI.GET_REQ_MSG: transactionType = "GET"; break;
        case SnmpAPI.GETNEXT_REQ_MSG: transactionType = "GETNEXT"; break;
        case SnmpAPI.SET_REQ_MSG: transactionType = "SET"; break;
        case SnmpAPI.TRP_REQ_MSG: transactionType = "SENDTRAP"; break;
        case SnmpAPI.GETBULK_REQ_MSG: transactionType = "GETBULK"; break;
        case SnmpAPI.INFORM_REQ_MSG: transactionType = "INFORM"; break;
        case SnmpAPI.TRP2_REQ_MSG: transactionType = "SENDV2TRAP"; break;
        default: transactionType = "TRANSACTION";
        }
        if (theLog != null)
            theLog.logMessage(transactionType, node + " " +
			(success?"SENT":"FAILED"));
    }

    /**
       This method logs an incoming trap.
       @roseuid 365A948801CE
	 */
	public static synchronized void logTrap(SnmpPDU pdu) {
          //APIv4
          UDPProtocolOptions opt = (UDPProtocolOptions)pdu.getProtocolOptions();

        JsnmpBridge.debugOut("LogFile.logTrap (" + pdu + ").");
        if (theLog != null)
            theLog.logMessage(
                "TRAP",
//                pdu.getAgentAddress() + " " +
//TLEE SNMPV2/V3 doesn't have an agentaddress, changed to use remotehost.
				//DNSLookup.inetAddrToString( pdu.getAgentAddress().getAddress() ) + " " +
				//APIv3->pdu.getRemoteHost() + " " +
				opt.getRemoteHost() + " " +
                pdu.getEnterprise() + " " +
                pdu.getTrapType() + " " +
                pdu.getSpecificType()
            );     
    }

    /**
	   This method logs a tagged message.
       @roseuid 3668150E02AA
     */
    public static synchronized void logMessage(String tag, String str) {
      if (theLog != null) {
        theLog.logString(tag + " " + currentTimeStamp() + " " + str);
      }
    }

    /**
       @roseuid 36777D520006
     */
    synchronized void logString(String str) {
        loggedLines++;
        String thisDayId = getDayId();
        if (!thisDayId.equals(todayFileId)) {
            todayFileId = thisDayId;
            todayFileNo = firstFreeFileNo(0);
            loggedLines = 1;
        }
        else if (loggedLines > MAX_LOG_LINES) {
            todayFileNo = firstFreeFileNo(todayFileNo + 1);
            loggedLines = 1;
        }
        String fileTitle = fullFileTitle(todayFileNo);
        try {
            PrintWriter pWriter = new PrintWriter(
            		new OutputStreamWriter(
            				new FileOutputStream(fileTitle, true /*append*/), Charset.defaultCharset())
            		, true /*autoflush*/);
            pWriter.println("" + loggedLines + " " + str);
            pWriter.close();
        }
        catch (java.io.IOException e) {
            System.err.println("Warning: Log File writing failed.");
            JsnmpBridge.debugOut(e.toString());
        }
    }

    /**
       @roseuid 36777D530198
     */
    static String getDayId() {
        return new java.text.SimpleDateFormat("yyMMdd").
            format(new java.util.Date());
    }

    /**
       @roseuid 36777D530238
     */
    static String currentTimeStamp() {
        return new java.text.SimpleDateFormat("yy/MM/dd HH:mm:ss").
            format(new java.util.Date());
    }

    /**
       @roseuid 36777D5302D9
     */
    String fullFileTitle(int fileNo) {
        return fileName + "_" + todayFileId + "_" + fileNo + ".log";
    }

    /**
       @roseuid 36777D540059
     */
    int firstFreeFileNo(final int startFrom) {
    	int startIndex = startFrom;
        while (new File(fullFileTitle(startIndex)).exists())
        	startIndex++;
        return startIndex;
    }
}