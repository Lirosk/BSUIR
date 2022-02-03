package com.company.Expression.TerminalExpressions;

import com.company.Context.Context;
import com.company.Expression.Expression;

public class TerminalExpressionMinus extends Expression {
    @Override
    public void interpret(Context c) {
        c.push(c.pop().minus(c.pop()));
    }
}
