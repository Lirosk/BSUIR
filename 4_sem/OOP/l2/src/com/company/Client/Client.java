package com.company.Client;

import com.company.Complex.Complex;
import com.company.Context.Context;
import com.company.Expression.Expression;
import com.company.Expression.TerminalExpressions.TerminalExpressionDivide;
import com.company.Expression.TerminalExpressions.TerminalExpressionMinus;
import com.company.Expression.TerminalExpressions.TerminalExpressionMultiply;
import com.company.Expression.TerminalExpressions.TerminalExpressionPlus;
import com.company.Expression.VariableExpression.VariableExpression;

import java.util.ArrayList;

public class Client {
    private final ArrayList<Expression> listExpression;

    public Client(String expression) {
        listExpression = parse(expression);
    }

    private ArrayList<Expression> parse(String expression) {
        ArrayList<Expression> list = new ArrayList<Expression>();

        expression = expression.replace(' ', '\0');
        expression += ' ';

        Expression operation = null;

        int j = 0;

        for (int i = 0; i < expression.length(); i++) {
            if (expression.charAt(i) == '(') {
                j = i;
                while (expression.charAt(i) != ')') {
                    i++;
                }

                list.add(new VariableExpression(Complex.parse(expression.substring(j+1, i))));
            }
            else if (Character.isDigit(expression.charAt(i))) {
                j = i;
                while (Character.isDigit(expression.charAt(i))) {
                    i++;
                }
                if (expression.charAt(i) == 'i' || expression.charAt(i) == 'I') {
                    i++;
                }

                list.add(new VariableExpression(Complex.parse(expression.substring(j, i))));
                i--;
            }
            else {
                switch (expression.charAt(i)) {
                    case ('+') -> operation = new TerminalExpressionPlus();
                    case ('-') -> operation = new TerminalExpressionMinus();
                    case ('*') -> operation = new TerminalExpressionMultiply();
                    case ('/') -> operation = new TerminalExpressionDivide();
                }
            }
        }

        list.add(operation);

        return list;
    }

    public Complex calculate() {
        Context context = new Context();

        for(Expression terminal: listExpression) {
            terminal.interpret(context);
        }

        return context.pop();
    }
}
