package core;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.sql.Connection;
import java.sql.DatabaseMetaData;
import java.sql.SQLException;

import com.gensym.classes.Item;
import com.gensym.classes.TextList;
import com.gensym.classes.modules.g2database.DbCursorObject;
import com.gensym.classes.modules.g2database.DbQueryItem;
import com.gensym.classes.modules.g2database.DbSqlObject;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.MultipleValuesHolder;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;

import config.BridgeConfiguration;
import config.BridgeParameters;
import config.ProcessParameters;
import exception.ErrorMessage;
import exception.InfoMessage;
import exception.WarningMessage;
import type.GDBControlValue;
import type.LogFileOperation;
import type.MultipleValuesFactory;
import type.StatusSymbol;
import type.StatusTuple;

//TODO: add statement.close() everywhere in the code!

/**
 * This class declares all bridge methods and
 * groups underlined objects which implements them
 * @author SoftServe
 *
 */
public class BridgeCore implements BridgeExternalInterface {
	/**
	 * Connection Manager of this bridge core instance
	 */
	private ConnectionsManager conMgr = null;
	/**
	 * Bridge Parameters of this bridge instance 
	 */
	private BridgeParameters bridgeParameters = null;
	/**
	 * Bridge Configuration of this bridge instance
	 */
	private BridgeConfiguration bridgeConf = null;
	/**
	 * Process Parameters of this bridge instance
	 */
	private ProcessParameters processParameters = null;
	/**
	 * Logger for all events
	 */
	private BridgeEventsLogger logger = null;
	/**
	 * Underlying JDBC connection
	 */
	private Connection dbConnection = null;
	/**
	 * Actual processor of most queries to bridge
	 */
	private QueryProcessor engine = null;
	/**
	 * Indicates if underlying connection is alive
	 */
	//TODO: update on error
	private boolean connectionAlive = false; 
	/**
	 * Indicates stored procedures support by underlying JDBC driver
	 */
	private boolean driverSupportsStoredProcedures = false;
	/**
	 * Database user name. Used on bridge reconnect
	 */
	private String conUserName = "";
	/**
	 * Database user password. Used on bridge reconnect
	 */
	private String conPassword = "";
	/**
	 * Database connection string. Used on bridge reconnect
	 */
	private String conStr = "";
	/**
	 * Database gsi connection string. Used on bridge reconnect
	 */
	private String conGsiStr = "";
	/**
	 * Bridge owner
	 */
	private G2JDBCBridge parent = null;
	
	/**
	 * Creates bridge core instance and ConnectionsManager instance
	 * @param bp Bridge Parameters for this bridge instance
	 * @param pp Process Parameters for this bridge instance
	 */
	public BridgeCore(BridgeParameters bp, ProcessParameters pp, G2JDBCBridge parent) {
		bridgeParameters = bp;
		processParameters = pp;
		this.parent = parent;
		bridgeConf = new BridgeConfiguration();
		if (processParameters.isDisableConsoleOut()) {
			Console.disable();
		}
		String driver = bp.getDriver();
		if (driver == null) {
			Console.puts(ErrorMessage.NO_JDBC_DRIVER);
			System.exit(0);
		} 
		try {
		 conMgr = new ConnectionsManager(driver);
		} catch (Exception e) {
			Console.puts(ErrorMessage.JDBC_REG_FAILED);
			System.exit(0);
		}
	}
	/**
	 * Establishes a connection between the bridge and the database
	 * @param user database user name
	 * @param password database user password
	 * @param connectionString database connection string
	 * @return operation result as a multiple values object
	 */
	@Override
	public MultipleValuesHolder dbConnect(String user, String password, String connectionString) {
		conUserName = user;
		conPassword = password;
		conStr = connectionString;
		try {
			dbConnection = conMgr.getConnection(user, password, connectionString);
		} catch (SQLException e) {
			logger.severe(ErrorMessage.CONNECT_FAILED);
			logger.severe(ErrorMessage.EMSG + e.getMessage());
			return MultipleValuesFactory.create3(StatusSymbol.FATAL,
					e.getErrorCode(), e.getMessage());
		}
		try {
			analyzeDatabaseMetaData(dbConnection.getMetaData());
		} catch (SQLException se) {
			logger.severe(ErrorMessage.MD_ANALYSIS_FAILED);
			logger.severe(ErrorMessage.EMSG + se.getMessage());
			return MultipleValuesFactory.create3(StatusSymbol.FATAL,
					se.getErrorCode(), se.getMessage());
		}
		engine = new QueryProcessor(dbConnection, logger, bridgeParameters, processParameters, parent);
		engine.setNullBindRepalcement(getNullBindingReplacement());
		engine.setNullFetchReplacement(getNullFetchingReplacement());
		connectionAlive = true;
		logger.info(InfoMessage.DB_CONNECT_OK);
		return MultipleValuesFactory.create3(StatusSymbol.SUCCESS, 0, InfoMessage.DB_CONNECT_OK);
	}
	/**
	 * Establishes a connection between the bridge and the database
	 * @param user database user name
	 * @param password database user password
	 * @param connectionString database connection string
     * @param gsiConnectionString gsi connection string
	 * @return operation result as a multiple values object
	 */
	@Override
	public MultipleValuesHolder dbConnect (String user, String password, String connectionString, String gsiConnectionString){
        conUserName = user;
		conPassword = password;
		conStr = connectionString;
        conGsiStr = gsiConnectionString;
		try {
			dbConnection = conMgr.getConnection(user, password, connectionString);
		} catch (SQLException e) {
			logger.severe(ErrorMessage.CONNECT_FAILED);
			logger.severe(ErrorMessage.EMSG + e.getMessage());
			return MultipleValuesFactory.create3(StatusSymbol.FATAL,
					e.getErrorCode(), e.getMessage());
		}
		try {
			analyzeDatabaseMetaData(dbConnection.getMetaData());
		} catch (SQLException se) {
			logger.severe(ErrorMessage.MD_ANALYSIS_FAILED);
			logger.severe(ErrorMessage.EMSG + se.getMessage());
			return MultipleValuesFactory.create3(StatusSymbol.FATAL,
					se.getErrorCode(), se.getMessage());
		}
		engine = new QueryProcessor(dbConnection, logger, bridgeParameters, processParameters, parent);
		engine.setNullBindRepalcement(getNullBindingReplacement());
		engine.setNullFetchReplacement(getNullFetchingReplacement());
		connectionAlive = true;
		logger.info(InfoMessage.DB_CONNECT_OK);
		return MultipleValuesFactory.create3(StatusSymbol.SUCCESS, 0, InfoMessage.DB_CONNECT_OK);
    }
    
