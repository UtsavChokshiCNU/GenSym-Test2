package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class G2ForeignObjectImplTest extends G2TestBase<G2ForeignObjectImpl> {

    @Override
    protected Class<G2ForeignObjectImpl> forClass() {
        return G2ForeignObjectImpl.class;
    }

    @Test
    public void test_setActiveStubs_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setActiveStubs(getStub(com.gensym.util.Sequence.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.ACTIVE_STUBS_)).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }
    @Test
    public void test_getActiveStubs_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ACTIVE_STUBS_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getActiveStubs()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


}