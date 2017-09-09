import java.awt.*;
import java.applet.Applet;
import java.io.*;
import java.net.*;

// Title: SimpleTextField
//
// Description:
// 	This reads and updates a text field, read from a given
// 	URL.  The data, font, and refresh info is passed as parameters.
//
//    Up to 5 data items may be displayed. (numbered 0-4)
//    A proper data set consists of the following parameters:
//      data0Name, data0URL, data0Width
//    dataName and dataURL are required
//    dataWidth specifies field width. Default is 20
//
//    A refreshRate of 0 (default) implies NO UPDATES.
//
//    Default font in TimesRoman Plain 12pt
//
// Instantiation:
// 	<applet code="SimpleTextField.class" width=500 height=100>
//	<param name=refreshRateInMS value="3000">
//	<param name=data0Name value="Tank Level: ">
//	<param name=data0URL  value="data/data0.txt">
//    <param name=data0Width value="40">
//	<param name=data1Name value="Tank Temperature: ">
//	<param name=data2URL  value="data/data1.txt">
//	</applet>

public class SimpleTextField extends Applet implements Runnable {

    // Default values for applet parameters.  These values will be used
    // if the user leaves "refreshRateInMS" or "dataSource unspecified.

    private static final String FONTNAME  = "TimesRoman";
    private static final int    FONTSIZE  = 12;
    private static final int    FONTSTYLE = Font.PLAIN;
    private static final int    SLEEPTIME = 0;
    private static final String DEFSOURCE = "No URL specified!";
    private static final int    DEFWIDTH  = 10;

    // Private state variables.

    private int     refreshRateInMS = SLEEPTIME;
    private Thread  updateThread     = null;
    private Font    textFont        = null;
    private Color   textColor       = Color.black;

    private String      data0URL   = DEFSOURCE;
    private Label       data0Name  = null;
    private TextField   data0Field = null;
    private int         data0Width = DEFWIDTH;

    private String      data1URL   = DEFSOURCE;
    private Label       data1Name  = null;
    private TextField   data1Field = null;
    private int         data1Width = DEFWIDTH;

    private String      data2URL   = DEFSOURCE;
    private Label       data2Name  = null;
    private TextField   data2Field = null;
    private int         data2Width = DEFWIDTH;

    private String      data3URL   = DEFSOURCE;
    private Label       data3Name  = null;
    private TextField   data3Field = null;
    private int         data3Width = DEFWIDTH;

    private String      data4URL   = DEFSOURCE;
    private Label       data4Name  = null;
    private TextField   data4Field = null;
    private int         data4Width = DEFWIDTH;

    public void init() {
	loadGlobalParams();
	loadDataParams();
	updateFields();
	createLayout();
    }
    
    public void paint(Graphics g) {
	paintComponents(g);
    }

    public void start() {

	// If refreshRate is > 0, create a refresh thread for this
	// applet and start it.
	if (refreshRateInMS > 0) {
		updateThread = new Thread(this);
		updateThread.start();
	}
    }

    public void stop() {

	// Stop the applet's thread.
	if (refreshRateInMS > 0) {
		updateThread.stop();
	}
    }

    public void run() {

	// Run the applet sleeping "refreshRateInMS" milliseconds between
	// each repaint.
	// Note: This only runs if a new Thread is created (in start())
	while (true) {
	    try {
		updateThread.sleep(refreshRateInMS);
	    } catch (InterruptedException e) {
	    }
	    updateFields();
	}
    }


    //
    // This function loads Global parameters such as refresh rate, font info
    //
    private void loadGlobalParams() {
	String param;
	String fontName  = FONTNAME;
	int    fontStyle = FONTSTYLE;
	int    fontSize  = FONTSIZE;

	// The "refreshRateInMS" parameter tells how long to pause between
	// data updates (in milliseconds).
	if ((param = getParameter("refreshRateInMS")) != null) {
		refreshRateInMS = Integer.parseInt(param);
	}

	// The four parameters: "fontname", "fontslant", "fontweight",
	// and "fontsize" are used to select a font for the labels.  
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
	setFont(new Font(fontName, fontStyle, fontSize));
    }