	/**
	 * Passes bridge configuration information to the bridge core
	 * @param kbVersion g2-database.kb version
	 * @param contextName GSI context name
	 * @param logFileName full path to the bridge log file and logging levels enumeration
	 * @param autoReconnect this flag indicates if bridge would reconnect to database on connection lost
	 * @param maximumDefinableCursors maximum amount of cursors that can be defined within this bridge
	 * @param enableMessaging enables or disables messages passing from this bridge to G2
	 * @param nullString SQL NULL replacement for fetching
	 * @param nullNumber SQL NULL replacement for fetching
	 * @param setNullString SQL NULL replacement for binding
	 * @param setNullNumber SQL NULL replacement for binding
	 * @param setNullOptions SQL NULL replacements usage options
	 * @return operation result as a multiple values object
	 */
	@Override
	public MultipleValuesHolder dbConfiguration
	 (int kbVersion, String contextName, String logFileName, boolean autoReconnect,
	  int maximumDefinableCursors, boolean enableMessaging, String nullString,
	  int nullNumber, String setNullString, int setNullNumber, int setNullOptions) {
		bridgeConf.setKbVersion(kbVersion);
		bridgeConf.setContextName(contextName);
		bridgeConf.setLogFileName(logFileName);
		bridgeConf.setAutoReconnectSet(autoReconnect);
		bridgeConf.setMaxDefinableCursors(maximumDefinableCursors);
		bridgeConf.setMessagingEnabled(enableMessaging);
		bridgeConf.setNullString(nullString);
		bridgeConf.setNullNumber(nullNumber);
		bridgeConf.setSetNullNumber(setNullNumber);
		bridgeConf.setSetNullString(setNullString);
		bridgeConf.setSetNullOptions(setNullOptions);
		logger = new BridgeEventsLogger(logFileName, processParameters.isDisableLogTimestamp());
		logger.info(InfoMessage.LOGGER_STARTED);
		logger.info(InfoMessage.B_CONF_OK);
	    return MultipleValuesFactory.create3(StatusSymbol.SUCCESS, 0, InfoMessage.B_CONF_OK);	
	}
	/**
	 * Updates status for given cursor
	 * @param cursor Cursor whose status should be updated
	 * @param status new status
	 * @param code DB-CODE for cursor
	 * @param msg DB-MESSAGE for cursor
	 */
	private void updateCursorStatus(DbCursorObject cursor, Object status, Object code, Object msg){
		if (cursor instanceof com.gensym.classes.modules.g2database.DbCursorObject) {
			try {
				cursor.setPropertyValue(Symbol.intern("DB-STATUS"), status);
				cursor.setPropertyValue(Symbol.intern("DB-CODE"), code);
				cursor.setPropertyValue(Symbol.intern("DB-MESSAGE"), msg);
			} catch (G2AccessException e) {
				logger.warning(WarningMessage.WRONG_CURSOR_OBJECT);
			}
		}
	}
	/**
	 * Commits all pending since the last commit queries to underlying database 
	 * @return operation result as a multiple values object
	 */
	@Override
	public MultipleValuesHolder dbCommit() {
		if(checkConnectionAndMaybeReconnect()) {
			return executeInExceptionContext("commitPendingQueries", 
					null , null, ErrorMessage.DB_COMMIT_FAILED,
					InfoMessage.DB_COMMIT_OK, 
					MultipleValuesFactory.create3(StatusSymbol.ERROR,
							0, ErrorMessage.IERROR), 0); 
		} 
		return MultipleValuesFactory.create3(StatusSymbol.DISCONNECTED, 0,
				ErrorMessage.CONN_BROKEN);
	}
	/**
	 * Cancels all pending since the last call to dbCommit queries
	 * @return operation result as a multiple values object
	 */
	@Override
	public MultipleValuesHolder dbRollback() {
		StatusTuple st =  engine.cancelPendingQueries();
		return MultipleValuesFactory.create3(st.getStatus(), st.getCode(), st.getText());
	}
	/**
	 * Executes given SQL statement without variables binding
	 * @param stmnt SQL statement to execute
	 * @param autoCommit if true, statement will be committed immediately, otherwise it will be pending till the next dbCommit call 
	 * @return operation result as a multiple values object
	 */
	@Override
	public MultipleValuesHolder dbExecuteImmediate(String stmnt, boolean autoCommit) {
		if(checkConnectionAndMaybeReconnect()) {
			Class[] at = {String.class, boolean.class};
			Object[] args = {stmnt, autoCommit};
			return executeInExceptionContext("executePlainSQL", 
					at, args, ErrorMessage.IMM_EXEC_FAILED,
					InfoMessage.EXEC_IMM_OK,
					MultipleValuesFactory.create3(StatusSymbol.FATAL,
							0, ErrorMessage.IERROR), 0);
		}
		return MultipleValuesFactory.create3(StatusSymbol.DISCONNECTED, 0,
				ErrorMessage.CONN_BROKEN);
	}
	/**
	 * Defines, modifies or executes given SQL object
	 * @param sqlObject DbSqlObject, related to a query
	 * @param stmnt SQL statement to define, execute or modify
	 * @param controlValue flag which indicates SQL statement definition, modification or execution
	 * @param tl list of variables values to bind
	 * @param ac auto commit flag for this operation
	 * @return operation result as a multiple values object
	 */
	@Override
	public MultipleValuesHolder dbSetDynamicExec(DbSqlObject sqlObject, String stmnt, int controlValue, TextList tl, boolean ac) {
		if(checkConnectionAndMaybeReconnect()) {
			DbSqlObject dbSqlObject = sqlObject;
			if (controlValue == GDBControlValue.GDB_INIT) {
				Class[] at = {DbSqlObject.class, String.class, TextList.class};
				Object[] args = {dbSqlObject, stmnt, tl};
				return executeInExceptionContext("defineSQL", at,
						args, ErrorMessage.SQL_OBJ_DEF_FAILED,
						InfoMessage.SQL_DEFINED,
						MultipleValuesFactory.create3(StatusSymbol.FATAL,
								0, ErrorMessage.IERROR), 0);
			} else if (controlValue == GDBControlValue.GDB_UPDATE) {
				Class[] at = {DbSqlObject.class, TextList.class};
				Object[] args = {dbSqlObject, tl};
				return executeInExceptionContext("updateSQL",
						at, args, ErrorMessage.BINDING_FAILED,
						InfoMessage.SQL_UPDATED,
						MultipleValuesFactory.create3(StatusSymbol.FATAL,
								0, ErrorMessage.IERROR), 0);
			} else if (controlValue == GDBControlValue.GDB_EXECUTE) {
				Class[] at = {DbSqlObject.class, boolean.class};
				Object[] args = {dbSqlObject, ac};
				return executeInExceptionContext("execSQL", at,
						args, ErrorMessage.SQL_EXEC_FAILED,
						InfoMessage.SQL_EXEC_OK,
						MultipleValuesFactory.create3(StatusSymbol.FATAL,
								0, ErrorMessage.IERROR), 0);
			}
		}
		return MultipleValuesFactory.create3(StatusSymbol.DISCONNECTED, 0,
				ErrorMessage.CONN_BROKEN);		
	}
	/**
	 * Executes given SQL-OBJECT
	 * @param sqlObject DbSqlObject for this query
	 * @param vs bind values as string
	 * @param controlValue dispatch value
	 * @param obj bind values holder
	 * @param ac auto commit flag for this query
	 * @return operation result as a multiple values object
	 */
	@Override
	public MultipleValuesHolder dbExecSQLObj(DbSqlObject sqlObject, String vs, int controlValue, Object obj, boolean ac) {
		if (checkConnectionAndMaybeReconnect()) {
			Class[] at = {DbSqlObject.class, String.class, Object.class, boolean.class};
			Object[] args = {sqlObject, vs, obj, ac};
			if (controlValue == GDBControlValue.GDB_UPDATE) {
				return executeInExceptionContext("updateSQLObject",
						at, args, ErrorMessage.UPDATE_SQL_OBJECT_FAILED,
						InfoMessage.UPDATE_SQL_OBJECT_OK, 
						MultipleValuesFactory.create3(StatusSymbol.FATAL,
								0, ErrorMessage.IERROR), 0);
			} else if (controlValue == GDBControlValue.GDB_EXECUTE) {
				Class[] at2 = {DbSqlObject.class, boolean.class};
				Object[] args2 = {sqlObject, ac};
				return executeInExceptionContext("execSQL",
						at2, args2, ErrorMessage.EXEC_SQL_OBJECT_FAILED,
						InfoMessage.EXEC_SQL_OBJECT_OK, 
						MultipleValuesFactory.create3(StatusSymbol.FATAL,
								0, ErrorMessage.IERROR), 0);
			}
		}
		return MultipleValuesFactory.create3(StatusSymbol.DISCONNECTED, 0,
				ErrorMessage.CONN_BROKEN);		
	}
	/**
	 * Executes stored procedure which is not supposed to return a value
	 * @param procCall SQL statement with stored procedure call
	 * @param controlValue not used
	 * @return operation result as a multiple values object
	 */
	@Override
	public MultipleValuesHolder dbExecStoredProc(String procCall, String controlValue) {
		if (checkConnectionAndMaybeReconnect()) {
			if (driverSupportsStoredProcedures) {
				Class[] at = {String.class};
				Object[] args = {procCall};
				return executeInExceptionContext("executeStoredProcedure",
						at, args, ErrorMessage.STORED_PROC_EXECUTION_FAILED,
						InfoMessage.SQL_EXEC_OK,
						MultipleValuesFactory.create3(StatusSymbol.FATAL,
								0, ErrorMessage.IERROR), 0);
			} else {
				return MultipleValuesFactory.create3(StatusSymbol.ERROR, 0,
						ErrorMessage.SP_NOT_SUPPORTED);
			}
		}
		return MultipleValuesFactory.create3(StatusSymbol.DISCONNECTED, 0,
				ErrorMessage.CONN_BROKEN);
	}
	/**
	 * Executes stored procedure which returns a value
	 * @param procName stored procedure name
	 * @param arguments arguments for stored procedure call
	 * @return operation result as a multiple values object
	 */	
	@Override
	public MultipleValuesHolder dbExecStoredProcRet(String procName, String arguments) {
		if (checkConnectionAndMaybeReconnect()) {
			Class at[] = {String.class, String.class};
			Object args[] = {procName, arguments};
			return executeInExceptionContext("executeStoredProcedureReturningValue",
					at, args, ErrorMessage.STORED_PROC_EXECUTION_FAILED,
					InfoMessage.STORED_PROC_RET_OK,
					MultipleValuesFactory.create4(null, StatusSymbol.FATAL,
							0, ErrorMessage.IERROR),
					1);
		}
		return MultipleValuesFactory.create4(null, StatusSymbol.DISCONNECTED, 0, ErrorMessage.CONN_BROKEN);
	}
	/**
	 * Executes given SQL statements and returns single result
	 * @param stmnt SQL statement to execute
	 * @return operation result as a multiple values object
	 */
	@Override
	public MultipleValuesHolder dbSQLFunction(String stmnt) {
		if (checkConnectionAndMaybeReconnect()) {
			Class[] at = {String.class};
			Object args[] = {stmnt};
			return executeInExceptionContext("executeSQLFunction",
					at, args, ErrorMessage.SQL_EXEC_FAILED,
					InfoMessage.SQL_EXEC_OK, 
					MultipleValuesFactory.create5(null, null,
							StatusSymbol.FATAL, 0, ErrorMessage.IERROR), 2);
		}
		return MultipleValuesFactory.create5(null, null, StatusSymbol.ERROR, 0,
				ErrorMessage.CONN_BROKEN);
	}
	/**
	 * Sets or modifies given cursor object
	 * @param cursor cursor to set or modify
	 * @param sql SQL statement for this cursor
	 * @param controlValue dispatch value
	 * @param tl list of the binding values  
	 */
	@Override
	public MultipleValuesHolder dbSetCursor(DbCursorObject cursor, String sql, int controlValue, TextList tl) {
		if (checkConnectionAndMaybeReconnect()) {
			if (controlValue == GDBControlValue.GDB_INIT) {
				Class[] at = {DbCursorObject.class, String.class, TextList.class};
				Object[] args = {cursor, sql, tl};
				return executeInExceptionContext("dbDefineCursor",
						at, args, ErrorMessage.DEFINE_CURSOR_FAILED,
						InfoMessage.CURSOR_DEFINED,
						MultipleValuesFactory.create3(StatusSymbol.FATAL,
								0, ErrorMessage.IERROR), 0);
			} else if (controlValue == GDBControlValue.GDB_UPDATE) {
				Class[] at = {DbCursorObject.class, String.class, TextList.class};
				Object[] args = {cursor, sql, tl};
				return executeInExceptionContext("dbSetCursor",
						at, args, ErrorMessage.SET_CURSOR_FAILED,
						InfoMessage.CURSOR_SET,
						MultipleValuesFactory.create3(StatusSymbol.FATAL,
								0, ErrorMessage.IERROR), 0);				
			}
			logger.severe(ErrorMessage.INCORRECT_GDB_VALUE);
			return MultipleValuesFactory.create3(StatusSymbol.ERROR, 0, ErrorMessage.INCORRECT_GDB_VALUE);
		} else {
			return MultipleValuesFactory.create3(StatusSymbol.DISCONNECTED, 0,
					ErrorMessage.CONN_BROKEN);	
		}
	} 
	
