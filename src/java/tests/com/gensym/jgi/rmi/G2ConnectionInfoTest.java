package com.gensym.jgi.rmi;

import com.gensym.jgi.G2ConnectionInfo;
import com.gensym.message.Resource;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;

public class G2ConnectionInfoTest {
	private static int lastInteger = 1;

	private G2ConnectionInfo g2ConnectionInfo;
	private String brokerUrl = anyString();
	private String logicalName = anyString();
	private String hostName = anyString();
	private String portName = Integer.toString(anyInteger());
	private String connectionClassName = anyString();
	private String gsiInterfaceClassName = anyString();
	private String g2ConnectionClassName = anyString();
	private String interfaceName = anyString();
	private String protocol = anyString();
	private String remoteProcessInitializationString = anyString();

	@Before
	public void init() {
		g2ConnectionInfo = new G2ConnectionInfo(brokerUrl, logicalName, hostName, portName, connectionClassName, gsiInterfaceClassName, interfaceName, protocol, false, remoteProcessInitializationString);
	}

	@Test
	public void test_initialize_success_returnsG2ConnectionInfoInstance() {
		G2ConnectionInfo.setDefaultLogicalName(anyString());
		G2ConnectionInfo.setDefaultPortName(Integer.toString(anyInteger()));
		G2ConnectionInfo.setDefaultGsiInterfaceClassName(anyString());
		G2ConnectionInfo.setDefaultProtocol(anyString());
		G2ConnectionInfo.setDefaultRpis(anyString());

		g2ConnectionInfo = new G2ConnectionInfo();
		assertNotNull(g2ConnectionInfo);

		g2ConnectionInfo = new G2ConnectionInfo(brokerUrl, logicalName, hostName, portName, connectionClassName, gsiInterfaceClassName, interfaceName, protocol, false, remoteProcessInitializationString);
		assertNotNull(g2ConnectionInfo);

		g2ConnectionInfo = new G2ConnectionInfo(hostName, portName);
		assertNotNull(g2ConnectionInfo);

		g2ConnectionInfo = new G2ConnectionInfo(brokerUrl, logicalName, hostName, portName, connectionClassName, gsiInterfaceClassName, interfaceName, protocol, false, remoteProcessInitializationString, false, false);
		assertNotNull(g2ConnectionInfo);

		g2ConnectionInfo = new G2ConnectionInfo(hostName, portName, false);
		assertNotNull(g2ConnectionInfo);

		g2ConnectionInfo = new G2ConnectionInfo(brokerUrl, hostName, portName);
		assertNotNull(g2ConnectionInfo);

		g2ConnectionInfo = new G2ConnectionInfo(brokerUrl, logicalName, hostName, portName, connectionClassName, gsiInterfaceClassName, interfaceName, protocol, false, remoteProcessInitializationString, false, false, false);
		assertNotNull(g2ConnectionInfo);

		g2ConnectionInfo = new G2ConnectionInfo(brokerUrl, hostName, portName, false, false);
		assertNotNull(g2ConnectionInfo);

		g2ConnectionInfo = new G2ConnectionInfo(brokerUrl, hostName, portName, g2ConnectionClassName, gsiInterfaceClassName);
		assertNotNull(g2ConnectionInfo);

		g2ConnectionInfo = new G2ConnectionInfo(brokerUrl, hostName, portName, g2ConnectionClassName, gsiInterfaceClassName, false, false);
		assertNotNull(g2ConnectionInfo);
	}

	@Test
	public void test_initialize_brokerUrlIsNullReference_setsGsiProtocol() {
		// Arrange
		g2ConnectionInfo = new G2ConnectionInfo(null, logicalName, hostName, portName, connectionClassName, gsiInterfaceClassName, interfaceName, null, false, remoteProcessInitializationString);

		// Act & Assert
		assertEquals(G2ConnectionInfo.GSI_PROTOCOL, g2ConnectionInfo.getProtocol());
	}

	// Assert
	@Test(expected = IllegalArgumentException.class)
	public void test_initialize_brokerUrlIsNullReferenceAndProtocolIsNotGsi_throwsIllegalArgumentException() {
		// Arrange
		// Nothing to arrange

		// Act
		g2ConnectionInfo = new G2ConnectionInfo(null, logicalName, hostName, portName, connectionClassName, gsiInterfaceClassName, interfaceName, G2ConnectionInfo.RMI_PROTOCOL, false, remoteProcessInitializationString);
	}

