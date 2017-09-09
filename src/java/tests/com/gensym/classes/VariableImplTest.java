package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class VariableImplTest extends G2TestBase<VariableImpl> {

    @Override
    protected Class<VariableImpl> forClass() {
        return VariableImpl.class;
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


    @Test
    public void test_setValidityInterval_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setValidityInterval("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.VALIDITY_INTERVAL_)).isEqualTo("ABC");
    }
    @Test
    public void test_getValidityInterval_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.VALIDITY_INTERVAL_, "ABC");

        assertThat(instance.getValidityInterval()).isEqualTo("ABC");
    }


    @Test
    public void test_setFormula_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setFormula("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.FORMULA_)).isEqualTo("ABC");
    }
    @Test
    public void test_getFormula_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.FORMULA_, "ABC");

        assertThat(instance.getFormula()).isEqualTo("ABC");
    }


    @Test
    public void test_getSimulationDetails_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.SIMULATION_DETAILS_, getStub(com.gensym.classes.SimulationSubtable.class));

        assertThat(instance.getSimulationDetails()).isEqualTo(getStub(com.gensym.classes.SimulationSubtable.class));
    }


    @Test
    public void test_setDataServer_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setDataServer(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.DATA_SERVER_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getDataServer_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.DATA_SERVER_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getDataServer()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setDefaultUpdateInterval_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setDefaultUpdateInterval(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.DEFAULT_UPDATE_INTERVAL_)).isEqualTo(42);
    }
    @Test
    public void test_getDefaultUpdateInterval_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.DEFAULT_UPDATE_INTERVAL_, 42);

        assertThat(instance.getDefaultUpdateInterval()).isEqualTo(42);
    }


}