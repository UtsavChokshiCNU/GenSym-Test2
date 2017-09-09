package com.gensym.com.tests;

import com.gensym.com.beans.excel12.ExcelSheet;
import com.gensym.com.beans.excel12.ExcelChart;
import com.gensym.com.beans.excel12.ChartGroup;
import com.gensym.com.beans.excel12.ExcelApplication;
import com.gensym.com.beans.excel12.Sheets;
import com.gensym.com.beans.excel12.Range;
import com.gensym.com.beans.excel12.Font;
import com.gensym.com.beans.excel12.XlWindowState;
import com.gensym.com.beans.excel12.XlChartType;
import com.gensym.com.beans.excel12.XlHAlign;

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

public class TestExcel implements WindowListener, ActiveXTraceLevels,
                                     ActiveXRuntimeConstants
{
    private static void setValueOfCell(ExcelApplication app,
                                         String range,
                                         String value) 
                          throws ActiveXException
    {
      Range chosen = app.getAxRange(new Variant(range));
      chosen.setAxValue(new Variant(value));
    }

    private static void setValueOfCell(ExcelApplication app,
                                         String range,
                                         int value) 
                          throws ActiveXException
    {
      Range chosen = app.getAxRange(new Variant(range));
      chosen.setAxValue(new Variant(value));
    }

    private static void centerRange(ExcelApplication app, 
                                    String range)
                                    throws ActiveXException
    {
      Range chosen = app.getAxRange(new Variant(range));
      chosen.setAxHorizontalAlignment(new Variant(XlHAlign.XL_H_ALIGN_CENTER));
    }

    private static void boldRange(ExcelApplication app, 
                                    String range)
                                    throws ActiveXException
    {
      Range chosen = app.getAxRange(new Variant(range));
      Font font = chosen.getAxFont();
      font.setAxBold(new Variant(true));
    }


    private static void select(ExcelApplication app, String range)
                          throws ActiveXException 
    {
      Range selected = app.getAxRange(new Variant(range));
      selected.Select();
    }


    private static void pause(Object o) {
        try {
          synchronized(o) {
            o.wait(2000);
          }
        }
        catch (InterruptedException e) 
        { }
    }

    public static void main(String[] args) {
      Frame f =  new Frame();
      
      try {

        // Create a new sheet
        ExcelSheet sheet = new ExcelSheet();
        sheet.setBackground(Color.lightGray);

        // Add the sheet to the window 
        f.add(sheet);
        f.resize(750,450);
        f.addWindowListener(new TestExcel());
   
        // Show the window containing the sheet
        
        f.show();

        // Get the application for this sheet
        ExcelApplication app = sheet.getAxApplication();

        // Mimimize the application
        app.setAxWindowState(XlWindowState.XL_MINIMIZED);
        
        // Establish bounds of the data, necessary for ExcelSheet because the 
        // view of the whole document given by Excel will depend upon the bounds
        // of the data in the spreadsheet
        sheet.setFrozen(true); // Freeze the display until bounds are established 
        centerRange(app, "A3:F4"); // Center all the cells in a range     
        boldRange(app, "A1");    // Bold the title
        setValueOfCell(app,"A1","Toys By Category");
        setValueOfCell(app,"F20"," ");
        sheet.setBackground(Color.white);
        sheet.setFrozen(false);  // UnFreeze causes a repaint
              
        // Add column and row headers to the sheet
        sheet.setFrozen(true); // Freeze the display while adding data
        setValueOfCell(app,"B3","Stuffed");
        setValueOfCell(app,"C3","Vehicles");
        setValueOfCell(app,"D3","Dolls");
        setValueOfCell(app,"E3","Computers");
        setValueOfCell(app,"F3","Other");
        setValueOfCell(app,"A4",1991);
        sheet.setFrozen(false); // UnFreeze causes a repaint


        // Add data to the sheet
        sheet.setFrozen(true); // Freeze the display while adding data
        setValueOfCell(app,"B4",15);
        setValueOfCell(app,"C4",10);
        setValueOfCell(app,"D4",20);
        setValueOfCell(app,"E4",20);
        setValueOfCell(app,"F4",20);
        sheet.setFrozen(false); // UnFreeze causes a repaint
        
        pause(sheet);

        // Select all the data
        select(app, "A3:F4");

        // Create a default chart for that data
        Sheets sheets = app.getAxCharts();
        sheets.Add();        
          
        ExcelChart chart = app.getAxActiveChart();  
        pause(sheet);
        chart.setAxHasDataTable(true);
        pause(sheet);

        chart.setAxChartType(XlChartType.XL3_D_PIE_EXPLODED);
        pause(sheet);
        chart.setAxRotation(new Variant(90));
        pause(sheet);
        chart.setAxRotation(new Variant(180));
        pause(sheet);
        chart.setAxRotation(new Variant(270));
        pause(sheet);
        chart.setAxRotation(new Variant(0));

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

