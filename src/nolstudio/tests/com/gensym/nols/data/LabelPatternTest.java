package com.gensym.nols.data;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import java.util.Random;
import java.util.Vector;

import static junit.framework.TestCase.assertTrue;
import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.core.Is.is;
import static org.hamcrest.core.IsEqual.equalTo;
import static org.hamcrest.core.IsNot.not;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertNull;

public class LabelPatternTest {
    private static final Random randomGenerator = new Random();

    private LabelPattern sut;

    @Before
    public void before() {
        this.sut = createLabelPattern();
    }

    @Test
    public void test_clone_labelsAreNotSet_clonedPatternLabelsAreNotSet() throws CloneNotSupportedException {
        // Arrange
        Vector<NolLabel> labelsPresent = null;
        Vector<NolLabel> labelsAbsent = null;
        Vector<NolLabel> existLabels = null;

        this.sut = new LabelPattern(labelsPresent, labelsAbsent, existLabels);

        // Act
        LabelPattern result = (LabelPattern) this.sut.clone();

        // Assert
        assertNotNull(result);

        assertNull(result.getLabelsPresent());
        assertNull(result.getLabelsAbsent());
        assertNull(result.getExistLabels());
    }

    @Test
    public void test_clone_labelsAreSet_clonedPatternLabelsAreSet() throws CloneNotSupportedException {
        // Arrange
        Vector<NolLabel> labelsPresent = createLabelsPresent();
        Vector<NolLabel> labelsAbsent = createLabelsAbsent();
        Vector<NolLabel> existLabels = createExistLabels(labelsPresent, labelsAbsent);

        this.sut = new LabelPattern(labelsPresent, labelsAbsent, existLabels);

        // Act
        LabelPattern result = (LabelPattern) this.sut.clone();

        // Assert
        assertNotNull(result);

        assertThat(labelsPresent.size(), is(not(equalTo(0))));
        assertThat(result.getLabelsPresent().size(), is(equalTo(labelsPresent.size())));
        Vector<NolLabel> actualLabelsPresent = (Vector<NolLabel>) result.getLabelsPresent();
        for (int i = 0; i < labelsPresent.size(); i++) {
            assertThat(actualLabelsPresent.get(i).getName(), is(equalTo(labelsPresent.get(i).getName())));
        }

        assertThat(labelsAbsent.size(), is(not(equalTo(0))));
        assertThat(result.getLabelsAbsent().size(), is(equalTo(labelsAbsent.size())));
        Vector<NolLabel> actualLabelsAbsent = (Vector<NolLabel>) result.getLabelsAbsent();
        for (int i = 0; i < labelsAbsent.size(); i++) {
            assertThat(actualLabelsAbsent.get(i).getName(), is(equalTo(labelsAbsent.get(i).getName())));
        }

        assertThat(existLabels.size(), is(not(equalTo(0))));
        assertThat(result.getExistLabels().size(), is(equalTo(existLabels.size())));
        Vector<NolLabel> actualExistLabels = (Vector<NolLabel>) result.getExistLabels();
        for (int i = 0; i < existLabels.size(); i++) {
            assertThat(actualExistLabels.get(i).getName(), is(equalTo(existLabels.get(i).getName())));
        }
    }

    @Test
    public void test_setLabelsPresent_always_setsPresentLabels() {
        // Arrange
        Vector<NolLabel> labelsPresent = createLabelsPresent();

        // Act
        this.sut.setLabelsPresent(labelsPresent);

        // Assert
        assertThat(labelsPresent.size(), is(not(equalTo(0))));
        assertThat(this.sut.getLabelsPresent().size(), is(equalTo(labelsPresent.size())));
        Vector<NolLabel> actualLabelsPresent = (Vector<NolLabel>) this.sut.getLabelsPresent();
        for (int i = 0; i < labelsPresent.size(); i++) {
            assertThat(actualLabelsPresent.get(i).getName(), is(equalTo(labelsPresent.get(i).getName())));
        }
    }

