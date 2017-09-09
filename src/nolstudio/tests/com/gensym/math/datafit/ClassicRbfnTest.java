package com.gensym.math.datafit;

import com.gensym.math.MathException;
import com.gensym.math.Utilities;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;
import org.junit.After;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.TemporaryFolder;
import org.junit.runner.RunWith;
import org.mockito.Matchers;
import org.powermock.core.classloader.annotations.PrepareForTest;
import org.powermock.modules.junit4.PowerMockRunner;

import java.io.*;
import java.util.Random;
import java.util.Vector;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.greaterThan;
import static org.hamcrest.core.IsEqual.equalTo;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.fail;
import static org.mockito.Mockito.times;
import static org.powermock.api.mockito.PowerMockito.*;

@RunWith(PowerMockRunner.class)
@PrepareForTest({Matlib.class})
public class ClassicRbfnTest {
    private static final Random RandomGenerator = new Random();
    private static final int nlayers = 3;

    @Rule
    public TemporaryFolder temporaryFolder = new TemporaryFolder();

    private ClassicRbfnExtended sut;
    private FileData fileData;
    private int[] sutNodes;
    private Vector<File> files;

    @Before
    public void before() {
        this.files = new Vector<>();
        this.sutNodes = createNodes();
        this.sut = new ClassicRbfnExtended(sutNodes, anyDouble(), anyInteger());
    }

    @After
    public void after() {
        for (File file : this.files) {
            file.delete();
        }
    }

    @Test
    public void test_getNin_always_retFirstNode() {
        // Arrange
        // No arrangements

        // Act & Assert
        assertThat(this.sut.getNin(), equalTo(this.sutNodes[0]));
    }

    @Test
    public void test_getNout_always_retLastNode() {
        // Arrange
        // No arrangements

        // Act & Assert
        assertThat(this.sut.getNout(), equalTo(this.sutNodes[this.sutNodes.length - 1]));
    }

    @Test
    public void test_setNout_always_setsNout() {
        // Arrange
        int value = anyInteger();

        // Act
        this.sut.setNout(value);

        // Assert
        assertThat(this.sut.getNout(), equalTo(value));
    }

    @Test
    public void test_setBias_always_setsBias() {
        // Arrange
        int value = anyInteger();

        // Act
        this.sut.setBias(value);

        // Assert
        assertThat(this.sut.bias, equalTo(value));
    }

    @Test
    public void test_setNormalizeData_always_setsNormalizedDataFlag() {
        // Arrange
        boolean[] testCases = new boolean[]{true, false};

        for (boolean testCase : testCases) {
            // Act
            this.sut.setNormalizeData(testCase);

            // Assert
            assertThat(this.sut.isNormalizedData(), equalTo(testCase));
        }
    }

    @Test
    public void test_getArchitectureParameters_always_retArchitectureParams() {
        // Arrange
        int expectedHiddenCount = -1;
        int expectedFactorsCount = -1;

        // Act
        ArchitectureParameters result = this.sut.getArchitectureParameters();

        // Assert
        assertThat(result.nin, equalTo(this.sut.getNin()));
        assertThat(result.nout, equalTo(this.sut.getNout()));
        assertThat(result.nhidden, equalTo(expectedHiddenCount));
        assertThat(result.nfactors, equalTo(expectedFactorsCount));
    }

    @Test
    public void test_prepareDataStat_always_preparesStats() throws MathException {
        // Arrange
        Matrix x = createMatrix();
        Matrix y = createMatrix();
        Matrix expectedXmean = Matlib.createMatrix();
        Matrix expectedYmean = Matlib.createMatrix();
        Matrix expectedXstd = Matlib.createMatrix();
        Matrix expectedYstd = Matlib.createMatrix();
        calculateExpectedMatrices(x, y, expectedXmean, expectedYmean, expectedXstd, expectedYstd);

        // Act
        this.sut.prepareDataStat(x, y);

        // Assert
        assertEqual(expectedXmean, this.sut.getXmean());
        assertEqual(expectedYmean, this.sut.getYmean());
        assertEqual(expectedXstd, this.sut.getXstd());
        assertEqual(expectedYstd, this.sut.getYstd());
    }

    @Test
    public void test_writeData_normalizeData_writesNormalizedData() throws IOException, MathException {
        // Arrange
        int numberOfSamples = 3;
        int dataLength = 4;
        Matrix x = createMatrix(numberOfSamples, dataLength);
        Matrix y = createMatrix(numberOfSamples, dataLength);
        File file = createEmptyFile();

        this.sut.prepareDataStat(x, y);
        this.sut.setNormalizeData(true);

        try (FileWriter fWriter = new FileWriter(file.getAbsolutePath());
             BufferedWriter bWriter = new BufferedWriter(fWriter)) {
            // Act
            this.sut.writeData(bWriter, x, y);
        }

        // Assert
        verifyFileContentsForData(file.getAbsolutePath(), x, y);
    }

    @Test
    public void test_writeData_notNormalizeData_writesData() throws IOException, MathException {
        // Arrange
        int numberOfSamples = 3;
        int inputDataLength = 4;
        int outputDataLength = 5;
        Matrix x = createMatrix(numberOfSamples, inputDataLength);
        Matrix y = createMatrix(numberOfSamples, outputDataLength);
        File file = createEmptyFile();

        try (FileWriter fWriter = new FileWriter(file.getAbsolutePath());
             BufferedWriter bWriter = new BufferedWriter(fWriter)) {
            // Act
            this.sut.writeData(bWriter, x, y);
        }

        // Assert
        verifyFileContentsForData(file.getAbsolutePath(), x, y);
    }

