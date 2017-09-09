package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class RootImplTest extends G2TestBase<RootImpl> {

    @Override
    protected Class<RootImpl> forClass() {
        return RootImpl.class;
    }

    @Test
    public void test_getFoundationClass_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.FOUNDATION_CLASS_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getFoundationClass()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


}