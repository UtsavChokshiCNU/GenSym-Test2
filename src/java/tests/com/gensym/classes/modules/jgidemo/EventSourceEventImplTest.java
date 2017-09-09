package com.gensym.classes.modules.jgidemo;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class EventSourceEventImplTest extends G2TestBase<EventSourceEventImpl> {

    @Override
    protected Class<EventSourceEventImpl> forClass() {
        return EventSourceEventImpl.class;
    }

    @Test
    public void test_setMessage_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setMessage("ABC");

        assertThat(attributes.getAttributeValue(Symbol.intern("MESSAGE"))).isEqualTo("ABC");
    }
    @Test
    public void test_getMessage_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(Symbol.intern("MESSAGE"), "ABC");

        assertThat(instance.getMessage()).isEqualTo("ABC");
    }


}