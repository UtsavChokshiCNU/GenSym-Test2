/*
import com.gensym.chart.bar.*;
import com.gensym.chart.line.*;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.URL;
import java.util.*;

import javax.swing.text.*;
import javax.swing.*;
import javax.swing.border.*;
import javax.swing.event.*;
*/

/**
Test class
Purpose: To test my scatter API
May 21, 1998
GENSYMCID-1515
This class was moved to neuronline dir????
 */
 
 /*
public class BarFrame extends JFrame implements ActionListener {

	private static final int DATASETSIZE = 20;

	private double [] y = new double[DATASETSIZE];
	private double [] x = new double[DATASETSIZE];
	private Random rand = new Random(10);
	private BarChart chart;



    public BarFrame() {
        super("Bar Chart");
        JPanel pane = new JPanel();
		pane.setBorder(BorderFactory.createEtchedBorder());
		pane.setLayout(new GridLayout());
        pane.setBackground(Color.pink);
        
		for(int i = 0; i < DATASETSIZE; i++) {
			y[i] = rand.nextDouble()*10;
		//	System.out.println("y: " + y[i]);
		}

  		chart = new BarChart("pic", y, 0, DATASETSIZE);
		chart.repaint();
		

		JPanel buttons = new JPanel();
		JButton butt;
		Dimension vpad10 = new Dimension(1,5);

		buttons.setBorder(BorderFactory.createTitledBorder("View Options"));
		buttons.setLayout(new BoxLayout(buttons, BoxLayout.Y_AXIS));
		Dimension dim = new Dimension(90,25);


		
		butt = new JButton ("Vertical");
		butt.addActionListener(this);
		butt.setPreferredSize(dim);
		butt.setMaximumSize(dim);
		buttons.add(butt);
		buttons.add(Box.createRigidArea(vpad10));

		butt = new JButton ("Horizontal");
		butt.addActionListener(this);
		butt.setPreferredSize(dim);
		butt.setMaximumSize(dim);
		buttons.add(butt);
		buttons.add(Box.createRigidArea(vpad10));

		butt = new JButton("Inverted");
		butt.addActionListener(this);
		butt.setPreferredSize(dim);
		butt.setMaximumSize(dim);
		buttons.add(butt);
		buttons.add(Box.createRigidArea(vpad10));

		butt = new JButton ("Filled");
		butt.addActionListener(this);
		butt.setPreferredSize(dim);
		butt.setMaximumSize(dim);
		buttons.add(butt);
		buttons.add(Box.createRigidArea(vpad10));

		butt = new JButton("Not Filled");
		butt.addActionListener(this);
		butt.setPreferredSize(dim);
		butt.setMaximumSize(dim);
		buttons.add(butt);
		buttons.add(Box.createRigidArea(vpad10));


		pane.add(chart);
		pane.add(buttons);
		setContentPane(pane);
    }
	

	public void actionPerformed(ActionEvent e) {
//		System.out.println("actionPerformed: = "+e.getActionCommand());
		String command = e.getActionCommand();

		if (command == "Horizontal") {
			chart.setChartOrientation(BarPlot.HORIZONTAL);
		}
		if (command == "Vertical") {
			chart.setChartOrientation(BarPlot.VERTICAL);
		}
		if (command == "Inverted") {
			chart.setChartOrientation(BarPlot.INVERTED);
		}
		if (command == "Filled") {
			chart.setChartFilled(true);
		}
		if (command == "Not Filled") {
			chart.setChartFilled(false);
		}
	}
				   
	public static void main(String[] args) {
          	
        try {
			UIManager.setLookAndFeel(UIManager.getCrossPlatformLookAndFeelClassName());
			//UIManager.setLookAndFeel("com.sun.java.swing.plaf.windows.WindowsLookAndFeel");
			 
        } catch (Exception e) {
            System.err.println("Couldn't use the cross-platform "
                             + "look and feel: " + e);
        }

        JFrame frame = new BarFrame();

        WindowListener l = new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                System.exit(0);
            }
        };
        frame.addWindowListener(l);

        frame.pack();
        frame.setVisible(true);
    }
}

*/