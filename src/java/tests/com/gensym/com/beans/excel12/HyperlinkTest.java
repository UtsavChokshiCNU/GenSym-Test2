package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class HyperlinkTest extends ActiveXDispatchableTestBase {

    private Hyperlink component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new Hyperlink(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(29), new Variant(78))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(29), new Variant(78));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(420))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(420));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(839))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(839));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(873), new Variant(570), new
                Variant(42L), new Variant(42L), new Variant(812))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(873), new Variant(570), 42L, 42L, new Variant(812));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(503), new
                Variant(42L), new Variant(42), new Variant(846), new Variant(9), new Variant(67), new Variant(349))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(503), 42L, 42, new Variant(846), new Variant(9), new Variant
                                (67), new Variant(349));
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
    public void test_getAxName_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxName();
                    }
                });
    }

    @Test
    public void test_getAxRange_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxRange();
                    }
                });
    }

    @Test
    public void test_getAxShape_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x62e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.getAxShape();
                    }
                });
    }

    @Test
    public void test_getAxSubAddress_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5bf).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxSubAddress();
                    }
                });
    }

    @Test
    public void test_setAxSubAddress_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5bf).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("DZCHXNXFil"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSubAddress("DZCHXNXFil");
                    }
                });
    }

    @Test
    public void test_getAxAddress_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xec).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxAddress();
                    }
                });
    }

    @Test
    public void test_setAxAddress_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xec).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("yKzLlZYuUG"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxAddress("yKzLlZYuUG");
                    }
                });
    }

    @Test
    public void test_getAxType_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxType();
                    }
                });
    }

    @Test
    public void test_AddToFavorites_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5c4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AddToFavorites();
                    }
                });
    }

    @Test
    public void test_Delete_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x75).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Delete();
                    }
                });
    }

    @Test
    public void test_Follow_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x650).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Follow();
                    }
                });
    }

    @Test
    public void test_Follow_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x650).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(481))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Follow(new Variant(481));
                    }
                });
    }

    @Test
    public void test_Follow_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x650).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(2), new Variant(834))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Follow(new Variant(2), new Variant(834));
                    }
                });
    }

    @Test
    public void test_Follow_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x650).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(502), new Variant(551), new
                Variant(233))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Follow(new Variant(502), new Variant(551), new Variant(233));
                    }
                });
    }

    @Test
    public void test_Follow_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x650).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(219), new Variant(45), new Variant
                (330), new Variant(162))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Follow(new Variant(219), new Variant(45), new Variant(330), new Variant(162));
                    }
                });
    }

    @Test
    public void test_Follow_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x650).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(860), new Variant(549), new
                Variant(881), new Variant(703), new Variant(828))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Follow(new Variant(860), new Variant(549), new Variant(881), new Variant(703), new
                                Variant(828));
                    }
                });
    }

}