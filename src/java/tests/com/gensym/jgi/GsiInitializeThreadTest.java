package com.gensym.jgi;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Mockito;
import org.powermock.core.classloader.annotations.PrepareForTest;
import org.powermock.modules.junit4.PowerMockRunner;

import static org.mockito.Matchers.anyLong;
import static org.mockito.Matchers.anyMap;
import static org.mockito.Mockito.verify;
import static org.mockito.Matchers.any;
import static org.mockito.Mockito.never;
import static org.powermock.api.mockito.PowerMockito.*;


/**
 * Created by Mohamed El Bahrawy on 18/06/2017.
 */
@RunWith(PowerMockRunner.class)
@PrepareForTest({JGInterface.class, GsiLoopThread.class, Thread.class})
public class GsiInitializeThreadTest {

    @Test
    public void connect_if_tickle_returs_zero() throws Exception {
        // given
        GsiInitializeThread gsiInitializeThread = mock(GsiInitializeThread.class);
        doCallRealMethod().when(gsiInitializeThread).run();

        mockStatic(JGInterface.class);
        mockStatic(GsiLoopThread.class);

        final int successStatus = 0;
        when(GsiLoopThread.connect_tickle()).thenReturn(successStatus);

        // when
        gsiInitializeThread.run();

        // then
        verifyStatic(never());
        JGInterface.getJGInterface(any(String[].class));
        verifyStatic();
        GsiLoopThread.connect_tickle ();
    }

    @Test
    public void report_error_if_any() throws Exception {

        // given
        GsiInitializeThread gsiInitializeThread = mock(GsiInitializeThread.class);
        doCallRealMethod().when(gsiInitializeThread).run();

        mockStatic(JGInterface.class);
        JGInterface jgInterface = mock(JGInterface.class);

        when(JGInterface.getJGInterface(new String[0])).thenReturn(jgInterface);

        mockStatic(GsiLoopThread.class);
        final int failStatus = -1;
        when(GsiLoopThread.connect_tickle()).thenReturn(failStatus);

        // when
        gsiInitializeThread.run();

        // then
        final int expectedContext = -1;
        final int expectedErrorCode = -1;
        final StringBuilder expectedErrorMessage = new StringBuilder("failed to initialize JNI code (connect): ").append(failStatus);
        final String expectedInitiateConnectionId = null;
        verify(jgInterface).communicationError(expectedContext, expectedErrorCode, expectedErrorMessage.toString(), expectedInitiateConnectionId);

        verifyStatic();
        JGInterface.getJGInterface(new String[0]);

    }

}
