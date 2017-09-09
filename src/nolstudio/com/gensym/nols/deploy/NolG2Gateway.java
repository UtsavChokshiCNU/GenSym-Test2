
/*
 * 
 * Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 * 
 * 
 */
package com.gensym.nols.deploy;

import java.io.File;
import java.util.Vector;

import javax.swing.JLayeredPane;

import com.gensym.DEBUG;
import com.gensym.classes.FloatArray;
import com.gensym.classes.IntegerArray;
import com.gensym.classes.modules.jgidemo.G2_EventSourceEvent;
import com.gensym.classes.modules.jgidemo.G2_EventSourceListener;
import com.gensym.core.DebugUtil;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2CommunicationErrorEvent;
import com.gensym.jgi.G2Connection;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.jgi.G2ConnectionHandlerFactory;
import com.gensym.jgi.G2ConnectionInfo;
import com.gensym.jgi.G2ConnectionListener;
import com.gensym.jgi.G2Gateway;
import com.gensym.math.MathException;
import com.gensym.math.datafit.ArchitectureParameters;
import com.gensym.math.datafit.EnsembleModel;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;
import com.gensym.nols.data.DataSeries;
import com.gensym.nols.data.NolAnnModel;
import com.gensym.nols.data.NolBpnModel;
import com.gensym.nols.data.NolModel2;
import com.gensym.nols.data.NolModelTrainThread;
import com.gensym.nols.data.NolPcaModel;
import com.gensym.nols.data.NolPlsModel;
import com.gensym.nols.data.NolRbfnModel;
import com.gensym.nols.data.NolRhoModel;
import com.gensym.nols.data.OnlineSensitivityThread;
import com.gensym.nols.data.Preprocessor;
import com.gensym.nols.data.Project2;
import com.gensym.nols.data.RawDataSource;
import com.gensym.nols.data.Variable;
import com.gensym.nols.data.ViewFilter;
import com.gensym.nols.main.IndependentDataManager;
import com.gensym.nols.main.NolMainFrame;
import com.gensym.nols.util.NolCmdLineArgHandler;
import com.gensym.nols.wksp.NolValidatePcaWKSP;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;

/**
 * Nol\G2 Gateway/Java Class to be used with nolstudio.kb.
 * To use:
 * <p>1. make sure nolstudio.kb is loaded and started, 
 * <p>2. run this class: java com.gensym.nols.deploy.NolG2Gateway
 */
public class NolG2Gateway implements G2ConnectionListener, G2_EventSourceListener {
	private G2Connection g2Connection = null;
	private static int instanceCount = 0;
	private NolMainFrame frame= null;
	private int connectionStatus;
	private String g2InterfaceName = "";	
	private IndependentDataManager dataManager;

	public static volatile NolG2Gateway g2Gateway;

  //symbols for catching exceptions in G2
  private static Symbol RETVAL_ = Symbol.intern("RETVAL");
  private static Symbol ERROR_ = Symbol.intern("ERROR");
  private static Symbol BACKTRACE_ = Symbol.intern("BACKTRACE");

	private boolean debugMode = false;
	private static final String G2INITFAILED = "G2_init_failed";
	private static final String G2CONNECTIONSTARTED = "G2_connection_started";
	private static final String G2CONNECTED = "G2_connected";
	private static final String G2CONNECTIONFAILED = "G2_connection_failed";
	private static final String G2CONNECTIONREFUSED = "G2_connection_refused";

/**
* Constructor for non-GUI nolstudio-g2 gateway
*/
	public NolG2Gateway(G2Connection connection){
		g2Gateway = this;
		instanceCount++;
		System.out.println("CREATED NolG2Gateway, count = "+instanceCount);
		this.g2Connection = connection;
		connection.addG2ConnectionListener(this);
		if (g2Connection == null) {
			System.out.println("No NolG2Gateway");
			connectionStatus = -1;
		}else{
			initializeCommonLocalRPCs(g2Connection);
		}
	}

/**
* Constructor for connecting nolstudio and g2
*/
	public NolG2Gateway(NolMainFrame frame, String args[]){
		g2Gateway = this;
		connectionStatus = -1;
		this.frame = frame;
		connect(args);
	}
		
	public void connect(String args[]){
// 1. Initialize the G2 Gateway Class
		NolCmdLineArgHandler cmdline = new NolCmdLineArgHandler(args);
		String listenerPort = cmdline.getOptionValue("-listenerport");
		if(listenerPort==null){
			listenerPort = "22044";
		}
		try {
			G2Gateway.initialize(new String[] {"-listenerport", listenerPort});
		
			// Set up a connection factory deal with unsolicited G2 connections
			G2Gateway.setConnectionHandlerFactory(new G2ConnectionHandlerFactory() {
				@Override
				public G2Connection createG2Connection(String connection_data){  
					G2Gateway new_gateway = new G2Gateway();
					return new_gateway;
				}
			});
		} catch (Throwable e) { 
			frame.showOKDialog(frame.getNolResourceString(G2INITFAILED));
			return;
		}

		G2Gateway.startup();
		frame.setProgressText(frame.getNolResourceString(G2CONNECTIONSTARTED));

		String host = cmdline.getOptionValue("-g2host");
		String port = cmdline.getOptionValue("-g2port");
		String interfacename  = cmdline.getOptionValue("-interfacename");
		g2InterfaceName =  interfacename;
		String interfaceclass  = cmdline.getOptionValue("-interfaceclass");
		if (port != null || host != null){
		//try to connect to a g2 if we are asked
			try {
				host = host == null ? "localhost" : host;
				port = port == null ? "1111" : port;
				interfaceclass = interfaceclass == null ? "NOLS-GATEWAY" : interfaceclass;
				interfacename = interfacename == null ? "NOLS-INTERFACE" : interfacename;
 				G2ConnectionInfo connectionInfo =
					new G2ConnectionInfo(null, "logical g2", host, port, null,
							interfaceclass, interfacename, "GSI", Boolean.FALSE, "machine1");
				g2Connection = G2Gateway.getOrMakeConnection(connectionInfo);
				g2Connection.addG2ConnectionListener(this);
				frame.setProgressText(frame.getNolResourceString(G2CONNECTED));
				connectionStatus = 1;

//				Symbol initNolstudioConnection =  Symbol.intern("NOLS-INITIATE-INTERFACE-SETTINGS");
//				g2Connection.callRPC(initNolstudioConnection, new Object[0],10000); 

			} catch (Exception e) { 
				frame.showOKDialog(frame.getNolResourceString(G2CONNECTIONREFUSED) + e.getMessage());
				frame.setProgressText(frame.getNolResourceString(G2CONNECTIONFAILED));
				connectionStatus = -1;
				return;
			}
		}
		instanceCount++;
		System.out.println("CREATED NolG2Gateway, count = "+instanceCount);
		if (g2Connection == null) {
			frame.setProgressText(frame.getNolResourceString(G2CONNECTIONFAILED));
			System.out.println("No NolG2Gateway");
			connectionStatus = -1;
		}else{
			initializeLocalRPCs(g2Connection);
			initializeCommonLocalRPCs(g2Connection);
		}
	}

/** */
	public void setDebug(boolean b){
		debugMode = b;
		if(debugMode){
			DEBUG.debugOutput = true;
			try {
			    DEBUG debugger = new DEBUG();
			    System.setErr(debugger); 
			    System.setOut(debugger);
			}
			catch (java.io.UnsupportedEncodingException ex) {
			    System.out.println("NolG2Gateway.setDebug(): Failed to create DEBUG, UnsupportedEncodingException: " + ex.toString());
			}
		}
	}


/** Return the status of g2gateway for the display in nolstudio.*/
	public int getConnectionStatus(){
		return connectionStatus;

	}

/** Return the inteface name in g2.*/
	public String getG2InterfaceName(){
		return g2InterfaceName;

	}

/**
   * Initialize all Local RPC's used by this subclass, this method is called only once
   * just before the first connection. 
*/

	public void initializeLocalRPCs(G2Connection con) {
    // Declare which Java methods and thier equivalent G2 RPC NAME,
    // in this class that can be called by the G2 connection	
		con.registerJavaMethod(this, "loadProject", Symbol.intern("NOLS-LOAD-PROJECT-IN-NOLSTUDIO"));
		con.registerJavaMethod(this, "addDataseries", Symbol.intern("NOLS-ADD-DATASERIES"));
		con.registerJavaMethod(this, "hasDataSeriesWithSameName",Symbol.intern("NOLS-HAS-DATASERIES-WITH-SAME-NAME"));
		con.registerJavaMethod(this, "showLineChart",Symbol.intern("NOLS-SHOW-LINE-CHART"));
		con.registerJavaMethod(this, "showProjectionChart",Symbol.intern("NOLS-SHOW-PROJECTION-CHART"));
		con.registerJavaMethod(this, "showXYChart",Symbol.intern("NOLS-SHOW-XY-CHART"));
		con.registerJavaMethod(this, "getRawDataSeriesNames",Symbol.intern("NOLS-GET-RAW-DATASERIES-NAMES-FROM-NOLSTUDIO"));
		con.registerJavaMethod(this, "getDataSeriesFullNames",Symbol.intern("NOLS-GET-DATASERIES-FULL-NAMES-FROM-NOLSTUDIO"));

		con.registerJavaMethod(this, "getPredictiveModelNames",Symbol.intern("NOLS-GET-NAME-LIST-OF-PREDICTIVE-MODELS"));
		con.registerJavaMethod(this, "getPredictiveModelParameters",Symbol.intern("NOLS-GET-PREDICTIVE-MODEL-PARAMETERS-FROM-NOLSTUDIO"));
		con.registerJavaMethod(this, "validatePredictiveModel",Symbol.intern("NOLS-VALIDATE-PREDICTIVE-MODEL-IN-NOLSTUDIO"));
		con.registerJavaMethod(this, "showPredictiveModelPrediction",Symbol.intern("NOLS-SHOW-PREDICTIVE-MODEL-PREDICTION-IN-NOLSTUDIO"));
		con.registerJavaMethod(this, "setPredictiveModelParameters",Symbol.intern("NOLS-SET-PREDICTIVE-MODEL-PARAMETERS-TO-NOLSTUDIO"));
		con.registerJavaMethod(this, "getPredictiveModelXMLParameters",Symbol.intern("NOLS-GET-PREDICTIVE-MODEL-XML-PARAMETERS-FROM-NOLSTUDIO"));

		con.registerJavaMethod(this, "getOptimizationNames",Symbol.intern("NOLS-GET-NAME-LIST-OF-OPTIMIZATIONS"));
		
		con.registerJavaMethod(this, "getBPNModelNames",Symbol.intern("NOLS-GET-NAME-LIST-OF-BPN-MODELS"));
		con.registerJavaMethod(this, "getBPNModelParameters",Symbol.intern("NOLS-GET-BPN-MODEL-PARAMETERS-FROM-NOLSTUDIO"));
		con.registerJavaMethod(this, "validateClassicModel",Symbol.intern("NOLS-VALIDATE-BPN-MODEL-IN-NOLSTUDIO"));
		con.registerJavaMethod(this, "showClassicModelPrediction",Symbol.intern("NOLS-SHOW-BPN-MODEL-PREDICTION-IN-NOLSTUDIO"));
		con.registerJavaMethod(this, "setBPNModelParameters",Symbol.intern("NOLS-SET-BPN-MODEL-PARAMETERS-TO-NOLSTUDIO"));

		con.registerJavaMethod(this, "getRBFNModelNames",Symbol.intern("NOLS-GET-NAME-LIST-OF-RBFN-MODELS"));
		con.registerJavaMethod(this, "getRBFNModelParameters",Symbol.intern("NOLS-GET-RBFN-MODEL-PARAMETERS-FROM-NOLSTUDIO"));
		con.registerJavaMethod(this, "showClassicModelPrediction",Symbol.intern("NOLS-SHOW-RBFN-MODEL-PREDICTION-IN-NOLSTUDIO"));
		con.registerJavaMethod(this, "validateClassicModel",Symbol.intern("NOLS-VALIDATE-RBFN-MODEL-IN-NOLSTUDIO"));
		con.registerJavaMethod(this, "setRBFNModelParameters",Symbol.intern("NOLS-SET-RBFN-MODEL-PARAMETERS-TO-NOLSTUDIO"));

		con.registerJavaMethod(this, "getAANModelNames",Symbol.intern("NOLS-GET-NAME-LIST-OF-AAN-MODELS"));
		con.registerJavaMethod(this, "getAANModelParameters",Symbol.intern("NOLS-GET-AAN-MODEL-PARAMETERS-FROM-NOLSTUDIO"));
		con.registerJavaMethod(this, "showClassicModelPrediction",Symbol.intern("NOLS-SHOW-AAN-MODEL-PREDICTION-IN-NOLSTUDIO"));
		con.registerJavaMethod(this, "validateAANModel",Symbol.intern("NOLS-VALIDATE-AAN-MODEL-IN-NOLSTUDIO"));
		con.registerJavaMethod(this, "setAANModelParameters",Symbol.intern("NOLS-SET-AAN-MODEL-PARAMETERS-TO-NOLSTUDIO"));
		
		con.registerJavaMethod(this, "getRHOModelNames",Symbol.intern("NOLS-GET-NAME-LIST-OF-RHO-MODELS"));
		con.registerJavaMethod(this, "getRHOModelParameters",Symbol.intern("NOLS-GET-RHO-MODEL-PARAMETERS-FROM-NOLSTUDIO"));
		con.registerJavaMethod(this, "showClassicModelPrediction",Symbol.intern("NOLS-SHOW-RHO-MODEL-PREDICTION-IN-NOLSTUDIO"));
		con.registerJavaMethod(this, "validateClassicModel",Symbol.intern("NOLS-VALIDATE-RHO-MODEL-IN-NOLSTUDIO"));
		con.registerJavaMethod(this, "setRHOModelParameters",Symbol.intern("NOLS-SET-RHO-MODEL-PARAMETERS-TO-NOLSTUDIO"));

		con.registerJavaMethod(this, "getPlsModelNames",Symbol.intern("NOLS-GET-NAME-LIST-OF-PLS-MODELS"));
		con.registerJavaMethod(this, "getPlsModelParameters",Symbol.intern("NOLS-GET-PLS-MODEL-PARAMETERS-FROM-NOLSTUDIO"));
		con.registerJavaMethod(this, "validatePlsModel",Symbol.intern("NOLS-VALIDATE-PLS-MODEL-IN-NOLSTUDIO"));
		con.registerJavaMethod(this, "showPlsModelPrediction",Symbol.intern("NOLS-SHOW-PLS-MODEL-PREDICTION-IN-NOLSTUDIO"));
	
		con.registerJavaMethod(this, "getPcaModelNames",Symbol.intern("NOLS-GET-NAME-LIST-OF-PCA-MODELS"));
		con.registerJavaMethod(this, "getPcaModelParameters",Symbol.intern("NOLS-GET-PCA-MODEL-PARAMETERS-FROM-NOLSTUDIO"));
		con.registerJavaMethod(this, "validatePcaModel",Symbol.intern("NOLS-VALIDATE-PCA-MODEL-IN-NOLSTUDIO"));
		con.registerJavaMethod(this, "getPcaModelData",Symbol.intern("NOLS-GET-PCA-DATA-FROM-NOLSTUDIO"));

		con.registerJavaMethod(this, "getDataSetFromStudio",Symbol.intern("GNNE-GET-DATA-SET-FROM-NOLSTUDIO"));
	
		con.registerJavaMethod(this, "saveProject", Symbol.intern("NOLS-SAVE-PROJECT-IN-NOLSTUDIO"));
	}

