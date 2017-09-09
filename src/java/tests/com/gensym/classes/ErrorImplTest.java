package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class ErrorImplTest extends G2TestBase<ErrorImpl> {

    @Override
    protected Class<ErrorImpl> forClass() {
        return ErrorImpl.class;
    }

    @Test
    public void test_setErrorDescription_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setErrorDescription("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.ERROR_DESCRIPTION_)).isEqualTo("ABC");
    }
    @Test
    public void test_getErrorDescription_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ERROR_DESCRIPTION_, "ABC");

        assertThat(instance.getErrorDescription()).isEqualTo("ABC");
    }


    @Test
    public void test_getErrorSourceItem_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ERROR_SOURCE_ITEM_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getErrorSourceItem()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_getErrorSourceLine_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ERROR_SOURCE_LINE_, 42);

        assertThat(instance.getErrorSourceLine()).isEqualTo(42);
    }


    @Test
    public void test_getErrorSourceColumn_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ERROR_SOURCE_COLUMN_, 42);

        assertThat(instance.getErrorSourceColumn()).isEqualTo(42);
    }


    @Test
    public void test_getErrorSourceTrace_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ERROR_SOURCE_TRACE_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getErrorSourceTrace()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


}