	/**
	 * Fetches  a copy of user-defined object 
	 * @param cursor Cursor position for fetch start
	 * @param mo user-defined object
	 * @param fetchBatch fetch batch size
	 * @param sq1Out first output sequence
	 * @param sq2Out second output sequence
	 * @return operation result as a multiple values object
	 */
	@Override
	public MultipleValuesHolder dbFetchObjectCopy(DbCursorObject cursor, Item mo, int fetchBatch, Sequence sq1Out, Sequence sq2Out) {
		if (checkConnectionAndMaybeReconnect()) {
			MultipleValuesHolder mvh;
			Class[] at = {DbCursorObject.class, Item.class, int.class, 
					Sequence.class, Sequence.class};
			Object[] args = {cursor, mo, fetchBatch, sq1Out, sq2Out};
			mvh = executeInExceptionContext("dbFetchObjectCopy",
					at, args, ErrorMessage.FETCH_OBJECT_FAILED,
					InfoMessage.FETCH_OBJECT_SUCCEEDED,
					MultipleValuesFactory.create6(null, StatusSymbol.FATAL,
							0, ErrorMessage.IERROR, 0, 0),
					1);
			updateCursorStatus(cursor, mvh.get(1), mvh.get(2),  mvh.get(3));
			return mvh;
		} else {
			return MultipleValuesFactory.create6(null, StatusSymbol.DISCONNECTED, 0,
					InfoMessage.DB_CON_CLOSED, 0, 0);
		}
	}
	
