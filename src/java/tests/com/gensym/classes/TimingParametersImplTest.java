package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class TimingParametersImplTest extends G2TestBase<TimingParametersImpl> {

    @Override
    protected Class<TimingParametersImpl> forClass() {
        return TimingParametersImpl.class;
    }

    @Test
    public void test_setSchedulerMode_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSchedulerMode(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.SCHEDULER_MODE_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getSchedulerMode_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.SCHEDULER_MODE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getSchedulerMode()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setClockAdjustmentInMinutes_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setClockAdjustmentInMinutes(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.CLOCK_ADJUSTMENT_IN_MINUTES_)).isEqualTo(42);
    }
    @Test
    public void test_getClockAdjustmentInMinutes_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.CLOCK_ADJUSTMENT_IN_MINUTES_, 42);

        assertThat(instance.getClockAdjustmentInMinutes()).isEqualTo(42);
    }


    @Test
    public void test_setForeignFunctionTimeoutInterval_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setForeignFunctionTimeoutInterval("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.FOREIGN_FUNCTION_TIMEOUT_INTERVAL_)).isEqualTo("ABC");
    }
    @Test
    public void test_getForeignFunctionTimeoutInterval_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.FOREIGN_FUNCTION_TIMEOUT_INTERVAL_, "ABC");

        assertThat(instance.getForeignFunctionTimeoutInterval()).isEqualTo("ABC");
    }


    @Test
    public void test_setReconnectToForeignImageAfterTimeout_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setReconnectToForeignImageAfterTimeout(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.RECONNECT_TO_FOREIGN_IMAGE_AFTER_TIMEOUTQ_)).isEqualTo(false);
    }
    @Test
    public void test_getReconnectToForeignImageAfterTimeout_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.RECONNECT_TO_FOREIGN_IMAGE_AFTER_TIMEOUTQ_, false);

        assertThat(instance.getReconnectToForeignImageAfterTimeout()).isEqualTo(false);
    }


    @Test
    public void test_setAttributeDisplayUpdateInterval_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setAttributeDisplayUpdateInterval("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.ATTRIBUTE_DISPLAY_UPDATE_INTERVAL_)).isEqualTo("ABC");
    }
    @Test
    public void test_getAttributeDisplayUpdateInterval_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ATTRIBUTE_DISPLAY_UPDATE_INTERVAL_, "ABC");

        assertThat(instance.getAttributeDisplayUpdateInterval()).isEqualTo("ABC");
    }


}