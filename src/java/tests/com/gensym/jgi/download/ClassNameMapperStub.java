package com.gensym.jgi.download;

import com.gensym.util.Symbol;

public class ClassNameMapperStub implements  ClassNameMapper {
    @Override
    public String javaClassNameFromG2ClassName(Symbol g2ClassName_) {
        return "javaClassNameFromG2ClassName" + g2ClassName_;
    }

    @Override
    public String getVersionForClass(Symbol g2ClassName_) {
        return "getVersionForClass" + g2ClassName_;
    }
}
