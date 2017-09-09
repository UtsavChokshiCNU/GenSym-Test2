package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class G2glProcessInstanceImplTest extends G2TestBase<G2glProcessInstanceImpl> {

    @Override
    protected Class<G2glProcessInstanceImpl> forClass() {
        return G2glProcessInstanceImpl.class;
    }

    @Test
    public void test_setG2glProcessInstanceIsPaused_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setG2glProcessInstanceIsPaused(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.G2GL_PROCESS_INSTANCE_IS_PAUSED_)).isEqualTo(false);
    }
    @Test
    public void test_getG2glProcessInstanceIsPaused_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2GL_PROCESS_INSTANCE_IS_PAUSED_, false);

        assertThat(instance.getG2glProcessInstanceIsPaused()).isEqualTo(false);
    }


}