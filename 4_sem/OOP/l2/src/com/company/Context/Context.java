package com.company.Context;
import com.company.Complex.Complex;

import java.util.ArrayDeque;

public class Context {
    private ArrayDeque<Complex> contextValues = new ArrayDeque<Complex>();

    public Complex pop() {
        return contextValues.pop();
    }

    public void push(Complex value) {
        contextValues.push(value);
    }
}
