package com.gensym.nols.data;

import com.gensym.DEBUG;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import java.awt.*;
import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.util.Arrays;
import java.util.Hashtable;
import java.util.Random;
import java.util.Vector;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.is;
import static org.hamcrest.Matchers.not;
import static org.hamcrest.collection.IsEmptyCollection.empty;
import static org.hamcrest.core.IsEqual.equalTo;
import static org.junit.Assert.*;
import static org.mockito.Mockito.verify;
import static org.powermock.api.mockito.PowerMockito.mock;
import static org.powermock.api.mockito.PowerMockito.when;

public class RawDataSourceTest {
    private static final int ANY_NUMBER = 0;
    private static final Random randomGenerator = new Random();

    private final ByteArrayOutputStream outContent = new ByteArrayOutputStream();
    private final int rows = 3;
    private final int cols = 4;

    private boolean debugFlag;
    private int numberOfLabels;
    private Vector<RawDataSourceListenerStub> sutEventListeners;

    @Before
    public void setup() {
        debugFlag = DEBUG.debugFlag;
        DEBUG.debugFlag = true;

        numberOfLabels = 10;

        setupStreams();
    }

    @After
    public void teardown() {
        DEBUG.debugFlag = debugFlag;

        cleanUpStreams();
    }

    @Test
    public void test_instance_always_setsNameAsRawData() {
        // Arrange
        RawDataSource sut = new RawDataSource();

        // Act & Assert
        assertThat(sut.getName(), is(equalTo("RawData")));
    }

    @Test
    public void test_instance_always_setsSelectStatus() {
        // Arrange
        RawDataSource sut = new RawDataSource();

        // Act & Assert
        assertTrue(sut.getSelectStatus());
    }

    @Test
    public void test_addDataSeries_dataSeriesDoesNotExist_invokesDataSeriesAddedEvent() {
        // Arrange
        Project project = createProject();
        RawDataSource sut = createSut(project);
        sut.setDataSeries(new Vector<DataSeries>());

        // Act
        sut.addDataSeries(createDataSeries(3, 4, getDataSeriesName(99)));

        // Assert
        assertThat(Arrays.asList(sutEventListeners), is(not(empty())));
        for (RawDataSourceListenerStub listener : sutEventListeners) {
            assertTrue(listener.DataSeriesAddedIsInvoked);
            assertThat(listener.DataSeriesAddedRawDataEvent.getIdentifier(), is(equalTo("dataSeriesAdded")));
        }
    }

    @Test
    public void test_addDataSeries_dataSeriesDoesNotExist_addsLabelMaskForDataSeries() {
        // Arrange
        Project project = createProject();
        RawDataSource sut = createSut(project);
        sut.setDataSeries(new Vector<DataSeries>());
        DataSeries newDataSeries = createDataSeries(3, 4, getDataSeriesName(99));

        // Act
        sut.addDataSeries(newDataSeries);

        // Assert
        assertThat(Arrays.asList(newDataSeries.getVarObjects()), is(not(empty())));
        for (int idx = 0; idx < newDataSeries.getVarObjects().size(); idx++) {
            Variable variable = newDataSeries.getVarByIndex(idx);
            boolean[][] labelMatrix = sut.getLabelMatrix(variable);
            assertNotNull(labelMatrix);
            assertThat(labelMatrix.length, is(equalTo(project.getNumberOfLabels())));

            for (boolean[] labels : labelMatrix) {
                assertThat(labels.length, is(equalTo(newDataSeries.getRow())));

                for (boolean label : labels) {
                    assertFalse(label);
                }
            }
        }
    }

    @Test
    public void test_addDataSeries_dataSeriesExists_doesNotInvokeDataSeriesAddedEvent() {
        // Arrange
        Project project = createProject();
        RawDataSource sut = createSut(project);

        // Act
        sut.addDataSeries((DataSeries) sut.getDataSeries().get(0));

        // Assert
        assertThat(Arrays.asList(sutEventListeners), is(not(empty())));
        for (RawDataSourceListenerStub listener : sutEventListeners) {
            assertFalse(listener.DataSeriesAddedIsInvoked);
        }
    }

    @Test
    public void test_removeDataSeries_isRemovedUsingIndex_invokesDataSeriesRemovedEvent() {
        // Arrange
        Project project = createProject();
        RawDataSource sut = createSut(project);

        // Act
        sut.removeDataSeries(0);

        // Assert
        assertThat(Arrays.asList(sutEventListeners), is(not(empty())));
        for (RawDataSourceListenerStub listener : sutEventListeners) {
            assertTrue(listener.DataSeriesRemovedIsInvoked);
            assertThat(listener.DataSeriesRemovedRawDataEvent.getIdentifier(), is(equalTo("dataSeriesRemoved")));
        }
    }

    @Test
    public void test_removeDataSeries_isRemovedUsingIndex_removesLabelMaskForDataSeries() {
        // Arrange
        Project project = createProject();
        RawDataSource sut = createSut(project);
        DataSeries dataSeries = sut.getDataSeries(0);

        // Act
        sut.removeDataSeries(0);

        // Assert
        assertThat(Arrays.asList(dataSeries.getVarObjects()), is(not(empty())));
        for (int idx = 0; idx < dataSeries.getVarObjects().size(); idx++) {
            Variable variable = dataSeries.getVarByIndex(idx);
            boolean[][] labelMatrix = sut.getLabelMatrix(variable);
            assertNull(labelMatrix);
        }
    }

    @Test
    public void test_removeDataSeries_isRemovedUsingObject_invokesDataSeriesRemovedEvent() {
        // Arrange
        Project project = createProject();
        RawDataSource sut = createSut(project);

        // Act
        sut.removeDataSeries((DataSeries) sut.getDataSeries().get(0));

        // Assert
        assertThat(Arrays.asList(sutEventListeners), is(not(empty())));
        for (RawDataSourceListenerStub listener : sutEventListeners) {
            assertTrue(listener.DataSeriesRemovedIsInvoked);
            assertThat(listener.DataSeriesRemovedRawDataEvent.getIdentifier(), is(equalTo("dataSeriesRemoved")));
        }
    }

