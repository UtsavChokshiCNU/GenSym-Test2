package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class ShapeTest extends ActiveXDispatchableTestBase {

    private Shape component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new Shape(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(858), new Variant(541))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(858), new Variant(541));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(853))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(853));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(916))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(916));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(414), new Variant(156), new
                Variant(42L), new Variant(42L), new Variant(563))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(414), new Variant(156), 42L, 42L, new Variant(563));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(468), new
                Variant(42L), new Variant(42), new Variant(290), new Variant(335), new Variant(797), new Variant(830))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(468), 42L, 42, new Variant(290), new Variant(335), new
                                Variant(797), new Variant(830));
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
    public void test_Apply_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x68b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Apply();
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
    public void test_Duplicate_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x40f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.Duplicate();
                    }
                });
    }

    @Test
    public void test_Flip_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x68c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Flip(42);
                    }
                });
    }

    @Test
    public void test_IncrementLeft_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x68e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42.32f))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.IncrementLeft(42.32f);
                    }
                });
    }

    @Test
    public void test_IncrementRotation_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x690).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42.32f))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.IncrementRotation(42.32f);
                    }
                });
    }

    @Test
    public void test_IncrementTop_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x691).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42.32f))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.IncrementTop(42.32f);
                    }
                });
    }

    @Test
    public void test_PickUp_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x692).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.PickUp();
                    }
                });
    }

    @Test
    public void test_RerouteConnections_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x693).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.RerouteConnections();
                    }
                });
    }

    @Test
    public void test_ScaleHeight_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x694).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42.32f), new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ScaleHeight(42.32f, 42);
                    }
                });
    }

    @Test
    public void test_ScaleHeight_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x694).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42.32f), new Variant(42), new
                Variant(376))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ScaleHeight(42.32f, 42, new Variant(376));
                    }
                });
    }

    @Test
    public void test_ScaleWidth_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x698).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42.32f), new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ScaleWidth(42.32f, 42);
                    }
                });
    }

    @Test
    public void test_ScaleWidth_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x698).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42.32f), new Variant(42), new
                Variant(482))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ScaleWidth(42.32f, 42, new Variant(482));
                    }
                });
    }

    @Test
    public void test_Select_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xeb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Select();
                    }
                });
    }

    @Test
    public void test_Select_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xeb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(996))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Select(new Variant(996));
                    }
                });
    }

    @Test
    public void test_SetShapesDefaultProperties_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x699).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SetShapesDefaultProperties();
                    }
                });
    }

    @Test
    public void test_Ungroup_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xf4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchable(new Returns<ShapeRange>() {
                    @Override
                    public ShapeRange invoke() throws ActiveXException {
                        return component.Ungroup();
                    }
                });
    }

    @Test
    public void test_ZOrder_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x26e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ZOrder(42);
                    }
                });
    }

    @Test
    public void test_getAxAdjustments_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x69b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Adjustments>() {
                    @Override
                    public Adjustments invoke() throws ActiveXException {
                        return component.getAxAdjustments();
                    }
                });
    }

    @Test
    public void test_getAxTextFrame_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x69c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<TextFrame>() {
                    @Override
                    public TextFrame invoke() throws ActiveXException {
                        return component.getAxTextFrame();
                    }
                });
    }

    @Test
    public void test_getAxAutoShapeType_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x69d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxAutoShapeType();
                    }
                });
    }

    @Test
    public void test_setAxAutoShapeType_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x69d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxAutoShapeType(42);
                    }
                });
    }

    @Test
    public void test_getAxCallout_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x69e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<CalloutFormat>() {
                    @Override
                    public CalloutFormat invoke() throws ActiveXException {
                        return component.getAxCallout();
                    }
                });
    }

    @Test
    public void test_getAxConnectionSiteCount_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x69f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxConnectionSiteCount();
                    }
                });
    }

    @Test
    public void test_getAxConnector_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6a0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxConnector();
                    }
                });
    }

    @Test
    public void test_getAxConnectorFormat_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6a1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<ConnectorFormat>() {
                    @Override
                    public ConnectorFormat invoke() throws ActiveXException {
                        return component.getAxConnectorFormat();
                    }
                });
    }

    @Test
    public void test_getAxFill_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x67f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<FillFormat>() {
                    @Override
                    public FillFormat invoke() throws ActiveXException {
                        return component.getAxFill();
                    }
                });
    }

    @Test
    public void test_getAxGroupItems_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6a2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<GroupShapes>() {
                    @Override
                    public GroupShapes invoke() throws ActiveXException {
                        return component.getAxGroupItems();
                    }
                });
    }

    @Test
    public void test_getAxHeight_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x7b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsFloat(new Returns<Float>() {
                    @Override
                    public Float invoke() throws ActiveXException {
                        return component.getAxHeight();
                    }
                });
    }

    @Test
    public void test_setAxHeight_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x7b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32f))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHeight(42.32f);
                    }
                });
    }

    @Test
    public void test_getAxHorizontalFlip_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6a3).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxHorizontalFlip();
                    }
                });
    }

    @Test
    public void test_getAxLeft_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x7f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsFloat(new Returns<Float>() {
                    @Override
                    public Float invoke() throws ActiveXException {
                        return component.getAxLeft();
                    }
                });
    }

    @Test
    public void test_setAxLeft_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x7f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32f))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxLeft(42.32f);
                    }
                });
    }

    @Test
    public void test_getAxLine_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x331).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<LineFormat>() {
                    @Override
                    public LineFormat invoke() throws ActiveXException {
                        return component.getAxLine();
                    }
                });
    }

    @Test
    public void test_getAxLockAspectRatio_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6a4).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxLockAspectRatio();
                    }
                });
    }

    @Test
    public void test_setAxLockAspectRatio_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6a4).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxLockAspectRatio(42);
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
    public void test_setAxName_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("aJpdnGKmWf"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxName("aJpdnGKmWf");
                    }
                });
    }

    @Test
    public void test_getAxNodes_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6a5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<ShapeNodes>() {
                    @Override
                    public ShapeNodes invoke() throws ActiveXException {
                        return component.getAxNodes();
                    }
                });
    }

    @Test
    public void test_getAxRotation_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsFloat(new Returns<Float>() {
                    @Override
                    public Float invoke() throws ActiveXException {
                        return component.getAxRotation();
                    }
                });
    }

    @Test
    public void test_setAxRotation_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32f))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxRotation(42.32f);
                    }
                });
    }

    @Test
    public void test_getAxPictureFormat_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x65f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<PictureFormat>() {
                    @Override
                    public PictureFormat invoke() throws ActiveXException {
                        return component.getAxPictureFormat();
                    }
                });
    }

    @Test
    public void test_getAxShadow_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x67).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<ShadowFormat>() {
                    @Override
                    public ShadowFormat invoke() throws ActiveXException {
                        return component.getAxShadow();
                    }
                });
    }

    @Test
    public void test_getAxTextEffect_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6a6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<TextEffectFormat>() {
                    @Override
                    public TextEffectFormat invoke() throws ActiveXException {
                        return component.getAxTextEffect();
                    }
                });
    }

    @Test
    public void test_getAxThreeD_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6a7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<ThreeDFormat>() {
                    @Override
                    public ThreeDFormat invoke() throws ActiveXException {
                        return component.getAxThreeD();
                    }
                });
    }

    @Test
    public void test_getAxTop_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x7e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsFloat(new Returns<Float>() {
                    @Override
                    public Float invoke() throws ActiveXException {
                        return component.getAxTop();
                    }
                });
    }

    @Test
    public void test_setAxTop_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x7e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32f))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxTop(42.32f);
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
    public void test_getAxVerticalFlip_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6a8).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxVerticalFlip();
                    }
                });
    }

    @Test
    public void test_getAxVertices_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x26d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxVertices();
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

    @Test
    public void test_getAxWidth_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x7a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsFloat(new Returns<Float>() {
                    @Override
                    public Float invoke() throws ActiveXException {
                        return component.getAxWidth();
                    }
                });
    }

    @Test
    public void test_setAxWidth_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x7a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32f))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxWidth(42.32f);
                    }
                });
    }

    @Test
    public void test_getAxZOrderPosition_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6a9).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxZOrderPosition();
                    }
                });
    }

    @Test
    public void test_getAxHyperlink_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6aa).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Hyperlink>() {
                    @Override
                    public Hyperlink invoke() throws ActiveXException {
                        return component.getAxHyperlink();
                    }
                });
    }

    @Test
    public void test_getAxBlackWhiteMode_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6ab).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxBlackWhiteMode();
                    }
                });
    }

    @Test
    public void test_setAxBlackWhiteMode_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6ab).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxBlackWhiteMode(42);
                    }
                });
    }

    @Test
    public void test_getAxDrawingObject_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6ac).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxDrawingObject();
                    }
                });
    }

    @Test
    public void test_getAxOnAction_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x254).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxOnAction();
                    }
                });
    }

    @Test
    public void test_setAxOnAction_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x254).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("zvEhaKhsuQ"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnAction("zvEhaKhsuQ");
                    }
                });
    }

    @Test
    public void test_getAxLocked_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxLocked();
                    }
                });
    }

    @Test
    public void test_setAxLocked_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x10d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxLocked(false);
                    }
                });
    }

    @Test
    public void test_getAxTopLeftCell_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x26c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxTopLeftCell();
                    }
                });
    }

    @Test
    public void test_getAxBottomRightCell_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x267).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxBottomRightCell();
                    }
                });
    }

    @Test
    public void test_getAxPlacement_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x269).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxPlacement();
                    }
                });
    }

    @Test
    public void test_setAxPlacement_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x269).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPlacement(42);
                    }
                });
    }

    @Test
    public void test_Copy_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x227).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Copy();
                    }
                });
    }

    @Test
    public void test_Cut_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x235).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Cut();
                    }
                });
    }

    @Test
    public void test_CopyPicture_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xd5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CopyPicture();
                    }
                });
    }

    @Test
    public void test_CopyPicture_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xd5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(883))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CopyPicture(new Variant(883));
                    }
                });
    }

    @Test
    public void test_CopyPicture_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xd5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(805), new Variant(502))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CopyPicture(new Variant(805), new Variant(502));
                    }
                });
    }

    @Test
    public void test_getAxControlFormat_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6ad).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<ControlFormat>() {
                    @Override
                    public ControlFormat invoke() throws ActiveXException {
                        return component.getAxControlFormat();
                    }
                });
    }

    @Test
    public void test_getAxLinkFormat_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6ae).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<LinkFormat>() {
                    @Override
                    public LinkFormat invoke() throws ActiveXException {
                        return component.getAxLinkFormat();
                    }
                });
    }

    @Test
    public void test_getAxOLEFormat_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6af).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<OLEFormat>() {
                    @Override
                    public OLEFormat invoke() throws ActiveXException {
                        return component.getAxOLEFormat();
                    }
                });
    }

    @Test
    public void test_getAxFormControlType_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6b0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxFormControlType();
                    }
                });
    }

}