    @Test
    public void test_setLabelsAbsent_always_setsAbsentLabels() {
        // Arrange
        Vector<NolLabel> labelsAbsent = createLabelsAbsent();

        // Act
        this.sut.setLabelsAbsent(labelsAbsent);

        // Assert
        assertThat(labelsAbsent.size(), is(not(equalTo(0))));
        assertThat(this.sut.getLabelsAbsent().size(), is(equalTo(labelsAbsent.size())));
        Vector<NolLabel> actualLabelsAbsent = (Vector<NolLabel>) this.sut.getLabelsAbsent();
        for (int i = 0; i < labelsAbsent.size(); i++) {
            assertThat(actualLabelsAbsent.get(i).getName(), is(equalTo(labelsAbsent.get(i).getName())));
        }
    }

    @Test
    public void test_setExistLabels_always_setsExistLabels() {
        // Arrange
        Vector<NolLabel> existLabels = createExistLabels(createLabelsPresent(), createLabelsAbsent());

        // Act
        this.sut.setExistLabels(existLabels);

        // Assert
        assertThat(existLabels.size(), is(not(equalTo(0))));
        assertThat(this.sut.getExistLabels().size(), is(equalTo(existLabels.size())));
        Vector<NolLabel> actualExistLabels = (Vector<NolLabel>) this.sut.getExistLabels();
        for (int i = 0; i < existLabels.size(); i++) {
            assertThat(actualExistLabels.get(i).getName(), is(equalTo(existLabels.get(i).getName())));
        }
    }

    @Test
    public void test_matchesPattern_presentLabelIsFalse_retFalse() {
        // Arrange
        Vector<NolLabel> labelsPresent = createLabelsPresent();
        Vector<NolLabel> labelsAbsent = createLabelsAbsent();
        Vector<NolLabel> existLabels = createExistLabels(labelsPresent, labelsAbsent);

        this.sut = new LabelPattern(labelsPresent, labelsAbsent, existLabels);

        int rowsCount = 3;
        boolean[][] labelMatrix = createFlagsMatrix(labelsPresent.size(), labelsAbsent.size(), rowsCount);

        for (int rowNumber = 0; rowNumber < labelsPresent.size(); rowNumber++) {
            labelMatrix[anyIndex(labelsPresent.size())][rowNumber] = false;

            // Act & Assert
            assertFalse(this.sut.matchesPattern(labelMatrix, rowNumber));
        }
    }

    @Test
    public void test_matchesPattern_absentLabelIsTrue_retFalse() {
        // Arrange
        Vector<NolLabel> labelsPresent = createLabelsPresent();
        Vector<NolLabel> labelsAbsent = createLabelsAbsent();
        Vector<NolLabel> existLabels = createExistLabels(labelsPresent, labelsAbsent);

        this.sut = new LabelPattern(labelsPresent, labelsAbsent, existLabels);

        int rowsCount = 3;
        boolean[][] labelMatrix = createFlagsMatrix(labelsPresent.size(), labelsAbsent.size(), rowsCount);

        for (int rowNumber = 0; rowNumber < labelsPresent.size(); rowNumber++) {
            // exist labels contains present labels first and then absent labels.
            // Therefore, we are setting false for any absent label by adding present labels count in index.
            labelMatrix[labelsPresent.size() + anyIndex(labelsAbsent.size())][rowNumber] = true;

            // Act & Assert
            assertFalse(this.sut.matchesPattern(labelMatrix, rowNumber));
        }
    }

    @Test
    public void test_matchesPattern_presentLabelTrueAbsentLabelFalse_retTrue() {
        // Arrange
        Vector<NolLabel> labelsPresent = createLabelsPresent();
        Vector<NolLabel> labelsAbsent = createLabelsAbsent();
        Vector<NolLabel> existLabels = createExistLabels(labelsPresent, labelsAbsent);

        this.sut = new LabelPattern(labelsPresent, labelsAbsent, existLabels);

        int rowsCount = 3;
        boolean[][] labelMatrix = createFlagsMatrix(labelsPresent.size(), labelsAbsent.size(), rowsCount);

        for (int rowNumber = 0; rowNumber < labelsPresent.size(); rowNumber++) {
            // Act & Assert
            assertTrue(this.sut.matchesPattern(labelMatrix, rowNumber));
        }
    }

    @Test
    public void test_equals_objectIsNull_retFalse() {
        // Arrange
        // No arrangement

        // Act & Assert
        assertFalse(this.sut.equals(null));
    }

    @Test
    public void test_equals_objectIsNotLabelPatternInstance_retFalse() {
        // Arrange
        Object object = new Object();

        // Act & Assert
        assertFalse(this.sut.equals(object));
    }

