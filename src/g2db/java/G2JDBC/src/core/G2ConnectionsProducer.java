package core;

import com.gensym.jgi.G2Connection;
import com.gensym.jgi.G2ConnectionHandlerFactory;
import com.gensym.jgi.G2Gateway;

import java.util.List;
import java.util.ArrayList;
/**
 * This class intended to create G2Connections for clients
 * and run connections checker thread once
 * @author SoftServe
 *
 */
public class G2ConnectionsProducer implements G2ConnectionHandlerFactory, Runnable {

	/**
	 * Related to the command line option 
	 * -shutdown_on_disconnect
	 */
	private boolean exitOnDisconnect = false;
	/**
	 * Indicates if there is at least one accepted connection
	 */
	private boolean anyConnectionAccepted = false;
	/**
	 * Thread where connections activity check is performed
	 */
	private Thread connectionsCheckerThread = null;
	/**
	 * Stores all created G2 Gateways
	 */
	private List<G2Gateway> gateways;
	/**
	 * Time interval between connections activity checks
	 */
	private static final long CHECK_TIMEOUT = 12000;
	
	/**
	 * Creates G2 Connections Producer
	 * @param haltOnDisconnect indicates if system will exit on last G2 Connection closing
	 */
	public G2ConnectionsProducer(boolean haltOnDisconnect) {
		exitOnDisconnect = haltOnDisconnect;
		gateways = new ArrayList<G2Gateway>();
	}
	/**
	 * Creates new G2 Connection
	 * @param connection_data configuration options for this connection
	 * @return created G2Connection instance
	 */
	@Override
	public G2Connection createG2Connection(String connection_data) {
		G2Gateway new_gateway = new G2Gateway();
		new G2JDBCBridge(new_gateway, connection_data);
		if(!anyConnectionAccepted && exitOnDisconnect) {
			anyConnectionAccepted = true;
			connectionsCheckerThread = new Thread(this);
			connectionsCheckerThread.start();
		}
		gateways.add(new_gateway);
		return new_gateway;
	}
	/**
	 * Connections activity checker thread
	 */
	@Override
	public void run() {
		do {
			try {
				Thread.sleep(CHECK_TIMEOUT);
			} catch (InterruptedException ioe) {
				//TODO: what should be here?
			}
			int gcount = gateways.size();
			boolean isAnyAliveConn = false;
			for (int i = 0; i < gcount; i++) {
				G2Gateway g2g = gateways.get(i);
				isAnyAliveConn |= g2g.isAlive();
				if(isAnyAliveConn) {
					break;
				}
			}
			if (!isAnyAliveConn) {
				System.exit(0);
			}
 		} while (true);
	}
}
