package com.gensym.G2SNMP.rpc;

public class TypeConversionException extends Exception {

    public TypeConversionException() {
    }

    public TypeConversionException(String s) {
        super(s);
    }

    public int getErrorCode() {
        return -1;
    }

}
