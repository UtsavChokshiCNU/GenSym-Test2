package com.gensym.nols.deploy;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;
import static org.mockito.Mockito.mock;
import static org.powermock.api.mockito.PowerMockito.doNothing;
import static org.powermock.api.mockito.PowerMockito.doThrow;
import static org.powermock.api.mockito.PowerMockito.mockStatic;
import static org.powermock.api.mockito.PowerMockito.verifyStatic;
import static org.powermock.api.mockito.PowerMockito.when;
import static org.powermock.api.mockito.PowerMockito.whenNew;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.PrintStream;
import java.util.Vector;

import javax.swing.JLayeredPane;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Matchers;
import org.powermock.core.classloader.annotations.PrepareForTest;
import org.powermock.modules.junit4.PowerMockRunner;
import org.powermock.reflect.Whitebox;

import com.gensym.classes.FloatArray;
import com.gensym.classes.modules.jgidemo.G2_EventSourceEvent;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2CommunicationErrorEvent;
import com.gensym.jgi.G2Connection;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.jgi.G2ConnectionHandlerFactory;
import com.gensym.jgi.G2ConnectionInfo;
import com.gensym.jgi.G2Gateway;
import com.gensym.nols.data.DataSeries;
import com.gensym.nols.data.NolPcaModel;
import com.gensym.nols.data.Preprocessor;
import com.gensym.nols.data.Project2;
import com.gensym.nols.data.RawDataSource;
import com.gensym.nols.data.Variable;
import com.gensym.nols.main.NolMainFrame;
import com.gensym.nols.util.NolCmdLineArgHandler;
import com.gensym.nols.wksp.NolValidatePcaWKSP;
import com.gensym.util.Sequence;

@RunWith(PowerMockRunner.class)
@PrepareForTest({G2Gateway.class, NolG2Gateway.class, System.class})
public class NolG2Gateway2Test
{
	private final ByteArrayOutputStream outContent = new ByteArrayOutputStream();

	@Before
	public void setupStreams()
	{
		System.setOut(new PrintStream(outContent));
	}

	@After
	public void cleanUpStreams()
	{
		System.setOut(null);
	}

	/**
	 * Method to test NolG2Gateway for frame input
	 * @throws Exception
	 */
	@Test
	public void testNolG2GatewayForFrameInput() throws Exception
	{
		final NolMainFrame frame = mock(NolMainFrame.class);
		final String args[] = {"Input1", "Input2"};

		mockStatic(G2Gateway.class);
		doNothing().when(G2Gateway.class, "setConnectionHandlerFactory", Matchers.any(G2ConnectionHandlerFactory.class));
		final NolCmdLineArgHandler cmdLine = mock(NolCmdLineArgHandler.class);
		when(cmdLine.getOptionValue("-g2host")).thenReturn("localhost");
		whenNew(NolCmdLineArgHandler.class).withArguments(args).thenReturn(cmdLine);

		final G2Connection g2Connection = mock(G2Connection.class);
		when(G2Gateway.getOrMakeConnection(Matchers.any(G2ConnectionInfo.class))).thenReturn(g2Connection);
		final NolG2Gateway testObj = new NolG2Gateway(frame, args);
		assertNotNull(testObj);
	}

	/**
	 * Method to test g2IsPaused()
	 */
	@Test
	public void testG2IsPaused()
	{
		final G2Connection connection = mock(G2Connection.class);
		final NolG2Gateway testObj = new NolG2Gateway(connection);

		final G2ConnectionEvent e = mock(G2ConnectionEvent.class);
		testObj.g2IsPaused(e);
		assertTrue(outContent.toString().contains("G2 Has been paused"));
	}

	/**
	 * Method to test g2IsResumed()
	 */
	@Test
	public void testG2IsResumed()
	{
		final G2Connection connection = mock(G2Connection.class);
		final NolG2Gateway testObj = new NolG2Gateway(connection);

		final G2ConnectionEvent e = mock(G2ConnectionEvent.class);
		testObj.g2IsResumed(e);
		assertTrue(outContent.toString().contains("G2 Has been resumed"));
	}

	/**
	 * Method to test g2IsReset()
	 */
	@Test
	public void testG2IsReset()
	{
		final G2Connection connection = mock(G2Connection.class);
		final NolG2Gateway testObj = new NolG2Gateway(connection);

		final G2ConnectionEvent e = mock(G2ConnectionEvent.class);
		testObj.g2IsReset(e);
		assertTrue(outContent.toString().contains("G2 Has been reset"));
	}

	/**
	 * Method to test g2IsStarted()
	 */
	@Test
	public void testG2IsStarted()
	{
		final G2Connection connection = mock(G2Connection.class);
		final NolG2Gateway testObj = new NolG2Gateway(connection);

		final G2ConnectionEvent e = mock(G2ConnectionEvent.class);
		testObj.g2IsStarted(e);
		assertTrue(outContent.toString().contains("G2 Has been Started"));
	}

