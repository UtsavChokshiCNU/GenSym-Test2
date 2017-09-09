package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class GfiInputInterfaceImplTest extends G2TestBase<GfiInputInterfaceImpl> {

    @Override
    protected Class<GfiInputInterfaceImpl> forClass() {
        return GfiInputInterfaceImpl.class;
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
    public void test_setIgnoreGfiInputBaseTime_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setIgnoreGfiInputBaseTime(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.IGNORE_GFI_INPUT_BASE_TIME_)).isEqualTo(false);
    }
    @Test
    public void test_getIgnoreGfiInputBaseTime_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.IGNORE_GFI_INPUT_BASE_TIME_, false);

        assertThat(instance.getIgnoreGfiInputBaseTime()).isEqualTo(false);
    }


    @Test
    public void test_setGfiInputVariablesUpdateMode_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setGfiInputVariablesUpdateMode(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.GFI_INPUT_VARIABLES_UPDATE_MODE_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getGfiInputVariablesUpdateMode_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.GFI_INPUT_VARIABLES_UPDATE_MODE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getGfiInputVariablesUpdateMode()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setGfiInputTimeStampFormat_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setGfiInputTimeStampFormat(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.GFI_INPUT_TIME_STAMP_FORMAT_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getGfiInputTimeStampFormat_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.GFI_INPUT_TIME_STAMP_FORMAT_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getGfiInputTimeStampFormat()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setGfiInputFileFormat_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setGfiInputFileFormat(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.GFI_INPUT_FILE_FORMAT_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getGfiInputFileFormat_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.GFI_INPUT_FILE_FORMAT_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getGfiInputFileFormat()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setGfiInputFilePathname_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setGfiInputFilePathname("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.GFI_INPUT_FILE_PATHNAME_)).isEqualTo("ABC");
    }
    @Test
    public void test_getGfiInputFilePathname_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.GFI_INPUT_FILE_PATHNAME_, "ABC");

        assertThat(instance.getGfiInputFilePathname()).isEqualTo("ABC");
    }


    @Test
    public void test_setGfiInputWhenActive_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setGfiInputWhenActive(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.GFI_INPUT_WHEN_ACTIVE_)).isEqualTo(false);
    }
    @Test
    public void test_getGfiInputWhenActive_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.GFI_INPUT_WHEN_ACTIVE_, false);

        assertThat(instance.getGfiInputWhenActive()).isEqualTo(false);
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