package com.gensym.draw;

import java.awt.*;
import java.awt.event.*;
import com.gensym.util.Symbol;

/**
* DrawShell implements a top-level window of an example application that
* demonstrates some of the uses of the PersistentCanvas class.  Users
* should NOT subclass this class, it is meant for instructional purposes.
*
* @author Joe Devlin
* @see com.gensym.draw.PersistentCanvas
*/
public class DrawShell extends Frame implements ActionListener, WindowListener
{
  private PersistentCanvas canvas;

  public void startup()
  {
    canvas = new PersistentCanvas();
    Button line_button = new Button("Line");
    Button rect_button = new Button("Rect");
    Button move_button = new Button("Move");
    Button change_button = new Button("Change");
    Button grow_e_button = new Button("GrowE");
    Button grow_w_button = new Button("GrowW");
    Button grow_n_button = new Button("GrowN");
    Button grow_s_button = new Button("GrowS");
    Button black_button =
        new DumbDrawColorButton(canvas,"Black", Color.black);
    Button red_button = 
        new DumbDrawColorButton(canvas,"Red", Color.red);
    Button green_button = 
        new DumbDrawColorButton(canvas,"Green", Color.green);
    Button blue_button = 
        new DumbDrawColorButton(canvas,"Blue", Color.blue);
    ViewScrollbar vscroll 
           = new ViewScrollbar(canvas,Scrollbar.VERTICAL,
                                50,50,0,100);
    ViewScrollbar hscroll 
           = new ViewScrollbar(canvas,Scrollbar.HORIZONTAL,
                                50,50,0,100);
    Panel tool_panel = new Panel();
    Panel color_panel = new Panel();
    Panel center_panel = new Panel();

    line_button.addActionListener(this);
    rect_button.addActionListener(this);
    move_button.addActionListener(this);
    change_button.addActionListener(this);
    grow_e_button.addActionListener(this);
    grow_w_button.addActionListener(this);
    grow_n_button.addActionListener(this);
    grow_s_button.addActionListener(this);
    black_button.addActionListener(this);
    red_button.addActionListener(this);
    green_button.addActionListener(this);
    blue_button.addActionListener(this);


    setSize(640,480);
    System.out.println("initting DrawApplet size="+canvas.getSize());
    
    tool_panel.setLayout(new GridLayout(8,1));
    tool_panel.add(line_button);
    tool_panel.add(rect_button);
    tool_panel.add(move_button);
    tool_panel.add(change_button);
    tool_panel.add(grow_n_button);
    tool_panel.add(grow_s_button);
    tool_panel.add(grow_e_button);
    tool_panel.add(grow_w_button);
    System.out.println("+++++++ progress 2");

    color_panel.setLayout(new GridLayout(4,1));
    color_panel.add(black_button);
    color_panel.add(red_button);
    color_panel.add(green_button);
    color_panel.add(blue_button);

    center_panel.setLayout(new BorderLayout());
    center_panel.add("South",hscroll);
    center_panel.add("East",vscroll);
    center_panel.add("Center",canvas);
    System.out.println("+++++++ progress 3");

    setLayout(new BorderLayout());
    add("West",tool_panel);
    add("Center",center_panel);
    add("East",color_panel);

    System.out.println("+++++++ progress 4");

    validate ();
    show();
        
    System.out.println("+++++++ progress 5");

    TextStyle small_style = 
        new TextStyle (new Font("sansserif",Font.PLAIN,14),
                         0,0,4);
    System.out.println("here about to add tbox");
    TextBoxElement tbox = new TextBoxElement (10, 30,200, 40,
                              "Hello World - The quick brown fox "+
                              "jumps over the lazy dogs.",
                              small_style,
                              Color.yellow, Color.black,
                              0, Color.black);
    canvas.addElement(tbox);
    TextCell textCell = tbox.getTextCell();
    textCell.setDrawBorder(true);
    textCell.setDrawBackground(true);
    System.out.println("here after add tbox");
    tbox.format(canvas.getGraphics());
    

    Point[] vertices = new Point[4];
    vertices[0] = new Point(150,150);
    vertices[1] = new Point(200,150);
    vertices[2] = new Point(200,200);
    vertices[3] = new Point(150,200);
    int[] widths = { 5, 4 , 3 };
    Color[] colors = new Color[3];
    colors[0] = Color.orange;
    colors[1] = Color.cyan;
    colors[2] = Color.magenta;
 
    Symbol[] color_symbols = { Symbol.intern("REG1"), Symbol.intern("REG2"),
			       Symbol.intern("REG3") };
    Object[] regionPattern = { Symbol.intern("REG1"), Symbol.intern("REG2"),
			        Symbol.intern("REG1") };

    ConnectionElement conn = new ConnectionElement
                                   (vertices,
				    widths, regionPattern,
				    color_symbols,colors,
				    ConnectionElement.ORTHOGONAL);
    canvas.addElement(conn);

    int[] xArray = { 300, 250, 350};
    int[] yArray = { 300, 400, 400};
    PolygonElement poly = new PolygonElement(Color.green, 3, xArray, yArray);

    canvas.addElement(poly);
  
    canvas.vertical_state.addObserver(vscroll);
    canvas.horizontal_state.addObserver(hscroll);
    canvas.setScroll();
    System.out.println("initting DrawApplet size="+canvas.getSize());


/*    frame = new JDIFrame("Important Application");
    frame.resize(800,600);
    frame.show(); */
    System.out.println("done with layout");
    addWindowListener(this);
  } 