	/**
	 * Fetches  a copy of user-defined object as list
	 * @param cursor Cursor position for fetch start
	 * @param mo user-defined object
	 * @param fetchBatch fetch batch size
	 * @param sq1Out first output sequence
	 * @param sq2Out second output sequence
	 * @return operation result as a multiple values object
	 */
	@Override
	public MultipleValuesHolder dbFetchObjectList(DbCursorObject cursor, Item mo, int fetchBatch, Sequence sq1Out, Sequence sq2Out) {
		if (checkConnectionAndMaybeReconnect()) {
			MultipleValuesHolder mvh;
			Class[] at = {DbCursorObject.class, Item.class, int.class, 
					Sequence.class, Sequence.class};
			Object[] args = {cursor, mo, fetchBatch, sq1Out, sq2Out};
			mvh = executeInExceptionContext("dbFetchObjectList",
					at, args, ErrorMessage.FETCH_OBJECTS_LIST_FAILED,
					InfoMessage.FETCH_OBJECTS_LIST_SUCCEEDED,
					MultipleValuesFactory.create6(null, StatusSymbol.FATAL,
							0, ErrorMessage.IERROR, 0, 0),
					1);			
			updateCursorStatus(cursor, mvh.get(1), mvh.get(2),  mvh.get(3));
			return mvh;
		} else {
			return MultipleValuesFactory.create6(null, StatusSymbol.DISCONNECTED, 0,
					InfoMessage.DB_CON_CLOSED, 0, 0);
		}		
	}
	
