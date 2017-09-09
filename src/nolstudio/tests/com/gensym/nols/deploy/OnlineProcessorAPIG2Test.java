package com.gensym.nols.deploy;

import com.gensym.classes.*;
import com.gensym.core.DebugUtil;
import com.gensym.jgi.G2AccessException;
import com.gensym.math.MathException;
import com.gensym.math.datafit.ArchitectureParameters;
import com.gensym.math.datafit.EnsembleModel;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;
import com.gensym.nols.data.*;
import com.gensym.nols.main.NolMainFrame;
import com.gensym.util.*;
import org.junit.After;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.TemporaryFolder;
import org.mockito.ArgumentCaptor;
import org.mockito.Matchers;
import org.mockito.Mockito;
import org.powermock.reflect.Whitebox;

import java.awt.*;
import java.io.*;
import java.lang.Object;
import java.lang.reflect.InvocationTargetException;
import java.net.MalformedURLException;
import java.text.ParseException;
import java.util.Random;
import java.util.Vector;
import java.util.zip.GZIPInputStream;
import java.util.zip.GZIPOutputStream;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.greaterThan;
import static org.hamcrest.core.Is.is;
import static org.hamcrest.core.IsEqual.equalTo;
import static org.junit.Assert.*;
import static org.mockito.Mockito.*;
import static org.powermock.api.mockito.PowerMockito.doAnswer;
import static org.powermock.api.mockito.PowerMockito.doThrow;
import static org.powermock.api.mockito.PowerMockito.mock;
import static org.powermock.api.mockito.PowerMockito.when;

public class OnlineProcessorAPIG2Test {
    private static final Random randomGenerator = new Random();
    private static final Symbol RETVAL = Symbol.intern("RETVAL");
    private static final Symbol ERROR = Symbol.intern("ERROR");
    private static final Symbol BACKTRACE = Symbol.intern("BACKTRACE");
    private static final double MILLISECONDS_IN_MINUTE = 60000;

    private final ByteArrayOutputStream errorContent = new ByteArrayOutputStream();
    private final ByteArrayOutputStream outContent = new ByteArrayOutputStream();
    private final Vector<File> files = new Vector<>();

    @Rule
    public TemporaryFolder temporaryFolder = new TemporaryFolder();
    
    private NolG2Gateway g2GatewayBackup;
    private NolMainFrame mainFramePreviousState;
    private OnlineProcessor sutProcessor;
    private OnlineProcessorAPIG2Extended sut;
    private String sutG2Uuid;

    @Before
    public void before() throws G2AccessException, MathException {
        this.sutProcessor = createProcessor();
        this.sut = new OnlineProcessorAPIG2Extended(sutProcessor);
        this.sutG2Uuid = "123456789";
        this.sut.setUuidForG2Object(this.sutG2Uuid);

        this.mainFramePreviousState = NolMainFrame.mainFrame;
        NolMainFrame.mainFrame = createNolMainFrame();

        g2GatewayBackup = NolG2Gateway.g2Gateway;
        NolG2Gateway.g2Gateway = createG2Gateway();

        setupStreams();
    }

    @After
    public void after() {
        for (File file : files) {
            file.delete();
        }

        files.removeAllElements();
        NolMainFrame.mainFrame = this.mainFramePreviousState;

        NolG2Gateway.g2Gateway = g2GatewayBackup;

        cleanUpStreams();
    }

    @Test
    public void test_instance_noParameters_setsProcessor() {
        // Arrange
        // No arrangements

        // Act
        this.sut = new OnlineProcessorAPIG2Extended();

        // Assert
        assertNotNull(this.sut.getProcessor());
    }

    @Test
    public void test_clone_processorNotSet_retNull() throws CloneNotSupportedException {
        // Arrange
        this.sut = new OnlineProcessorAPIG2Extended(null);

        // Act & Assert
        assertNull(((OnlineProcessorAPIG2) this.sut.clone()).getProcessor());
    }

    @Test
    public void test_clone_processorIsSet_retCloned() throws CloneNotSupportedException {
        // Arrange
        OnlineProcessor clonedProcessor = new OnlineProcessor();
        when(this.sutProcessor.clone()).thenReturn(clonedProcessor);

        // Act & Assert
        assertThat(((OnlineProcessorAPIG2) this.sut.clone()).getProcessor(), is(equalTo(clonedProcessor)));
    }

    @Test
    public void test_getDebugProcessor_always_retDebugState() {
        // Arrange
        boolean[] testCases = {true, false};

        for (boolean testCase : testCases) {
            // Act
            this.sut.setDebugProcessor(testCase);

            // Assert
            assertThat(this.sut.getDebugProcessor(), is(equalTo(testCase)));
        }
    }

    @Test
    public void test_loadModel_OnlineAutoRecursiveProcessor_loadsModel() throws MathException, IOException {
        // Arrange
        OnlineAutoRecusiveProcessor onlinePreprocessor = createOnlineAutoRecursiveProcessor();
        File file = createOnlineProcessorFile(onlinePreprocessor);

        // Act
        this.sut.loadModel(file.getAbsolutePath(), null);

        // Assert
        assertTrue(sut.isLoaded());
        assertThat(this.sut.getName(), is(equalTo(onlinePreprocessor.getName())));
        assertThat(this.sut.getComment(), is(equalTo(onlinePreprocessor.getComment())));

        assertThat(onlinePreprocessor.getInputNames().length, is(greaterThan(0)));
        assertThat(this.sut.getInputNames().size(), is(equalTo(onlinePreprocessor.getInputNames().length)));
        for (int i = 0; i < onlinePreprocessor.getInputNames().length; i++) {
            assertThat(this.sut.getInputNames().get(i), is(equalTo(onlinePreprocessor.getInputNames()[i])));
        }
    }

    @Test
    public void test_loadModel_OnlineProcessor_loadsModel() throws MathException, IOException {
        // Arrange
        OnlineProcessor onlinePreprocessor = createOnlineProcessor();
        File file = createOnlineProcessorFile(onlinePreprocessor);

        // Act
        this.sut.loadModel(file.getAbsolutePath(), null);

        // Assert
        assertTrue(sut.isLoaded());
        assertThat(this.sut.getProcessor().getName(), is(equalTo(onlinePreprocessor.getName())));
        assertThat(this.sut.getProcessor().getComment(), is(equalTo(onlinePreprocessor.getComment())));
    }

    @Test
    public void test_loadModel_FileIsEmpty_errorToConsole() throws MathException, IOException {
        // Arrange
        File file = createFile();

        // Act
        this.sut.loadModel(file.getAbsolutePath(), null);

        // Assert
        assertFalse(this.sut.isLoaded());
        assertTrue(errorContent.toString().startsWith("Non-Fatal exception"));
    }

    @Test
    public void test_loadModelWithDir_OnlineAutoRecursiveProcessor_loadsModel() throws MathException, IOException {
        // Arrange
        OnlineAutoRecusiveProcessor onlinePreprocessor = createOnlineAutoRecursiveProcessor();
        File file = createOnlineProcessorFile(onlinePreprocessor);
        String filename = file.getName();
        String directory = file.getAbsolutePath().replace(filename, "");

        // Act
        this.sut.loadModel(filename, directory);

        // Assert
        assertTrue(sut.isLoaded());
        assertThat(this.sut.getName(), is(equalTo(onlinePreprocessor.getName())));
        assertThat(this.sut.getComment(), is(equalTo(onlinePreprocessor.getComment())));

        assertThat(onlinePreprocessor.getInputNames().length, is(greaterThan(0)));
        assertThat(this.sut.getInputNames().size(), is(equalTo(onlinePreprocessor.getInputNames().length)));
        for (int i = 0; i < onlinePreprocessor.getInputNames().length; i++) {
            assertThat(this.sut.getInputNames().get(i), is(equalTo(onlinePreprocessor.getInputNames()[i])));
        }
    }

    @Test
    public void test_loadModelWithDir_OnlineProcessor_loadsModel() throws MathException, IOException {
        // Arrange
        OnlineProcessor onlinePreprocessor = createOnlineProcessor();
        File file = createOnlineProcessorFile(onlinePreprocessor);
        String filename = file.getName();
        String directory = file.getAbsolutePath().replace(filename, "");

        // Act
        this.sut.loadModel(filename, directory);

        // Assert
        assertTrue(sut.isLoaded());
        assertThat(this.sut.getProcessor().getName(), is(equalTo(onlinePreprocessor.getName())));
        assertThat(this.sut.getProcessor().getComment(), is(equalTo(onlinePreprocessor.getComment())));
    }

    @Test
    public void test_loadModelWithDir_FileIsEmpty_errorToConsole() throws MathException, IOException {
        // Arrange
        File file = createFile();
        String filename = file.getName();
        String directory = file.getAbsolutePath().replace(filename, "");

        // Act
        this.sut.loadModel(filename, directory);

        // Assert
        assertFalse(this.sut.isLoaded());
        assertTrue(errorContent.toString().startsWith("Non-Fatal exception"));
    }

    @Test
    public void test_getName_modelIsLoaded_retModelName() {
        // Arrange
        this.sut.setIsLoaded(true);

        // Act & Assert
        assertThat(this.sut.getName(), equalTo(this.sutProcessor.getName()));
    }

    @Test
    public void test_getName_modelNotLoaded_retEmptyString() {
        // Arrange
        // No arrangement

        // Act & Assert
        assertThat(this.sut.getName(), equalTo(""));
    }

    @Test
    public void test_getComment_modelIsLoaded_retModelComment() {
        // Arrange
        this.sut.setIsLoaded(true);

        // Act & Assert
        assertThat(this.sut.getComment(), equalTo(this.sutProcessor.getComment()));
    }

    @Test
    public void test_getComment_modelNotLoaded_retEmptyString() {
        // Arrange
        // No arrangement

        // Act & Assert
        assertThat(this.sut.getComment(), equalTo(""));
    }