	public void initializeCommonLocalRPCs(G2Connection con) {
		con.registerJavaMethod(this, "shutdownGateway",Symbol.intern("NOLS-SHUTDOWN-REMOTE-PROCESS"));
		con.registerJavaMethod(this, "trainPredictiveModel",Symbol.intern("GNNE-TRAIN-PREDICTIVE-MODEL-ONLINE"));
		con.registerJavaMethod(this, "trainPredictiveModelFromFile",Symbol.intern("GNNE-TRAIN-PREDICTIVE-MODEL-FROM-FILE"));
		con.registerJavaMethod(this, "trainPredictiveModelFromFileWithXMLExport",Symbol.intern("GNNE-TRAIN-PREDICTIVE-MODEL-FROM-FILE-WITH-XML-EXPORT"));
		con.registerJavaMethod(this, "calculatePredictiveModelSensitivityFromFile",Symbol.intern("GNNE-CALCULATE-PREDICTIVE-MODEL-SENSITIVITY-FROM-FILE"));
	}


  // *****************************************************************
  // G2ConnectionListener implementations

/**
* This Method is called when the connected G2 has been paused .
*/
	@Override
	public void g2IsPaused(G2ConnectionEvent e)
	{
		System.out.println("G2 Has been paused");
	}

	/**
	* This method is called when the connected G2 has been resumed.
	*/
	@Override
	public void g2IsResumed(G2ConnectionEvent e)
	{
		System.out.println("G2 Has been resumed");
	}

	/**
	* This method is called when the connected G2 has been reset.
	*/
	@Override
	public void g2IsReset(G2ConnectionEvent e)
	{
		System.out.println("G2 Has been reset");
	}

	/**
	* This method is called when the connected G2 has been started.
	*/
	@Override
	public void g2IsStarted(G2ConnectionEvent e)
	{
		System.out.println("G2 Has been Started");

	}

	/**
	* Called when G2 sends a message to the G2Connection.
	*/
	@Override
	public void g2MessageReceived(G2ConnectionEvent e)
	{
		System.out.println("Message received from G2 was: " + e.getMessage());
	}

	/**
	* Called when an asynchronous error has occured in the G2 communications interface
	* for the G2Connection
	*
	*@param error_event An G2CommunicationErrorEvent describing the error that occured.
	*/
	@Override
	public void communicationError(G2CommunicationErrorEvent error_event)
	{
		System.out.println(error_event.getMessage());
	}

	/**
	* Called when the network cannot deliver data that Java is attempting to write to G2.
	*/
	@Override
	public void readBlockage(G2ConnectionEvent event) {}

	/**
	* Called when the network cannot deliver data that G2 is attempting to write to Java.
	*/
	@Override
	public void writeBlockage(G2ConnectionEvent event) {}

	/** 
	* This method is called when the G2 connection has been shutdown.
	* Must call super() here.  MK -WHY??
	*/
	@Override
	public void g2ConnectionClosed(G2ConnectionEvent e)
	{
		System.out.println("G2 Connection has been closed ");
		if (frame == null)
			System.exit(0);
		frame.disconnectedG2();
	}

	/** 
	* This method is called to close the G2 connection.
	*/
	public void closeG2Connection()	throws G2AccessException
	{
		if (g2Connection == null){
			return;
		}
		Symbol nolsCloseNolstudioConnection =  Symbol.intern("NOLS-CLOSE-NOLSTUDIO-CONNECTION");
		Object[] arg = new Object[1];
		arg[0] = Symbol.intern(g2InterfaceName);
		g2Connection.callRPC(nolsCloseNolstudioConnection, arg, 10000); 	
	}



/**
* A connection has been established between this connection and a G2 GSI-INTERFACE.
* This method is called, so the connection specific information can be set up.
* Specifically, declaring G2 methods and procedures that this connection would like to call.
* Note: G2 method and procedure declarations are connection specific.
*/
	@Override
	public void g2ConnectionInitialized(G2ConnectionEvent e) {    
		 System.out.println("Connected to G2 get back");

		String remote_process_string = e.getMessage();
		try {
		  System.out.println("Connected to G2 @" + g2Connection.g2GetHostName() + ":" + g2Connection.g2GetPortNumberOrName());

		} catch (G2AccessException E) { 
			System.out.println(E.toString()); 
		}
	}

// *****************************************************************
// To Implement G2_EventSourceListener exported from G2-EVENT-SOURCE-CLASS

/**
* To Implement G2_EventSourceListener exported from G2 Event 
* Generator class G2EventSourceClass.
*/
	@Override
	public void anEvent(G2_EventSourceEvent arg1) throws G2AccessException{
		System.out.println("Received an event from " + arg1.getSource() + "..." + arg1.getMessage());
	}
  

/** Get data series names from G2 for import selection.*/

	public Vector getDataSetNamesFromG2()throws G2AccessException {
		Vector dataNames = new Vector();
		Vector AMatrixNames = new Vector();
		Vector setNames = new Vector();

		Symbol getDataSetNames =  Symbol.intern("NOLS-GET-DATA-SET-NAMES");
		Object[] arg = new Object[1];
		arg[0] =  Symbol.intern("NOLS-MATRIX");
		Vector result = (Vector) g2Connection.callRPC(getDataSetNames, arg,10000); 
//System.out.println("NOLS-MATRIX result size=" + result.size());
		for(int i=0;i<result.size();i++){
//System.out.println("result=" + result.elementAt(i).toString());
			AMatrixNames.addElement(result.elementAt(i).toString());
		}
		getDataSetNames =  Symbol.intern("NOLS-GET-DATA-SET-NAMES");
		arg = new Object[1];
		arg[0] =  Symbol.intern("GNNE-DATA-SET");
		result = (Vector) g2Connection.callRPC(getDataSetNames, arg,10000); 
//System.out.println("GNNE-DATA-SET result size=" + result.size());
		for(int i=0;i<result.size();i++){
//System.out.println("result=" + result.elementAt(i).toString());
			setNames.addElement(result.elementAt(i).toString());
		}
		dataNames.addElement(AMatrixNames);
		dataNames.addElement(setNames);
		return 	dataNames;
	}


/** Get named data series names from G2 for export selection, the data series can be empty.*/

	public Vector getAllNamedDataSetNamesFromG2()throws G2AccessException {
		Vector dataNames = new Vector();
		Vector AMatrixNames = new Vector();
		Vector setNames = new Vector();

		Symbol getDataSetNames =  Symbol.intern("NOLS-GET-ALL-NAMED-DATA-SET-NAMES");
		Object[] arg = new Object[1];
		arg[0] =  Symbol.intern("NOLS-MATRIX");
		Vector result = (Vector) g2Connection.callRPC(getDataSetNames, arg,10000); 
		for(int i=0;i<result.size();i++){
			AMatrixNames.addElement(result.elementAt(i).toString());
		}
		getDataSetNames =  Symbol.intern("NOLS-GET-ALL-NAMED-DATA-SET-NAMES");
		arg = new Object[1];
		arg[0] =  Symbol.intern("GNNE-DATA-SET");
		result = (Vector) g2Connection.callRPC(getDataSetNames, arg,10000); 
		for(int i=0;i<result.size();i++){
			setNames.addElement(result.elementAt(i).toString());
		}
		dataNames.addElement(AMatrixNames);
		dataNames.addElement(setNames);
		return 	dataNames;
	}

/** Get data series names from G2 for export selection, the data series can be empty.*/

	public Vector getAllDataSetNamesFromG2()throws G2AccessException {
		Vector dataNames = new Vector();
		Vector AMatrixNames = new Vector();
		Vector setNames = new Vector();

		Symbol getDataSetNames =  Symbol.intern("NOLS-GET-ALL-DATA-SET-NAMES");
		Object[] arg = new Object[1];
		arg[0] =  Symbol.intern("NOLS-MATRIX");
		Vector result = (Vector) g2Connection.callRPC(getDataSetNames, arg,10000); 
//System.out.println("NOLS-MATRIX result size=" + result.size());
		for(int i=0;i<result.size();i++){
//System.out.println("result=" + result.elementAt(i).toString());
			AMatrixNames.addElement(result.elementAt(i).toString());
		}
		getDataSetNames =  Symbol.intern("NOLS-GET-ALL-DATA-SET-NAMES");
		arg = new Object[1];
		arg[0] =  Symbol.intern("GNNE-DATA-SET");
		result = (Vector) g2Connection.callRPC(getDataSetNames, arg,10000); 
//System.out.println("GNNE-DATA-SET result size=" + result.size());
		for(int i=0;i<result.size();i++){
//System.out.println("result=" + result.elementAt(i).toString());
			setNames.addElement(result.elementAt(i).toString());
		}
		dataNames.addElement(AMatrixNames);
		dataNames.addElement(setNames);
		return 	dataNames;
	}


/** Get data series from G2 by name and type.*/
	public void getDataSetFromG2(String type, String name, boolean isName)throws G2AccessException {
//System.out.println("getDataSetFromG2 type=" + type+"   name=" +name);

		if ("NOLS-MATRIX".equals(type)){
			Symbol getDataSet =  Symbol.intern("NOLS-GET-A-MATRIX");
			Object[] arg = new Object[2];
			arg[0] =  name;
			arg[1] = isName;
			Vector result = (Vector) g2Connection.callRPC(getDataSet, arg,10000); 
			if (!result.isEmpty())	
				addDataseriesAsVector(name,result);
		}else if ("GNNE-DATA-SET".equals(type)){
			Symbol getDataSet =  Symbol.intern("GNNE-GET-DATA-SET");
			Object[] arg = new Object[2];
			arg[0] =  name;
			arg[1] = isName;
			Vector result = (Vector)g2Connection.callRPC(getDataSet, arg,10000); 
			if (!result.isEmpty())	
				addDataseriesAsVector(name,result);
		}
	}

