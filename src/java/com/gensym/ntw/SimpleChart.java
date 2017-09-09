package com.gensym.ntw;

import java.awt.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.message.*;
import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.VariableOrParameter;

public class SimpleChart extends Canvas implements VariableValueListener
{
  TwAccess context;
  private double low_value;
  private double high_value;
  private double low_time;
  private double high_time;
  private int margin = 60;
  private int count = 0;
  private double[] values = new double[1000];
  private double[] times = new double[1000];
  private Font font = new Font("sansserif",Font.PLAIN,14);
  private static final Symbol TYPE_ = Symbol.intern ("TYPE");
  public static final Symbol VARIABLE_VALUE_ =
  Symbol.intern ("VARIABLE-VALUE");
  private double last_time = 0.0;


  public SimpleChart (double lv, double hv,
                    double lt, double ht)
  {
    low_value = lv;
    high_value = hv;
    low_time = lt;
    high_time = ht;
  }

  public SimpleChart ()
  {

  }

  public void setInterface (TwAccess context) {
    this.context = context;
  }

  public void setRange (double lv, double hv,
                        double lt, double ht)
  {
    low_value = lv;
    high_value = hv;
    low_time = lt;
    high_time = ht;
  }

  @Override
  public void valueChanged (VariableValueEvent event) {
    System.out.println(event);
    Object newValue = event.getNewValue();
    //System.out.println("rcvd update="+newValue);
    
    int new_value = ((Integer) newValue).intValue();
    addPoint((double) new_value, last_time);
    repaint();
    last_time += 12.0;
  }
  
  @Override
  public void receivedInitialValue(VariableValueEvent e) {
  }

  @Override
  public void paint(Graphics g)
  {
    int i;
    double last_value = 0.0;
    double last_time = 0.0;
    boolean is_first_time = true;

    g.setColor(Color.white);
    Rectangle bounds = getBounds();
    g.fillRect(0,0,bounds.width,bounds.height);
    drawAxes(g);
    for (i=0; i<count ; i++) {
       if (is_first_time)
         is_first_time = false;
       else
         drawConnector(g,last_value,last_time,values[i],times[i]);
       drawPoint(g, values[i],times[i]);
       last_value = values[i];
       last_time = times[i];
    }
  }

  @Override
  public boolean handleEvent(Event event)
  {
    /* System.out.println("canvas got event="+event); */
    return super.handleEvent(event);
  }

  public void drawAxes(Graphics g)
  {
    g.setColor(Color.black);
    Rectangle bounds = getBounds();
    g.setFont(font);
   
    drawLabel(g,""+high_value,margin >> 1 ,margin);
    drawLabel(g,""+low_value,margin >> 1 ,(bounds.height-margin));

    int time_y = (bounds.height-(margin >> 1));
    drawLabel(g,""+low_time,margin,time_y);
    drawLabel(g,""+high_time,bounds.width - margin,time_y);

    g.drawLine(margin,margin,margin,bounds.height-margin);
    g.drawLine(margin,bounds.height-margin,
               bounds.width-margin,bounds.height-margin);

    
  }

  public void drawLabel(Graphics g, String s, int x , int y)
  {
    FontMetrics metrics = g.getFontMetrics();
   
    int y_adjust = metrics.getAscent() >> 1;
    int x_adjust = - (metrics.stringWidth(s) >> 1);

    g.drawString(s,x+x_adjust, y+y_adjust);
  }  

  public int scaleValue(double value)
  {
    Rectangle bounds = getBounds();
    int vrange = bounds.height - 2 * margin;
    int scaled_y;
 
    scaled_y = (int)
            (vrange * ((value - low_value) / (high_value - low_value)));
    
    return bounds.height - (margin + scaled_y);
  }

  public int scaleTime(double time)
  {
    Rectangle bounds = getBounds();
    int hrange = bounds.width - 2 * margin;
    int scaled_x;
 
    scaled_x = (int)
            (hrange * ((time - low_time) / (high_time - low_time)));
    
    return margin + scaled_x;
  }

  public void addPoint(double value, double time)
  {
    values[count] = value;
    times[count] = time;
 
    count++;
  }

  public void drawConnector(Graphics g, double value1, double time1,
                              double value2, double time2)
  {
    int scaled_y1 = scaleValue(value1);
    int scaled_x1 = scaleTime(time1);
    int scaled_y2 = scaleValue(value2);
    int scaled_x2 = scaleTime(time2);

    g.setColor(Color.black);
    g.drawLine(scaled_x1,scaled_y1,scaled_x2,scaled_y2);
  }

  public void drawPoint(Graphics g, double value, double time)
  {
    int scaled_y = scaleValue(value);
    int scaled_x = scaleTime(time);

    g.setColor(Color.red);
    g.fillRect(scaled_x-5,scaled_y-5,10,10);
  }


  public void testShow()
  throws G2AccessException {
    Frame frame = new Frame();

    setRange(0.0,100.0,0.0,500.0);

    VariableOrParameter itm = (VariableOrParameter) context.getUniqueNamedItem
      (Symbol.intern ("OBJECT"), Symbol.intern ("IV0"));
    System.out.println("item: " + itm);

    itm.addVariableValueListener(this);
	
    frame.setSize (800,600);
    frame.setLayout(new BorderLayout());
    frame.add("Center",this);
    frame.validate();
    frame.show();
  }

  public static void main(String[] args)
  {
    SimpleChart canvas = new SimpleChart();
    try {
      canvas.testShow();
    } catch (G2AccessException g2ae) {
      System.out.println("Error in testShow");
      g2ae.printStackTrace();
    }
  }
}