    @Test
    public void test_readWeights_versionIsNotOne_doesNotReadsWeights() throws IOException {
        // Arrange
        // No arrangements

        try (BufferedReader reader = createBufferedReader(2)) {
            // Act
            this.sut.readWeights(reader);
        }

        // Assert
        Matrix[] weights = this.sut.weights;
        for (int i = 0; i < nlayers - 1; i++) {
            assertThat(weights[i].getRows(), equalTo(0));
            assertThat(weights[i].getCols(), equalTo(0));
        }

        assertNull(weights[nlayers - 1]);
    }

    @Test
    public void test_readWeights_biasIncluded_readsWeightsAccordingly() throws IOException {
        // Arrange
        // No arrangements

        try (BufferedReader reader = createBufferedReader(1, 1, anyInteger())) {
            // Act
            this.sut.readWeights(reader);
        }

        // Assert
        assertThatWeightsAreRead();
    }

    @Test
    public void test_readWeights_biasOmitted_readsWeightsAccordingly() throws IOException {
        // Arrange
        // No arrangements

        try (BufferedReader reader = createBufferedReader(1, 0, anyInteger())) {
           // Act
            this.sut.readWeights(reader);
        }

        // Assert
        assertThatWeightsAreRead();
    }

    @Test
    public void test_readWeights_unitTypeSpherical_readsWeightsAccordingly() throws IOException {
        // Arrange
        // No arrangements

        try (BufferedReader reader = createBufferedReader(1, anyInteger(), 0)) {
            // Act
            this.sut.readWeights(reader);
        }

        // Assert
        assertThatWeightsAreRead();
    }

    @Test
    public void test_readWeights_unitTypeElliptical_readsWeightsAccordingly() throws IOException {
        // Arrange
        // No arrangements

        try (BufferedReader reader = createBufferedReader(1, anyInteger(), 1)) {
            // Act
            this.sut.readWeights(reader);
        }

        // Assert
        assertThatWeightsAreRead();
    }

    @Test
    public void test_writeParameters_always_writesParameters() throws IOException, MathException {
        // Arrange
        File file = createEmptyFile();

        try (FileWriter fWriter = new FileWriter(file.getAbsolutePath());
            BufferedWriter bWriter = new BufferedWriter(fWriter)) {
            // Act
            this.sut.writeParameters(bWriter);
        }

        // Assert
        verifyFileContentsForParameters(file.getAbsolutePath());
    }

    @Test
    public void test_writeWeights_biasIncluded_writeWeightsAccordingly() throws IOException {
        // Arrange
        File file = createEmptyFile();

        this.sut.setBias(1);
        loadWeights();

        try (FileWriter fWriter = new FileWriter(file.getAbsolutePath());
             BufferedWriter bWriter = new BufferedWriter(fWriter)) {
            // Act
            this.sut.writeWeights(bWriter);
        }

        // Assert
        verifyFileContentsForWeights(file.getAbsolutePath());
    }

    @Test
    public void test_writeWeights_biasOmitted_writeWeightsAccordingly() throws IOException {
        // Arrange
        File file = createEmptyFile();

        this.sut.setBias(0);
        loadWeights();

        try (FileWriter fWriter = new FileWriter(file.getAbsolutePath());
             BufferedWriter bWriter = new BufferedWriter(fWriter)) {
            // Act
            this.sut.writeWeights(bWriter);
        }

        // Assert
        verifyFileContentsForWeights(file.getAbsolutePath());
    }

    @Test
    public void test_writeWeights_unitTypeSpherical_writeWeightsAccordingly() throws IOException {
        // Arrange
        File file = createEmptyFile();

        this.sut.unitType = 0;
        loadWeights();

        try (FileWriter fWriter = new FileWriter(file.getAbsolutePath());
             BufferedWriter bWriter = new BufferedWriter(fWriter)) {
            // Act
            this.sut.writeWeights(bWriter);
        }

        // Assert
        verifyFileContentsForWeights(file.getAbsolutePath());
    }

    @Test
    public void test_writeWeights_unitTypeElliptical_writeWeightsAccordingly() throws IOException {
        // Arrange
        File file = createEmptyFile();

        this.sut.unitType = 1;
        loadWeights();

        try (FileWriter fWriter = new FileWriter(file.getAbsolutePath());
             BufferedWriter bWriter = new BufferedWriter(fWriter)) {
            // Act
            this.sut.writeWeights(bWriter);
        }

        // Assert
        verifyFileContentsForWeights(file.getAbsolutePath());
    }

    @Test
    public void test_writeNormalizeFactorToFile_always_writesData() throws MathException, IOException {
        // Arrange
        Matrix x = createMatrix();
        Matrix y = createMatrix();
        this.sut.prepareDataStat(x, y);

        File file = createEmptyFile();

        try (FileWriter fWriter = new FileWriter(file.getAbsolutePath());
             BufferedWriter bWriter = new BufferedWriter(fWriter)) {
            // Act
            this.sut.writeNormalizeFactorToFile(bWriter);
        }

        // Assert
        verifyFileContentsForNormalizedFactor(file.getAbsolutePath());
    }

    @Test
    public void test_unnormalizePrediction_always_unnormalizePrediction() throws MathException {
        // Arrange
        Matrix y = createMatrix();

        mockStatic(Matlib.class);
        doNothing().when(Matlib.class);
        Matlib.unnormalize(Matchers.any(Matrix.class), Matchers.any(Matrix.class), Matchers.any(Matrix.class), Matchers.any(Matrix.class));

        // Act
        this.sut.unnormalizePrediction(y);

        // Assert
        verifyStatic(times(1));
        Matlib.unnormalize(y, this.sut.getYmean(), this.sut.getYstd(), y);
    }

