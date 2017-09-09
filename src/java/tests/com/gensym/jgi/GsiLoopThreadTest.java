package com.gensym.jgi;

import org.assertj.core.api.Assertions;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.powermock.core.classloader.annotations.PrepareForTest;
import org.powermock.modules.junit4.PowerMockRunner;
import org.powermock.reflect.Whitebox;

import java.util.Vector;

import static org.assertj.core.api.Assertions.*;
import static org.mockito.Matchers.any;
import static org.mockito.Mockito.times;
import static org.mockito.Mockito.verify;
import static org.powermock.api.mockito.PowerMockito.*;
import static org.powermock.reflect.Whitebox.*;

/**
 * Created by Mohamed El Bahrawy on 17/06/2017.
 */

@RunWith(PowerMockRunner.class)
@PrepareForTest({GsiLoopThread.class, JGInterface.class})
public class GsiLoopThreadTest {

    private static final boolean DISABLE_OPTION_DEBUG = false;
    private static final String[] NO_COMMAND_LINE = null;

    @Test
    public void test_constructor() {

        // static mocks
        mockStatic(JGInterface.class);

        // mocks
        JGInterface intf = mock(JGInterface.class);

        // arrange
        String[] cmdLine = new String[0];
        boolean optionDebug = true;

        // when
        GsiLoopThread gsiLoopThread = new GsiLoopThread(intf, cmdLine, optionDebug);

        // arrange assertion
        JGInterface intrface = Whitebox.getInternalState(GsiLoopThread.class, "intrface");
        String[] commandLine = Whitebox.getInternalState(gsiLoopThread, "commandLine");
        GsiLoopThread invocation = Whitebox.getInternalState(GsiLoopThread.class, "invocation");
        Boolean option_debug = Whitebox.getInternalState(gsiLoopThread, "option_debug");

        // assert
        Assertions.assertThat(intrface).isSameAs(intf);
        Assertions.assertThat(commandLine).isSameAs(cmdLine);
        Assertions.assertThat(invocation).isSameAs(gsiLoopThread);
        assertThat(option_debug).isEqualTo(optionDebug);

    }

    @Test
    public void test_run_() throws Exception {
        // static mocks
        mockStatic(GsiLoopThread.class);
        mockStatic(JGInterface.class);

        // mocks
        GsiLoopThread gsiLoopThread = mock(GsiLoopThread.class);
        GsiInitializeThread gsiInitializeThread = mock(GsiInitializeThread.class);
        JGInterface jgInterface = mock(JGInterface.class);
        JGInterface intrface = mock(JGInterface.class);
        WorkWithContext work = mock(WorkWithContext.class);

        // arrange
        Integer return_value = 1;
        Boolean option_debug = false;
        String[] commandLine = {};
        Boolean started = true;
        Whitebox.setInternalState(gsiLoopThread, "option_debug", option_debug);
        Whitebox.setInternalState(GsiLoopThread.class, "intrface", intrface);
        Whitebox.setInternalState(gsiLoopThread, "commandLine",commandLine);
        Whitebox.setInternalState(GsiLoopThread.class, "started", started);

        JGInterface nullJgi = null;
        Integer context = 1;
        G2CommunicationException g2CommunicationException = new G2CommunicationException();

        Boolean needsTickle = true;
        Whitebox.setInternalState(gsiLoopThread, "needsTickle",needsTickle);

        // given
        when(gsiLoopThread, "initialize_tickle").thenReturn(return_value);
        whenNew(GsiInitializeThread.class).withNoArguments().thenReturn(gsiInitializeThread);
        when(gsiLoopThread, "finalize_tickle").thenReturn(return_value);
        when(JGInterface.getJGInterface(new String[0])).thenReturn(jgInterface).thenReturn(jgInterface).thenReturn(jgInterface).thenReturn(nullJgi);
        doThrow(g2CommunicationException).when(work).invoke();
        when(gsiLoopThread.dequeue()).thenReturn(work).thenThrow(Exception.class);
        when(work.getContext()).thenReturn(context);

        // when
        doCallRealMethod().when(gsiLoopThread).run();
        try {
            gsiLoopThread.run();
            fail("Runtime exception expected");
        } catch (RuntimeException ex) {

        }

        // arrange assertions
        Boolean needsTickleResult = Whitebox.getInternalState(gsiLoopThread, "needsTickle");

        // assert
        Assertions.assertThat(needsTickleResult).isFalse();

        // verify static
        verifyStatic(times(4));
        JGInterface.getJGInterface(any(String[].class));

        // verify
        verifyPrivate(gsiLoopThread).invoke( "initialize_tickle");
        verify(jgInterface).communicationError(-1, -1, "failed to initialize JNI code: " + return_value, null);
        verifyNew(GsiInitializeThread.class).withNoArguments();
        verify(gsiInitializeThread).start();
        verifyPrivate(gsiLoopThread).invoke("finalize_tickle");
        verify(jgInterface).communicationError(-1, -1, "failed to initialize JNI code (final): " + return_value, null);
        verify(work).invoke();
        verify(intrface).handleCommunicationError(context, -1, g2CommunicationException.getMessage(), null);
        verify(jgInterface).communicationError(-1, -1, "java.lang.Exception", null);
        verify(gsiLoopThread).gsi_run_loop(false);
        verify(gsiLoopThread).setInterfaceOutput(option_debug);

    }

