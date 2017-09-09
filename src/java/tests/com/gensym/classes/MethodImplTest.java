package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class MethodImplTest extends G2TestBase<MethodImpl> {

    @Override
    protected Class<MethodImpl> forClass() {
        return MethodImpl.class;
    }

    @Test
    public void test_setSynchronized_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSynchronized(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.SYNCHRONIZED_)).isEqualTo(false);
    }
    @Test
    public void test_getSynchronized_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.SYNCHRONIZED_, false);

        assertThat(instance.getSynchronized()).isEqualTo(false);
    }


}