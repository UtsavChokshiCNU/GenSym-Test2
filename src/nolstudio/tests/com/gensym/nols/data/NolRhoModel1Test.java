package com.gensym.nols.data;

import static org.powermock.api.mockito.PowerMockito.mock;
import static org.powermock.api.mockito.PowerMockito.when;
import static org.powermock.api.mockito.PowerMockito.whenNew;

import java.util.Vector;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Mockito;
import org.powermock.core.classloader.annotations.PrepareForTest;
import org.powermock.modules.junit4.PowerMockRunner;

import com.gensym.math.MathException;
import com.gensym.math.datafit.ClassicRbfn;
import com.gensym.math.datafit.ClassicValidationParameters;
import com.gensym.math.matrix.Matrix;

/**
 * This class tests NolRhoModel object. This class is required to create ClassicValidationParameters,
 * which requires to add whenNew() in test method.
 * @author Apparao
 */
@RunWith(PowerMockRunner.class)
@PrepareForTest(NolRhoModel.class)
public class NolRhoModel1Test
{
	/**
	 * Method to test if block in train()
	 * @throws Exception
	 */
	@Test
	public void testTrain() throws Exception
	{
		final Matrix XTrain = new Matrix();
		final Matrix YTrain = new Matrix();

		final NolClassicModelTrainer trainer = mock(NolClassicModelTrainer.class);
		final String[] fileNames = {"File1", "File2"};

		when(trainer.makeRPCfileNames()).thenReturn(fileNames);
		final NolRhoModel testObj = createTestObject();
		testObj.setTrainer(trainer);
		when(trainer.jrho_trainer(fileNames[0], fileNames[1])).thenReturn(1);

		final ClassicValidationParameters paramObj = mock(ClassicValidationParameters.class);
		whenNew(ClassicValidationParameters.class).withAnyArguments().thenReturn(paramObj);

		testObj.train(XTrain, YTrain);
		Mockito.verify(trainer).informListeners("complete", "");
		Mockito.verify(trainer).deleteFiles(fileNames);
	}

	private NolRhoModel createTestObject() throws MathException
	{
		final int[] nodes = {1,2,3};
		final double overlap = 1.0;
		final int unitType = 1;

		final ClassicRbfn net = new ClassicRbfn(nodes, overlap, unitType);
		final String name = "Test Name";
		final Vector outs = new Vector<>();
		outs.addElement(10.0);
		outs.addElement(11.0);
		final Vector ins = new Vector<>();
		final Vector oDelays = new Vector<>();
		oDelays.addElement(10000l);
		oDelays.addElement(10001l);
		final Vector iDelays = new Vector<>();

		final DataSeries ds = new DataSeries();
		final Project p = new Project();
		final Vector<Variable> varObjs = new Vector<>();
		final Variable var = new Variable("Preprocessor1", ds, 1);
		varObjs.addElement(var);
		final ViewFilter filter = new ViewFilter();
		final Preprocessor prep = new Preprocessor("Preprocessor1", p, varObjs, filter);

		final NolRhoModel testObj = new NolRhoModel(net, name, outs, ins, oDelays, iDelays, prep);
		return testObj;
	}
}
