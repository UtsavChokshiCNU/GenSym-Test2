package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class GsiInterfaceImplTest extends G2TestBase<GsiInterfaceImpl> {

    @Override
    protected Class<GsiInterfaceImpl> forClass() {
        return GsiInterfaceImpl.class;
    }

    @Test
    public void test_setGsiConnectionConfiguration_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setGsiConnectionConfiguration(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.GSI_CONNECTION_CONFIGURATION_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getGsiConnectionConfiguration_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.GSI_CONNECTION_CONFIGURATION_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getGsiConnectionConfiguration()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_setExternalSystemHasAScheduler_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setExternalSystemHasAScheduler(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.EXTERNAL_SYSTEM_HAS_A_SCHEDULER_)).isEqualTo(false);
    }
    @Test
    public void test_getExternalSystemHasAScheduler_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.EXTERNAL_SYSTEM_HAS_A_SCHEDULER_, false);

        assertThat(instance.getExternalSystemHasAScheduler()).isEqualTo(false);
    }


    @Test
    public void test_setPollExternalSystemForData_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setPollExternalSystemForData(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.POLL_EXTERNAL_SYSTEM_FOR_DATA_)).isEqualTo(false);
    }
    @Test
    public void test_getPollExternalSystemForData_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.POLL_EXTERNAL_SYSTEM_FOR_DATA_, false);

        assertThat(instance.getPollExternalSystemForData()).isEqualTo(false);
    }


    @Test
    public void test_setGroupingSpecification_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setGroupingSpecification(getStub(com.gensym.util.Sequence.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.GROUPING_SPECIFICATION_)).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }
    @Test
    public void test_getGroupingSpecification_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.GROUPING_SPECIFICATION_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getGroupingSpecification()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_setRemoteProcessInitializationString_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setRemoteProcessInitializationString("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.REMOTE_PROCESS_INITIALIZATION_STRING_)).isEqualTo("ABC");
    }
    @Test
    public void test_getRemoteProcessInitializationString_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.REMOTE_PROCESS_INITIALIZATION_STRING_, "ABC");

        assertThat(instance.getRemoteProcessInitializationString()).isEqualTo("ABC");
    }


    @Test
    public void test_setGsiApplicationName_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setGsiApplicationName(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.GSI_APPLICATION_NAME_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getGsiApplicationName_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.GSI_APPLICATION_NAME_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getGsiApplicationName()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_getGsiInterfaceStatus_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.GSI_INTERFACE_STATUS_, 42);

        assertThat(instance.getGsiInterfaceStatus()).isEqualTo(42);
    }


    @Test
    public void test_getGsiInterfaceIsSecure_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.GSI_INTERFACE_IS_SECURE_, false);

        assertThat(instance.getGsiInterfaceIsSecure()).isEqualTo(false);
    }


    @Test
    public void test_setIntervalToPollExternalSystem_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setIntervalToPollExternalSystem("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.INTERVAL_TO_POLL_EXTERNAL_SYSTEM_)).isEqualTo("ABC");
    }
    @Test
    public void test_getIntervalToPollExternalSystem_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.INTERVAL_TO_POLL_EXTERNAL_SYSTEM_, "ABC");

        assertThat(instance.getIntervalToPollExternalSystem()).isEqualTo("ABC");
    }


}