    //
    // This function loads the parameters for each data set
    //
    private void loadDataParams() {
	String param;

	// The "dataName" parameter is displayed for the user
	// If this is not specified, the field is not activated.
	if ((param = getParameter("data0Name")) != null) {
		data0Name = new Label(param);

		// The "dataURL" parameter holds the URL of the data source.
		if ((param = getParameter("data0URL")) != null) {
			data0URL = param;
		} 

		// The "dataWidth" parameter controls the width of the text field
		if ((param = getParameter("data0Width")) != null) {
			data0Width = Integer.parseInt(param);
		}
		data0Field = new TextField(data0Width);
	}

	// The "dataName" parameter is displayed for the user
	// If this is not specified, the field is not activated.
	if ((param = getParameter("data1Name")) != null) {
		data1Name = new Label(param);

		// The "dataURL" parameter holds the URL of the data source.
		if ((param = getParameter("data1URL")) != null) {
			data1URL = param;
		} 

		// The "dataWidth" parameter controls the width of the text field
		if ((param = getParameter("data1Width")) != null) {
			data1Width = Integer.parseInt(param);
		}
		data1Field = new TextField(data1Width);
	}

	// The "dataName" parameter is displayed for the user
	// If this is not specified, the field is not activated.
	if ((param = getParameter("data2Name")) != null) {
		data2Name = new Label(param);

		// The "dataURL" parameter holds the URL of the data source.
		if ((param = getParameter("data2URL")) != null) {
			data2URL = param;
		} 

		// The "dataWidth" parameter controls the width of the text field
		if ((param = getParameter("data2Width")) != null) {
			data2Width = Integer.parseInt(param);
		}
		data2Field = new TextField(data2Width);
	}

	// The "dataName" parameter is displayed for the user
	// If this is not specified, the field is not activated.
	if ((param = getParameter("data3Name")) != null) {
		data3Name = new Label(param);

		// The "dataURL" parameter holds the URL of the data source.
		if ((param = getParameter("data3URL")) != null) {
			data3URL = param;
		} 

		// The "dataWidth" parameter controls the width of the text field
		if ((param = getParameter("data3Width")) != null) {
			data3Width = Integer.parseInt(param);
		}
		data3Field = new TextField(data3Width);
	}

	// The "dataName" parameter is displayed for the user
	// If this is not specified, the field is not activated.
	if ((param = getParameter("data4Name")) != null) {
		data4Name = new Label(param);

		// The "dataURL" parameter holds the URL of the data source.
		if ((param = getParameter("data4URL")) != null) {
			data4URL = param;
		} 

		// The "dataWidth" parameter controls the width of the text field
		if ((param = getParameter("data4Width")) != null) {
			data4Width = Integer.parseInt(param);
		}
		data4Field = new TextField(data4Width);
	}
    }


    //
    // This function creates the layout and adds the data displays
    //
    private void createLayout() {
	GridBagLayout      gridbag     = new GridBagLayout();
	GridBagConstraints constraints = new GridBagConstraints();
	
	setLayout(gridbag);

	constraints.anchor = GridBagConstraints.WEST;
	constraints.weighty = 1.0;

	if (data0Name != null) {
		constraints.gridwidth = 1;
		constraints.fill = GridBagConstraints.NONE;
		constraints.weightx = 0.0;
		gridbag.setConstraints(data0Name, constraints);
		add(data0Name);
		constraints.gridwidth = GridBagConstraints.REMAINDER;
		constraints.weightx = 1.0;
		gridbag.setConstraints(data0Field, constraints);
		add(data0Field);
	}
	if (data1Name != null) {
		constraints.gridwidth = 1;
		constraints.fill = GridBagConstraints.NONE;
		constraints.weightx = 0.0;
		gridbag.setConstraints(data1Name, constraints);
		add(data1Name);
		constraints.gridwidth = GridBagConstraints.REMAINDER;
		constraints.weightx = 1.0;
		gridbag.setConstraints(data1Field, constraints);
		add(data1Field);
	}
	if (data2Name != null) {
		constraints.gridwidth = 1;
		constraints.fill = GridBagConstraints.NONE;
		constraints.weightx = 0.0;
		gridbag.setConstraints(data2Name, constraints);
		add(data2Name);
		constraints.gridwidth = GridBagConstraints.REMAINDER;
		constraints.weightx = 1.0;
		gridbag.setConstraints(data2Field, constraints);
		add(data2Field);
	}
	if (data3Name != null) {
		constraints.gridwidth = 1;
		constraints.fill = GridBagConstraints.NONE;
		constraints.weightx = 0.0;
		gridbag.setConstraints(data3Name, constraints);
		add(data3Name);
		constraints.gridwidth = GridBagConstraints.REMAINDER;
		constraints.weightx = 1.0;
		gridbag.setConstraints(data3Field, constraints);
		add(data3Field);
	}
	if (data4Name != null) {
		constraints.gridwidth = 1;
		constraints.fill = GridBagConstraints.NONE;
		constraints.weightx = 0.0;
		gridbag.setConstraints(data4Name, constraints);
		add(data4Name);
		constraints.gridwidth = GridBagConstraints.REMAINDER;
		constraints.weightx = 1.0;
		gridbag.setConstraints(data4Field, constraints);
		add(data4Field);
	}

	layout();
	repaint();
    }


    //
    // This function updates the data displays
    //
    private void updateFields() {
	    if (data0Name != null) {
          	data0Field.setText(readFromURL(data0URL));
	    }
	    if (data1Name != null) {
          	data1Field.setText(readFromURL(data1URL));
	    }
	    if (data2Name != null) {
          	data2Field.setText(readFromURL(data2URL));
	    }
	    if (data3Name != null) {
          	data3Field.setText(readFromURL(data3URL));
	    }
	    if (data4Name != null) {
          	data4Field.setText(readFromURL(data4URL));
	    }
    }


    //
    // This function opens a connection to a specified URL and
    // reads all data sent. The data is returned as a single string
    //
    private String readFromURL(String sourceURL) {
    	DataInputStream input;
	String line;
	String buffer = "";

	try {
		input = new DataInputStream(new URL(getDocumentBase(),sourceURL).openStream());
	} catch (java.io.IOException e) {
		return "Error opening " + sourceURL;
	}

	try {
		while ((line = input.readLine()) != null) {
		    buffer += line;
		}
	} catch (java.io.IOException e) {
		return "Error reading from " + sourceURL;
	}

	try {
		input.close();
	} catch (java.io.IOException e) {
		return "Error closing " + sourceURL;
	}

	return buffer;
    }

}
