package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class G2ExtensionImplTest extends G2TestBase<G2ExtensionImpl> {

    @Override
    protected Class<G2ExtensionImpl> forClass() {
        return G2ExtensionImpl.class;
    }

    @Test
    public void test_getG2UserName_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_USER_NAME_, "ABC");

        assertThat(instance.getG2UserName()).isEqualTo("ABC");
    }


    @Test
    public void test_getG2ConnectionStatus_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_CONNECTION_STATUS_, "ABC");

        assertThat(instance.getG2ConnectionStatus()).isEqualTo("ABC");
    }


    @Test
    public void test_getG2RoutingInformation_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_ROUTING_INFORMATION_, "ABC");

        assertThat(instance.getG2RoutingInformation()).isEqualTo("ABC");
    }


}