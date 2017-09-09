package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class ServerParametersImplTest extends G2TestBase<ServerParametersImpl> {

    @Override
    protected Class<ServerParametersImpl> forClass() {
        return ServerParametersImpl.class;
    }

    @Test
    public void test_getG2IsSecure_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_IS_SECURE_, false);

        assertThat(instance.getG2IsSecure()).isEqualTo(false);
    }


}