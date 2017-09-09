package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class RuleImplTest extends G2TestBase<RuleImpl> {

    @Override
    protected Class<RuleImpl> forClass() {
        return RuleImpl.class;
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
    public void test_setAuthors_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setAuthors(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.AUTHORS_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getAuthors_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.AUTHORS_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getAuthors()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_getChangeLog_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.CHANGE_LOG_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getChangeLog()).isEqualTo(getStub(com.gensym.util.Sequence.class));
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
    public void test_setScanInterval_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setScanInterval(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.SCAN_INTERVAL_)).isEqualTo(42);
    }
    @Test
    public void test_getScanInterval_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.SCAN_INTERVAL_, 42);

        assertThat(instance.getScanInterval()).isEqualTo(42);
    }


    @Test
    public void test_setFocalClasses_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setFocalClasses(getStub(com.gensym.util.Sequence.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.FOCAL_CLASSES_)).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }
    @Test
    public void test_getFocalClasses_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.FOCAL_CLASSES_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getFocalClasses()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_setFocalObjects_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setFocalObjects(getStub(com.gensym.util.Sequence.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.FOCAL_OBJECTS_)).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }
    @Test
    public void test_getFocalObjects_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.FOCAL_OBJECTS_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getFocalObjects()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_setCategories_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setCategories(getStub(com.gensym.util.Sequence.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.CATEGORIES_)).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }
    @Test
    public void test_getCategories_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.CATEGORIES_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getCategories()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_setRulePriority_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setRulePriority(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.RULE_PRIORITY_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getRulePriority_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.RULE_PRIORITY_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getRulePriority()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setDepthFirstBackwardChainingPrecedence_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setDepthFirstBackwardChainingPrecedence(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.DEPTH_FIRST_BACKWARD_CHAINING_PRECEDENCE_)).isEqualTo(42);
    }
    @Test
    public void test_getDepthFirstBackwardChainingPrecedence_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.DEPTH_FIRST_BACKWARD_CHAINING_PRECEDENCE_, 42);

        assertThat(instance.getDepthFirstBackwardChainingPrecedence()).isEqualTo(42);
    }


    @Test
    public void test_setTimeoutForRuleCompletion_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setTimeoutForRuleCompletion("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.TIMEOUT_FOR_RULE_COMPLETION_)).isEqualTo("ABC");
    }
    @Test
    public void test_getTimeoutForRuleCompletion_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.TIMEOUT_FOR_RULE_COMPLETION_, "ABC");

        assertThat(instance.getTimeoutForRuleCompletion()).isEqualTo("ABC");
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