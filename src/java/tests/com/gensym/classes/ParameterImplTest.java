package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class ParameterImplTest extends G2TestBase<ParameterImpl> {

    @Override
    protected Class<ParameterImpl> forClass() {
        return ParameterImpl.class;
    }

    @Test
    public void test_setOptions_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setOptions(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.OPTIONS_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getOptions_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.OPTIONS_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getOptions()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


}