	public void addDataseriesAsVector(String dsName, Vector X) throws G2AccessException{
		int nrows = X.size();
		double[][] xx = new double[nrows][];
		for(int i=0;i<nrows;i++){
			FloatArray inputRows = (FloatArray)X.elementAt(i); 
			xx[i] = inputRows.getFloatArrayContents();
		}
		Matrix XTemp = Matlib.createMatrix(xx);
		DataSeries ds = new DataSeries(XTemp);
		ds.setName(dsName);
		frame.finishAddDataSeries(ds);
	}

/** RPC from G2 to add a matrix to nolstudio as raw data series. A flag is returned to indicate
	the success.*/

	public int addDataseries(String dsName, Sequence X) throws G2AccessException{
		int flag = 0;
//System.out.println("Received a data series with name = " + dsName);
		int nrows = X.size();
//System.out.println("nrows = "+nrows);

		Object[] inputRows = X.getContents();
		double[][] xx = new double[nrows][];
		for(int i=0;i<nrows;i++){
			xx[i] = ((FloatArray)inputRows[i]).getFloatArrayContents();
		}
		Matrix XTemp = Matlib.createMatrix(xx);
		DataSeries ds = new DataSeries(XTemp);
		ds.setName(dsName);
		frame.finishAddDataSeries(ds);
		return flag;
	}

/** RPC from G2 to test whether there is already a data series with the same given name.*/

	public boolean hasDataSeriesWithSameName(String dsName) throws G2AccessException{
		boolean flag = false;
		Project2 project = frame.getProject();
		if(project.getRawDataSource().getDataSeries(dsName) != null){
			flag = true;
		}
		return flag;
	}
	   
/** RPC from G2 to get all the raw dataseries names.*/

	public Sequence getRawDataSeriesNames(Sequence names) throws G2AccessException{
		Project2 project = frame.getProject();
		RawDataSource rds = project.getRawDataSource();
		int n = rds.getNumberOfDataSeries();
		names.removeAllElements();
		for(int i=0;i<n;i++){
			names.addElement(project.getName()+rds.getDataSeriesName(i));
		}
		return names;
	}
	   
/** RPC from G2 to get all the dataseries full names.*/

	public Sequence getDataSeriesFullNames(Sequence names) throws G2AccessException{
		Project2 project = frame.getProject();
		RawDataSource rds = project.getRawDataSource();
		int n = rds.getNumberOfDataSeries();
		names.removeAllElements();
		for(int i=0;i<n;i++){
			names.addElement("RawData."+rds.getDataSeriesName(i));
		}
		Vector preps = project.getPreprocessors();
		for(int i=0;i<preps.size();i++){
			Preprocessor prep = (Preprocessor)preps.elementAt(i);
			int m = prep.getNumberOfDataSeries();
			for(int j=0;j<m;j++){
				names.addElement(prep.getName()+"."+prep.getDataSeriesName(j));
			}
		}
		return names;
	}
	   
	
	private String createTempDSName(){
		Project2 project = frame.getProject();
		int c = 0;
		while (true) {
			if(project.getRawDataSource().getDataSeries("Temp"+c) == null){
				return "Temp"+c;
			}
			c = c+1;
		}
	}

	public int showLineChart(Sequence X) throws G2AccessException{
		int flag = 0;
		int nrows = X.size();
//System.out.println("nrows = "+nrows);
		Object[] inputRows = X.getContents();
		double[][] xx = new double[nrows][];
		for(int i=0;i<nrows;i++){
			xx[i] = ((FloatArray)inputRows[i]).getFloatArrayContents();
		}
		Matrix XTemp = Matlib.createMatrix(xx);
		DataSeries ds = new DataSeries(XTemp);
		Vector varObjs = ds.getVarObjects();
		ds.setName(createTempDSName());
		frame.finishAddDataSeries(ds);
		frame.lineChartActionPerformed(varObjs);
		return flag;
	}


	public int showProjectionChart(Sequence X) throws G2AccessException{
		int flag = 0;
		int nrows = X.size();
//System.out.println("nrows = "+nrows);
		Object[] inputRows = X.getContents();
		double[][] xx = new double[nrows][];
		for(int i=0;i<nrows;i++){
			xx[i] = ((FloatArray)inputRows[i]).getFloatArrayContents();
		}
		Matrix XTemp = Matlib.createMatrix(xx);
		DataSeries ds = new DataSeries(XTemp);
		Vector varObjs = ds.getVarObjects();
		ds.setName(createTempDSName());
		frame.finishAddDataSeries(ds);
		frame.projectmapActionPerformed(ds);
		return flag;
	}

	public int showXYChart(Sequence X) throws G2AccessException{
		int flag = 0;
		int nrows = X.size();
//System.out.println("nrows = "+nrows);
		Object[] inputRows = X.getContents();
		double[][] xx = new double[nrows][];
		for(int i=0;i<nrows;i++){
			xx[i] = ((FloatArray)inputRows[i]).getFloatArrayContents();
		}
		Matrix XTemp = Matlib.createMatrix(xx);
		DataSeries ds = new DataSeries(XTemp);
		Vector varObjs = ds.getVarObjects();
		ds.setName(createTempDSName());
		frame.finishAddDataSeries(ds);
		Variable varObj1 = (Variable)varObjs.elementAt(0);
		Variable varObj2 = (Variable)varObjs.elementAt(1);
		frame.xymapActionPerformed(varObj1,varObj2);
		return flag;
	}

/** RPC from G2 to get all the predictive model names.*/

	public Sequence getPredictiveModelNames(Sequence names) throws G2AccessException{
		Project2 project = frame.getProject();
		int n = project.getNumberOfPredictiveModels();
		names.removeAllElements();
		for(int i=0;i<n;i++){
			names.addElement(project.getPredictiveModel(i).getName());
		}
		return names;
	}

/** RPC from G2 to get all the optimziation names.*/

	public Sequence getOptimizationNames(Sequence names) throws G2AccessException{
		Project2 project = frame.getProject();
		int n = project.getNumberOfOptimizations();
		names.removeAllElements();
		for(int i=0;i<n;i++){
			names.addElement(project.getOptimization(i).getName());
		}
		return names;
	}

/** RPC from G2 to get a predictive model parameters from given name.*/

	public Object getPredictiveModelParameters(Sequence parameters, String mName) throws G2AccessException{
//System.out.println("getPredictiveModelParameters mName= "+mName);
		parameters.removeAllElements();
		Project2 project = frame.getProject();
		int index = project.getPredictiveModelIndexByName(mName);
		if (index == -1){
			return parameters;
		}
		NolModel2 model = project.getPredictiveModel(index);
 //System.out.println("getPredictiveModelParameters found model");
		try{
			Vector infors = model.getParametersVector();
			parameters.addAll(infors);
		}catch(Exception evt){}
		return parameters;
	}
	
/** RPC from G2 to set a predictive model parameters from given name.*/
	public Object setPredictiveModelParameters(Sequence parameters, String mName) throws G2AccessException{
		Project2 project = frame.getProject();
		int index = project.getPredictiveModelIndexByName(mName);
		if (index == -1){
			return parameters;
		}
		NolModel2 model = project.getPredictiveModel(index);
		Vector params = new Vector();
 //This is wrong implement.
/*		Object[] paramObj = parameters.getContents();
		params.addElement(paramObj[0]);
		params.addElement(((IntegerArray)paramObj[1]).getIntegerArrayContents());
		params.addElement(((IntegerArray)paramObj[2]).getIntegerArrayContents());
		for(int i=3;i<paramObj.length;i++){
			params.addElement(((FloatArray)paramObj[i]).getFloatArrayContents());
		}
		try{
			model.setParametersVector(params);
		}catch(Exception evt){}
*/		return parameters;
	}

	public int validatePredictiveModel(String mName, Sequence X, Sequence Y) throws G2AccessException,MathException{
		Project2 project = frame.getProject();
		int index = project.getPredictiveModelIndexByName(mName);
		if (index == -1){
			return 0;
		}
		NolModel2 model = project.getPredictiveModel(index);
		Vector validateDataSeries = getValidationDataSeries(model,X,Y);
		if(!validateDataSeries.isEmpty()) {
			frame.showModelValidationWKSPGivenDataseries(model, validateDataSeries);
		}else{
			return 0;
		}
		return 1;
	}
	
/** RPC from G2 to show a prediction vs actual chart.*/
	public int showPredictiveModelPrediction(String mName) throws G2AccessException{
		int flag = 0;
		Project2 project = frame.getProject();
		int index = project.getPredictiveModelIndexByName(mName);
		if (index == -1) {
			return flag;
		}
		NolModel2 model = project.getPredictiveModel(index);
		if(model.isAutoRecursiveModel()){
//System.out.println("show auto recursive wksp");
			frame.showRecursivePredVsActWKSP(model);
		}else{
			frame.showModelPredVsActWKSP(model);
		}
		return 1;
	}
	
/** RPC from G2 to get all the bpn model names.*/

	public Sequence getBPNModelNames(Sequence names) throws G2AccessException{
		Project2 project = frame.getProject();
		int n = project.getNumberOfBpnModels();
		names.removeAllElements();
		for(int i=0;i<n;i++){
			names.addElement(project.getBpnModel(i).getName());
		}
		return names;
	}
	

/** RPC from G2 to get all the rbfn model names.*/

	public Sequence getRBFNModelNames(Sequence names) throws G2AccessException{
		Project2 project = frame.getProject();
		int n = project.getNumberOfRbfnModels();
		names.removeAllElements();
		for(int i=0;i<n;i++){
			names.addElement(project.getRbfnModel(i).getName());
		}
		return names;
	}
	
/** RPC from G2 to get all the aan model names.*/

	public Sequence getAANModelNames(Sequence names) throws G2AccessException{
		Project2 project = frame.getProject();
		int n = project.getNumberOfAnnModels();
		names.removeAllElements();
		for(int i=0;i<n;i++){
			names.addElement(project.getAnnModel(i).getName());
		}
		return names;
	}
	

/** RPC from G2 to get all the rho model names.*/

	public Sequence getRHOModelNames(Sequence names) throws G2AccessException{
		Project2 project = frame.getProject();
		int n = project.getNumberOfRhoModels();
		names.removeAllElements();
		for(int i=0;i<n;i++){
			names.addElement(project.getRhoModel(i).getName());
		}
		return names;
	}
	
/** RPC from G2 to get all the pls model names.*/

	public Sequence getPlsModelNames(Sequence names) throws G2AccessException{
		Project2 project = frame.getProject();
		int n = project.getNumberOfPlsModels();
		names.removeAllElements();
		for(int i=0;i<n;i++){
			names.addElement(project.getPlsModel(i).getName());
		}
		return names;
	}
	
/** RPC from G2 to get all the pca model names.*/

	public Sequence getPcaModelNames(Sequence names) throws G2AccessException{
		Project2 project = frame.getProject();
		int n = project.getNumberOfPcaModels();
		names.removeAllElements();
		for(int i=0;i<n;i++){
			names.addElement(project.getPcaModel(i).getName());
		}
		return names;
	}
	

/** RPC from G2 to get a bpn model parameters from given name.*/

	public Object getBPNModelParameters(Sequence parameters, String mName) throws G2AccessException{
		parameters.removeAllElements();
		Project2 project = frame.getProject();
		int index = project.getBpnModelIndexByName(mName);
		if (index == -1){
			return parameters;
		}
		NolBpnModel model = project.getBpnModel(index);
		try{
			Vector infors = model.getParametersVector();
			parameters.addAll(infors);
		}catch(Exception evt){}
		return parameters;
	}
	
/** RPC from G2 to set a bpn model parameters with given name and parameter sequence.*/

