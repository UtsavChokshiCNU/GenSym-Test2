package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class WorkbooksTest extends ActiveXDispatchableTestBase {

    private Workbooks component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new Workbooks(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(510), new Variant(821))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(510), new Variant(821));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(109))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(109));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(995))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(995));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(896), new Variant(3), new
                Variant(42L), new Variant(42L), new Variant(509))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(896), new Variant(3), 42L, 42L, new Variant(509));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(944), new
                Variant(42L), new Variant(42), new Variant(599), new Variant(719), new Variant(528), new Variant(6))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(944), 42L, 42, new Variant(599), new Variant(719), new
                                Variant(528), new Variant(6));
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
    public void test_Add_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Add();
                    }
                });
    }

    @Test
    public void test_Add_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(69))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Add(new Variant(69));
                    }
                });
    }

    @Test
    public void test_Close_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x115).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Close();
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
        on(0xaa).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(282))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxItem(new Variant(282));
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
    public void test_Open_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2aa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("oFsUwbUljO"))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Open("oFsUwbUljO");
                    }
                });
    }

    @Test
    public void test_Open_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2aa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("iKivJdogcP"), new Variant(855))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Open("iKivJdogcP", new Variant(855));
                    }
                });
    }

    @Test
    public void test_Open_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2aa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("JvWBRTEjkT"), new Variant(89),
                new Variant(696))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Open("JvWBRTEjkT", new Variant(89), new Variant(696));
                    }
                });
    }

    @Test
    public void test_Open_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2aa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("GwoRTvyZub"), new Variant(274),
                new Variant(481), new Variant(17))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Open("GwoRTvyZub", new Variant(274), new Variant(481), new Variant(17));
                    }
                });
    }

    @Test
    public void test_Open_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2aa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("TivggfYtJz"), new Variant(129),
                new Variant(467), new Variant(447), new Variant(161))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Open("TivggfYtJz", new Variant(129), new Variant(467), new Variant(447), new
                                Variant(161));
                    }
                });
    }

    @Test
    public void test_Open_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2aa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("jehgvAzEnL"), new Variant(628),
                new Variant(930), new Variant(920), new Variant(556), new Variant(10))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Open("jehgvAzEnL", new Variant(628), new Variant(930), new Variant(920), new
                                Variant(556), new Variant(10));
                    }
                });
    }

    @Test
    public void test_Open_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2aa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("UOcPrwCRzF"), new Variant(238),
                new Variant(216), new Variant(95), new Variant(234), new Variant(755), new Variant(139))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Open("UOcPrwCRzF", new Variant(238), new Variant(216), new Variant(95), new
                                Variant(234), new Variant(755), new Variant(139));
                    }
                });
    }

    @Test
    public void test_Open_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2aa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("BNLCIZqhey"), new Variant(782),
                new Variant(175), new Variant(156), new Variant(888), new Variant(711), new Variant(299), new Variant
                        (132))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Open("BNLCIZqhey", new Variant(782), new Variant(175), new Variant(156), new
                                Variant(888), new Variant(711), new Variant(299), new Variant(132));
                    }
                });
    }

    @Test
    public void test_Open_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2aa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("tMTpQWRCzM"), new Variant(648),
                new Variant(773), new Variant(849), new Variant(442), new Variant(750), new Variant(778), new Variant
                        (455), new Variant(455))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Open("tMTpQWRCzM", new Variant(648), new Variant(773), new Variant(849), new
                                Variant(442), new Variant(750), new Variant(778), new Variant(455), new Variant(455));
                    }
                });
    }

    @Test
    public void test_Open_TenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2aa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("JNTLzrQXuu"), new Variant(248),
                new Variant(29), new Variant(482), new Variant(796), new Variant(451), new Variant(363), new Variant
                        (524), new Variant(788), new Variant(814))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Open("JNTLzrQXuu", new Variant(248), new Variant(29), new Variant(482), new
                                Variant(796), new Variant(451), new Variant(363), new Variant(524), new Variant(788),
                                new Variant(814));
                    }
                });
    }

    @Test
    public void test_Open_ElevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2aa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("SLJmGiWodm"), new Variant(885),
                new Variant(680), new Variant(188), new Variant(829), new Variant(870), new Variant(422), new Variant
                        (603), new Variant(357), new Variant(424), new Variant(994))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Open("SLJmGiWodm", new Variant(885), new Variant(680), new Variant(188), new
                                Variant(829), new Variant(870), new Variant(422), new Variant(603), new Variant(357),
                                new Variant(424), new Variant(994));
                    }
                });
    }

    @Test
    public void test_Open_TwelveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2aa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("MEwAxTHjXY"), new Variant(594),
                new Variant(767), new Variant(538), new Variant(495), new Variant(49), new Variant(526), new Variant
                        (823), new Variant(193), new Variant(578), new Variant(226), new Variant(485))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Open("MEwAxTHjXY", new Variant(594), new Variant(767), new Variant(538), new
                                Variant(495), new Variant(49), new Variant(526), new Variant(823), new Variant(193),
                                new Variant(578), new Variant(226), new Variant(485));
                    }
                });
    }

    @Test
    public void test_Open_ThirteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2aa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("xaKjzHQEVM"), new Variant(688),
                new Variant(806), new Variant(503), new Variant(201), new Variant(992), new Variant(83), new Variant
                        (895), new Variant(4), new Variant(6), new Variant(791), new Variant(196), new Variant(428))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Open("xaKjzHQEVM", new Variant(688), new Variant(806), new Variant(503), new
                                Variant(201), new Variant(992), new Variant(83), new Variant(895), new Variant(4),
                                new Variant(6), new Variant(791), new Variant(196), new Variant(428));
                    }
                });
    }

    @Test
    public void test_OpenText_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ab).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("avWHGlJnmn"), new Variant(173),
                new Variant(564), new Variant(426), new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.OpenText("avWHGlJnmn", new Variant(173), new Variant(564), new Variant(426), 42);
                    }
                });
    }

    @Test
    public void test_OpenText_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ab).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("bqIBhxzhMP"), new Variant(810),
                new Variant(405), new Variant(800), new Variant(42), new Variant(257))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.OpenText("bqIBhxzhMP", new Variant(810), new Variant(405), new Variant(800), 42,
                                new Variant(257));
                    }
                });
    }

    @Test
    public void test_OpenText_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ab).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("KEvXoWuezp"), new Variant(235),
                new Variant(765), new Variant(223), new Variant(42), new Variant(88), new Variant(597))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.OpenText("KEvXoWuezp", new Variant(235), new Variant(765), new Variant(223), 42,
                                new Variant(88), new Variant(597));
                    }
                });
    }

    @Test
    public void test_OpenText_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ab).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("PChpDGGsfY"), new Variant(688),
                new Variant(735), new Variant(108), new Variant(42), new Variant(376), new Variant(403), new Variant
                        (760))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.OpenText("PChpDGGsfY", new Variant(688), new Variant(735), new Variant(108), 42,
                                new Variant(376), new Variant(403), new Variant(760));
                    }
                });
    }

    @Test
    public void test_OpenText_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ab).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("PWJqdpojEX"), new Variant(849),
                new Variant(958), new Variant(902), new Variant(42), new Variant(118), new Variant(864), new Variant
                        (240), new Variant(185))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.OpenText("PWJqdpojEX", new Variant(849), new Variant(958), new Variant(902), 42,
                                new Variant(118), new Variant(864), new Variant(240), new Variant(185));
                    }
                });
    }

    @Test
    public void test_OpenText_TenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ab).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("sskgoNIwof"), new Variant(45),
                new Variant(190), new Variant(863), new Variant(42), new Variant(222), new Variant(943), new Variant
                        (101), new Variant(44), new Variant(516))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.OpenText("sskgoNIwof", new Variant(45), new Variant(190), new Variant(863), 42, new
                                Variant(222), new Variant(943), new Variant(101), new Variant(44), new Variant(516));
                    }
                });
    }

    @Test
    public void test_OpenText_ElevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ab).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("ooiRMMuSmw"), new Variant(412),
                new Variant(819), new Variant(556), new Variant(42), new Variant(556), new Variant(679), new Variant
                        (184), new Variant(468), new Variant(676), new Variant(617))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.OpenText("ooiRMMuSmw", new Variant(412), new Variant(819), new Variant(556), 42,
                                new Variant(556), new Variant(679), new Variant(184), new Variant(468), new Variant
                                        (676), new Variant(617));
                    }
                });
    }

    @Test
    public void test_OpenText_TwelveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ab).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("VJRBMLMTyI"), new Variant(766),
                new Variant(213), new Variant(424), new Variant(42), new Variant(877), new Variant(881), new Variant
                        (523), new Variant(377), new Variant(71), new Variant(29), new Variant(344))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.OpenText("VJRBMLMTyI", new Variant(766), new Variant(213), new Variant(424), 42,
                                new Variant(877), new Variant(881), new Variant(523), new Variant(377), new Variant
                                        (71), new Variant(29), new Variant(344));
                    }
                });
    }

    @Test
    public void test_OpenText_ThirteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ab).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("TGHfnjEkDR"), new Variant(350),
                new Variant(961), new Variant(839), new Variant(42), new Variant(512), new Variant(191), new Variant
                        (764), new Variant(308), new Variant(696), new Variant(160), new Variant(783), new Variant(245))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.OpenText("TGHfnjEkDR", new Variant(350), new Variant(961), new Variant(839), 42,
                                new Variant(512), new Variant(191), new Variant(764), new Variant(308), new Variant
                                        (696), new Variant(160), new Variant(783), new Variant(245));
                    }
                });
    }

    @Test
    public void test_OpenText_FourteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2ab).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("MiOyeVuSzD"), new Variant(656),
                new Variant(410), new Variant(55), new Variant(42), new Variant(748), new Variant(434), new Variant
                        (93), new Variant(364), new Variant(376), new Variant(311), new Variant(970), new Variant
                        (163), new Variant(29))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.OpenText("MiOyeVuSzD", new Variant(656), new Variant(410), new Variant(55), 42, new
                                Variant(748), new Variant(434), new Variant(93), new Variant(364), new Variant(376),
                                new Variant(311), new Variant(970), new Variant(163), new Variant(29));
                    }
                });
    }

    @Test
    public void test_getAx_Default_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(557))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAx_Default(new Variant(557));
                    }
                });
    }

}