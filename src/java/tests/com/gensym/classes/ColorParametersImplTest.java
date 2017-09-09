package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class ColorParametersImplTest extends G2TestBase<ColorParametersImpl> {

    @Override
    protected Class<ColorParametersImpl> forClass() {
        return ColorParametersImpl.class;
    }

    @Test
    public void test_setColorMenuOrdering_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setColorMenuOrdering(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.COLOR_MENU_ORDERING_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getColorMenuOrdering_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.COLOR_MENU_ORDERING_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getColorMenuOrdering()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setColorsOn1stLevelColorMenu_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setColorsOn1stLevelColorMenu("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.COLORS_ON_1ST_LEVEL_COLOR_MENU_)).isEqualTo("ABC");
    }
    @Test
    public void test_getColorsOn1stLevelColorMenu_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.COLORS_ON_1ST_LEVEL_COLOR_MENU_, "ABC");

        assertThat(instance.getColorsOn1stLevelColorMenu()).isEqualTo("ABC");
    }


    @Test
    public void test_setColorsOn2ndLevelColorMenu_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setColorsOn2ndLevelColorMenu("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.COLORS_ON_2ND_LEVEL_COLOR_MENU_)).isEqualTo("ABC");
    }
    @Test
    public void test_getColorsOn2ndLevelColorMenu_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.COLORS_ON_2ND_LEVEL_COLOR_MENU_, "ABC");

        assertThat(instance.getColorsOn2ndLevelColorMenu()).isEqualTo("ABC");
    }


    @Test
    public void test_setNumberOfColumnsFor1stLevelColorMenu_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setNumberOfColumnsFor1stLevelColorMenu(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.NUMBER_OF_COLUMNS_FOR_1ST_LEVEL_COLOR_MENU_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getNumberOfColumnsFor1stLevelColorMenu_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.NUMBER_OF_COLUMNS_FOR_1ST_LEVEL_COLOR_MENU_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getNumberOfColumnsFor1stLevelColorMenu()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setNumberOfColumnsFor2ndLevelColorMenu_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setNumberOfColumnsFor2ndLevelColorMenu(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.NUMBER_OF_COLUMNS_FOR_2ND_LEVEL_COLOR_MENU_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getNumberOfColumnsFor2ndLevelColorMenu_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.NUMBER_OF_COLUMNS_FOR_2ND_LEVEL_COLOR_MENU_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getNumberOfColumnsFor2ndLevelColorMenu()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setDismissColorMenuAfterChoosing_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setDismissColorMenuAfterChoosing(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.DISMISS_COLOR_MENU_AFTER_CHOOSINGQ_)).isEqualTo(false);
    }
    @Test
    public void test_getDismissColorMenuAfterChoosing_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.DISMISS_COLOR_MENU_AFTER_CHOOSINGQ_, false);

        assertThat(instance.getDismissColorMenuAfterChoosing()).isEqualTo(false);
    }


}