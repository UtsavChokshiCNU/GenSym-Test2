package com.gensym.nols.data;

import static org.junit.Assert.assertEquals;
import static org.mockito.Mockito.times;
import static org.powermock.api.mockito.PowerMockito.mock;
import static org.powermock.api.mockito.PowerMockito.mockStatic;
import static org.powermock.api.mockito.PowerMockito.when;
import static org.powermock.api.mockito.PowerMockito.whenNew;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStreamWriter;
import java.nio.charset.Charset;
import java.util.Vector;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Mockito;
import org.powermock.core.classloader.annotations.PrepareForTest;
import org.powermock.modules.junit4.PowerMockRunner;
import org.powermock.reflect.Whitebox;

import com.gensym.math.datafit.ArchitectureParameters;
import com.gensym.math.datafit.Pls;
import com.gensym.math.datafit.TrainableModel;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;

@RunWith(PowerMockRunner.class)
@PrepareForTest({NolPlsModel.class, Matlib.class, Matrix.class})
public class NolPlsModel2Test
{
	/**
	 * Method to test writePLSWeightFile()
	 * @throws Exception
	 */
	@Test
	public void testWritePLSWeightFile() throws Exception
	{
		final String dir =  System.getProperty("user.dir");
		final String fileName = "TestFile";

		final File file = mock(File.class);
		whenNew(File.class).withArguments(dir, fileName).thenReturn(file);
		
		mockStatic(Charset.class);
		final FileOutputStream fileStream = mock(FileOutputStream.class);
		final OutputStreamWriter streamWriter = mock(OutputStreamWriter.class);
		final BufferedWriter source = mock(BufferedWriter.class);
		final Charset mockCharset = mock(Charset.class);
		
		when(Charset.defaultCharset()).thenReturn(mockCharset);
		whenNew(FileOutputStream.class).withArguments(file).thenReturn(fileStream);
		whenNew(OutputStreamWriter.class).withArguments(fileStream, mockCharset).thenReturn(streamWriter);
		whenNew(BufferedWriter.class).withArguments(streamWriter).thenReturn(source);

		final NolPlsModel testObj = createNolPlsModelObject();

		final Pls pls = mock(Pls.class);
		final Vector<TrainableModel> models = new Vector<>();
		models.addElement(pls);
		Whitebox.setInternalState(testObj, "models", models);

		testObj.writePLSWeightFile(dir, fileName);
		Mockito.verify(source).write("1; Version of this file save/restore protocol");
		Mockito.verify(source, times(2)).newLine();
		Mockito.verify(source).write(1+"; Number of submodels");
		Mockito.verify(source).close();
		Mockito.verify(streamWriter).close();
		Mockito.verify(fileStream).close();
	}

	/**
	 * Method to test writeXMLFile()
	 * @throws Exception
	 */
	@Test
	public void testWriteXMLFile() throws Exception
	{
		final NolPlsModel testObj = createNolPlsModelObject();
		final BufferedWriter target = mock(BufferedWriter.class);
		final int indentNumber = 10;

		final ArchitectureParameters ap = new ArchitectureParameters(10,  20, 3, 4);
		final Pls pls = new Pls(ap);

		final Matrix m = mock(Matrix.class);
		when(m.getCols()).thenReturn(1);

		Whitebox.setInternalState(pls, "Xmean", m);
		Whitebox.setInternalState(pls, "Ymean", m);
		Whitebox.setInternalState(pls, "R", m);

		mockStatic(Matlib.class);
		when(Matlib.class, "createMatrix").thenReturn(m);
		final double[] doubleArray = {10.0};
		when(Matlib.class, "create1DArray", m).thenReturn(doubleArray);

		final Vector<TrainableModel> models = new Vector<>();
		models.addElement(pls);
		Whitebox.setInternalState(testObj, "models", models);
		final int returnVal = testObj.writeXMLFile(target, indentNumber);
		assertEquals(11, returnVal);
		Mockito.verify(target).write("										<bpn>\n", 0, 16);
		Mockito.verify(target).write("											<numberOfInputs>1</numberOfInputs>\n", 0, 46);
		Mockito.verify(target).write("											<numberOfOutputs>1</numberOfOutputs>\n", 0, 48);
		Mockito.verify(target).write("											<numberOfInnerNodes>1</numberOfInnerNodes>\n", 0, 54);
		Mockito.verify(target).write("											<inputMeans>\n", 0, 24);
	}

	/**
	 * private method to create NolPlsModel object
	 * @return
	 */
	private NolPlsModel createNolPlsModelObject()
	{
		final int nin = 2;
		final int nout = 2;
		final int nhidden = 2;
		final int nfactors = 0;
		final ArchitectureParameters AP = new ArchitectureParameters(nin, nout, nhidden, nfactors);

		final String name = "TestInput";
		final Vector outs = new Vector<>();
		final Vector ins = new Vector<>();
		final Vector oDelays = new Vector<>();
		final Vector iDelays = new Vector<>();
		final Preprocessor prep = mock(Preprocessor.class);

		final NolPlsModel testObj = new NolPlsModel(AP, name, outs, ins, oDelays, iDelays, prep);
		testObj.VERBOSE = true;
		return testObj;
	}

}