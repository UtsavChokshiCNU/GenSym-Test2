package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class G2MeterDataServiceImplTest extends G2TestBase<G2MeterDataServiceImpl> {

    @Override
    protected Class<G2MeterDataServiceImpl> forClass() {
        return G2MeterDataServiceImpl.class;
    }

    @Test
    public void test_setG2MeterName_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setG2MeterName(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.G2_METER_NAME_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getG2MeterName_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_METER_NAME_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getG2MeterName()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


}