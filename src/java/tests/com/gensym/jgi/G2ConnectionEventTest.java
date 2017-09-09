package com.gensym.jgi;

import org.junit.*;
import static org.junit.Assert.*;

/**
 * @author Deepti
 * @version $Revision: 1.0 $
 */
public class G2ConnectionEventTest {
	/**
	 * Run the G2ConnectionEvent(Object,int) constructor test.
	 */
	@Test
	public void testG2ConnectionEvent()  {
		Object source = new Object();
		int id = 1;
		G2ConnectionEvent result = new G2ConnectionEvent(source, id);
		assertNotNull(result);
		assertEquals(1, result.getId());
        assert(result.toString().contains("1"));
	}

	/**
	 * Run the G2ConnectionEvent(Object,int,String,boolean) constructor test.
	 */
	@Test
	public void testG2ConnectionEventState()  {
		Object source = new G2Gateway();
		int id = 1;
		String message = "test";
		boolean state = true;
		G2ConnectionEvent result = new G2ConnectionEvent(source, id, message, state);
		assertNotNull(result);
		assertEquals(1, result.getId());
		assertEquals(true, result.getState());
	}
	/**
	 * Run the int getId() method test.
	 */
	@Test
	public void testGetId()  {
		G2ConnectionEvent fixture = new G2ConnectionEvent(new Object(), 1, "test", true);
		int result = fixture.getId();
		assertEquals(1, result);
	}

	/**
	 * Run the String getMessage() method test.
	 */
	@Test
	public void testGetMessage() {
		G2ConnectionEvent fixture = new G2ConnectionEvent(new Object(), 1, "test", true);
		String result = fixture.getMessage();
		assertEquals("test", result);
	}
	/**
	 * Run the boolean getState() method test.
	 */
	@Test
	public void testGetState() {
		G2ConnectionEvent fixture = new G2ConnectionEvent(new Object(), 1, "test", true);
		boolean result = fixture.getState();
		assertEquals(true, result);
	}
	/**
	 * Run the String paramString() method test.
	 */
	@Test
	public void testParamStringPaused() {
		G2ConnectionEvent fixture = new G2ConnectionEvent(new Object(), 0, "test", true);
		String result = fixture.paramString();
		assertEquals("PAUSED", result);
	}
	/**
	 * Run the String paramString() method test.
	 */
	@Test
	public void testParamStringResumed() {
		G2ConnectionEvent fixture = new G2ConnectionEvent(new Object(), 1, "test", true);
		String result = fixture.paramString();
		assertEquals("RESUMED", result);
	}
	/**
	 * Run the String paramString() method test.
	 */
	@Test
	public void testParamStringReset() {
		G2ConnectionEvent fixture = new G2ConnectionEvent(new Object(), 2, "test", true);
		String result = fixture.paramString();
		assertEquals("RESET", result);
	}
	/**
	 * Run the String paramString() method test.
	 */
	@Test
	public void testParamStringStarted() {
		G2ConnectionEvent fixture = new G2ConnectionEvent(new Object(), 3, "test", true);
		String result = fixture.paramString();
		assertEquals("STARTED", result);
	}
	/**
	 * Run the String paramString() method test.
	 */
	@Test
	public void testParamStringConnectionClosed() {
		G2ConnectionEvent fixture = new G2ConnectionEvent(new Object(), 10, "test", true);
		String result = fixture.paramString();
		assertEquals("CONNECTION CLOSED", result);
	}
	/**
	 * Run the String paramString() method test.
	 */
	@Test
	public void testParamStringConnectionInitialized() {
		G2ConnectionEvent fixture = new G2ConnectionEvent(new Object(), 11, "test", true);
		String result = fixture.paramString();
		assertEquals("CONNECTION INITIALIZED", result);
	}
	/**
	 * Run the String paramString() method test.
	 */
	@Test
	public void testParamStringMessageRecieved() {
		G2ConnectionEvent fixture = new G2ConnectionEvent(new Object(), 20, "test", true);
		String result = fixture.paramString();
		assertEquals("MESSAGE RECEIVED", result);
	}
	/**
	 * Run the String paramString() method test.
	 */
	@Test
	public void testParamStringCommunicationError() {
		G2ConnectionEvent fixture = new G2ConnectionEvent(new Object(), 21, "test", true);
		String result = fixture.paramString();
		assertEquals("COMMUNICATION ERROR", result);
	}
    /**
     * Run the String paramString() method test.
     */
    @Test
    public void testParamStringNoCommunicationError() {
        G2ConnectionEvent fixture = new G2ConnectionEvent(new Object(), 22, "test", true);
        String result = fixture.paramString();
        assertEquals("NOCONNECTION COMMUNICATION ERRORPAUSED", result);
    }
    /**
     * Run the String paramString() method test.
     */
    @Test
    public void testParamStringReadBlockage() {
        G2ConnectionEvent fixture = new G2ConnectionEvent(new Object(), 30, "test", true);
        String result = fixture.paramString();
        assertEquals("READ BLOCKAGE", result);
    }
    /**
     * Run the String paramString() method test.
     */
    @Test
    public void testParamStringWriteBlockage() {
        G2ConnectionEvent fixture = new G2ConnectionEvent(new Object(), 31, "test", true);
        String result = fixture.paramString();
        assertEquals("WRITE BLOCKAGE", result);
    }
    /**
     * Run the String paramString() method test.
     */
    @Test
    public void testParamStringDef() {
        G2ConnectionEvent fixture = new G2ConnectionEvent(new Object(), 12, "test", true);
        String result = fixture.paramString();
        assertEquals("", result);
    }
}