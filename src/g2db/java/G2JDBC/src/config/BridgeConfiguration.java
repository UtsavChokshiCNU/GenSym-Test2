package config;

/**
 * This class stores parameters set by dbConfiguration
 * @author SoftServe
 *
 */
public class BridgeConfiguration {
	public BridgeConfiguration() {
		
	}
	public int getKbVersion() {
		return kbVersion;
	}
	public void setKbVersion(int kbVersion) {
		this.kbVersion = kbVersion;
	}
	public String getContextName() {
		return contextName;
	}
	public void setContextName(String contextName) {
		this.contextName = contextName;
	}
	public String getLogFileName() {
		return logFileName;
	}
	public void setLogFileName(String logFileName) {
		this.logFileName = logFileName;
	}
	public boolean isAutoReconnectSet() {
		return autoReconnectSet;
	}
	public void setAutoReconnectSet(boolean autoReconnectSet) {
		this.autoReconnectSet = autoReconnectSet;
	}
	public int getMaxDefinableCursors() {
		return maxDefinableCursors;
	}
	public void setMaxDefinableCursors(int maxDefinableCursors) {
		this.maxDefinableCursors = maxDefinableCursors;
	}
	public boolean isMessagingEnabled() {
		return messagingEnabled;
	}
	public void setMessagingEnabled(boolean messagingEnabled) {
		this.messagingEnabled = messagingEnabled;
	}
	public String getNullString() {
		return nullString;
	}
	public void setNullString(String nullString) {
		this.nullString = nullString;
	}
	public int getNullNumber() {
		return nullNumber;
	}
	public void setNullNumber(int nullNumber) {
		this.nullNumber = nullNumber;
	}
	public String getSetNullString() {
		return setNullString;
	}
	public void setSetNullString(String setNullString) {
		this.setNullString = setNullString;
	}
	public int getSetNullNumber() {
		return setNullNumber;
	}
	public void setSetNullNumber(int setNullNumber) {
		this.setNullNumber = setNullNumber;
	}
	public int getSetNullOptions() {
		return setNullOptions;
	}
	public void setSetNullOptions(int setNullOptions) {
		this.setNullOptions = setNullOptions;
	}

	/**
	 * G2-Database KB version. Not used in this bridge
	 */
	private int kbVersion;
	/**
	 * GSI context name. Not used in this bridge
	 */
	private String contextName;
	/**
	 * Full path to bridge log file
	 */
	private String logFileName;
	/**
	 * If true, bridge will attempt to recover broken connection once per each request
	 */
	private boolean autoReconnectSet;
	/**
	 * Maximum cursor amount for this bridge
	 */
	private int maxDefinableCursors;
	/**
	 * Not used due to JDBC limitations
	 */
	private boolean messagingEnabled;
	/**
	 * SQL NULL replacement for fetching
	 */
	private String nullString;
	/**
	 * Alternative SQL NULL replacement for fetching
	 */
	private int nullNumber;
	/**
	 * SQL NULL placeholder for binding
	 */
	private String setNullString;
	/**
	 * Alternative SQL NULL placeholder for binding
	 */
	private int setNullNumber;
	/**
	 * This option determines which SQL NULL replacement should be used
	 */
	private int setNullOptions;
}
