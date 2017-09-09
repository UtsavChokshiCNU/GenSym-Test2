package com.gensym.jgi.rmi;

import static org.junit.Assert.*;

import java.awt.Frame;

import org.junit.Before;
import org.junit.Ignore;
import org.junit.Test;
import org.mockito.Spy;

import com.gensym.g2studio.G2Studio;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.rmi.TwRMIClientImpl;
import com.gensym.shell.util.ContextChangedEvent;

public class G2StudioTest {

	private Object object = new Object();
	private String[] args = new String[] { "test1", "test2" };
	private G2Studio g2Studio;

	@Spy
	private TwAccess twAcces = new TwRMIClientImpl();
	@Spy
	private ContextChangedEvent contextChangedEvent = new ContextChangedEvent(object, twAcces, false);

	@Before
	public void init() {
		g2Studio = new G2Studio(args);
	}

	/**
	 * All test have to be included in this because only Single UI object may be created.
	 * @throws G2AccessException
	 */
	@Test
	public void testGetAppFrameDeleteItem() throws G2AccessException {
		g2Studio.setConnection(twAcces);
		assertNotNull(g2Studio.getConnectionManager());
		assertFalse(g2Studio.deleteItem(object, false, false));
		g2Studio.currentConnectionChanged(contextChangedEvent);
		assertFalse(g2Studio.getDevOption());
	}
}
