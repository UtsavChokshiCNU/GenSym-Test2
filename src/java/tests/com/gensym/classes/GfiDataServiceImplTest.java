package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class GfiDataServiceImplTest extends G2TestBase<GfiDataServiceImpl> {

    @Override
    protected Class<GfiDataServiceImpl> forClass() {
        return GfiDataServiceImpl.class;
    }

    @Test
    public void test_setGfiInputInterfaceObject_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setGfiInputInterfaceObject("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.GFI_INPUT_INTERFACE_OBJECT_)).isEqualTo("ABC");
    }
    @Test
    public void test_getGfiInputInterfaceObject_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.GFI_INPUT_INTERFACE_OBJECT_, "ABC");

        assertThat(instance.getGfiInputInterfaceObject()).isEqualTo("ABC");
    }


}