package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class NetworkInterfaceImplTest extends G2TestBase<NetworkInterfaceImpl> {

    @Override
    protected Class<NetworkInterfaceImpl> forClass() {
        return NetworkInterfaceImpl.class;
    }

    @Test
    public void test_setIdentifyingAttributes_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setIdentifyingAttributes(getStub(com.gensym.util.Sequence.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.IDENTIFYING_ATTRIBUTES_)).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }
    @Test
    public void test_getIdentifyingAttributes_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.IDENTIFYING_ATTRIBUTES_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getIdentifyingAttributes()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_setInterfaceWarningMessageLevel_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setInterfaceWarningMessageLevel(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.INTERFACE_WARNING_MESSAGE_LEVEL_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getInterfaceWarningMessageLevel_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.INTERFACE_WARNING_MESSAGE_LEVEL_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getInterfaceWarningMessageLevel()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setDisableInterleavingOfLargeMessages_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setDisableInterleavingOfLargeMessages(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.DISABLE_INTERLEAVING_OF_LARGE_MESSAGES_)).isEqualTo(false);
    }
    @Test
    public void test_getDisableInterleavingOfLargeMessages_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.DISABLE_INTERLEAVING_OF_LARGE_MESSAGES_, false);

        assertThat(instance.getDisableInterleavingOfLargeMessages()).isEqualTo(false);
    }


    @Test
    public void test_setInterfaceTimeoutPeriod_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setInterfaceTimeoutPeriod("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.INTERFACE_TIMEOUT_PERIOD_)).isEqualTo("ABC");
    }
    @Test
    public void test_getInterfaceTimeoutPeriod_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.INTERFACE_TIMEOUT_PERIOD_, "ABC");

        assertThat(instance.getInterfaceTimeoutPeriod()).isEqualTo("ABC");
    }


    @Test
    public void test_setInterfaceInitializationTimeoutPeriod_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setInterfaceInitializationTimeoutPeriod("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.INTERFACE_INITIALIZATION_TIMEOUT_PERIOD_)).isEqualTo("ABC");
    }
    @Test
    public void test_getInterfaceInitializationTimeoutPeriod_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.INTERFACE_INITIALIZATION_TIMEOUT_PERIOD_, "ABC");

        assertThat(instance.getInterfaceInitializationTimeoutPeriod()).isEqualTo("ABC");
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