/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ClosingThread.java
 *
 */

package com.gensym.core;

import com.gensym.message.Trace;

public class ExitThread extends Thread {

  public static final long defaultWait = 1000;
  public static final int defaultExitCode = 0;

  private long wait;
  private int exitCode;

  public ExitThread() {
    this (defaultWait, defaultExitCode);
  }

  public ExitThread(long wait, int exitCode) {
    this.wait = wait;
    this.exitCode = exitCode;
  }

  @Override
  public void run() {
    try {
      sleep(wait);
    } catch (InterruptedException ie) {
      Trace.exception(ie);
    } finally {
      System.exit(exitCode);
    }
  }

  public static void exit() {
    ExitThread t = new ExitThread();
    t.start();
    try {
		t.join();
	} catch (InterruptedException e) {
		Trace.exception(e);
	}
  }

  public static void exit(long wait, int exitCode) {
    ExitThread t = new ExitThread(wait, exitCode);
    t.start();
    try {
		t.join();
	} catch (InterruptedException e) {
		Trace.exception(e);
	}
  }
}
