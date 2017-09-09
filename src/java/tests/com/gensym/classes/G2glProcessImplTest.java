package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class G2glProcessImplTest extends G2TestBase<G2glProcessImpl> {

    @Override
    protected Class<G2glProcessImpl> forClass() {
        return G2glProcessImpl.class;
    }

    @Test
    public void test_setCallableAsAProcedure_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setCallableAsAProcedure(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.CALLABLE_AS_A_PROCEDURE_)).isEqualTo(false);
    }
    @Test
    public void test_getCallableAsAProcedure_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.CALLABLE_AS_A_PROCEDURE_, false);

        assertThat(instance.getCallableAsAProcedure()).isEqualTo(false);
    }


    @Test
    public void test_setEnableInstanceCompensation_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setEnableInstanceCompensation(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.ENABLE_INSTANCE_COMPENSATION_)).isEqualTo(false);
    }
    @Test
    public void test_getEnableInstanceCompensation_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ENABLE_INSTANCE_COMPENSATION_, false);

        assertThat(instance.getEnableInstanceCompensation()).isEqualTo(false);
    }


    @Test
    public void test_setThisIsAnAbstractProcess_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setThisIsAnAbstractProcess(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.THIS_IS_AN_ABSTRACT_PROCESS_)).isEqualTo(false);
    }
    @Test
    public void test_getThisIsAnAbstractProcess_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.THIS_IS_AN_ABSTRACT_PROCESS_, false);

        assertThat(instance.getThisIsAnAbstractProcess()).isEqualTo(false);
    }


    @Test
    public void test_setBreakOnExecutionFault_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setBreakOnExecutionFault(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.BREAK_ON_EXECUTION_FAULT_)).isEqualTo(false);
    }
    @Test
    public void test_getBreakOnExecutionFault_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.BREAK_ON_EXECUTION_FAULT_, false);

        assertThat(instance.getBreakOnExecutionFault()).isEqualTo(false);
    }


    @Test
    public void test_setThreadTokenClass_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setThreadTokenClass(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.THREAD_TOKEN_CLASS_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getThreadTokenClass_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.THREAD_TOKEN_CLASS_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getThreadTokenClass()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_getLatestAttemptedCompilationVersionNumber_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.LATEST_ATTEMPTED_COMPILATION_VERSION_NUMBER_, 42);

        assertThat(instance.getLatestAttemptedCompilationVersionNumber()).isEqualTo(42);
    }


    @Test
    public void test_getNumberOfErrorsInLatestAttemptedCompilation_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.NUMBER_OF_ERRORS_IN_LATEST_ATTEMPTED_COMPILATION_, 42);

        assertThat(instance.getNumberOfErrorsInLatestAttemptedCompilation()).isEqualTo(42);
    }


    @Test
    public void test_getNumberOfWarningsInLatestAttemptedCompilation_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.NUMBER_OF_WARNINGS_IN_LATEST_ATTEMPTED_COMPILATION_, 42);

        assertThat(instance.getNumberOfWarningsInLatestAttemptedCompilation()).isEqualTo(42);
    }


    @Test
    public void test_getG2glProcessCompilationVersionNumber_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2GL_PROCESS_COMPILATION_VERSION_NUMBER_, 42);

        assertThat(instance.getG2glProcessCompilationVersionNumber()).isEqualTo(42);
    }


    @Test
    public void test_getG2glProcessProcedureSignature_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2GL_PROCESS_PROCEDURE_SIGNATURE_, "ABC");

        assertThat(instance.getG2glProcessProcedureSignature()).isEqualTo("ABC");
    }


}