	@Test
	public void test_getBrokerURL_always_returnsBrokerUrl() {
		assertEquals(brokerUrl, g2ConnectionInfo.getBrokerURL());
	}

	@Test
	public void test_getHost_always_returnsHost() {
		assertEquals(hostName, g2ConnectionInfo.getHost());
	}

	@Test
	public void test_getPort_always_returnsPort() {
		assertEquals(portName, g2ConnectionInfo.getPort());
	}

	@Test
	public void test_getSecure_always_returnsSecureFlag() {
		this.g2ConnectionInfo = new G2ConnectionInfo(
				anyString(),
				anyString(),
				anyString(),
				Integer.toString(anyInteger()),
				anyString(),
				anyString(),
				anyString(),
				anyString(),
				anyBoolean(),
				anyString(),
				anyBoolean(),
				anyBoolean(),
				false);

		assertFalse(g2ConnectionInfo.getSecure());

		this.g2ConnectionInfo = new G2ConnectionInfo(
				anyString(),
				anyString(),
				anyString(),
				Integer.toString(anyInteger()),
				anyString(),
				anyString(),
				anyString(),
				anyString(),
				anyBoolean(),
				anyString(),
				anyBoolean(),
				anyBoolean(),
				true);

		assertTrue(g2ConnectionInfo.getSecure());
	}

	@Test
	public void test_getConnectionClassName_always_returnsConnectionClassName() {
		assertEquals(connectionClassName, g2ConnectionInfo.getConnectionClassName());
	}

	@Test
	public void test_getGsiInterfaceClassName_always_returnsGsiInterfaceClassName() {
		assertEquals(gsiInterfaceClassName, g2ConnectionInfo.getGsiInterfaceClassName());
	}

	@Test
	public void test_getGsiInterfaceName_always_returnsGsiInterfaceName() {
		assertEquals(interfaceName, g2ConnectionInfo.getGsiInterfaceName());
	}

	@Test
	public void test_getInterfaceName_always_returnsGsiInterfaceName() {
		assertEquals(interfaceName, g2ConnectionInfo.getInterfaceName());
	}

	@Test
	public void test_getRpis_always_returnsGsiInterfaceName() {
		assertEquals(remoteProcessInitializationString, g2ConnectionInfo.getRpis());
	}

	@Test
	public void test_getRemoteProcessInitString_always_returnsGsiInterfaceName() {
		assertEquals(remoteProcessInitializationString, g2ConnectionInfo.getRemoteProcessInitString());
	}

	@Test
	public void test_getPermanent_always_returnsIsPermanentFlag() {
		this.g2ConnectionInfo = new G2ConnectionInfo(
				brokerUrl,
				logicalName,
				hostName,
				portName,
				connectionClassName,
				gsiInterfaceClassName,
				interfaceName,
				protocol,
				false,
				remoteProcessInitializationString);
		assertFalse(g2ConnectionInfo.getPermanent());

		this.g2ConnectionInfo = new G2ConnectionInfo(
				brokerUrl,
				logicalName,
				hostName,
				portName,
				connectionClassName,
				gsiInterfaceClassName,
				interfaceName,
				protocol,
				true,
				remoteProcessInitializationString);
		assertTrue(g2ConnectionInfo.getPermanent());
	}

	@Test
	public void test_isSharable_always_returnsSharableFlag() {
		this.g2ConnectionInfo = new G2ConnectionInfo(
				anyString(),
				anyString(),
				anyString(),
				Integer.toString(anyInteger()),
				anyString(),
				anyString(),
				anyString(),
				anyString(),
				anyBoolean(),
				anyString(),
				anyBoolean(),
				false,
				anyBoolean());

		assertFalse(g2ConnectionInfo.isSharable());

		this.g2ConnectionInfo = new G2ConnectionInfo(
				anyString(),
				anyString(),
				anyString(),
				Integer.toString(anyInteger()),
				anyString(),
				anyString(),
				anyString(),
				anyString(),
				anyBoolean(),
				anyString(),
				anyBoolean(),
				true,
				anyBoolean());

		assertTrue(g2ConnectionInfo.isSharable());
	}

