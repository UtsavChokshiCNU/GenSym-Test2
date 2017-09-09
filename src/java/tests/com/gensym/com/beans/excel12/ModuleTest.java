package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class ModuleTest extends ActiveXDispatchableTestBase {

    private Module component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new Module(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(692), new Variant(256))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(692), new Variant(256));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(190))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(190));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(356))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(356));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(873), new Variant(235), new
                Variant(42L), new Variant(42L), new Variant(753))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(873), new Variant(235), 42L, 42L, new Variant(753));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(495), new
                Variant(42L), new Variant(42), new Variant(726), new Variant(140), new Variant(277), new Variant(273))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(495), 42L, 42, new Variant(726), new Variant(140), new
                                Variant(277), new Variant(273));
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
        on(0x227).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(226))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Copy(new Variant(226));
                    }
                });
    }

    @Test
    public void test_Copy_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x227).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(142), new Variant(863))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Copy(new Variant(142), new Variant(863));
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
        on(0x80010000).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("yCbZGgBFCA"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAx_CodeName("yCbZGgBFCA");
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
        on(0x27d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(820))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Move(new Variant(820));
                    }
                });
    }

    @Test
    public void test_Move_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x27d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(234), new Variant(21))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Move(new Variant(234), new Variant(21));
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
        on(0x6e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("ewqKwElSqB"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxName("ewqKwElSqB");
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
        on(0x274).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("SNdoNmTSPZ"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnDoubleClick("SNdoNmTSPZ");
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
        on(0x407).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("AeKWbmyORR"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnSheetActivate("AeKWbmyORR");
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
        on(0x439).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("AqSbaFuojD"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnSheetDeactivate("AqSbaFuojD");
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
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(860))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(860));
                    }
                });
    }

    @Test
    public void test_PrintOut_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(104), new Variant(859))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(104), new Variant(859));
                    }
                });
    }

    @Test
    public void test_PrintOut_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(36), new Variant(538), new Variant
                (912))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(36), new Variant(538), new Variant(912));
                    }
                });
    }

    @Test
    public void test_PrintOut_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(852), new Variant(869), new
                Variant(320), new Variant(651))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(852), new Variant(869), new Variant(320), new Variant(651));
                    }
                });
    }

    @Test
    public void test_PrintOut_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(351), new Variant(556), new
                Variant(103), new Variant(802), new Variant(806))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(351), new Variant(556), new Variant(103), new Variant(802),
                                new Variant(806));
                    }
                });
    }

    @Test
    public void test_PrintOut_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(264), new Variant(360), new
                Variant(169), new Variant(786), new Variant(14), new Variant(428))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(264), new Variant(360), new Variant(169), new Variant(786),
                                new Variant(14), new Variant(428));
                    }
                });
    }

    @Test
    public void test_PrintOut_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(155), new Variant(158), new
                Variant(739), new Variant(899), new Variant(694), new Variant(426), new Variant(398))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(155), new Variant(158), new Variant(739), new Variant(899),
                                new Variant(694), new Variant(426), new Variant(398));
                    }
                });
    }

    @Test
    public void test__Dummy18_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10012).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy18();
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
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(492))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect(new Variant(492));
                    }
                });
    }

    @Test
    public void test_Protect_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(464), new Variant(604))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect(new Variant(464), new Variant(604));
                    }
                });
    }

    @Test
    public void test_Protect_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(393), new Variant(27), new Variant
                (333))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect(new Variant(393), new Variant(27), new Variant(333));
                    }
                });
    }

    @Test
    public void test_Protect_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(920), new Variant(554), new
                Variant(96), new Variant(766))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect(new Variant(920), new Variant(554), new Variant(96), new Variant(766));
                    }
                });
    }

    @Test
    public void test_Protect_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(784), new Variant(618), new
                Variant(828), new Variant(192), new Variant(103))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect(new Variant(784), new Variant(618), new Variant(828), new Variant(192), new
                                Variant(103));
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
    public void test__Dummy21_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10015).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy21();
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
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("SDkSCgGxLN"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("SDkSCgGxLN");
                    }
                });
    }

    @Test
    public void test_SaveAs_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("VqiTlwfGBr"), new Variant(665))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("VqiTlwfGBr", new Variant(665));
                    }
                });
    }

    @Test
    public void test_SaveAs_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("wocFTFpjXu"), new Variant(399),
                new Variant(862))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("wocFTFpjXu", new Variant(399), new Variant(862));
                    }
                });
    }

    @Test
    public void test_SaveAs_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("iOGdbTeDRV"), new Variant(256),
                new Variant(267), new Variant(333))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("iOGdbTeDRV", new Variant(256), new Variant(267), new Variant(333));
                    }
                });
    }

    @Test
    public void test_SaveAs_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("PgpZbuXAek"), new Variant(939),
                new Variant(604), new Variant(707), new Variant(127))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("PgpZbuXAek", new Variant(939), new Variant(604), new Variant(707), new
                                Variant(127));
                    }
                });
    }

    @Test
    public void test_SaveAs_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("LRUYnURSTq"), new Variant(472),
                new Variant(87), new Variant(851), new Variant(149), new Variant(934))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("LRUYnURSTq", new Variant(472), new Variant(87), new Variant(851), new
                                Variant(149), new Variant(934));
                    }
                });
    }

    @Test
    public void test_SaveAs_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("jkvOsEDcIe"), new Variant(436),
                new Variant(957), new Variant(385), new Variant(89), new Variant(559), new Variant(857))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("jkvOsEDcIe", new Variant(436), new Variant(957), new Variant(385), new
                                Variant(89), new Variant(559), new Variant(857));
                    }
                });
    }

    @Test
    public void test_SaveAs_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("nvxCnuplJK"), new Variant(966),
                new Variant(218), new Variant(720), new Variant(852), new Variant(480), new Variant(479), new Variant
                        (312))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("nvxCnuplJK", new Variant(966), new Variant(218), new Variant(720), new
                                Variant(852), new Variant(480), new Variant(479), new Variant(312));
                    }
                });
    }

    @Test
    public void test_SaveAs_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("LKmgZNFUiR"), new Variant(697),
                new Variant(774), new Variant(368), new Variant(211), new Variant(230), new Variant(306), new Variant
                        (881), new Variant(341))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("LKmgZNFUiR", new Variant(697), new Variant(774), new Variant(368), new
                                Variant(211), new Variant(230), new Variant(306), new Variant(881), new Variant(341));
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
        on(0xeb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(670))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Select(new Variant(670));
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
        on(0x11d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(185))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Unprotect(new Variant(185));
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
    public void test_InsertFile_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x248).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(751))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.InsertFile(new Variant(751));
                    }
                });
    }

    @Test
    public void test_InsertFile_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x248).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(34), new Variant(382))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.InsertFile(new Variant(34), new Variant(382));
                    }
                });
    }

}