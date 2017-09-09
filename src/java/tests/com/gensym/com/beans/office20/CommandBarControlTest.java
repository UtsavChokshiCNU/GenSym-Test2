package com.gensym.com.beans.office20;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class CommandBarControlTest extends ActiveXDispatchableTestBase {

    private CommandBarControl component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new CommandBarControl(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(896), new Variant(312))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(896), new Variant(312));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(935))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(935));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(400))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(400));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(861), new Variant(428), new
                Variant(42L), new Variant(42L), new Variant(733))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(861), new Variant(428), 42L, 42L, new Variant(733));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(352), new
                Variant(42L), new Variant(42), new Variant(893), new Variant(588), new Variant(580), new Variant(444))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(352), 42L, 42, new Variant(893), new Variant(588), new
                                Variant(580), new Variant(444));
                    }
                });
    }

    @Test
    public void test_getAxaccParent_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xffffec78).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxaccParent();
                    }
                });
    }

    @Test
    public void test_getAxaccChildCount_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xffffec77).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxaccChildCount();
                    }
                });
    }

    @Test
    public void test_getAxaccChild_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xffffec76).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(228))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxaccChild(new Variant(228));
                    }
                });
    }

    @Test
    public void test_getAxaccName_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xffffec75).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxaccName();
                    }
                });
    }

    @Test
    public void test_getAxaccName_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xffffec75).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(718))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxaccName(new Variant(718));
                    }
                });
    }

    @Test
    public void test_getAxaccValue_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xffffec74).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxaccValue();
                    }
                });
    }

    @Test
    public void test_getAxaccValue_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xffffec74).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(435))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxaccValue(new Variant(435));
                    }
                });
    }

    @Test
    public void test_getAxaccDescription_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xffffec73).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxaccDescription();
                    }
                });
    }

    @Test
    public void test_getAxaccDescription_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xffffec73).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(389))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxaccDescription(new Variant(389));
                    }
                });
    }

    @Test
    public void test_getAxaccRole_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xffffec72).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxaccRole();
                    }
                });
    }

    @Test
    public void test_getAxaccRole_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xffffec72).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(586))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxaccRole(new Variant(586));
                    }
                });
    }

    @Test
    public void test_getAxaccState_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xffffec71).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxaccState();
                    }
                });
    }

    @Test
    public void test_getAxaccState_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xffffec71).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(875))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxaccState(new Variant(875));
                    }
                });
    }

    @Test
    public void test_getAxaccHelp_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xffffec70).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxaccHelp();
                    }
                });
    }

    @Test
    public void test_getAxaccHelp_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xffffec70).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(459))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxaccHelp(new Variant(459));
                    }
                });
    }

    @Test
    public void test_getAxaccHelpTopic_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xffffec6f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(909))
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxaccHelpTopic(new Variant(909));
                    }
                });
    }

    @Test
    public void test_getAxaccHelpTopic_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xffffec6f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(336), new Variant(68))
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxaccHelpTopic(new Variant(336), new Variant(68));
                    }
                });
    }

    @Test
    public void test_getAxaccKeyboardShortcut_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xffffec6e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxaccKeyboardShortcut();
                    }
                });
    }

    @Test
    public void test_getAxaccKeyboardShortcut_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xffffec6e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(319))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxaccKeyboardShortcut(new Variant(319));
                    }
                });
    }

    @Test
    public void test_getAxaccFocus_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xffffec6d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxaccFocus();
                    }
                });
    }

    @Test
    public void test_getAxaccSelection_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xffffec6c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxaccSelection();
                    }
                });
    }

    @Test
    public void test_getAxaccDefaultAction_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xffffec6b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxaccDefaultAction();
                    }
                });
    }

    @Test
    public void test_getAxaccDefaultAction_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xffffec6b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(898))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxaccDefaultAction(new Variant(898));
                    }
                });
    }

    @Test
    public void test_accSelect_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xffffec6a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.accSelect(42);
                    }
                });
    }

    @Test
    public void test_accSelect_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xffffec6a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(194))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.accSelect(42, new Variant(194));
                    }
                });
    }

    @Test
    public void test_accLocation_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0xffffec69).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(968), new Variant(266), new
                Variant(725), new Variant(469))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.accLocation(new Variant(968), new Variant(266), new Variant(725), new Variant(469));
                    }
                });
    }

    @Test
    public void test_accLocation_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0xffffec69).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(296), new Variant(612), new
                Variant(778), new Variant(30), new Variant(755))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.accLocation(new Variant(296), new Variant(612), new Variant(778), new Variant(30),
                                new Variant(755));
                    }
                });
    }

    @Test
    public void test_accNavigate_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xffffec68).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.accNavigate(42);
                    }
                });
    }

    @Test
    public void test_accNavigate_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xffffec68).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(40))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.accNavigate(42, new Variant(40));
                    }
                });
    }

    @Test
    public void test_accHitTest_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xffffec67).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.accHitTest(42, 42);
                    }
                });
    }

    @Test
    public void test_accDoDefaultAction_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xffffec66).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.accDoDefaultAction();
                    }
                });
    }

    @Test
    public void test_accDoDefaultAction_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xffffec66).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(323))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.accDoDefaultAction(new Variant(323));
                    }
                });
    }

    @Test
    public void test_setAxaccName_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xffffec75).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(932))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxaccName(new Variant(932));
                    }
                });
    }

    @Test
    public void test_setAxaccName_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xffffec75).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(829), new Variant
                ("fThqyeWixd"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxaccName(new Variant(829), "fThqyeWixd");
                    }
                });
    }

    @Test
    public void test_setAxaccValue_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xffffec74).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(237))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxaccValue(new Variant(237));
                    }
                });
    }

    @Test
    public void test_setAxaccValue_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xffffec74).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(669), new Variant
                ("xKamcprBoe"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxaccValue(new Variant(669), "xKamcprBoe");
                    }
                });
    }

    @Test
    public void test_getAxApplication_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030000).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxApplication();
                    }
                });
    }

    @Test
    public void test_getAxCreator_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030001).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxCreator();
                    }
                });
    }

    @Test
    public void test_getAxBeginGroup_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040000).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxBeginGroup();
                    }
                });
    }

    @Test
    public void test_setAxBeginGroup_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60040000).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxBeginGroup(false);
                    }
                });
    }

    @Test
    public void test_getAxBuiltIn_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040002).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxBuiltIn();
                    }
                });
    }

    @Test
    public void test_getAxCaption_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040003).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxCaption();
                    }
                });
    }

    @Test
    public void test_setAxCaption_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60040003).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("GiqSyxFcSS"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCaption("GiqSyxFcSS");
                    }
                });
    }

    @Test
    public void test_getAxControl_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040005).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxControl();
                    }
                });
    }

    @Test
    public void test_Copy_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040006).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchable(new Returns<CommandBarControl>() {
                    @Override
                    public CommandBarControl invoke() throws ActiveXException {
                        return component.Copy();
                    }
                });
    }

    @Test
    public void test_Copy_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60040006).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(267))
                .verifyReturnsDispatchable(new Returns<CommandBarControl>() {
                    @Override
                    public CommandBarControl invoke() throws ActiveXException {
                        return component.Copy(new Variant(267));
                    }
                });
    }

    @Test
    public void test_Copy_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040006).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(210), new Variant(319))
                .verifyReturnsDispatchable(new Returns<CommandBarControl>() {
                    @Override
                    public CommandBarControl invoke() throws ActiveXException {
                        return component.Copy(new Variant(210), new Variant(319));
                    }
                });
    }

    @Test
    public void test_Delete_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040007).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Delete();
                    }
                });
    }

    @Test
    public void test_Delete_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60040007).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(739))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Delete(new Variant(739));
                    }
                });
    }

    @Test
    public void test_getAxDescriptionText_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040008).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxDescriptionText();
                    }
                });
    }

    @Test
    public void test_setAxDescriptionText_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60040008).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("HnrQKnkGHM"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDescriptionText("HnrQKnkGHM");
                    }
                });
    }

    @Test
    public void test_getAxEnabled_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6004000a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxEnabled();
                    }
                });
    }

    @Test
    public void test_setAxEnabled_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6004000a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxEnabled(false);
                    }
                });
    }

    @Test
    public void test_Execute_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6004000c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Execute();
                    }
                });
    }

    @Test
    public void test_getAxHeight_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6004000d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxHeight();
                    }
                });
    }

    @Test
    public void test_setAxHeight_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6004000d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHeight(42);
                    }
                });
    }

    @Test
    public void test_getAxHelpContextId_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6004000f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxHelpContextId();
                    }
                });
    }

    @Test
    public void test_setAxHelpContextId_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6004000f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHelpContextId(42);
                    }
                });
    }

    @Test
    public void test_getAxHelpFile_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040011).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxHelpFile();
                    }
                });
    }

    @Test
    public void test_setAxHelpFile_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60040011).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("BITThhijAk"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHelpFile("BITThhijAk");
                    }
                });
    }

    @Test
    public void test_getAxId_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040013).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxId();
                    }
                });
    }

    @Test
    public void test_getAxIndex_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040014).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxIndex();
                    }
                });
    }

    @Test
    public void test_getAxInstanceId_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040015).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxInstanceId();
                    }
                });
    }

    @Test
    public void test_Move_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040016).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchable(new Returns<CommandBarControl>() {
                    @Override
                    public CommandBarControl invoke() throws ActiveXException {
                        return component.Move();
                    }
                });
    }

    @Test
    public void test_Move_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60040016).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(366))
                .verifyReturnsDispatchable(new Returns<CommandBarControl>() {
                    @Override
                    public CommandBarControl invoke() throws ActiveXException {
                        return component.Move(new Variant(366));
                    }
                });
    }

    @Test
    public void test_Move_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040016).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(113), new Variant(473))
                .verifyReturnsDispatchable(new Returns<CommandBarControl>() {
                    @Override
                    public CommandBarControl invoke() throws ActiveXException {
                        return component.Move(new Variant(113), new Variant(473));
                    }
                });
    }

    @Test
    public void test_getAxLeft_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040017).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxLeft();
                    }
                });
    }

    @Test
    public void test_getAxOLEUsage_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040018).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxOLEUsage();
                    }
                });
    }

    @Test
    public void test_setAxOLEUsage_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60040018).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOLEUsage(42);
                    }
                });
    }

    @Test
    public void test_getAxOnAction_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6004001a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxOnAction();
                    }
                });
    }

    @Test
    public void test_setAxOnAction_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6004001a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("SilJGEhxzG"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnAction("SilJGEhxzG");
                    }
                });
    }

    @Test
    public void test_getAxParent_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6004001c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<CommandBar>() {
                    @Override
                    public CommandBar invoke() throws ActiveXException {
                        return component.getAxParent();
                    }
                });
    }

    @Test
    public void test_getAxParameter_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6004001d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxParameter();
                    }
                });
    }

    @Test
    public void test_setAxParameter_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6004001d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("GIqPFvuAEK"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxParameter("GIqPFvuAEK");
                    }
                });
    }

    @Test
    public void test_getAxPriority_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6004001f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxPriority();
                    }
                });
    }

    @Test
    public void test_setAxPriority_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6004001f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPriority(42);
                    }
                });
    }

    @Test
    public void test_Reset_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040021).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Reset();
                    }
                });
    }

    @Test
    public void test_SetFocus_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040022).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SetFocus();
                    }
                });
    }

    @Test
    public void test_getAxTag_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040023).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxTag();
                    }
                });
    }

    @Test
    public void test_setAxTag_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60040023).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("dkRaAgVrcF"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxTag("dkRaAgVrcF");
                    }
                });
    }

    @Test
    public void test_getAxTooltipText_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040025).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxTooltipText();
                    }
                });
    }

    @Test
    public void test_setAxTooltipText_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60040025).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("zAknRiFPMV"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxTooltipText("zAknRiFPMV");
                    }
                });
    }

    @Test
    public void test_getAxTop_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040027).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxTop();
                    }
                });
    }

    @Test
    public void test_getAxType_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040028).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxType();
                    }
                });
    }

    @Test
    public void test_getAxVisible_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040029).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxVisible();
                    }
                });
    }

    @Test
    public void test_setAxVisible_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60040029).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxVisible(false);
                    }
                });
    }

    @Test
    public void test_getAxWidth_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6004002b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxWidth();
                    }
                });
    }

    @Test
    public void test_setAxWidth_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6004002b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxWidth(42);
                    }
                });
    }

    @Test
    public void test_Reserved1_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6004002d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Reserved1();
                    }
                });
    }

    @Test
    public void test_Reserved2_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6004002e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Reserved2();
                    }
                });
    }

    @Test
    public void test_Reserved3_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6004002f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Reserved3();
                    }
                });
    }

    @Test
    public void test_Reserved4_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040030).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Reserved4();
                    }
                });
    }

    @Test
    public void test_Reserved5_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040031).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Reserved5();
                    }
                });
    }

    @Test
    public void test_Reserved6_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040032).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Reserved6();
                    }
                });
    }

    @Test
    public void test_Reserved7_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040033).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Reserved7();
                    }
                });
    }

    @Test
    public void test_Reserved8_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040034).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Reserved8();
                    }
                });
    }

}