	/**
	 * Method to test g2MessageReceived()
	 */
	@Test
	public void testG2MessageReceived()
	{
		final G2Connection connection = mock(G2Connection.class);
		final NolG2Gateway testObj = new NolG2Gateway(connection);

		final G2ConnectionEvent e = mock(G2ConnectionEvent.class);
		when(e.getMessage()).thenReturn("Operation Completed");
		testObj.g2MessageReceived(e);
		assertTrue(outContent.toString().contains("Message received from G2 was: Operation Completed"));
	}

	/**
	 * Method to test communicationError()
	 */
	@Test
	public void testCommunicationError()
	{
		final G2Connection connection = mock(G2Connection.class);
		final NolG2Gateway testObj = new NolG2Gateway(connection);

		final G2CommunicationErrorEvent e = mock(G2CommunicationErrorEvent.class);
		when(e.getMessage()).thenReturn("404 Error");
		testObj.communicationError(e);
		assertTrue(outContent.toString().contains("404 Error"));
	}

	/**
	 * Method to test g2ConnectionClosed()
	 */
	@Test
	public void testG2ConnectionClosed()
	{
		final G2Connection connection = mock(G2Connection.class);
		final NolG2Gateway testObj = new NolG2Gateway(connection);

		final NolMainFrame frame = mock(NolMainFrame.class);
		Whitebox.setInternalState(testObj, "frame", frame);
		final G2ConnectionEvent e = mock(G2ConnectionEvent.class);
		testObj.readBlockage(e);
		testObj.writeBlockage(e);
		testObj.g2ConnectionClosed(e);
		assertTrue(outContent.toString().contains("G2 Connection has been closed "));
	}

	/**
	 * Method to test g2ConnectionInitialized()
	 * @throws G2AccessException
	 */
	@Test
	public void testG2ConnectionInitialized() throws G2AccessException
	{
		final G2Connection connection = mock(G2Connection.class);
		final NolG2Gateway testObj = new NolG2Gateway(connection);

		final G2ConnectionEvent e = mock(G2ConnectionEvent.class);
		when(e.getMessage()).thenReturn("Connection Initialized");
		final G2Connection g2Connection = mock(G2Connection.class);
		when(g2Connection.g2GetHostName()).thenReturn("localhost");
		when(g2Connection.g2GetPortNumberOrName()).thenReturn("8080");
		Whitebox.setInternalState(testObj, "g2Connection", g2Connection);

		testObj.g2ConnectionInitialized(e);
		assertTrue(outContent.toString().contains("Connected to G2 get back"));
		assertTrue(outContent.toString().contains("Connected to G2 @"));
		assertTrue(outContent.toString().contains("localhost"));
		assertTrue(outContent.toString().contains("8080"));

		final G2AccessException exception = new G2AccessException();
		doThrow(exception).when(g2Connection).g2GetHostName();
		testObj.g2ConnectionInitialized(e);
		assertTrue(outContent.toString().contains(exception.toString()));
	}

	/**
	 * Method to test anEvent()
	 * @throws G2AccessException
	 */
	@Test
	public void testAnEvent() throws G2AccessException
	{
		final G2Connection connection = mock(G2Connection.class);
		final NolG2Gateway testObj = new NolG2Gateway(connection);

		final G2_EventSourceEvent arg1 = mock(G2_EventSourceEvent.class);
		when(arg1.getSource()).thenReturn("G2EventSource");
		testObj.anEvent(arg1);
		assertTrue(outContent.toString().contains("Received an event from G2EventSource"));
	}

	/**
	 * Method to test addDataseries()
	 * @throws G2AccessException
	 */
	@Test
	public void testAddDataseries() throws G2AccessException
	{
		final G2Connection connection = mock(G2Connection.class);
		final NolG2Gateway testObj = new NolG2Gateway(connection);

		final String dsName = "Test DataSource";
		final Sequence X = mock(Sequence.class);

		when(X.size()).thenReturn(2);
		final FloatArray fa1 = mock(FloatArray.class);
		when(fa1.getFloatArrayContents()).thenReturn(new double[]{1.0, 2.0, 3.0});
		final FloatArray fa2 = mock(FloatArray.class);
		when(fa1.getFloatArrayContents()).thenReturn(new double[]{11.0, 12.0, 13.0});
		final FloatArray[] inputRows = {fa1, fa2};
		when(X.getContents()).thenReturn(inputRows);

		final NolMainFrame frame = mock(NolMainFrame.class);
		Whitebox.setInternalState(testObj, "frame", frame);

		final int returnVal = testObj.addDataseries(dsName, X);
		assertEquals(0, returnVal);
	}

