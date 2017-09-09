package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class DataServerParametersImplTest extends G2TestBase<DataServerParametersImpl> {

    @Override
    protected Class<DataServerParametersImpl> forClass() {
        return DataServerParametersImpl.class;
    }

    @Test
    public void test_setPriorityOfDataService_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setPriorityOfDataService(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.PRIORITY_OF_DATA_SERVICE_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getPriorityOfDataService_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.PRIORITY_OF_DATA_SERVICE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getPriorityOfDataService()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setG2MeterDataServiceOn_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setG2MeterDataServiceOn(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.G2_METER_DATA_SERVICE_ON_)).isEqualTo(false);
    }
    @Test
    public void test_getG2MeterDataServiceOn_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_METER_DATA_SERVICE_ON_, false);

        assertThat(instance.getG2MeterDataServiceOn()).isEqualTo(false);
    }


}