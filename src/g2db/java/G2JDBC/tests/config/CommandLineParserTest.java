package config;

import static org.junit.Assert.*;

/**
 * Tests command line parser
 * @author SoftServe
 *
 */
public class CommandLineParserTest {
	
	private final String[] cmdline1 = { "-maxcols", "23", "-port" };
	private final String[] cmdline2 = { "-maxcols", "23", "-port", "7845", "-shutdown_on_disconnect" };
	
	@org.junit.Test(expected = exception.InvalidCommandLineException.class)
	public void testCmdLineParserException()
	 throws exception.InvalidCommandLineException {
			BridgeParameters bp = CommandLineParser.parseCommandLine(cmdline1);
			assertFalse(bp != null);
	}
	
	@org.junit.Test
	public void testCmdLineOptionsRetrieval()
	throws exception.InvalidCommandLineException {
		BridgeParameters bp = CommandLineParser.parseCommandLine(cmdline2);
		assertEquals( "7845", bp.getPort());
		assertEquals("23", bp.getMaxcols());
		assertEquals(true, bp.isShutdownOnDisconnect());
	}

}
