package com.gensym.G2SNMP;

import java.lang.reflect.Field;
import junit.framework.TestCase;
import org.easymock.MockControl;
import com.adventnet.snmp.snmp2.SnmpAPI;
import com.adventnet.snmp.snmp2.UDPProtocolOptions;
import com.gensym.G2SNMP.trapd.TrapDaemon;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2Connection;

public class G2SNMPTest extends TestCase {
	private JsnmpBridge aBridge;
	private MockControl control;
	private G2Connection mockG2connection;
	private SnmpAPI snmpApiD;
	private TrapDaemon trapDaemon;
	private static int port = 2000;
	private String connectionData = "-p 1 -v 2 -d -n " + port;
	private String ppdFileName;
	private String mibNames;
	private UDPProtocolOptions sessionOpt;

	protected void setUp() throws Exception {
		super.setUp();
		control = MockControl.createNiceControl(G2Connection.class);
		mockG2connection = (G2Connection) control.getMock();
		snmpApiD = new SnmpAPI();
	}

	protected void tearDown() throws Exception {
		super.tearDown();
		control = null;
		snmpApiD = null;
		sessionOpt = null;
		trapDaemon = null;
		mockG2connection = null;
		aBridge = null;
	}

	public void testTaskInitException() {
		TaskInitException taskinitexception = new TaskInitException();
	};

	public void testtrapDaemon() throws TaskInitException {
		trapDaemon = new TrapDaemon(snmpApiD, mockG2connection, ppdFileName,
				mibNames, port);
		sessionOpt = (UDPProtocolOptions) trapDaemon.snmpSession
				.getProtocolOptions();
		assertEquals(port, sessionOpt.getLocalPort());
		trapDaemon.finalize();
	};

	public void testg2ConnectionInitialized() throws SecurityException,
			NoSuchFieldException, IllegalArgumentException,
			IllegalAccessException, G2AccessException {
		
		aBridge = new JsnmpBridge(mockG2connection, connectionData);
		Field field = aBridge.getClass().getDeclaredField("snmpApiD");
		field.setAccessible(true);
		field.set(aBridge, snmpApiD);
		
		control.expectAndDefaultReturn(mockG2connection.g2GetHostName(), "local");
		control.expectAndDefaultReturn(mockG2connection.g2GetPortNumberOrName(), "local");
		
		control.replay();
		aBridge.g2ConnectionInitialized(null);
		control.verify();
		
		field = aBridge.getClass().getDeclaredField("trapDaemon");
		field.setAccessible(true);
		trapDaemon = (TrapDaemon) field.get(aBridge);

		sessionOpt = (UDPProtocolOptions) trapDaemon.snmpSession
				.getProtocolOptions();
		assertEquals(port, sessionOpt.getLocalPort());
		trapDaemon.finalize();
	};

}
