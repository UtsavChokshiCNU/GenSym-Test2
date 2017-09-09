package com.gensym.jgi;

public class G2ConnectionListenerStub implements G2ConnectionListener {
    private boolean connectionInitialized;
    private boolean errorCommunicated;

    @Override
    public void g2IsPaused(G2ConnectionEvent event) {

    }

    @Override
    public void g2IsResumed(G2ConnectionEvent event) {

    }

    @Override
    public void g2IsReset(G2ConnectionEvent event) {

    }

    @Override
    public void g2IsStarted(G2ConnectionEvent event) {

    }

    @Override
    public void g2ConnectionClosed(G2ConnectionEvent event) {

    }

    @Override
    public void g2ConnectionInitialized(G2ConnectionEvent event) {
        this.connectionInitialized = true;
    }

    @Override
    public void g2MessageReceived(G2ConnectionEvent event) {

    }

    @Override
    public void communicationError(G2CommunicationErrorEvent error_event) {
        this.errorCommunicated = true;
    }

    @Override
    public void readBlockage(G2ConnectionEvent event) {

    }

    @Override
    public void writeBlockage(G2ConnectionEvent event) {

    }

    public boolean isConnectionInitialized() {
        return this.connectionInitialized;
    }

    public boolean isErrorCommunicated() {
        return this.errorCommunicated;
    }
}