	public Object setBPNModelParameters(Sequence parameters, String mName) throws G2AccessException{
		Project2 project = frame.getProject();
		int index = project.getBpnModelIndexByName(mName);
		if (index == -1) {
			return parameters;
		}
		NolBpnModel model = project.getBpnModel(index);
		Vector params = new Vector();

		Object[] paramObj = parameters.getContents();
		params.addElement(paramObj[0]);
		params.addElement(((IntegerArray)paramObj[1]).getIntegerArrayContents());
		params.addElement(((IntegerArray)paramObj[2]).getIntegerArrayContents());
		for(int i=3;i<paramObj.length;i++){
			params.addElement(((FloatArray)paramObj[i]).getFloatArrayContents());
		}
		try{
			model.setParametersVector(params);
		}catch(Exception evt){}
		return parameters;
	}
	
/** RPC from G2 to get a rbfn model parameters from given name.*/

	public Object getRBFNModelParameters(Sequence parameters, String mName) throws G2AccessException{
		parameters.removeAllElements();

		Project2 project = frame.getProject();
		int index = project.getRbfnModelIndexByName(mName);
		if (index == -1) {
			return parameters;
		}
		NolRbfnModel model = project.getRbfnModel(index);
		try{
			Vector infors = model.getParametersVector();
			parameters.addAll(infors);
		}catch(Exception evt){}
		return parameters;
	}
	
/** RPC from G2 to set a rbfn model parameters with given name and parameter sequence.*/

	public Object setRBFNModelParameters(Sequence parameters, String mName) throws G2AccessException{
		Project2 project = frame.getProject();
		int index = project.getRbfnModelIndexByName(mName);
		if (index == -1){
			return parameters;
		}
		NolRbfnModel model = project.getRbfnModel(index);
		Vector params = new Vector();
		Object[] paramObj = parameters.getContents();
		params.addElement(paramObj[0]);

		params.addElement(((IntegerArray)paramObj[1]).getIntegerArrayContents());
		params.addElement(paramObj[2]);
		params.addElement(paramObj[3]);

		for(int i=4;i<paramObj.length;i++){
			params.addElement(((FloatArray)paramObj[i]).getFloatArrayContents());
		}
		try{
			model.setParametersVector(params);
		}catch(Exception evt){}
		return parameters;
	}
	
/** RPC from G2 to get a aan model parameters from given name.*/

	public Object getAANModelParameters(Sequence parameters, String mName) throws G2AccessException{
		parameters.removeAllElements();

		Project2 project = frame.getProject();
		int index = project.getAnnModelIndexByName(mName);
		if (index == -1) {
			return parameters;
		}
		NolAnnModel model = project.getAnnModel(index);
		try{
			Vector infors = model.getParametersVector();
			parameters.addAll(infors);
		}catch(Exception evt){}
		return parameters;
	}
	
/** RPC from G2 to set a aan model parameters with given name and parameter sequence.*/

	public Object setAANModelParameters(Sequence parameters, String mName) throws G2AccessException{
		Project2 project = frame.getProject();
		int index = project.getAnnModelIndexByName(mName);
		if (index == -1) {
			return parameters;
		}
		NolAnnModel model = project.getAnnModel(index);
		Vector params = new Vector();

		Object[] paramObj = parameters.getContents();
		params.addElement(paramObj[0]);
		params.addElement(((IntegerArray)paramObj[1]).getIntegerArrayContents());
		params.addElement(((IntegerArray)paramObj[2]).getIntegerArrayContents());
		for(int i=3;i<paramObj.length-1;i++){
			params.addElement(((FloatArray)paramObj[i]).getFloatArrayContents());
		}
		params.addElement(paramObj[paramObj.length-1]);
		try{
			model.setParametersVector(params);
		}catch(Exception evt){}
		return parameters;
	}

/** RPC from G2 to get a rho model parameters from given name.*/

	public Object getRHOModelParameters(Sequence parameters, String mName) throws G2AccessException{
		parameters.removeAllElements();

		Project2 project = frame.getProject();
		int index = project.getRhoModelIndexByName(mName);
		if (index == -1) {
			return parameters;
		}
		NolRhoModel model = project.getRhoModel(index);
		try{
			Vector infors = model.getParametersVector();
			parameters.addAll(infors);
		}catch(Exception evt){}
		return parameters;
	}

/** RPC from G2 to set a aan model parameters with given name and parameter sequence.*/
	public Object setRHOModelParameters(Sequence parameters, String mName) throws G2AccessException{
		Project2 project = frame.getProject();
		int index = project.getRhoModelIndexByName(mName);
		if (index == -1) {
			return parameters;
		}
		NolRhoModel model = project.getRhoModel(index);
		Vector params = new Vector();
		Object[] paramObj = parameters.getContents();
		params.addElement(paramObj[0]);

		params.addElement(((IntegerArray)paramObj[1]).getIntegerArrayContents());
		params.addElement(paramObj[2]);
		params.addElement(paramObj[3]);

		for(int i=4;i<paramObj.length;i++){
			params.addElement(((FloatArray)paramObj[i]).getFloatArrayContents());
		}
		try{
			model.setParametersVector(params);
		}catch(Exception evt){}
		return parameters;
	}

/** RPC from G2 to get a Pls model parameters from given name.*/

	public Object getPlsModelParameters(Sequence parameters, String mName) throws G2AccessException{
		parameters.removeAllElements();
//System.out.println("name="+mName);
		Project2 project = frame.getProject();
		int index = project.getPlsModelIndexByName(mName);
//System.out.println("index="+index);
		if (index == -1) {
			return parameters;
		}
		NolPlsModel model = project.getPlsModel(index);
//System.out.println("get model");
		try{
			Vector infors = model.getParametersVector();
			parameters.addAll(infors);
		}catch(Exception evt){
			System.out.println("evt="+evt.getMessage());
		}
		return parameters;
	}


/** RPC from G2 to get a Pca model parameters from given name.*/

	public Object getPcaModelParameters(Sequence parameters, String mName) throws G2AccessException{
		parameters.removeAllElements();

		Project2 project = frame.getProject();
		int index = project.getPcaModelIndexByName(mName);
		if (index == -1){
			return parameters;
		}
		NolPcaModel model = project.getPcaModel(index);
		try{
			Vector infors = model.getParametersVector();
			parameters.addAll(infors);
		}catch(Exception evt){}
		return parameters;
	}

/** RPC from G2 to get a Pca model data from given name.*/

