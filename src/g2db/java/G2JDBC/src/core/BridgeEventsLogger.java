package core;

import java.io.IOException;
import java.util.logging.Logger;
import java.util.logging.FileHandler;
import java.util.logging.SimpleFormatter;
import java.util.logging.LogRecord;
import java.util.StringTokenizer;

import exception.ErrorMessage;
import exception.WarningMessage;
import type.LogFilteringLevel;

/**
 * This class is a logger singleton
 * and used by the rest of the bridge code.
 * @author SoftServe
 *
 */
public class BridgeEventsLogger extends Logger {
	
	/**
	 * Handles file I/O for this logger
	 */
	private FileHandler handler = null;
	/**
	 * Full path to log file
	 */
	private String fileName = null;
	/**
	 * Indicates if this logger is active and can log messages
	 */
	private boolean alive = false;
	/**
	 * Indicates if INFO messages are allowed to be logged
	 */
	private boolean infoModeOn = false;
	/**
	 * Indicates if WARNING messages are allowed to be logged
	 */
	private boolean warningModeOn = false;
	/**
	 * Indicates if ERROR messages are allowed to be logged
	 */
	private boolean errorModeOn = false;
	/**
	 * Indicates if timestamp should be removed from log message
	 * Will be true if switch -t is set in dbConfiguration
	 */
	private boolean isTimestampDisabled = false;
	/**
	 * Global logger name for entire application
	 */
	private static final String LOGGER_NAME = "core.BridgeEventsLogger";
	/**
	 * Warning message about writing to inactive logger
	 */
	private static final String INVALID_LOGGER_USAGE = 
		"Warning: Attempt was made to write a message to the closed logger:";
	/**
	 * Warning message about invalid logger mode used
	 */
	private static final String INVALID_MODE = 
		"Warning: Invalid mode used for logger configuration: ";
	
	/**
	 * Creates new logger instance and makes it active
	 * @param fileNameAndOptions configuration string for this logger instance
	 */
	public BridgeEventsLogger(String fileNameAndOptions, boolean disableTimestamp) {
		super(LOGGER_NAME, null);
		isTimestampDisabled = disableTimestamp;
		if (fileNameAndOptions == null || "".equals(fileNameAndOptions)) {
			System.out.println(WarningMessage.LOG_FILE_NOT_SPEC);
			return;
		}	
		fileName = getFileNameFromInitStr(fileNameAndOptions);
		initModesFromInitStr(fileNameAndOptions);
		open(fileName);
	}
	
	/**
	 * Closes logger instance
	 * @return true if logger was closed successfully or is already closed by the call time
	 */
	public boolean close() {
		if (!alive) {
			return true;
		}
		removeHandler(handler);
		handler.close();
		alive = false;
		return true;
	}
	
	/**
	 * Closes and then opens this logger instance
	 * @param file full path to the new log file
	 * @param modes string with logging levels, separated by space or comma
	 * @return true on success, false otherwise
	 */
	public boolean reopen(String file, String modes) {
		boolean retval = close();
		if (!retval) {
			return retval;
		}
		retval = open(file);
		infoModeOn = false;
		warningModeOn = false;
		errorModeOn = false;		
		parseModesString(modes);
		return retval;
	}
	
	/**
	 * Logs INFO message
	 * @param msg message which should be logged
	 */
	@Override
	public void info(String msg) {
		if (alive) {
			if(infoModeOn) {
				super.info(msg);
			}
		} else {
			logToConsole(msg);
		}
	}
	
	/**
	 * Logs WARNING message
	 * @param msg message which should be logged
	 */
	@Override
	public void warning(String msg) {
		if (alive) {
			if(warningModeOn) {
				super.warning(msg);
			}
		} else {
			logToConsole(msg);
		}
	}	
	
	/**
	 * Logs ERROR message
	 * @param msg message which should be logged
	 */
	@Override
	public void severe(String msg) {
		if (alive) {
			if (errorModeOn) {
				super.severe(msg);
			}
		} else {
			logToConsole(msg);
		}
	}	
	
	/**
	 * Logs message to console
	 * @param msg message which should be logged
	 */
	private void logToConsole(String msg) {
		Console.puts(INVALID_LOGGER_USAGE);
		Console.puts(msg);
	}
	
	/**
	 * Opens new file for this logger instance
	 * @param file full path to new log file
	 * @return true if file was attached to logger successfully, false otherwise
	 */
	private boolean open(String file) {
		try {
			handler = new FileHandler(file, false);
			handler.setFormatter(new CustomFormatter());
			addHandler(handler);
		} catch (IOException ioe) {
			Console.puts(ErrorMessage.LOG_FILE_OPEN_FAILED + fileName);
			return false;
		}
		alive = true;
		return true;
	}
	
	/**
	 * Gets file name from logger initialization string
	 * @param initStr logger initialization string
	 * @return logger file name
	 */
	private String getFileNameFromInitStr(String initStr) {
		int firstComma = initStr.indexOf(',');
		if (firstComma == -1) {
			return initStr;
		}
		return initStr.substring(0, firstComma);
	}
	
	/**
	 * Starts initialization of this logger logging modes
	 * @param initStr logger modes, separated by comma or space
	 */
	private void initModesFromInitStr(String initStr) {
		int firstComma = initStr.indexOf(',');
		if (firstComma == -1) {
			infoModeOn = true;
			warningModeOn = true;
			errorModeOn = true;
			return; //no modes supplied
		}
		String modesStr = initStr.substring(firstComma);
		parseModesString(modesStr);
	}
	
	/**
	 * Initializes modes level flags from logger modes string
	 * @param modesString logger modes string
	 */
	private void parseModesString(String modesString) {
		//we should separate two cases here:
		//commas and spaces
		StringTokenizer tokenizer = null;
		if (modesString.contains(",")) {
			tokenizer = new StringTokenizer(modesString, ",");
		} else {
			tokenizer = new StringTokenizer(modesString, " ");
		}
		while(tokenizer.hasMoreTokens()) {
			String token = tokenizer.nextToken();
			token = token.trim();
			if (token.equalsIgnoreCase(LogFilteringLevel.ALL)) {
				infoModeOn = true;
				warningModeOn = true;
				errorModeOn = true;
			} else if (token.equalsIgnoreCase(LogFilteringLevel.FATAL)
					|| token.equalsIgnoreCase(LogFilteringLevel.ERROR)) {
				errorModeOn = true;
			} else if (token.equalsIgnoreCase(LogFilteringLevel.WARN1)
					|| token.equalsIgnoreCase(LogFilteringLevel.WARN2)) {
				warningModeOn = true;
			} else if (token.equalsIgnoreCase(LogFilteringLevel.INFO)) {
				infoModeOn = true;
			} else {
				Console.puts(INVALID_MODE + token);
			}
		}
 	}

	/**
	 * This class is used to remove log timestamp
	 * @author SoftServe
	 *
	 */
	class CustomFormatter extends SimpleFormatter {
		
		/**
		 * Default constructor
		 */
		public CustomFormatter () {
			super();
		}
		
		/**
		 * This method cuts timestamp from log message when outer class variable 
		 * isTimestampDisabled is set.
		 * @param lr LogRecord to format
		 * @return formatted log record as String
		 */
		@Override
		public String format(LogRecord lr) {
			String msg = super.format(lr);
			if (isTimestampDisabled) {
				int msgStart = msg.indexOf(LOGGER_NAME);
				msg = msg.substring(msgStart);
			}
			return msg;
		}
	}
}
