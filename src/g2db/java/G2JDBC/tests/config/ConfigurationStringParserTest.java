package config;

import static org.junit.Assert.*;

/**
 * Tests configuration string parser.
 * @author SoftServe
 *
 */
public class ConfigurationStringParserTest {

	private String s1 = "-b24 -T -c -n74 -fINFO,ERROR";
	private String s2 = "-A -b31 -o -r22";

	
	@org.junit.Test
	public void testProcessParametersParsing1() {
		ConfigurationStringParser p = new ConfigurationStringParser(s1);
		ProcessParameters pp = p.parseProcessParameters();
		assertEquals(24, pp.getMaxBindVars());
		assertEquals(true, pp.isDisableIOTimestamp());
		assertEquals(true, pp.isDisableConsoleOut());
		assertEquals(false, pp.isSmartFetch());
		assertEquals("INFO,ERROR", pp.getLogFileFilter());
	}
	
	@org.junit.Test
	public void testProcessParametersParsing2() {
		ConfigurationStringParser p = new ConfigurationStringParser(s2);
		ProcessParameters pp = p.parseProcessParameters();
		assertEquals(true, pp.isAutoCommit());
		assertEquals(31, pp.getMaxBindVars());
		assertEquals(true, pp.isDisableConsoleOut());
		assertEquals(22, pp.getMaxRegisteredItems());
	}
	
		
}
