package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class QueryTableTest extends ActiveXDispatchableTestBase {

    private QueryTable component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new QueryTable(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(810), new Variant(282))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(810), new Variant(282));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(703))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(703));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(989))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(989));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(347), new Variant(797), new
                Variant(42L), new Variant(42L), new Variant(178))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(347), new Variant(797), 42L, 42L, new Variant(178));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(715), new
                Variant(42L), new Variant(42), new Variant(193), new Variant(609), new Variant(38), new Variant(928))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(715), 42L, 42, new Variant(193), new Variant(609), new
                                Variant(38), new Variant(928));
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
        on(0x6e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("AYWoCruxbj"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxName("AYWoCruxbj");
                    }
                });
    }

    @Test
    public void test_getAxFieldNames_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x630).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxFieldNames();
                    }
                });
    }

    @Test
    public void test_setAxFieldNames_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x630).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxFieldNames(false);
                    }
                });
    }

    @Test
    public void test_getAxRowNumbers_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x631).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxRowNumbers();
                    }
                });
    }

    @Test
    public void test_setAxRowNumbers_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x631).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxRowNumbers(false);
                    }
                });
    }

    @Test
    public void test_getAxFillAdjacentFormulas_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x632).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxFillAdjacentFormulas();
                    }
                });
    }

    @Test
    public void test_setAxFillAdjacentFormulas_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x632).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxFillAdjacentFormulas(false);
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
    public void test_getAxRefreshing_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x633).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxRefreshing();
                    }
                });
    }

    @Test
    public void test_getAxFetchedRowOverflow_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x634).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxFetchedRowOverflow();
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
    public void test_CancelRefresh_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x635).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CancelRefresh();
                    }
                });
    }

    @Test
    public void test_getAxRefreshStyle_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x636).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxRefreshStyle();
                    }
                });
    }

    @Test
    public void test_setAxRefreshStyle_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x636).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxRefreshStyle(42);
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
    public void test_getAxDestination_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2a9).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxDestination();
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
        on(0x598).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(28))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxConnection(new Variant(28));
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
        on(0x5c8).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(565))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSql(new Variant(565));
                    }
                });
    }

    @Test
    public void test_getAxPostText_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x637).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxPostText();
                    }
                });
    }

    @Test
    public void test_setAxPostText_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x637).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("AvkgCOxuMG"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPostText("AvkgCOxuMG");
                    }
                });
    }

    @Test
    public void test_getAxResultRange_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x638).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxResultRange();
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
    public void test_Refresh_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x589).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Refresh();
                    }
                });
    }

    @Test
    public void test_Refresh_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x589).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(434))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Refresh(new Variant(434));
                    }
                });
    }

    @Test
    public void test_getAxParameters_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x639).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Parameters>() {
                    @Override
                    public Parameters invoke() throws ActiveXException {
                        return component.getAxParameters();
                    }
                });
    }

    @Test
    public void test_getAxRecordset_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x48d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxRecordset();
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
    public void test_getAxTablesOnlyFromHTML_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x63a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxTablesOnlyFromHTML();
                    }
                });
    }

    @Test
    public void test_setAxTablesOnlyFromHTML_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x63a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxTablesOnlyFromHTML(false);
                    }
                });
    }

    @Test
    public void test_getAxEnableEditing_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x63b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxEnableEditing();
                    }
                });
    }

    @Test
    public void test_setAxEnableEditing_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x63b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxEnableEditing(false);
                    }
                });
    }

}