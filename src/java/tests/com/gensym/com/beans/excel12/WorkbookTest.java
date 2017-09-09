package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import com.gensym.com.beans.office20.CommandBars;
import org.junit.Before;
import org.junit.Test;

public class WorkbookTest extends ActiveXDispatchableTestBase {

    private Workbook component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new Workbook(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(579), new Variant(792))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(579), new Variant(792));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(780))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(780));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(249))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(249));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(138), new Variant(848), new
                Variant(42L), new Variant(42L), new Variant(335))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(138), new Variant(848), 42L, 42L, new Variant(335));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(267), new
                Variant(42L), new Variant(42), new Variant(345), new Variant(703), new Variant(811), new Variant(622))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(267), 42L, 42, new Variant(345), new Variant(703), new
                                Variant(811), new Variant(622));
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
    public void test_getAxAcceptLabelsInFormulas_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5a1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxAcceptLabelsInFormulas();
                    }
                });
    }

    @Test
    public void test_setAxAcceptLabelsInFormulas_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5a1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxAcceptLabelsInFormulas(false);
                    }
                });
    }

    @Test
    public void test_Activate_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x130).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Activate();
                    }
                });
    }

    @Test
    public void test_getAxActiveChart_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<ExcelChart>() {
                    @Override
                    public ExcelChart invoke() throws ActiveXException {
                        return component.getAxActiveChart();
                    }
                });
    }

    @Test
    public void test_getAxActiveSheet_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x133).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxActiveSheet();
                    }
                });
    }

    @Test
    public void test_getAxAuthor_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x23e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxAuthor();
                    }
                });
    }

    @Test
    public void test_setAxAuthor_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x23e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("jsRNElQime"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxAuthor("jsRNElQime");
                    }
                });
    }

    @Test
    public void test_getAxAutoUpdateFrequency_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5a2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxAutoUpdateFrequency();
                    }
                });
    }

    @Test
    public void test_setAxAutoUpdateFrequency_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5a2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxAutoUpdateFrequency(42);
                    }
                });
    }

    @Test
    public void test_getAxAutoUpdateSaveChanges_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5a3).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxAutoUpdateSaveChanges();
                    }
                });
    }

    @Test
    public void test_setAxAutoUpdateSaveChanges_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5a3).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxAutoUpdateSaveChanges(false);
                    }
                });
    }

    @Test
    public void test_getAxChangeHistoryDuration_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5a4).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxChangeHistoryDuration();
                    }
                });
    }

    @Test
    public void test_setAxChangeHistoryDuration_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5a4).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxChangeHistoryDuration(42);
                    }
                });
    }

    @Test
    public void test_getAxBuiltinDocumentProperties_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x498).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxBuiltinDocumentProperties();
                    }
                });
    }

    @Test
    public void test_ChangeFileAccess_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3dd).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ChangeFileAccess(42);
                    }
                });
    }

    @Test
    public void test_ChangeFileAccess_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3dd).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(867))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ChangeFileAccess(42, new Variant(867));
                    }
                });
    }

    @Test
    public void test_ChangeFileAccess_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3dd).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(227), new Variant
                (0))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ChangeFileAccess(42, new Variant(227), new Variant(0));
                    }
                });
    }

    @Test
    public void test_ChangeLink_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x322).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("TgbgHofDhg"), new Variant
                ("RRbWYOzxCm"), new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ChangeLink("TgbgHofDhg", "RRbWYOzxCm", 42);
                    }
                });
    }

    @Test
    public void test_getAxCharts_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x79).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Sheets>() {
                    @Override
                    public Sheets invoke() throws ActiveXException {
                        return component.getAxCharts();
                    }
                });
    }

    @Test
    public void test_Close_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x115).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Close();
                    }
                });
    }

    @Test
    public void test_Close_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x115).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(66))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Close(new Variant(66));
                    }
                });
    }

    @Test
    public void test_Close_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x115).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(385), new Variant(465))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Close(new Variant(385), new Variant(465));
                    }
                });
    }

    @Test
    public void test_Close_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x115).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(76), new Variant(609), new Variant
                (527))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Close(new Variant(76), new Variant(609), new Variant(527));
                    }
                });
    }

    @Test
    public void test_getAxCodeName_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x55d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxCodeName();
                    }
                });
    }

    @Test
    public void test_getAx_CodeName_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x80010000).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAx_CodeName();
                    }
                });
    }

    @Test
    public void test_setAx_CodeName_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x80010000).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("rCbuIDjjDg"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAx_CodeName("rCbuIDjjDg");
                    }
                });
    }

    @Test
    public void test_getAxColors_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxColors();
                    }
                });
    }

    @Test
    public void test_getAxColors_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x11e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(416))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxColors(new Variant(416));
                    }
                });
    }

    @Test
    public void test_setAxColors_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x11e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(706))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxColors(new Variant(706));
                    }
                });
    }

    @Test
    public void test_setAxColors_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(919), new Variant(163))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxColors(new Variant(919), new Variant(163));
                    }
                });
    }

    @Test
    public void test_getAxCommandBars_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x59f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<CommandBars>() {
                    @Override
                    public CommandBars invoke() throws ActiveXException {
                        return component.getAxCommandBars();
                    }
                });
    }

    @Test
    public void test_getAxComments_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x23f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxComments();
                    }
                });
    }

    @Test
    public void test_setAxComments_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x23f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("DcHObkHCJJ"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxComments("DcHObkHCJJ");
                    }
                });
    }

    @Test
    public void test_getAxConflictResolution_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x497).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxConflictResolution();
                    }
                });
    }

    @Test
    public void test_setAxConflictResolution_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x497).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxConflictResolution(42);
                    }
                });
    }

    @Test
    public void test_getAxContainer_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x4a6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxContainer();
                    }
                });
    }

    @Test
    public void test_getAxCreateBackup_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxCreateBackup();
                    }
                });
    }

    @Test
    public void test_getAxCustomDocumentProperties_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x499).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxCustomDocumentProperties();
                    }
                });
    }

    @Test
    public void test_getAxDate1904_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x193).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxDate1904();
                    }
                });
    }

    @Test
    public void test_setAxDate1904_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x193).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDate1904(false);
                    }
                });
    }

    @Test
    public void test_DeleteNumberFormat_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x18d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("rmxmeDAJft"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.DeleteNumberFormat("rmxmeDAJft");
                    }
                });
    }

    @Test
    public void test_getAxDialogSheets_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fc).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Sheets>() {
                    @Override
                    public Sheets invoke() throws ActiveXException {
                        return component.getAxDialogSheets();
                    }
                });
    }

    @Test
    public void test_getAxDisplayDrawingObjects_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x194).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxDisplayDrawingObjects();
                    }
                });
    }

    @Test
    public void test_setAxDisplayDrawingObjects_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x194).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDisplayDrawingObjects(42);
                    }
                });
    }

    @Test
    public void test_ExclusiveAccess_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x490).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.ExclusiveAccess();
                    }
                });
    }

    @Test
    public void test_getAxFileFormat_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x120).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxFileFormat();
                    }
                });
    }

    @Test
    public void test_ForwardMailer_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3cd).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ForwardMailer();
                    }
                });
    }

    @Test
    public void test_getAxFullName_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x121).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxFullName();
                    }
                });
    }

    @Test
    public void test_getAxHasMailer_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3d0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxHasMailer();
                    }
                });
    }

    @Test
    public void test_setAxHasMailer_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3d0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHasMailer(false);
                    }
                });
    }

    @Test
    public void test_getAxHasPassword_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x122).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxHasPassword();
                    }
                });
    }

    @Test
    public void test_getAxHasRoutingSlip_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3b6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxHasRoutingSlip();
                    }
                });
    }

    @Test
    public void test_setAxHasRoutingSlip_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3b6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHasRoutingSlip(false);
                    }
                });
    }

    @Test
    public void test_getAxIsAddin_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5a5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxIsAddin();
                    }
                });
    }

    @Test
    public void test_setAxIsAddin_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5a5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxIsAddin(false);
                    }
                });
    }

    @Test
    public void test_getAxKeywords_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x241).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxKeywords();
                    }
                });
    }

    @Test
    public void test_setAxKeywords_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x241).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("LABUPwgQpw"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxKeywords("LABUPwgQpw");
                    }
                });
    }

    @Test
    public void test_LinkInfo_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x327).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("NIGeYCRIOS"), new Variant(42))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.LinkInfo("NIGeYCRIOS", 42);
                    }
                });
    }

    @Test
    public void test_LinkInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x327).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("LgHiKcTVkr"), new Variant(42),
                new Variant(934))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.LinkInfo("LgHiKcTVkr", 42, new Variant(934));
                    }
                });
    }

    @Test
    public void test_LinkInfo_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x327).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("ooCnSoWLUp"), new Variant(42),
                new Variant(29), new Variant(714))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.LinkInfo("ooCnSoWLUp", 42, new Variant(29), new Variant(714));
                    }
                });
    }

    @Test
    public void test_LinkSources_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x328).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.LinkSources();
                    }
                });
    }

    @Test
    public void test_LinkSources_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x328).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(601))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.LinkSources(new Variant(601));
                    }
                });
    }

    @Test
    public void test_getAxMailer_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3d3).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Mailer>() {
                    @Override
                    public Mailer invoke() throws ActiveXException {
                        return component.getAxMailer();
                    }
                });
    }

    @Test
    public void test_MergeWorkbook_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5a6).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(470))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.MergeWorkbook(new Variant(470));
                    }
                });
    }

    @Test
    public void test_getAxModules_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x246).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Sheets>() {
                    @Override
                    public Sheets invoke() throws ActiveXException {
                        return component.getAxModules();
                    }
                });
    }

    @Test
    public void test_getAxMultiUserEditing_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x491).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxMultiUserEditing();
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
    public void test_getAxNames_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1ba).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Names>() {
                    @Override
                    public Names invoke() throws ActiveXException {
                        return component.getAxNames();
                    }
                });
    }

    @Test
    public void test_NewWindow_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x118).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchable(new Returns<Window>() {
                    @Override
                    public Window invoke() throws ActiveXException {
                        return component.NewWindow();
                    }
                });
    }

    @Test
    public void test_getAxOnSave_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x49a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxOnSave();
                    }
                });
    }

    @Test
    public void test_setAxOnSave_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x49a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("WBnLbmenXY"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnSave("WBnLbmenXY");
                    }
                });
    }

    @Test
    public void test_getAxOnSheetActivate_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x407).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxOnSheetActivate();
                    }
                });
    }

    @Test
    public void test_setAxOnSheetActivate_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x407).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("ZGlESkFAGT"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnSheetActivate("ZGlESkFAGT");
                    }
                });
    }

    @Test
    public void test_getAxOnSheetDeactivate_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x439).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxOnSheetDeactivate();
                    }
                });
    }

    @Test
    public void test_setAxOnSheetDeactivate_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x439).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("HZgZRKdubg"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnSheetDeactivate("HZgZRKdubg");
                    }
                });
    }

    @Test
    public void test_OpenLinks_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x323).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("mEIRDVnOpP"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.OpenLinks("mEIRDVnOpP");
                    }
                });
    }

    @Test
    public void test_OpenLinks_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x323).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("JzJJHCgoIb"), new Variant(670))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.OpenLinks("JzJJHCgoIb", new Variant(670));
                    }
                });
    }

    @Test
    public void test_OpenLinks_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x323).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("GstdiSTzCs"), new Variant(873),
                new Variant(646))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.OpenLinks("GstdiSTzCs", new Variant(873), new Variant(646));
                    }
                });
    }

    @Test
    public void test_getAxPath_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x123).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxPath();
                    }
                });
    }

    @Test
    public void test_getAxPersonalViewListSettings_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5a7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxPersonalViewListSettings();
                    }
                });
    }

    @Test
    public void test_setAxPersonalViewListSettings_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5a7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPersonalViewListSettings(false);
                    }
                });
    }

    @Test
    public void test_getAxPersonalViewPrintSettings_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5a8).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxPersonalViewPrintSettings();
                    }
                });
    }

    @Test
    public void test_setAxPersonalViewPrintSettings_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5a8).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPersonalViewPrintSettings(false);
                    }
                });
    }

    @Test
    public void test_PivotCaches_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5a9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchable(new Returns<PivotCaches>() {
                    @Override
                    public PivotCaches invoke() throws ActiveXException {
                        return component.PivotCaches();
                    }
                });
    }

    @Test
    public void test_Post_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x48e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Post();
                    }
                });
    }

    @Test
    public void test_Post_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x48e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(849))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Post(new Variant(849));
                    }
                });
    }

    @Test
    public void test_getAxPrecisionAsDisplayed_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x195).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxPrecisionAsDisplayed();
                    }
                });
    }

    @Test
    public void test_setAxPrecisionAsDisplayed_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x195).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPrecisionAsDisplayed(false);
                    }
                });
    }

    @Test
    public void test_PrintOut_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut();
                    }
                });
    }

    @Test
    public void test_PrintOut_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(72))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(72));
                    }
                });
    }

    @Test
    public void test_PrintOut_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(169), new Variant(415))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(169), new Variant(415));
                    }
                });
    }

    @Test
    public void test_PrintOut_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(257), new Variant(492), new
                Variant(955))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(257), new Variant(492), new Variant(955));
                    }
                });
    }

    @Test
    public void test_PrintOut_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(76), new Variant(925), new Variant
                (734), new Variant(977))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(76), new Variant(925), new Variant(734), new Variant(977));
                    }
                });
    }

    @Test
    public void test_PrintOut_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(951), new Variant(470), new
                Variant(235), new Variant(743), new Variant(939))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(951), new Variant(470), new Variant(235), new Variant(743),
                                new Variant(939));
                    }
                });
    }

    @Test
    public void test_PrintOut_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(793), new Variant(862), new
                Variant(550), new Variant(619), new Variant(509), new Variant(789))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(793), new Variant(862), new Variant(550), new Variant(619),
                                new Variant(509), new Variant(789));
                    }
                });
    }

    @Test
    public void test_PrintOut_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(547), new Variant(201), new
                Variant(940), new Variant(532), new Variant(623), new Variant(703), new Variant(702))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(547), new Variant(201), new Variant(940), new Variant(532),
                                new Variant(623), new Variant(703), new Variant(702));
                    }
                });
    }

    @Test
    public void test_PrintPreview_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x119).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintPreview();
                    }
                });
    }

    @Test
    public void test_PrintPreview_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x119).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(606))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintPreview(new Variant(606));
                    }
                });
    }

    @Test
    public void test_Protect_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect();
                    }
                });
    }

    @Test
    public void test_Protect_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(271))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect(new Variant(271));
                    }
                });
    }

    @Test
    public void test_Protect_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(461), new Variant(832))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect(new Variant(461), new Variant(832));
                    }
                });
    }

    @Test
    public void test_Protect_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(588), new Variant(268), new
                Variant(287))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect(new Variant(588), new Variant(268), new Variant(287));
                    }
                });
    }

    @Test
    public void test_ProtectSharing_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5aa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ProtectSharing();
                    }
                });
    }

    @Test
    public void test_ProtectSharing_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5aa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(868))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ProtectSharing(new Variant(868));
                    }
                });
    }

    @Test
    public void test_ProtectSharing_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5aa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(524), new Variant(493))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ProtectSharing(new Variant(524), new Variant(493));
                    }
                });
    }

    @Test
    public void test_ProtectSharing_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5aa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(714), new Variant(602), new
                Variant(70))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ProtectSharing(new Variant(714), new Variant(602), new Variant(70));
                    }
                });
    }

    @Test
    public void test_ProtectSharing_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5aa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(280), new Variant(580), new
                Variant(108), new Variant(285))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ProtectSharing(new Variant(280), new Variant(580), new Variant(108), new Variant
                                (285));
                    }
                });
    }

    @Test
    public void test_ProtectSharing_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5aa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(808), new Variant(365), new
                Variant(464), new Variant(41), new Variant(959))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ProtectSharing(new Variant(808), new Variant(365), new Variant(464), new Variant
                                (41), new Variant(959));
                    }
                });
    }

    @Test
    public void test_ProtectSharing_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5aa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(486), new Variant(766), new
                Variant(693), new Variant(269), new Variant(772), new Variant(209))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ProtectSharing(new Variant(486), new Variant(766), new Variant(693), new Variant
                                (269), new Variant(772), new Variant(209));
                    }
                });
    }

    @Test
    public void test_getAxProtectStructure_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x24c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxProtectStructure();
                    }
                });
    }

    @Test
    public void test_getAxProtectWindows_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x127).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxProtectWindows();
                    }
                });
    }

    @Test
    public void test_getAxReadOnly_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x128).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxReadOnly();
                    }
                });
    }

    @Test
    public void test_getAxReadOnlyRecommended_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x129).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxReadOnlyRecommended();
                    }
                });
    }

    @Test
    public void test_RefreshAll_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.RefreshAll();
                    }
                });
    }

    @Test
    public void test_Reply_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3d1).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Reply();
                    }
                });
    }

    @Test
    public void test_ReplyAll_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3d2).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ReplyAll();
                    }
                });
    }

    @Test
    public void test_RemoveUser_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5ad).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.RemoveUser(42);
                    }
                });
    }

    @Test
    public void test_getAxRevisionNumber_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x494).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxRevisionNumber();
                    }
                });
    }

    @Test
    public void test_Route_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3b2).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Route();
                    }
                });
    }

    @Test
    public void test_getAxRouted_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3b7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxRouted();
                    }
                });
    }

    @Test
    public void test_getAxRoutingSlip_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3b5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<RoutingSlip>() {
                    @Override
                    public RoutingSlip invoke() throws ActiveXException {
                        return component.getAxRoutingSlip();
                    }
                });
    }

    @Test
    public void test_RunAutoMacros_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x27a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.RunAutoMacros(42);
                    }
                });
    }

    @Test
    public void test_Save_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Save();
                    }
                });
    }

    @Test
    public void test_SaveAs_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(498), new Variant(337), new
                Variant(704), new Variant(899), new Variant(799), new Variant(332), new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs(new Variant(498), new Variant(337), new Variant(704), new Variant(899), new
                                Variant(799), new Variant(332), 42);
                    }
                });
    }

    @Test
    public void test_SaveAs_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(398), new Variant(704), new
                Variant(811), new Variant(653), new Variant(144), new Variant(76), new Variant(42), new Variant(321))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs(new Variant(398), new Variant(704), new Variant(811), new Variant(653), new
                                Variant(144), new Variant(76), 42, new Variant(321));
                    }
                });
    }

    @Test
    public void test_SaveAs_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(302), new Variant(703), new
                Variant(689), new Variant(743), new Variant(974), new Variant(910), new Variant(42), new Variant(225)
                , new Variant(507))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs(new Variant(302), new Variant(703), new Variant(689), new Variant(743), new
                                Variant(974), new Variant(910), 42, new Variant(225), new Variant(507));
                    }
                });
    }

    @Test
    public void test_SaveAs_TenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(976), new Variant(706), new
                Variant(930), new Variant(625), new Variant(561), new Variant(218), new Variant(42), new Variant(487)
                , new Variant(790), new Variant(687))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs(new Variant(976), new Variant(706), new Variant(930), new Variant(625), new
                                Variant(561), new Variant(218), 42, new Variant(487), new Variant(790), new Variant
                                (687));
                    }
                });
    }

    @Test
    public void test_SaveAs_ElevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(407), new Variant(635), new
                Variant(698), new Variant(588), new Variant(415), new Variant(464), new Variant(42), new Variant(414)
                , new Variant(850), new Variant(357), new Variant(878))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs(new Variant(407), new Variant(635), new Variant(698), new Variant(588), new
                                Variant(415), new Variant(464), 42, new Variant(414), new Variant(850), new Variant
                                (357), new Variant(878));
                    }
                });
    }

    @Test
    public void test_SaveCopyAs_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xaf).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveCopyAs();
                    }
                });
    }

    @Test
    public void test_SaveCopyAs_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xaf).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(610))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveCopyAs(new Variant(610));
                    }
                });
    }

    @Test
    public void test_getAxSaved_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x12a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxSaved();
                    }
                });
    }

    @Test
    public void test_setAxSaved_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x12a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSaved(false);
                    }
                });
    }

    @Test
    public void test_getAxSaveLinkValues_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x196).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxSaveLinkValues();
                    }
                });
    }

    @Test
    public void test_setAxSaveLinkValues_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x196).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSaveLinkValues(false);
                    }
                });
    }

    @Test
    public void test_SendMail_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3b3).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(329))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SendMail(new Variant(329));
                    }
                });
    }

    @Test
    public void test_SendMail_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3b3).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(885), new Variant(791))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SendMail(new Variant(885), new Variant(791));
                    }
                });
    }

    @Test
    public void test_SendMail_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3b3).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(673), new Variant(971), new
                Variant(70))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SendMail(new Variant(673), new Variant(971), new Variant(70));
                    }
                });
    }

    @Test
    public void test_SendMailer_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3d4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(710), new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SendMailer(new Variant(710), 42);
                    }
                });
    }

    @Test
    public void test_SetLinkOnData_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x329).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("UyzjCIvuvl"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SetLinkOnData("UyzjCIvuvl");
                    }
                });
    }

    @Test
    public void test_SetLinkOnData_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x329).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("iSLrxJFVWo"), new Variant(108))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SetLinkOnData("iSLrxJFVWo", new Variant(108));
                    }
                });
    }

    @Test
    public void test_getAxSheets_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1e5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Sheets>() {
                    @Override
                    public Sheets invoke() throws ActiveXException {
                        return component.getAxSheets();
                    }
                });
    }

    @Test
    public void test_getAxShowConflictHistory_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x493).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxShowConflictHistory();
                    }
                });
    }

    @Test
    public void test_setAxShowConflictHistory_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x493).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxShowConflictHistory(false);
                    }
                });
    }

    @Test
    public void test_getAxStyles_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1ed).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Styles>() {
                    @Override
                    public Styles invoke() throws ActiveXException {
                        return component.getAxStyles();
                    }
                });
    }

    @Test
    public void test_getAxSubject_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3b9).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxSubject();
                    }
                });
    }

    @Test
    public void test_setAxSubject_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3b9).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("gofceRuRjf"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSubject("gofceRuRjf");
                    }
                });
    }

    @Test
    public void test_getAxTitle_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxTitle();
                    }
                });
    }

    @Test
    public void test_setAxTitle_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xc7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("zgJiObqeEW"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxTitle("zgJiObqeEW");
                    }
                });
    }

    @Test
    public void test_Unprotect_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Unprotect();
                    }
                });
    }

    @Test
    public void test_Unprotect_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x11d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(96))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Unprotect(new Variant(96));
                    }
                });
    }

    @Test
    public void test_UnprotectSharing_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5af).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.UnprotectSharing();
                    }
                });
    }

    @Test
    public void test_UnprotectSharing_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5af).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(608))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.UnprotectSharing(new Variant(608));
                    }
                });
    }

    @Test
    public void test_UpdateFromFile_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3e3).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.UpdateFromFile();
                    }
                });
    }

    @Test
    public void test_UpdateLink_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x324).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.UpdateLink();
                    }
                });
    }

    @Test
    public void test_UpdateLink_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x324).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(976))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.UpdateLink(new Variant(976));
                    }
                });
    }

    @Test
    public void test_UpdateLink_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x324).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(47), new Variant(389))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.UpdateLink(new Variant(47), new Variant(389));
                    }
                });
    }

    @Test
    public void test_getAxUpdateRemoteReferences_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x19b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxUpdateRemoteReferences();
                    }
                });
    }

    @Test
    public void test_setAxUpdateRemoteReferences_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x19b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxUpdateRemoteReferences(false);
                    }
                });
    }

    @Test
    public void test_getAxUserControl_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x4ba).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxUserControl();
                    }
                });
    }

    @Test
    public void test_setAxUserControl_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x4ba).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxUserControl(false);
                    }
                });
    }

    @Test
    public void test_getAxUserStatus_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x495).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxUserStatus();
                    }
                });
    }

    @Test
    public void test_getAxCustomViews_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5b0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<CustomViews>() {
                    @Override
                    public CustomViews invoke() throws ActiveXException {
                        return component.getAxCustomViews();
                    }
                });
    }

    @Test
    public void test_getAxWindows_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1ae).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Windows>() {
                    @Override
                    public Windows invoke() throws ActiveXException {
                        return component.getAxWindows();
                    }
                });
    }

    @Test
    public void test_getAxWorksheets_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1ee).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Sheets>() {
                    @Override
                    public Sheets invoke() throws ActiveXException {
                        return component.getAxWorksheets();
                    }
                });
    }

    @Test
    public void test_getAxWriteReserved_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x12b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxWriteReserved();
                    }
                });
    }

    @Test
    public void test_getAxWriteReservedBy_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x12c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxWriteReservedBy();
                    }
                });
    }

    @Test
    public void test_getAxExcel4IntlMacroSheets_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x245).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Sheets>() {
                    @Override
                    public Sheets invoke() throws ActiveXException {
                        return component.getAxExcel4IntlMacroSheets();
                    }
                });
    }

    @Test
    public void test_getAxExcel4MacroSheets_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x243).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Sheets>() {
                    @Override
                    public Sheets invoke() throws ActiveXException {
                        return component.getAxExcel4MacroSheets();
                    }
                });
    }

    @Test
    public void test_getAxTemplateRemoveExtData_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5b1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxTemplateRemoveExtData();
                    }
                });
    }

    @Test
    public void test_setAxTemplateRemoveExtData_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5b1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxTemplateRemoveExtData(false);
                    }
                });
    }

    @Test
    public void test_HighlightChangesOptions_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5b2).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.HighlightChangesOptions();
                    }
                });
    }

    @Test
    public void test_HighlightChangesOptions_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5b2).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(687))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.HighlightChangesOptions(new Variant(687));
                    }
                });
    }

    @Test
    public void test_HighlightChangesOptions_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5b2).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(100), new Variant(716))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.HighlightChangesOptions(new Variant(100), new Variant(716));
                    }
                });
    }

    @Test
    public void test_HighlightChangesOptions_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5b2).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(552), new Variant(436), new
                Variant(828))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.HighlightChangesOptions(new Variant(552), new Variant(436), new Variant(828));
                    }
                });
    }

    @Test
    public void test_getAxHighlightChangesOnScreen_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5b5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxHighlightChangesOnScreen();
                    }
                });
    }

    @Test
    public void test_setAxHighlightChangesOnScreen_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5b5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHighlightChangesOnScreen(false);
                    }
                });
    }

    @Test
    public void test_getAxKeepChangeHistory_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5b6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxKeepChangeHistory();
                    }
                });
    }

    @Test
    public void test_setAxKeepChangeHistory_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5b6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxKeepChangeHistory(false);
                    }
                });
    }

    @Test
    public void test_getAxListChangesOnNewSheet_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5b7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxListChangesOnNewSheet();
                    }
                });
    }

    @Test
    public void test_setAxListChangesOnNewSheet_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5b7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxListChangesOnNewSheet(false);
                    }
                });
    }

    @Test
    public void test_PurgeChangeHistoryNow_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5b8).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PurgeChangeHistoryNow(42);
                    }
                });
    }

    @Test
    public void test_PurgeChangeHistoryNow_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5b8).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(970))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PurgeChangeHistoryNow(42, new Variant(970));
                    }
                });
    }

    @Test
    public void test_AcceptAllChanges_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5ba).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AcceptAllChanges();
                    }
                });
    }

    @Test
    public void test_AcceptAllChanges_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5ba).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(582))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AcceptAllChanges(new Variant(582));
                    }
                });
    }

    @Test
    public void test_AcceptAllChanges_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5ba).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(814), new Variant(981))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AcceptAllChanges(new Variant(814), new Variant(981));
                    }
                });
    }

    @Test
    public void test_AcceptAllChanges_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5ba).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(417), new Variant(814), new
                Variant(626))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AcceptAllChanges(new Variant(417), new Variant(814), new Variant(626));
                    }
                });
    }

    @Test
    public void test_RejectAllChanges_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5bb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.RejectAllChanges();
                    }
                });
    }

    @Test
    public void test_RejectAllChanges_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5bb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(250))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.RejectAllChanges(new Variant(250));
                    }
                });
    }

    @Test
    public void test_RejectAllChanges_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5bb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(853), new Variant(782))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.RejectAllChanges(new Variant(853), new Variant(782));
                    }
                });
    }

    @Test
    public void test_RejectAllChanges_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5bb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(372), new Variant(396), new
                Variant(741))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.RejectAllChanges(new Variant(372), new Variant(396), new Variant(741));
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
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(443))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotTableWizard(new Variant(443));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(425), new Variant(855))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotTableWizard(new Variant(425), new Variant(855));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(951), new Variant(86), new Variant
                (827))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotTableWizard(new Variant(951), new Variant(86), new Variant(827));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(934), new Variant(850), new
                Variant(481), new Variant(880))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotTableWizard(new Variant(934), new Variant(850), new Variant(481), new Variant
                                (880));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(359), new Variant(111), new
                Variant(330), new Variant(975), new Variant(768))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotTableWizard(new Variant(359), new Variant(111), new Variant(330), new Variant
                                (975), new Variant(768));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(308), new Variant(942), new
                Variant(911), new Variant(608), new Variant(550), new Variant(575))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotTableWizard(new Variant(308), new Variant(942), new Variant(911), new Variant
                                (608), new Variant(550), new Variant(575));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(334), new Variant(571), new
                Variant(339), new Variant(528), new Variant(531), new Variant(566), new Variant(762))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotTableWizard(new Variant(334), new Variant(571), new Variant(339), new Variant
                                (528), new Variant(531), new Variant(566), new Variant(762));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(181), new Variant(338), new
                Variant(736), new Variant(999), new Variant(479), new Variant(73), new Variant(177), new Variant(31))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotTableWizard(new Variant(181), new Variant(338), new Variant(736), new Variant
                                (999), new Variant(479), new Variant(73), new Variant(177), new Variant(31));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(557), new Variant(43), new Variant
                (268), new Variant(324), new Variant(838), new Variant(864), new Variant(616), new Variant(269), new
                Variant(651))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotTableWizard(new Variant(557), new Variant(43), new Variant(268), new Variant
                                (324), new Variant(838), new Variant(864), new Variant(616), new Variant(269), new
                                Variant(651));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_TenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(286), new Variant(541), new
                Variant(126), new Variant(762), new Variant(145), new Variant(89), new Variant(23), new Variant(204),
                new Variant(627), new Variant(202))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotTableWizard(new Variant(286), new Variant(541), new Variant(126), new Variant
                                (762), new Variant(145), new Variant(89), new Variant(23), new Variant(204), new
                                Variant(627), new Variant(202));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_ElevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(107), new Variant(904), new
                Variant(864), new Variant(773), new Variant(503), new Variant(97), new Variant(656), new Variant(230)
                , new Variant(493), new Variant(738), new Variant(417))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotTableWizard(new Variant(107), new Variant(904), new Variant(864), new Variant
                                (773), new Variant(503), new Variant(97), new Variant(656), new Variant(230), new
                                Variant(493), new Variant(738), new Variant(417));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_TwelveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(73), new Variant(269), new Variant
                (890), new Variant(313), new Variant(404), new Variant(487), new Variant(267), new Variant(309), new
                Variant(727), new Variant(335), new Variant(908), new Variant(985))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotTableWizard(new Variant(73), new Variant(269), new Variant(890), new Variant
                                (313), new Variant(404), new Variant(487), new Variant(267), new Variant(309), new
                                Variant(727), new Variant(335), new Variant(908), new Variant(985));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_ThirteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(268), new Variant(965), new
                Variant(510), new Variant(493), new Variant(297), new Variant(704), new Variant(755), new Variant
                (488), new Variant(157), new Variant(14), new Variant(170), new Variant(555), new Variant(846))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotTableWizard(new Variant(268), new Variant(965), new Variant(510), new Variant
                                (493), new Variant(297), new Variant(704), new Variant(755), new Variant(488), new
                                Variant(157), new Variant(14), new Variant(170), new Variant(555), new Variant(846));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_FourteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(890), new Variant(464), new
                Variant(772), new Variant(864), new Variant(155), new Variant(464), new Variant(606), new Variant(34)
                , new Variant(765), new Variant(611), new Variant(905), new Variant(811), new Variant(751), new
                        Variant(179))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotTableWizard(new Variant(890), new Variant(464), new Variant(772), new Variant
                                (864), new Variant(155), new Variant(464), new Variant(606), new Variant(34), new
                                Variant(765), new Variant(611), new Variant(905), new Variant(811), new Variant(751),
                                new Variant(179));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_FifteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(268), new Variant(186), new
                Variant(40), new Variant(977), new Variant(115), new Variant(499), new Variant(302), new Variant(174)
                , new Variant(414), new Variant(789), new Variant(541), new Variant(719), new Variant(785), new
                        Variant(856), new Variant(656))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotTableWizard(new Variant(268), new Variant(186), new Variant(40), new Variant
                                (977), new Variant(115), new Variant(499), new Variant(302), new Variant(174), new
                                Variant(414), new Variant(789), new Variant(541), new Variant(719), new Variant(785),
                                new Variant(856), new Variant(656));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_SixteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(321), new Variant(337), new
                Variant(44), new Variant(686), new Variant(660), new Variant(746), new Variant(596), new Variant(428)
                , new Variant(500), new Variant(914), new Variant(121), new Variant(36), new Variant(467), new
                        Variant(360), new Variant(84), new Variant(239))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PivotTableWizard(new Variant(321), new Variant(337), new Variant(44), new Variant
                                (686), new Variant(660), new Variant(746), new Variant(596), new Variant(428), new
                                Variant(500), new Variant(914), new Variant(121), new Variant(36), new Variant(467),
                                new Variant(360), new Variant(84), new Variant(239));
                    }
                });
    }

    @Test
    public void test_ResetColors_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5bc).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ResetColors();
                    }
                });
    }

    @Test
    public void test_getAxVBProject_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5bd).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxVBProject();
                    }
                });
    }

    @Test
    public void test_FollowHyperlink_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5be).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("WPepZESmZm"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.FollowHyperlink("WPepZESmZm");
                    }
                });
    }

    @Test
    public void test_FollowHyperlink_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5be).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("SYYgZazVJk"), new Variant(202))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.FollowHyperlink("SYYgZazVJk", new Variant(202));
                    }
                });
    }

    @Test
    public void test_FollowHyperlink_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5be).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("YwNRlGUVdp"), new Variant(119),
                new Variant(739))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.FollowHyperlink("YwNRlGUVdp", new Variant(119), new Variant(739));
                    }
                });
    }

    @Test
    public void test_FollowHyperlink_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5be).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("NJHceXTHaW"), new Variant(644),
                new Variant(254), new Variant(745))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.FollowHyperlink("NJHceXTHaW", new Variant(644), new Variant(254), new Variant(745));
                    }
                });
    }

    @Test
    public void test_FollowHyperlink_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5be).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("txVtlSmCHM"), new Variant(37),
                new Variant(285), new Variant(687), new Variant(162))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.FollowHyperlink("txVtlSmCHM", new Variant(37), new Variant(285), new Variant(687),
                                new Variant(162));
                    }
                });
    }

    @Test
    public void test_FollowHyperlink_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5be).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("qRDWjXoIQN"), new Variant(792),
                new Variant(818), new Variant(723), new Variant(354), new Variant(199))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.FollowHyperlink("qRDWjXoIQN", new Variant(792), new Variant(818), new Variant(723),
                                new Variant(354), new Variant(199));
                    }
                });
    }

    @Test
    public void test_FollowHyperlink_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5be).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("uuUsWgzaoM"), new Variant(12),
                new Variant(730), new Variant(990), new Variant(306), new Variant(824), new Variant(874))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.FollowHyperlink("uuUsWgzaoM", new Variant(12), new Variant(730), new Variant(990),
                                new Variant(306), new Variant(824), new Variant(874));
                    }
                });
    }

    @Test
    public void test_AddToFavorites_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5c4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AddToFavorites();
                    }
                });
    }

    @Test
    public void test_getAxIsInplace_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6f4).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxIsInplace();
                    }
                });
    }

}