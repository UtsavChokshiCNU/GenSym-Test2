package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class BordersTest extends ActiveXDispatchableTestBase {

    private Borders component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new Borders(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(47), new Variant(701))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(47), new Variant(701));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(446))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(446));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(735))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(735));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(640), new Variant(492), new
                Variant(42L), new Variant(42L), new Variant(176))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(640), new Variant(492), 42L, 42L, new Variant(176));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(26), new
                Variant(42L), new Variant(42), new Variant(10), new Variant(735), new Variant(93), new Variant(465))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(26), 42L, 42, new Variant(10), new Variant(735), new Variant
                                (93), new Variant(465));
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
    public void test_getAxColor_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x63).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxColor();
                    }
                });
    }

    @Test
    public void test_setAxColor_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x63).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(927))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxColor(new Variant(927));
                    }
                });
    }

    @Test
    public void test_getAxColorIndex_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x61).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxColorIndex();
                    }
                });
    }

    @Test
    public void test_setAxColorIndex_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x61).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(751))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxColorIndex(new Variant(751));
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
                .verifyReturnsDispatchable(new Returns<Border>() {
                    @Override
                    public Border invoke() throws ActiveXException {
                        return component.getAxItem(42);
                    }
                });
    }

    @Test
    public void test_getAxLineStyle_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x77).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxLineStyle();
                    }
                });
    }

    @Test
    public void test_setAxLineStyle_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x77).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(278))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxLineStyle(new Variant(278));
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
    public void test_getAxValue_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxValue();
                    }
                });
    }

    @Test
    public void test_setAxValue_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(234))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxValue(new Variant(234));
                    }
                });
    }

    @Test
    public void test_getAxWeight_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x78).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxWeight();
                    }
                });
    }

    @Test
    public void test_setAxWeight_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x78).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(215))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxWeight(new Variant(215));
                    }
                });
    }

    @Test
    public void test_getAx_Default_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(42))
                .verifyReturnsDispatchable(new Returns<Border>() {
                    @Override
                    public Border invoke() throws ActiveXException {
                        return component.getAx_Default(42);
                    }
                });
    }

}