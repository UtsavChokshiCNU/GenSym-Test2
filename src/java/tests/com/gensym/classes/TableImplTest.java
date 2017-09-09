package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class TableImplTest extends G2TestBase<TableImpl> {

    @Override
    protected Class<TableImpl> forClass() {
        return TableImpl.class;
    }

    @Test
    public void test_getTableRows_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.TABLE_ROWS_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getTableRows()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_getFormatType_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.FORMAT_TYPE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getFormatType()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


}