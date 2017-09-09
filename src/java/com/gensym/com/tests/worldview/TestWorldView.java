package com.gensym.com.tests.worldview;

import com.gensym.com.beans.worldviewlib.*;

import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.Variant;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.ActiveXTraceLevels;
import com.gensym.com.ActiveXException;
import com.gensym.com.NativeMethodBroker;

import java.lang.InterruptedException;

import java.awt.Frame;
import java.awt.Color;
import java.awt.event.*;

import com.gensym.com.ActiveXTraceTool;

import java.util.Date;

public class TestWorldView implements WindowListener, ActiveXTraceLevels,
                                     ActiveXRuntimeConstants
{

    public static void main(String[] args) {
      Frame f =  new Frame();
      
      try {

        /*
        ActiveXTraceTool tool =  new ActiveXTraceTool();
        tool.setAxTraceLevel((short)40);
        tool.setLogToStdout(true);
        */

        // Create a new sheet
        WorldviewWorldviewctrl world =  new WorldviewWorldviewctrl();
        

        // Add the sheet to the window 
        f.add(world);
        f.resize(750,450);
        f.addWindowListener(new TestWorldView());
   
        // Show the window containing the sheet
        
        f.show();

        System.out.println("Before setting world");
        //world.setAxWorld("D:\\vremlov2.wrl");
        world.setAxWorld("D:\\rucube.wrl");
        System.out.println("World = " +world.getAxWorld());
        world.AboutBox();



      }
    catch (Exception e) {
      e.printStackTrace();
      System.out.println("Failure : " + e);
    }
	}

  @Override
  public void windowOpened(WindowEvent e) {
  }

  @Override
  public void windowClosing(WindowEvent e) {
    System.exit(0);
  }

  @Override
  public  void windowClosed(WindowEvent e) {
    System.exit(0);
  }

 @Override
 public void windowIconified(WindowEvent e) {
 }

 @Override
 public  void windowDeiconified(WindowEvent e) {
 }


 @Override
 public  void windowActivated(WindowEvent e) {
 }

 @Override
 public void windowDeactivated(WindowEvent e) {
 }


}

