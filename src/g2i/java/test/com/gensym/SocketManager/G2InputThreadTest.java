package com.gensym.SocketManager;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Mock;
import org.mockito.Mockito;
import org.powermock.core.classloader.annotations.PrepareForTest;
import org.powermock.modules.junit4.PowerMockRunner;
import org.powermock.reflect.Whitebox;

import java.io.InputStream;
import java.net.Socket;

import static org.assertj.core.api.Assertions.assertThat;
import static org.mockito.Mockito.verify;
import static org.powermock.api.mockito.PowerMockito.*;

/**
 * Created by Mohamed El Bahrawy on 19/06/2017.
 */
@RunWith(PowerMockRunner.class)
@PrepareForTest({G2InputThread.class, G2JavaLog.class})
public class G2InputThreadTest {

    @Test
    public void create_new_g2_input_thread() {
        // static mocks
        mockStatic(G2InputThread.class);

        // mocks
        G2InputThread g2InputThreadMock = mock(G2InputThread.class);

        // given
        G2ClientSocket g2ClientSocketMock = mock(G2ClientSocket.class);
        g2ClientSocketMock.refID = "refID";

        mockStatic(G2JavaLog.class);
        // when
        G2InputThread g2InputThread = new G2InputThread(g2ClientSocketMock);

        // then
        final String g2clientFieldName = "g2client";
        G2ClientSocket g2client = Whitebox.getInternalState(g2InputThread, g2clientFieldName);
        assertThat(g2client).isSameAs(g2ClientSocketMock);

        final String charsReadFieldName = "charsRead";
        StringBuffer charsRead = Whitebox.getInternalState(g2InputThread, charsReadFieldName);
        assertThat(charsRead).isEmpty();

        StringBuilder expectedThreadName = new StringBuilder("Input ").append(g2ClientSocketMock.refID);
        assertThat(g2InputThread.getName()).isEqualTo(expectedThreadName.toString());
        StringBuilder logText = new StringBuilder("Created a client socket input thread for ").append(g2client.refID);
        verifyStatic();
        G2JavaLog.log(G2JavaLog.SOCKET_INFORMATION, logText.toString());
    }

    @Test
    public void get_result_when_thread_is_not_alive() {
        // static mocks
        mockStatic(G2InputThread.class);

        // mocks
        G2InputThread g2InputThreadMock = mock(G2InputThread.class);

        //given
        final boolean isAlive = false;
        when(g2InputThreadMock.isAlive()).thenReturn(isAlive);

        when(g2InputThreadMock.getResult()).thenCallRealMethod();

        // when
        String result = g2InputThreadMock.getResult();

        //then
        assertThat(result).isEmpty();
        verify(g2InputThreadMock).isAlive();
    }

    @Test
    public void get_result_when_thread_alive() {
        // static mocks
        mockStatic(G2InputThread.class);

        // mocks
        G2InputThread g2InputThreadMock = mock(G2InputThread.class);

        //given
        final boolean isAlive = true;
        when(g2InputThreadMock.isAlive()).thenReturn(isAlive);

        String charsReadValue = "test";
        StringBuffer charsRead = new StringBuffer("test");
        final String charsReadFieldName = "charsRead";
        Whitebox.setInternalState(g2InputThreadMock, charsReadFieldName, charsRead);

        when(g2InputThreadMock.getResult()).thenCallRealMethod();

        // when
        String result = g2InputThreadMock.getResult();

        //then
        assertThat(result).isEqualTo(charsReadValue);

        StringBuffer newCharsReadValue = Whitebox.getInternalState(g2InputThreadMock, charsReadFieldName);
        assertThat(newCharsReadValue.toString()).isEmpty();

        verify(g2InputThreadMock).isAlive();
    }

