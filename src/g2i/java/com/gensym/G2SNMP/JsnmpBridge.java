package com.gensym.G2SNMP;

import com.adventnet.snmp.snmp2.SnmpAPI;
import com.adventnet.snmp.snmp2.SnmpException;
import com.gensym.jgi.G2Connection;
import com.gensym.jgi.G2Gateway;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.core.CmdLineArgHandler;
import com.gensym.G2SNMP.trapd.TrapDaemon;
import java.util.StringTokenizer;
import com.gensym.util.Symbol;
import com.gensym.G2SNMP.util.DNSLookup;
import java.io.*;

/**
 * The G2ConnectionHandlerFactory for the bridge. Defined in the same
 * JsnmpBridge component as Rose does not seem to be able to work well with
 * static inner classes.
 */
class JsnmpFactory implements com.gensym.jgi.G2ConnectionHandlerFactory {

	/**
	 * @roseuid 3667C9800236
	 */
	public G2Connection createG2Connection(String connectionData) {
		JsnmpBridge.debugOut("JsnmpFactory.createG2Connection ("
				+ connectionData + ").");
		G2Gateway aGateway = new G2Gateway();
		JsnmpBridge aBridge = new JsnmpBridge(aGateway, connectionData);
		aGateway.addG2ConnectionListener(aBridge);
		// System.out.println (aGateway.getG2ConnectionInfo().getHost());

		return aGateway;
	}
}

/**
 * The main class of the bridge. Instantiated once per every incoming
 * connection.
 */
public final class JsnmpBridge extends com.gensym.jgi.G2ConnectionAdapter {
	/**
	 * This is a static debug mode indicator. In this mode the bridge prints
	 * lots of useless information.
	 */
	private static boolean debug = false;
	/**
	 * This is a static silent mode indicator. In this mode the bridge does not
	 * print anything.
	 */
	private static boolean silent = false;
	private static volatile LogFile logFile;
	/**
	 * This can be either TrapDaemon or Transactor.
	 */
	private Task task;
	private static volatile TrapDaemon trapDaemon = null;
	private static volatile SnmpAPI snmpApi;
	private static volatile SnmpAPI snmpApiD;
	private G2Connection g2connection;
	private String connectionData;
	private String g2Info;
	private static final String LOG_FILE_OPTION = "-log";
	private static final String LOG_SIZE_OPTION = "-maxloglines";
	private static final String NO_LOG_OPTION = "-nolog";
	private static final String PPD_FILE_OPTION = "-ppdfilename";
	private static final String DEBUG_OPTION = "-debug";
	private static final String SILENT_OPTION = "-silent";
	private static final String HELP_OPTION = "-help";
	private static final String MIBS_OPTION = "-mibs";
	private static volatile String ppdFileName;
	private static volatile String mibNames;
	private static final int DEFAULT_MODE = 2;
	private static final int DEFAULT_TCPPORT = 22041;
	private static final String DEFAULT_MIBS = "SNMPv2-MIB";
	private static int EngineBoots;