	/**
	 * Fetches values and stores them into user-defined object
	 * @param cursor Cursor to start fetching from
	 * @param mo user-defined object
	 * @param controlValue Control Value
	 * @param fetchBatch fetch batch size
	 * @param sq1Out first output sequence
	 * @param sq2Out second output sequence
	 * @return operation result as a multiple values object
	 */
	@Override
	public MultipleValuesHolder dbFetchUpdateObject(DbCursorObject cursor, Item mo, int controlValue, int fetchBatch, Sequence sq1Out, Sequence sq2Out) {
		if (checkConnectionAndMaybeReconnect()) {
			Class[] at = {DbCursorObject.class, Item.class, int.class,
					int.class, Sequence.class, Sequence.class};
			Object[] args = {cursor, mo, controlValue, fetchBatch,
					sq1Out, sq2Out};
			return executeInExceptionContext("dbFetchUpdateObject",
					at, args, ErrorMessage.FETCH_UPDATE_OBJECT_FAILED,
					InfoMessage.FETCH_UPDATE_OBJECT_SUCCEEDED,
					MultipleValuesFactory.create5(StatusSymbol.FATAL, 0, ErrorMessage.IERROR,
							0, 0), 0);
		} else {
			return MultipleValuesFactory.create5(StatusSymbol.DISCONNECTED, 0,
					InfoMessage.DB_CON_CLOSED, 0, 0);
		}
	}	
	
