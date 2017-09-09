package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class ExcelChartTest extends ActiveXDispatchableTestBase {

    private ExcelChart component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new ExcelChart(axProxy);
        onProxy = true;
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(401), new Variant(689))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(401), new Variant(689));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(554))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(554));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(592))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(592));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(954), new Variant(109), new
                Variant(42L), new Variant(42L), new Variant(857))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(954), new Variant(109), 42L, 42L, new Variant(857));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(715), new
                Variant(42L), new Variant(42), new Variant(218), new Variant(120), new Variant(628), new Variant(747))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(715), 42L, 42, new Variant(218), new Variant(120), new
                                Variant(628), new Variant(747));
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
        on(0x227).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(397))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Copy(new Variant(397));
                    }
                });
    }

    @Test
    public void test_Copy_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x227).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(99), new Variant(437))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Copy(new Variant(99), new Variant(437));
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
        on(0x80010000).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("QPmoFPGZiV"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAx_CodeName("QPmoFPGZiV");
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
        on(0x27d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(815))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Move(new Variant(815));
                    }
                });
    }

    @Test
    public void test_Move_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x27d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(8), new Variant(167))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Move(new Variant(8), new Variant(167));
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
        on(0x6e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("NDWNLwKDed"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxName("NDWNLwKDed");
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
        on(0x274).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("GeaizvnKCW"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnDoubleClick("GeaizvnKCW");
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
        on(0x407).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("YWRcpKKbXp"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnSheetActivate("YWRcpKKbXp");
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
        on(0x439).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("ztHMSjmdlM"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnSheetDeactivate("ztHMSjmdlM");
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
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(115))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(115));
                    }
                });
    }

    @Test
    public void test_PrintOut_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(538), new Variant(946))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(538), new Variant(946));
                    }
                });
    }

    @Test
    public void test_PrintOut_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(350), new Variant(907), new
                Variant(623))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(350), new Variant(907), new Variant(623));
                    }
                });
    }

    @Test
    public void test_PrintOut_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(549), new Variant(543), new
                Variant(326), new Variant(177))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(549), new Variant(543), new Variant(326), new Variant(177));
                    }
                });
    }

    @Test
    public void test_PrintOut_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(631), new Variant(127), new
                Variant(191), new Variant(561), new Variant(96))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(631), new Variant(127), new Variant(191), new Variant(561),
                                new Variant(96));
                    }
                });
    }

    @Test
    public void test_PrintOut_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(837), new Variant(375), new
                Variant(801), new Variant(687), new Variant(166), new Variant(439))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(837), new Variant(375), new Variant(801), new Variant(687),
                                new Variant(166), new Variant(439));
                    }
                });
    }

    @Test
    public void test_PrintOut_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(61), new Variant(741), new Variant
                (447), new Variant(377), new Variant(297), new Variant(822), new Variant(497))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(61), new Variant(741), new Variant(447), new Variant(377), new
                                Variant(297), new Variant(822), new Variant(497));
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
        on(0x119).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(140))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintPreview(new Variant(140));
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
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(77))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect(new Variant(77));
                    }
                });
    }

    @Test
    public void test_Protect_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(607), new Variant(503))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect(new Variant(607), new Variant(503));
                    }
                });
    }

    @Test
    public void test_Protect_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(690), new Variant(214), new
                Variant(824))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect(new Variant(690), new Variant(214), new Variant(824));
                    }
                });
    }

    @Test
    public void test_Protect_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(387), new Variant(831), new
                Variant(46), new Variant(936))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect(new Variant(387), new Variant(831), new Variant(46), new Variant(936));
                    }
                });
    }

    @Test
    public void test_Protect_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(934), new Variant(920), new
                Variant(563), new Variant(151), new Variant(662))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect(new Variant(934), new Variant(920), new Variant(563), new Variant(151), new
                                Variant(662));
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
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("JfjSKpHfWZ"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("JfjSKpHfWZ");
                    }
                });
    }

    @Test
    public void test_SaveAs_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("PfmfCnOmFV"), new Variant(390))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("PfmfCnOmFV", new Variant(390));
                    }
                });
    }

    @Test
    public void test_SaveAs_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("KJLHRmjUmW"), new Variant(893),
                new Variant(109))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("KJLHRmjUmW", new Variant(893), new Variant(109));
                    }
                });
    }

    @Test
    public void test_SaveAs_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("eQLftSyqva"), new Variant(457),
                new Variant(262), new Variant(17))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("eQLftSyqva", new Variant(457), new Variant(262), new Variant(17));
                    }
                });
    }

    @Test
    public void test_SaveAs_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("ErkCMtnMCW"), new Variant(860),
                new Variant(304), new Variant(686), new Variant(91))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("ErkCMtnMCW", new Variant(860), new Variant(304), new Variant(686), new
                                Variant(91));
                    }
                });
    }

    @Test
    public void test_SaveAs_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("RVZHHvQBWy"), new Variant(652),
                new Variant(912), new Variant(509), new Variant(792), new Variant(299))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("RVZHHvQBWy", new Variant(652), new Variant(912), new Variant(509), new
                                Variant(792), new Variant(299));
                    }
                });
    }

    @Test
    public void test_SaveAs_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("cPtVRkFizh"), new Variant(689),
                new Variant(887), new Variant(281), new Variant(998), new Variant(745), new Variant(525))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("cPtVRkFizh", new Variant(689), new Variant(887), new Variant(281), new
                                Variant(998), new Variant(745), new Variant(525));
                    }
                });
    }

    @Test
    public void test_SaveAs_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("QmQHbPyAhO"), new Variant(51),
                new Variant(345), new Variant(619), new Variant(349), new Variant(772), new Variant(87), new Variant
                        (153))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("QmQHbPyAhO", new Variant(51), new Variant(345), new Variant(619), new
                                Variant(349), new Variant(772), new Variant(87), new Variant(153));
                    }
                });
    }

    @Test
    public void test_SaveAs_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("XHqEyuQPxI"), new Variant(499),
                new Variant(920), new Variant(159), new Variant(417), new Variant(92), new Variant(321), new Variant
                        (339), new Variant(658))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("XHqEyuQPxI", new Variant(499), new Variant(920), new Variant(159), new
                                Variant(417), new Variant(92), new Variant(321), new Variant(339), new Variant(658));
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
        on(0xeb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(34))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Select(new Variant(34));
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
        on(0x11d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(485))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Unprotect(new Variant(485));
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
        on(0x97).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(414))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ApplyDataLabels(42, new Variant(414));
                    }
                });
    }

    @Test
    public void test_ApplyDataLabels_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x97).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(592), new Variant
                (313))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ApplyDataLabels(42, new Variant(592), new Variant(313));
                    }
                });
    }

    @Test
    public void test_ApplyDataLabels_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x97).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(953), new Variant
                (761), new Variant(637))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ApplyDataLabels(42, new Variant(953), new Variant(761), new Variant(637));
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
        on(0x2f8).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(220))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Arcs(new Variant(220));
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
        on(0x9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(684))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.AreaGroups(new Variant(684));
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
        on(0x72).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(657))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AutoFormat(42, new Variant(657));
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
        on(0x17).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(72), new Variant(42))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Axes(new Variant(72), 42);
                    }
                });
    }

    @Test
    public void test_SetBackgroundPicture_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x4a4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("WNHehTbtUT"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SetBackgroundPicture("WNHehTbtUT");
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
        on(0xa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(261))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.BarGroups(new Variant(261));
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
        on(0x22d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(726))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Buttons(new Variant(726));
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
        on(0x8).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(713))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.ChartGroups(new Variant(713));
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
        on(0x424).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(970))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.ChartObjects(new Variant(970));
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
        on(0xc4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(656))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ChartWizard(new Variant(656));
                    }
                });
    }

    @Test
    public void test_ChartWizard_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(847), new Variant(16))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ChartWizard(new Variant(847), new Variant(16));
                    }
                });
    }

    @Test
    public void test_ChartWizard_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(234), new Variant(58), new Variant
                (92))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ChartWizard(new Variant(234), new Variant(58), new Variant(92));
                    }
                });
    }

    @Test
    public void test_ChartWizard_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(23), new Variant(347), new Variant
                (155), new Variant(836))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ChartWizard(new Variant(23), new Variant(347), new Variant(155), new Variant(836));
                    }
                });
    }

    @Test
    public void test_ChartWizard_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(873), new Variant(291), new Variant
                (485), new Variant(152), new Variant(623))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ChartWizard(new Variant(873), new Variant(291), new Variant(485), new Variant(152),
                                new Variant(623));
                    }
                });
    }

    @Test
    public void test_ChartWizard_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(460), new Variant(88), new Variant
                (449), new Variant(847), new Variant(272), new Variant(540))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ChartWizard(new Variant(460), new Variant(88), new Variant(449), new Variant(847),
                                new Variant(272), new Variant(540));
                    }
                });
    }

    @Test
    public void test_ChartWizard_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(268), new Variant(72), new Variant
                (373), new Variant(162), new Variant(400), new Variant(533), new Variant(432))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ChartWizard(new Variant(268), new Variant(72), new Variant(373), new Variant(162),
                                new Variant(400), new Variant(533), new Variant(432));
                    }
                });
    }

    @Test
    public void test_ChartWizard_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(40), new Variant(272), new Variant
                (236), new Variant(333), new Variant(447), new Variant(516), new Variant(585), new Variant(653))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ChartWizard(new Variant(40), new Variant(272), new Variant(236), new Variant(333),
                                new Variant(447), new Variant(516), new Variant(585), new Variant(653));
                    }
                });
    }

    @Test
    public void test_ChartWizard_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(378), new Variant(154), new Variant
                (204), new Variant(952), new Variant(4), new Variant(314), new Variant(211), new Variant(922), new
                Variant(966))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ChartWizard(new Variant(378), new Variant(154), new Variant(204), new Variant(952),
                                new Variant(4), new Variant(314), new Variant(211), new Variant(922), new Variant(966));
                    }
                });
    }

    @Test
    public void test_ChartWizard_TenArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(327), new Variant(813), new Variant
                (682), new Variant(741), new Variant(633), new Variant(957), new Variant(445), new Variant(948), new
                Variant(559), new Variant(319))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ChartWizard(new Variant(327), new Variant(813), new Variant(682), new Variant(741),
                                new Variant(633), new Variant(957), new Variant(445), new Variant(948), new Variant
                                        (559), new Variant(319));
                    }
                });
    }

    @Test
    public void test_ChartWizard_ElevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(666), new Variant(491), new Variant
                (689), new Variant(762), new Variant(270), new Variant(868), new Variant(548), new Variant(698), new
                Variant(895), new Variant(13), new Variant(391))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ChartWizard(new Variant(666), new Variant(491), new Variant(689), new Variant(762),
                                new Variant(270), new Variant(868), new Variant(548), new Variant(698), new Variant
                                        (895), new Variant(13), new Variant(391));
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
        on(0x338).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(712))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.CheckBoxes(new Variant(712));
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
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(134))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(134));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(887), new Variant(691))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(887), new Variant(691));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(553), new Variant(582), new
                Variant(882))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(553), new Variant(582), new Variant(882));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(71), new Variant(40), new Variant
                (465), new Variant(163))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(71), new Variant(40), new Variant(465), new Variant(163));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(945), new Variant(776), new
                Variant(385), new Variant(883), new Variant(936))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(945), new Variant(776), new Variant(385), new Variant
                                (883), new Variant(936));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(555), new Variant(284), new
                Variant(573), new Variant(30), new Variant(752), new Variant(456))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(555), new Variant(284), new Variant(573), new Variant(30)
                                , new Variant(752), new Variant(456));
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
        on(0xb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(563))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.ColumnGroups(new Variant(563));
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
        on(0x1ca).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(971), new Variant(42), new Variant
                (42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CreatePublisher(new Variant(971), 42, 42);
                    }
                });
    }

    @Test
    public void test_CreatePublisher_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1ca).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(892), new Variant(42), new Variant
                (42), new Variant(798))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CreatePublisher(new Variant(892), 42, 42, new Variant(798));
                    }
                });
    }

    @Test
    public void test_CreatePublisher_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1ca).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(213), new Variant(42), new Variant
                (42), new Variant(717), new Variant(520))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CreatePublisher(new Variant(213), 42, 42, new Variant(717), new Variant(520));
                    }
                });
    }

    @Test
    public void test_CreatePublisher_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1ca).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(612), new Variant(42), new Variant
                (42), new Variant(96), new Variant(220), new Variant(58))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CreatePublisher(new Variant(612), 42, 42, new Variant(96), new Variant(220), new
                                Variant(58));
                    }
                });
    }

    @Test
    public void test_CreatePublisher_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1ca).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(690), new Variant(42), new Variant
                (42), new Variant(407), new Variant(57), new Variant(707), new Variant(606))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CreatePublisher(new Variant(690), 42, 42, new Variant(407), new Variant(57), new
                                Variant(707), new Variant(606));
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
        on(0xe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(137))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.DoughnutGroups(new Variant(137));
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
        on(0x304).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(47))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Drawings(new Variant(47));
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
        on(0x58).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(356))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.DrawingObjects(new Variant(356));
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
        on(0x344).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(971))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.DropDowns(new Variant(971));
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
        on(0x1).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(982))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Evaluate(new Variant(982));
                    }
                });
    }

    @Test
    public void test__Evaluate_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xfffffffb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(26))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Evaluate(new Variant(26));
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
        on(0x342).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(366))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.GroupBoxes(new Variant(366));
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
        on(0x459).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(108))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.GroupObjects(new Variant(108));
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
        on(0x34).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(239))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxHasAxis(new Variant(239));
                    }
                });
    }

    @Test
    public void test_getAxHasAxis_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x34).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(547), new Variant(965))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxHasAxis(new Variant(547), new Variant(965));
                    }
                });
    }

    @Test
    public void test_setAxHasAxis_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x34).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(815))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHasAxis(new Variant(815));
                    }
                });
    }

    @Test
    public void test_setAxHasAxis_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x34).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(9), new Variant(381))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHasAxis(new Variant(9), new Variant(381));
                    }
                });
    }

    @Test
    public void test_setAxHasAxis_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x34).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(127), new Variant(388), new
                Variant(270))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHasAxis(new Variant(127), new Variant(388), new Variant(270));
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
        on(0x349).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(874))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Labels(new Variant(874));
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
        on(0xc).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(655))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.LineGroups(new Variant(655));
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
        on(0x2ff).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(501))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Lines(new Variant(501));
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
        on(0x340).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(616))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.ListBoxes(new Variant(616));
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
        on(0x575).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(39))
                .verifyReturnsDispatchable(new Returns<ExcelChart>() {
                    @Override
                    public ExcelChart invoke() throws ActiveXException {
                        return component.Location(42, new Variant(39));
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
        on(0x31f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(225))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.OLEObjects(new Variant(225));
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
        on(0x33a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(151))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.OptionButtons(new Variant(151));
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
        on(0x321).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(979))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Ovals(new Variant(979));
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
        on(0xd3).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(751))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Paste(new Variant(751));
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
        on(0x303).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(537))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Pictures(new Variant(537));
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
        on(0xd).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(86))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.PieGroups(new Variant(86));
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
        on(0xf).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(54))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.RadarGroups(new Variant(54));
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
        on(0x306).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(283))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Rectangles(new Variant(283));
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
        on(0x3a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(661))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxRightAngleAxes(new Variant(661));
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
        on(0x3b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(303))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxRotation(new Variant(303));
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
        on(0x33e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(269))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.ScrollBars(new Variant(269));
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
        on(0x44).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(718))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.SeriesCollection(new Variant(718));
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
        on(0x346).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(203))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Spinners(new Variant(203));
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
        on(0x309).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(534))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.TextBoxes(new Variant(534));
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
        on(0x579).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(454))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ApplyCustomType(42, new Variant(454));
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
        on(0x10).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(974))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.XYGroups(new Variant(974));
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
                (600), new Variant(480), new Variant(637))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetChartElement(42, 42, new Variant(600), new Variant(480), new Variant(637));
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
                (510))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SetSourceData(getMock(Range.class), new Variant(510));
                    }
                });
    }

    @Test
    public void test_Export_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x586).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("NBTwzSzvwv"))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Export("NBTwzSzvwv");
                    }
                });
    }

    @Test
    public void test_Export_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x586).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("zWUoPhwdcv"), new Variant(431))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Export("zWUoPhwdcv", new Variant(431));
                    }
                });
    }

    @Test
    public void test_Export_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x586).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("fbMHgjMDty"), new Variant(171),
                new Variant(647))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Export("fbMHgjMDty", new Variant(171), new Variant(647));
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
    public void test_Deactivate_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5fa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Deactivate();
                    }
                });
    }

    @Test
    public void test_Resize_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x100).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Resize();
                    }
                });
    }

    @Test
    public void test_MouseDown_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5fb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42), new Variant
                (42), new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.MouseDown(42, 42, 42, 42);
                    }
                });
    }

    @Test
    public void test_MouseUp_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5fc).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42), new Variant
                (42), new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.MouseUp(42, 42, 42, 42);
                    }
                });
    }

    @Test
    public void test_MouseMove_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5fd).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42), new Variant
                (42), new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.MouseMove(42, 42, 42, 42);
                    }
                });
    }

    @Test
    public void test_BeforeRightClick_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(377))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.BeforeRightClick(new Variant(377));
                    }
                });
    }

    @Test
    public void test_DragPlot_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5ff).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.DragPlot();
                    }
                });
    }

    @Test
    public void test_DragOver_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x600).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.DragOver();
                    }
                });
    }

    @Test
    public void test_BeforeDoubleClick_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x601).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42), new Variant
                (42), new Variant(298))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.BeforeDoubleClick(42, 42, 42, new Variant(298));
                    }
                });
    }

    @Test
    public void test_SeriesChange_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x602).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SeriesChange(42, 42);
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

}