package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class HttpServerImplTest extends G2TestBase<HttpServerImpl> {

    @Override
    protected Class<HttpServerImpl> forClass() {
        return HttpServerImpl.class;
    }

    @Test
    public void test_getHttpServerPort_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.HTTP_SERVER_PORT_, 42);

        assertThat(instance.getHttpServerPort()).isEqualTo(42);
    }


    @Test
    public void test_setHttpServerDispatch_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setHttpServerDispatch(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.HTTP_SERVER_DISPATCH_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getHttpServerDispatch_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.HTTP_SERVER_DISPATCH_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getHttpServerDispatch()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


}