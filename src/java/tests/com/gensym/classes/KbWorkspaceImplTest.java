package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class KbWorkspaceImplTest extends G2TestBase<KbWorkspaceImpl> {

    @Override
    protected Class<KbWorkspaceImpl> forClass() {
        return KbWorkspaceImpl.class;
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
    public void test_setModuleAssignment_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setModuleAssignment(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.MODULE_ASSIGNMENT_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getModuleAssignment_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.MODULE_ASSIGNMENT_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getModuleAssignment()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setDefaultWindowPositionAndScale_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setDefaultWindowPositionAndScale(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.DEFAULT_WINDOW_POSITION_AND_SCALE_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getDefaultWindowPositionAndScale_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.DEFAULT_WINDOW_POSITION_AND_SCALE_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getDefaultWindowPositionAndScale()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_setEdgesOfWorkspace_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setEdgesOfWorkspace(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.EDGES_OF_WORKSPACE_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getEdgesOfWorkspace_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.EDGES_OF_WORKSPACE_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getEdgesOfWorkspace()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_setParentOfSubworkspace_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setParentOfSubworkspace(getStub(com.gensym.classes.Block.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.PARENT_OF_SUBWORKSPACE_)).isEqualTo(getStub(com.gensym.classes.Block.class));
    }
    @Test
    public void test_getParentOfSubworkspace_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.PARENT_OF_SUBWORKSPACE_, getStub(com.gensym.classes.Block.class));

        assertThat(instance.getParentOfSubworkspace()).isEqualTo(getStub(com.gensym.classes.Block.class));
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
    public void test_setWorkspaceMargin_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setWorkspaceMargin(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.WORKSPACE_MARGIN_)).isEqualTo(42);
    }
    @Test
    public void test_getWorkspaceMargin_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.WORKSPACE_MARGIN_, 42);

        assertThat(instance.getWorkspaceMargin()).isEqualTo(42);
    }


    @Test
    public void test_setBackgroundImages_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setBackgroundImages(getStub(com.gensym.util.Sequence.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.BACKGROUND_IMAGES_)).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }
    @Test
    public void test_getBackgroundImages_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.BACKGROUND_IMAGES_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getBackgroundImages()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_setFrameStyle_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setFrameStyle(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.FRAME_STYLE_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getFrameStyle_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.FRAME_STYLE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getFrameStyle()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setTitleBarText_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setTitleBarText("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.TITLE_BAR_TEXT_)).isEqualTo("ABC");
    }
    @Test
    public void test_getTitleBarText_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.TITLE_BAR_TEXT_, "ABC");

        assertThat(instance.getTitleBarText()).isEqualTo("ABC");
    }


    @Test
    public void test_setViewPreferences_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setViewPreferences(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.VIEW_PREFERENCES_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getViewPreferences_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.VIEW_PREFERENCES_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getViewPreferences()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_setPreferBufferedDrawing_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setPreferBufferedDrawing(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.PREFER_BUFFERED_DRAWING_)).isEqualTo(false);
    }
    @Test
    public void test_getPreferBufferedDrawing_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.PREFER_BUFFERED_DRAWING_, false);

        assertThat(instance.getPreferBufferedDrawing()).isEqualTo(false);
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
    public void test_getKbWorkspaceInitialWidthForClass_ReturnsExpected() throws Exception {
        int expected = mockClassAttributeValue(SystemAttributeSymbols.KB_WORKSPACE_INITIAL_WIDTH_, int.class);

        assertThat(instance.getKbWorkspaceInitialWidthForClass()).isEqualTo(expected);
    }


    @Test
    public void test_getKbWorkspaceInitialHeightForClass_ReturnsExpected() throws Exception {
        int expected = mockClassAttributeValue(SystemAttributeSymbols.KB_WORKSPACE_INITIAL_HEIGHT_, int.class);

        assertThat(instance.getKbWorkspaceInitialHeightForClass()).isEqualTo(expected);
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