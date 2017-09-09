package com.gensym.jgi;

import com.gensym.classes.G2Definition;
import com.gensym.classes.Item;
import com.gensym.util.*;

import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.List;

public class G2ConnectionStub implements G2Connection {
    public List<G2ConnectionListener> G2ConnectionListeners = new ArrayList<G2ConnectionListener>();

    @Override
    public void addG2ConnectionListener(G2ConnectionListener listener) {
        G2ConnectionListeners.add(listener);
    }

    @Override
    public void removeG2ConnectionListener(G2ConnectionListener listener) {
        if (G2ConnectionListeners.contains(listener)) {
            G2ConnectionListeners.remove(listener);
        }
    }

    @Override
    public void returnMessage(String message) {

    }

    @Override
    public void reportLogBookErrorMessage(Symbol error_symbol, String error_message) {

    }

    @Override
    public void closeConnection() {

    }

    @Override
    public boolean isAlive() {
        return false;
    }

    @Override
    public void registerJavaMethod(Object target, String method_name, Symbol g2_RPD_name) {

    }

    @Override
    public void registerJavaMethod(Object target, Method java_method, Symbol g2_RPD_name, boolean call_in_new_thread) {

    }

    @Override
    public Object callRPC(Symbol g2_procedure_name, Object[] args, int timeout) throws G2AccessException {
        return null;
    }

    @Override
    public Object callRPC(Symbol g2_procedure_name, Object[] args) throws G2AccessException {
        return null;
    }

    @Override
    public void startRPC(Symbol g2_procedure_name, Object[] items) {

    }

    @Override
    public boolean canCallRPC() {
        return false;
    }

    @Override
    public void setRemoteRPCReturnKind(Symbol g2_procedure_name, int return_value_type) {

    }

    @Override
    public Item getG2ProxyForJavaObject(String javaProxyClass, Symbol g2ParentClass, Object javaObject) throws G2AccessException {
        return null;
    }

    @Override
    public Item getUniqueNamedItem(Symbol itmClass, Symbol itmName) throws G2AccessException {
        return null;
    }

    @Override
    public Item getItemWithUUID(String uuid) throws G2AccessException {
        return null;
    }

    @Override
    public String getAttributeAsText(Item itm, Symbol slotName, Symbol specificClassIfAny) throws G2AccessException {
        return null;
    }

    @Override
    public ClassManager getClassManager() {
        return null;
    }

    @Override
    public Class getInterfaceForG2Class(Symbol className_) {
        return null;
    }

    @Override
    public Object getClassAttributeValue(Symbol className, Symbol attrName) throws G2AccessException {
        return null;
    }

    @Override
    public Structure getClassAttributeValues(Symbol className, Sequence attrNames) throws G2AccessException {
        return null;
    }

    @Override
    public Sequence getAttributeDescriptions(Symbol className, Sequence attributeNames) throws G2AccessException {
        return null;
    }

    @Override
    public Structure subscribeToItem(Item itm, Sequence denotation, Object userData) throws G2AccessException {
        return null;
    }

    @Override
    public boolean unsubscribeToItem(int subscrpnHandle) throws G2AccessException {
        return false;
    }

    @Override
    public Sequence subscribeToItemMultiple(Item itm, Sequence denotation_sequences, Object userData) throws G2AccessException {
        return null;
    }

    @Override
    public boolean unsubscribeToItemMultiple(Sequence subscrpnHandles) throws G2AccessException {
        return false;
    }

    @Override
    public double g2UnixTime() throws G2AccessException {
        return 0;
    }

    @Override
    public double g2UnixTimeAtStart() throws G2AccessException {
        return 0;
    }

    @Override
    public String g2GetHostName() throws G2AccessException {
        return null;
    }

    @Override
    public String g2GetPortNumberOrName() throws G2AccessException {
        return null;
    }

    @Override
    public String g2GetPortNumberOrNameGivenIndex(int index) throws G2AccessException {
        return null;
    }

    @Override
    public String g2GetSoftwareVersion() throws G2AccessException {
        return null;
    }

    @Override
    public G2Version getG2Version() {
        return null;
    }

    @Override
    public boolean getSecureContext() {
        return false;
    }

    @Override
    public Symbol getG2State() throws G2AccessException {
        return null;
    }

    @Override
    public Symbol setG2State(Symbol newState) throws G2AccessException {
        return null;
    }

    @Override
    public Sequence getStrictInstancesOfClass(Symbol g2ClassName_) throws G2AccessException {
        return null;
    }

    @Override
    public Sequence getDirectSubclasses(Symbol g2ClassName_) throws G2AccessException {
        return null;
    }

    @Override
    public String toURLString() {
        return null;
    }

    @Override
    public String toShortString() {
        return null;
    }

    @Override
    public void setInterfaceDebugOptions(boolean on) {

    }

    @Override
    public void setInterfaceDebugOptions(int level) {

    }

    @Override
    public Item createItem(Symbol className) throws G2AccessException {
        return null;
    }

    @Override
    public Object getValue(Item itm, Denotation denotation) throws G2AccessException {
        return null;
    }

    @Override
    public boolean setValue(Item itm, Denotation denotation, Object value) throws G2AccessException {
        return false;
    }

    @Override
    public G2Definition getDefinition(Symbol g2ClassName) throws G2AccessException {
        return null;
    }

    @Override
    public void returnValues(Item[] items, Structure[] attributesArray, Object[] values, int[] statusValues) {

    }
}
