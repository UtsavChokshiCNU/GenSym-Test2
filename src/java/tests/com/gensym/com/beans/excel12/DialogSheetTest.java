package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class DialogSheetTest extends ActiveXDispatchableTestBase {

    private DialogSheet component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new DialogSheet(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(657), new Variant(100))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(657), new Variant(100));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(208))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(208));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(625))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(625));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(50), new Variant(897), new
                Variant(42L), new Variant(42L), new Variant(565))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(50), new Variant(897), 42L, 42L, new Variant(565));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(553), new
                Variant(42L), new Variant(42), new Variant(580), new Variant(357), new Variant(986), new Variant(883))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(553), 42L, 42, new Variant(580), new Variant(357), new
                                Variant(986), new Variant(883));
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
        on(0x227).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(394))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Copy(new Variant(394));
                    }
                });
    }

    @Test
    public void test_Copy_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x227).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(523), new Variant(755))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Copy(new Variant(523), new Variant(755));
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
        on(0x80010000).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("OZsCGUhirZ"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAx_CodeName("OZsCGUhirZ");
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
        on(0x27d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(488))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Move(new Variant(488));
                    }
                });
    }

    @Test
    public void test_Move_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x27d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(395), new Variant(707))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Move(new Variant(395), new Variant(707));
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
        on(0x6e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("udLmaAtCPJ"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxName("udLmaAtCPJ");
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
        on(0x274).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("ANEaGFGpPm"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnDoubleClick("ANEaGFGpPm");
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
        on(0x407).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("bFlYPOJbFl"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnSheetActivate("bFlYPOJbFl");
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
        on(0x439).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("uwJKMqaAmm"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnSheetDeactivate("uwJKMqaAmm");
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
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(104))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(104));
                    }
                });
    }

    @Test
    public void test_PrintOut_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(778), new Variant(17))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(778), new Variant(17));
                    }
                });
    }

    @Test
    public void test_PrintOut_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(689), new Variant(478), new
                Variant(540))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(689), new Variant(478), new Variant(540));
                    }
                });
    }

    @Test
    public void test_PrintOut_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(568), new Variant(97), new Variant
                (205), new Variant(904))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(568), new Variant(97), new Variant(205), new Variant(904));
                    }
                });
    }

    @Test
    public void test_PrintOut_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(390), new Variant(576), new
                Variant(182), new Variant(75), new Variant(377))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(390), new Variant(576), new Variant(182), new Variant(75), new
                                Variant(377));
                    }
                });
    }

    @Test
    public void test_PrintOut_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(237), new Variant(270), new
                Variant(499), new Variant(353), new Variant(863), new Variant(859))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(237), new Variant(270), new Variant(499), new Variant(353),
                                new Variant(863), new Variant(859));
                    }
                });
    }

    @Test
    public void test_PrintOut_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x389).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(520), new Variant(316), new
                Variant(640), new Variant(913), new Variant(832), new Variant(815), new Variant(143))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintOut(new Variant(520), new Variant(316), new Variant(640), new Variant(913),
                                new Variant(832), new Variant(815), new Variant(143));
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
        on(0x119).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(410))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PrintPreview(new Variant(410));
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
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(749))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect(new Variant(749));
                    }
                });
    }

    @Test
    public void test_Protect_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(136), new Variant(572))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect(new Variant(136), new Variant(572));
                    }
                });
    }

    @Test
    public void test_Protect_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(888), new Variant(801), new
                Variant(773))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect(new Variant(888), new Variant(801), new Variant(773));
                    }
                });
    }

    @Test
    public void test_Protect_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(420), new Variant(248), new
                Variant(538), new Variant(136))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect(new Variant(420), new Variant(248), new Variant(538), new Variant(136));
                    }
                });
    }

    @Test
    public void test_Protect_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(852), new Variant(197), new
                Variant(288), new Variant(770), new Variant(897))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Protect(new Variant(852), new Variant(197), new Variant(288), new Variant(770), new
                                Variant(897));
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
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("YihAtcRtIE"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("YihAtcRtIE");
                    }
                });
    }

    @Test
    public void test_SaveAs_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("vhAtAesNtK"), new Variant(702))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("vhAtAesNtK", new Variant(702));
                    }
                });
    }

    @Test
    public void test_SaveAs_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("ePguOiRcvD"), new Variant(434),
                new Variant(568))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("ePguOiRcvD", new Variant(434), new Variant(568));
                    }
                });
    }

    @Test
    public void test_SaveAs_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("YsBpcdmrBc"), new Variant(30),
                new Variant(766), new Variant(465))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("YsBpcdmrBc", new Variant(30), new Variant(766), new Variant(465));
                    }
                });
    }

    @Test
    public void test_SaveAs_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("xInxUlSUvm"), new Variant(663),
                new Variant(480), new Variant(205), new Variant(269))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("xInxUlSUvm", new Variant(663), new Variant(480), new Variant(205), new
                                Variant(269));
                    }
                });
    }

    @Test
    public void test_SaveAs_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("xDOgDbGqIM"), new Variant(320),
                new Variant(596), new Variant(583), new Variant(347), new Variant(695))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("xDOgDbGqIM", new Variant(320), new Variant(596), new Variant(583), new
                                Variant(347), new Variant(695));
                    }
                });
    }

    @Test
    public void test_SaveAs_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("cwOwMsEkyj"), new Variant(504),
                new Variant(809), new Variant(592), new Variant(614), new Variant(950), new Variant(244))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("cwOwMsEkyj", new Variant(504), new Variant(809), new Variant(592), new
                                Variant(614), new Variant(950), new Variant(244));
                    }
                });
    }

    @Test
    public void test_SaveAs_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("SAAdESKgRG"), new Variant(423),
                new Variant(97), new Variant(764), new Variant(208), new Variant(518), new Variant(766), new Variant
                        (17))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("SAAdESKgRG", new Variant(423), new Variant(97), new Variant(764), new
                                Variant(208), new Variant(518), new Variant(766), new Variant(17));
                    }
                });
    }

    @Test
    public void test_SaveAs_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("DVbQZOMBkw"), new Variant(782),
                new Variant(751), new Variant(595), new Variant(802), new Variant(826), new Variant(874), new Variant
                        (411), new Variant(234))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveAs("DVbQZOMBkw", new Variant(782), new Variant(751), new Variant(595), new
                                Variant(802), new Variant(826), new Variant(874), new Variant(411), new Variant(234));
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
        on(0xeb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(51))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Select(new Variant(51));
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
        on(0x11d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(856))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Unprotect(new Variant(856));
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
    public void test__Dummy29_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1001d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy29();
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
        on(0x2f8).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(686))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Arcs(new Variant(686));
                    }
                });
    }

    @Test
    public void test__Dummy31_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1001f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy31();
                    }
                });
    }

    @Test
    public void test__Dummy32_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10020).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy32();
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
        on(0x22d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(489))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Buttons(new Variant(489));
                    }
                });
    }

    @Test
    public void test__Dummy34_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10022).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy34();
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
    public void test__Dummy36_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10024).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy36();
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
        on(0x424).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(296))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.ChartObjects(new Variant(296));
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
        on(0x338).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(170))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.CheckBoxes(new Variant(170));
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
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(988))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(988));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(795), new Variant(776))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(795), new Variant(776));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(288), new Variant(742), new
                Variant(577))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(288), new Variant(742), new Variant(577));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(302), new Variant(821), new
                Variant(282), new Variant(357))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(302), new Variant(821), new Variant(282), new Variant(357));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(696), new Variant(695), new
                Variant(921), new Variant(118), new Variant(914))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(696), new Variant(695), new Variant(921), new Variant
                                (118), new Variant(914));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(885), new Variant(214), new
                Variant(676), new Variant(828), new Variant(10), new Variant(501))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckSpelling(new Variant(885), new Variant(214), new Variant(676), new Variant
                                (828), new Variant(10), new Variant(501));
                    }
                });
    }

    @Test
    public void test__Dummy40_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10028).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy40();
                    }
                });
    }

    @Test
    public void test__Dummy41_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10029).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy41();
                    }
                });
    }

    @Test
    public void test__Dummy42_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1002a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy42();
                    }
                });
    }

    @Test
    public void test__Dummy43_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1002b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy43();
                    }
                });
    }

    @Test
    public void test__Dummy44_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1002c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy44();
                    }
                });
    }

    @Test
    public void test__Dummy45_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1002d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy45();
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
        on(0x304).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(453))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Drawings(new Variant(453));
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
        on(0x58).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(580))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.DrawingObjects(new Variant(580));
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
        on(0x344).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(158))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.DropDowns(new Variant(158));
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
        on(0x1).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(141))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Evaluate(new Variant(141));
                    }
                });
    }

    @Test
    public void test__Evaluate_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xfffffffb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(678))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Evaluate(new Variant(678));
                    }
                });
    }

    @Test
    public void test__Dummy56_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10038).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy56();
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
        on(0x342).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(641))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.GroupBoxes(new Variant(641));
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
        on(0x459).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(963))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.GroupObjects(new Variant(963));
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
        on(0x349).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(43))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Labels(new Variant(43));
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
        on(0x2ff).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(165))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Lines(new Variant(165));
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
        on(0x340).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(630))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.ListBoxes(new Variant(630));
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
        on(0x31f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(572))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.OLEObjects(new Variant(572));
                    }
                });
    }

    @Test
    public void test__Dummy65_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10041).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy65();
                    }
                });
    }

    @Test
    public void test__Dummy66_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10042).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy66();
                    }
                });
    }

    @Test
    public void test__Dummy67_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10043).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy67();
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
        on(0x33a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(293))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.OptionButtons(new Variant(293));
                    }
                });
    }

    @Test
    public void test__Dummy69_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10045).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy69();
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
        on(0x321).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(3))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Ovals(new Variant(3));
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
        on(0xd3).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(479))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Paste(new Variant(479));
                    }
                });
    }

    @Test
    public void test_Paste_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xd3).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(234), new Variant(760))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Paste(new Variant(234), new Variant(760));
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
        on(0x403).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(383))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PasteSpecial(new Variant(383));
                    }
                });
    }

    @Test
    public void test_PasteSpecial_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x403).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(388), new Variant(472))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PasteSpecial(new Variant(388), new Variant(472));
                    }
                });
    }

    @Test
    public void test_PasteSpecial_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x403).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(95), new Variant(270), new Variant
                (175))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PasteSpecial(new Variant(95), new Variant(270), new Variant(175));
                    }
                });
    }

    @Test
    public void test_PasteSpecial_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x403).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(254), new Variant(177), new
                Variant(990), new Variant(834))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PasteSpecial(new Variant(254), new Variant(177), new Variant(990), new Variant(834));
                    }
                });
    }

    @Test
    public void test_PasteSpecial_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x403).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(580), new Variant(165), new
                Variant(425), new Variant(226), new Variant(340))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PasteSpecial(new Variant(580), new Variant(165), new Variant(425), new Variant(226)
                                , new Variant(340));
                    }
                });
    }

    @Test
    public void test_PasteSpecial_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x403).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(988), new Variant(447), new
                Variant(626), new Variant(90), new Variant(474), new Variant(885))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PasteSpecial(new Variant(988), new Variant(447), new Variant(626), new Variant(90),
                                new Variant(474), new Variant(885));
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
        on(0x303).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(318))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Pictures(new Variant(318));
                    }
                });
    }

    @Test
    public void test__Dummy74_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1004a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy74();
                    }
                });
    }

    @Test
    public void test__Dummy75_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1004b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy75();
                    }
                });
    }

    @Test
    public void test__Dummy76_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1004c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy76();
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
        on(0x306).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(55))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Rectangles(new Variant(55));
                    }
                });
    }

    @Test
    public void test__Dummy78_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1004e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy78();
                    }
                });
    }

    @Test
    public void test__Dummy79_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1004f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy79();
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
        on(0x599).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("sXHELlZmhx"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxScrollArea("sXHELlZmhx");
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
        on(0x33e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(435))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.ScrollBars(new Variant(435));
                    }
                });
    }

    @Test
    public void test__Dummy82_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10052).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy82();
                    }
                });
    }

    @Test
    public void test__Dummy83_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10053).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy83();
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
        on(0x346).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(762))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.Spinners(new Variant(762));
                    }
                });
    }

    @Test
    public void test__Dummy85_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10055).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy85();
                    }
                });
    }

    @Test
    public void test__Dummy86_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10056).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy86();
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
        on(0x309).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(677))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.TextBoxes(new Variant(677));
                    }
                });
    }

    @Test
    public void test__Dummy88_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10058).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy88();
                    }
                });
    }

    @Test
    public void test__Dummy89_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10059).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy89();
                    }
                });
    }

    @Test
    public void test__Dummy90_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1005a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy90();
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
    public void test_getAxDefaultButton_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x359).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxDefaultButton();
                    }
                });
    }

    @Test
    public void test_setAxDefaultButton_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x359).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(816))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDefaultButton(new Variant(816));
                    }
                });
    }

    @Test
    public void test_getAxDialogFrame_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x347).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<DialogFrame>() {
                    @Override
                    public DialogFrame invoke() throws ActiveXException {
                        return component.getAxDialogFrame();
                    }
                });
    }

    @Test
    public void test_EditBoxes_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x33c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.EditBoxes();
                    }
                });
    }

    @Test
    public void test_EditBoxes_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x33c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(335))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.EditBoxes(new Variant(335));
                    }
                });
    }

    @Test
    public void test_getAxFocus_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x32e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxFocus();
                    }
                });
    }

    @Test
    public void test_setAxFocus_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x32e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(935))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxFocus(new Variant(935));
                    }
                });
    }

    @Test
    public void test_Hide_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x32d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Hide();
                    }
                });
    }

    @Test
    public void test_Hide_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x32d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(193))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Hide(new Variant(193));
                    }
                });
    }

    @Test
    public void test_Show_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Show();
                    }
                });
    }

}