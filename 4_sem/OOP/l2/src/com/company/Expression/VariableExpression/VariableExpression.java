package com.company.Expression.VariableExpression;

import com.company.Complex.Complex;
import com.company.Context.Context;
import com.company.Expression.Expression;

public class VariableExpression extends Expression {
    private Complex num;

    public VariableExpression(Complex num) {
        this.num = num;
    }

    @Override
    public void interpret(Context c) {
        c.push(num);
    }
}
