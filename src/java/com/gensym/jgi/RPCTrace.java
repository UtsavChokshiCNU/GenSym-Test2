/**
 * This class is to trace RPC performace. When traceOn is set on, tracing RPC
 * is kicked off in G2Gateway. Users can make stardand RPCTrace reports including
 * a general report and a summary report. The general report presents full info
 * per each RPC call with its name, arguments, duration, and stack traces
 * (if stackOn is on). The summary report presents summary info of RPC calls with name,
 * total duration, average duration and number of calls in order of decresed
 * the total duration. Also, users can empty all history data in RPC data storage by
 * call emptyDataStorage method.
 * RPCTraceCommands provides full access controls to the class
 *
 * @author FY
 * @undocumented
 */

package com.gensym.jgi;

import java.util.Vector;
import java.io.*;

import com.gensym.util.Symbol;
import com.gensym.core.DebugUtil;
import com.gensym.jgi.G2Gateway;

public class RPCTrace {
  private static boolean traceOn;
  private static boolean reportOn;
  private static boolean stackOn;
  private static boolean emptyDataOn;
  private static Vector RPCTraceData = new Vector();

  public RPCTrace() {
  }

  public static void emptyDataStorage() {
    RPCTraceData.clear();
  }

  public static void setTraceOn(boolean on) {
    traceOn = on;
    G2Gateway.rpcTraceOn = on;
  }

  public static void setStackOn(boolean on) {
    stackOn = on;
  }

  public static void setEmptyDataOn(boolean on) {
    emptyDataOn = on;
  }

  public static void setReportOn(boolean on) {
    reportOn = on;
  }

  public static boolean isTraceOn() {
    return traceOn;
  }

  public static boolean isStackOn() {
    return stackOn;
  }

  public static boolean isEmptyDataOn() {
    return emptyDataOn;
  }

  public static boolean isReportOn() {
    return reportOn;
  }

  public static RPCTraceEntry getRPCEntryByIndex(int index) throws Exception {
    if (index > RPCTraceData.size())
      throw new Exception("The index is out of the range of stored trace data.");

    return  (RPCTraceEntry) RPCTraceData.get(index);
  }

  public static void writeReportToBuffer(BufferedWriter buff) throws IOException {
    if (RPCTraceData.isEmpty()){
    	return;
    }

    //Write summary report
    writeOutSummaryReport(buff);
    //Write general report
    writeOutGeneralReport(buff, true);

    buff.close();

  }


  public static synchronized void addRPCTraceData(Symbol pName, Object[] args, long duration) {
    Exception ex = null;
    if (stackOn) {
      ex = new Exception();
      ex.fillInStackTrace();
    }

    RPCTraceEntry entry = new RPCTraceEntry(pName, args, duration, ex);
    RPCTraceData.add(entry);
  }

  public static Vector getRPCProcedureByName(String pName) {
    int i;
    Vector aVec = new Vector();

    for (i=0; i < RPCTraceData.size(); i++) {
      if (pName.equals(((RPCTraceEntry) RPCTraceData.get(i)).getProcedureName().toString()))
        aVec.add(RPCTraceData.get(i));

    }

    return aVec;
  }

  public static Vector getRPCProcedureWithMaxDuration() {
    long max = 0;
    Vector aVec = new Vector();
    RPCTraceEntry entry;

    if (RPCTraceData.isEmpty()) {
    	return null;
    }
    for (int i =0; i < RPCTraceData.size(); i++) {
      long dTime = ((RPCTraceEntry) RPCTraceData.get(i)).getDuration();
      if (dTime > max)
        max = dTime;
    }

    //Get procedures with max ones
    for (int j =0; j < RPCTraceData.size(); j++) {
      if (max == ((RPCTraceEntry) RPCTraceData.get(j)).getDuration())
        aVec.add(RPCTraceData.get(j));
    }

    return aVec;

  }

  public static Vector getRPCProcedureWithMinDuration() {
    long min = 1000000;
    Vector aVec = new Vector();

    if (RPCTraceData.isEmpty()){
    	return null;
    }
    for (int i =0; i < RPCTraceData.size(); i++) {
      long dTime = ((RPCTraceEntry) RPCTraceData.get(i)).getDuration();
      if (dTime < min)
        min = dTime;
    }

    //Get procedures with max ones
    for (int j =0; j < RPCTraceData.size(); j++) {
      if (min == ((RPCTraceEntry) RPCTraceData.get(j)).getDuration())
        aVec.add(RPCTraceData.get(j));
    }

    return aVec;
  }

  public static long getRPCAverageDuration() {
    long sum=0;
    int dataSize = 0;

    dataSize = RPCTraceData.size();
    if (dataSize == 0){
    	return 0;
    }

    for (int i = 0; i < dataSize; i++) {
      sum += ((RPCTraceEntry) RPCTraceData.get(i)).getDuration();
    }

    return (sum/dataSize);
  }

