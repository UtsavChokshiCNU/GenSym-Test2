package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class HashTableImplTest extends G2TestBase<HashTableImpl> {

    @Override
    protected Class<HashTableImpl> forClass() {
        return HashTableImpl.class;
    }

    @Test
    public void test_getG2HashTableSequence_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_HASH_TABLE_SEQUENCE_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getG2HashTableSequence()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_getG2HashTableNumberOfEntries_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.G2_HASH_TABLE_NUMBER_OF_ENTRIES_, 42);

        assertThat(instance.getG2HashTableNumberOfEntries()).isEqualTo(42);
    }


}