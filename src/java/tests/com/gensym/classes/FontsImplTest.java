package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class FontsImplTest extends G2TestBase<FontsImpl> {

    @Override
    protected Class<FontsImpl> forClass() {
        return FontsImpl.class;
    }

    @Test
    public void test_setFontForAttributeTables_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setFontForAttributeTables(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.FONT_FOR_ATTRIBUTE_TABLES_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getFontForAttributeTables_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.FONT_FOR_ATTRIBUTE_TABLES_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getFontForAttributeTables()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setFontForAttributeDisplays_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setFontForAttributeDisplays(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.FONT_FOR_ATTRIBUTE_DISPLAYS_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getFontForAttributeDisplays_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.FONT_FOR_ATTRIBUTE_DISPLAYS_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getFontForAttributeDisplays()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setFontForStatements_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setFontForStatements(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.FONT_FOR_STATEMENTS_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getFontForStatements_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.FONT_FOR_STATEMENTS_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getFontForStatements()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setFontForFreeText_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setFontForFreeText(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.FONT_FOR_FREE_TEXT_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getFontForFreeText_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.FONT_FOR_FREE_TEXT_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getFontForFreeText()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setFontForEditing_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setFontForEditing(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.FONT_FOR_EDITING_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getFontForEditing_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.FONT_FOR_EDITING_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getFontForEditing()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setFontForDescriptions_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setFontForDescriptions(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.FONT_FOR_DESCRIPTIONS_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getFontForDescriptions_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.FONT_FOR_DESCRIPTIONS_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getFontForDescriptions()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


}