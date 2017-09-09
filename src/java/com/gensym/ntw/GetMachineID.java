/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 GetMachineID.java
 *
 */
package com.gensym.ntw;

public class GetMachineID {

  public native String getLocalMachineID();

  public static void main (String[] args) {
    System.loadLibrary( "JgiInterface" );
    System.out.println("The id of this machine is \"" +
		       new GetMachineID().getLocalMachineID() +
		       "\"");
  }

}
