package com.gensym.nols.data;

import org.junit.After;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.TemporaryFolder;

import java.awt.*;
import java.io.*;
import java.text.DateFormat;
import java.time.format.DateTimeFormatter;
import java.util.Arrays;
import java.util.Objects;
import java.util.Random;
import java.util.Vector;
import java.util.zip.GZIPInputStream;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.collection.IsEmptyCollection.empty;
import static org.hamcrest.core.Is.is;
import static org.hamcrest.core.IsEqual.equalTo;
import static org.hamcrest.core.IsNot.not;
import static org.junit.Assert.*;
import static org.mockito.Mockito.verify;
import static org.powermock.api.mockito.PowerMockito.mock;
import static org.powermock.api.mockito.PowerMockito.when;

public class ProjectTest {
    private final static String FILENAME = "fileformat.fmt";
    private final static Color[] colors = new Color[]{Color.BLACK, Color.BLUE, Color.CYAN, Color.DARK_GRAY, Color.GRAY, Color.GREEN, Color.LIGHT_GRAY, Color.MAGENTA, Color.ORANGE, Color.PINK, Color.RED};
    private final static Random randomGenearator = new Random();

    @Rule
    public TemporaryFolder temporaryFolder = new TemporaryFolder();

    private boolean setRawDataSource;
    private RawDataSource projectRawDataSource;
    private String fileDirectory;
    private Vector<ProjectListenerStub> projectListeners;

    @Before
    public void before() throws Exception {
        setRawDataSource = true;
        fileDirectory = temporaryFolder.newFolder().getAbsolutePath();
    }

    @After
    public void after() throws Exception {
        File file = new File(fileDirectory + "\\" + FILENAME);
        if (file.exists()) {
            file.delete();
        }

        temporaryFolder.delete();
    }

    @Test
    public void test_getName_always_returnsName() throws Exception {
        // Arrange
        String name = "Project Name";
        Project sut = createProject(name);

        // Act & Assert
        assertThat(sut.getName(), is(equalTo(name)));
    }

    @Test
    public void test_setName_always_setsProjectName() throws Exception {
        // Arrange
        String name = "Project Name";
        Project sut = createProject();

        // Act
        sut.setName(name);

        // Assert
        assertThat(sut.getName(), is(equalTo(name)));
    }

    @Test
    public void test_setComment_always_setsProjectComment() throws Exception {
        // Arrange
        String comment = "Project Comment";
        Project sut = createProject();

        // Act
        sut.setComment(comment);

        // Assert
        assertThat(sut.getComment(), is(equalTo(comment)));
    }

    @Test
    public void test_makeUniqueNameForVariable_always_returnsUniqueNameForVariable() throws Exception {
        // Arrange
        Project sut = createProject();
        int maxVariableCounter = getMaxVariableCounter(sut);

        for (int i = 1; i <= 3; i++) {
            // Act
            String variableName = sut.makeUniqueNameForVariable();

            // Assert
            assertThat(variableName, is(equalTo("Var" + (maxVariableCounter + i))));
        }
    }

    @Test
    public void test_getCustomTimeFormats_customTimeFormatsDoesNotExist_returnsEmptyCustomTimeFormatsList() throws Exception {
        // Arrange
        Project sut = createProject();

        // Act
        Vector<DateFormat> timeFormats = sut.getCustomTimeFormats();

        // Assert
        assertThat(timeFormats.size(), is(equalTo(0)));
    }

    @Test
    public void test_setCustomTimeFormats_customTimeFormatsExist_returnsCustomTimeFormatsList() throws Exception {
        // Arrange
        Project sut = createProject();
        Vector<DateTimeFormatter> customTimeFormats = new Vector<>();
        customTimeFormats.add(DateTimeFormatter.ofPattern("HH:mm"));
        customTimeFormats.add(DateTimeFormatter.ofPattern("HH:mm:ss"));
        customTimeFormats.add(DateTimeFormatter.ofPattern("hh:mm:ss"));

        // Act
        sut.setCustomTimeFormats(customTimeFormats);

        // Assert
        Vector<DateTimeFormatter> timeFormats = sut.getCustomTimeFormats();
        for (DateTimeFormatter customTimeFormat : customTimeFormats) {
            assertTrue(timeFormats.contains(customTimeFormat));
        }
    }

    @Test
    public void test_getCustomDateFormats_customDateFormatsDoesNotExist_returnsEmptyCustomDateFormatsList() throws Exception {
        // Arrange
        Project sut = createProject();

        // Act
        Vector<DateFormat> dateFormats = sut.getCustomDateFormats();

        // Assert
        assertThat(dateFormats.size(), is(equalTo(0)));
    }

    @Test
    public void test_setCustomDateFormats_customDateFormatsExist_returnsCustomDateFormatsList() throws Exception {
        // Arrange
        Project sut = createProject();
        Vector<DateTimeFormatter> customDateFormats = new Vector<>();
        customDateFormats.add(DateTimeFormatter.ofPattern("dd/MM/yyyy"));
        customDateFormats.add(DateTimeFormatter.ofPattern("MM/dd/yyyy"));
        customDateFormats.add(DateTimeFormatter.ofPattern("yyyy/MM/dd"));

        // Act
        sut.setCustomDateFormats(customDateFormats);

        // Assert
        Vector dateFormats = sut.getCustomDateFormats();
        for (DateTimeFormatter customDateFormat : customDateFormats) {
            assertTrue(dateFormats.contains(customDateFormat));
        }
    }

    @Test
    public void test_getCustomDateTimeFormats_customDateTimeFormatsDoesNotExist_returnsEmptyCustomDateTimeFormatsList() throws Exception {
        // Arrange
        Project sut = createProject();

        // Act
        Vector dateTimeFormats = sut.getCustomDateTimeFormats();

        // Assert
        assertThat(dateTimeFormats.size(), is(equalTo(0)));
    }

