package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class ItemReferenceParametersImplTest extends G2TestBase<ItemReferenceParametersImpl> {

    @Override
    protected Class<ItemReferenceParametersImpl> forClass() {
        return ItemReferenceParametersImpl.class;
    }

    @Test
    public void test_setShowUuidsInAttributeTables_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setShowUuidsInAttributeTables(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.SHOW_UUIDS_IN_ATTRIBUTE_TABLES_)).isEqualTo(false);
    }
    @Test
    public void test_getShowUuidsInAttributeTables_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.SHOW_UUIDS_IN_ATTRIBUTE_TABLES_, false);

        assertThat(instance.getShowUuidsInAttributeTables()).isEqualTo(false);
    }


}