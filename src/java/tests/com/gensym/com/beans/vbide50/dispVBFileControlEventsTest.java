package com.gensym.com.beans.vbide50;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class dispVBFileControlEventsTest extends ActiveXDispatchableTestBase {

    private dispVBFileControlEvents component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new dispVBFileControlEvents(axProxy);
    }

    @Test
    public void test_AfterAddFile_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(724), new Variant(42), new Variant
                ("tTzINtjoLc"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AfterAddFile(new Variant(724), 42, "tTzINtjoLc");
                    }
                });
    }

    @Test
    public void test_AfterChangeFileName_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(609), new Variant(42), new Variant
                ("OWMePfvQPH"), new Variant("EahKGzlZqv"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AfterChangeFileName(new Variant(609), 42, "OWMePfvQPH", "EahKGzlZqv");
                    }
                });
    }

    @Test
    public void test_AfterCloseFile_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(413), new Variant(42), new Variant
                ("dRJUJfVsmF"), new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AfterCloseFile(new Variant(413), 42, "dRJUJfVsmF", false);
                    }
                });
    }

    @Test
    public void test_AfterWriteFile_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(164), new Variant((short) 42), new
                Variant("mzaUOehuHw"), new Variant((short) 42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AfterWriteFile(new Variant(164), (short) 42, "mzaUOehuHw", (short) 42);
                    }
                });
    }

    @Test
    public void test_AfterRemoveFile_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(728), new Variant(42), new Variant
                ("XuBWANEoBd"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AfterRemoveFile(new Variant(728), 42, "XuBWANEoBd");
                    }
                });
    }

    @Test
    public void test_BeforeLoadFile_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(305), new Variant(945))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.BeforeLoadFile(new Variant(305), new Variant(945));
                    }
                });
    }

    @Test
    public void test_DoGetNewFileName_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x8).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(199), new Variant(42), new Variant
                (531), new Variant("uyKQohFfbd"), new Variant(305))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.DoGetNewFileName(new Variant(199), 42, new Variant(531), "uyKQohFfbd", new Variant
                                (305));
                    }
                });
    }

    @Test
    public void test_RequestChangeFileName_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(118), new Variant(42), new Variant
                ("vxZYdLWObu"), new Variant("SyyaskzPSS"), new Variant(18))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.RequestChangeFileName(new Variant(118), 42, "vxZYdLWObu", "SyyaskzPSS", new Variant
                                (18));
                    }
                });
    }

    @Test
    public void test_RequestWriteFile_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(527), new Variant("MOFHPlBfaj"), new
                Variant(183))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.RequestWriteFile(new Variant(527), "MOFHPlBfaj", new Variant(183));
                    }
                });
    }

}