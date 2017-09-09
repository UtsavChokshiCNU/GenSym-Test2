package com.gensym.com.beans.office20;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class CommandBarTest extends ActiveXDispatchableTestBase {

    private CommandBar component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new CommandBar(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(43), new Variant(52))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(43), new Variant(52));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(606))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(606));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(704))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(704));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(717), new Variant(760), new
                Variant(42L), new Variant(42L), new Variant(624))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(717), new Variant(760), 42L, 42L, new Variant(624));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(305), new
                Variant(42L), new Variant(42), new Variant(729), new Variant(287), new Variant(275), new Variant(152))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(305), 42L, 42, new Variant(729), new Variant(287), new
                                Variant(275), new Variant(152));
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
        on(0xffffec76).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(262))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxaccChild(new Variant(262));
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
        on(0xffffec75).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(391))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxaccName(new Variant(391));
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
        on(0xffffec74).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(970))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxaccValue(new Variant(970));
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
        on(0xffffec73).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(880))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxaccDescription(new Variant(880));
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
        on(0xffffec72).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(802))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxaccRole(new Variant(802));
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
        on(0xffffec71).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(7))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxaccState(new Variant(7));
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
        on(0xffffec70).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(86))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxaccHelp(new Variant(86));
                    }
                });
    }

    @Test
    public void test_getAxaccHelpTopic_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xffffec6f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(178))
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxaccHelpTopic(new Variant(178));
                    }
                });
    }

    @Test
    public void test_getAxaccHelpTopic_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xffffec6f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(573), new Variant(152))
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxaccHelpTopic(new Variant(573), new Variant(152));
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
        on(0xffffec6e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(814))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxaccKeyboardShortcut(new Variant(814));
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
        on(0xffffec6b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(853))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxaccDefaultAction(new Variant(853));
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
        on(0xffffec6a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(970))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.accSelect(42, new Variant(970));
                    }
                });
    }

    @Test
    public void test_accLocation_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0xffffec69).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(200), new Variant(473), new
                Variant(957), new Variant(160))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.accLocation(new Variant(200), new Variant(473), new Variant(957), new Variant(160));
                    }
                });
    }

    @Test
    public void test_accLocation_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0xffffec69).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(459), new Variant(632), new
                Variant(189), new Variant(927), new Variant(141))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.accLocation(new Variant(459), new Variant(632), new Variant(189), new Variant(927),
                                new Variant(141));
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
        on(0xffffec68).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(121))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.accNavigate(42, new Variant(121));
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
        on(0xffffec66).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(490))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.accDoDefaultAction(new Variant(490));
                    }
                });
    }

    @Test
    public void test_setAxaccName_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xffffec75).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(69))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxaccName(new Variant(69));
                    }
                });
    }

    @Test
    public void test_setAxaccName_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xffffec75).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(104), new Variant
                ("CKdAvaWIiT"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxaccName(new Variant(104), "CKdAvaWIiT");
                    }
                });
    }

    @Test
    public void test_setAxaccValue_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xffffec74).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(438))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxaccValue(new Variant(438));
                    }
                });
    }

    @Test
    public void test_setAxaccValue_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xffffec74).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(981), new Variant
                ("nWSCCMLzkV"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxaccValue(new Variant(981), "nWSCCMLzkV");
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
    public void test_getAxBuiltIn_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040000).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxBuiltIn();
                    }
                });
    }

    @Test
    public void test_getAxContext_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040001).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxContext();
                    }
                });
    }

    @Test
    public void test_setAxContext_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60040001).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("SboZwIFhoF"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxContext("SboZwIFhoF");
                    }
                });
    }

    @Test
    public void test_getAxControls_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040003).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<CommandBarControls>() {
                    @Override
                    public CommandBarControls invoke() throws ActiveXException {
                        return component.getAxControls();
                    }
                });
    }

    @Test
    public void test_Delete_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040004).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Delete();
                    }
                });
    }

    @Test
    public void test_getAxEnabled_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040005).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxEnabled();
                    }
                });
    }

    @Test
    public void test_setAxEnabled_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60040005).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxEnabled(false);
                    }
                });
    }

    @Test
    public void test_FindControl_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040007).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchable(new Returns<CommandBarControl>() {
                    @Override
                    public CommandBarControl invoke() throws ActiveXException {
                        return component.FindControl();
                    }
                });
    }

    @Test
    public void test_FindControl_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60040007).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(320))
                .verifyReturnsDispatchable(new Returns<CommandBarControl>() {
                    @Override
                    public CommandBarControl invoke() throws ActiveXException {
                        return component.FindControl(new Variant(320));
                    }
                });
    }

    @Test
    public void test_FindControl_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040007).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(975), new Variant(427))
                .verifyReturnsDispatchable(new Returns<CommandBarControl>() {
                    @Override
                    public CommandBarControl invoke() throws ActiveXException {
                        return component.FindControl(new Variant(975), new Variant(427));
                    }
                });
    }

    @Test
    public void test_FindControl_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040007).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(788), new Variant(486), new
                Variant(725))
                .verifyReturnsDispatchable(new Returns<CommandBarControl>() {
                    @Override
                    public CommandBarControl invoke() throws ActiveXException {
                        return component.FindControl(new Variant(788), new Variant(486), new Variant(725));
                    }
                });
    }

    @Test
    public void test_FindControl_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040007).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(662), new Variant(279), new
                Variant(896), new Variant(973))
                .verifyReturnsDispatchable(new Returns<CommandBarControl>() {
                    @Override
                    public CommandBarControl invoke() throws ActiveXException {
                        return component.FindControl(new Variant(662), new Variant(279), new Variant(896), new
                                Variant(973));
                    }
                });
    }

    @Test
    public void test_FindControl_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040007).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(514), new Variant(890), new
                Variant(213), new Variant(23), new Variant(900))
                .verifyReturnsDispatchable(new Returns<CommandBarControl>() {
                    @Override
                    public CommandBarControl invoke() throws ActiveXException {
                        return component.FindControl(new Variant(514), new Variant(890), new Variant(213), new
                                Variant(23), new Variant(900));
                    }
                });
    }

    @Test
    public void test_getAxHeight_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040008).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxHeight();
                    }
                });
    }

    @Test
    public void test_setAxHeight_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60040008).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHeight(42);
                    }
                });
    }

    @Test
    public void test_getAxIndex_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6004000a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxIndex();
                    }
                });
    }

    @Test
    public void test_getAxInstanceId_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6004000b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxInstanceId();
                    }
                });
    }

    @Test
    public void test_getAxLeft_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6004000c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxLeft();
                    }
                });
    }

    @Test
    public void test_setAxLeft_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6004000c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxLeft(42);
                    }
                });
    }

    @Test
    public void test_getAxName_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6004000e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxName();
                    }
                });
    }

    @Test
    public void test_setAxName_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6004000e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("CKqfTehSoW"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxName("CKqfTehSoW");
                    }
                });
    }

    @Test
    public void test_getAxNameLocal_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040010).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxNameLocal();
                    }
                });
    }

    @Test
    public void test_setAxNameLocal_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60040010).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("zCLrgBnaui"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxNameLocal("zCLrgBnaui");
                    }
                });
    }

    @Test
    public void test_getAxParent_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040012).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxParent();
                    }
                });
    }

    @Test
    public void test_getAxPosition_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040013).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxPosition();
                    }
                });
    }

    @Test
    public void test_setAxPosition_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60040013).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPosition(42);
                    }
                });
    }

    @Test
    public void test_getAxRowIndex_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040015).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxRowIndex();
                    }
                });
    }

    @Test
    public void test_setAxRowIndex_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60040015).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxRowIndex(42);
                    }
                });
    }

    @Test
    public void test_getAxProtection_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040017).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxProtection();
                    }
                });
    }

    @Test
    public void test_setAxProtection_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60040017).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxProtection(42);
                    }
                });
    }

    @Test
    public void test_Reset_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040019).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Reset();
                    }
                });
    }

    @Test
    public void test_ShowPopup_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6004001a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ShowPopup();
                    }
                });
    }

    @Test
    public void test_ShowPopup_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6004001a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(844))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ShowPopup(new Variant(844));
                    }
                });
    }

    @Test
    public void test_ShowPopup_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6004001a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(322), new Variant(387))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ShowPopup(new Variant(322), new Variant(387));
                    }
                });
    }

    @Test
    public void test_getAxTop_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6004001b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxTop();
                    }
                });
    }

    @Test
    public void test_setAxTop_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6004001b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxTop(42);
                    }
                });
    }

    @Test
    public void test_getAxType_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6004001d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxType();
                    }
                });
    }

    @Test
    public void test_getAxVisible_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6004001e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxVisible();
                    }
                });
    }

    @Test
    public void test_setAxVisible_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6004001e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxVisible(false);
                    }
                });
    }

    @Test
    public void test_getAxWidth_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040020).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxWidth();
                    }
                });
    }

    @Test
    public void test_setAxWidth_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60040020).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxWidth(42);
                    }
                });
    }

}