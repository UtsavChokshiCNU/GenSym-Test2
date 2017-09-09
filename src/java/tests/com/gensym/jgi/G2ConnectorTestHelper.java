package com.gensym.jgi;

import com.gensym.classes.G2Definition;
import com.gensym.classes.Item;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import org.mockito.invocation.InvocationOnMock;
import org.mockito.stubbing.Answer;
import org.powermock.api.mockito.PowerMockito;

import java.lang.reflect.Method;
import java.util.ArrayList;

import static com.gensym.helpers.ObjectsFactory.anyObjectsSequence;
import static com.gensym.helpers.ObjectsFactory.anySymbol;
import static org.junit.Assert.fail;
import static org.mockito.Matchers.*;
import static org.powermock.api.mockito.PowerMockito.*;

public class G2ConnectorTestHelper {
    private static final int SamplesCount = 10;
    protected static final double Delta = 0.00001;

    protected ArrayList<G2ConnectionListener> addedConnectionListeners = new ArrayList<G2ConnectionListener>();
    protected boolean connectionCreationThrowsException = false;
    protected boolean connectionIsClosed;
    protected G2Connection getOrMakeConnectionResponse;
    protected G2Connector sut;
    protected G2Gateway connection;
    protected ArrayList<G2ConnectionListenerStub> listeners;
    protected String returnedMessage;
    protected Symbol reportedErrorSymbol;
    protected String reportedErrorMessage;
    protected Object registeredTarget;
    protected String registeredMethodName;
    protected Symbol registeredRpdName;
    protected boolean registeredWithNewThread;
    protected Method registeredMethod;
    protected Symbol calledG2ProcedureName;
    protected Object[] calledArgs;
    protected int calledTimeout;
    protected Symbol startedRpcProcedureName;
    protected Object[] startedRpcItems;
    protected boolean canCallRpc;
    protected Symbol remoteRpcG2ProcedureName;
    protected int remoteRpcReturnValueType;
    protected Symbol uniqueItemClass;
    protected Symbol uniqueItemName;
    protected String attributeAsText;
    protected double g2UnixTime;
    protected double g2UnixTimeAtStart;
    protected String g2HostName;
    protected String g2PortNumberOrName;
    protected String g2PortNumberOrNameGivenIndex;
    protected String g2SoftwareVersion;
    protected Symbol g2State;
    protected Symbol setG2State;
    protected Sequence strictInstanceOfClass;
    protected Sequence directSubclasses;
    protected boolean interfaceDebugFlag;
    protected int interfaceDebugLevel;
    protected G2Definition definition;
    protected Sequence attributeDescription;

    protected ArrayList<G2ConnectionListenerStub> addConnectionListeners() {
        this.listeners = anyConnectionListenersList();
        for (G2ConnectionListener listener : this.listeners) {
            this.sut.addG2ConnectionListener(listener);
        }
        return this.listeners;
    }

