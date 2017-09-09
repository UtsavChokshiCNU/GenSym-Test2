package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class ExcelSheetTest extends ActiveXDispatchableTestBase {

    private ExcelSheet component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new ExcelSheet(axProxy);
        onProxy = true;
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(962), new Variant(615))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(962), new Variant(615));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(906))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(906));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(151))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(151));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(261), new Variant(681), new
                Variant(42L), new Variant(42L), new Variant(231))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(261), new Variant(681), 42L, 42L, new Variant(231));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(442), new
                Variant(42L), new Variant(42), new Variant(117), new Variant(41), new Variant(187), new Variant(275))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(442), 42L, 42, new Variant(117), new Variant(41), new
                                Variant(187), new Variant(275));
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
        on(0x227).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(28))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Copy(new Variant(28));
                    }
                });
    }

    @Test
    public void test_Copy_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x227).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(95), new Variant(906))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Copy(new Variant(95), new Variant(906));
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
        on(0x80010000).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("bxrxOaOcDY"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAx_CodeName("bxrxOaOcDY");
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
        on(0x27d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(940))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Move(new Variant(940));
                    }
                });
    }

    @Test
    public void test_Move_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x27d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(227), new Variant(777))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Move(new Variant(227), new Variant(777));
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
        on(0x6e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("hYLyRaRuer"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxName("hYLyRaRuer");
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
        on(0x274).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("XJjHFFiMUB"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnDoubleClick("XJjHFFiMUB");
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
        on(0x407).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("PqDOidZzJT"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnSheetActivate("PqDOidZzJT");
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
        on(0x439).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("XKdrBCPJSi"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnSheetDeactivate("XKdrBCPJSi");
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
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(863))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(863));
                    }
                });
    }

    @Test
    public void test_PrintOut_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(994), new Variant(205))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(994), new Variant(205));
                    }
                });
    }

    @Test
    public void test_PrintOut_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(460), new Variant(697), new
                Variant(469))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(460), new Variant(697), new Variant(469));
                    }
                });
    }

    @Test
    public void test_PrintOut_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(161), new Variant(473), new
                Variant(61), new Variant(965))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(161), new Variant(473), new Variant(61), new Variant(965));
                    }
                });
    }

    @Test
    public void test_PrintOut_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(69), new Variant(424), new Variant
                (637), new Variant(587), new Variant(461))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(69), new Variant(424), new Variant(637), new Variant(587), new
                                Variant(461));
                    }
                });
    }

    @Test
    public void test_PrintOut_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(468), new Variant(998), new
                Variant(457), new Variant(643), new Variant(723), new Variant(911))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(468), new Variant(998), new Variant(457), new Variant(643),
                                new Variant(723), new Variant(911));
                    }
                });
    }

    @Test
    public void test_PrintOut_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(727), new Variant(857), new
                Variant(175), new Variant(765), new Variant(35), new Variant(674), new Variant(670))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(727), new Variant(857), new Variant(175), new Variant(765),
                                new Variant(35), new Variant(674), new Variant(670));
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
        on(0x119).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(828))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintPreview(new Variant(828));
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
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(572))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect(new Variant(572));
                    }
                });
    }

    @Test
    public void test_Protect_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(150), new Variant(859))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect(new Variant(150), new Variant(859));
                    }
                });
    }

    @Test
    public void test_Protect_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(895), new Variant(91), new Variant
                (444))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect(new Variant(895), new Variant(91), new Variant(444));
                    }
                });
    }

    @Test
    public void test_Protect_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(326), new Variant(432), new
                Variant(407), new Variant(153))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect(new Variant(326), new Variant(432), new Variant(407), new Variant(153));
                    }
                });
    }

    @Test
    public void test_Protect_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(951), new Variant(532), new
                Variant(923), new Variant(439), new Variant(610))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect(new Variant(951), new Variant(532), new Variant(923), new Variant(439), new
                                Variant(610));
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
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("ijWJinUjOv"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("ijWJinUjOv");
                    }
                });
    }

    @Test
    public void test_SaveAs_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("WNUIzquIIn"), new Variant(886))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("WNUIzquIIn", new Variant(886));
                    }
                });
    }

    @Test
    public void test_SaveAs_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("roclGTVzHU"), new Variant(942),
                new Variant(242))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("roclGTVzHU", new Variant(942), new Variant(242));
                    }
                });
    }

    @Test
    public void test_SaveAs_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("RTXfrGVWNu"), new Variant(663),
                new Variant(611), new Variant(591))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("RTXfrGVWNu", new Variant(663), new Variant(611), new Variant(591));
                    }
                });
    }

    @Test
    public void test_SaveAs_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("YLBhSivMxo"), new Variant(204),
                new Variant(106), new Variant(669), new Variant(571))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("YLBhSivMxo", new Variant(204), new Variant(106), new Variant(669), new
                                Variant(571));
                    }
                });
    }

    @Test
    public void test_SaveAs_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("uxsBAutoBN"), new Variant(159),
                new Variant(778), new Variant(665), new Variant(165), new Variant(154))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("uxsBAutoBN", new Variant(159), new Variant(778), new Variant(665), new
                                Variant(165), new Variant(154));
                    }
                });
    }

    @Test
    public void test_SaveAs_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("GlkOeeodbI"), new Variant(424),
                new Variant(468), new Variant(176), new Variant(397), new Variant(197), new Variant(938))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("GlkOeeodbI", new Variant(424), new Variant(468), new Variant(176), new
                                Variant(397), new Variant(197), new Variant(938));
                    }
                });
    }

    @Test
    public void test_SaveAs_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("MzDyFUaVra"), new Variant(332),
                new Variant(751), new Variant(368), new Variant(854), new Variant(875), new Variant(327), new Variant
                        (219))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("MzDyFUaVra", new Variant(332), new Variant(751), new Variant(368), new
                                Variant(854), new Variant(875), new Variant(327), new Variant(219));
                    }
                });
    }

    @Test
    public void test_SaveAs_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("jTOAuwBevZ"), new Variant(38),
                new Variant(782), new Variant(423), new Variant(993), new Variant(774), new Variant(761), new Variant
                        (980), new Variant(46))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("jTOAuwBevZ", new Variant(38), new Variant(782), new Variant(423), new
                                Variant(993), new Variant(774), new Variant(761), new Variant(980), new Variant(46));
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
        on(0xeb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(949))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Select(new Variant(949));
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
        on(0x11d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(799))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Unprotect(new Variant(799));
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
        on(0x2f8).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(954))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Arcs(new Variant(954));
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
        on(0x4a4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("koRkczdbNz"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SetBackgroundPicture("koRkczdbNz");
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
        on(0x22d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(922))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Buttons(new Variant(922));
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
        on(0x424).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(397))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.ChartObjects(new Variant(397));
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
        on(0x338).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(347))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.CheckBoxes(new Variant(347));
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
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(461))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(461));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(252), new Variant(395))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(252), new Variant(395));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(429), new Variant(474), new
                Variant(944))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(429), new Variant(474), new Variant(944));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(358), new Variant(565), new
                Variant(923), new Variant(716))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(358), new Variant(565), new Variant(923), new Variant(716));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(468), new Variant(512), new
                Variant(362), new Variant(573), new Variant(504))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(468), new Variant(512), new Variant(362), new Variant
                                (573), new Variant(504));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(780), new Variant(21), new Variant
                (408), new Variant(536), new Variant(473), new Variant(103))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(780), new Variant(21), new Variant(408), new Variant(536)
                                , new Variant(473), new Variant(103));
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
        on(0x304).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(423))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Drawings(new Variant(423));
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
        on(0x58).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(867))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.DrawingObjects(new Variant(867));
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
        on(0x344).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(373))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.DropDowns(new Variant(373));
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
        on(0x1).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(576))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Evaluate(new Variant(576));
                    }
                });
    }

    @Test
    public void test__Evaluate_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xfffffffb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(691))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Evaluate(new Variant(691));
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
        on(0x342).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(832))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.GroupBoxes(new Variant(832));
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
        on(0x459).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(652))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.GroupObjects(new Variant(652));
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
        on(0x349).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(394))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Labels(new Variant(394));
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
        on(0x2ff).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(24))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Lines(new Variant(24));
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
        on(0x340).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(945))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.ListBoxes(new Variant(945));
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
        on(0x31f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(675))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.OLEObjects(new Variant(675));
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
        on(0x271).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("QQenBbFDGJ"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnCalculate("QQenBbFDGJ");
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
        on(0x275).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("fUFKWMMEuO"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnData("fUFKWMMEuO");
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
        on(0x273).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("QBJrTNhYhk"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnEntry("QBJrTNhYhk");
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
        on(0x33a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(716))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.OptionButtons(new Variant(716));
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
        on(0x321).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(386))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Ovals(new Variant(386));
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
        on(0xd3).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(638))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Paste(new Variant(638));
                    }
                });
    }

    @Test
    public void test_Paste_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xd3).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(591), new Variant(372))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Paste(new Variant(591), new Variant(372));
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
        on(0x403).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(762))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PasteSpecial(new Variant(762));
                    }
                });
    }

    @Test
    public void test_PasteSpecial_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x403).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(918), new Variant(215))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PasteSpecial(new Variant(918), new Variant(215));
                    }
                });
    }

    @Test
    public void test_PasteSpecial_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x403).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(741), new Variant(781), new
                Variant(113))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PasteSpecial(new Variant(741), new Variant(781), new Variant(113));
                    }
                });
    }

    @Test
    public void test_PasteSpecial_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x403).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(219), new Variant(833), new
                Variant(81), new Variant(369))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PasteSpecial(new Variant(219), new Variant(833), new Variant(81), new Variant(369));
                    }
                });
    }

    @Test
    public void test_PasteSpecial_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x403).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(943), new Variant(31), new Variant
                (500), new Variant(974), new Variant(976))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PasteSpecial(new Variant(943), new Variant(31), new Variant(500), new Variant(974),
                                new Variant(976));
                    }
                });
    }

    @Test
    public void test_PasteSpecial_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x403).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(533), new Variant(147), new
                Variant(736), new Variant(81), new Variant(73), new Variant(715))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PasteSpecial(new Variant(533), new Variant(147), new Variant(736), new Variant(81),
                                new Variant(73), new Variant(715));
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
        on(0x303).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(175))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Pictures(new Variant(175));
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
        on(0x2b2).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(58))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.PivotTables(new Variant(58));
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
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(457))
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.PivotTableWizard(new Variant(457));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(160), new Variant(815))
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.PivotTableWizard(new Variant(160), new Variant(815));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(670), new Variant(787), new
                Variant(352))
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.PivotTableWizard(new Variant(670), new Variant(787), new Variant(352));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(448), new Variant(240), new
                Variant(966), new Variant(219))
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.PivotTableWizard(new Variant(448), new Variant(240), new Variant(966), new
                                Variant(219));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(553), new Variant(322), new
                Variant(199), new Variant(186), new Variant(788))
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.PivotTableWizard(new Variant(553), new Variant(322), new Variant(199), new
                                Variant(186), new Variant(788));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(817), new Variant(40), new Variant
                (792), new Variant(485), new Variant(592), new Variant(978))
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.PivotTableWizard(new Variant(817), new Variant(40), new Variant(792), new
                                Variant(485), new Variant(592), new Variant(978));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(569), new Variant(516), new
                Variant(175), new Variant(276), new Variant(774), new Variant(386), new Variant(495))
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.PivotTableWizard(new Variant(569), new Variant(516), new Variant(175), new
                                Variant(276), new Variant(774), new Variant(386), new Variant(495));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(996), new Variant(842), new
                Variant(56), new Variant(37), new Variant(665), new Variant(517), new Variant(698), new Variant(729))
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.PivotTableWizard(new Variant(996), new Variant(842), new Variant(56), new
                                Variant(37), new Variant(665), new Variant(517), new Variant(698), new Variant(729));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(115), new Variant(170), new
                Variant(843), new Variant(67), new Variant(706), new Variant(126), new Variant(522), new Variant(9),
                new Variant(12))
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.PivotTableWizard(new Variant(115), new Variant(170), new Variant(843), new
                                Variant(67), new Variant(706), new Variant(126), new Variant(522), new Variant(9),
                                new Variant(12));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_TenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(120), new Variant(682), new
                Variant(294), new Variant(123), new Variant(647), new Variant(936), new Variant(530), new Variant(50)
                , new Variant(509), new Variant(29))
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.PivotTableWizard(new Variant(120), new Variant(682), new Variant(294), new
                                Variant(123), new Variant(647), new Variant(936), new Variant(530), new Variant(50),
                                new Variant(509), new Variant(29));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_ElevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(970), new Variant(999), new
                Variant(734), new Variant(435), new Variant(556), new Variant(532), new Variant(628), new Variant(85)
                , new Variant(978), new Variant(264), new Variant(963))
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.PivotTableWizard(new Variant(970), new Variant(999), new Variant(734), new
                                Variant(435), new Variant(556), new Variant(532), new Variant(628), new Variant(85),
                                new Variant(978), new Variant(264), new Variant(963));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_TwelveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(758), new Variant(840), new
                Variant(179), new Variant(148), new Variant(348), new Variant(627), new Variant(710), new Variant
                (112), new Variant(413), new Variant(360), new Variant(632), new Variant(155))
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.PivotTableWizard(new Variant(758), new Variant(840), new Variant(179), new
                                Variant(148), new Variant(348), new Variant(627), new Variant(710), new Variant(112),
                                new Variant(413), new Variant(360), new Variant(632), new Variant(155));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_ThirteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(943), new Variant(687), new
                Variant(382), new Variant(402), new Variant(574), new Variant(762), new Variant(130), new Variant
                (410), new Variant(182), new Variant(301), new Variant(532), new Variant(975), new Variant(409))
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.PivotTableWizard(new Variant(943), new Variant(687), new Variant(382), new
                                Variant(402), new Variant(574), new Variant(762), new Variant(130), new Variant(410),
                                new Variant(182), new Variant(301), new Variant(532), new Variant(975), new Variant
                                        (409));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_FourteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(732), new Variant(190), new
                Variant(261), new Variant(554), new Variant(27), new Variant(504), new Variant(511), new Variant(232)
                , new Variant(670), new Variant(156), new Variant(434), new Variant(398), new Variant(614), new
                        Variant(53))
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.PivotTableWizard(new Variant(732), new Variant(190), new Variant(261), new
                                Variant(554), new Variant(27), new Variant(504), new Variant(511), new Variant(232),
                                new Variant(670), new Variant(156), new Variant(434), new Variant(398), new Variant
                                        (614), new Variant(53));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_FifteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(652), new Variant(111), new
                Variant(141), new Variant(777), new Variant(206), new Variant(919), new Variant(942), new Variant
                (173), new Variant(540), new Variant(380), new Variant(492), new Variant(303), new Variant(381), new
                Variant(507), new Variant(21))
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.PivotTableWizard(new Variant(652), new Variant(111), new Variant(141), new
                                Variant(777), new Variant(206), new Variant(919), new Variant(942), new Variant(173),
                                new Variant(540), new Variant(380), new Variant(492), new Variant(303), new Variant
                                        (381), new Variant(507), new Variant(21));
                    }
                });
    }

    @Test
    public void test_PivotTableWizard_SixteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ac).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(374), new Variant(363), new
                Variant(360), new Variant(834), new Variant(413), new Variant(257), new Variant(709), new Variant
                (782), new Variant(495), new Variant(604), new Variant(539), new Variant(352), new Variant(317), new
                Variant(191), new Variant(575), new Variant(71))
                .verifyReturnsDispatchable(new Returns<PivotTable>() {
                    @Override
                    public PivotTable invoke() throws ActiveXException {
                        return component.PivotTableWizard(new Variant(374), new Variant(363), new Variant(360), new
                                Variant(834), new Variant(413), new Variant(257), new Variant(709), new Variant(782),
                                new Variant(495), new Variant(604), new Variant(539), new Variant(352), new Variant
                                        (317), new Variant(191), new Variant(575), new Variant(71));
                    }
                });
    }

    @Test
    public void test_getAxRange_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xc5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(843))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxRange(new Variant(843));
                    }
                });
    }

    @Test
    public void test_getAxRange_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(79), new Variant(771))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxRange(new Variant(79), new Variant(771));
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
        on(0x306).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(562))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Rectangles(new Variant(562));
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
        on(0x38c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(344))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Scenarios(new Variant(344));
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
        on(0x599).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("ZlfxTpZQIl"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxScrollArea("ZlfxTpZQIl");
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
        on(0x33e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(287))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.ScrollBars(new Variant(287));
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
        on(0x346).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(621))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Spinners(new Variant(621));
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
        on(0x309).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(657))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.TextBoxes(new Variant(657));
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

    @Test
    public void test_SelectionChange_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x607).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SelectionChange(getMock(Range.class));
                    }
                });
    }

    @Test
    public void test_BeforeDoubleClick_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x601).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (868))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.BeforeDoubleClick(getMock(Range.class), new Variant(868));
                    }
                });
    }

    @Test
    public void test_BeforeRightClick_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (145))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.BeforeRightClick(getMock(Range.class), new Variant(145));
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
    public void test_Change_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x609).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Change(getMock(Range.class));
                    }
                });
    }

}