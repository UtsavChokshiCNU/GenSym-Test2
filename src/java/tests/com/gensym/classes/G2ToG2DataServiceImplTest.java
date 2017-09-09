package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class G2ToG2DataServiceImplTest extends G2TestBase<G2ToG2DataServiceImpl> {

    @Override
    protected Class<G2ToG2DataServiceImpl> forClass() {
        return G2ToG2DataServiceImpl.class;
    }

    @Test
    public void test_setG2ToG2InterfaceName_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setG2ToG2InterfaceName(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.G2_TO_G2_INTERFACE_NAME_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getG2ToG2InterfaceName_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_TO_G2_INTERFACE_NAME_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getG2ToG2InterfaceName()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setRemoteG2Expression_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setRemoteG2Expression("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.REMOTE_G2_EXPRESSION_)).isEqualTo("ABC");
    }
    @Test
    public void test_getRemoteG2Expression_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.REMOTE_G2_EXPRESSION_, "ABC");

        assertThat(instance.getRemoteG2Expression()).isEqualTo("ABC");
    }


}