    @Test
    public void enqueue_without_tickle() {

        // given
        GsiLoopThread gsiLoopThreadMock = mock(GsiLoopThread.class);

        Work workMock = mock(Work.class);

        Vector workQueueMock = mock(Vector.class);

        final String workQueueFieldName = "work_queue";
        setInternalState(gsiLoopThreadMock, workQueueFieldName, workQueueMock);

        final String needTickleFieldName = "needsTickle";
        final boolean needTickle = false;
        setInternalState(gsiLoopThreadMock, needTickleFieldName, needTickle);

        doCallRealMethod().when(gsiLoopThreadMock).enqueue(workMock);

        // when
        gsiLoopThreadMock.enqueue(workMock);

        // then
        verify(workQueueMock).addElement(workMock);
    }

    @Test
    public void enqueue_with_tickle() {

        // given
        GsiLoopThread gsiLoopThreadMock = mock(GsiLoopThread.class);

        Work workMock = mock(Work.class);

        Vector workQueueMock = mock(Vector.class);

        final String workQueueFieldName = "work_queue";
        setInternalState(gsiLoopThreadMock, workQueueFieldName, workQueueMock);

        final String needTickleFieldName = "needsTickle";
        final boolean needTickle = true;
        setInternalState(gsiLoopThreadMock, needTickleFieldName, needTickle);

        doCallRealMethod().when(gsiLoopThreadMock).enqueue(workMock);

        // when
        gsiLoopThreadMock.enqueue(workMock);

        // then
        Boolean actualNeedTickle = getInternalState(gsiLoopThreadMock, needTickleFieldName);
        assertThat(actualNeedTickle).isFalse();
        verify(workQueueMock).addElement(workMock);
        verify(gsiLoopThreadMock).tickle_gsi();
    }

    @Test
    public void dequeue_work_from_work_queue() throws Exception {

        // given
        GsiLoopThread gsiLoopThreadMock = mock(GsiLoopThread.class);

        Work workMock = mock(Work.class);

        Vector workQueueMock = mock(Vector.class);

        final int removeIndex = 0;
        when(workQueueMock.remove(removeIndex)).thenReturn(workMock);

        final boolean isWorkQueueEmpty = false;
        when(workQueueMock.isEmpty()).thenReturn(isWorkQueueEmpty);

        final String workQueueFieldName = "work_queue";
        setInternalState(gsiLoopThreadMock, workQueueFieldName, workQueueMock);

        when(gsiLoopThreadMock.dequeue()).thenCallRealMethod();

        // when
        Work actualWork = gsiLoopThreadMock.dequeue();

        // then
        assertThat(actualWork).isSameAs(workMock);

        verify(workQueueMock).remove(removeIndex);
        verify(workQueueMock).isEmpty();

    }

    @Test
    public void get_null_if_no_work_on_work_queue() throws Exception {

        // given
        GsiLoopThread gsiLoopThreadMock = mock(GsiLoopThread.class);

        Vector workQueueMock = mock(Vector.class);

        final boolean isWorkQueueEmpty = true;
        when(workQueueMock.isEmpty()).thenReturn(isWorkQueueEmpty);

        final String workQueueFieldName = "work_queue";
        setInternalState(gsiLoopThreadMock, workQueueFieldName, workQueueMock);

        when(gsiLoopThreadMock.dequeue()).thenCallRealMethod();

        // when
        Work actualWork = gsiLoopThreadMock.dequeue();

        // then
        assertThat(actualWork).isNull();
        verify(workQueueMock).isEmpty();

    }

    @Test
    public void get_null_if_out_of_index() throws Exception {
        // given
        GsiLoopThread gsiLoopThreadMock = mock(GsiLoopThread.class);

        Work workMock = mock(Work.class);

        Vector workQueueMock = mock(Vector.class);

        final int removeIndex = 0;
        when(workQueueMock.remove(removeIndex)).thenThrow(ArrayIndexOutOfBoundsException.class);

        final boolean isWorkQueueEmpty = false;
        when(workQueueMock.isEmpty()).thenReturn(isWorkQueueEmpty);

        final String workQueueFieldName = "work_queue";
        setInternalState(gsiLoopThreadMock, workQueueFieldName, workQueueMock);

        when(gsiLoopThreadMock.dequeue()).thenCallRealMethod();

        // when
        Work actualWork = gsiLoopThreadMock.dequeue();

        // then
        assertThat(actualWork).isNull();

        verify(workQueueMock).remove(removeIndex);
        verify(workQueueMock).isEmpty();
    }

}
