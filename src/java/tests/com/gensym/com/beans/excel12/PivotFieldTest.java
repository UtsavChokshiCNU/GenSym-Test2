package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class PivotFieldTest extends ActiveXDispatchableTestBase {

    private PivotField component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new PivotField(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(265), new Variant(70))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(265), new Variant(70));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(541))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(541));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(421))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(421));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(586), new Variant(870), new
                Variant(42L), new Variant(42L), new Variant(123))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(586), new Variant(870), 42L, 42L, new Variant(123));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(443), new
                Variant(42L), new Variant(42), new Variant(352), new Variant(857), new Variant(704), new Variant(301))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(443), 42L, 42, new Variant(352), new Variant(857), new
                                Variant(704), new Variant(301));
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
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.getAxParent();
                    }
                });
    }

    @Test
    public void test_getAxCalculation_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x13c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxCalculation();
                    }
                });
    }

    @Test
    public void test_setAxCalculation_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x13c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCalculation(42);
                    }
                });
    }

    @Test
    public void test_getAxChildField_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2e0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<PivotField>() {
                    @Override
                    public PivotField invoke() throws ActiveXException {
                        return component.getAxChildField();
                    }
                });
    }

    @Test
    public void test_getAxChildItems_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2da).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxChildItems();
                    }
                });
    }

    @Test
    public void test_getAxChildItems_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2da).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(913))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxChildItems(new Variant(913));
                    }
                });
    }

    @Test
    public void test_getAxCurrentPage_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2e2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxCurrentPage();
                    }
                });
    }

    @Test
    public void test_setAxCurrentPage_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2e2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("BbpIplVSsa"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCurrentPage("BbpIplVSsa");
                    }
                });
    }

    @Test
    public void test_getAxDataRange_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2d0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxDataRange();
                    }
                });
    }

    @Test
    public void test_getAxDataType_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2d2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxDataType();
                    }
                });
    }

    @Test
    public void test_getAx_Default_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAx_Default();
                    }
                });
    }

    @Test
    public void test_setAx_Default_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("AzJJbsouhY"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAx_Default("AzJJbsouhY");
                    }
                });
    }

    @Test
    public void test_getAxFunction_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x383).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxFunction();
                    }
                });
    }

    @Test
    public void test_setAxFunction_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x383).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxFunction(42);
                    }
                });
    }

    @Test
    public void test_getAxGroupLevel_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2d3).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxGroupLevel();
                    }
                });
    }

    @Test
    public void test_getAxHiddenItems_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2d8).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxHiddenItems();
                    }
                });
    }

    @Test
    public void test_getAxHiddenItems_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2d8).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(18))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxHiddenItems(new Variant(18));
                    }
                });
    }

    @Test
    public void test_getAxLabelRange_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2cf).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxLabelRange();
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
        on(0x6e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("vHLVnxkAZf"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxName("vHLVnxkAZf");
                    }
                });
    }

    @Test
    public void test_getAxNumberFormat_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxNumberFormat();
                    }
                });
    }

    @Test
    public void test_setAxNumberFormat_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xc1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("lUmbiuWqkv"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxNumberFormat("lUmbiuWqkv");
                    }
                });
    }

    @Test
    public void test_getAxOrientation_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x86).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxOrientation();
                    }
                });
    }

    @Test
    public void test_setAxOrientation_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x86).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOrientation(42);
                    }
                });
    }

    @Test
    public void test_getAxShowAllItems_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1c4).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxShowAllItems();
                    }
                });
    }

    @Test
    public void test_setAxShowAllItems_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x1c4).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxShowAllItems(false);
                    }
                });
    }

    @Test
    public void test_getAxParentField_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2dc).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<PivotField>() {
                    @Override
                    public PivotField invoke() throws ActiveXException {
                        return component.getAxParentField();
                    }
                });
    }

    @Test
    public void test_getAxParentItems_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2d9).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxParentItems();
                    }
                });
    }

    @Test
    public void test_getAxParentItems_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2d9).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(331))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxParentItems(new Variant(331));
                    }
                });
    }

    @Test
    public void test_PivotItems_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2e1).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.PivotItems();
                    }
                });
    }

    @Test
    public void test_PivotItems_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2e1).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(600))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.PivotItems(new Variant(600));
                    }
                });
    }

    @Test
    public void test_getAxPosition_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x85).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxPosition();
                    }
                });
    }

    @Test
    public void test_setAxPosition_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x85).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(254))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPosition(new Variant(254));
                    }
                });
    }

    @Test
    public void test_getAxSourceName_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2d1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxSourceName();
                    }
                });
    }

    @Test
    public void test_Subtotals_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2dd).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Subtotals();
                    }
                });
    }

    @Test
    public void test_Subtotals_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2dd).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(408))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Subtotals(new Variant(408));
                    }
                });
    }

    @Test
    public void test_getAxBaseField_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2de).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxBaseField();
                    }
                });
    }

    @Test
    public void test_setAxBaseField_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2de).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(142))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxBaseField(new Variant(142));
                    }
                });
    }

    @Test
    public void test_getAxBaseItem_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2df).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxBaseItem();
                    }
                });
    }

    @Test
    public void test_setAxBaseItem_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2df).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(804))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxBaseItem(new Variant(804));
                    }
                });
    }

    @Test
    public void test_getAxTotalLevels_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2d4).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxTotalLevels();
                    }
                });
    }

    @Test
    public void test_getAxValue_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxValue();
                    }
                });
    }

    @Test
    public void test_setAxValue_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("sTejznJoxJ"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxValue("sTejznJoxJ");
                    }
                });
    }

    @Test
    public void test_getAxVisibleItems_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2d7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxVisibleItems();
                    }
                });
    }

    @Test
    public void test_getAxVisibleItems_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2d7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(663))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxVisibleItems(new Variant(663));
                    }
                });
    }

    @Test
    public void test_CalculatedItems_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5e3).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchable(new Returns<CalculatedItems>() {
                    @Override
                    public CalculatedItems invoke() throws ActiveXException {
                        return component.CalculatedItems();
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
    public void test_getAxDragToColumn_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5e4).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxDragToColumn();
                    }
                });
    }

    @Test
    public void test_setAxDragToColumn_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5e4).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDragToColumn(false);
                    }
                });
    }

    @Test
    public void test_getAxDragToHide_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5e5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxDragToHide();
                    }
                });
    }

    @Test
    public void test_setAxDragToHide_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5e5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDragToHide(false);
                    }
                });
    }

    @Test
    public void test_getAxDragToPage_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5e6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxDragToPage();
                    }
                });
    }

    @Test
    public void test_setAxDragToPage_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5e6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDragToPage(false);
                    }
                });
    }

    @Test
    public void test_getAxDragToRow_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5e7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxDragToRow();
                    }
                });
    }

    @Test
    public void test_setAxDragToRow_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5e7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDragToRow(false);
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
        on(0x105).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("MBBLGQsCOb"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxFormula("MBBLGQsCOb");
                    }
                });
    }

    @Test
    public void test_getAxIsCalculated_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5e8).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxIsCalculated();
                    }
                });
    }

    @Test
    public void test_getAxMemoryUsed_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x174).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxMemoryUsed();
                    }
                });
    }

    @Test
    public void test_getAxServerBased_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5e9).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxServerBased();
                    }
                });
    }

    @Test
    public void test_setAxServerBased_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5e9).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxServerBased(false);
                    }
                });
    }

    @Test
    public void test_AutoSort_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5ea).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant("IUsKjAkkmm"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AutoSort(42, "IUsKjAkkmm");
                    }
                });
    }

    @Test
    public void test_AutoShow_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5eb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42), new Variant
                (42), new Variant("HkxTaFFcmh"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AutoShow(42, 42, 42, "HkxTaFFcmh");
                    }
                });
    }

    @Test
    public void test_getAxAutoSortOrder_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5ec).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxAutoSortOrder();
                    }
                });
    }

    @Test
    public void test_getAxAutoSortField_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5ed).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxAutoSortField();
                    }
                });
    }

    @Test
    public void test_getAxAutoShowType_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5ee).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxAutoShowType();
                    }
                });
    }

    @Test
    public void test_getAxAutoShowRange_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5ef).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxAutoShowRange();
                    }
                });
    }

    @Test
    public void test_getAxAutoShowCount_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5f0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxAutoShowCount();
                    }
                });
    }

    @Test
    public void test_getAxAutoShowField_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5f1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxAutoShowField();
                    }
                });
    }

}