    @Test
    public void test_getRMSE_always_retRmse() {
        // Arrange
        this.sut.rmse = anyDouble();

        // Act & Assert
        assertThat(this.sut.getRMSE(), equalTo(this.sut.rmse));
    }

    @Test
    public void test_getDescription_always_retDescription() {
        // Arrange
        // No arrangements

        // Act & Assert
        assertThat(this.sut.getDescription(), equalTo(expectedDescription()));
    }

    @Test
    public void test_getParametersVector_biasOmitted_retModelAccordingly() throws IOException {
        // Arrange
        this.sut.setBias(0);
        loadWeights();

        // Act
        Vector result = this.sut.getParametersVector();

        // Assert
        verifyParametersVector(result);
    }

    @Test
    public void test_getParametersVector_biasIncluded_retModelAccordingly() throws IOException {
        // Arrange
        this.sut.setBias(1);
        loadWeights();

        // Act
        Vector result = this.sut.getParametersVector();

        // Assert
        verifyParametersVector(result);
    }

    @Test
    public void test_getParametersVector_unitTypeSpherical_retModelAccordingly() throws IOException {
        // Arrange
        this.sut.unitType = 0;
        loadWeights();

        // Act
        Vector result = this.sut.getParametersVector();

        // Assert
        verifyParametersVector(result);
    }

    @Test
    public void test_getParametersVector_unitTypeElliptical_retModelAccordingly() throws IOException {
        // Arrange
        this.sut.unitType = 1;
        loadWeights();

        // Act
        Vector result = this.sut.getParametersVector();

        // Assert
        verifyParametersVector(result);
    }

    @Test
    public void test_setParametersVector_biasOmitted_setsParametersAccordingly() {
        // Arrange
        this.sut.setBias(0);
        Vector parametersVector = createParametersVector();

        // Act
        this.sut.setParametersVector(parametersVector);

        // Assert
        verifyParametersAreSet(parametersVector);
    }

    @Test
    public void test_setParametersVector_biasIncluded_setsParametersAccordingly() {
        // Arrange
        this.sut.setBias(1);
        Vector parametersVector = createParametersVector();

        // Act
        this.sut.setParametersVector(parametersVector);

        // Assert
        verifyParametersAreSet(parametersVector);
    }

    @Test
    public void test_setParametersVector_unitTypeSpherical_setsParametersAccordingly() {
        // Arrange
        this.sut.unitType = 0;
        Vector parametersVector = createParametersVector();

        // Act
        this.sut.setParametersVector(parametersVector);

        // Assert
        verifyParametersAreSet(parametersVector);
    }

    @Test
    public void test_setParametersVector_unitTypeElliptical_setsParametersAccordingly() {
        // Arrange
        this.sut.unitType = 1;
        Vector parametersVector = createParametersVector();

        // Act
        this.sut.setParametersVector(parametersVector);

        // Assert
        verifyParametersAreSet(parametersVector);
    }

    @Test
    public void test_writeXMLFile_biasOmitted_writesXmlAccordingly() throws IOException {
        // Arrange
        File file = createEmptyFile();

        this.sut.setBias(0);
        loadWeights();

        int indentNumber = 0;

        try (FileWriter fWriter = new FileWriter(file.getAbsolutePath());
             BufferedWriter bWriter = new BufferedWriter(fWriter)) {
            // Act
            this.sut.writeXMLFile(bWriter, indentNumber);
        }

        // Assert
        verifyXmlContent(file.getAbsolutePath(), indentNumber);
    }

    @Test
    public void test_writeXMLFile_biasIncluded_writesXmlAccordingly() throws IOException {
        // Arrange
        File file = createEmptyFile();

        this.sut.setBias(1);
        loadWeights();

        int indentNumber = 0;

        try (FileWriter fWriter = new FileWriter(file.getAbsolutePath());
             BufferedWriter bWriter = new BufferedWriter(fWriter)) {
            // Act
            this.sut.writeXMLFile(bWriter, indentNumber);
        }

        // Assert
        verifyXmlContent(file.getAbsolutePath(), indentNumber);
    }

    @Test
    public void test_writeXMLFile_unitTypeSpherical_writesXmlAccordingly() throws IOException {
        // Arrange
        File file = createEmptyFile();

        this.sut.unitType = 0;
        loadWeights();

        int indentNumber = 0;

        try (FileWriter fWriter = new FileWriter(file.getAbsolutePath());
             BufferedWriter bWriter = new BufferedWriter(fWriter)) {
            // Act
            this.sut.writeXMLFile(bWriter, indentNumber);
        }

        // Assert
        verifyXmlContent(file.getAbsolutePath(), indentNumber);
    }

    @Test
    public void test_writeXMLFile_unitTypeElliptical_writesXmlAccordingly() throws IOException {
        // Arrange
        File file = createEmptyFile();

        this.sut.unitType = 1;
        loadWeights();

        int indentNumber = 0;

        try (FileWriter fWriter = new FileWriter(file.getAbsolutePath());
             BufferedWriter bWriter = new BufferedWriter(fWriter)) {
            // Act
            this.sut.writeXMLFile(bWriter, indentNumber);
        }

        // Assert
        verifyXmlContent(file.getAbsolutePath(), indentNumber);
    }

