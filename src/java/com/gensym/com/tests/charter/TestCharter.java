package com.gensym.com.tests.charter;

import com.gensym.com.beans.ccocxlib.*;

import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.Variant;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.ActiveXTraceLevels;
import com.gensym.com.ActiveXException;
import com.gensym.com.NativeMethodBroker;
import com.gensym.com.ActiveXTraceTool;

import java.lang.InterruptedException;

import java.awt.Frame;
import java.awt.Color;
import java.awt.event.*;

import java.util.Date;

public class TestCharter implements WindowListener, ActiveXTraceLevels,
                                     ActiveXRuntimeConstants
{

    public static void main(String[] args) {
      Frame f =  new Frame();
      
      try {
/*
        ActiveXTraceTool tool = new ActiveXTraceTool();        
        tool.setAxTraceLevel((short) 40);
        tool.setLogToStdout(true);
*/
        // Create a new sheet
        CcocxCcocxctrl charter = new CcocxCcocxctrl();
        

        // Add the sheet to the window 
        f.add(charter);
        f.resize(750,450);
        f.addWindowListener(new TestCharter());
   
        // Show the window containing the sheet
        
        f.show();
        /*
        charter.setAxBackColor(Color.white);
        charter.AboutBox();
        */

        //charter.setAxCenterColor(Color.white);

        charter.setAxShowCaption(true);

        charter.setAxCaption("Level of Sewage Tank");

        charter.setAxUnits("mm");

        charter.setAxShowLCL(false);
        charter.setAxShowUCL(true);

        charter.setAxShowTarget(true);
        charter.setAxTarget(50.0);

        


        int graphType = charter.getAxGraphType();
        System.out.println("Graph type found = " + graphType);

        /*
        charter.setAxGraphType(ConstantsGraphType.CC_RUN);
        
        charter.setAxGraphType(ConstantsGraphType.CC_RANGE);
        charter.setAxGraphType(ConstantsGraphType.CC_STD_DEV);
        charter.setAxGraphType(ConstantsGraphType.CC_INDIVIDUALS);
        charter.setAxGraphType(ConstantsGraphType.CC_MOVING_RANGE);

        graphType = charter.getAxGraphType();
        System.out.println("Graph type found = " + graphType);
        */

        charter.setAxRealtime(true);
        
        charter.setAxAppearance(0);
        double lastValue = 50.0;
        short index;
        long startTime, endTime, diff;
        double average, persecond;
        charter.setAxGraphType(ConstantsGraphType.CC_STD_DEV);
        while (true) {
         
          startTime = System.currentTimeMillis();
          for (int i = 0; i < 1000; i ++) {  
            charter.setAxGraphType(ConstantsGraphType.CC_STD_DEV);  
            //index = charter.CCAddValue((Math.random() - 0.5) * 10 + lastValue);
            //charter.CCSetDate(index,new Date());
          }
          endTime = System.currentTimeMillis();
          diff = (endTime - startTime);
          average = (diff / 1000.0);
          persecond = (1000 / average);

          System.out.println("\n\nTime to make 1000 basic method calls = " + diff);
          System.out.println("Average = " + average);
          System.out.println("PerSecond = " + persecond);


          startTime = System.currentTimeMillis();
          for (int i = 0; i < 10; i ++) {  
            index = charter.CCAddValue((Math.random() - 0.5) * 10 + lastValue);
            charter.CCSetDate(index,new Date());
          }
          endTime = System.currentTimeMillis();
          diff = (endTime - startTime);
          average = (diff / 10.0);
          persecond = (1000 / average);

          System.out.println("\n\nTime to set 10 data points = " + diff);
          System.out.println("Average = " + average);
          System.out.println("PerSecond = " + persecond);

          /*
          charter.setAxGraphType(ConstantsGraphType.CC_STD_DEV);
          for (int i = 0; i < 50; i ++) {
            index = charter.CCAddValue((Math.random() - 0.5) * 10 + lastValue);
            //charter.setAxDate(index,new Date());
          }
          */
        }
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

