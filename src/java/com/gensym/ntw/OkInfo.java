/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 OkInfo.java
 *
 */
package com.gensym.ntw;

import com.gensym.util.Sequence;
import com.gensym.util.Symbol;

class OkInfo {

  private String machineName;
  void setMachineName(String n) { machineName = n; }
  String getMachineName() { return machineName; }

  private String machineID;
  void setMachineID(String n) { machineID = n; }
  String getMachineID() { return machineID; }


  private int code1;
  void setCode1(int c) { code1 = c; }
  int getCode1() { return code1; }

  private int code2;
  void setCode2(int c) { code2 = c; }
  int getCode2() { return code2; }

  private int code3;
  void setCode3(int c) { code3 = c; }
  int getCode3() { return code3; }

  private int code4;
  void setCode4(int c) { code4 = c; }
  int getCode4() { return code4; }

  private int code5;
  void setCode5(int c) { code5 = c; }
  int getCode5() { return code5; }


  private boolean temporaryLicense;
  void setTemporaryLicense(boolean b) { temporaryLicense = b; }
  boolean getTemporaryLicense() { return temporaryLicense; }

  private Sequence from;
  void setFrom(Sequence f) { from = f; }
  Sequence getFrom() { return from; }

  private Sequence to;
  void setTo(Sequence t) { to = t; }
  Sequence getTo() { return to; }

  private Symbol level;
  void setLevel(Symbol l) { level = l; }
  Symbol getLevel() { return level; }

  /* Not counting processes in this version (if ever) */
  //private int processCount;
  //void setProcessCount(int n) { processCount = n; }
  //int getProcessCount() { return processCount; }


  static final Symbol DEVELOPMENT = Symbol.intern("DEVELOPMENT");

  OkInfo() {
    temporaryLicense = false;
    level = DEVELOPMENT;
    //    processCount = 1;
  }


  String describe() {
    String s = "OkInfo object";
    s += "\n  machine: " + machineName;
    s += "\n  id: \"" + machineID + "\"";
    s += "\n  codes: " + String.valueOf(code1) + " " + String.valueOf(code2) +
      " " + String.valueOf(code3) + " " + String.valueOf(code4) +
      " " + String.valueOf(code5);
    s += "\n  level: " + level;
    //s += "\n  process limit: " + String.valueOf(processCount);
    if ( temporaryLicense ) {
      s += "\n  from: " + String.valueOf(from.elementAt(0)) + " " + 
	from.elementAt(1) + " " + String.valueOf(from.elementAt(2));
      s += "\n    to: " + String.valueOf(to.elementAt(0)) + " " + 
	to.elementAt(1) + " " +	String.valueOf(to.elementAt(2));
    }
    return s;
  }


}