	/**
	 * Returns data associated with a database cursor to G2 in a query item
	 * @param cursor Cursor to start fetching from
	 * @param returnFormat one of ARRAYS or LISTS symbols
	 * @param fetchBatch fetch batch size
	 * @return operation result as a multiple values object
	 */
	@Override
	public MultipleValuesHolder dbFetchQueryItem(DbCursorObject cursor, int returnFormat, int fetchBatch) {
		if (checkConnectionAndMaybeReconnect()) {
			MultipleValuesHolder mvh;
			Class[] at = {DbCursorObject.class, int.class, int.class};
			Object[] args = {cursor, returnFormat, fetchBatch};
			mvh = executeInExceptionContext("dbFetchQueryItem",
					at, args, ErrorMessage.FETCH_QUERY_ITEM_FAILED,
					InfoMessage.FETCH_QUERY_ITEM_SUCCEEDED,
					MultipleValuesFactory.create6(null, StatusSymbol.FATAL,
							0, ErrorMessage.IERROR, 0, 0), 1);
			updateCursorStatus(cursor, mvh.get(1), mvh.get(2),  mvh.get(3));
			return mvh;
		} else {
			return MultipleValuesFactory.create6(null, StatusSymbol.DISCONNECTED, 0,
					InfoMessage.DB_CON_CLOSED, 0, 0);
		}
	}
	
	/**
	 * Fetches a specified number of rows (records) from a database cursor and returns
     * them directly to the attributes of a specified object in G2
	 * @param cursor database cursor to start fetching from
	 * @param queryObject object to return values in
	 * @param fetchBatch fetch batch size
	 * @param sq1Out first output sequence
	 * @param sq2Out second output sequence
	 * @return operation result as a multiple values object
	 */
	@Override
	public MultipleValuesHolder dbFetchRecords(DbCursorObject cursor, Item queryObject, int fetchBatch, Sequence sq1Out, Sequence sq2Out) {
		if (checkConnectionAndMaybeReconnect()) {
			MultipleValuesHolder mvh;
			Class[] at = {DbCursorObject.class, Item.class, int.class, Sequence.class, Sequence.class};
			Object[] args = {cursor, queryObject, fetchBatch, sq1Out, sq2Out};
			mvh = executeInExceptionContext("dbFetchRecords",
					at, args, ErrorMessage.FETCH_RECORDS_FAILED,
					InfoMessage.FETCH_RECORDS_SUCCEEDED,
					MultipleValuesFactory.create5(StatusSymbol.FATAL, 0, ErrorMessage.IERROR,
							0, 0), 0);
			updateCursorStatus(cursor, mvh.get(0), mvh.get(1),  mvh.get(2));
			return mvh;
		} else {
			return MultipleValuesFactory.create6(null, StatusSymbol.DISCONNECTED, 0,
					InfoMessage.DB_CON_CLOSED, 0, 0);
		}
	}
	
	/**
	 * Performs a query and returns the results within a structure where each element of
     * the structure is a name/sequence pair containing one column of database data
	 * @param cursor database cursor to start fetching from
	 * @param rcdsToFetch maximum number of records to fetch
	 * @return operation result as a multiple values object
	 */
	@Override
	public MultipleValuesHolder dbFetchStructure(DbCursorObject cursor, int rcdsToFetch) {
		if (checkConnectionAndMaybeReconnect()) {
			Class[] at = {DbCursorObject.class, int.class};
			Object[] args = {cursor, rcdsToFetch};
			return executeInExceptionContext("dbFetchStructure",
					at, args, ErrorMessage.FETCH_STRUCTURE_FAILED,
					InfoMessage.FETCH_STRUCTURE_SUCCEEDED,
					MultipleValuesFactory.create6(null, StatusSymbol.FATAL, 0,
							ErrorMessage.IERROR, 0, 0), 1);
		} else {
			return MultipleValuesFactory.create6(null, StatusSymbol.DISCONNECTED, 0,
					InfoMessage.DB_CON_CLOSED, 0, 0);
		}
	}
	/**
	 * Refreshes the cursor data and repositions the cursor pointer to the first record in
     * the database cursor
	 * @param cursor database cursor to refresh
	 * @return operation result as a multiple values object
	 */
	@Override
	public MultipleValuesHolder dbRefreshCursor(DbCursorObject cursor) {
		return engine.dbRefreshCursor(cursor);
	}
	