    @Test
    public void test_equals_presentLabelsAndAbsentLabelsAreMatched_retTrue() {
        // Arrange
        Vector<NolLabel> labelsPresent = createLabelsPresent();
        Vector<NolLabel> labelsAbsent = createLabelsPresent();
        Vector<NolLabel> existLabels = createExistLabels(labelsPresent, labelsAbsent);

        this.sut = new LabelPattern(labelsPresent, labelsAbsent, existLabels);
        LabelPattern object = new LabelPattern(labelsPresent, labelsAbsent, existLabels);

        // Act & Assert
        assertTrue(this.sut.equals(object));
    }

    @Test
    public void test_equals_presentLabelsAreNotMatched_retFalse() {
        // Arrange
        Vector<NolLabel> labelsPresent = createLabelsPresent();
        Vector<NolLabel> labelsAbsent = createLabelsPresent();
        Vector<NolLabel> existLabels = createExistLabels(labelsPresent, labelsAbsent);

        this.sut = new LabelPattern(labelsPresent, labelsAbsent, existLabels);

        Vector<NolLabel> labelsPresent2 = new Vector<>();
        labelsPresent2.addAll(labelsPresent);
        // Removed one of the present labels
        labelsPresent2.removeElementAt(anyIndex(labelsPresent2.size()));
        LabelPattern object = new LabelPattern(labelsPresent2, labelsAbsent, existLabels);

        // Act & Assert
        assertFalse(this.sut.equals(object));
    }

    @Test
    public void test_equals_absentLabelsAreNotMatched_retFalse() {
        // Arrange
        Vector<NolLabel> labelsPresent = createLabelsPresent();
        Vector<NolLabel> labelsAbsent = createLabelsPresent();
        Vector<NolLabel> existLabels = createExistLabels(labelsPresent, labelsAbsent);

        this.sut = new LabelPattern(labelsPresent, labelsAbsent, existLabels);

        Vector<NolLabel> labelsAbsent2 = new Vector<>();
        labelsAbsent2.addAll(labelsAbsent);
        // Removed one of the Absent labels
        labelsAbsent2.removeElementAt(anyIndex(labelsAbsent2.size()));
        LabelPattern object = new LabelPattern(labelsPresent, labelsAbsent2, existLabels);

        // Act & Assert
        assertFalse(this.sut.equals(object));
    }

    @Test
    public void test_hashCode_labelsAreNotSet_retCorrectHashCode() {
        // Arrange
        Vector<NolLabel> existLabels = createExistLabels(createLabelsPresent(), createLabelsPresent());

        this.sut = new LabelPattern(null, null, existLabels);

        // Act & Assert
        assertThat(this.sut.hashCode(), is(equalTo(expectedHashCode(null, null))));
    }

    @Test
    public void test_hashCode_presentLabelsAreNotSet_retCorrectHashCode() {
        // Arrange
        Vector<NolLabel> labelsAbsent = createLabelsPresent();
        Vector<NolLabel> existLabels = createExistLabels(createLabelsPresent(), labelsAbsent);

        this.sut = new LabelPattern(null, labelsAbsent, existLabels);

        // Act & Assert
        assertThat(this.sut.hashCode(), is(equalTo(expectedHashCode(null, labelsAbsent))));
    }

    @Test
    public void test_hashCode_absentLabelsAreNotSet_retCorrectHashCode() {
        // Arrange
        Vector<NolLabel> labelsPresent = createLabelsPresent();
        Vector<NolLabel> existLabels = createExistLabels(labelsPresent, createLabelsAbsent());

        this.sut = new LabelPattern(labelsPresent, null, existLabels);

        // Act & Assert
        assertThat(this.sut.hashCode(), is(equalTo(expectedHashCode(labelsPresent, null))));
    }

    @Test
    public void test_hashCode_labelsAreNotNull_retCorrectHashCode() {
        // Arrange
        Vector<NolLabel> labelsPresent = createLabelsPresent();
        Vector<NolLabel> labelsAbsent = createLabelsAbsent();
        Vector<NolLabel> existLabels = createExistLabels(labelsPresent, labelsAbsent);

        this.sut = new LabelPattern(labelsPresent, labelsAbsent, existLabels);

        // Act & Assert
        assertThat(this.sut.hashCode(), is(equalTo(expectedHashCode(labelsPresent, labelsAbsent))));
    }

