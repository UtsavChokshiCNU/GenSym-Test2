/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 CommandKey.java
 *
 */

package com.gensym.ui;


/**
 *  This convenience class can be used to refer to a particular command-key tuple
 *  as one object.
 */
public class CommandKey implements java.io.Serializable
{

  private static final long serialVersionUID = 1L;
  private Command command;
  private String key;

  // This otherwise unused no-arg constructor required by JRMI
  public CommandKey () {}

  public CommandKey (Command command, String key) {
    this.command = command;
    this.key = key;
  }

  public Command getCommand() { return command; }

  public String getKey() { return key; }

  public void setCommand(Command command) { this.command = command; }

  public void setKey(String key) { this.key = key; }

  @Override
  public int hashCode() { return command.hashCode()^key.hashCode(); }

  @Override
  public boolean equals(Object that) {
    if (that instanceof CommandKey)
      return ((command.equals(((CommandKey)that).command)) && (key.equals(((CommandKey)that).key)));
    else
      return false;
  }

  @Override
  public String toString() { return "["+super.toString()+", command="+command+", key="+key+"]"; }
  
}
