package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class FillFormatTest extends ActiveXDispatchableTestBase {

    private FillFormat component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new FillFormat(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(117), new Variant(43))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(117), new Variant(43));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(36))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(36));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(602))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(602));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(720), new Variant(493), new
                Variant(42L), new Variant(42L), new Variant(320))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(720), new Variant(493), 42L, 42L, new Variant(320));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(993), new
                Variant(42L), new Variant(42), new Variant(890), new Variant(19), new Variant(502), new Variant(788))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(993), 42L, 42, new Variant(890), new Variant(19), new
                                Variant(502), new Variant(788));
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
    public void test_Background_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Background();
                    }
                });
    }

    @Test
    public void test_OneColorGradient_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42), new Variant
                (42.32f))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.OneColorGradient(42, 42, 42.32f);
                    }
                });
    }

    @Test
    public void test_Patterned_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xc).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Patterned(42);
                    }
                });
    }

    @Test
    public void test_PresetGradient_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0xd).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42), new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PresetGradient(42, 42, 42);
                    }
                });
    }

    @Test
    public void test_PresetTextured_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PresetTextured(42);
                    }
                });
    }

    @Test
    public void test_Solid_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xf).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Solid();
                    }
                });
    }

    @Test
    public void test_TwoColorGradient_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.TwoColorGradient(42, 42);
                    }
                });
    }

    @Test
    public void test_UserPicture_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x11).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("IMslnXFxGM"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.UserPicture("IMslnXFxGM");
                    }
                });
    }

    @Test
    public void test_UserTextured_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x12).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("KPjlRsunSg"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.UserTextured("KPjlRsunSg");
                    }
                });
    }

    @Test
    public void test_getAxBackColor_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x64).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<ColorFormat>() {
                    @Override
                    public ColorFormat invoke() throws ActiveXException {
                        return component.getAxBackColor();
                    }
                });
    }

    @Test
    public void test_setAxBackColor_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x64).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(getMock(ColorFormat.class)))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxBackColor(getMock(ColorFormat.class));
                    }
                });
    }

    @Test
    public void test_getAxForeColor_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x65).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<ColorFormat>() {
                    @Override
                    public ColorFormat invoke() throws ActiveXException {
                        return component.getAxForeColor();
                    }
                });
    }

    @Test
    public void test_setAxForeColor_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x65).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(getMock(ColorFormat.class)))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxForeColor(getMock(ColorFormat.class));
                    }
                });
    }

    @Test
    public void test_getAxGradientColorType_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x66).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxGradientColorType();
                    }
                });
    }

    @Test
    public void test_getAxGradientDegree_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x67).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsFloat(new Returns<Float>() {
                    @Override
                    public Float invoke() throws ActiveXException {
                        return component.getAxGradientDegree();
                    }
                });
    }

    @Test
    public void test_getAxGradientStyle_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x68).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxGradientStyle();
                    }
                });
    }

    @Test
    public void test_getAxGradientVariant_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x69).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxGradientVariant();
                    }
                });
    }

    @Test
    public void test_getAxPattern_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxPattern();
                    }
                });
    }

    @Test
    public void test_getAxPresetGradientType_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxPresetGradientType();
                    }
                });
    }

    @Test
    public void test_getAxPresetTexture_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxPresetTexture();
                    }
                });
    }

    @Test
    public void test_getAxTextureName_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxTextureName();
                    }
                });
    }

    @Test
    public void test_getAxTextureType_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxTextureType();
                    }
                });
    }

    @Test
    public void test_getAxTransparency_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsFloat(new Returns<Float>() {
                    @Override
                    public Float invoke() throws ActiveXException {
                        return component.getAxTransparency();
                    }
                });
    }

    @Test
    public void test_setAxTransparency_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32f))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxTransparency(42.32f);
                    }
                });
    }

    @Test
    public void test_getAxType_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x70).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxType();
                    }
                });
    }

    @Test
    public void test_getAxVisible_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x71).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxVisible();
                    }
                });
    }

    @Test
    public void test_setAxVisible_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x71).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxVisible(42);
                    }
                });
    }

}