	/**
	 * Returns data associated with a database cursor to an existing query item in G2.
     * The data within the query item may be either replaced or appended
	 * @param cursor database cursor to start fetching from
	 * @param queryItem query item to update
	 * @param updateType one of the REPLACE or APPEND symbols
	 * @param rcdsToUpdate maximum number of records to be updated
	 * @return operation result as a multiple values object
	 */
	@Override
	public MultipleValuesHolder dbUpdateQueryItem(DbCursorObject cursor, DbQueryItem queryItem, int updateType, int rcdsToUpdate) {
		if (checkConnectionAndMaybeReconnect()) {
			MultipleValuesHolder mvh;
			Class[] at = {DbCursorObject.class, DbQueryItem.class, int.class, int.class};
			Object[] args = {cursor, queryItem, updateType, rcdsToUpdate};
			mvh =  executeInExceptionContext("dbUpdateQueryItem",
					at, args, ErrorMessage.UPDATE_QUERY_ITEM_FAILED,
					InfoMessage.UPDATE_QUERY_ITEM_SUCCEEDED,
					MultipleValuesFactory.create5(StatusSymbol.FATAL, 0, ErrorMessage.IERROR,
							0, 0), 0);
			updateCursorStatus(cursor, mvh.get(0), mvh.get(1),  mvh.get(2));
			return mvh;
		} else {
			return MultipleValuesFactory.create5(StatusSymbol.DISCONNECTED, 0,
					InfoMessage.DB_CON_CLOSED, 0, 0);
		}
	}
	/**
	 * Not supported due to JDBC API limitations
	 * @return error status, code and message
	 */
	@Override
	public MultipleValuesHolder dbDisableAllTriggers() {
		return MultipleValuesFactory.create3(StatusSymbol.FATAL, 0, ErrorMessage.TR_NOT_SUPPORTED);
	}
	/**
	 * Not supported due to JDBC API limitations
	 * @return error status, code and message
	 */
	@Override
	public MultipleValuesHolder dbGetTriggers() {
		return MultipleValuesFactory.create5(null, 0, StatusSymbol.FATAL, 0, ErrorMessage.TR_NOT_SUPPORTED);
	}
	/**
	 * Not supported due to JDBC API limitations
	 * @return error status, code and message
	 */
	@Override
	public MultipleValuesHolder dbSetTrigger(Symbol symbol, boolean tv) {
		return MultipleValuesFactory.create3(StatusSymbol.FATAL, 0, ErrorMessage.TR_NOT_SUPPORTED);
	}
	/**
	 * Not supported due to JDBC API limitations
	 * @return error status, code and message
	 */
	@Override
	public MultipleValuesHolder dbSetTriggerObj(Object obj, boolean tv) {
		return MultipleValuesFactory.create3(StatusSymbol.FATAL, 0, ErrorMessage.TR_NOT_SUPPORTED);
	}
	/**
	 * Controls bridge events logging
	 * @param mode logging mode: one of CLOSE or OPEN symbols
	 * @param filter logging messages levels which allowed to go into log 
	 * @param file full path to bridge log file
	 * @return operation result as a multiple values object
	 */
	@Override
	public MultipleValuesHolder dbLogfile(Symbol mode, String filter, String file) {
		boolean status = false;
		if (LogFileOperation.CLOSE.equals(mode)) {
			status = logger.close();
			if (status) {
				return MultipleValuesFactory.create3(StatusSymbol.SUCCESS, 0, InfoMessage.LOGGER_CLOSED);
			} else {
				return MultipleValuesFactory.create3(StatusSymbol.ERROR, 0, ErrorMessage.LOG_CLOSE_FAILED);
			}
		} else if (LogFileOperation.OPEN.equals(mode)) {
			status = logger.reopen(file, filter);
			if (status) {
				return MultipleValuesFactory.create3(StatusSymbol.SUCCESS, 0, InfoMessage.LOGGER_REOPENED);
			} else {
				return MultipleValuesFactory.create3(StatusSymbol.ERROR, 0, ErrorMessage.LOG_REOPEN_FAILED);
			}
		} else {
			return MultipleValuesFactory.create3(StatusSymbol.ERROR, 0, ErrorMessage.LOG_CNTRL_INVALID);
		}
	}
	
	/**
	 * Not supported in this bridge
	 */
	@Override
	public MultipleValuesHolder dbRedirectCallback() {
		logger.warning(WarningMessage.INVALID_CALL);
		return MultipleValuesFactory.create3(StatusSymbol.FATAL, 0, ErrorMessage.DB_RC_NOT_SUPPORTED);
		
	}
	
	/**
	 * Disconnects bridge instance from database
	 * @return operation result as a multiple values object
	 */
	@Override
	public MultipleValuesHolder dbDisconnect() {
		if (dbConnection != null) {
			try {
				dbConnection.close();
				dbConnection = null;
				connectionAlive = false;
			} catch (SQLException e) {
				logger.severe(ErrorMessage.DISCONN_ERR);
				logger.severe(e.getMessage());
				return MultipleValuesFactory.create3(StatusSymbol.ERROR,
						e.getErrorCode(), e.getMessage());
			}
		}
		logger.info(InfoMessage.B_DISCONN_OK);
		return MultipleValuesFactory.create3(StatusSymbol.SUCCESS, 0, InfoMessage.B_DISCONN_OK);
	}
	/**
	 * Terminates bridge instance
	 * @return operation result as a multiple values object
	 */
	@Override
	public MultipleValuesHolder dbKillBridge() {
		Console.puts(InfoMessage.BRIDGE_KILLED);
		dbDisconnect();
		logger.info(InfoMessage.BRIDGE_KILLED);
		System.exit(0);
		return MultipleValuesFactory.create3(StatusSymbol.SUCCESS, 0, InfoMessage.BRIDGE_KILLED);
	}
	/**
	 * Tests if underlying database connection is alive
	 * @return operation result as a multiple values object
	 */
	@Override
	public MultipleValuesHolder dbPing() {
		try {
			if (connectionAlive && !dbConnection.isClosed()) {
				return MultipleValuesFactory.create3(StatusSymbol.SUCCESS, 0, InfoMessage.DB_CON_OK);
			}
		} catch (SQLException e) {
			connectionAlive = false;
			return MultipleValuesFactory.create3(StatusSymbol.ERROR, e.getErrorCode(),
					ErrorMessage.CON_CHK_FAILED);
		}
		return MultipleValuesFactory.create3(StatusSymbol.DISCONNECTED, 0,
				InfoMessage.DB_CON_CLOSED);
	}
	/**
	 * Examines underlying database for additional features support
	 * @param dbmtd DatabaseMetaData of underlying database
	 */
	private void analyzeDatabaseMetaData(DatabaseMetaData dbmtd) {
		try {
			driverSupportsStoredProcedures = dbmtd.supportsStoredProcedures();
		} catch (SQLException se) {
			logger.warning(WarningMessage.STORED_PROC_STATUS_UNK);
		}
	}
	
