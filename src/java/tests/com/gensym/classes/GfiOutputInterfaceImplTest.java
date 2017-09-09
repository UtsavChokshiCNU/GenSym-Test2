package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class GfiOutputInterfaceImplTest extends G2TestBase<GfiOutputInterfaceImpl> {

    @Override
    protected Class<GfiOutputInterfaceImpl> forClass() {
        return GfiOutputInterfaceImpl.class;
    }

    @Test
    public void test_getFileSystem_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.FILE_SYSTEM_, "ABC");

        assertThat(instance.getFileSystem()).isEqualTo("ABC");
    }


    @Test
    public void test_getFileStatus_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.FILE_STATUS_, "ABC");

        assertThat(instance.getFileStatus()).isEqualTo("ABC");
    }


    @Test
    public void test_setMaximumNumberOfOutputLines_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setMaximumNumberOfOutputLines(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.MAXIMUM_NUMBER_OF_OUTPUT_LINES_)).isEqualTo(42);
    }
    @Test
    public void test_getMaximumNumberOfOutputLines_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.MAXIMUM_NUMBER_OF_OUTPUT_LINES_, 42);

        assertThat(instance.getMaximumNumberOfOutputLines()).isEqualTo(42);
    }


    @Test
    public void test_setGfiOutputValues_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setGfiOutputValues("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.GFI_OUTPUT_VALUES_)).isEqualTo("ABC");
    }
    @Test
    public void test_getGfiOutputValues_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.GFI_OUTPUT_VALUES_, "ABC");

        assertThat(instance.getGfiOutputValues()).isEqualTo("ABC");
    }


    @Test
    public void test_setGfiOutputFileUpdateFrequency_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setGfiOutputFileUpdateFrequency("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.GFI_OUTPUT_FILE_UPDATE_FREQUENCY_)).isEqualTo("ABC");
    }
    @Test
    public void test_getGfiOutputFileUpdateFrequency_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.GFI_OUTPUT_FILE_UPDATE_FREQUENCY_, "ABC");

        assertThat(instance.getGfiOutputFileUpdateFrequency()).isEqualTo("ABC");
    }


    @Test
    public void test_setGfiOutputTimeStampFormat_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setGfiOutputTimeStampFormat(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.GFI_OUTPUT_TIME_STAMP_FORMAT_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getGfiOutputTimeStampFormat_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.GFI_OUTPUT_TIME_STAMP_FORMAT_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getGfiOutputTimeStampFormat()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setGfiOutputFileFormat_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setGfiOutputFileFormat(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.GFI_OUTPUT_FILE_FORMAT_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getGfiOutputFileFormat_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.GFI_OUTPUT_FILE_FORMAT_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getGfiOutputFileFormat()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setRenamedGfiOutputFilePathname_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setRenamedGfiOutputFilePathname("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.RENAMED_GFI_OUTPUT_FILE_PATHNAME_)).isEqualTo("ABC");
    }
    @Test
    public void test_getRenamedGfiOutputFilePathname_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.RENAMED_GFI_OUTPUT_FILE_PATHNAME_, "ABC");

        assertThat(instance.getRenamedGfiOutputFilePathname()).isEqualTo("ABC");
    }


    @Test
    public void test_setGfiOutputFilePathname_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setGfiOutputFilePathname("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.GFI_OUTPUT_FILE_PATHNAME_)).isEqualTo("ABC");
    }
    @Test
    public void test_getGfiOutputFilePathname_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.GFI_OUTPUT_FILE_PATHNAME_, "ABC");

        assertThat(instance.getGfiOutputFilePathname()).isEqualTo("ABC");
    }


    @Test
    public void test_setGfiOutputWhenActive_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setGfiOutputWhenActive(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.GFI_OUTPUT_WHEN_ACTIVE_)).isEqualTo(false);
    }
    @Test
    public void test_getGfiOutputWhenActive_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.GFI_OUTPUT_WHEN_ACTIVE_, false);

        assertThat(instance.getGfiOutputWhenActive()).isEqualTo(false);
    }


    @Test
    public void test_setTextConversionStyle_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setTextConversionStyle(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.TEXT_CONVERSION_STYLE_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getTextConversionStyle_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.TEXT_CONVERSION_STYLE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getTextConversionStyle()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


}