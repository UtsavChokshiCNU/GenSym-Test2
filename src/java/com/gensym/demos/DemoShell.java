package com.gensym.demos;

import java.io.*;
import java.awt.Frame;
import java.awt.TextArea;
import java.awt.MenuBar;
import java.awt.Menu;
import java.awt.MenuItem;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.awt.Color;

public class DemoShell extends Frame{
  private Demo demo;
  private String msg;
  private MenuBar menuBar;
  private String fileName;
  private Frame sourceFrame;
  private Class demoClass;

  public DemoShell(String title, String msg, Demo demo, String fileName){
    super(title);
    this.demo = demo;
    this.msg = msg;
    this.demoClass = demo.getClass();
    this.fileName = fileName;

    TextArea ta = new TextArea(msg, 20, 60, TextArea.SCROLLBARS_VERTICAL_ONLY);
    ta.setEditable(false);
    add(ta);

    menuBar = new MenuBar();
    Menu fileMenu = new Menu("File");
    menuBar.add(fileMenu);

    MenuItem demoMenuItem = new MenuItem("Run Demo");
    fileMenu.add(demoMenuItem);
    DemoAdapter da = new DemoAdapter();
    demoMenuItem.addActionListener(da);

    fileMenu.addSeparator();

    MenuItem exitMenuItem = new MenuItem("Exit");
    fileMenu.add(exitMenuItem);
    ExitAdapter ea = new ExitAdapter();
    exitMenuItem.addActionListener(ea);

    Menu viewMenu = new Menu("View");
    menuBar.add(viewMenu);
    MenuItem sourceCode = new MenuItem("Source Code");
    viewMenu.add(sourceCode);
    sourceCode.addActionListener(new ViewAdapter());

    setMenuBar(menuBar);

    WinAdapter wa = new WinAdapter();
    addWindowListener(wa);
  }

  private void viewSource(String fileName){
    System.out.println("View Source");

    InputStream s = demoClass.getResourceAsStream(fileName);
    BufferedReader bufReader = new BufferedReader(new InputStreamReader(s));
    sourceFrame = new Frame(fileName);
    TextArea ta = new TextArea();
    ta.setEditable(false);
    try{
      while(true){
	String line = bufReader.readLine();
	if (line == null) break;
	ta.append(line+"\n");
      }
    }
    catch(IOException ex){
      ex.printStackTrace();
    }
    sourceFrame.add(ta);
    sourceFrame.setSize(400, 400);
    sourceFrame.setVisible(true);
    WindowListener wa = new WindowAdapter(){
      @Override
      public void windowClosing(WindowEvent e){
	sourceFrame.setVisible(false);
      }
    };
    sourceFrame.addWindowListener(wa);
  }

  public class ExitAdapter implements ActionListener{
    @Override
    public void actionPerformed(ActionEvent e){
      System.exit(0);
    }
  }

  public class DemoAdapter implements ActionListener{
    @Override
    public void actionPerformed(ActionEvent e){
      demo.runDemo((Frame)(DemoShell.this));
    }
  }

  public class WinAdapter extends WindowAdapter{
    @Override
    public void windowClosing(WindowEvent e){
      System.exit(0);
    }
  }

  public class ViewAdapter implements ActionListener{
    @Override
    public void actionPerformed(ActionEvent e){
      viewSource(fileName);
    }
  }

  @Override
  public MenuBar getMenuBar(){
    return menuBar;
  }

}
   






