package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

import java.util.Date;

public class MailerTest extends ActiveXDispatchableTestBase {

    private Mailer component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new Mailer(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(84), new Variant(958))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(84), new Variant(958));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(46))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(46));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(970))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(970));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(417), new Variant(353), new
                Variant(42L), new Variant(42L), new Variant(377))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(417), new Variant(353), 42L, 42L, new Variant(377));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(128), new
                Variant(42L), new Variant(42), new Variant(653), new Variant(149), new Variant(943), new Variant(669))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(128), 42L, 42, new Variant(653), new Variant(149), new
                                Variant(943), new Variant(669));
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
    public void test_getAxBCCRecipients_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3d7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxBCCRecipients();
                    }
                });
    }

    @Test
    public void test_setAxBCCRecipients_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3d7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(776))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxBCCRecipients(new Variant(776));
                    }
                });
    }

    @Test
    public void test_getAxCCRecipients_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3d6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxCCRecipients();
                    }
                });
    }

    @Test
    public void test_setAxCCRecipients_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3d6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(654))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCCRecipients(new Variant(654));
                    }
                });
    }

    @Test
    public void test_getAxEnclosures_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3d8).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxEnclosures();
                    }
                });
    }

    @Test
    public void test_setAxEnclosures_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3d8).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(649))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxEnclosures(new Variant(649));
                    }
                });
    }

    @Test
    public void test_getAxReceived_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3da).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxReceived();
                    }
                });
    }

    @Test
    public void test_getAxSendDateTime_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3db).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDate(new Returns<Date>() {
                    @Override
                    public Date invoke() throws ActiveXException {
                        return component.getAxSendDateTime();
                    }
                });
    }

    @Test
    public void test_getAxSender_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3dc).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxSender();
                    }
                });
    }

    @Test
    public void test_getAxSubject_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3b9).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxSubject();
                    }
                });
    }

    @Test
    public void test_setAxSubject_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3b9).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("BOJDqYNPnK"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSubject("BOJDqYNPnK");
                    }
                });
    }

    @Test
    public void test_getAxToRecipients_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3d5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxToRecipients();
                    }
                });
    }

    @Test
    public void test_setAxToRecipients_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3d5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(820))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxToRecipients(new Variant(820));
                    }
                });
    }

    @Test
    public void test_getAxWhichAddress_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3ce).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxWhichAddress();
                    }
                });
    }

    @Test
    public void test_setAxWhichAddress_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3ce).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(142))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxWhichAddress(new Variant(142));
                    }
                });
    }

}