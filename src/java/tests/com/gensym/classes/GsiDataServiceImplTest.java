package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class GsiDataServiceImplTest extends G2TestBase<GsiDataServiceImpl> {

    @Override
    protected Class<GsiDataServiceImpl> forClass() {
        return GsiDataServiceImpl.class;
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
    public void test_getGsiVariableStatus_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.GSI_VARIABLE_STATUS_, 42);

        assertThat(instance.getGsiVariableStatus()).isEqualTo(42);
    }


}