    @Test
    public void thread_alive_and_chars_read() {
        // static mocks
        mockStatic(G2InputThread.class);

        // mocks
        G2InputThread g2InputThreadMock = mock(G2InputThread.class);

        //given
        final boolean isAlive = true;
        when(g2InputThreadMock.isAlive()).thenReturn(isAlive);

        StringBuffer charsReadValue = new StringBuffer("test");
        final String charsReadFieldName = "charsRead";
        Whitebox.setInternalState(g2InputThreadMock, charsReadFieldName, charsReadValue);

        when(g2InputThreadMock.isResult()).thenCallRealMethod();

        // when
        boolean isResult = g2InputThreadMock.isResult();

        //then
        assertThat(isResult).isTrue();
        verify(g2InputThreadMock).isAlive();
    }

    @Test
    public void thread_alive_and_no_chars_read() {
        // static mocks
        mockStatic(G2InputThread.class);

        // mocks
        G2InputThread g2InputThreadMock = mock(G2InputThread.class);

        //given
        final boolean isAlive = true;
        when(g2InputThreadMock.isAlive()).thenReturn(isAlive);

        StringBuffer charsReadValue = new StringBuffer("");
        final String charsReadFieldName = "charsRead";
        Whitebox.setInternalState(g2InputThreadMock, charsReadFieldName, charsReadValue);

        when(g2InputThreadMock.isResult()).thenCallRealMethod();

        // when
        boolean isResult = g2InputThreadMock.isResult();

        //then
        assertThat(isResult).isFalse();
        verify(g2InputThreadMock).isAlive();
    }


    @Test
    public void thread_not_alive() {
        // static mocks
        mockStatic(G2InputThread.class);

        // mocks
        G2InputThread g2InputThreadMock = mock(G2InputThread.class);

        //given
        final boolean isAlive = false;
        when(g2InputThreadMock.isAlive()).thenReturn(isAlive);

        when(g2InputThreadMock.isResult()).thenCallRealMethod();

        // when
        boolean isResult = g2InputThreadMock.isResult();

        //then
        assertThat(isResult).isFalse();
        verify(g2InputThreadMock).isAlive();
    }

    @Test
    public void append_result() throws Exception {
        // static mocks
        mockStatic(G2InputThread.class);

        // mocks
        G2InputThread g2InputThreadMock = mock(G2InputThread.class);

        // given
        StringBuffer charsReadValue = new StringBuffer("a");
        final String charsReadFieldName = "charsRead";
        Whitebox.setInternalState(g2InputThreadMock, charsReadFieldName, charsReadValue);

        final String appendResultMethodName = "appendResult";
        char appendChar = 'a';
        doCallRealMethod().when(g2InputThreadMock, appendResultMethodName, appendChar);

        // when
        Whitebox.invokeMethod(g2InputThreadMock, appendResultMethodName, appendChar);

        // then
        StringBuffer actualCharsReadValue = Whitebox.getInternalState(g2InputThreadMock, charsReadFieldName);
        StringBuffer expectedCharsReadValue = new StringBuffer("aa");
        assertThat(actualCharsReadValue.toString()).isEqualTo(expectedCharsReadValue.toString());

    }

    @Test
    public void run_if_is_not_active() throws Exception{
        // static mocks
        mockStatic(G2InputThread.class);

        // mocks
        G2InputThread g2InputThreadMock = mock(G2InputThread.class);

        // given
        g2InputThreadMock.isActive = false;
        G2ClientSocket g2ClientSocketMock = mock(G2ClientSocket.class);
        g2ClientSocketMock.client = mock(Socket.class);
        InputStream inputStream = mock(InputStream.class);
        when(g2ClientSocketMock.client.getInputStream()).thenReturn(inputStream);

        final String g2clientFieldName = "g2client";
        Whitebox.setInternalState(g2InputThreadMock, g2clientFieldName, g2ClientSocketMock);

        doCallRealMethod().when(g2InputThreadMock).run();

        // when
        g2InputThreadMock.run();

        // then
    }



}
