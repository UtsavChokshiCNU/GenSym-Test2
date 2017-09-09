package com.gensym.classes;

import com.gensym.util.Symbol;

public interface ItemG2Proxy extends Item, G2_ProxyObject {
    Symbol realG2ClassName = Symbol.intern(ItemG2ProxyStub.class.getName());
}
