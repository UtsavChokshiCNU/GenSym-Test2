package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class G2glFlowGateImplTest extends G2TestBase<G2glFlowGateImpl> {

    @Override
    protected Class<G2glFlowGateImpl> forClass() {
        return G2glFlowGateImpl.class;
    }

    @Test
    public void test_setSuppressJoinFailure_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSuppressJoinFailure(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.SUPPRESS_JOIN_FAILURE_)).isEqualTo(false);
    }
    @Test
    public void test_getSuppressJoinFailure_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.SUPPRESS_JOIN_FAILURE_, false);

        assertThat(instance.getSuppressJoinFailure()).isEqualTo(false);
    }


}