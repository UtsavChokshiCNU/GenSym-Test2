package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class SystemItemImplTest extends G2TestBase<SystemItemImpl> {

    @Override
    protected Class<SystemItemImpl> forClass() {
        return SystemItemImpl.class;
    }

    @Test
    public void test_setUuid_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setUuid("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.UUID_)).isEqualTo("ABC");
    }
    @Test
    public void test_getUuid_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.UUID_, "ABC");

        assertThat(instance.getUuid()).isEqualTo("ABC");
    }


}