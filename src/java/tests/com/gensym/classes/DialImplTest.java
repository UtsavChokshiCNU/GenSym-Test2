package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class DialImplTest extends G2TestBase<DialImpl> {

    @Override
    protected Class<DialImpl> forClass() {
        return DialImpl.class;
    }

    @Test
    public void test_setTracingAndBreakpoints_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setTracingAndBreakpoints("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.TRACING_AND_BREAKPOINTS_)).isEqualTo("ABC");
    }
    @Test
    public void test_getTracingAndBreakpoints_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.TRACING_AND_BREAKPOINTS_, "ABC");

        assertThat(instance.getTracingAndBreakpoints()).isEqualTo("ABC");
    }


    @Test
    public void test_setLowValueForDialRuling_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setLowValueForDialRuling(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.LOW_VALUE_FOR_DIAL_RULING_)).isEqualTo(42);
    }
    @Test
    public void test_getLowValueForDialRuling_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.LOW_VALUE_FOR_DIAL_RULING_, 42);

        assertThat(instance.getLowValueForDialRuling()).isEqualTo(42);
    }


    @Test
    public void test_setIncrementPerDialRuling_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setIncrementPerDialRuling(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.INCREMENT_PER_DIAL_RULING_)).isEqualTo(42);
    }
    @Test
    public void test_getIncrementPerDialRuling_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.INCREMENT_PER_DIAL_RULING_, 42);

        assertThat(instance.getIncrementPerDialRuling()).isEqualTo(42);
    }


    @Test
    public void test_setExpressionToDisplay_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setExpressionToDisplay("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.EXPRESSION_TO_DISPLAY_)).isEqualTo("ABC");
    }
    @Test
    public void test_getExpressionToDisplay_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.EXPRESSION_TO_DISPLAY_, "ABC");

        assertThat(instance.getExpressionToDisplay()).isEqualTo("ABC");
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
    public void test_getValueToDisplay_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.VALUE_TO_DISPLAY_, 42);

        assertThat(instance.getValueToDisplay()).isEqualTo(42);
    }


    @Test
    public void test_setEvaluationAttributes_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setEvaluationAttributes(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.EVALUATION_ATTRIBUTES_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getEvaluationAttributes_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.EVALUATION_ATTRIBUTES_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getEvaluationAttributes()).isEqualTo(getStub(com.gensym.util.Structure.class));
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
    public void test_getIconDescriptionForClass_ReturnsExpected() throws Exception {
        com.gensym.util.Structure expected = mockClassAttributeValue(SystemAttributeSymbols.ICON_DESCRIPTION_, com.gensym.util.Structure.class);

        assertThat(instance.getIconDescriptionForClass()).isEqualTo(expected);
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