    @Test
    public void test_addLabelCategory_projectHasOnlyOneLabel_invokesLabelCategoryAddedEvent() {
        // Arrange
        numberOfLabels = 1;
        Project project = createProject();
        RawDataSource sut = createSut(project);

        // Act
        sut.addLabelCategory();

        // Assert
        assertThat(Arrays.asList(sutEventListeners), is(not(empty())));
        for (RawDataSourceListenerStub listener : sutEventListeners) {
            assertTrue(listener.LabelCategoryAddedIsInvoked);
            assertThat(listener.LabelCategoryAddedRawDataEvent.getIdentifier(), is(equalTo("labelCategoryAdded")));
        }
    }

    @Test
    public void test_addLabelCategory_always_addsLabelCategory() {
        // Arrange
        Project project = createProject();
        RawDataSource sut = createSut(project);
        int dataSeriesCount = 3;
        addDataSeries(sut, dataSeriesCount);

        // Act
        sut.addLabelCategory();

        // Assert
        assertThat(sut.getDataSeries().size(), is(equalTo(dataSeriesCount)));
        for (DataSeries dataSeries : (Vector<DataSeries>) sut.getDataSeries()) {

            assertThat(Arrays.asList(dataSeries.getVarObjects()), is(not(empty())));
            for (int idx = 0; idx < dataSeries.getVarObjects().size(); idx++) {
                Variable variable = dataSeries.getVarByIndex(idx);
                boolean[][] labelMatrix = sut.getLabelMatrix(variable);
                assertNotNull(labelMatrix);

                // + 1 is for category
                assertThat(labelMatrix.length, is(equalTo(project.getNumberOfLabels() + 1)));

                // added last in matrix for category
                boolean[] labels = labelMatrix[labelMatrix.length - 1];
                assertThat(labels.length, is(equalTo(dataSeries.getRow())));

                for (boolean label : labels) {
                    assertFalse(label);
                }
            }
        }
    }

    @Test
    public void test_changeLabelOrder_always_invokesLabelOrderChangedEvent() {
        // Arrange
        Project project = createProject();
        RawDataSource sut = createSut(project);

        // Act
        sut.changeLabelOrder();

        // Assert
        assertThat(Arrays.asList(sutEventListeners), is(not(empty())));
        for (RawDataSourceListenerStub listener : sutEventListeners) {
            assertTrue(listener.LabelOrderChangedIsInvoked);
            assertThat(listener.LabelOrderChangedRawDataEvent.getIdentifier(), is(equalTo("labelOrderChanged")));
        }
    }

    @Test
    public void test_labelNameChanged_always_invokesLabelNameChangedEvent() {
        // Arrange
        Project project = createProject();
        RawDataSource sut = createSut(project);
        NolLabel label = new NolLabel("Label 1");

        // Act
        sut.labelNameChanged(label);

        // Assert
        assertThat(Arrays.asList(sutEventListeners), is(not(empty())));
        for (RawDataSourceListenerStub listener : sutEventListeners) {
            assertTrue(listener.LabelNameChangedIsInvoked);
            assertThat(listener.LabelNameChangedRawDataEvent.getIdentifier(), is(equalTo("labelNameChanged")));
            assertThat(listener.LabelNameChangedRawDataEvent.getEventObject(), is(equalTo(label)));
        }
    }

    @Test
    public void test_labelColorChanged_always_invokesLabelColorChangedEvent() {
        // Arrange
        Project project = createProject();
        RawDataSource sut = createSut(project);
        NolLabel label = new NolLabel("Label 1");

        // Act
        sut.labelColorChanged(label);

        // Assert
        assertThat(Arrays.asList(sutEventListeners), is(not(empty())));
        for (RawDataSourceListenerStub listener : sutEventListeners) {
            assertTrue(listener.LabelColorChangedIsInvoked);
            assertThat(listener.LabelColorChangedRawDataEvent.getIdentifier(), is(equalTo("labelColorChanged")));
            assertThat(listener.LabelColorChangedRawDataEvent.getEventObject(), is(equalTo(label)));
        }
    }

    @Test
    public void test_undoLabeling_always_invokesDataPointsLabeledEvent() {
        // Arrange
        Project project = createProject();
        RawDataSource sut = createSut(project);
        Vector<Variable> expectedVariables = getDataSourceVariables(sut);

        // Act
        sut.undoLabeling();

        // Assert
        assertThat(Arrays.asList(sutEventListeners), is(not(empty())));
        for (RawDataSourceListenerStub listener : sutEventListeners) {
            assertTrue(listener.DataPointsLabeledIsInvoked);
            assertThat(listener.DataPointsLabeledRawDataEvent.getIdentifier(), is(equalTo("dataPointsLabeled")));

            // Variables are from more than one data series
            assertNull(listener.DataPointsLabeledRawDataEvent.getDataSeries());

            Vector<Variable> variables = listener.DataPointsLabeledRawDataEvent.getVarObjects();
            for (Variable expected : expectedVariables) {
                assertTrue(variables.contains(expected));
            }
        }
    }

    @Test
    public void test_redoLabeling_labelingWasNeverUndone_doesNotInvokeDataPointsLabeledEvent() {
        // Arrange
        Project project = createProject();
        RawDataSource sut = createSut(project);

        // Act
        sut.redoLabeling();

        // Assert
        assertThat(Arrays.asList(sutEventListeners), is(not(empty())));
        for (RawDataSourceListenerStub listener : sutEventListeners) {
            assertFalse(listener.DataPointsLabeledIsInvoked);
        }
    }

