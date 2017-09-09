package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class G2ListImplTest extends G2TestBase<G2ListImpl> {

    @Override
    protected Class<G2ListImpl> forClass() {
        return G2ListImpl.class;
    }

    @Test
    public void test_setG2ListSequence_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setG2ListSequence(getStub(com.gensym.util.Sequence.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.G2_LIST_SEQUENCE_)).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }
    @Test
    public void test_getG2ListSequence_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_LIST_SEQUENCE_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getG2ListSequence()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_getElementType_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ELEMENT_TYPE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getElementType()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setAllowDuplicateElements_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setAllowDuplicateElements(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.ALLOW_DUPLICATE_ELEMENTS_)).isEqualTo(false);
    }
    @Test
    public void test_getAllowDuplicateElements_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ALLOW_DUPLICATE_ELEMENTS_, false);

        assertThat(instance.getAllowDuplicateElements()).isEqualTo(false);
    }


    @Test
    public void test_setListIsPermanent_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setListIsPermanent(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.LIST_IS_PERMANENT_)).isEqualTo(false);
    }
    @Test
    public void test_getListIsPermanent_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.LIST_IS_PERMANENT_, false);

        assertThat(instance.getListIsPermanent()).isEqualTo(false);
    }


}