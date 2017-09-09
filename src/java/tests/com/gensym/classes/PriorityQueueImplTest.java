package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class PriorityQueueImplTest extends G2TestBase<PriorityQueueImpl> {

    @Override
    protected Class<PriorityQueueImpl> forClass() {
        return PriorityQueueImpl.class;
    }

    @Test
    public void test_getG2PriorityQueueSequence_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_PRIORITY_QUEUE_SEQUENCE_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getG2PriorityQueueSequence()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_getG2PriorityQueueNumberOfEntries_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_PRIORITY_QUEUE_NUMBER_OF_ENTRIES_, 42);

        assertThat(instance.getG2PriorityQueueNumberOfEntries()).isEqualTo(42);
    }


}