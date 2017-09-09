package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

import java.util.Date;

public class PivotTableTest extends ActiveXDispatchableTestBase {

    private PivotTable component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new PivotTable(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(125), new Variant(412))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(125), new Variant(412));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(181))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(181));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(844))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(844));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(704), new Variant(938), new
                Variant(42L), new Variant(42L), new Variant(335))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(704), new Variant(938), 42L, 42L, new Variant(335));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(566), new
                Variant(42L), new Variant(42), new Variant(588), new Variant(86), new Variant(33), new Variant(817))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(566), 42L, 42, new Variant(588), new Variant(86), new
                                Variant(33), new Variant(817));
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
    public void test_AddFields_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2c4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AddFields();
                    }
                });
    }

    @Test
    public void test_AddFields_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2c4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(121))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AddFields(new Variant(121));
                    }
                });
    }

    @Test
    public void test_AddFields_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2c4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(665), new Variant(645))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AddFields(new Variant(665), new Variant(645));
                    }
                });
    }

    @Test
    public void test_AddFields_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2c4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(561), new Variant(839), new
                Variant(305))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AddFields(new Variant(561), new Variant(839), new Variant(305));
                    }
                });
    }

    @Test
    public void test_AddFields_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2c4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(722), new Variant(672), new
                Variant(5), new Variant(40))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AddFields(new Variant(722), new Variant(672), new Variant(5), new Variant(40));
                    }
                });
    }

    @Test
    public void test_getAxColumnFields_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2c9).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxColumnFields();
                    }
                });
    }

    @Test
    public void test_getAxColumnFields_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2c9).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(591))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxColumnFields(new Variant(591));
                    }
                });
    }

    @Test
    public void test_getAxColumnGrand_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2b6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxColumnGrand();
                    }
                });
    }

    @Test
    public void test_setAxColumnGrand_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2b6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxColumnGrand(false);
                    }
                });
    }

    @Test
    public void test_getAxColumnRange_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2be).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxColumnRange();
                    }
                });
    }

    @Test
    public void test_ShowPages_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2c2).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ShowPages();
                    }
                });
    }

    @Test
    public void test_ShowPages_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2c2).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(732))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ShowPages(new Variant(732));
                    }
                });
    }

    @Test
    public void test_getAxDataBodyRange_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2c1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxDataBodyRange();
                    }
                });
    }

    @Test
    public void test_getAxDataFields_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2cb).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxDataFields();
                    }
                });
    }

    @Test
    public void test_getAxDataFields_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2cb).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(131))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxDataFields(new Variant(131));
                    }
                });
    }

    @Test
    public void test_getAxDataLabelRange_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2c0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxDataLabelRange();
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
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("PcvWRiQTem"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAx_Default("PcvWRiQTem");
                    }
                });
    }

    @Test
    public void test_getAxHasAutoFormat_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2b7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxHasAutoFormat();
                    }
                });
    }

    @Test
    public void test_setAxHasAutoFormat_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2b7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHasAutoFormat(false);
                    }
                });
    }

    @Test
    public void test_getAxHiddenFields_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2c7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxHiddenFields();
                    }
                });
    }

    @Test
    public void test_getAxHiddenFields_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2c7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(879))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxHiddenFields(new Variant(879));
                    }
                });
    }

    @Test
    public void test_getAxInnerDetail_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ba).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxInnerDetail();
                    }
                });
    }

    @Test
    public void test_setAxInnerDetail_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2ba).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("DGpcfwkAsQ"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxInnerDetail("DGpcfwkAsQ");
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
        on(0x6e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("KbvWZZysXp"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxName("KbvWZZysXp");
                    }
                });
    }

    @Test
    public void test_getAxPageFields_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ca).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxPageFields();
                    }
                });
    }

    @Test
    public void test_getAxPageFields_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2ca).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(1))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxPageFields(new Variant(1));
                    }
                });
    }

    @Test
    public void test_getAxPageRange_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2bf).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxPageRange();
                    }
                });
    }

    @Test
    public void test_getAxPageRangeCells_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5ca).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxPageRangeCells();
                    }
                });
    }

    @Test
    public void test_PivotFields_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ce).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.PivotFields();
                    }
                });
    }

    @Test
    public void test_PivotFields_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2ce).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(143))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.PivotFields(new Variant(143));
                    }
                });
    }

    @Test
    public void test_getAxRefreshDate_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2b8).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDate(new Returns<Date>() {
                    @Override
                    public Date invoke() throws ActiveXException {
                        return component.getAxRefreshDate();
                    }
                });
    }

    @Test
    public void test_getAxRefreshName_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2b9).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxRefreshName();
                    }
                });
    }

    @Test
    public void test_RefreshTable_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2cd).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.RefreshTable();
                    }
                });
    }

    @Test
    public void test_getAxRowFields_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2c8).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxRowFields();
                    }
                });
    }

    @Test
    public void test_getAxRowFields_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2c8).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(856))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxRowFields(new Variant(856));
                    }
                });
    }

    @Test
    public void test_getAxRowGrand_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2b5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxRowGrand();
                    }
                });
    }

    @Test
    public void test_setAxRowGrand_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2b5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxRowGrand(false);
                    }
                });
    }

    @Test
    public void test_getAxRowRange_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2bd).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxRowRange();
                    }
                });
    }

    @Test
    public void test_getAxSaveData_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2b4).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxSaveData();
                    }
                });
    }

    @Test
    public void test_setAxSaveData_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2b4).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSaveData(false);
                    }
                });
    }

    @Test
    public void test_getAxSourceData_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ae).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxSourceData();
                    }
                });
    }

    @Test
    public void test_setAxSourceData_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2ae).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(439))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSourceData(new Variant(439));
                    }
                });
    }

    @Test
    public void test_getAxTableRange1_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2bb).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxTableRange1();
                    }
                });
    }

    @Test
    public void test_getAxTableRange2_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2bc).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxTableRange2();
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
        on(0x6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("xOcEqHvUOr"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxValue("xOcEqHvUOr");
                    }
                });
    }

    @Test
    public void test_getAxVisibleFields_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2c6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxVisibleFields();
                    }
                });
    }

    @Test
    public void test_getAxVisibleFields_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2c6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(665))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxVisibleFields(new Variant(665));
                    }
                });
    }

    @Test
    public void test_getAxCacheIndex_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5cb).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxCacheIndex();
                    }
                });
    }

    @Test
    public void test_setAxCacheIndex_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5cb).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCacheIndex(42);
                    }
                });
    }

    @Test
    public void test_CalculatedFields_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5cc).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchable(new Returns<CalculatedFields>() {
                    @Override
                    public CalculatedFields invoke() throws ActiveXException {
                        return component.CalculatedFields();
                    }
                });
    }

    @Test
    public void test_getAxDisplayErrorString_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5cd).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxDisplayErrorString();
                    }
                });
    }

    @Test
    public void test_setAxDisplayErrorString_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5cd).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDisplayErrorString(false);
                    }
                });
    }

    @Test
    public void test_getAxDisplayNullString_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5ce).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxDisplayNullString();
                    }
                });
    }

    @Test
    public void test_setAxDisplayNullString_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5ce).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDisplayNullString(false);
                    }
                });
    }

    @Test
    public void test_getAxEnableDrilldown_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5cf).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxEnableDrilldown();
                    }
                });
    }

    @Test
    public void test_setAxEnableDrilldown_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5cf).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxEnableDrilldown(false);
                    }
                });
    }

    @Test
    public void test_getAxEnableFieldDialog_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5d0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxEnableFieldDialog();
                    }
                });
    }

    @Test
    public void test_setAxEnableFieldDialog_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5d0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxEnableFieldDialog(false);
                    }
                });
    }

    @Test
    public void test_getAxEnableWizard_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5d1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxEnableWizard();
                    }
                });
    }

    @Test
    public void test_setAxEnableWizard_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5d1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxEnableWizard(false);
                    }
                });
    }

    @Test
    public void test_getAxErrorString_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5d2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxErrorString();
                    }
                });
    }

    @Test
    public void test_setAxErrorString_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5d2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("WwdyDkTbfc"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxErrorString("WwdyDkTbfc");
                    }
                });
    }

    @Test
    public void test_GetData_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5d3).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("uIfyIaXFUC"))
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.GetData("uIfyIaXFUC");
                    }
                });
    }

    @Test
    public void test_ListFormulas_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5d4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ListFormulas();
                    }
                });
    }

    @Test
    public void test_getAxManualUpdate_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5d5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxManualUpdate();
                    }
                });
    }

    @Test
    public void test_setAxManualUpdate_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5d5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxManualUpdate(false);
                    }
                });
    }

    @Test
    public void test_getAxMergeLabels_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5d6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxMergeLabels();
                    }
                });
    }

    @Test
    public void test_setAxMergeLabels_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5d6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMergeLabels(false);
                    }
                });
    }

    @Test
    public void test_getAxNullString_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5d7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxNullString();
                    }
                });
    }

    @Test
    public void test_setAxNullString_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5d7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("dbYSXrPHUf"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxNullString("dbYSXrPHUf");
                    }
                });
    }

    @Test
    public void test_PivotCache_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5d8).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchable(new Returns<PivotCache>() {
                    @Override
                    public PivotCache invoke() throws ActiveXException {
                        return component.PivotCache();
                    }
                });
    }

    @Test
    public void test_PivotFormulas_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5d9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchable(new Returns<PivotFormulas>() {
                    @Override
                    public PivotFormulas invoke() throws ActiveXException {
                        return component.PivotFormulas();
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotTableWizard();
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(560))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotTableWizard(new Variant(560));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(209), new Variant(456))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotTableWizard(new Variant(209), new Variant(456));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(621), new Variant(167), new
                Variant(631))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotTableWizard(new Variant(621), new Variant(167), new Variant(631));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(66), new Variant(993), new Variant
                (61), new Variant(683))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotTableWizard(new Variant(66), new Variant(993), new Variant(61), new Variant
                                (683));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(601), new Variant(250), new
                Variant(201), new Variant(481), new Variant(278))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotTableWizard(new Variant(601), new Variant(250), new Variant(201), new Variant
                                (481), new Variant(278));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(143), new Variant(936), new
                Variant(919), new Variant(439), new Variant(588), new Variant(988))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotTableWizard(new Variant(143), new Variant(936), new Variant(919), new Variant
                                (439), new Variant(588), new Variant(988));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(696), new Variant(641), new
                Variant(708), new Variant(45), new Variant(921), new Variant(308), new Variant(394))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotTableWizard(new Variant(696), new Variant(641), new Variant(708), new Variant
                                (45), new Variant(921), new Variant(308), new Variant(394));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(973), new Variant(750), new
                Variant(797), new Variant(484), new Variant(836), new Variant(578), new Variant(33), new Variant(677))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotTableWizard(new Variant(973), new Variant(750), new Variant(797), new Variant
                                (484), new Variant(836), new Variant(578), new Variant(33), new Variant(677));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(756), new Variant(818), new
                Variant(508), new Variant(766), new Variant(327), new Variant(653), new Variant(946), new Variant
                (832), new Variant(61))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotTableWizard(new Variant(756), new Variant(818), new Variant(508), new Variant
                                (766), new Variant(327), new Variant(653), new Variant(946), new Variant(832), new
                                Variant(61));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_TenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(371), new Variant(973), new
                Variant(936), new Variant(58), new Variant(582), new Variant(989), new Variant(767), new Variant(476)
                , new Variant(521), new Variant(485))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotTableWizard(new Variant(371), new Variant(973), new Variant(936), new Variant
                                (58), new Variant(582), new Variant(989), new Variant(767), new Variant(476), new
                                Variant(521), new Variant(485));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_ElevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(917), new Variant(978), new
                Variant(619), new Variant(498), new Variant(570), new Variant(215), new Variant(152), new Variant
                (455), new Variant(273), new Variant(566), new Variant(605))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotTableWizard(new Variant(917), new Variant(978), new Variant(619), new Variant
                                (498), new Variant(570), new Variant(215), new Variant(152), new Variant(455), new
                                Variant(273), new Variant(566), new Variant(605));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_TwelveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(291), new Variant(705), new
                Variant(560), new Variant(949), new Variant(156), new Variant(96), new Variant(441), new Variant(997)
                , new Variant(429), new Variant(158), new Variant(952), new Variant(409))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotTableWizard(new Variant(291), new Variant(705), new Variant(560), new Variant
                                (949), new Variant(156), new Variant(96), new Variant(441), new Variant(997), new
                                Variant(429), new Variant(158), new Variant(952), new Variant(409));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_ThirteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(987), new Variant(484), new
                Variant(573), new Variant(137), new Variant(141), new Variant(352), new Variant(205), new Variant
                (643), new Variant(546), new Variant(862), new Variant(376), new Variant(246), new Variant(196))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotTableWizard(new Variant(987), new Variant(484), new Variant(573), new Variant
                                (137), new Variant(141), new Variant(352), new Variant(205), new Variant(643), new
                                Variant(546), new Variant(862), new Variant(376), new Variant(246), new Variant(196));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_FourteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(668), new Variant(876), new
                Variant(192), new Variant(82), new Variant(154), new Variant(562), new Variant(325), new Variant(475)
                , new Variant(156), new Variant(350), new Variant(268), new Variant(398), new Variant(989), new
                        Variant(29))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotTableWizard(new Variant(668), new Variant(876), new Variant(192), new Variant
                                (82), new Variant(154), new Variant(562), new Variant(325), new Variant(475), new
                                Variant(156), new Variant(350), new Variant(268), new Variant(398), new Variant(989),
                                new Variant(29));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_FifteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(0), new Variant(831), new Variant
                (770), new Variant(607), new Variant(496), new Variant(708), new Variant(640), new Variant(227), new
                Variant(27), new Variant(445), new Variant(578), new Variant(762), new Variant(324), new Variant(826)
                , new Variant(924))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotTableWizard(new Variant(0), new Variant(831), new Variant(770), new Variant
                                (607), new Variant(496), new Variant(708), new Variant(640), new Variant(227), new
                                Variant(27), new Variant(445), new Variant(578), new Variant(762), new Variant(324),
                                new Variant(826), new Variant(924));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_SixteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(227), new Variant(29), new Variant
                (814), new Variant(389), new Variant(646), new Variant(19), new Variant(993), new Variant(508), new
                Variant(876), new Variant(6), new Variant(956), new Variant(91), new Variant(955), new Variant(923),
                new Variant(781), new Variant(232))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotTableWizard(new Variant(227), new Variant(29), new Variant(814), new Variant
                                (389), new Variant(646), new Variant(19), new Variant(993), new Variant(508), new
                                Variant(876), new Variant(6), new Variant(956), new Variant(91), new Variant(955),
                                new Variant(923), new Variant(781), new Variant(232));
                    }
                });
    }

    @Test
    public void test_getAxSubtotalHiddenPageItems_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5da).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxSubtotalHiddenPageItems();
                    }
                });
    }

    @Test
    public void test_setAxSubtotalHiddenPageItems_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5da).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSubtotalHiddenPageItems(false);
                    }
                });
    }

    @Test
    public void test_getAxPageFieldOrder_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x595).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxPageFieldOrder();
                    }
                });
    }

    @Test
    public void test_setAxPageFieldOrder_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x595).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPageFieldOrder(42);
                    }
                });
    }

    @Test
    public void test_getAxPageFieldStyle_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5db).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxPageFieldStyle();
                    }
                });
    }

    @Test
    public void test_setAxPageFieldStyle_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5db).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("QecqnBBbWQ"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPageFieldStyle("QecqnBBbWQ");
                    }
                });
    }

    @Test
    public void test_getAxPageFieldWrapCount_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x596).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxPageFieldWrapCount();
                    }
                });
    }

    @Test
    public void test_setAxPageFieldWrapCount_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x596).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPageFieldWrapCount(42);
                    }
                });
    }

    @Test
    public void test_getAxPreserveFormatting_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5dc).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxPreserveFormatting();
                    }
                });
    }

    @Test
    public void test_setAxPreserveFormatting_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5dc).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPreserveFormatting(false);
                    }
                });
    }

    @Test
    public void test_PivotSelect_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5dd).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("MXdCDeGbLa"), new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotSelect("MXdCDeGbLa", 42);
                    }
                });
    }

    @Test
    public void test_getAxPivotSelection_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5de).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxPivotSelection();
                    }
                });
    }

    @Test
    public void test_setAxPivotSelection_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5de).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("MaGVlQnlPd"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPivotSelection("MaGVlQnlPd");
                    }
                });
    }

    @Test
    public void test_getAxSelectionMode_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5df).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxSelectionMode();
                    }
                });
    }

    @Test
    public void test_setAxSelectionMode_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5df).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSelectionMode(42);
                    }
                });
    }

    @Test
    public void test_getAxTableStyle_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5e0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxTableStyle();
                    }
                });
    }

    @Test
    public void test_setAxTableStyle_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5e0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("jmpmOtyhHl"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxTableStyle("jmpmOtyhHl");
                    }
                });
    }

    @Test
    public void test_getAxTag_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5e1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxTag();
                    }
                });
    }

    @Test
    public void test_setAxTag_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5e1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("PovHouZiIs"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxTag("PovHouZiIs");
                    }
                });
    }

    @Test
    public void test_Update_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2a8).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Update();
                    }
                });
    }

    @Test
    public void test_getAxVacatedStyle_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5e2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxVacatedStyle();
                    }
                });
    }

    @Test
    public void test_setAxVacatedStyle_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5e2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("hbkHmaeBKL"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxVacatedStyle("hbkHmaeBKL");
                    }
                });
    }

}