    private double anyDouble() {
        // Returns random integer between 1 and 10.
        return RandomGenerator.nextDouble();
    }

    private int anyInteger() {
        // Returns random integer between 3 and 5.
        return RandomGenerator.nextInt(3) + 3;
    }

    private String arrayToText(Matrix m, int row) {
        int cols = m.getCols();
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < cols - 1; i++) {
            sb.append(m.get(row, i)).append(", ");
        }

        sb.append(m.get(row, cols - 1)).append("");
        return sb.toString();
    }

    private void assertEqual(Matrix expected, Matrix actual) {
        assertThat(actual.getRows(), equalTo(expected.getRows()));
        assertThat(actual.getCols(), equalTo(expected.getCols()));

        for (int r = 0; r < expected.getRows(); r++) {
            for (int c = 0; c < expected.getCols(); c++) {
                assertThat(actual.get(r, c), equalTo(expected.get(r, c)));
            }
        }
    }

    private void assertNextLineEquals(BufferedReader bReader, String message) throws IOException {
        String line = bReader.readLine();
        assertThat(line, equalTo(message));
    }

    private void assertThatWeightsAreRead() {
        assertThat(this.sut.getNin(), equalTo(this.fileData.nodes[0]));
        assertThat(this.sut.getNout(), equalTo(this.fileData.nodes[2]));
        assertThat(this.sut.overlap, equalTo(this.fileData.overlap));
        assertThat(this.sut.unitType, equalTo(this.fileData.unitType));
        assertThat(this.sut.bias, equalTo(this.fileData.bias));

        assertThat(this.fileData.weights.length, greaterThan(0));
        assertThat(this.sut.weights.length, equalTo(this.fileData.weights.length));

        for (int i = 0; i < this.fileData.weights.length; i++) {
            Matrix actual = this.sut.weights[i];
            Matrix expected = this.fileData.weights[i];

            assertThat(expected.getRows(), greaterThan(0));
            assertThat(expected.getCols(), greaterThan(0));

            for (int r = 0; r < expected.getRows(); r++) {
                for (int c = 0; c < expected.getCols(); c++) {
                    assertThat(actual.get(r, c), equalTo(expected.get(r, c)));
                }
            }
        }
    }

    private void calculateExpectedMatrices(Matrix x, Matrix y, Matrix expectedXmean, Matrix expectedYmean, Matrix expectedXstd, Matrix expectedYstd) throws MathException {
        Matrix cloneX = clone(x);
        Matrix cloneY = clone(y);
        Matlib.mean(cloneX, expectedXmean);
        Matlib.mean(cloneY, expectedYmean);
        Matlib.std(cloneX, expectedXstd);
        Matlib.std(cloneY, expectedYstd);
    }

    private Matrix clone(Matrix matrix) {
        Matrix cloned = Matlib.createMatrix(matrix.getRows(), matrix.getCols());

        for (int r = 0; r < matrix.getRows(); r++) {
            for (int c = 0; c < matrix.getCols(); c++) {
                cloned.set(r, c, matrix.get(r, c));
            }
        }

        return cloned;
    }

    private String[] convertArray(double[] inputs) {
        String[] strings = new String[inputs.length];

        for (int i = 0; i < inputs.length; i++) {
            strings[i] = String.valueOf(inputs[i]);
        }

        return strings;
    }

    private BufferedReader createBufferedReader(int version) throws IOException {
        return createBufferedReader(version, 1, 0, anyInteger(), anyInteger());
    }

    private BufferedReader createBufferedReader(int bias, int unitType) throws IOException {
        return createBufferedReader(1, bias, unitType, anyInteger(), anyInteger());
    }

    private BufferedReader createBufferedReader(int bias, int unitType, int inputs, int outputs) throws IOException {
        return createBufferedReader(1, bias, unitType, inputs, outputs);
    }

    private BufferedReader createBufferedReader(int version, int bias, int unitType) throws IOException {
        return createBufferedReader(version, bias, unitType, anyInteger(), anyInteger());
    }

    private BufferedReader createBufferedReader(int version, int bias, int unitType, int inputs, int outputs) throws IOException {
        File file = createEmptyFile();
        this.fileData = new FileData();
        this.fileData.bias = bias;
        this.fileData.unitType = unitType;

        try (FileWriter fWriter = new FileWriter(file.getAbsoluteFile());
             BufferedWriter writer = new BufferedWriter(fWriter)) {
            writer.write(version + ";");
            writer.newLine();

            this.fileData.nodes = new int[]{inputs, anyInteger(), outputs};
            writer.write(this.fileData.nodes[0] + "," + this.fileData.nodes[1] + "," + this.fileData.nodes[2] + ";");
            writer.newLine();

            this.fileData.overlap = anyDouble();
            writer.write(this.fileData.overlap + ";");
            writer.newLine();

            writer.write(unitType + ";");
            writer.newLine();
            writer.write(bias + ";");
            writer.newLine();
            writeWeights(writer);

            return new BufferedReader(new FileReader(file.getAbsolutePath()));
        } catch (Exception ex) {
            fail("Failed to create buffered reader.");
            return null;
        }
    }

    private File createEmptyFile() throws IOException {
        File file = temporaryFolder.newFile();

        files.addElement(file);

        return file;
    }

    private Matrix createMatrix() {
        // Creating a 3 x 4 matrix with sample data
        int rows = 3;
        int columns = 4;
        return createMatrix(rows, columns);
    }

    private Matrix createMatrix(int m, int n) {
        // Creating a m x n matrix with sample data
        Matrix matrix = Matlib.createMatrix(m, n);
        populateMatrix(matrix);
        return matrix;
    }

    private int[] createNodes() {
        // Input: 3
        // Output: 3
        // h: anyInteger
        return new int[]{3, anyInteger(), 3};
    }

    private Vector createParametersVector() {
        Vector parameters = new Vector();
        parameters.addElement(3d);

        int[] nodes = new int[]{this.sut.getNin(), anyInteger(), this.sut.getNout()};
        parameters.addElement(nodes);
        int inputsCount = nodes[0];
        int outputsCount = nodes[2];

        // The variables h, hp, hx and nx are copied from product code. No idea why are they chosen.
        int h = nodes[1];
        int hp, hx, nx;

        if (this.sut.bias == 1) {
            hp = h + 1;
        } else {
            hp = h;
        }

        if (this.sut.unitType == 0) {
            hx = h;
            nx = 1;
        } else {
            hx = inputsCount * h;
            nx = inputsCount;
        }

        parameters.addElement(anyDouble());
        parameters.addElement(this.sut.unitType);

        // Unit centers
        this.sut.weights[0] = Matlib.zeros(h, inputsCount);
        for (int i = 0; i < h; i++) {
            double[] weights = new double[inputsCount];
            for (int j = 0; j < inputsCount; j++) {
                weights[j] = anyDouble();
            }

            parameters.addElement(weights);
        }

        // Unit shapes
        this.sut.weights[1] = Matlib.zeros(hx, nx);
        for (int i = 0; i < hx; i++) {
            double[] weights = new double[nx];
            for (int j = 0; j < nx; j++) {
                weights[j] = anyDouble();
            }

            parameters.addElement(weights);
        }

        // Second layer weights
        this.sut.weights[2] = Matlib.zeros(hp, outputsCount);
        for (int i = 0; i < hp; i++) {
            double[] weights = new double[outputsCount];
            for (int j = 0; j < outputsCount; j++) {
                weights[j] = anyDouble();
            }

            parameters.addElement(weights);
        }

        return parameters;
    }

    private String expectedDescription() {
        String newLine = System.getProperty("line.separator");
        String description = "" + this.sut.nodes[0];
        for (int i = 1; i < nlayers; i++) {
            description = description + ", " + this.sut.nodes[i];
        }

        description = description + "; Layer sizes." + newLine;
        description = description + this.sut.overlap + "; Unit overlap parameter" + newLine;
        description = description + this.sut.unitType + "; Unit type (0 = spherical, 1 = elliptical) " + newLine;
        description = description + this.sut.bias + "; Bias (0 = omitted, 1 = included)" + newLine;

        return description;
    }

    private void loadWeights() throws IOException {
        loadWeights(anyInteger(), anyInteger());
    }

    private void loadWeights(int inputs, int outputs) throws IOException {
        try (BufferedReader reader = createBufferedReader(this.sut.bias, this.sut.unitType, inputs, outputs)) {
            this.sut.readWeights(reader);
        } catch (Exception ex) {
            fail("Failed to load weights.");
        }
    }

    private void populateArray(double[] inputs) {
        for (int i = 0; i < inputs.length; i++) {
            inputs[i] = anyDouble();
        }
    }

    private void populateMatrix(Matrix matrix) {
        for (int r = 0; r < matrix.getRows(); r++) {
            for (int c = 0; c < matrix.getCols(); c++) {
                matrix.set(r, c, anyDouble());
            }
        }
    }

    private void verifyFileContentsForData(String filePath, Matrix x, Matrix y) throws IOException {
        try (FileReader fReader = new FileReader(filePath);
             BufferedReader bReader = new BufferedReader(fReader)) {
            int len = x.getRows();
            int inputsCount = x.getCols();
            int outputsCount = y.getCols();

            assertNextLineEquals(bReader, "1; Version of this save/restore protocol for data sets");
            assertNextLineEquals(bReader, len + " ; Number of samples in this data-set");
            assertNextLineEquals(bReader, inputsCount + " ; Length of each input data vector");
            assertNextLineEquals(bReader, outputsCount + " ; Length of each output data vector");

            if (this.sut.isNormalizedData()) {
                // scale the inputs
                Matrix xNormalized = Matlib.createMatrix();
                Matrix yNormalized = Matlib.createMatrix();
                Matlib.normalize(x, this.sut.getXmean(), this.sut.getXstd(), xNormalized);
                Matlib.normalize(y, this.sut.getYmean(), this.sut.getYstd(), yNormalized);

                for (int i = 0; i < len; i++) {
                    String inputRow = arrayToText(xNormalized, i);
                    String outputRow = arrayToText(yNormalized, i);
                    double timeStamp = (double) i;

                    assertNextLineEquals(bReader, i + ", " + timeStamp + ", OK, " + inputRow + ", " + outputRow);
                }
            } else {
                for (int i = 0; i < len; i++) {
                    String inputRow = arrayToText(x, i);
                    String outputRow = arrayToText(y, i);
                    double timeStamp = (double) i;

                    assertNextLineEquals(bReader, i + ", " + timeStamp + ", OK, " + inputRow + ", " + outputRow);
                }
            }
        } catch (Exception ex) {
            fail("Failed to verify file contents");
        }
    }

    private void verifyFileContentsForNormalizedFactor(String path) throws IOException {
        try (FileReader fReader = new FileReader(path);
             BufferedReader bReader = new BufferedReader(fReader)) {
            String expected = "Means,";
            for (int i = 0; i < this.sut.getXmean().getCols(); i++) {
                expected += this.sut.getXmean().get(0, i) + ",";
            }

            for (int i = 0; i < this.sut.getYmean().getCols(); i++) {
                expected += String.valueOf(this.sut.getYmean().get(0, i));
                if (i < this.sut.getYmean().getCols() - 1) {
                    expected += ",";
                }
            }

            assertNextLineEquals(bReader, expected);

            expected = "Stds,";
            for (int i = 0; i < this.sut.getXstd().getCols(); i++) {
                expected += this.sut.getXstd().get(0, i) + ",";
            }

            for (int i = 0; i < this.sut.getYstd().getCols(); i++) {
                expected += String.valueOf(this.sut.getYstd().get(0, i));
                if (i < this.sut.getYstd().getCols() - 1) {
                    expected += ",";
                }
            }

            assertNextLineEquals(bReader, expected);
        } catch (Exception ex) {
            fail("Failed to verify file contents");
        }
    }

    private void verifyFileContentsForParameters(String path) throws IOException {
        try (FileReader fReader = new FileReader(path);
             BufferedReader bReader = new BufferedReader(fReader)) {
            assertNextLineEquals(bReader, "1; Version of this file save/restore protocol for RBFNs or Rho-Nets");
            assertNextLineEquals(bReader, this.sut.nodes[0] + ", " + this.sut.nodes[1] + ", " + this.sut.nodes[2] + "; Layer sizes.");
            assertNextLineEquals(bReader, this.sut.overlap + "; Unit overlap parameter");
            assertNextLineEquals(bReader, this.sut.unitType + "; Unit type (0 = spherical, 1 = elliptical) ");
            assertNextLineEquals(bReader, this.sut.bias + "; Bias (0 = omitted, 1 = included)");
        } catch (Exception ex) {
            fail("Failed to verify file contents");
        }
    }

    private void verifyFileContentsForWeights(String path) throws IOException {
        try (FileReader fReader = new FileReader(path);
             BufferedReader bReader = new BufferedReader(fReader)) {
            int inputsCount = this.sut.nodes[0];
            int outputsCount = this.sut.nodes[2];

            // The variables h, hp, hx and nx are copied from product code. No idea why are they chosen.
            int h = this.sut.nodes[1];
            int hp, hx, nx;

            if (this.sut.bias == 1) {
                hp = h + 1;
            } else {
                hp = h;
            }

            if (this.sut.unitType == 0) {
                hx = h;
                nx = 1;
            } else {
                hx = inputsCount * h;
                nx = inputsCount;
            }

            for (int i = 0; i < h; i++) {
                String expected = "";
                for (int j = 0; j < inputsCount; j++) {
                    if (j == inputsCount - 1) {
                        expected += this.sut.weights[0].get(i, j) + " ; Unit centers";
                    } else {
                        expected += this.sut.weights[0].get(i, j) + ",";
                    }
                }

                assertNextLineEquals(bReader, expected);
            }

            for (int i = 0; i < hx; i++) {
                String expected = "";
                for (int j = 0; j < nx; j++) {
                    if (j == nx - 1) {
                        expected += this.sut.weights[1].get(i, j) + " ; Unit shapes";
                    } else {
                        expected += this.sut.weights[1].get(i, j) + ",";
                    }
                }

                assertNextLineEquals(bReader, expected);
            }

            for (int i = 0; i < hp; i++) {
                String expected = "";
                for (int j = 0; j < outputsCount; j++) {
                    if (j == outputsCount - 1) {
                        expected += this.sut.weights[2].get(i, j) + " ; Second layer weights";
                    } else {
                        expected += this.sut.weights[2].get(i, j) + ",";
                    }
                }

                assertNextLineEquals(bReader, expected);
            }
        } catch (Exception ex) {
            fail("Failed to verify file contents");
        }
    }

    private int verifyNodes(BufferedReader bReader, int indentNumber) throws IOException {
        indentNumber++;
        for (int i = 0; i < this.sut.nodes.length; i++) {
            assertNextLineEquals(bReader, Utilities.indent(indentNumber) + "<layer>");

            indentNumber++;
            assertNextLineEquals(bReader, Utilities.indent(indentNumber) + "<layerIndex>" + (i + 1) + "</layerIndex>");
            assertNextLineEquals(bReader, Utilities.indent(indentNumber) + "<layerSize>" + this.sut.nodes[i] + "</layerSize>");

            indentNumber--;
            assertNextLineEquals(bReader, Utilities.indent(indentNumber) + "</layer>");
        }

        return indentNumber;
    }

    private void verifyParametersAreSet(Vector parameters) {
        int index = 0;
        double layers = (double) parameters.get(index++);
        assertThat((double) this.sut.nlayers, equalTo(layers));

        int[] nodes = (int[]) parameters.get(index++);
        assertThat(this.sut.nodes.length, equalTo(nodes.length));
        for (int i = 0; i < nodes.length; i++) {
            assertThat(this.sut.nodes[i], equalTo(nodes[i]));
        }

        int inputsCount = nodes[0];
        int outputsCount = nodes[2];

        // The variables h, hp, hx and nx are copied from product code. No idea why are they chosen.
        int h = nodes[1];
        int hp, hx, nx;

        if (this.sut.bias == 1) {
            hp = h + 1;
        } else {
            hp = h;
        }

        if (this.sut.unitType == 0) {
            hx = h;
            nx = 1;
        } else {
            hx = inputsCount * h;
            nx = inputsCount;
        }

        double overlap = (double) parameters.get(index++);
        assertThat(this.sut.overlap, equalTo(overlap));

        int unitType = (int) parameters.get(index++);
        assertThat(this.sut.unitType, equalTo(unitType));

        // Unit centers
        for (int i = 0; i < h; i++) {
            double[] weights = (double[]) parameters.get(index++);

            assertThat(this.sut.weights[0].getCols(), equalTo(weights.length));
            for (int j = 0; j < inputsCount; j++) {
                assertThat(this.sut.weights[0].get(i, j), equalTo(weights[j]));
            }
        }

        // Unit shapes
        for (int i = 0; i < hx; i++) {
            double[] weights = (double[]) parameters.get(index++);

            assertThat(this.sut.weights[1].getCols(), equalTo(weights.length));
            for (int j = 0; j < nx; j++) {
                assertThat(this.sut.weights[1].get(i, j), equalTo(weights[j]));
            }
        }

        // Second layer weights
        for (int i = 0; i < hp; i++) {
            double[] weights = (double[]) parameters.get(index++);

            assertThat(this.sut.weights[2].getCols(), equalTo(weights.length));
            for (int j = 0; j < outputsCount; j++) {
                assertThat(this.sut.weights[2].get(i, j), equalTo(weights[j]));
            }
        }
    }

    private void verifyParametersVector(Vector result) {
        int index = 0;

        double layers = (double) result.get(index++);
        assertThat(layers, equalTo((double) nlayers));

        int[] nodes = (int[]) result.get(index++);
        assertThat(nodes.length, equalTo(this.sut.nodes.length));
        for (int i = 0; i < this.sut.nodes.length; i++) {
            assertThat(nodes[i], equalTo(this.sut.nodes[i]));
        }

        int inputsCount = nodes[0];
        int outputsCount = nodes[2];

        // The variables h, hp, hx and nx are copied from product code. No idea why are they chosen.
        int h = nodes[1];
        int hp, hx, nx;

        if (this.sut.bias == 1) {
            hp = h + 1;
        } else {
            hp = h;
        }

        if (this.sut.unitType == 0) {
            hx = h;
            nx = 1;
        } else {
            hx = inputsCount * h;
            nx = inputsCount;
        }

        double overlap = (double) result.get(index++);
        assertThat(overlap, equalTo(this.sut.overlap));

        int unitType = (int) result.get(index++);
        assertThat(unitType, equalTo(this.sut.unitType));

        // Unit centers
        for (int i = 0; i < h; i++) {
            double[] actual = (double[]) result.get(index++);

            assertThat(actual.length, equalTo(inputsCount));
            for (int j = 0; j < inputsCount; j++) {
                assertThat(actual[j], equalTo(this.sut.weights[0].get(i, j)));
            }
        }

        // Unit shapes
        for (int i = 0; i < hx; i++) {
            double[] actual = (double[]) result.get(index++);

            assertThat(actual.length, equalTo(nx));
            for (int j = 0; j < nx; j++) {
                assertThat(actual[j], equalTo(this.sut.weights[1].get(i, j)));
            }
        }

        // Second layer weights
        for (int i = 0; i < hp; i++) {
            double[] actual = (double[]) result.get(index++);

            assertThat(actual.length, equalTo(outputsCount));
            for (int j = 0; j < outputsCount; j++) {
                assertThat(actual[j], equalTo(this.sut.weights[2].get(i, j)));
            }
        }
    }

    private void verifyXmlContent(String path, int indentNumber) throws IOException {
        try (FileReader fReader = new FileReader(path);
            BufferedReader bReader = new BufferedReader(fReader)) {
            assertNextLineEquals(bReader, Utilities.indent(indentNumber) + "<rbfn>");
            indentNumber = verifyNodes(bReader, indentNumber);

            assertNextLineEquals(bReader, Utilities.indent(indentNumber) + "<overlap>" + this.sut.overlap + "</overlap>");
            assertNextLineEquals(bReader, Utilities.indent(indentNumber) + "<unitType>" + this.sut.unitType + "</unitType>");
            assertNextLineEquals(bReader, Utilities.indent(indentNumber) + "<bias>" + this.sut.bias + "</bias>");

            int inputsCount = this.sut.nodes[0];
            int outputsCount = this.sut.nodes[2];

            // The variables h, hp, hx and nx are copied from product code. No idea why are they chosen.
            int h = this.sut.nodes[1];
            int hp, hx, nx;
            if (this.sut.bias == 1) {
                hp = h + 1;
            } else {
                hp = h;
            }

            if (this.sut.unitType == 0) {
                hx = h;
                nx = 1;
            } else {
                hx = inputsCount * h;
                nx = inputsCount;
            }

            indentNumber = verifyUnitCenters(bReader, indentNumber, h, inputsCount);
            indentNumber = verifyUnitShapes(bReader, indentNumber, hx, nx);
            indentNumber = verifySecondLayerWeights(bReader, indentNumber, hp, outputsCount);

            indentNumber--;
            assertNextLineEquals(bReader, Utilities.indent(indentNumber) + "</rbfn>");
        } catch (Exception ex) {
            fail("Failed to verify file contents");
        }
    }

    private int verifySecondLayerWeights(BufferedReader bReader, int indentNumber, int hp, int outputsCount) throws IOException {
        assertNextLineEquals(bReader, Utilities.indent(indentNumber) + "<secondLayerWeights>");

        indentNumber++;
        for (int i = 0; i < hp; i++) {
            for (int j = 0; j < outputsCount; j++) {
                assertNextLineEquals(bReader, Utilities.indent(indentNumber) + "<node>");

                indentNumber++;
                assertNextLineEquals(bReader, Utilities.indent(indentNumber) + "<weight>" + this.sut.weights[2].get(i, j) + "</weight>");
                assertNextLineEquals(bReader, Utilities.indent(indentNumber) + "<row>" + i + "</row>");
                assertNextLineEquals(bReader, Utilities.indent(indentNumber) + "<column>" + j + "</column>");

                indentNumber--;
                assertNextLineEquals(bReader, Utilities.indent(indentNumber) + "</node>");
            }
        }

        indentNumber--;
        assertNextLineEquals(bReader, Utilities.indent(indentNumber) + "</secondLayerWeights>");

        return indentNumber;
    }

    private int verifyUnitShapes(BufferedReader bReader, int indentNumber, int hx, int nx) throws IOException {
        assertNextLineEquals(bReader, Utilities.indent(indentNumber) + "<unitShapes>");

        indentNumber++;
        for (int i = 0; i < hx; i++) {
            for (int j = 0; j < nx; j++) {
                assertNextLineEquals(bReader, Utilities.indent(indentNumber) + "<node>");

                indentNumber++;
                assertNextLineEquals(bReader, Utilities.indent(indentNumber) + "<center>" + this.sut.weights[1].get(i, j) + "</center>");
                assertNextLineEquals(bReader, Utilities.indent(indentNumber) + "<row>" + i + "</row>");
                assertNextLineEquals(bReader, Utilities.indent(indentNumber) + "<column>" + j + "</column>");

                indentNumber--;
                assertNextLineEquals(bReader, Utilities.indent(indentNumber) + "</node>");
            }
        }

        indentNumber--;
        assertNextLineEquals(bReader, Utilities.indent(indentNumber) + "</unitShapes>");

        return indentNumber;
    }

    private int verifyUnitCenters(BufferedReader bReader, int indentNumber, int h, int inputsCount) throws IOException {
        assertNextLineEquals(bReader, Utilities.indent(indentNumber) + "<unitCenters>");

        indentNumber++;
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < inputsCount; j++) {
                assertNextLineEquals(bReader, Utilities.indent(indentNumber) + "<node>");

                indentNumber++;
                assertNextLineEquals(bReader, Utilities.indent(indentNumber) + "<center>" + this.sut.weights[0].get(i, j) + "</center>");
                assertNextLineEquals(bReader, Utilities.indent(indentNumber) + "<row>" + i + "</row>");
                assertNextLineEquals(bReader, Utilities.indent(indentNumber) + "<column>" + j + "</column>");

                indentNumber--;
                assertNextLineEquals(bReader, Utilities.indent(indentNumber) + "</node>");
            }
        }

        indentNumber--;
        assertNextLineEquals(bReader, Utilities.indent(indentNumber) + "</unitCenters>");

        return indentNumber;
    }

    private void writeWeights(BufferedWriter writer) throws IOException {
        int inputsCount = this.fileData.nodes[0];
        int outputsCount = this.fileData.nodes[2];

        // The variables h, hp, hx and nx are copied from product code. No idea why are they chosen.
        int h = this.fileData.nodes[1];
        int hp, hx, nx;

        if (this.fileData.bias == 1) {
            hp = h + 1;
        } else {
            hp = h;
        }

        if (this.fileData.unitType == 0) {
            hx = h;
            nx = 1;
        } else {
            hx = inputsCount * h;
            nx = inputsCount;
        }

        // Write weight matrix
        this.fileData.weights = new Matrix[nlayers];
        this.fileData.weights[0] = Matlib.createMatrix(h, inputsCount);
        for (int i = 0; i < h; i++) {
            double[] weights = new double[inputsCount];
            populateArray(weights);

            for (int j = 0; j < inputsCount; j++) {
                this.fileData.weights[0].set(i, j, weights[j]);
            }

            String[] values = convertArray(weights);
            writer.write(String.join(",", values) + " ; Unit centers");
            writer.newLine();
        }

        this.fileData.weights[1] = Matlib.createMatrix(hx, nx);
        for (int i = 0; i < hx; i++) {
            double[] weights = new double[nx];
            populateArray(weights);

            for (int j = 0; j < nx; j++) {
                this.fileData.weights[1].set(i, j, weights[j]);
            }

            String[] values = convertArray(weights);
            writer.write(String.join(",", values) + " ; Unit shapes");
            writer.newLine();
        }

        this.fileData.weights[2] = Matlib.createMatrix(hp, outputsCount);
        for (int i = 0; i < hp; i++) {
            double[] weights = new double[outputsCount];
            populateArray(weights);

            for (int j = 0; j < outputsCount; j++) {
                this.fileData.weights[2].set(i, j, weights[j]);
            }

            String[] values = convertArray(weights);
            writer.write(String.join(",", values) + " ; Second layer weights");
            writer.newLine();
        }
    }

    // ClassicRbfn class is extended to read its protected fields.
    private class ClassicRbfnExtended extends ClassicRbfn {

        ClassicRbfnExtended(int[] nodes, double overlap, int unitType) {

            super(nodes, overlap, unitType);
            MaxAct = Matlib.createMatrix();
        }

        public Matrix getXmean() {
            return Xmean;
        }

        Matrix getYmean() {
            return Ymean;
        }

        public Matrix getXstd() {
            return Xstd;
        }

        Matrix getYstd() {
            return Ystd;
        }
    }

    private class FileData {
        public int[] nodes;
        public double overlap;
        public int bias;
        public Matrix[] weights;
        int unitType;
    }
}