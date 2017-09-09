package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class ScrapImplTest extends G2TestBase<ScrapImpl> {

    @Override
    protected Class<ScrapImpl> forClass() {
        return ScrapImpl.class;
    }

    @Test
    public void test_setMinimumSizeInWorkspace_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setMinimumSizeInWorkspace(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.MINIMUM_SIZE_IN_WORKSPACE_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getMinimumSizeInWorkspace_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.MINIMUM_SIZE_IN_WORKSPACE_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getMinimumSizeInWorkspace()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_setSizeInWorkspace_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSizeInWorkspace(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.SIZE_IN_WORKSPACE_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getSizeInWorkspace_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.SIZE_IN_WORKSPACE_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getSizeInWorkspace()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_setCurrentAttributeDisplays_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setCurrentAttributeDisplays(getStub(com.gensym.util.Sequence.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.CURRENT_ATTRIBUTE_DISPLAYS_)).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }
    @Test
    public void test_getCurrentAttributeDisplays_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.CURRENT_ATTRIBUTE_DISPLAYS_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getCurrentAttributeDisplays()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


}