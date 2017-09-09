package com.gensym.nols.util;

import static org.hamcrest.CoreMatchers.is;
import static org.hamcrest.MatcherAssert.assertThat;
import static org.mockito.Matchers.anyInt;
import static org.mockito.Matchers.eq;
import static org.mockito.Mockito.doReturn;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.never;
import static org.mockito.Mockito.spy;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;

import java.awt.Color;
import java.math.BigInteger;
import java.util.Date;

import javax.swing.table.TableModel;

import org.junit.Before;
import org.junit.Test;
import org.powermock.core.classloader.annotations.PrepareForTest;

@PrepareForTest({ColumnSorter.class})
public class ColumnSorterTest {

    final int COLUMN_INDEX = 2;

    private TableModel model;
    private ColumnSorter columnSorter;

    @Before
    public void setup() {
        model = mock(TableModel.class);
        final int[] column = {0, 1, 2, 3, 4};
        columnSorter = spy(new ColumnSorter(model, column));
    }

    /**
     * When column index is unavailable in array then it returns 0
     */
    @Test
    public void test_compareRowsByColumn_IndexUnavailable_returnsZero() {
        //Act and Assert
        assertThat(columnSorter.compareRowsByColumn(1, 1, 10), is(0));
    }

    /**
     * When columnIndexIsAvailableInArray but o1 and o2 are null then it returns 0
     */
    @Test
    public void test_compareRowsByColumn_o1Ando2AreNull_returnsZero() {
        //Act and Assert
        assertThat(columnSorter.compareRowsByColumn(1, 1, COLUMN_INDEX), is(0));
    }

    /**
     * When columnIndexIsAvailableInArray but o2 is null then it returns 1
     */
    @Test
    public void test_compareRowsByColumn_o2IsNull_returnsOne() {
        //Arrange
        when(model.getValueAt(1, COLUMN_INDEX)).thenReturn(new Object());

        //Act and Assert
        assertThat(columnSorter.compareRowsByColumn(1, 2, COLUMN_INDEX), is(1));
    }

    /**
     * When columnIndexIsAvailableInArray but o1 is null then it returns -1
     */
    @Test
    public void test_compareRowsByColumn_o1IsNull_returnsMinusOne() {
        //Arrange
        when(model.getValueAt(2, COLUMN_INDEX)).thenReturn(new Object());

        //Act and Assert
        assertThat(columnSorter.compareRowsByColumn(1, 2, COLUMN_INDEX), is(-1));
    }

    /**
     * when both numbers are equal then it returns 0
     */
    @Test
    public void test_compareRowsByColumn_BothNumbersAreEqual_returnsZero() {
        //Arrange
        when(model.getValueAt(anyInt(), eq(COLUMN_INDEX))).thenReturn(10);
        when(model.getColumnClass(COLUMN_INDEX)).thenReturn((Class) BigInteger.class);

        //Act and Assert
        assertThat(columnSorter.compareRowsByColumn(1, 2, COLUMN_INDEX), is(0));
    }

    /**
     * when numbers 1 is less than number 2 then it returns -1
     */
    @Test
    public void test_compareRowsByColumn_N1IsLessThanN2_returnsMinusOne() {
        //Arrange
        when(model.getValueAt(1, COLUMN_INDEX)).thenReturn(9);
        when(model.getValueAt(2, COLUMN_INDEX)).thenReturn(10);
        when(model.getColumnClass(COLUMN_INDEX)).thenReturn((Class) BigInteger.class);

        //Act and Assert
        assertThat(columnSorter.compareRowsByColumn(1, 2, COLUMN_INDEX), is(-1));
    }

    /**
     * when numbers 1 is greater than number 2 then it returns 1
     */
    @Test
    public void test_compareRowsByColumn_N1IsMoreThanN2_returnsOne() {
        //Arrange
        when(model.getValueAt(1, COLUMN_INDEX)).thenReturn(9);
        when(model.getValueAt(2, COLUMN_INDEX)).thenReturn(8);
        when(model.getColumnClass(COLUMN_INDEX)).thenReturn((Class) BigInteger.class);

        //Act and Assert
        assertThat(columnSorter.compareRowsByColumn(1, 2, COLUMN_INDEX), is(1));
    }

