package com.gensym.ntw;
 
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.message.*;
import java.awt.*;
import com.gensym.jgi.G2AccessException;
 
public class ImprovedChart extends SimpleChart
{
     
    public static void main (String argv[])
    {
        ImprovedChart chart;
         
        chart = new ImprovedChart ();
	try {
	  chart.testShow();
	} catch (G2AccessException g2ae) {
	  System.out.println("Couldn't show ImprovedChart: " + g2ae);
	  g2ae.printStackTrace();
	}
    }
     
    @Override
    public void drawPoint (Graphics g, double pointValue, double pointTime)
    {
        int scaledX;
        int scaledY;
         
        scaledY = scaleValue(pointValue);
        scaledX = scaleTime(pointTime);
        g.setColor(Color.blue);
        g.fillOval(scaledX - 10, scaledY - 10, 20, 20);
    }
}
