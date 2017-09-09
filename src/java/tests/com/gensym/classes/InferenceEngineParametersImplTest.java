package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class InferenceEngineParametersImplTest extends G2TestBase<InferenceEngineParametersImpl> {

    @Override
    protected Class<InferenceEngineParametersImpl> forClass() {
        return InferenceEngineParametersImpl.class;
    }

    @Test
    public void test_setRecursionLimit_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setRecursionLimit(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.RECURSION_LIMIT_)).isEqualTo(42);
    }
    @Test
    public void test_getRecursionLimit_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.RECURSION_LIMIT_, 42);

        assertThat(instance.getRecursionLimit()).isEqualTo(42);
    }


    @Test
    public void test_setTruthThreshold_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setTruthThreshold(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.TRUTH_THRESHOLD_)).isEqualTo(false);
    }
    @Test
    public void test_getTruthThreshold_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.TRUTH_THRESHOLD_, false);

        assertThat(instance.getTruthThreshold()).isEqualTo(false);
    }


}