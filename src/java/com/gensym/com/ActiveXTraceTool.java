/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.ActiveXTraceTool.java
 *
 *   Author: Allan Scott
 */
package com.gensym.com;

import com.gensym.tracebeans.TraceTool;
import com.gensym.tracebeans.TraceElementVector;
import com.gensym.tracebeans.TraceElement;

import java.io.ObjectInputStream;
import java.io.IOException;

/** Gensym provides a tracing mechanism for recording the activities of
* Java software.  This mechanism is provided by the com.gensym.message 
* package.  The com.gensym.com package uses this mechanism significantly
* because it provides a means of logging and understanding software that
* can be invaluable in many circumstances
* <p>
* Gensym also provides some visual beans for creating and viewing these
* traces.  These are provided in the com.gensym.tracebeans package.
* <p>
* The com.gensym.com package differs significantly from many java packages
* in that it is heavily dependent on native code contained in JavaContainer.dll.
*<p>
* A trace is normally defined by the following three things:
* <ul>
* <li> A trace level (an integer)
* <li> A trace key (a String)
* <li> A trace class (a String which is a class name) 
* </ul>
* Using the class <code>TraceTool</code> it is possible to interactively
* set up a trace of the activities of the com.gensym.com module.
* <p>
* The motivation for subclassing <code>TraceTool</code> is to provide an
* extra degree of control over the tracing produced by the JavaContainer.dll.
* By setting the property axTraceLevel on an ActiveXTraceTool you are controlling
* whether the JavaContainer.dll will propagate traces to the Java code.  This
* is necessary because there are situations where the tracing produced by 
* JavaContainer is not relevant to the problem being debugged.  There is also
* a significant performance hit in communicating trace messages from native
* code to Java. 
*<p>
* @see com.gensym.tracebeans.TraceTool
* @see com.gensym.message.Trace
* @see com.gensym.message.Message
* @see ActiveXTraceLevels
*/
public class ActiveXTraceTool extends TraceTool
                              implements ActiveXTraceLevels
 {
	
	static final long serialVersionUID = 3313929252610335368L;

	private short axTraceLevel = NativeMethodBroker.getTraceLevel();
      
      /** Construct a new <code>ActiveXTraceTool</code>.  Provides a
      * zero argument constructor so that this can be treated as 
      * a Java bean.  Creating one of these will automatically
      * cause tracing of the com.gensym.com module to take place.
      */
	public ActiveXTraceTool() {
		super();
            TraceElementVector traces = getTraces();
            traces.addElement(new TraceElement("com.gensym.com",
                                               "java.lang.Object",             
                                               AX_MAX_TRACE_LEVEL));
            setIsRunning(true);
            setTraceOn(true);
            setTraces(traces);
	}

      /** Set the trace level that is used by the native dll - 
      * JavaContainer.dll.  The choices among possible traceLevels
      * are summarized by the interface <code>ActiveXTraceLevels</code>
      * @see ActiveXTraceLevels
      */
	public void setAxTraceLevel(short axTraceLevel) {
		NativeMethodBroker.setTraceLevel(axTraceLevel);
		this.axTraceLevel = NativeMethodBroker.getTraceLevel();
	}

      /** Get the trace level that is used by the native dll - 
      * JavaContainer.dll.  The choices among possible traceLevels
      * are summarized by the interface <code>ActiveXTraceLevels</code>
      * @see ActiveXTraceLevels
      */
	public short getAxTraceLevel() {
		axTraceLevel = NativeMethodBroker.getTraceLevel();
		return axTraceLevel;
	}

      /** A convenience method that sets the trace level used by the
      * native dll to ActiveXTraceLevels.AX_ERROR
      */
	public void axDebugErrors () {
		NativeMethodBroker.setTraceLevel(AX_ERROR);
	}

      /** A convenience method that sets the trace level used by the
      * native dll to ActiveXTraceLevels.AX_PROGRESS
      */
	public void axDebugProgressReports () {
		NativeMethodBroker.setTraceLevel(AX_PROGRESS);
	}

      /** A convenience method that sets the trace level used by the
      * native dll to ActiveXTraceLevels.AX_MORE_DETAIL
      */
	public void axDebugMoreDetail () {
		NativeMethodBroker.setTraceLevel(AX_MORE_DETAIL);
	}

      /** A convenience method that sets the trace level used by the
      * native dll to ActiveXTraceLevels.AX_DATA_DUMPS
      */
	public void axDebugDataDumps () {
		NativeMethodBroker.setTraceLevel(AX_DATA_DUMPS);
	}

	private void readObject(ObjectInputStream in) throws IOException {
			try {
				in.defaultReadObject();
				setAxTraceLevel(axTraceLevel);
			}
			catch (Exception e) {
			}
	}

}
