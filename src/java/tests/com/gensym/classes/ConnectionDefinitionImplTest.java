package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class ConnectionDefinitionImplTest extends G2TestBase<ConnectionDefinitionImpl> {

    @Override
    protected Class<ConnectionDefinitionImpl> forClass() {
        return ConnectionDefinitionImpl.class;
    }

    @Test
    public void test_setCrossSectionPattern_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setCrossSectionPattern(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.CROSS_SECTION_PATTERN_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getCrossSectionPattern_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.CROSS_SECTION_PATTERN_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getCrossSectionPattern()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_setStubLength_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setStubLength("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.STUB_LENGTH_)).isEqualTo("ABC");
    }
    @Test
    public void test_getStubLength_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.STUB_LENGTH_, "ABC");

        assertThat(instance.getStubLength()).isEqualTo("ABC");
    }


    @Test
    public void test_setJunctionBlock_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setJunctionBlock(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.JUNCTION_BLOCK_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getJunctionBlock_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.JUNCTION_BLOCK_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getJunctionBlock()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


}