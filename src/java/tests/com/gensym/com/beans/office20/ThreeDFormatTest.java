package com.gensym.com.beans.office20;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class ThreeDFormatTest extends ActiveXDispatchableTestBase {

    private ThreeDFormat component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new ThreeDFormat(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(528), new Variant(839))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(528), new Variant(839));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(439))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(439));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(807))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(807));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(644), new Variant(330), new
                Variant(42L), new Variant(42L), new Variant(110))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(644), new Variant(330), 42L, 42L, new Variant(110));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(436), new
                Variant(42L), new Variant(42), new Variant(328), new Variant(584), new Variant(906), new Variant(761))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(436), 42L, 42, new Variant(328), new Variant(584), new
                                Variant(906), new Variant(761));
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
    public void test_IncrementRotationX_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42.32f))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.IncrementRotationX(42.32f);
                    }
                });
    }

    @Test
    public void test_IncrementRotationY_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42.32f))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.IncrementRotationY(42.32f);
                    }
                });
    }

    @Test
    public void test_ResetRotation_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ResetRotation();
                    }
                });
    }

    @Test
    public void test_SetThreeDFormat_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xd).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SetThreeDFormat(42);
                    }
                });
    }

    @Test
    public void test_SetExtrusionDirection_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SetExtrusionDirection(42);
                    }
                });
    }

    @Test
    public void test_getAxDepth_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x64).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsFloat(new Returns<Float>() {
                    @Override
                    public Float invoke() throws ActiveXException {
                        return component.getAxDepth();
                    }
                });
    }

    @Test
    public void test_setAxDepth_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x64).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32f))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDepth(42.32f);
                    }
                });
    }

    @Test
    public void test_getAxExtrusionColor_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x65).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<ColorFormat>() {
                    @Override
                    public ColorFormat invoke() throws ActiveXException {
                        return component.getAxExtrusionColor();
                    }
                });
    }

    @Test
    public void test_getAxExtrusionColorType_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x66).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxExtrusionColorType();
                    }
                });
    }

    @Test
    public void test_setAxExtrusionColorType_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x66).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxExtrusionColorType(42);
                    }
                });
    }

    @Test
    public void test_getAxPerspective_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x67).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxPerspective();
                    }
                });
    }

    @Test
    public void test_setAxPerspective_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x67).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPerspective(42);
                    }
                });
    }

    @Test
    public void test_getAxPresetExtrusionDirection_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x68).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxPresetExtrusionDirection();
                    }
                });
    }

    @Test
    public void test_getAxPresetLightingDirection_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x69).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxPresetLightingDirection();
                    }
                });
    }

    @Test
    public void test_setAxPresetLightingDirection_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x69).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPresetLightingDirection(42);
                    }
                });
    }

    @Test
    public void test_getAxPresetLightingSoftness_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxPresetLightingSoftness();
                    }
                });
    }

    @Test
    public void test_setAxPresetLightingSoftness_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPresetLightingSoftness(42);
                    }
                });
    }

    @Test
    public void test_getAxPresetMaterial_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxPresetMaterial();
                    }
                });
    }

    @Test
    public void test_setAxPresetMaterial_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPresetMaterial(42);
                    }
                });
    }

    @Test
    public void test_getAxPresetThreeDFormat_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxPresetThreeDFormat();
                    }
                });
    }

    @Test
    public void test_getAxRotationX_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsFloat(new Returns<Float>() {
                    @Override
                    public Float invoke() throws ActiveXException {
                        return component.getAxRotationX();
                    }
                });
    }

    @Test
    public void test_setAxRotationX_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32f))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxRotationX(42.32f);
                    }
                });
    }

    @Test
    public void test_getAxRotationY_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsFloat(new Returns<Float>() {
                    @Override
                    public Float invoke() throws ActiveXException {
                        return component.getAxRotationY();
                    }
                });
    }

    @Test
    public void test_setAxRotationY_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32f))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxRotationY(42.32f);
                    }
                });
    }

    @Test
    public void test_getAxVisible_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxVisible();
                    }
                });
    }

    @Test
    public void test_setAxVisible_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxVisible(42);
                    }
                });
    }

}