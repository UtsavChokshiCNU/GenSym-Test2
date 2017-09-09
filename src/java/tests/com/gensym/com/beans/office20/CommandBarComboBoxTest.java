package com.gensym.com.beans.office20;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class CommandBarComboBoxTest extends ActiveXDispatchableTestBase {

    private CommandBarComboBox component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new CommandBarComboBox(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(651), new Variant(188))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(651), new Variant(188));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(78))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(78));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(572))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(572));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(332), new Variant(801), new
                Variant(42L), new Variant(42L), new Variant(472))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(332), new Variant(801), 42L, 42L, new Variant(472));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(654), new
                Variant(42L), new Variant(42), new Variant(812), new Variant(92), new Variant(546), new Variant(622))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(654), 42L, 42, new Variant(812), new Variant(92), new
                                Variant(546), new Variant(622));
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
        on(0xffffec76).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(781))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxaccChild(new Variant(781));
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
        on(0xffffec75).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(908))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxaccName(new Variant(908));
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
        on(0xffffec74).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(915))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxaccValue(new Variant(915));
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
        on(0xffffec73).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(914))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxaccDescription(new Variant(914));
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
        on(0xffffec72).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(723))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxaccRole(new Variant(723));
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
        on(0xffffec71).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(37))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxaccState(new Variant(37));
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
        on(0xffffec70).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(3))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxaccHelp(new Variant(3));
                    }
                });
    }

    @Test
    public void test_getAxaccHelpTopic_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xffffec6f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(220))
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxaccHelpTopic(new Variant(220));
                    }
                });
    }

    @Test
    public void test_getAxaccHelpTopic_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xffffec6f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(738), new Variant(827))
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxaccHelpTopic(new Variant(738), new Variant(827));
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
        on(0xffffec6e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(208))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxaccKeyboardShortcut(new Variant(208));
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
        on(0xffffec6b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(175))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxaccDefaultAction(new Variant(175));
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
        on(0xffffec6a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(444))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.accSelect(42, new Variant(444));
                    }
                });
    }

    @Test
    public void test_accLocation_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0xffffec69).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(326), new Variant(234), new
                Variant(957), new Variant(787))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.accLocation(new Variant(326), new Variant(234), new Variant(957), new Variant(787));
                    }
                });
    }

    @Test
    public void test_accLocation_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0xffffec69).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(820), new Variant(293), new
                Variant(773), new Variant(624), new Variant(901))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.accLocation(new Variant(820), new Variant(293), new Variant(773), new Variant(624),
                                new Variant(901));
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
        on(0xffffec68).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(667))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.accNavigate(42, new Variant(667));
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
        on(0xffffec66).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(82))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.accDoDefaultAction(new Variant(82));
                    }
                });
    }

    @Test
    public void test_setAxaccName_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xffffec75).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(557))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxaccName(new Variant(557));
                    }
                });
    }

    @Test
    public void test_setAxaccName_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xffffec75).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(952), new Variant
                ("nyMpOnKuAV"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxaccName(new Variant(952), "nyMpOnKuAV");
                    }
                });
    }

    @Test
    public void test_setAxaccValue_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xffffec74).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(11))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxaccValue(new Variant(11));
                    }
                });
    }

    @Test
    public void test_setAxaccValue_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xffffec74).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(967), new Variant
                ("DRUvvIWdop"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxaccValue(new Variant(967), "DRUvvIWdop");
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
        on(0x60040003).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("RXQcyNTajp"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCaption("RXQcyNTajp");
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
        on(0x60040006).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(885))
                .verifyReturnsDispatchable(new Returns<CommandBarControl>() {
                    @Override
                    public CommandBarControl invoke() throws ActiveXException {
                        return component.Copy(new Variant(885));
                    }
                });
    }

    @Test
    public void test_Copy_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040006).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(858), new Variant(498))
                .verifyReturnsDispatchable(new Returns<CommandBarControl>() {
                    @Override
                    public CommandBarControl invoke() throws ActiveXException {
                        return component.Copy(new Variant(858), new Variant(498));
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
        on(0x60040007).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(215))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Delete(new Variant(215));
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
        on(0x60040008).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("TqTHZBWHXR"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDescriptionText("TqTHZBWHXR");
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
        on(0x60040011).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("rWGfcPyvTJ"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHelpFile("rWGfcPyvTJ");
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
        on(0x60040016).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(486))
                .verifyReturnsDispatchable(new Returns<CommandBarControl>() {
                    @Override
                    public CommandBarControl invoke() throws ActiveXException {
                        return component.Move(new Variant(486));
                    }
                });
    }

    @Test
    public void test_Move_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60040016).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(70), new Variant(52))
                .verifyReturnsDispatchable(new Returns<CommandBarControl>() {
                    @Override
                    public CommandBarControl invoke() throws ActiveXException {
                        return component.Move(new Variant(70), new Variant(52));
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
        on(0x6004001a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("ImoBwsTKBF"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnAction("ImoBwsTKBF");
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
        on(0x6004001d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("xSwFjjjzkJ"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxParameter("xSwFjjjzkJ");
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
        on(0x60040023).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("FbWGbHWDvq"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxTag("FbWGbHWDvq");
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
        on(0x60040025).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("ovKfDiZdyd"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxTooltipText("ovKfDiZdyd");
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

    @Test
    public void test_AddItem_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60050000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("YaJtQdpuvB"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AddItem("YaJtQdpuvB");
                    }
                });
    }

    @Test
    public void test_AddItem_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60050000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("pGRsFsKorN"), new Variant(617))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AddItem("pGRsFsKorN", new Variant(617));
                    }
                });
    }

    @Test
    public void test_Clear_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60050001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Clear();
                    }
                });
    }

    @Test
    public void test_getAxDropDownLines_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60050002).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxDropDownLines();
                    }
                });
    }

    @Test
    public void test_setAxDropDownLines_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60050002).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDropDownLines(42);
                    }
                });
    }

    @Test
    public void test_getAxDropDownWidth_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60050004).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxDropDownWidth();
                    }
                });
    }

    @Test
    public void test_setAxDropDownWidth_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60050004).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDropDownWidth(42);
                    }
                });
    }

    @Test
    public void test_getAxList_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60050006).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(42))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxList(42);
                    }
                });
    }

    @Test
    public void test_setAxList_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60050006).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42), new Variant
                ("XzALDdvYea"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxList(42, "XzALDdvYea");
                    }
                });
    }

    @Test
    public void test_getAxListCount_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60050008).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxListCount();
                    }
                });
    }

    @Test
    public void test_getAxListHeaderCount_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60050009).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxListHeaderCount();
                    }
                });
    }

    @Test
    public void test_setAxListHeaderCount_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60050009).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxListHeaderCount(42);
                    }
                });
    }

    @Test
    public void test_getAxListIndex_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6005000b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxListIndex();
                    }
                });
    }

    @Test
    public void test_setAxListIndex_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6005000b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxListIndex(42);
                    }
                });
    }

    @Test
    public void test_RemoveItem_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6005000d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.RemoveItem(42);
                    }
                });
    }

    @Test
    public void test_getAxStyle_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6005000e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxStyle();
                    }
                });
    }

    @Test
    public void test_setAxStyle_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6005000e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxStyle(42);
                    }
                });
    }

    @Test
    public void test_getAxText_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60050010).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxText();
                    }
                });
    }

    @Test
    public void test_setAxText_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60050010).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("LposLwBzWh"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxText("LposLwBzWh");
                    }
                });
    }

}