	/**
	 * This is the start-up procedure for the bridge. It should create
	 * JsnmpBridge object and initialize it properly.
	 * 
	 * @roseuid 365D6261026D
	 */
	public static void main(String args[]) {

		stateOut("Java-based G2-SNMP Bridge Version 5.0 Rev. 0");
		stateOut("");
		// stateOut("RESTRICTED DISTRIBUTION ONLY!");
		stateOut("");
		System.runFinalizersOnExit(true);

		CmdLineArgHandler cmdLine = new CmdLineArgHandler(args);
		setDebug(cmdLine.getSwitchValue(DEBUG_OPTION));
		silent = cmdLine.getSwitchValue(SILENT_OPTION);
		if (cmdLine.getSwitchValue(HELP_OPTION)) {
			String space = "    ";
			System.out.println("Options supported:");
			System.out.println(space + G2Gateway.LISTENER_PORT_OPTION
					+ " <port-number>");
			System.out.println(space + LOG_FILE_OPTION
					+ "          <file-name>");
			System.out.println(space + LOG_SIZE_OPTION + "  <number>");
			System.out.println(space + NO_LOG_OPTION);
			System.out.println(space + PPD_FILE_OPTION + "  <file-name>");
			System.out.println(space + MIBS_OPTION + " <file-name(s)>");
			System.out.println(space + DEBUG_OPTION);
			System.out.println(space + SILENT_OPTION);
			System.out.println(space + HELP_OPTION);
			System.exit(0);
		}

		if (!cmdLine.getSwitchValue(NO_LOG_OPTION))
			try {
				String logName = cmdLine.getOptionValue(LOG_FILE_OPTION);
				int lines = (int) cmdLine.getOptionLong(LOG_SIZE_OPTION, 50000);
				if (lines < 1)
					throw new NumberFormatException(
							"the number should be greater than zero.");
				logFile = new LogFile(logName, "Java-based SNMP Bridge", lines);
			} catch (NumberFormatException e) {
				System.err.println("Error: incorrect '" + LOG_SIZE_OPTION
						+ "' parameter value.");
				debugOut(e.toString());
				System.exit(1);
			}

		ppdFileName = cmdLine.getOptionValue(PPD_FILE_OPTION);
		mibNames = DEFAULT_MIBS;
		mibNames = cmdLine.getOptionValue(MIBS_OPTION);

		int port = DEFAULT_TCPPORT;
		try {
			port = (int) cmdLine.getOptionLong(G2Gateway.LISTENER_PORT_OPTION,
					DEFAULT_TCPPORT);

			/*
			 * I need to try ServerSocket to check the port availability.
			 * Otherwise G2Gateway would find another free port and
			 * self-initialize on it without notifying me.
			 */
			new java.net.ServerSocket(port).close();

			G2Gateway.initialize(port);
			G2Gateway.setConnectionHandlerFactory(new JsnmpFactory());
			G2Gateway.startup();
			stateOut("Listening on port " + port + "...");
			snmpApi = new SnmpAPI();
			snmpApi.Standard_Prefix = ".";
			// System.out.println ("Standard_Prefix = " +
			// snmpApi.Standard_Prefix);
			snmpApi.start();
			// TLEE 4/3/02 a seperate SnmpAPI object for trapdemons
			snmpApiD = new SnmpAPI();
			// snmpApiD.Standard_Prefix = ".";
			// System.out.println ("Standard_Prefix = " +
			// snmpApi.Standard_Prefix);
			snmpApiD.start();
			// setDebug (debug); // this is to set snmpApi.DEBUG
			// this is set above based on user input: WSM setDebug(false);
		} catch (NumberFormatException e) {
			System.err.println("Error: incorrect port number.");
			debugOut(e.toString());
			System.exit(1);
		} catch (java.io.IOException e) {
			System.err.println("Error: TCP port " + port
					+ " initialization failed.");
			debugOut(e.toString());
			System.exit(1);
		} catch (com.gensym.util.AlreadyInitializedException e) {
			System.err.println("Error: G2 Gateway initialization failed.");
			debugOut(e.toString());
			System.exit(1);
		}

		// Initialize the DNS look-up indices. DNSLookup is a singleton, so
		// there
		// is no way to create a new instance, only access the single one
		// provided.

		DNSLookup.getInstance().readXrefFile("DNSTest.cfg");
		readBoots("jsnmpboots.ser");
	}

	/**
	 * @roseuid 365D62FC01E4
	 */
	public JsnmpBridge(G2Connection g2connection, String connectionData) {
		this.g2connection = g2connection;
		this.connectionData = connectionData;
		g2Info = "G2 access (from unknown) ";
	}

	public void g2ConnectionInitialized(G2ConnectionEvent event) {

		synchronized (g2connection) {
			g2Info = "unknown";
			
			try {
				g2Info = g2connection.g2GetHostName() + ":"
						+ g2connection.g2GetPortNumberOrName();
			} catch (com.gensym.jgi.G2AccessException e) {
				System.err
						.println("Warning: Getting G2 connection information failed.");
			}
			g2Info = "G2 access (from " + g2Info + ") ";

			StringTokenizer st = new StringTokenizer(connectionData);
			int n = st.countTokens();
			String[] args = new String[n];
			for (int i = 0; i < n; i++) {
				args[i] = st.nextToken();
			}
			CmdLineArgHandler aHandler = new CmdLineArgHandler(args);
			setDebug(aHandler.getSwitchValue("-d"));
			int timeOut = Transactor.DEFAULT_TIMEOUT;
			int mode = DEFAULT_MODE;
			String optionName = "";
			try {
				optionName = "-t"; // timeout option
				timeOut = (int) aHandler.getOptionLong(optionName,
						Transactor.DEFAULT_TIMEOUT);
				optionName = "-p"; // bridge mode option
				mode = (int) aHandler.getOptionLong(optionName, DEFAULT_MODE);
			} catch (NumberFormatException e) {
				killThisG2Connection(e, "Warning: Unknown value of '"
						+ optionName + "' initialization parameter.");
				return;
			}

			debugOut("JsnmpBridge.g2ConnectionInitialized (timeout=" + timeOut
					+ ", mode=" + mode + ")");

			switch (mode) {
			case 1: // receive traps
				if (trapDaemon != null) {
					killThisG2Connection(
							null,
							"Warning: "
									+ g2Info
									+ "was denied as one GSI interface is already connected to receive traps.");
					return;
				}
				try {
					String snmpversion = aHandler.getOptionValue("-v");
					// 6/6/02 WSM: Added if statement below to default SNMP
					// version to V1.
					int port = (int) aHandler.getOptionLong("-n", 162);
					if (snmpversion == null) {
						snmpversion = "V1";
						JsnmpBridge
								.debugOut("\n-v not supplied, defaulting to "
										+ snmpversion);
					} else if (snmpversion.equals("v3")
							|| snmpversion.equals("V3")) {
						String engineID = aHandler.getOptionValue("-e");
						String userName = aHandler.getOptionValue("-u");
						if (engineID == null || userName == null) {
							killThisG2Connection(null, "Warning: " + g2Info
									+ "invalid engineID or username");
							return;
						}
						String authPassword = aHandler.getOptionValue("-w");
						String privPassword = aHandler.getOptionValue("-s");
						String authProtocol = aHandler.getOptionValue("-a");
						debugOut("snmpversion=" + snmpversion + " engineID="
								+ engineID + " userName=" + userName + " port="
								+ port + " authPassword=" + authPassword
								+ " privPassword=" + privPassword
								+ " authProtocol=" + authProtocol);

						trapDaemon = new TrapDaemon(snmpApiD, g2connection,
								ppdFileName, mibNames, engineID, userName,
								port, authPassword, privPassword, authProtocol);
					} else {
						trapDaemon = new TrapDaemon(snmpApiD, g2connection,
								ppdFileName, mibNames, port);
					}
					task = trapDaemon;
					stateOut(g2Info + "was granted (to receive traps).");
				} catch (TaskInitException e) {
					killThisG2Connection(e,
							"Error: SNMP trap receiving daemon failed to initialize.");
					trapDaemon = null;
					task = null;
				}
				break;
			case 2: // get/set/send traps
				try {
					task = new Transactor(snmpApi, g2connection, timeOut);
					stateOut(g2Info + "was granted (to perform transactions).");
				} catch (TaskInitException e) {
					killThisG2Connection(e,
							"Error: SNMP transaction handler failed to initialize.");
					task = null;
				}
				break;
			default:
				killThisG2Connection(null, "Warning: " + g2Info
						+ "was denied because of unknown -p parameter value.");
			}
		}
	}

