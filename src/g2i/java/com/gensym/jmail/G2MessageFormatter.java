package com.gensym.jmail;

/**
 * <p>Title: </p>
 * <p>Description: </p>
 * <p>Copyright: Gensym Copyright (c) 2004-2006</p>
 * <p>Company: Gensym Corporation</p>
 * @author not attributable
 * @version 1.0
 */

import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * @author pprintz
 *
 */
public class G2MessageFormatter {

	/**
	 * Simple class to add a timestamp to a log message
	 */

	private static final ThreadLocal<SimpleDateFormat> FORMATTER = new ThreadLocal<SimpleDateFormat>(){

		@Override
		protected SimpleDateFormat initialValue() {
			return new SimpleDateFormat("ddMMMyyyy HH:mm:ss");
		}
	};
	
	public static String format(int level, String message) {
		return "[" + FORMATTER.get().format(new Date()) + "] [" + level + "] " + message;
	}
}