  @Override
  public void actionPerformed(ActionEvent event)
  {
      Object object_target = event.getSource();
      System.out.println("action="+event+" on "+object_target);
      if (object_target instanceof DumbDrawColorButton)
      {
         DumbDrawColorButton color_button 
             = (DumbDrawColorButton) object_target;

         System.out.println("Setting Color="+color_button.getColor());
         canvas.current_color = color_button.getColor();
      }

      if (object_target instanceof Button)
      {
         Button button = (Button) object_target;
         String button_label = button.getLabel();

         if (button_label.compareTo("Line") == 0)
             canvas.setEventHandler(new LineTool(canvas));

         if (button_label.compareTo("Rect") == 0)
             canvas.setEventHandler(new RectTool(canvas));
         
         if (button_label.compareTo("Move") == 0)
	   {
	     System.out.println("move tool");
             canvas.setEventHandler(new MoveTool(canvas));
	   }
         
         if (button_label.compareTo("Change") == 0)
           {
             canvas.setEventHandler(new ChangeTool(canvas));
	     canvas.dumpElements();
           }

         if (button_label.compareTo("GrowN") == 0)
             canvas.growLogical(100,false,true);
         
         if (button_label.compareTo("GrowS") == 0)
             canvas.growLogical(100,false,false);
         
         if (button_label.compareTo("GrowE") == 0)
             canvas.growLogical(100,true,false);
         
         if (button_label.compareTo("GrowW") == 0)
             canvas.growLogical(100,true,true);
      }


  }

  @Override
  public void windowOpened(WindowEvent e) {}
  @Override
  public void windowClosing(WindowEvent e) 
 {
    System.out.println("closing");
    System.exit(0);
  }

  @Override
  public void windowClosed(WindowEvent e) 
  {
    System.out.println("closed");
    System.exit(0);
  }

  @Override
  public void windowIconified(WindowEvent e)
  {
    System.out.println("Iconified");
  }
  @Override
  public void windowDeiconified(WindowEvent e)
 {
    System.out.println("act");
  }
  @Override
  public void windowActivated(WindowEvent e) {}
  @Override
  public void windowDeactivated(WindowEvent e)  
{
    System.out.println("de-act");
  }

  public static void main(String args[]) 
  {
      DrawShell shell = new DrawShell();

      
      shell.startup();

      
  }
}

