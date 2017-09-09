package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class FreeTextImplTest extends G2TestBase<FreeTextImpl> {

    @Override
    protected Class<FreeTextImpl> forClass() {
        return FreeTextImpl.class;
    }

    @Test
    public void test_setMinimumSizeInWorkspace_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setMinimumSizeInWorkspace(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.MINIMUM_SIZE_IN_WORKSPACE_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getMinimumSizeInWorkspace_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.MINIMUM_SIZE_IN_WORKSPACE_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getMinimumSizeInWorkspace()).isEqualTo(getStub(com.gensym.util.Structure.class));
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
    public void test_setText_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setText("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.TEXT_)).isEqualTo("ABC");
    }
    @Test
    public void test_getText_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.TEXT_, "ABC");

        assertThat(instance.getText()).isEqualTo("ABC");
    }


    @Test
    public void test_getTextYMagnification_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.TEXT_Y_MAGNIFICATION_, 42);

        assertThat(instance.getTextYMagnification()).isEqualTo(42);
    }


    @Test
    public void test_getTextXMagnification_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.TEXT_X_MAGNIFICATION_, 42);

        assertThat(instance.getTextXMagnification()).isEqualTo(42);
    }


    @Test
    public void test_setTextFont_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setTextFont(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.TEXT_FONT_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getTextFont_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.TEXT_FONT_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getTextFont()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_setTextAlignment_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setTextAlignment(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.TEXT_ALIGNMENT_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getTextAlignment_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.TEXT_ALIGNMENT_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getTextAlignment()).isEqualTo(getStub(com.gensym.util.Symbol.class));
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
    public void test_getFormatType_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.FORMAT_TYPE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getFormatType()).isEqualTo(getStub(com.gensym.util.Symbol.class));
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
    public void test_setItemConfiguration_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setItemConfiguration(getStub(com.gensym.util.Sequence.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.ITEM_CONFIGURATION_)).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }
    @Test
    public void test_getItemConfiguration_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ITEM_CONFIGURATION_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getItemConfiguration()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_setNames_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setNames("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.NAMES_)).isEqualTo("ABC");
    }
    @Test
    public void test_getNames_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.NAMES_, "ABC");

        assertThat(instance.getNames()).isEqualTo("ABC");
    }


    @Test
    public void test_getLayerPosition_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.LAYER_POSITION_, 42);

        assertThat(instance.getLayerPosition()).isEqualTo(42);
    }


    @Test
    public void test_setFollowingItemInWorkspaceLayering_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setFollowingItemInWorkspaceLayering(getStub(com.gensym.classes.Block.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.FOLLOWING_ITEM_IN_WORKSPACE_LAYERING_)).isEqualTo(getStub(com.gensym.classes.Block.class));
    }
    @Test
    public void test_getFollowingItemInWorkspaceLayering_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.FOLLOWING_ITEM_IN_WORKSPACE_LAYERING_, getStub(com.gensym.classes.Block.class));

        assertThat(instance.getFollowingItemInWorkspaceLayering()).isEqualTo(getStub(com.gensym.classes.Block.class));
    }


    @Test
    public void test_setPositionInWorkspace_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setPositionInWorkspace(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.POSITION_IN_WORKSPACE_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getPositionInWorkspace_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.POSITION_IN_WORKSPACE_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getPositionInWorkspace()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_setRelationships_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setRelationships(getStub(com.gensym.util.Sequence.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.RELATIONSHIPS_)).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }
    @Test
    public void test_getRelationships_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.RELATIONSHIPS_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getRelationships()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_getItemNotes_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ITEM_NOTES_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getItemNotes()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_getContainingModule_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.CONTAINING_MODULE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getContainingModule()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_getItemActive_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ITEM_ACTIVE_, false);

        assertThat(instance.getItemActive()).isEqualTo(false);
    }


    @Test
    public void test_getItemStatus_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.ITEM_STATUS_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getItemStatus()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_getDefaultTextBoxFormatNameForClass_ReturnsExpected() throws Exception {
        com.gensym.util.Symbol expected = mockClassAttributeValue(SystemAttributeSymbols.DEFAULT_TEXT_BOX_FORMAT_NAME_, com.gensym.util.Symbol.class);

        assertThat(instance.getDefaultTextBoxFormatNameForClass()).isEqualTo(expected);
    }


    @Test
    public void test_getInstantiateForClass_ReturnsExpected() throws Exception {
        boolean expected = mockClassAttributeValue(SystemAttributeSymbols.INSTANTIATE_, boolean.class);

        assertThat(instance.getInstantiateForClass()).isEqualTo(expected);
    }


    @Test
    public void test_getIncludeInMenusForClass_ReturnsExpected() throws Exception {
        boolean expected = mockClassAttributeValue(SystemAttributeSymbols.INCLUDE_IN_MENUS_, boolean.class);

        assertThat(instance.getIncludeInMenusForClass()).isEqualTo(expected);
    }


    @Test
    public void test_getSystemMenuChoicesForClass_ReturnsExpected() throws Exception {
        java.lang.Object expected = mockClassAttributeValue(SystemAttributeSymbols.SYSTEM_MENU_CHOICES_, java.lang.Object.class);

        assertThat(instance.getSystemMenuChoicesForClass()).isEqualTo(expected);
    }


}