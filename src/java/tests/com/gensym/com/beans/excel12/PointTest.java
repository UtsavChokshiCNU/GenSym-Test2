package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class PointTest extends ActiveXDispatchableTestBase {

    private Point component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new Point(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(125), new Variant(699))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(125), new Variant(699));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(337))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(337));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(787))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(787));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(38), new Variant(87), new
                Variant(42L), new Variant(42L), new Variant(301))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(38), new Variant(87), 42L, 42L, new Variant(301));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(878), new
                Variant(42L), new Variant(42), new Variant(140), new Variant(917), new Variant(230), new Variant(855))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(878), 42L, 42, new Variant(140), new Variant(917), new
                                Variant(230), new Variant(855));
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
        on(0x97).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(897))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ApplyDataLabels(42, new Variant(897));
                    }
                });
    }

    @Test
    public void test_ApplyDataLabels_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x97).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(14), new Variant
                (964))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ApplyDataLabels(42, new Variant(14), new Variant(964));
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
    public void test_getAxDataLabel_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x9e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<DataLabel>() {
                    @Override
                    public DataLabel invoke() throws ActiveXException {
                        return component.getAxDataLabel();
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
    public void test_getAxHasDataLabel_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x4d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxHasDataLabel();
                    }
                });
    }

    @Test
    public void test_setAxHasDataLabel_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x4d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHasDataLabel(false);
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
    public void test_getAxSecondaryPlot_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x67e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxSecondaryPlot();
                    }
                });
    }

    @Test
    public void test_setAxSecondaryPlot_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x67e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSecondaryPlot(false);
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

}