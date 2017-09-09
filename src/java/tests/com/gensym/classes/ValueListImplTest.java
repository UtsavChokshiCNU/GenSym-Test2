package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class ValueListImplTest extends G2TestBase<ValueListImpl> {

    @Override
    protected Class<ValueListImpl> forClass() {
        return ValueListImpl.class;
    }

    @Test
    public void test_setG2ListSequence_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setG2ListSequence(getStub(com.gensym.util.Sequence.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.G2_LIST_SEQUENCE_)).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }
    @Test
    public void test_getG2ListSequence_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_LIST_SEQUENCE_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getG2ListSequence()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


}