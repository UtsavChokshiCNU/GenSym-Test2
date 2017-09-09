package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class PrinterSetupImplTest extends G2TestBase<PrinterSetupImpl> {

    @Override
    protected Class<PrinterSetupImpl> forClass() {
        return PrinterSetupImpl.class;
    }

    @Test
    public void test_setPrintingDetails_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setPrintingDetails(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.PRINTING_DETAILS_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getPrintingDetails_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.PRINTING_DETAILS_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getPrintingDetails()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_setPageLayout_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setPageLayout(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.PAGE_LAYOUT_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getPageLayout_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.PAGE_LAYOUT_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getPageLayout()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_setPrintSpooling_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setPrintSpooling(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.PRINT_SPOOLING_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getPrintSpooling_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.PRINT_SPOOLING_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getPrintSpooling()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_setPrintingPriority_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setPrintingPriority(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.PRINTING_PRIORITY_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getPrintingPriority_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.PRINTING_PRIORITY_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getPrintingPriority()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setPrintingFileFormat_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setPrintingFileFormat(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.PRINTING_FILE_FORMAT_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getPrintingFileFormat_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.PRINTING_FILE_FORMAT_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getPrintingFileFormat()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setPageEconomyMode_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setPageEconomyMode(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.PAGE_ECONOMY_MODE_)).isEqualTo(false);
    }
    @Test
    public void test_getPageEconomyMode_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.PAGE_ECONOMY_MODE_, false);

        assertThat(instance.getPageEconomyMode()).isEqualTo(false);
    }


}