	public Object getPcaModelData(Sequence parameters, String mName) throws G2AccessException{
		parameters.removeAllElements();

		Project2 project = frame.getProject();
		int index = project.getPcaModelIndexByName(mName);
		if (index == -1){
			return parameters;
		}
		NolPcaModel model = project.getPcaModel(index);
		try{
			Vector infors = model.getDataVector();
			parameters.addAll(infors);
		}catch(Exception evt){}
		return parameters;
	}




/** RPC from G2 to show a prediction vs actual chart.*/
	public int showClassicModelPrediction(String mName) throws G2AccessException{
		Project2 project = frame.getProject();
		NolModel2 model = getClassicModelFromName(mName);
		if (model == null ){
			return 0;
		}
		frame.showClassicModelPredVsActWKSP(model);
		return 1;
	}

/** RPC from G2 to show a prediction vs actual chart.*/
	public int showPlsModelPrediction(String mName) throws G2AccessException{
		Project2 project = frame.getProject();
		int index = project.getPlsModelIndexByName(mName);
		if (index != -1){
			NolPlsModel model = project.getPlsModel(index);
			if (model == null ){
				return 0;
			}
			frame.showClassicModelPredVsActWKSP(model);
			return 1;
		}
		return 0;
	}


/** RPC from G2 to validate a classic model given the input and output data.*/
	public int validateClassicModel(String mName, Sequence X, Sequence Y) throws G2AccessException,MathException{
		Project2 project = frame.getProject();
		NolModel2 model = getClassicModelFromName(mName);
		if (model == null ){
			return 0;
		}
		Vector validateDataSeries = getValidationDataSeries(model,X,Y);
		if(!validateDataSeries.isEmpty()) {
			frame.showModelValidationWKSPGivenDataseries(model, validateDataSeries);
		}else{
			return 0;
		}
		return 1;
	}
	
/** RPC from G2 to validate a autoassociative model given the variable samples.*/
	public int validateAANModel(String mName, Sequence X) throws G2AccessException,MathException{
		Project2 project = frame.getProject();
		NolModel2 model = getClassicModelFromName(mName);
// System.out.println("getClassicModelFromName ="+model);
		if (model == null ){
			return 0;
		}
		Vector validateDataSeries = getValidationDataSeries((NolAnnModel)model,X);
// System.out.println("validateDataSeries.size() ="+validateDataSeries.size());
		if(!validateDataSeries.isEmpty()) {
			frame.showModelValidationWKSPGivenDataseries(model, validateDataSeries);
		}else{
			return 0;
		}
		return 1;
	}

/** RPC from G2 to validate a pls model given the input and output data.*/
	public int validatePlsModel(String mName, Sequence X, Sequence Y) throws G2AccessException,MathException{
		Project2 project = frame.getProject();
		int index = project.getPlsModelIndexByName(mName);
		if (index != -1){
			NolPlsModel model = project.getPlsModel(index);
			if (model == null ){
				return 0;
			}
			Vector validateDataSeries = getValidationDataSeries(model,X,Y);
			if(!validateDataSeries.isEmpty()) {
				frame.showModelValidationWKSPGivenDataseries(model, validateDataSeries);
			}else{
				return 0;
			}
			return 1;
		}
		return 0;
	}
	
/** RPC from G2 to validate a Pca model given the variable samples.*/
	public int validatePcaModel(String mName, Sequence X) throws G2AccessException,MathException{
		Project2 project = frame.getProject();
		int index = project.getPcaModelIndexByName(mName);
		if (index != -1){
			NolPcaModel model = project.getPcaModel(index);
			if (model == null ){
				return 0;
			}
			DataSeries ds = getValidationDataSeries(model,X);
			try{
				NolValidatePcaWKSP activeInternalFrame = new NolValidatePcaWKSP(frame,model,ds);
				activeInternalFrame.setClosable(true);
				activeInternalFrame.setMaximizable(false);
				activeInternalFrame.setIconifiable(true);
				activeInternalFrame.setResizable(true);
				frame.getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER);
				activeInternalFrame.setBounds(50, 10, 640,440);
				try { 
					activeInternalFrame.setSelected(true); 
				} catch (java.beans.PropertyVetoException e2) {
					System.err.println("Non-Fatal exception: " + e2.getMessage());
					e2.printStackTrace();		
				}
				frame.getEditor().moveToFront(activeInternalFrame);
				activeInternalFrame.setBounds(50, 10, 660,480);
				activeInternalFrame.validate();
				frame.addWindowMenuItem(activeInternalFrame);
			}catch(MathException evt){
				System.out.println("evt="+evt.getMessage());		
			}
			return 1;
		}
		return 0;
	}
	

	private NolModel2 getClassicModelFromName(String mName){
		Project2 project = frame.getProject();
		int index = project.getBpnModelIndexByName(mName);
		if (index != -1){
			NolModel2 model = project.getBpnModel(index);
			return model;
		}
		index = project.getRbfnModelIndexByName(mName);
		if (index != -1){
			NolModel2 model = project.getRbfnModel(index);
			return model;
		}
		index = project.getAnnModelIndexByName(mName);
		if (index != -1){
			NolModel2 model = project.getAnnModel(index);
			return model;
		}

		index = project.getRhoModelIndexByName(mName);
		if (index != -1){
			NolModel2 model = project.getRhoModel(index);
			return model;
		}
		return null;

	}

	private Vector getValidationDataSeries(NolAnnModel model, Sequence X)throws G2AccessException,MathException{
		Vector validateDataSeries = new Vector();
		int nio = model.getMaximumInputs();
		int nrowsx = X.size();
		if(nrowsx <= 0 ){
			return validateDataSeries;
		}

		Object[] inputRowsX = X.getContents();
		double[][] xx = new double[nrowsx][];
		int col = 0;
		for(int i=0;i<nrowsx;i++){
			double[] x1 = ((FloatArray)inputRowsX[i]).getFloatArrayContents();
			col = x1.length;
			if (nio > col){
				return validateDataSeries;
			}
			double[] xy = new double[col];
			for (int j=0;j<col;j++){
				xy[j] = x1[j];
			}
			xx[i] = xy;
		}
		Matrix XTemp = Matlib.createMatrix(xx);
		DataSeries ds = new DataSeries(XTemp);
		Vector ins = model.getInputs();
		Vector inputVarNames = new Vector();
		for(int i=0;i<ins.size();i++){
			inputVarNames.addElement(ins.elementAt(i));
		}
		Preprocessor prep = model.getPreprocessor();
		Vector originalVarNames = prep.getOriginalVarNames(inputVarNames);		
		for(int i=0;i<originalVarNames.size();i++){
			String varName = (String)originalVarNames.elementAt(i);
			Variable varObj = prep.getVariableFromVariableName(varName);
			ds.setVariableParameters(i, varObj.getTag(), varObj.getName(),varObj.getUnit());
		}
		if (model.getHasTimeStamps()) {
			String varName = (String)originalVarNames.elementAt(0);
			Variable varObj = prep.getVariableFromVariableName(varName);
			DataSeries ods = varObj.getDataSeries();
			long[] timeStamps = ods.getTimeStamps();
			long interv = timeStamps[0];
			if(timeStamps.length>1){
				interv = (timeStamps[timeStamps.length-1]-timeStamps[0])/(timeStamps.length-1);
			}
			long[] newTimeStamps = new long[nrowsx]; 
			for(int i=0;i<nrowsx;i++){
				newTimeStamps[i] = timeStamps[0] + interv*i;	
			}
			ds.setTimeStamps(newTimeStamps);
		}
		validateDataSeries.addElement(ds);
		ds.setName(createTempDSName());
		frame.finishAddDataSeries(ds);
		return validateDataSeries;
	}

	private DataSeries getValidationDataSeries(NolPcaModel model, Sequence X)throws G2AccessException,MathException{
		int nio = model.getNin();
		int nrowsx = X.size();
		if(nrowsx <= 0 ){
			throw new MathException("The data size is zero.");
		}

		Object[] inputRowsX = X.getContents();
		double[][] xx = new double[nrowsx][];
		int col = 0;
		for(int i=0;i<nrowsx;i++){
			double[] x1 = ((FloatArray)inputRowsX[i]).getFloatArrayContents();
			col = x1.length;
			if (nio > col){
				throw new MathException("The number of column of data is less than the model input number.");
			}
			double[] xy = new double[col];
			for (int j=0;j<col;j++){
				xy[j] = x1[j];
			}
			xx[i] = xy;
		}
		Matrix XTemp = Matlib.createMatrix(xx);
		DataSeries ds = new DataSeries(XTemp);
		Vector ins = model.getInputs();
		Vector inputVarNames = new Vector();
		for(int i=0;i<ins.size();i++){
			inputVarNames.addElement(ins.elementAt(i));
		}
		Preprocessor prep = model.getPreprocessor();
		for(int i=0;i<inputVarNames.size();i++){
			String varName = (String)inputVarNames.elementAt(i);
			Variable varObj = prep.getVariableFromVariableName(varName);
			ds.setVariableParameters(i, varObj.getTag(), varObj.getName(),varObj.getUnit());
		}
		ds.setName(createTempDSName());
		frame.finishAddDataSeries(ds);
		return ds;
	}


	private Vector getValidationDataSeries(NolModel2 model, Sequence X, Sequence Y)throws G2AccessException,MathException{
		Vector validateDataSeries = new Vector();
		int nio = model.getMaximumInputs()+model.getNumberOfOutputs(0);
		int nrowsx = X.size();
		int nrowsy = Y.size();
		if (nrowsx != nrowsy){
			return validateDataSeries ;
		}
		if(nrowsx <= 0 ){
			return validateDataSeries;
		}

		Object[] inputRowsX = X.getContents();
		Object[] inputRowsY= Y.getContents();
		double[][] xx = new double[nrowsx][];
		int col = 0;
		for(int i=0;i<nrowsx;i++){
			double[] x1 = ((FloatArray)inputRowsX[i]).getFloatArrayContents();
			double[] y1 = ((FloatArray)inputRowsY[i]).getFloatArrayContents();
			col = x1.length + y1.length;
			if (nio > col){
				return validateDataSeries;
			}
			double[] xy = new double[col];
			for (int j=0;j<x1.length;j++){
				xy[j] = x1[j];
			}
			for (int j=0;j<y1.length;j++){
				xy[x1.length+j] = y1[j];
			}
			xx[i] = xy;
		}
		Matrix XTemp = Matlib.createMatrix(xx);
		DataSeries ds = new DataSeries(XTemp);
		Vector ins = model.getInputs();
		Vector outs = model.getOutputs();
		Vector inputVarNames = new Vector();
		for(int i=0;i<ins.size();i++){
			inputVarNames.addElement(ins.elementAt(i));
		}
		for(int i=0;i<outs.size();i++){
			inputVarNames.addElement(outs.elementAt(i));
		}
		Preprocessor prep = model.getPreprocessor();
		Vector originalVarNames = prep.getOriginalVarNames(inputVarNames);		
		for(int i=0;i<originalVarNames.size();i++){
			String varName = (String)originalVarNames.elementAt(i);
			Variable varObj = prep.getVariableFromVariableName(varName);
			ds.setVariableParameters(i, varObj.getTag(), varObj.getName(),varObj.getUnit());
		}
		if (model.getHasTimeStamps()) {
			String varName = (String)originalVarNames.elementAt(0);
			Variable varObj = prep.getVariableFromVariableName(varName);
			DataSeries ods = varObj.getDataSeries();
			long[] timeStamps = ods.getTimeStamps();
			long interv = timeStamps[0];
			if(timeStamps.length>1){
				interv = (timeStamps[timeStamps.length-1]-timeStamps[0])/(timeStamps.length-1);
			}
			long[] newTimeStamps = new long[nrowsx]; 
			for(int i=0;i<nrowsx;i++){
				newTimeStamps[i] = timeStamps[0] + interv*i;	
			}
			ds.setTimeStamps(newTimeStamps);
		}
		validateDataSeries.addElement(ds);
		ds.setName(createTempDSName());
		frame.finishAddDataSeries(ds);
		return validateDataSeries;
	}
	
/** RPC from G2 to load a certain project file. A flag is returned to indicate
	the success.*/

	public int loadProject(String pjPath, String pjName) throws G2AccessException{
		int flag = 0;
		File dirFile = new File(pjPath);
		if(dirFile.isDirectory()) { 
			frame.setProjectDirectory(pjPath);
			frame.openProjectActionPerformed(pjName);
			flag = 1;
		}
		return flag;
	}

/** RPC from G2 to save a certain project file. A flag is returned to indicate
	the success.*/

	public int saveProject(String pjPath, String pjName) throws G2AccessException{
		int flag = 0;
		File dirFile = new File(pjPath);
		if(dirFile.isDirectory()) { 
			frame.setProjectDirectory(pjPath);
			frame.saveProjectActionPerformed(pjName);
			flag = 1;
		}
		return flag;
	}

// *********** Main ******************************************************
/**
* Main method
*/
	public static void main(String args[]) {

	// 1. Initialize the G2 Gateway Class
		NolCmdLineArgHandler cmdline = new NolCmdLineArgHandler(args);
		String listenerPort = cmdline.getOptionValue("-listenerport");
		if(listenerPort==null){
			listenerPort = "22044";
		}
		try {
			G2Gateway.initialize(new String[] {"-listenerport", listenerPort});
		}catch (Exception E) { System.out.println(E.toString());}

		try {
		// Set up a connection factory deal with unsolicited G2 connections
			G2Gateway.setConnectionHandlerFactory(new G2ConnectionHandlerFactory() {
				@Override
				public G2Connection createG2Connection(String connection_data){  
					G2Gateway new_gateway = new G2Gateway();
					NolG2Gateway egw = new NolG2Gateway(new_gateway);
					return new_gateway;
				}
			});
		} catch (Error e) { 
			System.out.println("Caught error"); 
		}

		G2Gateway.startup();
		System.out.println("NolG2Gateway...started...waiting...");

		String host = cmdline.getOptionValue("-g2host");
		String port = cmdline.getOptionValue("-g2port");
		String interfacename  = cmdline.getOptionValue("-interfacename");
		String interfaceclass  = cmdline.getOptionValue("-interfaceclass");
		if (port != null || host != null){
		//try to connect to a g2 if we are asked
			try {
				host = host == null ? "localhost" : host;
				port = port == null ? "1111" : port;
				interfaceclass = interfaceclass == null ? "NOLS-GATEWAY" : interfaceclass;
				interfacename = interfacename == null ? "NOLS-INTERFACE" : interfacename;
 				G2ConnectionInfo connectionInfo =
					new G2ConnectionInfo(null, "logical g2", host, port, null,
							interfaceclass, interfacename, "GSI", Boolean.FALSE, "NOLRPIS");
				G2Connection g2_connection = G2Gateway.getOrMakeConnection(connectionInfo);
				NolG2Gateway egw = new NolG2Gateway(g2_connection);
				//g2_connection.returnMessage("Connected to NolG2Gateway \n Hi There from G2Gateway Java VM, how are you G2 ?");
				System.out.println("Connected to G2 OK");			

/*				String debug = cmdline.getOptionValue("-debug");
				if (debug != null){
					if (debug.equals("true")){
						egw.setDebug(true);
					}else{
						egw.setDebug(false);
					}
				}
  */
				//Set default as non-debug mode.
				egw.setDebug(false);
			} catch (Exception E) { 
				System.out.println(E.toString()); 
			}
		}
	}

	public void clear(){
		g2Connection = null;
		frame = null;
		dataManager = null;
		g2InterfaceName = "";
		connectionStatus = -1;
	}

	/** RPC from G2: shutdown (this) gateway Java process */
	public int shutdownGateway() throws G2AccessException {
		// Postpone exit, so that we can return the result via RPC
		new Thread("RPC shutdown") {
			@Override
			public void run() {
				try {
					Thread.sleep(1000);
				}
				catch (InterruptedException e) {
					// just need to "declare the catch" to silence the compiler
				}
				System.exit(0);
			}
		}.start();
		return 1;
	}

	
/** Export the data series to g2 as nols-matrix.*/

	public void exportDataMatrixToG2(DataSeries ds, String type, String dsName,boolean isName)throws G2AccessException, MathException {
		Symbol getDataSequence =  Symbol.intern("NOLS-GET-A-DATA-SEQUENCE");
		Object[] arg = new Object[0];
		Sequence dataSqs= (Sequence) g2Connection.callRPC(getDataSequence, arg,1000);
		dataSqs.removeAllElements();
		double[][] data = ds.getFiniteData();
		for (int i=0;i<data.length;i++){
			double[] x = data[i];
			dataSqs.addElement(x);
		}		
		Symbol getDataMatrix =  Symbol.intern("NOLS-EXPORT-DATA-SERIES-MATRIX");
		arg = new Object[3];
		arg[0] =  dsName;
		arg[1] =  isName;
		arg[2] =  dataSqs;
		g2Connection.callRPC(getDataMatrix, arg,10000); 
	}

