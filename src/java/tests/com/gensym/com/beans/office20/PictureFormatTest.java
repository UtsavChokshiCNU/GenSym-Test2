package com.gensym.com.beans.office20;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

import java.awt.*;

public class PictureFormatTest extends ActiveXDispatchableTestBase {

    private PictureFormat component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new PictureFormat(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(278), new Variant(564))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(278), new Variant(564));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(345))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(345));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(216))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(216));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(148), new Variant(380), new
                Variant(42L), new Variant(42L), new Variant(616))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(148), new Variant(380), 42L, 42L, new Variant(616));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(596), new
                Variant(42L), new Variant(42), new Variant(322), new Variant(798), new Variant(106), new Variant(442))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(596), 42L, 42, new Variant(322), new Variant(798), new
                                Variant(106), new Variant(442));
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
    public void test_IncrementBrightness_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42.32f))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.IncrementBrightness(42.32f);
                    }
                });
    }

    @Test
    public void test_IncrementContrast_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42.32f))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.IncrementContrast(42.32f);
                    }
                });
    }

    @Test
    public void test_getAxBrightness_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x64).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsFloat(new Returns<Float>() {
                    @Override
                    public Float invoke() throws ActiveXException {
                        return component.getAxBrightness();
                    }
                });
    }

    @Test
    public void test_setAxBrightness_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x64).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32f))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxBrightness(42.32f);
                    }
                });
    }

    @Test
    public void test_getAxColorType_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x65).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxColorType();
                    }
                });
    }

    @Test
    public void test_setAxColorType_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x65).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxColorType(42);
                    }
                });
    }

    @Test
    public void test_getAxContrast_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x66).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsFloat(new Returns<Float>() {
                    @Override
                    public Float invoke() throws ActiveXException {
                        return component.getAxContrast();
                    }
                });
    }

    @Test
    public void test_setAxContrast_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x66).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32f))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxContrast(42.32f);
                    }
                });
    }

    @Test
    public void test_getAxCropBottom_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x67).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsFloat(new Returns<Float>() {
                    @Override
                    public Float invoke() throws ActiveXException {
                        return component.getAxCropBottom();
                    }
                });
    }

    @Test
    public void test_setAxCropBottom_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x67).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32f))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCropBottom(42.32f);
                    }
                });
    }

    @Test
    public void test_getAxCropLeft_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x68).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsFloat(new Returns<Float>() {
                    @Override
                    public Float invoke() throws ActiveXException {
                        return component.getAxCropLeft();
                    }
                });
    }

    @Test
    public void test_setAxCropLeft_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x68).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32f))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCropLeft(42.32f);
                    }
                });
    }

    @Test
    public void test_getAxCropRight_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x69).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsFloat(new Returns<Float>() {
                    @Override
                    public Float invoke() throws ActiveXException {
                        return component.getAxCropRight();
                    }
                });
    }

    @Test
    public void test_setAxCropRight_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x69).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32f))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCropRight(42.32f);
                    }
                });
    }

    @Test
    public void test_getAxCropTop_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsFloat(new Returns<Float>() {
                    @Override
                    public Float invoke() throws ActiveXException {
                        return component.getAxCropTop();
                    }
                });
    }

    @Test
    public void test_setAxCropTop_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32f))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCropTop(42.32f);
                    }
                });
    }

    @Test
    public void test_getAxTransparencyColor_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsColor(new Returns<Color>() {
                    @Override
                    public Color invoke() throws ActiveXException {
                        return component.getAxTransparencyColor();
                    }
                });
    }

    @Test
    public void test_setAxTransparencyColor_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(getMock(Color.class)))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxTransparencyColor(getMock(Color.class));
                    }
                });
    }

    @Test
    public void test_getAxTransparentBackground_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxTransparentBackground();
                    }
                });
    }

    @Test
    public void test_setAxTransparentBackground_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxTransparentBackground(42);
                    }
                });
    }

}