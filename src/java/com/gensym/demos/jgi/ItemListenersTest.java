package com.gensym.demos.jgi;

import com.gensym.classes.Item;
import com.gensym.classes.VariableOrParameter;
import com.gensym.classes.modules.jgidemo.EventSourceClass;
import com.gensym.classes.modules.jgidemo.G2_EventSourceEvent;
import com.gensym.classes.modules.jgidemo.G2_EventSourceListener;
import com.gensym.core.CmdLineArgHandler;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2CommunicationErrorEvent;
import com.gensym.jgi.G2Connection;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.jgi.G2Gateway;
import com.gensym.util.ItemEvent;
import com.gensym.util.ItemListener;
import com.gensym.util.Symbol;
import com.gensym.util.VariableValueEvent;
import com.gensym.util.VariableValueListener;
import com.gensym.jgi.G2ConnectionListener;

public class ItemListenersTest {
	// The correct way to make a Symbol.
	public static final Symbol ITEM_ = Symbol.intern("ITEM");
	public static final Symbol A_TEST_CLASS_INSTANCE_ = Symbol
			.intern("A-TEST-CLASS-INSTANCE");

	public static void main(String[] args) {
		// read command-line
		CmdLineArgHandler cmdLine = new CmdLineArgHandler(args);
		// information for connecting to G2
		String url = cmdLine.getOptionValue("-url");
		String host = cmdLine.getOptionValue("-g2host");
		host = (host == null ? "localhost" : host);
		String port = cmdLine.getOptionValue("-g2port");
		port = (port == null ? "1111" : port);
		// information to find a unique named item in G2
		String classString = cmdLine.getOptionValue("-class");
		String nameString = cmdLine.getOptionValue("-name");
		// convert the strings to symbols
		Symbol clazz = (classString == null ? ITEM_ : Symbol.intern(classString
				.toUpperCase()));
		Symbol name = (nameString == null ? A_TEST_CLASS_INSTANCE_ : Symbol
				.intern(nameString.toUpperCase()));
		// do actual work
		final G2Access context;
		try {
			// connect to G2
			context = G2Gateway.getOrMakeConnection(url, host, port);
			// obtain a java object that represents a G2 ITEM
			Item item = context.getUniqueNamedItem(clazz, name);

			// Define a simple implementation of the ItemListener interface
			ItemListener il = new ItemListener() {
				@Override
				public void itemModified(ItemEvent e) {
					System.out.println("itemModified: " + e);
					try {
						context.callRPC(Symbol.intern("TC33-CALLBACK"),
								new Object[] { e.toString() });
					} catch (G2AccessException e1) {
						e1.printStackTrace();
					}
				}

				@Override
				public void itemDeleted(ItemEvent e) {
					System.out.println("itemDeleted: " + e);
				}

				@Override
				public void receivedInitialValues(ItemEvent e) {
					System.out.println("receivedInitialValues: " + e);
					try {
						context.callRPC(Symbol.intern("TC29-CALLBACK"),
								new Object[] { e.toString() });
					} catch (G2AccessException e1) {
						e1.printStackTrace();
					}
				}
			};
			VariableOrParameter var = (VariableOrParameter) (context
					.getUniqueNamedItem(clazz, Symbol
							.intern("TEST-QUANTITATIVE-PARAMETER")));

			// initiate the subscription
			item.addItemListener(il);

			VariableValueListener vil = new VariableValueListener() {
				@Override
				public void valueChanged(VariableValueEvent e) {
					System.out.println("valueChanged: " + e);
					try {
						context.callRPC(Symbol.intern("TC38-CALLBACK"),
								new Object[] { e.toString() });
					} catch (G2AccessException e1) {
						e1.printStackTrace();
					}
				}

				@Override
				public void receivedInitialValue(VariableValueEvent e) {
					System.out.println("receivedInitialValues: " + e);
					try {
						context.callRPC(Symbol.intern("TC35-CALLBACK"),
								new Object[] { e.toString() });
					} catch (G2AccessException e1) {
						e1.printStackTrace();
					}
				}
			};

			// initiate the subscription
			var.addVariableValueListener(vil);

			G2ConListener list = new G2ConListener((G2Connection) context);
		} catch (Exception ex) {
			System.out.println(ex.getMessage());
			ex.printStackTrace();
			System.exit(-1);
		}
	}
}

class G2ConListener implements G2ConnectionListener, G2_EventSourceListener {
	private G2Connection g2Connection = null;
	private static Class eventSourceClass = EventSourceClass.class;

	public G2ConListener(G2Connection con) {
		this.g2Connection = con;

		con.addG2ConnectionListener(this);
	}

	public void attachToG2EventSource(EventSourceClass eventSource)
			throws G2AccessException {
		eventSource.addG2_EventSourceListener(this);
		System.out.println("Added " + this.toString()
				+ " as listener to Event-Source-Class events");
	}

	@Override
	public void g2ConnectionInitialized(G2ConnectionEvent e) {

	}

	/**
	 * This Method is called when the connected G2 has been paused .
	 */
	@Override
	public void g2IsPaused(G2ConnectionEvent e) {
		System.out.println("G2 Has been paused");
	}

	/**
	 * This method is called when the connected G2 has been resumed.
	 */
	@Override
	public void g2IsResumed(G2ConnectionEvent e) {
		System.out.println("G2 Has been resumed");
	}

	/**
	 * This method is called when the connected G2 has been reset.
	 */
	@Override
	public void g2IsReset(G2ConnectionEvent e) {
		System.out.println("G2 Has been reset");
	}

	/**
	 * This method is called when the connected G2 has been started.
	 */
	@Override
	public void g2IsStarted(G2ConnectionEvent e) {
		System.out.println("G2 Has been Started");
	}

	/**
	 * Called when G2 sends a message to the G2Connection.
	 */
	@Override
	public void g2MessageReceived(G2ConnectionEvent e) {
		System.out.println("Message received from G2 was: " + e.getMessage());

		try {
			g2Connection.callRPC(Symbol.intern("TC46-CALLBACK"),
					new Object[] { e.getMessage() });
		} catch (G2AccessException e1) {
			e1.printStackTrace();
		}
	}

	/**
	 * Called when an asynchronous error has occured in the G2 communications
	 * interface for the G2Connection
	 * 
	 *@param error_event
	 *            An G2CommunicationErrorEvent describing the error that
	 *            occured.
	 */
	@Override
	public void communicationError(G2CommunicationErrorEvent error_event) {
		System.out.println(error_event.getMessage());
	}

	/**
	 * Called when the network cannot deliver data that Java is attempting to
	 * write to G2.
	 */
	@Override
	public void readBlockage(G2ConnectionEvent event) {
	}

	/**
	 * Called when the network cannot deliver data that G2 is attempting to
	 * write to Java.
	 */
	@Override
	public void writeBlockage(G2ConnectionEvent event) {
	}

	/**
	 * This method is called when the G2 connection has been shutdown.
	 */
	@Override
	public void g2ConnectionClosed(G2ConnectionEvent e) {
		System.out.println("G2 Connection has been closed ");
	}

	@Override
	public void anEvent(G2_EventSourceEvent arg1) throws G2AccessException {
		System.out.println("Received an event from " + arg1.getSource() + "..."
				+ arg1.getMessage());

	}

}
