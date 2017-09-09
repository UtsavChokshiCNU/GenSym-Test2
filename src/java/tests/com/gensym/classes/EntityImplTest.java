package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class EntityImplTest extends G2TestBase<EntityImpl> {

    @Override
    protected Class<EntityImpl> forClass() {
        return EntityImpl.class;
    }

    @Test
    public void test_getAttributeDisplayItems_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ATTRIBUTE_DISPLAY_ITEMS_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getAttributeDisplayItems()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_getNameBoxItem_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.NAME_BOX_ITEM_, "ABC");

        assertThat(instance.getNameBoxItem()).isEqualTo("ABC");
    }


    @Test
    public void test_setIconVariables_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setIconVariables(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.ICON_VARIABLES_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getIconVariables_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ICON_VARIABLES_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getIconVariables()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_setIconColor_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setIconColor(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.ICON_COLOR_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getIconColor_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ICON_COLOR_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getIconColor()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setIconReflection_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setIconReflection(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.ICON_REFLECTION_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getIconReflection_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ICON_REFLECTION_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getIconReflection()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setIconHeading_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setIconHeading(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.ICON_HEADING_)).isEqualTo(42);
    }
    @Test
    public void test_getIconHeading_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ICON_HEADING_, 42);

        assertThat(instance.getIconHeading()).isEqualTo(42);
    }


    @Test
    public void test_setItemColorPattern_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setItemColorPattern(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.ITEM_COLOR_PATTERN_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getItemColorPattern_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ITEM_COLOR_PATTERN_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getItemColorPattern()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_setSizeInWorkspace_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setSizeInWorkspace(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.SIZE_IN_WORKSPACE_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getSizeInWorkspace_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.SIZE_IN_WORKSPACE_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getSizeInWorkspace()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_setCurrentAttributeDisplays_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setCurrentAttributeDisplays(getStub(com.gensym.util.Sequence.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.CURRENT_ATTRIBUTE_DISPLAYS_)).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }
    @Test
    public void test_getCurrentAttributeDisplays_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.CURRENT_ATTRIBUTE_DISPLAYS_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getCurrentAttributeDisplays()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_setNameBox_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setNameBox(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.NAME_BOX_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getNameBox_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.NAME_BOX_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getNameBox()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_setStripeColor_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setStripeColor(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.STRIPE_COLOR_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getStripeColor_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.STRIPE_COLOR_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getStripeColor()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setBorderColor_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setBorderColor(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.BORDER_COLOR_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getBorderColor_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.BORDER_COLOR_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getBorderColor()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setTextColor_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setTextColor(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.TEXT_COLOR_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getTextColor_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.TEXT_COLOR_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getTextColor()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setForegroundColor_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setForegroundColor(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.FOREGROUND_COLOR_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getForegroundColor_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.FOREGROUND_COLOR_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getForegroundColor()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setBackgroundColor_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setBackgroundColor(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.BACKGROUND_COLOR_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getBackgroundColor_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.BACKGROUND_COLOR_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getBackgroundColor()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_getIconDescriptionForClass_ReturnsExpected() throws Exception {
        com.gensym.util.Structure expected = mockClassAttributeValue(SystemAttributeSymbols.ICON_DESCRIPTION_, com.gensym.util.Structure.class);

        assertThat(instance.getIconDescriptionForClass()).isEqualTo(expected);
    }


}