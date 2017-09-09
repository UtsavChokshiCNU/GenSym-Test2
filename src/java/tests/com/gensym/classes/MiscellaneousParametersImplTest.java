package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class MiscellaneousParametersImplTest extends G2TestBase<MiscellaneousParametersImpl> {

    @Override
    protected Class<MiscellaneousParametersImpl> forClass() {
        return MiscellaneousParametersImpl.class;
    }

    @Test
    public void test_setRepeatRandomFunctionOnReset_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setRepeatRandomFunctionOnReset(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.REPEAT_RANDOM_FUNCTION_ON_RESETQ_)).isEqualTo(false);
    }
    @Test
    public void test_getRepeatRandomFunctionOnReset_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.REPEAT_RANDOM_FUNCTION_ON_RESETQ_, false);

        assertThat(instance.getRepeatRandomFunctionOnReset()).isEqualTo(false);
    }


    @Test
    public void test_setInitialMarginForWorkspaces_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setInitialMarginForWorkspaces(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.INITIAL_MARGIN_FOR_WORKSPACES_)).isEqualTo(42);
    }
    @Test
    public void test_getInitialMarginForWorkspaces_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.INITIAL_MARGIN_FOR_WORKSPACES_, 42);

        assertThat(instance.getInitialMarginForWorkspaces()).isEqualTo(42);
    }


    @Test
    public void test_setStartKbAfterLoad_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setStartKbAfterLoad(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.START_KB_AFTER_LOADQ_)).isEqualTo(false);
    }
    @Test
    public void test_getStartKbAfterLoad_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.START_KB_AFTER_LOADQ_, false);

        assertThat(instance.getStartKbAfterLoad()).isEqualTo(false);
    }


    @Test
    public void test_getG2RunState_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_RUN_STATE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getG2RunState()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setConfirmRunStateChanges_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setConfirmRunStateChanges(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.CONFIRM_RUN_STATE_CHANGES_)).isEqualTo(false);
    }
    @Test
    public void test_getConfirmRunStateChanges_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.CONFIRM_RUN_STATE_CHANGES_, false);

        assertThat(instance.getConfirmRunStateChanges()).isEqualTo(false);
    }


    @Test
    public void test_setBackwardCompatibilityFeatures_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setBackwardCompatibilityFeatures(getStub(com.gensym.util.Sequence.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.BACKWARD_COMPATIBILITY_FEATURES_)).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }
    @Test
    public void test_getBackwardCompatibilityFeatures_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.BACKWARD_COMPATIBILITY_FEATURES_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getBackwardCompatibilityFeatures()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_setShowUuidsInAttributeTables_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setShowUuidsInAttributeTables(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.SHOW_UUIDS_IN_ATTRIBUTE_TABLES_)).isEqualTo(false);
    }
    @Test
    public void test_getShowUuidsInAttributeTables_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.SHOW_UUIDS_IN_ATTRIBUTE_TABLES_, false);

        assertThat(instance.getShowUuidsInAttributeTables()).isEqualTo(false);
    }


    @Test
    public void test_setEnableExplanationControls_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setEnableExplanationControls(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.ENABLE_EXPLANATION_CONTROLS_)).isEqualTo(false);
    }
    @Test
    public void test_getEnableExplanationControls_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ENABLE_EXPLANATION_CONTROLS_, false);

        assertThat(instance.getEnableExplanationControls()).isEqualTo(false);
    }


    @Test
    public void test_setConnectionCachingEnabled_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setConnectionCachingEnabled(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.CONNECTION_CACHING_ENABLEDQ_)).isEqualTo(false);
    }
    @Test
    public void test_getConnectionCachingEnabled_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.CONNECTION_CACHING_ENABLEDQ_, false);

        assertThat(instance.getConnectionCachingEnabled()).isEqualTo(false);
    }


    @Test
    public void test_setPreferNativeLoginDialog_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setPreferNativeLoginDialog(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.PREFER_NATIVE_LOGIN_DIALOG_)).isEqualTo(false);
    }
    @Test
    public void test_getPreferNativeLoginDialog_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.PREFER_NATIVE_LOGIN_DIALOG_, false);

        assertThat(instance.getPreferNativeLoginDialog()).isEqualTo(false);
    }


    @Test
    public void test_setAutomaticDeadlockDetectionFrequency_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setAutomaticDeadlockDetectionFrequency("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.AUTOMATIC_DEADLOCK_DETECTION_FREQUENCY_)).isEqualTo("ABC");
    }
    @Test
    public void test_getAutomaticDeadlockDetectionFrequency_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.AUTOMATIC_DEADLOCK_DETECTION_FREQUENCY_, "ABC");

        assertThat(instance.getAutomaticDeadlockDetectionFrequency()).isEqualTo("ABC");
    }


}