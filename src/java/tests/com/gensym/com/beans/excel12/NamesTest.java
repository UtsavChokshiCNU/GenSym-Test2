package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class NamesTest extends ActiveXDispatchableTestBase {

    private Names component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new Names(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(692), new Variant(499))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(692), new Variant(499));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(117))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(117));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(643))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(643));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(474), new Variant(798), new
                Variant(42L), new Variant(42L), new Variant(302))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(474), new Variant(798), 42L, 42L, new Variant(302));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(568), new
                Variant(42L), new Variant(42), new Variant(162), new Variant(581), new Variant(344), new Variant(604))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(568), 42L, 42, new Variant(162), new Variant(581), new
                                Variant(344), new Variant(604));
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
                .verifyReturnsDispatchable(new Returns<Name>() {
                    @Override
                    public Name invoke() throws ActiveXException {
                        return component.Add();
                    }
                });
    }

    @Test
    public void test_Add_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(641))
                .verifyReturnsDispatchable(new Returns<Name>() {
                    @Override
                    public Name invoke() throws ActiveXException {
                        return component.Add(new Variant(641));
                    }
                });
    }

    @Test
    public void test_Add_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(415), new Variant(524))
                .verifyReturnsDispatchable(new Returns<Name>() {
                    @Override
                    public Name invoke() throws ActiveXException {
                        return component.Add(new Variant(415), new Variant(524));
                    }
                });
    }

    @Test
    public void test_Add_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(309), new Variant(515), new Variant
                (861))
                .verifyReturnsDispatchable(new Returns<Name>() {
                    @Override
                    public Name invoke() throws ActiveXException {
                        return component.Add(new Variant(309), new Variant(515), new Variant(861));
                    }
                });
    }

    @Test
    public void test_Add_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(23), new Variant(915), new Variant
                (80), new Variant(789))
                .verifyReturnsDispatchable(new Returns<Name>() {
                    @Override
                    public Name invoke() throws ActiveXException {
                        return component.Add(new Variant(23), new Variant(915), new Variant(80), new Variant(789));
                    }
                });
    }

    @Test
    public void test_Add_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(424), new Variant(827), new Variant
                (214), new Variant(541), new Variant(79))
                .verifyReturnsDispatchable(new Returns<Name>() {
                    @Override
                    public Name invoke() throws ActiveXException {
                        return component.Add(new Variant(424), new Variant(827), new Variant(214), new Variant(541),
                                new Variant(79));
                    }
                });
    }

    @Test
    public void test_Add_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(100), new Variant(728), new Variant
                (913), new Variant(73), new Variant(581), new Variant(524))
                .verifyReturnsDispatchable(new Returns<Name>() {
                    @Override
                    public Name invoke() throws ActiveXException {
                        return component.Add(new Variant(100), new Variant(728), new Variant(913), new Variant(73),
                                new Variant(581), new Variant(524));
                    }
                });
    }

    @Test
    public void test_Add_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(537), new Variant(232), new Variant
                (882), new Variant(667), new Variant(681), new Variant(239), new Variant(481))
                .verifyReturnsDispatchable(new Returns<Name>() {
                    @Override
                    public Name invoke() throws ActiveXException {
                        return component.Add(new Variant(537), new Variant(232), new Variant(882), new Variant(667),
                                new Variant(681), new Variant(239), new Variant(481));
                    }
                });
    }

    @Test
    public void test_Add_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(633), new Variant(710), new Variant
                (572), new Variant(389), new Variant(4), new Variant(138), new Variant(214), new Variant(447))
                .verifyReturnsDispatchable(new Returns<Name>() {
                    @Override
                    public Name invoke() throws ActiveXException {
                        return component.Add(new Variant(633), new Variant(710), new Variant(572), new Variant(389),
                                new Variant(4), new Variant(138), new Variant(214), new Variant(447));
                    }
                });
    }

    @Test
    public void test_Add_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(721), new Variant(325), new Variant
                (93), new Variant(643), new Variant(954), new Variant(128), new Variant(416), new Variant(174), new
                Variant(123))
                .verifyReturnsDispatchable(new Returns<Name>() {
                    @Override
                    public Name invoke() throws ActiveXException {
                        return component.Add(new Variant(721), new Variant(325), new Variant(93), new Variant(643),
                                new Variant(954), new Variant(128), new Variant(416), new Variant(174), new Variant
                                        (123));
                    }
                });
    }

    @Test
    public void test_Add_TenArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(358), new Variant(730), new Variant
                (586), new Variant(764), new Variant(314), new Variant(206), new Variant(675), new Variant(577), new
                Variant(439), new Variant(834))
                .verifyReturnsDispatchable(new Returns<Name>() {
                    @Override
                    public Name invoke() throws ActiveXException {
                        return component.Add(new Variant(358), new Variant(730), new Variant(586), new Variant(764),
                                new Variant(314), new Variant(206), new Variant(675), new Variant(577), new Variant
                                        (439), new Variant(834));
                    }
                });
    }

    @Test
    public void test_Add_ElevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(865), new Variant(21), new Variant
                (976), new Variant(288), new Variant(411), new Variant(350), new Variant(821), new Variant(270), new
                Variant(348), new Variant(425), new Variant(414))
                .verifyReturnsDispatchable(new Returns<Name>() {
                    @Override
                    public Name invoke() throws ActiveXException {
                        return component.Add(new Variant(865), new Variant(21), new Variant(976), new Variant(288),
                                new Variant(411), new Variant(350), new Variant(821), new Variant(270), new Variant
                                        (348), new Variant(425), new Variant(414));
                    }
                });
    }

    @Test
    public void test_Item_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xaa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchable(new Returns<Name>() {
                    @Override
                    public Name invoke() throws ActiveXException {
                        return component.Item();
                    }
                });
    }

    @Test
    public void test_Item_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xaa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(663))
                .verifyReturnsDispatchable(new Returns<Name>() {
                    @Override
                    public Name invoke() throws ActiveXException {
                        return component.Item(new Variant(663));
                    }
                });
    }

    @Test
    public void test_Item_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xaa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(909), new Variant(22))
                .verifyReturnsDispatchable(new Returns<Name>() {
                    @Override
                    public Name invoke() throws ActiveXException {
                        return component.Item(new Variant(909), new Variant(22));
                    }
                });
    }

    @Test
    public void test_Item_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0xaa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(543), new Variant(435), new Variant
                (15))
                .verifyReturnsDispatchable(new Returns<Name>() {
                    @Override
                    public Name invoke() throws ActiveXException {
                        return component.Item(new Variant(543), new Variant(435), new Variant(15));
                    }
                });
    }

    @Test
    public void test__Default_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchable(new Returns<Name>() {
                    @Override
                    public Name invoke() throws ActiveXException {
                        return component._Default();
                    }
                });
    }

    @Test
    public void test__Default_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(398))
                .verifyReturnsDispatchable(new Returns<Name>() {
                    @Override
                    public Name invoke() throws ActiveXException {
                        return component._Default(new Variant(398));
                    }
                });
    }

    @Test
    public void test__Default_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(312), new Variant(753))
                .verifyReturnsDispatchable(new Returns<Name>() {
                    @Override
                    public Name invoke() throws ActiveXException {
                        return component._Default(new Variant(312), new Variant(753));
                    }
                });
    }

    @Test
    public void test__Default_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(387), new Variant(241), new Variant
                (864))
                .verifyReturnsDispatchable(new Returns<Name>() {
                    @Override
                    public Name invoke() throws ActiveXException {
                        return component._Default(new Variant(387), new Variant(241), new Variant(864));
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
    public void test_getAx_NewEnum_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xfffffffc).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsGenericValue(new Returns<Object>() {
                    @Override
                    public Object invoke() throws ActiveXException {
                        return component.getAx_NewEnum();
                    }
                });
    }

}