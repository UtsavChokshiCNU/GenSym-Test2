package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class G2ToG2DataInterfaceImplTest extends G2TestBase<G2ToG2DataInterfaceImpl> {

    @Override
    protected Class<G2ToG2DataInterfaceImpl> forClass() {
        return G2ToG2DataInterfaceImpl.class;
    }

    @Test
    public void test_setIcpConnectionSpecification_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setIcpConnectionSpecification(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.ICP_CONNECTION_SPECIFICATION_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getIcpConnectionSpecification_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ICP_CONNECTION_SPECIFICATION_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getIcpConnectionSpecification()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_getInterfaceStatus_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.INTERFACE_STATUS_, "ABC");

        assertThat(instance.getInterfaceStatus()).isEqualTo("ABC");
    }


    @Test
    public void test_getInterfaceIsSecure_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.INTERFACE_IS_SECURE_, false);

        assertThat(instance.getInterfaceIsSecure()).isEqualTo(false);
    }


}