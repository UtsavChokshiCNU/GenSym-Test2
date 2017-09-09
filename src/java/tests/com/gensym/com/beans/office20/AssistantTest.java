package com.gensym.com.beans.office20;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class AssistantTest extends ActiveXDispatchableTestBase {

    private Assistant component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new Assistant(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(312), new Variant(162))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(312), new Variant(162));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(572))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(572));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(742))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(742));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(756), new Variant(373), new
                Variant(42L), new Variant(42L), new Variant(932))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(756), new Variant(373), 42L, 42L, new Variant(932));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(802), new
                Variant(42L), new Variant(42), new Variant(867), new Variant(19), new Variant(328), new Variant(832))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(802), 42L, 42, new Variant(867), new Variant(19), new
                                Variant(328), new Variant(832));
                    }
                });
    }

    @Test
    public void test_getAxApplication_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020000).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxApplication();
                    }
                });
    }

    @Test
    public void test_getAxCreator_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020001).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxCreator();
                    }
                });
    }

    @Test
    public void test_getAxParent_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030000).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxParent();
                    }
                });
    }

    @Test
    public void test_Move_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Move(42, 42);
                    }
                });
    }

    @Test
    public void test_setAxTop_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60030002).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxTop(42);
                    }
                });
    }

    @Test
    public void test_getAxTop_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030002).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxTop();
                    }
                });
    }

    @Test
    public void test_setAxLeft_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60030004).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxLeft(42);
                    }
                });
    }

    @Test
    public void test_getAxLeft_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030004).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxLeft();
                    }
                });
    }

    @Test
    public void test_Help_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030006).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Help();
                    }
                });
    }

    @Test
    public void test_StartWizard_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030007).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(false), new Variant
                ("GBuOshhJIY"), new Variant(42))
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.StartWizard(false, "GBuOshhJIY", 42);
                    }
                });
    }

    @Test
    public void test_StartWizard_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030007).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(false), new Variant
                ("MRJEYiddDw"), new Variant(42), new Variant(365))
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.StartWizard(false, "MRJEYiddDw", 42, new Variant(365));
                    }
                });
    }

    @Test
    public void test_StartWizard_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030007).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(false), new Variant
                ("aXRpVWVJEa"), new Variant(42), new Variant(686), new Variant(61))
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.StartWizard(false, "aXRpVWVJEa", 42, new Variant(686), new Variant(61));
                    }
                });
    }

    @Test
    public void test_StartWizard_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030007).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(false), new Variant
                ("qnQqYSHnHk"), new Variant(42), new Variant(392), new Variant(706), new Variant(795))
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.StartWizard(false, "qnQqYSHnHk", 42, new Variant(392), new Variant(706), new
                                Variant(795));
                    }
                });
    }

    @Test
    public void test_StartWizard_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030007).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(false), new Variant
                ("xGRHXRbyqW"), new Variant(42), new Variant(24), new Variant(332), new Variant(531), new Variant(293))
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.StartWizard(false, "xGRHXRbyqW", 42, new Variant(24), new Variant(332), new
                                Variant(531), new Variant(293));
                    }
                });
    }

    @Test
    public void test_StartWizard_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030007).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(false), new Variant
                ("pohFDaJqUl"), new Variant(42), new Variant(764), new Variant(978), new Variant(960), new Variant
                (886), new Variant(518))
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.StartWizard(false, "pohFDaJqUl", 42, new Variant(764), new Variant(978), new
                                Variant(960), new Variant(886), new Variant(518));
                    }
                });
    }

    @Test
    public void test_StartWizard_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030007).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(false), new Variant
                ("McKnbkBsCR"), new Variant(42), new Variant(698), new Variant(735), new Variant(230), new Variant
                (734), new Variant(895), new Variant(62))
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.StartWizard(false, "McKnbkBsCR", 42, new Variant(698), new Variant(735), new
                                Variant(230), new Variant(734), new Variant(895), new Variant(62));
                    }
                });
    }

    @Test
    public void test_EndWizard_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030008).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.EndWizard(42, false);
                    }
                });
    }

    @Test
    public void test_EndWizard_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030008).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(false), new
                Variant(420))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.EndWizard(42, false, new Variant(420));
                    }
                });
    }

    @Test
    public void test_ActivateWizard_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030009).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ActivateWizard(42, 42);
                    }
                });
    }

    @Test
    public void test_ActivateWizard_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030009).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42), new
                Variant(476))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ActivateWizard(42, 42, new Variant(476));
                    }
                });
    }

    @Test
    public void test_ResetTips_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6003000a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ResetTips();
                    }
                });
    }

    @Test
    public void test_getAxNewBalloon_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6003000b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxNewBalloon();
                    }
                });
    }

    @Test
    public void test_getAxBalloonError_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6003000c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxBalloonError();
                    }
                });
    }

    @Test
    public void test_getAxVisible_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6003000d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxVisible();
                    }
                });
    }

    @Test
    public void test_setAxVisible_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6003000d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxVisible(false);
                    }
                });
    }

    @Test
    public void test_getAxAnimation_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6003000f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxAnimation();
                    }
                });
    }

    @Test
    public void test_setAxAnimation_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6003000f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxAnimation(42);
                    }
                });
    }

    @Test
    public void test_getAxReduced_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030011).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxReduced();
                    }
                });
    }

    @Test
    public void test_setAxReduced_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60030011).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxReduced(false);
                    }
                });
    }

    @Test
    public void test_setAxAssistWithHelp_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60030013).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxAssistWithHelp(false);
                    }
                });
    }

    @Test
    public void test_getAxAssistWithHelp_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030013).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxAssistWithHelp();
                    }
                });
    }

    @Test
    public void test_setAxAssistWithWizards_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60030015).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxAssistWithWizards(false);
                    }
                });
    }

    @Test
    public void test_getAxAssistWithWizards_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030015).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxAssistWithWizards();
                    }
                });
    }

    @Test
    public void test_setAxAssistWithAlerts_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60030017).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxAssistWithAlerts(false);
                    }
                });
    }

    @Test
    public void test_getAxAssistWithAlerts_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030017).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxAssistWithAlerts();
                    }
                });
    }

    @Test
    public void test_setAxMoveWhenInTheWay_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60030019).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMoveWhenInTheWay(false);
                    }
                });
    }

    @Test
    public void test_getAxMoveWhenInTheWay_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030019).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxMoveWhenInTheWay();
                    }
                });
    }

    @Test
    public void test_setAxSounds_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6003001b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSounds(false);
                    }
                });
    }

    @Test
    public void test_getAxSounds_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6003001b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxSounds();
                    }
                });
    }

    @Test
    public void test_setAxFeatureTips_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6003001d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxFeatureTips(false);
                    }
                });
    }

    @Test
    public void test_getAxFeatureTips_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6003001d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxFeatureTips();
                    }
                });
    }

    @Test
    public void test_setAxMouseTips_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6003001f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMouseTips(false);
                    }
                });
    }

    @Test
    public void test_getAxMouseTips_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6003001f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxMouseTips();
                    }
                });
    }

    @Test
    public void test_setAxKeyboardShortcutTips_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60030021).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxKeyboardShortcutTips(false);
                    }
                });
    }

    @Test
    public void test_getAxKeyboardShortcutTips_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030021).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxKeyboardShortcutTips();
                    }
                });
    }

    @Test
    public void test_setAxHighPriorityTips_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60030023).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHighPriorityTips(false);
                    }
                });
    }

    @Test
    public void test_getAxHighPriorityTips_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030023).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxHighPriorityTips();
                    }
                });
    }

    @Test
    public void test_setAxTipOfDay_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60030025).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxTipOfDay(false);
                    }
                });
    }

    @Test
    public void test_getAxTipOfDay_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030025).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxTipOfDay();
                    }
                });
    }

    @Test
    public void test_setAxGuessHelp_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60030027).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxGuessHelp(false);
                    }
                });
    }

    @Test
    public void test_getAxGuessHelp_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030027).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxGuessHelp();
                    }
                });
    }

    @Test
    public void test_setAxSearchWhenProgramming_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60030029).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSearchWhenProgramming(false);
                    }
                });
    }

    @Test
    public void test_getAxSearchWhenProgramming_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030029).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxSearchWhenProgramming();
                    }
                });
    }

    @Test
    public void test_getAxItem_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxItem();
                    }
                });
    }

    @Test
    public void test_getAxFileName_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6003002c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxFileName();
                    }
                });
    }

    @Test
    public void test_setAxFileName_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6003002c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("STmQSWmXsH"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxFileName("STmQSWmXsH");
                    }
                });
    }

    @Test
    public void test_getAxName_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6003002e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxName();
                    }
                });
    }

}