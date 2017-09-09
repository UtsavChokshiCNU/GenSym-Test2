package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class QuantitativeParameterImplTest extends G2TestBase<QuantitativeParameterImpl> {

    @Override
    protected Class<QuantitativeParameterImpl> forClass() {
        return QuantitativeParameterImpl.class;
    }

    @Test
    public void test_setInitialValue_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setInitialValue(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.INITIAL_VALUE_)).isEqualTo(42);
    }
    @Test
    public void test_getInitialValue_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.INITIAL_VALUE_, 42);

        assertThat(instance.getInitialValue()).isEqualTo(42);
    }


}