/** Export the data series to g2 as gnne-data-set.*/

	public void exportDataSetToG2(DataSeries ds, String dsName,boolean isName, Vector usedNames, Vector outputNames)throws G2AccessException, MathException {
		Symbol getDataSequence =  Symbol.intern("NOLS-GET-A-DATA-SEQUENCE");
		Object[] arg = new Object[0];
		Sequence inputSq = (Sequence) g2Connection.callRPC(getDataSequence, arg,1000);
		Sequence outputSq = (Sequence) g2Connection.callRPC(getDataSequence, arg,1000);

		inputSq.removeAllElements();
		outputSq.removeAllElements();
		Vector varObjects = ds.getVarObjects();
		Matrix data = ds.getDataMatrix();
		int cols = varObjects.size();
		Matrix inB = Matlib.zeros(1,cols);
		Matrix outB = Matlib.zeros(1,cols);
		for (int i=0;i<cols;i++){
			String varName = varObjects.elementAt(i).toString();
			if (usedNames.contains(varName)){
				if(outputNames.contains(varName)){
					outB.set(i,1.0);
				}else{
					inB.set(i,1.0);
				}
			}
		}
		Matrix inD = Matlib.createMatrix();
		Matrix outD = Matlib.createMatrix();
		Matrix B = Matlib.createMatrix();
		Matrix validData = Matlib.createMatrix();
		Matlib.findFiniteRows(data,B);
		Matlib.getRows(data,B,validData);
		int rr = validData.getRows();
		int counter = 0;
		double[] newTimeStamps = new double[rr];
		if(ds.getHasTimeStamps()){
			long[] timeStamps = ds.getTimeStamps();
			for (int i=0;i<data.getRows();i++){
				if(B.get(i) > 0 ) {
					newTimeStamps[counter] = timeStamps[i] / 1000.0;
					counter = counter + 1;
				}
			}
		}else{
			for (int i=0;i<rr;i++){
				newTimeStamps[i] = 10000d + i * 10;
			}
		}
		Matlib.getColumns(validData,outB, outD);
		Matlib.getColumns(validData,inB, inD);

		Matlib.clear(validData);
		Matlib.clear(B);
		Matlib.clear(outB);
		Matlib.clear(inB);

		double[][] dd = Matlib.create2DArray(inD);
		for (int i=0;i<dd.length;i++){
			double[] x = dd[i];
			inputSq.addElement(x);
		}		
		dd = Matlib.create2DArray(outD);
		for (int i=0;i<dd.length;i++){
			double[] x = dd[i];
			outputSq.addElement(x);
		}	
		Matlib.clear(inD);
		Matlib.clear(outD);
		Symbol sendDataSet =  Symbol.intern("GNNE-GET-DATA-SERIES-FROM-NOLSTUDIO");
		arg = new Object[5];
		arg[0] =  dsName;
		arg[1] =  isName;
		arg[2] =  inputSq;
		arg[3] =  outputSq;
		arg[4] =  newTimeStamps;
		g2Connection.callRPC(sendDataSet, arg,10000); 
	}

	public Sequence getDataSetFromStudio(String name)throws G2AccessException, MathException {
		Symbol getDataSequence =  Symbol.intern("NOLS-GET-A-DATA-SEQUENCE");
		Object[] arg = new Object[0];
		Sequence inputSq = (Sequence) g2Connection.callRPC(getDataSequence, arg,1000);
		Sequence outputSq = (Sequence) g2Connection.callRPC(getDataSequence, arg,1000);
		Sequence timeSq = (Sequence) g2Connection.callRPC(getDataSequence, arg,1000);
		Sequence results = (Sequence) g2Connection.callRPC(getDataSequence, arg,1000);

		
		Project2 project = frame.getProject();
		RawDataSource rds = project.getRawDataSource();
		int n = rds.getNumberOfDataSeries();
		boolean found = false;
		DataSeries ds = new DataSeries();
		for(int i=0;i<n;i++){
			String newName = "RawData."+rds.getDataSeriesName(i);
			if(newName.equals(name)){
				ds =rds.getDataSeries(i);
				found = true;
				break;
			}
		}
		if (!found){
			Vector preps = project.getPreprocessors();
			for(int i=0;i<preps.size();i++){
				Preprocessor prep = (Preprocessor)preps.elementAt(i);
				int m = prep.getNumberOfDataSeries();
				for(int j=0;j<m;j++){
					String newName = prep.getName()+"."+prep.getDataSeriesName(j);
					if(newName.equals(name)){
						ds =prep.getDataSeries(j);
						found = true;
						break;
					}
				}
				if(found){
					break;
				}
			}
		}
		if (!found){
			return results;
		}
		frame.toFront();
		Vector[] varSelect = frame.classifyInputOutput(ds);
		if (varSelect.length != 2 ){
			return results;
		}
		Vector usedNames = varSelect[0]; 
		Vector outputNames = varSelect[1]; 

		inputSq.removeAllElements();
		outputSq.removeAllElements();
		timeSq.removeAllElements();
		results.removeAllElements();
		Vector varObjects = ds.getVarObjects();
		
		
		Matrix data = ds.getDataMatrix();
		int cols = varObjects.size();
		Matrix inB = Matlib.zeros(1,cols);
		Matrix outB = Matlib.zeros(1,cols);
		for (int i=0;i<cols;i++){
			String varName = varObjects.elementAt(i).toString();
			if (usedNames.contains(varName)){
				if(outputNames.contains(varName)){
					outB.set(i,1.0);
				}else{
					inB.set(i,1.0);
				}
			}
		}
		Matrix inD = Matlib.createMatrix();
		Matrix outD = Matlib.createMatrix();
		Matrix B = Matlib.createMatrix();
		Matrix validData = Matlib.createMatrix();
		Matlib.findFiniteRows(data,B);
		Matlib.getRows(data,B,validData);
		int rr = validData.getRows();
		if(ds.getHasTimeStamps()){
			long[] timeStamps = ds.getTimeStamps();
			for (int i=0;i<data.getRows();i++){
				if(B.get(i) > 0 ) {
					timeSq.addElement(timeStamps[i] / 1000.0);
				}
			}
		}else{
			for (int i=0;i<rr;i++){
				timeSq.addElement(10000 + i * 10d);
			}
		}
		Matlib.getColumns(validData,outB, outD);
		Matlib.getColumns(validData,inB, inD);

		Matlib.clear(validData);
		Matlib.clear(B);
		Matlib.clear(outB);
		Matlib.clear(inB);

		double[][] dd = Matlib.create2DArray(inD);
		for (int i=0;i<dd.length;i++){
			double[] x = dd[i];
			inputSq.addElement(x);
		}		
		dd = Matlib.create2DArray(outD);
		for (int i=0;i<dd.length;i++){
			double[] x = dd[i];
			outputSq.addElement(x);
		}	
		Matlib.clear(inD);
		Matlib.clear(outD);
		
		results.addElement(inputSq);
		results.addElement(outputSq);
		results.addElement(timeSq);
		return results;
	}

/** inform that the model training has been complete.*/

	public void informG2TrainingComplete(String uuid, boolean isComplete)throws G2AccessException {
		Symbol informG2 =  Symbol.intern("NOLS-MODEL-TRAINING-COMPLETE");
		Object[] arg = new Object[2];
		arg[0] =  uuid;
		arg[1] =  isComplete;
		g2Connection.callRPC(informG2, arg,10000); 
	}

/** inform that error occur to the model object.*/

	public void informG2ErrorOccur(String uuid, boolean hasError, String errorMessage)throws G2AccessException {
		Symbol informG2 =  Symbol.intern("GNNE-MODEL-HAS-ERROR");
		Object[] arg = new Object[3];
		arg[0] =  uuid;
		arg[1] =  hasError;
		arg[2] =  errorMessage;
		g2Connection.callRPC(informG2, arg,10000); 
	}

	public Sequence getDataSequence()throws G2AccessException{
		Symbol getDataSequence =  Symbol.intern("NOLS-GET-A-DATA-SEQUENCE");
		Object[] arg = new Object[0];
		Sequence dataSqs= (Sequence) g2Connection.callRPC(getDataSequence, arg,1000);
		return dataSqs;
	}


	/** RPC from G2 to get a predictive model parameters in xml format from given name.*/

	public Object getPredictiveModelXMLParameters(Sequence parameters, String mName) throws G2AccessException{
//System.out.println("getPredictiveModelXMLParameters= mName"+mName);
		parameters.removeAllElements();
		Project2 project = frame.getProject();
		int index = project.getPredictiveModelIndexByName(mName);
		if (index == -1){
			return parameters;
		}
		NolModel2 model = project.getPredictiveModel(index);
		if(!model.isTrained()){
			return parameters;
		}
		try{
			Vector infors = model.getWholeParametersVector();
			parameters.addAll(infors);
		}catch(Exception evt){
			System.out.println("evt="+evt.getMessage());
		}
		return parameters;
	}	

/** Retrain the predictive model.*/
	public Structure trainPredictiveModel(final String uuid, final Sequence input, final Sequence output, 
			final double timeInMinute, final boolean autoStop, final boolean newTraining, final boolean display)
	{
		double minutes = timeInMinute;
		Structure retval = new Structure();
//System.out.println("trainPredictiveModel=");
		try{
			int nrows = input.size();
			if(nrows != output.size()){
				MathException e = new MathException("Input and Output don't have the same number of samples.");
				throw e;
			}
			if(nrows <10){
				MathException e = new MathException("There is not enough data for training.");
				throw e;
			}
			Object[] inputRows = input.getContents();
			Object[] outputRows = output.getContents();
			double[][] x = new double[nrows][];
			double[][] y = new double[nrows][];
			for(int i=0;i<nrows;i++){
				x[i] = ((FloatArray)inputRows[i]).getFloatArrayContents();
				y[i] = ((FloatArray)outputRows[i]).getFloatArrayContents();
			}

			Matrix X = Matlib.createMatrix(x);
			Matrix Y = Matlib.createMatrix(y);


			double[] validTest = Matlib.hasConstantColumns(X);
			if(validTest.length > 0){
				String s = "[";
				for(int i=0;i<validTest.length;i++){
					s = s + validTest[i]+" ";
				}
				s = s + "]";
				MathException e = new MathException("Using un-changing data "+s+" for training.");
				throw e;
			}
			boolean validTestB = Matlib.hasNaN(X);
			if(validTestB){
				MathException e = new MathException("Using infinite number for training.");
				throw e;
			}
			validTestB = Matlib.hasNaN(Y);
			if(validTestB){
				MathException e = new MathException("Using infinite number for training.");
				throw e;
			}

//			Vector listener = new Vector();
//			listener.addElement(new OnlineModelListener(processor));
//			listener.addElement(new OnlineModelListener(this));
			if (Double.compare(minutes, 0.0) == 0 ) 
				minutes = 1;
			double timeInMilli = (minutes*60000.0);
			int inputCols = X.getCols();
			int nout = Y.getCols();
			EnsembleModel ensemble = new EnsembleModel(new ArchitectureParameters(inputCols,nout,0,0));
			ensemble.setTrainingTime((long)timeInMilli);  
			ensemble.useAutomaticStopping(autoStop);
			ensemble.removeAllListeners();

//			ensemble.addListener(this);
			NolModelTrainThread trainerThread = new NolModelTrainThread(ensemble);
			Thread trainingthread = new Thread(trainerThread);
			int prior = trainingthread.getPriority()-3;
			if(prior <Thread.MIN_PRIORITY){
				prior = Thread.MIN_PRIORITY;
			}
			trainingthread.setPriority(prior);
			trainerThread.setInput1(X);
			trainerThread.setOutput1(Y);
			OnlineModelListener onlineModelListener = new OnlineModelListener(uuid, this, display);
			ensemble.addListener(onlineModelListener);
			if(display){
				NolOnlineSimpleConsoleFrame console = onlineModelListener.getSimpleOnlineConsole();
				ensemble.addListener(console);
				console.setModel1TrainInput(X);
				console.setModel1TrainOutput(Y);
				console.setOutputModelTrainingThread(trainingthread);
				console.setBounds(100,100,750,500);
				console.setReady(false);
				console.setVisible(true);
				console.toFront();	
			}
			trainingthread.start();
		} catch (Exception ie){
			ie.printStackTrace();
			String errorMessage = ie.getMessage();
			if (errorMessage == null ){
				errorMessage = "Exception During Training.";
			}
			retval.setAttributeValue(ERROR_, new String(errorMessage));
			retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace(ie)));
			try{
				informG2ErrorOccur(uuid, true, errorMessage);
			}catch(Exception e){}
		}
		return retval;
	}

