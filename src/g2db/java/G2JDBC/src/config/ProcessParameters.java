package config;

/**
 * This class holds options names for the 
 * remote-process-initialization-string parameter
 * @author SoftServe
 *
 */
public final class ProcessParameters {
	public static final String AUTO_COMMIT = "-A";
	public static final String MAX_BIND_VARS = "-b";
	public static final String LOGFILE_FILTER = "-f";
	public static final String SMART_FETCH = "-F";
	public static final String MAX_BIND_NAME_LEN = "-n";
	public static final String DISABLE_CONSOLE_OUT1 = "-c";
	public static final String DISABLE_CONSOLE_OUT2 = "-C";
	public static final String DISABLE_CONSOLE_OUT3 = "-o";
	public static final String POOL_INTERVAL = "-p";
	public static final String MAX_REGISTERED_ITEMS = "-r";
	public static final String DISABLE_LOG_TIMESTAMP = "-t";
	public static final String DISABLE_IO_TIMESTAMP = "-T";
	
	/**
	 * Enables auto commit for entire bridge
	 */
	private boolean autoCommit;
	/**
	 * Maximum amount of bind variables that can be used in single query
	 */
	private int maxBindVars;
	/**
	 * Controls logging level by message type
	 */
	private String logFileFilter;
	/**
	 * Enables smart fetch
	 */
	private boolean smartFetch;
	/**
	 * Not used in this bridge
	 */
	private int maxBindNameLen;
	/**
	 * Disables output to console if true
	 */
	private boolean disableConsoleOut;
	/**
	 * Not used in this bridge due to the triggers absence in JDBC
	 */
	private int poolInterval;
	/**
	 * Maximum registered items for this bridge
	 */
	private int maxRegisteredItems;
	/**
	 * Not used in this bridge
	 */
	private boolean disableLogTimestamp;
	/**
	 * Disables date timestamp for console output
	 */
	private boolean disableIOTimestamp;
	
	/**
	 * Default constructor
	 */
	public ProcessParameters() {
		
	}
	
	public boolean isAutoCommit() {
		return autoCommit;
	}
	public void setAutoCommit(boolean autoCommit) {
		this.autoCommit = autoCommit;
	}
	public int getMaxBindVars() {
		return maxBindVars;
	}
	public void setMaxBindVars(int maxBindVars) {
		this.maxBindVars = maxBindVars;
	}
	public String getLogFileFilter() {
		return logFileFilter;
	}
	public void setLogFileFilter(String logFileFilter) {
		this.logFileFilter = logFileFilter;
	}
	public boolean isSmartFetch() {
		return smartFetch;
	}
	public void setSmartFetch(boolean smartFetch) {
		this.smartFetch = smartFetch;
	}
	public int getMaxBindNameLen() {
		return maxBindNameLen;
	}
	public void setMaxBindNameLen(int maxBindNameLen) {
		this.maxBindNameLen = maxBindNameLen;
	}
	public boolean isDisableConsoleOut() {
		return disableConsoleOut;
	}
	public void setDisableConsoleOut(boolean disableConsoleOut) {
		this.disableConsoleOut = disableConsoleOut;
	}
	public int getPoolInterval() {
		return poolInterval;
	}
	public void setPoolInterval(int poolInterval) {
		this.poolInterval = poolInterval;
	}
	public int getMaxRegisteredItems() {
		return maxRegisteredItems;
	}
	public void setMaxRegisteredItems(int maxRegisteredItems) {
		this.maxRegisteredItems = maxRegisteredItems;
	}
	public boolean isDisableLogTimestamp() {
		return disableLogTimestamp;
	}
	public void setDisableLogTimestamp(boolean disableLogTimestamp) {
		this.disableLogTimestamp = disableLogTimestamp;
	}
	public boolean isDisableIOTimestamp() {
		return disableIOTimestamp;
	}
	public void setDisableIOTimestamp(boolean disableIOTimestamp) {
		this.disableIOTimestamp = disableIOTimestamp;
	}
}
