package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class MessageBoardParametersImplTest extends G2TestBase<MessageBoardParametersImpl> {

    @Override
    protected Class<MessageBoardParametersImpl> forClass() {
        return MessageBoardParametersImpl.class;
    }

    @Test
    public void test_setInitialWidthOfMessageBoard_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setInitialWidthOfMessageBoard(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.INITIAL_WIDTH_OF_MESSAGE_BOARD_)).isEqualTo(42);
    }
    @Test
    public void test_getInitialWidthOfMessageBoard_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.INITIAL_WIDTH_OF_MESSAGE_BOARD_, 42);

        assertThat(instance.getInitialWidthOfMessageBoard()).isEqualTo(42);
    }


    @Test
    public void test_setInitialHeightOfMessageBoard_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setInitialHeightOfMessageBoard(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.INITIAL_HEIGHT_OF_MESSAGE_BOARD_)).isEqualTo(42);
    }
    @Test
    public void test_getInitialHeightOfMessageBoard_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.INITIAL_HEIGHT_OF_MESSAGE_BOARD_, 42);

        assertThat(instance.getInitialHeightOfMessageBoard()).isEqualTo(42);
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
    public void test_setMaximumNumberOfEntries_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setMaximumNumberOfEntries(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.MAXIMUM_NUMBER_OF_ENTRIES_)).isEqualTo(42);
    }
    @Test
    public void test_getMaximumNumberOfEntries_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.MAXIMUM_NUMBER_OF_ENTRIES_, 42);

        assertThat(instance.getMaximumNumberOfEntries()).isEqualTo(42);
    }


    @Test
    public void test_setHighlightNewMessages_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setHighlightNewMessages(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.HIGHLIGHT_NEW_MESSAGES_)).isEqualTo(false);
    }
    @Test
    public void test_getHighlightNewMessages_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.HIGHLIGHT_NEW_MESSAGES_, false);

        assertThat(instance.getHighlightNewMessages()).isEqualTo(false);
    }


    @Test
    public void test_setMinimumDisplayInterval_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setMinimumDisplayInterval("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.MINIMUM_DISPLAY_INTERVAL_)).isEqualTo("ABC");
    }
    @Test
    public void test_getMinimumDisplayInterval_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.MINIMUM_DISPLAY_INTERVAL_, "ABC");

        assertThat(instance.getMinimumDisplayInterval()).isEqualTo("ABC");
    }


    @Test
    public void test_setPreferNativeMessageBoard_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setPreferNativeMessageBoard(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.PREFER_NATIVE_MESSAGE_BOARD_)).isEqualTo(false);
    }
    @Test
    public void test_getPreferNativeMessageBoard_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.PREFER_NATIVE_MESSAGE_BOARD_, false);

        assertThat(instance.getPreferNativeMessageBoard()).isEqualTo(false);
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