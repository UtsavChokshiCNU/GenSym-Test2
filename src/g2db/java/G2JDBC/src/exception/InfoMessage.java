package exception;

/**
 * Holds info-level messages
 * @author SoftServe
 *
 */
public class InfoMessage {

	public static final String LOGGER_STARTED = 
		"G2-JDBC bridge logger started";
	public static final String DB_CONNECT_OK = 
		"Connection to a database was established";
	public static final String B_CONF_OK = 
		"Bridge configuration changed successfully";
	public static final String B_DISCONN_OK = 
		"Connection to a database closed successfully";
	public static final String BRIDGE_KILLED = 
		"Bridge was killed by calling db-kill-bridge";
	public static final String DB_CON_OK = 
		"Connection to a database is alive";
	public static final String DB_CON_CLOSED = 
		"Connection to a database is closed";
	public static final String COMM_PPLAIN_Q = 
		"Committing pending plain SQL queries...";
	public static final String COMM_PREP_Q = 
		"Committing pending prepared SQL queries...";
	public static final String AMOUNT_OF_COMM_PLAIN_Q = 
		"Amount of committed plain queries: ";
	public static final String AMOUNT_OF_COMM_PREP_Q = 
		"Amount of committed prepared queries: ";
	public static final String EXEC_PLAIN_SQL = 
		"Starting immediate execution...";
	public static final String CACHING_SQL = 
		"Caching SQL statement for further commit...";
	public static final String EXEC_IMM_OK =
		"Execute immediate finished successfully";
	public static final String CANCELLING_SQL = 
		"Cancelling changes made since the last commit...";
	public static final String SQL_CANCELLED = 
		"Pending since the last commit SQL statements cancelled";
	public static final String SQL_DEFINED = 
		"SQL statement was defined successfully";
	public static final String SQL_UPDATED = 
		"SQL statement was updated successfully";
	public static final String CURSOR_DEFINED = 
		"Cursor was defined successfully";
	public static final String CURSOR_SET = 
		"Cursor was set successfully";	
	public static final String FETCH_QUERY_ITEM_SUCCEEDED = 
		"Fetch item query succeeded";	
	public static final String UPDATE_QUERY_ITEM_SUCCEEDED = 
		"Update item query succeeded";
	public static final String FETCH_STRUCTURE_SUCCEEDED = 
		"Fetch structure succeeded";
	public static final String FETCH_OBJECT_SUCCEEDED = 
		"Fetch object succeeded";
	public static final String FETCH_OBJECTS_LIST_SUCCEEDED = 
		"Fetch objects list succeeded";	
	public static final String FETCH_UPDATE_OBJECT_SUCCEEDED = 
		"Fetch update object succeeded";		
	public static final String STORED_PROC_RET_OK = 
		"Stored procedure returned value successfully";
	public static final String SQL_EXEC_OK = 
		"SQL execution completed successfully";
	public static final String SQL_QUEUED_OK = 
		"SQL statement successfully marked as pending";
	public static final String LOGGER_CLOSED = 
		"Logger closed successfully";	
	public static final String LOGGER_REOPENED = 
		"Logger reopened successfully";
	public static final String FETCH_RECORDS_SUCCEEDED = 
		"Fetch records successed";
	public static final String SQL_FUNCTION_OK = 
		"SQL Function executed successfully";	
	public static final String DB_COMMIT_OK = 
		"Pending queries committed successfully";
	public static final String UPDATE_SQL_OBJECT_OK = 
		"Successfully updated SQL object";
	public static final String EXEC_SQL_OBJECT_OK = 
		"Successfully executed SQL object";
	
		
}
