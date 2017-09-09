package config;

import java.util.regex.Pattern;
import java.util.regex.Matcher;

import core.Console;

/**
 * Parses remote process initialization string
 * @author SoftServe
 *
 */
public class ConfigurationStringParser {

	/**
	 * Copy of parsed string
	 */
	private String confStr = null;
	
	/**
	 * ConfigurationStringParser constructor
	 * @param confStr string which should be parsed
	 */
	public ConfigurationStringParser(String confStr) {
		this.confStr = confStr;
	}
	/**
	 * Searches for known switches and options in the parsed string
	 * @return ProcessParameters instance with appropriate fields set to data from parsed string
	 */
	//ignores -p option (triggers)
	public ProcessParameters parseProcessParameters() {
		ProcessParameters pp = new ProcessParameters();
		boolean switchValue = isSwitchSet(ProcessParameters.AUTO_COMMIT);
		pp.setAutoCommit(switchValue);
		String optionValue = getOptionValue(ProcessParameters.MAX_BIND_VARS);
		if (optionValue != null) {
			try {
				pp.setMaxBindVars(Integer.parseInt(optionValue));
			} catch (NumberFormatException nfe) {
				Console.putsWithDate("Not a number: " + optionValue);
				pp.setMaxBindVars(0);
			}
		}
		optionValue = getOptionValue(ProcessParameters.LOGFILE_FILTER);
		pp.setLogFileFilter(optionValue);
		switchValue = isSwitchSet(ProcessParameters.SMART_FETCH);
		pp.setSmartFetch(switchValue);
		optionValue = getOptionValue(ProcessParameters.MAX_BIND_NAME_LEN);
		if (optionValue != null) {
			try {
				pp.setMaxBindNameLen(Integer.parseInt(optionValue));
			} catch (NumberFormatException nfe) {
				Console.putsWithDate("Not a number: " + optionValue);
				pp.setMaxBindNameLen(0);
			}
		}
		switchValue = isSwitchSet(ProcessParameters.DISABLE_CONSOLE_OUT1);
		switchValue |= isSwitchSet(ProcessParameters.DISABLE_CONSOLE_OUT2);
		switchValue |= isSwitchSet(ProcessParameters.DISABLE_CONSOLE_OUT3);
		pp.setDisableConsoleOut(switchValue);
		optionValue = getOptionValue(ProcessParameters.MAX_REGISTERED_ITEMS);
		if (optionValue != null) {
			try {
				pp.setMaxRegisteredItems(Integer.parseInt(optionValue));
			} catch (NumberFormatException nfe) {
				Console.putsWithDate("Not a number: " + optionValue);
				pp.setMaxRegisteredItems(0);
			}
		}
		switchValue = isSwitchSet(ProcessParameters.DISABLE_IO_TIMESTAMP);
		pp.setDisableIOTimestamp(switchValue);
		switchValue = isSwitchSet(ProcessParameters.DISABLE_LOG_TIMESTAMP);
		pp.setDisableLogTimestamp(switchValue);
		
		return pp;
	}
	
	/**
	 * Gets option value from string
	 * @param option option name
	 * @return option value or null if such option is undefined in the parsed string
	 */
	private String getOptionValue(String option) {
		String regex = "(\\b?)" + "(" + option + ")"  + "(\\S+)";
		Pattern p = Pattern.compile(regex);
		Matcher m = p.matcher(confStr);
		m.find();
		try {
			return m.group(3);
		} catch (IllegalStateException ise) {
			return null;
		}
	}
	
	/**
	 * Examines if given switch is set in the parsed string
	 * @param swtch switch name
	 * @return true if switch is set
	 */
	private boolean isSwitchSet(String swtch) {
		String regex = swtch + "\\b";
		Pattern p = Pattern.compile(regex);
		Matcher m = p.matcher(confStr);
		return m.find();
	}
	
}
