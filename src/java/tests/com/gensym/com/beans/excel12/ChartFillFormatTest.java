package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class ChartFillFormatTest extends ActiveXDispatchableTestBase {

    private ChartFillFormat component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new ChartFillFormat(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(547), new Variant(649))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(547), new Variant(649));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(973))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(973));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(160))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(160));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(164), new Variant(259), new
                Variant(42L), new Variant(42L), new Variant(776))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(164), new Variant(259), 42L, 42L, new Variant(776));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(185), new
                Variant(42L), new Variant(42), new Variant(720), new Variant(991), new Variant(526), new Variant(975))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(185), 42L, 42, new Variant(720), new Variant(991), new
                                Variant(526), new Variant(975));
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
    public void test_OneColorGradient_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x655).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42), new Variant
                (42.32f))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.OneColorGradient(42, 42, 42.32f);
                    }
                });
    }

    @Test
    public void test_TwoColorGradient_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x658).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.TwoColorGradient(42, 42);
                    }
                });
    }

    @Test
    public void test_PresetTextured_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x659).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PresetTextured(42);
                    }
                });
    }

    @Test
    public void test_Solid_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x65b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Solid();
                    }
                });
    }

    @Test
    public void test_Patterned_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x65c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Patterned(42);
                    }
                });
    }

    @Test
    public void test_UserPicture_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x65d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.UserPicture();
                    }
                });
    }

    @Test
    public void test_UserPicture_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x65d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(274))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.UserPicture(new Variant(274));
                    }
                });
    }

    @Test
    public void test_UserPicture_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x65d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(230), new Variant(182))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.UserPicture(new Variant(230), new Variant(182));
                    }
                });
    }

    @Test
    public void test_UserPicture_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x65d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(216), new Variant(551), new
                Variant(930))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.UserPicture(new Variant(216), new Variant(551), new Variant(930));
                    }
                });
    }

    @Test
    public void test_UserPicture_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x65d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(109), new Variant(915), new
                Variant(655), new Variant(647))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.UserPicture(new Variant(109), new Variant(915), new Variant(655), new Variant(647));
                    }
                });
    }

    @Test
    public void test_UserTextured_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x662).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("HbgQcAyurA"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.UserTextured("HbgQcAyurA");
                    }
                });
    }

    @Test
    public void test_PresetGradient_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x664).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42), new Variant
                (42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PresetGradient(42, 42, 42);
                    }
                });
    }

    @Test
    public void test_getAxBackColor_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x666).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<ChartColorFormat>() {
                    @Override
                    public ChartColorFormat invoke() throws ActiveXException {
                        return component.getAxBackColor();
                    }
                });
    }

    @Test
    public void test_getAxForeColor_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x667).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<ChartColorFormat>() {
                    @Override
                    public ChartColorFormat invoke() throws ActiveXException {
                        return component.getAxForeColor();
                    }
                });
    }

    @Test
    public void test_getAxGradientColorType_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x668).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxGradientColorType();
                    }
                });
    }

    @Test
    public void test_getAxGradientDegree_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x669).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsFloat(new Returns<Float>() {
                    @Override
                    public Float invoke() throws ActiveXException {
                        return component.getAxGradientDegree();
                    }
                });
    }

    @Test
    public void test_getAxGradientStyle_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x66a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxGradientStyle();
                    }
                });
    }

    @Test
    public void test_getAxGradientVariant_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x66b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxGradientVariant();
                    }
                });
    }

    @Test
    public void test_getAxPattern_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxPattern();
                    }
                });
    }

    @Test
    public void test_getAxPresetGradientType_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x665).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxPresetGradientType();
                    }
                });
    }

    @Test
    public void test_getAxPresetTexture_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x65a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxPresetTexture();
                    }
                });
    }

    @Test
    public void test_getAxTextureName_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x66c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxTextureName();
                    }
                });
    }

    @Test
    public void test_getAxTextureType_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x66d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxTextureType();
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
    public void test_getAxVisible_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x22e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxVisible();
                    }
                });
    }

    @Test
    public void test_setAxVisible_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x22e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxVisible(42);
                    }
                });
    }

}