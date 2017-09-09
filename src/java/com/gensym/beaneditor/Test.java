package com.gensym.beaneditor;

import java.awt.*;
import java.awt.event.*;
import com.gensym.draw.*;

class Test extends Frame implements ActionListener
{
  private BeanCanvas canvas;

  private MenuItem createMenuItem(String string)
  {
    MenuItem item = new MenuItem(string);
    item.addActionListener(this);
    return item;
  }

  public void startup ()
  {
 
    MenuBar menuBar = new MenuBar();
    Menu fileMenu = new Menu("File");
    menuBar.add(fileMenu);
    fileMenu.add(createMenuItem("Quit"));

    Menu growMenu = new Menu("Grow");
    menuBar.add(growMenu);
    growMenu.add(createMenuItem("North"));
    growMenu.add(createMenuItem("South"));
    growMenu.add(createMenuItem("East"));
    growMenu.add(createMenuItem("West"));

    Menu beansMenu = new Menu("Beans");
    menuBar.add(beansMenu);
    beansMenu.add(createMenuItem("AWT Button"));
    beansMenu.add(createMenuItem("CollectionList"));
    beansMenu.add(createMenuItem("StructureMUX"));
    beansMenu.add(createMenuItem("None"));

    Menu eventMenu = new Menu("Events");
    menuBar.add(eventMenu);
    eventMenu.add(createMenuItem("Show All Events"));
    eventMenu.add(createMenuItem("Hide All Events"));

    Menu reportMenu = new Menu("Report");
    menuBar.add(reportMenu);
    reportMenu.add(createMenuItem("Contents"));
    setMenuBar(menuBar);

    canvas = new BeanCanvas();
  
    ViewScrollbar vscroll 
           = new ViewScrollbar(canvas,Scrollbar.VERTICAL,
                                50,50,0,100);
    ViewScrollbar hscroll 
           = new ViewScrollbar(canvas,Scrollbar.HORIZONTAL,
                                50,50,0,100);

    setSize(640,480);
    System.out.println("initting DrawApplet size="+canvas.getSize());
    
    Panel hackPanel = new Panel();
    hackPanel.setLayout(new BorderLayout());
    setLayout(new BorderLayout());
    add("Center",hackPanel);
    hackPanel.add("South",hscroll);
    hackPanel.add("East",vscroll);
    hackPanel.add("Center",canvas);
    System.out.println("+++++++ progress 3");

    System.out.println("+++++++ progress 4");

    validate ();
    show();
        
    System.out.println("+++++++ progress 5");


  
    canvas.addScrollObserver(vscroll,false);
    canvas.addScrollObserver(hscroll,true);
    canvas.setScroll();
    System.out.println("initting DrawApplet size="+canvas.getSize());


    System.out.println("done with layout");

    canvas.setEventHandler(new BeanEditTool(canvas, this));
    System.out.println("frame insets ="+getInsets());
    System.out.println("canvas insets ="+canvas.getInsets());
  }

  @Override
  public void actionPerformed(ActionEvent event)
  {
    System.out.println("action-event="+event);
    String command = event.getActionCommand();

    if (command.equals("Quit"))
      System.exit(0);
    else if (command.equals("AWT Button"))
      canvas.setNewBeanClass("java.awt.Button");
    else if (command.equals("CollectionList"))
      canvas.setNewBeanClass("com.gensym.controls.CollectionList");
    else if (command.equals("StructureMUX"))
      canvas.setNewBeanClass("com.gensym.controls.StructureMUX");
    else if (command.equals("None"))
      canvas.setNewBeanClass(null);
    else if (command.equals("North"))
      {

      }
    else if (command.equals("Contents"))
      {
	canvas.dumpElements();
      }
  }

  public static void main (String[] args)
  {
    Test test = new Test();
    test.startup();
  }
}
