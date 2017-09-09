package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class SeriesTest extends ActiveXDispatchableTestBase {

    private Series component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new Series(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(65), new Variant(342))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(65), new Variant(342));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(12))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(12));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(52))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(52));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(382), new Variant(617), new
                Variant(42L), new Variant(42L), new Variant(411))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(382), new Variant(617), 42L, 42L, new Variant(411));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(625), new
                Variant(42L), new Variant(42), new Variant(941), new Variant(923), new Variant(429), new Variant(478))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(625), 42L, 42, new Variant(941), new Variant(923), new
                                Variant(429), new Variant(478));
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
    public void test_ApplyDataLabels_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x97).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ApplyDataLabels(42);
                    }
                });
    }

    @Test
    public void test_ApplyDataLabels_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x97).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(507))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ApplyDataLabels(42, new Variant(507));
                    }
                });
    }

    @Test
    public void test_ApplyDataLabels_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x97).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(188), new Variant
                (372))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ApplyDataLabels(42, new Variant(188), new Variant(372));
                    }
                });
    }

    @Test
    public void test_ApplyDataLabels_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x97).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(844), new Variant
                (171), new Variant(34))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ApplyDataLabels(42, new Variant(844), new Variant(171), new Variant(34));
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
    public void test_getAxBorder_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x80).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Border>() {
                    @Override
                    public Border invoke() throws ActiveXException {
                        return component.getAxBorder();
                    }
                });
    }

    @Test
    public void test_ClearFormats_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x70).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ClearFormats();
                    }
                });
    }

    @Test
    public void test_Copy_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x227).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Copy();
                    }
                });
    }

    @Test
    public void test_DataLabels_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x9d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.DataLabels();
                    }
                });
    }

    @Test
    public void test_DataLabels_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x9d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(233))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.DataLabels(new Variant(233));
                    }
                });
    }

    @Test
    public void test_Delete_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x75).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Delete();
                    }
                });
    }

    @Test
    public void test_ErrorBar_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x98).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42), new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ErrorBar(42, 42, 42);
                    }
                });
    }

    @Test
    public void test_ErrorBar_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x98).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42), new Variant
                (42), new Variant(460))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ErrorBar(42, 42, 42, new Variant(460));
                    }
                });
    }

    @Test
    public void test_ErrorBar_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x98).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42), new Variant
                (42), new Variant(240), new Variant(722))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ErrorBar(42, 42, 42, new Variant(240), new Variant(722));
                    }
                });
    }

    @Test
    public void test_getAxErrorBars_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x9f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<ErrorBars>() {
                    @Override
                    public ErrorBars invoke() throws ActiveXException {
                        return component.getAxErrorBars();
                    }
                });
    }

    @Test
    public void test_getAxExplosion_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxExplosion();
                    }
                });
    }

    @Test
    public void test_setAxExplosion_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xb6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxExplosion(42);
                    }
                });
    }

    @Test
    public void test_getAxFormula_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x105).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxFormula();
                    }
                });
    }

    @Test
    public void test_setAxFormula_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x105).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("PrIdpvByva"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxFormula("PrIdpvByva");
                    }
                });
    }

    @Test
    public void test_getAxFormulaLocal_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x107).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxFormulaLocal();
                    }
                });
    }

    @Test
    public void test_setAxFormulaLocal_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x107).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("tkdPOBTEkG"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxFormulaLocal("tkdPOBTEkG");
                    }
                });
    }

    @Test
    public void test_getAxFormulaR1C1_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x108).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxFormulaR1C1();
                    }
                });
    }

    @Test
    public void test_setAxFormulaR1C1_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x108).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("CJqeskuAxL"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxFormulaR1C1("CJqeskuAxL");
                    }
                });
    }

    @Test
    public void test_getAxFormulaR1C1Local_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x109).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxFormulaR1C1Local();
                    }
                });
    }

    @Test
    public void test_setAxFormulaR1C1Local_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x109).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("PqglgstuFD"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxFormulaR1C1Local("PqglgstuFD");
                    }
                });
    }

    @Test
    public void test_getAxHasDataLabels_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x4e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxHasDataLabels();
                    }
                });
    }

    @Test
    public void test_setAxHasDataLabels_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x4e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHasDataLabels(false);
                    }
                });
    }

    @Test
    public void test_getAxHasErrorBars_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxHasErrorBars();
                    }
                });
    }

    @Test
    public void test_setAxHasErrorBars_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xa0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHasErrorBars(false);
                    }
                });
    }

    @Test
    public void test_getAxInterior_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x81).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Interior>() {
                    @Override
                    public Interior invoke() throws ActiveXException {
                        return component.getAxInterior();
                    }
                });
    }

    @Test
    public void test_getAxFill_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x67f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<ChartFillFormat>() {
                    @Override
                    public ChartFillFormat invoke() throws ActiveXException {
                        return component.getAxFill();
                    }
                });
    }

    @Test
    public void test_getAxInvertIfNegative_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x84).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxInvertIfNegative();
                    }
                });
    }

    @Test
    public void test_setAxInvertIfNegative_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x84).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxInvertIfNegative(false);
                    }
                });
    }

    @Test
    public void test_getAxMarkerBackgroundColor_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x49).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxMarkerBackgroundColor();
                    }
                });
    }

    @Test
    public void test_setAxMarkerBackgroundColor_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x49).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMarkerBackgroundColor(42);
                    }
                });
    }

    @Test
    public void test_getAxMarkerBackgroundColorIndex_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x4a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxMarkerBackgroundColorIndex();
                    }
                });
    }

    @Test
    public void test_setAxMarkerBackgroundColorIndex_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x4a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMarkerBackgroundColorIndex(42);
                    }
                });
    }

    @Test
    public void test_getAxMarkerForegroundColor_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x4b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxMarkerForegroundColor();
                    }
                });
    }

    @Test
    public void test_setAxMarkerForegroundColor_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x4b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMarkerForegroundColor(42);
                    }
                });
    }

    @Test
    public void test_getAxMarkerForegroundColorIndex_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x4c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxMarkerForegroundColorIndex();
                    }
                });
    }

    @Test
    public void test_setAxMarkerForegroundColorIndex_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x4c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMarkerForegroundColorIndex(42);
                    }
                });
    }

    @Test
    public void test_getAxMarkerSize_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xe7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxMarkerSize();
                    }
                });
    }

    @Test
    public void test_setAxMarkerSize_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xe7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMarkerSize(42);
                    }
                });
    }

    @Test
    public void test_getAxMarkerStyle_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x48).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxMarkerStyle();
                    }
                });
    }

    @Test
    public void test_setAxMarkerStyle_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x48).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMarkerStyle(42);
                    }
                });
    }

    @Test
    public void test_getAxName_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxName();
                    }
                });
    }

    @Test
    public void test_setAxName_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("BjOPZiGoew"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxName("BjOPZiGoew");
                    }
                });
    }

    @Test
    public void test_Paste_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xd3).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Paste();
                    }
                });
    }

    @Test
    public void test_getAxPictureType_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxPictureType();
                    }
                });
    }

    @Test
    public void test_setAxPictureType_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xa1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPictureType(42);
                    }
                });
    }

    @Test
    public void test_getAxPictureUnit_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxPictureUnit();
                    }
                });
    }

    @Test
    public void test_setAxPictureUnit_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xa2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPictureUnit(42);
                    }
                });
    }

    @Test
    public void test_getAxPlotOrder_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xe4).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxPlotOrder();
                    }
                });
    }

    @Test
    public void test_setAxPlotOrder_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xe4).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPlotOrder(42);
                    }
                });
    }

    @Test
    public void test_Points_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x46).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Points();
                    }
                });
    }

    @Test
    public void test_Points_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x46).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(656))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Points(new Variant(656));
                    }
                });
    }

    @Test
    public void test_Select_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xeb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Select();
                    }
                });
    }

    @Test
    public void test_getAxSmooth_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa3).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxSmooth();
                    }
                });
    }

    @Test
    public void test_setAxSmooth_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xa3).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSmooth(false);
                    }
                });
    }

    @Test
    public void test_Trendlines_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x9a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Trendlines();
                    }
                });
    }

    @Test
    public void test_Trendlines_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x9a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(362))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Trendlines(new Variant(362));
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
    public void test_getAxChartType_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x578).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxChartType();
                    }
                });
    }

    @Test
    public void test_setAxChartType_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x578).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxChartType(42);
                    }
                });
    }

    @Test
    public void test_ApplyCustomType_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x579).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ApplyCustomType(42);
                    }
                });
    }

    @Test
    public void test_getAxValues_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa4).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxValues();
                    }
                });
    }

    @Test
    public void test_setAxValues_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xa4).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(166))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxValues(new Variant(166));
                    }
                });
    }

    @Test
    public void test_getAxXValues_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x457).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxXValues();
                    }
                });
    }

    @Test
    public void test_setAxXValues_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x457).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(156))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxXValues(new Variant(156));
                    }
                });
    }

    @Test
    public void test_getAxBubbleSizes_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x680).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxBubbleSizes();
                    }
                });
    }

    @Test
    public void test_setAxBubbleSizes_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x680).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(693))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxBubbleSizes(new Variant(693));
                    }
                });
    }

    @Test
    public void test_getAxBarShape_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x57b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxBarShape();
                    }
                });
    }

    @Test
    public void test_setAxBarShape_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x57b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxBarShape(42);
                    }
                });
    }

    @Test
    public void test_getAxApplyPictToSides_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x67b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxApplyPictToSides();
                    }
                });
    }

    @Test
    public void test_setAxApplyPictToSides_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x67b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxApplyPictToSides(false);
                    }
                });
    }

    @Test
    public void test_getAxApplyPictToFront_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x67c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxApplyPictToFront();
                    }
                });
    }

    @Test
    public void test_setAxApplyPictToFront_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x67c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxApplyPictToFront(false);
                    }
                });
    }

    @Test
    public void test_getAxApplyPictToEnd_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x67d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxApplyPictToEnd();
                    }
                });
    }

    @Test
    public void test_setAxApplyPictToEnd_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x67d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxApplyPictToEnd(false);
                    }
                });
    }

    @Test
    public void test_getAxHas3DEffect_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x681).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxHas3DEffect();
                    }
                });
    }

    @Test
    public void test_setAxHas3DEffect_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x681).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHas3DEffect(false);
                    }
                });
    }

    @Test
    public void test_getAxShadow_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x67).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxShadow();
                    }
                });
    }

    @Test
    public void test_setAxShadow_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x67).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxShadow(false);
                    }
                });
    }

    @Test
    public void test_getAxHasLeaderLines_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x572).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxHasLeaderLines();
                    }
                });
    }

    @Test
    public void test_setAxHasLeaderLines_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x572).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHasLeaderLines(false);
                    }
                });
    }

    @Test
    public void test_getAxLeaderLines_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x682).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<LeaderLines>() {
                    @Override
                    public LeaderLines invoke() throws ActiveXException {
                        return component.getAxLeaderLines();
                    }
                });
    }

}