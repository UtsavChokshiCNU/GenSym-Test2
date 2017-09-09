package com.gensym.com.beans.office20;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class CommandBarsTest extends ActiveXDispatchableTestBase {

    private CommandBars component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new CommandBars(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(849), new Variant(157))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(849), new Variant(157));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(158))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(158));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(975))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(975));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(162), new Variant(180), new
                Variant(42L), new Variant(42L), new Variant(283))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(162), new Variant(180), 42L, 42L, new Variant(283));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(488), new
                Variant(42L), new Variant(42), new Variant(816), new Variant(300), new Variant(786), new Variant(736))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(488), 42L, 42, new Variant(816), new Variant(300), new
                                Variant(786), new Variant(736));
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
    public void test_getAxActionControl_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030000).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<CommandBarControl>() {
                    @Override
                    public CommandBarControl invoke() throws ActiveXException {
                        return component.getAxActionControl();
                    }
                });
    }

    @Test
    public void test_getAxActiveMenuBar_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030001).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<CommandBar>() {
                    @Override
                    public CommandBar invoke() throws ActiveXException {
                        return component.getAxActiveMenuBar();
                    }
                });
    }

    @Test
    public void test_Add_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchable(new Returns<CommandBar>() {
                    @Override
                    public CommandBar invoke() throws ActiveXException {
                        return component.Add();
                    }
                });
    }

    @Test
    public void test_Add_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60030002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(587))
                .verifyReturnsDispatchable(new Returns<CommandBar>() {
                    @Override
                    public CommandBar invoke() throws ActiveXException {
                        return component.Add(new Variant(587));
                    }
                });
    }

    @Test
    public void test_Add_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(86), new Variant(535))
                .verifyReturnsDispatchable(new Returns<CommandBar>() {
                    @Override
                    public CommandBar invoke() throws ActiveXException {
                        return component.Add(new Variant(86), new Variant(535));
                    }
                });
    }

    @Test
    public void test_Add_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(407), new Variant(364), new
                Variant(360))
                .verifyReturnsDispatchable(new Returns<CommandBar>() {
                    @Override
                    public CommandBar invoke() throws ActiveXException {
                        return component.Add(new Variant(407), new Variant(364), new Variant(360));
                    }
                });
    }

    @Test
    public void test_Add_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(787), new Variant(343), new
                Variant(543), new Variant(983))
                .verifyReturnsDispatchable(new Returns<CommandBar>() {
                    @Override
                    public CommandBar invoke() throws ActiveXException {
                        return component.Add(new Variant(787), new Variant(343), new Variant(543), new Variant(983));
                    }
                });
    }

    @Test
    public void test_getAxCount_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030003).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxCount();
                    }
                });
    }

    @Test
    public void test_getAxDisplayTooltips_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030004).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxDisplayTooltips();
                    }
                });
    }

    @Test
    public void test_setAxDisplayTooltips_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60030004).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDisplayTooltips(false);
                    }
                });
    }

    @Test
    public void test_getAxDisplayKeysInTooltips_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030006).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxDisplayKeysInTooltips();
                    }
                });
    }

    @Test
    public void test_setAxDisplayKeysInTooltips_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60030006).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDisplayKeysInTooltips(false);
                    }
                });
    }

    @Test
    public void test_FindControl_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030008).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchable(new Returns<CommandBarControl>() {
                    @Override
                    public CommandBarControl invoke() throws ActiveXException {
                        return component.FindControl();
                    }
                });
    }

    @Test
    public void test_FindControl_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60030008).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(65))
                .verifyReturnsDispatchable(new Returns<CommandBarControl>() {
                    @Override
                    public CommandBarControl invoke() throws ActiveXException {
                        return component.FindControl(new Variant(65));
                    }
                });
    }

    @Test
    public void test_FindControl_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030008).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(228), new Variant(880))
                .verifyReturnsDispatchable(new Returns<CommandBarControl>() {
                    @Override
                    public CommandBarControl invoke() throws ActiveXException {
                        return component.FindControl(new Variant(228), new Variant(880));
                    }
                });
    }

    @Test
    public void test_FindControl_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030008).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(777), new Variant(709), new
                Variant(123))
                .verifyReturnsDispatchable(new Returns<CommandBarControl>() {
                    @Override
                    public CommandBarControl invoke() throws ActiveXException {
                        return component.FindControl(new Variant(777), new Variant(709), new Variant(123));
                    }
                });
    }

    @Test
    public void test_FindControl_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030008).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(390), new Variant(392), new
                Variant(585), new Variant(798))
                .verifyReturnsDispatchable(new Returns<CommandBarControl>() {
                    @Override
                    public CommandBarControl invoke() throws ActiveXException {
                        return component.FindControl(new Variant(390), new Variant(392), new Variant(585), new
                                Variant(798));
                    }
                });
    }

    @Test
    public void test_getAxItem_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(784))
                .verifyReturnsDispatchable(new Returns<CommandBar>() {
                    @Override
                    public CommandBar invoke() throws ActiveXException {
                        return component.getAxItem(new Variant(784));
                    }
                });
    }

    @Test
    public void test_getAxLargeButtons_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6003000a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxLargeButtons();
                    }
                });
    }

    @Test
    public void test_setAxLargeButtons_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6003000a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxLargeButtons(false);
                    }
                });
    }

    @Test
    public void test_getAxMenuAnimationStyle_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6003000c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxMenuAnimationStyle();
                    }
                });
    }

    @Test
    public void test_setAxMenuAnimationStyle_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6003000c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMenuAnimationStyle(42);
                    }
                });
    }

    @Test
    public void test_getAx_NewEnum_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xfffffffc).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsGenericValue(new Returns<Object>() {
                    @Override
                    public Object invoke() throws ActiveXException {
                        return component.getAx_NewEnum();
                    }
                });
    }

    @Test
    public void test_getAxParent_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6003000f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxParent();
                    }
                });
    }

    @Test
    public void test_ReleaseFocus_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60030010).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ReleaseFocus();
                    }
                });
    }

}