	/**
	 * Method to test validatePcaModel()
	 * @throws Exception
	 */
	@Test
	public void testValidatePcaModel() throws Exception
	{
		final String mName = "InputModel";
		final Sequence X = mock(Sequence.class);
		when(X.size()).thenReturn(2);

		final FloatArray fa1 = mock(FloatArray.class);
		when(fa1.getFloatArrayContents()).thenReturn(new double[]{1.0, 2.0, 3.0});
		final FloatArray fa2 = mock(FloatArray.class);
		when(fa2.getFloatArrayContents()).thenReturn(new double[]{11.0, 12.0, 13.0});
		final FloatArray[] inputRows = {fa1, fa2};
		when(X.getContents()).thenReturn(inputRows);

		final NolMainFrame frame = mock(NolMainFrame.class);

		final Project2 project = mock(Project2.class);
		when(frame.getProject()).thenReturn(project);
		when(project.getPcaModelIndexByName(mName)).thenReturn(12);

		final NolPcaModel model = mock(NolPcaModel.class);
		when(project.getPcaModel(12)).thenReturn(model);
		final Vector v = new Vector<>();
		v.addElement("s1");
		v.addElement("s2");
		when(model.getInputs()).thenReturn(v);

		final RawDataSource ds = mock(RawDataSource.class);
		when(project.getRawDataSource()).thenReturn(ds);

		final Preprocessor prep = mock(Preprocessor.class);
		when(model.getPreprocessor()).thenReturn(prep);
		final Variable varObj = mock(Variable.class);
		when(prep.getVariableFromVariableName(Matchers.anyString())).thenReturn(varObj);

		final G2Connection connection = mock(G2Connection.class);
		final NolG2Gateway testObj = new NolG2Gateway(connection);
		Whitebox.setInternalState(testObj, "frame", frame);

		final NolValidatePcaWKSP activeInternalFrame = mock(NolValidatePcaWKSP.class);
		whenNew(NolValidatePcaWKSP.class).withArguments(Matchers.eq(frame), Matchers.eq(model),
				Matchers.any(DataSeries.class)).thenReturn(activeInternalFrame);

		final JLayeredPane layeredPane = mock(JLayeredPane.class);
		when(frame.getEditor()).thenReturn(layeredPane);

		int returnVal = testObj.validatePcaModel(mName, X);
		assertEquals(1, returnVal);

		when(project.getPcaModelIndexByName(mName)).thenReturn(-1);
		returnVal = testObj.validatePcaModel(mName, X);
		assertEquals(0, returnVal);
	}

	/**
	 * Method to test loadProject
	 * @throws Exception
	 */
	@Test
	public void testLoadProject() throws Exception
	{
		final G2Connection connection = mock(G2Connection.class);
		final NolG2Gateway testObj = new NolG2Gateway(connection);

		final String pjPath = "TestDir";
		final String pjName = "TestFile";
		final File dirFile = mock(File.class);
		when(dirFile.isDirectory()).thenReturn(true);
		whenNew(File.class).withArguments("TestDir").thenReturn(dirFile);

		final NolMainFrame frame = mock(NolMainFrame.class);
		Whitebox.setInternalState(testObj, "frame", frame);

		assertEquals(1, testObj.loadProject(pjPath, pjName));
	}

	/**
	 * Method to test saveProject
	 * @throws Exception
	 */
	@Test
	public void testSaveProject() throws Exception
	{
		final G2Connection connection = mock(G2Connection.class);
		final NolG2Gateway testObj = new NolG2Gateway(connection);

		final String pjPath = "TestDir";
		final String pjName = "TestFile";
		final File dirFile = mock(File.class);
		when(dirFile.isDirectory()).thenReturn(true);
		whenNew(File.class).withArguments("TestDir").thenReturn(dirFile);

		final NolMainFrame frame = mock(NolMainFrame.class);
		Whitebox.setInternalState(testObj, "frame", frame);

		assertEquals(1, testObj.saveProject(pjPath, pjName));
	}

	/**
	 * Method to test NolG2Gateway for frame input
	 * @throws Exception
	 */
	@Test
	public void testMain() throws Exception
	{
		final String args[] = {"Input1", "Input2"};

		mockStatic(G2Gateway.class);
		doNothing().when(G2Gateway.class, "setConnectionHandlerFactory", Matchers.any(G2ConnectionHandlerFactory.class));
		final NolCmdLineArgHandler cmdLine = mock(NolCmdLineArgHandler.class);
		when(cmdLine.getOptionValue("-g2host")).thenReturn("localhost");
		whenNew(NolCmdLineArgHandler.class).withArguments(args).thenReturn(cmdLine);

		final G2Connection g2Connection = mock(G2Connection.class);
		when(G2Gateway.getOrMakeConnection(Matchers.any(G2ConnectionInfo.class))).thenReturn(g2Connection);
		NolG2Gateway.main(args);

		verifyStatic();
		G2Gateway.startup();
	}

	/**
	 * Method to test shutdownGateway
	 * @throws G2AccessException
	 */
	@Test
	public void testShutdownGateway() throws G2AccessException
	{
		final G2Connection connection = mock(G2Connection.class);
		final NolG2Gateway testObj = new NolG2Gateway(connection);
		assertEquals(1, testObj.shutdownGateway());
	}
}
