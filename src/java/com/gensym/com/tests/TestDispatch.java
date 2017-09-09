package com.gensym.com.tests;

import com.gensym.com.beans.excel12.ExcelChart;
import com.gensym.com.beans.excel12.ExcelApplication;
import com.gensym.com.beans.excel12.Sheets;
import com.gensym.com.beans.excel12.Worksheet;
import com.gensym.com.beans.excel12.Range;
import com.gensym.com.beans.excel12.XlWindowState;

import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.Variant;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.NativeMethodBroker;
import com.gensym.com.ActiveXTraceLevels;

import java.awt.*;
import java.awt.event.*;

public class TestDispatch implements WindowListener, ActiveXTraceLevels,
                                     ActiveXRuntimeConstants
{

	public static void main(String[] args) {
		Frame f =  new Frame();

    try {
    ExcelChart chart = new ExcelChart();
		f.add(chart);
    f.resize(400,400);
    f.addWindowListener(new TestDispatch());
		f.show();

    System.out.println("Chart = " + chart + "\n\n");
   
    NativeMethodBroker.setTraceLevel(AX_DATA_DUMPS);

    System.out.println("GETTING APPLICATION");
    ExcelApplication app = chart.getAxApplication();
    System.out.println("Application = " + app + "\n\n");

    System.out.println("MINIMIZING THE APPLICATION");
    app.setAxWindowState(XlWindowState.XL_MINIMIZED);
    if (app.getAxWindowState() == XlWindowState.XL_MINIMIZED)
      System.out.println("Application minimized\n\n");
    else System.out.println("Application failed to minimize\n\n");


    System.out.println("GETTING WORKSHEETS");
    Sheets work = app.getAxWorksheets();
    System.out.println("Worksheets = " + work + "\n\n");
    
    System.out.println("GET 0x57f");
    System.out.println(chart.getAxProtectGoalSeek() + "\n\n");

    System.out.println("GET SHEET");
    ActiveXDispatchable unknown =
      work.getAxItem(new com.gensym.com.Variant(1));
    System.out.println("unknown = " + unknown);
    Worksheet sheet 
      = new Worksheet(unknown);
    System.out.println(sheet + "\n\n");

    System.out.println("GET CELLS");
    Range cells = sheet.getAxCells();
    System.out.println(cells + "\n\n");


    System.out.println("GET A PARTICULAR CELL");
    Variant variant = cells.getAxItem(new Variant(2), new Variant(2));
    Range cell = new Range(variant.getActiveXDispatchableValue());
    System.out.println(cell + "\n\n");

   
    System.out.println("GET VALUE OF A CELL");
    Variant value = cell.getAxValue();
    System.out.println(value + "\n\n");

    System.out.println("CALLING AddRef");
    sheet.AddRef();
    
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

