package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class LogFileParametersImplTest extends G2TestBase<LogFileParametersImpl> {

    @Override
    protected Class<LogFileParametersImpl> forClass() {
        return LogFileParametersImpl.class;
    }

    @Test
    public void test_setLogFileEnabled_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setLogFileEnabled(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.LOG_FILE_ENABLED_)).isEqualTo(false);
    }
    @Test
    public void test_getLogFileEnabled_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.LOG_FILE_ENABLED_, false);

        assertThat(instance.getLogFileEnabled()).isEqualTo(false);
    }


    @Test
    public void test_setDirectoryForLogFiles_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setDirectoryForLogFiles("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.DIRECTORY_FOR_LOG_FILES_)).isEqualTo("ABC");
    }
    @Test
    public void test_getDirectoryForLogFiles_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.DIRECTORY_FOR_LOG_FILES_, "ABC");

        assertThat(instance.getDirectoryForLogFiles()).isEqualTo("ABC");
    }


    @Test
    public void test_setRootNameForLogFiles_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setRootNameForLogFiles("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.ROOT_NAME_FOR_LOG_FILES_)).isEqualTo("ABC");
    }
    @Test
    public void test_getRootNameForLogFiles_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ROOT_NAME_FOR_LOG_FILES_, "ABC");

        assertThat(instance.getRootNameForLogFiles()).isEqualTo("ABC");
    }


    @Test
    public void test_getCurrentLogFile_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.CURRENT_LOG_FILE_, "ABC");

        assertThat(instance.getCurrentLogFile()).isEqualTo("ABC");
    }


    @Test
    public void test_setWhenToCloseCurrentLogFileAndOpenNextOne_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setWhenToCloseCurrentLogFileAndOpenNextOne(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.WHEN_TO_CLOSE_CURRENT_LOG_FILE_AND_OPEN_NEXT_ONE_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getWhenToCloseCurrentLogFileAndOpenNextOne_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.WHEN_TO_CLOSE_CURRENT_LOG_FILE_AND_OPEN_NEXT_ONE_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getWhenToCloseCurrentLogFileAndOpenNextOne()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_setWhenToBackUpCurrentLogFileOtherThanWhenClosing_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setWhenToBackUpCurrentLogFileOtherThanWhenClosing("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.WHEN_TO_BACK_UP_CURRENT_LOG_FILE_OTHER_THAN_WHEN_CLOSING_)).isEqualTo("ABC");
    }
    @Test
    public void test_getWhenToBackUpCurrentLogFileOtherThanWhenClosing_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.WHEN_TO_BACK_UP_CURRENT_LOG_FILE_OTHER_THAN_WHEN_CLOSING_, "ABC");

        assertThat(instance.getWhenToBackUpCurrentLogFileOtherThanWhenClosing()).isEqualTo("ABC");
    }


    @Test
    public void test_setMaximumNumberOfLogFiles_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setMaximumNumberOfLogFiles(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.MAXIMUM_NUMBER_OF_LOG_FILES_)).isEqualTo(42);
    }
    @Test
    public void test_getMaximumNumberOfLogFiles_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.MAXIMUM_NUMBER_OF_LOG_FILES_, 42);

        assertThat(instance.getMaximumNumberOfLogFiles()).isEqualTo(42);
    }


}