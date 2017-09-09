package core;

/**
 * Invokes bridge main function
 * @author SoftServe
 *
 */
public class ToplevelTests {

	@org.junit.Test
	public void testRuntime() {
		String args[] = {"-help"};
		G2JDBCBridge.main(args);
	}

	
}