/** Retrain the predictive model using data from files.*/
	public Structure trainPredictiveModelFromFile(final Sequence modelParams, final Sequence dataSeriesFileNames, 
			final double timeInMinute, final boolean autoStop, final boolean newTraining, final boolean display)
	{
		double minutes = timeInMinute;
		Structure retval = new Structure();
if(DEBUG.debugOutput) {
	System.out.println("start trainPredictiveModelFromFile modelParams.size="+modelParams.size());
}
		String uuid = modelParams.elementAt(0).toString(); 
		try{
			if (modelParams.size() < 7 ){ 
				throw new MathException("Wrong model parameters");
			} 
			String modelName = modelParams.elementAt(1).toString();
			boolean isTimeBased = Boolean.parseBoolean(modelParams.elementAt(3).toString());
if(DEBUG.debugOutput) {
	System.out.println("Model is time based ="+isTimeBased);
}
			int inputCols = Integer.parseInt(modelParams.elementAt(4).toString());
			int nout = Integer.parseInt(modelParams.elementAt(5).toString());
if(DEBUG.debugOutput) {
	System.out.println("Model number of input ="+inputCols);
}
if(DEBUG.debugOutput) {
	System.out.println("Model number of output ="+nout);
}
			Sequence variables = (Sequence)modelParams.elementAt(6);
			Vector outs = new Vector();
			Vector ins = new Vector();
			Vector outDelays = new Vector();
			Vector inDelays = new Vector();
			for(int i=0;i<variables.size();i++){
				Structure variable = (Structure)variables.elementAt(i);
				String varName = (String)variable.getAttributeValue(Symbol.intern("VARIABLE-NAME"));
				Sequence nodes = (Sequence)variable.getAttributeValue(Symbol.intern("NODES"));
				Vector delays = new Vector();
				boolean isOutput = false;
				for(int j=0;j<nodes.size();j++){
					Structure node = (Structure)nodes.elementAt(j);
					String classification = node.getAttributeValue(Symbol.intern("CLASSIFICATION")).toString();
					try{
						Object d = node.getAttributeValue(Symbol.intern("DELAY"));
						delays.addElement(d);
					}catch (NoSuchAttributeException evt){
					}catch (RuntimeException evt){}

					if (classification.equals("output")) {
						outs.addElement(varName);
						isOutput = true;
					}else if(classification.equals("input")) {
						if ((!isOutput) && (!ins.contains(varName))){
							ins.addElement(varName);
							isOutput = false;
						}
					}	
				}
				if(isOutput){
					if(delays.isEmpty()){
						outDelays.addElement(new long[0]);
					}else{
						long[] dls = new long[delays.size()];
						for(int k=0;k<dls.length;k++){
							dls[k] = Double.valueOf(delays.elementAt(k).toString()).longValue();
						}						
						outDelays.addElement(dls);
					}
				}else{
					if(delays.isEmpty()){
						inDelays.addElement(new long[1]);
					}else{
						long[] dls = new long[delays.size()];
						for(int k=0;k<dls.length;k++){
							dls[k] = Double.valueOf(delays.elementAt(k).toString()).longValue();
						}						
						inDelays.addElement(dls);
					}
				}
			}
if(DEBUG.debugOutput) {
	System.out.println("Finished converting variables");
}

			Vector retraindataSeries = new Vector();
			Vector varObjs = new Vector();
			Project2 project = new Project2("tempTrainingProject");
			for(int i=0;i<dataSeriesFileNames.size();i++){
				String dsFileName = dataSeriesFileNames.elementAt(i).toString();
				DataSeries ds = new DataSeries();
if(DEBUG.debugOutput) {
	System.out.println("loading dataseries name ="+dsFileName);
}
				ds.Load(dsFileName, 0);
				Vector vars = ds.getVarObjects();
				varObjs.addAll(vars);
				project.addDataSeries(ds);
				retraindataSeries.addElement(ds);
			}
			Preprocessor preprocessor = new Preprocessor("tempTrainingPreprocessor", project, varObjs, new ViewFilter());
			EnsembleModel ensemble = new EnsembleModel(new ArchitectureParameters(inputCols,nout,0,0));
if(DEBUG.debugOutput) {
	System.out.println("Setting up the model for training.");
}


			boolean infiniteData = false;
			boolean unchangingData = false;
			for(int i=0;i<outs.size();i++){
				String varName = outs.elementAt(i).toString();
				Variable varObj = preprocessor.getVariableFromVariableName(varName);
				if (varObj == null) {
					throw new MathException("Data Series Does not contains output variable:"+varName);
				}
				double[] stat = varObj.getStatistics();
				if (Double.isNaN(stat[6]) || Double.isInfinite(stat[6])) {
					infiniteData = true;
				}
				if(stat[6] < 1.0e-20 ) {
					unchangingData = true;
				}
			}
			if(infiniteData) {
				throw new MathException("Using infinite number for training");
			}
			if(unchangingData) {
				throw new MathException("Using un-changing data for training");
			}
			for(int i=0;i<ins.size();i++){
				String varName = ins.elementAt(i).toString();
if(DEBUG.debugOutput) {
	System.out.println("varName=."+varName);
}
				Variable varObj = preprocessor.getVariableFromVariableName(varName);
				if (varObj == null) {
					throw new MathException("Data Series Does not contains input variable:"+varName);
				}
				double[] stat = varObj.getStatistics();
				if (Double.isNaN(stat[6]) || Double.isInfinite(stat[6])) {
					infiniteData = true;
				}
				if(stat[6] < 1.0e-20 ) {
					unchangingData = true;
				}
			}
			if(infiniteData) {
				throw new MathException("Using infinite number for training");
			}
			if(unchangingData) {
				throw new MathException("Using un-changing data for training");
			}
			NolModel2 model = new NolModel2(ensemble,modelName,outs,ins,outDelays,inDelays, preprocessor);
			model.setHasTimeStamps(isTimeBased);

			Matrix X = Matlib.createMatrix();
			Matrix Y = Matlib.createMatrix();
if(DEBUG.debugOutput) {
	System.out.println("Prepare data matrix for training.");
}
			model.prepareTrainingSetFromDataSeries(retraindataSeries,X,Y);

			
			if (Double.compare(minutes, 0.0) == 0 ) 
				minutes = 1;
			double timeInMilli = (minutes*60000.0);
			ensemble.setTrainingTime((long)timeInMilli);  
			ensemble.useAutomaticStopping(autoStop);
			ensemble.removeAllListeners();

			NolModelTrainThread trainerThread = new NolModelTrainThread(ensemble);
			Thread trainingthread = new Thread(trainerThread);
			int prior = trainingthread.getPriority()-3;
			if(prior <Thread.MIN_PRIORITY){
				prior = Thread.MIN_PRIORITY;
			}
			trainingthread.setPriority(prior);
			trainerThread.setInput1(X);
			trainerThread.setOutput1(Y);
			OnlineModelListener onlineModelListener = new OnlineModelListener(uuid, this, model, display);
			ensemble.addListener(onlineModelListener);
if(DEBUG.debugOutput) {
	System.out.println("Launching training thread.");
}
			if(display){
				NolOnlineSimpleConsoleFrame console = onlineModelListener.getSimpleOnlineConsole();
				ensemble.addListener(console);
				console.setModel1TrainInput(X);
				console.setModel1TrainOutput(Y);
				console.setModel(model);
				console.setOutputModelTrainingThread(trainingthread);
				console.setBounds(100,100,750,500);
				console.setReady(false);
				console.setVisible(true);
				console.toFront();	
			}
			trainingthread.start();
		} catch (MathException ie){
			handleTrainPredictiveModelException(retval, uuid, ie);
		} catch (NoSuchAttributeException ie){
			handleTrainPredictiveModelException(retval, uuid, ie);
		} catch (RuntimeException ie){
			handleTrainPredictiveModelException(retval, uuid, ie);
		}
		
		return retval;
	}
	
	/**
	 * 
	 * @param retval
	 * @param uuid
	 * @param ie
	 */
	private void handleTrainPredictiveModelException(Structure retval, String uuid, Exception ie){
		String errorMessage = ie.getMessage();
		if (errorMessage == null ){
			errorMessage = "Exception During Training.";
		}
		if(DEBUG.debugOutput) { 
			System.out.println("Error String ="+ie.toString());
			System.out.println("Error Message ="+errorMessage);
		}
		
		try{
			informG2ErrorOccur(uuid, true, errorMessage);
		} catch(G2AccessException e){
		} catch(RuntimeException e){}
		if(DEBUG.debugOutput) 
			System.out.println("Finish sending error message back to G2.");
		retval.setAttributeValue(ERROR_, new String(errorMessage));
		retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace(ie)));
	}

/** inform that the model training has been complete.*/

	public void informG2TrainingComplete(String uuid, boolean isComplete, Vector params)throws G2AccessException {
if(DEBUG.debugOutput) {
	System.out.println("informG2TrainingComplete uuid = "+uuid);	
}
		Symbol getDataSequence =  Symbol.intern("NOLS-GET-A-DATA-SEQUENCE");
		Object[] arg = new Object[0];
		Sequence paramSqs= (Sequence) g2Connection.callRPC(getDataSequence, arg,1000);
		paramSqs.removeAllElements();
		paramSqs.addAll(params);

		Symbol informG2 =  Symbol.intern("GNNE-MODEL-TRAINING-COMPLETE");
		arg = new Object[3];
		arg[0] =  uuid;
		arg[1] =  isComplete;
		arg[2] =  paramSqs;
		g2Connection.callRPC(informG2, arg,10000); 
	}

/** inform that the model training has been complete.*/

	public void informG2SimpleTrainingComplete(String uuid, boolean isComplete, Vector params)throws G2AccessException {
		Symbol getDataSequence =  Symbol.intern("NOLS-GET-A-DATA-SEQUENCE");
		Object[] arg = new Object[0];
		Sequence paramSqs= (Sequence) g2Connection.callRPC(getDataSequence, arg,1000);
		paramSqs.removeAllElements();
		paramSqs.addAll(params);

		Symbol informG2 =  Symbol.intern("GNNE-SIMPLE-MODEL-TRAINING-COMPLETE");
		arg = new Object[3];
		arg[0] =  uuid;
		arg[1] =  isComplete;
		arg[2] =  paramSqs;
		g2Connection.callRPC(informG2, arg,10000); 
	}
