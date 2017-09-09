package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class MenuItemsTest extends ActiveXDispatchableTestBase {

    private MenuItems component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new MenuItems(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(21), new Variant(507))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(21), new Variant(507));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(568))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(568));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(522))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(522));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(332), new Variant(486), new
                Variant(42L), new Variant(42L), new Variant(736))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(332), new Variant(486), 42L, 42L, new Variant(736));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(40), new
                Variant(42L), new Variant(42), new Variant(806), new Variant(542), new Variant(639), new Variant(995))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(40), 42L, 42, new Variant(806), new Variant(542), new
                                Variant(639), new Variant(995));
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
    public void test_Add_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("CEDXNiLaSh"))
                .verifyReturnsDispatchable(new Returns<MenuItem>() {
                    @Override
                    public MenuItem invoke() throws ActiveXException {
                        return component.Add("CEDXNiLaSh");
                    }
                });
    }

    @Test
    public void test_Add_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("zPxSGdmXEs"), new Variant(513))
                .verifyReturnsDispatchable(new Returns<MenuItem>() {
                    @Override
                    public MenuItem invoke() throws ActiveXException {
                        return component.Add("zPxSGdmXEs", new Variant(513));
                    }
                });
    }

    @Test
    public void test_Add_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("KFahpzqLXF"), new Variant(852),
                new Variant(278))
                .verifyReturnsDispatchable(new Returns<MenuItem>() {
                    @Override
                    public MenuItem invoke() throws ActiveXException {
                        return component.Add("KFahpzqLXF", new Variant(852), new Variant(278));
                    }
                });
    }

    @Test
    public void test_Add_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("ngRbQqlHcj"), new Variant(119),
                new Variant(207), new Variant(884))
                .verifyReturnsDispatchable(new Returns<MenuItem>() {
                    @Override
                    public MenuItem invoke() throws ActiveXException {
                        return component.Add("ngRbQqlHcj", new Variant(119), new Variant(207), new Variant(884));
                    }
                });
    }

    @Test
    public void test_Add_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("zGdpaDWiEJ"), new Variant(641),
                new Variant(269), new Variant(243), new Variant(146))
                .verifyReturnsDispatchable(new Returns<MenuItem>() {
                    @Override
                    public MenuItem invoke() throws ActiveXException {
                        return component.Add("zGdpaDWiEJ", new Variant(641), new Variant(269), new Variant(243), new
                                Variant(146));
                    }
                });
    }

    @Test
    public void test_Add_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("qlkqfbDqpy"), new Variant(668),
                new Variant(371), new Variant(372), new Variant(177), new Variant(561))
                .verifyReturnsDispatchable(new Returns<MenuItem>() {
                    @Override
                    public MenuItem invoke() throws ActiveXException {
                        return component.Add("qlkqfbDqpy", new Variant(668), new Variant(371), new Variant(372), new
                                Variant(177), new Variant(561));
                    }
                });
    }

    @Test
    public void test_Add_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("zRdyDurLgG"), new Variant(341),
                new Variant(687), new Variant(551), new Variant(895), new Variant(63), new Variant(668))
                .verifyReturnsDispatchable(new Returns<MenuItem>() {
                    @Override
                    public MenuItem invoke() throws ActiveXException {
                        return component.Add("zRdyDurLgG", new Variant(341), new Variant(687), new Variant(551), new
                                Variant(895), new Variant(63), new Variant(668));
                    }
                });
    }

    @Test
    public void test_Add_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("YWxqzZIrXI"), new Variant(697),
                new Variant(380), new Variant(877), new Variant(843), new Variant(254), new Variant(922), new Variant
                        (498))
                .verifyReturnsDispatchable(new Returns<MenuItem>() {
                    @Override
                    public MenuItem invoke() throws ActiveXException {
                        return component.Add("YWxqzZIrXI", new Variant(697), new Variant(380), new Variant(877), new
                                Variant(843), new Variant(254), new Variant(922), new Variant(498));
                    }
                });
    }

    @Test
    public void test_AddMenu_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x256).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("TOQTwDDvMv"))
                .verifyReturnsDispatchable(new Returns<Menu>() {
                    @Override
                    public Menu invoke() throws ActiveXException {
                        return component.AddMenu("TOQTwDDvMv");
                    }
                });
    }

    @Test
    public void test_AddMenu_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x256).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("GPPlEzKXLQ"), new Variant(815))
                .verifyReturnsDispatchable(new Returns<Menu>() {
                    @Override
                    public Menu invoke() throws ActiveXException {
                        return component.AddMenu("GPPlEzKXLQ", new Variant(815));
                    }
                });
    }

    @Test
    public void test_AddMenu_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x256).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("xbKoiduRhm"), new Variant(762),
                new Variant(384))
                .verifyReturnsDispatchable(new Returns<Menu>() {
                    @Override
                    public Menu invoke() throws ActiveXException {
                        return component.AddMenu("xbKoiduRhm", new Variant(762), new Variant(384));
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
    public void test_getAx_Default_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(529))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAx_Default(new Variant(529));
                    }
                });
    }

    @Test
    public void test_getAxItem_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xaa).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(112))
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxItem(new Variant(112));
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

}