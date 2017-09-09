package com.gensym.G2SNMP.trapd;

import java.io.*;
import java.nio.charset.Charset;

import com.adventnet.snmp.snmp2.SnmpPDU;
import com.adventnet.snmp.snmp2.SnmpAPI;
import com.adventnet.snmp.snmp2.UDPProtocolOptions;
import java.util.StringTokenizer;
import com.gensym.G2SNMP.JsnmpBridge;
import com.gensym.G2SNMP.LogFile;
import com.gensym.G2SNMP.rpc.*;

/**
   This object implements a filter that
   holds trap patterns to be rejected by the bridge.
*/
class TrapFilter {
    public static final String IGNORE_STR = "IGNORE";
    public static final String LOGONLY_STR = "LOGONLY";
    public static final String FORMAT_STR = "FORMAT";
    
    private SVector patterns;

    /**
       The constructor sets up the filter and fills it
       with initial data imported from the .ppd file.
       @roseuid 365ACFC30308
     */
    public TrapFilter(String ppdFileName, int capacity) {
        patterns = new SVector(capacity);
        parsePpdFile(ppdFileName);
    }

    /**
       This method determines whether the given PDU should
       be forwarded to Integrity (true), or not (false).
       @roseuid 365AD0A8005E
     */
    protected boolean shouldForward(SnmpPDU pdu) {
        //APIv4
        UDPProtocolOptions opt = (UDPProtocolOptions)pdu.getProtocolOptions();

        JsnmpBridge.debugOut("TrapFilter.shouldForward()");
        switch (pdu.getCommand()){
        case SnmpAPI.TRP_REQ_MSG:
            LogFile.logTrap(pdu);
            try{
                return !(patterns.isContained(new TrapPattern(pdu.getEnterprise().toString(),
                         pdu.getTrapType(),
                         pdu.getSpecificType())));
            }catch(com.gensym.G2SNMP.rpc.TypeConversionException e){
                JsnmpBridge.debugOut(e.getMessage());
                return false;
            }
        case SnmpAPI.TRP2_REQ_MSG:
            //APIv3->LogFile.logMessage("SNMPv2 trap received", pdu.getAddress().getHostName());
            LogFile.logMessage ("SNMPv2 trap received", opt.getRemoteHost());
            LogFile.logTrap(pdu);            
            return true;
	case SnmpAPI.INFORM_REQ_MSG:
            //APIv3->LogFile.logMessage("SNMPv2 INFORM received", pdu.getAddress().getHostName());            
            LogFile.logMessage("SNMPv2 INFORM received", opt.getRemoteHost());            
            LogFile.logTrap(pdu);
	    return true;
        default:
            JsnmpBridge.debugOut("Did not receive a trap PDU: " + pdu.toString());
            return false;
        }
    }

    /**
       @roseuid 365AD1CB008F
     */
    public void registerTrap(String enterpriseId, int genericId, double specificId) throws com.gensym.G2SNMP.rpc.TypeConversionException {
        JsnmpBridge.debugOut("TrapFilter.registerTrap(" + enterpriseId + ", " + genericId + ", " + specificId + ")");
        patterns.addElement(new TrapPattern(enterpriseId, genericId, specificId));
        com.gensym.G2SNMP.LogFile.logMessage("FILTER", "trap ADDED and filtering turned ON for " + enterpriseId + " " + genericId + " " + java.lang.Math.round(specificId));
    }

    /**
       @roseuid 365AD1E803D0
     */
    public void deregisterTrap(String enterpriseId, int genericId, double specificId) throws com.gensym.G2SNMP.rpc.TypeConversionException {
        JsnmpBridge.debugOut("TrapFilter.deregisterTrap(" + enterpriseId + ", " + genericId + ", " + specificId + ")");
        patterns.removeElement(new TrapPattern(enterpriseId, genericId, specificId));
        com.gensym.G2SNMP.LogFile.logMessage("FILTER", "filtering turned OFF for " + enterpriseId + " " + genericId + " " + java.lang.Math.round(specificId));
    }

    /**
       @roseuid 366531470023
     */
    public void parsePpdFile(String ppdFileName) {

        if (ppdFileName == null) {
            System.err.println("Warning (trap filter) : No PPD file name specified. Starting with empty filter");
            return;
        }

        BufferedReader st = null;
        try {
            st = new BufferedReader(new InputStreamReader(new FileInputStream(ppdFileName), Charset.defaultCharset()));
        } catch (FileNotFoundException e) {
            System.err.println("Warning (trap filter): PPD file not found. Starting with empty filter");
            return;
        }

        String[] currentStr = new String[6];
        boolean formatStr = false;
        int i = 0;
        String theStr;
        long strNum = 0;
        try {
            while ((theStr = st.readLine()) != null) {
                strNum++;
                // skip empty string
                if (theStr.equals("")){
                    continue;
                }
                if (!formatStr) {
                    StringTokenizer str = new StringTokenizer(theStr);
                    for (i = 0; (str.hasMoreTokens() && (i < 6)); i++){
                        currentStr[i] = str.nextToken();
                    }
                    if (currentStr[i - 1].equals(FORMAT_STR)) {
                        formatStr = true;
                    }
                    if (i < 5) { // less than 5 elements in string
                        System.err.println("Warning (trap filter): Less than 5 elements in line " + strNum + ". PPD file parsing terminated");
                        break;
                    }
                    if ((currentStr[0].equals(IGNORE_STR))||
                        (currentStr[0].equals(LOGONLY_STR))){
                        try {
                            registerTrap(
                                currentStr[1],
                                Integer.parseInt(currentStr[2]),
                                Integer.parseInt(currentStr[3]));
                        } catch (NumberFormatException e) {
                            System.err.println("Warning (trap filter): Wrong number format in PPD file. Line " + strNum + " ignored");
                        } catch(com.gensym.G2SNMP.rpc.TypeConversionException e){
                            System.err.println("Warning (trap filter): " + e.getMessage() + ". Line " + strNum + " ignored");
                        }
                    }
                } else {
                    formatStr = false;
                }
            }
            st.close();
        } catch (IOException e) {
            System.err.println("Warning (trap filter): I/O exception parsing PPD file. Line" + strNum);
            return;
        }
    }

}