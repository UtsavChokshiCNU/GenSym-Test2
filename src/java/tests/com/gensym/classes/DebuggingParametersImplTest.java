package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class DebuggingParametersImplTest extends G2TestBase<DebuggingParametersImpl> {

    @Override
    protected Class<DebuggingParametersImpl> forClass() {
        return DebuggingParametersImpl.class;
    }

    @Test
    public void test_setWarningMessageLevel_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setWarningMessageLevel(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.WARNING_MESSAGE_LEVEL_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getWarningMessageLevel_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.WARNING_MESSAGE_LEVEL_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getWarningMessageLevel()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setTracingMessageLevel_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setTracingMessageLevel(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.TRACING_MESSAGE_LEVEL_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getTracingMessageLevel_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.TRACING_MESSAGE_LEVEL_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getTracingMessageLevel()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setBreakpointLevel_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setBreakpointLevel(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.BREAKPOINT_LEVEL_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getBreakpointLevel_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.BREAKPOINT_LEVEL_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getBreakpointLevel()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setSourceSteppingLevel_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSourceSteppingLevel(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.SOURCE_STEPPING_LEVEL_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getSourceSteppingLevel_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.SOURCE_STEPPING_LEVEL_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getSourceSteppingLevel()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setTracingAndBreakpointsEnabled_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setTracingAndBreakpointsEnabled(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.TRACING_AND_BREAKPOINTS_ENABLEDQ_)).isEqualTo(false);
    }
    @Test
    public void test_getTracingAndBreakpointsEnabled_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.TRACING_AND_BREAKPOINTS_ENABLEDQ_, false);

        assertThat(instance.getTracingAndBreakpointsEnabled()).isEqualTo(false);
    }


    @Test
    public void test_setShowProcedureInvocationHierarchyAtPauseFromBreakpoint_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setShowProcedureInvocationHierarchyAtPauseFromBreakpoint(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.SHOW_PROCEDURE_INVOCATION_HIERARCHY_AT_PAUSE_FROM_BREAKPOINT_)).isEqualTo(false);
    }
    @Test
    public void test_getShowProcedureInvocationHierarchyAtPauseFromBreakpoint_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.SHOW_PROCEDURE_INVOCATION_HIERARCHY_AT_PAUSE_FROM_BREAKPOINT_, false);

        assertThat(instance.getShowProcedureInvocationHierarchyAtPauseFromBreakpoint()).isEqualTo(false);
    }


    @Test
    public void test_setDisassemblerEnabled_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setDisassemblerEnabled(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.DISASSEMBLER_ENABLEDQ_)).isEqualTo(false);
    }
    @Test
    public void test_getDisassemblerEnabled_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.DISASSEMBLER_ENABLEDQ_, false);

        assertThat(instance.getDisassemblerEnabled()).isEqualTo(false);
    }


    @Test
    public void test_setGenerateSourceAnnotationInfo_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setGenerateSourceAnnotationInfo(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.GENERATE_SOURCE_ANNOTATION_INFO_)).isEqualTo(false);
    }
    @Test
    public void test_getGenerateSourceAnnotationInfo_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.GENERATE_SOURCE_ANNOTATION_INFO_, false);

        assertThat(instance.getGenerateSourceAnnotationInfo()).isEqualTo(false);
    }


    @Test
    public void test_setTracingFile_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setTracingFile("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.TRACING_FILE_)).isEqualTo("ABC");
    }
    @Test
    public void test_getTracingFile_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.TRACING_FILE_, "ABC");

        assertThat(instance.getTracingFile()).isEqualTo("ABC");
    }


    @Test
    public void test_setDynamicDisplayDelayInMilliseconds_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setDynamicDisplayDelayInMilliseconds(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.DYNAMIC_DISPLAY_DELAY_IN_MILLISECONDS_)).isEqualTo(42);
    }
    @Test
    public void test_getDynamicDisplayDelayInMilliseconds_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.DYNAMIC_DISPLAY_DELAY_IN_MILLISECONDS_, 42);

        assertThat(instance.getDynamicDisplayDelayInMilliseconds()).isEqualTo(42);
    }


}