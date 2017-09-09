package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class TrendlinesTest extends ActiveXDispatchableTestBase {

    private Trendlines component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new Trendlines(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(371), new Variant(314))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(371), new Variant(314));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(24))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(24));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(672))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(672));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(443), new Variant(968), new
                Variant(42L), new Variant(42L), new Variant(709))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(443), new Variant(968), 42L, 42L, new Variant(709));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(152), new
                Variant(42L), new Variant(42), new Variant(958), new Variant(915), new Variant(543), new Variant(877))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(152), 42L, 42, new Variant(958), new Variant(915), new
                                Variant(543), new Variant(877));
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
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyReturnsDispatchable(new Returns<Trendline>() {
                    @Override
                    public Trendline invoke() throws ActiveXException {
                        return component.Add(42);
                    }
                });
    }

    @Test
    public void test_Add_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(227))
                .verifyReturnsDispatchable(new Returns<Trendline>() {
                    @Override
                    public Trendline invoke() throws ActiveXException {
                        return component.Add(42, new Variant(227));
                    }
                });
    }

    @Test
    public void test_Add_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(841), new Variant
                (399))
                .verifyReturnsDispatchable(new Returns<Trendline>() {
                    @Override
                    public Trendline invoke() throws ActiveXException {
                        return component.Add(42, new Variant(841), new Variant(399));
                    }
                });
    }

    @Test
    public void test_Add_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(594), new Variant
                (106), new Variant(371))
                .verifyReturnsDispatchable(new Returns<Trendline>() {
                    @Override
                    public Trendline invoke() throws ActiveXException {
                        return component.Add(42, new Variant(594), new Variant(106), new Variant(371));
                    }
                });
    }

    @Test
    public void test_Add_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(565), new Variant
                (554), new Variant(48), new Variant(519))
                .verifyReturnsDispatchable(new Returns<Trendline>() {
                    @Override
                    public Trendline invoke() throws ActiveXException {
                        return component.Add(42, new Variant(565), new Variant(554), new Variant(48), new Variant(519));
                    }
                });
    }

    @Test
    public void test_Add_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(736), new Variant
                (767), new Variant(159), new Variant(867), new Variant(467))
                .verifyReturnsDispatchable(new Returns<Trendline>() {
                    @Override
                    public Trendline invoke() throws ActiveXException {
                        return component.Add(42, new Variant(736), new Variant(767), new Variant(159), new Variant
                                (867), new Variant(467));
                    }
                });
    }

    @Test
    public void test_Add_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(69), new Variant
                (753), new Variant(162), new Variant(983), new Variant(454), new Variant(234))
                .verifyReturnsDispatchable(new Returns<Trendline>() {
                    @Override
                    public Trendline invoke() throws ActiveXException {
                        return component.Add(42, new Variant(69), new Variant(753), new Variant(162), new Variant
                                (983), new Variant(454), new Variant(234));
                    }
                });
    }

    @Test
    public void test_Add_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(676), new Variant
                (423), new Variant(558), new Variant(416), new Variant(533), new Variant(348), new Variant(511))
                .verifyReturnsDispatchable(new Returns<Trendline>() {
                    @Override
                    public Trendline invoke() throws ActiveXException {
                        return component.Add(42, new Variant(676), new Variant(423), new Variant(558), new Variant
                                (416), new Variant(533), new Variant(348), new Variant(511));
                    }
                });
    }

    @Test
    public void test_Add_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(96), new Variant
                (343), new Variant(245), new Variant(399), new Variant(333), new Variant(531), new Variant(162), new
                Variant(340))
                .verifyReturnsDispatchable(new Returns<Trendline>() {
                    @Override
                    public Trendline invoke() throws ActiveXException {
                        return component.Add(42, new Variant(96), new Variant(343), new Variant(245), new Variant
                                (399), new Variant(333), new Variant(531), new Variant(162), new Variant(340));
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
    public void test_Item_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xaa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchable(new Returns<Trendline>() {
                    @Override
                    public Trendline invoke() throws ActiveXException {
                        return component.Item();
                    }
                });
    }

    @Test
    public void test_Item_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xaa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(463))
                .verifyReturnsDispatchable(new Returns<Trendline>() {
                    @Override
                    public Trendline invoke() throws ActiveXException {
                        return component.Item(new Variant(463));
                    }
                });
    }

    @Test
    public void test__NewEnum_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xfffffffc).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsGenericValue(new Returns<Object>() {
                    @Override
                    public Object invoke() throws ActiveXException {
                        return component._NewEnum();
                    }
                });
    }

}