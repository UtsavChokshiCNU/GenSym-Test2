package com.gensym.nols.data;

import static org.junit.Assert.assertEquals;

import java.util.Vector;

import org.junit.Test;

import com.gensym.math.datafit.ArchitectureParameters;
import com.gensym.math.datafit.EnsembleModel;


public class NolOptimizeModelTest {

	@Test
	public void testGetNin() {
		EnsembleModel outputEnsemble = new EnsembleModel(
				new ArchitectureParameters(2, 1, 0, 0));
		
		Vector<String> outs = new Vector<String>();
		outs.add("% C3 IN C2 COMP");
		
		Vector<String> ins = new Vector<String>();
		ins.add("DeC2FeedFlow.m");
		
		Vector<String> manis = (Vector<String>) ins.clone();
		Vector<String> exogs = new Vector<String>();
		
		Vector<long[]> outDelays = new Vector<long[]>();
		outDelays.add(new long[] {0});
		
		Vector<long[]> inputDelays = new Vector<long[]>();
		inputDelays.add(new long[] {0, 60000});
		
		Preprocessor prep = new Preprocessor();
		
		NolOptimizeModel model = new NolOptimizeModel(outputEnsemble, "Model14",
				outs, ins, manis, exogs, outDelays, inputDelays, prep);
		assertEquals(2, model.getNin());
	}
}
