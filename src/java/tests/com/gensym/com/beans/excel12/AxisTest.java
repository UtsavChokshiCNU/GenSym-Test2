package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class AxisTest extends ActiveXDispatchableTestBase {

    private Axis component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new Axis(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(204), new Variant(259))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(204), new Variant(259));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(604))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(604));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(577))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(577));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(828), new Variant(798), new
                Variant(42L), new Variant(42L), new Variant(246))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(828), new Variant(798), 42L, 42L, new Variant(246));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(808), new
                Variant(42L), new Variant(42), new Variant(703), new Variant(75), new Variant(294), new Variant(401))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(808), 42L, 42, new Variant(703), new Variant(75), new
                                Variant(294), new Variant(401));
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
    public void test_getAxAxisBetweenCategories_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxAxisBetweenCategories();
                    }
                });
    }

    @Test
    public void test_setAxAxisBetweenCategories_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxAxisBetweenCategories(false);
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
    public void test_getAxAxisTitle_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x52).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<AxisTitle>() {
                    @Override
                    public AxisTitle invoke() throws ActiveXException {
                        return component.getAxAxisTitle();
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
    public void test_getAxCategoryNames_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x9c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxCategoryNames();
                    }
                });
    }

    @Test
    public void test_setAxCategoryNames_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x9c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(94))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCategoryNames(new Variant(94));
                    }
                });
    }

    @Test
    public void test_getAxCrosses_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxCrosses();
                    }
                });
    }

    @Test
    public void test_setAxCrosses_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCrosses(42);
                    }
                });
    }

    @Test
    public void test_getAxCrossesAt_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxCrossesAt();
                    }
                });
    }

    @Test
    public void test_setAxCrossesAt_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32d))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCrossesAt(42.32d);
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
    public void test_getAxHasMajorGridlines_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x18).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxHasMajorGridlines();
                    }
                });
    }

    @Test
    public void test_setAxHasMajorGridlines_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x18).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHasMajorGridlines(false);
                    }
                });
    }

    @Test
    public void test_getAxHasMinorGridlines_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x19).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxHasMinorGridlines();
                    }
                });
    }

    @Test
    public void test_setAxHasMinorGridlines_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x19).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHasMinorGridlines(false);
                    }
                });
    }

    @Test
    public void test_getAxHasTitle_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x36).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxHasTitle();
                    }
                });
    }

    @Test
    public void test_setAxHasTitle_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x36).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHasTitle(false);
                    }
                });
    }

    @Test
    public void test_getAxMajorGridlines_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x59).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Gridlines>() {
                    @Override
                    public Gridlines invoke() throws ActiveXException {
                        return component.getAxMajorGridlines();
                    }
                });
    }

    @Test
    public void test_getAxMajorTickMark_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxMajorTickMark();
                    }
                });
    }

    @Test
    public void test_setAxMajorTickMark_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x1a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMajorTickMark(42);
                    }
                });
    }

    @Test
    public void test_getAxMajorUnit_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x25).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxMajorUnit();
                    }
                });
    }

    @Test
    public void test_setAxMajorUnit_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x25).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32d))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMajorUnit(42.32d);
                    }
                });
    }

    @Test
    public void test_getAxMajorUnitIsAuto_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x26).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxMajorUnitIsAuto();
                    }
                });
    }

    @Test
    public void test_setAxMajorUnitIsAuto_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x26).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMajorUnitIsAuto(false);
                    }
                });
    }

    @Test
    public void test_getAxMaximumScale_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x23).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxMaximumScale();
                    }
                });
    }

    @Test
    public void test_setAxMaximumScale_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x23).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32d))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMaximumScale(42.32d);
                    }
                });
    }

    @Test
    public void test_getAxMaximumScaleIsAuto_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x24).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxMaximumScaleIsAuto();
                    }
                });
    }

    @Test
    public void test_setAxMaximumScaleIsAuto_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x24).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMaximumScaleIsAuto(false);
                    }
                });
    }

    @Test
    public void test_getAxMinimumScale_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x21).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxMinimumScale();
                    }
                });
    }

    @Test
    public void test_setAxMinimumScale_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x21).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32d))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMinimumScale(42.32d);
                    }
                });
    }

    @Test
    public void test_getAxMinimumScaleIsAuto_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x22).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxMinimumScaleIsAuto();
                    }
                });
    }

    @Test
    public void test_setAxMinimumScaleIsAuto_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x22).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMinimumScaleIsAuto(false);
                    }
                });
    }

    @Test
    public void test_getAxMinorGridlines_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Gridlines>() {
                    @Override
                    public Gridlines invoke() throws ActiveXException {
                        return component.getAxMinorGridlines();
                    }
                });
    }

    @Test
    public void test_getAxMinorTickMark_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxMinorTickMark();
                    }
                });
    }

    @Test
    public void test_setAxMinorTickMark_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x1b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMinorTickMark(42);
                    }
                });
    }

    @Test
    public void test_getAxMinorUnit_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x27).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxMinorUnit();
                    }
                });
    }

    @Test
    public void test_setAxMinorUnit_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x27).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32d))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMinorUnit(42.32d);
                    }
                });
    }

    @Test
    public void test_getAxMinorUnitIsAuto_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x28).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxMinorUnitIsAuto();
                    }
                });
    }

    @Test
    public void test_setAxMinorUnitIsAuto_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x28).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMinorUnitIsAuto(false);
                    }
                });
    }

    @Test
    public void test_getAxReversePlotOrder_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxReversePlotOrder();
                    }
                });
    }

    @Test
    public void test_setAxReversePlotOrder_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxReversePlotOrder(false);
                    }
                });
    }

    @Test
    public void test_getAxScaleType_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x29).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxScaleType();
                    }
                });
    }

    @Test
    public void test_setAxScaleType_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x29).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxScaleType(42);
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
    public void test_getAxTickLabelPosition_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxTickLabelPosition();
                    }
                });
    }

    @Test
    public void test_setAxTickLabelPosition_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x1c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxTickLabelPosition(42);
                    }
                });
    }

    @Test
    public void test_getAxTickLabels_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<TickLabels>() {
                    @Override
                    public TickLabels invoke() throws ActiveXException {
                        return component.getAxTickLabels();
                    }
                });
    }

    @Test
    public void test_getAxTickLabelSpacing_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxTickLabelSpacing();
                    }
                });
    }

    @Test
    public void test_setAxTickLabelSpacing_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x1d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxTickLabelSpacing(42);
                    }
                });
    }

    @Test
    public void test_getAxTickMarkSpacing_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxTickMarkSpacing();
                    }
                });
    }

    @Test
    public void test_setAxTickMarkSpacing_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x1f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxTickMarkSpacing(42);
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
    public void test_getAxBaseUnit_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x66f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxBaseUnit();
                    }
                });
    }

    @Test
    public void test_setAxBaseUnit_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x66f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxBaseUnit(42);
                    }
                });
    }

    @Test
    public void test_getAxBaseUnitIsAuto_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x670).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxBaseUnitIsAuto();
                    }
                });
    }

    @Test
    public void test_setAxBaseUnitIsAuto_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x670).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxBaseUnitIsAuto(false);
                    }
                });
    }

    @Test
    public void test_getAxMajorUnitScale_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x671).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxMajorUnitScale();
                    }
                });
    }

    @Test
    public void test_setAxMajorUnitScale_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x671).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMajorUnitScale(42);
                    }
                });
    }

    @Test
    public void test_getAxMinorUnitScale_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x672).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxMinorUnitScale();
                    }
                });
    }

    @Test
    public void test_setAxMinorUnitScale_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x672).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMinorUnitScale(42);
                    }
                });
    }

    @Test
    public void test_getAxCategoryType_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x673).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxCategoryType();
                    }
                });
    }

    @Test
    public void test_setAxCategoryType_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x673).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCategoryType(42);
                    }
                });
    }

    @Test
    public void test_getAxLeft_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x7f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxLeft();
                    }
                });
    }

    @Test
    public void test_getAxTop_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x7e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxTop();
                    }
                });
    }

    @Test
    public void test_getAxWidth_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x7a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxWidth();
                    }
                });
    }

    @Test
    public void test_getAxHeight_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x7b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxHeight();
                    }
                });
    }

}