    /**
     * when both the dates are same then it returns 0
     */
    @Test
    public void test_compareRowsByColumn_BothDatesAreEqual_returnsZero() {
        //Arrange
        when(model.getValueAt(anyInt(), eq(COLUMN_INDEX))).thenReturn(new Date());
        when(model.getColumnClass(COLUMN_INDEX)).thenReturn((Class) Date.class);

        //Act and Assert
        assertThat(columnSorter.compareRowsByColumn(1, 2, COLUMN_INDEX), is(0));
    }

    /**
     * when date 1 is less than date 2 then it returns -1
     */
    @Test
    public void test_compareRowsByColumn_Date1IsLessThanDate2_returnsMinusOne() {
        //Arrange
        final Date currentDate = new Date();
        when(model.getValueAt(1, COLUMN_INDEX)).thenReturn(currentDate);
        when(model.getValueAt(2, COLUMN_INDEX)).thenReturn(new Date(currentDate.getTime() + 1));
        when(model.getColumnClass(COLUMN_INDEX)).thenReturn((Class) Date.class);

        //Act and Assert
        assertThat(columnSorter.compareRowsByColumn(1, 2, COLUMN_INDEX), is(-1));
    }

    /**
     * when date 1 is greater than date 2 then it returns 1
     */
    @Test
    public void test_compareRowsByColumn_Date1IsMoreThanDate2_returnsOne() {
        //Arrange
        final Date currentDate = new Date();
        when(model.getValueAt(1, COLUMN_INDEX)).thenReturn(new Date(currentDate.getTime() + 1));
        when(model.getValueAt(2, COLUMN_INDEX)).thenReturn(currentDate);
        when(model.getColumnClass(COLUMN_INDEX)).thenReturn((Class) Date.class);

        //Act and Assert
        assertThat(columnSorter.compareRowsByColumn(1, 2, COLUMN_INDEX), is(1));
    }

    /**
     * when both string numbers are equal returns 0
     */
    @Test
    public void test_compareRowsByColumn_BothStringNumbersAreEqual_returnsZero() {
        //Arrange
        when(model.getValueAt(anyInt(), eq(COLUMN_INDEX))).thenReturn("10");
        when(model.getColumnClass(COLUMN_INDEX)).thenReturn((Class) String.class);

        //Act and Assert
        assertThat(columnSorter.compareRowsByColumn(1, 2, COLUMN_INDEX), is(0));
    }

    /**
     * when both string number 1 is less than string number 2 then it returns -1
     */
    @Test
    public void test_compareRowsByColumn_StringN1IsLessThanStringN2_returnsMinusOne() {
        //Arrange
        when(model.getValueAt(1, COLUMN_INDEX)).thenReturn("9");
        when(model.getValueAt(2, COLUMN_INDEX)).thenReturn("10");
        when(model.getColumnClass(COLUMN_INDEX)).thenReturn((Class) String.class);

        //Act and Assert
        assertThat(columnSorter.compareRowsByColumn(1, 2, COLUMN_INDEX), is(-1));
    }

    /**
     * when both string number 1 is greater than string number 2 then it returns 1
     */
    @Test
    public void test_compareRowsByColumn_StringN1IsMoreThanStringN2_returnsOne() {
        //Arrange
        when(model.getValueAt(1, COLUMN_INDEX)).thenReturn("9");
        when(model.getValueAt(2, COLUMN_INDEX)).thenReturn("8");
        when(model.getColumnClass(COLUMN_INDEX)).thenReturn((Class) String.class);

        //Act and Assert
        assertThat(columnSorter.compareRowsByColumn(1, 2, COLUMN_INDEX), is(1));
    }

