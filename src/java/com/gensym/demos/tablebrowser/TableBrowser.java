package com.gensym.demos.tablebrowser;

import com.gensym.demos.tablebrowser.excel.Worksheet;
import com.gensym.demos.tablebrowser.excel.Chart;
import com.gensym.demos.tablebrowser.excel.ChartGroup;
import com.gensym.demos.tablebrowser.excel.ChartTitle;
import com.gensym.demos.tablebrowser.excel.Characters;
import com.gensym.demos.tablebrowser.excel.Application;
import com.gensym.demos.tablebrowser.excel.Sheets;
import com.gensym.demos.tablebrowser.excel.Range;
import com.gensym.demos.tablebrowser.excel.Font;
import com.gensym.demos.tablebrowser.excel.XlWindowState;
import com.gensym.demos.tablebrowser.excel.XlChartType;
import com.gensym.demos.tablebrowser.excel.XlHAlign;
import com.gensym.demos.tablebrowser.office.Assistant;

import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.Variant;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.ActiveXTraceLevels;
import com.gensym.com.ActiveXException;
import com.gensym.com.NativeMethodBroker;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.Frame;
import java.awt.Color;
import java.awt.Button;
import java.awt.Panel;

import java.lang.InterruptedException;

import javax.swing.JPanel;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JFrame;
import javax.swing.JComboBox;


