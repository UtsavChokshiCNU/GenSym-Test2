package exception;

/**
 * 
 * @author SoftServe
 *
 */
public class ErrorMessage {
	
	public static final String NO_JDBC_DRIVER = 
		"Error: command-line parameter \"-driver\" is missing";
	public static final String JDBC_REG_FAILED = 
		"Failed to register JDBC driver";
	public static final String CONN_BROKEN = 
		"Bridge has no valid connection to database";
	public static final String SP_NOT_SUPPORTED = 
		"Stored procedures are not supported by this JDBC driver";
	public static final String TR_NOT_SUPPORTED = 
		"Triggers can not be used form JDBC API";
	public static final String LOG_FILE_OPEN_FAILED = 
		"Error: can not open file for logging: ";
	public static final String LOGGER_BROKEN = 
		"Logger can not be used";
	public static final String CONNECT_FAILED = 
		"Connection to database failed";
	public static final String MD_ANALYSIS_FAILED = 
		"Database MetaData analysis failed";
	public static final String EMSG = "Error Message: ";
	public static final String DISCONN_ERR = 
		"Error on disconnect from database";
	public static final String CON_CHK_FAILED = 
		"Failed to check connection status";
	public static final String IMM_EXEC_FAILED = 
		"Immediate SQL execution failed";
	public static final String DB_RC_NOT_SUPPORTED = 
		"dbRedirectCallback is not supported in this bridge";
	public static final String DEFINE_CURSOR_FAILED = 
		"Define cursor failed";
	public static final String SET_CURSOR_FAILED = 
		"Set cursor failed";	
	public static final String INCORRECT_GDB_VALUE = 
		"Incorrect GDB value was provided";
	public static final String WRONG_RETURN_TYPE = 
		"Wrong return type was specified";	
	public static final String FETCH_QUERY_ITEM_FAILED =
		"Fetch query item failed";
	public static final String UPDATE_QUERY_ITEM_FAILED =
		"Update query item failed";
	public static final String FETCH_STRUCTURE_FAILED = 
		"Fetch structure failed";
	public static final String FETCH_OBJECT_FAILED = 
		"Fetch object failed";
	public static final String SQL_OBJ_DEF_FAILED = 
		"SQL object definition failed";
	public static final String BINDING_FAILED = 
		"Failed to bind variables";
	public static final String SQL_EXEC_FAILED = 
		"SQL execution failed";
	public static final String FETCH_OBJECTS_LIST_FAILED = 
		"Fetch objects list failed";
	public static final String FETCH_UPDATE_OBJECT_FAILED = 
		"Fetch update object failed";
	public static final String STORED_PROC_EXECUTION_FAILED = 
		"Stored procedure execution failed";
	public static final String FETCH_RECORDS_FAILED = 
		"Fetch records failed";
	public static final String STATEMENT_NOT_FOUND = 
		"Required statement not defined";
	public static final String LOG_CNTRL_INVALID = 
		"Logging control symbol is unknown";
	public static final String LOG_CLOSE_FAILED = 
		"Failed to close logger";	
	public static final String LOG_REOPEN_FAILED = 
		"Failed to open logger";
	public static final String DB_COMMIT_FAILED = 
		"dbCommit failed";	
	public static final String IERROR = 
		"Serious internal error has occured. Please contact Gensym Customer Support";
	public static final String UPDATE_SQL_OBJECT_FAILED = 
		"Failed to updated SQL object";
	public static final String EXEC_SQL_OBJECT_FAILED = 
		"Failed to execute SQL object";	
	
}
