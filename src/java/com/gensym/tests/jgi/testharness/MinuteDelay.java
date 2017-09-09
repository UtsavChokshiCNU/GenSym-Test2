/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 MinuteDelay.java
 *
 *
 *   Modifications:
 *
 */


package com.gensym.tests.jgi.testharness;

public class MinuteDelay
{
    public MinuteDelay()
    {
    }

    static public void main(String args[])
    {
      try{
       Thread.sleep(60000);
      }catch (Exception e){System.out.println(e.toString());}
    }
}
