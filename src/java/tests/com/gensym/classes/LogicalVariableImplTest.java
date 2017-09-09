package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class LogicalVariableImplTest extends G2TestBase<LogicalVariableImpl> {

    @Override
    protected Class<LogicalVariableImpl> forClass() {
        return LogicalVariableImpl.class;
    }

    @Test
    public void test_setInitialValue_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setInitialValue(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.INITIAL_VALUE_)).isEqualTo(false);
    }
    @Test
    public void test_getInitialValue_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.INITIAL_VALUE_, false);

        assertThat(instance.getInitialValue()).isEqualTo(false);
    }


}