    @Test
    public void test_setCustomDateTimeFormats_customDateTimeFormatsExist_returnsCustomDateTimeFormatsList() throws Exception {
        // Arrange
        Project sut = createProject();
        Vector<DateTimeFormatter> customDateTimeFormats = new Vector<>();
        customDateTimeFormats.add(DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm"));
        customDateTimeFormats.add(DateTimeFormatter.ofPattern("MM/dd/yyyy HH:mm:ss"));
        customDateTimeFormats.add(DateTimeFormatter.ofPattern("yyyy/MM/dd hh:mm:ss"));

        // Act
        sut.setCustomDateTimeFormats(customDateTimeFormats);

        // Assert
        Vector dateTimeFormats = sut.getCustomDateTimeFormats();
        for (DateTimeFormatter customDateTimeFormat : customDateTimeFormats) {
            assertTrue(dateTimeFormats.contains(customDateTimeFormat));
        }
    }

    @Test
    public void test_getDataSeriesFileFormat_dataSeriesFileFormatExists_returnsDataSeriesFileFormat() throws Exception {
        // Arrange
        Project sut = createProject();
        int dataSeriesFileFormatsCount = 3;
        Vector<DataSeriesFileFormat> dataSeriesFileFormats = new Vector<>();
        for (int i = 0; i < dataSeriesFileFormatsCount; i++) {
            dataSeriesFileFormats.add(createDataSeriesFileFormat("Name " + (i + 1)));
            sut.setDataSeriesFileFormat(dataSeriesFileFormats.lastElement());
        }

        for (DataSeriesFileFormat dataSeriesFileFormat : dataSeriesFileFormats) {
            // Act & Assert
            assertThat(sut.getDataSeriesFileFormat(dataSeriesFileFormat.getName()), is(equalTo(dataSeriesFileFormat)));
        }
    }

    @Test
    public void test_setDataSeriesFileFormat_dataSeriesFileFormatDoesNotExist_addsFileFormat() throws Exception {
        // Arrange
        Project sut = createProject();
        int dataSeriesFileFormatsCount = 3;
        Vector<DataSeriesFileFormat> dataSeriesFileFormats = new Vector<>();
        for (int i = 0; i < dataSeriesFileFormatsCount; i++) {
            dataSeriesFileFormats.add(createDataSeriesFileFormat("Name " + (i + 1)));
        }

        // Act
        for (DataSeriesFileFormat dataSeriesFileFormat : dataSeriesFileFormats) {
            sut.setDataSeriesFileFormat(dataSeriesFileFormat);
        }

        // Assert
        assertThat(sut.getNumberOfDataSeriesFileFormat(), is(equalTo(dataSeriesFileFormatsCount)));
        Vector sutDataSeriesFileFormats = sut.getDataSeriesFileFormats();
        for (DataSeriesFileFormat dataSeriesFileFormat : dataSeriesFileFormats) {
            assertTrue(sutDataSeriesFileFormats.contains(dataSeriesFileFormat));
        }
    }

    @Test
    public void test_setDataSeriesFileFormat_dataSeriesFileFormatAlreadyExists_overridesFileFormat() throws Exception {
        // Arrange
        Project sut = createProject();
        DataSeriesFileFormat dataSeriesFileFormat1 = createDataSeriesFileFormat("Name 1");
        DataSeriesFileFormat dataSeriesFileFormat2 = createDataSeriesFileFormat("Name 1");
        sut.setDataSeriesFileFormat(dataSeriesFileFormat1);

        // Act
        sut.setDataSeriesFileFormat(dataSeriesFileFormat2);

        // Assert
        Vector dataSeriesFileFormats = sut.getDataSeriesFileFormats();
        assertFalse(dataSeriesFileFormats.contains(dataSeriesFileFormat1));
        assertTrue(dataSeriesFileFormats.contains(dataSeriesFileFormat2));
    }

    @Test
    public void test_setDataSeriesFileFormat_always_invokesDataFileFormatSettedEventIsInvoked() throws Exception {
        // Arrange
        Project sut = createProject();
        DataSeriesFileFormat dataSeriesFileFormat = createDataSeriesFileFormat("Name 1");

        // Act
        sut.setDataSeriesFileFormat(dataSeriesFileFormat);

        // Assert
        assertThat(Arrays.asList(projectListeners), is(not(empty())));
        for (ProjectListenerStub projectListener : projectListeners) {
            assertTrue(projectListener.DataFileFormatSettedIsInvoked);
            assertThat(projectListener.DataFileFormatSettedEvent.getIdentifier(), is(equalTo("dataFileFormatSetted")));
        }
    }

    @Test
    public void test_removeDataSeriesFileFormat_always_removesDataSeriesFileFormat() throws Exception {
        // Arrange
        Project sut = createProject();
        DataSeriesFileFormat dataSeriesFileFormat1 = createDataSeriesFileFormat("Name 1");
        DataSeriesFileFormat dataSeriesFileFormat2 = createDataSeriesFileFormat("Name 2");
        sut.setDataSeriesFileFormat(dataSeriesFileFormat1);
        sut.setDataSeriesFileFormat(dataSeriesFileFormat2);

        // Act
        sut.removeDataSeriesFileFormat(dataSeriesFileFormat1);

        // Assert
        Vector dataSeriesFileFormats = sut.getDataSeriesFileFormats();
        assertFalse(dataSeriesFileFormats.contains(dataSeriesFileFormat1));
        assertTrue(dataSeriesFileFormats.contains(dataSeriesFileFormat2));
    }

    @Test
    public void test_removeDataSeriesFileFormat_always_invokesDataFileFormatRemovedEventIsInvoked() throws Exception {
        // Arrange
        Project sut = createProject();
        DataSeriesFileFormat dataSeriesFileFormat = createDataSeriesFileFormat("Name 1");
        sut.setDataSeriesFileFormat(dataSeriesFileFormat);

        // Act
        sut.removeDataSeriesFileFormat(dataSeriesFileFormat);

        // Assert
        assertThat(Arrays.asList(projectListeners), is(not(empty())));
        for (ProjectListenerStub projectListener : projectListeners) {
            assertTrue(projectListener.DataFileFormatRemovedIsInvoked);
            assertThat(projectListener.DataFileFormatRemovedEvent.getIdentifier(), is(equalTo("dataFileFormatRemoved")));
        }
    }

    @Test
    public void test_removeDataSeriesFileFormat_dataSeriesFileFormatDoesNotExist_doesNotRemoveDataSeriesFileFormat() throws Exception {
        // Arrange
        Project sut = createProject();
        DataSeriesFileFormat dataSeriesFileFormat1 = createDataSeriesFileFormat("Name 1");
        DataSeriesFileFormat dataSeriesFileFormat2 = createDataSeriesFileFormat("Name 2");
        DataSeriesFileFormat dataSeriesFileFormat3 = createDataSeriesFileFormat("Name 3");
        sut.setDataSeriesFileFormat(dataSeriesFileFormat1);
        sut.setDataSeriesFileFormat(dataSeriesFileFormat2);

        // Act
        sut.removeDataSeriesFileFormat(dataSeriesFileFormat3);

        // Assert
        Vector dataSeriesFileFormats = sut.getDataSeriesFileFormats();
        assertTrue(dataSeriesFileFormats.contains(dataSeriesFileFormat1));
        assertTrue(dataSeriesFileFormats.contains(dataSeriesFileFormat2));
    }

    @Test
    public void test_addProcessedDataSeries_dataSeriesIsNotAlreadyAdded_addsDataSeries() throws Exception {
        // Arrange
        Project sut = createProject();
        DataSeries dataSeries = createDataSeries("DataSeries 1");

        // Act
        sut.addProcessedDataSeries(dataSeries);

        // Assert
        Vector processedData = sut.getProcessedData();
        assertTrue(processedData.contains(dataSeries));
    }

    @Test
    public void test_addProcessedDataSeries_dataSeriesIsAlreadyAdded_doesNotAddSameDataSeries() throws Exception {
        // Arrange
        Project sut = createProject();
        DataSeries dataSeries = createDataSeries("DataSeries 1");
        sut.addProcessedDataSeries(dataSeries);
        int processedDataSeriesCount = sut.getProcessedData().size();

        // Act
        sut.addProcessedDataSeries(dataSeries);

        // Assert
        assertThat(sut.getProcessedData().size(), is(equalTo(processedDataSeriesCount)));
    }

    @Test
    public void test_removeProcessedDataSeries_dataSeriesDoesNotExist_doesNotRemoveAnyProcessedData() throws Exception {
        // Arrange
        Project sut = createProject();
        DataSeries dataSeries = createDataSeries("DataSeries 1");
        sut.addProcessedDataSeries(dataSeries);
        int processedDataSeriesCount = sut.getProcessedData().size();
        DataSeries dataSeries2 = createDataSeries("DataSeries 2");

        // Act
        sut.removeProcessedDataSeries(dataSeries2);

        // Assert
        assertThat(sut.getProcessedData().size(), is(equalTo(processedDataSeriesCount)));
    }

    @Test
    public void test_removeProcessedDataSeries_dataSeriesExist_removesProcessedDataSeries() throws Exception {
        // Arrange
        Project sut = createProject();
        DataSeries dataSeries = createDataSeries("DataSeries 1");
        sut.addProcessedDataSeries(dataSeries);

        // Act
        sut.removeProcessedDataSeries(dataSeries);

        // Assert
        assertFalse(sut.getProcessedData().contains(dataSeries));
    }

    @Test
    public void test_removeProcessedDataSeries_dataSeriesDoesNotExist_doesNotRemoveProcessedDataSeries() throws Exception {
        // Arrange
        Project sut = createProject();
        DataSeries dataSeries = createDataSeries("DataSeries 1");
        DataSeries dataSeries2 = createDataSeries("DataSeries 2");
        sut.addProcessedDataSeries(dataSeries);

        // Act
        sut.removeProcessedDataSeries(dataSeries2);

        // Assert
        assertTrue(sut.getProcessedData().contains(dataSeries));
    }

    @Test
    public void test_getProcessedDataByPreprocessor_dataSeriesFoundAgainstPreprocessor_returnsAllDataSeries() throws Exception {
        // Arrange
        Project sut = createProject();
        Preprocessor preprocessor = createPreprocessor();
        Vector<DataSeries> dataSeriesList = new Vector<>();
        dataSeriesList.add(createDataSeries("DataSeries 1", preprocessor));
        dataSeriesList.add(createDataSeries("DataSeries 2", preprocessor));
        dataSeriesList.add(createDataSeries("DataSeries 3", createPreprocessor()));
        for (DataSeries dataSeries : dataSeriesList) {
            sut.addProcessedDataSeries(dataSeries);
        }

        // Act
        Vector processedDataList = sut.getProcessedDataByPreprocessor(preprocessor);

        // Assert
        assertTrue(processedDataList.contains(dataSeriesList.get(0)));
        assertTrue(processedDataList.contains(dataSeriesList.get(1)));
        assertFalse(processedDataList.contains(dataSeriesList.get(2)));
    }

    @Test
    public void test_getLabel_labelExists_returnsLabel() throws Exception {
        // Arrange
        Project sut = createProject();
        addProjectLabels(sut);

        for (int idx = 0; idx < sut.getLabels().size(); idx++) {
            // Act
            NolLabel label = sut.getLabel(idx);

            // Assert
            assertThat(label, is(equalTo(sut.getLabels().get(idx))));
        }
    }

    @Test
    public void test_getLabel_labelDoesNotExist_returnsNull() throws Exception {
        // Arrange
        Project sut = createProject();
        addProjectLabels(sut);

        // Act
        NolLabel label = sut.getLabel(sut.getLabels().size());

        // Assert
        assertNull(label);
    }

    @Test
    public void test_getNumberOfLabels_always_returnsLabelsCount() throws Exception {
        // Arrange
        Project sut = createProject();

        for (int labelsCount = 1; labelsCount <= 5; labelsCount++) {
            sut.addLabelCategory("Name " + labelsCount, "Comment " + labelsCount, colors[labelsCount]);

            // Act
            int numberOfLabels = sut.getNumberOfLabels();

            // Assert
            assertThat(numberOfLabels, is(equalTo(labelsCount)));
        }
    }

    @Test
    public void test_getLabelIndexByLabel_always_returnsIndexOfLabel() throws Exception {
        // Arrange
        Project sut = createProject();
        addProjectLabels(sut);
        Vector<NolLabel> sutLabels = (Vector<NolLabel>)sut.getLabels();

        assertThat(Arrays.asList(sutLabels), is(not(empty())));
        for (int i = 0; i < sutLabels.size(); i++) {
            // Act & Assert
            assertThat(sut.getLabelIndex(sutLabels.get(i)), is(equalTo(i)));
        }
    }

    @Test
    public void test_getTopLabelIndex_labelWithZeroOrderExists_returnsTopLabelIndex() throws Exception {
        // Arrange
        Project sut = createProject();
        addProjectLabels(sut);

        // Act
        int topLabelIndex = sut.getTopLabelIndex();

        // Assert
        Vector<NolLabel> labels = sut.getLabels();
        int idx = 0;
        for (; idx < labels.size(); idx++) {
            NolLabel label = labels.get(idx);
            if (label.getLabelOrder() == 0) {
                break;
            }
        }

        assertThat(topLabelIndex, is(equalTo(idx)));
    }

    @Test
    public void test_getTopLabelIndex_labelWithZeroOrderDoesNotExist_returnsMinusOne() throws Exception {
        // Arrange
        Project sut = createProject();
        addProjectLabels(sut);
        sut.changeLabelOrder(new int[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

        // Act
        int topLabelIndex = sut.getTopLabelIndex();

        // Assert
        assertThat(topLabelIndex, is(equalTo(-1)));
    }

    @Test
    public void test_getLabelColor_always_returnsTopLabelColor() throws Exception {
        // Arrange
        Project sut = createProject();
        addProjectLabels(sut);

        Vector<NolLabel> labels = (Vector<NolLabel>) sut.getLabels();
        for (int idx = 1; idx <= labels.size(); idx++) {
            boolean[] labelArray = new boolean[sut.getLabels().size()];

            for (int j = 0; j < idx; j++) {
                labelArray[j] = true;
            }

            // Act
            Color color = sut.getLabelColor(labelArray);

            // Assert
            int index = -1;
            int order = Integer.MAX_VALUE;
            for (int j = 0; j < labels.size(); j++) {
                if (labelArray[j]) {
                    NolLabel label = labels.elementAt(j);
                    int labelOrder = label.getLabelOrder();
                    if (labelOrder < order) {
                        index = j;
                        order = labelOrder;
                    }
                }
            }

            assertThat(color, is(equalTo(labels.get(index).getLabelColor())));
        }
    }

    @Test
    public void test_getLabelColor_allFlagsAreFalse_returnsWhiteColor() throws Exception {
        // Arrange
        Project sut = createProject();
        addProjectLabels(sut);

        // Act
        Color color = sut.getLabelColor(new boolean[sut.getLabels().size()]);

        // Assert
        assertThat(color, is(equalTo(Color.WHITE)));
    }

    @Test
    public void test_getLabelColor_labelArraySizeIsDifferentThanNumberOfLabels_returnsWhite() throws Exception {
        // Arrange
        Project sut = createProject();
        addProjectLabels(sut);
        boolean[] labelArray = new boolean[sut.getLabels().size() - 1];

        // Act & Assert
        assertThat(sut.getLabelColor(labelArray), is(equalTo(Color.WHITE)));
    }

    @Test
    public void test_addLabelCategory_newLabelIsAdded_addsLabelCategoryAndReturnsIndex() throws Exception {
        // Arrange
        Project sut = createProject();
        for (int idx = 0; idx < 10; idx++) {
            String labelName = "Label Name " + idx;
            String comment = "Comment " + idx;
            Color labelColor = colors[idx];

            // Act
            int labelCategoryIndex = sut.addLabelCategory(labelName, comment, labelColor);

            // Assert
            assertThat(labelCategoryIndex, is(equalTo(idx)));
        }
    }

    @Test
    public void test_addLabelCategory_sameLabelIsAdded_returnsExistingLabelIndex() throws Exception {
        // Arrange
        Project sut = createProject();
        for (int idx = 0; idx < 10; idx++) {
            String labelName = "Label Name " + idx;
            String comment = "Comment " + idx;
            Color labelColor = colors[idx];
            int existingLabelIndex = sut.addLabelCategory(labelName, comment, labelColor);

            // Act
            int labelIndex = sut.addLabelCategory(labelName, comment, labelColor);

            // Assert
            assertThat(labelIndex, is(equalTo(existingLabelIndex)));
        }
    }

    @Test
    public void test_removeLabelCategory_always_removesLabel() throws Exception {
        // Arrange
        Project sut = createProject();
        addProjectLabels(sut);
        Vector clonedLabels = cloneLabels(sut.getLabels());
        int labelIndexToBeRemoved = clonedLabels.size() / 2;
        Object label = clonedLabels.get(labelIndexToBeRemoved);

        // Act
        sut.removeLabelCategory(sut.getLabel(labelIndexToBeRemoved));

        // Assert
        Vector sutLabels = sut.getLabels();
        assertFalse(sutLabels.contains(label));
    }

    @Test
    public void test_removeLabelCategory_always_updatesLabelOrders() throws Exception {
        // Arrange
        Project sut = createProject();
        addProjectLabels(sut);
        Vector<NolLabel> existingLabels = cloneLabels(sut.getLabels());
        int labelIndexToBeRemoved = existingLabels.size() / 2;
        NolLabel label = existingLabels.get(labelIndexToBeRemoved);
        int order = label.getLabelOrder();

        Vector<NolLabel> labelsWithGreaterLabel = getLabelsWithGreaterThanOrder(existingLabels, order);

        // Act
        sut.removeLabelCategory(sut.getLabel(labelIndexToBeRemoved));

        // Assert
        Vector<NolLabel> sutLabels = sut.getLabels();
        assertThat(Arrays.asList(labelsWithGreaterLabel), is(not(empty())));
        assertThat(Arrays.asList(sutLabels), is(not(empty())));

        for (NolLabel labelWithGreaterLabel : labelsWithGreaterLabel) {
            assertThat(Arrays.asList(labelsWithGreaterLabel), is(not(empty())));
            for (NolLabel sutLabel : sutLabels) {
                if (Objects.equals(sutLabel.getName(), labelWithGreaterLabel.getName())) {
                    int updatedLabel = labelWithGreaterLabel.getLabelOrder() - 1;
                    assertThat(sutLabel.getLabelOrder(), is(equalTo(updatedLabel)));
                }
            }
        }
    }

    @Test
    public void test_removeLabelCategory_always_invokesRawDataSourceRemoveLabelCategory() throws Exception {
        // Arrange
        Project sut = createProject();
        addProjectLabels(sut);
        Vector existingLabels = cloneLabels(sut.getLabels());
        int labelIndexToBeRemoved = existingLabels.size() / 2;

        // Act
        sut.removeLabelCategory(sut.getLabel(labelIndexToBeRemoved));

        // Assert
        RawDataSource rawDataSource = sut.getRawDataSource();
        verify(rawDataSource).removeLabelCategory(labelIndexToBeRemoved);
    }

    @Test
    public void test_changeLabelOrder_always_updatesLabelOrders() throws Exception {
        // Arrange
        Project sut = createProject();
        addProjectLabels(sut);
        Vector<NolLabel> existingLabels = cloneLabels(sut.getLabels());
        int[] labelOrder = new int[existingLabels.size()];
        for (int idx = 0; idx < existingLabels.size(); idx++) {
            labelOrder[idx] = randomGenearator.nextInt();
        }

        // Act
        sut.changeLabelOrder(labelOrder);

        // Assert
        Vector<NolLabel> sutLabels = sut.getLabels();
        assertThat(sutLabels.size(), is(equalTo(existingLabels.size())));
        for (int idx = 0; idx < existingLabels.size(); idx++) {
            assertThat(sutLabels.get(idx).getLabelOrder(), is(equalTo(labelOrder[idx])));
        }
    }

    @Test
    public void test_changeLabelOrder_always_invokesRawDataSourceChangeLabelOrder() throws Exception {
        // Arrange
        Project sut = createProject();
        addProjectLabels(sut);
        Vector existingLabels = cloneLabels(sut.getLabels());
        int[] labelOrder = new int[existingLabels.size()];
        for (int idx = 0; idx < existingLabels.size(); idx++) {
            labelOrder[idx] = randomGenearator.nextInt();
        }

        // Act
        sut.changeLabelOrder(labelOrder);

        // Assert
        RawDataSource rawDataSource = sut.getRawDataSource();
        verify(rawDataSource).changeLabelOrder();
    }

    @Test
    public void test_labelNameChanged_always_alwaysInvokesDataSourceLabelNameChanged() throws Exception {
        // Arrange
        Project sut = createProject();
        addProjectLabels(sut);
        NolLabel label = sut.getLabel(3);

        // Act
        sut.labelNameChanged(label);

        // Assert
        verify(projectRawDataSource).labelNameChanged(label);
    }

    @Test
    public void test_labelColorChanged_always_alwaysInvokesDataSourceLabelColorChanged() throws Exception {
        // Arrange
        Project sut = createProject();
        addProjectLabels(sut);
        NolLabel label = sut.getLabel(3);

        // Act
        sut.labelColorChanged(label);

        // Assert
        verify(projectRawDataSource).labelColorChanged(label);
    }

    @Test
    public void test_getPreprocessorIndexByName_preprocessorExists_returnsIndex() throws Exception {
        // Arrange
        Project sut = createProject();

        for (int i = 0; i < 3; i++) {
            String name = "Name " + (i + 1);
            Preprocessor preprocessor = createPreprocessor(name);
            sut.addPreprocessor(preprocessor);

            // Act & Assert
            assertThat(sut.getPreprocessorIndexByName(name), is(equalTo(i)));
        }
    }

    @Test
    public void test_getPreprocessorIndexByName_preprocessorDoesNotExist_returnsMinusOne() throws Exception {
        // Arrange
        Project sut = createProject();

        // Act & Assert
        assertThat(sut.getPreprocessorIndexByName("Any Name"), is(equalTo(-1)));
    }

    @Test
    public void test_getPreprocessorByIndex_always_returnsPreprocessorByIndex() throws Exception {
        // Arrange
        Project sut = createProject();

        for (int i = 0; i < 3; i++) {
            Preprocessor preprocessor = createPreprocessor("Name " + (i + 1));
            sut.addPreprocessor(preprocessor);

            // Act & Assert
            assertThat(sut.getPreprocessorByIndex(i), is(equalTo(preprocessor)));
        }
    }

    @Test
    public void test_addPreprocessor_preprocessorDoesNotExistAlready_addsPreprocessor() throws Exception {
// Arrange
        Project sut = createProject();
        Preprocessor preprocessor = createPreprocessor();

        // Act
        sut.addPreprocessor(preprocessor);

        // Assert
        Vector preprocessors = sut.getPreprocessors();
        assertTrue(preprocessors.contains(preprocessor));
    }

    @Test
    public void test_addPreprocessor_preprocessorExistsAlready_doesNotAddPreprocessor() throws Exception {
// Arrange
        Project sut = createProject();
        Preprocessor preprocessor = createPreprocessor();
        sut.addPreprocessor(preprocessor);

        // Act
        sut.addPreprocessor(preprocessor);

        // Assert
        assertThat(sut.getPreprocessors().size(), is(equalTo(1)));
    }

    @Test
    public void test_removePreprocessorByPreprocessor_always_removesPreprocessorAndProcessedData() throws Exception {
        // Arrange
        Project sut = createProject();
        Preprocessor preprocessor1 = createPreprocessor();
        Preprocessor preprocessor2 = createPreprocessor();
        DataSeries dataSeries1 = createDataSeries("DataSeries 1", preprocessor1);
        DataSeries dataSeries2 = createDataSeries("DataSeries 2", preprocessor1);
        DataSeries dataSeries3 = createDataSeries("DataSeries 3", preprocessor2);
        sut.addPreprocessor(preprocessor1);
        sut.addPreprocessor(preprocessor2);
        sut.addProcessedDataSeries(dataSeries1);
        sut.addProcessedDataSeries(dataSeries2);
        sut.addProcessedDataSeries(dataSeries3);

        // Act
        sut.removePreprocessor(preprocessor1);

        // Assert
        Vector preprocessors = sut.getPreprocessors();
        Vector dataSeriesList = sut.getProcessedData();

        assertFalse(preprocessors.contains(preprocessor1));
        assertFalse(dataSeriesList.contains(dataSeries1));
        assertFalse(dataSeriesList.contains(dataSeries2));

        assertTrue(preprocessors.contains(preprocessor2));
        assertTrue(dataSeriesList.contains(dataSeries3));
    }

    @Test
    public void test_removePreprocessorByIndex_always_removesPreprocessorAndProcessedData() throws Exception {
        // Arrange
        Project sut = createProject();
        Preprocessor preprocessor1 = createPreprocessor("Preprocessor 1");
        Preprocessor preprocessor2 = createPreprocessor("Preprocessor 2");
        DataSeries dataSeries1 = createDataSeries("DataSeries 1", preprocessor1);
        DataSeries dataSeries2 = createDataSeries("DataSeries 2", preprocessor1);
        DataSeries dataSeries3 = createDataSeries("DataSeries 3", preprocessor2);
        sut.addPreprocessor(preprocessor1);
        sut.addPreprocessor(preprocessor2);
        sut.addProcessedDataSeries(dataSeries1);
        sut.addProcessedDataSeries(dataSeries2);
        sut.addProcessedDataSeries(dataSeries3);

        // Act
        sut.removePreprocessor(sut.getPreprocessorIndexByName(preprocessor1.getName()));

        // Assert
        Vector preprocessors = sut.getPreprocessors();
        Vector dataSeriesList = sut.getProcessedData();

        assertFalse(preprocessors.contains(preprocessor1));
        assertFalse(dataSeriesList.contains(dataSeries1));
        assertFalse(dataSeriesList.contains(dataSeries2));

        assertTrue(preprocessors.contains(preprocessor2));
        assertTrue(dataSeriesList.contains(dataSeries3));
    }

    @Test
    public void test_removePreprocessorByPreprocessor_preprocessorDoesNotExist_doesNotRemoveAnyPreprocessor() throws Exception {
        // Arrange
        Project sut = createProject();
        Preprocessor preprocessor1 = createPreprocessor();
        Preprocessor preprocessor2 = createPreprocessor();
        Preprocessor preprocessor3 = createPreprocessor();
        DataSeries dataSeries1 = createDataSeries("DataSeries 1", preprocessor1);
        DataSeries dataSeries2 = createDataSeries("DataSeries 2", preprocessor1);
        DataSeries dataSeries3 = createDataSeries("DataSeries 3", preprocessor2);
        sut.addPreprocessor(preprocessor1);
        sut.addPreprocessor(preprocessor2);
        sut.addProcessedDataSeries(dataSeries1);
        sut.addProcessedDataSeries(dataSeries2);
        sut.addProcessedDataSeries(dataSeries3);

        // Act
        sut.removePreprocessor(preprocessor3);

        // Assert
        Vector preprocessors = sut.getPreprocessors();
        Vector dataSeriesList = sut.getProcessedData();

        assertTrue(preprocessors.contains(preprocessor1));
        assertTrue(preprocessors.contains(preprocessor2));

        assertTrue(dataSeriesList.contains(dataSeries1));
        assertTrue(dataSeriesList.contains(dataSeries2));
        assertTrue(dataSeriesList.contains(dataSeries3));
    }

    @Test
    public void test_removePreprocessorByIndex_preprocessorDoesNotExist_doesNotRemoveAnyPreprocessor() throws Exception {
        // Arrange
        Project sut = createProject();
        Preprocessor preprocessor1 = createPreprocessor("Preprocessor 1");
        Preprocessor preprocessor2 = createPreprocessor("Preprocessor 2");
        DataSeries dataSeries1 = createDataSeries("DataSeries 1", preprocessor1);
        DataSeries dataSeries2 = createDataSeries("DataSeries 2", preprocessor1);
        DataSeries dataSeries3 = createDataSeries("DataSeries 3", preprocessor2);
        sut.addPreprocessor(preprocessor1);
        sut.addPreprocessor(preprocessor2);
        sut.addProcessedDataSeries(dataSeries1);
        sut.addProcessedDataSeries(dataSeries2);
        sut.addProcessedDataSeries(dataSeries3);
        int indexOfLastPreprocessor = sut.getPreprocessorIndexByName(preprocessor2.getName());

        // Act
        sut.removePreprocessor(indexOfLastPreprocessor + 1);

        // Assert
        Vector preprocessors = sut.getPreprocessors();
        Vector dataSeriesList = sut.getProcessedData();

        assertTrue(preprocessors.contains(preprocessor1));
        assertTrue(preprocessors.contains(preprocessor2));

        assertTrue(dataSeriesList.contains(dataSeries1));
        assertTrue(dataSeriesList.contains(dataSeries2));
        assertTrue(dataSeriesList.contains(dataSeries3));
    }

    @Test
    public void test_addPredictiveModel_modelDoesNotExist_addsModel() throws Exception {
        // Arrange
        Project sut = createProject();
        int predictiveModelsCount = 3;
        Vector<NolModel2> predictiveModels = new Vector<>();
        for (int i = 0; i < predictiveModelsCount; i++) {
            predictiveModels.add(createPredictiveModel("Name " + (i + 1)));
        }

        // Act
        for (NolModel2 model : predictiveModels) {
            sut.addPredictiveModel(model);
        }

        // Assert
        assertThat(sut.getNumberOfPredictiveModels(), is(equalTo(predictiveModelsCount)));
        Vector sutPredictiveModels = sut.getPredictiveModels();
        for (NolModel2 model : predictiveModels) {
            assertTrue(sutPredictiveModels.contains(model));
        }
    }

    @Test
    public void test_addPredictiveModel_modelExists_overridesExistingModel() throws Exception {
        // Arrange
        Project sut = createProject();
        NolModel2 predictiveModel1 = createPredictiveModel("Name 1");
        NolModel2 predictiveModel2 = createPredictiveModel("Name 1");
        sut.addPredictiveModel(predictiveModel1);

        // Act
        sut.addPredictiveModel(predictiveModel2);

        // Assert
        Vector predictiveModels = sut.getPredictiveModels();
        assertFalse(predictiveModels.contains(predictiveModel1));
        assertTrue(predictiveModels.contains(predictiveModel2));
    }

    @Test
    public void test_deletePredictiveModelByModel_predictiveModelDoesNotExist_doesNotRemoveAnyPredictiveModel() throws Exception {
        // Arrange
        Project sut = createProject();
        NolModel2 predictiveModel1 = createPredictiveModel("Name 1");
        NolModel2 predictiveModel2 = createPredictiveModel("Name 2");
        NolModel2 predictiveModel3 = createPredictiveModel("Name 3");
        sut.addPredictiveModel(predictiveModel1);
        sut.addPredictiveModel(predictiveModel2);

        // Act
        sut.deletePredictiveModel(predictiveModel3);

        // Assert
        Vector predictiveModels = sut.getPredictiveModels();
        assertTrue(predictiveModels.contains(predictiveModel1));
        assertTrue(predictiveModels.contains(predictiveModel2));
    }

    @Test
    public void test_deletePredictiveModelByIndex_predictiveModelDoesNotExist_doesNotRemoveAnyPredictiveModel() throws Exception {
        // Arrange
        Project sut = createProject();
        NolModel2 predictiveModel1 = createPredictiveModel("Name 1");
        NolModel2 predictiveModel2 = createPredictiveModel("Name 2");
        sut.addPredictiveModel(predictiveModel1);
        sut.addPredictiveModel(predictiveModel2);
        int indexOfLastPredictiveModel = sut.getPredictiveModelIndexByName(predictiveModel2.getName());

        // Act
        sut.deletePredictiveModel(indexOfLastPredictiveModel + 1);

        // Assert
        Vector predictiveModels = sut.getPredictiveModels();
        assertTrue(predictiveModels.contains(predictiveModel1));
        assertTrue(predictiveModels.contains(predictiveModel2));
    }

    @Test
    public void test_deletePredictiveModelByModel_always_removesPredictiveModel() throws Exception {
        // Arrange
        Project sut = createProject();
        NolModel2 predictiveModel1 = createPredictiveModel("Name 1");
        NolModel2 predictiveModel2 = createPredictiveModel("Name 2");
        sut.addPredictiveModel(predictiveModel1);
        sut.addPredictiveModel(predictiveModel2);

        // Act
        sut.deletePredictiveModel(predictiveModel1);

        // Assert
        Vector predictiveModels = sut.getPredictiveModels();
        assertFalse(predictiveModels.contains(predictiveModel1));
        assertTrue(predictiveModels.contains(predictiveModel2));
    }

    @Test
    public void test_deletePredictiveModelByIndex_always_removesPredictiveModel() throws Exception {
        // Arrange
        Project sut = createProject();
        NolModel2 predictiveModel1 = createPredictiveModel("Name 1");
        NolModel2 predictiveModel2 = createPredictiveModel("Name 2");
        sut.addPredictiveModel(predictiveModel1);
        sut.addPredictiveModel(predictiveModel2);

        // Act
        sut.deletePredictiveModel(sut.getPredictiveModelIndexByName(predictiveModel2.getName()));

        // Assert
        Vector predictiveModels = sut.getPredictiveModels();
        assertTrue(predictiveModels.contains(predictiveModel1));
        assertFalse(predictiveModels.contains(predictiveModel2));
    }

    @Test
    public void test_getPredictiveModel_always_returnsPredictiveModel() throws Exception {
        // Arrange
        Project sut = createProject();
        int predictiveModelsCount = 3;
        Vector<NolModel2> predictiveModels = new Vector<>();
        for (int i = 0; i < predictiveModelsCount; i++) {
            NolModel2 model = createPredictiveModel("Name " + (i + 1));
            predictiveModels.add(model);
            sut.addPredictiveModel(model);
        }

        for(NolModel2 predictiveModel : predictiveModels) {
            // Act
            NolModel2 sutModel = sut.getPredictiveModel(sut.getPredictiveModelIndexByName(predictiveModel.getName()));

            // Assert
            assertThat(sutModel, is(equalTo(predictiveModel)));
        }
    }

    @Test
    public void test_addOptimizationModel_modelDoesNotExist_addsModel() throws Exception {
        // Arrange
        Project sut = createProject();
        int optimizationModelsCount = 3;
        Vector<NolOptimizeModel> optimizationModels = new Vector<>();
        for (int i = 0; i < optimizationModelsCount; i++) {
            optimizationModels.add(createOptimizationModel("Name " + (i + 1)));
        }

        // Act
        for (NolOptimizeModel model : optimizationModels) {
            sut.addOptimizationModel(model);
        }

        // Assert
        assertThat(sut.getNumberOfOptimizationModels(), is(equalTo(optimizationModelsCount)));
        Vector sutOptimizationModels = sut.getOptimizationModels();
        for (NolOptimizeModel model : optimizationModels) {
            assertTrue(sutOptimizationModels.contains(model));
        }
    }

    @Test
    public void test_addOptimizationModel_modelExists_overridesExistingModel() throws Exception {
        // Arrange
        Project sut = createProject();
        NolOptimizeModel optimizationModel1 = createOptimizationModel("Name 1");
        NolOptimizeModel optimizationModel2 = createOptimizationModel("Name 1");
        sut.addOptimizationModel(optimizationModel1);

        // Act
        sut.addOptimizationModel(optimizationModel2);

        // Assert
        Vector optimizationModels = sut.getOptimizationModels();
        assertFalse(optimizationModels.contains(optimizationModel1));
        assertTrue(optimizationModels.contains(optimizationModel2));
    }

    @Test
    public void test_deleteOptimizationModelByModel_always_removesOptimizationModel() throws Exception {
        // Arrange
        Project sut = createProject();
        NolOptimizeModel optimizationModel1 = createOptimizationModel("Name 1");
        NolOptimizeModel optimizationModel2 = createOptimizationModel("Name 2");
        sut.addOptimizationModel(optimizationModel1);
        sut.addOptimizationModel(optimizationModel2);

        // Act
        sut.deleteOptimizationModel(optimizationModel1);

        // Assert
        Vector optimizationModels = sut.getOptimizationModels();
        assertFalse(optimizationModels.contains(optimizationModel1));
        assertTrue(optimizationModels.contains(optimizationModel2));
    }

    @Test
    public void test_deleteOptimizationModelByIndex_always_removesOptimizationModel() throws Exception {
        // Arrange
        Project sut = createProject();
        NolOptimizeModel optimizationModel1 = createOptimizationModel("Name 1");
        NolOptimizeModel optimizationModel2 = createOptimizationModel("Name 2");
        sut.addOptimizationModel(optimizationModel1);
        sut.addOptimizationModel(optimizationModel2);

        // Act
        sut.deleteOptimizationModel(sut.getOptimizationModelIndexByName(optimizationModel2.getName()));

        // Assert
        Vector optimizationModels = sut.getOptimizationModels();
        assertTrue(optimizationModels.contains(optimizationModel1));
        assertFalse(optimizationModels.contains(optimizationModel2));
    }

    @Test
    public void test_deleteOptimizationModelByModel_optimizationModelDoesNotExist_doesNotRemoveAnyOptimizationModel() throws Exception {
        // Arrange
        Project sut = createProject();
        NolOptimizeModel optimizationModel1 = createOptimizationModel("Name 1");
        NolOptimizeModel optimizationModel2 = createOptimizationModel("Name 2");
        NolOptimizeModel optimizationModel3 = createOptimizationModel("Name 3");
        sut.addOptimizationModel(optimizationModel1);
        sut.addOptimizationModel(optimizationModel2);

        // Act
        sut.deleteOptimizationModel(optimizationModel3);

        // Assert
        Vector optimizationModels = sut.getOptimizationModels();
        assertTrue(optimizationModels.contains(optimizationModel1));
        assertTrue(optimizationModels.contains(optimizationModel2));
    }

    @Test
    public void test_deleteOptimizationModelByIndex_optimizationModelDoesNotExist_doesNotRemoveAnyOptimizationModel() throws Exception {
        // Arrange
        Project sut = createProject();
        NolOptimizeModel optimizationModel1 = createOptimizationModel("Name 1");
        NolOptimizeModel optimizationModel2 = createOptimizationModel("Name 2");
        sut.addOptimizationModel(optimizationModel1);
        sut.addOptimizationModel(optimizationModel2);
        int indexOfLastOptimizationModel = sut.getOptimizationModelIndexByName(optimizationModel2.getName());

        // Act
        sut.deleteOptimizationModel(indexOfLastOptimizationModel + 1);

        // Assert
        Vector optimizationModels = sut.getOptimizationModels();
        assertTrue(optimizationModels.contains(optimizationModel1));
        assertTrue(optimizationModels.contains(optimizationModel2));
    }

    @Test
    public void test_getOptimizationModel_always_returnsOptimizationModel() throws Exception {
        // Arrange
        Project sut = createProject();
        int optimizationModelsCount = 3;
        Vector<NolOptimizeModel> optimizationModels = new Vector<>();
        for (int i = 0; i < optimizationModelsCount; i++) {
            NolOptimizeModel model = createOptimizationModel("Name " + (i + 1));
            optimizationModels.add(model);
            sut.addOptimizationModel(model);
        }

        for(NolOptimizeModel optimizationModel : optimizationModels) {
            // Act
            NolOptimizeModel sutModel = sut.getOptimizationModel(sut.getOptimizationModelIndexByName(optimizationModel.getName()));

            // Assert
            assertThat(sutModel, is(equalTo(optimizationModel)));
        }
    }

    @Test
    public void test_addSimulation_modelDoesNotExist_addsModel() throws Exception {
        // Arrange
        Project sut = createProject();
        int simulationsCount = 3;
        Vector<ResponseSurfaceSimulation> simulations = new Vector<>();
        for (int i = 0; i < simulationsCount; i++) {
            simulations.add(createSimulation("Name " + (i + 1)));
        }

        // Act
        for (ResponseSurfaceSimulation model : simulations) {
            sut.addSimulation(model);
        }

        // Assert
        assertThat(sut.getNumberOfSimulations(), is(equalTo(simulationsCount)));
        Vector sutSimulations = sut.getSimulations();
        for (ResponseSurfaceSimulation model : simulations) {
            assertTrue(sutSimulations.contains(model));
        }
    }

    @Test
    public void
    test_addSimulation_modelExists_overridesExistingModel() throws Exception {
        // Arrange
        Project sut = createProject();
        ResponseSurfaceSimulation simulation1 = createSimulation("Name 1");
        ResponseSurfaceSimulation simulation2 = createSimulation("Name 1");
        sut.addSimulation(simulation1);

        // Act
        sut.addSimulation(simulation2);

        // Assert
        Vector simulations = sut.getSimulations();
        assertThat(sut.getNumberOfSimulations(), is(equalTo(1)));
        assertTrue(simulations.contains(simulation2));
    }

    @Test
    public void test_deleteSimulationByModel_always_removesSimulation() throws Exception {
        // Arrange
        Project sut = createProject();
        ResponseSurfaceSimulation simulation1 = createSimulation("Name 1");
        ResponseSurfaceSimulation simulation2 = createSimulation("Name 2");
        sut.addSimulation(simulation1);
        sut.addSimulation(simulation2);

        // Act
        sut.deleteSimulation(simulation1);

        // Assert
        Vector simulations = sut.getSimulations();
        assertFalse(simulations.contains(simulation1));
        assertTrue(simulations.contains(simulation2));
    }

    @Test
    public void test_deleteSimulationByIndex_always_removesSimulation() throws Exception {
        // Arrange
        Project sut = createProject();
        ResponseSurfaceSimulation simulation1 = createSimulation("Name 1");
        ResponseSurfaceSimulation simulation2 = createSimulation("Name 2");
        ResponseSurfaceSimulation simulation3 = createSimulation("Name 3");
        sut.addSimulation(simulation1);
        sut.addSimulation(simulation2);

        // Act
        sut.deleteSimulation(sut.getSimulationIndexByName(simulation3.getName()));

        // Assert
        Vector simulations = sut.getSimulations();
        assertTrue(simulations.contains(simulation1));
        assertTrue(simulations.contains(simulation2));
    }

    @Test
    public void test_deleteSimulationByModel_simulationDoesNotExist_doesNotRemoveAnySimulation() throws Exception {
        // Arrange
        Project sut = createProject();
        ResponseSurfaceSimulation simulation1 = createSimulation("Name 1");
        ResponseSurfaceSimulation simulation2 = createSimulation("Name 2");
        sut.addSimulation(simulation1);
        sut.addSimulation(simulation2);

        // Act
        sut.deleteSimulation(simulation1);

        // Assert
        Vector simulations = sut.getSimulations();
        assertFalse(simulations.contains(simulation1));
        assertTrue(simulations.contains(simulation2));
    }

    @Test
    public void test_deleteSimulationByIndex_simulationDoesNotExist_doesNotRemoveAnySimulation() throws Exception {
        // Arrange
        Project sut = createProject();
        ResponseSurfaceSimulation simulation1 = createSimulation("Name 1");
        ResponseSurfaceSimulation simulation2 = createSimulation("Name 2");
        sut.addSimulation(simulation1);
        sut.addSimulation(simulation2);
        int indexOfLastSimulation = sut.getSimulationIndexByName(simulation2.getName());

        // Act
        sut.deleteSimulation(indexOfLastSimulation + 1);

        // Assert
        Vector simulations = sut.getSimulations();
        assertTrue(simulations.contains(simulation1));
        assertTrue(simulations.contains(simulation2));
    }

    @Test
    public void test_getSimulation_always_returnsSimulation() throws Exception {
        // Arrange
        Project sut = createProject();
        int simulationsCount = 3;
        Vector<ResponseSurfaceSimulation> simulations = new Vector<>();
        for (int i = 0; i < simulationsCount; i++) {
            ResponseSurfaceSimulation model = createSimulation("Name " + (i + 1));
            simulations.add(model);
            sut.addSimulation(model);
        }

        for(ResponseSurfaceSimulation simulation : simulations) {
            // Act
            ResponseSurfaceSimulation sutModel = sut.getSimulation(sut.getSimulationIndexByName(simulation.getName()));

            // Assert
            assertThat(sutModel, is(equalTo(simulation)));
        }
    }

    @Test
    public void test_addOptimization_modelDoesNotExist_addsModel() throws Exception {
        // Arrange
        Project sut = createProject();
        int optimizationsCount = 3;
        Vector<NolOptimization> optimizations = new Vector<>();
        for (int i = 0; i < optimizationsCount; i++) {
            optimizations.add(createOptimization("Name " + (i + 1)));
        }

        // Act
        for (NolOptimization model : optimizations) {
            sut.addOptimization(model);
        }

        // Assert
        assertThat(sut.getNumberOfOptimizations(), is(equalTo(optimizationsCount)));
        Vector sutOptimizations = sut.getOptimizations();
        for (NolOptimization model : optimizations) {
            assertTrue(sutOptimizations.contains(model));
        }
    }

    @Test
    public void test_addOptimization_modelExists_overridesExistingModel() throws Exception {
        // Arrange
        Project sut = createProject();
        NolOptimization optimization1 = createOptimization("Name 1");
        NolOptimization optimization2 = createOptimization("Name 1");
        sut.addOptimization(optimization1);

        // Act
        sut.addOptimization(optimization2);

        // Assert
        Vector optimizations = sut.getOptimizations();
        assertThat(sut.getNumberOfOptimizations(), is(equalTo(1)));
        assertTrue(optimizations.contains(optimization2));
    }

    @Test
    public void test_deleteOptimizationByModel_always_removesOptimization() throws Exception {
        // Arrange
        Project sut = createProject();
        NolOptimization optimization1 = createOptimization("Name 1");
        NolOptimization optimization2 = createOptimization("Name 2");
        sut.addOptimization(optimization1);
        sut.addOptimization(optimization2);

        // Act
        sut.deleteOptimization(optimization1);

        // Assert
        Vector optimizations = sut.getOptimizations();
        assertFalse(optimizations.contains(optimization1));
        assertTrue(optimizations.contains(optimization2));
    }

    @Test
    public void test_deleteOptimizationByIndex_always_removesOptimization() throws Exception {
        // Arrange
        Project sut = createProject();
        NolOptimization optimization1 = createOptimization("Name 1");
        NolOptimization optimization2 = createOptimization("Name 2");
        sut.addOptimization(optimization1);
        sut.addOptimization(optimization2);

        // Act
        sut.deleteOptimization(sut.getOptimizationIndexByName(optimization2.getName()));

        // Assert
        Vector optimizations = sut.getOptimizations();
        assertTrue(optimizations.contains(optimization1));
        assertFalse(optimizations.contains(optimization2));
    }

    @Test
    public void test_deleteOptimizationByModel_optimizationDoesNotExist_DoesNotRemoveAnyOptimization() throws Exception {
        // Arrange
        Project sut = createProject();
        NolOptimization optimization1 = createOptimization("Name 1");
        NolOptimization optimization2 = createOptimization("Name 2");
        NolOptimization optimization3 = createOptimization("Name 3");
        sut.addOptimization(optimization1);
        sut.addOptimization(optimization2);

        // Act
        sut.deleteOptimization(optimization3);

        // Assert
        Vector optimizations = sut.getOptimizations();
        assertTrue(optimizations.contains(optimization1));
        assertTrue(optimizations.contains(optimization2));
    }

    @Test
    public void test_deleteOptimizationByIndex_optimizationDoesNotExist_DoesNotRemoveAnyOptimization() throws Exception {
        // Arrange
        Project sut = createProject();
        NolOptimization optimization1 = createOptimization("Name 1");
        NolOptimization optimization2 = createOptimization("Name 2");
        sut.addOptimization(optimization1);
        sut.addOptimization(optimization2);
        int indexOfLastOptimization = sut.getOptimizationIndexByName(optimization2.getName());

        // Act
        sut.deleteOptimization(indexOfLastOptimization + 1);

        // Assert
        Vector optimizations = sut.getOptimizations();
        assertTrue(optimizations.contains(optimization1));
        assertTrue(optimizations.contains(optimization2));
    }

    @Test
    public void test_getOptimization_always_returnsOptimization() throws Exception {
        // Arrange
        Project sut = createProject();
        int optimizationsCount = 3;
        Vector<NolOptimization> optimizations = new Vector<>();
        for (int i = 0; i < optimizationsCount; i++) {
            NolOptimization model = createOptimization("Name " + (i + 1));
            optimizations.add(model);
            sut.addOptimization(model);
        }

        for(NolOptimization optimization : optimizations) {
            // Act
            NolOptimization sutModel = sut.getOptimization(sut.getOptimizationIndexByName(optimization.getName()));

            // Assert
            assertThat(sutModel, is(equalTo(optimization)));
        }
    }

    @Test
    public void test_loadFileFormat_always_loadsFileFormatsFromFile() throws Exception {
        // Arrange
        Project sut = createProject();
        String filename = createFile();
        Vector<DataSeriesFileFormat> dataSeriesFileFormats = saveFileFormat(filename);

        // Act
        sut.loadFileFormat(fileDirectory);

        // Assert
         assertThat(Arrays.asList(dataSeriesFileFormats), is(not(empty())));
         for (DataSeriesFileFormat dataSeriesFileFormat : dataSeriesFileFormats) {
             assertNotNull(sut.getDataSeriesFileFormat(dataSeriesFileFormat.getName()));
         }
    }

    @Test
    public void test_saveBinary_always_savesProject() throws Exception {
        // Arrange
        setRawDataSource = false;
        Project sut = createProject();
        populateProject(sut);
        String filename = createFile();
        Project project = new Project();

        // Act
        sut.saveBinary(filename);

        // Assert
        loadBinary(project, filename);
        verifyProjectAreSame(sut, project);
    }

    @Test
    public void test_initDataTreeForTransientField_always_resetsTransientFieldOfAllObjects() throws Exception {
        // Arrange
        Project sut = createProject();
        populateProjectWithMocks(sut);

        // Act
        sut.initDataTreeForTransientField();

        // Assert
        assertThat(Arrays.asList(sut.getPreprocessors()), is(not(empty())));
        for (Preprocessor preprocessor : (Vector<Preprocessor>) sut.getPreprocessors()) {
            verify(preprocessor).initTransient(sut);
            verify(preprocessor).initHasCode();
        }

        assertThat(Arrays.asList(sut.getSimulations()), is(not(empty())));
        for (ResponseSurfaceSimulation simulation : (Vector<ResponseSurfaceSimulation>) sut.getSimulations()) {
            verify(simulation).initTransient(sut);
        }

        assertThat(Arrays.asList(sut.getOptimizations()), is(not(empty())));
        for (NolOptimization optimization : (Vector<NolOptimization>) sut.getOptimizations()) {
            verify(optimization).initTransient(sut);
        }

        assertThat(Arrays.asList(sut.getPredictiveModels()), is(not(empty())));
        for (NolModel2 predictiveModel : (Vector<NolModel2>) sut.getPredictiveModels()) {
            verify(predictiveModel).initTransient(sut);
        }

        assertThat(Arrays.asList(sut.getOptimizationModels()), is(not(empty())));
        for (NolOptimizeModel optimizationModel : (Vector<NolOptimizeModel>) sut.getOptimizationModels()) {
            verify(optimizationModel).initTransient(sut);
        }

        assertThat(Arrays.asList(sut.getProcessedData()), is(not(empty())));
        for (DataSeries processedData : (Vector<DataSeries>) sut.getProcessedData()) {
            verify(processedData).initTransient(sut);
        }
    }

    @Test
    public void test_changeDataSeriesName_always_changesDataSeriesName() throws Exception {
        // Arrange
        String newName = "Data Series 2";
        Project sut = createProject();
        DataSeries dataSeries = createDataSeries("Data Series 1");
        sut.addProcessedDataSeries(dataSeries);

        // Act
        sut.changeDataSeriesName(dataSeries, newName);

        // Assert
        assertThat(sut.getProcessedData().size(), is(equalTo(1)));
        assertThat(((DataSeries)sut.getProcessedData().get(0)).getName(), is(equalTo(newName)));
    }

    private void addProjectLabels(Project project) {
        int labelsCount = 10;

        for (int idx = 0; idx < labelsCount; idx++) {
            project.addLabelCategory("Label Name " + idx, "Label Comment " + idx, colors[idx]);
        }
    }

    private Vector<NolLabel> cloneLabels(Vector<NolLabel> labels) {
        Vector<NolLabel> clonedLabels = new Vector<>();

        for (NolLabel label : labels) {
            NolLabel cloned = new NolLabel(label.getName(), label.getComment(), label.getLabelColor());
            cloned.setLabelOrder(label.getLabelOrder());
            clonedLabels.addElement(cloned);
        }

        return clonedLabels;
    }

    private DataSeries createDataSeries(String name) {
        int rows = 3, cols = 4;
        DataSeries dataSeries = new DataSeries(rows, cols);
        dataSeries.setName(name);
        return dataSeries;
    }

    private DataSeries createDataSeries(String name, Preprocessor preprocessor) {
        DataSeries dataSeries = createDataSeries(name);
        dataSeries.setDataSource(preprocessor);
        return dataSeries;
    }

    private DataSeriesFileFormat createDataSeriesFileFormat(String name) {
        DataSeriesFileFormat fileFormat = new DataSeriesFileFormat();
        fileFormat.setName(name);
        return fileFormat;
    }

    private String createFile() throws IOException {
        String filename = fileDirectory + "\\" + FILENAME;

        File file = new File(filename);
        if (file.exists() == false) {
            temporaryFolder.newFile();
        }

        return filename;
    }

    private NolOptimization createOptimization(String name) {
        NolOptimization optimization = new NolOptimization();
        optimization.setName(name);
        return optimization;
    }

    private NolOptimizeModel createOptimizationModel(String name) {
        NolOptimizeModel model = new NolOptimizeModel();
        model.setName(name);
        model.getPreprocessor(createPreprocessor());
        return model;
    }

    private NolModel2 createPredictiveModel(String name) {
        NolModel2 model = new NolModel2();
        model.setName(name);
        model.getPreprocessor(createPreprocessor());
        return model;
    }

    private Preprocessor createPreprocessor() {
        return createPreprocessor("Preprocessor Default Name");
    }

    private Preprocessor createPreprocessor(String name) {
        Preprocessor preprocessor = new Preprocessor();
        preprocessor.setName(name);
        return preprocessor;
    }

    private Project createProject() {
        return createProject("Project Default Name");
    }

    private Project createProject(String name) {
        Project project = new Project(name);

        if (setRawDataSource) {
            projectRawDataSource = mock(RawDataSource.class);

            Vector<DataSeries> dataSeriesList = new Vector<>();
            for (int i = 0; i < 3; i++) {
                dataSeriesList.add(createDataSeries("DataSeries Default Name " + (i + 1)));
            }

            when(projectRawDataSource.getDataSeries()).thenReturn(dataSeriesList);

            project.setRawDataSource(projectRawDataSource);
        }

        projectListeners = new Vector<>();
        for (int i = 0; i < 3; i++) {
            ProjectListenerStub projectListener = createProjectListener();
            projectListeners.add(projectListener);
            project.addProjectListener(projectListener);
        }

        project.setProjectDirectory(fileDirectory);

        return project;
    }

    private ProjectListenerStub createProjectListener() {
        ProjectListenerStub projectListener = new ProjectListenerStub();
        return projectListener;
    }

    private ResponseSurfaceSimulation createSimulation(String name) {
        ResponseSurfaceSimulation simulation = new ResponseSurfaceSimulation();
        simulation.setName(name);
        return simulation;
    }

    private Vector<NolLabel> getLabelsWithGreaterThanOrder(Vector<NolLabel> labels, int order) {
        Vector<NolLabel> greaterOrderLabels = new Vector<>();

        for (NolLabel label : labels) {
            if (label.getLabelOrder() > order) {
                greaterOrderLabels.add(label);
            }
        }

        return greaterOrderLabels;
    }

    private int getMaxVariableCounter(Project sut) {
        int maxVariableCounter = 0;

        for (DataSeries dataSeries : (Vector<DataSeries>) sut.getRawDataSource().getDataSeries()) {
            for (Variable variable : (Vector<Variable>)dataSeries.getVarObjects()) {
                String name = variable.getName();
                name = name.replace("Var", "");
                int counter = new Integer(name);

                if (counter > maxVariableCounter) {
                    maxVariableCounter = counter;
                }
            }
        }

        return maxVariableCounter;
    }

    private void loadBinary(Project project, String fileName) throws IOException, ClassNotFoundException {
        FileInputStream fileInputStream = null;
        GZIPInputStream gzipInputStream = null;
        ObjectInputStream objectInputStream = null;

        try {
            File sourceFile = new File(fileName);

            fileInputStream = new FileInputStream(sourceFile);
            gzipInputStream = new GZIPInputStream(fileInputStream);
            objectInputStream = new ObjectInputStream(gzipInputStream);

            Vector content = (Vector) objectInputStream.readObject();
            objectInputStream.close();
            project.setName((String) content.elementAt(0));
            project.setRawDataSource((RawDataSource) content.elementAt(1));

            for (Preprocessor preprocessor : (Vector<Preprocessor>) content.elementAt(4)) {
                project.addPreprocessor(preprocessor);
            }

            for (DataSeries processedData : (Vector<DataSeries>) content.elementAt(5)) {
                project.addProcessedDataSeries(processedData);
            }

            for (NolModel2 predictiveModel : (Vector<NolModel2>) content.elementAt(6)) {
                project.addPredictiveModel(predictiveModel);
            }

            for (NolOptimizeModel optimizationModel : (Vector<NolOptimizeModel>) content.elementAt(7)) {
                project.addOptimizationModel(optimizationModel);
            }

            for (ResponseSurfaceSimulation simulation : (Vector<ResponseSurfaceSimulation>) content.elementAt(8)) {
                project.addSimulation(simulation);
            }

            for (NolOptimization optimization : (Vector<NolOptimization>) content.elementAt(9)) {
                project.addOptimization(optimization);
            }

            for (DataSeriesFileFormat dataSeriesFileFormat : (Vector<DataSeriesFileFormat>) content.elementAt(10)) {
                project.setDataSeriesFileFormat(dataSeriesFileFormat);
            }
        } finally {
            if (objectInputStream != null) {
                objectInputStream.close();
            } else if (gzipInputStream != null) {
                gzipInputStream.close();
            } else if (fileInputStream != null) {
                fileInputStream.close();
            }
        }
    }

    private void populateProject(Project project) {
        for (ProjectListenerStub listener : projectListeners) {
            project.removeProjectListener(listener);
        }

        project.addDataSeries(createDataSeries("Data Series 1"));
        project.addPredictiveModel(createPredictiveModel("Predictive Model 1"));
        Preprocessor preprocessor = createPreprocessor("Preprocessor 1");
        project.addPreprocessor(preprocessor);
        project.addProcessedDataSeries(createDataSeries("Processed Data Series 1", preprocessor));
        project.addLabelCategory("Label Name 1", "Label Comments 1", Color.BLACK);
        project.addOptimization(createOptimization("Optimization 1"));
        project.addOptimizationModel(createOptimizationModel("Optimization Model 1"));
        project.addSimulation(createSimulation("Simulation 1"));
    }

    private void populateProjectWithMocks(Project project) {
        DataSeries dataSeries = mock(DataSeries.class);
        when(dataSeries.getName()).thenReturn("Data Series 1");
        project.addDataSeries(dataSeries);

        NolModel2 predictiveModel = mock(NolModel2.class);
        when(predictiveModel.getName()).thenReturn("Predictive Model 1");
        project.addPredictiveModel(predictiveModel);

        Preprocessor preprocessor = mock(Preprocessor.class);
        when(preprocessor.getName()).thenReturn("Preprocessor 1");
        project.addPreprocessor(preprocessor);

        DataSeries processedDataSeries = mock(DataSeries.class);
        when(processedDataSeries.getName()).thenReturn("Processed Data Series 1");
        project.addProcessedDataSeries(processedDataSeries);

        NolOptimization optimization = mock(NolOptimization.class);
        when(optimization.getName()).thenReturn("Optimization 1");
        project.addOptimization(optimization);

        NolOptimizeModel optimizationModel = mock(NolOptimizeModel.class);
        when(optimizationModel.getName()).thenReturn("Optimization Model 1");
        project.addOptimizationModel(optimizationModel);

        ResponseSurfaceSimulation simulation = mock(ResponseSurfaceSimulation.class);
        when(simulation.getName()).thenReturn("Simulation 1");
        project.addSimulation(simulation);

        project.addLabelCategory("Label Name 1", "Label Comment 1", Color.GREEN);
    }

    private Vector<DataSeriesFileFormat> saveFileFormat(String filename) {
        Vector<DataSeriesFileFormat> dataSeriesInputFormats = new Vector<>();
        for (int i = 0; i < 3; i++) {
            dataSeriesInputFormats.add(createDataSeriesFileFormat("Data Series File Format " + i));
        }

        VersionManagerForFileFormat versionForFileFormat = new VersionManagerForFileFormat();
        versionForFileFormat.setFileFormats(dataSeriesInputFormats);
        versionForFileFormat.saveToFile(filename);

        return dataSeriesInputFormats;
    }

    private void verifyProjectAreSame(Project expected, Project actual) {
        assertThat(actual.getNumberOfDataSeriesFileFormat(), is(equalTo(expected.getNumberOfDataSeriesFileFormat())));
        assertThat(actual.getNumberOfPredictiveModels(), is(equalTo(expected.getNumberOfPredictiveModels())));
        assertThat(actual.getNumberOfOptimizationModels(), is(equalTo(expected.getNumberOfOptimizationModels())));
        assertThat(actual.getNumberOfOptimizations(), is(equalTo(expected.getNumberOfOptimizations())));
        assertThat(actual.getNumberOfPredictiveModels(), is(equalTo(expected.getNumberOfPredictiveModels())));
        assertThat(actual.getNumberOfPreprocessors(), is(equalTo(expected.getNumberOfPreprocessors())));
        assertThat(actual.getNumberOfSimulations(), is(equalTo(expected.getNumberOfSimulations())));
    }

    private class ProjectListenerStub implements ProjectListener {
        private boolean DataFileFormatRemovedIsInvoked = false;
        private ProjectEvent DataFileFormatRemovedEvent = null;
        private boolean DataFileFormatSettedIsInvoked = false;
        private ProjectEvent DataFileFormatSettedEvent = null;

        @Override
        public void DataFileFormatSetted(ProjectEvent e) {
            DataFileFormatSettedIsInvoked = true;
            DataFileFormatSettedEvent = e;
        }

        @Override
        public void DataFileFormatRemoved(ProjectEvent e) {
            DataFileFormatRemovedIsInvoked = true;
            DataFileFormatRemovedEvent = e;
        }
    }
}