    @Test
    public void test_hasLabel_LabelIsAPresentLabel_retTrue() {
        // Arrange
        Vector<NolLabel> labelsPresent = createLabelsPresent();
        Vector<NolLabel> labelsAbsent = createLabelsAbsent();
        Vector<NolLabel> existLabels = createExistLabels(labelsPresent, labelsAbsent);

        this.sut = new LabelPattern(labelsPresent, labelsAbsent, existLabels);

        for (NolLabel aLabelsPresent : labelsPresent) {
            // Act & Assert
            assertTrue(this.sut.hasLabel(aLabelsPresent));
        }
    }

    @Test
    public void test_hasLabel_LabelIsAnAbsentLabel_retTrue() {
        // Arrange
        Vector<NolLabel> labelsPresent = createLabelsPresent();
        Vector<NolLabel> labelsAbsent = createLabelsAbsent();
        Vector<NolLabel> existLabels = createExistLabels(labelsPresent, labelsAbsent);

        this.sut = new LabelPattern(labelsPresent, labelsAbsent, existLabels);

        for (NolLabel aLabelsAbsent : labelsAbsent) {
            // Act & Assert
            assertTrue(this.sut.hasLabel(aLabelsAbsent));
        }
    }

    @Test
    public void test_hasLabel_LabelIsNotALabel_retFalse() {
        // Arrange
        Vector<NolLabel> labelsPresent = createLabelsPresent();
        Vector<NolLabel> labelsAbsent = createLabelsAbsent();
        Vector<NolLabel> existLabels = createExistLabels(labelsPresent, labelsAbsent);

        this.sut = new LabelPattern(labelsPresent, labelsAbsent, existLabels);

        // Act & Assert
        assertFalse(this.sut.hasLabel(anyNolLabel()));
    }

    private int anyIndex(int max) {
        return randomGenerator.nextInt(max);
    }

    private NolLabel anyNolLabel() {
        return new NolLabel();
    }

    private Vector<NolLabel> createExistLabels(Vector<NolLabel> labelsPresent, Vector<NolLabel> labelsAbsent) {
        Vector<NolLabel> existLabels = new Vector<>();

        existLabels.addAll(labelsPresent);
        existLabels.addAll(labelsAbsent);

        return existLabels;
    }

    private boolean[][] createFlagsMatrix(int presentLabelsCount, int absentLabelsCount, int rowsCount) {
        boolean[][] trueFlags = new boolean[presentLabelsCount + absentLabelsCount][rowsCount];

        for (int i = 0; i < presentLabelsCount; i++) {
            for (int j = 0; j < rowsCount; j++) {
                trueFlags[i][j] = true;
            }
        }

        for (int i = presentLabelsCount; i < presentLabelsCount + absentLabelsCount; i++) {
            for (int j = 0; j < rowsCount; j++) {
                trueFlags[i][j] = false;
            }
        }

        return trueFlags;
    }

    private LabelPattern createLabelPattern() {
        return new LabelPattern();
    }

    private Vector<NolLabel> createLabelsAbsent() {
        Vector<NolLabel> labelsAbsent = new Vector<>();

        labelsAbsent.addElement(new NolLabel("labelAbsent1"));
        labelsAbsent.addElement(new NolLabel("labelAbsent2"));
        labelsAbsent.addElement(new NolLabel("labelAbsent3"));

        return labelsAbsent;
    }

    private Vector<NolLabel> createLabelsPresent() {
        Vector<NolLabel> labelsPresent = new Vector<>();

        labelsPresent.addElement(new NolLabel("labelPresent1"));
        labelsPresent.addElement(new NolLabel("labelPresent2"));
        labelsPresent.addElement(new NolLabel("labelPresent3"));

        return labelsPresent;
    }

    private int expectedHashCode(Vector<NolLabel> labelsPresent, Vector<NolLabel> labelsAbsent) {
        final int prime = 31;
        int result = 1;
        result = prime * result + ((labelsPresent == null) ? 0 : labelsPresent.hashCode());
        result = prime * result + ((labelsAbsent == null) ? 0 : labelsAbsent.hashCode());
        return result;
    }
}