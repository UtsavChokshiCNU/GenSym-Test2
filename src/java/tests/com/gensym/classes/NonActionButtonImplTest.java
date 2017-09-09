package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class NonActionButtonImplTest extends G2TestBase<NonActionButtonImpl> {

    @Override
    protected Class<NonActionButtonImpl> forClass() {
        return NonActionButtonImpl.class;
    }

    @Test
    public void test_setValueOnActivation_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setValueOnActivation("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.VALUE_ON_ACTIVATION_)).isEqualTo("ABC");
    }
    @Test
    public void test_getValueOnActivation_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.VALUE_ON_ACTIVATION_, "ABC");

        assertThat(instance.getValueOnActivation()).isEqualTo("ABC");
    }


    @Test
    public void test_setVariableOrParameter_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setVariableOrParameter("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.VARIABLE_OR_PARAMETER_)).isEqualTo("ABC");
    }
    @Test
    public void test_getVariableOrParameter_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.VARIABLE_OR_PARAMETER_, "ABC");

        assertThat(instance.getVariableOrParameter()).isEqualTo("ABC");
    }


    @Test
    public void test_setEvaluationAttributes_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setEvaluationAttributes(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.EVALUATION_ATTRIBUTES_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getEvaluationAttributes_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.EVALUATION_ATTRIBUTES_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getEvaluationAttributes()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


}