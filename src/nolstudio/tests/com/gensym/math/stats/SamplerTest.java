package com.gensym.math.stats;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

public class SamplerTest {
	
	private Sampler sampler;
	
	@Before
	public void init() {
		sampler = new Sampler(6);
	}

	@Test
	public void sampleTest() {
		int result = sampler.nextSample();
		assertTrue(result < 6);
	}
	
	@Test(expected = NegativeArraySizeException.class)
	public void testSampleWithNegativeNo() {
		sampler = new Sampler(-5);
	}
	
	@Test
	public void testForZero() {
		sampler = new Sampler(0);
		assertEquals(-1, sampler.nextSample());
	}
	
	@Test
	public void testReset() {
		sampler = new Sampler(1);
		int res = sampler.nextSample();
		sampler = new Sampler(res);
		res = sampler.nextSample();
		try {
			sampler = new Sampler(res);
		} catch(NegativeArraySizeException nae) {
			sampler.reset();
			sampler.nextSample();
		}
	}
}
