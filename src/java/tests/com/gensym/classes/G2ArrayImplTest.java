package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class G2ArrayImplTest extends G2TestBase<G2ArrayImpl> {

    @Override
    protected Class<G2ArrayImpl> forClass() {
        return G2ArrayImpl.class;
    }

    @Test
    public void test_getElementType_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ELEMENT_TYPE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getElementType()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setInitialValues_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setInitialValues("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.INITIAL_VALUES_)).isEqualTo("ABC");
    }
    @Test
    public void test_getInitialValues_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.INITIAL_VALUES_, "ABC");

        assertThat(instance.getInitialValues()).isEqualTo("ABC");
    }


    @Test
    public void test_setArrayIsPermanent_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setArrayIsPermanent(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.ARRAY_IS_PERMANENT_)).isEqualTo(false);
    }
    @Test
    public void test_getArrayIsPermanent_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ARRAY_IS_PERMANENT_, false);

        assertThat(instance.getArrayIsPermanent()).isEqualTo(false);
    }


    @Test
    public void test_setG2ArraySequence_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setG2ArraySequence(getStub(com.gensym.util.Sequence.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.G2_ARRAY_SEQUENCE_)).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }
    @Test
    public void test_getG2ArraySequence_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_ARRAY_SEQUENCE_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getG2ArraySequence()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


}