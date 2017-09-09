package com.gensym.JMibParser;

import java.text.SimpleDateFormat;
import java.util.Date;

public class G2MessageFormatter {

    /** Simple class to add a timestamp to a log message
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