    protected G2Gateway anyG2Gateway() throws G2AccessException {
        G2Gateway g2Gateway = mock(G2Gateway.class);
        G2ConnectionInfo listener = anyG2ConnectionInfo();

        when(g2Gateway.getG2ConnectionInfo()).thenReturn(listener);

        PowerMockito.doAnswer(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                G2ConnectionListener listener = invocation.getArgumentAt(0, G2ConnectionListener.class);
                addedConnectionListeners.add(listener);
                return null;
            }
        }).when(g2Gateway).addG2ConnectionListener(any(G2ConnectionListener.class));

        PowerMockito.doAnswer(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                G2ConnectionListener listener = invocation.getArgumentAt(0, G2ConnectionListener.class);
                addedConnectionListeners.remove(listener);
                return null;
            }
        }).when(g2Gateway).removeG2ConnectionListener(any(G2ConnectionListener.class));

        PowerMockito.doAnswer(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                connectionIsClosed = true;
                return null;
            }
        }).when(g2Gateway).closeConnection();

        PowerMockito.doAnswer(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                returnedMessage = invocation.getArgumentAt(0, String.class);

                return null;
            }
        }).when(g2Gateway).returnMessage(anyString());

        PowerMockito.doAnswer(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                reportedErrorSymbol = invocation.getArgumentAt(0, Symbol.class);
                reportedErrorMessage = invocation.getArgumentAt(1, String.class);

                return null;
            }
        }).when(g2Gateway).reportLogBookErrorMessage(any(Symbol.class), any(String.class));

        PowerMockito.doAnswer(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                registeredTarget = invocation.getArgumentAt(0, Object.class);
                registeredMethodName = invocation.getArgumentAt(1, String.class);
                registeredRpdName = invocation.getArgumentAt(2, Symbol.class);

                return null;
            }
        }).when(g2Gateway).registerJavaMethod(any(Object.class), any(String.class), any(Symbol.class));

        PowerMockito.doAnswer(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                registeredTarget = invocation.getArgumentAt(0, Object.class);
                registeredMethod = invocation.getArgumentAt(1, Method.class);
                registeredRpdName = invocation.getArgumentAt(2, Symbol.class);
                registeredWithNewThread = invocation.getArgumentAt(3, boolean.class);

                return null;
            }
        }).when(g2Gateway).registerJavaMethod(any(Object.class), any(Method.class), any(Symbol.class), anyBoolean());

        PowerMockito.doAnswer(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                calledG2ProcedureName = invocation.getArgumentAt(0, Symbol.class);
                calledArgs = invocation.getArgumentAt(1, Object[].class);
                calledTimeout = invocation.getArgumentAt(2, int.class);

                return null;
            }
        }).when(g2Gateway).callRPC(any(Symbol.class), any(Object[].class), anyInt());

        PowerMockito.doAnswer(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                startedRpcProcedureName = invocation.getArgumentAt(0, Symbol.class);
                startedRpcItems = invocation.getArgumentAt(1, Object[].class);

                return null;
            }
        }).when(g2Gateway).startRPC(any(Symbol.class), any(Object[].class));

        PowerMockito.when(g2Gateway.canCallRPC()).then(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                return canCallRpc;
            }
        });

        PowerMockito.doAnswer(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                remoteRpcG2ProcedureName = invocation.getArgumentAt(0, Symbol.class);
                remoteRpcReturnValueType = invocation.getArgumentAt(1, int.class);

                return null;
            }
        }).when(g2Gateway).setRemoteRPCReturnKind(any(Symbol.class), anyInt());

        PowerMockito.doAnswer(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                uniqueItemClass = invocation.getArgumentAt(0, Symbol.class);
                uniqueItemName = invocation.getArgumentAt(1, Symbol.class);

                return null;
            }
        }).when(g2Gateway).getUniqueNamedItem(any(Symbol.class), any(Symbol.class));

        PowerMockito.when(g2Gateway.getAttributeAsText(any(Item.class), any(Symbol.class), any(Symbol.class))).then(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                return attributeAsText;
            }
        });

        PowerMockito.when(g2Gateway.getAttributeDescriptions(any(Symbol.class), any(Sequence.class))).then(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                return attributeDescription;
            }
        });

        PowerMockito.when(g2Gateway.g2UnixTime()).then(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                return g2UnixTime;
            }
        });

        PowerMockito.when(g2Gateway.g2UnixTimeAtStart()).then(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                return g2UnixTimeAtStart;
            }
        });

        PowerMockito.when(g2Gateway.g2GetHostName()).then(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                return g2HostName;
            }
        });

        PowerMockito.when(g2Gateway.g2GetPortNumberOrName()).then(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                return g2PortNumberOrName;
            }
        });

        PowerMockito.when(g2Gateway.g2GetPortNumberOrNameGivenIndex(anyInt())).then(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                return g2PortNumberOrNameGivenIndex;
            }
        });

        PowerMockito.when(g2Gateway.g2GetSoftwareVersion()).then(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                return g2SoftwareVersion;
            }
        });

        PowerMockito.when(g2Gateway.getG2State()).then(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                return g2State;
            }
        });

        PowerMockito.when(g2Gateway.setG2State(any(Symbol.class))).then(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                setG2State = invocation.getArgumentAt(0, Symbol.class);

                return g2State;
            }
        });

        PowerMockito.when(g2Gateway.getStrictInstancesOfClass(any(Symbol.class))).then(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                setG2State = invocation.getArgumentAt(0, Symbol.class);

                return strictInstanceOfClass;
            }
        });

        PowerMockito.when(g2Gateway.getDefinition(any(Symbol.class))).then(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                return definition;
            }
        });

        PowerMockito.when(g2Gateway.getDirectSubclasses(any(Symbol.class))).then(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                setG2State = invocation.getArgumentAt(0, Symbol.class);

                return directSubclasses;
            }
        });

        PowerMockito.doAnswer(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                interfaceDebugFlag = invocation.getArgumentAt(0, boolean.class);

                return null;
            }
        }).when(g2Gateway).setInterfaceDebugOptions(anyBoolean());

        PowerMockito.doAnswer(new Answer<Object>() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                interfaceDebugLevel = invocation.getArgumentAt(0, int.class);

                return null;
            }
        }).when(g2Gateway).setInterfaceDebugOptions(anyInt());

        return g2Gateway;
    }

    protected G2ConnectionListenerStub anyG2ConnectionListener() {
        return new G2ConnectionListenerStub();
    }

    protected G2ConnectionInfo anyG2ConnectionInfo() {
        G2ConnectionInfo connectionInfo = mock(G2ConnectionInfo.class);
        when(connectionInfo.isSharable()).thenReturn(false);
        when(connectionInfo.isForceNew()).thenReturn(true);
        return connectionInfo;
    }

    protected ArrayList<G2ConnectionListenerStub> anyConnectionListenersList() {
        this.listeners = new ArrayList<G2ConnectionListenerStub>();

        for (int idx = 0; idx < SamplesCount; idx++) {
            this.listeners.add(anyG2ConnectionListener());
        }

        return this.listeners;
    }

    protected void arrangeG2GatewayGetOrMakeConnection() {
        mockStatic(G2Gateway.class);
        mockStatic(G2Gateway.class, new Answer() {
            @Override
            public Object answer(InvocationOnMock invocation) throws Throwable {
                String method = invocation.getMethod().getName();

                if (method.equals("getOrMakeConnection")) {
                    if (connectionCreationThrowsException) {
                        throw new G2AccessInitiationException("Failed to create connection.");
                    }

                    return getOrMakeConnectionResponse;
                }

                return null;
            }
        });
    }

    protected void addAllListeners_assertExceptionIsNotThrown() {
        try {
            // Act
            this.sut.addAllListeners();
        } catch (Exception ex) {
            // Assert
            fail("addAllListeners: Should not throw exception.");
        }
    }

    protected void closeConnection_assertExceptionIsNotThrown() {
        try {
            // Act
            this.sut.closeConnection();
        } catch (Exception ex) {
            // Assert
            fail("closeConnection: Should not throw exception.");
        }
    }

    protected void closePrivateConnection_assertExceptionIsNotThrown() {
        try {
            // Act
            this.sut.closePrivateConnection();
        } catch (Exception ex) {
            // Assert
            fail("closePrivateConnection: Should not throw exception.");
        }
    }

    protected void removeAllListeners_assertExceptionIsNotThrown() {
        try {
            // Act
            this.sut.removeAllListeners();
        } catch (Exception ex) {
            // Assert
            fail("removeAllListeners: Should not throw exception.");
        }
    }

    protected void resetResponses() {
        this.getOrMakeConnectionResponse = new G2ConnectionStub();
        this.connectionCreationThrowsException = false;
        this.returnedMessage = "";
        this.reportedErrorMessage = "";
        this.reportedErrorSymbol = null;
        this.registeredTarget = null;
        this.registeredMethodName = "";
        this.registeredRpdName = null;
        this.canCallRpc = false;
        this.remoteRpcG2ProcedureName = null;
        this.remoteRpcReturnValueType = 0;
        this.attributeAsText = com.gensym.helpers.ObjectsFactory.anyString();
        this.g2UnixTime = com.gensym.helpers.ObjectsFactory.anyDouble();
        this.g2UnixTimeAtStart = com.gensym.helpers.ObjectsFactory.anyDouble();
        this.g2HostName = com.gensym.helpers.ObjectsFactory.anyString();
        this.g2PortNumberOrName = com.gensym.helpers.ObjectsFactory.anyString();
        this.g2PortNumberOrNameGivenIndex = com.gensym.helpers.ObjectsFactory.anyString();
        this.g2SoftwareVersion = com.gensym.helpers.ObjectsFactory.anyString();
        this.g2State = anySymbol();
        this.strictInstanceOfClass = anyObjectsSequence();
        this.directSubclasses = anyObjectsSequence();
        this.interfaceDebugLevel = 0;
        this.definition = mock(G2Definition.class);
        this.attributeDescription = anyObjectsSequence();
    }

    protected GraphicsStub anyGraphics() {
        return new GraphicsStub();
    }
}