    /**
     * when both string are equal then it returns 0
     */
    @Test
    public void test_compareRowsByColumn_BothStringAreEqual_returnsZero() {
        //Arrange
        when(model.getValueAt(anyInt(), eq(COLUMN_INDEX))).thenReturn("A");
        when(model.getColumnClass(COLUMN_INDEX)).thenReturn((Class) String.class);

        //Act and Assert
        assertThat(columnSorter.compareRowsByColumn(1, 2, COLUMN_INDEX), is(0));
    }

    /**
     * when both string 1 is less than string 2 then it returns -1
     */
    @Test
    public void test_compareRowsByColumn_firstStrIsLessThanSecondStr_returnsMinusOne() {
        //Arrange
        when(model.getValueAt(1, COLUMN_INDEX)).thenReturn("A");
        when(model.getValueAt(2, COLUMN_INDEX)).thenReturn("B");
        when(model.getColumnClass(COLUMN_INDEX)).thenReturn((Class) String.class);

        //Act and Assert
        assertThat(columnSorter.compareRowsByColumn(1, 2, COLUMN_INDEX), is(-1));
    }

    /**
     * when both string 1 is greater than string 2 then it returns 1
     */
    @Test
    public void test_compareRowsByColumn_firstStrIsMoreThanSecondStr_returnsOne() {
        //Arrange
        when(model.getValueAt(1, COLUMN_INDEX)).thenReturn("B");
        when(model.getValueAt(2, COLUMN_INDEX)).thenReturn("A");
        when(model.getColumnClass(COLUMN_INDEX)).thenReturn((Class) String.class);

        //Act and Assert
        assertThat(columnSorter.compareRowsByColumn(1, 2, COLUMN_INDEX), is(1));
    }

    /**
     * when both boolean values are same then it returns 0
     */
    @Test
    public void test_compareRowsByColumn_BothBoolValuesAreSame_returnsZero() {
        //Arrange
        when(model.getValueAt(anyInt(), eq(COLUMN_INDEX))).thenReturn(true);
        when(model.getColumnClass(COLUMN_INDEX)).thenReturn((Class) Boolean.class);

        //Act and Assert
        assertThat(columnSorter.compareRowsByColumn(1, 2, COLUMN_INDEX), is(0));
    }

    /**
     * when first boolean is true then it returns -1
     */
    @Test
    public void test_compareRowsByColumn_firstBooleanIsTrue_returnsMinusOne() {
        //Arrange
        when(model.getValueAt(1, COLUMN_INDEX)).thenReturn(false);
        when(model.getValueAt(2, COLUMN_INDEX)).thenReturn(true);
        when(model.getColumnClass(COLUMN_INDEX)).thenReturn((Class) Boolean.class);

        //Act and Assert
        assertThat(columnSorter.compareRowsByColumn(1, 2, COLUMN_INDEX), is(-1));
    }

    /**
     * when first boolean is false then it returns 1
     */
    @Test
    public void test_compareRowsByColumn_firstBooleanIsFalse_returnsOne() {
        //Arrange
        when(model.getValueAt(1, COLUMN_INDEX)).thenReturn(true);
        when(model.getValueAt(2, COLUMN_INDEX)).thenReturn(false);
        when(model.getColumnClass(COLUMN_INDEX)).thenReturn((Class) Boolean.class);

        //Act and Assert
        assertThat(columnSorter.compareRowsByColumn(1, 2, COLUMN_INDEX), is(1));
    }

    /**
     * when both colored bar values are equal then it returns 0
     */
    @Test
    public void test_compareRowsByColumn_BothColoredBarValuesAreEqual_returnsZero() {
        //Arrange
        final ColoredBar coloredBar = new ColoredBar(Color.black, true, 1, 1);
        when(model.getValueAt(anyInt(), eq(COLUMN_INDEX))).thenReturn(coloredBar);
        when(model.getColumnClass(COLUMN_INDEX)).thenReturn((Class) ColoredBar.class);

        //Act and Assert
        assertThat(columnSorter.compareRowsByColumn(1, 2, COLUMN_INDEX), is(0));
    }

