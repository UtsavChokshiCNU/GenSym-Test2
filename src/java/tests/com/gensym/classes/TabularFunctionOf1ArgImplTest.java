package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class TabularFunctionOf1ArgImplTest extends G2TestBase<TabularFunctionOf1ArgImpl> {

    @Override
    protected Class<TabularFunctionOf1ArgImpl> forClass() {
        return TabularFunctionOf1ArgImpl.class;
    }

    @Test
    public void test_setKeepSorted_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setKeepSorted(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.KEEP_SORTED_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getKeepSorted_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.KEEP_SORTED_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getKeepSorted()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setInterpolate_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setInterpolate(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.INTERPOLATE_)).isEqualTo(false);
    }
    @Test
    public void test_getInterpolate_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.INTERPOLATE_, false);

        assertThat(instance.getInterpolate()).isEqualTo(false);
    }


    @Test
    public void test_setValuesForTableOfValues_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setValuesForTableOfValues(getStub(com.gensym.util.Sequence.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.VALUES_FOR_TABLE_OF_VALUES_)).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }
    @Test
    public void test_getValuesForTableOfValues_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.VALUES_FOR_TABLE_OF_VALUES_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getValuesForTableOfValues()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


}