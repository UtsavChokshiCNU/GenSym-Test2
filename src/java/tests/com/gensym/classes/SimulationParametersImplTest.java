package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class SimulationParametersImplTest extends G2TestBase<SimulationParametersImpl> {

    @Override
    protected Class<SimulationParametersImpl> forClass() {
        return SimulationParametersImpl.class;
    }

    @Test
    public void test_setDefaultSimulationTimeIncrement_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setDefaultSimulationTimeIncrement(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.DEFAULT_SIMULATION_TIME_INCREMENT_)).isEqualTo(42);
    }
    @Test
    public void test_getDefaultSimulationTimeIncrement_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.DEFAULT_SIMULATION_TIME_INCREMENT_, 42);

        assertThat(instance.getDefaultSimulationTimeIncrement()).isEqualTo(42);
    }


    @Test
    public void test_setIntegrationAlgorithm_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setIntegrationAlgorithm(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.INTEGRATION_ALGORITHM_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getIntegrationAlgorithm_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.INTEGRATION_ALGORITHM_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getIntegrationAlgorithm()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setSimulatorOn_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSimulatorOn(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.SIMULATOR_ON_)).isEqualTo(false);
    }
    @Test
    public void test_getSimulatorOn_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.SIMULATOR_ON_, false);

        assertThat(instance.getSimulatorOn()).isEqualTo(false);
    }


    @Test
    public void test_setSimulationProcedure_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSimulationProcedure(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.SIMULATION_PROCEDURE_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getSimulationProcedure_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.SIMULATION_PROCEDURE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getSimulationProcedure()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setSendAllValuesAtBeginningOfCycle_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSendAllValuesAtBeginningOfCycle(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.SEND_ALL_VALUES_AT_BEGINNING_OF_CYCLEQ_)).isEqualTo(false);
    }
    @Test
    public void test_getSendAllValuesAtBeginningOfCycle_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.SEND_ALL_VALUES_AT_BEGINNING_OF_CYCLEQ_, false);

        assertThat(instance.getSendAllValuesAtBeginningOfCycle()).isEqualTo(false);
    }


}