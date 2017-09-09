package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class GraphImplTest extends G2TestBase<GraphImpl> {

    @Override
    protected Class<GraphImpl> forClass() {
        return GraphImpl.class;
    }

    @Test
    public void test_setScrollContinuously_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setScrollContinuously(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.SCROLL_CONTINUOUSLYQ_)).isEqualTo(false);
    }
    @Test
    public void test_getScrollContinuously_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.SCROLL_CONTINUOUSLYQ_, false);

        assertThat(instance.getScrollContinuously()).isEqualTo(false);
    }


    @Test
    public void test_setPercentageExtraSpaceToLeave_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setPercentageExtraSpaceToLeave(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.PERCENTAGE_EXTRA_SPACE_TO_LEAVE_)).isEqualTo(42);
    }
    @Test
    public void test_getPercentageExtraSpaceToLeave_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.PERCENTAGE_EXTRA_SPACE_TO_LEAVE_, 42);

        assertThat(instance.getPercentageExtraSpaceToLeave()).isEqualTo(42);
    }


    @Test
    public void test_setShowGridLines_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setShowGridLines(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.SHOW_GRID_LINESQ_)).isEqualTo(false);
    }
    @Test
    public void test_getShowGridLines_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.SHOW_GRID_LINESQ_, false);

        assertThat(instance.getShowGridLines()).isEqualTo(false);
    }


    @Test
    public void test_setExpressionsToDisplay_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setExpressionsToDisplay("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.EXPRESSIONS_TO_DISPLAY_)).isEqualTo("ABC");
    }
    @Test
    public void test_getExpressionsToDisplay_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.EXPRESSIONS_TO_DISPLAY_, "ABC");

        assertThat(instance.getExpressionsToDisplay()).isEqualTo("ABC");
    }


    @Test
    public void test_setLabelToDisplay_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setLabelToDisplay("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.LABEL_TO_DISPLAY_)).isEqualTo("ABC");
    }
    @Test
    public void test_getLabelToDisplay_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.LABEL_TO_DISPLAY_, "ABC");

        assertThat(instance.getLabelToDisplay()).isEqualTo("ABC");
    }


    @Test
    public void test_setDisplayUpdateInterval_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setDisplayUpdateInterval(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.DISPLAY_UPDATE_INTERVAL_)).isEqualTo(42);
    }
    @Test
    public void test_getDisplayUpdateInterval_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.DISPLAY_UPDATE_INTERVAL_, 42);

        assertThat(instance.getDisplayUpdateInterval()).isEqualTo(42);
    }


    @Test
    public void test_setDisplayWaitInterval_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setDisplayWaitInterval(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.DISPLAY_WAIT_INTERVAL_)).isEqualTo(42);
    }
    @Test
    public void test_getDisplayWaitInterval_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.DISPLAY_WAIT_INTERVAL_, 42);

        assertThat(instance.getDisplayWaitInterval()).isEqualTo(42);
    }


    @Test
    public void test_setDisplayUpdatePriority_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setDisplayUpdatePriority(getStub(com.gensym.util.Symbol.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.DISPLAY_UPDATE_PRIORITY_)).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }
    @Test
    public void test_getDisplayUpdatePriority_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.DISPLAY_UPDATE_PRIORITY_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getDisplayUpdatePriority()).isEqualTo(getStub(com.gensym.util.Symbol.class));
    }


    @Test
    public void test_setShowSimulatedValues_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setShowSimulatedValues(false);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.SHOW_SIMULATED_VALUES_)).isEqualTo(false);
    }
    @Test
    public void test_getShowSimulatedValues_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.SHOW_SIMULATED_VALUES_, false);

        assertThat(instance.getShowSimulatedValues()).isEqualTo(false);
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
    public void test_getTableRows_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.TABLE_ROWS_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getTableRows()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_getFormatType_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.FORMAT_TYPE_, getStub(com.gensym.util.Symbol.class));

        assertThat(instance.getFormatType()).isEqualTo(getStub(com.gensym.util.Symbol.class));
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