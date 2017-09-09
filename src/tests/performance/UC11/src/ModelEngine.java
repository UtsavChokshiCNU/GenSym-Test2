import java.io.IOException;
import java.util.Vector;
import java.util.logging.FileHandler;
import java.util.logging.Level;
import java.util.logging.Logger;

import com.gensym.jgi.*;
import com.gensym.core.*;
import com.gensym.util.*;

public class ModelEngine extends G2ConnectionAdapter implements Runnable {

	private Vector<Gateway> gateways;

	private String listenerport = "22222";

	private static Logger logger = Logger.getLogger("com.gensym.me");
	private static FileHandler fh;

	public ModelEngine() {
		gateways = new Vector<Gateway>();
	}

	public void setLogFile(String filename) {
		try {
			fh = new FileHandler(filename);
		} catch (SecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		logger.addHandler(fh);
		logger.setUseParentHandlers(false);
	}

	public void setLoggingEnabled(boolean enabled) {
		if (enabled = true) {
			logger.setLevel(Level.ALL);
		} else {
			logger.setLevel(Level.OFF);
		}
	}

	public void setListenerPort(String port) {
		listenerport = port;
	}

	public void testRPC() {
	}

	public Sequence testRPCData(Sequence input) {
		return input;
	}

	/*
	 * (from interface G2ConnectionListener)
	 * 
	 * When G2 is shutdown and the connection broken then the Mail client is
	 * shut down as well.
	 */
	public void g2ConnectionClosed(G2ConnectionEvent e) {
		Gateway gateway = (Gateway) e.getSource();
		gateways.remove(gateway);
		logger.info("Lost connection with " + gateway.getHostName() + " port "
				+ gateway.getPortNumber());
		System.exit(0);
	}

	/*
	 * (from interface G2ConnectionListener)
	 */
	public void g2ConnectionInitialized(G2ConnectionEvent e) {
		Gateway gateway = (Gateway) e.getSource();
		try {
			logger.info("Connected to " + gateway.g2GetHostName() + " port "
					+ gateway.g2GetPortNumberOrName());
			gateway.setHostName(gateway.g2GetHostName());
			gateway.setPortNumber(gateway.g2GetPortNumberOrName());
		} catch (G2AccessException ex) {
			logger.log(Level.SEVERE, "G2 Connection initialization error", ex);
		}
	}

	public void run() {

		// Setup a connection factory deal
		try {
			G2Gateway
					.initialize(new String[] { "-listenerport", listenerport }); // Initialization
																					// at
																					// class
																					// level
			logger.info("Waiting to accept a connection on port "
					+ listenerport + " ....");
		} catch (AlreadyInitializedException e) {
			logger.log(Level.SEVERE,
					"Connection factory initialization error: " + e.toString());
		}
		try {
			G2Gateway
					.setConnectionHandlerFactory(new G2ConnectionHandlerFactory() { // Attach
						// factory
						// at
						// class
						// level
						public G2Connection createG2Connection(
								String connection_data) {
							Gateway newGateway = new Gateway();
							newGateway
									.addG2ConnectionListener(ModelEngine.this);
							logger.fine("Connection factory started...");
							try {
								java.lang.reflect.Method method;
								method = ModelEngine.this.getClass()
										.getDeclaredMethod("testRPC");
								newGateway.registerJavaMethod(ModelEngine.this,
										method, Symbol.intern("TEST-RPC"),
										false);
								method = ModelEngine.this.getClass()
										.getDeclaredMethod("testRPCData",
												new Class[] { Sequence.class });
								newGateway.registerJavaMethod(ModelEngine.this,
										method, Symbol.intern("TEST-RPCDATA"),
										false);
							} catch (NoSuchMethodException e) {
								logger.log(Level.SEVERE,
										"No such method error", e);
							}
							ModelEngine.this.gateways.add(newGateway);
							return newGateway;
						}
					});
		} catch (Error e) {
			logger.log(Level.SEVERE, "Connection factory deal error.", e);
		}
		;
		G2Gateway.startup(); // Gateway startup at class level

	}

	/*
	 * @param args
	 */
	public static void main(String[] args) {
		// System.out.println("Start Model Engine...");
		CmdLineArgHandler argHandler = new CmdLineArgHandler(args);
		// Create Model Engine instance
		final ModelEngine modelEngine = new ModelEngine();
		// setup logging
		String logFile = argHandler.getOptionValue("-log");
		if (logFile != null) {
			modelEngine.setLogFile(logFile);
			if (logFile.equals("")) {
				modelEngine.setLoggingEnabled(false);
			} else {
				modelEngine.setLoggingEnabled(true);
			}
		}
		// Setup listener port
		String listenerport = argHandler.getOptionValue("-listenerport");
		if (listenerport != null) {
			modelEngine.setListenerPort(listenerport);
		}

		modelEngine.run();
	}

}

/*
 * G2Gateway encapsulation class
 */
class Gateway extends G2Gateway {

	private String hostName;
	private String portNumber;

	public void setHostName(String hostName) {
		this.hostName = hostName;
	}

	public void setPortNumber(String portNumber) {
		this.portNumber = portNumber;
	}

	public String getHostName() {
		return this.hostName;
	}

	public String getPortNumber() {
		return this.portNumber;
	}
}
