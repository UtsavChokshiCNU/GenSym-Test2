package com.gensym.nols.wksp;

import static org.junit.Assert.assertArrayEquals;

import java.util.Vector;

import org.junit.Before;
import org.junit.Test;

public class DelaysStorageTest {

	private static final long DELAY3 = 20000l;
	private static final long DELAY2 = 10000l;
	private static final long DELAY1 = 0l;
	private static final long[] DELAYS = new long[] {DELAY1, DELAY2};
	private static final String VAR1 = "Var1";
	private DelaysStorage ds;
	private Vector<String> vars;
	private Vector<long[]> delays;

	@Before
	public void setup() {
		ds = new DelaysStorage();
		vars = new Vector<String>();
		delays = new Vector<long[]>();
		vars.add(VAR1);
		delays.add(DELAYS);
		ds.add(vars, delays);
	}
	
	@Test
	public void testAddVariablesWithDelays() {
		assertArrayEquals(new Long[] {DELAY1, DELAY2}, ds.getDelaysFor(VAR1));
	}

	@Test
	public void testDoubleAddVariablesWithDelays() {
		Vector<String> vars2 = new Vector<String>();
		Vector<long[]> delays2 = new Vector<long[]>();
		vars2.add(VAR1);
		delays2.add(new long[] {DELAY1, DELAY3});
		ds.add(vars2, delays2);
		assertArrayEquals(new Long[] {DELAY1, DELAY2, DELAY3},
				ds.getDelaysFor(VAR1));
	}

	@Test
	public void testAddVariablesWithNoDelays() {
		ds.add(vars, new Vector<long[]>());
		assertArrayEquals(new Long[] {DELAY1, DELAY2}, ds.getDelaysFor(VAR1));
	}
	
	@Test
	public void testGetNoDelays() {
		assertArrayEquals(new Long[0], ds.getDelaysFor("Var2"));
	}

}