    /**
     * when colored bar one value is less than colored bar two then it returns -1
     */
    @Test
    public void test_compareRowsByColumn_barOneValIsLessThanBarTwoVal_returnsMinusOne() {
        //Arrange
        final ColoredBar coloredBarOne = new ColoredBar(Color.black, true, 1, 1);
        final ColoredBar coloredBarTwo = new ColoredBar(Color.black, true, 2, 1);
        when(model.getValueAt(1, COLUMN_INDEX)).thenReturn(coloredBarOne);
        when(model.getValueAt(2, COLUMN_INDEX)).thenReturn(coloredBarTwo);
        when(model.getColumnClass(COLUMN_INDEX)).thenReturn((Class) ColoredBar.class);

        //Act and Assert
        assertThat(columnSorter.compareRowsByColumn(1, 2, COLUMN_INDEX), is(-1));
    }

    /**
     * when colored bar one value is greater than colored bar two then it returns 1
     */
    @Test
    public void test_compareRowsByColumn_barOneValIsMoreThanBarTwoVal_returnsOne() {
        //Arrange
        final ColoredBar coloredBarOne = new ColoredBar(Color.black, true, 2, 1);
        final ColoredBar coloredBarTwo = new ColoredBar(Color.black, true, 1, 1);
        when(model.getValueAt(1, COLUMN_INDEX)).thenReturn(coloredBarOne);
        when(model.getValueAt(2, COLUMN_INDEX)).thenReturn(coloredBarTwo);
        when(model.getColumnClass(COLUMN_INDEX)).thenReturn((Class) ColoredBar.class);

        //Act and Assert
        assertThat(columnSorter.compareRowsByColumn(1, 2, COLUMN_INDEX), is(1));
    }

    /**
     * when both string objects are equal then it returns zero
     */
    @Test
    public void test_compareRowsByColumn_BothStringObjectsAreEqual_returnsZero() {
        //Arrange
        when(model.getValueAt(anyInt(), eq(COLUMN_INDEX))).thenReturn("A");
        when(model.getColumnClass(COLUMN_INDEX)).thenReturn((Class) Object.class);

        //Act and Assert
        assertThat(columnSorter.compareRowsByColumn(1, 2, COLUMN_INDEX), is(0));
    }

    /**
     * when first string object is less than second string object then it returns -1
     */
    @Test
    public void test_compareRowsByColumn_firstStrObjIsLessThanSecondStrObj_returnsMinusOne() {
        //Arrange
        when(model.getValueAt(1, COLUMN_INDEX)).thenReturn("A");
        when(model.getValueAt(2, COLUMN_INDEX)).thenReturn("B");
        when(model.getColumnClass(COLUMN_INDEX)).thenReturn((Class) Object.class);

        //Act and Assert
        assertThat(columnSorter.compareRowsByColumn(1, 2, COLUMN_INDEX), is(-1));
    }

    /**
     * when first string object is greater than second string object then it returns 1
     */
    @Test
    public void test_compareRowsByColumn_firstStrObjIsMoreThanSecondStrObj_returnsOne() {
        //Arrange
        when(model.getValueAt(1, COLUMN_INDEX)).thenReturn("B");
        when(model.getValueAt(2, COLUMN_INDEX)).thenReturn("A");
        when(model.getColumnClass(COLUMN_INDEX)).thenReturn((Class) Object.class);

        //Act and Assert
        assertThat(columnSorter.compareRowsByColumn(1, 2, COLUMN_INDEX), is(1));
    }

    /**
     * ascendingOrder false and compareRowsByColumn Returns 1 so it returns -1
     */
    @Test
    public void test_compare_descendingAndcompareRowsByColumnReturnsOne_returnsMinusOne() {
        //Arrange
        columnSorter.sortingColumns.add(1);
        columnSorter.sortingColumns.add(2);
        doReturn(1).when(columnSorter).compareRowsByColumn(1, 2, 1);

        //Act and Assert
        assertThat(columnSorter.compare(1, 2), is(-1));
    }

