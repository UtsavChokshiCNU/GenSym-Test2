package exception;

/**
 * Holds warning messages.
 * @author SoftServe
 *
 */
public class WarningMessage {

	public static final String LOG_FILE_NOT_SPEC = 
		"Warning: Log file name is not specified";
	public static final String STORED_PROC_STATUS_UNK = 
		"Stored procedures support can not be determined from Database MetaData";
	public static final String STORED_PROC_RET_NO_VALUE = 
		"Stored procedure unexpectedly returned no value";
	public static final String NO_SUCH_ATTRIBUTE = 
		"No such attribute ";
	public static final String WRONG_CURSOR_OBJECT = 
		"Wrong cursor object";
	public static final String SQL_FUNC_RET_NULL = 
		"Executed SQL function returned no result";
	public static final String NULL_CHARSET = 
		"Warning: empty charset usage";	
	public static final String BIND_VARS_MAX_REACHED = 
		"Warning: Bridge reached maximum bind variables count while preparing SQL query";	
	public static final String INVALID_CALL = 
		"Warning: attempt to call unsupported method";	
}
