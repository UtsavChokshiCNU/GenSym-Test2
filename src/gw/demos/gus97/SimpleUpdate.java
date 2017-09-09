import java.awt.*;
import java.applet.Applet;
import java.io.*;
import java.net.*;

// Title: SimpleUpdate
//
// Author: Buck Hubad. (more like C&P artist)
//
// Description:
// 	This reads and updates a line of text, read from a given
// 	URL.  The dataSource, refreshRateInMS, and font info can
// 	be passed as parameters from html.
//
// Instantiation:
// 	<applet code="SimpleUpdate.class" width=500 height=80>
//	<param name=refreshRateInMS value="3000">
//	<param name=dataSource value="http://siam:8080/data/data1.txt">
//	<param name=fontname value="Courier">
//	<param name=fontslant value="italic">
//	<param name=fontweight value="bold">
//	<param name=fontsize value="18">
//	</applet>

public class SimpleUpdate extends Applet implements Runnable {

    // Default values for applet parameters.  These values will be used
    // if the user leaves "label", "fontname", "fontsize", "fontslant", 
    // "fontweight", or "sleeptime" unspecified.

    private static final String LABEL     = "Hello, world.";
    private static final String FONTNAME  = "TimesRoman";
    private static final int    FONTSIZE  = 12;
    private static final int    FONTSTYLE = Font.PLAIN;
    private static final int    SLEEPTIME = 650;
    private static final String DEFSOURCE = "http://siam:8080/data/data1.txt";

    // Private state variables.

    private String  textValue       = LABEL;
    private int     refreshRateInMS = SLEEPTIME;
    private Font    textFont        = null;
    private Thread  flashThread     = null;
    private Color   textColor       = Color.black;
    private String  dataSource      = DEFSOURCE;


    public void init() {

	String param;
	String fontName  = FONTNAME;
	int    fontStyle = FONTSTYLE;
	int    fontSize  = FONTSIZE;

	// The "refreshRateInMS" parameter tells how long to pause between
	// data updates (in milliseconds).

	if ((param = getParameter("refreshRateInMS")) != null) {
	    refreshRateInMS = Integer.parseInt(param);
	}

	// The "dataSource" parameter holds the URL of the data source.

	if ((param = getParameter("dataSource")) != null) {
	    dataSource = param;
	} 

	// Initialize text field

	textValue = readFromURL();

	// The four parameters: "fontname", "fontslant", "fontweight",
	// and "fontsize" are used to select a font for the label.  
	// In the Java font model, "fontslant" and "fontweight" are combined 
	// into font "style".

	if ((param = getParameter("fontname")) != null) {
	    fontName = param;
	}

	if ((param = getParameter("fontslant")) != null &&
	    (param.equals("italic") || param.equals("ITALIC"))) {
	    fontStyle |= Font.ITALIC; 
	}

	if ((param = getParameter("fontweight")) != null &&
	    (param.equals("bold") || param.equals("BOLD"))) {
	    fontStyle |= Font.BOLD;
	}

	if ((param = getParameter("fontsize")) != null) {
	    fontSize = Integer.parseInt(param);
	}

	// Create a font object from the font parameters.

	textFont = new Font(fontName, fontStyle, fontSize);
    }
    
    public void paint(Graphics g) {

	// We recompute dimensions every time in case the applet is
	// resized.
	//
	// "dim"       is the applet width and height.
	// "metrics"   is the set of font parameters for the font we have
	//             chosen.
	// "textWidth" is the width of the label in the chosen font.
	// "x"         is the horizontal position of the beginning of
	//             the label.
	// "y"         is the vertical position of the baseline of
	//             the label. The "baseline" is the position
	//             of bottom of a line of text not counting 
	//             the tails of lower case "g", "y", etc.  The
	//             extra space taken up by the tails is called
	//             the _descent_ of the font.

	Dimension   dim	      = size();             
	FontMetrics metrics   = getFontMetrics(textFont); 
	int         textWidth = metrics.stringWidth(textValue);


	// The label will be clipped if "x" and "y" are outside
	// the applet.

	int         x	      = (dim.width  - textWidth) / 2;
	int         y	      = (dim.height - metrics.getHeight()) / 2 +
	  metrics.getHeight() - metrics.getDescent();

	// Draw the label.

	// We set the font first so that the FontMetrics will return
	// a correct value for the width of the label.

	g.setFont(textFont); 
	g.setColor(textColor);
	g.drawString(textValue, x, y);
    }

    public void start() {

	// Create a thread for this applet and start it.

	flashThread = new Thread(this);
	flashThread.start();
    }

    public void stop() {

	// Stop the applet's thread.

	flashThread.stop();
    }

    public void run() {

	// Run the applet sleeping "refreshRateInMS" milliseconds between
	// each repaint.

	while (true) {
	    try {
		flashThread.sleep(refreshRateInMS);
	    } catch (InterruptedException e) {
	    }

          textValue = readFromURL();

	    repaint();
	}
    }

    private String readFromURL() {
    	DataInputStream input;
	String line;
	String buffer = "";

	try {
		input = new DataInputStream(
			new URL(dataSource).openStream());
	} catch (java.io.IOException e) {
		return "Error opening " + dataSource;
	}

	try {
		while ((line = input.readLine()) != null) {
		    buffer += line;
		}
	} catch (java.io.IOException e) {
		return "Error reading from " + dataSource;
	}

	try {
		input.close();
	} catch (java.io.IOException e) {
		return "Error closing " + dataSource;
	}

	return buffer;
    }

}
