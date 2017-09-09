package core;

import java.net.InetAddress;
import java.net.UnknownHostException;


import com.gensym.classes.Item;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2Connection;
import com.gensym.jgi.G2Gateway;
import com.gensym.util.Symbol;

import config.BridgeParameters;
import config.CommandLineParser;
import config.ConfigurationStringParser;
import config.ProcessParameters;
import exception.InvalidCommandLineException;
import com.gensym.util.AlreadyInitializedException;
/**
 * 
 * @author SoftServe
 * This class implements bridge entry point and registers
 * necessary JavaLink interface 
 *
 */
public class G2JDBCBridge {
	/**
	 * Standard bridge output on initialization stage
	 */
	private static final String initMessage = 
		"Starting G2-JDBC Bridge Version 2011";
	/**
	 * G2 Server connection instance 
	 */
	private G2Connection g2Connection = null;
	/**
	 * Bridge configuration parameters
	 */
	private static BridgeParameters bridgeParameters = null; 
	/**
	 * Holds bridge implementation instance
	 */
	private BridgeCore core = null;
	/**
	 * If true, bridge will shutdown on last connection close
	 */
	private static boolean haltOnDisconnect = false;
	/**
	 * Saves connection instance and registers callable methods
	 * @param connection connection to G2 Server
	 */
	public G2JDBCBridge(G2Connection connection, String initParams) {
		g2Connection = connection;
		ConfigurationStringParser csp = new ConfigurationStringParser(initParams);
		ProcessParameters pp = csp.parseProcessParameters();
		synchronized (G2JDBCBridge.class) {
			core = new BridgeCore(bridgeParameters, pp, this);
		}
		registerJavaMethods(connection);
		Console.putsWithDate("G2-JDBC Bridge connected to G2 Server");
	}

