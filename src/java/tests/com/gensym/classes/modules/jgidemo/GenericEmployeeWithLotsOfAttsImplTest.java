package com.gensym.classes.modules.jgidemo;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class GenericEmployeeWithLotsOfAttsImplTest extends G2TestBase<GenericEmployeeWithLotsOfAttsImpl> {

    @Override
    protected Class<GenericEmployeeWithLotsOfAttsImpl> forClass() {
        return GenericEmployeeWithLotsOfAttsImpl.class;
    }

    @Test
    public void test_setLotsOfAtts_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setLotsOfAtts("ABC");

        assertThat(attributes.getAttributeValue(Symbol.intern("LOTS-OF-ATTS"))).isEqualTo("ABC");
    }
    @Test
    public void test_getLotsOfAtts_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("LOTS-OF-ATTS"), "ABC");

        assertThat(instance.getLotsOfAtts()).isEqualTo("ABC");
    }


}