    @Test
    public void test_calculateOutputAtTimeForG2_always_invokesCalculateOutput() throws MathException, NoSuchAttributeException {
        // Arrange
        String time = "05:00:00";

        // Act
        Structure retVal = this.sut.calculateOutputAtTimeForG2(time);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(true)));
        verify(this.sutProcessor).calculateOutputAtTime(time);
    }

    @Test
    public void test_calculateOutputAtTimeForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        String time = "05:00:00";
        MathException exception = new MathException("Failed to calculate output at time.");
        doThrow(exception).when(this.sutProcessor).calculateOutputAtTime(time);

        // Act
        Structure retVal = this.sut.calculateOutputAtTimeForG2(time);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_calculateOutputForRowForG2_always_invokesCalculateOutput() throws MathException, NoSuchAttributeException {
        // Arrange
        // No arrangement

        // Act
        Structure retVal = this.sut.calculateOutputForRowForG2();

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(true)));
        verify(this.sutProcessor).calculateOutputForRow();
    }

    @Test
    public void test_calculateOutputForRowForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        MathException exception = new MathException("Failed to calculate output for row.");
        doThrow(exception).when(this.sutProcessor).calculateOutputForRow();

        // Act
        Structure retVal = this.sut.calculateOutputForRowForG2();

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getNumberOfInputs_modelLoaded_retProcessorInputsCount() {
        // Arrange
        this.sut.setIsLoaded(true);

        // Act & Assert
        assertThat(this.sut.getNumberOfInputs(), equalTo(this.sutProcessor.getNumberOfInputs()));
    }

    @Test
    public void test_getNumberOfInputs_modelNotLoaded_retZero() {
        // Arrange
        // No arrangement

        // Act & Assert
        assertThat(this.sut.getNumberOfInputs(), equalTo(0));
    }

    @Test
    public void test_getInputName_modelNotLoaded_retEmptyString() {
        // Arrange
        int index = anyInteger();

        // Act & Assert
        assertThat(this.sut.getInputName(index), equalTo(""));
    }

    @Test
    public void test_getInputName_modelLoaded_retProcessorInputName() {
        // Arrange
        sut.setIsLoaded(true);
        int index = anyInteger();

        // Act
        String result = this.sut.getInputName(index);

        // Assert
        verify(this.sutProcessor).getInputName(index);
        assertThat(result, equalTo(this.sutProcessor.getInputName(index)));
    }

    @Test
    public void test_getInputNames_modelNotLoaded_retEmptySequence() throws MathException, IOException {
        // Arrange
        // No arrangements

        // Act & Assert
        assertThat(this.sut.getInputNames().size(), is(equalTo(0)));
    }

    @Test
    public void test_getInputNames_modelLoaded_retProcessorInputs() throws MathException, IOException {
        // Arrange
        OnlineProcessor onlineProcessor = loadModel();

        // Act
        Sequence result = this.sut.getInputNames();

        // Assert
        assertThat(onlineProcessor.getInputNames().length, is(greaterThan(0)));
        assertThat(result.size(), is(equalTo(onlineProcessor.getInputNames().length)));
        for (int i = 0; i < onlineProcessor.getInputNames().length; i++) {
            assertThat(result.get(i), is(equalTo(onlineProcessor.getInputNames()[i])));
        }
    }

    @Test
    public void test_getInputTag_modelNotLoaded_retEmptyString() {
        // Arrange
        int index = anyInteger();

        // Act & Assert
        assertThat(this.sut.getInputTag(index), equalTo(""));
    }

    @Test
    public void test_getInputTag_modelLoaded_retProcessorInputTag() {
        // Arrange
        sut.setIsLoaded(true);
        int index = anyInteger();

        // Act
        String result = this.sut.getInputTag(index);

        // Assert
        verify(this.sutProcessor).getInputTag(index);
        assertThat(result, equalTo(this.sutProcessor.getInputTag(index)));
    }

    @Test
    public void test_getInputTags_modelNotLoaded_retEmptySeq() {
        // Arrange
        // No arrangement

        // Act & Assert
        assertThat(this.sut.getInputTags().size(), equalTo(0));
    }

    @Test
    public void test_getInputTags_modelLoaded_retProcessorInputTags() {
        // Arrange
        sut.setIsLoaded(true);

        // Act
        Sequence result = this.sut.getInputTags();

        // Assert
        assertThat(this.sutProcessor.getInputTags().length, greaterThan(0));
        assertThat(result.size(), equalTo(this.sutProcessor.getInputTags().length));
        for (String inputTag : this.sutProcessor.getInputTags()) {
            assertTrue(result.contains(inputTag));
        }
    }

    @Test
    public void test_getNumberOfOutputs_modelLoaded_retProcessorOutputsCount() {
        // Arrange
        this.sut.setIsLoaded(true);

        // Act & Assert
        assertThat(this.sut.getNumberOfOutputs(), equalTo(this.sutProcessor.getNumberOfOutputs()));
    }

    @Test
    public void test_getNumberOfOutputs_modelNotLoaded_retZero() {
        // Arrange
        // No arrangement

        // Act & Assert
        assertThat(this.sut.getNumberOfOutputs(), equalTo(0));
    }

    @Test
    public void test_getOutputName_modelNotLoaded_retEmptyString() {
        // Arrange
        int index = anyInteger();

        // Act & Assert
        assertThat(this.sut.getOutputName(index), equalTo(""));
    }

    @Test
    public void test_getOutputName_modelLoaded_retProcessorOutputName() {
        // Arrange
        sut.setIsLoaded(true);
        int index = anyInteger();

        // Act
        String result = this.sut.getOutputName(index);

        // Assert
        verify(this.sutProcessor).getOutputName(index);
        assertThat(result, equalTo(this.sutProcessor.getOutputName(index)));
    }

    @Test
    public void test_getOutputNames_modelNotLoaded_retEmptySeq() {
        // Arrange
        // No arrangement

        // Act & Assert
        assertThat(this.sut.getOutputNames().size(), equalTo(0));
    }

    @Test
    public void test_getOutputNames_modelLoaded_retProcessorOutputNames() {
        // Arrange
        sut.setIsLoaded(true);

        // Act
        Sequence result = this.sut.getOutputNames();

        // Assert
        assertThat(this.sutProcessor.getOutputNames().length, greaterThan(0));
        assertThat(result.size(), equalTo(this.sutProcessor.getOutputNames().length));
        for (String outputName : this.sutProcessor.getOutputNames()) {
            assertTrue(result.contains(outputName));
        }
    }

    @Test
    public void test_getOutputTag_modelNotLoaded_retEmptyString() {
        // Arrange
        int index = anyInteger();

        // Act & Assert
        assertThat(this.sut.getOutputTag(index), equalTo(""));
    }

    @Test
    public void test_getOutputTag_modelLoaded_retProcessorOutputTag() {
        // Arrange
        sut.setIsLoaded(true);
        int index = anyInteger();

        // Act
        String result = this.sut.getOutputTag(index);

        // Assert
        verify(this.sutProcessor).getOutputTag(index);
        assertThat(result, equalTo(this.sutProcessor.getOutputTag(index)));
    }

    @Test
    public void test_getOutputTags_modelNotLoaded_retEmptySeq() {
        // Arrange
        // No arrangement

        // Act & Assert
        assertThat(this.sut.getOutputTags().size(), equalTo(0));
    }

    @Test
    public void test_getOutputTags_modelLoaded_retProcessorOutputTags() {
        // Arrange
        sut.setIsLoaded(true);

        // Act
        Sequence result = this.sut.getOutputTags();

        // Assert
        assertThat(this.sutProcessor.getOutputTags().length, greaterThan(0));
        assertThat(result.size(), equalTo(this.sutProcessor.getOutputTags().length));
        for (String OutputTag : this.sutProcessor.getOutputTags()) {
            assertTrue(result.contains(OutputTag));
        }
    }

    @Test
    public void test_setTimeFormatForG2_always_invokesSetTimeFormat() throws MathException, NoSuchAttributeException {
        // Arrange
        String timeFormat = "hh:mm:ss";

        // Act
        Structure retVal = this.sut.setTimeFormatForG2(timeFormat);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(true)));
        verify(this.sutProcessor).setTimeFormat(timeFormat);
    }

    @Test
    public void test_setTimeFormatForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        String timeFormat = "hh:mm:ss";
        MathException exception = new MathException("Failed to set time format.");
        doThrow(exception).when(this.sutProcessor).setTimeFormat(timeFormat);

        // Act
        Structure retVal = this.sut.setTimeFormatForG2(timeFormat);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_setInputAtTimeByIndexForG2_always_invokesSetInput() throws MathException, NoSuchAttributeException, ParseException {
        // Arrange
        int inputNumber = anyInteger();
        double value = anyDouble();
        String time = "06:00:00";

        // Act
        Structure retVal = this.sut.setInputAtTimeByIndexForG2(inputNumber, value, time);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(true)));
        verify(this.sutProcessor).setInputAtTimeByIndex(inputNumber, value, time);
    }

    @Test
    public void test_setInputAtTimeByIndexForG2_MathException_setsError() throws MathException, NoSuchAttributeException, ParseException {
        // Arrange
        int inputNumber = anyInteger();
        double value = anyDouble();
        String time = "06:00:00";
        MathException exception = new MathException("Failed to set input at time by index.");
        doThrow(exception).when(this.sutProcessor).setInputAtTimeByIndex(inputNumber, value, time);

        // Act
        Structure retVal = this.sut.setInputAtTimeByIndexForG2(inputNumber, value, time);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_setInputAtTimeByIndexForG2_ParseException_setsError() throws MathException, NoSuchAttributeException, ParseException {
        // Arrange
        int inputNumber = anyInteger();
        double value = anyDouble();
        String time = "06:00:00";
        ParseException exception = new ParseException("Failed to set input at time by index.", 0);
        doThrow(exception).when(this.sutProcessor).setInputAtTimeByIndex(inputNumber, value, time);

        // Act
        Structure retVal = this.sut.setInputAtTimeByIndexForG2(inputNumber, value, time);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_setInputAtTimeByNameForG2_always_invokesSetInput() throws MathException, NoSuchAttributeException, ParseException {
        // Arrange
        String varName = "Variable Tag 1";
        double value = anyDouble();
        String time = "07:30:00";

        // Act
        Structure retVal = this.sut.setInputAtTimeByNameForG2(varName, value, time);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(true)));
        verify(this.sutProcessor).setInputAtTimeByName(varName, value, time);
    }

    @Test
    public void test_setInputAtTimeByNameForG2_MathException_setsError() throws MathException, NoSuchAttributeException, ParseException {
        // Arrange
        String varName = "Variable Tag 1";
        double value = anyDouble();
        String time = "07:30:00";
        MathException exception = new MathException("Failed to set input at time by name.");
        doThrow(exception).when(this.sutProcessor).setInputAtTimeByName(varName, value, time);

        // Act
        Structure retVal = this.sut.setInputAtTimeByNameForG2(varName, value, time);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_setInputAtTimeByNameForG2_ParseException_setsError() throws MathException, NoSuchAttributeException, ParseException {
        // Arrange
        String varName = "Variable Tag 1";
        double value = anyDouble();
        String time = "07:30:00";
        ParseException exception = new ParseException("Failed to set input at time by name.", 0);
        doThrow(exception).when(this.sutProcessor).setInputAtTimeByName(varName, value, time);

        // Act
        Structure retVal = this.sut.setInputAtTimeByNameForG2(varName, value, time);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_setInputAtTimeByTagForG2_always_invokesSetInput() throws MathException, NoSuchAttributeException, ParseException {
        // Arrange
        String varTag = "Variable Tag 1";
        double value = anyDouble();
        String time = "07:30:00";

        // Act
        Structure retVal = this.sut.setInputAtTimeByTagForG2(varTag, value, time);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(true)));
        verify(this.sutProcessor).setInputAtTimeByTag(varTag, value, time);
    }

    @Test
    public void test_setInputAtTimeByTagForG2_MathException_setsError() throws MathException, NoSuchAttributeException, ParseException {
        // Arrange
        String varTag = "Variable Tag 1";
        double value = anyDouble();
        String time = "07:30:00";
        MathException exception = new MathException("Failed to set input at time by tag.");
        doThrow(exception).when(this.sutProcessor).setInputAtTimeByTag(varTag, value, time);

        // Act
        Structure retVal = this.sut.setInputAtTimeByTagForG2(varTag, value, time);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_setInputAtTimeByTagForG2_ParseException_setsError() throws MathException, NoSuchAttributeException, ParseException {
        // Arrange
        String varTag = "Variable Tag 1";
        double value = anyDouble();
        String time = "07:30:00";
        ParseException exception = new ParseException("Failed to set input at time by tag.", 0);
        doThrow(exception).when(this.sutProcessor).setInputAtTimeByTag(varTag, value, time);

        // Act
        Structure retVal = this.sut.setInputAtTimeByTagForG2(varTag, value, time);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_setInputForRowByIndexForG2_always_invokesSetInput() throws MathException, NoSuchAttributeException {
        // Arrange
        int inputName = anyInteger();
        double value = anyDouble();

        // Act
        Structure retVal = this.sut.setInputForRowByIndexForG2(inputName, value);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(true)));
        verify(this.sutProcessor).setInputForRowByIndex(inputName, value);
    }

    @Test
    public void test_setInputForRowByIndexForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        int inputName = anyInteger();
        double value = anyDouble();
        MathException exception = new MathException("Failed to set input for row by index.");
        doThrow(exception).when(this.sutProcessor).setInputForRowByIndex(inputName, value);

        // Act
        Structure retVal = this.sut.setInputForRowByIndexForG2(inputName, value);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_setInputForRowByNameForG2_always_invokesSetInput() throws MathException, NoSuchAttributeException {
        // Arrange
        String varName = "Variable Name 1";
        double value = anyDouble();

        // Act
        Structure retVal = this.sut.setInputForRowByNameForG2(varName, value);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(true)));
        verify(this.sutProcessor).setInputForRowByName(varName, value);
    }

    @Test
    public void test_setInputForRowByNameForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        String varName = "Variable Name 1";
        double value = anyDouble();
        MathException exception = new MathException("Failed to set input for row by name.");
        doThrow(exception).when(this.sutProcessor).setInputForRowByName(varName, value);

        // Act
        Structure retVal = this.sut.setInputForRowByNameForG2(varName, value);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_setInputForRowByTagForG2_always_invokesSetInput() throws MathException, NoSuchAttributeException {
        // Arrange
        String varTag = "Variable Tag 1";
        double value = anyDouble();

        // Act
        Structure retVal = this.sut.setInputForRowByTagForG2(varTag, value);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(true)));
        verify(this.sutProcessor).setInputForRowByTag(varTag, value);
    }

    @Test
    public void test_setInputForRowByTagForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        String varTag = "Variable Tag 1";
        double value = anyDouble();
        MathException exception = new MathException("Failed to set input for row by index.");
        doThrow(exception).when(this.sutProcessor).setInputForRowByTag(varTag, value);

        // Act
        Structure retVal = this.sut.setInputForRowByTagForG2(varTag, value);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getCurrentOutputByIndexForG2_always_invokesGetOutput() throws MathException, NoSuchAttributeException {
        // Arrange
        int inputNumber = anyInteger();
        double value = anyDouble();
        when(this.sutProcessor.getCurrentOutputByIndex(inputNumber)).thenReturn(value);

        // Act
        Structure retVal = this.sut.getCurrentOutputByIndexForG2(inputNumber);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(value)));
    }

    @Test
    public void test_getCurrentOutputByIndexForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        int inputNumber = anyInteger();
        MathException exception = new MathException("Failed to get current output by index.");
        when(this.sutProcessor.getCurrentOutputByIndex(inputNumber)).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getCurrentOutputByIndexForG2(inputNumber);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getCurrentOutputByNameForG2_always_invokesGetOutput() throws MathException, NoSuchAttributeException {
        // Arrange
        String varName = "Variable Name 1";
        double value = anyDouble();
        when(this.sutProcessor.getCurrentOutputByName(varName)).thenReturn(value);

        // Act
        Structure retVal = this.sut.getCurrentOutputByNameForG2(varName);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(value)));
    }

    @Test
    public void test_getCurrentOutputByNameForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        String varName = "Variable Name 1";
        MathException exception = new MathException("Failed to get current output by name.");
        when(this.sutProcessor.getCurrentOutputByName(varName)).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getCurrentOutputByNameForG2(varName);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getCurrentOutputByTagForG2_always_invokesGetOutput() throws MathException, NoSuchAttributeException {
        // Arrange
        String varTag = "Variable Tag 1";
        double value = anyDouble();
        when(this.sutProcessor.getCurrentOutputByTag(varTag)).thenReturn(value);

        // Act
        Structure retVal = this.sut.getCurrentOutputByTagForG2(varTag);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(value)));
    }

    @Test
    public void test_getCurrentOutputByTagForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        String varTag = "Variable Tag 1";
        MathException exception = new MathException("Failed to get current output by tag.");
        when(this.sutProcessor.getCurrentOutputByTag(varTag)).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getCurrentOutputByTagForG2(varTag);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getOutputAtTimeByIndexForG2_always_invokesGetOutput() throws MathException, NoSuchAttributeException, ParseException {
        // Arrange
        int inputNumber = anyInteger();
        String time = "02:45:00";
        double value = anyDouble();
        when(this.sutProcessor.getOutputAtTimeByIndex(inputNumber, time)).thenReturn(value);

        // Act
        Structure retVal = this.sut.getOutputAtTimeByIndexForG2(inputNumber, time);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(value)));
    }

    @Test
    public void test_getOutputAtTimeByIndexForG2_MathException_setsError() throws MathException, NoSuchAttributeException, ParseException {
        // Arrange
        int inputNumber = anyInteger();
        String time = "02:45:00";
        MathException exception = new MathException("Failed to get current output by index.");
        when(this.sutProcessor.getOutputAtTimeByIndex(inputNumber, time)).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getOutputAtTimeByIndexForG2(inputNumber, time);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getOutputAtTimeByIndexForG2_ParseException_setsError() throws MathException, NoSuchAttributeException, ParseException {
        // Arrange
        int inputNumber = anyInteger();
        String time = "02:45:00";
        ParseException exception = new ParseException("Failed to get current output by index.", 0);
        when(this.sutProcessor.getOutputAtTimeByIndex(inputNumber, time)).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getOutputAtTimeByIndexForG2(inputNumber, time);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getOutputAtTimeByNameForG2_always_invokesGetOutput() throws MathException, NoSuchAttributeException, ParseException {
        // Arrange
        String varName = "Variable Name 1";
        String time = "02:45:00";
        double value = anyDouble();
        when(this.sutProcessor.getOutputAtTimeByName(varName, time)).thenReturn(value);

        // Act
        Structure retVal = this.sut.getOutputAtTimeByNameForG2(varName, time);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(value)));
    }

    @Test
    public void test_getOutputAtTimeByNameForG2_MathException_setsError() throws MathException, NoSuchAttributeException, ParseException {
        // Arrange
        String varName = "Variable Name 1";
        String time = "02:45:00";
        MathException exception = new MathException("Failed to get current output by name.");
        when(this.sutProcessor.getOutputAtTimeByName(varName, time)).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getOutputAtTimeByNameForG2(varName, time);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getOutputAtTimeByNameForG2_ParseException_setsError() throws MathException, NoSuchAttributeException, ParseException {
        // Arrange
        String varName = "Variable Name 1";
        String time = "02:45:00";
        ParseException exception = new ParseException("Failed to get current output by index.", 0);
        when(this.sutProcessor.getOutputAtTimeByName(varName, time)).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getOutputAtTimeByNameForG2(varName, time);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getOutputAtTimeByTagForG2_always_invokesGetOutput() throws MathException, NoSuchAttributeException, ParseException {
        // Arrange
        String varTag = "Variable Tag 1";
        String time = "02:45:00";
        double value = anyDouble();
        when(this.sutProcessor.getOutputAtTimeByTag(varTag, time)).thenReturn(value);

        // Act
        Structure retVal = this.sut.getOutputAtTimeByTagForG2(varTag, time);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(value)));
    }

    @Test
    public void test_getOutputAtTimeByTagForG2_MathException_setsError() throws MathException, NoSuchAttributeException, ParseException {
        // Arrange
        String varTag = "Variable Tag 1";
        String time = "02:45:00";
        MathException exception = new MathException("Failed to get current output by tag.");
        when(this.sutProcessor.getOutputAtTimeByTag(varTag, time)).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getOutputAtTimeByTagForG2(varTag, time);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getOutputAtTimeByTagForG2_ParseException_setsError() throws MathException, NoSuchAttributeException, ParseException {
        // Arrange
        String varTag = "Variable Tag 1";
        String time = "02:45:00";
        ParseException exception = new ParseException("Failed to get current output by index.", 0);
        when(this.sutProcessor.getOutputAtTimeByTag(varTag, time)).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getOutputAtTimeByTagForG2(varTag, time);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_hasTimeStamps_always_retPrepHasTimeStamps() throws NoSuchAttributeException {
        // Arrange
        boolean[] testCases = {true, false};

        for (boolean testCase : testCases) {
            when(this.sutProcessor.getHasTimeStamps()).thenReturn(testCase);

            // Act & Assert
            assertThat(this.sut.hasTimeStamps().getAttributeValue(RETVAL), is(equalTo(testCase)));
        }
    }

    @Test
    public void test_getMaxValueByNameForG2_always_invokesGetMaxValue() throws MathException, NoSuchAttributeException {
        // Arrange
        String varName = "Variable Name 1";
        Double value = anyDouble();
        when(this.sutProcessor.getMaxValueByName(varName)).thenReturn(value);

        // Act
        Structure retVal = this.sut.getMaxValueByNameForG2(varName);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(value)));
    }

    @Test
    public void test_getMaxValueByNameForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        String varName = "Variable Name 1";
        MathException exception = new MathException("Failed to get max value.");
        when(this.sutProcessor.getMaxValueByName(varName)).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getMaxValueByNameForG2(varName);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getMaxValueByTagForG2_always_invokesGetMaxValue() throws MathException, NoSuchAttributeException {
        // Arrange
        String varTag = "Variable Tag 1";
        Double value = anyDouble();
        when(this.sutProcessor.getMaxValueByTag(varTag)).thenReturn(value);

        // Act
        Structure retVal = this.sut.getMaxValueByTagForG2(varTag);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(value)));
    }

    @Test
    public void test_getMaxValueByTagForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        String varTag = "Variable Tag 1";
        MathException exception = new MathException("Failed to get tag value.");
        when(this.sutProcessor.getMaxValueByTag(varTag)).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getMaxValueByTagForG2(varTag);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getMinValueByNameForG2_always_invokesGetMinValue() throws MathException, NoSuchAttributeException {
        // Arrange
        String varName = "Variable Name 1";
        Double value = anyDouble();
        when(this.sutProcessor.getMinValueByName(varName)).thenReturn(value);

        // Act
        Structure retVal = this.sut.getMinValueByNameForG2(varName);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(value)));
    }

    @Test
    public void test_getMinValueByNameForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        String varName = "Variable Name 1";
        MathException exception = new MathException("Failed to get minimum value.");
        when(this.sutProcessor.getMinValueByName(varName)).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getMinValueByNameForG2(varName);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getMinValueByTagForG2_always_invokesGetMinValue() throws MathException, NoSuchAttributeException {
        // Arrange
        String varTag = "Variable Tag 1";
        Double value = anyDouble();
        when(this.sutProcessor.getMinValueByTag(varTag)).thenReturn(value);

        // Act
        Structure retVal = this.sut.getMinValueByTagForG2(varTag);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(value)));
    }

    @Test
    public void test_getMinValueByTagForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        String varTag = "Variable Tag 1";
        MathException exception = new MathException("Failed to get minimum value.");
        when(this.sutProcessor.getMinValueByTag(varTag)).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getMinValueByTagForG2(varTag);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getMeanValueByNameForG2_always_invokesGetMean() throws MathException, NoSuchAttributeException {
        // Arrange
        String varName = "Variable Name 1";
        Double value = anyDouble();
        when(this.sutProcessor.getMeanValueByName(varName)).thenReturn(value);

        // Act
        Structure retVal = this.sut.getMeanValueByNameForG2(varName);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(value)));
    }

    @Test
    public void test_getMeanValueByNameForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        String varName = "Variable Name 1";
        MathException exception = new MathException("Failed to get mean value.");
        when(this.sutProcessor.getMeanValueByName(varName)).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getMeanValueByNameForG2(varName);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getMeanValueByTagForG2_always_invokesGetMean() throws MathException, NoSuchAttributeException {
        // Arrange
        String varTag = "Variable Tag 1";
        Double value = anyDouble();
        when(this.sutProcessor.getMeanValueByTag(varTag)).thenReturn(value);

        // Act
        Structure retVal = this.sut.getMeanValueByTagForG2(varTag);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(value)));
    }

    @Test
    public void test_getMeanValueByTagForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        String varTag = "Variable Tag 1";
        MathException exception = new MathException("Failed to get mean value.");
        when(this.sutProcessor.getMeanValueByTag(varTag)).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getMeanValueByTagForG2(varTag);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getMedianValueByNameForG2_always_invokesGetMedian() throws MathException, NoSuchAttributeException {
        // Arrange
        String varName = "Variable Name 1";
        Double value = anyDouble();
        when(this.sutProcessor.getMedianValueByName(varName)).thenReturn(value);

        // Act
        Structure retVal = this.sut.getMedianValueByNameForG2(varName);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(value)));
    }

    @Test
    public void test_getMedianValueByNameForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        String varName = "Variable Name 1";
        MathException exception = new MathException("Failed to get median value.");
        when(this.sutProcessor.getMedianValueByName(varName)).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getMedianValueByNameForG2(varName);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getMedianValueByTagForG2_always_invokesGetMedian() throws MathException, NoSuchAttributeException {
        // Arrange
        String varTag = "Variable Tag 1";
        Double value = anyDouble();
        when(this.sutProcessor.getMedianValueByTag(varTag)).thenReturn(value);

        // Act
        Structure retVal = this.sut.getMedianValueByTagForG2(varTag);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(value)));
    }

    @Test
    public void test_getMedianValueByTagForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        String varTag = "Variable Tag 1";
        MathException exception = new MathException("Failed to get median value.");
        when(this.sutProcessor.getMedianValueByTag(varTag)).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getMedianValueByTagForG2(varTag);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getSumValueByNameForG2_always_invokesGetSum() throws MathException, NoSuchAttributeException {
        // Arrange
        String varName = "Variable Name 1";
        Double value = anyDouble();
        when(this.sutProcessor.getSumValueByName(varName)).thenReturn(value);

        // Act
        Structure retVal = this.sut.getSumValueByNameForG2(varName);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(value)));
    }

    @Test
    public void test_getSumValueByNameForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        String varName = "Variable Name 1";
        MathException exception = new MathException("Failed to get sum value.");
        when(this.sutProcessor.getSumValueByName(varName)).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getSumValueByNameForG2(varName);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getSumValueByTagForG2_always_invokesGetSum() throws MathException, NoSuchAttributeException {
        // Arrange
        String varTag = "Variable Tag 1";
        Double value = anyDouble();
        when(this.sutProcessor.getSumValueByTag(varTag)).thenReturn(value);

        // Act
        Structure retVal = this.sut.getSumValueByTagForG2(varTag);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(value)));
    }

    @Test
    public void test_getSumValueByTagForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        String varTag = "Variable Tag 1";
        MathException exception = new MathException("Failed to get sum value.");
        when(this.sutProcessor.getSumValueByTag(varTag)).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getSumValueByTagForG2(varTag);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getSTDValueByNameForG2_always_invokesGetSTD() throws MathException, NoSuchAttributeException {
        // Arrange
        String varName = "Variable Name 1";
        Double value = anyDouble();
        when(this.sutProcessor.getSTDValueByName(varName)).thenReturn(value);

        // Act
        Structure retVal = this.sut.getSTDValueByNameForG2(varName);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(value)));
    }

    @Test
    public void test_getSTDValueByNameForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        String varName = "Variable Name 1";
        MathException exception = new MathException("Failed to get STD value.");
        when(this.sutProcessor.getSTDValueByName(varName)).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getSTDValueByNameForG2(varName);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getSTDValueByTagForG2_always_invokesGetSTD() throws MathException, NoSuchAttributeException {
        // Arrange
        String varTag = "Variable Tag 1";
        Double value = anyDouble();
        when(this.sutProcessor.getSTDValueByTag(varTag)).thenReturn(value);

        // Act
        Structure retVal = this.sut.getSTDValueByTagForG2(varTag);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(value)));
    }

    @Test
    public void test_getSTDValueByTagForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        String varTag = "Variable Tag 1";
        MathException exception = new MathException("Failed to get STD value.");
        when(this.sutProcessor.getSTDValueByTag(varTag)).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getSTDValueByTagForG2(varTag);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getVarianceValueByNameForG2_always_invokesGetVariance() throws MathException, NoSuchAttributeException {
        // Arrange
        String varName = "Variable Name 1";
        Double value = anyDouble();
        when(this.sutProcessor.getVarianceValueByName(varName)).thenReturn(value);

        // Act
        Structure retVal = this.sut.getVarianceValueByNameForG2(varName);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(value)));
    }

    @Test
    public void test_getVarianceValueByNameForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        String varName = "Variable Name 1";
        MathException exception = new MathException("Failed to get variance value.");
        when(this.sutProcessor.getVarianceValueByName(varName)).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getVarianceValueByNameForG2(varName);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getVarianceValueByTagForG2_always_invokesGetVariance() throws MathException, NoSuchAttributeException {
        // Arrange
        String varTag = "Variable Tag 1";
        Double value = anyDouble();
        when(this.sutProcessor.getVarianceValueByTag(varTag)).thenReturn(value);

        // Act
        Structure retVal = this.sut.getVarianceValueByTagForG2(varTag);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(value)));
    }

    @Test
    public void test_getVarianceValueByTagForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        String varTag = "Variable Tag 1";
        MathException exception = new MathException("Failed to get variance value.");
        when(this.sutProcessor.getVarianceValueByTag(varTag)).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getVarianceValueByTagForG2(varTag);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getKurtValueByNameForG2_always_invokesGetKurt() throws MathException, NoSuchAttributeException {
        // Arrange
        String varName = "Variable Name 1";
        Double value = anyDouble();
        when(this.sutProcessor.getKurtValueByName(varName)).thenReturn(value);

        // Act
        Structure retVal = this.sut.getKurtValueByNameForG2(varName);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(value)));
    }

    @Test
    public void test_getKurtValueByNameForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        String varName = "Variable Name 1";
        MathException exception = new MathException("Failed to get kurtosis value.");
        when(this.sutProcessor.getKurtValueByName(varName)).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getKurtValueByNameForG2(varName);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getKurtValueByTagForG2_always_invokesGetKurt() throws MathException, NoSuchAttributeException {
        // Arrange
        String varTag = "Variable Tag 1";
        Double value = anyDouble();
        when(this.sutProcessor.getKurtValueByTag(varTag)).thenReturn(value);

        // Act
        Structure retVal = this.sut.getKurtValueByTagForG2(varTag);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(value)));
    }

    @Test
    public void test_getKurtValueByTagForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        String varTag = "Variable Tag 1";
        MathException exception = new MathException("Failed to get kurtosis value.");
        when(this.sutProcessor.getKurtValueByTag(varTag)).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getKurtValueByTagForG2(varTag);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getSkewValueByNameForG2_always_invokesGetSkew() throws MathException, NoSuchAttributeException {
        // Arrange
        String varName = "Variable Name 1";
        Double value = anyDouble();
        when(this.sutProcessor.getSkewValueByName(varName)).thenReturn(value);

        // Act
        Structure retVal = this.sut.getSkewValueByNameForG2(varName);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(value)));
    }

    @Test
    public void test_getSkewValueByNameForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        String varName = "Variable Name 1";
        MathException exception = new MathException("Failed to get skew value.");
        when(this.sutProcessor.getSkewValueByName(varName)).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getSkewValueByNameForG2(varName);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getSkewValueByTagForG2_always_invokesGetSkew() throws MathException, NoSuchAttributeException {
        // Arrange
        String varTag = "Variable Tag 1";
        Double value = anyDouble();
        when(this.sutProcessor.getSkewValueByTag(varTag)).thenReturn(value);

        // Act
        Structure retVal = this.sut.getSkewValueByTagForG2(varTag);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(value)));
    }

    @Test
    public void test_getSkewValueByTagForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        String varTag = "Variable Tag 1";
        MathException exception = new MathException("Failed to get skew value.");
        when(this.sutProcessor.getSkewValueByTag(varTag)).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getSkewValueByTagForG2(varTag);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getRangeValueByNameForG2_always_invokesGetRange() throws MathException, NoSuchAttributeException {
        // Arrange
        String varName = "Variable Name 1";
        Double value = anyDouble();
        when(this.sutProcessor.getRangeValueByName(varName)).thenReturn(value);

        // Act
        Structure retVal = this.sut.getRangeValueByNameForG2(varName);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(value)));
    }

    @Test
    public void test_getRangeValueByNameForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        String varName = "Variable Name 1";
        MathException exception = new MathException("Failed to get range value.");
        when(this.sutProcessor.getRangeValueByName(varName)).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getRangeValueByNameForG2(varName);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getRangeValueByTagForG2_always_invokesGetRange() throws MathException, NoSuchAttributeException {
        // Arrange
        String varTag = "Variable Tag 1";
        Double value = anyDouble();
        when(this.sutProcessor.getRangeValueByTag(varTag)).thenReturn(value);

        // Act
        Structure retVal = this.sut.getRangeValueByTagForG2(varTag);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(value)));
    }

    @Test
    public void test_getRangeValueByTagForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        String varTag = "Variable Tag 1";
        MathException exception = new MathException("Failed to get range value.");
        when(this.sutProcessor.getRangeValueByTag(varTag)).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getRangeValueByTagForG2(varTag);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getInputDelayByNameForG2_always_invokesGetInputDelay() throws MathException, NoSuchAttributeException {
        // Arrange
        String varName = "Variable Name 1";
        long[] delays = {System.currentTimeMillis(), System.currentTimeMillis() + 1, System.currentTimeMillis() + 2};
        when(this.sutProcessor.getInputDelayByName(varName)).thenReturn(delays);

        // Act
        Structure retVal = this.sut.getInputDelayByNameForG2(varName);

        // Assert
        Sequence actual = (Sequence) retVal.getAttributeValue(RETVAL);
        assertThat(delays.length, is(greaterThan(0)));
        assertThat(actual.size(), is(equalTo(delays.length)));
        for (int i = 0; i < delays.length; i++) {
            assertThat(actual.get(i), is(equalTo((double) delays[i])));
        }
    }

    @Test
    public void test_getInputDelayByNameForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        String varName = "Variable Name 1";
        MathException exception = new MathException("Failed to get input delay.");
        when(this.sutProcessor.getInputDelayByName(varName)).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getInputDelayByNameForG2(varName);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getInputDelayByTagForG2_always_invokesgetInputDelay() throws MathException, NoSuchAttributeException, IOException {
        // Arrange
        String varTag = "Variable Tag 1";
        long[] delays = {System.currentTimeMillis(), System.currentTimeMillis() + 1, System.currentTimeMillis() + 2};
        when(this.sutProcessor.getInputDelayByTag(varTag)).thenReturn(delays);

        // Act
        Structure retVal = this.sut.getInputDelayByTagForG2(varTag);

        // Assert
        Sequence actual = (Sequence) retVal.getAttributeValue(RETVAL);
        assertThat(delays.length, is(greaterThan(0)));
        assertThat(actual.size(), is(equalTo(delays.length)));
        for (int i = 0; i < delays.length; i++) {
            assertThat(actual.get(i), is(equalTo((double) delays[i])));
        }
    }

    @Test
    public void test_getInputDelayByTagForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        String varTag = "Variable Tag 1";
        MathException exception = new MathException("Failed to get input delay.");
        when(this.sutProcessor.getInputDelayByTag(varTag)).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getInputDelayByTagForG2(varTag);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getFormulasForG2_always_invokesGetFormulas() throws MathException, NoSuchAttributeException {
        // Arrange
        String formulas = "Formulas";
        when(this.sutProcessor.getFormulas()).thenReturn(formulas);

        // Act
        Structure retVal = this.sut.getFormulasForG2();

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(formulas)));
    }

    @Test
    public void test_getFormulasForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        MathException exception = new MathException("Failed to get input delay.");
        when(this.sutProcessor.getFormulas()).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getFormulasForG2();

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_clearDataBufferForG2_modelNotLoaded_doesNotInvokeMethod() throws MathException, NoSuchAttributeException, IOException {
        // Arrange
        // No arrangement

        // Act
        Structure result = this.sut.clearDataBufferForG2();

        // Assert
        verify(this.sutProcessor, never()).clearDataBuffer();
        // Asserting that no attributes are set
        assertThat(result.getAttributeCount(), equalTo(0));
    }

    @Test
    public void test_clearDataBufferForG2_modelLoaded_invokesClearDataBuffer() throws MathException, NoSuchAttributeException, IOException {
        // Arrange
        this.sut.setIsLoaded(true);

        // Act
        Structure result = this.sut.clearDataBufferForG2();

        // Assert
        verify(this.sutProcessor).clearDataBuffer();
        // Asserting that no attributes are set
        assertThat(result.getAttributeCount(), equalTo(0));
    }

    @Test
    public void test_clearDataBufferForG2_exception_setsError() throws MathException, NoSuchAttributeException, IOException {
        // Arrange
        this.sut.setIsLoaded(true);
        MathException exception = new MathException("Failed to clear data buffer.");
        doThrow(exception).when(this.sutProcessor).clearDataBuffer();

        // Act
        Structure retVal = this.sut.clearDataBufferForG2();

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_trainModel_debugEnabled_outputToConsole() {
        // Arrange
        Sequence input = createInputSequence();
        Sequence output = createOutputSequence();
        double timeInMinute = anyDouble();

        this.sut.setIsLoaded(true);
        this.sut.setDebugProcessor(true);

        // Act
        this.sut.trainModel(input, output, timeInMinute, false, false, false);

        // Assert
        assertTrue(outContent.toString().contains("start re-training model"));
        assertTrue(outContent.toString().contains("start re-training model isloaded=" + this.sut.isLoaded()));
        assertTrue(outContent.toString().contains("start re-training model in processor"));
    }

    @Test
    public void test_trainModel_debugNotEnabled_doesNotOutputToConsole() {
        // Arrange
        Sequence input = createInputSequence();
        Sequence output = createOutputSequence();
        double timeInMinute = anyDouble();

        this.sut.setIsLoaded(true);
        this.sut.setDebugProcessor(false);

        // Act
        this.sut.trainModel(input, output, timeInMinute, false, false, false);

        // Assert
        assertFalse(outContent.toString().contains("start re-training model"));
        assertFalse(outContent.toString().contains("start re-training model isloaded=" + this.sut.isLoaded()));
        assertFalse(outContent.toString().contains("start re-training model in processor"));
    }

    @Test
    public void test_trainModel_modelNotLoaded_informsG2Error() throws G2AccessException {
        // Arrange
        Sequence input = createInputSequence();
        Sequence output = createOutputSequence();
        double timeInMinute = anyDouble();

        // Act
        this.sut.trainModel(input, output, timeInMinute, false, false, false);

        // Assert
        verify(NolG2Gateway.g2Gateway).informG2ErrorOccur(this.sutG2Uuid, true, "Can not train unloaded model");
    }

    @Test
    public void test_trainModel_inputOutputSizeMismatch_informsG2Error() throws G2AccessException {
        // Arrange
        this.sut.setIsLoaded(true);
        Sequence input = createInputSequence();
        Sequence output = createOutputSequence();
        double timeInMinute = anyDouble();

        input.removeElementAt(0);

        // Act
        this.sut.trainModel(input, output, timeInMinute, false, false, false);

        // Assert
        verify(NolG2Gateway.g2Gateway).informG2ErrorOccur(this.sutG2Uuid, true, "Input and Output don't have the same number of samples.");
    }

    @Test
    public void test_trainModel_notEnoughSamples_informsG2Error() throws G2AccessException {
        // Arrange
        Sequence input = createInputSequence();
        Sequence output = createOutputSequence();
        double timeInMinute = anyDouble();

        this.sut.setIsLoaded(true);
        input.removeElementAt(0);
        output.removeElementAt(0);

        // Act
        this.sut.trainModel(input, output, timeInMinute, false, false, false);

        // Assert
        verify(NolG2Gateway.g2Gateway).informG2ErrorOccur(this.sutG2Uuid, true, "There is not enough data for training.");
    }

    @Test
    public void test_trainModel_always_invokesMethodWithMatrixX() throws G2AccessException, MathException {
        // Arrange
        Sequence input = createInputSequence();
        Sequence output = createOutputSequence();
        double timeInMinute = anyDouble();

        this.sut.setIsLoaded(true);

        Matrix expectedMatrix = expectedMatrix(input);
        ArgumentCaptor<Matrix> matrixXCaptor = ArgumentCaptor.forClass(Matrix.class);

        // Act
        this.sut.trainModel(input, output, timeInMinute, false, false, false);

        // Assert
        verify(this.sutProcessor).trainModel(Matchers.any(Vector.class), matrixXCaptor.capture(), Matchers.any(Matrix.class), Matchers.anyDouble(), Matchers.anyBoolean(), Matchers.anyBoolean(), Matchers.anyBoolean());
        assertThatMatricesAreEqual(matrixXCaptor.getValue(), expectedMatrix);
    }

    @Test
    public void test_trainModel_always_invokesMethodWithMatrixY() throws G2AccessException, MathException {
        // Arrange
        Sequence input = createInputSequence();
        Sequence output = createOutputSequence();
        double timeInMinute = anyDouble();

        this.sut.setIsLoaded(true);

        Matrix expectedMatrix = expectedMatrix(output);
        ArgumentCaptor<Matrix> matrixYCaptor = ArgumentCaptor.forClass(Matrix.class);

        // Act
        this.sut.trainModel(input, output, timeInMinute, false, false, false);

        // Assert
        verify(this.sutProcessor).trainModel(Matchers.any(Vector.class), Matchers.any(Matrix.class), matrixYCaptor.capture(), Matchers.anyDouble(), Matchers.anyBoolean(), Matchers.anyBoolean(), Matchers.anyBoolean());
        assertThatMatricesAreEqual(matrixYCaptor.getValue(), expectedMatrix);
    }

    @Test
    public void test_trainModel_always_invokesMethodWithTime() throws G2AccessException, MathException {
        // Arrange
        Sequence input = createInputSequence();
        Sequence output = createOutputSequence();
        double timeInMinute = anyDouble();

        this.sut.setIsLoaded(true);

        ArgumentCaptor<Double> timeInMinuteCaptor = ArgumentCaptor.forClass(Double.class);

        // Act
        this.sut.trainModel(input, output, timeInMinute, false, false, false);

        // Assert
        verify(this.sutProcessor).trainModel(Matchers.any(Vector.class), Matchers.any(Matrix.class), Matchers.any(Matrix.class), timeInMinuteCaptor.capture(), Matchers.anyBoolean(), Matchers.anyBoolean(), Matchers.anyBoolean());
        assertThat(timeInMinuteCaptor.getValue(), is(equalTo(timeInMinute * MILLISECONDS_IN_MINUTE)));
    }

    @Test
    public void test_trainModel_timeIsNotSet_setsTimeAsOne() throws G2AccessException, MathException {
        // Arrange
        Sequence input = createInputSequence();
        Sequence output = createOutputSequence();

        this.sut.setIsLoaded(true);
        double timeInMinute = 0;

        ArgumentCaptor<Double> timeInMinuteCaptor = ArgumentCaptor.forClass(Double.class);

        // Act
        this.sut.trainModel(input, output, timeInMinute, false, false, false);

        // Assert
        verify(this.sutProcessor).trainModel(Matchers.any(Vector.class), Matchers.any(Matrix.class), Matchers.any(Matrix.class), timeInMinuteCaptor.capture(), Matchers.anyBoolean(), Matchers.anyBoolean(), Matchers.anyBoolean());
        assertThat(timeInMinuteCaptor.getValue(), is(equalTo(1.0 * MILLISECONDS_IN_MINUTE)));
    }

    @Test
    public void test_trainModel_always_invokesMethodWithAutoStop() throws G2AccessException, MathException {
        // Arrange
        Sequence input = createInputSequence();
        Sequence output = createOutputSequence();
        double timeInMinute = anyDouble();

        this.sut.setIsLoaded(true);
        boolean[] testCases = {true, false};

        ArgumentCaptor<Boolean> autoStopCaptor = ArgumentCaptor.forClass(Boolean.class);

        for (boolean testCase : testCases) {
            reset(this.sutProcessor);

            // Act
            this.sut.trainModel(input, output, timeInMinute, testCase, false, false);

            // Assert
            verify(this.sutProcessor).trainModel(Matchers.any(Vector.class), Matchers.any(Matrix.class), Matchers.any(Matrix.class), Matchers.any(Double.class), autoStopCaptor.capture(), Matchers.anyBoolean(), Matchers.anyBoolean());
            assertThat(autoStopCaptor.getValue(), is(equalTo(testCase)));
        }
    }

    @Test
    public void test_trainModel_always_invokesMethodWithNewTraining() throws G2AccessException, MathException {
        // Arrange
        Sequence input = createInputSequence();
        Sequence output = createOutputSequence();
        double timeInMinute = anyDouble();

        this.sut.setIsLoaded(true);
        boolean[] testCases = {true, false};

        ArgumentCaptor<Boolean> newTrainingCaptor = ArgumentCaptor.forClass(Boolean.class);

        for (boolean testCase : testCases) {
            reset(this.sutProcessor);

            // Act
            this.sut.trainModel(input, output, timeInMinute, false, testCase, false);

            // Assert
            verify(this.sutProcessor).trainModel(Matchers.any(Vector.class), Matchers.any(Matrix.class), Matchers.any(Matrix.class), Matchers.any(Double.class), Matchers.anyBoolean(), newTrainingCaptor.capture(), Matchers.anyBoolean());
            assertThat(newTrainingCaptor.getValue(), is(equalTo(testCase)));
        }
    }

    @Test
    public void test_trainModel_always_invokesMethodWithDisplay() throws G2AccessException, MathException {
        // Arrange
        Sequence input = createInputSequence();
        Sequence output = createOutputSequence();
        double timeInMinute = anyDouble();

        this.sut.setIsLoaded(true);
        boolean[] testCases = {true, false};

        ArgumentCaptor<Boolean> displayCaptor = ArgumentCaptor.forClass(Boolean.class);

        for (boolean testCase : testCases) {
            reset(this.sutProcessor);

            // Act
            this.sut.trainModel(input, output, timeInMinute, false, false, testCase);

            // Assert
            verify(this.sutProcessor).trainModel(Matchers.any(Vector.class), Matchers.any(Matrix.class), Matchers.any(Matrix.class), Matchers.any(Double.class), Matchers.anyBoolean(), Matchers.anyBoolean(), displayCaptor.capture());
            assertThat(displayCaptor.getValue(), is(equalTo(testCase)));
        }
    }

    @Test
    public void test_trainModel_exception_informsG2Error() throws G2AccessException, MathException {
        // Arrange
        Sequence input = createInputSequence();
        Sequence output = createOutputSequence();
        double timeInMinute = anyDouble();

        this.sut.setIsLoaded(true);
        MathException exception = new MathException("Failed to train model.");
        doThrow(exception).when(this.sutProcessor).trainModel(Matchers.any(Vector.class), Matchers.any(Matrix.class), Matchers.any(Matrix.class), Matchers.anyDouble(), Matchers.anyBoolean(), Matchers.anyBoolean(), Matchers.anyBoolean());

        // Act
        this.sut.trainModel(input, output, timeInMinute, false, false, false);

        // Assert
        verify(NolG2Gateway.g2Gateway).informG2ErrorOccur(this.sutG2Uuid, true, exception.getMessage());
    }

    @Test
    public void test_trainModelFromFile_debugEnabled_outputToConsole() {
        // Arrange
        String inputDataFileName = "inputDataFileName";
        String outputDataFileName = "outputDataFileName";
        double timeInMinute = anyDouble();

        this.sut.setIsLoaded(true);
        this.sut.setDebugProcessor(true);

        // Act
        this.sut.trainModelFromFile(inputDataFileName, outputDataFileName, timeInMinute, false, false, false);

        // Assert
        assertTrue(outContent.toString().contains("start re-training model"));
    }

    @Test
    public void test_trainModelFromFile_debugNotEnabled_doesNotOutputToConsole() {
        // Arrange
        String inputDataFileName = "inputDataFileName";
        String outputDataFileName = "outputDataFileName";
        double timeInMinute = anyDouble();

        this.sut.setIsLoaded(true);
        this.sut.setDebugProcessor(false);

        // Act
        this.sut.trainModelFromFile(inputDataFileName, outputDataFileName, timeInMinute, false, false, false);

        // Assert
        assertFalse(outContent.toString().contains("start re-training model"));
    }

    @Test
    public void test_trainModelFromFile_modelNotLoaded_informsG2Error() throws G2AccessException {
        // Arrange
        String inputDataFileName = "inputDataFileName";
        String outputDataFileName = "outputDataFileName";
        double timeInMinute = anyDouble();

        // Act
        this.sut.trainModelFromFile(inputDataFileName, outputDataFileName, timeInMinute, false, false, false);

        // Assert
        verify(NolG2Gateway.g2Gateway).informG2ErrorOccur(this.sutG2Uuid, true, "Can not train unloaded model");
    }

    @Test
    public void test_trainModelFromFile_always_invokesMethodWithTime() throws G2AccessException, MathException, IOException {
        // Arrange
        String inputDataFileName = "inputDataFileName";
        String outputDataFileName = "outputDataFileName";
        double timeInMinute = anyDouble();

        this.sut.setIsLoaded(true);

        ArgumentCaptor<Double> timeInMinuteCaptor = ArgumentCaptor.forClass(Double.class);

        // Act
        this.sut.trainModelFromFile(inputDataFileName, outputDataFileName, timeInMinute, false, false, false);

        // Assert
        verify(this.sutProcessor).trainModelFromFile(Matchers.any(Vector.class), Matchers.anyString(), Matchers.anyString(), timeInMinuteCaptor.capture(), Matchers.anyBoolean(), Matchers.anyBoolean(), Matchers.anyBoolean());
        assertThat(timeInMinuteCaptor.getValue(), is(equalTo(timeInMinute * MILLISECONDS_IN_MINUTE)));
    }

    @Test
    public void test_trainModelFromFile_always_invokesMethodWithInputFile() throws G2AccessException, MathException, IOException {
        // Arrange
        String inputDataFileName = "inputDataFileName";
        String outputDataFileName = "outputDataFileName";
        double timeInMinute = anyDouble();

        this.sut.setIsLoaded(true);

        ArgumentCaptor<String> inputFileStringCaptor = ArgumentCaptor.forClass(String.class);

        // Act
        this.sut.trainModelFromFile(inputDataFileName, outputDataFileName, timeInMinute, false, false, false);

        // Assert
        verify(this.sutProcessor).trainModelFromFile(Matchers.any(Vector.class), inputFileStringCaptor.capture(), Matchers.anyString(), Matchers.anyDouble(), Matchers.anyBoolean(), Matchers.anyBoolean(), Matchers.anyBoolean());
        assertThat(inputFileStringCaptor.getValue(), is(equalTo(inputDataFileName)));
    }

    @Test
    public void test_trainModelFromFile_always_invokesMethodWithOutputFile() throws G2AccessException, MathException, IOException {
        // Arrange
        String inputDataFileName = "inputDataFileName";
        String outputDataFileName = "outputDataFileName";
        double timeInMinute = anyDouble();

        this.sut.setIsLoaded(true);

        ArgumentCaptor<String> outputFileStringCaptor = ArgumentCaptor.forClass(String.class);

        // Act
        this.sut.trainModelFromFile(inputDataFileName, outputDataFileName, timeInMinute, false, false, false);

        // Assert
        verify(this.sutProcessor).trainModelFromFile(Matchers.any(Vector.class), Matchers.anyString(), outputFileStringCaptor.capture(), Matchers.anyDouble(), Matchers.anyBoolean(), Matchers.anyBoolean(), Matchers.anyBoolean());
        assertThat(outputFileStringCaptor.getValue(), is(equalTo(outputDataFileName)));
    }

    @Test
    public void test_trainModelFromFile_timeIsNotSet_setsTimeAsOne() throws G2AccessException, MathException, IOException {
        // Arrange
        String inputDataFileName = "inputDataFileName";
        String outputDataFileName = "outputDataFileName";

        this.sut.setIsLoaded(true);
        double timeInMinute = 0;

        ArgumentCaptor<Double> timeInMinuteCaptor = ArgumentCaptor.forClass(Double.class);

        // Act
        this.sut.trainModelFromFile(inputDataFileName, outputDataFileName, timeInMinute, false, false, false);

        // Assert
        verify(this.sutProcessor).trainModelFromFile(Matchers.any(Vector.class), Matchers.anyString(), Matchers.anyString(), timeInMinuteCaptor.capture(), Matchers.anyBoolean(), Matchers.anyBoolean(), Matchers.anyBoolean());
        assertThat(timeInMinuteCaptor.getValue(), is(equalTo(1.0 * MILLISECONDS_IN_MINUTE)));
    }

    @Test
    public void test_trainModelFromFile_always_invokesMethodWithAutoStop() throws G2AccessException, MathException, IOException {
        // Arrange
        String inputDataFileName = "inputDataFileName";
        String outputDataFileName = "outputDataFileName";
        double timeInMinute = anyDouble();

        this.sut.setIsLoaded(true);
        boolean[] testCases = {true, false};

        ArgumentCaptor<Boolean> autoStopCaptor = ArgumentCaptor.forClass(Boolean.class);

        for (boolean testCase : testCases) {
            reset(this.sutProcessor);

            // Act
            this.sut.trainModelFromFile(inputDataFileName, outputDataFileName, timeInMinute, testCase, false, false);

            // Assert
            verify(this.sutProcessor).trainModelFromFile(Matchers.any(Vector.class), Matchers.anyString(), Matchers.anyString(), Matchers.any(Double.class), autoStopCaptor.capture(), Matchers.anyBoolean(), Matchers.anyBoolean());
            assertThat(autoStopCaptor.getValue(), is(equalTo(testCase)));
        }
    }

    @Test
    public void test_trainModelFromFile_always_invokesMethodWithNewTraining() throws G2AccessException, MathException, IOException {
        // Arrange
        String inputDataFileName = "inputDataFileName";
        String outputDataFileName = "outputDataFileName";
        double timeInMinute = anyDouble();

        this.sut.setIsLoaded(true);
        boolean[] testCases = {true, false};

        ArgumentCaptor<Boolean> newTrainingCaptor = ArgumentCaptor.forClass(Boolean.class);

        for (boolean testCase : testCases) {
            reset(this.sutProcessor);

            // Act
            this.sut.trainModelFromFile(inputDataFileName, outputDataFileName, timeInMinute, false, testCase, false);

            // Assert
            verify(this.sutProcessor).trainModelFromFile(Matchers.any(Vector.class), Matchers.anyString(), Matchers.anyString(), Matchers.any(Double.class), Matchers.anyBoolean(), newTrainingCaptor.capture(), Matchers.anyBoolean());
            assertThat(newTrainingCaptor.getValue(), is(equalTo(testCase)));
        }
    }

    @Test
    public void test_trainModelFromFile_always_invokesMethodWithDisplay() throws G2AccessException, MathException, IOException {
        // Arrange
        String inputDataFileName = "inputDataFileName";
        String outputDataFileName = "outputDataFileName";
        double timeInMinute = anyDouble();

        this.sut.setIsLoaded(true);
        boolean[] testCases = {true, false};

        ArgumentCaptor<Boolean> displayCaptor = ArgumentCaptor.forClass(Boolean.class);

        for (boolean testCase : testCases) {
            reset(this.sutProcessor);

            // Act
            this.sut.trainModelFromFile(inputDataFileName, outputDataFileName, timeInMinute, false, false, testCase);

            // Assert
            verify(this.sutProcessor).trainModelFromFile(Matchers.any(Vector.class), Matchers.anyString(), Matchers.anyString(), Matchers.any(Double.class), Matchers.anyBoolean(), Matchers.anyBoolean(), displayCaptor.capture());
            assertThat(displayCaptor.getValue(), is(equalTo(testCase)));
        }
    }

    @Test
    public void test_trainModelFromFile_IOException_informsG2Error() throws G2AccessException, MathException, IOException {
        // Arrange
        String inputDataFileName = "inputDataFileName";
        String outputDataFileName = "outputDataFileName";
        double timeInMinute = anyDouble();

        this.sut.setIsLoaded(true);
        IOException exception = new IOException("Failed to train model.");
        doThrow(exception).when(this.sutProcessor).trainModelFromFile(Matchers.any(Vector.class), Matchers.anyString(), Matchers.anyString(), Matchers.anyDouble(), Matchers.anyBoolean(), Matchers.anyBoolean(), Matchers.anyBoolean());

        // Act
        this.sut.trainModelFromFile(inputDataFileName, outputDataFileName, timeInMinute, false, false, false);

        // Assert
        verify(NolG2Gateway.g2Gateway).informG2ErrorOccur(this.sutG2Uuid, true, exception.getMessage());
    }

    @Test
    public void test_trainModelFromFile_MathException_informsG2Error() throws G2AccessException, MathException, IOException {
        // Arrange
        String inputDataFileName = "inputDataFileName";
        String outputDataFileName = "outputDataFileName";
        double timeInMinute = anyDouble();

        this.sut.setIsLoaded(true);
        MathException exception = new MathException("Failed to train model.");
        doThrow(exception).when(this.sutProcessor).trainModelFromFile(Matchers.any(Vector.class), Matchers.anyString(), Matchers.anyString(), Matchers.anyDouble(), Matchers.anyBoolean(), Matchers.anyBoolean(), Matchers.anyBoolean());

        // Act
        this.sut.trainModelFromFile(inputDataFileName, outputDataFileName, timeInMinute, false, false, false);

        // Assert
        verify(NolG2Gateway.g2Gateway).informG2ErrorOccur(this.sutG2Uuid, true, exception.getMessage());
    }

    @Test
    public void test_trainModelFromFileAndDs_debugEnabled_outputToConsole() {
        // Arrange
        Sequence dataSeriesFileNames = createFileNames();
        double timeInMinute = anyDouble();

        this.sut.setIsLoaded(true);
        this.sut.setDebugProcessor(true);

        // Act
        this.sut.trainModelFromFile(dataSeriesFileNames, timeInMinute, false, false, false);

        // Assert
        assertTrue(outContent.toString().contains("start re-training model"));
    }

    @Test
    public void test_trainModelFromFileAndDs_debugNotEnabled_doesNotOutputToConsole() {
        // Arrange
        Sequence dataSeriesFileNames = createFileNames();
        double timeInMinute = anyDouble();

        this.sut.setIsLoaded(true);
        this.sut.setDebugProcessor(false);

        // Act
        this.sut.trainModelFromFile(dataSeriesFileNames, timeInMinute, false, false, false);

        // Assert
        assertFalse(outContent.toString().contains("start re-training model"));
    }

    @Test
    public void test_trainModelFromFileAndDs_modelNotLoaded_informsG2Error() throws G2AccessException {
        // Arrange
        Sequence dataSeriesFileNames = createFileNames();
        double timeInMinute = anyDouble();

        // Act
        this.sut.trainModelFromFile(dataSeriesFileNames, timeInMinute, false, false, false);

        // Assert
        verify(NolG2Gateway.g2Gateway).informG2ErrorOccur(this.sutG2Uuid, true, "Can not train unloaded model");
    }

    @Test
    public void test_trainModelFromFileAndDs_always_invokesMethodWithTime() throws G2AccessException, MathException, IOException {
        // Arrange
        Sequence dataSeriesFileNames = createFileNames();
        double timeInMinute = anyDouble();

        this.sut.setIsLoaded(true);

        ArgumentCaptor<Double> timeInMinuteCaptor = ArgumentCaptor.forClass(Double.class);

        // Act
        this.sut.trainModelFromFile(dataSeriesFileNames, timeInMinute, false, false, false);

        // Assert
        verify(this.sutProcessor).trainModelFromFile(Matchers.any(Vector.class), Matchers.any(String[].class), timeInMinuteCaptor.capture(), Matchers.anyBoolean(), Matchers.anyBoolean(), Matchers.anyBoolean());
        assertThat(timeInMinuteCaptor.getValue(), is(equalTo(timeInMinute * MILLISECONDS_IN_MINUTE)));
    }

    @Test
    public void test_trainModelFromFileAndDs_always_invokesMethodWithInputFile() throws G2AccessException, MathException, IOException {
        // Arrange
        Sequence dataSeriesFileNames = createFileNames();
        double timeInMinute = anyDouble();

        this.sut.setIsLoaded(true);

        ArgumentCaptor<String[]> dataSeriesFileNamesCaptor = ArgumentCaptor.forClass(String[].class);

        // Act
        this.sut.trainModelFromFile(dataSeriesFileNames, timeInMinute, false, false, false);

        // Assert
        verify(this.sutProcessor).trainModelFromFile(Matchers.any(Vector.class), dataSeriesFileNamesCaptor.capture(), Matchers.anyDouble(), Matchers.anyBoolean(), Matchers.anyBoolean(), Matchers.anyBoolean());
        assertThat(dataSeriesFileNames.size(), is(greaterThan(0)));
        for(int i = 0; i < dataSeriesFileNames.size(); i++) {
            assertThat(dataSeriesFileNamesCaptor.getValue()[i], is(equalTo((String)dataSeriesFileNames.get(i))));
        }
    }

    @Test
    public void test_trainModelFromFileAndDs_timeIsNotSet_setsTimeAsOne() throws G2AccessException, MathException, IOException {
        // Arrange
        Sequence dataSeriesFileNames = createFileNames();

        this.sut.setIsLoaded(true);
        double timeInMinute = 0;

        ArgumentCaptor<Double> timeInMinuteCaptor = ArgumentCaptor.forClass(Double.class);

        // Act
        this.sut.trainModelFromFile(dataSeriesFileNames, timeInMinute, false, false, false);

        // Assert
        verify(this.sutProcessor).trainModelFromFile(Matchers.any(Vector.class), Matchers.any(String[].class), timeInMinuteCaptor.capture(), Matchers.anyBoolean(), Matchers.anyBoolean(), Matchers.anyBoolean());
        assertThat(timeInMinuteCaptor.getValue(), is(equalTo(1.0 * MILLISECONDS_IN_MINUTE)));
    }

    @Test
    public void test_trainModelFromFileAndDs_always_invokesMethodWithAutoStop() throws G2AccessException, MathException, IOException {
        // Arrange
        Sequence dataSeriesFileNames = createFileNames();
        double timeInMinute = anyDouble();

        this.sut.setIsLoaded(true);
        boolean[] testCases = {true, false};

        ArgumentCaptor<Boolean> autoStopCaptor = ArgumentCaptor.forClass(Boolean.class);

        for (boolean testCase : testCases) {
            reset(this.sutProcessor);

            // Act
            this.sut.trainModelFromFile(dataSeriesFileNames, timeInMinute, testCase, false, false);

            // Assert
            verify(this.sutProcessor).trainModelFromFile(Matchers.any(Vector.class), Matchers.any(String[].class), Matchers.any(Double.class), autoStopCaptor.capture(), Matchers.anyBoolean(), Matchers.anyBoolean());
            assertThat(autoStopCaptor.getValue(), is(equalTo(testCase)));
        }
    }

    @Test
    public void test_trainModelFromFileAndDs_always_invokesMethodWithNewTraining() throws G2AccessException, MathException, IOException {
        // Arrange
        Sequence dataSeriesFileNames = createFileNames();
        double timeInMinute = anyDouble();

        this.sut.setIsLoaded(true);
        boolean[] testCases = {true, false};

        ArgumentCaptor<Boolean> newTrainingCaptor = ArgumentCaptor.forClass(Boolean.class);

        for (boolean testCase : testCases) {
            reset(this.sutProcessor);

            // Act
            this.sut.trainModelFromFile(dataSeriesFileNames, timeInMinute, false, testCase, false);

            // Assert
            verify(this.sutProcessor).trainModelFromFile(Matchers.any(Vector.class), Matchers.any(String[].class), Matchers.any(Double.class), Matchers.anyBoolean(), newTrainingCaptor.capture(), Matchers.anyBoolean());
            assertThat(newTrainingCaptor.getValue(), is(equalTo(testCase)));
        }
    }

    @Test
    public void test_trainModelFromFileAndDs_always_invokesMethodWithDisplay() throws G2AccessException, MathException, IOException {
        // Arrange
        Sequence dataSeriesFileNames = createFileNames();
        double timeInMinute = anyDouble();

        this.sut.setIsLoaded(true);
        boolean[] testCases = {true, false};

        ArgumentCaptor<Boolean> displayCaptor = ArgumentCaptor.forClass(Boolean.class);

        for (boolean testCase : testCases) {
            reset(this.sutProcessor);

            // Act
            this.sut.trainModelFromFile(dataSeriesFileNames, timeInMinute, false, false, testCase);

            // Assert
            verify(this.sutProcessor).trainModelFromFile(Matchers.any(Vector.class), Matchers.any(String[].class), Matchers.any(Double.class), Matchers.anyBoolean(), Matchers.anyBoolean(), displayCaptor.capture());
            assertThat(displayCaptor.getValue(), is(equalTo(testCase)));
        }
    }

    @Test
    public void test_trainModelFromFile_exception_informsG2Error() throws G2AccessException, MathException, IOException {
        // Arrange
        Sequence dataSeriesFileNames = createFileNames();
        double timeInMinute = anyDouble();

        this.sut.setIsLoaded(true);
        MathException exception = new MathException("Failed to train model.");
        doThrow(exception).when(this.sutProcessor).trainModelFromFile(Matchers.any(Vector.class), Matchers.any(String[].class), Matchers.anyDouble(), Matchers.anyBoolean(), Matchers.anyBoolean(), Matchers.anyBoolean());

        // Act
        this.sut.trainModelFromFile(dataSeriesFileNames, timeInMinute, false, false, false);

        // Assert
        verify(NolG2Gateway.g2Gateway).informG2ErrorOccur(this.sutG2Uuid, true, exception.getMessage());
    }

    @Test
    public void test_getModelRateForG2_always_invokesGetVariance() throws MathException, NoSuchAttributeException {
        // Arrange
        Double value = anyDouble();
        when(this.sutProcessor.getModelRate()).thenReturn(value);

        // Act
        Structure retVal = this.sut.getModelRateForG2();

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(value)));
    }

    @Test
    public void test_getModelRateForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        MathException exception = new MathException("Failed to get variance value.");
        when(this.sutProcessor.getModelRate()).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getModelRateForG2();

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getTestRmseForG2_always_invokesGetVariance() throws MathException, NoSuchAttributeException {
        // Arrange
        double[] values = {anyDouble(), anyDouble(), anyDouble()};
        when(this.sutProcessor.getTestRmse()).thenReturn(values);

        // Act
        Structure retVal = this.sut.getTestRmseForG2();

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(values)));
    }

    @Test
    public void test_getTestRmseForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        MathException exception = new MathException("Failed to get variance value.");
        when(this.sutProcessor.getTestRmse()).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getTestRmseForG2();

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getTrainingRmseForG2_always_invokesGetVariance() throws MathException, NoSuchAttributeException {
        // Arrange
        double[] values = {anyDouble(), anyDouble(), anyDouble()};
        when(this.sutProcessor.getTrainingRmse()).thenReturn(values);

        // Act
        Structure retVal = this.sut.getTrainingRmseForG2();

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(values)));
    }

    @Test
    public void test_getTrainingRmseForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        MathException exception = new MathException("Failed to get variance value.");
        when(this.sutProcessor.getTrainingRmse()).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getTrainingRmseForG2();

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getTestCorrForG2_always_invokesGetVariance() throws MathException, NoSuchAttributeException {
        // Arrange
        double[] values = {anyDouble(), anyDouble(), anyDouble()};
        when(this.sutProcessor.getTestCorr()).thenReturn(values);

        // Act
        Structure retVal = this.sut.getTestCorrForG2();

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(values)));
    }

    @Test
    public void test_getTestCorrForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        MathException exception = new MathException("Failed to get variance value.");
        when(this.sutProcessor.getTestCorr()).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getTestCorrForG2();

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getTrainingCorrForG2_always_invokesGetVariance() throws MathException, NoSuchAttributeException {
        // Arrange
        double[] values = {anyDouble(), anyDouble(), anyDouble()};
        when(this.sutProcessor.getTrainingCorr()).thenReturn(values);

        // Act
        Structure retVal = this.sut.getTrainingCorrForG2();

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(values)));
    }

    @Test
    public void test_getTrainingCorrForG2_exception_setsError() throws MathException, NoSuchAttributeException {
        // Arrange
        MathException exception = new MathException("Failed to get variance value.");
        when(this.sutProcessor.getTrainingCorr()).thenThrow(exception);

        // Act
        Structure retVal = this.sut.getTrainingCorrForG2();

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_getInputUnit_modelNotLoaded_retEmptyString() {
        // Arrange
        int index = anyInteger();

        // Act & Assert
        assertThat(this.sut.getInputUnit(index), equalTo(""));
    }

    @Test
    public void test_getInputUnit_modelNotLoaded_informsG2Error() throws G2AccessException {
        // Arrange
        // No arrangements

        // Act
        this.sut.getInputUnit(anyInteger());

        // Assert
        verify(NolG2Gateway.g2Gateway).informG2ErrorOccur(this.sutG2Uuid, true, "Can not get parameters for unloaded model");
    }

    @Test
    public void test_getInputUnit_modelLoaded_retProcessorInputUnit() {
        // Arrange
        sut.setIsLoaded(true);
        int index = anyInteger();

        // Act
        String result = this.sut.getInputUnit(index);

        // Assert
        verify(this.sutProcessor).getInputUnit(index);
        assertThat(result, equalTo(this.sutProcessor.getInputUnit(index)));
    }

    @Test
    public void test_getOutputUnit_modelNotLoaded_retEmptyString() {
        // Arrange
        int index = anyInteger();

        // Act & Assert
        assertThat(this.sut.getOutputUnit(index), equalTo(""));
    }

    @Test
    public void test_getOutputUnit_modelNotLoaded_informsG2Error() throws G2AccessException {
        // Arrange
        // No arrangements

        // Act
        this.sut.getOutputUnit(anyInteger());

        // Assert
        verify(NolG2Gateway.g2Gateway).informG2ErrorOccur(this.sutG2Uuid, true, "Can not get parameters for unloaded model");
    }

    @Test
    public void test_getOutputUnit_modelLoaded_retProcessorOutputUnit() {
        // Arrange
        sut.setIsLoaded(true);
        int index = anyInteger();

        // Act
        String result = this.sut.getOutputUnit(index);

        // Assert
        verify(this.sutProcessor).getOutputUnit(index);
        assertThat(result, equalTo(this.sutProcessor.getOutputUnit(index)));
    }

    @Test
    public void test_setVariableValueAtTimeByNameForG2_always_invokesMethod() throws MathException, NoSuchAttributeException, ParseException {
        // Arrange
        String varName = "Variable Name 1";
        double value = anyDouble();
        String time = "11:00:00";

        // Act
        Structure retVal = this.sut.setVariableValueAtTimeByNameForG2(varName, value, time);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(true)));
        verify(this.sutProcessor).setVariableValueAtTimeByName(varName, value, time);
    }

    @Test
    public void test_setVariableValueAtTimeByNameForG2_exception_setsError() throws MathException, NoSuchAttributeException, ParseException {
        // Arrange
        String varName = "Variable Name 1";
        double value = anyDouble();
        String time = "11:00:00";
        MathException exception = new MathException("Failed to set time format.");
        doThrow(exception).when(this.sutProcessor).setVariableValueAtTimeByName(varName, value, time);

        // Act
        Structure retVal = this.sut.setVariableValueAtTimeByNameForG2(varName, value, time);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_setVariableValueAtTimeByTagForG2_always_invokesMethod() throws MathException, NoSuchAttributeException, ParseException {
        // Arrange
        String varTag = "Variable Tag 1";
        double value = anyDouble();
        String time = "11:00:00";

        // Act
        Structure retVal = this.sut.setVariableValueAtTimeByTagForG2(varTag, value, time);

        // Assert
        assertThat(retVal.getAttributeValue(RETVAL), is(equalTo(true)));
        verify(this.sutProcessor).setVariableValueAtTimeByTag(varTag, value, time);
    }

    @Test
    public void test_setVariableValueAtTimeByTagForG2_exception_setsError() throws MathException, NoSuchAttributeException, ParseException {
        // Arrange
        String varTag = "Variable Tag 1";
        double value = anyDouble();
        String time = "11:00:00";
        MathException exception = new MathException("Failed to set time format.");
        doThrow(exception).when(this.sutProcessor).setVariableValueAtTimeByTag(varTag, value, time);

        // Act
        Structure retVal = this.sut.setVariableValueAtTimeByTagForG2(varTag, value, time);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_loadFromProject_mainFrameNotSet_retFalse() {
        // Arrange
        String modelName = "Model Name 1";
        NolMainFrame.mainFrame = null;

        // Act
        boolean result = this.sut.loadFromProject(modelName);

        // Assert
        assertFalse(result);
        assertFalse(this.sut.isLoaded());
    }

    @Test
    public void test_loadFromProject_modelNotExist_retFalse() {
        // Arrange
        String modelName = "Model Name 1";

        when(NolMainFrame.mainFrame.getProject().getPredictiveModelIndexByName(modelName)).thenReturn(-1);

        // Act & Assert
        assertFalse(this.sut.loadFromProject(modelName));
    }

    @Test
    public void test_loadFromProject_modelAutoRecursive_autoRecursiveProcessor() {
        // Arrange
        String modelName = "Model Name 1";
        int index = NolMainFrame.mainFrame.getProject().getPredictiveModelIndexByName(modelName);
        when(NolMainFrame.mainFrame.getProject().getPredictiveModel(index).isAutoRecursiveModel()).thenReturn(true);

        // Act
        boolean result = this.sut.loadFromProject(modelName);

        // Assert
        assertTrue(result);
        assertThat(this.sut.getProcessor().getClass(), is(equalTo(OnlineAutoRecusiveProcessor.class)));
    }

    @Test
    public void test_loadFromProject_modelNotAutoRecursive_onlineProcessor() {
        // Arrange
        String modelName = "Model Name 1";
        int index = NolMainFrame.mainFrame.getProject().getPredictiveModelIndexByName(modelName);
        when(NolMainFrame.mainFrame.getProject().getPredictiveModel(index).isAutoRecursiveModel()).thenReturn(false);

        // Act
        boolean result = this.sut.loadFromProject(modelName);

        // Assert
        assertTrue(result);
        assertThat(this.sut.getProcessor().getClass(), is(equalTo(OnlineProcessor.class)));
    }

    @Test
    public void test_setUuidForG2Object_when_then() {
        // Arrange


        // Act


        // Assert

    }

    @Test
    public void test_trainingComplete_gatewayNotSet_doesNotThrowExcep() throws G2AccessException {
        // Arrange
        NolG2Gateway.g2Gateway = null;

        try {
            // Act
            this.sut.trainingComplete();
        } catch (Exception ex) {
            // Assert
            fail("Invoking trainingComplete should not throw exception when G2 Gateway is not set.");
        }
    }

    @Test
    public void test_trainingComplete_g2UuidNotSet_doesNotInformG2() throws G2AccessException {
        // Arrange
       this.sut.setUuidForG2Object("");

        // Act
        this.sut.trainingComplete();

        // Assert
        verify(NolG2Gateway.g2Gateway, never()).informG2TrainingComplete(Matchers.anyString(), Matchers.anyBoolean());
    }

    @Test
    public void test_trainingComplete_g2UuidIsSet_informsG2() throws G2AccessException {
        // Arrange
        // No arrangements

        // Act
        this.sut.trainingComplete();

        // Assert
        verify(NolG2Gateway.g2Gateway).informG2TrainingComplete(sutG2Uuid, true);
    }

    @Test
    public void test_trainingComplete_exception_informsG2Error() throws G2AccessException {
        // Arrange
        G2AccessException exception = new G2AccessException("Failed to inform training complete.");
        doThrow(exception).when(NolG2Gateway.g2Gateway).informG2TrainingComplete(this.sutG2Uuid, true);

        // Act
        this.sut.trainingComplete();

        // Assert
        verify(NolG2Gateway.g2Gateway).informG2ErrorOccur(this.sutG2Uuid, true, exception.getMessage());
    }

    @Test
    public void test_errorOccur_exception_doesNotThrowException() throws G2AccessException {
        // Arrange
        G2AccessException exception = new G2AccessException("Failed to inform G2 Error Occurred.");
        doThrow(exception).when(NolG2Gateway.g2Gateway).informG2ErrorOccur(this.sutG2Uuid, true, exception.getMessage());

        try {
            // Act
            this.sut.errorOccur(anyString());
        } catch (Exception ex) {
            // Assert
            fail("Should not throw exception.");
        }
    }

    @Test
    public void test_saveModel_withFileExtension_savesProcessor() throws IOException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, InstantiationException, IllegalAccessException {
        // Arrange
        this.sutProcessor = new OnlineProcessor();
        this.sut = new OnlineProcessorAPIG2Extended(this.sutProcessor);
        File file = createFile();
        String filename = file.getName();
        String directory = file.getAbsolutePath().replace(filename, "");

        String expectedName = filename.substring(0, filename.indexOf("."));

        // Act
        this.sut.saveModel(filename, directory);

        // Assert
        OnlineProcessor processor = readProcessor(file.getAbsolutePath());
        assertThat(processor.getName(), is(equalTo(expectedName)));
    }

    @Test
    public void test_saveModel_withoutFileExtension_savesProcessor() throws IOException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, InstantiationException, IllegalAccessException {
        // Arrange
        this.sutProcessor = new OnlineProcessor();
        this.sut = new OnlineProcessorAPIG2Extended(this.sutProcessor);
        File file = createFileWithoutExtension();
        String filename = file.getName();
        String directory = file.getAbsolutePath().replace(filename, "");

        // Act
        this.sut.saveModel(filename, directory);

        // Assert
        OnlineProcessor processor = readProcessor(file.getAbsolutePath() + ".mod");
        assertThat(processor.getName(), is(equalTo(filename)));
    }

    @Test
    public void test_saveModel_success_retTrue() throws IOException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, InstantiationException, IllegalAccessException {
        // Arrange
        this.sutProcessor = new OnlineProcessor();
        this.sut = new OnlineProcessorAPIG2Extended(this.sutProcessor);
        File file = createFileWithoutExtension();
        String filename = file.getName();
        String directory = file.getAbsolutePath().replace(filename, "");

        // Act & Assert
        assertTrue(this.sut.saveModel(filename, directory));
    }

    @Test
    public void test_saveModel_exception_retFalse() throws IOException, G2AccessException {
        // Arrange
        this.sutProcessor = new OnlineProcessor();
        this.sut = new OnlineProcessorAPIG2Extended(this.sutProcessor);
        File file = createFileWithoutExtension();
        this.sut.setUuidForG2Object(this.sutG2Uuid);

        // Act & Assert
        assertFalse(this.sut.saveModel(file.getAbsolutePath(), null));
        verify(NolG2Gateway.g2Gateway).informG2ErrorOccur(Matchers.anyString(), Matchers.anyBoolean(), Matchers.anyString());
    }

    @Test
    public void test_calculateSensitivity_modelNotLoaded_informsG2Error() throws G2AccessException {
        // Arrange
        Sequence input = new Sequence();
        Sequence signedSensitivity = new Sequence();
        Sequence absSensitivity = new Sequence();

        // Act
        this.sut.calculateSensitivity(input, signedSensitivity, absSensitivity);

        // Assert
        verify(NolG2Gateway.g2Gateway).informG2ErrorOccur(this.sutG2Uuid, true, "Can not run unloaded model");
    }

    @Test
    public void test_calculateSensitivity_debugFlagNotSet_messageNotShown() throws G2AccessException {
        // Arrange
        this.sut.setDebugProcessor(false);
        Sequence input = new Sequence();
        Sequence signedSensitivity = new Sequence();
        Sequence absSensitivity = new Sequence();
        this.setErrorFrame();

        // Act
        this.sut.calculateSensitivity(input, signedSensitivity, absSensitivity);

        // Assert
        verify(this.sutErrorFrame(), never()).setVisible(true);
    }

    @Test
    public void test_calculateSensitivity_debugFlagIsSet_messageShown() throws G2AccessException {
        // Arrange
        this.sut.setDebugProcessor(true);
        Sequence input = new Sequence();
        Sequence signedSensitivity = new Sequence();
        Sequence absSensitivity = new Sequence();
        this.setErrorFrame();

        // Act
        this.sut.calculateSensitivity(input, signedSensitivity, absSensitivity);

        // Assert
        verify(this.sutErrorTextArea()).append(String.format("start calculateSensitivity isloaded=%s\n", sut.isLoaded()));
        verify(this.sutErrorFrame()).setVisible(true);
    }

    @Test
    public void test_calculateSensitivity_inSeqEmpty_informsG2Error() throws G2AccessException {
        // Arrange
        this.sut.setIsLoaded(true);
        Sequence input = new Sequence();
        Sequence signedSensitivity = new Sequence();
        Sequence absSensitivity = new Sequence();

        // Act
        this.sut.calculateSensitivity(input, signedSensitivity, absSensitivity);

        // Assert
        verify(NolG2Gateway.g2Gateway).informG2ErrorOccur(this.sutG2Uuid, true, "There is not enough data for calculation.");
    }

    @Test
    public void test_calculateSensitivity_inSeqExist_retRetVal() throws G2AccessException, NoSuchAttributeException, MathException {
        // Arrange
        this.sut.setIsLoaded(true);
        Sequence input = createInputSequence();
        Sequence signedSensitivity = new Sequence();
        Sequence absSensitivity = new Sequence();
        Sequence expectedInput = createInputSequence();
        Sequence expectedSignedSensitivity = new Sequence();
        Sequence expectedAbsSensitivity = new Sequence();

        // Act
        Structure result = this.sut.calculateSensitivity(input, signedSensitivity, absSensitivity);

        // Assert
        Sequence expected = expectedSensitivity(expectedInput, expectedSignedSensitivity, expectedAbsSensitivity);
        Sequence actual = (Sequence) result.getAttributeValue(RETVAL);
        assertNotNull(actual);
        assertThat(actual.size(), equalTo(expected.size()));
        assertThat(signedSensitivity.size(), equalTo(expectedSignedSensitivity.size()));
        assertThat(absSensitivity.size(), equalTo(expectedAbsSensitivity.size()));
    }

    @Test
    public void test_calculateSensitivity_MathExcep_informsG2Error() throws G2AccessException, NoSuchAttributeException, MathException {
        // Arrange
        this.sut.setIsLoaded(true);
        Sequence input = createInputSequence();
        Sequence signedSensitivity = new Sequence();
        Sequence absSensitivity = new Sequence();
        MathException exception = new MathException("Failed to calculate sensitivity.");
        doThrow(exception).when(this.sutProcessor).calculateSensitivity(Matchers.any(Matrix.class), Matchers.any(Matrix.class), Matchers.any(Matrix.class));

        // Act
        this.sut.calculateSensitivity(input, signedSensitivity, absSensitivity);

        // Assert
        verify(NolG2Gateway.g2Gateway).informG2ErrorOccur(this.sutG2Uuid, true, exception.getMessage());
    }

    @Test
    public void test_calculateSensitivity_RuntimeExcep_informsG2Error() throws G2AccessException, NoSuchAttributeException, MathException {
        // Arrange
        this.sut.setIsLoaded(true);
        Sequence input = createInputSequence();
        Sequence signedSensitivity = new Sequence();
        Sequence absSensitivity = new Sequence();
        RuntimeException exception = new RuntimeException("Failed to calculate sensitivity.");
        doThrow(exception).when(this.sutProcessor).calculateSensitivity(Matchers.any(Matrix.class), Matchers.any(Matrix.class), Matchers.any(Matrix.class));

        // Act
        this.sut.calculateSensitivity(input, signedSensitivity, absSensitivity);

        // Assert
        verify(NolG2Gateway.g2Gateway).informG2ErrorOccur(this.sutG2Uuid, true, exception.getMessage());
    }

    @Test
    public void test_prepareTrainingDataFileForG2_modelNotLoaded_invokesError() throws MathException, NoSuchAttributeException, IOException, G2AccessException {
        // Arrange
        Sequence dataSeriesFileNames = new Sequence();
        dataSeriesFileNames.addElement("DataSeries File Name 1");
        dataSeriesFileNames.addElement("DataSeries File Name 2");
        int fileType = anyInteger();
        String inputDataFileName = "Input Data File Name";
        String outDataFileName = "Output Data File Name";

        // Act
        this.sut.prepareTrainingDataFile(dataSeriesFileNames, fileType, inputDataFileName, outDataFileName);

        // Assert
        verify(NolG2Gateway.g2Gateway).informG2ErrorOccur(this.sutG2Uuid, true, "Can not use unloaded model");
    }

    @Test
    public void test_prepareTrainingDataFileForG2_always_invokesProcessorMethod() throws MathException, NoSuchAttributeException, IOException {
        // Arrange
        this.sut.setIsLoaded(true);
        Sequence dataSeriesFileNames = new Sequence();
        dataSeriesFileNames.addElement("DataSeries File Name 1");
        dataSeriesFileNames.addElement("DataSeries File Name 2");
        int fileType = anyInteger();
        String inputDataFileName = "Input Data File Name";
        String outDataFileName = "Output Data File Name";

        // Act
        this.sut.prepareTrainingDataFile(dataSeriesFileNames, fileType, inputDataFileName, outDataFileName);

        // Assert
        verify(this.sutProcessor).prepareTrainingDataFile(Mockito.any(String[].class), Mockito.anyInt(), Mockito.anyString(), Mockito.anyString());
    }

    @Test
    public void test_prepareTrainingDataFileForG2_MathExcep_setsError() throws MathException, NoSuchAttributeException, IOException {
        // Arrange
        this.sut.setIsLoaded(true);
        Sequence dataSeriesFileNames = new Sequence();
        dataSeriesFileNames.addElement("DataSeries File Name 1");
        dataSeriesFileNames.addElement("DataSeries File Name 2");
        int fileType = anyInteger();
        String inputDataFileName = "Input Data File Name";
        String outDataFileName = "Output Data File Name";
        MathException exception = new MathException("Failed to set time format.");
        doThrow(exception).when(this.sutProcessor).prepareTrainingDataFile(Mockito.any(String[].class), Mockito.anyInt(), Mockito.anyString(), Mockito.anyString());

        // Act
        Structure retVal = this.sut.prepareTrainingDataFile(dataSeriesFileNames, fileType, inputDataFileName, outDataFileName);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    @Test
    public void test_prepareTrainingDataFileForG2_IOExcep_setsError() throws MathException, NoSuchAttributeException, IOException {
        // Arrange
        this.sut.setIsLoaded(true);
        Sequence dataSeriesFileNames = new Sequence();
        dataSeriesFileNames.addElement("DataSeries File Name 1");
        dataSeriesFileNames.addElement("DataSeries File Name 2");
        int fileType = anyInteger();
        String inputDataFileName = "Input Data File Name";
        String outDataFileName = "Output Data File Name";
        IOException exception = new IOException("Failed to set time format.");
        doThrow(exception).when(this.sutProcessor).prepareTrainingDataFile(Mockito.any(String[].class), Mockito.anyInt(), Mockito.anyString(), Mockito.anyString());

        // Act
        Structure retVal = this.sut.prepareTrainingDataFile(dataSeriesFileNames, fileType, inputDataFileName, outDataFileName);

        // Assert
        assertThat(retVal.getAttributeValue(ERROR), is(equalTo(exception.getMessage())));
        assertThat(retVal.getAttributeValue(BACKTRACE), is(equalTo(DebugUtil.getStackTrace(exception))));
    }

    private boolean anyBoolean() {
        return false;
    }

    private double anyDouble() {
        // Always returns non-zero random double
        return randomGenerator.nextDouble() + 0.1;
    }

    private int anyInteger() {
        return randomGenerator.nextInt(10) + 1;
    }

    private int anySamplesCount() {
        return randomGenerator.nextInt(10) + 1;
    }

    private String anyString() {
        return "Any String";
    }

    private Vector anyVector() {
        return new Vector();
    }

    private void assertThatMatricesAreEqual(Matrix actual, Matrix expected) {
        assertThat(actual.getRows(), is(equalTo(expected.getRows())));
        assertThat(actual.getCols(), is(equalTo(expected.getCols())));
        for (int row = 0; row < expected.getRows(); row++) {
            for (int col = 0; col < expected.getCols(); col++) {
                assertThat(actual.get(row, col), is(equalTo(expected.get(row, col))));
            }
        }
    }

    private void cleanUpStreams() {
        System.setErr(null);
        System.setOut(null);
    }

    private Frame createErrorFrame() {
        return mock(Frame.class);
    }

    private File createFile() throws IOException {
        File file = temporaryFolder.newFile();
        files.add(file);
        return file;
    }

    private File createFileWithoutExtension() throws IOException {
        File file = temporaryFolder.newFolder();
        files.add(file);

        file = temporaryFolder.newFile("FileNameWithoutExtension");
        files.add(file);
        return file;
    }

    private Sequence createFileNames() {
        Sequence filenames = new Sequence();

        filenames.add("File 1");
        filenames.add("File 2");
        filenames.add("File 3");

        return filenames;
    }

    private NolG2Gateway createG2Gateway() throws G2AccessException {
        NolG2Gateway gateway = mock(NolG2Gateway.class);

        Sequence dataSequence = new Sequence();
        when(gateway.getDataSequence()).thenReturn(dataSequence);

        return gateway;
    }

    private Sequence createInputSequence() {
        Sequence input = new Sequence();

        // Adding 10 input samples which are minimum required samples for training
        for (int i = 0; i < 10; i++) {
            FloatArrayStub floatArray = new FloatArrayStub();
            // Setting random values
            floatArray.setFloatArrayContents(new double[]{i * 3 + 1, i * 3 + 2, i * 3 + 3});
            input.addElement(floatArray);
        }

        return input;
    }

    private NolMainFrame createNolMainFrame() {
        NolMainFrame frame = mock(NolMainFrame.class);

        int index = 0;
        Project2 project = mock(Project2.class);
        when(project.getPredictiveModelIndexByName(Matchers.anyString())).thenReturn(index);

        NolModel2 model = mock(NolModel2.class);
        Preprocessor preprocessor = mock(Preprocessor.class);
        when(model.getPreprocessor()).thenReturn(preprocessor);
        when(model.getInputVarNames()).thenReturn(new Vector());
        when(model.getInputDelays()).thenReturn(new Vector());
        when(model.getOutputVarNames()).thenReturn(new Vector());
        when(model.getOutputDelays()).thenReturn(new Vector());

        when(project.getPredictiveModel(index)).thenReturn(model);

        when(frame.getProject()).thenReturn(project);

        return frame;
    }

    private OnlineAutoRecusiveProcessor createOnlineAutoRecursiveProcessor() throws MathException {
        EnsembleModel ensembleModel = new EnsembleModel(new ArchitectureParameters(anyInteger(), anyInteger(), anyInteger(), anyInteger()));

        Vector<String> inputs = new Vector<>();
        inputs.addElement("Input 1");
        inputs.addElement("Input 2");
        inputs.addElement("Input 3");

        Vector<String> outputs = new Vector<>();
        outputs.addElement("Output 1");
        outputs.addElement("Output 2");
        outputs.addElement("Output 3");

        Vector<String> inputTags = new Vector<>();
        Vector<String> inputUnits = new Vector<>();

        DataSeries inputDataSeries = new DataSeries(anySamplesCount(), inputs.size());
        for (int i = 0; i < inputs.size(); i++) {
            inputTags.addElement(inputs.get(i) + "Tag");
            inputUnits.addElement(inputs.get(i) + "Unit");
            inputDataSeries.setVariableParameters(i, inputs.get(i) + "Tag", inputs.get(i), inputs.get(i) + "Unit");
        }

        Vector<String> outputTags = new Vector<>();
        Vector<String> outputUnits = new Vector<>();

        DataSeries outputDataSeries = new DataSeries(anySamplesCount(), outputs.size());
        for (int i = 0; i < outputs.size(); i++) {
            outputTags.addElement(outputs.get(i) + "Tag");
            outputUnits.addElement(outputs.get(i) + "Unit");
            outputDataSeries.setVariableParameters(i, outputs.get(i) + "Tag", outputs.get(i), outputs.get(i) + "Unit");
        }

        Vector<DataSeries> dataSeriesList = new Vector<>();
        dataSeriesList.add(inputDataSeries);
        dataSeriesList.add(outputDataSeries);

        Preprocessor preprocessor = new Preprocessor(anyString(), anyString(), inputs, inputTags, anyVector(), anyVector(), anyBoolean());
        preprocessor.setDataSeries(dataSeriesList);

        Vector<long[]> inputDelays = new Vector<>();
        inputDelays.addElement(new long[]{1, 2, 3});
        inputDelays.addElement(new long[]{4, 5, 6});
        inputDelays.addElement(new long[]{7, 8, 9});

        Vector<long[]> outputDelays = new Vector<>();
        outputDelays.addElement(new long[]{11, 12, 13});
        outputDelays.addElement(new long[]{14, 15, 16});
        outputDelays.addElement(new long[]{17, 18, 19});

        NolModel2 model = new NolModel2(ensembleModel, anyString(), outputs, inputs, outputDelays, inputDelays, preprocessor);

        OnlineAutoRecusiveProcessor processor = new OnlineAutoRecusiveProcessor("OnlineAutoRecursiveProcessor Name", preprocessor, model);
        processor.setComment("OnlineAutoRecursiveProcessor Comment");

        return processor;
    }

    private File createOnlineProcessorFile(OnlineProcessor onlineProcessor) throws IOException {
        File file = temporaryFolder.newFile();
        FileOutputStream fos = null;
        GZIPOutputStream gzos = null;
        ObjectOutputStream out = null;

        try {
            fos = new FileOutputStream(file);
            gzos = new GZIPOutputStream(fos);
            out = new ObjectOutputStream(gzos);

            VersionManagerForOnlineProcessor versionManager = new VersionManagerForOnlineProcessor();
            versionManager.setProcessor(onlineProcessor);
            out.writeObject(versionManager);
        } catch (Exception e) {
            fail("Failed to create formulas file.");
        } finally {
            if (out != null) {
                out.close();
            } else if (gzos != null) {
                gzos.close();
            } else if (fos != null) {
                fos.close();
            }
        }

        files.addElement(file);
        return file;
    }

    private OnlineProcessor createOnlineProcessor() {
        OnlineProcessor processor = new OnlineProcessor();

        processor.setName("Online Processor 1 Name");
        processor.setComment("Online Processor 1 Comment");
        processor.outputData = new DataSeries();

        return processor;
    }

    private Sequence createOutputSequence() {
        Sequence output = new Sequence();

        // Adding 10 input samples which are minimum required samples for training
        for (int i = 0; i < 10; i++) {
            FloatArrayStub floatArray = new FloatArrayStub();
            // Setting random values
            floatArray.setFloatArrayContents(new double[]{i * 3 + 31, i * 3 + 32, i * 3 + 33});
            output.addElement(floatArray);
        }

        return output;
    }

    private OnlineProcessor createProcessor() throws MathException {
        OnlineProcessor onlineProcessor = mock(OnlineProcessor.class);

        when(onlineProcessor.getName()).thenReturn("SUT Processor Name");
        when(onlineProcessor.getComment()).thenReturn("SUT Processor Comment");

        String[] inputNames = {"Input Name 1", "Input Name 2", "Input Name 3"};
        when(onlineProcessor.getNumberOfInputs()).thenReturn(inputNames.length);
        when(onlineProcessor.getInputNames()).thenReturn(inputNames);
        when(onlineProcessor.getInputName(Matchers.anyInt())).thenReturn("SUT Processor Get Input Name Result");

        String[] inputTags = {"Input Tag 1", "Input Tag 2", "Input Tag 3"};
        when(onlineProcessor.getInputTags()).thenReturn(inputTags);
        when(onlineProcessor.getInputTag(Matchers.anyInt())).thenReturn("SUT Processor Get Input Tag Result");

        String[] inputUnits = {"Input Unit 1", "Input Unit 2", "Input Unit 3"};
        when(onlineProcessor.getInputUnits()).thenReturn(inputUnits);
        when(onlineProcessor.getInputUnit(Matchers.anyInt())).thenReturn("SUT Processor Get Input Unit Result");

        String[] outputNames = {"Output Name 1", "Output Name 2", "Output Name 3"};
        when(onlineProcessor.getNumberOfOutputs()).thenReturn(outputNames.length);
        when(onlineProcessor.getOutputNames()).thenReturn(outputNames);
        when(onlineProcessor.getOutputName(Matchers.anyInt())).thenReturn("SUT Processor Get Output Name Result");

        String[] outputTags = {"Output Tag 1", "Output Tag 2", "Output Tag 3"};
        when(onlineProcessor.getOutputTags()).thenReturn(outputTags);
        when(onlineProcessor.getOutputTag(Matchers.anyInt())).thenReturn("SUT Processor Get Output Tag Result");

        String[] outputUnits = {"Output Unit 1", "Output Unit 2", "Output Unit 3"};
        when(onlineProcessor.getOutputUnits()).thenReturn(outputUnits);
        when(onlineProcessor.getOutputUnit(Matchers.anyInt())).thenReturn("SUT Processor Get Output Unit Result");

        doAnswer(invocation -> {
            Matrix x = invocation.getArgumentAt(0, Matrix.class);
            Matrix signedSensitivityValues = invocation.getArgumentAt(1, Matrix.class);
            Matrix absSensitivityValues = invocation.getArgumentAt(2, Matrix.class);

            // Setting signed sensitivity values as first half x matrix rows
            signedSensitivityValues.redimension(x.getRows() / 2, x.getCols());
            for (int row = 0; row < x.getRows() / 2; row++) {
                for (int col = 0; col < x.getCols(); col++) {
                    signedSensitivityValues.set(row, col, x.get(row, col));
                }
            }

            // Setting absolute sensitivity values as first half x matrix rows
            absSensitivityValues.redimension(x.getRows() / 2, x.getCols());
            for (int row = 0; row < x.getRows() / 2; row++) {
                for (int col = 0; col < x.getCols(); col++) {
                    absSensitivityValues.set(row, col, x.get(row + x.getRows() / 2, col));
                }
            }

            return null;
        }).when(onlineProcessor).calculateSensitivity(Matchers.any(Matrix.class), Matchers.any(Matrix.class), Matchers.any(Matrix.class));

        return onlineProcessor;
    }

    private TextArea createTextArea() {
        return mock(TextArea.class);
    }

    private Matrix expectedMatrix(Sequence sequence) throws G2AccessException {
        Object[] contents = sequence.getContents();
        int sequenceSize = contents.length;
        double[][] array = new double[sequenceSize][];
        for (int i = 0; i < sequenceSize; i++) {
            array[i] = ((FloatArray) contents[i]).getFloatArrayContents();
        }

        return Matlib.createMatrix(array);
    }

    private Sequence expectedSensitivity(Sequence input, Sequence signedSensitivity, Sequence absSensitivity) throws MathException, G2AccessException {
        int inputsCount = input.size();

        Object[] inputRows = input.getContents();
        double[][] x = new double[inputsCount][];
        for (int i = 0; i < inputsCount; i++) {
            x[i] = ((FloatArray) inputRows[i]).getFloatArrayContents();
        }

        Matrix X = Matlib.createMatrix(x);
        Matrix signedSensitivityValues = Matlib.createMatrix();
        Matrix absSensitivityValues = Matlib.createMatrix();

        this.sutProcessor.calculateSensitivity(X, signedSensitivityValues, absSensitivityValues);
        Matlib.clear(X);
        signedSensitivity.removeAllElements();
        Matlib.transpose(signedSensitivityValues, signedSensitivityValues);
        double[][] data = Matlib.create2DArray(signedSensitivityValues);

        for (int i = 0; i < data.length; i++) {
            double[] newData = data[i];
            Sequence newSequence = NolG2Gateway.g2Gateway.getDataSequence();
            newSequence.removeAllElements();

            for (int j = 0; j < newData.length; j++) {
                newSequence.addElement(newData[j]);
            }

            signedSensitivity.addElement(newSequence);
        }

        Matlib.clear(signedSensitivityValues);
        absSensitivity.removeAllElements();
        Matlib.transpose(absSensitivityValues, absSensitivityValues);
        data = Matlib.create2DArray(absSensitivityValues);

        for (int i = 0; i < data.length; i++) {
            double[] newData = data[i];
            Sequence newSequence = NolG2Gateway.g2Gateway.getDataSequence();
            newSequence.removeAllElements();
            for (int j = 0; j < newData.length; j++) {
                newSequence.addElement(newData[j]);
            }
            
            absSensitivity.addElement(newSequence);
        }

        Matlib.clear(absSensitivityValues);

        Sequence result = NolG2Gateway.g2Gateway.getDataSequence();
        result.addElement(signedSensitivity);
        result.addElement(absSensitivity);

        return result;
    }

    private OnlineAutoRecusiveProcessor loadModel() throws MathException, IOException {
        OnlineAutoRecusiveProcessor onlinePreprocessor = createOnlineAutoRecursiveProcessor();
        File file = createOnlineProcessorFile(onlinePreprocessor);
        this.sut.loadModel(file.getAbsolutePath());

        return onlinePreprocessor;
    }

    private OnlineProcessor readProcessor(String path) throws IOException, ClassNotFoundException {
        FileInputStream fis = null;
        GZIPInputStream gzis = null;
        ObjectInputStream ois = null;
        OnlineProcessor processor;

        try {
            fis = new FileInputStream(path);
            gzis = new GZIPInputStream(fis);
            ois = new ObjectInputStream(gzis);

            VersionManagerForOnlineProcessor versionManager = (VersionManagerForOnlineProcessor) ois.readObject();
            processor = versionManager.getProcessor();
        } finally {
            if (ois != null) {
                ois.close();
            } else if (gzis != null) {
                gzis.close();
            } else if (fis != null) {
                fis.close();
            }
        }

        return processor;
    }

    private void setErrorFrame() {
        Whitebox.setInternalState(OnlineProcessorAPIG2.class, "errorFrame", createErrorFrame());
        Whitebox.setInternalState(OnlineProcessorAPIG2.class, "errorTA", createTextArea());
    }

    private void setupStreams() {
        System.setOut(new PrintStream(outContent));
        System.setErr(new PrintStream(errorContent));
    }

    private Frame sutErrorFrame() {
        return Whitebox.getInternalState(OnlineProcessorAPIG2.class, "errorFrame");
    }

    private TextArea sutErrorTextArea() {
        return Whitebox.getInternalState(OnlineProcessorAPIG2.class, "errorTA");
    }

    public class FloatArrayStub implements FloatArray {
        double[] floatArrayContents;

        @Override
        public int getArrayLength() throws G2AccessException {
            return 0;
        }

        @Override
        public Object getG2ArrayContents() throws G2AccessException {
            return null;
        }

        @Override
        public void setG2ArrayContents(Object o) throws G2AccessException {

        }

        @Override
        public Symbol getElementType() throws G2AccessException {
            return null;
        }

        @Override
        public Object getInitialValues() throws G2AccessException {
            return null;
        }

        @Override
        public void setInitialValues(Object o) throws G2AccessException {

        }

        @Override
        public boolean getArrayIsPermanent() throws G2AccessException {
            return false;
        }

        @Override
        public void setArrayIsPermanent(boolean b) throws G2AccessException {

        }

        @Override
        public Sequence getG2ArraySequence() throws G2AccessException {
            return null;
        }

        @Override
        public void setG2ArraySequence(Sequence sequence) throws G2AccessException {

        }

        @Override
        public double[] getFloatArrayContents() throws G2AccessException {
            return floatArrayContents;
        }

        @Override
        public KbWorkspace getSubworkspace() throws G2AccessException {
            return null;
        }

        @Override
        public void setSubworkspace(KbWorkspace kbWorkspace) throws G2AccessException {

        }

        @Override
        public Sequence getAttributeDisplayItems() throws G2AccessException {
            return null;
        }

        @Override
        public Object getNameBoxItem() throws G2AccessException {
            return null;
        }

        @Override
        public Structure getIconVariables() throws G2AccessException {
            return null;
        }

        @Override
        public void setIconVariables(Structure structure) throws G2AccessException {

        }

        @Override
        public Symbol getIconColor() throws G2AccessException {
            return null;
        }

        @Override
        public void setIconColor(Symbol symbol) throws G2AccessException {

        }

        @Override
        public Symbol getIconReflection() throws G2AccessException {
            return null;
        }

        @Override
        public void setIconReflection(Symbol symbol) throws G2AccessException {

        }

        @Override
        public int getIconHeading() throws G2AccessException {
            return 0;
        }

        @Override
        public void setIconHeading(int i) throws G2AccessException {

        }

        @Override
        public Structure getItemColorPattern() throws G2AccessException {
            return null;
        }

        @Override
        public void setItemColorPattern(Structure structure) throws G2AccessException {

        }

        @Override
        public Structure getSizeInWorkspace() throws G2AccessException {
            return null;
        }

        @Override
        public void setSizeInWorkspace(Structure structure) throws G2AccessException {

        }

        @Override
        public Sequence getCurrentAttributeDisplays() throws G2AccessException {
            return null;
        }

        @Override
        public void setCurrentAttributeDisplays(Sequence sequence) throws G2AccessException {

        }

        @Override
        public Structure getNameBox() throws G2AccessException {
            return null;
        }

        @Override
        public void setNameBox(Structure structure) throws G2AccessException {

        }

        @Override
        public Symbol getStripeColor() throws G2AccessException {
            return null;
        }

        @Override
        public void setStripeColor(Symbol symbol) throws G2AccessException {

        }

        @Override
        public Symbol getBorderColor() throws G2AccessException {
            return null;
        }

        @Override
        public void setBorderColor(Symbol symbol) throws G2AccessException {

        }

        @Override
        public Symbol getTextColor() throws G2AccessException {
            return null;
        }

        @Override
        public void setTextColor(Symbol symbol) throws G2AccessException {

        }

        @Override
        public Symbol getForegroundColor() throws G2AccessException {
            return null;
        }

        @Override
        public void setForegroundColor(Symbol symbol) throws G2AccessException {

        }

        @Override
        public Symbol getBackgroundColor() throws G2AccessException {
            return null;
        }

        @Override
        public void setBackgroundColor(Symbol symbol) throws G2AccessException {

        }

        @Override
        public Structure getIconDescriptionForClass() throws G2AccessException {
            return null;
        }

        @Override
        public Symbol reflectVertically() throws G2AccessException {
            return null;
        }

        @Override
        public Symbol reflectHorizontally() throws G2AccessException {
            return null;
        }

        @Override
        public Sequence getItemConfiguration() throws G2AccessException {
            return null;
        }

        @Override
        public void setItemConfiguration(Sequence sequence) throws G2AccessException {

        }

        @Override
        public Object getNames() throws G2AccessException {
            return null;
        }

        @Override
        public void setNames(Object o) throws G2AccessException {

        }

        @Override
        public int getLayerPosition() throws G2AccessException {
            return 0;
        }

        @Override
        public Block getFollowingItemInWorkspaceLayering() throws G2AccessException {
            return null;
        }

        @Override
        public void setFollowingItemInWorkspaceLayering(Block block) throws G2AccessException {

        }

        @Override
        public Structure getPositionInWorkspace() throws G2AccessException {
            return null;
        }

        @Override
        public void setPositionInWorkspace(Structure structure) throws G2AccessException {

        }

        @Override
        public Sequence getRelationships() throws G2AccessException {
            return null;
        }

        @Override
        public void setRelationships(Sequence sequence) throws G2AccessException {

        }

        @Override
        public Sequence getItemNotes() throws G2AccessException {
            return null;
        }

        @Override
        public Symbol getContainingModule() throws G2AccessException {
            return null;
        }

        @Override
        public boolean getItemActive() throws G2AccessException {
            return false;
        }

        @Override
        public Symbol getItemStatus() throws G2AccessException {
            return null;
        }

        @Override
        public boolean getInstantiateForClass() throws G2AccessException {
            return false;
        }

        @Override
        public boolean getIncludeInMenusForClass() throws G2AccessException {
            return false;
        }

        @Override
        public Object getSystemMenuChoicesForClass() throws G2AccessException {
            return null;
        }

        @Override
        public Rectangle getBounds() throws G2AccessException {
            return null;
        }

        @Override
        public void setBounds(int i, int i1, int i2, int i3) throws G2AccessException {

        }

        @Override
        public Sequence getContainmentHierarchy() throws G2AccessException {
            return null;
        }

        @Override
        public Sequence getCurrentUserMenuChoices(Symbol symbol) throws G2AccessException {
            return null;
        }

        @Override
        public boolean getTransient() throws G2AccessException {
            return false;
        }

        @Override
        public boolean getManuallyDisabled() throws G2AccessException {
            return false;
        }

        @Override
        public void setManuallyDisabled(boolean b) throws G2AccessException {

        }

        @Override
        public boolean getPermanent() throws G2AccessException {
            return false;
        }

        @Override
        public boolean getDoNotStripTextMark() throws G2AccessException {
            return false;
        }

        @Override
        public void setDoNotStripTextMark(boolean b) throws G2AccessException {

        }

        @Override
        public boolean getStripTextMark() throws G2AccessException {
            return false;
        }

        @Override
        public void setStripTextMark(boolean b) throws G2AccessException {

        }

        @Override
        public Symbol getRepresentationType() throws G2AccessException {
            return null;
        }

        @Override
        public String getTableHeader() throws G2AccessException {
            return null;
        }

        @Override
        public int getItemWidth() throws G2AccessException {
            return 0;
        }

        @Override
        public int getItemHeight() throws G2AccessException {
            return 0;
        }

        @Override
        public int getItemYPosition() throws G2AccessException {
            return 0;
        }

        @Override
        public int getItemXPosition() throws G2AccessException {
            return 0;
        }

        @Override
        public void addItemListener(ItemListener itemListener) throws G2AccessException {

        }

        @Override
        public void removeItemListener(ItemListener itemListener) throws G2AccessException {

        }

        @Override
        public void removeItemListenerForThreeTiers(ItemListener itemListener, Sequence sequence) throws G2AccessException {

        }

        @Override
        public Sequence addItemListenerRetrievingStateMultiple(ItemListener itemListener, Sequence sequence) throws G2AccessException {
            return null;
        }

        @Override
        public void removeItemListener(ItemListener itemListener, Symbol[] symbols) throws G2AccessException {

        }

        @Override
        public void addItemListener(ItemListener itemListener, Symbol[] symbols) throws G2AccessException {

        }

        @Override
        public void restoreNormalSize() throws G2AccessException {

        }

        @Override
        public boolean transferOff() throws G2AccessException {
            return false;
        }

        @Override
        public boolean transferToItem(Item item, Symbol symbol, Symbol symbol1) throws G2AccessException {
            return false;
        }

        @Override
        public boolean transferTo(Item item, Symbol symbol, Symbol symbol1) throws G2AccessException {
            return false;
        }

        @Override
        public boolean transferToWorkspace(KbWorkspace kbWorkspace, int i, int i1) throws G2AccessException {
            return false;
        }

        @Override
        public boolean transferTo(KbWorkspace kbWorkspace, int i, int i1) throws G2AccessException {
            return false;
        }

        @Override
        public Sequence retrieveCurrentUserMenuChoices() throws G2AccessException {
            return null;
        }

        @Override
        public boolean isProprietaryThroughContainment() throws G2AccessException {
            return false;
        }

        @Override
        public boolean moveByForVB(int i, int i1, int i2) throws G2AccessException {
            return false;
        }

        @Override
        public boolean moveBy(int i, int i1, boolean b) throws G2AccessException {
            return false;
        }

        @Override
        public boolean moveForVB(int i, int i1, int i2) throws G2AccessException {
            return false;
        }

        @Override
        public boolean move(int i, int i1, boolean b) throws G2AccessException {
            return false;
        }

        @Override
        public Item g2Clone() throws G2AccessException {
            return null;
        }

        @Override
        public void dropToBottom() throws G2AccessException {

        }

        @Override
        public void liftToTop() throws G2AccessException {

        }

        @Override
        public void makeTransient() throws G2AccessException {

        }

        @Override
        public void makePermanent() throws G2AccessException {

        }

        @Override
        public boolean isEnabled() throws G2AccessException {
            return false;
        }

        @Override
        public void disable() throws G2AccessException {

        }

        @Override
        public void enable() throws G2AccessException {

        }

        @Override
        public void deleteForVB(int i, int i1) throws G2AccessException {

        }

        @Override
        public void delete(boolean b, boolean b1) throws G2AccessException {

        }

        @Override
        public String getUuid() throws G2AccessException {
            return null;
        }

        @Override
        public void setUuid(String s) throws G2AccessException {

        }

        @Override
        public Symbol getG2ClassName() throws G2AccessException {
            return null;
        }

        @Override
        public Symbol getFoundationClass() throws G2AccessException {
            return null;
        }

        @Override
        public Object getPropertyValue(Symbol symbol) throws G2AccessException, NoSuchAttributeException {
            return null;
        }

        @Override
        public void setPropertyValue(Symbol symbol, Object o) throws G2AccessException {

        }

        @Override
        public Sequence getVisibleAttributes(Symbol symbol) throws G2AccessException {
            return null;
        }

        @Override
        public Structure getAttributeValues(Sequence sequence) throws G2AccessException {
            return null;
        }

        @Override
        public Sequence getAttributeDescriptions() throws G2AccessException {
            return null;
        }

        @Override
        public Sequence getAttributeDescriptions(Sequence sequence) throws G2AccessException {
            return null;
        }

        @Override
        public void processItemEvent(ItemEvent itemEvent) {

        }

        @Override
        public boolean isLocallyCached() {
            return false;
        }

        @Override
        public void setLocallyCached(boolean b) {

        }

        @Override
        public Structure getDialog(Symbol symbol, Structure structure) throws G2AccessException, MalformedURLException {
            return null;
        }

        @Override
        public Object getCachedAttributeValue(Symbol symbol, Object o) {
            return null;
        }

        @Override
        public boolean isItemLocal() {
            return false;
        }

        @Override
        public boolean isInstanceOfG2Class(Symbol symbol) {
            return false;
        }

        @Override
        public G2Definition getDefinition() throws G2AccessException {
            return null;
        }

        @Override
        public void startMethod(Symbol symbol, Object[] objects) throws G2AccessException {

        }

        @Override
        public Object callMethod(Symbol symbol, Object[] objects, int i) throws G2AccessException {
            return null;
        }

        @Override
        public Sequence getItemConfigurationSnapshot() throws G2AccessException {
            return null;
        }

        @Override
        public Symbol getConnectionStyleSnapshot() {
            return null;
        }

        @Override
        public Vector getCompleteConfigurationSnapshot() throws G2AccessException {
            return null;
        }

        @Override
        public boolean isValid() {
            return false;
        }

        @Override
        public void setAttributeWritesAreCached(boolean b) {

        }

        @Override
        public boolean isAttributeWritesCached() {
            return false;
        }

        @Override
        public void flushAttributeWriteCache() throws G2AccessException {

        }

        private void setFloatArrayContents(double[] contents) {
            floatArrayContents = contents;
        }
    }

    // Extending OnlineProcessorAPIG2 class to test training complete method.
    public class OnlineProcessorAPIG2Extended extends OnlineProcessorAPIG2 {
        OnlineProcessorAPIG2Extended() {
            super();
        }

        OnlineProcessorAPIG2Extended(OnlineProcessor processor) {
            super(processor);
        }

        public void trainingComplete() {
            super.trainingComplete();
        }
    }
}