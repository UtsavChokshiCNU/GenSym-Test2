package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class GsiMessageServiceImplTest extends G2TestBase<GsiMessageServiceImpl> {

    @Override
    protected Class<GsiMessageServiceImpl> forClass() {
        return GsiMessageServiceImpl.class;
    }

    @Test
    public void test_setGsiInterfaceName_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setGsiInterfaceName(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.GSI_INTERFACE_NAME_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getGsiInterfaceName_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.GSI_INTERFACE_NAME_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getGsiInterfaceName()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setDataServerForMessages_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setDataServerForMessages(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.DATA_SERVER_FOR_MESSAGES_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getDataServerForMessages_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.DATA_SERVER_FOR_MESSAGES_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getDataServerForMessages()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


}