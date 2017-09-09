package com.gensym.com.beans.excel12;

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
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(800), new Variant(206))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(800), new Variant(206));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(881))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(881));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(487))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(487));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(891), new Variant(934), new
                Variant(42L), new Variant(42L), new Variant(162))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(891), new Variant(934), 42L, 42L, new Variant(162));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(934), new
                Variant(42L), new Variant(42), new Variant(66), new Variant(22), new Variant(696), new Variant(626))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(934), 42L, 42, new Variant(66), new Variant(22), new Variant
                                (696), new Variant(626));
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
    public void test_Item_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xaa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(471))
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.Item(new Variant(471));
                    }
                });
    }

    @Test
    public void test__Default_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(201))
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component._Default(new Variant(201));
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
        on(0x6b1).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42.32f), new
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
        on(0x6b2).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42.32f), new
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
        on(0x6b7).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(228))
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.AddCurve(new Variant(228));
                    }
                });
    }

    @Test
    public void test_AddLabel_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6b9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42.32f), new
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
        on(0x6ba).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42.32f), new Variant(42.32f), new
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
        on(0x6bb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("RRKMLoiVUE"), new Variant(42),
                new Variant(42), new Variant(42.32f), new Variant(42.32f), new Variant(42.32f), new Variant(42.32f))
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.AddPicture("RRKMLoiVUE", 42, 42, 42.32f, 42.32f, 42.32f, 42.32f);
                    }
                });
    }

    @Test
    public void test_AddPolyline_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6be).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(996))
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.AddPolyline(new Variant(996));
                    }
                });
    }

    @Test
    public void test_AddShape_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6bf).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42.32f), new
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
        on(0x6c0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant("qKAJfmjnnx"),
                new Variant("jhDMmrhaDN"), new Variant(42.32f), new Variant(42), new Variant(42), new Variant(42.32f)
                , new Variant(42.32f))
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.AddTextEffect(42, "qKAJfmjnnx", "jhDMmrhaDN", 42.32f, 42, 42, 42.32f, 42.32f);
                    }
                });
    }

    @Test
    public void test_AddTextbox_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6c6).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42.32f), new
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
        on(0x6c7).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42.32f), new
                Variant(42.32f))
                .verifyReturnsDispatchable(new Returns<FreeformBuilder>() {
                    @Override
                    public FreeformBuilder invoke() throws ActiveXException {
                        return component.BuildFreeform(42, 42.32f, 42.32f);
                    }
                });
    }

    @Test
    public void test_getAxRange_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xc5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(344))
                .verifyReturnsDispatchable(new Returns<ShapeRange>() {
                    @Override
                    public ShapeRange invoke() throws ActiveXException {
                        return component.getAxRange(new Variant(344));
                    }
                });
    }

    @Test
    public void test_SelectAll_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6c9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SelectAll();
                    }
                });
    }

    @Test
    public void test_AddFormControl_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6ca).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42), new Variant
                (42), new Variant(42), new Variant(42))
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.AddFormControl(42, 42, 42, 42, 42);
                    }
                });
    }

    @Test
    public void test_AddOLEObject_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6cb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.AddOLEObject();
                    }
                });
    }

    @Test
    public void test_AddOLEObject_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6cb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(885))
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.AddOLEObject(new Variant(885));
                    }
                });
    }

    @Test
    public void test_AddOLEObject_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6cb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(975), new Variant(433))
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.AddOLEObject(new Variant(975), new Variant(433));
                    }
                });
    }

    @Test
    public void test_AddOLEObject_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6cb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(869), new Variant(462), new
                Variant(466))
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.AddOLEObject(new Variant(869), new Variant(462), new Variant(466));
                    }
                });
    }

    @Test
    public void test_AddOLEObject_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6cb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(668), new Variant(648), new
                Variant(344), new Variant(167))
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.AddOLEObject(new Variant(668), new Variant(648), new Variant(344), new
                                Variant(167));
                    }
                });
    }

    @Test
    public void test_AddOLEObject_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6cb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(859), new Variant(854), new
                Variant(474), new Variant(51), new Variant(215))
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.AddOLEObject(new Variant(859), new Variant(854), new Variant(474), new
                                Variant(51), new Variant(215));
                    }
                });
    }

    @Test
    public void test_AddOLEObject_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6cb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(704), new Variant(421), new
                Variant(218), new Variant(50), new Variant(246), new Variant(867))
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.AddOLEObject(new Variant(704), new Variant(421), new Variant(218), new
                                Variant(50), new Variant(246), new Variant(867));
                    }
                });
    }

    @Test
    public void test_AddOLEObject_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6cb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(23), new Variant(637), new Variant
                (881), new Variant(85), new Variant(335), new Variant(89), new Variant(299))
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.AddOLEObject(new Variant(23), new Variant(637), new Variant(881), new
                                Variant(85), new Variant(335), new Variant(89), new Variant(299));
                    }
                });
    }

    @Test
    public void test_AddOLEObject_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6cb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(877), new Variant(401), new
                Variant(67), new Variant(550), new Variant(274), new Variant(132), new Variant(333), new Variant(397))
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.AddOLEObject(new Variant(877), new Variant(401), new Variant(67), new
                                Variant(550), new Variant(274), new Variant(132), new Variant(333), new Variant(397));
                    }
                });
    }

    @Test
    public void test_AddOLEObject_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6cb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(226), new Variant(77), new Variant
                (543), new Variant(83), new Variant(802), new Variant(691), new Variant(285), new Variant(6), new
                Variant(312))
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.AddOLEObject(new Variant(226), new Variant(77), new Variant(543), new
                                Variant(83), new Variant(802), new Variant(691), new Variant(285), new Variant(6),
                                new Variant(312));
                    }
                });
    }

    @Test
    public void test_AddOLEObject_TenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6cb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(521), new Variant(738), new
                Variant(71), new Variant(265), new Variant(655), new Variant(682), new Variant(714), new Variant(423)
                , new Variant(333), new Variant(485))
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.AddOLEObject(new Variant(521), new Variant(738), new Variant(71), new
                                Variant(265), new Variant(655), new Variant(682), new Variant(714), new Variant(423),
                                new Variant(333), new Variant(485));
                    }
                });
    }

    @Test
    public void test_AddOLEObject_ElevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6cb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(268), new Variant(874), new
                Variant(6), new Variant(871), new Variant(941), new Variant(872), new Variant(788), new Variant(508),
                new Variant(532), new Variant(991), new Variant(486))
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.AddOLEObject(new Variant(268), new Variant(874), new Variant(6), new Variant
                                (871), new Variant(941), new Variant(872), new Variant(788), new Variant(508), new
                                Variant(532), new Variant(991), new Variant(486));
                    }
                });
    }

}