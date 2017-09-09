package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class ObjectDefinitionImplTest extends G2TestBase<ObjectDefinitionImpl> {

    @Override
    protected Class<ObjectDefinitionImpl> forClass() {
        return ObjectDefinitionImpl.class;
    }

    @Test
    public void test_setAttributeDisplays_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setAttributeDisplays("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.ATTRIBUTE_DISPLAYS_)).isEqualTo("ABC");
    }
    @Test
    public void test_getAttributeDisplays_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ATTRIBUTE_DISPLAYS_, "ABC");

        assertThat(instance.getAttributeDisplays()).isEqualTo("ABC");
    }


    @Test
    public void test_setStubs_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setStubs("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.STUBS_)).isEqualTo("ABC");
    }
    @Test
    public void test_getStubs_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.STUBS_, "ABC");

        assertThat(instance.getStubs()).isEqualTo("ABC");
    }


}