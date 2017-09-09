package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class ChartTest extends ActiveXDispatchableTestBase {

    private Chart component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new Chart(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(988), new Variant(212))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(988), new Variant(212));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(827))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(827));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(971))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(971));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(286), new Variant(352), new
                Variant(42L), new Variant(42L), new Variant(503))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(286), new Variant(352), 42L, 42L, new Variant(503));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(44), new
                Variant(42L), new Variant(42), new Variant(91), new Variant(978), new Variant(307), new Variant(786))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(44), 42L, 42, new Variant(91), new Variant(978), new Variant
                                (307), new Variant(786));
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
        on(0x227).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(30))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Copy(new Variant(30));
                    }
                });
    }

    @Test
    public void test_Copy_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x227).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(785), new Variant(298))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Copy(new Variant(785), new Variant(298));
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
        on(0x80010000).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("RDaKfMXpEY"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAx_CodeName("RDaKfMXpEY");
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
        on(0x27d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(250))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Move(new Variant(250));
                    }
                });
    }

    @Test
    public void test_Move_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x27d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(249), new Variant(727))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Move(new Variant(249), new Variant(727));
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
        on(0x6e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("RmZErTMxcI"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxName("RmZErTMxcI");
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
        on(0x274).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("roRKWHRcWB"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnDoubleClick("roRKWHRcWB");
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
        on(0x407).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("XWGTWkHNSw"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnSheetActivate("XWGTWkHNSw");
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
        on(0x439).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("LMjuZehFzI"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnSheetDeactivate("LMjuZehFzI");
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
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(15))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(15));
                    }
                });
    }

    @Test
    public void test_PrintOut_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(513), new Variant(871))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(513), new Variant(871));
                    }
                });
    }

    @Test
    public void test_PrintOut_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(345), new Variant(270), new
                Variant(207))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(345), new Variant(270), new Variant(207));
                    }
                });
    }

    @Test
    public void test_PrintOut_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(827), new Variant(611), new
                Variant(872), new Variant(156))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(827), new Variant(611), new Variant(872), new Variant(156));
                    }
                });
    }

    @Test
    public void test_PrintOut_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(592), new Variant(856), new
                Variant(658), new Variant(671), new Variant(325))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(592), new Variant(856), new Variant(658), new Variant(671),
                                new Variant(325));
                    }
                });
    }

    @Test
    public void test_PrintOut_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(375), new Variant(841), new
                Variant(541), new Variant(316), new Variant(58), new Variant(916))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(375), new Variant(841), new Variant(541), new Variant(316),
                                new Variant(58), new Variant(916));
                    }
                });
    }

    @Test
    public void test_PrintOut_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(22), new Variant(704), new Variant
                (416), new Variant(517), new Variant(51), new Variant(665), new Variant(922))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(22), new Variant(704), new Variant(416), new Variant(517), new
                                Variant(51), new Variant(665), new Variant(922));
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
        on(0x119).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(989))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintPreview(new Variant(989));
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
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(124))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect(new Variant(124));
                    }
                });
    }

    @Test
    public void test_Protect_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(638), new Variant(123))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect(new Variant(638), new Variant(123));
                    }
                });
    }

    @Test
    public void test_Protect_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(699), new Variant(78), new Variant
                (285))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect(new Variant(699), new Variant(78), new Variant(285));
                    }
                });
    }

    @Test
    public void test_Protect_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(600), new Variant(305), new
                Variant(121), new Variant(33))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect(new Variant(600), new Variant(305), new Variant(121), new Variant(33));
                    }
                });
    }

    @Test
    public void test_Protect_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(182), new Variant(860), new
                Variant(512), new Variant(761), new Variant(99))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect(new Variant(182), new Variant(860), new Variant(512), new Variant(761), new
                                Variant(99));
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
    public void test__Dummy23_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10017).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy23();
                    }
                });
    }

    @Test
    public void test_SaveAs_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("ukXHYgVcvV"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("ukXHYgVcvV");
                    }
                });
    }

    @Test
    public void test_SaveAs_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("ZuEKlZDVXJ"), new Variant(661))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("ZuEKlZDVXJ", new Variant(661));
                    }
                });
    }

    @Test
    public void test_SaveAs_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("bWgfsOCBvd"), new Variant(842),
                new Variant(465))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("bWgfsOCBvd", new Variant(842), new Variant(465));
                    }
                });
    }

    @Test
    public void test_SaveAs_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("djoapoasyd"), new Variant(669),
                new Variant(993), new Variant(461))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("djoapoasyd", new Variant(669), new Variant(993), new Variant(461));
                    }
                });
    }

    @Test
    public void test_SaveAs_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("SXTEnuogij"), new Variant(983),
                new Variant(119), new Variant(569), new Variant(466))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("SXTEnuogij", new Variant(983), new Variant(119), new Variant(569), new
                                Variant(466));
                    }
                });
    }

    @Test
    public void test_SaveAs_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("zlXHHwXxYn"), new Variant(413),
                new Variant(538), new Variant(823), new Variant(731), new Variant(518))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("zlXHHwXxYn", new Variant(413), new Variant(538), new Variant(823), new
                                Variant(731), new Variant(518));
                    }
                });
    }

    @Test
    public void test_SaveAs_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("LMqaSsxmWa"), new Variant(688),
                new Variant(670), new Variant(913), new Variant(726), new Variant(356), new Variant(924))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("LMqaSsxmWa", new Variant(688), new Variant(670), new Variant(913), new
                                Variant(726), new Variant(356), new Variant(924));
                    }
                });
    }

    @Test
    public void test_SaveAs_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("aQwwwuRXkq"), new Variant(826),
                new Variant(402), new Variant(165), new Variant(367), new Variant(496), new Variant(521), new Variant
                        (488))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("aQwwwuRXkq", new Variant(826), new Variant(402), new Variant(165), new
                                Variant(367), new Variant(496), new Variant(521), new Variant(488));
                    }
                });
    }

    @Test
    public void test_SaveAs_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("wSsQjREgLW"), new Variant(849),
                new Variant(565), new Variant(62), new Variant(565), new Variant(625), new Variant(490), new Variant
                        (843), new Variant(858))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("wSsQjREgLW", new Variant(849), new Variant(565), new Variant(62), new
                                Variant(565), new Variant(625), new Variant(490), new Variant(843), new Variant(858));
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
        on(0xeb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(383))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Select(new Variant(383));
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
        on(0x11d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(607))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Unprotect(new Variant(607));
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
        on(0x97).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(499))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ApplyDataLabels(42, new Variant(499));
                    }
                });
    }

    @Test
    public void test_ApplyDataLabels_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x97).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(436), new Variant
                (372))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ApplyDataLabels(42, new Variant(436), new Variant(372));
                    }
                });
    }

    @Test
    public void test_ApplyDataLabels_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x97).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(69), new Variant
                (676), new Variant(493))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ApplyDataLabels(42, new Variant(69), new Variant(676), new Variant(493));
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
        on(0x2f8).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(420))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Arcs(new Variant(420));
                    }
                });
    }

    @Test
    public void test_getAxArea3DGroup_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<ChartGroup>() {
                    @Override
                    public ChartGroup invoke() throws ActiveXException {
                        return component.getAxArea3DGroup();
                    }
                });
    }

    @Test
    public void test_AreaGroups_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.AreaGroups();
                    }
                });
    }

    @Test
    public void test_AreaGroups_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(31))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.AreaGroups(new Variant(31));
                    }
                });
    }

    @Test
    public void test_AutoFormat_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x72).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AutoFormat(42);
                    }
                });
    }

    @Test
    public void test_AutoFormat_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x72).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(864))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AutoFormat(42, new Variant(864));
                    }
                });
    }

    @Test
    public void test_getAxAutoScaling_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxAutoScaling();
                    }
                });
    }

    @Test
    public void test_setAxAutoScaling_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxAutoScaling(false);
                    }
                });
    }

    @Test
    public void test_Axes_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x17).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(919), new Variant(42))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Axes(new Variant(919), 42);
                    }
                });
    }

    @Test
    public void test_SetBackgroundPicture_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x4a4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("irVmKTbZur"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SetBackgroundPicture("irVmKTbZur");
                    }
                });
    }

    @Test
    public void test_getAxBar3DGroup_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x12).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<ChartGroup>() {
                    @Override
                    public ChartGroup invoke() throws ActiveXException {
                        return component.getAxBar3DGroup();
                    }
                });
    }

    @Test
    public void test_BarGroups_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.BarGroups();
                    }
                });
    }

    @Test
    public void test_BarGroups_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(305))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.BarGroups(new Variant(305));
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
        on(0x22d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(94))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Buttons(new Variant(94));
                    }
                });
    }

    @Test
    public void test_getAxChartArea_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x50).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<ChartArea>() {
                    @Override
                    public ChartArea invoke() throws ActiveXException {
                        return component.getAxChartArea();
                    }
                });
    }

    @Test
    public void test_ChartGroups_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x8).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.ChartGroups();
                    }
                });
    }

    @Test
    public void test_ChartGroups_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x8).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(55))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.ChartGroups(new Variant(55));
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
        on(0x424).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(814))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.ChartObjects(new Variant(814));
                    }
                });
    }

    @Test
    public void test_getAxChartTitle_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x51).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<ChartTitle>() {
                    @Override
                    public ChartTitle invoke() throws ActiveXException {
                        return component.getAxChartTitle();
                    }
                });
    }

    @Test
    public void test_ChartWizard_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ChartWizard();
                    }
                });
    }

    @Test
    public void test_ChartWizard_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xc4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(557))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ChartWizard(new Variant(557));
                    }
                });
    }

    @Test
    public void test_ChartWizard_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(3), new Variant(130))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ChartWizard(new Variant(3), new Variant(130));
                    }
                });
    }

    @Test
    public void test_ChartWizard_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(763), new Variant(275), new Variant
                (312))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ChartWizard(new Variant(763), new Variant(275), new Variant(312));
                    }
                });
    }

    @Test
    public void test_ChartWizard_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(94), new Variant(68), new Variant
                (35), new Variant(112))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ChartWizard(new Variant(94), new Variant(68), new Variant(35), new Variant(112));
                    }
                });
    }

    @Test
    public void test_ChartWizard_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(762), new Variant(561), new Variant
                (80), new Variant(789), new Variant(943))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ChartWizard(new Variant(762), new Variant(561), new Variant(80), new Variant(789),
                                new Variant(943));
                    }
                });
    }

    @Test
    public void test_ChartWizard_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(562), new Variant(504), new Variant
                (432), new Variant(148), new Variant(125), new Variant(255))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ChartWizard(new Variant(562), new Variant(504), new Variant(432), new Variant(148),
                                new Variant(125), new Variant(255));
                    }
                });
    }

    @Test
    public void test_ChartWizard_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(618), new Variant(347), new Variant
                (355), new Variant(16), new Variant(25), new Variant(444), new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ChartWizard(new Variant(618), new Variant(347), new Variant(355), new Variant(16),
                                new Variant(25), new Variant(444), new Variant(42));
                    }
                });
    }

    @Test
    public void test_ChartWizard_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(762), new Variant(679), new Variant
                (539), new Variant(381), new Variant(594), new Variant(445), new Variant(552), new Variant(975))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ChartWizard(new Variant(762), new Variant(679), new Variant(539), new Variant(381),
                                new Variant(594), new Variant(445), new Variant(552), new Variant(975));
                    }
                });
    }

    @Test
    public void test_ChartWizard_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(403), new Variant(804), new Variant
                (347), new Variant(310), new Variant(31), new Variant(316), new Variant(314), new Variant(908), new
                Variant(264))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ChartWizard(new Variant(403), new Variant(804), new Variant(347), new Variant(310),
                                new Variant(31), new Variant(316), new Variant(314), new Variant(908), new Variant
                                        (264));
                    }
                });
    }

    @Test
    public void test_ChartWizard_TenArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(845), new Variant(241), new Variant
                (274), new Variant(71), new Variant(651), new Variant(501), new Variant(925), new Variant(288), new
                Variant(127), new Variant(981))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ChartWizard(new Variant(845), new Variant(241), new Variant(274), new Variant(71),
                                new Variant(651), new Variant(501), new Variant(925), new Variant(288), new Variant
                                        (127), new Variant(981));
                    }
                });
    }

    @Test
    public void test_ChartWizard_ElevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(826), new Variant(728), new Variant
                (527), new Variant(197), new Variant(765), new Variant(853), new Variant(344), new Variant(680), new
                Variant(941), new Variant(984), new Variant(898))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ChartWizard(new Variant(826), new Variant(728), new Variant(527), new Variant(197),
                                new Variant(765), new Variant(853), new Variant(344), new Variant(680), new Variant
                                        (941), new Variant(984), new Variant(898));
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
        on(0x338).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(497))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.CheckBoxes(new Variant(497));
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
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(396))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(396));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(17), new Variant(530))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(17), new Variant(530));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(62), new Variant(355), new Variant
                (872))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(62), new Variant(355), new Variant(872));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(229), new Variant(386), new
                Variant(410), new Variant(27))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(229), new Variant(386), new Variant(410), new Variant(27));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(215), new Variant(70), new Variant
                (860), new Variant(993), new Variant(244))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(215), new Variant(70), new Variant(860), new Variant(993)
                                , new Variant(244));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(731), new Variant(232), new
                Variant(881), new Variant(526), new Variant(478), new Variant(573))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(731), new Variant(232), new Variant(881), new Variant
                                (526), new Variant(478), new Variant(573));
                    }
                });
    }

    @Test
    public void test_getAxColumn3DGroup_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x13).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<ChartGroup>() {
                    @Override
                    public ChartGroup invoke() throws ActiveXException {
                        return component.getAxColumn3DGroup();
                    }
                });
    }

    @Test
    public void test_ColumnGroups_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.ColumnGroups();
                    }
                });
    }

    @Test
    public void test_ColumnGroups_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(944))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.ColumnGroups(new Variant(944));
                    }
                });
    }

    @Test
    public void test_CopyPicture_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0xd5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42), new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CopyPicture(42, 42, 42);
                    }
                });
    }

    @Test
    public void test_getAxCorners_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x4f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Corners>() {
                    @Override
                    public Corners invoke() throws ActiveXException {
                        return component.getAxCorners();
                    }
                });
    }

    @Test
    public void test_CreatePublisher_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1ca).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(605), new Variant(42), new Variant
                (42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CreatePublisher(new Variant(605), 42, 42);
                    }
                });
    }

    @Test
    public void test_CreatePublisher_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1ca).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(688), new Variant(42), new Variant
                (42), new Variant(917))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CreatePublisher(new Variant(688), 42, 42, new Variant(917));
                    }
                });
    }

    @Test
    public void test_CreatePublisher_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1ca).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(565), new Variant(42), new Variant
                (42), new Variant(652), new Variant(673))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CreatePublisher(new Variant(565), 42, 42, new Variant(652), new Variant(673));
                    }
                });
    }

    @Test
    public void test_CreatePublisher_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1ca).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(282), new Variant(42), new Variant
                (42), new Variant(275), new Variant(512), new Variant(649))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CreatePublisher(new Variant(282), 42, 42, new Variant(275), new Variant(512), new
                                Variant(649));
                    }
                });
    }

    @Test
    public void test_CreatePublisher_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1ca).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(239), new Variant(42), new Variant
                (42), new Variant(858), new Variant(852), new Variant(963), new Variant(981))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CreatePublisher(new Variant(239), 42, 42, new Variant(858), new Variant(852), new
                                Variant(963), new Variant(981));
                    }
                });
    }

    @Test
    public void test_getAxDataTable_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x573).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<DataTable>() {
                    @Override
                    public DataTable invoke() throws ActiveXException {
                        return component.getAxDataTable();
                    }
                });
    }

    @Test
    public void test_getAxDepthPercent_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxDepthPercent();
                    }
                });
    }

    @Test
    public void test_setAxDepthPercent_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x30).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDepthPercent(42);
                    }
                });
    }

    @Test
    public void test_Deselect_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x460).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Deselect();
                    }
                });
    }

    @Test
    public void test_getAxDisplayBlanksAs_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxDisplayBlanksAs();
                    }
                });
    }

    @Test
    public void test_setAxDisplayBlanksAs_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDisplayBlanksAs(42);
                    }
                });
    }

    @Test
    public void test_DoughnutGroups_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.DoughnutGroups();
                    }
                });
    }

    @Test
    public void test_DoughnutGroups_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(834))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.DoughnutGroups(new Variant(834));
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
        on(0x304).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(935))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Drawings(new Variant(935));
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
        on(0x58).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(366))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.DrawingObjects(new Variant(366));
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
        on(0x344).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(629))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.DropDowns(new Variant(629));
                    }
                });
    }

    @Test
    public void test_getAxElevation_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x31).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxElevation();
                    }
                });
    }

    @Test
    public void test_setAxElevation_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x31).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxElevation(42);
                    }
                });
    }

    @Test
    public void test_Evaluate_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x1).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(726))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Evaluate(new Variant(726));
                    }
                });
    }

    @Test
    public void test__Evaluate_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xfffffffb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(575))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Evaluate(new Variant(575));
                    }
                });
    }

    @Test
    public void test_getAxFloor_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x53).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Floor>() {
                    @Override
                    public Floor invoke() throws ActiveXException {
                        return component.getAxFloor();
                    }
                });
    }

    @Test
    public void test_getAxGapDepth_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x32).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxGapDepth();
                    }
                });
    }

    @Test
    public void test_setAxGapDepth_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x32).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxGapDepth(42);
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
        on(0x342).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(905))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.GroupBoxes(new Variant(905));
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
        on(0x459).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(29))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.GroupObjects(new Variant(29));
                    }
                });
    }

    @Test
    public void test_getAxHasAxis_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x34).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxHasAxis();
                    }
                });
    }

    @Test
    public void test_getAxHasAxis_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x34).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(161))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxHasAxis(new Variant(161));
                    }
                });
    }

    @Test
    public void test_getAxHasAxis_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x34).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(239), new Variant(802))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxHasAxis(new Variant(239), new Variant(802));
                    }
                });
    }

    @Test
    public void test_setAxHasAxis_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x34).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(412))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHasAxis(new Variant(412));
                    }
                });
    }

    @Test
    public void test_setAxHasAxis_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x34).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(199), new Variant(756))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHasAxis(new Variant(199), new Variant(756));
                    }
                });
    }

    @Test
    public void test_setAxHasAxis_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x34).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(650), new Variant(879), new
                Variant(554))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHasAxis(new Variant(650), new Variant(879), new Variant(554));
                    }
                });
    }

    @Test
    public void test_getAxHasDataTable_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x574).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxHasDataTable();
                    }
                });
    }

    @Test
    public void test_setAxHasDataTable_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x574).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHasDataTable(false);
                    }
                });
    }

    @Test
    public void test_getAxHasLegend_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x35).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxHasLegend();
                    }
                });
    }

    @Test
    public void test_setAxHasLegend_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x35).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHasLegend(false);
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
    public void test_getAxHeightPercent_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x37).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxHeightPercent();
                    }
                });
    }

    @Test
    public void test_setAxHeightPercent_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x37).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHeightPercent(42);
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
        on(0x349).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(157))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Labels(new Variant(157));
                    }
                });
    }

    @Test
    public void test_getAxLegend_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x54).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Legend>() {
                    @Override
                    public Legend invoke() throws ActiveXException {
                        return component.getAxLegend();
                    }
                });
    }

    @Test
    public void test_getAxLine3DGroup_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x14).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<ChartGroup>() {
                    @Override
                    public ChartGroup invoke() throws ActiveXException {
                        return component.getAxLine3DGroup();
                    }
                });
    }

    @Test
    public void test_LineGroups_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.LineGroups();
                    }
                });
    }

    @Test
    public void test_LineGroups_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xc).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(801))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.LineGroups(new Variant(801));
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
        on(0x2ff).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(838))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Lines(new Variant(838));
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
        on(0x340).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(368))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.ListBoxes(new Variant(368));
                    }
                });
    }

    @Test
    public void test_Location_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x575).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyReturnsDispatchable(new Returns<ExcelChart>() {
                    @Override
                    public ExcelChart invoke() throws ActiveXException {
                        return component.Location(42);
                    }
                });
    }

    @Test
    public void test_Location_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x575).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(113))
                .verifyReturnsDispatchable(new Returns<ExcelChart>() {
                    @Override
                    public ExcelChart invoke() throws ActiveXException {
                        return component.Location(42, new Variant(113));
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
        on(0x31f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(138))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.OLEObjects(new Variant(138));
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
        on(0x33a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(169))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.OptionButtons(new Variant(169));
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
        on(0x321).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(685))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Ovals(new Variant(685));
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
        on(0xd3).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(482))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Paste(new Variant(482));
                    }
                });
    }

    @Test
    public void test_getAxPerspective_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x39).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxPerspective();
                    }
                });
    }

    @Test
    public void test_setAxPerspective_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x39).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPerspective(42);
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
        on(0x303).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(619))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Pictures(new Variant(619));
                    }
                });
    }

    @Test
    public void test_getAxPie3DGroup_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x15).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<ChartGroup>() {
                    @Override
                    public ChartGroup invoke() throws ActiveXException {
                        return component.getAxPie3DGroup();
                    }
                });
    }

    @Test
    public void test_PieGroups_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xd).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.PieGroups();
                    }
                });
    }

    @Test
    public void test_PieGroups_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xd).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(459))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.PieGroups(new Variant(459));
                    }
                });
    }

    @Test
    public void test_getAxPlotArea_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x55).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<PlotArea>() {
                    @Override
                    public PlotArea invoke() throws ActiveXException {
                        return component.getAxPlotArea();
                    }
                });
    }

    @Test
    public void test_getAxPlotVisibleOnly_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxPlotVisibleOnly();
                    }
                });
    }

    @Test
    public void test_setAxPlotVisibleOnly_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPlotVisibleOnly(false);
                    }
                });
    }

    @Test
    public void test_RadarGroups_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xf).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.RadarGroups();
                    }
                });
    }

    @Test
    public void test_RadarGroups_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xf).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(659))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.RadarGroups(new Variant(659));
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
        on(0x306).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(847))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Rectangles(new Variant(847));
                    }
                });
    }

    @Test
    public void test_getAxRightAngleAxes_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxRightAngleAxes();
                    }
                });
    }

    @Test
    public void test_setAxRightAngleAxes_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(892))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxRightAngleAxes(new Variant(892));
                    }
                });
    }

    @Test
    public void test_getAxRotation_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxRotation();
                    }
                });
    }

    @Test
    public void test_setAxRotation_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(825))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxRotation(new Variant(825));
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
        on(0x33e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(898))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.ScrollBars(new Variant(898));
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
        on(0x44).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(255))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.SeriesCollection(new Variant(255));
                    }
                });
    }

    @Test
    public void test_getAxSizeWithWindow_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxSizeWithWindow();
                    }
                });
    }

    @Test
    public void test_setAxSizeWithWindow_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSizeWithWindow(false);
                    }
                });
    }

    @Test
    public void test_getAxShowWindow_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x577).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxShowWindow();
                    }
                });
    }

    @Test
    public void test_setAxShowWindow_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x577).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxShowWindow(false);
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
        on(0x346).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(809))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Spinners(new Variant(809));
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
    public void test_getAxSurfaceGroup_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x16).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<ChartGroup>() {
                    @Override
                    public ChartGroup invoke() throws ActiveXException {
                        return component.getAxSurfaceGroup();
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
        on(0x309).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(596))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.TextBoxes(new Variant(596));
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
    public void test_ApplyCustomType_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x579).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(277))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ApplyCustomType(42, new Variant(277));
                    }
                });
    }

    @Test
    public void test_getAxWalls_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x56).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Walls>() {
                    @Override
                    public Walls invoke() throws ActiveXException {
                        return component.getAxWalls();
                    }
                });
    }

    @Test
    public void test_getAxWallsAndGridlines2D_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xd2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxWallsAndGridlines2D();
                    }
                });
    }

    @Test
    public void test_setAxWallsAndGridlines2D_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xd2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxWallsAndGridlines2D(false);
                    }
                });
    }

    @Test
    public void test_XYGroups_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.XYGroups();
                    }
                });
    }

    @Test
    public void test_XYGroups_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x10).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(929))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.XYGroups(new Variant(929));
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
    public void test_getAxPlotBy_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xca).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxPlotBy();
                    }
                });
    }

    @Test
    public void test_setAxPlotBy_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xca).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPlotBy(42);
                    }
                });
    }

    @Test
    public void test_CopyChartBuild_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x57c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CopyChartBuild();
                    }
                });
    }

    @Test
    public void test_getAxProtectFormatting_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x57d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxProtectFormatting();
                    }
                });
    }

    @Test
    public void test_setAxProtectFormatting_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x57d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxProtectFormatting(false);
                    }
                });
    }

    @Test
    public void test_getAxProtectData_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x57e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxProtectData();
                    }
                });
    }

    @Test
    public void test_setAxProtectData_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x57e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxProtectData(false);
                    }
                });
    }

    @Test
    public void test_getAxProtectGoalSeek_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x57f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxProtectGoalSeek();
                    }
                });
    }

    @Test
    public void test_setAxProtectGoalSeek_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x57f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxProtectGoalSeek(false);
                    }
                });
    }

    @Test
    public void test_getAxProtectSelection_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x580).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxProtectSelection();
                    }
                });
    }

    @Test
    public void test_setAxProtectSelection_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x580).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxProtectSelection(false);
                    }
                });
    }

    @Test
    public void test_GetChartElement_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x581).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42), new Variant
                (109), new Variant(113), new Variant(195))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetChartElement(42, 42, new Variant(109), new Variant(113), new Variant(195));
                    }
                });
    }

    @Test
    public void test_SetSourceData_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x585).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SetSourceData(getMock(Range.class));
                    }
                });
    }

    @Test
    public void test_SetSourceData_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x585).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (385))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SetSourceData(getMock(Range.class), new Variant(385));
                    }
                });
    }

    @Test
    public void test_Export_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x586).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("hqIwNHSTmR"))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Export("hqIwNHSTmR");
                    }
                });
    }

    @Test
    public void test_Export_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x586).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("EiwwBQqMct"), new Variant(349))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Export("EiwwBQqMct", new Variant(349));
                    }
                });
    }

    @Test
    public void test_Export_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x586).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("TQZEJxKBCS"), new Variant(266),
                new Variant(239))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Export("TQZEJxKBCS", new Variant(266), new Variant(239));
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

}