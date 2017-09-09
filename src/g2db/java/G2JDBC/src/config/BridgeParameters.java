package config;

/**
 * This class stores global bridge parameters
 * @author SoftServe
 */

public class BridgeParameters {
	
	/**
	 * Port where this bridge will accept connections
	 */
	private String port = "22041";
	/**
	 * The maximum number of database rows that the G2-
     * Database bridge can return to G2 in a single transaction
	 */
	private String maxrows = "200";
	/**
	 * The maximum number of database columns that the G2-
     * Database bridge can return to G2 in a single transaction
	 */
	private String maxcols = "30";
	/**
	 * The text conversion style that the bridge will use to
     * convert between database character sets and G2 character
     * sets
	 */
	private String charset = "ISO-8859-1";
	/**
	 * Halt a bridge when connection to G2 Server is lost
	 */
	private boolean shutdownOnDisconnect = false;
	/**
	 * Displays information about a bridge usage;
	 */
	private boolean helpRequired = false;
	
	/**
	 * Database driver for this bridge instance
	 */
	private String driver = null;
		
	public String getDriver() {
		return driver;
	}

	public void setDriver(String driver) {
		this.driver = driver;
	}

	public boolean isHelpRequired() {
		return helpRequired;
	}

	public void setHelpRequired(boolean helpRequired) {
		this.helpRequired = helpRequired;
	}

	public boolean isShutdownOnDisconnect() {
		return shutdownOnDisconnect;
	}

	public void setShutdownOnDisconnect(boolean shutdownOnDisconnect) {
		this.shutdownOnDisconnect = shutdownOnDisconnect;
	}

	public String getCharset() {
		return charset;
	}

	public void setCharset(String charset) {
		this.charset = charset;
	}

	public String getMaxcols() {
		return maxcols;
	}

	public void setMaxcols(String maxcols) {
		this.maxcols = maxcols;
	}

	public String getMaxrows() {
		return maxrows;
	}

	public void setMaxrows(String maxrows) {
		this.maxrows = maxrows;
	}

	public String getPort() {
		return port;
	}

	public void setPort(String port) {
		this.port = port;
	}

	/**
	 * Default constructor
	 */
	public BridgeParameters() {
		
	}
}