    @Test
    public void test_redoLabeling_wasUndonePreviously_invokesDataPointsLabeledEvent() {
        // Arrange
        Project project = createProject();
        RawDataSource sut = createSut(project);
        Vector<Variable> expectedVariables = getDataSourceVariables(sut);
        sut.undoLabeling();
        resetListeners();

        // Act
        sut.redoLabeling();

        // Assert
        assertThat(Arrays.asList(sutEventListeners), is(not(empty())));
        for (RawDataSourceListenerStub listener : sutEventListeners) {
            assertTrue(listener.DataPointsLabeledIsInvoked);
            assertThat(listener.DataPointsLabeledRawDataEvent.getIdentifier(), is(equalTo("dataPointsLabeled")));

            // Variables are from more than one data series
            assertNull(listener.DataPointsLabeledRawDataEvent.getDataSeries());

            Vector<Variable> variables = listener.DataPointsLabeledRawDataEvent.getVarObjects();
            for (Variable expected : expectedVariables) {
                assertTrue(variables.contains(expected));
            }
        }
    }

    @Test
    public void test_labelPoints_projectDoesNotHaveAnyLabels_doesNotInvokeDataPointsLabeledEvent() {
        // Arrange
        numberOfLabels = 0;
        Project project = createProject();
        RawDataSource sut = createSut(project);
        boolean[] newLabels = new boolean[]{true, false};
        int dataSeriesCount = 3;
        addDataSeries(sut, dataSeriesCount);

        assertThat(Arrays.asList(sut.getDataSeries()), is(not(empty())));
        for (DataSeries dataSeries : (Vector<DataSeries>) sut.getDataSeries()) {

            assertThat(Arrays.asList(dataSeries.getVarObjects()), is(not(empty())));
            for (Variable variable : (Vector<Variable>) dataSeries.getVarObjects()) {
                for (boolean newLabel : newLabels) {
                    // Act
                    sut.labelPoints(ANY_NUMBER, variable, newLabel);

                    // Assert
                    assertThat(Arrays.asList(sutEventListeners), is(not(empty())));
                    for (RawDataSourceListenerStub listener : sutEventListeners) {
                        assertFalse(listener.DataPointsLabeledIsInvoked);
                    }
                }
            }
        }
    }

    @Test
    public void test_labelPoints_projectHasLabels_invokesDataPointsLabeledEvent() {
        // Arrange
        Project project = createProject();
        RawDataSource sut = createSut(project);
        boolean[] newLabels = new boolean[]{true, false};
        int dataSeriesCount = 3;
        addDataSeries(sut, dataSeriesCount);

        assertThat(Arrays.asList(sut.getDataSeries()), is(not(empty())));
        for (DataSeries dataSeries : (Vector<DataSeries>) sut.getDataSeries()) {

            assertThat(Arrays.asList(dataSeries.getVarObjects()), is(not(empty())));
            for (Variable variable : (Vector<Variable>) dataSeries.getVarObjects()) {

                assertThat(Arrays.asList(project.getNumberOfLabels()), is(not(equalTo(0))));
                for (int labelNumber = 0; labelNumber < project.getNumberOfLabels(); labelNumber++) {
                    for (boolean newLabel : newLabels) {
                        // Act
                        sut.labelPoints(labelNumber, variable, newLabel);

                        // Assert
                        verifyDataPointsLabeledIsCalled(dataSeries, variable, newLabel);
                    }
                }
            }
        }
    }

    @Test
    public void test_labelPointsWithHashtable_projectDoesNotHaveAnyLabels_doesNotInvokeDataPointsLabeledEvent() {
        // Arrange
        numberOfLabels = 0;
        Project project = createProject();
        RawDataSource sut = createSut(project);
        boolean[] newLabels = new boolean[]{true, false};
        int dataSeriesCount = 3;
        addDataSeries(sut, dataSeriesCount);

        assertThat(Arrays.asList(sut.getDataSeries()), is(not(empty())));
        for (DataSeries dataSeries : (Vector<DataSeries>) sut.getDataSeries()) {

            for (boolean newLabel : newLabels) {
                Hashtable varObjsAndRowNumber = createDimensionsHashtable(dataSeries);

                // Act
                sut.labelPoints(ANY_NUMBER, varObjsAndRowNumber, newLabel);

                // Assert
                assertThat(Arrays.asList(sutEventListeners), is(not(empty())));
                for (RawDataSourceListenerStub listener : sutEventListeners) {
                    assertFalse(listener.DataPointsLabeledIsInvoked);
                }
            }
        }
    }

    @Test
    public void test_labelPointsWithDimensionsHashtable_projectHasLabels_invokesDataPointsLabeledEvent() {
        // Arrange
        Project project = createProject();
        RawDataSource sut = createSut(project);
        boolean[] newLabels = new boolean[]{true, false};
        int dataSeriesCount = 3;
        addDataSeries(sut, dataSeriesCount);

        assertThat(Arrays.asList(sut.getDataSeries()), is(not(empty())));
        for (DataSeries dataSeries : (Vector<DataSeries>) sut.getDataSeries()) {

            assertThat(Arrays.asList(project.getNumberOfLabels()), is(not(equalTo(0))));
            for (int labelNumber = 0; labelNumber < project.getNumberOfLabels(); labelNumber++) {
                for (boolean newLabel : newLabels) {
                    Hashtable varObjsAndRowNumber = createDimensionsHashtable(dataSeries);

                    // Act
                    sut.labelPoints(labelNumber, varObjsAndRowNumber, newLabel);

                    // Assert
                    assertThat(Arrays.asList(sutEventListeners), is(not(empty())));
                    for (RawDataSourceListenerStub listener : sutEventListeners) {
                        assertTrue(listener.DataPointsLabeledIsInvoked);
                        assertThat(listener.DataPointsLabeledRawDataEvent.getIdentifier(), is(equalTo("dataPointsLabeled")));
                    }
                }
            }
        }
    }

