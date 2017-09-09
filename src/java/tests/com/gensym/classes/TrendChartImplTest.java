package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class TrendChartImplTest extends G2TestBase<TrendChartImpl> {

    @Override
    protected Class<TrendChartImpl> forClass() {
        return TrendChartImpl.class;
    }

    @Test
    public void test_setTitle_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setTitle("ABC");

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.TITLE_)).isEqualTo("ABC");
    }
    @Test
    public void test_getTitle_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.TITLE_, "ABC");

        assertThat(instance.getTitle()).isEqualTo("ABC");
    }


    @Test
    public void test_setPlots_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setPlots(getStub(com.gensym.util.Sequence.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.PLOTS_)).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }
    @Test
    public void test_getPlots_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.PLOTS_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getPlots()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_setValueAxes_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setValueAxes(getStub(com.gensym.util.Sequence.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.VALUE_AXES_)).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }
    @Test
    public void test_getValueAxes_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.VALUE_AXES_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getValueAxes()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_setTimeAxis_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setTimeAxis(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.TIME_AXIS_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getTimeAxis_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.TIME_AXIS_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getTimeAxis()).isEqualTo(getStub(com.gensym.util.Structure.class));
    }


    @Test
    public void test_setPointFormats_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setPointFormats(getStub(com.gensym.util.Sequence.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.POINT_FORMATS_)).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }
    @Test
    public void test_getPointFormats_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.POINT_FORMATS_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getPointFormats()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_setConnectorFormats_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setConnectorFormats(getStub(com.gensym.util.Sequence.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.CONNECTOR_FORMATS_)).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }
    @Test
    public void test_getConnectorFormats_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.CONNECTOR_FORMATS_, getStub(com.gensym.util.Sequence.class));

        assertThat(instance.getConnectorFormats()).isEqualTo(getStub(com.gensym.util.Sequence.class));
    }


    @Test
    public void test_setTrendChartFormat_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setTrendChartFormat(getStub(com.gensym.util.Structure.class));

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.TREND_CHART_FORMAT_)).isEqualTo(getStub(com.gensym.util.Structure.class));
    }
    @Test
    public void test_getTrendChartFormat_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.TREND_CHART_FORMAT_, getStub(com.gensym.util.Structure.class));

        assertThat(instance.getTrendChartFormat()).isEqualTo(getStub(com.gensym.util.Structure.class));
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