	@Test
	public void test_isForceNew_always_returnsForceNewFlag() {
		this.g2ConnectionInfo = new G2ConnectionInfo(
				anyString(),
				anyString(),
				anyString(),
				Integer.toString(anyInteger()),
				anyString(),
				anyString(),
				anyString(),
				anyString(),
				anyBoolean(),
				anyString(),
				false,
				anyBoolean(),
				anyBoolean());

		assertFalse(g2ConnectionInfo.isForceNew());

		this.g2ConnectionInfo = new G2ConnectionInfo(
				anyString(),
				anyString(),
				anyString(),
				Integer.toString(anyInteger()),
				anyString(),
				anyString(),
				anyString(),
				anyString(),
				anyBoolean(),
				anyString(),
				true,
				anyBoolean(),
				anyBoolean());

		assertTrue(g2ConnectionInfo.isForceNew());
	}

	@Test
	public void test_matches_brokerUrlDoesNotMatch_returnsFalse() {
		G2ConnectionInfo other = new G2ConnectionInfo(anyString(), logicalName, hostName, portName, connectionClassName, gsiInterfaceClassName, interfaceName, protocol, false, remoteProcessInitializationString);

		// Act & Assert
		assertFalse(g2ConnectionInfo.matches(other));
	}

	@Test
	public void test_matches_hostNameDoesNotMatch_returnsFalse() {
		// Arrange
		G2ConnectionInfo other = new G2ConnectionInfo(brokerUrl, anyString(), portName, g2ConnectionClassName,
				gsiInterfaceClassName, false, false);

		// Act & Assert
		assertFalse(g2ConnectionInfo.matches(other));
	}

	@Test
	public void test_matches_portDoesNotMatch_returnsFalse() {
		// Arrange
		G2ConnectionInfo g2ConnectionInfo2 = new G2ConnectionInfo(brokerUrl, hostName, Integer.toString(anyInteger()), g2ConnectionClassName,
				gsiInterfaceClassName, false, false);

		// Act & Assert
		assertFalse(g2ConnectionInfo.matches(g2ConnectionInfo2));
	}

	@Test
	public void test_matches_connectionClassNameDoesNotMatch_returnsFalse() {
		G2ConnectionInfo other = new G2ConnectionInfo(brokerUrl, logicalName, hostName, portName, anyString(), gsiInterfaceClassName, interfaceName, protocol, false, remoteProcessInitializationString);

		// Act & Assert
		assertFalse(g2ConnectionInfo.matches(other));
	}

	@Test
	public void test_matches_gsiInterfaceClassNameDoesNotMatch_returnsFalse() {
		G2ConnectionInfo other = new G2ConnectionInfo(brokerUrl, logicalName, hostName, portName, connectionClassName, anyString(), interfaceName, protocol, false, remoteProcessInitializationString);

		// Act & Assert
		assertFalse(g2ConnectionInfo.matches(other));
	}

	@Test
	public void test_matches_objectPropertiesMatch_returnsTrue() {
		G2ConnectionInfo other = new G2ConnectionInfo(brokerUrl, logicalName, hostName, portName, connectionClassName, gsiInterfaceClassName, interfaceName, protocol, false, remoteProcessInitializationString);

		// Act & Assert
		assertTrue(g2ConnectionInfo.matches(other));
	}

	@Test
	public void test_equals_objectsAreEqual_returnsTrue() {
		// Arrange
		G2ConnectionInfo g2ConnectionInfo2 = new G2ConnectionInfo(brokerUrl, logicalName, hostName, portName, connectionClassName, gsiInterfaceClassName, interfaceName, protocol, false, remoteProcessInitializationString);

		// Act & Assert
		assertTrue(this.g2ConnectionInfo.equals(g2ConnectionInfo2));
	}

	@Test
	public void test_equals_objectsIsNullReference_returnsFalse() {
		// Arrange
		// Nothing to arrange

		// Act && Assert
		assertFalse(this.g2ConnectionInfo.equals(null));
	}

	@Test
	public void test_matches_objectIsNullReference_returnsFalse() {
	    // Arrange
	    // Nothing to arrange

	    // Act & Assert
		assertFalse(this.g2ConnectionInfo.matches(null));
	}