public class TableBrowser extends JPanel 
                        implements WindowListener 
{
    public Worksheet sheet;
    public Chart chart;
    public Application app;

    private JPanel choices;
    private JButton viewChart;
    private JButton back;
    private JButton print;
    private JLabel label;
    private JComboBox combobox;

    private String tableName;
    private String[] columnNames;
    private String[] rowNames;
    private int[][] data;
    private int numberOfColumns;
    private int numberOfRows;
    private int numberOfDataRows;
    private int numberOfDataColumns;
    private int maxLengthOfColumnNames;
    private String tableExtrema;
    private String selectionRange;
    private Range selection;
    private int selectedIndex;
    private ActionListener actionListener;

    private static final String defaultTableName 
      = "Percentage Toys Sold By Category";
    private static final String[] defaultColumnNames 
      = {"Dolls", "Vehicles", "Computer", "Sports", "Other"};
    private static final String[] defaultRowNames
      = {"1991", "1993", "1995"};
   
    private static final int defaultData[][] 
      = {{ 20, 15, 15, 10, 40},
         { 20, 15, 20, 15, 30},
         { 15, 20, 20, 10 ,35}};

    private static final String[] alphabet = 
    { "A", "B", "C", "D", "E", "F", "G", "H",
      "I", "J", "K", "L", "M", "N", "O", "P",
      "Q", "R", "S", "T", "U", "V", "W", "X",
      "Y", "Z" };

    private static final short MINIMUM_NUMBER_OF_ROWS = 20;
    private static final short MINIMUM_NUMBER_OF_COLUMNS = 5;
    private static final String defaultTableExtrema = "F22";
    private static final String defaultTitleLocation = "A1";


    public TableBrowser() 
    {
      this(defaultTableName, 
           defaultColumnNames,
           defaultRowNames,
           defaultData);
    }

    public TableBrowser(String tableName,
                        String[] columnNames,
                        String[] rowNames,
                        int[][] data) 
    {
      this.tableName = tableName;
      this.columnNames = columnNames;
      this.rowNames = rowNames;
      this.data = data;

      numberOfDataRows = rowNames.length;
      numberOfDataColumns = columnNames.length;
      numberOfRows = ((numberOfDataRows + 2) < MINIMUM_NUMBER_OF_ROWS) ?
                     MINIMUM_NUMBER_OF_ROWS:
                     (numberOfDataRows  + 2);
      numberOfColumns = ((numberOfDataColumns + 2) < MINIMUM_NUMBER_OF_COLUMNS) ?
                         MINIMUM_NUMBER_OF_COLUMNS :
                         (numberOfDataColumns + 2);
      
      maxLengthOfColumnNames = 0;
      for (int i = 0; i < numberOfDataColumns; i++)
      { 
         int length = columnNames[i].length();
         if (length > maxLengthOfColumnNames)
            maxLengthOfColumnNames = length;
      }
                                 
      setLayout(new BorderLayout());
      sheet = new Worksheet();

      sheet.setSize(new Dimension(maxLengthOfColumnNames * 
                                  numberOfColumns * 10,
                                  numberOfRows * 25));
      
      add(sheet,"Center");
      sheet.setBackground(Color.lightGray);

      choices = new JPanel();
      choices.setBackground(Color.lightGray);

      actionListener = new TableBrowserActionListener();

      label = new JLabel("Select row:");
      label.setEnabled(false);

      combobox = new JComboBox();
      giveRowChoices();
      combobox.addActionListener(actionListener);      
      combobox.setEditable(false);
      combobox.setEnabled(false);

      back = new JButton("<< Back");
      back.addActionListener(actionListener);
      back.setEnabled(false);
      
      
      print = new JButton("Print");
      print.addActionListener(actionListener);
      print.setEnabled(false);
      
      viewChart = new JButton("View Chart");
      viewChart.addActionListener(actionListener);
      viewChart.setEnabled(false);

      choices.add(back);
      choices.add(print);
      choices.add(viewChart);      
      choices.add(label);
      choices.add(combobox);
      
      add(choices, "South");

    }

    public void activateComponents() 
         throws ActiveXException 
    {      
      app = sheet.getAxApplication();
      app.setAxWindowState(XlWindowState.XL_MINIMIZED);
      addTable();
      viewChart.setEnabled(true);
      print.setEnabled(true);
      label.setEnabled(true);
      combobox.setEnabled(true);
    }

    private void addTable() 
      throws ActiveXException {
        sheet.setFrozen(true);
        addTableName(tableName);
        addTableBounds(columnNames, rowNames);
        addColumnNames(columnNames);
        addRowNames(rowNames);
        sheet.setBackground(Color.white);
        sheet.setFrozen(false);
        sheet.setFrozen(true);
        addData(data);  
        selectFromIndex(0);
        centerSelection();
        sheet.setFrozen(false);
    }

    private void addTableName(String tableName)
              throws ActiveXException
    {           
      setValueOfCell("A1", tableName); 
      setBoldRange("A1", true);
    }

    private void addTableBounds(String[] columnNames, String[] rowNames)
              throws ActiveXException
    { 
      if ((numberOfDataColumns != numberOfColumns)
          || (numberOfDataRows != numberOfRows))
      {
          setValueOfCell(defaultTableExtrema, " ");
      }
    }

    private void addColumnNames(String[] columnNames) 
              throws ActiveXException
    {           
      int length = columnNames.length;

      for (int i = 0; i < length; i++) 
      {  
        setValueOfCell(determineColumn(i + 1) + 2,
                       columnNames[i]);                         
      }
    }

    private void addRowNames(String[] rowNames) 
              throws ActiveXException
    {           
      int length = rowNames.length;

      for (int i = 0; i < length; i++) 
      {  
        setValueOfCell("A" + (i + 3),
                       rowNames[i]);                         
      }
    }

    private void addData(int[][] data) 
      throws ActiveXException 
    {
      int dataRows = data.length;
      int dataColumns = data[0].length;

      for (int i = 0; i < dataRows; i++)
        for (int j = 0; j < dataColumns; j++)
        {
          String range = determineColumn(j + 1) + (i + 3);
          if ((i == (dataRows - 1))
              && (j == (dataColumns -1)))
              tableExtrema = range;
          setValueOfCell(range,
                         data[i][j]);                         
        }
    }

    private void giveRowChoices() {
      label.setText("Select Row:    ");

      // Bug in swing: Do not call removeAllItems when a combobox is empty.
      if (combobox.getItemCount() != 0)
        combobox.removeAllItems();

      combobox.addItem("All");      
      for (int i =0 ; i < numberOfDataRows; i ++)
        combobox.addItem(rowNames[i] + "     ");
    }

    private void giveChartTypeChoices() {
      label.setText("Select Chart:   ");

      // Bug in swing: Do not call removeAllItems when a combobox is empty.
      if (combobox.getItemCount() != 0)
        combobox.removeAllItems();

      combobox.addItem("Bar Chart");      
      combobox.addItem("Pyramid");      
      combobox.addItem("Pie Chart");      
      combobox.addItem("3D Pie Chart");      
    }

    private String determineColumn(int i) 
    {
      int alphabetLength = alphabet.length;

      if (i < alphabetLength) {
        return alphabet[i];   
      }
      else {
          int key1 = i / alphabetLength;
          int key2 = i % alphabetLength;

          if ((key1 < alphabetLength)
              &&
              (key2 < alphabetLength))
              return alphabet[key1] + alphabet[key2];
          else return "ZZ";
      }
    }


    private void selectFromIndex(int index) 
      throws ActiveXException
    { 
      if (selectionRange != null)
        setBlueSelection(false); 
      if (index == 0)
        selectionRange =  "A2:" + tableExtrema;
      else {
        String lastColumn = determineColumn(numberOfDataColumns + 1);
        String row = "" + (index + 2);
        selectionRange = "A2:" + lastColumn + 2;
        selectionRange = selectionRange + ", A" + 
          row + ":" + lastColumn + row;
      }
      selectedIndex = index;
      select(selectionRange);
      setBlueSelection(true);
    }

    private void setValueOfCell(String range, String value) 
                          throws ActiveXException
    {
      System.out.println("range = " + range);
      System.out.println("value = " + value);
      Range chosen = app.getAxRange(new Variant(range));
      chosen.setAxValue(new Variant(value));
    }

    private void setValueOfCell(String range, int value) 
                          throws ActiveXException
    {
      System.out.println("range = " + range);
      System.out.println("value = " + value);
      Range chosen = app.getAxRange(new Variant(range));
      chosen.setAxValue(new Variant(value));
    }

    private void centerSelection()
                                    throws ActiveXException
    {
      selection.setAxHorizontalAlignment(new Variant(XlHAlign.XL_H_ALIGN_CENTER));
    }

    private void setBoldRange(String range,
                              boolean bold)
                                    throws ActiveXException
    {
      Range chosen = app.getAxRange(new Variant(range));
      Font font = chosen.getAxFont();
      font.setAxBold(new Variant(bold));
    }

    private void select(String range)
                    throws ActiveXException 
    {
      selection = app.getAxRange(new Variant(range));
      selection.Select();
    }

    private void setBlueSelection(boolean setBlue) 
                    throws ActiveXException
    {
      Font font = selection.getAxFont();
      if (setBlue) 
        font.setAxColorIndex(new Variant(5));
      else font.setAxColorIndex(new Variant(0)); 
    }


    //********************* Handling Charts *************

    private void addChart()
                        throws ActiveXException
    {
      Sheets sheets = app.getAxCharts();
      sheets.Add();
      chart = app.getAxActiveChart();  
    }

    private void deleteChart() 
                    throws ActiveXException
    {
      boolean oldDisplayAlerts = app.getAxDisplayAlerts();
      app.setAxDisplayAlerts(false);
      chart.Delete();
      app.setAxDisplayAlerts(oldDisplayAlerts);
      chart = null;
    }

    private void setChartType(String type) 
                    throws ActiveXException
    {
      if (type != null) {
        if (type.equals("Pie Chart")) {
          chart.setAxChartType(XlChartType.XL_PIE);
          return;
        }
        if (type.equals("Bar Chart")) {
          chart.setAxChartType(XlChartType.XL_BAR_CLUSTERED);
          return;
        }
        if (type.equals("3D Pie Chart")) {
          chart.setAxChartType(XlChartType.XL3_D_PIE);
          return;
        }
        if (type.equals("Pyramid")) {
          chart.setAxChartType(XlChartType.XL_PYRAMID_COL);
          return;
        }
      }
    }

    //************ Configuring dimensions *********************

    @Override
    public Dimension getMinimumSize() 
    {
      return getPreferredSize();
    }

    @Override
    public Dimension getPreferredSize() 
    {
      Dimension sheetDimension = sheet.getSize();
      int sheetWidth = sheetDimension.width;
      int sheetHeight = sheetDimension.height;

      return new Dimension(sheetWidth, sheetHeight + 20);
    }

    //******************** Deleting Excel resources when finished *******
    
    @Override
    public void finalize() {        
      try {
      boolean oldDisplayAlerts = app.getAxDisplayAlerts();
      app.setAxDisplayAlerts(false);
      if (chart != null)
        chart.Delete();
      if (sheet != null)
         sheet.Delete();
      app.setAxDisplayAlerts(oldDisplayAlerts);
      }
      catch (ActiveXException e) { }
    }

    public void delete() {
        finalize();
    }
    
    //*************** ActionListener for button actions *****
   
    class TableBrowserActionListener implements ActionListener 
    {

      @Override
      public void actionPerformed(ActionEvent e) {
        Object cmdSource = (Object)e.getSource ();
        
        if (cmdSource == print) {
           System.out.println("PRINT");
           try {
             if (chart == null)
               sheet.PrintOut();
             else chart.PrintOut();
           }
           catch (ActiveXException x) 
           { }
           return;
        }

        if (cmdSource == viewChart) {
            System.out.println("VIEW CHART");
            try {
              addChart();
            }
            catch (ActiveXException x) {    
              return;
            }   
            viewChart.setEnabled(false);
            back.setEnabled(true);
            label.setEnabled(false);
            giveChartTypeChoices();
            return;
        }

        if (cmdSource == back) {
          System.out.println("BACK");
          try {
              deleteChart();
          }
          catch (ActiveXException x) {
            return;
          }
          back.setEnabled(false);
          viewChart.setEnabled(true);
          label.setEnabled(true);
          combobox.removeActionListener(actionListener);
          giveRowChoices();
          combobox.addActionListener(actionListener);
          combobox.setSelectedIndex(selectedIndex);
          chart = null;
          return;
        }

        if (cmdSource == combobox) {
          System.out.println("COMBOBOX");
          int selected = combobox.getSelectedIndex();
          String selectedString = (String) combobox.getSelectedItem();
          try {
            if (chart == null)
              selectFromIndex(selected);
            else setChartType(selectedString);
          }
          catch (ActiveXException x) {
              return;
          }
          return;
        }
      }
    }

    //***************  Testing Code ************************

    public static void main(String[] args) {
      JFrame frame =  new JFrame("Table Browser");
      
      try {
        TableBrowser tableBrowser = new TableBrowser(); 
        // Create a new TableBrowser and add to the frame
        frame.getContentPane().setLayout(new BorderLayout());
        frame.getContentPane().add(tableBrowser, "Center");
        frame.setSize(tableBrowser.getPreferredSize());
        frame.addWindowListener(tableBrowser);
        frame.show();
        tableBrowser.activateComponents();
      }
      catch(Exception e) {
        e.printStackTrace();
        System.out.println("Failure : " + e);
      }      
    }    

    @Override
    public void windowOpened(WindowEvent e) {
    }

    @Override
    public void windowClosing(WindowEvent e) {
        delete();
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
