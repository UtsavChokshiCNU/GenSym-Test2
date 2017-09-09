package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class ToolbarButtonsTest extends ActiveXDispatchableTestBase {

    private ToolbarButtons component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new ToolbarButtons(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(884), new Variant(337))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(884), new Variant(337));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(963))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(963));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(34))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(34));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(433), new Variant(768), new
                Variant(42L), new Variant(42L), new Variant(720))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(433), new Variant(768), 42L, 42L, new Variant(720));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(357), new
                Variant(42L), new Variant(42), new Variant(370), new Variant(102), new Variant(997), new Variant(783))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(357), 42L, 42, new Variant(370), new Variant(102), new
                                Variant(997), new Variant(783));
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
    public void test_Add_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchable(new Returns<ToolbarButton>() {
                    @Override
                    public ToolbarButton invoke() throws ActiveXException {
                        return component.Add();
                    }
                });
    }

    @Test
    public void test_Add_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(645))
                .verifyReturnsDispatchable(new Returns<ToolbarButton>() {
                    @Override
                    public ToolbarButton invoke() throws ActiveXException {
                        return component.Add(new Variant(645));
                    }
                });
    }

    @Test
    public void test_Add_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(910), new Variant(551))
                .verifyReturnsDispatchable(new Returns<ToolbarButton>() {
                    @Override
                    public ToolbarButton invoke() throws ActiveXException {
                        return component.Add(new Variant(910), new Variant(551));
                    }
                });
    }

    @Test
    public void test_Add_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(711), new Variant(331), new Variant
                (331))
                .verifyReturnsDispatchable(new Returns<ToolbarButton>() {
                    @Override
                    public ToolbarButton invoke() throws ActiveXException {
                        return component.Add(new Variant(711), new Variant(331), new Variant(331));
                    }
                });
    }

    @Test
    public void test_Add_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(727), new Variant(547), new Variant
                (643), new Variant(277))
                .verifyReturnsDispatchable(new Returns<ToolbarButton>() {
                    @Override
                    public ToolbarButton invoke() throws ActiveXException {
                        return component.Add(new Variant(727), new Variant(547), new Variant(643), new Variant(277));
                    }
                });
    }

    @Test
    public void test_Add_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(998), new Variant(440), new Variant
                (602), new Variant(580), new Variant(787))
                .verifyReturnsDispatchable(new Returns<ToolbarButton>() {
                    @Override
                    public ToolbarButton invoke() throws ActiveXException {
                        return component.Add(new Variant(998), new Variant(440), new Variant(602), new Variant(580),
                                new Variant(787));
                    }
                });
    }

    @Test
    public void test_Add_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(925), new Variant(953), new Variant
                (228), new Variant(729), new Variant(365), new Variant(711))
                .verifyReturnsDispatchable(new Returns<ToolbarButton>() {
                    @Override
                    public ToolbarButton invoke() throws ActiveXException {
                        return component.Add(new Variant(925), new Variant(953), new Variant(228), new Variant(729),
                                new Variant(365), new Variant(711));
                    }
                });
    }

    @Test
    public void test_Add_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(358), new Variant(982), new Variant
                (239), new Variant(85), new Variant(414), new Variant(598), new Variant(860))
                .verifyReturnsDispatchable(new Returns<ToolbarButton>() {
                    @Override
                    public ToolbarButton invoke() throws ActiveXException {
                        return component.Add(new Variant(358), new Variant(982), new Variant(239), new Variant(85),
                                new Variant(414), new Variant(598), new Variant(860));
                    }
                });
    }

    @Test
    public void test_Add_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(296), new Variant(998), new Variant
                (183), new Variant(364), new Variant(617), new Variant(183), new Variant(892), new Variant(501))
                .verifyReturnsDispatchable(new Returns<ToolbarButton>() {
                    @Override
                    public ToolbarButton invoke() throws ActiveXException {
                        return component.Add(new Variant(296), new Variant(998), new Variant(183), new Variant(364),
                                new Variant(617), new Variant(183), new Variant(892), new Variant(501));
                    }
                });
    }

    @Test
    public void test_getAxCount_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x76).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxCount();
                    }
                });
    }

    @Test
    public void test_getAxItem_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xaa).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(42))
                .verifyReturnsDispatchable(new Returns<ToolbarButton>() {
                    @Override
                    public ToolbarButton invoke() throws ActiveXException {
                        return component.getAxItem(42);
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
    public void test_getAx_Default_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(42))
                .verifyReturnsDispatchable(new Returns<ToolbarButton>() {
                    @Override
                    public ToolbarButton invoke() throws ActiveXException {
                        return component.getAx_Default(42);
                    }
                });
    }

}