	/**
	 * Determines SQL NULL replacement for binding
	 * @return SQL NULL replacement
	 */
	private Object getNullBindingReplacement() {
		int flag = bridgeConf.getSetNullOptions();
		if (flag < 10) {
			return bridgeConf.getSetNullNumber();
		} else if (flag < 100) {
			return bridgeConf.getSetNullString();
		} else {
			return null;
		}
	}
	/**
	 * Determines SQL NULL replacement for fetching
	 * @return SQL NULL replacement
	 */
	private Object getNullFetchingReplacement() {
		int flag = bridgeConf.getSetNullOptions();
		if (flag < 10) {
			return bridgeConf.getNullNumber();
		} else if (flag < 100) {
			return bridgeConf.getNullString();
		} else {
			return null;
		}
	}
	
	public BridgeParameters getBridgeParameters() {
		return bridgeParameters;
	}

	public void setBridgeParameters(BridgeParameters bridgeParameters) {
		this.bridgeParameters = bridgeParameters;
	}
	
	/**
	 * Checks underlying connection and attempts to reconnect 
	 * if flag autoReconnect is set in the bridge configuration
	 * @return true if connection is alive, false otherwise
	 */
	private boolean checkConnectionAndMaybeReconnect() {
		if (connectionAlive) {
			return true;
		}
		if (bridgeConf.isAutoReconnectSet()) {
			MultipleValuesHolder mvh = dbConnect(conUserName, conPassword, conStr);
			if (StatusSymbol.SUCCESS.equals(mvh.getFirst())) {
				return true;
			}
		}
		return false;
	}
	
	/**
	 * Executes QueryProcessor instance method and handles its side effects
	 * @param methodName method name to execute
	 * @param argTypes method argument types enumeration
	 * @param args method arguments array
	 * @param errorMessage error message for case when method execution fails
	 * @param infoMessage info message for case when method execution succeeds
	 * @param retTemplate return value for method for case when its invocation fails
	 * @param statusIndex StatusSymbol position in the method return value
	 * @return method execution result as multiple values object
	 */
	private MultipleValuesHolder executeInExceptionContext(String methodName,
			Class[] argTypes, Object[] args,
			String errorMessage, String infoMessage,
			MultipleValuesHolder retTemplate, int statusIndex) {
		MultipleValuesHolder mvh = null;
		int eCode = 0;
		String msg  = "An internal error in the bridge has occured";
		Method m = null;
		try {
			m = engine.getClass().getMethod(methodName, argTypes);
		} catch (NoSuchMethodException nsme) {
			logger.severe("FATAL ERROR: No method definition found for "
					+ methodName);
			return retTemplate;
		}
		try {
			mvh = (MultipleValuesHolder)m.invoke(engine, args);
			logger.info(infoMessage);
			return mvh;
		
		} catch (IllegalAccessException iae) {
			logger.severe(ErrorMessage.EMSG + iae.getMessage());
			return retTemplate;
		} catch (IllegalArgumentException iae) {
			logger.severe(ErrorMessage.EMSG + iae.getMessage());
			return retTemplate;
		} catch  (NullPointerException npe) {
			logger.severe(ErrorMessage.EMSG + npe.getMessage());
			return retTemplate;
		} catch (ExceptionInInitializerError eie) {
			logger.severe(ErrorMessage.EMSG + eie.getMessage());
			return retTemplate;
		} catch (InvocationTargetException e) {
			Throwable cause = e.getCause();
			if (cause instanceof SQLException) {
				eCode = ((SQLException)cause).getErrorCode();
				msg = cause.getMessage();
			} else {
				msg = cause.toString();
			}
			retTemplate.set(statusIndex, StatusSymbol.ERROR);
			retTemplate.set(statusIndex + 1, eCode);
			retTemplate.set(statusIndex + 2, msg);
			logger.severe(errorMessage);
			logger.severe(ErrorMessage.EMSG + msg);
			return retTemplate;
		} 
	}
}
