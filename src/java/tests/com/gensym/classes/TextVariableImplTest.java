package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class TextVariableImplTest extends G2TestBase<TextVariableImpl> {

    @Override
    protected Class<TextVariableImpl> forClass() {
        return TextVariableImpl.class;
    }

    @Test
    public void test_setInitialValue_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setInitialValue("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.INITIAL_VALUE_)).isEqualTo("ABC");
    }
    @Test
    public void test_getInitialValue_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.INITIAL_VALUE_, "ABC");

        assertThat(instance.getInitialValue()).isEqualTo("ABC");
    }


}