package core;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;


/**
 * This class is responsible for creating, destroying \
 * and handling connections to database via JDBC
 * @author SoftServe
 *
 */
public class ConnectionsManager {

	/**
	 * Creates new ConnectionsManager instance
	 * @param driver Underlying JDBC driver full class name
	 * @throws ClassNotFoundException when driver can not be found
	 * @throws InstantiationException on driver instantiation exception
	 * @throws IllegalAccessException on security exception
	 */
	public ConnectionsManager(String driver) throws ClassNotFoundException,
	 InstantiationException, IllegalAccessException {
		Class.forName(driver).newInstance();
	}
	
	/**
	 * Creates new connection to a database
	 * @param user user name
	 * @param password user password
	 * @param conStr database connection string
	 * @return connection to a database through the JDBC driver
	 * @throws SQLException when fails to establish connection
	 */
	public Connection getConnection(String user, String password, String conStr)
	 throws SQLException {
		return DriverManager.getConnection(conStr, user, password);
	}
	
}