    @Test
    public void test_labelPointsWithDimensionsHashtable_projectHasLabels_modifiesLabelPoints() {
        // Arrange
        Project project = createProject();
        RawDataSource sut = createSut(project);
        boolean[] newLabels = new boolean[]{true, false};
        int dataSeriesCount = 3;
        addDataSeries(sut, dataSeriesCount);

        assertThat(Arrays.asList(sut.getDataSeries()), is(not(empty())));
        for (DataSeries dataSeries : (Vector<DataSeries>) sut.getDataSeries()) {

            Dimension dimension = createDimension(dataSeries);

            assertThat(Arrays.asList(project.getNumberOfLabels()), is(not(equalTo(0))));
            for (int labelNumber = 0; labelNumber < project.getNumberOfLabels(); labelNumber++) {
                for (boolean newLabel : newLabels) {
                    Hashtable varObjsAndRowNumber = createDimensionsHashtable(dataSeries, dimension);

                    // Act
                    sut.labelPoints(labelNumber, varObjsAndRowNumber, newLabel);

                    // Assert
                    assertThat(Arrays.asList(dataSeries.getVarObjects()), is(not(empty())));
                    for (Variable variable : (Vector<Variable>) dataSeries.getVarObjects()) {
                        boolean[][] labelMatrix = sut.getLabelMatrix(variable);
                        assertNotNull(labelMatrix);

                        boolean[] labelArray = labelMatrix[labelNumber];
                        for (int i = dimension.width; i <= dimension.height; i++) {    //dim.width: start row number; dim.height: end row number
                            assertThat(labelArray[i], is(equalTo(newLabel)));
                        }
                    }
                }
            }
        }
    }

    @Test
    public void test_labelPointsWithRowNumbersHashtable_projectHasLabels_invokesDataPointsLabeledEvent() {
        // Arrange
        Project project = createProject();
        RawDataSource sut = createSut(project);
        boolean[] newLabels = new boolean[]{true, false};
        int dataSeriesCount = 3;
        addDataSeries(sut, dataSeriesCount);

        assertThat(Arrays.asList(sut.getDataSeries()), is(not(empty())));
        for (DataSeries dataSeries : (Vector<DataSeries>) sut.getDataSeries()) {

            assertThat(Arrays.asList(project.getNumberOfLabels()), is(not(equalTo(0))));
            for (int labelNumber = 0; labelNumber < project.getNumberOfLabels(); labelNumber++) {
                for (boolean newLabel : newLabels) {
                    Hashtable varObjsAndRowNumber = createRowNumbersHashtable(dataSeries);

                    // Act
                    sut.labelPoints(labelNumber, varObjsAndRowNumber, newLabel);

                    // Assert
                    assertThat(Arrays.asList(sutEventListeners), is(not(empty())));
                    for (RawDataSourceListenerStub listener : sutEventListeners) {
                        assertTrue(listener.DataPointsLabeledIsInvoked);
                        assertThat(listener.DataPointsLabeledRawDataEvent.getIdentifier(), is(equalTo("dataPointsLabeled")));
                    }
                }
            }
        }
    }

    @Test
    public void test_labelPointsWithRowNumbersHashtable_projectHasLabels_modifiesLabelPoints() {
        // Arrange
        Project project = createProject();
        RawDataSource sut = createSut(project);
        boolean[] newLabels = new boolean[]{true, false};
        int dataSeriesCount = 3;
        addDataSeries(sut, dataSeriesCount);

        assertThat(Arrays.asList(sut.getDataSeries()), is(not(empty())));
        for (DataSeries dataSeries : (Vector<DataSeries>) sut.getDataSeries()) {

            int[] rowNumbers = createRowNumbers(dataSeries);

            assertThat(Arrays.asList(project.getNumberOfLabels()), is(not(equalTo(0))));
            for (int labelNumber = 0; labelNumber < project.getNumberOfLabels(); labelNumber++) {
                for (boolean newLabel : newLabels) {
                    Hashtable varObjsAndRowNumber = createRowNumbersHashtable(dataSeries, rowNumbers);

                    // Act
                    sut.labelPoints(labelNumber, varObjsAndRowNumber, newLabel);

                    // Assert
                    assertThat(Arrays.asList(dataSeries.getVarObjects()), is(not(empty())));
                    for (Variable variable : (Vector<Variable>) dataSeries.getVarObjects()) {
                        boolean[][] labelMatrix = sut.getLabelMatrix(variable);
                        assertNotNull(labelMatrix);

                        boolean[] labelArray = labelMatrix[labelNumber];
                        for (int i = 0; i < rowNumbers.length; i++) {    //dim.width: start row number; dim.height: end row number
                            assertThat(labelArray[rowNumbers[i]], is(equalTo(newLabel)));
                        }
                    }
                }
            }
        }
    }

    @Test
    public void test_removeLabelCategory_projectDoesNotHaveLabels_invokesLabelCategoryRemovedEvent() {
        // Arrange
        numberOfLabels = 0;
        Project project = createProject();
        RawDataSource sut = createSut(project);
        int dataSeriesCount = 3;
        addDataSeries(sut, dataSeriesCount);

        // Act
        sut.removeLabelCategory(ANY_NUMBER);

        // Assert
        assertThat(Arrays.asList(sutEventListeners), is(not(empty())));
        for (RawDataSourceListenerStub listener : sutEventListeners) {
            assertTrue(listener.LabelCategoryRemovedIsInvoked);
            assertThat(listener.LabelCategoryRemovedRawDataEvent.getIdentifier(), is(equalTo("labelCategoryRemoved")));
        }
    }

    @Test
    public void test_removeLabelCategory_projectHasLabels_invokesLabelCategoryRemovedEvent() {
        // Arrange
        Project project = createProject();
        RawDataSource sut = createSut(project);
        int dataSeriesCount = 3;
        addDataSeries(sut, dataSeriesCount);

        assertThat(Arrays.asList(project.getNumberOfLabels()), is(not(equalTo(0))));
        for (int labelNumber = project.getNumberOfLabels() - 1; labelNumber >= 0; labelNumber--) {
            // Act
            sut.removeLabelCategory(labelNumber);

            // Assert
            assertThat(Arrays.asList(sutEventListeners), is(not(empty())));
            for (RawDataSourceListenerStub listener : sutEventListeners) {
                assertTrue(listener.LabelCategoryRemovedIsInvoked);
                assertThat(listener.LabelCategoryRemovedRawDataEvent.getIdentifier(), is(equalTo("labelCategoryRemoved")));
            }
        }
    }

