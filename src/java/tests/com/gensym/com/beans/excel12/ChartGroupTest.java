package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class ChartGroupTest extends ActiveXDispatchableTestBase {

    private ChartGroup component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new ChartGroup(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(233), new Variant(410))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(233), new Variant(410));
                    }
                });
    }

    @Test
    public void test_AddRef_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsLong(new Returns<Long>() {
                    @Override
                    public Long invoke() throws ActiveXException {
                        return component.AddRef();
                    }
                });
    }

    @Test
    public void test_Release_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsLong(new Returns<Long>() {
                    @Override
                    public Long invoke() throws ActiveXException {
                        return component.Release();
                    }
                });
    }

    @Test
    public void test_GetTypeInfoCount_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(424))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(424));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(558))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(558));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(786), new Variant(471), new
                Variant(42L), new Variant(42L), new Variant(295))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(786), new Variant(471), 42L, 42L, new Variant(295));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(107), new
                Variant(42L), new Variant(42), new Variant(774), new Variant(507), new Variant(835), new Variant(564))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(107), 42L, 42, new Variant(774), new Variant(507), new
                                Variant(835), new Variant(564));
                    }
                });
    }

    @Test
    public void test_getAxApplication_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x94).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<ExcelApplication>() {
                    @Override
                    public ExcelApplication invoke() throws ActiveXException {
                        return component.getAxApplication();
                    }
                });
    }

    @Test
    public void test_getAxCreator_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x95).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxCreator();
                    }
                });
    }

    @Test
    public void test_getAxParent_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x96).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxParent();
                    }
                });
    }

    @Test
    public void test_getAxAxisGroup_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxAxisGroup();
                    }
                });
    }

    @Test
    public void test_setAxAxisGroup_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxAxisGroup(42);
                    }
                });
    }

    @Test
    public void test_getAxDoughnutHoleSize_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x466).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxDoughnutHoleSize();
                    }
                });
    }

    @Test
    public void test_setAxDoughnutHoleSize_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x466).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDoughnutHoleSize(42);
                    }
                });
    }

    @Test
    public void test_getAxDownBars_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x8d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<DownBars>() {
                    @Override
                    public DownBars invoke() throws ActiveXException {
                        return component.getAxDownBars();
                    }
                });
    }

    @Test
    public void test_getAxDropLines_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x8e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<DropLines>() {
                    @Override
                    public DropLines invoke() throws ActiveXException {
                        return component.getAxDropLines();
                    }
                });
    }

    @Test
    public void test_getAxFirstSliceAngle_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxFirstSliceAngle();
                    }
                });
    }

    @Test
    public void test_setAxFirstSliceAngle_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxFirstSliceAngle(42);
                    }
                });
    }

    @Test
    public void test_getAxGapWidth_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x33).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxGapWidth();
                    }
                });
    }

    @Test
    public void test_setAxGapWidth_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x33).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxGapWidth(42);
                    }
                });
    }

    @Test
    public void test_getAxHasDropLines_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxHasDropLines();
                    }
                });
    }

    @Test
    public void test_setAxHasDropLines_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHasDropLines(false);
                    }
                });
    }

    @Test
    public void test_getAxHasHiLoLines_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxHasHiLoLines();
                    }
                });
    }

    @Test
    public void test_setAxHasHiLoLines_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHasHiLoLines(false);
                    }
                });
    }

    @Test
    public void test_getAxHasRadarAxisLabels_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x40).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxHasRadarAxisLabels();
                    }
                });
    }

    @Test
    public void test_setAxHasRadarAxisLabels_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x40).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHasRadarAxisLabels(false);
                    }
                });
    }

    @Test
    public void test_getAxHasSeriesLines_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x41).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxHasSeriesLines();
                    }
                });
    }

    @Test
    public void test_setAxHasSeriesLines_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x41).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHasSeriesLines(false);
                    }
                });
    }

    @Test
    public void test_getAxHasUpDownBars_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x42).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxHasUpDownBars();
                    }
                });
    }

    @Test
    public void test_setAxHasUpDownBars_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x42).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHasUpDownBars(false);
                    }
                });
    }

    @Test
    public void test_getAxHiLoLines_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x8f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<HiLoLines>() {
                    @Override
                    public HiLoLines invoke() throws ActiveXException {
                        return component.getAxHiLoLines();
                    }
                });
    }

    @Test
    public void test_getAxIndex_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1e6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxIndex();
                    }
                });
    }

    @Test
    public void test_getAxOverlap_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x38).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxOverlap();
                    }
                });
    }

    @Test
    public void test_setAxOverlap_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x38).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOverlap(42);
                    }
                });
    }

    @Test
    public void test_getAxRadarAxisLabels_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x90).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<TickLabels>() {
                    @Override
                    public TickLabels invoke() throws ActiveXException {
                        return component.getAxRadarAxisLabels();
                    }
                });
    }

    @Test
    public void test_SeriesCollection_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x44).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.SeriesCollection();
                    }
                });
    }

    @Test
    public void test_SeriesCollection_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x44).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(367))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.SeriesCollection(new Variant(367));
                    }
                });
    }

    @Test
    public void test_getAxSeriesLines_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x91).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<SeriesLines>() {
                    @Override
                    public SeriesLines invoke() throws ActiveXException {
                        return component.getAxSeriesLines();
                    }
                });
    }

    @Test
    public void test_getAxSubType_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxSubType();
                    }
                });
    }

    @Test
    public void test_setAxSubType_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSubType(42);
                    }
                });
    }

    @Test
    public void test_getAxType_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxType();
                    }
                });
    }

    @Test
    public void test_setAxType_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxType(42);
                    }
                });
    }

    @Test
    public void test_getAxUpBars_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x8c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<UpBars>() {
                    @Override
                    public UpBars invoke() throws ActiveXException {
                        return component.getAxUpBars();
                    }
                });
    }

    @Test
    public void test_getAxVaryByCategories_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxVaryByCategories();
                    }
                });
    }

    @Test
    public void test_setAxVaryByCategories_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxVaryByCategories(false);
                    }
                });
    }

    @Test
    public void test_getAxSizeRepresents_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x674).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxSizeRepresents();
                    }
                });
    }

    @Test
    public void test_setAxSizeRepresents_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x674).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSizeRepresents(42);
                    }
                });
    }

    @Test
    public void test_getAxBubbleScale_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x675).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxBubbleScale();
                    }
                });
    }

    @Test
    public void test_setAxBubbleScale_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x675).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxBubbleScale(42);
                    }
                });
    }

    @Test
    public void test_getAxShowNegativeBubbles_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x676).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxShowNegativeBubbles();
                    }
                });
    }

    @Test
    public void test_setAxShowNegativeBubbles_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x676).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxShowNegativeBubbles(false);
                    }
                });
    }

    @Test
    public void test_getAxSplitType_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x677).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxSplitType();
                    }
                });
    }

    @Test
    public void test_setAxSplitType_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x677).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSplitType(42);
                    }
                });
    }

    @Test
    public void test_getAxSplitValue_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x678).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxSplitValue();
                    }
                });
    }

    @Test
    public void test_setAxSplitValue_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x678).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(585))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSplitValue(new Variant(585));
                    }
                });
    }

    @Test
    public void test_getAxSecondPlotSize_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x679).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxSecondPlotSize();
                    }
                });
    }

    @Test
    public void test_setAxSecondPlotSize_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x679).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSecondPlotSize(42);
                    }
                });
    }

    @Test
    public void test_getAxHas3DShading_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x67a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxHas3DShading();
                    }
                });
    }

    @Test
    public void test_setAxHas3DShading_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x67a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHas3DShading(false);
                    }
                });
    }

}