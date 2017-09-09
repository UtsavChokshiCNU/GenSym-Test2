package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class ButtonImplTest extends G2TestBase<ButtonImpl> {

    @Override
    protected Class<ButtonImpl> forClass() {
        return ButtonImpl.class;
    }

    @Test
    public void test_setLabel_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setLabel("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.LABEL_)).isEqualTo("ABC");
    }
    @Test
    public void test_getLabel_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.LABEL_, "ABC");

        assertThat(instance.getLabel()).isEqualTo("ABC");
    }


}