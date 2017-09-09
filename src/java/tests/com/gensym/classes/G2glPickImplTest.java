package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class G2glPickImplTest extends G2TestBase<G2glPickImpl> {

    @Override
    protected Class<G2glPickImpl> forClass() {
        return G2glPickImpl.class;
    }

    @Test
    public void test_setThisIsAnInstantiationTrigger_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setThisIsAnInstantiationTrigger(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.THIS_IS_AN_INSTANTIATION_TRIGGER_)).isEqualTo(false);
    }
    @Test
    public void test_getThisIsAnInstantiationTrigger_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.THIS_IS_AN_INSTANTIATION_TRIGGER_, false);

        assertThat(instance.getThisIsAnInstantiationTrigger()).isEqualTo(false);
    }


}