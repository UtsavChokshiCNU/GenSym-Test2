package com.gensym.com.beans.office20;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class ShapesTest extends ActiveXDispatchableTestBase {

    private Shapes component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new Shapes(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(70), new Variant(518))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(70), new Variant(518));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(646))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(646));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(8))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(8));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(92), new Variant(869), new
                Variant(42L), new Variant(42L), new Variant(314))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(92), new Variant(869), 42L, 42L, new Variant(314));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(269), new
                Variant(42L), new Variant(42), new Variant(774), new Variant(122), new Variant(131), new Variant(80))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(269), 42L, 42, new Variant(774), new Variant(122), new
                                Variant(131), new Variant(80));
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
    public void test_getAxParent_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxParent();
                    }
                });
    }

    @Test
    public void test_getAxCount_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxCount();
                    }
                });
    }

    @Test
    public void test_Item_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(934))
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.Item(new Variant(934));
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
    public void test_AddCallout_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42.32f), new
                Variant(42.32f), new Variant(42.32f), new Variant(42.32f))
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.AddCallout(42, 42.32f, 42.32f, 42.32f, 42.32f);
                    }
                });
    }

    @Test
    public void test_AddConnector_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42.32f), new
                Variant(42.32f), new Variant(42.32f), new Variant(42.32f))
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.AddConnector(42, 42.32f, 42.32f, 42.32f, 42.32f);
                    }
                });
    }

    @Test
    public void test_AddCurve_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xc).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(676))
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.AddCurve(new Variant(676));
                    }
                });
    }

    @Test
    public void test_AddLabel_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0xd).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42.32f), new
                Variant(42.32f), new Variant(42.32f), new Variant(42.32f))
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.AddLabel(42, 42.32f, 42.32f, 42.32f, 42.32f);
                    }
                });
    }

    @Test
    public void test_AddLine_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0xe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42.32f), new Variant(42.32f), new
                Variant(42.32f), new Variant(42.32f))
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.AddLine(42.32f, 42.32f, 42.32f, 42.32f);
                    }
                });
    }

    @Test
    public void test_AddPicture_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0xf).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("GPKAcNbjqg"), new Variant(42), new
                Variant(42), new Variant(42.32f), new Variant(42.32f), new Variant(42.32f), new Variant(42.32f))
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.AddPicture("GPKAcNbjqg", 42, 42, 42.32f, 42.32f, 42.32f, 42.32f);
                    }
                });
    }

    @Test
    public void test_AddPolyline_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x10).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(162))
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.AddPolyline(new Variant(162));
                    }
                });
    }

    @Test
    public void test_AddShape_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42.32f), new
                Variant(42.32f), new Variant(42.32f), new Variant(42.32f))
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.AddShape(42, 42.32f, 42.32f, 42.32f, 42.32f);
                    }
                });
    }

    @Test
    public void test_AddTextEffect_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x12).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant("JcBQUZenuX"), new
                Variant("oGNdKlRyKy"), new Variant(42.32f), new Variant(42), new Variant(42), new Variant(42.32f),
                new Variant(42.32f))
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.AddTextEffect(42, "JcBQUZenuX", "oGNdKlRyKy", 42.32f, 42, 42, 42.32f, 42.32f);
                    }
                });
    }

    @Test
    public void test_AddTextbox_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x13).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42.32f), new
                Variant(42.32f), new Variant(42.32f), new Variant(42.32f))
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.AddTextbox(42, 42.32f, 42.32f, 42.32f, 42.32f);
                    }
                });
    }

    @Test
    public void test_BuildFreeform_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x14).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42.32f), new
                Variant(42.32f))
                .verifyReturnsDispatchable(new Returns<FreeformBuilder>() {
                    @Override
                    public FreeformBuilder invoke() throws ActiveXException {
                        return component.BuildFreeform(42, 42.32f, 42.32f);
                    }
                });
    }

    @Test
    public void test_Range_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x15).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(25))
                .verifyReturnsDispatchable(new Returns<ShapeRange>() {
                    @Override
                    public ShapeRange invoke() throws ActiveXException {
                        return component.Range(new Variant(25));
                    }
                });
    }

    @Test
    public void test_SelectAll_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x16).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SelectAll();
                    }
                });
    }

    @Test
    public void test_getAxBackground_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x64).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.getAxBackground();
                    }
                });
    }

    @Test
    public void test_getAxDefault_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x65).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.getAxDefault();
                    }
                });
    }

}