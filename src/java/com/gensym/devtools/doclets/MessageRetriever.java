/*
 * @(#)MessageRetriever.java	1.4 98/09/22
 *
 * Copyright 1998 by Sun Microsystems, Inc.,
 * 901 San Antonio Road, Palo Alto, California, 94303, U.S.A.
 * All rights reserved.
 *
 * This software is the confidential and proprietary information
 * of Sun Microsystems, Inc. ("Confidential Information").  You
 * shall not disclose such Confidential Information and shall use
 * it only in accordance with the terms of the license agreement
 * you entered into with Sun.
 */

package com.gensym.devtools.doclets;

import com.sun.javadoc.*;
import java.io.*;
import java.util.*;
import java.lang.*;
import java.text.MessageFormat;


/** 
 * Retrieve and format messages stored in a resource.
 *
 * @since JDK1.2
 * @author Atul M Dambalkar
 * @author Robert Field
*/
public class MessageRetriever {
    private ResourceBundle messageRB;

    /**
     * Initilize the ResourceBundle with the given resource.
     *
     * @param resourcelocation Resource.
     */
    public MessageRetriever(String resourcelocation) {
	try {
	    messageRB = ResourceBundle.getBundle(resourcelocation);
	} catch (MissingResourceException e) {
            throw new Error("Fatal: Resource for javadoc doclets is missing: "+
                             resourcelocation);
	}
    }

    /**
     * get and format message string from resource
     *
     * @param key selects message from resource
     */
    public String getText(String key) {
	return getText(key, (String)null);
    }

    /**
     * Get and format message string from resource
     *
     * @param key selects message from resource
     * @param a1 Argument, to be repalced in the message.
     */
    public String getText(String key, String a1) {
	return getText(key, a1, null);
    }

    /**
     * Get and format message string from resource
     *
     * @param key selects message from resource
     * @param a1 first argument to be replaced in the message.
     * @param a2 second argument to be replaced in the message.
     */
    public String getText(String key, String a1, String a2) {
	return getText(key, a1, a2, null);
    }

    /**
     * Get and format message string from resource
     *
     * @param key selects message from resource
     * @param a1 first argument to be replaced in the message.
     * @param a2 second argument to be replaced in the message.
     * @param a3 third argument to be replaced in the message.
     */
    public String getText(String key, String a1, String a2, String a3) {
	try {
	    String message = messageRB.getString(key);
	    String[] args = new String[3];
	    args[0] = a1;
	    args[1] = a2;
	    args[2] = a3;
	    return MessageFormat.format(message, args);
	} catch (MissingResourceException e) {
	    throw new Error("Fatal: Resource for javadoc is broken. There is no " + key + " key in resource.");
	}
    }
    
    /**
     * Print error message, increment error count.
     *
     * @param msg message to print
     */
   static void printError(String msg) {
	if (Configuration.root != null) {
            Configuration.root.printError(msg);
        } else {
            System.err.println(/* Main.program + ": " + */ msg);
        }
    }    

    /**
     * Print warning message, increment warning count.
     *
     * @param msg message to print
     */
    static void printWarning(String msg) {
	if (Configuration.root != null) {
            Configuration.root.printWarning(msg);
        } else {
            System.err.println(/* Main.program +  ": warning - " + */ "Warning: " + msg);
        }
    }    

    /**
     * Print a message.
     *
     * @param msg message to print
     */
    static void printNotice(String msg) {
	if (Configuration.root != null) {
            Configuration.root.printNotice(msg);
        } else {
            System.err.println(msg);
        }
    }    

    /**
     * Print error message, increment error count.
     *
     * @param key selects message from resource
     */
    public void error(String key) { 
        printError(getText(key)); 
    }

    /**
     * Print error message, increment error count.
     *
     * @param key selects message from resource
     * @param a1 first argument to be replaced in the message.
     */
    public void error(String key, String a1) { 
        printError(getText(key, a1)); 
    }

    /**
     * Print error message, increment error count.
     *
     * @param key selects message from resource
     * @param a1 first argument to be replaced in the message.
     * @param a2 second argument to be replaced in the message.
     */
    public void error(String key, String a1, String a2) { 
        printError(getText(key, a1, a2)); 
    }

    /**
     * Print error message, increment error count.
     *
     * @param key selects message from resource
     * @param a1 first argument to be replaced in the message.
     * @param a2 second argument to be replaced in the message.
     * @param a3 third argument to be replaced in the message.
     */
    public void error(String key, String a1, String a2, String a3) { 
        printError(getText(key, a1, a2, a3)); 
    }

    /**
     * Print warning message, increment warning count.
     *
     * @param key selects message from resource
     */
    public void warning(String key) { 
        printWarning(getText(key)); 
    }

    /**
     * Print warning message, increment warning count.
     *
     * @param key selects message from resource
     * @param a1 first argument to be replaced in the message.
     */
    public void warning(String key, String a1) { 
        printWarning(getText(key, a1)); 
    }

    /**
     * Print warning message, increment warning count.
     *
     * @param key selects message from resource
     * @param a1 first argument to be replaced in the message.
     * @param a2 second argument to be replaced in the message.
     */
    public void warning(String key, String a1, String a2) { 
        printWarning(getText(key, a1, a2)); 
    }

    /**
     * Print warning message, increment warning count.
     *
     * @param key selects message from resource
     * @param a1 first argument to be replaced in the message.
     * @param a2 second argument to be replaced in the message.
     * @param a3 third argument to be replaced in the message.
     */
    public void warning(String key, String a1, String a2, String a3) { 
        printWarning(getText(key, a1, a2, a3)); 
    }

    /**
     * Print a message.
     *
     * @param key selects message from resource
     */
    public void notice(String key) { 
        printNotice(getText(key)); 
    }

    /**
     * Print a message.
     *
     * @param key selects message from resource
     * @param a1 first argument to be replaced in the message.
     */
    public void notice(String key, String a1) { 
        printNotice(getText(key, a1)); 
    }

    /**
     * Print a message.
     *
     * @param key selects message from resource
     * @param a1 first argument to be replaced in the message.
     * @param a2 second argument to be replaced in the message.
     */
    public void notice(String key, String a1, String a2) { 
        printNotice(getText(key, a1, a2)); 
    }

    /**
     * Print a message.
     *
     * @param key selects message from resource
     * @param a1 first argument to be replaced in the message.
     * @param a2 second argument to be replaced in the message.
     * @param a3 third argument to be replaced in the message.
     */
    public void notice(String key, String a1, String a2, String a3) { 
        printNotice(getText(key, a1, a2, a3)); 
    }
}