  public Vector getAllRPCTraceEntry() {
    return ((Vector) RPCTraceData.clone());
  }



  public static void writeOutGeneralReport(BufferedWriter buff, boolean includeStack) throws IOException {
    RPCTraceEntry entry;

    buff.write("****** RPC GENERAL REPORT ******");
    buff.newLine();
    for (int i=0; i < RPCTraceData.size(); i++) {
      entry = (RPCTraceEntry) RPCTraceData.get(i);
      buff.write("PRC procedure name: ");
      String pName = entry.getProcedureName().toString();
      buff.write(pName);
      buff.newLine();

      buff.write(pName + " arguments: ");
      buff.newLine();
      Object pArg = entry.getProcedureArgs();
      buff.write("\t" + DebugUtil.printArray(pArg));
      buff.newLine();

      buff.write(pName + " duration (in millisecond): ");
      long dTime =  entry.getDuration();
      buff.write(dTime + "");
      buff.newLine();

      if (includeStack && stackOn) {
        buff.write(pName + " stacktrace:");
        buff.newLine();
        Exception ex = entry.getStackTrace();
        if (ex != null)
          ex.printStackTrace(new PrintWriter(buff));
        buff.newLine();
      }

      buff.write("-- End of " + pName);
      buff.newLine();
      buff.newLine();
    }

    buff.write("--- End of General Report ---");
    buff.newLine();
    buff.newLine();
    buff.flush();

  }

  public static void writeOutSummaryReport(BufferedWriter buff) throws IOException {
    Vector aVec = sortSummaryVector(makeSummaryVector());

    buff.write("****** SUMMARY REPORT ******");
    buff.newLine();
    RPCSumRptEntry arr;
    for (int i=0; i < aVec.size(); i++) {
      arr = (RPCSumRptEntry) aVec.get(i);

      //Get procedure name
      buff.write("Procedure Name: ");
      String pName = arr.getName().toString();
      buff.write(pName + "; ");
      //buff.newLine();

      //Get total
      buff.write("Total: ");
      buff.write(arr.getTotal() + "; ");
      //buff.newLine();

      //Get average
      buff.write("Average: ");
      buff.write(arr.getAverage() + "; ");
      //buff.newLine();

      //Get counts
      buff.write("Number of calls: ");
      buff.write(arr.getCalls() + "");
      buff.newLine();

      buff.write("-- End of " + pName);
      buff.newLine();
      buff.newLine();
     }

     buff.write("--- End of Summary Report ---");
     buff.newLine();
     buff.newLine();
     buff.flush();

  }

  private static Vector makeSummaryVector() {
    Vector summaryRecords = new Vector();
    Vector data = (Vector) RPCTraceData.clone();


    if (RPCTraceData.isEmpty()){
    	return null;
    }

    //Make a summary record
    int[] removeIndexs = new int[data.size()];
    int index = 0;
    long sum = 0;
    for (int i=0; i < data.size();) {
        index = 0;
        sum = 0;
        for (int j=0; j < data.size(); j++) {
          if ((((RPCTraceEntry) data.get(i)).getProcedureName()).equals(((RPCTraceEntry) data.get(j)).getProcedureName())) {
            sum += ((RPCTraceEntry) data.get(j)).getDuration();
            removeIndexs[index++] = j;
          }
        }

        //Set RPCSumRptEntry for summary report
        RPCSumRptEntry entry = new RPCSumRptEntry(((RPCTraceEntry) data.get(i)).getProcedureName(),
                                          sum, sum/index, index);
        summaryRecords.add(entry);

        //Remove done items from vectors
          for (int k=0; k < index; k++) {

            data.remove(removeIndexs[k]);
            //The index of vector is shifted to left after an item is removed
            for (int g=k+1; g < index; g++) {
              removeIndexs[g] = removeIndexs[g] - 1;
           }
          }

        //Leave the loop if none is in the vector
        if (data.isEmpty()) 
        	break;
    }

    return summaryRecords;
  }

  private static Vector sortSummaryVector(Vector sVec) {
    Vector sortedSummaryVec = new Vector();
    Vector tempVec = (Vector) sVec.clone();

    if (sVec.isEmpty()) 
    	return null;

    boolean hasRecord = true;
    long max = 0;
    int index = 0;
    do {
      index = 0;
      max = 0;
      for (int i = 0; i < tempVec.size(); i++) {
        RPCSumRptEntry entry = (RPCSumRptEntry) tempVec.get(i);
        long aValue = entry.getTotal();
        if (aValue >= max) {
          max = aValue;
          index = i;
        }
      }
      //Get the oe with max duratioin and set it into sortedSummaryVec;
      //remove the record from tempVec and check its size
      sortedSummaryVec.add(tempVec.get(index));
      tempVec.remove(index);
      if (tempVec.isEmpty()) 
    	  hasRecord = false;
    } while (hasRecord);

    return  sortedSummaryVec;
  }

}