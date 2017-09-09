package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class NewTableImplTest extends G2TestBase<NewTableImpl> {

    @Override
    protected Class<NewTableImpl> forClass() {
        return NewTableImpl.class;
    }

    @Test
    public void test_setDefaultCellFormat_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setDefaultCellFormat(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.DEFAULT_CELL_FORMAT_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getDefaultCellFormat_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.DEFAULT_CELL_FORMAT_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getDefaultCellFormat()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_setDefaultEvaluationSetting_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setDefaultEvaluationSetting(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.DEFAULT_EVALUATION_SETTING_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getDefaultEvaluationSetting_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.DEFAULT_EVALUATION_SETTING_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getDefaultEvaluationSetting()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


}