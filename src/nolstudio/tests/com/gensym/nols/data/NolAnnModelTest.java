package com.gensym.nols.data;

import com.gensym.math.MathException;
import com.gensym.math.datafit.ClassicBpn;
import com.gensym.math.matrix.Matrix;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.TemporaryFolder;
import org.powermock.api.mockito.PowerMockito;

import java.io.BufferedWriter;
import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.Collections;
import java.util.Random;
import java.util.Vector;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.empty;
import static org.hamcrest.core.Is.is;
import static org.hamcrest.core.IsEqual.equalTo;
import static org.hamcrest.core.IsNot.not;
import static org.junit.Assert.assertTrue;
import static org.mockito.Matchers.any;
import static org.mockito.Mockito.verify;
import static org.powermock.api.mockito.PowerMockito.mock;
import static org.powermock.api.mockito.PowerMockito.when;

public class NolAnnModelTest {
    private static final String UNSCALED_WEIGHTS_CONTENT = "Unscaled Weights Content";
    private static final String WEIGHTS_CONTENT = "Weights Content";
    private static final String XML_FILE_CONTENT = "XML File Content";
    private static final String NEW_LINE = "\r\n";
    private static final Random randomGenerator = new Random();
    private static final int writeXmlFileResponse = 10;

    @Rule
    public TemporaryFolder temporaryFolder = new TemporaryFolder();

    private ClassicBpn sutClassicBpn;
    private Vector<File> temporaryFiles = new Vector<>();
    private NolAnnModel sut;

    private static String readFileContents(String filepath)
            throws IOException {
        byte[] encoded = Files.readAllBytes(Paths.get(filepath));
        return new String(encoded);
    }

    @Before
    public void setup() throws IOException, MathException {
        sutClassicBpn = createClassicBpn();
        String name = "NolBpnModel Name";
        Vector<String> outputs = createVariableNames("output");
        Vector<String> inputs = createVariableNames("input");
        Vector<long[]> outputDelays = createDelays(outputs.size());
        Vector<long[]> inputDelays = createDelays(inputs.size());
        Preprocessor preprocessor = createPreprocessor();
        sut = new NolAnnModel(sutClassicBpn, name, outputs, outputDelays, inputs, inputDelays, preprocessor);
    }

    @Test
    public void test_setNormalStd_always_setsNormalStandard() {
        // Arrange
        double[] values = new double[]{randomGenerator.nextDouble(), randomGenerator.nextDouble(), randomGenerator.nextDouble()};

        // Act
        sut.setNormalStd(values);

        // Assert
        assertThat(Arrays.asList(values), is(not(empty())));
        for (int i = 0; i < values.length; i++) {
            assertThat(sut.getNormalStd()[i], is(equalTo(values[i])));
        }
    }

    @Test
    public void test_setRunMode_always_setsRunMode() {
        // Arrange
        int value = randomGenerator.nextInt();

        // Act
        sut.setRunMode(value);

        // Assert
        assertThat(sut.getRunMode(), is(equalTo(value)));
    }

    @Test
    public void test_writeANNToFile_runModeIsZero_writesAnnModelToFileWithCorrectRunMode() throws IOException {
        // Arrange
        sut.setRunMode(0);
        File file = createFile();

        // Act
        sut.writeANNToFile(file.getAbsolutePath());

        // Assert
        String content = readFileContents(file.getAbsolutePath());
        assertThat(content, is(equalTo(expectedAnnModelContent())));
    }

    @Test
    public void test_writeANNToFile_runModeIsNotZero_writesAnnModelToFileWithCorrectRunMode() throws IOException {
        // Arrange
        sut.setRunMode(1);
        File file = createFile();

        // Act
        sut.writeANNToFile(file.getAbsolutePath());

        // Assert
        String content = readFileContents(file.getAbsolutePath());
        assertThat(content, is(equalTo(expectedAnnModelContent())));
    }

    @Test
    public void test_getParametersVector_always_returnsBaseParametersVector() throws MathException {
        // Arrange
        // No arrangements

        // Act
        Vector parameters = sut.getParametersVector();

        // Assert
        Vector baseParameters = sutClassicBpn.getParametersVector();
        assertThat(Collections.singletonList(baseParameters), is(not(empty())));
        for (Object baseParameter : baseParameters) {
            assertTrue(parameters.contains(baseParameter));
        }
    }

    @Test
    public void test_getParametersVector_always_returnsNormalStandard() throws MathException {
        // Arrange
        double[] newParameters = new double[]{randomGenerator.nextDouble(), randomGenerator.nextDouble(), randomGenerator.nextDouble()};
        sut.setNormalStd(newParameters);

        // Act
        Vector parameters = sut.getParametersVector();

        // Assert
        assertTrue(parameters.contains(newParameters));
    }

    @Test
    public void test_getParametersVector_always_returnsRunMode() throws MathException {
        // Arrange
        int runMode = randomGenerator.nextInt();
        sut.setRunMode(runMode);

        // Act
        Vector parameters = sut.getParametersVector();

        // Assert
        assertThat(parameters.lastElement(), is(equalTo((double) runMode)));
    }