    /**
     * ascendingOrder true and compareRowsByColumn Returns 1 so it returns 1
     */
    @Test
    public void test_compare_ascendingAndcompareRowsByColumnReturnsOne_returnsOne() {
        //Arrange
        columnSorter.sortingColumns.add(1);
        columnSorter.sortingColumns.add(2);
        doReturn(1).when(columnSorter).compareRowsByColumn(1, 2, 1);
        columnSorter.ascending = true;

        //Act and Assert
        assertThat(columnSorter.compare(1, 2), is(1));
    }

    /**
     * ascendingOrder true and compareRowsByColumn Returns 0 so it returns 0
     */
    @Test
    public void test_compare_ascendingAndcompareRowsByColumnReturnsZero_returnsZero() {
        //Arrange
        columnSorter.sortingColumns.add(1);
        columnSorter.sortingColumns.add(2);
        doReturn(0).when(columnSorter).compareRowsByColumn(1, 2, 1);
        columnSorter.ascending = true;

        //Act and Assert
        assertThat(columnSorter.compare(1, 2), is(0));
    }

    /**
     * unsorted numbers are shuttle sorted
     */
    @Test
    public void test_shuttlesort_unsortedNumber_returnsShuttleSortedList() {
        //Arrange
        final int[] from = {2, 1, 4, 3, 9};
        final int[] to = {1, 3, 2, 5, 4};
        final int[] expectedResult = {1, 3, 2, 5, 9};

        //Act
        columnSorter.shuttlesort(from, to, 0, 4);

        //Assert
        assertThat(from, is(expectedResult));
    }

    /**
     * unsorted numbers with duplicates are shuttle sorted
     */
    @Test
    public void test_shuttlesort_unsortedNumberWithDuplicates_returnsShuttleSortedList() {
        //Arrange
        final int[] from = {2, 2, 1, 3, 9};
        final int[] to = {1, 3, 4, 5, 5};
        final int[] expectedResult = {1, 3, 4, 5, 9};

        //Act
        columnSorter.shuttlesort(from, to, 0, 4);

        //Assert
        assertThat(from, is(expectedResult));
    }


    /**
     * single element are shuttle sorted
     */
    @Test
    public void test_shuttlesort_singleElementInFromAndTo_returnsShuttleSortedList() {
        //Arrange
        final int[] from = {1};
        final int[] to = {2};
        final int[] expectedResult = {1};

        //Act
        columnSorter.shuttlesort(from, to, 0, 1);

        //Assert
        assertThat(from, is(expectedResult));
    }

    /**
     * unsorted numbers with duplicates are shuttle sorted
     */
    @Test
    public void test_shuttlesort_singleElementInTo_returnsShuttleSortedList() {
        //Arrange
        final int[] from = {2,5,2,3};
        final int[] to = {1};
        final int[] expectedResult = {2,5,2,3};

        //Act
        columnSorter.shuttlesort(from, to, 0, 1);

        //Assert
        assertThat(from, is(expectedResult));
    }

    /**
     * When column value found it calls setValueAt and sets value
     */
    @Test
    public void test_setValueAt_ColumnValueFound_setsValue() {
        //Arrange
        final Object aValue = 1;
        final int aRow = 2;
        final int aColumn = 3;
        columnSorter.indexes = new int[3];
        columnSorter.indexes[0] = 10;
        columnSorter.indexes[1] = 11;
        columnSorter.indexes[2] = 12;

        //Act
        columnSorter.setValueAt(aValue, aRow, aColumn);

        //Assert
        verify(model).setValueAt(1,12,3);
    }

    /**
     * When column value not found it doesn't call setValueAt and returns from mid
     */
    @Test
    public void test_setValueAt_ColumnValueNotFound_doesntSetValue() {
        //Arrange
        final Object aValue = 1;
        final int aRow = 2;
        final int aColumn = 13;
        columnSorter.indexes = new int[3];
        columnSorter.indexes[0] = 10;
        columnSorter.indexes[1] = 11;
        columnSorter.indexes[2] = 12;

        //Act
        columnSorter.setValueAt(aValue, aRow, aColumn);

        //Assert
        verify(model,never()).setValueAt(anyInt(),anyInt(),anyInt());
    }
}
