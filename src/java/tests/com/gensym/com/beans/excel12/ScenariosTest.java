package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class ScenariosTest extends ActiveXDispatchableTestBase {

    private Scenarios component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new Scenarios(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(94), new Variant(709))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(94), new Variant(709));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(780))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(780));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(663))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(663));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(406), new Variant(753), new
                Variant(42L), new Variant(42L), new Variant(778))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(406), new Variant(753), 42L, 42L, new Variant(778));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(589), new
                Variant(42L), new Variant(42), new Variant(221), new Variant(900), new Variant(44), new Variant(815))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(589), 42L, 42, new Variant(221), new Variant(900), new
                                Variant(44), new Variant(815));
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
    public void test_Add_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("NgSlgGgbHz"), new Variant(375))
                .verifyReturnsDispatchable(new Returns<Scenario>() {
                    @Override
                    public Scenario invoke() throws ActiveXException {
                        return component.Add("NgSlgGgbHz", new Variant(375));
                    }
                });
    }

    @Test
    public void test_Add_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("nkVrFiBKTj"), new Variant(966),
                new Variant(920))
                .verifyReturnsDispatchable(new Returns<Scenario>() {
                    @Override
                    public Scenario invoke() throws ActiveXException {
                        return component.Add("nkVrFiBKTj", new Variant(966), new Variant(920));
                    }
                });
    }

    @Test
    public void test_Add_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("YgAfKIIObO"), new Variant(797),
                new Variant(464), new Variant(512))
                .verifyReturnsDispatchable(new Returns<Scenario>() {
                    @Override
                    public Scenario invoke() throws ActiveXException {
                        return component.Add("YgAfKIIObO", new Variant(797), new Variant(464), new Variant(512));
                    }
                });
    }

    @Test
    public void test_Add_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("CFPooofhYc"), new Variant(97), new
                Variant(922), new Variant(907), new Variant(476))
                .verifyReturnsDispatchable(new Returns<Scenario>() {
                    @Override
                    public Scenario invoke() throws ActiveXException {
                        return component.Add("CFPooofhYc", new Variant(97), new Variant(922), new Variant(907), new
                                Variant(476));
                    }
                });
    }

    @Test
    public void test_Add_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("JBqUNdBkjA"), new Variant(875),
                new Variant(828), new Variant(89), new Variant(595), new Variant(326))
                .verifyReturnsDispatchable(new Returns<Scenario>() {
                    @Override
                    public Scenario invoke() throws ActiveXException {
                        return component.Add("JBqUNdBkjA", new Variant(875), new Variant(828), new Variant(89), new
                                Variant(595), new Variant(326));
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
    public void test_CreateSummary_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x391).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CreateSummary(42);
                    }
                });
    }

    @Test
    public void test_CreateSummary_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x391).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(846))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CreateSummary(42, new Variant(846));
                    }
                });
    }

    @Test
    public void test_Item_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xaa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(85))
                .verifyReturnsDispatchable(new Returns<Scenario>() {
                    @Override
                    public Scenario invoke() throws ActiveXException {
                        return component.Item(new Variant(85));
                    }
                });
    }

    @Test
    public void test_Merge_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x234).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(889))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Merge(new Variant(889));
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