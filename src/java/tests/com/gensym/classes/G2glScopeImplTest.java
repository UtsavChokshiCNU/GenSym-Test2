package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class G2glScopeImplTest extends G2TestBase<G2glScopeImpl> {

    @Override
    protected Class<G2glScopeImpl> forClass() {
        return G2glScopeImpl.class;
    }

    @Test
    public void test_setVariableAccessSerializable_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setVariableAccessSerializable(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.VARIABLE_ACCESS_SERIALIZABLE_)).isEqualTo(false);
    }
    @Test
    public void test_getVariableAccessSerializable_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.VARIABLE_ACCESS_SERIALIZABLE_, false);

        assertThat(instance.getVariableAccessSerializable()).isEqualTo(false);
    }


}