	/**
	 * Register our Java Methods that G2 can call as Remote Procedures.
	 */
	private void registerJavaMethods(G2Connection con) {
		con.registerJavaMethod(core, "dbCommit", 
				Symbol.intern("COMMIT_RP"));
		con.registerJavaMethod(core, "dbConnect", 
				Symbol.intern("CONNECT_RP"));
		con.registerJavaMethod(core, "dbConfiguration", 
				Symbol.intern("CONFIGURATION_RP"));
		con.registerJavaMethod(core, "dbExecuteImmediate", 
				Symbol.intern("EXEC_IMMEDIATE_RP"));
		con.registerJavaMethod(core, "dbSetDynamicExec", 
				Symbol.intern("EXEC_SQL_RP"));
		con.registerJavaMethod(core, "dbExecSQLObj", 
				Symbol.intern("EXEC_SQL_OBJ_RP"));
		con.registerJavaMethod(core, "dbExecStoredProc", 
				Symbol.intern("EXEC_STORED_PROC_RP"));
		con.registerJavaMethod(core, "dbExecStoredProcRet", 
				Symbol.intern("EXEC_STORED_PROC_RETURN_RP"));
		con.registerJavaMethod(core, "dbDisconnect", 
				Symbol.intern("DISCONNECT_RP"));
		con.registerJavaMethod(core, "dbSqlFunction", 
				Symbol.intern("SQL_FUNCTION_RP"));		
		con.registerJavaMethod(core, "dbKillBridge", 
				Symbol.intern("KILL_BRIDGE_RP"));
		con.registerJavaMethod(core, "dbLogfile", 
				Symbol.intern("LOG_FILE_RP"));
		con.registerJavaMethod(core, "dbPing", 
				Symbol.intern("PING_DB_RP"));
		con.registerJavaMethod(core, "dbRollback", 
				Symbol.intern("ROLLBACK_RP"));
		con.registerJavaMethod(core, "dbSetCursor", 
				Symbol.intern("SET_CURSOR_RP"));
		con.registerJavaMethod(core, "dbRefreshCursor", 
				Symbol.intern("REFRESH_CURSOR_RP"));
		con.registerJavaMethod(core, "dbFetchRecords", 
				Symbol.intern("FETCH_RECORDS_RP"));
		con.registerJavaMethod(core, "dbFetchStructure", 
				Symbol.intern("FETCH_STRUCTURE_RP"));
		con.registerJavaMethod(core, "dbFetchQueryItem", 
				Symbol.intern("FETCH_QUERY_ITEM_RP"));	
		con.registerJavaMethod(core, "dbUpdateQueryItem", 
				Symbol.intern("UPDATE_QUERY_ITEM_RP"));		
		con.registerJavaMethod(core, "dbFetchObjectCopy", 
				Symbol.intern("FETCH_OBJECT_COPY_RP"));
		con.registerJavaMethod(core, "dbFetchObjectList", 
				Symbol.intern("FETCH_OBJECT_LIST_RP"));
		con.registerJavaMethod(core, "dbFetchUpdateObject", 
				Symbol.intern("FETCH_OBJECT_UPDATE_RP"));
		con.registerJavaMethod(core, "dbGetTriggers", 
				Symbol.intern("GET_TRIGGERS_RP"));
		con.registerJavaMethod(core, "dbSetTrigger", 
				Symbol.intern("SET_TRIGGER_RP"));
		con.registerJavaMethod(core, "dbDisableAllTriggers", 
				Symbol.intern("DISABLE_ALL_TRIGGERS_RP"));
		con.registerJavaMethod(core, "dbRedirectCallback", 
				Symbol.intern("REDIRECT_CALLBACK_RP"));
	}
	/**
	 * @param args G2-JDBC bridge arguments
	 * Entry point for G2-JDBC bridge           
	 */
	public static void main(String[] args) {
		System.out.println(initMessage);

		
		synchronized (G2JDBCBridge.class) {
			try {
				bridgeParameters = CommandLineParser.parseCommandLine(args);
			} catch (InvalidCommandLineException icle) {
				System.out.println("Invalid command line");
				System.exit(0);
			}
			G2JDBCAuthorize jdbcAuth = new G2JDBCAuthorize();
			if (!jdbcAuth.authorize())
				return;
			G2Gateway.initialize(new String[] { "-listenerport",
						bridgeParameters.getPort() });
			if (bridgeParameters.isHelpRequired()) {
				printHelp();
			}
			haltOnDisconnect = bridgeParameters.isShutdownOnDisconnect();
			G2ConnectionsProducer g2cp = new G2ConnectionsProducer(haltOnDisconnect);
			G2Gateway.setConnectionHandlerFactory(g2cp);
			G2Gateway.startup();
			String hostName = "<unknown>";
			try {
				InetAddress ia = InetAddress.getLocalHost();
				hostName = ia.getHostName();
			} catch (UnknownHostException uhe) {
				Console.putsWithDate("An exception occured: " + uhe.getMessage());
			}
			Console.putsWithDate("Waiting to accept a connection on:");
			Console.putsWithDate(hostName + ":" + bridgeParameters.getPort());
		}
	}
	/**
	 * Prints help about command line options
	 */
	private static void printHelp() {
		Console.puts("G2-JDBC Bridge Command Line Options:");
		Console.puts("-maxrows <value> - maximum rows count in fetch procedures");
		Console.puts("-maxcols <value> - maximum columns count in fetch procedures");
		Console.puts("-charset <value> - underlying database charset");
		Console.puts("-shutdown_on_disconnect - database bridge will shutdown when last G2 connection closes");
		Console.puts("-help - displays this message");
	}
	/**
	 * Creates G2 Item using current G2 Connection
	 * @param itemClass item class name as symbol
	 * @return new G2 Item instance
	 * @throws G2AccessException when item can not be created
	 */
	public Item createG2Item(Symbol itemClass) throws G2AccessException {
		return g2Connection.createItem(itemClass);
	}
}
