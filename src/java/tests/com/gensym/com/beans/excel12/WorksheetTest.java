package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class WorksheetTest extends ActiveXDispatchableTestBase {

    private Worksheet component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new Worksheet(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(94), new Variant(517))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(94), new Variant(517));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(247))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(247));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(654))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(654));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(360), new Variant(475), new
                Variant(42L), new Variant(42L), new Variant(124))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(360), new Variant(475), 42L, 42L, new Variant(124));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(543), new
                Variant(42L), new Variant(42), new Variant(251), new Variant(644), new Variant(753), new Variant(611))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(543), 42L, 42, new Variant(251), new Variant(644), new
                                Variant(753), new Variant(611));
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
    public void test_Copy_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x227).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(638))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Copy(new Variant(638));
                    }
                });
    }

    @Test
    public void test_Copy_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x227).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(390), new Variant(709))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Copy(new Variant(390), new Variant(709));
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
        on(0x80010000).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("xaPuZvQABf"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAx_CodeName("xaPuZvQABf");
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
    public void test_Move_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x27d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Move();
                    }
                });
    }

    @Test
    public void test_Move_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x27d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(260))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Move(new Variant(260));
                    }
                });
    }

    @Test
    public void test_Move_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x27d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(529), new Variant(740))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Move(new Variant(529), new Variant(740));
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
        on(0x6e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("lIZkmqPUWT"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxName("lIZkmqPUWT");
                    }
                });
    }

    @Test
    public void test_getAxNext_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxNext();
                    }
                });
    }

    @Test
    public void test_getAxOnDoubleClick_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x274).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxOnDoubleClick();
                    }
                });
    }

    @Test
    public void test_setAxOnDoubleClick_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x274).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("XPSuoBWdFT"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnDoubleClick("XPSuoBWdFT");
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
        on(0x407).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("iQBRlegQBa"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnSheetActivate("iQBRlegQBa");
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
        on(0x439).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("CYdmSzRcNF"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnSheetDeactivate("CYdmSzRcNF");
                    }
                });
    }

    @Test
    public void test_getAxPageSetup_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3e6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<PageSetup>() {
                    @Override
                    public PageSetup invoke() throws ActiveXException {
                        return component.getAxPageSetup();
                    }
                });
    }

    @Test
    public void test_getAxPrevious_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxPrevious();
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
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(98))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(98));
                    }
                });
    }

    @Test
    public void test_PrintOut_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(526), new Variant(67))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(526), new Variant(67));
                    }
                });
    }

    @Test
    public void test_PrintOut_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(98), new Variant(937), new Variant
                (304))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(98), new Variant(937), new Variant(304));
                    }
                });
    }

    @Test
    public void test_PrintOut_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(662), new Variant(170), new
                Variant(181), new Variant(79))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(662), new Variant(170), new Variant(181), new Variant(79));
                    }
                });
    }

    @Test
    public void test_PrintOut_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(956), new Variant(417), new
                Variant(744), new Variant(465), new Variant(347))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(956), new Variant(417), new Variant(744), new Variant(465),
                                new Variant(347));
                    }
                });
    }

    @Test
    public void test_PrintOut_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(508), new Variant(986), new
                Variant(107), new Variant(35), new Variant(641), new Variant(921))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(508), new Variant(986), new Variant(107), new Variant(35), new
                                Variant(641), new Variant(921));
                    }
                });
    }

    @Test
    public void test_PrintOut_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(16), new Variant(937), new Variant
                (747), new Variant(90), new Variant(398), new Variant(236), new Variant(365))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(16), new Variant(937), new Variant(747), new Variant(90), new
                                Variant(398), new Variant(236), new Variant(365));
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
        on(0x119).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(524))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintPreview(new Variant(524));
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
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(494))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect(new Variant(494));
                    }
                });
    }

    @Test
    public void test_Protect_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(180), new Variant(234))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect(new Variant(180), new Variant(234));
                    }
                });
    }

    @Test
    public void test_Protect_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(469), new Variant(568), new
                Variant(794))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect(new Variant(469), new Variant(568), new Variant(794));
                    }
                });
    }

    @Test
    public void test_Protect_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(55), new Variant(175), new Variant
                (433), new Variant(315))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect(new Variant(55), new Variant(175), new Variant(433), new Variant(315));
                    }
                });
    }

    @Test
    public void test_Protect_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(334), new Variant(386), new
                Variant(482), new Variant(158), new Variant(16))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect(new Variant(334), new Variant(386), new Variant(482), new Variant(158), new
                                Variant(16));
                    }
                });
    }

    @Test
    public void test_getAxProtectContents_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x124).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxProtectContents();
                    }
                });
    }

    @Test
    public void test_getAxProtectDrawingObjects_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x125).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxProtectDrawingObjects();
                    }
                });
    }

    @Test
    public void test_getAxProtectionMode_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x487).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxProtectionMode();
                    }
                });
    }

    @Test
    public void test_getAxProtectScenarios_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x126).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxProtectScenarios();
                    }
                });
    }

    @Test
    public void test_SaveAs_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("WkPacxqNNF"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("WkPacxqNNF");
                    }
                });
    }

    @Test
    public void test_SaveAs_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("HHhcnpKXZy"), new Variant(565))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("HHhcnpKXZy", new Variant(565));
                    }
                });
    }

    @Test
    public void test_SaveAs_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("ZVxlrJThes"), new Variant(734),
                new Variant(517))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("ZVxlrJThes", new Variant(734), new Variant(517));
                    }
                });
    }

    @Test
    public void test_SaveAs_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("acyIqPZFqh"), new Variant(381),
                new Variant(495), new Variant(127))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("acyIqPZFqh", new Variant(381), new Variant(495), new Variant(127));
                    }
                });
    }

    @Test
    public void test_SaveAs_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("ZdVNLRCqUr"), new Variant(408),
                new Variant(419), new Variant(456), new Variant(702))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("ZdVNLRCqUr", new Variant(408), new Variant(419), new Variant(456), new
                                Variant(702));
                    }
                });
    }

    @Test
    public void test_SaveAs_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("vBmJtyexth"), new Variant(316),
                new Variant(377), new Variant(653), new Variant(69), new Variant(355))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("vBmJtyexth", new Variant(316), new Variant(377), new Variant(653), new
                                Variant(69), new Variant(355));
                    }
                });
    }

    @Test
    public void test_SaveAs_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("JZtfrNPHGm"), new Variant(63),
                new Variant(767), new Variant(211), new Variant(789), new Variant(892), new Variant(677))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("JZtfrNPHGm", new Variant(63), new Variant(767), new Variant(211), new
                                Variant(789), new Variant(892), new Variant(677));
                    }
                });
    }

    @Test
    public void test_SaveAs_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("lcFGNPwvFV"), new Variant(571),
                new Variant(501), new Variant(668), new Variant(968), new Variant(393), new Variant(206), new Variant
                        (764))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("lcFGNPwvFV", new Variant(571), new Variant(501), new Variant(668), new
                                Variant(968), new Variant(393), new Variant(206), new Variant(764));
                    }
                });
    }

    @Test
    public void test_SaveAs_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("xpStrYnzyP"), new Variant(852),
                new Variant(371), new Variant(548), new Variant(786), new Variant(767), new Variant(367), new Variant
                        (183), new Variant(174))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("xpStrYnzyP", new Variant(852), new Variant(371), new Variant(548), new
                                Variant(786), new Variant(767), new Variant(367), new Variant(183), new Variant(174));
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
    public void test_Select_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xeb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(266))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Select(new Variant(266));
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
        on(0x11d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(695))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Unprotect(new Variant(695));
                    }
                });
    }

    @Test
    public void test_getAxVisible_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x22e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxVisible();
                    }
                });
    }

    @Test
    public void test_setAxVisible_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x22e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxVisible(42);
                    }
                });
    }

    @Test
    public void test_getAxShapes_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x561).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Shapes>() {
                    @Override
                    public Shapes invoke() throws ActiveXException {
                        return component.getAxShapes();
                    }
                });
    }

    @Test
    public void test_getAxTransitionExpEval_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x191).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxTransitionExpEval();
                    }
                });
    }

    @Test
    public void test_setAxTransitionExpEval_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x191).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxTransitionExpEval(false);
                    }
                });
    }

    @Test
    public void test_Arcs_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2f8).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Arcs();
                    }
                });
    }

    @Test
    public void test_Arcs_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2f8).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(33))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Arcs(new Variant(33));
                    }
                });
    }

    @Test
    public void test_getAxAutoFilterMode_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x318).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxAutoFilterMode();
                    }
                });
    }

    @Test
    public void test_setAxAutoFilterMode_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x318).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxAutoFilterMode(false);
                    }
                });
    }

    @Test
    public void test_SetBackgroundPicture_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x4a4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("nwhbzpDHwC"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SetBackgroundPicture("nwhbzpDHwC");
                    }
                });
    }

    @Test
    public void test_Buttons_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x22d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Buttons();
                    }
                });
    }

    @Test
    public void test_Buttons_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x22d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(751))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Buttons(new Variant(751));
                    }
                });
    }

    @Test
    public void test_Calculate_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x117).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Calculate();
                    }
                });
    }

    @Test
    public void test_getAxEnableCalculation_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x590).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxEnableCalculation();
                    }
                });
    }

    @Test
    public void test_setAxEnableCalculation_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x590).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxEnableCalculation(false);
                    }
                });
    }

    @Test
    public void test_getAxCells_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xee).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxCells();
                    }
                });
    }

    @Test
    public void test_ChartObjects_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x424).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.ChartObjects();
                    }
                });
    }

    @Test
    public void test_ChartObjects_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x424).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(388))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.ChartObjects(new Variant(388));
                    }
                });
    }

    @Test
    public void test_CheckBoxes_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x338).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.CheckBoxes();
                    }
                });
    }

    @Test
    public void test_CheckBoxes_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x338).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(229))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.CheckBoxes(new Variant(229));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling();
                    }
                });
    }

    @Test
    public void test_CheckSpelling_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(73))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(73));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(475), new Variant(846))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(475), new Variant(846));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(37), new Variant(312), new Variant
                (63))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(37), new Variant(312), new Variant(63));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(961), new Variant(350), new
                Variant(785), new Variant(687))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(961), new Variant(350), new Variant(785), new Variant(687));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(979), new Variant(276), new
                Variant(238), new Variant(435), new Variant(393))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(979), new Variant(276), new Variant(238), new Variant
                                (435), new Variant(393));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(973), new Variant(293), new
                Variant(247), new Variant(63), new Variant(917), new Variant(329))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(973), new Variant(293), new Variant(247), new Variant(63)
                                , new Variant(917), new Variant(329));
                    }
                });
    }

    @Test
    public void test_getAxCircularReference_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x42d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxCircularReference();
                    }
                });
    }

    @Test
    public void test_ClearArrows_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3ca).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ClearArrows();
                    }
                });
    }

    @Test
    public void test_getAxColumns_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xf1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxColumns();
                    }
                });
    }

    @Test
    public void test_getAxConsolidationFunction_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x315).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxConsolidationFunction();
                    }
                });
    }

    @Test
    public void test_getAxConsolidationOptions_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x316).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxConsolidationOptions();
                    }
                });
    }

    @Test
    public void test_getAxConsolidationSources_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x317).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxConsolidationSources();
                    }
                });
    }

    @Test
    public void test_getAxDisplayAutomaticPageBreaks_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x283).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxDisplayAutomaticPageBreaks();
                    }
                });
    }

    @Test
    public void test_setAxDisplayAutomaticPageBreaks_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x283).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDisplayAutomaticPageBreaks(false);
                    }
                });
    }

    @Test
    public void test_Drawings_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x304).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Drawings();
                    }
                });
    }

    @Test
    public void test_Drawings_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x304).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(293))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Drawings(new Variant(293));
                    }
                });
    }

    @Test
    public void test_DrawingObjects_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x58).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.DrawingObjects();
                    }
                });
    }

    @Test
    public void test_DrawingObjects_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x58).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(18))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.DrawingObjects(new Variant(18));
                    }
                });
    }

    @Test
    public void test_DropDowns_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x344).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.DropDowns();
                    }
                });
    }

    @Test
    public void test_DropDowns_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x344).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(233))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.DropDowns(new Variant(233));
                    }
                });
    }

    @Test
    public void test_getAxEnableAutoFilter_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x484).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxEnableAutoFilter();
                    }
                });
    }

    @Test
    public void test_setAxEnableAutoFilter_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x484).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxEnableAutoFilter(false);
                    }
                });
    }

    @Test
    public void test_getAxEnableSelection_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x591).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxEnableSelection();
                    }
                });
    }

    @Test
    public void test_setAxEnableSelection_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x591).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxEnableSelection(42);
                    }
                });
    }

    @Test
    public void test_getAxEnableOutlining_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x485).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxEnableOutlining();
                    }
                });
    }

    @Test
    public void test_setAxEnableOutlining_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x485).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxEnableOutlining(false);
                    }
                });
    }

    @Test
    public void test_getAxEnablePivotTable_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x486).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxEnablePivotTable();
                    }
                });
    }

    @Test
    public void test_setAxEnablePivotTable_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x486).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxEnablePivotTable(false);
                    }
                });
    }

    @Test
    public void test_Evaluate_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x1).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(565))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Evaluate(new Variant(565));
                    }
                });
    }

    @Test
    public void test__Evaluate_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xfffffffb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(928))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Evaluate(new Variant(928));
                    }
                });
    }

    @Test
    public void test_getAxFilterMode_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x320).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxFilterMode();
                    }
                });
    }

    @Test
    public void test_ResetAllPageBreaks_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x592).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ResetAllPageBreaks();
                    }
                });
    }

    @Test
    public void test_GroupBoxes_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x342).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.GroupBoxes();
                    }
                });
    }

    @Test
    public void test_GroupBoxes_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x342).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(262))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.GroupBoxes(new Variant(262));
                    }
                });
    }

    @Test
    public void test_GroupObjects_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x459).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.GroupObjects();
                    }
                });
    }

    @Test
    public void test_GroupObjects_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x459).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(709))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.GroupObjects(new Variant(709));
                    }
                });
    }

    @Test
    public void test_Labels_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x349).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Labels();
                    }
                });
    }

    @Test
    public void test_Labels_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x349).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(91))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Labels(new Variant(91));
                    }
                });
    }

    @Test
    public void test_Lines_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ff).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Lines();
                    }
                });
    }

    @Test
    public void test_Lines_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2ff).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(280))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Lines(new Variant(280));
                    }
                });
    }

    @Test
    public void test_ListBoxes_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x340).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.ListBoxes();
                    }
                });
    }

    @Test
    public void test_ListBoxes_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x340).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(891))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.ListBoxes(new Variant(891));
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
    public void test_OLEObjects_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x31f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.OLEObjects();
                    }
                });
    }

    @Test
    public void test_OLEObjects_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x31f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(882))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.OLEObjects(new Variant(882));
                    }
                });
    }

    @Test
    public void test_getAxOnCalculate_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x271).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxOnCalculate();
                    }
                });
    }

    @Test
    public void test_setAxOnCalculate_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x271).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("rrOONArFBs"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnCalculate("rrOONArFBs");
                    }
                });
    }

    @Test
    public void test_getAxOnData_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x275).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxOnData();
                    }
                });
    }

    @Test
    public void test_setAxOnData_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x275).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("UqPjgkyAyl"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnData("UqPjgkyAyl");
                    }
                });
    }

    @Test
    public void test_getAxOnEntry_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x273).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxOnEntry();
                    }
                });
    }

    @Test
    public void test_setAxOnEntry_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x273).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("VelLhpduMN"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnEntry("VelLhpduMN");
                    }
                });
    }

    @Test
    public void test_OptionButtons_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x33a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.OptionButtons();
                    }
                });
    }

    @Test
    public void test_OptionButtons_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x33a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(907))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.OptionButtons(new Variant(907));
                    }
                });
    }

    @Test
    public void test_getAxOutline_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x66).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Outline>() {
                    @Override
                    public Outline invoke() throws ActiveXException {
                        return component.getAxOutline();
                    }
                });
    }

    @Test
    public void test_Ovals_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x321).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Ovals();
                    }
                });
    }

    @Test
    public void test_Ovals_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x321).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(485))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Ovals(new Variant(485));
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
    public void test_Paste_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xd3).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(10))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Paste(new Variant(10));
                    }
                });
    }

    @Test
    public void test_Paste_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xd3).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(976), new Variant(407))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Paste(new Variant(976), new Variant(407));
                    }
                });
    }

    @Test
    public void test_PasteSpecial_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x403).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PasteSpecial();
                    }
                });
    }

    @Test
    public void test_PasteSpecial_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x403).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(17))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PasteSpecial(new Variant(17));
                    }
                });
    }

    @Test
    public void test_PasteSpecial_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x403).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(150), new Variant(91))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PasteSpecial(new Variant(150), new Variant(91));
                    }
                });
    }

    @Test
    public void test_PasteSpecial_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x403).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(291), new Variant(831), new
                Variant(54))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PasteSpecial(new Variant(291), new Variant(831), new Variant(54));
                    }
                });
    }

    @Test
    public void test_PasteSpecial_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x403).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(533), new Variant(778), new
                Variant(834), new Variant(943))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PasteSpecial(new Variant(533), new Variant(778), new Variant(834), new Variant(943));
                    }
                });
    }

    @Test
    public void test_PasteSpecial_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x403).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(296), new Variant(203), new
                Variant(332), new Variant(645), new Variant(390))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PasteSpecial(new Variant(296), new Variant(203), new Variant(332), new Variant(645)
                                , new Variant(390));
                    }
                });
    }

    @Test
    public void test_PasteSpecial_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x403).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(356), new Variant
                (730), new Variant(503), new Variant(715), new Variant(970))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PasteSpecial(new Variant(42), new Variant(356), new Variant(730), new Variant(503),
                                new Variant(715), new Variant(970));
                    }
                });
    }

    @Test
    public void test_Pictures_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x303).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Pictures();
                    }
                });
    }

    @Test
    public void test_Pictures_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x303).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(312))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Pictures(new Variant(312));
                    }
                });
    }

    @Test
    public void test_PivotTables_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2b2).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.PivotTables();
                    }
                });
    }

    @Test
    public void test_PivotTables_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2b2).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(294))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.PivotTables(new Variant(294));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.PivotTableWizard();
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(402))
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.PivotTableWizard(new Variant(402));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(986), new Variant(856))
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.PivotTableWizard(new Variant(986), new Variant(856));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(136), new Variant(790), new
                Variant(906))
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.PivotTableWizard(new Variant(136), new Variant(790), new Variant(906));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(397), new Variant(146), new
                Variant(252), new Variant(386))
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.PivotTableWizard(new Variant(397), new Variant(146), new Variant(252), new
                                Variant(386));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(402), new Variant(127), new
                Variant(911), new Variant(719), new Variant(168))
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.PivotTableWizard(new Variant(402), new Variant(127), new Variant(911), new
                                Variant(719), new Variant(168));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(499), new Variant(413), new
                Variant(404), new Variant(676), new Variant(14), new Variant(404))
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.PivotTableWizard(new Variant(499), new Variant(413), new Variant(404), new
                                Variant(676), new Variant(14), new Variant(404));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(478), new Variant(557), new
                Variant(536), new Variant(868), new Variant(114), new Variant(691), new Variant(797))
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.PivotTableWizard(new Variant(478), new Variant(557), new Variant(536), new
                                Variant(868), new Variant(114), new Variant(691), new Variant(797));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(350), new Variant(910), new
                Variant(803), new Variant(158), new Variant(634), new Variant(529), new Variant(911), new Variant(28))
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.PivotTableWizard(new Variant(350), new Variant(910), new Variant(803), new
                                Variant(158), new Variant(634), new Variant(529), new Variant(911), new Variant(28));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(559), new Variant(87), new Variant
                (794), new Variant(289), new Variant(266), new Variant(940), new Variant(673), new Variant(141), new
                Variant(177))
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.PivotTableWizard(new Variant(559), new Variant(87), new Variant(794), new
                                Variant(289), new Variant(266), new Variant(940), new Variant(673), new Variant(141),
                                new Variant(177));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_TenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(212), new Variant(445), new
                Variant(738), new Variant(786), new Variant(869), new Variant(429), new Variant(172), new Variant
                (733), new Variant(827), new Variant(249))
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.PivotTableWizard(new Variant(212), new Variant(445), new Variant(738), new
                                Variant(786), new Variant(869), new Variant(429), new Variant(172), new Variant(733),
                                new Variant(827), new Variant(249));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_ElevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(976), new Variant(712), new
                Variant(70), new Variant(985), new Variant(280), new Variant(777), new Variant(721), new Variant(155)
                , new Variant(777), new Variant(510), new Variant(17))
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.PivotTableWizard(new Variant(976), new Variant(712), new Variant(70), new
                                Variant(985), new Variant(280), new Variant(777), new Variant(721), new Variant(155),
                                new Variant(777), new Variant(510), new Variant(17));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_TwelveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(700), new Variant(737), new
                Variant(592), new Variant(192), new Variant(918), new Variant(680), new Variant(646), new Variant
                (733), new Variant(999), new Variant(562), new Variant(134), new Variant(202))
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.PivotTableWizard(new Variant(700), new Variant(737), new Variant(592), new
                                Variant(192), new Variant(918), new Variant(680), new Variant(646), new Variant(733),
                                new Variant(999), new Variant(562), new Variant(134), new Variant(202));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_ThirteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(354), new Variant(469), new
                Variant(470), new Variant(890), new Variant(215), new Variant(974), new Variant(89), new Variant(884)
                , new Variant(909), new Variant(794), new Variant(685), new Variant(609), new Variant(896))
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.PivotTableWizard(new Variant(354), new Variant(469), new Variant(470), new
                                Variant(890), new Variant(215), new Variant(974), new Variant(89), new Variant(884),
                                new Variant(909), new Variant(794), new Variant(685), new Variant(609), new Variant
                                        (896));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_FourteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(644), new Variant(705), new
                Variant(542), new Variant(782), new Variant(282), new Variant(859), new Variant(22), new Variant(139)
                , new Variant(580), new Variant(111), new Variant(944), new Variant(84), new Variant(819), new
                        Variant(668))
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.PivotTableWizard(new Variant(644), new Variant(705), new Variant(542), new
                                Variant(782), new Variant(282), new Variant(859), new Variant(22), new Variant(139),
                                new Variant(580), new Variant(111), new Variant(944), new Variant(84), new Variant
                                        (819), new Variant(668));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_FifteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(56), new Variant(992), new Variant
                (57), new Variant(105), new Variant(516), new Variant(355), new Variant(970), new Variant(757), new
                Variant(733), new Variant(732), new Variant(278), new Variant(140), new Variant(424), new Variant
                (854), new Variant(955))
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.PivotTableWizard(new Variant(56), new Variant(992), new Variant(57), new
                                Variant(105), new Variant(516), new Variant(355), new Variant(970), new Variant(757),
                                new Variant(733), new Variant(732), new Variant(278), new Variant(140), new Variant
                                        (424), new Variant(854), new Variant(955));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_SixteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(165), new Variant(568), new
                Variant(932), new Variant(747), new Variant(88), new Variant(442), new Variant(637), new Variant(119)
                , new Variant(901), new Variant(133), new Variant(768), new Variant(992), new Variant(560), new
                        Variant(956), new Variant(593), new Variant(517))
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.PivotTableWizard(new Variant(165), new Variant(568), new Variant(932), new
                                Variant(747), new Variant(88), new Variant(442), new Variant(637), new Variant(119),
                                new Variant(901), new Variant(133), new Variant(768), new Variant(992), new Variant
                                        (560), new Variant(956), new Variant(593), new Variant(517));
                    }
                });
    }

    @Test
    public void test_getAxRange_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xc5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(704))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxRange(new Variant(704));
                    }
                });
    }

    @Test
    public void test_getAxRange_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(993), new Variant(888))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxRange(new Variant(993), new Variant(888));
                    }
                });
    }

    @Test
    public void test_Rectangles_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x306).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Rectangles();
                    }
                });
    }

    @Test
    public void test_Rectangles_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x306).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(302))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Rectangles(new Variant(302));
                    }
                });
    }

    @Test
    public void test_getAxRows_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x102).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxRows();
                    }
                });
    }

    @Test
    public void test_Scenarios_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x38c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Scenarios();
                    }
                });
    }

    @Test
    public void test_Scenarios_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x38c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(79))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Scenarios(new Variant(79));
                    }
                });
    }

    @Test
    public void test_getAxScrollArea_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x599).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxScrollArea();
                    }
                });
    }

    @Test
    public void test_setAxScrollArea_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x599).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("QiTkXaDaem"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxScrollArea("QiTkXaDaem");
                    }
                });
    }

    @Test
    public void test_ScrollBars_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x33e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.ScrollBars();
                    }
                });
    }

    @Test
    public void test_ScrollBars_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x33e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(407))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.ScrollBars(new Variant(407));
                    }
                });
    }

    @Test
    public void test_ShowAllData_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x31a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ShowAllData();
                    }
                });
    }

    @Test
    public void test_ShowDataForm_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x199).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ShowDataForm();
                    }
                });
    }

    @Test
    public void test_Spinners_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x346).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Spinners();
                    }
                });
    }

    @Test
    public void test_Spinners_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x346).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(291))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Spinners(new Variant(291));
                    }
                });
    }

    @Test
    public void test_getAxStandardHeight_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x197).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxStandardHeight();
                    }
                });
    }

    @Test
    public void test_getAxStandardWidth_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x198).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxStandardWidth();
                    }
                });
    }

    @Test
    public void test_setAxStandardWidth_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x198).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32d))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxStandardWidth(42.32d);
                    }
                });
    }

    @Test
    public void test_TextBoxes_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x309).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.TextBoxes();
                    }
                });
    }

    @Test
    public void test_TextBoxes_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x309).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(876))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.TextBoxes(new Variant(876));
                    }
                });
    }

    @Test
    public void test_getAxTransitionFormEntry_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x192).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxTransitionFormEntry();
                    }
                });
    }

    @Test
    public void test_setAxTransitionFormEntry_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x192).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxTransitionFormEntry(false);
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
    public void test_getAxUsedRange_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x19c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxUsedRange();
                    }
                });
    }

    @Test
    public void test_getAxHPageBreaks_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x58a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<HPageBreaks>() {
                    @Override
                    public HPageBreaks invoke() throws ActiveXException {
                        return component.getAxHPageBreaks();
                    }
                });
    }

    @Test
    public void test_getAxVPageBreaks_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x58b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<VPageBreaks>() {
                    @Override
                    public VPageBreaks invoke() throws ActiveXException {
                        return component.getAxVPageBreaks();
                    }
                });
    }

    @Test
    public void test_getAxQueryTables_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x59a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<QueryTables>() {
                    @Override
                    public QueryTables invoke() throws ActiveXException {
                        return component.getAxQueryTables();
                    }
                });
    }

    @Test
    public void test_getAxDisplayPageBreaks_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x59b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxDisplayPageBreaks();
                    }
                });
    }

    @Test
    public void test_setAxDisplayPageBreaks_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x59b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDisplayPageBreaks(false);
                    }
                });
    }

    @Test
    public void test_getAxComments_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x23f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Comments>() {
                    @Override
                    public Comments invoke() throws ActiveXException {
                        return component.getAxComments();
                    }
                });
    }

    @Test
    public void test_getAxHyperlinks_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x571).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Hyperlinks>() {
                    @Override
                    public Hyperlinks invoke() throws ActiveXException {
                        return component.getAxHyperlinks();
                    }
                });
    }

    @Test
    public void test_ClearCircles_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x59c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ClearCircles();
                    }
                });
    }

    @Test
    public void test_CircleInvalid_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x59d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CircleInvalid();
                    }
                });
    }

    @Test
    public void test_getAxDisplayRightToLeft_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x288).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxDisplayRightToLeft();
                    }
                });
    }

    @Test
    public void test_setAxDisplayRightToLeft_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x288).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDisplayRightToLeft(42);
                    }
                });
    }

    @Test
    public void test_getAxAutoFilter_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x319).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<AutoFilter>() {
                    @Override
                    public AutoFilter invoke() throws ActiveXException {
                        return component.getAxAutoFilter();
                    }
                });
    }

}