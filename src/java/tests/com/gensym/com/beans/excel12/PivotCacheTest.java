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

public class PivotCacheTest extends ActiveXDispatchableTestBase {

    private PivotCache component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new PivotCache(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(979), new Variant(357))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(979), new Variant(357));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(983))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(983));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(321))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(321));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(218), new Variant(533), new
                Variant(42L), new Variant(42L), new Variant(199))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(218), new Variant(533), 42L, 42L, new Variant(199));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(869), new
                Variant(42L), new Variant(42), new Variant(595), new Variant(773), new Variant(286), new Variant(895))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(869), 42L, 42, new Variant(595), new Variant(773), new
                                Variant(286), new Variant(895));
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
    public void test_getAxBackgroundQuery_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x593).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxBackgroundQuery();
                    }
                });
    }

    @Test
    public void test_setAxBackgroundQuery_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x593).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxBackgroundQuery(false);
                    }
                });
    }

    @Test
    public void test_getAxConnection_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x598).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxConnection();
                    }
                });
    }

    @Test
    public void test_setAxConnection_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x598).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(76))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxConnection(new Variant(76));
                    }
                });
    }

    @Test
    public void test_getAxEnableRefresh_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5c5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxEnableRefresh();
                    }
                });
    }

    @Test
    public void test_setAxEnableRefresh_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5c5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxEnableRefresh(false);
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
    public void test_getAxOptimizeCache_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x594).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxOptimizeCache();
                    }
                });
    }

    @Test
    public void test_setAxOptimizeCache_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x594).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOptimizeCache(false);
                    }
                });
    }

    @Test
    public void test_getAxRecordCount_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5c6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxRecordCount();
                    }
                });
    }

    @Test
    public void test_Refresh_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x589).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Refresh();
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
    public void test_getAxRefreshOnFileOpen_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5c7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxRefreshOnFileOpen();
                    }
                });
    }

    @Test
    public void test_setAxRefreshOnFileOpen_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5c7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxRefreshOnFileOpen(false);
                    }
                });
    }

    @Test
    public void test_getAxSql_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5c8).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxSql();
                    }
                });
    }

    @Test
    public void test_setAxSql_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5c8).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(463))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSql(new Variant(463));
                    }
                });
    }

    @Test
    public void test_getAxSavePassword_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5c9).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxSavePassword();
                    }
                });
    }

    @Test
    public void test_setAxSavePassword_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5c9).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSavePassword(false);
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
        on(0x2ae).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(17))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSourceData(new Variant(17));
                    }
                });
    }

}