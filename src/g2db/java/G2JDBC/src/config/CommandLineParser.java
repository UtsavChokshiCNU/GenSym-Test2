package config;

import exception.InvalidCommandLineException;

/**
 * This class parses bridge application arguments 
 * and returns BridgeParameters instance
 * @author SoftServe
 *
 */
public class CommandLineParser {

	private CommandLineParser() {
		
	}
	
	/**
	 * Parses given command line
	 * @param args command Line which should be parsed
	 * @return BridgeParameters object which represents command line content
	 * @throws InvalidCommandLineException when command line contains option without value
	 */
	public static BridgeParameters parseCommandLine(String[] args)
	 throws InvalidCommandLineException {
		BridgeParameters bridgeParameters = new BridgeParameters();
		String optVal = getOptionValueOrSignalError(args, BridgeOptions.PORT);
		if (optVal != null) {
			bridgeParameters.setPort(optVal);
		}
		optVal = getOptionValueOrSignalError(args, BridgeOptions.DRIVER);
		bridgeParameters.setDriver(optVal);
		optVal = getOptionValueOrSignalError(args, BridgeOptions.MAX_COLUMNS);
		if (optVal != null) {
			bridgeParameters.setMaxcols(optVal);
		}
		optVal = getOptionValueOrSignalError(args, BridgeOptions.MAX_ROWS);
		if (optVal != null) {
			bridgeParameters.setMaxrows(optVal);
		}
		boolean switchValue = examineSwitchValue(args, BridgeOptions.SHUTDOWN_ON_DISCONNECT);
		bridgeParameters.setShutdownOnDisconnect(switchValue);
		switchValue = examineSwitchValue(args, BridgeOptions.HELP);
		bridgeParameters.setHelpRequired(switchValue);
		return bridgeParameters;
	}
	
	/**
	 * Gets option value from command line
	 * @param args command line
	 * @param option option name
	 * @return option value or null if command line has no such option
	 * @throws InvalidCommandLineException when option misses value
	 */
	private static String getOptionValueOrSignalError(String[] args, String option)
	 throws InvalidCommandLineException {
		for (int i=0; i < args.length; i++) {
			if (option.equalsIgnoreCase(args[i])) {
				if (i + 1 < args.length) {
					return args[i + 1];
				} else {
					throw new InvalidCommandLineException();
				}
			}
		}
		return null;
	}
	
	/**
	 * Examines if given switch is present in command line
	 * @param args command line
	 * @param swname switch name
	 * @return true if switch is set, false otherwise
	 */
	private static boolean examineSwitchValue(String[] args, String swname) {
		for(int i = 0; i < args.length; i++) {
			if (swname.equalsIgnoreCase(args[i])) {
				return true;
			}
		}
		return false;
	}
}