    @Test
    public void test_labelPointsWithRowNumbers_projectDoesNotHaveAnyLabels_doesNotInvokeDataPointsLabeledEvent() {
        // Arrange
        numberOfLabels = 0;
        Project project = createProject();
        RawDataSource sut = createSut(project);
        boolean[] newLabels = new boolean[]{true, false};
        int dataSeriesCount = 3;
        addDataSeries(sut, dataSeriesCount);

        assertThat(Arrays.asList(sut.getDataSeries()), is(not(empty())));
        for (DataSeries dataSeries : (Vector<DataSeries>) sut.getDataSeries()) {

            assertThat(Arrays.asList(dataSeries.getVarObjects()), is(not(empty())));
            for (Variable variable : (Vector<Variable>) dataSeries.getVarObjects()) {

                for (boolean newLabel : newLabels) {
                    int[] rowNumbers = createRowNumbers(dataSeries);

                    // Act
                    sut.labelPoints(ANY_NUMBER, variable, rowNumbers, newLabel);

                    // Assert
                    assertThat(Arrays.asList(sutEventListeners), is(not(empty())));
                    for (RawDataSourceListenerStub listener : sutEventListeners) {
                        assertFalse(listener.DataPointsLabeledIsInvoked);
                    }
                }
            }
        }
    }

    @Test
    public void test_labelPointsWithRowNumbers_projectHasLabels_invokesDataPointsLabeledEvent() {
        // Arrange
        Project project = createProject();
        RawDataSource sut = createSut(project);
        boolean[] newLabels = new boolean[]{true, false};
        int dataSeriesCount = 3;
        addDataSeries(sut, dataSeriesCount);

        assertThat(Arrays.asList(sut.getDataSeries()), is(not(empty())));
        for (DataSeries dataSeries : (Vector<DataSeries>) sut.getDataSeries()) {

            assertThat(Arrays.asList(project.getNumberOfLabels()), is(not(equalTo(0))));
            for (int labelNumber = 0; labelNumber < project.getNumberOfLabels(); labelNumber++) {

                assertThat(Arrays.asList(dataSeries.getVarObjects()), is(not(empty())));
                for (Variable variable : (Vector<Variable>) dataSeries.getVarObjects()) {

                    for (boolean newLabel : newLabels) {
                        int[] rowNumbers = createRowNumbers(dataSeries);

                        // Act
                        sut.labelPoints(labelNumber, variable, rowNumbers, newLabel);

                        // Assert
                        assertThat(Arrays.asList(sutEventListeners), is(not(empty())));
                        for (RawDataSourceListenerStub listener : sutEventListeners) {
                            assertTrue(listener.DataPointsLabeledIsInvoked);
                            assertThat(listener.DataPointsLabeledRawDataEvent.getIdentifier(), is(equalTo("dataPointsLabeled")));
                        }
                    }
                }
            }
        }
    }

    @Test
    public void test_labelPointsWithRowNumbers_projectHasLabels_modifiesLabelPoints() {
        // Arrange
        Project project = createProject();
        RawDataSource sut = createSut(project);
        boolean[] newLabels = new boolean[]{true, false};
        int dataSeriesCount = 3;
        addDataSeries(sut, dataSeriesCount);

        assertThat(Arrays.asList(sut.getDataSeries()), is(not(empty())));
        for (DataSeries dataSeries : (Vector<DataSeries>) sut.getDataSeries()) {

            assertThat(Arrays.asList(project.getNumberOfLabels()), is(not(equalTo(0))));
            for (int labelNumber = 0; labelNumber < project.getNumberOfLabels(); labelNumber++) {

                assertThat(Arrays.asList(dataSeries.getVarObjects()), is(not(empty())));
                for (Variable variable : (Vector<Variable>) dataSeries.getVarObjects()) {

                    for (boolean newLabel : newLabels) {
                        int[] rowNumbers = createRowNumbers(dataSeries);

                        // Act
                        sut.labelPoints(labelNumber, variable, rowNumbers, newLabel);

                        // Assert
                        boolean[][] labelMatrix = sut.getLabelMatrix(variable);
                        assertNotNull(labelMatrix);

                        boolean[] labelArray = labelMatrix[labelNumber];
                        for (int i = 0; i < rowNumbers.length; i++) {    //dim.width: start row number; dim.height: end row number
                            assertThat(labelArray[rowNumbers[i]], is(equalTo(newLabel)));
                        }
                    }
                }
            }
        }
    }

    @Test
    public void test_labelPointsWithMinMaxIndex_projectDoesNotHaveAnyLabels_doesNotInvokeDataPointsLabeledEvent() {
        // Arrange
        numberOfLabels = 0;
        Project project = createProject();
        RawDataSource sut = createSut(project);
        boolean[] newLabels = new boolean[]{true, false};
        int dataSeriesCount = 3;
        addDataSeries(sut, dataSeriesCount);

        assertThat(Arrays.asList(sut.getDataSeries()), is(not(empty())));
        for (DataSeries dataSeries : (Vector<DataSeries>) sut.getDataSeries()) {

            for (boolean newLabel : newLabels) {
                int row1 = 0;
                int row2 = dataSeries.getRow() - 1;

                // Act
                sut.labelPoints(ANY_NUMBER, dataSeries.getVarObjects(), row1, row2, newLabel);

                // Assert
                assertThat(Arrays.asList(sutEventListeners), is(not(empty())));
                for (RawDataSourceListenerStub listener : sutEventListeners) {
                    assertFalse(listener.DataPointsLabeledIsInvoked);
                }
            }
        }
    }

