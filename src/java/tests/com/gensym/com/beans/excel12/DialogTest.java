package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class DialogTest extends ActiveXDispatchableTestBase {

    private Dialog component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new Dialog(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(961), new Variant(999))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(961), new Variant(999));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(562))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(562));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(372))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(372));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(514), new Variant(827), new
                Variant(42L), new Variant(42L), new Variant(906))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(514), new Variant(827), 42L, 42L, new Variant(906));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(516), new
                Variant(42L), new Variant(42), new Variant(394), new Variant(802), new Variant(570), new Variant(403))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(516), 42L, 42, new Variant(394), new Variant(802), new
                                Variant(570), new Variant(403));
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
    public void test_Show_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Show();
                    }
                });
    }

    @Test
    public void test_Show_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x1f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(61))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Show(new Variant(61));
                    }
                });
    }

    @Test
    public void test_Show_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(122), new Variant(933))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Show(new Variant(122), new Variant(933));
                    }
                });
    }

    @Test
    public void test_Show_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(832), new Variant(124), new
                Variant(287))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Show(new Variant(832), new Variant(124), new Variant(287));
                    }
                });
    }

    @Test
    public void test_Show_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(691), new Variant(63), new Variant
                (607), new Variant(338))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Show(new Variant(691), new Variant(63), new Variant(607), new Variant(338));
                    }
                });
    }

    @Test
    public void test_Show_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(511), new Variant(435), new
                Variant(758), new Variant(749), new Variant(922))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Show(new Variant(511), new Variant(435), new Variant(758), new Variant(749),
                                new Variant(922));
                    }
                });
    }

    @Test
    public void test_Show_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(575), new Variant(203), new
                Variant(746), new Variant(267), new Variant(261), new Variant(871))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Show(new Variant(575), new Variant(203), new Variant(746), new Variant(267),
                                new Variant(261), new Variant(871));
                    }
                });
    }

    @Test
    public void test_Show_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(844), new Variant(796), new
                Variant(424), new Variant(848), new Variant(413), new Variant(865), new Variant(340))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Show(new Variant(844), new Variant(796), new Variant(424), new Variant(848),
                                new Variant(413), new Variant(865), new Variant(340));
                    }
                });
    }

    @Test
    public void test_Show_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(259), new Variant(510), new
                Variant(351), new Variant(862), new Variant(476), new Variant(213), new Variant(998), new Variant(309))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Show(new Variant(259), new Variant(510), new Variant(351), new Variant(862),
                                new Variant(476), new Variant(213), new Variant(998), new Variant(309));
                    }
                });
    }

    @Test
    public void test_Show_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(736), new Variant(944), new
                Variant(645), new Variant(968), new Variant(371), new Variant(377), new Variant(337), new Variant
                (257), new Variant(170))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Show(new Variant(736), new Variant(944), new Variant(645), new Variant(968),
                                new Variant(371), new Variant(377), new Variant(337), new Variant(257), new Variant
                                        (170));
                    }
                });
    }

    @Test
    public void test_Show_TenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(754), new Variant(9), new Variant
                (143), new Variant(183), new Variant(759), new Variant(569), new Variant(185), new Variant(197), new
                Variant(82), new Variant(233))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Show(new Variant(754), new Variant(9), new Variant(143), new Variant(183),
                                new Variant(759), new Variant(569), new Variant(185), new Variant(197), new Variant
                                        (82), new Variant(233));
                    }
                });
    }

    @Test
    public void test_Show_ElevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(14), new Variant(855), new Variant
                (314), new Variant(186), new Variant(666), new Variant(449), new Variant(909), new Variant(76), new
                Variant(171), new Variant(490), new Variant(476))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Show(new Variant(14), new Variant(855), new Variant(314), new Variant(186),
                                new Variant(666), new Variant(449), new Variant(909), new Variant(76), new Variant
                                        (171), new Variant(490), new Variant(476));
                    }
                });
    }

    @Test
    public void test_Show_TwelveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(446), new Variant(538), new
                Variant(557), new Variant(606), new Variant(948), new Variant(108), new Variant(90), new Variant(204)
                , new Variant(206), new Variant(280), new Variant(942), new Variant(452))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Show(new Variant(446), new Variant(538), new Variant(557), new Variant(606),
                                new Variant(948), new Variant(108), new Variant(90), new Variant(204), new Variant
                                        (206), new Variant(280), new Variant(942), new Variant(452));
                    }
                });
    }

    @Test
    public void test_Show_ThirteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(971), new Variant(787), new
                Variant(676), new Variant(945), new Variant(937), new Variant(383), new Variant(54), new Variant(272)
                , new Variant(503), new Variant(898), new Variant(820), new Variant(965), new Variant(993))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Show(new Variant(971), new Variant(787), new Variant(676), new Variant(945),
                                new Variant(937), new Variant(383), new Variant(54), new Variant(272), new Variant
                                        (503), new Variant(898), new Variant(820), new Variant(965), new Variant(993));
                    }
                });
    }

    @Test
    public void test_Show_FourteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(411), new Variant(31), new Variant
                (788), new Variant(903), new Variant(535), new Variant(219), new Variant(179), new Variant(267), new
                Variant(569), new Variant(631), new Variant(292), new Variant(412), new Variant(937), new Variant(386))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Show(new Variant(411), new Variant(31), new Variant(788), new Variant(903),
                                new Variant(535), new Variant(219), new Variant(179), new Variant(267), new Variant
                                        (569), new Variant(631), new Variant(292), new Variant(412), new Variant(937)
                                , new Variant(386));
                    }
                });
    }

    @Test
    public void test_Show_FifteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(545), new Variant(44), new Variant
                (891), new Variant(420), new Variant(32), new Variant(867), new Variant(256), new Variant(46), new
                Variant(614), new Variant(742), new Variant(218), new Variant(903), new Variant(448), new Variant(48)
                , new Variant(976))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Show(new Variant(545), new Variant(44), new Variant(891), new Variant(420),
                                new Variant(32), new Variant(867), new Variant(256), new Variant(46), new Variant
                                        (614), new Variant(742), new Variant(218), new Variant(903), new Variant(448)
                                , new Variant(48), new Variant(976));
                    }
                });
    }

    @Test
    public void test_Show_SixteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(604), new Variant(660), new
                Variant(691), new Variant(481), new Variant(722), new Variant(470), new Variant(178), new Variant
                (446), new Variant(19), new Variant(838), new Variant(54), new Variant(688), new Variant(404), new
                Variant(463), new Variant(811), new Variant(169))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Show(new Variant(604), new Variant(660), new Variant(691), new Variant(481),
                                new Variant(722), new Variant(470), new Variant(178), new Variant(446), new Variant
                                        (19), new Variant(838), new Variant(54), new Variant(688), new Variant(404),
                                new Variant(463), new Variant(811), new Variant(169));
                    }
                });
    }

    @Test
    public void test_Show_SeventeenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(807), new Variant(795), new
                Variant(967), new Variant(622), new Variant(713), new Variant(154), new Variant(166), new Variant
                (770), new Variant(217), new Variant(953), new Variant(365), new Variant(934), new Variant(468), new
                Variant(430), new Variant(417), new Variant(740), new Variant(721))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Show(new Variant(807), new Variant(795), new Variant(967), new Variant(622),
                                new Variant(713), new Variant(154), new Variant(166), new Variant(770), new Variant
                                        (217), new Variant(953), new Variant(365), new Variant(934), new Variant(468)
                                , new Variant(430), new Variant(417), new Variant(740), new Variant(721));
                    }
                });
    }

    @Test
    public void test_Show_EighteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(114), new Variant(755), new
                Variant(882), new Variant(910), new Variant(792), new Variant(259), new Variant(596), new Variant
                (967), new Variant(258), new Variant(213), new Variant(19), new Variant(829), new Variant(362), new
                Variant(284), new Variant(785), new Variant(883), new Variant(958), new Variant(370))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Show(new Variant(114), new Variant(755), new Variant(882), new Variant(910),
                                new Variant(792), new Variant(259), new Variant(596), new Variant(967), new Variant
                                        (258), new Variant(213), new Variant(19), new Variant(829), new Variant(362),
                                new Variant(284), new Variant(785), new Variant(883), new Variant(958), new Variant
                                        (370));
                    }
                });
    }

    @Test
    public void test_Show_NineteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(118), new Variant(0), new Variant
                (797), new Variant(841), new Variant(452), new Variant(298), new Variant(286), new Variant(961), new
                Variant(615), new Variant(896), new Variant(903), new Variant(254), new Variant(817), new Variant
                (713), new Variant(523), new Variant(45), new Variant(186), new Variant(238), new Variant(461))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Show(new Variant(118), new Variant(0), new Variant(797), new Variant(841),
                                new Variant(452), new Variant(298), new Variant(286), new Variant(961), new Variant
                                        (615), new Variant(896), new Variant(903), new Variant(254), new Variant(817)
                                , new Variant(713), new Variant(523), new Variant(45), new Variant(186), new Variant
                                        (238), new Variant(461));
                    }
                });
    }

    @Test
    public void test_Show_TwentyArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(812), new Variant(228), new
                Variant(553), new Variant(161), new Variant(883), new Variant(420), new Variant(105), new Variant
                (922), new Variant(771), new Variant(292), new Variant(979), new Variant(982), new Variant(377), new
                Variant(974), new Variant(983), new Variant(309), new Variant(174), new Variant(595), new Variant
                (220), new Variant(776))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Show(new Variant(812), new Variant(228), new Variant(553), new Variant(161),
                                new Variant(883), new Variant(420), new Variant(105), new Variant(922), new Variant
                                        (771), new Variant(292), new Variant(979), new Variant(982), new Variant(377)
                                , new Variant(974), new Variant(983), new Variant(309), new Variant(174), new Variant
                                        (595), new Variant(220), new Variant(776));
                    }
                });
    }

    @Test
    public void test_Show_TwentyOneArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(54), new Variant(658), new Variant
                (872), new Variant(543), new Variant(675), new Variant(876), new Variant(751), new Variant(523), new
                Variant(798), new Variant(547), new Variant(847), new Variant(474), new Variant(986), new Variant
                (715), new Variant(607), new Variant(832), new Variant(701), new Variant(569), new Variant(130), new
                Variant(754), new Variant(35))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Show(new Variant(54), new Variant(658), new Variant(872), new Variant(543),
                                new Variant(675), new Variant(876), new Variant(751), new Variant(523), new Variant
                                        (798), new Variant(547), new Variant(847), new Variant(474), new Variant(986)
                                , new Variant(715), new Variant(607), new Variant(832), new Variant(701), new Variant
                                        (569), new Variant(130), new Variant(754), new Variant(35));
                    }
                });
    }

    @Test
    public void test_Show_TwentyTwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(600), new Variant(164), new
                Variant(95), new Variant(360), new Variant(274), new Variant(879), new Variant(631), new Variant(498)
                , new Variant(763), new Variant(738), new Variant(165), new Variant(649), new Variant(618), new
                        Variant(303), new Variant(385), new Variant(52), new Variant(809), new Variant(112), new
                        Variant(286), new Variant(938), new Variant(331), new Variant(229))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Show(new Variant(600), new Variant(164), new Variant(95), new Variant(360),
                                new Variant(274), new Variant(879), new Variant(631), new Variant(498), new Variant
                                        (763), new Variant(738), new Variant(165), new Variant(649), new Variant(618)
                                , new Variant(303), new Variant(385), new Variant(52), new Variant(809), new Variant
                                        (112), new Variant(286), new Variant(938), new Variant(331), new Variant(229));
                    }
                });
    }

    @Test
    public void test_Show_TwentyThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(26), new Variant(953), new Variant
                (517), new Variant(596), new Variant(644), new Variant(246), new Variant(509), new Variant(661), new
                Variant(463), new Variant(122), new Variant(207), new Variant(985), new Variant(765), new Variant
                (637), new Variant(279), new Variant(847), new Variant(719), new Variant(417), new Variant(656), new
                Variant(210), new Variant(304), new Variant(742), new Variant(35))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Show(new Variant(26), new Variant(953), new Variant(517), new Variant(596),
                                new Variant(644), new Variant(246), new Variant(509), new Variant(661), new Variant
                                        (463), new Variant(122), new Variant(207), new Variant(985), new Variant(765)
                                , new Variant(637), new Variant(279), new Variant(847), new Variant(719), new Variant
                                        (417), new Variant(656), new Variant(210), new Variant(304), new Variant(742)
                                , new Variant(35));
                    }
                });
    }

    @Test
    public void test_Show_TwentyFourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(499), new Variant(946), new
                Variant(69), new Variant(147), new Variant(126), new Variant(816), new Variant(971), new Variant(93),
                new Variant(555), new Variant(186), new Variant(893), new Variant(126), new Variant(564), new Variant
                        (407), new Variant(731), new Variant(316), new Variant(310), new Variant(509), new Variant
                        (474), new Variant(654), new Variant(750), new Variant(955), new Variant(993), new Variant(880))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Show(new Variant(499), new Variant(946), new Variant(69), new Variant(147),
                                new Variant(126), new Variant(816), new Variant(971), new Variant(93), new Variant
                                        (555), new Variant(186), new Variant(893), new Variant(126), new Variant(564)
                                , new Variant(407), new Variant(731), new Variant(316), new Variant(310), new Variant
                                        (509), new Variant(474), new Variant(654), new Variant(750), new Variant(955)
                                , new Variant(993), new Variant(880));
                    }
                });
    }

    @Test
    public void test_Show_TwentyFiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(609), new Variant(680), new
                Variant(775), new Variant(350), new Variant(615), new Variant(965), new Variant(183), new Variant
                (225), new Variant(45), new Variant(821), new Variant(114), new Variant(184), new Variant(535), new
                Variant(845), new Variant(968), new Variant(950), new Variant(286), new Variant(77), new Variant(778)
                , new Variant(985), new Variant(171), new Variant(558), new Variant(190), new Variant(363), new
                        Variant(344))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Show(new Variant(609), new Variant(680), new Variant(775), new Variant(350),
                                new Variant(615), new Variant(965), new Variant(183), new Variant(225), new Variant
                                        (45), new Variant(821), new Variant(114), new Variant(184), new Variant(535),
                                new Variant(845), new Variant(968), new Variant(950), new Variant(286), new Variant
                                        (77), new Variant(778), new Variant(985), new Variant(171), new Variant(558),
                                new Variant(190), new Variant(363), new Variant(344));
                    }
                });
    }

    @Test
    public void test_Show_TwentySixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(223), new Variant(120), new
                Variant(233), new Variant(527), new Variant(192), new Variant(466), new Variant(673), new Variant
                (378), new Variant(335), new Variant(56), new Variant(240), new Variant(470), new Variant(912), new
                Variant(650), new Variant(697), new Variant(868), new Variant(278), new Variant(959), new Variant
                (602), new Variant(541), new Variant(521), new Variant(394), new Variant(473), new Variant(290), new
                Variant(624), new Variant(764))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Show(new Variant(223), new Variant(120), new Variant(233), new Variant(527),
                                new Variant(192), new Variant(466), new Variant(673), new Variant(378), new Variant
                                        (335), new Variant(56), new Variant(240), new Variant(470), new Variant(912),
                                new Variant(650), new Variant(697), new Variant(868), new Variant(278), new Variant
                                        (959), new Variant(602), new Variant(541), new Variant(521), new Variant(394)
                                , new Variant(473), new Variant(290), new Variant(624), new Variant(764));
                    }
                });
    }

    @Test
    public void test_Show_TwentySevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(452), new Variant(701), new
                Variant(702), new Variant(454), new Variant(101), new Variant(112), new Variant(25), new Variant(56),
                new Variant(364), new Variant(184), new Variant(845), new Variant(819), new Variant(502), new Variant
                        (693), new Variant(911), new Variant(528), new Variant(884), new Variant(873), new Variant
                        (485), new Variant(75), new Variant(478), new Variant(410), new Variant(963), new Variant
                        (239), new Variant(238), new Variant(806), new Variant(584))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Show(new Variant(452), new Variant(701), new Variant(702), new Variant(454),
                                new Variant(101), new Variant(112), new Variant(25), new Variant(56), new Variant
                                        (364), new Variant(184), new Variant(845), new Variant(819), new Variant(502)
                                , new Variant(693), new Variant(911), new Variant(528), new Variant(884), new Variant
                                        (873), new Variant(485), new Variant(75), new Variant(478), new Variant(410),
                                new Variant(963), new Variant(239), new Variant(238), new Variant(806), new Variant
                                        (584));
                    }
                });
    }

    @Test
    public void test_Show_TwentyEightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(943), new Variant(970), new
                Variant(314), new Variant(175), new Variant(382), new Variant(969), new Variant(951), new Variant
                (857), new Variant(964), new Variant(446), new Variant(729), new Variant(960), new Variant(638), new
                Variant(530), new Variant(261), new Variant(951), new Variant(273), new Variant(100), new Variant
                (623), new Variant(37), new Variant(578), new Variant(667), new Variant(502), new Variant(448), new
                Variant(717), new Variant(237), new Variant(404), new Variant(661))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Show(new Variant(943), new Variant(970), new Variant(314), new Variant(175),
                                new Variant(382), new Variant(969), new Variant(951), new Variant(857), new Variant
                                        (964), new Variant(446), new Variant(729), new Variant(960), new Variant(638)
                                , new Variant(530), new Variant(261), new Variant(951), new Variant(273), new Variant
                                        (100), new Variant(623), new Variant(37), new Variant(578), new Variant(667),
                                new Variant(502), new Variant(448), new Variant(717), new Variant(237), new Variant
                                        (404), new Variant(661));
                    }
                });
    }

    @Test
    public void test_Show_TwentyNineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(392), new Variant(464), new
                Variant(141), new Variant(502), new Variant(499), new Variant(773), new Variant(83), new Variant(685)
                , new Variant(174), new Variant(396), new Variant(492), new Variant(253), new Variant(327), new
                        Variant(979), new Variant(801), new Variant(967), new Variant(638), new Variant(288), new
                        Variant(883), new Variant(418), new Variant(63), new Variant(478), new Variant(516), new
                        Variant(756), new Variant(516), new Variant(140), new Variant(495), new Variant(405), new
                        Variant(996))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Show(new Variant(392), new Variant(464), new Variant(141), new Variant(502),
                                new Variant(499), new Variant(773), new Variant(83), new Variant(685), new Variant
                                        (174), new Variant(396), new Variant(492), new Variant(253), new Variant(327)
                                , new Variant(979), new Variant(801), new Variant(967), new Variant(638), new Variant
                                        (288), new Variant(883), new Variant(418), new Variant(63), new Variant(478),
                                new Variant(516), new Variant(756), new Variant(516), new Variant(140), new Variant
                                        (495), new Variant(405), new Variant(996));
                    }
                });
    }

    @Test
    public void test_Show_ThirtyArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(608), new Variant(62), new Variant
                (891), new Variant(52), new Variant(403), new Variant(198), new Variant(687), new Variant(792), new
                Variant(190), new Variant(97), new Variant(950), new Variant(231), new Variant(851), new Variant(463)
                , new Variant(228), new Variant(280), new Variant(502), new Variant(234), new Variant(532), new
                        Variant(140), new Variant(74), new Variant(741), new Variant(114), new Variant(882), new
                        Variant(192), new Variant(351), new Variant(81), new Variant(952), new Variant(930), new
                        Variant(770))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Show(new Variant(608), new Variant(62), new Variant(891), new Variant(52),
                                new Variant(403), new Variant(198), new Variant(687), new Variant(792), new Variant
                                        (190), new Variant(97), new Variant(950), new Variant(231), new Variant(851),
                                new Variant(463), new Variant(228), new Variant(280), new Variant(502), new Variant
                                        (234), new Variant(532), new Variant(140), new Variant(74), new Variant(741),
                                new Variant(114), new Variant(882), new Variant(192), new Variant(351), new Variant
                                        (81), new Variant(952), new Variant(930), new Variant(770));
                    }
                });
    }

}