package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class SeriesCollectionTest extends ActiveXDispatchableTestBase {

    private SeriesCollection component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new SeriesCollection(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(684), new Variant(286))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(684), new Variant(286));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(496))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(496));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(737))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(737));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(244), new Variant(125), new
                Variant(42L), new Variant(42L), new Variant(989))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(244), new Variant(125), 42L, 42L, new Variant(989));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(741), new
                Variant(42L), new Variant(42), new Variant(977), new Variant(743), new Variant(705), new Variant(201))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(741), 42L, 42, new Variant(977), new Variant(743), new
                                Variant(705), new Variant(201));
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
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(236), new Variant(42))
                .verifyReturnsDispatchable(new Returns<Series>() {
                    @Override
                    public Series invoke() throws ActiveXException {
                        return component.Add(new Variant(236), 42);
                    }
                });
    }

    @Test
    public void test_Add_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(613), new Variant(42), new Variant
                (210))
                .verifyReturnsDispatchable(new Returns<Series>() {
                    @Override
                    public Series invoke() throws ActiveXException {
                        return component.Add(new Variant(613), 42, new Variant(210));
                    }
                });
    }

    @Test
    public void test_Add_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(762), new Variant(42), new Variant
                (846), new Variant(864))
                .verifyReturnsDispatchable(new Returns<Series>() {
                    @Override
                    public Series invoke() throws ActiveXException {
                        return component.Add(new Variant(762), 42, new Variant(846), new Variant(864));
                    }
                });
    }

    @Test
    public void test_Add_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(738), new Variant(42), new Variant
                (870), new Variant(575), new Variant(121))
                .verifyReturnsDispatchable(new Returns<Series>() {
                    @Override
                    public Series invoke() throws ActiveXException {
                        return component.Add(new Variant(738), 42, new Variant(870), new Variant(575), new Variant
                                (121));
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
    public void test_Extend_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xe3).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(873))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Extend(new Variant(873));
                    }
                });
    }

    @Test
    public void test_Extend_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xe3).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(21), new Variant(265))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Extend(new Variant(21), new Variant(265));
                    }
                });
    }

    @Test
    public void test_Extend_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0xe3).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(624), new Variant(772), new Variant
                (990))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Extend(new Variant(624), new Variant(772), new Variant(990));
                    }
                });
    }

    @Test
    public void test_Item_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xaa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(51))
                .verifyReturnsDispatchable(new Returns<Series>() {
                    @Override
                    public Series invoke() throws ActiveXException {
                        return component.Item(new Variant(51));
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

    @Test
    public void test_Paste_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xd3).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Paste(42);
                    }
                });
    }

    @Test
    public void test_Paste_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xd3).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(228))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Paste(42, new Variant(228));
                    }
                });
    }

    @Test
    public void test_Paste_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0xd3).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(228), new Variant
                (123))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Paste(42, new Variant(228), new Variant(123));
                    }
                });
    }

    @Test
    public void test_Paste_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0xd3).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(481), new Variant
                (805), new Variant(714))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Paste(42, new Variant(481), new Variant(805), new Variant(714));
                    }
                });
    }

    @Test
    public void test_Paste_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0xd3).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42), new Variant
                (425), new Variant(844), new Variant(574))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Paste(42, new Variant(42), new Variant(425), new Variant(844), new Variant(574));
                    }
                });
    }

    @Test
    public void test_NewSeries_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x45d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchable(new Returns<Series>() {
                    @Override
                    public Series invoke() throws ActiveXException {
                        return component.NewSeries();
                    }
                });
    }

}