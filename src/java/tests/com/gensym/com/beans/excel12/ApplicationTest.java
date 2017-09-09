package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import com.gensym.com.beans.office20.Assistant;
import com.gensym.com.beans.office20.CommandBars;
import com.gensym.com.beans.office20.FileSearch;
import com.gensym.com.beans.office20.IFind;
import com.gensym.com.beans.vbide50.VBE;
import org.junit.Before;
import org.junit.Test;

public class ApplicationTest extends ActiveXDispatchableTestBase {

    private Application component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new Application(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(366), new Variant(226))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(366), new Variant(226));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(797))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(797));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(963))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(963));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(295), new Variant(377), new
                Variant(42L), new Variant(42L), new Variant(212))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(295), new Variant(377), 42L, 42L, new Variant(212));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(143), new
                Variant(42L), new Variant(42), new Variant(851), new Variant(979), new Variant(249), new Variant(458))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(143), 42L, 42, new Variant(851), new Variant(979), new
                                Variant(249), new Variant(458));
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
                .verifyReturnsDispatchable(new Returns<ExcelApplication>() {
                    @Override
                    public ExcelApplication invoke() throws ActiveXException {
                        return component.getAxParent();
                    }
                });
    }

    @Test
    public void test_getAxActiveCell_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x131).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxActiveCell();
                    }
                });
    }

    @Test
    public void test_getAxActiveChart_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<ExcelChart>() {
                    @Override
                    public ExcelChart invoke() throws ActiveXException {
                        return component.getAxActiveChart();
                    }
                });
    }

    @Test
    public void test_getAxActiveDialog_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x32f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<DialogSheet>() {
                    @Override
                    public DialogSheet invoke() throws ActiveXException {
                        return component.getAxActiveDialog();
                    }
                });
    }

    @Test
    public void test_getAxActiveMenuBar_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2f6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<MenuBar>() {
                    @Override
                    public MenuBar invoke() throws ActiveXException {
                        return component.getAxActiveMenuBar();
                    }
                });
    }

    @Test
    public void test_getAxActivePrinter_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x132).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxActivePrinter();
                    }
                });
    }

    @Test
    public void test_setAxActivePrinter_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x132).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("vYHaBpPuka"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxActivePrinter("vYHaBpPuka");
                    }
                });
    }

    @Test
    public void test_getAxActiveSheet_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x133).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxActiveSheet();
                    }
                });
    }

    @Test
    public void test_getAxActiveWindow_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2f7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Window>() {
                    @Override
                    public Window invoke() throws ActiveXException {
                        return component.getAxActiveWindow();
                    }
                });
    }

    @Test
    public void test_getAxActiveWorkbook_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x134).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxActiveWorkbook();
                    }
                });
    }

    @Test
    public void test_getAxAddIns_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x225).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<AddIns>() {
                    @Override
                    public AddIns invoke() throws ActiveXException {
                        return component.getAxAddIns();
                    }
                });
    }

    @Test
    public void test_getAxAssistant_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x59e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Assistant>() {
                    @Override
                    public Assistant invoke() throws ActiveXException {
                        return component.getAxAssistant();
                    }
                });
    }

    @Test
    public void test_Calculate_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x117).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Calculate();
                    }
                });
    }

    @Test
    public void test_getAxCells_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xee).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxCells();
                    }
                });
    }

    @Test
    public void test_getAxCharts_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x79).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Sheets>() {
                    @Override
                    public Sheets invoke() throws ActiveXException {
                        return component.getAxCharts();
                    }
                });
    }

    @Test
    public void test_getAxColumns_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xf1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxColumns();
                    }
                });
    }

    @Test
    public void test_getAxCommandBars_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x59f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<CommandBars>() {
                    @Override
                    public CommandBars invoke() throws ActiveXException {
                        return component.getAxCommandBars();
                    }
                });
    }

    @Test
    public void test_getAxDDEAppReturnCode_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x14c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxDDEAppReturnCode();
                    }
                });
    }

    @Test
    public void test_DDEExecute_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x14d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant("EChaheNRzc"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.DDEExecute(42, "EChaheNRzc");
                    }
                });
    }

    @Test
    public void test_DDEInitiate_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x14e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("BcrEcCVtgP"), new Variant
                ("cDqyBubNwb"))
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.DDEInitiate("BcrEcCVtgP", "cDqyBubNwb");
                    }
                });
    }

    @Test
    public void test_DDEPoke_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x14f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(654), new Variant
                (643))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.DDEPoke(42, new Variant(654), new Variant(643));
                    }
                });
    }

    @Test
    public void test_DDERequest_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x150).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant("FjadbSMcWo"))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.DDERequest(42, "FjadbSMcWo");
                    }
                });
    }

    @Test
    public void test_DDETerminate_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x151).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.DDETerminate(42);
                    }
                });
    }

    @Test
    public void test_getAxDialogSheets_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fc).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Sheets>() {
                    @Override
                    public Sheets invoke() throws ActiveXException {
                        return component.getAxDialogSheets();
                    }
                });
    }

    @Test
    public void test_Evaluate_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x1).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(341))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Evaluate(new Variant(341));
                    }
                });
    }

    @Test
    public void test__Evaluate_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xfffffffb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(856))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Evaluate(new Variant(856));
                    }
                });
    }

    @Test
    public void test_ExecuteExcel4Macro_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x15e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("dGmprDCveE"))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.ExecuteExcel4Macro("dGmprDCveE");
                    }
                });
    }

    @Test
    public void test_Intersect_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class));
                    }
                });
    }

    @Test
    public void test_Intersect_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(491))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(491));
                    }
                });
    }

    @Test
    public void test_Intersect_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(342), new Variant(141))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(342), new
                                Variant(141));
                    }
                });
    }

    @Test
    public void test_Intersect_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(182), new Variant(488), new Variant(688))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(182), new
                                Variant(488), new Variant(688));
                    }
                });
    }

    @Test
    public void test_Intersect_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(927), new Variant(714), new Variant(720), new Variant(541))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(927), new
                                Variant(714), new Variant(720), new Variant(541));
                    }
                });
    }

    @Test
    public void test_Intersect_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(250), new Variant(771), new Variant(429), new Variant(75), new
                Variant(168))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(250), new
                                Variant(771), new Variant(429), new Variant(75), new Variant(168));
                    }
                });
    }

    @Test
    public void test_Intersect_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(82), new Variant(911), new Variant(716), new Variant(769), new
                Variant(984), new Variant(310))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(82), new
                                Variant(911), new Variant(716), new Variant(769), new Variant(984), new Variant(310));
                    }
                });
    }

    @Test
    public void test_Intersect_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(658), new Variant(260), new Variant(634), new Variant(336), new
                Variant(355), new Variant(380), new Variant(72))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(658), new
                                Variant(260), new Variant(634), new Variant(336), new Variant(355), new Variant(380),
                                new Variant(72));
                    }
                });
    }

    @Test
    public void test_Intersect_TenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(655), new Variant(268), new Variant(373), new Variant(427), new
                Variant(962), new Variant(242), new Variant(473), new Variant(564))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(655), new
                                Variant(268), new Variant(373), new Variant(427), new Variant(962), new Variant(242),
                                new Variant(473), new Variant(564));
                    }
                });
    }

    @Test
    public void test_Intersect_ElevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(654), new Variant(844), new Variant(140), new Variant(481), new
                Variant(865), new Variant(387), new Variant(544), new Variant(282), new Variant(508))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(654), new
                                Variant(844), new Variant(140), new Variant(481), new Variant(865), new Variant(387),
                                new Variant(544), new Variant(282), new Variant(508));
                    }
                });
    }

    @Test
    public void test_Intersect_TwelveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(259), new Variant(822), new Variant(634), new Variant(530), new
                Variant(892), new Variant(330), new Variant(569), new Variant(808), new Variant(1), new Variant(313))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(259), new
                                Variant(822), new Variant(634), new Variant(530), new Variant(892), new Variant(330),
                                new Variant(569), new Variant(808), new Variant(1), new Variant(313));
                    }
                });
    }

    @Test
    public void test_Intersect_ThirteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(774), new Variant(771), new Variant(465), new Variant(282), new
                Variant(442), new Variant(193), new Variant(460), new Variant(414), new Variant(896), new Variant
                (845), new Variant(805))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(774), new
                                Variant(771), new Variant(465), new Variant(282), new Variant(442), new Variant(193),
                                new Variant(460), new Variant(414), new Variant(896), new Variant(845), new Variant
                                        (805));
                    }
                });
    }

    @Test
    public void test_Intersect_FourteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(469), new Variant(872), new Variant(643), new Variant(206), new
                Variant(134), new Variant(682), new Variant(59), new Variant(266), new Variant(987), new Variant(472)
                , new Variant(109), new Variant(579))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(469), new
                                Variant(872), new Variant(643), new Variant(206), new Variant(134), new Variant(682),
                                new Variant(59), new Variant(266), new Variant(987), new Variant(472), new Variant
                                        (109), new Variant(579));
                    }
                });
    }

    @Test
    public void test_Intersect_FifteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(23), new Variant(349), new Variant(90), new Variant(19), new
                Variant(485), new Variant(553), new Variant(795), new Variant(536), new Variant(190), new Variant
                (582), new Variant(353), new Variant(617), new Variant(126))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(23), new
                                Variant(349), new Variant(90), new Variant(19), new Variant(485), new Variant(553),
                                new Variant(795), new Variant(536), new Variant(190), new Variant(582), new Variant
                                        (353), new Variant(617), new Variant(126));
                    }
                });
    }

    @Test
    public void test_Intersect_SixteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(141), new Variant(304), new Variant(861), new Variant(932), new
                Variant(409), new Variant(608), new Variant(755), new Variant(693), new Variant(214), new Variant
                (745), new Variant(923), new Variant(995), new Variant(106), new Variant(106))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(141), new
                                Variant(304), new Variant(861), new Variant(932), new Variant(409), new Variant(608),
                                new Variant(755), new Variant(693), new Variant(214), new Variant(745), new Variant
                                        (923), new Variant(995), new Variant(106), new Variant(106));
                    }
                });
    }

    @Test
    public void test_Intersect_SeventeenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(331), new Variant(31), new Variant(753), new Variant(710), new
                Variant(407), new Variant(760), new Variant(191), new Variant(69), new Variant(504), new Variant(582)
                , new Variant(597), new Variant(482), new Variant(316), new Variant(200), new Variant(727))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(331), new
                                Variant(31), new Variant(753), new Variant(710), new Variant(407), new Variant(760),
                                new Variant(191), new Variant(69), new Variant(504), new Variant(582), new Variant
                                        (597), new Variant(482), new Variant(316), new Variant(200), new Variant(727));
                    }
                });
    }

    @Test
    public void test_Intersect_EighteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(110), new Variant(374), new Variant(342), new Variant(461), new
                Variant(544), new Variant(468), new Variant(4), new Variant(997), new Variant(207), new Variant(439),
                new Variant(292), new Variant(185), new Variant(430), new Variant(920), new Variant(727), new Variant
                        (852))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(110), new
                                Variant(374), new Variant(342), new Variant(461), new Variant(544), new Variant(468),
                                new Variant(4), new Variant(997), new Variant(207), new Variant(439), new Variant
                                        (292), new Variant(185), new Variant(430), new Variant(920), new Variant(727)
                                , new Variant(852));
                    }
                });
    }

    @Test
    public void test_Intersect_NineteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(666), new Variant(45), new Variant(935), new Variant(960), new
                Variant(227), new Variant(602), new Variant(908), new Variant(132), new Variant(660), new Variant
                (485), new Variant(401), new Variant(601), new Variant(977), new Variant(74), new Variant(114), new
                Variant(659), new Variant(885))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(666), new
                                Variant(45), new Variant(935), new Variant(960), new Variant(227), new Variant(602),
                                new Variant(908), new Variant(132), new Variant(660), new Variant(485), new Variant
                                        (401), new Variant(601), new Variant(977), new Variant(74), new Variant(114),
                                new Variant(659), new Variant(885));
                    }
                });
    }

    @Test
    public void test_Intersect_TwentyArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(813), new Variant(821), new Variant(765), new Variant(45), new
                Variant(437), new Variant(66), new Variant(605), new Variant(477), new Variant(341), new Variant(184)
                , new Variant(319), new Variant(756), new Variant(951), new Variant(981), new Variant(221), new
                        Variant(758), new Variant(706), new Variant(417))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(813), new
                                Variant(821), new Variant(765), new Variant(45), new Variant(437), new Variant(66),
                                new Variant(605), new Variant(477), new Variant(341), new Variant(184), new Variant
                                        (319), new Variant(756), new Variant(951), new Variant(981), new Variant(221)
                                , new Variant(758), new Variant(706), new Variant(417));
                    }
                });
    }

    @Test
    public void test_Intersect_TwentyOneArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(99), new Variant(670), new Variant(242), new Variant(952), new
                Variant(80), new Variant(622), new Variant(350), new Variant(306), new Variant(457), new Variant(765)
                , new Variant(860), new Variant(689), new Variant(752), new Variant(235), new Variant(609), new
                        Variant(358), new Variant(914), new Variant(812), new Variant(413))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(99), new
                                Variant(670), new Variant(242), new Variant(952), new Variant(80), new Variant(622),
                                new Variant(350), new Variant(306), new Variant(457), new Variant(765), new Variant
                                        (860), new Variant(689), new Variant(752), new Variant(235), new Variant(609)
                                , new Variant(358), new Variant(914), new Variant(812), new Variant(413));
                    }
                });
    }

    @Test
    public void test_Intersect_TwentyTwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(657), new Variant(191), new Variant(478), new Variant(754), new
                Variant(155), new Variant(690), new Variant(257), new Variant(694), new Variant(577), new Variant
                (775), new Variant(611), new Variant(550), new Variant(455), new Variant(12), new Variant(661), new
                Variant(522), new Variant(735), new Variant(216), new Variant(621), new Variant(800))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(657), new
                                Variant(191), new Variant(478), new Variant(754), new Variant(155), new Variant(690),
                                new Variant(257), new Variant(694), new Variant(577), new Variant(775), new Variant
                                        (611), new Variant(550), new Variant(455), new Variant(12), new Variant(661),
                                new Variant(522), new Variant(735), new Variant(216), new Variant(621), new Variant
                                        (800));
                    }
                });
    }

    @Test
    public void test_Intersect_TwentyThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(117), new Variant(393), new Variant(968), new Variant(24), new
                Variant(888), new Variant(410), new Variant(268), new Variant(726), new Variant(335), new Variant
                (641), new Variant(207), new Variant(942), new Variant(93), new Variant(294), new Variant(952), new
                Variant(394), new Variant(434), new Variant(767), new Variant(400), new Variant(543), new Variant(896))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(117), new
                                Variant(393), new Variant(968), new Variant(24), new Variant(888), new Variant(410),
                                new Variant(268), new Variant(726), new Variant(335), new Variant(641), new Variant
                                        (207), new Variant(942), new Variant(93), new Variant(294), new Variant(952),
                                new Variant(394), new Variant(434), new Variant(767), new Variant(400), new Variant
                                        (543), new Variant(896));
                    }
                });
    }

    @Test
    public void test_Intersect_TwentyFourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(848), new Variant(844), new Variant(838), new Variant(127), new
                Variant(624), new Variant(986), new Variant(790), new Variant(517), new Variant(687), new Variant
                (206), new Variant(118), new Variant(822), new Variant(948), new Variant(0), new Variant(64), new
                Variant(707), new Variant(699), new Variant(691), new Variant(825), new Variant(330), new Variant
                (219), new Variant(684))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(848), new
                                Variant(844), new Variant(838), new Variant(127), new Variant(624), new Variant(986),
                                new Variant(790), new Variant(517), new Variant(687), new Variant(206), new Variant
                                        (118), new Variant(822), new Variant(948), new Variant(0), new Variant(64),
                                new Variant(707), new Variant(699), new Variant(691), new Variant(825), new Variant
                                        (330), new Variant(219), new Variant(684));
                    }
                });
    }

    @Test
    public void test_Intersect_TwentyFiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(398), new Variant(314), new Variant(182), new Variant(373), new
                Variant(80), new Variant(122), new Variant(601), new Variant(109), new Variant(616), new Variant(413)
                , new Variant(51), new Variant(590), new Variant(629), new Variant(691), new Variant(387), new
                        Variant(555), new Variant(106), new Variant(63), new Variant(474), new Variant(692), new
                        Variant(645), new Variant(360), new Variant(839))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(398), new
                                Variant(314), new Variant(182), new Variant(373), new Variant(80), new Variant(122),
                                new Variant(601), new Variant(109), new Variant(616), new Variant(413), new Variant
                                        (51), new Variant(590), new Variant(629), new Variant(691), new Variant(387),
                                new Variant(555), new Variant(106), new Variant(63), new Variant(474), new Variant
                                        (692), new Variant(645), new Variant(360), new Variant(839));
                    }
                });
    }

    @Test
    public void test_Intersect_TwentySixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(527), new Variant(882), new Variant(535), new Variant(737), new
                Variant(341), new Variant(974), new Variant(740), new Variant(39), new Variant(350), new Variant(815)
                , new Variant(605), new Variant(260), new Variant(362), new Variant(401), new Variant(957), new
                        Variant(246), new Variant(277), new Variant(67), new Variant(276), new Variant(45), new
                        Variant(189), new Variant(888), new Variant(312), new Variant(481))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(527), new
                                Variant(882), new Variant(535), new Variant(737), new Variant(341), new Variant(974),
                                new Variant(740), new Variant(39), new Variant(350), new Variant(815), new Variant
                                        (605), new Variant(260), new Variant(362), new Variant(401), new Variant(957)
                                , new Variant(246), new Variant(277), new Variant(67), new Variant(276), new Variant
                                        (45), new Variant(189), new Variant(888), new Variant(312), new Variant(481));
                    }
                });
    }

    @Test
    public void test_Intersect_TwentySevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(675), new Variant(930), new Variant(568), new Variant(148), new
                Variant(372), new Variant(809), new Variant(545), new Variant(270), new Variant(107), new Variant
                (144), new Variant(279), new Variant(295), new Variant(845), new Variant(320), new Variant(866), new
                Variant(944), new Variant(665), new Variant(646), new Variant(658), new Variant(266), new Variant
                (266), new Variant(88), new Variant(840), new Variant(288), new Variant(218))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(675), new
                                Variant(930), new Variant(568), new Variant(148), new Variant(372), new Variant(809),
                                new Variant(545), new Variant(270), new Variant(107), new Variant(144), new Variant
                                        (279), new Variant(295), new Variant(845), new Variant(320), new Variant(866)
                                , new Variant(944), new Variant(665), new Variant(646), new Variant(658), new Variant
                                        (266), new Variant(266), new Variant(88), new Variant(840), new Variant(288),
                                new Variant(218));
                    }
                });
    }

    @Test
    public void test_Intersect_TwentyEightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(134), new Variant(98), new Variant(553), new Variant(452), new
                Variant(51), new Variant(739), new Variant(869), new Variant(262), new Variant(578), new Variant(141)
                , new Variant(449), new Variant(50), new Variant(709), new Variant(219), new Variant(613), new
                        Variant(263), new Variant(48), new Variant(160), new Variant(978), new Variant(785), new
                        Variant(884), new Variant(646), new Variant(105), new Variant(609), new Variant(80), new
                        Variant(452))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(134), new
                                Variant(98), new Variant(553), new Variant(452), new Variant(51), new Variant(739),
                                new Variant(869), new Variant(262), new Variant(578), new Variant(141), new Variant
                                        (449), new Variant(50), new Variant(709), new Variant(219), new Variant(613),
                                new Variant(263), new Variant(48), new Variant(160), new Variant(978), new Variant
                                        (785), new Variant(884), new Variant(646), new Variant(105), new Variant(609)
                                , new Variant(80), new Variant(452));
                    }
                });
    }

    @Test
    public void test_Intersect_TwentyNineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(519), new Variant(170), new Variant(42), new Variant(983), new
                Variant(612), new Variant(530), new Variant(659), new Variant(363), new Variant(283), new Variant
                (520), new Variant(217), new Variant(894), new Variant(220), new Variant(265), new Variant(270), new
                Variant(417), new Variant(277), new Variant(913), new Variant(909), new Variant(444), new Variant
                (999), new Variant(880), new Variant(605), new Variant(197), new Variant(860), new Variant(506), new
                Variant(253))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(519), new
                                Variant(170), new Variant(42), new Variant(983), new Variant(612), new Variant(530),
                                new Variant(659), new Variant(363), new Variant(283), new Variant(520), new Variant
                                        (217), new Variant(894), new Variant(220), new Variant(265), new Variant(270)
                                , new Variant(417), new Variant(277), new Variant(913), new Variant(909), new Variant
                                        (444), new Variant(999), new Variant(880), new Variant(605), new Variant(197)
                                , new Variant(860), new Variant(506), new Variant(253));
                    }
                });
    }

    @Test
    public void test_Intersect_ThirtyArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2fe).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(37), new Variant(799), new Variant(51), new Variant(159), new
                Variant(127), new Variant(460), new Variant(486), new Variant(810), new Variant(277), new Variant
                (446), new Variant(944), new Variant(768), new Variant(529), new Variant(503), new Variant(453), new
                Variant(678), new Variant(797), new Variant(570), new Variant(886), new Variant(834), new Variant
                (264), new Variant(980), new Variant(366), new Variant(374), new Variant(454), new Variant(873), new
                Variant(560), new Variant(618))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Intersect(getMock(Range.class), getMock(Range.class), new Variant(37), new
                                Variant(799), new Variant(51), new Variant(159), new Variant(127), new Variant(460),
                                new Variant(486), new Variant(810), new Variant(277), new Variant(446), new Variant
                                        (944), new Variant(768), new Variant(529), new Variant(503), new Variant(453)
                                , new Variant(678), new Variant(797), new Variant(570), new Variant(886), new Variant
                                        (834), new Variant(264), new Variant(980), new Variant(366), new Variant(374)
                                , new Variant(454), new Variant(873), new Variant(560), new Variant(618));
                    }
                });
    }

    @Test
    public void test_getAxMenuBars_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x24d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<MenuBars>() {
                    @Override
                    public MenuBars invoke() throws ActiveXException {
                        return component.getAxMenuBars();
                    }
                });
    }

    @Test
    public void test_getAxModules_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x246).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Modules>() {
                    @Override
                    public Modules invoke() throws ActiveXException {
                        return component.getAxModules();
                    }
                });
    }

    @Test
    public void test_getAxNames_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1ba).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Names>() {
                    @Override
                    public Names invoke() throws ActiveXException {
                        return component.getAxNames();
                    }
                });
    }

    @Test
    public void test_getAxRange_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xc5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(546))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxRange(new Variant(546));
                    }
                });
    }

    @Test
    public void test_getAxRange_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(939), new Variant(495))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxRange(new Variant(939), new Variant(495));
                    }
                });
    }

    @Test
    public void test_getAxRows_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x102).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxRows();
                    }
                });
    }

    @Test
    public void test_Run_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run();
                    }
                });
    }

    @Test
    public void test_Run_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(640))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(640));
                    }
                });
    }

    @Test
    public void test_Run_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(571), new Variant(414))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(571), new Variant(414));
                    }
                });
    }

    @Test
    public void test_Run_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(585), new Variant(993), new
                Variant(968))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(585), new Variant(993), new Variant(968));
                    }
                });
    }

    @Test
    public void test_Run_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(199), new Variant(137), new
                Variant(493), new Variant(832))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(199), new Variant(137), new Variant(493), new Variant(832));
                    }
                });
    }

    @Test
    public void test_Run_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(818), new Variant(63), new Variant
                (672), new Variant(218), new Variant(578))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(818), new Variant(63), new Variant(672), new Variant(218),
                                new Variant(578));
                    }
                });
    }

    @Test
    public void test_Run_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(711), new Variant(200), new
                Variant(862), new Variant(555), new Variant(507), new Variant(410))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(711), new Variant(200), new Variant(862), new Variant(555),
                                new Variant(507), new Variant(410));
                    }
                });
    }

    @Test
    public void test_Run_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(679), new Variant(115), new
                Variant(845), new Variant(780), new Variant(926), new Variant(567), new Variant(132))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(679), new Variant(115), new Variant(845), new Variant(780),
                                new Variant(926), new Variant(567), new Variant(132));
                    }
                });
    }

    @Test
    public void test_Run_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(541), new Variant(420), new
                Variant(563), new Variant(930), new Variant(361), new Variant(499), new Variant(65), new Variant(393))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(541), new Variant(420), new Variant(563), new Variant(930),
                                new Variant(361), new Variant(499), new Variant(65), new Variant(393));
                    }
                });
    }

    @Test
    public void test_Run_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(353), new Variant(786), new
                Variant(947), new Variant(400), new Variant(751), new Variant(75), new Variant(947), new Variant(974)
                , new Variant(254))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(353), new Variant(786), new Variant(947), new Variant(400),
                                new Variant(751), new Variant(75), new Variant(947), new Variant(974), new Variant
                                        (254));
                    }
                });
    }

    @Test
    public void test_Run_TenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(738), new Variant(231), new
                Variant(665), new Variant(744), new Variant(516), new Variant(90), new Variant(514), new Variant(514)
                , new Variant(233), new Variant(909))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(738), new Variant(231), new Variant(665), new Variant(744),
                                new Variant(516), new Variant(90), new Variant(514), new Variant(514), new Variant
                                        (233), new Variant(909));
                    }
                });
    }

    @Test
    public void test_Run_ElevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(777), new Variant(858), new
                Variant(848), new Variant(965), new Variant(769), new Variant(313), new Variant(134), new Variant
                (502), new Variant(152), new Variant(99), new Variant(643))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(777), new Variant(858), new Variant(848), new Variant(965),
                                new Variant(769), new Variant(313), new Variant(134), new Variant(502), new Variant
                                        (152), new Variant(99), new Variant(643));
                    }
                });
    }

    @Test
    public void test_Run_TwelveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(38), new Variant(454), new Variant
                (898), new Variant(9), new Variant(204), new Variant(799), new Variant(698), new Variant(489), new
                Variant(862), new Variant(966), new Variant(456), new Variant(228))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(38), new Variant(454), new Variant(898), new Variant(9), new
                                Variant(204), new Variant(799), new Variant(698), new Variant(489), new Variant(862),
                                new Variant(966), new Variant(456), new Variant(228));
                    }
                });
    }

    @Test
    public void test_Run_ThirteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(50), new Variant(463), new Variant
                (12), new Variant(147), new Variant(268), new Variant(889), new Variant(934), new Variant(251), new
                Variant(383), new Variant(287), new Variant(709), new Variant(640), new Variant(767))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(50), new Variant(463), new Variant(12), new Variant(147),
                                new Variant(268), new Variant(889), new Variant(934), new Variant(251), new Variant
                                        (383), new Variant(287), new Variant(709), new Variant(640), new Variant(767));
                    }
                });
    }

    @Test
    public void test_Run_FourteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(770), new Variant(377), new
                Variant(869), new Variant(66), new Variant(21), new Variant(466), new Variant(62), new Variant(703),
                new Variant(596), new Variant(722), new Variant(578), new Variant(86), new Variant(417), new Variant
                        (853))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(770), new Variant(377), new Variant(869), new Variant(66),
                                new Variant(21), new Variant(466), new Variant(62), new Variant(703), new Variant
                                        (596), new Variant(722), new Variant(578), new Variant(86), new Variant(417),
                                new Variant(853));
                    }
                });
    }

    @Test
    public void test_Run_FifteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(752), new Variant(783), new
                Variant(732), new Variant(953), new Variant(20), new Variant(663), new Variant(703), new Variant(200)
                , new Variant(78), new Variant(701), new Variant(827), new Variant(154), new Variant(888), new
                        Variant(635), new Variant(339))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(752), new Variant(783), new Variant(732), new Variant(953),
                                new Variant(20), new Variant(663), new Variant(703), new Variant(200), new Variant
                                        (78), new Variant(701), new Variant(827), new Variant(154), new Variant(888),
                                new Variant(635), new Variant(339));
                    }
                });
    }

    @Test
    public void test_Run_SixteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(16), new Variant(994), new Variant
                (968), new Variant(147), new Variant(499), new Variant(260), new Variant(18), new Variant(476), new
                Variant(643), new Variant(967), new Variant(929), new Variant(327), new Variant(644), new Variant
                (840), new Variant(862), new Variant(747))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(16), new Variant(994), new Variant(968), new Variant(147),
                                new Variant(499), new Variant(260), new Variant(18), new Variant(476), new Variant
                                        (643), new Variant(967), new Variant(929), new Variant(327), new Variant(644)
                                , new Variant(840), new Variant(862), new Variant(747));
                    }
                });
    }

    @Test
    public void test_Run_SeventeenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(906), new Variant(554), new
                Variant(194), new Variant(197), new Variant(933), new Variant(95), new Variant(987), new Variant(675)
                , new Variant(87), new Variant(275), new Variant(617), new Variant(285), new Variant(554), new
                        Variant(589), new Variant(87), new Variant(680), new Variant(64))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(906), new Variant(554), new Variant(194), new Variant(197),
                                new Variant(933), new Variant(95), new Variant(987), new Variant(675), new Variant
                                        (87), new Variant(275), new Variant(617), new Variant(285), new Variant(554),
                                new Variant(589), new Variant(87), new Variant(680), new Variant(64));
                    }
                });
    }

    @Test
    public void test_Run_EighteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(370), new Variant(757), new
                Variant(520), new Variant(994), new Variant(56), new Variant(203), new Variant(458), new Variant(201)
                , new Variant(684), new Variant(599), new Variant(611), new Variant(827), new Variant(552), new
                        Variant(575), new Variant(712), new Variant(253), new Variant(884), new Variant(331))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(370), new Variant(757), new Variant(520), new Variant(994),
                                new Variant(56), new Variant(203), new Variant(458), new Variant(201), new Variant
                                        (684), new Variant(599), new Variant(611), new Variant(827), new Variant(552)
                                , new Variant(575), new Variant(712), new Variant(253), new Variant(884), new Variant
                                        (331));
                    }
                });
    }

    @Test
    public void test_Run_NineteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(644), new Variant(112), new
                Variant(216), new Variant(665), new Variant(959), new Variant(758), new Variant(612), new Variant
                (684), new Variant(209), new Variant(787), new Variant(501), new Variant(535), new Variant(523), new
                Variant(712), new Variant(932), new Variant(866), new Variant(277), new Variant(298), new Variant(955))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(644), new Variant(112), new Variant(216), new Variant(665),
                                new Variant(959), new Variant(758), new Variant(612), new Variant(684), new Variant
                                        (209), new Variant(787), new Variant(501), new Variant(535), new Variant(523)
                                , new Variant(712), new Variant(932), new Variant(866), new Variant(277), new Variant
                                        (298), new Variant(955));
                    }
                });
    }

    @Test
    public void test_Run_TwentyArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(903), new Variant(506), new
                Variant(473), new Variant(383), new Variant(159), new Variant(597), new Variant(669), new Variant
                (341), new Variant(414), new Variant(878), new Variant(763), new Variant(939), new Variant(541), new
                Variant(892), new Variant(957), new Variant(108), new Variant(470), new Variant(649), new Variant(16)
                , new Variant(174))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(903), new Variant(506), new Variant(473), new Variant(383),
                                new Variant(159), new Variant(597), new Variant(669), new Variant(341), new Variant
                                        (414), new Variant(878), new Variant(763), new Variant(939), new Variant(541)
                                , new Variant(892), new Variant(957), new Variant(108), new Variant(470), new Variant
                                        (649), new Variant(16), new Variant(174));
                    }
                });
    }

    @Test
    public void test_Run_TwentyOneArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(361), new Variant(637), new
                Variant(279), new Variant(916), new Variant(861), new Variant(672), new Variant(877), new Variant(67)
                , new Variant(339), new Variant(879), new Variant(583), new Variant(460), new Variant(500), new
                        Variant(73), new Variant(399), new Variant(573), new Variant(915), new Variant(359), new
                        Variant(429), new Variant(756), new Variant(37))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(361), new Variant(637), new Variant(279), new Variant(916),
                                new Variant(861), new Variant(672), new Variant(877), new Variant(67), new Variant
                                        (339), new Variant(879), new Variant(583), new Variant(460), new Variant(500)
                                , new Variant(73), new Variant(399), new Variant(573), new Variant(915), new Variant
                                        (359), new Variant(429), new Variant(756), new Variant(37));
                    }
                });
    }

    @Test
    public void test_Run_TwentyTwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(943), new Variant(128), new
                Variant(841), new Variant(229), new Variant(124), new Variant(42), new Variant(606), new Variant(356)
                , new Variant(507), new Variant(66), new Variant(101), new Variant(333), new Variant(531), new
                        Variant(859), new Variant(671), new Variant(103), new Variant(794), new Variant(802), new
                        Variant(293), new Variant(923), new Variant(241), new Variant(77))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(943), new Variant(128), new Variant(841), new Variant(229),
                                new Variant(124), new Variant(42), new Variant(606), new Variant(356), new Variant
                                        (507), new Variant(66), new Variant(101), new Variant(333), new Variant(531),
                                new Variant(859), new Variant(671), new Variant(103), new Variant(794), new Variant
                                        (802), new Variant(293), new Variant(923), new Variant(241), new Variant(77));
                    }
                });
    }

    @Test
    public void test_Run_TwentyThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(956), new Variant(158), new
                Variant(91), new Variant(510), new Variant(10), new Variant(480), new Variant(63), new Variant(951),
                new Variant(887), new Variant(242), new Variant(903), new Variant(623), new Variant(587), new Variant
                        (23), new Variant(933), new Variant(658), new Variant(962), new Variant(961), new Variant
                        (577), new Variant(423), new Variant(718), new Variant(580), new Variant(377))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(956), new Variant(158), new Variant(91), new Variant(510),
                                new Variant(10), new Variant(480), new Variant(63), new Variant(951), new Variant
                                        (887), new Variant(242), new Variant(903), new Variant(623), new Variant(587)
                                , new Variant(23), new Variant(933), new Variant(658), new Variant(962), new Variant
                                        (961), new Variant(577), new Variant(423), new Variant(718), new Variant(580)
                                , new Variant(377));
                    }
                });
    }

    @Test
    public void test_Run_TwentyFourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(323), new Variant(217), new
                Variant(96), new Variant(326), new Variant(820), new Variant(628), new Variant(544), new Variant(558)
                , new Variant(304), new Variant(817), new Variant(919), new Variant(564), new Variant(747), new
                        Variant(658), new Variant(98), new Variant(136), new Variant(182), new Variant(229), new
                        Variant(416), new Variant(204), new Variant(101), new Variant(669), new Variant(767), new
                        Variant(316))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(323), new Variant(217), new Variant(96), new Variant(326),
                                new Variant(820), new Variant(628), new Variant(544), new Variant(558), new Variant
                                        (304), new Variant(817), new Variant(919), new Variant(564), new Variant(747)
                                , new Variant(658), new Variant(98), new Variant(136), new Variant(182), new Variant
                                        (229), new Variant(416), new Variant(204), new Variant(101), new Variant(669)
                                , new Variant(767), new Variant(316));
                    }
                });
    }

    @Test
    public void test_Run_TwentyFiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(209), new Variant(365), new
                Variant(216), new Variant(208), new Variant(684), new Variant(731), new Variant(770), new Variant
                (386), new Variant(308), new Variant(302), new Variant(196), new Variant(39), new Variant(270), new
                Variant(822), new Variant(732), new Variant(748), new Variant(324), new Variant(327), new Variant
                (373), new Variant(343), new Variant(281), new Variant(889), new Variant(37), new Variant(510), new
                Variant(560))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(209), new Variant(365), new Variant(216), new Variant(208),
                                new Variant(684), new Variant(731), new Variant(770), new Variant(386), new Variant
                                        (308), new Variant(302), new Variant(196), new Variant(39), new Variant(270),
                                new Variant(822), new Variant(732), new Variant(748), new Variant(324), new Variant
                                        (327), new Variant(373), new Variant(343), new Variant(281), new Variant(889)
                                , new Variant(37), new Variant(510), new Variant(560));
                    }
                });
    }

    @Test
    public void test_Run_TwentySixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(863), new Variant(372), new
                Variant(71), new Variant(221), new Variant(402), new Variant(272), new Variant(662), new Variant(627)
                , new Variant(610), new Variant(758), new Variant(636), new Variant(749), new Variant(176), new
                        Variant(995), new Variant(290), new Variant(808), new Variant(83), new Variant(400), new
                        Variant(482), new Variant(317), new Variant(637), new Variant(972), new Variant(902), new
                        Variant(373), new Variant(729), new Variant(723))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(863), new Variant(372), new Variant(71), new Variant(221),
                                new Variant(402), new Variant(272), new Variant(662), new Variant(627), new Variant
                                        (610), new Variant(758), new Variant(636), new Variant(749), new Variant(176)
                                , new Variant(995), new Variant(290), new Variant(808), new Variant(83), new Variant
                                        (400), new Variant(482), new Variant(317), new Variant(637), new Variant(972)
                                , new Variant(902), new Variant(373), new Variant(729), new Variant(723));
                    }
                });
    }

    @Test
    public void test_Run_TwentySevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(872), new Variant(540), new
                Variant(859), new Variant(700), new Variant(525), new Variant(712), new Variant(724), new Variant
                (929), new Variant(623), new Variant(83), new Variant(528), new Variant(231), new Variant(613), new
                Variant(692), new Variant(694), new Variant(341), new Variant(41), new Variant(29), new Variant(563),
                new Variant(122), new Variant(750), new Variant(61), new Variant(27), new Variant(943), new Variant
                        (971), new Variant(741), new Variant(398))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(872), new Variant(540), new Variant(859), new Variant(700),
                                new Variant(525), new Variant(712), new Variant(724), new Variant(929), new Variant
                                        (623), new Variant(83), new Variant(528), new Variant(231), new Variant(613),
                                new Variant(692), new Variant(694), new Variant(341), new Variant(41), new Variant
                                        (29), new Variant(563), new Variant(122), new Variant(750), new Variant(61),
                                new Variant(27), new Variant(943), new Variant(971), new Variant(741), new Variant
                                        (398));
                    }
                });
    }

    @Test
    public void test_Run_TwentyEightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(707), new Variant(841), new
                Variant(431), new Variant(347), new Variant(541), new Variant(301), new Variant(58), new Variant(644)
                , new Variant(804), new Variant(602), new Variant(730), new Variant(829), new Variant(339), new
                        Variant(558), new Variant(453), new Variant(442), new Variant(368), new Variant(927), new
                        Variant(840), new Variant(556), new Variant(811), new Variant(290), new Variant(408), new
                        Variant(815), new Variant(900), new Variant(456), new Variant(605), new Variant(67))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(707), new Variant(841), new Variant(431), new Variant(347),
                                new Variant(541), new Variant(301), new Variant(58), new Variant(644), new Variant
                                        (804), new Variant(602), new Variant(730), new Variant(829), new Variant(339)
                                , new Variant(558), new Variant(453), new Variant(442), new Variant(368), new Variant
                                        (927), new Variant(840), new Variant(556), new Variant(811), new Variant(290)
                                , new Variant(408), new Variant(815), new Variant(900), new Variant(456), new Variant
                                        (605), new Variant(67));
                    }
                });
    }

    @Test
    public void test_Run_TwentyNineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(317), new Variant(30), new Variant
                (697), new Variant(781), new Variant(263), new Variant(679), new Variant(782), new Variant(178), new
                Variant(280), new Variant(488), new Variant(868), new Variant(383), new Variant(977), new Variant
                (575), new Variant(834), new Variant(872), new Variant(982), new Variant(681), new Variant(508), new
                Variant(939), new Variant(583), new Variant(215), new Variant(987), new Variant(744), new Variant
                (316), new Variant(380), new Variant(467), new Variant(64), new Variant(565))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(317), new Variant(30), new Variant(697), new Variant(781),
                                new Variant(263), new Variant(679), new Variant(782), new Variant(178), new Variant
                                        (280), new Variant(488), new Variant(868), new Variant(383), new Variant(977)
                                , new Variant(575), new Variant(834), new Variant(872), new Variant(982), new Variant
                                        (681), new Variant(508), new Variant(939), new Variant(583), new Variant(215)
                                , new Variant(987), new Variant(744), new Variant(316), new Variant(380), new Variant
                                        (467), new Variant(64), new Variant(565));
                    }
                });
    }

    @Test
    public void test_Run_ThirtyArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(742), new Variant(582), new
                Variant(542), new Variant(863), new Variant(918), new Variant(437), new Variant(30), new Variant(18),
                new Variant(606), new Variant(38), new Variant(313), new Variant(535), new Variant(862), new Variant
                        (681), new Variant(650), new Variant(775), new Variant(690), new Variant(940), new Variant
                        (504), new Variant(215), new Variant(308), new Variant(119), new Variant(73), new Variant
                        (672), new Variant(441), new Variant(970), new Variant(823), new Variant(242), new Variant
                        (155), new Variant(586))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(742), new Variant(582), new Variant(542), new Variant(863),
                                new Variant(918), new Variant(437), new Variant(30), new Variant(18), new Variant
                                        (606), new Variant(38), new Variant(313), new Variant(535), new Variant(862),
                                new Variant(681), new Variant(650), new Variant(775), new Variant(690), new Variant
                                        (940), new Variant(504), new Variant(215), new Variant(308), new Variant(119)
                                , new Variant(73), new Variant(672), new Variant(441), new Variant(970), new Variant
                                        (823), new Variant(242), new Variant(155), new Variant(586));
                    }
                });
    }

    @Test
    public void test_Run_ThirtyOneArgs_ShouldRedirectToProxy() throws Exception {
        on(0x103).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(57), new Variant(960), new Variant
                (939), new Variant(42), new Variant(169), new Variant(847), new Variant(848), new Variant(366), new
                Variant(13), new Variant(665), new Variant(912), new Variant(915), new Variant(316), new Variant(702)
                , new Variant(410), new Variant(298), new Variant(471), new Variant(826), new Variant(182), new
                        Variant(44), new Variant(82), new Variant(65), new Variant(442), new Variant(528), new
                        Variant(390), new Variant(166), new Variant(417), new Variant(351), new Variant(164), new
                        Variant(587), new Variant(610))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.Run(new Variant(57), new Variant(960), new Variant(939), new Variant(42),
                                new Variant(169), new Variant(847), new Variant(848), new Variant(366), new Variant
                                        (13), new Variant(665), new Variant(912), new Variant(915), new Variant(316),
                                new Variant(702), new Variant(410), new Variant(298), new Variant(471), new Variant
                                        (826), new Variant(182), new Variant(44), new Variant(82), new Variant(65),
                                new Variant(442), new Variant(528), new Variant(390), new Variant(166), new Variant
                                        (417), new Variant(351), new Variant(164), new Variant(587), new Variant(610));
                    }
                });
    }

    @Test
    public void test__Run2_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2();
                    }
                });
    }

    @Test
    public void test__Run2_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(200))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(200));
                    }
                });
    }

    @Test
    public void test__Run2_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(600), new Variant(867))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(600), new Variant(867));
                    }
                });
    }

    @Test
    public void test__Run2_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(651), new Variant(847), new
                Variant(23))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(651), new Variant(847), new Variant(23));
                    }
                });
    }

    @Test
    public void test__Run2_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(363), new Variant(807), new
                Variant(224), new Variant(350))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(363), new Variant(807), new Variant(224), new Variant(350));
                    }
                });
    }

    @Test
    public void test__Run2_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(904), new Variant(643), new
                Variant(233), new Variant(896), new Variant(626))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(904), new Variant(643), new Variant(233), new Variant(896)
                                , new Variant(626));
                    }
                });
    }

    @Test
    public void test__Run2_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(561), new Variant(406), new
                Variant(172), new Variant(573), new Variant(183), new Variant(214))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(561), new Variant(406), new Variant(172), new Variant(573)
                                , new Variant(183), new Variant(214));
                    }
                });
    }

    @Test
    public void test__Run2_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(57), new Variant(136), new Variant
                (896), new Variant(395), new Variant(583), new Variant(102), new Variant(884))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(57), new Variant(136), new Variant(896), new Variant(395),
                                new Variant(583), new Variant(102), new Variant(884));
                    }
                });
    }

    @Test
    public void test__Run2_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(71), new Variant(76), new Variant
                (394), new Variant(590), new Variant(569), new Variant(551), new Variant(24), new Variant(554))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(71), new Variant(76), new Variant(394), new Variant(590),
                                new Variant(569), new Variant(551), new Variant(24), new Variant(554));
                    }
                });
    }

    @Test
    public void test__Run2_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(631), new Variant(252), new
                Variant(343), new Variant(961), new Variant(606), new Variant(436), new Variant(570), new Variant(90)
                , new Variant(500))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(631), new Variant(252), new Variant(343), new Variant(961)
                                , new Variant(606), new Variant(436), new Variant(570), new Variant(90), new Variant
                                        (500));
                    }
                });
    }

    @Test
    public void test__Run2_TenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(641), new Variant(933), new
                Variant(511), new Variant(775), new Variant(923), new Variant(557), new Variant(793), new Variant
                (566), new Variant(586), new Variant(784))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(641), new Variant(933), new Variant(511), new Variant(775)
                                , new Variant(923), new Variant(557), new Variant(793), new Variant(566), new Variant
                                        (586), new Variant(784));
                    }
                });
    }

    @Test
    public void test__Run2_ElevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(937), new Variant(237), new
                Variant(168), new Variant(260), new Variant(53), new Variant(830), new Variant(610), new Variant(276)
                , new Variant(122), new Variant(474), new Variant(731))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(937), new Variant(237), new Variant(168), new Variant(260)
                                , new Variant(53), new Variant(830), new Variant(610), new Variant(276), new Variant
                                        (122), new Variant(474), new Variant(731));
                    }
                });
    }

    @Test
    public void test__Run2_TwelveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(68), new Variant(332), new Variant
                (64), new Variant(581), new Variant(221), new Variant(599), new Variant(444), new Variant(133), new
                Variant(316), new Variant(257), new Variant(129), new Variant(121))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(68), new Variant(332), new Variant(64), new Variant(581),
                                new Variant(221), new Variant(599), new Variant(444), new Variant(133), new Variant
                                        (316), new Variant(257), new Variant(129), new Variant(121));
                    }
                });
    }

    @Test
    public void test__Run2_ThirteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(309), new Variant(791), new
                Variant(961), new Variant(409), new Variant(110), new Variant(473), new Variant(976), new Variant
                (376), new Variant(318), new Variant(658), new Variant(289), new Variant(869), new Variant(332))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(309), new Variant(791), new Variant(961), new Variant(409)
                                , new Variant(110), new Variant(473), new Variant(976), new Variant(376), new Variant
                                        (318), new Variant(658), new Variant(289), new Variant(869), new Variant(332));
                    }
                });
    }

    @Test
    public void test__Run2_FourteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(383), new Variant(480), new
                Variant(818), new Variant(171), new Variant(980), new Variant(479), new Variant(272), new Variant
                (683), new Variant(85), new Variant(708), new Variant(357), new Variant(963), new Variant(192), new
                Variant(808))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(383), new Variant(480), new Variant(818), new Variant(171)
                                , new Variant(980), new Variant(479), new Variant(272), new Variant(683), new Variant
                                        (85), new Variant(708), new Variant(357), new Variant(963), new Variant(192),
                                new Variant(808));
                    }
                });
    }

    @Test
    public void test__Run2_FifteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(756), new Variant(610), new
                Variant(229), new Variant(290), new Variant(471), new Variant(862), new Variant(918), new Variant
                (537), new Variant(666), new Variant(364), new Variant(673), new Variant(128), new Variant(399), new
                Variant(173), new Variant(983))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(756), new Variant(610), new Variant(229), new Variant(290)
                                , new Variant(471), new Variant(862), new Variant(918), new Variant(537), new Variant
                                        (666), new Variant(364), new Variant(673), new Variant(128), new Variant(399)
                                , new Variant(173), new Variant(983));
                    }
                });
    }

    @Test
    public void test__Run2_SixteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(292), new Variant(34), new Variant
                (969), new Variant(360), new Variant(914), new Variant(521), new Variant(21), new Variant(397), new
                Variant(883), new Variant(762), new Variant(792), new Variant(410), new Variant(529), new Variant(97)
                , new Variant(252), new Variant(518))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(292), new Variant(34), new Variant(969), new Variant(360),
                                new Variant(914), new Variant(521), new Variant(21), new Variant(397), new Variant
                                        (883), new Variant(762), new Variant(792), new Variant(410), new Variant(529)
                                , new Variant(97), new Variant(252), new Variant(518));
                    }
                });
    }

    @Test
    public void test__Run2_SeventeenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(675), new Variant(972), new
                Variant(936), new Variant(800), new Variant(588), new Variant(196), new Variant(890), new Variant
                (648), new Variant(514), new Variant(458), new Variant(730), new Variant(183), new Variant(467), new
                Variant(308), new Variant(353), new Variant(564), new Variant(234))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(675), new Variant(972), new Variant(936), new Variant(800)
                                , new Variant(588), new Variant(196), new Variant(890), new Variant(648), new Variant
                                        (514), new Variant(458), new Variant(730), new Variant(183), new Variant(467)
                                , new Variant(308), new Variant(353), new Variant(564), new Variant(234));
                    }
                });
    }

    @Test
    public void test__Run2_EighteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(571), new Variant(296), new
                Variant(611), new Variant(678), new Variant(42), new Variant(270), new Variant(148), new Variant(371)
                , new Variant(5), new Variant(673), new Variant(174), new Variant(522), new Variant(756), new Variant
                        (637), new Variant(550), new Variant(499), new Variant(170), new Variant(426))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(571), new Variant(296), new Variant(611), new Variant(678)
                                , new Variant(42), new Variant(270), new Variant(148), new Variant(371), new Variant
                                        (5), new Variant(673), new Variant(174), new Variant(522), new Variant(756),
                                new Variant(637), new Variant(550), new Variant(499), new Variant(170), new Variant
                                        (426));
                    }
                });
    }

    @Test
    public void test__Run2_NineteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(960), new Variant(892), new
                Variant(246), new Variant(527), new Variant(424), new Variant(841), new Variant(701), new Variant
                (157), new Variant(22), new Variant(75), new Variant(250), new Variant(959), new Variant(684), new
                Variant(14), new Variant(988), new Variant(301), new Variant(141), new Variant(961), new Variant(994))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(960), new Variant(892), new Variant(246), new Variant(527)
                                , new Variant(424), new Variant(841), new Variant(701), new Variant(157), new Variant
                                        (22), new Variant(75), new Variant(250), new Variant(959), new Variant(684),
                                new Variant(14), new Variant(988), new Variant(301), new Variant(141), new Variant
                                        (961), new Variant(994));
                    }
                });
    }

    @Test
    public void test__Run2_TwentyArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(208), new Variant(939), new
                Variant(570), new Variant(277), new Variant(104), new Variant(741), new Variant(114), new Variant
                (962), new Variant(81), new Variant(771), new Variant(444), new Variant(914), new Variant(931), new
                Variant(392), new Variant(220), new Variant(368), new Variant(128), new Variant(27), new Variant(906)
                , new Variant(423))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(208), new Variant(939), new Variant(570), new Variant(277)
                                , new Variant(104), new Variant(741), new Variant(114), new Variant(962), new Variant
                                        (81), new Variant(771), new Variant(444), new Variant(914), new Variant(931),
                                new Variant(392), new Variant(220), new Variant(368), new Variant(128), new Variant
                                        (27), new Variant(906), new Variant(423));
                    }
                });
    }

    @Test
    public void test__Run2_TwentyOneArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(41), new Variant(626), new Variant
                (237), new Variant(38), new Variant(754), new Variant(923), new Variant(828), new Variant(529), new
                Variant(212), new Variant(976), new Variant(304), new Variant(436), new Variant(985), new Variant
                (167), new Variant(493), new Variant(326), new Variant(906), new Variant(59), new Variant(751), new
                Variant(920), new Variant(340))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(41), new Variant(626), new Variant(237), new Variant(38),
                                new Variant(754), new Variant(923), new Variant(828), new Variant(529), new Variant
                                        (212), new Variant(976), new Variant(304), new Variant(436), new Variant(985)
                                , new Variant(167), new Variant(493), new Variant(326), new Variant(906), new Variant
                                        (59), new Variant(751), new Variant(920), new Variant(340));
                    }
                });
    }

    @Test
    public void test__Run2_TwentyTwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(58), new Variant(706), new Variant
                (465), new Variant(529), new Variant(420), new Variant(33), new Variant(71), new Variant(58), new
                Variant(581), new Variant(0), new Variant(604), new Variant(322), new Variant(119), new Variant(613),
                new Variant(771), new Variant(398), new Variant(71), new Variant(121), new Variant(653), new Variant
                        (881), new Variant(449), new Variant(917))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(58), new Variant(706), new Variant(465), new Variant(529),
                                new Variant(420), new Variant(33), new Variant(71), new Variant(58), new Variant(581)
                                , new Variant(0), new Variant(604), new Variant(322), new Variant(119), new Variant
                                        (613), new Variant(771), new Variant(398), new Variant(71), new Variant(121),
                                new Variant(653), new Variant(881), new Variant(449), new Variant(917));
                    }
                });
    }

    @Test
    public void test__Run2_TwentyThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(84), new Variant(100), new Variant
                (827), new Variant(591), new Variant(980), new Variant(346), new Variant(788), new Variant(948), new
                Variant(329), new Variant(226), new Variant(719), new Variant(863), new Variant(665), new Variant
                (630), new Variant(32), new Variant(40), new Variant(230), new Variant(760), new Variant(297), new
                Variant(496), new Variant(664), new Variant(531), new Variant(521))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(84), new Variant(100), new Variant(827), new Variant(591),
                                new Variant(980), new Variant(346), new Variant(788), new Variant(948), new Variant
                                        (329), new Variant(226), new Variant(719), new Variant(863), new Variant(665)
                                , new Variant(630), new Variant(32), new Variant(40), new Variant(230), new Variant
                                        (760), new Variant(297), new Variant(496), new Variant(664), new Variant(531)
                                , new Variant(521));
                    }
                });
    }

    @Test
    public void test__Run2_TwentyFourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(280), new Variant(277), new
                Variant(719), new Variant(498), new Variant(849), new Variant(854), new Variant(911), new Variant
                (189), new Variant(142), new Variant(375), new Variant(269), new Variant(301), new Variant(805), new
                Variant(554), new Variant(638), new Variant(292), new Variant(181), new Variant(514), new Variant
                (695), new Variant(966), new Variant(498), new Variant(23), new Variant(246), new Variant(696))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(280), new Variant(277), new Variant(719), new Variant(498)
                                , new Variant(849), new Variant(854), new Variant(911), new Variant(189), new Variant
                                        (142), new Variant(375), new Variant(269), new Variant(301), new Variant(805)
                                , new Variant(554), new Variant(638), new Variant(292), new Variant(181), new Variant
                                        (514), new Variant(695), new Variant(966), new Variant(498), new Variant(23),
                                new Variant(246), new Variant(696));
                    }
                });
    }

    @Test
    public void test__Run2_TwentyFiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(755), new Variant(298), new
                Variant(166), new Variant(228), new Variant(685), new Variant(238), new Variant(26), new Variant(564)
                , new Variant(568), new Variant(489), new Variant(722), new Variant(137), new Variant(663), new
                        Variant(630), new Variant(443), new Variant(391), new Variant(157), new Variant(913), new
                        Variant(833), new Variant(830), new Variant(651), new Variant(110), new Variant(64), new
                        Variant(24), new Variant(542))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(755), new Variant(298), new Variant(166), new Variant(228)
                                , new Variant(685), new Variant(238), new Variant(26), new Variant(564), new Variant
                                        (568), new Variant(489), new Variant(722), new Variant(137), new Variant(663)
                                , new Variant(630), new Variant(443), new Variant(391), new Variant(157), new Variant
                                        (913), new Variant(833), new Variant(830), new Variant(651), new Variant(110)
                                , new Variant(64), new Variant(24), new Variant(542));
                    }
                });
    }

    @Test
    public void test__Run2_TwentySixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(382), new Variant(696), new
                Variant(250), new Variant(469), new Variant(102), new Variant(327), new Variant(145), new Variant
                (528), new Variant(398), new Variant(152), new Variant(514), new Variant(571), new Variant(787), new
                Variant(577), new Variant(573), new Variant(346), new Variant(226), new Variant(506), new Variant
                (215), new Variant(871), new Variant(450), new Variant(681), new Variant(99), new Variant(424), new
                Variant(196), new Variant(123))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(382), new Variant(696), new Variant(250), new Variant(469)
                                , new Variant(102), new Variant(327), new Variant(145), new Variant(528), new Variant
                                        (398), new Variant(152), new Variant(514), new Variant(571), new Variant(787)
                                , new Variant(577), new Variant(573), new Variant(346), new Variant(226), new Variant
                                        (506), new Variant(215), new Variant(871), new Variant(450), new Variant(681)
                                , new Variant(99), new Variant(424), new Variant(196), new Variant(123));
                    }
                });
    }

    @Test
    public void test__Run2_TwentySevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(637), new Variant(171), new
                Variant(266), new Variant(85), new Variant(715), new Variant(283), new Variant(185), new Variant(616)
                , new Variant(103), new Variant(532), new Variant(332), new Variant(411), new Variant(61), new
                        Variant(553), new Variant(838), new Variant(739), new Variant(526), new Variant(736), new
                        Variant(492), new Variant(741), new Variant(7), new Variant(339), new Variant(549), new
                        Variant(683), new Variant(945), new Variant(39), new Variant(54))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(637), new Variant(171), new Variant(266), new Variant(85),
                                new Variant(715), new Variant(283), new Variant(185), new Variant(616), new Variant
                                        (103), new Variant(532), new Variant(332), new Variant(411), new Variant(61),
                                new Variant(553), new Variant(838), new Variant(739), new Variant(526), new Variant
                                        (736), new Variant(492), new Variant(741), new Variant(7), new Variant(339),
                                new Variant(549), new Variant(683), new Variant(945), new Variant(39), new Variant(54));
                    }
                });
    }

    @Test
    public void test__Run2_TwentyEightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(133), new Variant(173), new
                Variant(193), new Variant(438), new Variant(375), new Variant(372), new Variant(932), new Variant
                (347), new Variant(481), new Variant(424), new Variant(127), new Variant(760), new Variant(252), new
                Variant(827), new Variant(28), new Variant(604), new Variant(727), new Variant(978), new Variant(172)
                , new Variant(695), new Variant(465), new Variant(677), new Variant(557), new Variant(851), new
                        Variant(882), new Variant(774), new Variant(69), new Variant(997))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(133), new Variant(173), new Variant(193), new Variant(438)
                                , new Variant(375), new Variant(372), new Variant(932), new Variant(347), new Variant
                                        (481), new Variant(424), new Variant(127), new Variant(760), new Variant(252)
                                , new Variant(827), new Variant(28), new Variant(604), new Variant(727), new Variant
                                        (978), new Variant(172), new Variant(695), new Variant(465), new Variant(677)
                                , new Variant(557), new Variant(851), new Variant(882), new Variant(774), new Variant
                                        (69), new Variant(997));
                    }
                });
    }

    @Test
    public void test__Run2_TwentyNineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(130), new Variant(915), new
                Variant(48), new Variant(615), new Variant(131), new Variant(970), new Variant(934), new Variant(11),
                new Variant(362), new Variant(448), new Variant(704), new Variant(14), new Variant(63), new Variant
                        (229), new Variant(64), new Variant(678), new Variant(727), new Variant(160), new Variant(16)
                , new Variant(993), new Variant(479), new Variant(187), new Variant(155), new Variant(628), new
                        Variant(625), new Variant(954), new Variant(992), new Variant(405), new Variant(435))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(130), new Variant(915), new Variant(48), new Variant(615),
                                new Variant(131), new Variant(970), new Variant(934), new Variant(11), new Variant
                                        (362), new Variant(448), new Variant(704), new Variant(14), new Variant(63),
                                new Variant(229), new Variant(64), new Variant(678), new Variant(727), new Variant
                                        (160), new Variant(16), new Variant(993), new Variant(479), new Variant(187),
                                new Variant(155), new Variant(628), new Variant(625), new Variant(954), new Variant
                                        (992), new Variant(405), new Variant(435));
                    }
                });
    }

    @Test
    public void test__Run2_ThirtyArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(854), new Variant(478), new
                Variant(286), new Variant(290), new Variant(896), new Variant(585), new Variant(423), new Variant
                (174), new Variant(484), new Variant(585), new Variant(390), new Variant(399), new Variant(524), new
                Variant(363), new Variant(109), new Variant(189), new Variant(581), new Variant(665), new Variant(8),
                new Variant(525), new Variant(803), new Variant(613), new Variant(681), new Variant(519), new Variant
                        (804), new Variant(756), new Variant(306), new Variant(76), new Variant(771), new Variant(413))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(854), new Variant(478), new Variant(286), new Variant(290)
                                , new Variant(896), new Variant(585), new Variant(423), new Variant(174), new Variant
                                        (484), new Variant(585), new Variant(390), new Variant(399), new Variant(524)
                                , new Variant(363), new Variant(109), new Variant(189), new Variant(581), new Variant
                                        (665), new Variant(8), new Variant(525), new Variant(803), new Variant(613),
                                new Variant(681), new Variant(519), new Variant(804), new Variant(756), new Variant
                                        (306), new Variant(76), new Variant(771), new Variant(413));
                    }
                });
    }

    @Test
    public void test__Run2_ThirtyOneArgs_ShouldRedirectToProxy() throws Exception {
        on(0x326).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(46), new Variant(717), new Variant
                (395), new Variant(584), new Variant(525), new Variant(39), new Variant(189), new Variant(19), new
                Variant(139), new Variant(851), new Variant(489), new Variant(728), new Variant(619), new Variant
                (242), new Variant(757), new Variant(722), new Variant(125), new Variant(429), new Variant(605), new
                Variant(182), new Variant(505), new Variant(938), new Variant(975), new Variant(887), new Variant
                (230), new Variant(450), new Variant(145), new Variant(322), new Variant(412), new Variant(104), new
                Variant(114))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._Run2(new Variant(46), new Variant(717), new Variant(395), new Variant(584),
                                new Variant(525), new Variant(39), new Variant(189), new Variant(19), new Variant
                                        (139), new Variant(851), new Variant(489), new Variant(728), new Variant(619)
                                , new Variant(242), new Variant(757), new Variant(722), new Variant(125), new Variant
                                        (429), new Variant(605), new Variant(182), new Variant(505), new Variant(938)
                                , new Variant(975), new Variant(887), new Variant(230), new Variant(450), new Variant
                                        (145), new Variant(322), new Variant(412), new Variant(104), new Variant(114));
                    }
                });
    }

    @Test
    public void test_getAxSelection_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x93).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxSelection();
                    }
                });
    }

    @Test
    public void test_SendKeys_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x17f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(576))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SendKeys(new Variant(576));
                    }
                });
    }

    @Test
    public void test_SendKeys_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x17f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(82), new Variant(324))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SendKeys(new Variant(82), new Variant(324));
                    }
                });
    }

    @Test
    public void test_getAxSheets_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1e5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Sheets>() {
                    @Override
                    public Sheets invoke() throws ActiveXException {
                        return component.getAxSheets();
                    }
                });
    }

    @Test
    public void test_getAxShortcutMenus_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x308).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(42))
                .verifyReturnsDispatchable(new Returns<Menu>() {
                    @Override
                    public Menu invoke() throws ActiveXException {
                        return component.getAxShortcutMenus(42);
                    }
                });
    }

    @Test
    public void test_getAxThisWorkbook_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxThisWorkbook();
                    }
                });
    }

    @Test
    public void test_getAxToolbars_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x228).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Toolbars>() {
                    @Override
                    public Toolbars invoke() throws ActiveXException {
                        return component.getAxToolbars();
                    }
                });
    }

    @Test
    public void test_Union_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class));
                    }
                });
    }

    @Test
    public void test_Union_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(65))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(65));
                    }
                });
    }

    @Test
    public void test_Union_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(233), new Variant(661))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(233), new
                                Variant(661));
                    }
                });
    }

    @Test
    public void test_Union_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(173), new Variant(550), new Variant(533))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(173), new
                                Variant(550), new Variant(533));
                    }
                });
    }

    @Test
    public void test_Union_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(974), new Variant(286), new Variant(315), new Variant(821))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(974), new
                                Variant(286), new Variant(315), new Variant(821));
                    }
                });
    }

    @Test
    public void test_Union_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(567), new Variant(7), new Variant(559), new Variant(625), new
                Variant(570))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(567), new
                                Variant(7), new Variant(559), new Variant(625), new Variant(570));
                    }
                });
    }

    @Test
    public void test_Union_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(748), new Variant(247), new Variant(763), new Variant(765), new
                Variant(458), new Variant(177))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(748), new
                                Variant(247), new Variant(763), new Variant(765), new Variant(458), new Variant(177));
                    }
                });
    }

    @Test
    public void test_Union_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(417), new Variant(533), new Variant(694), new Variant(958), new
                Variant(912), new Variant(78), new Variant(912))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(417), new
                                Variant(533), new Variant(694), new Variant(958), new Variant(912), new Variant(78),
                                new Variant(912));
                    }
                });
    }

    @Test
    public void test_Union_TenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(435), new Variant(315), new Variant(373), new Variant(428), new
                Variant(173), new Variant(587), new Variant(747), new Variant(161))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(435), new
                                Variant(315), new Variant(373), new Variant(428), new Variant(173), new Variant(587),
                                new Variant(747), new Variant(161));
                    }
                });
    }

    @Test
    public void test_Union_ElevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(894), new Variant(49), new Variant(622), new Variant(754), new
                Variant(632), new Variant(174), new Variant(277), new Variant(107), new Variant(173))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(894), new
                                Variant(49), new Variant(622), new Variant(754), new Variant(632), new Variant(174),
                                new Variant(277), new Variant(107), new Variant(173));
                    }
                });
    }

    @Test
    public void test_Union_TwelveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(627), new Variant(135), new Variant(190), new Variant(889), new
                Variant(613), new Variant(585), new Variant(346), new Variant(285), new Variant(840), new Variant(539))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(627), new
                                Variant(135), new Variant(190), new Variant(889), new Variant(613), new Variant(585),
                                new Variant(346), new Variant(285), new Variant(840), new Variant(539));
                    }
                });
    }

    @Test
    public void test_Union_ThirteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(53), new Variant(616), new Variant(668), new Variant(29), new
                Variant(624), new Variant(603), new Variant(245), new Variant(459), new Variant(73), new Variant(858)
                , new Variant(948))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(53), new
                                Variant(616), new Variant(668), new Variant(29), new Variant(624), new Variant(603),
                                new Variant(245), new Variant(459), new Variant(73), new Variant(858), new Variant
                                        (948));
                    }
                });
    }

    @Test
    public void test_Union_FourteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(362), new Variant(390), new Variant(178), new Variant(123), new
                Variant(990), new Variant(885), new Variant(220), new Variant(462), new Variant(538), new Variant
                (488), new Variant(4), new Variant(885))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(362), new
                                Variant(390), new Variant(178), new Variant(123), new Variant(990), new Variant(885),
                                new Variant(220), new Variant(462), new Variant(538), new Variant(488), new Variant
                                        (4), new Variant(885));
                    }
                });
    }

    @Test
    public void test_Union_FifteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(602), new Variant(958), new Variant(806), new Variant(806), new
                Variant(448), new Variant(549), new Variant(790), new Variant(815), new Variant(866), new Variant(3),
                new Variant(866), new Variant(401), new Variant(908))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(602), new
                                Variant(958), new Variant(806), new Variant(806), new Variant(448), new Variant(549),
                                new Variant(790), new Variant(815), new Variant(866), new Variant(3), new Variant
                                        (866), new Variant(401), new Variant(908));
                    }
                });
    }

    @Test
    public void test_Union_SixteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(53), new Variant(886), new Variant(120), new Variant(688), new
                Variant(550), new Variant(531), new Variant(134), new Variant(574), new Variant(400), new Variant
                (574), new Variant(168), new Variant(809), new Variant(969), new Variant(89))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(53), new
                                Variant(886), new Variant(120), new Variant(688), new Variant(550), new Variant(531),
                                new Variant(134), new Variant(574), new Variant(400), new Variant(574), new Variant
                                        (168), new Variant(809), new Variant(969), new Variant(89));
                    }
                });
    }

    @Test
    public void test_Union_SeventeenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(497), new Variant(600), new Variant(429), new Variant(576), new
                Variant(738), new Variant(470), new Variant(529), new Variant(274), new Variant(995), new Variant
                (335), new Variant(928), new Variant(193), new Variant(34), new Variant(911), new Variant(542))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(497), new
                                Variant(600), new Variant(429), new Variant(576), new Variant(738), new Variant(470),
                                new Variant(529), new Variant(274), new Variant(995), new Variant(335), new Variant
                                        (928), new Variant(193), new Variant(34), new Variant(911), new Variant(542));
                    }
                });
    }

    @Test
    public void test_Union_EighteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(192), new Variant(178), new Variant(672), new Variant(321), new
                Variant(704), new Variant(208), new Variant(519), new Variant(832), new Variant(910), new Variant(23)
                , new Variant(172), new Variant(780), new Variant(709), new Variant(979), new Variant(109), new
                        Variant(323))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(192), new
                                Variant(178), new Variant(672), new Variant(321), new Variant(704), new Variant(208),
                                new Variant(519), new Variant(832), new Variant(910), new Variant(23), new Variant
                                        (172), new Variant(780), new Variant(709), new Variant(979), new Variant(109)
                                , new Variant(323));
                    }
                });
    }

    @Test
    public void test_Union_NineteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(308), new Variant(434), new Variant(822), new Variant(571), new
                Variant(724), new Variant(687), new Variant(510), new Variant(283), new Variant(289), new Variant
                (992), new Variant(321), new Variant(405), new Variant(314), new Variant(951), new Variant(262), new
                Variant(696), new Variant(438))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(308), new
                                Variant(434), new Variant(822), new Variant(571), new Variant(724), new Variant(687),
                                new Variant(510), new Variant(283), new Variant(289), new Variant(992), new Variant
                                        (321), new Variant(405), new Variant(314), new Variant(951), new Variant(262)
                                , new Variant(696), new Variant(438));
                    }
                });
    }

    @Test
    public void test_Union_TwentyArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(781), new Variant(868), new Variant(539), new Variant(820), new
                Variant(330), new Variant(718), new Variant(843), new Variant(127), new Variant(466), new Variant
                (840), new Variant(45), new Variant(500), new Variant(193), new Variant(20), new Variant(943), new
                Variant(2), new Variant(935), new Variant(454))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(781), new
                                Variant(868), new Variant(539), new Variant(820), new Variant(330), new Variant(718),
                                new Variant(843), new Variant(127), new Variant(466), new Variant(840), new Variant
                                        (45), new Variant(500), new Variant(193), new Variant(20), new Variant(943),
                                new Variant(2), new Variant(935), new Variant(454));
                    }
                });
    }

    @Test
    public void test_Union_TwentyOneArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(632), new Variant(181), new Variant(583), new Variant(752), new
                Variant(336), new Variant(983), new Variant(369), new Variant(482), new Variant(258), new Variant(36)
                , new Variant(951), new Variant(714), new Variant(359), new Variant(872), new Variant(797), new
                        Variant(109), new Variant(228), new Variant(375), new Variant(897))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(632), new
                                Variant(181), new Variant(583), new Variant(752), new Variant(336), new Variant(983),
                                new Variant(369), new Variant(482), new Variant(258), new Variant(36), new Variant
                                        (951), new Variant(714), new Variant(359), new Variant(872), new Variant(797)
                                , new Variant(109), new Variant(228), new Variant(375), new Variant(897));
                    }
                });
    }

    @Test
    public void test_Union_TwentyTwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(647), new Variant(971), new Variant(192), new Variant(546), new
                Variant(140), new Variant(127), new Variant(751), new Variant(750), new Variant(339), new Variant
                (560), new Variant(926), new Variant(707), new Variant(764), new Variant(943), new Variant(799), new
                Variant(103), new Variant(86), new Variant(540), new Variant(488), new Variant(994))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(647), new
                                Variant(971), new Variant(192), new Variant(546), new Variant(140), new Variant(127),
                                new Variant(751), new Variant(750), new Variant(339), new Variant(560), new Variant
                                        (926), new Variant(707), new Variant(764), new Variant(943), new Variant(799)
                                , new Variant(103), new Variant(86), new Variant(540), new Variant(488), new Variant
                                        (994));
                    }
                });
    }

    @Test
    public void test_Union_TwentyThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(831), new Variant(979), new Variant(452), new Variant(625), new
                Variant(769), new Variant(204), new Variant(90), new Variant(406), new Variant(709), new Variant(498)
                , new Variant(44), new Variant(978), new Variant(879), new Variant(883), new Variant(950), new
                        Variant(389), new Variant(854), new Variant(198), new Variant(809), new Variant(581), new
                        Variant(718))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(831), new
                                Variant(979), new Variant(452), new Variant(625), new Variant(769), new Variant(204),
                                new Variant(90), new Variant(406), new Variant(709), new Variant(498), new Variant
                                        (44), new Variant(978), new Variant(879), new Variant(883), new Variant(950),
                                new Variant(389), new Variant(854), new Variant(198), new Variant(809), new Variant
                                        (581), new Variant(718));
                    }
                });
    }

    @Test
    public void test_Union_TwentyFourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(460), new Variant(515), new Variant(466), new Variant(28), new
                Variant(364), new Variant(53), new Variant(322), new Variant(549), new Variant(810), new Variant(369)
                , new Variant(992), new Variant(740), new Variant(442), new Variant(733), new Variant(918), new
                        Variant(798), new Variant(158), new Variant(896), new Variant(932), new Variant(707), new
                        Variant(152), new Variant(408))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(460), new
                                Variant(515), new Variant(466), new Variant(28), new Variant(364), new Variant(53),
                                new Variant(322), new Variant(549), new Variant(810), new Variant(369), new Variant
                                        (992), new Variant(740), new Variant(442), new Variant(733), new Variant(918)
                                , new Variant(798), new Variant(158), new Variant(896), new Variant(932), new Variant
                                        (707), new Variant(152), new Variant(408));
                    }
                });
    }

    @Test
    public void test_Union_TwentyFiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(9), new Variant(723), new Variant(473), new Variant(806), new
                Variant(782), new Variant(418), new Variant(399), new Variant(119), new Variant(714), new Variant
                (314), new Variant(285), new Variant(287), new Variant(464), new Variant(835), new Variant(36), new
                Variant(484), new Variant(853), new Variant(634), new Variant(551), new Variant(685), new Variant
                (877), new Variant(675), new Variant(189))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(9), new
                                Variant(723), new Variant(473), new Variant(806), new Variant(782), new Variant(418),
                                new Variant(399), new Variant(119), new Variant(714), new Variant(314), new Variant
                                        (285), new Variant(287), new Variant(464), new Variant(835), new Variant(36),
                                new Variant(484), new Variant(853), new Variant(634), new Variant(551), new Variant
                                        (685), new Variant(877), new Variant(675), new Variant(189));
                    }
                });
    }

    @Test
    public void test_Union_TwentySixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(221), new Variant(109), new Variant(508), new Variant(352), new
                Variant(967), new Variant(139), new Variant(928), new Variant(482), new Variant(967), new Variant
                (825), new Variant(61), new Variant(567), new Variant(811), new Variant(521), new Variant(475), new
                Variant(365), new Variant(477), new Variant(434), new Variant(121), new Variant(88), new Variant(46),
                new Variant(489), new Variant(853), new Variant(90))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(221), new
                                Variant(109), new Variant(508), new Variant(352), new Variant(967), new Variant(139),
                                new Variant(928), new Variant(482), new Variant(967), new Variant(825), new Variant
                                        (61), new Variant(567), new Variant(811), new Variant(521), new Variant(475),
                                new Variant(365), new Variant(477), new Variant(434), new Variant(121), new Variant
                                        (88), new Variant(46), new Variant(489), new Variant(853), new Variant(90));
                    }
                });
    }

    @Test
    public void test_Union_TwentySevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(584), new Variant(507), new Variant(271), new Variant(703), new
                Variant(975), new Variant(766), new Variant(442), new Variant(655), new Variant(830), new Variant
                (904), new Variant(377), new Variant(293), new Variant(306), new Variant(111), new Variant(74), new
                Variant(172), new Variant(605), new Variant(103), new Variant(946), new Variant(306), new Variant
                (529), new Variant(866), new Variant(717), new Variant(140), new Variant(870))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(584), new
                                Variant(507), new Variant(271), new Variant(703), new Variant(975), new Variant(766),
                                new Variant(442), new Variant(655), new Variant(830), new Variant(904), new Variant
                                        (377), new Variant(293), new Variant(306), new Variant(111), new Variant(74),
                                new Variant(172), new Variant(605), new Variant(103), new Variant(946), new Variant
                                        (306), new Variant(529), new Variant(866), new Variant(717), new Variant(140)
                                , new Variant(870));
                    }
                });
    }

    @Test
    public void test_Union_TwentyEightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(489), new Variant(415), new Variant(56), new Variant(218), new
                Variant(193), new Variant(92), new Variant(18), new Variant(212), new Variant(281), new Variant(145),
                new Variant(366), new Variant(285), new Variant(520), new Variant(957), new Variant(276), new Variant
                        (676), new Variant(691), new Variant(79), new Variant(810), new Variant(21), new Variant(708)
                , new Variant(629), new Variant(363), new Variant(701), new Variant(710), new Variant(374))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(489), new
                                Variant(415), new Variant(56), new Variant(218), new Variant(193), new Variant(92),
                                new Variant(18), new Variant(212), new Variant(281), new Variant(145), new Variant
                                        (366), new Variant(285), new Variant(520), new Variant(957), new Variant(276)
                                , new Variant(676), new Variant(691), new Variant(79), new Variant(810), new Variant
                                        (21), new Variant(708), new Variant(629), new Variant(363), new Variant(701),
                                new Variant(710), new Variant(374));
                    }
                });
    }

    @Test
    public void test_Union_TwentyNineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(637), new Variant(148), new Variant(900), new Variant(893), new
                Variant(704), new Variant(279), new Variant(722), new Variant(474), new Variant(907), new Variant
                (705), new Variant(20), new Variant(103), new Variant(240), new Variant(293), new Variant(274), new
                Variant(380), new Variant(512), new Variant(403), new Variant(365), new Variant(583), new Variant
                (193), new Variant(964), new Variant(699), new Variant(483), new Variant(555), new Variant(300), new
                Variant(662))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(637), new
                                Variant(148), new Variant(900), new Variant(893), new Variant(704), new Variant(279),
                                new Variant(722), new Variant(474), new Variant(907), new Variant(705), new Variant
                                        (20), new Variant(103), new Variant(240), new Variant(293), new Variant(274),
                                new Variant(380), new Variant(512), new Variant(403), new Variant(365), new Variant
                                        (583), new Variant(193), new Variant(964), new Variant(699), new Variant(483)
                                , new Variant(555), new Variant(300), new Variant(662));
                    }
                });
    }

    @Test
    public void test_Union_ThirtyArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Range.class)), new Variant
                (getMock(Range.class)), new Variant(428), new Variant(994), new Variant(156), new Variant(115), new
                Variant(53), new Variant(238), new Variant(128), new Variant(229), new Variant(566), new Variant(126)
                , new Variant(171), new Variant(514), new Variant(805), new Variant(307), new Variant(261), new
                        Variant(742), new Variant(599), new Variant(513), new Variant(23), new Variant(3), new
                        Variant(851), new Variant(328), new Variant(435), new Variant(770), new Variant(20), new
                        Variant(361), new Variant(906), new Variant(243))
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.Union(getMock(Range.class), getMock(Range.class), new Variant(428), new
                                Variant(994), new Variant(156), new Variant(115), new Variant(53), new Variant(238),
                                new Variant(128), new Variant(229), new Variant(566), new Variant(126), new Variant
                                        (171), new Variant(514), new Variant(805), new Variant(307), new Variant(261)
                                , new Variant(742), new Variant(599), new Variant(513), new Variant(23), new Variant
                                        (3), new Variant(851), new Variant(328), new Variant(435), new Variant(770),
                                new Variant(20), new Variant(361), new Variant(906), new Variant(243));
                    }
                });
    }

    @Test
    public void test_getAxWindows_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1ae).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Windows>() {
                    @Override
                    public Windows invoke() throws ActiveXException {
                        return component.getAxWindows();
                    }
                });
    }

    @Test
    public void test_getAxWorkbooks_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x23c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Workbooks>() {
                    @Override
                    public Workbooks invoke() throws ActiveXException {
                        return component.getAxWorkbooks();
                    }
                });
    }

    @Test
    public void test_getAxWorksheetFunction_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5a0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<WorksheetFunction>() {
                    @Override
                    public WorksheetFunction invoke() throws ActiveXException {
                        return component.getAxWorksheetFunction();
                    }
                });
    }

    @Test
    public void test_getAxWorksheets_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1ee).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Sheets>() {
                    @Override
                    public Sheets invoke() throws ActiveXException {
                        return component.getAxWorksheets();
                    }
                });
    }

    @Test
    public void test_getAxExcel4IntlMacroSheets_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x245).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Sheets>() {
                    @Override
                    public Sheets invoke() throws ActiveXException {
                        return component.getAxExcel4IntlMacroSheets();
                    }
                });
    }

    @Test
    public void test_getAxExcel4MacroSheets_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x243).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Sheets>() {
                    @Override
                    public Sheets invoke() throws ActiveXException {
                        return component.getAxExcel4MacroSheets();
                    }
                });
    }

    @Test
    public void test_ActivateMicrosoftApp_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x447).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ActivateMicrosoftApp(42);
                    }
                });
    }

    @Test
    public void test_AddChartAutoFormat_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xd8).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(345), new Variant("umPInYqMeD"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AddChartAutoFormat(new Variant(345), "umPInYqMeD");
                    }
                });
    }

    @Test
    public void test_AddChartAutoFormat_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0xd8).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(3), new Variant("PeNtivchjv"), new
                Variant(411))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AddChartAutoFormat(new Variant(3), "PeNtivchjv", new Variant(411));
                    }
                });
    }

    @Test
    public void test_AddCustomList_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x30c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(249))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AddCustomList(new Variant(249));
                    }
                });
    }

    @Test
    public void test_AddCustomList_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x30c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(171), new Variant(846))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AddCustomList(new Variant(171), new Variant(846));
                    }
                });
    }

    @Test
    public void test_getAxAlertBeforeOverwriting_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3a2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxAlertBeforeOverwriting();
                    }
                });
    }

    @Test
    public void test_setAxAlertBeforeOverwriting_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3a2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxAlertBeforeOverwriting(false);
                    }
                });
    }

    @Test
    public void test_getAxAltStartupPath_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x139).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxAltStartupPath();
                    }
                });
    }

    @Test
    public void test_setAxAltStartupPath_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x139).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("ZGEFKwrGmd"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxAltStartupPath("ZGEFKwrGmd");
                    }
                });
    }

    @Test
    public void test_getAxAskToUpdateLinks_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3e0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxAskToUpdateLinks();
                    }
                });
    }

    @Test
    public void test_setAxAskToUpdateLinks_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3e0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxAskToUpdateLinks(false);
                    }
                });
    }

    @Test
    public void test_getAxEnableAnimations_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x49c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxEnableAnimations();
                    }
                });
    }

    @Test
    public void test_setAxEnableAnimations_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x49c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxEnableAnimations(false);
                    }
                });
    }

    @Test
    public void test_getAxAutoCorrect_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x479).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<AutoCorrect>() {
                    @Override
                    public AutoCorrect invoke() throws ActiveXException {
                        return component.getAxAutoCorrect();
                    }
                });
    }

    @Test
    public void test_getAxBuild_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x13a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxBuild();
                    }
                });
    }

    @Test
    public void test_getAxCalculateBeforeSave_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x13b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxCalculateBeforeSave();
                    }
                });
    }

    @Test
    public void test_setAxCalculateBeforeSave_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x13b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCalculateBeforeSave(false);
                    }
                });
    }

    @Test
    public void test_getAxCalculation_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x13c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxCalculation();
                    }
                });
    }

    @Test
    public void test_setAxCalculation_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x13c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCalculation(42);
                    }
                });
    }

    @Test
    public void test_getAxCaller_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x13d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxCaller();
                    }
                });
    }

    @Test
    public void test_getAxCaller_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x13d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(781))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxCaller(new Variant(781));
                    }
                });
    }

    @Test
    public void test_getAxCanPlaySounds_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x13e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxCanPlaySounds();
                    }
                });
    }

    @Test
    public void test_getAxCanRecordSounds_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x13f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxCanRecordSounds();
                    }
                });
    }

    @Test
    public void test_getAxCaption_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x8b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxCaption();
                    }
                });
    }

    @Test
    public void test_setAxCaption_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x8b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("jOednmMlFJ"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCaption("jOednmMlFJ");
                    }
                });
    }

    @Test
    public void test_getAxCellDragAndDrop_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x140).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxCellDragAndDrop();
                    }
                });
    }

    @Test
    public void test_setAxCellDragAndDrop_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x140).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCellDragAndDrop(false);
                    }
                });
    }

    @Test
    public void test_CentimetersToPoints_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x43e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42.32d))
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.CentimetersToPoints(42.32d);
                    }
                });
    }

    @Test
    public void test_CheckSpelling_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("WPVfrmXxuH"))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.CheckSpelling("WPVfrmXxuH");
                    }
                });
    }

    @Test
    public void test_CheckSpelling_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("ACFfEqFecx"), new Variant(873))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.CheckSpelling("ACFfEqFecx", new Variant(873));
                    }
                });
    }

    @Test
    public void test_CheckSpelling_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("yqjgnfCusQ"), new Variant(354),
                new Variant(551))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.CheckSpelling("yqjgnfCusQ", new Variant(354), new Variant(551));
                    }
                });
    }

    @Test
    public void test_getAxClipboardFormats_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x141).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxClipboardFormats();
                    }
                });
    }

    @Test
    public void test_getAxClipboardFormats_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x141).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(42))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxClipboardFormats(new Variant(42));
                    }
                });
    }

    @Test
    public void test_getAxDisplayClipboardWindow_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x142).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxDisplayClipboardWindow();
                    }
                });
    }

    @Test
    public void test_setAxDisplayClipboardWindow_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x142).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDisplayClipboardWindow(false);
                    }
                });
    }

    @Test
    public void test_getAxColorButtons_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x16d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxColorButtons();
                    }
                });
    }

    @Test
    public void test_setAxColorButtons_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x16d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxColorButtons(false);
                    }
                });
    }

    @Test
    public void test_getAxCommandUnderlines_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x143).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxCommandUnderlines();
                    }
                });
    }

    @Test
    public void test_setAxCommandUnderlines_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x143).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCommandUnderlines(42);
                    }
                });
    }

    @Test
    public void test_getAxConstrainNumeric_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x144).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxConstrainNumeric();
                    }
                });
    }

    @Test
    public void test_setAxConstrainNumeric_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x144).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxConstrainNumeric(false);
                    }
                });
    }

    @Test
    public void test_ConvertFormula_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x145).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(56), new Variant(42))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.ConvertFormula(new Variant(56), 42);
                    }
                });
    }

    @Test
    public void test_ConvertFormula_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x145).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(820), new Variant(42), new Variant
                (737))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.ConvertFormula(new Variant(820), 42, new Variant(737));
                    }
                });
    }

    @Test
    public void test_ConvertFormula_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x145).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(480), new Variant(42), new Variant
                (812), new Variant(308))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.ConvertFormula(new Variant(480), 42, new Variant(812), new Variant(308));
                    }
                });
    }

    @Test
    public void test_ConvertFormula_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x145).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(77), new Variant(42), new Variant
                (988), new Variant(259), new Variant(434))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.ConvertFormula(new Variant(77), 42, new Variant(988), new Variant(259), new
                                Variant(434));
                    }
                });
    }

    @Test
    public void test_getAxCopyObjectsWithCells_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3df).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxCopyObjectsWithCells();
                    }
                });
    }

    @Test
    public void test_setAxCopyObjectsWithCells_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3df).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCopyObjectsWithCells(false);
                    }
                });
    }

    @Test
    public void test_getAxCursor_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x489).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxCursor();
                    }
                });
    }

    @Test
    public void test_setAxCursor_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x489).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCursor(42);
                    }
                });
    }

    @Test
    public void test_getAxCustomListCount_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x313).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxCustomListCount();
                    }
                });
    }

    @Test
    public void test_getAxCutCopyMode_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x14a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxCutCopyMode();
                    }
                });
    }

    @Test
    public void test_setAxCutCopyMode_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x14a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCutCopyMode(42);
                    }
                });
    }

    @Test
    public void test_getAxDataEntryMode_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x14b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxDataEntryMode();
                    }
                });
    }

    @Test
    public void test_setAxDataEntryMode_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x14b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDataEntryMode(42);
                    }
                });
    }

    @Test
    public void test_Dummy1_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6e7).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Dummy1();
                    }
                });
    }

    @Test
    public void test_Dummy2_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6e8).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Dummy2();
                    }
                });
    }

    @Test
    public void test_Dummy3_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6e9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Dummy3();
                    }
                });
    }

    @Test
    public void test_Dummy4_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6ea).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Dummy4();
                    }
                });
    }

    @Test
    public void test_Dummy5_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6eb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Dummy5();
                    }
                });
    }

    @Test
    public void test_Dummy6_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6ec).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Dummy6();
                    }
                });
    }

    @Test
    public void test_Dummy7_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6ed).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Dummy7();
                    }
                });
    }

    @Test
    public void test_Dummy8_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6ee).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Dummy8();
                    }
                });
    }

    @Test
    public void test_Dummy9_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6ef).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Dummy9();
                    }
                });
    }

    @Test
    public void test_Dummy10_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6f0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Dummy10();
                    }
                });
    }

    @Test
    public void test_Dummy11_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6f1).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Dummy11();
                    }
                });
    }

    @Test
    public void test_getAx_Default_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAx_Default();
                    }
                });
    }

    @Test
    public void test_getAxDefaultFilePath_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x40e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxDefaultFilePath();
                    }
                });
    }

    @Test
    public void test_setAxDefaultFilePath_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x40e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("krCeriKJnO"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDefaultFilePath("krCeriKJnO");
                    }
                });
    }

    @Test
    public void test_DeleteChartAutoFormat_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xd9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("PeJrKLRdUu"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.DeleteChartAutoFormat("PeJrKLRdUu");
                    }
                });
    }

    @Test
    public void test_DeleteCustomList_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x30f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.DeleteCustomList(42);
                    }
                });
    }

    @Test
    public void test_getAxDialogs_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2f9).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Dialogs>() {
                    @Override
                    public Dialogs invoke() throws ActiveXException {
                        return component.getAxDialogs();
                    }
                });
    }

    @Test
    public void test_getAxDisplayAlerts_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x157).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxDisplayAlerts();
                    }
                });
    }

    @Test
    public void test_setAxDisplayAlerts_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x157).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDisplayAlerts(false);
                    }
                });
    }

    @Test
    public void test_getAxDisplayFormulaBar_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x158).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxDisplayFormulaBar();
                    }
                });
    }

    @Test
    public void test_setAxDisplayFormulaBar_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x158).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDisplayFormulaBar(false);
                    }
                });
    }

    @Test
    public void test_getAxDisplayFullScreen_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x425).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxDisplayFullScreen();
                    }
                });
    }

    @Test
    public void test_setAxDisplayFullScreen_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x425).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDisplayFullScreen(false);
                    }
                });
    }

    @Test
    public void test_getAxDisplayNoteIndicator_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x159).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxDisplayNoteIndicator();
                    }
                });
    }

    @Test
    public void test_setAxDisplayNoteIndicator_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x159).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDisplayNoteIndicator(false);
                    }
                });
    }

    @Test
    public void test_getAxDisplayCommentIndicator_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x4ac).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxDisplayCommentIndicator();
                    }
                });
    }

    @Test
    public void test_setAxDisplayCommentIndicator_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x4ac).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDisplayCommentIndicator(42);
                    }
                });
    }

    @Test
    public void test_getAxDisplayExcel4Menus_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x39f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxDisplayExcel4Menus();
                    }
                });
    }

    @Test
    public void test_setAxDisplayExcel4Menus_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x39f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDisplayExcel4Menus(false);
                    }
                });
    }

    @Test
    public void test_getAxDisplayRecentFiles_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x39e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxDisplayRecentFiles();
                    }
                });
    }

    @Test
    public void test_setAxDisplayRecentFiles_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x39e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDisplayRecentFiles(false);
                    }
                });
    }

    @Test
    public void test_getAxDisplayScrollBars_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x15a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxDisplayScrollBars();
                    }
                });
    }

    @Test
    public void test_setAxDisplayScrollBars_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x15a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDisplayScrollBars(false);
                    }
                });
    }

    @Test
    public void test_getAxDisplayStatusBar_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x15b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxDisplayStatusBar();
                    }
                });
    }

    @Test
    public void test_setAxDisplayStatusBar_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x15b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDisplayStatusBar(false);
                    }
                });
    }

    @Test
    public void test_DoubleClick_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x15d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.DoubleClick();
                    }
                });
    }

    @Test
    public void test_getAxEditDirectlyInCell_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3a1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxEditDirectlyInCell();
                    }
                });
    }

    @Test
    public void test_setAxEditDirectlyInCell_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3a1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxEditDirectlyInCell(false);
                    }
                });
    }

    @Test
    public void test_getAxEnableAutoComplete_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x49b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxEnableAutoComplete();
                    }
                });
    }

    @Test
    public void test_setAxEnableAutoComplete_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x49b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxEnableAutoComplete(false);
                    }
                });
    }

    @Test
    public void test_getAxEnableCancelKey_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x448).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxEnableCancelKey();
                    }
                });
    }

    @Test
    public void test_setAxEnableCancelKey_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x448).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxEnableCancelKey(42);
                    }
                });
    }

    @Test
    public void test_getAxEnableSound_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x4ad).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxEnableSound();
                    }
                });
    }

    @Test
    public void test_setAxEnableSound_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x4ad).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxEnableSound(false);
                    }
                });
    }

    @Test
    public void test_getAxEnableTipWizard_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x428).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxEnableTipWizard();
                    }
                });
    }

    @Test
    public void test_setAxEnableTipWizard_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x428).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxEnableTipWizard(false);
                    }
                });
    }

    @Test
    public void test_getAxFileConverters_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3a3).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxFileConverters();
                    }
                });
    }

    @Test
    public void test_getAxFileConverters_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3a3).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(224))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxFileConverters(new Variant(224));
                    }
                });
    }

    @Test
    public void test_getAxFileConverters_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3a3).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(77), new Variant(688))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxFileConverters(new Variant(77), new Variant(688));
                    }
                });
    }

    @Test
    public void test_getAxFileSearch_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x4b0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<FileSearch>() {
                    @Override
                    public FileSearch invoke() throws ActiveXException {
                        return component.getAxFileSearch();
                    }
                });
    }

    @Test
    public void test_getAxFileFind_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x4b1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<IFind>() {
                    @Override
                    public IFind invoke() throws ActiveXException {
                        return component.getAxFileFind();
                    }
                });
    }

    @Test
    public void test_FindFile_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x42c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.FindFile();
                    }
                });
    }

    @Test
    public void test_getAxFixedDecimal_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x15f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxFixedDecimal();
                    }
                });
    }

    @Test
    public void test_setAxFixedDecimal_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x15f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxFixedDecimal(false);
                    }
                });
    }

    @Test
    public void test_getAxFixedDecimalPlaces_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x160).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxFixedDecimalPlaces();
                    }
                });
    }

    @Test
    public void test_setAxFixedDecimalPlaces_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x160).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxFixedDecimalPlaces(42);
                    }
                });
    }

    @Test
    public void test_GetCustomListContents_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x312).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.GetCustomListContents(42);
                    }
                });
    }

    @Test
    public void test_GetCustomListNum_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x311).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(172))
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.GetCustomListNum(new Variant(172));
                    }
                });
    }

    @Test
    public void test_GetOpenFilename_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x433).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.GetOpenFilename();
                    }
                });
    }

    @Test
    public void test_GetOpenFilename_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x433).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(243))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.GetOpenFilename(new Variant(243));
                    }
                });
    }

    @Test
    public void test_GetOpenFilename_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x433).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(602), new Variant(540))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.GetOpenFilename(new Variant(602), new Variant(540));
                    }
                });
    }

    @Test
    public void test_GetOpenFilename_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x433).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(737), new Variant(840), new
                Variant(442))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.GetOpenFilename(new Variant(737), new Variant(840), new Variant(442));
                    }
                });
    }

    @Test
    public void test_GetOpenFilename_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x433).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(352), new Variant(270), new
                Variant(296), new Variant(383))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.GetOpenFilename(new Variant(352), new Variant(270), new Variant(296), new
                                Variant(383));
                    }
                });
    }

    @Test
    public void test_GetOpenFilename_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x433).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(249), new Variant(943), new
                Variant(617), new Variant(941), new Variant(188))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.GetOpenFilename(new Variant(249), new Variant(943), new Variant(617), new
                                Variant(941), new Variant(188));
                    }
                });
    }

    @Test
    public void test_GetSaveAsFilename_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x434).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.GetSaveAsFilename();
                    }
                });
    }

    @Test
    public void test_GetSaveAsFilename_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x434).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(611))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.GetSaveAsFilename(new Variant(611));
                    }
                });
    }

    @Test
    public void test_GetSaveAsFilename_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x434).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(733), new Variant(244))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.GetSaveAsFilename(new Variant(733), new Variant(244));
                    }
                });
    }

    @Test
    public void test_GetSaveAsFilename_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x434).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(417), new Variant(236), new
                Variant(582))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.GetSaveAsFilename(new Variant(417), new Variant(236), new Variant(582));
                    }
                });
    }

    @Test
    public void test_GetSaveAsFilename_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x434).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(751), new Variant(341), new
                Variant(538), new Variant(901))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.GetSaveAsFilename(new Variant(751), new Variant(341), new Variant(538), new
                                Variant(901));
                    }
                });
    }

    @Test
    public void test_GetSaveAsFilename_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x434).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(705), new Variant(287), new
                Variant(300), new Variant(953), new Variant(500))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.GetSaveAsFilename(new Variant(705), new Variant(287), new Variant(300), new
                                Variant(953), new Variant(500));
                    }
                });
    }

    @Test
    public void test_Goto_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1db).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Goto();
                    }
                });
    }

    @Test
    public void test_Goto_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x1db).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(652))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Goto(new Variant(652));
                    }
                });
    }

    @Test
    public void test_Goto_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1db).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(818), new Variant(877))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Goto(new Variant(818), new Variant(877));
                    }
                });
    }

    @Test
    public void test_getAxHeight_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x7b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxHeight();
                    }
                });
    }

    @Test
    public void test_setAxHeight_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x7b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32d))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHeight(42.32d);
                    }
                });
    }

    @Test
    public void test_Help_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x162).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Help();
                    }
                });
    }

    @Test
    public void test_Help_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x162).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(421))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Help(new Variant(421));
                    }
                });
    }

    @Test
    public void test_Help_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x162).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(637), new Variant(137))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Help(new Variant(637), new Variant(137));
                    }
                });
    }

    @Test
    public void test_getAxIgnoreRemoteRequests_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x164).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxIgnoreRemoteRequests();
                    }
                });
    }

    @Test
    public void test_setAxIgnoreRemoteRequests_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x164).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxIgnoreRemoteRequests(false);
                    }
                });
    }

    @Test
    public void test_InchesToPoints_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x43f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42.32d))
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.InchesToPoints(42.32d);
                    }
                });
    }

    @Test
    public void test_InputBox_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x165).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("CHKyLNmbDs"))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.InputBox("CHKyLNmbDs");
                    }
                });
    }

    @Test
    public void test_InputBox_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x165).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("PfoSVdMWEQ"), new Variant(915))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.InputBox("PfoSVdMWEQ", new Variant(915));
                    }
                });
    }

    @Test
    public void test_InputBox_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x165).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("ayYdoVKWlJ"), new Variant(695),
                new Variant(478))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.InputBox("ayYdoVKWlJ", new Variant(695), new Variant(478));
                    }
                });
    }

    @Test
    public void test_InputBox_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x165).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("UbRWRWfHAh"), new Variant(316),
                new Variant(164), new Variant(874))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.InputBox("UbRWRWfHAh", new Variant(316), new Variant(164), new Variant(874));
                    }
                });
    }

    @Test
    public void test_InputBox_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x165).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("nqBbUzDRjO"), new Variant(890),
                new Variant(563), new Variant(593), new Variant(984))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.InputBox("nqBbUzDRjO", new Variant(890), new Variant(563), new Variant(593),
                                new Variant(984));
                    }
                });
    }

    @Test
    public void test_InputBox_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x165).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("oibVfMPyQv"), new Variant(890),
                new Variant(595), new Variant(883), new Variant(908), new Variant(684))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.InputBox("oibVfMPyQv", new Variant(890), new Variant(595), new Variant(883),
                                new Variant(908), new Variant(684));
                    }
                });
    }

    @Test
    public void test_InputBox_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x165).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("SjMPZHrHSi"), new Variant(50),
                new Variant(127), new Variant(487), new Variant(272), new Variant(772), new Variant(798))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.InputBox("SjMPZHrHSi", new Variant(50), new Variant(127), new Variant(487),
                                new Variant(272), new Variant(772), new Variant(798));
                    }
                });
    }

    @Test
    public void test_InputBox_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x165).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("FcCNSNGpLJ"), new Variant(80),
                new Variant(550), new Variant(359), new Variant(865), new Variant(831), new Variant(755), new Variant
                        (704))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.InputBox("FcCNSNGpLJ", new Variant(80), new Variant(550), new Variant(359),
                                new Variant(865), new Variant(831), new Variant(755), new Variant(704));
                    }
                });
    }

    @Test
    public void test_getAxInteractive_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x169).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxInteractive();
                    }
                });
    }

    @Test
    public void test_setAxInteractive_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x169).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxInteractive(false);
                    }
                });
    }

    @Test
    public void test_getAxInternational_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x16a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxInternational();
                    }
                });
    }

    @Test
    public void test_getAxInternational_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x16a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(377))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxInternational(new Variant(377));
                    }
                });
    }

    @Test
    public void test_getAxIteration_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x16b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxIteration();
                    }
                });
    }

    @Test
    public void test_setAxIteration_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x16b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxIteration(false);
                    }
                });
    }

    @Test
    public void test_getAxLargeButtons_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x16c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxLargeButtons();
                    }
                });
    }

    @Test
    public void test_setAxLargeButtons_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x16c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxLargeButtons(false);
                    }
                });
    }

    @Test
    public void test_getAxLeft_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x7f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxLeft();
                    }
                });
    }

    @Test
    public void test_setAxLeft_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x7f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32d))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxLeft(42.32d);
                    }
                });
    }

    @Test
    public void test_getAxLibraryPath_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x16e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxLibraryPath();
                    }
                });
    }

    @Test
    public void test_MacroOptions_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x46f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.MacroOptions();
                    }
                });
    }

    @Test
    public void test_MacroOptions_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x46f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(159))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.MacroOptions(new Variant(159));
                    }
                });
    }

    @Test
    public void test_MacroOptions_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x46f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(827), new Variant(977))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.MacroOptions(new Variant(827), new Variant(977));
                    }
                });
    }

    @Test
    public void test_MacroOptions_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x46f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(500), new Variant(526), new
                Variant(824))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.MacroOptions(new Variant(500), new Variant(526), new Variant(824));
                    }
                });
    }

    @Test
    public void test_MacroOptions_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x46f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(927), new Variant(644), new
                Variant(786), new Variant(672))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.MacroOptions(new Variant(927), new Variant(644), new Variant(786), new Variant(672));
                    }
                });
    }

    @Test
    public void test_MacroOptions_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x46f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(299), new Variant(161), new
                Variant(385), new Variant(605), new Variant(933))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.MacroOptions(new Variant(299), new Variant(161), new Variant(385), new Variant(605)
                                , new Variant(933));
                    }
                });
    }

    @Test
    public void test_MacroOptions_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0x46f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(591), new Variant(717), new
                Variant(981), new Variant(584), new Variant(714), new Variant(594))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.MacroOptions(new Variant(591), new Variant(717), new Variant(981), new Variant(584)
                                , new Variant(714), new Variant(594));
                    }
                });
    }

    @Test
    public void test_MacroOptions_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x46f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(778), new Variant(599), new
                Variant(718), new Variant(757), new Variant(156), new Variant(730), new Variant(883))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.MacroOptions(new Variant(778), new Variant(599), new Variant(718), new Variant(757)
                                , new Variant(156), new Variant(730), new Variant(883));
                    }
                });
    }

    @Test
    public void test_MacroOptions_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x46f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(620), new Variant(698), new
                Variant(20), new Variant(93), new Variant(164), new Variant(912), new Variant(164), new Variant(793))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.MacroOptions(new Variant(620), new Variant(698), new Variant(20), new Variant(93),
                                new Variant(164), new Variant(912), new Variant(164), new Variant(793));
                    }
                });
    }

    @Test
    public void test_MacroOptions_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0x46f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(282), new Variant(226), new
                Variant(749), new Variant(524), new Variant(538), new Variant(767), new Variant(524), new Variant
                (510), new Variant(925))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.MacroOptions(new Variant(282), new Variant(226), new Variant(749), new Variant(524)
                                , new Variant(538), new Variant(767), new Variant(524), new Variant(510), new Variant
                                        (925));
                    }
                });
    }

    @Test
    public void test_MacroOptions_TenArgs_ShouldRedirectToProxy() throws Exception {
        on(0x46f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(761), new Variant(823), new
                Variant(835), new Variant(275), new Variant(408), new Variant(277), new Variant(914), new Variant
                (901), new Variant(174), new Variant(421))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.MacroOptions(new Variant(761), new Variant(823), new Variant(835), new Variant(275)
                                , new Variant(408), new Variant(277), new Variant(914), new Variant(901), new Variant
                                        (174), new Variant(421));
                    }
                });
    }

    @Test
    public void test_MailLogoff_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3b1).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.MailLogoff();
                    }
                });
    }

    @Test
    public void test_MailLogon_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3af).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.MailLogon();
                    }
                });
    }

    @Test
    public void test_MailLogon_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3af).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(407))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.MailLogon(new Variant(407));
                    }
                });
    }

    @Test
    public void test_MailLogon_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3af).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(717), new Variant(477))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.MailLogon(new Variant(717), new Variant(477));
                    }
                });
    }

    @Test
    public void test_MailLogon_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3af).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(774), new Variant(531), new
                Variant(228))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.MailLogon(new Variant(774), new Variant(531), new Variant(228));
                    }
                });
    }

    @Test
    public void test_getAxMailSession_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3ae).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxMailSession();
                    }
                });
    }

    @Test
    public void test_getAxMailSystem_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3cb).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxMailSystem();
                    }
                });
    }

    @Test
    public void test_getAxMathCoprocessorAvailable_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x16f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxMathCoprocessorAvailable();
                    }
                });
    }

    @Test
    public void test_getAxMaxChange_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x170).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxMaxChange();
                    }
                });
    }

    @Test
    public void test_setAxMaxChange_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x170).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32d))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMaxChange(42.32d);
                    }
                });
    }

    @Test
    public void test_getAxMaxIterations_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x171).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxMaxIterations();
                    }
                });
    }

    @Test
    public void test_setAxMaxIterations_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x171).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMaxIterations(42);
                    }
                });
    }

    @Test
    public void test_getAxMemoryFree_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x172).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxMemoryFree();
                    }
                });
    }

    @Test
    public void test_getAxMemoryTotal_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x173).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxMemoryTotal();
                    }
                });
    }

    @Test
    public void test_getAxMemoryUsed_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x174).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxMemoryUsed();
                    }
                });
    }

    @Test
    public void test_getAxMouseAvailable_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x175).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxMouseAvailable();
                    }
                });
    }

    @Test
    public void test_getAxMoveAfterReturn_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x176).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxMoveAfterReturn();
                    }
                });
    }

    @Test
    public void test_setAxMoveAfterReturn_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x176).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMoveAfterReturn(false);
                    }
                });
    }

    @Test
    public void test_getAxMoveAfterReturnDirection_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x478).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxMoveAfterReturnDirection();
                    }
                });
    }

    @Test
    public void test_setAxMoveAfterReturnDirection_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x478).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMoveAfterReturnDirection(42);
                    }
                });
    }

    @Test
    public void test_getAxRecentFiles_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x4b2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<RecentFiles>() {
                    @Override
                    public RecentFiles invoke() throws ActiveXException {
                        return component.getAxRecentFiles();
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
    public void test_NextLetter_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3cc).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.NextLetter();
                    }
                });
    }

    @Test
    public void test_getAxNetworkTemplatesPath_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x184).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxNetworkTemplatesPath();
                    }
                });
    }

    @Test
    public void test_getAxODBCErrors_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x4b3).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<ODBCErrors>() {
                    @Override
                    public ODBCErrors invoke() throws ActiveXException {
                        return component.getAxODBCErrors();
                    }
                });
    }

    @Test
    public void test_getAxODBCTimeout_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x4b4).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxODBCTimeout();
                    }
                });
    }

    @Test
    public void test_setAxODBCTimeout_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x4b4).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxODBCTimeout(42);
                    }
                });
    }

    @Test
    public void test_getAxOnCalculate_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x271).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxOnCalculate();
                    }
                });
    }

    @Test
    public void test_setAxOnCalculate_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x271).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("tEShhVifow"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnCalculate("tEShhVifow");
                    }
                });
    }

    @Test
    public void test_getAxOnData_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x275).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxOnData();
                    }
                });
    }

    @Test
    public void test_setAxOnData_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x275).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("YzyPGrjqFq"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnData("YzyPGrjqFq");
                    }
                });
    }

    @Test
    public void test_getAxOnDoubleClick_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x274).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxOnDoubleClick();
                    }
                });
    }

    @Test
    public void test_setAxOnDoubleClick_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x274).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("BmAMEgTBVH"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnDoubleClick("BmAMEgTBVH");
                    }
                });
    }

    @Test
    public void test_getAxOnEntry_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x273).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxOnEntry();
                    }
                });
    }

    @Test
    public void test_setAxOnEntry_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x273).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("GnXoRwkFjo"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnEntry("GnXoRwkFjo");
                    }
                });
    }

    @Test
    public void test_OnKey_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x272).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("yQFhkEDzwD"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.OnKey("yQFhkEDzwD");
                    }
                });
    }

    @Test
    public void test_OnKey_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x272).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("vqKRiIrFgT"), new Variant(893))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.OnKey("vqKRiIrFgT", new Variant(893));
                    }
                });
    }

    @Test
    public void test_OnRepeat_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x301).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("NfIsdlvWMp"), new Variant
                ("fuSeNeeUAi"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.OnRepeat("NfIsdlvWMp", "fuSeNeeUAi");
                    }
                });
    }

    @Test
    public void test_getAxOnSheetActivate_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x407).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxOnSheetActivate();
                    }
                });
    }

    @Test
    public void test_setAxOnSheetActivate_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x407).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("UwhEuCNGJH"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnSheetActivate("UwhEuCNGJH");
                    }
                });
    }

    @Test
    public void test_getAxOnSheetDeactivate_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x439).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxOnSheetDeactivate();
                    }
                });
    }

    @Test
    public void test_setAxOnSheetDeactivate_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x439).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("dbdNvXkhBm"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnSheetDeactivate("dbdNvXkhBm");
                    }
                });
    }

    @Test
    public void test_OnTime_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x270).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(152), new Variant("kFYFrOTpGg"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.OnTime(new Variant(152), "kFYFrOTpGg");
                    }
                });
    }

    @Test
    public void test_OnTime_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x270).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(515), new Variant("jkrSGYTeVl"),
                new Variant(520))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.OnTime(new Variant(515), "jkrSGYTeVl", new Variant(520));
                    }
                });
    }

    @Test
    public void test_OnTime_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x270).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(922), new Variant("vWHDMEQPrW"),
                new Variant(158), new Variant(38))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.OnTime(new Variant(922), "vWHDMEQPrW", new Variant(158), new Variant(38));
                    }
                });
    }

    @Test
    public void test_OnUndo_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x302).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("hPHKhMIQWx"), new Variant
                ("obKlIfNZcK"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.OnUndo("hPHKhMIQWx", "obKlIfNZcK");
                    }
                });
    }

    @Test
    public void test_getAxOnWindow_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x26f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxOnWindow();
                    }
                });
    }

    @Test
    public void test_setAxOnWindow_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x26f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("hgdqABbBKO"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOnWindow("hgdqABbBKO");
                    }
                });
    }

    @Test
    public void test_getAxOperatingSystem_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x177).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxOperatingSystem();
                    }
                });
    }

    @Test
    public void test_getAxOrganizationName_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x178).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxOrganizationName();
                    }
                });
    }

    @Test
    public void test_getAxPath_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x123).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxPath();
                    }
                });
    }

    @Test
    public void test_getAxPathSeparator_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x179).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxPathSeparator();
                    }
                });
    }

    @Test
    public void test_getAxPreviousSelections_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x17a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxPreviousSelections();
                    }
                });
    }

    @Test
    public void test_getAxPreviousSelections_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x17a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(537))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxPreviousSelections(new Variant(537));
                    }
                });
    }

    @Test
    public void test_getAxPivotTableSelection_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x4b5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxPivotTableSelection();
                    }
                });
    }

    @Test
    public void test_setAxPivotTableSelection_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x4b5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPivotTableSelection(false);
                    }
                });
    }

    @Test
    public void test_getAxPromptForSummaryInfo_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x426).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxPromptForSummaryInfo();
                    }
                });
    }

    @Test
    public void test_setAxPromptForSummaryInfo_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x426).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPromptForSummaryInfo(false);
                    }
                });
    }

    @Test
    public void test_Quit_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x12e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Quit();
                    }
                });
    }

    @Test
    public void test_RecordMacro_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x305).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.RecordMacro();
                    }
                });
    }

    @Test
    public void test_RecordMacro_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x305).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(834))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.RecordMacro(new Variant(834));
                    }
                });
    }

    @Test
    public void test_RecordMacro_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x305).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(873), new Variant(391))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.RecordMacro(new Variant(873), new Variant(391));
                    }
                });
    }

    @Test
    public void test_getAxRecordRelative_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x17b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxRecordRelative();
                    }
                });
    }

    @Test
    public void test_getAxReferenceStyle_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x17c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxReferenceStyle();
                    }
                });
    }

    @Test
    public void test_setAxReferenceStyle_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x17c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxReferenceStyle(42);
                    }
                });
    }

    @Test
    public void test_getAxRegisteredFunctions_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x307).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxRegisteredFunctions();
                    }
                });
    }

    @Test
    public void test_getAxRegisteredFunctions_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x307).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(494))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxRegisteredFunctions(new Variant(494));
                    }
                });
    }

    @Test
    public void test_getAxRegisteredFunctions_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x307).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(227), new Variant(266))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxRegisteredFunctions(new Variant(227), new Variant(266));
                    }
                });
    }

    @Test
    public void test_RegisterXLL_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x1e).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("GLgPFETIOs"))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.RegisterXLL("GLgPFETIOs");
                    }
                });
    }

    @Test
    public void test_Repeat_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x12d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Repeat();
                    }
                });
    }

    @Test
    public void test_ResetTipWizard_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3a0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ResetTipWizard();
                    }
                });
    }

    @Test
    public void test_getAxRollZoom_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x4b6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxRollZoom();
                    }
                });
    }

    @Test
    public void test_setAxRollZoom_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x4b6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxRollZoom(false);
                    }
                });
    }

    @Test
    public void test_Save_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x11b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Save();
                    }
                });
    }

    @Test
    public void test_Save_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x11b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(419))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Save(new Variant(419));
                    }
                });
    }

    @Test
    public void test_SaveWorkspace_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xd4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveWorkspace();
                    }
                });
    }

    @Test
    public void test_SaveWorkspace_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xd4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(280))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SaveWorkspace(new Variant(280));
                    }
                });
    }

    @Test
    public void test_getAxScreenUpdating_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x17e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxScreenUpdating();
                    }
                });
    }

    @Test
    public void test_setAxScreenUpdating_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x17e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxScreenUpdating(false);
                    }
                });
    }

    @Test
    public void test_SetDefaultChart_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xdb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SetDefaultChart();
                    }
                });
    }

    @Test
    public void test_SetDefaultChart_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xdb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(787))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SetDefaultChart(new Variant(787));
                    }
                });
    }

    @Test
    public void test_SetDefaultChart_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xdb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(323), new Variant(372))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.SetDefaultChart(new Variant(323), new Variant(372));
                    }
                });
    }

    @Test
    public void test_getAxSheetsInNewWorkbook_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3e1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxSheetsInNewWorkbook();
                    }
                });
    }

    @Test
    public void test_setAxSheetsInNewWorkbook_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3e1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSheetsInNewWorkbook(42);
                    }
                });
    }

    @Test
    public void test_getAxShowChartTipNames_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x4b7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxShowChartTipNames();
                    }
                });
    }

    @Test
    public void test_setAxShowChartTipNames_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x4b7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxShowChartTipNames(false);
                    }
                });
    }

    @Test
    public void test_getAxShowChartTipValues_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x4b8).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxShowChartTipValues();
                    }
                });
    }

    @Test
    public void test_setAxShowChartTipValues_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x4b8).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxShowChartTipValues(false);
                    }
                });
    }

    @Test
    public void test_getAxStandardFont_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x39c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxStandardFont();
                    }
                });
    }

    @Test
    public void test_setAxStandardFont_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x39c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("ldeJgeENdK"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxStandardFont("ldeJgeENdK");
                    }
                });
    }

    @Test
    public void test_getAxStandardFontSize_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x39d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxStandardFontSize();
                    }
                });
    }

    @Test
    public void test_setAxStandardFontSize_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x39d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32d))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxStandardFontSize(42.32d);
                    }
                });
    }

    @Test
    public void test_getAxStartupPath_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x181).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxStartupPath();
                    }
                });
    }

    @Test
    public void test_getAxStatusBar_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x182).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxStatusBar();
                    }
                });
    }

    @Test
    public void test_setAxStatusBar_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x182).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(290))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxStatusBar(new Variant(290));
                    }
                });
    }

    @Test
    public void test_getAxTemplatesPath_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x17d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxTemplatesPath();
                    }
                });
    }

    @Test
    public void test_getAxShowToolTips_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x183).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxShowToolTips();
                    }
                });
    }

    @Test
    public void test_setAxShowToolTips_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x183).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxShowToolTips(false);
                    }
                });
    }

    @Test
    public void test_getAxTop_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x7e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxTop();
                    }
                });
    }

    @Test
    public void test_setAxTop_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x7e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32d))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxTop(42.32d);
                    }
                });
    }

    @Test
    public void test_getAxDefaultSaveFormat_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x4b9).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxDefaultSaveFormat();
                    }
                });
    }

    @Test
    public void test_setAxDefaultSaveFormat_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x4b9).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDefaultSaveFormat(42);
                    }
                });
    }

    @Test
    public void test_getAxTransitionMenuKey_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x136).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxTransitionMenuKey();
                    }
                });
    }

    @Test
    public void test_setAxTransitionMenuKey_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x136).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("AoTmrTbSqZ"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxTransitionMenuKey("AoTmrTbSqZ");
                    }
                });
    }

    @Test
    public void test_getAxTransitionMenuKeyAction_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x137).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxTransitionMenuKeyAction();
                    }
                });
    }

    @Test
    public void test_setAxTransitionMenuKeyAction_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x137).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxTransitionMenuKeyAction(42);
                    }
                });
    }

    @Test
    public void test_getAxTransitionNavigKeys_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x138).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxTransitionNavigKeys();
                    }
                });
    }

    @Test
    public void test_setAxTransitionNavigKeys_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x138).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxTransitionNavigKeys(false);
                    }
                });
    }

    @Test
    public void test_Undo_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x12f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Undo();
                    }
                });
    }

    @Test
    public void test_getAxUsableHeight_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x185).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxUsableHeight();
                    }
                });
    }

    @Test
    public void test_getAxUsableWidth_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x186).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxUsableWidth();
                    }
                });
    }

    @Test
    public void test_getAxUserControl_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x4ba).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxUserControl();
                    }
                });
    }

    @Test
    public void test_setAxUserControl_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x4ba).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxUserControl(false);
                    }
                });
    }

    @Test
    public void test_getAxUserName_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x187).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxUserName();
                    }
                });
    }

    @Test
    public void test_setAxUserName_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x187).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("uTelkTmyzI"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxUserName("uTelkTmyzI");
                    }
                });
    }

    @Test
    public void test_getAxValue_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxValue();
                    }
                });
    }

    @Test
    public void test_getAxVBE_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x4bb).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<VBE>() {
                    @Override
                    public VBE invoke() throws ActiveXException {
                        return component.getAxVBE();
                    }
                });
    }

    @Test
    public void test_getAxVersion_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x188).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxVersion();
                    }
                });
    }

    @Test
    public void test_getAxVisible_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x22e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxVisible();
                    }
                });
    }

    @Test
    public void test_setAxVisible_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x22e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxVisible(false);
                    }
                });
    }

    @Test
    public void test_Volatile_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x314).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Volatile();
                    }
                });
    }

    @Test
    public void test_Volatile_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x314).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(585))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Volatile(new Variant(585));
                    }
                });
    }

    @Test
    public void test_Wait_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x189).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(802))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Wait(new Variant(802));
                    }
                });
    }

    @Test
    public void test_getAxWidth_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x7a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDouble(new Returns<Double>() {
                    @Override
                    public Double invoke() throws ActiveXException {
                        return component.getAxWidth();
                    }
                });
    }

    @Test
    public void test_setAxWidth_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x7a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32d))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxWidth(42.32d);
                    }
                });
    }

    @Test
    public void test_getAxWindowsForPens_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x18b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxWindowsForPens();
                    }
                });
    }

    @Test
    public void test_getAxWindowState_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x18c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxWindowState();
                    }
                });
    }

    @Test
    public void test_setAxWindowState_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x18c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxWindowState(42);
                    }
                });
    }

    @Test
    public void test_getAxUILanguage_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxUILanguage();
                    }
                });
    }

    @Test
    public void test_setAxUILanguage_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxUILanguage(42);
                    }
                });
    }

    @Test
    public void test_getAxDefaultSheetDirection_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xe5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxDefaultSheetDirection();
                    }
                });
    }

    @Test
    public void test_setAxDefaultSheetDirection_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xe5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDefaultSheetDirection(42);
                    }
                });
    }

    @Test
    public void test_getAxCursorMovement_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xe8).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxCursorMovement();
                    }
                });
    }

    @Test
    public void test_setAxCursorMovement_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xe8).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCursorMovement(42);
                    }
                });
    }

    @Test
    public void test_getAxControlCharacters_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xe9).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxControlCharacters();
                    }
                });
    }

    @Test
    public void test_setAxControlCharacters_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xe9).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxControlCharacters(42);
                    }
                });
    }

    @Test
    public void test__WSFunction_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._WSFunction();
                    }
                });
    }

    @Test
    public void test__WSFunction_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xa9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(164))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._WSFunction(new Variant(164));
                    }
                });
    }

    @Test
    public void test__WSFunction_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(915), new Variant(113))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._WSFunction(new Variant(915), new Variant(113));
                    }
                });
    }

    @Test
    public void test__WSFunction_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(251), new Variant(630), new Variant
                (99))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._WSFunction(new Variant(251), new Variant(630), new Variant(99));
                    }
                });
    }

    @Test
    public void test__WSFunction_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(270), new Variant(713), new Variant
                (133), new Variant(214))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._WSFunction(new Variant(270), new Variant(713), new Variant(133), new
                                Variant(214));
                    }
                });
    }

    @Test
    public void test__WSFunction_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(727), new Variant(225), new Variant
                (616), new Variant(95), new Variant(355))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._WSFunction(new Variant(727), new Variant(225), new Variant(616), new
                                Variant(95), new Variant(355));
                    }
                });
    }

    @Test
    public void test__WSFunction_SixArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(756), new Variant(941), new Variant
                (260), new Variant(393), new Variant(918), new Variant(898))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._WSFunction(new Variant(756), new Variant(941), new Variant(260), new
                                Variant(393), new Variant(918), new Variant(898));
                    }
                });
    }

    @Test
    public void test__WSFunction_SevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(114), new Variant(137), new Variant
                (111), new Variant(396), new Variant(757), new Variant(726), new Variant(894))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._WSFunction(new Variant(114), new Variant(137), new Variant(111), new
                                Variant(396), new Variant(757), new Variant(726), new Variant(894));
                    }
                });
    }

    @Test
    public void test__WSFunction_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(238), new Variant(358), new Variant
                (469), new Variant(725), new Variant(419), new Variant(698), new Variant(14), new Variant(837))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._WSFunction(new Variant(238), new Variant(358), new Variant(469), new
                                Variant(725), new Variant(419), new Variant(698), new Variant(14), new Variant(837));
                    }
                });
    }

    @Test
    public void test__WSFunction_NineArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(510), new Variant(258), new Variant
                (1), new Variant(639), new Variant(342), new Variant(164), new Variant(821), new Variant(323), new
                Variant(104))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._WSFunction(new Variant(510), new Variant(258), new Variant(1), new Variant
                                (639), new Variant(342), new Variant(164), new Variant(821), new Variant(323), new
                                Variant(104));
                    }
                });
    }

    @Test
    public void test__WSFunction_TenArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(398), new Variant(969), new Variant
                (417), new Variant(324), new Variant(914), new Variant(805), new Variant(194), new Variant(442), new
                Variant(546), new Variant(387))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._WSFunction(new Variant(398), new Variant(969), new Variant(417), new
                                Variant(324), new Variant(914), new Variant(805), new Variant(194), new Variant(442),
                                new Variant(546), new Variant(387));
                    }
                });
    }

    @Test
    public void test__WSFunction_ElevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(306), new Variant(797), new Variant
                (873), new Variant(167), new Variant(516), new Variant(861), new Variant(228), new Variant(262), new
                Variant(673), new Variant(195), new Variant(979))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._WSFunction(new Variant(306), new Variant(797), new Variant(873), new
                                Variant(167), new Variant(516), new Variant(861), new Variant(228), new Variant(262),
                                new Variant(673), new Variant(195), new Variant(979));
                    }
                });
    }

    @Test
    public void test__WSFunction_TwelveArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(138), new Variant(303), new Variant
                (965), new Variant(584), new Variant(899), new Variant(139), new Variant(249), new Variant(291), new
                Variant(138), new Variant(82), new Variant(70), new Variant(823))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._WSFunction(new Variant(138), new Variant(303), new Variant(965), new
                                Variant(584), new Variant(899), new Variant(139), new Variant(249), new Variant(291),
                                new Variant(138), new Variant(82), new Variant(70), new Variant(823));
                    }
                });
    }

    @Test
    public void test__WSFunction_ThirteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(679), new Variant(793), new Variant
                (542), new Variant(101), new Variant(354), new Variant(39), new Variant(296), new Variant(243), new
                Variant(454), new Variant(252), new Variant(699), new Variant(592), new Variant(178))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._WSFunction(new Variant(679), new Variant(793), new Variant(542), new
                                Variant(101), new Variant(354), new Variant(39), new Variant(296), new Variant(243),
                                new Variant(454), new Variant(252), new Variant(699), new Variant(592), new Variant
                                        (178));
                    }
                });
    }

    @Test
    public void test__WSFunction_FourteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(809), new Variant(700), new Variant
                (14), new Variant(657), new Variant(499), new Variant(704), new Variant(157), new Variant(305), new
                Variant(717), new Variant(797), new Variant(488), new Variant(376), new Variant(441), new Variant(178))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._WSFunction(new Variant(809), new Variant(700), new Variant(14), new Variant
                                (657), new Variant(499), new Variant(704), new Variant(157), new Variant(305), new
                                Variant(717), new Variant(797), new Variant(488), new Variant(376), new Variant(441),
                                new Variant(178));
                    }
                });
    }

    @Test
    public void test__WSFunction_FifteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(7), new Variant(499), new Variant
                (322), new Variant(968), new Variant(768), new Variant(352), new Variant(633), new Variant(312), new
                Variant(546), new Variant(131), new Variant(603), new Variant(523), new Variant(71), new Variant(982)
                , new Variant(99))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._WSFunction(new Variant(7), new Variant(499), new Variant(322), new Variant
                                (968), new Variant(768), new Variant(352), new Variant(633), new Variant(312), new
                                Variant(546), new Variant(131), new Variant(603), new Variant(523), new Variant(71),
                                new Variant(982), new Variant(99));
                    }
                });
    }

    @Test
    public void test__WSFunction_SixteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(993), new Variant(405), new Variant
                (258), new Variant(921), new Variant(257), new Variant(490), new Variant(338), new Variant(558), new
                Variant(135), new Variant(10), new Variant(494), new Variant(171), new Variant(67), new Variant(271),
                new Variant(525), new Variant(645))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._WSFunction(new Variant(993), new Variant(405), new Variant(258), new
                                Variant(921), new Variant(257), new Variant(490), new Variant(338), new Variant(558),
                                new Variant(135), new Variant(10), new Variant(494), new Variant(171), new Variant
                                        (67), new Variant(271), new Variant(525), new Variant(645));
                    }
                });
    }

    @Test
    public void test__WSFunction_SeventeenArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(598), new Variant(379), new Variant
                (835), new Variant(879), new Variant(808), new Variant(540), new Variant(906), new Variant(237), new
                Variant(549), new Variant(932), new Variant(973), new Variant(800), new Variant(382), new Variant
                (452), new Variant(480), new Variant(194), new Variant(347))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._WSFunction(new Variant(598), new Variant(379), new Variant(835), new
                                Variant(879), new Variant(808), new Variant(540), new Variant(906), new Variant(237),
                                new Variant(549), new Variant(932), new Variant(973), new Variant(800), new Variant
                                        (382), new Variant(452), new Variant(480), new Variant(194), new Variant(347));
                    }
                });
    }

    @Test
    public void test__WSFunction_EighteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(317), new Variant(243), new Variant
                (232), new Variant(790), new Variant(435), new Variant(293), new Variant(735), new Variant(194), new
                Variant(463), new Variant(557), new Variant(84), new Variant(755), new Variant(455), new Variant(172)
                , new Variant(53), new Variant(768), new Variant(628), new Variant(847))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._WSFunction(new Variant(317), new Variant(243), new Variant(232), new
                                Variant(790), new Variant(435), new Variant(293), new Variant(735), new Variant(194),
                                new Variant(463), new Variant(557), new Variant(84), new Variant(755), new Variant
                                        (455), new Variant(172), new Variant(53), new Variant(768), new Variant(628),
                                new Variant(847));
                    }
                });
    }

    @Test
    public void test__WSFunction_NineteenArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(349), new Variant(211), new Variant
                (263), new Variant(512), new Variant(400), new Variant(609), new Variant(8), new Variant(995), new
                Variant(707), new Variant(108), new Variant(933), new Variant(710), new Variant(918), new Variant
                (277), new Variant(724), new Variant(986), new Variant(66), new Variant(575), new Variant(709))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._WSFunction(new Variant(349), new Variant(211), new Variant(263), new
                                Variant(512), new Variant(400), new Variant(609), new Variant(8), new Variant(995),
                                new Variant(707), new Variant(108), new Variant(933), new Variant(710), new Variant
                                        (918), new Variant(277), new Variant(724), new Variant(986), new Variant(66),
                                new Variant(575), new Variant(709));
                    }
                });
    }

    @Test
    public void test__WSFunction_TwentyArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(687), new Variant(825), new Variant
                (336), new Variant(719), new Variant(459), new Variant(22), new Variant(416), new Variant(941), new
                Variant(771), new Variant(762), new Variant(508), new Variant(965), new Variant(106), new Variant
                (216), new Variant(212), new Variant(453), new Variant(238), new Variant(206), new Variant(360), new
                Variant(186))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._WSFunction(new Variant(687), new Variant(825), new Variant(336), new
                                Variant(719), new Variant(459), new Variant(22), new Variant(416), new Variant(941),
                                new Variant(771), new Variant(762), new Variant(508), new Variant(965), new Variant
                                        (106), new Variant(216), new Variant(212), new Variant(453), new Variant(238)
                                , new Variant(206), new Variant(360), new Variant(186));
                    }
                });
    }

    @Test
    public void test__WSFunction_TwentyOneArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(938), new Variant(376), new Variant
                (906), new Variant(142), new Variant(718), new Variant(274), new Variant(84), new Variant(197), new
                Variant(931), new Variant(922), new Variant(298), new Variant(925), new Variant(170), new Variant
                (720), new Variant(778), new Variant(919), new Variant(756), new Variant(548), new Variant(656), new
                Variant(390), new Variant(252))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._WSFunction(new Variant(938), new Variant(376), new Variant(906), new
                                Variant(142), new Variant(718), new Variant(274), new Variant(84), new Variant(197),
                                new Variant(931), new Variant(922), new Variant(298), new Variant(925), new Variant
                                        (170), new Variant(720), new Variant(778), new Variant(919), new Variant(756)
                                , new Variant(548), new Variant(656), new Variant(390), new Variant(252));
                    }
                });
    }

    @Test
    public void test__WSFunction_TwentyTwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(962), new Variant(814), new Variant
                (715), new Variant(913), new Variant(595), new Variant(273), new Variant(179), new Variant(616), new
                Variant(603), new Variant(374), new Variant(13), new Variant(110), new Variant(547), new Variant(947)
                , new Variant(532), new Variant(434), new Variant(675), new Variant(475), new Variant(109), new
                        Variant(409), new Variant(718), new Variant(609))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._WSFunction(new Variant(962), new Variant(814), new Variant(715), new
                                Variant(913), new Variant(595), new Variant(273), new Variant(179), new Variant(616),
                                new Variant(603), new Variant(374), new Variant(13), new Variant(110), new Variant
                                        (547), new Variant(947), new Variant(532), new Variant(434), new Variant(675)
                                , new Variant(475), new Variant(109), new Variant(409), new Variant(718), new Variant
                                        (609));
                    }
                });
    }

    @Test
    public void test__WSFunction_TwentyThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(5), new Variant(67), new Variant
                (953), new Variant(86), new Variant(803), new Variant(531), new Variant(73), new Variant(829), new
                Variant(309), new Variant(492), new Variant(416), new Variant(315), new Variant(722), new Variant
                (543), new Variant(124), new Variant(508), new Variant(131), new Variant(233), new Variant(772), new
                Variant(176), new Variant(255), new Variant(249), new Variant(432))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._WSFunction(new Variant(5), new Variant(67), new Variant(953), new Variant
                                (86), new Variant(803), new Variant(531), new Variant(73), new Variant(829), new
                                Variant(309), new Variant(492), new Variant(416), new Variant(315), new Variant(722),
                                new Variant(543), new Variant(124), new Variant(508), new Variant(131), new Variant
                                        (233), new Variant(772), new Variant(176), new Variant(255), new Variant(249)
                                , new Variant(432));
                    }
                });
    }

    @Test
    public void test__WSFunction_TwentyFourArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(349), new Variant(905), new Variant
                (104), new Variant(428), new Variant(366), new Variant(568), new Variant(592), new Variant(136), new
                Variant(601), new Variant(531), new Variant(815), new Variant(631), new Variant(543), new Variant
                (614), new Variant(813), new Variant(394), new Variant(156), new Variant(838), new Variant(24), new
                Variant(361), new Variant(206), new Variant(37), new Variant(657), new Variant(53))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._WSFunction(new Variant(349), new Variant(905), new Variant(104), new
                                Variant(428), new Variant(366), new Variant(568), new Variant(592), new Variant(136),
                                new Variant(601), new Variant(531), new Variant(815), new Variant(631), new Variant
                                        (543), new Variant(614), new Variant(813), new Variant(394), new Variant(156)
                                , new Variant(838), new Variant(24), new Variant(361), new Variant(206), new Variant
                                        (37), new Variant(657), new Variant(53));
                    }
                });
    }

    @Test
    public void test__WSFunction_TwentyFiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(250), new Variant(99), new Variant
                (199), new Variant(685), new Variant(313), new Variant(417), new Variant(66), new Variant(987), new
                Variant(578), new Variant(923), new Variant(922), new Variant(769), new Variant(186), new Variant
                (897), new Variant(814), new Variant(157), new Variant(502), new Variant(138), new Variant(88), new
                Variant(847), new Variant(857), new Variant(886), new Variant(741), new Variant(795), new Variant(993))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._WSFunction(new Variant(250), new Variant(99), new Variant(199), new Variant
                                (685), new Variant(313), new Variant(417), new Variant(66), new Variant(987), new
                                Variant(578), new Variant(923), new Variant(922), new Variant(769), new Variant(186),
                                new Variant(897), new Variant(814), new Variant(157), new Variant(502), new Variant
                                        (138), new Variant(88), new Variant(847), new Variant(857), new Variant(886),
                                new Variant(741), new Variant(795), new Variant(993));
                    }
                });
    }

    @Test
    public void test__WSFunction_TwentySixArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(773), new Variant(482), new Variant
                (712), new Variant(915), new Variant(417), new Variant(987), new Variant(676), new Variant(295), new
                Variant(294), new Variant(149), new Variant(569), new Variant(558), new Variant(314), new Variant(27)
                , new Variant(607), new Variant(175), new Variant(740), new Variant(270), new Variant(191), new
                        Variant(170), new Variant(557), new Variant(132), new Variant(882), new Variant(396), new
                        Variant(885), new Variant(555))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._WSFunction(new Variant(773), new Variant(482), new Variant(712), new
                                Variant(915), new Variant(417), new Variant(987), new Variant(676), new Variant(295),
                                new Variant(294), new Variant(149), new Variant(569), new Variant(558), new Variant
                                        (314), new Variant(27), new Variant(607), new Variant(175), new Variant(740),
                                new Variant(270), new Variant(191), new Variant(170), new Variant(557), new Variant
                                        (132), new Variant(882), new Variant(396), new Variant(885), new Variant(555));
                    }
                });
    }

    @Test
    public void test__WSFunction_TwentySevenArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(68), new Variant(945), new Variant
                (756), new Variant(568), new Variant(616), new Variant(639), new Variant(343), new Variant(304), new
                Variant(793), new Variant(430), new Variant(578), new Variant(351), new Variant(643), new Variant
                (126), new Variant(728), new Variant(607), new Variant(636), new Variant(802), new Variant(12), new
                Variant(544), new Variant(722), new Variant(272), new Variant(794), new Variant(974), new Variant(17)
                , new Variant(938), new Variant(184))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._WSFunction(new Variant(68), new Variant(945), new Variant(756), new Variant
                                (568), new Variant(616), new Variant(639), new Variant(343), new Variant(304), new
                                Variant(793), new Variant(430), new Variant(578), new Variant(351), new Variant(643),
                                new Variant(126), new Variant(728), new Variant(607), new Variant(636), new Variant
                                        (802), new Variant(12), new Variant(544), new Variant(722), new Variant(272),
                                new Variant(794), new Variant(974), new Variant(17), new Variant(938), new Variant
                                        (184));
                    }
                });
    }

    @Test
    public void test__WSFunction_TwentyEightArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(793), new Variant(177), new Variant
                (590), new Variant(738), new Variant(893), new Variant(58), new Variant(225), new Variant(303), new
                Variant(705), new Variant(446), new Variant(899), new Variant(982), new Variant(677), new Variant
                (857), new Variant(988), new Variant(612), new Variant(84), new Variant(279), new Variant(533), new
                Variant(93), new Variant(297), new Variant(938), new Variant(489), new Variant(43), new Variant(878),
                new Variant(398), new Variant(297), new Variant(904))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._WSFunction(new Variant(793), new Variant(177), new Variant(590), new
                                Variant(738), new Variant(893), new Variant(58), new Variant(225), new Variant(303),
                                new Variant(705), new Variant(446), new Variant(899), new Variant(982), new Variant
                                        (677), new Variant(857), new Variant(988), new Variant(612), new Variant(84),
                                new Variant(279), new Variant(533), new Variant(93), new Variant(297), new Variant
                                        (938), new Variant(489), new Variant(43), new Variant(878), new Variant(398),
                                new Variant(297), new Variant(904));
                    }
                });
    }

    @Test
    public void test__WSFunction_TwentyNineArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(0), new Variant(36), new Variant
                (822), new Variant(957), new Variant(998), new Variant(143), new Variant(290), new Variant(13), new
                Variant(608), new Variant(22), new Variant(240), new Variant(681), new Variant(421), new Variant(478)
                , new Variant(402), new Variant(48), new Variant(276), new Variant(884), new Variant(200), new
                        Variant(570), new Variant(892), new Variant(900), new Variant(30), new Variant(393), new
                        Variant(159), new Variant(728), new Variant(463), new Variant(597), new Variant(137))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._WSFunction(new Variant(0), new Variant(36), new Variant(822), new Variant
                                (957), new Variant(998), new Variant(143), new Variant(290), new Variant(13), new
                                Variant(608), new Variant(22), new Variant(240), new Variant(681), new Variant(421),
                                new Variant(478), new Variant(402), new Variant(48), new Variant(276), new Variant
                                        (884), new Variant(200), new Variant(570), new Variant(892), new Variant(900)
                                , new Variant(30), new Variant(393), new Variant(159), new Variant(728), new Variant
                                        (463), new Variant(597), new Variant(137));
                    }
                });
    }

    @Test
    public void test__WSFunction_ThirtyArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(201), new Variant(365), new Variant
                (467), new Variant(278), new Variant(971), new Variant(827), new Variant(33), new Variant(394), new
                Variant(824), new Variant(394), new Variant(992), new Variant(242), new Variant(332), new Variant
                (351), new Variant(814), new Variant(415), new Variant(95), new Variant(557), new Variant(879), new
                Variant(851), new Variant(764), new Variant(839), new Variant(152), new Variant(244), new Variant
                (646), new Variant(550), new Variant(432), new Variant(261), new Variant(242), new Variant(224))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component._WSFunction(new Variant(201), new Variant(365), new Variant(467), new
                                Variant(278), new Variant(971), new Variant(827), new Variant(33), new Variant(394),
                                new Variant(824), new Variant(394), new Variant(992), new Variant(242), new Variant
                                        (332), new Variant(351), new Variant(814), new Variant(415), new Variant(95),
                                new Variant(557), new Variant(879), new Variant(851), new Variant(764), new Variant
                                        (839), new Variant(152), new Variant(244), new Variant(646), new Variant(550)
                                , new Variant(432), new Variant(261), new Variant(242), new Variant(224));
                    }
                });
    }

    @Test
    public void test_getAxEnableEvents_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x4bc).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxEnableEvents();
                    }
                });
    }

    @Test
    public void test_setAxEnableEvents_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x4bc).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxEnableEvents(false);
                    }
                });
    }

    @Test
    public void test_getAxDisplayInfoWindow_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x4bd).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxDisplayInfoWindow();
                    }
                });
    }

    @Test
    public void test_setAxDisplayInfoWindow_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x4bd).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDisplayInfoWindow(false);
                    }
                });
    }

}