	void killThisG2Connection(Exception e, String msg) {
		System.err.println(msg);
		g2connection.reportLogBookErrorMessage(Symbol
				.intern("JAVA-SNMP-BRIDGE-ERROR"), msg);
		if (e != null)
			debugOut(e.toString());
		g2connection.closeConnection();
	}

	public void g2ConnectionClosed(G2ConnectionEvent event) {
		synchronized (g2connection) {
			stateOut(g2Info + "was closed.");
			g2connection.removeG2ConnectionListener(this);
			if (trapDaemon != null && trapDaemon.equals(task)) {
				trapDaemon = null;
				task = null;
				System.gc();
			}
		}
	}

	/**
	 * This static method should be used by all to print any kind of information
	 * useful for debug (such as "a method started".)
	 * 
	 * @roseuid 3665578A0294
	 */
	public static void debugOut(String str) {
		if (debug)
			System.out.println("  " + str);
	}

	/**
	 * @roseuid 3667C97E021F
	 */
	protected void finalize() {
		debugOut("JsnmpBridge.finalize ().");
		if (g2connection != null && g2connection.isAlive())
			g2connection.closeConnection();
	}

	/**
	 * This static method should be used by all to print any kind of bridge
	 * state information.
	 * 
	 * @roseuid 3668150703AE
	 */
	public static void stateOut(String str) {
		if (!silent)
			System.out.println(str);
	}

	/**
	 * This static method allows debug mode changing from outside of this class.
	 * It was originally designed just for external testing.
	 */
	public static void setDebug(boolean debug) {
		JsnmpBridge.debug = debug;
		if (snmpApi != null)
			snmpApi.setDebug(debug);
		if (snmpApiD != null)
			snmpApiD.setDebug(debug);
	}

	/**
	 * File to keep track of number of SnmpEngineBoots, as a requirement of
	 * SNMPv3
	 **/
	private static void readBoots(String EngineFile) {
		snmpApiD.setEngineBootsSerializeFileName(EngineFile);
		try {
			if (snmpApiD.deSerializeEngineBoots() == false) {
				snmpApiD.setSnmpEngineBoots(1);
			} else {
				snmpApiD.setSnmpEngineBoots(snmpApiD.getSnmpEngineBoots() + 1);
				snmpApi.setSnmpEngineBoots(snmpApiD.getSnmpEngineBoots());
				debugOut("Boots = " + snmpApiD.getSnmpEngineBoots());
				snmpApiD.serializeEngineBoots();
			}
		} catch (SnmpException e) {
			System.err.println("Error: " + e.getMessage()
					+ "\nCreating new Engine boots file: " + EngineFile);
			snmpApiD.setSnmpEngineBoots(1);
			try {
				snmpApiD.serializeEngineBoots();
			} catch (SnmpException se) {
			}
		}
	}
}