    @Test
    public void test_labelPointsWithMinMaxIndex_projectHasLabels_invokesDataPointsLabeledEvent() {
        // Arrange
        Project project = createProject();
        RawDataSource sut = createSut(project);
        boolean[] newLabels = new boolean[]{true, false};
        int dataSeriesCount = 3;
        addDataSeries(sut, dataSeriesCount);

        assertThat(Arrays.asList(sut.getDataSeries()), is(not(empty())));
        for (DataSeries dataSeries : (Vector<DataSeries>) sut.getDataSeries()) {

            assertThat(Arrays.asList(project.getNumberOfLabels()), is(not(equalTo(0))));
            for (int labelNumber = 0; labelNumber < project.getNumberOfLabels(); labelNumber++) {

                for (boolean newLabel : newLabels) {
                    int row1 = 0;
                    int row2 = dataSeries.getRow() - 1;

                    // Act
                    sut.labelPoints(labelNumber, dataSeries.getVarObjects(), row1, row2, newLabel);

                    // Assert
                    assertThat(Arrays.asList(sutEventListeners), is(not(empty())));
                    for (RawDataSourceListenerStub listener : sutEventListeners) {
                        assertTrue(listener.DataPointsLabeledIsInvoked);
                        assertThat(listener.DataPointsLabeledRawDataEvent.getIdentifier(), is(equalTo("dataPointsLabeled")));
                    }
                }
            }
        }
    }

    @Test
    public void test_labelPointsWithMinMaxIndex_projectHasLabels_modifiesLabelPoints() {
        // Arrange
        Project project = createProject();
        RawDataSource sut = createSut(project);
        boolean[] newLabels = new boolean[]{true, false};
        int dataSeriesCount = 3;
        addDataSeries(sut, dataSeriesCount);

        assertThat(Arrays.asList(sut.getDataSeries()), is(not(empty())));
        for (DataSeries dataSeries : (Vector<DataSeries>) sut.getDataSeries()) {

            assertThat(Arrays.asList(project.getNumberOfLabels()), is(not(equalTo(0))));
            for (int labelNumber = 0; labelNumber < project.getNumberOfLabels(); labelNumber++) {

                for (boolean newLabel : newLabels) {
                    int row1 = 0;
                    int row2 = dataSeries.getRow() - 1;

                    // Act
                    sut.labelPoints(labelNumber, dataSeries.getVarObjects(), row1, row2, newLabel);

                    // Assert
                    assertThat(Arrays.asList(dataSeries.getVarObjects()), is(not(empty())));
                    for (Variable variable : (Vector<Variable>) dataSeries.getVarObjects()) {
                        boolean[][] labelMatrix = sut.getLabelMatrix(variable);
                        assertNotNull(labelMatrix);

                        boolean[] labelArray = labelMatrix[labelNumber];
                        for (int i = row1; i <= row2; i++) {    //dim.width: start row number; dim.height: end row number
                            assertThat(labelArray[i], is(equalTo(newLabel)));
                        }
                    }
                }
            }
        }
    }

    @Test
    public void test_labelPointsAllVariablesWithRowNumbers_projectDoesNotHaveAnyLabels_doesNotInvokeDataPointsLabeledEvent() {
        // Arrange
        numberOfLabels = 0;
        Project project = createProject();
        RawDataSource sut = createSut(project);
        boolean[] newLabels = new boolean[]{true, false};
        int dataSeriesCount = 3;
        addDataSeries(sut, dataSeriesCount);

        assertThat(Arrays.asList(sut.getDataSeries()), is(not(empty())));
        for (DataSeries dataSeries : (Vector<DataSeries>) sut.getDataSeries()) {

            for (boolean newLabel : newLabels) {
                int[] rowNumbers = createRowNumbers(dataSeries);

                // Act
                sut.labelPoints(ANY_NUMBER, dataSeries.getVarObjects(), rowNumbers, newLabel);

                // Assert
                assertThat(Arrays.asList(sutEventListeners), is(not(empty())));
                for (RawDataSourceListenerStub listener : sutEventListeners) {
                    assertFalse(listener.DataPointsLabeledIsInvoked);
                }
            }
        }
    }

    @Test
    public void test_labelPointsAllVariablesWithRowNumbers_projectHasLabels_invokesDataPointsLabeledEvent() {
        // Arrange
        Project project = createProject();
        RawDataSource sut = createSut(project);
        boolean[] newLabels = new boolean[]{true, false};
        int dataSeriesCount = 3;
        addDataSeries(sut, dataSeriesCount);

        assertThat(Arrays.asList(sut.getDataSeries()), is(not(empty())));
        for (DataSeries dataSeries : (Vector<DataSeries>) sut.getDataSeries()) {

            assertThat(Arrays.asList(project.getNumberOfLabels()), is(not(equalTo(0))));
            for (int labelNumber = 0; labelNumber < project.getNumberOfLabels(); labelNumber++) {

                for (boolean newLabel : newLabels) {
                    int[] rowNumbers = createRowNumbers(dataSeries);

                    // Act
                    sut.labelPoints(labelNumber, dataSeries.getVarObjects(), rowNumbers, newLabel);

                    // Assert
                    assertThat(Arrays.asList(sutEventListeners), is(not(empty())));
                    for (RawDataSourceListenerStub listener : sutEventListeners) {
                        assertTrue(listener.DataPointsLabeledIsInvoked);
                        assertThat(listener.DataPointsLabeledRawDataEvent.getIdentifier(), is(equalTo("dataPointsLabeled")));
                    }
                }
            }
        }
    }