    @Test
    public void test_setParametersVector_always_invokesClassicBpnSetParametersVector() throws MathException {
        // Arrange
        Vector<Object> parameters = new Vector<>();
        parameters.add("New Parameter 1");
        parameters.add("New Parameter 2");
        parameters.add("New Parameter 3");
        double[] normalStd = new double[]{randomGenerator.nextDouble(), randomGenerator.nextDouble(), randomGenerator.nextDouble()};
        parameters.add(normalStd);
        int runMode = randomGenerator.nextInt();
        parameters.add(runMode);

        // Act
        sut.setParametersVector(parameters);

        // Assert
        assertThat(sut.getNormalStd(), is(equalTo(normalStd)));
        assertThat(sut.getRunMode(), is(equalTo(runMode)));
        verify(sutClassicBpn).setParametersVector(parameters);
    }

    // -- Helper Methods --

    private ClassicBpn createClassicBpn() throws IOException, MathException {
        ClassicBpn classicBpn = mock(ClassicBpn.class);

        PowerMockito.when(classicBpn.getDescription()).thenReturn("ClassicBpn Description");

        Vector<String> parameters = new Vector<>();
        parameters.add("Parameter 1");
        parameters.add("Parameter 2");
        parameters.add("Parameter 3");
        PowerMockito.when(classicBpn.getParametersVector()).thenReturn(parameters);

        PowerMockito.doAnswer(invocation -> {
            BufferedWriter target = invocation.getArgumentAt(0, BufferedWriter.class);
            Matrix x = invocation.getArgumentAt(1, Matrix.class);
            Matrix y = invocation.getArgumentAt(2, Matrix.class);

            String content = getMatrixContentString(x, y);
            target.write(content, 0, content.length());
            return null;
        }).when(classicBpn).writeData(any(BufferedWriter.class), any(Matrix.class), any(Matrix.class));

        PowerMockito.doAnswer(invocation -> {
            BufferedWriter target = invocation.getArgumentAt(0, BufferedWriter.class);
            target.write(UNSCALED_WEIGHTS_CONTENT);
            return null;
        }).when(classicBpn).writeUnscaledWeights(any(BufferedWriter.class));

        PowerMockito.doAnswer(invocation -> {
            BufferedWriter target = invocation.getArgumentAt(0, BufferedWriter.class);
            target.write(WEIGHTS_CONTENT);
            return null;
        }).when(classicBpn).writeWeights(any(BufferedWriter.class));

        PowerMockito.when(classicBpn.writeXMLFile(any(BufferedWriter.class), any(int.class))).then(invocation -> {
            BufferedWriter target = invocation.getArgumentAt(0, BufferedWriter.class);
            int indentNumber = invocation.getArgumentAt(1, int.class);

            if (target != null) {
                target.write(indentNumber + XML_FILE_CONTENT);
            }

            return writeXmlFileResponse;
        });

        when(classicBpn.getRMSE()).thenReturn(randomGenerator.nextDouble());

        return classicBpn;
    }

    private Vector<long[]> createDelays(int variablesCount) {
        Vector<long[]> delays = new Vector<>();
        for (int i = 0; i < variablesCount; i++) {
            int variableDelaysCount = 3;
            long[] delay = new long[variableDelaysCount];
            for (int j = 0; j < delay.length; j++) {
                delay[j] = randomGenerator.nextLong();
            }

            delays.add(delay);
        }

        return delays;
    }

    private File createFile() throws IOException {
        temporaryFiles.addElement(temporaryFolder.newFile());
        return temporaryFiles.lastElement();
    }

    private Preprocessor createPreprocessor() {
        return mock(Preprocessor.class);
    }

    private Vector<String> createVariableNames(String prefix) {
        int variableSamplesCount = 3;
        Vector<String> variableNames = new Vector<>();
        for (int i = 0; i < variableSamplesCount; i++) {
            variableNames.add(prefix + i);
        }

        return variableNames;
    }

    private String expectedAnnModelContent() {
        StringBuilder builder = new StringBuilder();

        builder.append(WEIGHTS_CONTENT);
        builder.append(sut.getNormalStd()[0]);
        for (int i = 1; i < sut.getNormalStd().length; i++) {
            builder.append(", ").append(sut.getNormalStd()[i]);
        }

        builder.append("; Normal noise stdev");
        builder.append(NEW_LINE);

        if (sut.getRunMode() == 0) {
            builder.append("FILTER-ONLY ; Run mode");
        } else {
            builder.append("CORRECT-GROSS-ERRORS ; Run mode");
        }

        builder.append(NEW_LINE);

        return builder.toString();
    }

    private String getMatrixContentString(Matrix x, Matrix y) {
        String content = "Matrix X:";
        for (int r = 0; r < x.getRows(); r++) {
            for (int c = 0; c < x.getCols(); c++) {
                content += r + "," + c + "=" + x.get(r, c);
            }
        }

        content += "Matrix Y:";
        for (int r = 0; r < y.getRows(); r++) {
            for (int c = 0; c < y.getCols(); c++) {
                content += r + "," + c + "=" + y.get(r, c);
            }
        }
        return content;
    }
}