	@Test
	public void test_matches_referenceObjectIsNotSharable_returnsFalse() {
		// Arrange
		this.g2ConnectionInfo = new G2ConnectionInfo(
				anyString(),
				anyString(),
				anyString(),
				Integer.toString(anyInteger()),
				anyString(),
				anyString(),
				anyString(),
				anyString(),
				anyBoolean(),
				anyString(),
				anyBoolean(),
				false,
				anyBoolean());

		G2ConnectionInfo other = new G2ConnectionInfo(
				anyString(),
				anyString(),
				anyString(),
				Integer.toString(anyInteger()),
				anyString(),
				anyString(),
				anyString(),
				anyString(),
				anyBoolean(),
				anyString(),
				anyBoolean(),
				anyBoolean(),
				anyBoolean());

		// Act & Assert
		assertFalse(this.g2ConnectionInfo.matches(other));
	}

	@Test
	public void test_hashCode_always_returnsHashcode() {
	    // Arrange
		int hashCode = g2ConnectionInfo.hashCode();
		assertFalse(hashCode == 0);

		// Act & Assert
		assertEquals(hashCode, g2ConnectionInfo.hashCode());
	}

	@Test
	public void test_compareWithNulls_localValueIsNullReference_returnsTrue() {
	    // Arrange
		Object otherValue = anyObject();
		Object defaultValue = anyObject();

	    // Act &  Assert
		assertTrue(G2ConnectionInfo.compareWithNulls(null, otherValue, defaultValue));
	}

	@Test
	public void test_compareWithNulls_localValueIsDefaultValue_returnsTrue() {
		// Arrange
		Object localValue = anyObject();

		// Act &  Assert
		assertTrue(G2ConnectionInfo.compareWithNulls(localValue, null, localValue));
	}

	@Test
	public void test_compareWithNulls_localValueIsNotDefaultValue_returnsFalse() {
		// Arrange
		Object localValue = anyObject();
		Object defaultValue = anyObject();

		// Act &  Assert
		assertFalse(G2ConnectionInfo.compareWithNulls(localValue, null, defaultValue));
	}

	@Test
	public void test_compareWithNulls_localValueIsOtherValue_returnsTrue() {
		// Arrange
		Object localValue = anyObject();
		Object defaultValue = anyObject();

		// Act &  Assert
		assertTrue(G2ConnectionInfo.compareWithNulls(localValue, localValue, defaultValue));
	}

	@Test
	public void test_compareWithNulls_localValueIsNotOtherValue_returnsFalse() {
		// Arrange
		Object localValue = anyObject();
		Object otherValue = anyObject();
		Object defaultValue = anyObject();

		// Act &  Assert
		assertFalse(G2ConnectionInfo.compareWithNulls(localValue, otherValue, defaultValue));
	}

	@Test
	public void test_toString_always_returnsObjectString() {
	    // Arrange
		// Nothing to arrange

	    // Act & Assert
		assertEquals(expectedToString(this.g2ConnectionInfo), this.g2ConnectionInfo.toString());
	}

	// ---- Helper Methods ----

	private static boolean anyBoolean() {
		return lastInteger++ % 2 == 0;
	}

	private static int anyInteger() {
		return lastInteger++;
	}

	private static Object anyObject() {
		return new Object();
	}

	private static String anyString() {
		return "String " + lastInteger++;
	}

	private static String expectedToString(G2ConnectionInfo connectionInfo) {
		return connectionInfo.getClass().getName() + ": " +
			connectionInfo.getBrokerURL() + "|" +
			connectionInfo.getLogicalName() + "|" +
			connectionInfo.getHost() +"|" +
			connectionInfo.getPort() + "|" +
			connectionInfo.getConnectionClassName() + "|" +
			connectionInfo.getGsiInterfaceClassName() + "|" +
			connectionInfo.getGsiInterfaceName() + "|" +
			connectionInfo.getProtocol() + "|" +
			connectionInfo.getPermanent() + "|" +
			connectionInfo.getRemoteProcessInitString() + "|" +
			connectionInfo.isForceNew() + "|" +
			connectionInfo.isSharable();
	}
}
