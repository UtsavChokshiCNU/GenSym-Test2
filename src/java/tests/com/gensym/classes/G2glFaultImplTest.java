package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class G2glFaultImplTest extends G2TestBase<G2glFaultImpl> {

    @Override
    protected Class<G2glFaultImpl> forClass() {
        return G2glFaultImpl.class;
    }

    @Test
    public void test_getFaultName_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.FAULT_NAME_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getFaultName()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_getFaultData_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.FAULT_DATA_, "ABC");

        assertThat(instance.getFaultData()).isEqualTo("ABC");
    }


}