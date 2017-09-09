package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class ConnectionPostImplTest extends G2TestBase<ConnectionPostImpl> {

    @Override
    protected Class<ConnectionPostImpl> forClass() {
        return ConnectionPostImpl.class;
    }

    @Test
    public void test_setSuperiorConnection_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSuperiorConnection("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.SUPERIOR_CONNECTION_)).isEqualTo("ABC");
    }
    @Test
    public void test_getSuperiorConnection_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.SUPERIOR_CONNECTION_, "ABC");

        assertThat(instance.getSuperiorConnection()).isEqualTo("ABC");
    }


}