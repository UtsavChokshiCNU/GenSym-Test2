package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class GenericActionButtonImplTest extends G2TestBase<GenericActionButtonImpl> {

    @Override
    protected Class<GenericActionButtonImpl> forClass() {
        return GenericActionButtonImpl.class;
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
    public void test_setAction_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setAction("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.ACTION_)).isEqualTo("ABC");
    }
    @Test
    public void test_getAction_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ACTION_, "ABC");

        assertThat(instance.getAction()).isEqualTo("ABC");
    }


    @Test
    public void test_setActionPriority_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setActionPriority(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.ACTION_PRIORITY_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getActionPriority_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ACTION_PRIORITY_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getActionPriority()).isEqualTo(getStub(com.gensym.util.Symbol.class));
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