    @Test
    public void test_labelPointsAllVariablesWithRowNumbers_projectHasLabels_modifiesLabelPoints() {
        // Arrange
        Project project = createProject();
        RawDataSource sut = createSut(project);
        boolean[] newLabels = new boolean[]{true, false};
        int dataSeriesCount = 3;
        addDataSeries(sut, dataSeriesCount);

        assertThat(Arrays.asList(sut.getDataSeries()), is(not(empty())));
        for (DataSeries dataSeries : (Vector<DataSeries>) sut.getDataSeries()) {

            assertThat(Arrays.asList(project.getNumberOfLabels()), is(not(equalTo(0))));
            for (int labelNumber = 0; labelNumber < project.getNumberOfLabels(); labelNumber++) {

                for (boolean newLabel : newLabels) {
                    int[] rowNumbers = createRowNumbers(dataSeries);

                    // Act
                    sut.labelPoints(labelNumber, dataSeries.getVarObjects(), rowNumbers, newLabel);

                    // Assert
                    assertThat(Arrays.asList(dataSeries.getVarObjects()), is(not(empty())));
                    for (Variable variable : (Vector<Variable>) dataSeries.getVarObjects()) {

                        boolean[][] labelMatrix = sut.getLabelMatrix(variable);
                        assertNotNull(labelMatrix);

                        boolean[] labelArray = labelMatrix[labelNumber];
                        for (int i = 0; i < rowNumbers.length; i++) {    //dim.width: start row number; dim.height: end row number
                            assertThat(labelArray[rowNumbers[i]], is(equalTo(newLabel)));
                        }
                    }
                }
            }
        }
    }

    @Test
    public void test_getPointLabels_labelMatrixDoesNotExist_returnsNewBooleanArray() {
        // Arrange
        Project project = createProject();
        RawDataSource sut = createSut(project);

        assertThat(Arrays.asList(sut.getDataSeries()), is(not(empty())));
        for (DataSeries dataSeries : (Vector<DataSeries>) sut.getDataSeries()) {

            assertThat(Arrays.asList(dataSeries.getVarObjects()), is(not(empty())));
            for (Variable variable : (Vector<Variable>) dataSeries.getVarObjects()) {

                for (int rowNumber = 0; rowNumber < dataSeries.getRow(); rowNumber++) {
                    // Act
                    boolean[] pointLabels = sut.getPointLabels(variable, rowNumber);

                    // Assert
                    assertNotNull(pointLabels);
                    assertThat(pointLabels.length, is(equalTo(project.getNumberOfLabels())));
                    for (int idx = 0; idx < pointLabels.length; idx++) {
                        assertFalse(pointLabels[idx]);
                    }
                }
            }
        }
    }

    @Test
    public void test_getPointLabels_labelMatrixExists_returnsLabelMatrixOfGivenPoint() {
        // Arrange
        Project project = createProject();
        RawDataSource sut = createSut(project);
        int dataSeriesCount = 3;
        addDataSeries(sut, dataSeriesCount);

        assertThat(Arrays.asList(sut.getDataSeries()), is(not(empty())));
        for (DataSeries dataSeries : (Vector<DataSeries>) sut.getDataSeries()) {

            // Setting random labelPoints
            boolean[][] expectedLabelMatrix = createLabelMatrix(dataSeries, project.getNumberOfLabels());
            assertThat(project.getNumberOfLabels(), is(not(equalTo(0))));
            for (int labelNumber = 0; labelNumber < project.getNumberOfLabels(); labelNumber++) {

                assertThat(Arrays.asList(dataSeries.getVarObjects()), is(not(empty())));
                for (Variable variable : (Vector<Variable>) dataSeries.getVarObjects()) {
                    sut.labelPoints(labelNumber, variable, expectedLabelMatrix[labelNumber][0]);
                }
            }

            assertThat(Arrays.asList(dataSeries.getVarObjects()), is(not(empty())));
            for (Variable variable : (Vector<Variable>) dataSeries.getVarObjects()) {

                for (int rowNumber = 0; rowNumber < dataSeries.getRow(); rowNumber++) {
                    // Act
                    boolean[] pointLabels = sut.getPointLabels(variable, rowNumber);

                    // Assert
                    assertNotNull(pointLabels);
                    assertThat(pointLabels.length, is(equalTo(project.getNumberOfLabels())));
                    for (int idx = 0; idx < pointLabels.length; idx++) {
                        assertThat(pointLabels[idx], is(equalTo(expectedLabelMatrix[idx][rowNumber])));
                    }
                }
            }
        }
    }

    @Test
    public void test_getSelectStatus_always_returnsSelectionStatus() {
        // Arrange
        Project project = createProject();
        RawDataSource sut = createSut(project);
        boolean[] statuses = new boolean[]{true, false};

        for (boolean status : statuses) {
            // Act
            sut.setSelectStatus(status);

            // Assert
            assertThat(sut.getSelectStatus(), is(equalTo(status)));
        }
    }

    @Test
    public void test_setTimeStamps_always_invokesSetTimeStampsEvent() {
        // Arrange
        Project project = createProject();
        RawDataSource sut = createSut(project);

        assertThat(Arrays.asList(sut.getDataSeries()), is(not(empty())));
        for (DataSeries dataSeries : (Vector<DataSeries>)sut.getDataSeries()) {
            // Act
            sut.setTimeStamps(dataSeries);

            // Assert
            assertThat(Arrays.asList(project.getPreprocessors()), is(not(empty())));
            for (Preprocessor preprocessor : (Vector<Preprocessor>)project.getPreprocessors()) {
                verify(preprocessor).setTimeStamps(dataSeries);
            }
        }
    }

    private boolean[][] createLabelMatrix(DataSeries dataSeries, int numberOfLabels) {
        boolean[][] labelMatrix = new boolean[numberOfLabels][dataSeries.getRow()];
        boolean value = false;

        for (int labelNumber = 0; labelNumber < numberOfLabels; labelNumber++) {
            value = !value;
            for (int row = 0; row < dataSeries.getRow(); row++) {
                labelMatrix[labelNumber][row] = value;
            }
        }

        return labelMatrix;
    }

    private void addDataSeries(RawDataSource dataSource, int dataSeriesCount) {
        dataSource.setDataSeries(new Vector<DataSeries>());
        for (int idx = 1; idx <= dataSeriesCount; idx++) {
            dataSource.addDataSeries(createDataSeries(rows, cols, getDataSeriesName(idx)));
        }
    }

    private void cleanUpStreams() {
        System.setOut(null);
    }

    private Dimension createDimension(DataSeries dataSeries) {
        Dimension dimension = new Dimension();
        dimension.width = 0;
        dimension.height = dataSeries.getRow() - 1;

        return dimension;
    }

