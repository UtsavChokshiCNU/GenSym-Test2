package com.gensym.nols.data;

import com.gensym.math.MathException;
import com.gensym.nols.data.function.FunctionInterface;

import java.io.Serializable;
import java.util.Vector;

public class FunctionInterfaceStub implements FunctionInterface, Serializable {
    private String name;

    public FunctionInterfaceStub(int number) {
        name = "function" + number;
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public String getDescription() {
        return null;
    }

    @Override
    public int getMinimumInputs() {
        return 0;
    }

    @Override
    public int getMaximumInputs() {
        return 0;
    }

    @Override
    public int getNumberOfOutputs(int numberOfInputs) {
        return 0;
    }

    @Override
    public void evaluate(long[] t, Vector inputs, Vector outputs) throws MathException {

    }

    @Override
    public Vector getInputVarNames() {
        return null;
    }

    @Override
    public Vector getOutputVarNames() {
        return null;
    }

    @Override
    public long getRequiredHistoryLength() {
        return 0;
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        return null;
    }
}
