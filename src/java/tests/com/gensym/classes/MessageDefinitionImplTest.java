package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class MessageDefinitionImplTest extends G2TestBase<MessageDefinitionImpl> {

    @Override
    protected Class<MessageDefinitionImpl> forClass() {
        return MessageDefinitionImpl.class;
    }

    @Test
    public void test_setDefaultMessageProperties_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setDefaultMessageProperties(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.DEFAULT_MESSAGE_PROPERTIES_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getDefaultMessageProperties_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.DEFAULT_MESSAGE_PROPERTIES_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getDefaultMessageProperties()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


}