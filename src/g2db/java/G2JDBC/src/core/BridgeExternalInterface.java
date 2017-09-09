package core;


import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.classes.Item;
import com.gensym.classes.TextList;
import com.gensym.classes.modules.g2database.DbCursorObject;
import com.gensym.classes.modules.g2database.DbQueryItem;
import com.gensym.classes.modules.g2database.DbSqlObject;
import com.gensym.jgi.MultipleValuesHolder;

/**
 * Contains declarations of the bridge public API
 * @author SoftServe
 *
 */
public interface BridgeExternalInterface {
	/**
	 * Establishes a connection between the bridge and the database
	 * @param user database user name
	 * @param password database user password
	 * @param connectionString database connection string
	 * @return operation result as a multiple values object
	 */
	public MultipleValuesHolder dbConnect (String user, String password, String connectionString);
	/**
	 * Establishes a connection between the bridge and the database
	 * @param user database user name
	 * @param password database user password
	 * @param connectionString database connection string
     * @param gsiConnectionString gsi connection string
	 * @return operation result as a multiple values object
	 */
	public MultipleValuesHolder dbConnect (String user, String password, String connectionString, String gsiConnectionString);
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
	public MultipleValuesHolder dbConfiguration
	 (int kbVersion, String contextName, String logFileName, boolean autoReconnect,
	  int maximumDefinableCursors, boolean enableMessaging, String nullString,
	  int nullNumber, String setNullString, int setNullNumber, int setNullOptions);
	/**
	 * Disconnects bridge instance from database
	 * @return operation result as a multiple values object
	 */
	public MultipleValuesHolder dbDisconnect();
	/**
	 * Terminates bridge instance
	 * @return operation result as a multiple values object
	 */
	public MultipleValuesHolder dbKillBridge();
	/**
	 * Tests if underlying database connection is alive
	 * @return operation result as a multiple values object
	 */
	public MultipleValuesHolder dbPing();
	/**
	 * Commits all pending since the last commit queries to underlying database 
	 * @return operation result as a multiple values object
	 */
	public MultipleValuesHolder dbCommit();
	/**
	 * Executes given SQL statement without variables binding
	 * @param stmnt SQL statement to execute
	 * @param autoCommit if true, statement will be committed immediately, otherwise it will be pending till the next dbCommit call 
	 * @return operation result as a multiple values object
	 */
	public MultipleValuesHolder dbExecuteImmediate(String stmnt, boolean autoCommit);
	/**
	 * Defines, modifies or executes given SQL object
	 * @param sqlObject DbSqlObject, related to a query
	 * @param stmnt SQL statement to define, execute or modify
	 * @param controlValue flag which indicates SQL statement definition, modification or execution
	 * @param tl list of variables values to bind
	 * @param ac auto commit flag for this operation
	 * @return operation result as a multiple values object
	 */
	public MultipleValuesHolder dbSetDynamicExec(DbSqlObject sqlObject, String stmnt, int controlValue, TextList tl, boolean ac);
	/**
	 * Executes given SQL-OBJECT
	 * @param sqlObject DbSqlObject for this query
	 * @param vs bind values as string
	 * @param controlValue dispatch value
	 * @param obj bind values holder
	 * @param ac auto commit flag for this query
	 * @return operation result as a multiple values object
	 */
	public MultipleValuesHolder dbExecSQLObj(DbSqlObject sqlObject, String vs, int controlValue, Object obj, boolean ac);
	/**
	 * Executes stored procedure which is not supposed to return a value
	 * @param procCall SQL statement with stored procedure call
	 * @param controlValue not used
	 * @return operation result as a multiple values object
	 */
	public MultipleValuesHolder dbExecStoredProc(String procCall, String controlValue);
	/**
	 * Executes stored procedure which returns a value
	 * @param procName stored procedure name
	 * @param arguments arguments for stored procedure call
	 * @return operation result as a multiple values object
	 */
	public MultipleValuesHolder dbExecStoredProcRet(String procName, String arguments);
	/**
	 * Cancels all pending since the last call to dbCommit queries
	 * @return operation result as a multiple values object
	 */
	public MultipleValuesHolder dbRollback();
	/**
	 * Executes given SQL statements and returns single result
	 * @param stmnt SQL statement to execute
	 * @return operation result as a multiple values object
	 */
	public MultipleValuesHolder dbSQLFunction(String stmnt);
	/**
	 * Modifies given database cursor
	 * @param cursor Cursor to be modified
	 * @param sql SQL statement
	 * @param controlValue dispatch value
	 * @param tl text values as TextList
	 * @return operation result as a multiple values object
	 */
	public MultipleValuesHolder dbSetCursor(DbCursorObject cursor, String sql, int controlValue, TextList tl);
	/**
	 * Fetches  a copy of user-defined object 
	 * @param cursor Cursor position for fetch start
	 * @param mo user-defined object
	 * @param fetchBatch fetch batch size
	 * @param sq1Out first output sequence
	 * @param sq2Out second output sequence
	 * @return operation result as a multiple values object
	 */
	public MultipleValuesHolder dbFetchObjectCopy(DbCursorObject cursor, Item mo, int fetchBatch, Sequence sq1Out, Sequence sq2Out);
	/**
	 * Fetches  a copy of user-defined object as list
	 * @param cursor Cursor position for fetch start
	 * @param mo user-defined object
	 * @param fetchBatch fetch batch size
	 * @param sq1Out first output sequence
	 * @param sq2Out second output sequence
	 * @return operation result as a multiple values object
	 */
	public MultipleValuesHolder dbFetchObjectList(DbCursorObject cursor, Item mo, int fetchBatch, Sequence sq1Out, Sequence sq2Out);
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
	public MultipleValuesHolder dbFetchUpdateObject(DbCursorObject cursor, Item mo, int controlValue, int fetchBatch, Sequence sq1Out, Sequence sq2Out);
	/**
	 * Returns data associated with a database cursor to G2 in a query item
	 * @param cursor Cursor to start fetching from
	 * @param returnFormat one of ARRAYS or LISTS symbols
	 * @param fetchBatch fetch batch size
	 * @return operation result as a multiple values object
	 */
	public MultipleValuesHolder dbFetchQueryItem(DbCursorObject cursor, int returnFormat, int fetchBatch);
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
	public MultipleValuesHolder dbFetchRecords(DbCursorObject cursor, Item queryObject, int fetchBatch, Sequence sq1Out, Sequence sq2Out);
	/**
	 * Performs a query and returns the results within a structure where each element of
     * the structure is a name/sequence pair containing one column of database data
	 * @param cursor database cursor to start fetching from
	 * @param rcdsToFetch maximum number of records to fetch
	 * @return operation result as a multiple values object
	 */
	public MultipleValuesHolder dbFetchStructure(DbCursorObject cursor, int rcdsToFetch);
	/**
	 * Refreshes the cursor data and repositions the cursor pointer to the first record in
     * the database cursor
	 * @param cursor database cursor to refresh
	 * @return operation result as a multiple values object
	 */
	public MultipleValuesHolder dbRefreshCursor(DbCursorObject cursor);
	/**
	 * Returns data associated with a database cursor to an existing query item in G2.
     * The data within the query item may be either replaced or appended
	 * @param cursor database cursor to start fetching from
	 * @param queryItem query item to update
	 * @param updateType one of the REPLACE or APPEND symbols
	 * @param rcdsToUpdate maximum number of records to be updated
	 * @return operation result as a multiple values object
	 */
	public MultipleValuesHolder dbUpdateQueryItem(DbCursorObject cursor, DbQueryItem queryItem, int updateType, int rcdsToUpdate);
	/**
	 * Not supported due to JDBC API limitations
	 * @return error status, code and message
	 */
	public MultipleValuesHolder dbDisableAllTriggers();
	/**
	 * Not supported due to JDBC API limitations
	 * @return error status, code and message
	 */
	public MultipleValuesHolder dbGetTriggers();
	/**
	 * Controls bridge events logging
	 * @param mode logging mode: one of CLOSE or OPEN symbols
	 * @param filter logging messages levels which allowed to go into log 
	 * @param file full path to bridge log file
	 * @return operation result as a multiple values object
	 */
	public MultipleValuesHolder dbLogfile(Symbol mode, String filter, String file);
	/**
	 * Not supported due to the triggers absence.  
	 * @return error status, code and message
	 */
	public MultipleValuesHolder dbRedirectCallback();
	/**
	 * Not supported due to JDBC API limitations
	 * @return error status, code and message
	 */
	public MultipleValuesHolder dbSetTrigger(Symbol symbol, boolean tv);
	/**
	 * Not supported due to JDBC API limitations
	 * @return error status, code and message
	 */
	public MultipleValuesHolder dbSetTriggerObj(Object obj, boolean tv);
}
