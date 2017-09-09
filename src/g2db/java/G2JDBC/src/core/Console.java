package core;

import java.util.Date;
import java.text.SimpleDateFormat;

/**
 * Controls console output.
 * @author SoftServe
 *
 */
public class Console {

	/**
	 * Indicates if output through this Console is enabled
	 */
	private static boolean enabled = true;

	/**
	 * Enables output through this console
	 */
	public static void enable() {
		enabled = true;
	}
	
	/**
	 * Disables output through this console
	 */
	public static void disable() {
		enabled = false;
	}
	
	/**
	 * Prints given string to console
	 * @param s string which should be printed
	 */
	public static void puts(String s) {
		if(enabled) {
			System.out.println(s);
		}
	}
	
	/**
	 * Prints given string, preceded by timestamp
	 * @param s string which should be printed
	 */
	public static void putsWithDate(String s) {
		if (enabled) {
			Date d = new Date();
			SimpleDateFormat sdf = new SimpleDateFormat();
			sdf.applyPattern("yyyy-MM-d H:mm:ss");
			String dateString = sdf.format(d);
			System.out.println(dateString + " " + s);
		}
	}
}
