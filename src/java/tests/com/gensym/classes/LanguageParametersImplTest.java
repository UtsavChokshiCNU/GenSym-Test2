package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class LanguageParametersImplTest extends G2TestBase<LanguageParametersImpl> {

    @Override
    protected Class<LanguageParametersImpl> forClass() {
        return LanguageParametersImpl.class;
    }

    @Test
    public void test_setCurrentLanguage_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setCurrentLanguage(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.CURRENT_LANGUAGE_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getCurrentLanguage_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.CURRENT_LANGUAGE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getCurrentLanguage()).isEqualTo(getStub(com.gensym.util.Symbol.class));
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