/** Retrain the predictive model using data from files.*/
	public Structure trainPredictiveModelFromFileWithXMLExport(final Sequence modelParams, final Sequence dataSeriesFileNames, 
			final double timeInMinute, final boolean autoStop, final boolean newTraining, final boolean display, final String xmlFilePath)
	{
		double minutes = timeInMinute;
		Structure retval = new Structure();
		System.out.println("trainPredictiveModelFromFile modelParams.size="+modelParams.size());
		String uuid = modelParams.elementAt(0).toString(); 

		try{
			if (modelParams.size() < 7 ){ 
				throw new MathException("Wrong model parameters");
			} 
			String modelName = modelParams.elementAt(1).toString();
			int inputCols = Integer.parseInt(modelParams.elementAt(4).toString());
			int nout = Integer.parseInt(modelParams.elementAt(5).toString());
			Sequence variables = (Sequence)modelParams.elementAt(6);
			Vector outs = new Vector();
			Vector ins = new Vector();
			Vector outDelays = new Vector();
			Vector inDelays = new Vector();
			for(int i=0;i<variables.size();i++){
				Structure variable = (Structure)variables.elementAt(i);
				String varName = (String)variable.getAttributeValue(Symbol.intern("VARIABLE-NAME"));
//System.out.println("varName  ="+varName);
				Sequence nodes = (Sequence)variable.getAttributeValue(Symbol.intern("NODES"));
				Vector delays = new Vector();
				boolean isOutput = false;
				for(int j=0;j<nodes.size();j++){
					Structure node = (Structure)nodes.elementAt(j);
					String classification = node.getAttributeValue(Symbol.intern("CLASSIFICATION")).toString();
					try{
						Object d = node.getAttributeValue(Symbol.intern("DELAY"));
						delays.addElement(d);
					} catch (NoSuchAttributeException evt){
					} catch (RuntimeException evt){}

					if (classification.equals("output")) {
						outs.addElement(varName);
						isOutput = true;
					}else if(classification.equals("input")) {
						if ((!isOutput) && (!ins.contains(varName))){
							ins.addElement(varName);
							isOutput = false;
						}
					}	
				}
				if(isOutput){
					if(delays.isEmpty()){
						outDelays.addElement(new long[0]);
					}else{
						long[] dls = new long[delays.size()];
						for(int k=0;k<dls.length;k++){
							dls[k] = Long.parseLong(delays.elementAt(k).toString());
						}						
						outDelays.addElement(dls);
					}
				}else{
					if(delays.isEmpty()){
						inDelays.addElement(new long[1]);
					}else{
						long[] dls = new long[delays.size()];
						for(int k=0;k<dls.length;k++){
							dls[k] = Long.parseLong(delays.elementAt(k).toString());
						}						
						inDelays.addElement(dls);
					}
				}
//System.out.println("delays.size()  ="+delays.size());
			}
//System.out.println("outDelays.size()  ="+outDelays.size());
//System.out.println("inDelays.size()  ="+inDelays.size());

			Vector retraindataSeries = new Vector();
			Vector varObjs = new Vector();
			Project2 project = new Project2("tempTrainingProject");

			for(int i=0;i<dataSeriesFileNames.size();i++){
				String dsFileName = dataSeriesFileNames.elementAt(i).toString();
				DataSeries ds = new DataSeries();
				ds.Load(dsFileName, 0);
				Vector vars = ds.getVarObjects();
				varObjs.addAll(vars);
				project.addDataSeries(ds);
				retraindataSeries.addElement(ds);
			}
			Preprocessor preprocessor = new Preprocessor("tempTrainingPreprocessor", project, varObjs, new ViewFilter());
			EnsembleModel ensemble = new EnsembleModel(new ArchitectureParameters(inputCols,nout,0,0));
			NolModel2 model = new NolModel2(ensemble,modelName,outs,ins,outDelays,inDelays, preprocessor);


			Matrix X = Matlib.createMatrix();
			Matrix Y = Matlib.createMatrix();
			model.prepareTrainingSetFromDataSeries(retraindataSeries,X,Y);

			
			if (Double.compare(minutes, 0.0) == 0 ) 
				minutes = 1;
			double timeInMilli = (minutes*60000.0);
			ensemble.setTrainingTime((long)timeInMilli);  
			ensemble.useAutomaticStopping(autoStop);
			ensemble.removeAllListeners();

			NolModelTrainThread trainerThread = new NolModelTrainThread(ensemble);
			Thread trainingthread = new Thread(trainerThread);
			int prior = trainingthread.getPriority()-3;
			if(prior <Thread.MIN_PRIORITY){
				prior = Thread.MIN_PRIORITY;
			}
			trainingthread.setPriority(prior);
			trainerThread.setInput1(X);
			trainerThread.setOutput1(Y);
			OnlineModelListener onlineModelListener = new OnlineModelListener(uuid, this, model, display);
			onlineModelListener.setXmlFilePath(xmlFilePath);
			ensemble.addListener(onlineModelListener);
			if(display){
				NolOnlineSimpleConsoleFrame console = onlineModelListener.getSimpleOnlineConsole();
				ensemble.addListener(console);
				console.setModel1TrainInput(X);
				console.setModel1TrainOutput(Y);
				console.setOutputModelTrainingThread(trainingthread);
				console.setBounds(100,100,750,500);
				console.setReady(false);
				console.setVisible(true);
				console.toFront();	
			}
			trainingthread.start();
		} catch (MathException ie){
			handletrainPredictiveModelXMLExcpetion(retval, uuid, ie);
		} catch (NoSuchAttributeException ie){
			handletrainPredictiveModelXMLExcpetion(retval, uuid, ie);
		} catch (RuntimeException ie){
			handletrainPredictiveModelXMLExcpetion(retval, uuid, ie);
		}
		return retval;
	}

	/**
	 * 
	 * @param retval
	 * @param uuid
	 * @param ie
	 */
	private void handletrainPredictiveModelXMLExcpetion(Structure retval, String uuid, Exception ie){
		ie.printStackTrace();
		String errorMessage = ie.getMessage();
		if (errorMessage == null ){
			errorMessage = "Exception During Training.";
		}
		retval.setAttributeValue(ERROR_, new String(errorMessage));
		retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace(ie)));
		try{
			informG2ErrorOccur(uuid, true, errorMessage);
		}catch(G2AccessException e){
		}catch(RuntimeException e){}
	}


/** calculate the predictive model sensitivity using data from files.*/
	public Structure calculatePredictiveModelSensitivityFromFile(Sequence modelParams, Sequence dataSeriesFileNames)
	{
		Structure retval = new Structure();
if(DEBUG.debugOutput) {
	System.out.println("start calculatePredictiveModelSensitivityFromFile modelParams.size="+modelParams.size());
}
		String uuid = modelParams.elementAt(0).toString(); 
		try{
			if (modelParams.size() < 8 ){ 
				throw new MathException("Wrong model parameters");
			} 
			String modelName = modelParams.elementAt(1).toString();
			boolean isTimeBased = Boolean.parseBoolean(modelParams.elementAt(3).toString());
if(DEBUG.debugOutput) {
	System.out.println("Model is time based ="+isTimeBased);
}
			int inputCols = Integer.parseInt(modelParams.elementAt(4).toString());
			int nout = Integer.parseInt(modelParams.elementAt(5).toString());
if(DEBUG.debugOutput) {
	System.out.println("Model number of input ="+inputCols);
}
if(DEBUG.debugOutput) {
	System.out.println("Model number of output ="+nout);
}
			Sequence variables = (Sequence)modelParams.elementAt(6);
			Sequence ensembleSqs = (Sequence)modelParams.elementAt(7);
			Vector outs = new Vector();
			Vector ins = new Vector();
			Vector outDelays = new Vector();
			Vector inDelays = new Vector();
			for(int i=0;i<variables.size();i++){
				Structure variable = (Structure)variables.elementAt(i);
				String varName = (String)variable.getAttributeValue(Symbol.intern("VARIABLE-NAME"));
				Sequence nodes = (Sequence)variable.getAttributeValue(Symbol.intern("NODES"));
				Vector delays = new Vector();
				boolean isOutput = false;
				for(int j=0;j<nodes.size();j++){
					Structure node = (Structure)nodes.elementAt(j);
					String classification = node.getAttributeValue(Symbol.intern("CLASSIFICATION")).toString();
					try{
						Object d = node.getAttributeValue(Symbol.intern("DELAY"));
						delays.addElement(d);
					}catch (NoSuchAttributeException evt){
					}catch (RuntimeException evt){}

					if (classification.equals("output")) {
						outs.addElement(varName);
						isOutput = true;
					}else if(classification.equals("input")) {
						if ((!isOutput) && (!ins.contains(varName))){
							ins.addElement(varName);
							isOutput = false;
						}
					}	
				}
				if(isOutput){
					if(delays.isEmpty()){
						outDelays.addElement(new long[0]);
					}else{
						long[] dls = new long[delays.size()];
						for(int k=0;k<dls.length;k++){
							dls[k] = Double.valueOf(delays.elementAt(k).toString()).longValue();
						}						
						outDelays.addElement(dls);
					}
				}else{
					if(delays.isEmpty()){
						inDelays.addElement(new long[1]);
					}else{
						long[] dls = new long[delays.size()];
						for(int k=0;k<dls.length;k++){
							dls[k] = Double.valueOf(delays.elementAt(k).toString()).longValue();
						}						
						inDelays.addElement(dls);
					}
				}
			}
if(DEBUG.debugOutput) {
	System.out.println("Finished converting variables");
}

			Vector calculatingDataSeries = new Vector();
			Vector varObjs = new Vector();
			Project2 project = new Project2("tempCalculateSensitivityProject");
			for(int i=0;i<dataSeriesFileNames.size();i++){
				String dsFileName = dataSeriesFileNames.elementAt(i).toString();
				DataSeries ds = new DataSeries();
if(DEBUG.debugOutput) {
	System.out.println("loading dataseries name ="+dsFileName);
}
				ds.Load(dsFileName, 0);
				Vector vars = ds.getVarObjects();
				varObjs.addAll(vars);
				project.addDataSeries(ds);
				calculatingDataSeries.addElement(ds);
			}
			Preprocessor preprocessor = new Preprocessor("tempTrainingPreprocessor", project, varObjs, new ViewFilter());
			EnsembleModel ensemble = new EnsembleModel(new ArchitectureParameters(inputCols,nout,0,0));
if(DEBUG.debugOutput) {
	System.out.println("Setting up the model for training.");
}
			Object[] paramObj = ensembleSqs.getContents();
			Vector params = new Vector();
			for(int i=0;i<paramObj.length;i++){
				params.addElement(paramObj[i]);
			}
			ensemble.setParametersVector(params);
if(DEBUG.debugOutput) {
	System.out.println("Finish Setting up the ensemble model for training.");
}

			boolean infiniteData = false;
			boolean unchangingData = false;
			for(int i=0;i<outs.size();i++){
				String varName = outs.elementAt(i).toString();
				Variable varObj = preprocessor.getVariableFromVariableName(varName);
				if (varObj == null) {
					throw new MathException("Data Series Does not contains output variable:"+varName);
				}
				double[] stat = varObj.getStatistics();
				if (Double.isNaN(stat[6]) || Double.isInfinite(stat[6])) {
					infiniteData = true;
				}
				if(stat[6] < 1.0e-20 ) {
					unchangingData = true;
				}
			}
			if(infiniteData) {
				throw new MathException("Using infinite number for training");
			}
			if(unchangingData) {
				throw new MathException("Using un-changing data for training");
			}
			for(int i=0;i<ins.size();i++){
				String varName = ins.elementAt(i).toString();
if(DEBUG.debugOutput) {
	System.out.println("varName=."+varName);
}
				Variable varObj = preprocessor.getVariableFromVariableName(varName);
				if (varObj == null) {
					throw new MathException("Data Series Does not contains input variable:"+varName);
				}
				double[] stat = varObj.getStatistics();
				if (Double.isNaN(stat[6]) || Double.isInfinite(stat[6])) {
					infiniteData = true;
				}
				if(stat[6] < 1.0e-20 ) {
					unchangingData = true;
				}
			}
			if(infiniteData) {
				throw new MathException("Using infinite number for calculation");
			}
			if(unchangingData) {
				throw new MathException("Using un-changing data for calculation");
			}
			NolModel2 model = new NolModel2(ensemble,modelName,outs,ins,outDelays,inDelays, preprocessor);
			model.setHasTimeStamps(isTimeBased);


			int ni = ins.size();
			int no = outs.size();
			Matrix signedSensitivityValues = Matlib.createMatrix(ni,no);
			for(int c=0;c<no;c++){
				for(int r=0;r<ni;r++){
					signedSensitivityValues.set(r,c,Double.NaN);
				}
			}
			OnlineSensitivityThread senThread = new OnlineSensitivityThread(uuid, this, model, 
				signedSensitivityValues, ins, calculatingDataSeries);
			Thread thread = new Thread(senThread);
			int prior = thread.getPriority()-3;
			if(prior <Thread.MIN_PRIORITY) {
				prior = Thread.MIN_PRIORITY;
			}
			thread.setPriority(prior);
			thread.start();
		} catch (MathException ie){
			handleCalcPredictiveModelSensitivityException(retval, uuid, ie);
		} catch (NoSuchAttributeException ie){
			handleCalcPredictiveModelSensitivityException(retval, uuid, ie);
		} catch (RuntimeException ie){
			handleCalcPredictiveModelSensitivityException(retval, uuid, ie);
		}
		return retval;
	}
	
	/**
	 * 
	 * @param retval
	 * @param uuid
	 * @param ie
	 */
	private void handleCalcPredictiveModelSensitivityException(Structure retval, String uuid, Exception ie) {
		String errorMessage = ie.getMessage();
		if (errorMessage == null ){
			errorMessage = "Exception During Sensitivity Calculation.";
		}
		if(DEBUG.debugOutput) {
			System.out.println("Error String ="+ie.toString());
			System.out.println("Error Message ="+errorMessage);
		}
		
		try{
			informG2ErrorOccur(uuid, true, errorMessage);
		} catch(G2AccessException e){
		} catch(RuntimeException e){}
		
		if(DEBUG.debugOutput) 
			System.out.println("Finish sending error message back to G2.");
		retval.setAttributeValue(ERROR_, new String(errorMessage));
		retval.setAttributeValue(BACKTRACE_, new String(DebugUtil.getStackTrace(ie)));
	}

/** inform that the model training has been complete.*/
	public void endSensitivityCalculation(String uuid, Matrix signedSensitivityValues)throws G2AccessException {
if(DEBUG.debugOutput) {
	System.out.println("endSensitivityCalculation uuid = "+uuid);	
}
		Symbol getDataSequence =  Symbol.intern("NOLS-GET-A-DATA-SEQUENCE");
		Object[] arg = new Object[0];
		Sequence paramSqs= (Sequence) g2Connection.callRPC(getDataSequence, arg,1000);
		paramSqs.removeAllElements();

		Symbol informG2 =  Symbol.intern("GNNE-MODEL-TRAINING-COMPLETE");
		arg = new Object[3];
		arg[0] =  uuid;
		arg[2] =  paramSqs;
		g2Connection.callRPC(informG2, arg,10000); 
	}
}
	
