package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class VariableOrParameterImplTest extends G2TestBase<VariableOrParameterImpl> {

    @Override
    protected Class<VariableOrParameterImpl> forClass() {
        return VariableOrParameterImpl.class;
    }

    @Test
    public void test_setTracingAndBreakpoints_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setTracingAndBreakpoints("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.TRACING_AND_BREAKPOINTS_)).isEqualTo("ABC");
    }
    @Test
    public void test_getTracingAndBreakpoints_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.TRACING_AND_BREAKPOINTS_, "ABC");

        assertThat(instance.getTracingAndBreakpoints()).isEqualTo("ABC");
    }


    @Test
    public void test_setDataType_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setDataType(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.DATA_TYPE_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getDataType_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.DATA_TYPE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getDataType()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setHistoryKeepingSpec_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setHistoryKeepingSpec(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.HISTORY_KEEPING_SPEC_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getHistoryKeepingSpec_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.HISTORY_KEEPING_SPEC_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getHistoryKeepingSpec()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_getLastRecordedValueText_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.LAST_RECORDED_VALUE_TEXT_, "ABC");

        assertThat(instance.getLastRecordedValueText()).isEqualTo("ABC");
    }


    @Test
    public void test_setValueStructureUsingUnixTime_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setValueStructureUsingUnixTime(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.VALUE_STRUCTURE_USING_UNIX_TIME_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getValueStructureUsingUnixTime_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.VALUE_STRUCTURE_USING_UNIX_TIME_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getValueStructureUsingUnixTime()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_setValueStructure_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setValueStructure(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.VALUE_STRUCTURE_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getValueStructure_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.VALUE_STRUCTURE_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getValueStructure()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_setHistoryUsingUnixTime_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setHistoryUsingUnixTime(getStub(com.gensym.util.Sequence.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.HISTORY_USING_UNIX_TIME_)).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }
    @Test
    public void test_getHistoryUsingUnixTime_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.HISTORY_USING_UNIX_TIME_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getHistoryUsingUnixTime()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_setHistory_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setHistory(getStub(com.gensym.util.Sequence.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.HISTORY_)).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }
    @Test
    public void test_getHistory_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.HISTORY_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getHistory()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_getEffectiveDataType_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.EFFECTIVE_DATA_TYPE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getEffectiveDataType()).isEqualTo(getStub(com.gensym.util.Symbol.class));
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