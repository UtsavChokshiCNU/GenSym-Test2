package com.gensym.com.tests.matlab;

import com.gensym.com.*;

import com.gensym.com.beans.mlapp.MatlabApplication;

import java.util.Vector;

public class TestMatlab
{ 
  public TestMatlab () 
  {
    /* Uncomment this for tracing */
/*
    ActiveXTraceTool tool =  new ActiveXTraceTool();
    tool.setAxTraceLevel((short)40);
    tool.setLogToStdout(true);
*/
        try {  

    Vector v1 
      = new Vector();
             
                                
    Vector v2
      = new Vector();

    MatlabApplication mlab = new MatlabApplication();
    System.out.println(mlab.Execute("tempo = [0:1:100]"));
   
    try {
      // Test 
      mlab.axInvoke(22,new Vector());
    }
    catch (ActiveXException f)
    {
      System.out.println("EXPECTED EXCEPTION:");
      System.out.println(f);
      System.out.flush();
      f.printStackTrace();
    }
    // Need to implement VT_SAFEARRAY and VT_PTR to support
    // array puts and gets.
    //mlab.PutFullMatrix("tempo", "global", v1, v2);
      
    /* Delete the application when we are finished with it */

      //System.out.println("Before quit");
      //mlab.Quit();
      //System.out.println("Before release");
      //mlab.Release();
      System.out.println("Before delete");
      mlab.delete();  
    }
    catch(ActiveXException e)
    {
      System.out.println("Oddly I got the exception here");
      e.printStackTrace();
    } 

  }

  public static void main(String[] args)
  {
      new TestMatlab();
  }

}