    private Hashtable createDimensionsHashtable(DataSeries dataSeries) {
        Dimension dimension = createDimension(dataSeries);
        return createDimensionsHashtable(dataSeries, dimension);
    }

    private Hashtable createDimensionsHashtable(DataSeries dataSeries, Dimension dimension) {
        Hashtable hashtable = new Hashtable();

        for (Variable variable : (Vector<Variable>) dataSeries.getVarObjects()) {
            hashtable.put(variable, dimension);
        }

        return hashtable;
    }

    private int[] createRowNumbers(DataSeries dataSeries) {
        int[] rowNumbers = new int[dataSeries.getRow()];
        for (int idx = 0; idx < rowNumbers.length; idx++) {
            rowNumbers[idx] = idx;
        }

        return rowNumbers;
    }

    private Hashtable createRowNumbersHashtable(DataSeries dataSeries) {
        int[] rowNumbers = createRowNumbers(dataSeries);
        return createRowNumbersHashtable(dataSeries, rowNumbers);
    }

    private Hashtable createRowNumbersHashtable(DataSeries dataSeries, int[] rowNumbers) {
        Hashtable hashtable = new Hashtable();

        for (Variable variable : (Vector<Variable>) dataSeries.getVarObjects()) {
            hashtable.put(variable, rowNumbers);
        }

        return hashtable;
    }

    private long[] createTimes() {
        return createTimes(System.currentTimeMillis());
    }

    private long[] createTimes(long baseTime) {
        long[] times = new long[10];

        for (int idx = 0; idx < times.length; idx++) {
            times[idx] = baseTime + (idx * 1000);
        }

        return times;
    }

    private DataSeries createDataSeries(int rows, int cols, String name) {
        DataSeries dataSeries = new DataSeries(rows, cols);

        dataSeries.setName(name);
        dataSeries.setDataMatrix(createMatrix(rows, cols));

        return dataSeries;
    }

    private Vector createDataSeriesVector(DataSeries... dataSeries) {
        Vector<DataSeries> dataSeriesList = new Vector<>();

        for (int idx = 0; idx < dataSeries.length; idx++) {
            dataSeriesList.add(dataSeries[idx]);
        }

        return dataSeriesList;
    }

    private RawDataSourceListenerStub createRawDataSourceListener() {
        RawDataSourceListenerStub listener = new RawDataSourceListenerStub();
        return listener;
    }

    private String createLabel(int idx) {
        return "Label " + idx;
    }

    private Matrix createMatrix(int rows, int cols) {
        Matrix data = Matlib.createMatrix(rows, cols);

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                data.set(r, c, randomGenerator.nextDouble());
            }
        }

        return data;
    }

    private Project createProject() {
        Vector<String> labels = new Vector<>();

        for (int idx = 1; idx <= numberOfLabels; idx++) {
            labels.add(createLabel(idx));
        }

        Project project = mock(Project.class);

        when(project.getLabels()).thenReturn(labels);
        when(project.getNumberOfLabels()).thenReturn(labels.size());
        Vector<Preprocessor> preprocessors = createPreprocessors();
        when(project.getPreprocessors()).thenReturn(preprocessors);

        return project;
    }

    private Vector<Preprocessor> createPreprocessors() {
        Vector<Preprocessor> preprocessors = new Vector<Preprocessor>();

        preprocessors.add(createPreprocessor());
        preprocessors.add(createPreprocessor());
        preprocessors.add(createPreprocessor());

        return preprocessors;
    }

    private Preprocessor createPreprocessor() {
        Preprocessor preprocessor = mock(Preprocessor.class);
        return preprocessor;
    }

    private RawDataSource createSut(Project project) {
        RawDataSource dataSource = new RawDataSource(project);
        int rows = 3, cols = 4;

        dataSource.setDataSeries(createDataSeriesVector(
                createDataSeries(rows, cols, getDataSeriesName(1)),
                createDataSeries(rows, cols, getDataSeriesName(2)),
                createDataSeries(rows, cols, getDataSeriesName(3))));

        sutEventListeners = new Vector<>();
        for (int idx = 0; idx < 3; idx++) {
            RawDataSourceListenerStub rawDataSourceListener = createRawDataSourceListener();
            sutEventListeners.addElement(rawDataSourceListener);
            dataSource.addListener(rawDataSourceListener);
        }

        return dataSource;
    }

    private String getDataSeriesName(int id) {
        return "Data Series " + id;
    }

    private Vector<Variable> getDataSourceVariables(RawDataSource dataSource) {
        Vector<Variable> variables = new Vector<Variable>();

        for (DataSeries dataSeries : (Vector<DataSeries>) dataSource.getDataSeries()) {
            for (Variable variable : (Vector<Variable>) dataSeries.getVarObjects()) {
                variables.addElement(variable);
            }
        }

        return variables;
    }

    private void resetListeners() {
        for (RawDataSourceListenerStub listener : sutEventListeners) {
            listener.DataPointsLabeledIsInvoked = false;
            listener.DataPointsLabeledRawDataEvent = null;
        }
    }

    private void setupStreams() {
        System.setOut(new PrintStream(outContent));
    }

    private void verifyDataPointsLabeledIsCalled(DataSeries dataSeries, Variable variable, boolean newLabel) {
        assertThat(Arrays.asList(sutEventListeners), is(not(empty())));
        for (RawDataSourceListenerStub listener : sutEventListeners) {
            assertTrue(listener.DataPointsLabeledIsInvoked);
            assertThat(listener.DataPointsLabeledRawDataEvent.getIdentifier(), is(equalTo("dataPointsLabeled")));

            assertThat(listener.DataPointsLabeledRawDataEvent.getDataSeries(), is(equalTo(dataSeries)));

            Vector<Variable> variables = listener.DataPointsLabeledRawDataEvent.getVarObjects();
            assertThat(variables.size(), is(equalTo(1)));
            assertThat(variables.firstElement(), is(equalTo(variable)));
        }
    }
}