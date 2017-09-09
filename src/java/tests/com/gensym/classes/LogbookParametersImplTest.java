package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class LogbookParametersImplTest extends G2TestBase<LogbookParametersImpl> {

    @Override
    protected Class<LogbookParametersImpl> forClass() {
        return LogbookParametersImpl.class;
    }

    @Test
    public void test_setWidthForPages_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setWidthForPages(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.WIDTH_FOR_PAGES_)).isEqualTo(42);
    }
    @Test
    public void test_getWidthForPages_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.WIDTH_FOR_PAGES_, 42);

        assertThat(instance.getWidthForPages()).isEqualTo(42);
    }


    @Test
    public void test_setHeightForPages_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setHeightForPages(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.HEIGHT_FOR_PAGES_)).isEqualTo(42);
    }
    @Test
    public void test_getHeightForPages_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.HEIGHT_FOR_PAGES_, 42);

        assertThat(instance.getHeightForPages()).isEqualTo(42);
    }


    @Test
    public void test_setMarginForPages_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setMarginForPages(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.MARGIN_FOR_PAGES_)).isEqualTo(42);
    }
    @Test
    public void test_getMarginForPages_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.MARGIN_FOR_PAGES_, 42);

        assertThat(instance.getMarginForPages()).isEqualTo(42);
    }


    @Test
    public void test_setXOffsetForNextPage_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setXOffsetForNextPage(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.X_OFFSET_FOR_NEXT_PAGE_)).isEqualTo(42);
    }
    @Test
    public void test_getXOffsetForNextPage_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.X_OFFSET_FOR_NEXT_PAGE_, 42);

        assertThat(instance.getXOffsetForNextPage()).isEqualTo(42);
    }


    @Test
    public void test_setYOffsetForNextPage_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setYOffsetForNextPage(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.Y_OFFSET_FOR_NEXT_PAGE_)).isEqualTo(42);
    }
    @Test
    public void test_getYOffsetForNextPage_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.Y_OFFSET_FOR_NEXT_PAGE_, 42);

        assertThat(instance.getYOffsetForNextPage()).isEqualTo(42);
    }


    @Test
    public void test_setXOffsetForLogbook_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setXOffsetForLogbook(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.X_OFFSET_FOR_LOGBOOK_)).isEqualTo(42);
    }
    @Test
    public void test_getXOffsetForLogbook_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.X_OFFSET_FOR_LOGBOOK_, 42);

        assertThat(instance.getXOffsetForLogbook()).isEqualTo(42);
    }


    @Test
    public void test_setYOffsetForLogbook_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setYOffsetForLogbook(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.Y_OFFSET_FOR_LOGBOOK_)).isEqualTo(42);
    }
    @Test
    public void test_getYOffsetForLogbook_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.Y_OFFSET_FOR_LOGBOOK_, 42);

        assertThat(instance.getYOffsetForLogbook()).isEqualTo(42);
    }


    @Test
    public void test_setMaximumNumberOfPagesToShow_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setMaximumNumberOfPagesToShow(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.MAXIMUM_NUMBER_OF_PAGES_TO_SHOW_)).isEqualTo(42);
    }
    @Test
    public void test_getMaximumNumberOfPagesToShow_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.MAXIMUM_NUMBER_OF_PAGES_TO_SHOW_, 42);

        assertThat(instance.getMaximumNumberOfPagesToShow()).isEqualTo(42);
    }


    @Test
    public void test_setNumberOfPagesToShedAtLimit_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setNumberOfPagesToShedAtLimit(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.NUMBER_OF_PAGES_TO_SHED_AT_LIMIT_)).isEqualTo(42);
    }
    @Test
    public void test_getNumberOfPagesToShedAtLimit_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.NUMBER_OF_PAGES_TO_SHED_AT_LIMIT_, 42);

        assertThat(instance.getNumberOfPagesToShedAtLimit()).isEqualTo(42);
    }


    @Test
    public void test_setSpacingBetweenEntries_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSpacingBetweenEntries(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.SPACING_BETWEEN_ENTRIES_)).isEqualTo(42);
    }
    @Test
    public void test_getSpacingBetweenEntries_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.SPACING_BETWEEN_ENTRIES_, 42);

        assertThat(instance.getSpacingBetweenEntries()).isEqualTo(42);
    }


    @Test
    public void test_setLogInformMessages_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setLogInformMessages(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.LOG_INFORM_MESSAGES_)).isEqualTo(false);
    }
    @Test
    public void test_getLogInformMessages_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.LOG_INFORM_MESSAGES_, false);

        assertThat(instance.getLogInformMessages()).isEqualTo(false);
    }


    @Test
    public void test_setMaximumNumberOfPagesToKeepInMemory_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setMaximumNumberOfPagesToKeepInMemory(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.MAXIMUM_NUMBER_OF_PAGES_TO_KEEP_IN_MEMORY_)).isEqualTo(42);
    }
    @Test
    public void test_getMaximumNumberOfPagesToKeepInMemory_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.MAXIMUM_NUMBER_OF_PAGES_TO_KEEP_IN_MEMORY_, 42);

        assertThat(instance.getMaximumNumberOfPagesToKeepInMemory()).isEqualTo(42);
    }


    @Test
    public void test_setLiftLogbookToTopWhenNewPagesAreAdded_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setLiftLogbookToTopWhenNewPagesAreAdded(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.LIFT_LOGBOOK_TO_TOP_WHEN_NEW_PAGES_ARE_ADDEDQ_)).isEqualTo(false);
    }
    @Test
    public void test_getLiftLogbookToTopWhenNewPagesAreAdded_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.LIFT_LOGBOOK_TO_TOP_WHEN_NEW_PAGES_ARE_ADDEDQ_, false);

        assertThat(instance.getLiftLogbookToTopWhenNewPagesAreAdded()).isEqualTo(false);
    }


    @Test
    public void test_setPreferNativeLogbook_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setPreferNativeLogbook(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.PREFER_NATIVE_LOGBOOK_)).isEqualTo(false);
    }
    @Test
    public void test_getPreferNativeLogbook_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.PREFER_NATIVE_LOGBOOK_, false);

        assertThat(instance.getPreferNativeLogbook()).isEqualTo(false);
    }


    @Test
    public void test_setIncludeDateInMessages_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setIncludeDateInMessages(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.INCLUDE_DATE_IN_MESSAGES_)).isEqualTo(false);
    }
    @Test
    public void test_getIncludeDateInMessages_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.INCLUDE_DATE_IN_MESSAGES_, false);

        assertThat(instance.getIncludeDateInMessages()).isEqualTo(false);
    }


}